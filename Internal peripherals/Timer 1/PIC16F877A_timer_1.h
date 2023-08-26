#ifndef PIC16F877A_TIMER_1_H
#define PIC16F877A_TIMER_1_H

#include <xc.h>

// Variable to define the type of pre-scaler of the timer 1 module
enum timer1_prescaler
{
    TIMER1_DIV_1,
    TIMER1_DIV_2,
    TIMER1_DIV_4,
    TIMER1_DIV_8
};

// Veriable to define if the counter is synchronous or asynchronous
enum counter_sync
{
    COUNTER_SYNC,
    COUNTER_ASYNC
};

void timer1TimerInit(uint8_t prescaler);
void timer1CounterInit(uint8_t prescaler, uint8_t sync);
uint16_t timer1Read(void);

#endif