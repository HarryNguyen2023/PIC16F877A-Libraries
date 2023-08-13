#ifndef PIC16F877A_TIMER0_H
#define PIC16F877A_TIMER0_H

#include <xc.h>

// Define the pre-scaler value 
enum pre_scaler
{
    TIMER0_DIV_1 = 1,
    TIMER0_DIV_2 = 2,
    TIMER0_DIV_4 = 4,
    TIMER0_DIV_8 = 8,
    TIMER0_DIV_16 = 16,
    TIMER0_DIV_32 = 32,
    TIMER0_DIV_64 = 64,
    TIMER0_DIV_128 = 128,
    TIMER0_DIV_256 = 256
};

// Define the edge 
enum timer0_edge
{
    TIMER0_RISING,
    TIMER0_FALLING
};

void timer0TimerInit(uint16_t prescaler);
void timer0CounterInit(uint16_t prescaler, uint8_t edge);

#endif