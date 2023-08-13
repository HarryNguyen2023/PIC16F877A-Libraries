#include "PIC16F877A_timer0.h"

// ------------------Static functions used only by internal functions and hidden from user---------------------

// Function to assign the pre-scaler value to the Timer 0 
static void timer0SetPrescaler(uint16_t prescaler)
{
    switch(prescaler)
    {
        case TIMER0_DIV_1:
            PSA = 1;
            PS2 = 0;
            PS1 = 0;
            PS0 = 0;
            break;
        case TIMER0_DIV_2:
            PS2 = 0;
            PS1 = 0;
            PS0 = 0;
            break;
        case TIMER0_DIV_4:
            PS2 = 0;
            PS1 = 0;
            PS0 = 1;
            break;
        case TIMER0_DIV_8:
            PS2 = 0;
            PS1 = 1;
            PS0 = 0;
            break;
        case TIMER0_DIV_16:
            PS2 = 0;
            PS1 = 1;
            PS0 = 1;
            break;
        case TIMER0_DIV_32:
            PS2 = 1;
            PS1 = 0;
            PS0 = 0;
            break;
        case TIMER0_DIV_64:
            PS2 = 1;
            PS1 = 0;
            PS0 = 1;
            break;
        case TIMER0_DIV_128:
            PS2 = 1;
            PS1 = 1;
            PS0 = 0;
            break;
        case TIMER0_DIV_256:
            PS2 = 1;
            PS1 = 1;
            PS0 = 1;
            break;
    }
    return;
}

// ----------------------------------Functions that interface with user----------------------------------------

// Function to initiate the timer 0 timer module according to the working cycle of input micro second
void timer0TimerInit(uint16_t prescaler)
{
    // Set the pre-load value for the Timer 0
    TMR0 = 0;
    // Enable timer mode 
    T0CS = 0;
    // Assign pre-scaler to Timer 0
    PSA = 0;
    // Assign the corresponding pre-scaler value
    timer0SetPrescaler(prescaler);
    // Enable Timer 0 interrupt
    TMR0IF = 0;
    TMR0IE = 1;
    GIE = 1;
}

// Function to initiate the Timer 0 counter mode
void timer0CounterInit(uint16_t prescaler, uint8_t edge)
{
    // Configure input pin
    TRISA4 = 1;
    // Set pre load value
    TMR0 = 0;
    // Enable counter mode
    T0CS = 1;
    // Configure the type of edge 
    T0SE = (edge == TIMER0_RISING) ? 0 : 1;
    // Assign the pre-scaler to Timer 0
    PSA = 0;
    // Set the pre-scaler value
    timer0SetPrescaler(prescaler);
}

