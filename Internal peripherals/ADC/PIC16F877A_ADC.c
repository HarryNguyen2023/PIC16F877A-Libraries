#include "PIC16F877A_ADC.h"

//---------------------------------------------------- Static funcitons-------------------------------------------------------

static void ADC_setInput(uint8_t* adc_channel, uint8_t len)
{
    for(uint8_t i = 0; i < len; ++i)
    {
        switch(adc_channel[i])
        {
            case 0:
                TRISA0 = 1;
                break;
            case 1:
                TRISA1 = 1;
                break;
            case 2:
                TRISA2 = 1;
                break;
            case 3:
                TRISA3 = 1;
                break;
            case 4:
                TRISA5 = 1;
                break;
            case 5:
                TRISE0 = 1;
                break;
            case 6:
                TRISE1 = 1;
                break;
            case 7:
                TRISE2 = 1;
                break;
        }
    }
    return;
}

// ------------------------------------------------ General functions ----------------------------------------------------

// Function to initiate the ADC module
void ADC_Init(uint8_t* adc_channel, uint8_t len)
{
    // Configure the specific ADC channel to be input pins
    ADC_setInput(adc_channel, len);
    // Configure the ADC module with clock source Fosc/64
    ADCON0 = 0x81;
    ADCON1 = 0xC0;
}

// Function to read the data from a specific channel
uint16_t ADC_Read(uint8_t adc_channel)
{
    if(adc_channel > 7)
        return 0;
    
    // Clear the channel selection bit
    ADCON0 &= 0b11000101;
    // Select the desired channel
    ADCON0 |= adc_channel << 3;
    // Wait for the acquisition time 
    __delay_us(30);
    // Activate the ADC sampling
    GO_DONE = 1;
    // Waiting for the conversion to be completed
    while(ADCON0bits.GO_DONE);
    return ((ADRESH << 8) + ADRESL);
}

// Function to convert raw data from ADC module to Celsius degree
float ADC_lm35toDeg(uint16_t negative_deg, uint16_t positive_deg)
{
    return (positive_deg - negative_deg) * 500 / 1023.0f;
}