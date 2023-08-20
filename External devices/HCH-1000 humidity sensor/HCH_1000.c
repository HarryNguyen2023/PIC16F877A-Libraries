#include "HCH_1000.h"

#define _XTAL_FREQ 16000000

// ------------------Static functions used only by internal functions and hidden from user---------------------

// Function to get the actual frequency of the HCH-1000 sensor
static uint16_t HCH1000_calFreq()
{
    long unsigned int timer1_ticks = edgeT2 + (timer1_ovf * 65536) - edgeT1;
    return (uint16_t)((_XTAL_FREQ / timer1_ticks) / 4);
} 

static void HCH1000_stopMeasure()
{
    CCP1CON &= 0b11110000;
}

// ----------------------------------Functions that interface with user----------------------------------------

// Function to initiate the HCH-1000 humidity sensor
void HCH1000_Init()
{
    // Configure the input capture to timer 1 timer mode
    captureRisingInit();
    // Enable timer 1 interrupt
    TMR1IF = 0;
    TMR1IE = 1;
}

// Function to get the frequency of the HCH-1000 humidity sensor
uint16_t HCH1000_getFreq()
{
    return hch1000_freq;
}

// Function to put inside the timer 1 interrupt service handling to get the number of timer 1 overflow
void HCH1000_timer1Ovf()
{
    timer1_ovf++;
}

// Function to convert the HCH-1000 frequency to Celsius degree temperature
float HCH1000_freqToHumidity(uint16_t freq)
{
    return 565.1 - 0.076725 * freq;
}

// Function to start the measurement of the HCH-1000
void HCH1000_startMeasure()
{
    CCP1CON |= 0b00000101;
}

// Function to get the frequency of the HCH-1000 humidity sensor using input capture
uint8_t HCH1000_readFreq()
{
    if(hch1000_state == IDLE)
    {
        edgeT1 = CCPR1;
        timer1_ovf = 0;
        hch1000_state = DONE;
        return 0;
    }
    else
    {
        edgeT2 = CCPR1;
        hch1000_freq = HCH1000_calFreq();
        hch1000_state = IDLE;
        // Stop the measurement for a time
        HCH1000_stopMeasure();
        return 1;
    }
}