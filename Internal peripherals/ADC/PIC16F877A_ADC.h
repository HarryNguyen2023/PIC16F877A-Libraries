#ifndef PIC16F877A_ADC_H
#define PIC16F877A_ADC_H

#include <xc.h>

// Define the external crystal frequency
#define _XTAL_FREQ 16000000

void ADC_Init(uint8_t* adc_channel, uint8_t len);
uint16_t ADC_Read(uint8_t adc_channel);
float ADC_lm35toDeg(uint16_t negative_deg, uint16_t positive_deg);

#endif