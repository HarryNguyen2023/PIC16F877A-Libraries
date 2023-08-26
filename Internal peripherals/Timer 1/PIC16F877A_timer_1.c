#include "PIC16F877A_timer_1.h"

// Function to initiate the timer 1 timer module
void timer1TimerInit(uint8_t prescaler)
{
    // Set the pre-scaler value for the the timer 1
    T1CON |= prescaler << 4;
    // Enable timer 1 timer mode
    TMR1CS = 0;
    // Enable timer 1 
    TMR1ON = 1;
    // Enable timer 1 interrupt
    TMR1IF = 0;
    TMR1IE = 1;
    PEIE = 1;
    GIE = 1;
}

// Function to initiate the timer 1 counter mode
void timer1CounterInit(uint8_t prescaler, uint8_t sync)
{
    // Set the pre-scaler value for the the timer 1
    T1CON |= prescaler << 4;
    // Enable timer 1 timer mode
    TMR1CS = 1;
    // Configure if the external pulse is synchronous to the internal phase clock
    T1OSCEN = (sync) ? 1 : 0;
    // Enable timer 1 
    TMR1ON = 1;
}

// Function to read the value of the timer 1 register
uint16_t timer1Read()
{
    return TMR1;
}
