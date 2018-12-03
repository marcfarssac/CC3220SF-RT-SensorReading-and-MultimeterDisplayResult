/*
 * Copyright (c) 2016-2017, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== adcsinglechannel.c ========
 */
#include <stdint.h>
#include <stddef.h>

/* POSIX Header files */
#include <pthread.h>

/* Driver Header files */
#include <ti/drivers/ADC.h>
#include <ti/drivers/PWM.h>
#include <ti/display/Display.h>
#include <ti/drivers/GPIO.h>

/* Board Header files */
#include "Board.h"
//#include "ADCReading.h"

/* ADC sample count */
#define ADC_SAMPLE_COUNT  (10)

#define THREADSTACKSIZE   (768)

/* ADC conversion result variables */

uint16_t adcValue0;
bool calibrate;
uint32_t adcValue0MicroVolt;
uint16_t adcValue1[ADC_SAMPLE_COUNT];
uint32_t adcValue1MicroVolt[ADC_SAMPLE_COUNT];

/*
#ifdef __cplusplus
extern "C" {
#endif

typedef struct ADCReading adcReading;
void adcReading_setCalibration(bool enable);
bool adcReading_getCalibration();
void adcReading_setADCValue(uint16_t adcValue);
uint16_t ADCReading_getADCValue();

#ifdef __cplusplus
}
#endif
*/

static Display_Handle display;

/*
 *  ======== threadFxn0 ========
 *  Open an ADC instance and get a sampling result from a one-shot conversion.
 */
void *threadADCRead(void *arg0)
{
    ADC_Handle   adc;
    ADC_Params   params;
    int_fast16_t res;
    uint32_t   time = 50000;

    ADC_init();
    ADC_Params_init(&params);
    adc = ADC_open(Board_ADC0, &params);

    if (adc == NULL) {
        Display_printf(display, 0, 0, "Error initializing ADC channel 0\n");
        while (1);
    }

    /* Blocking mode conversion */

    while (1) {

    res = ADC_convert(adc, &adcValue0);
    //adcReading_setADCValue(adcValue0);

    if (res == ADC_STATUS_SUCCESS) {

        adcValue0MicroVolt = ADC_convertRawToMicroVolts(adc, adcValue0);

        Display_printf(display, 0, 0, "ADC channel 0 raw result: %d\n", adcValue0);
        Display_printf(display, 0, 0, "ADC channel 0 convert result: %d uV\n",
            adcValue0MicroVolt);
    }
    else {
        Display_printf(display, 0, 0, "ADC channel 0 convert failed\n");
    }
    usleep(time);

    }

    ADC_close(adc);

    return (NULL);
}

/*
 *  ======== threadFxn1 ========
 *  Open a ADC handle and get an array of sampling results after
 *  calling several conversions.
 */
void *threadADCWrite(void *arg0)
{
    /* Period and duty in microseconds */
    uint16_t   pwmPeriod = 4500;

    /* Sleep time in microseconds */
    uint32_t   time = 50000;
    PWM_Handle pwm1 = NULL;
    PWM_Params params;

    PWM_init();
    PWM_Params_init(&params);
    params.dutyUnits = PWM_DUTY_US;
    params.dutyValue = 0;
    params.periodUnits = PWM_PERIOD_US;
    params.periodValue = pwmPeriod;
    pwm1 = PWM_open(Board_PWM0, &params);
    if (pwm1 == NULL) {
        /* Board_PWM0 did not open */
        while (1);
    }

    PWM_start(pwm1);

    while (1) {

    if (calibrate) {PWM_setDuty(pwm1, (adcValue0 - 91.4)/0.827);}
    else {PWM_setDuty(pwm1, adcValue0);}
    usleep(time);
    }

    return (NULL);
}

/*
 *  ======== gpioButtonFxn3 ========
 *  Callback function for the GPIO interrupt on Board_GPIO_BUTTON1.
 *  This may not be used for all boards.
 */
void gpioButtonPushed(uint_least8_t index)
{
    /* Clear the GPIO interrupt and toggle an LED */
    //adcReading_setCalibration(!adcReading_getCalibration());
    calibrate = !calibrate;
    GPIO_toggle(Board_GPIO_LED0);
}

/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    pthread_t           threadRead, threadWrite;
    pthread_attr_t      attrs;
    struct sched_param  priParam;
    int                 retc;
    int                 detachState;

    calibrate = false;
    /* Call driver init functions */
    GPIO_init();

    GPIO_setConfig(Board_GPIO_LED0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(Board_GPIO_BUTTON0, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);

    /* install Button callback */
    GPIO_setCallback(Board_GPIO_BUTTON0, gpioButtonPushed);

    /* Enable interrupts */
    GPIO_enableInt(Board_GPIO_BUTTON0);

    Display_init();

    /* Open the display for output */
    display = Display_open(Display_Type_UART, NULL);
    if (display == NULL) {
        /* Failed to open display driver */
        while (1);
    }

    Display_printf(display, 0, 0, "Starting the adc\n");

    /* Create application threads */
    pthread_attr_init(&attrs);

    detachState = PTHREAD_CREATE_DETACHED;
    /* Set priority and stack size attributes */
    retc = pthread_attr_setdetachstate(&attrs, detachState);
    if (retc != 0) {
        /* pthread_attr_setdetachstate() failed */
        while (1);
    }

    retc |= pthread_attr_setstacksize(&attrs, THREADSTACKSIZE);
    if (retc != 0) {
        /* pthread_attr_setstacksize() failed */
        while (1);
    }

    /* Create threadFxn0 thread */
    priParam.sched_priority = 1;
    pthread_attr_setschedparam(&attrs, &priParam);

    retc = pthread_create(&threadRead, &attrs, threadADCRead, NULL);
    if (retc != 0) {
        /* pthread_create() failed */
        while (1);
    }

    retc = pthread_create(&threadWrite, &attrs, threadADCWrite, NULL);
    if (retc != 0) {
        /* pthread_create() failed */
        while (1);
    }

    return (NULL);
}
