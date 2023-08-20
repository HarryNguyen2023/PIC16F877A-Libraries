#ifndef HCH1000_H
#define HCH1000_H

#include "PIC16F877A_input_capture.h"

enum hch1000_phase
{
    IDLE,
    DONE
};

// Variable save the value of the humdity frequency
uint16_t hch1000_freq = 0;
uint8_t hch1000_state = IDLE;
uint16_t edgeT1 = 0;
uint16_t edgeT2 = 0;
uint16_t timer1_ovf = 0;

void HCH1000_Init(void);
float HCH1000_freqToHumidity(uint16_t hch1000_freq);
uint16_t HCH1000_getFreq(void);
void HCH1000_timer1Ovf(void);
void HCH1000_startMeasure(void);
uint8_t HCH1000_readFreq(void);

#endif