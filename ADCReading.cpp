/*
 * ADCReading.cpp
 *
 *  Created on: 2 dic. 2018
 *      Author: marcf
 */

#include <ADCReading.h>
#include <stdint.h>

ADCReading::ADCReading()
{
adcValue0 = 0;
calibrate = false;
}

void ADCReading::setCalibration(bool onOff)
{
     calibrate = onOff;
}

bool ADCReading::getCalibration()
{
     return calibrate;
}

void ADCReading::setADCValue(uint16_t adcValue)
{
    adcValue0 = adcValue;
}

uint16_t ADCReading::getADCValue()
{

    uint16_t returnValue;
    returnValue = adcValue0;

    if (calibrate)
    {
        returnValue = ((adcValue0 - 91.4)/0.827);
    }

    return returnValue;
}


ADCReading::~ADCReading()
{
    // TODO Auto-generated destructor stub
}

