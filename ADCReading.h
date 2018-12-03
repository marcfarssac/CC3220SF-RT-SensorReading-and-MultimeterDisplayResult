/*
 * ADCReading.h
 *
 *  Created on: 2 dic. 2018
 *      Author: marcf
 */
#include <stdint.h>

#ifndef ADCREADING_H_
#define ADCREADING_H_

#ifdef __cplusplus


class ADCReading
{
private:
    uint16_t adcValue0;
    bool calibrate;
public:
    ADCReading();
    void setCalibration(bool enable);
    bool getCalibration();
    void setADCValue(uint16_t adcValue);
    uint16_t getADCValue();
    virtual ~ADCReading();
};

#endif /* cpluplus */
#endif /* ADCREADING_H_ */
