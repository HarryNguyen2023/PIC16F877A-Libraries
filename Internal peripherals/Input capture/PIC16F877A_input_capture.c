#include "PIC16F877A_input_capture.h"

// ------------------Static functions used only by internal functions and hidden from user---------------------

// Function to initiate the timer 1 in counter mode
static void timer1Init()
{
    // Reload the timer 1 register to 0
    TMR1 = 0;
    // Select the internal clock source for timer 1
    TMR1CS = 0;
    // Set the prescaler value to 1:1
    T1CKPS1 = 0;
    T1CKPS0 = 0;
    // Enable the timer 1
    TMR1ON = 1;
}

// Function to initiate the interrupt for CCP1 module
static void ccp1InterruptInit()
{
    CCP1IF = 0;
    // Enable CCP1 interrupt
    CCP1IE = 1;
    // Enable peripheral interrupt
    PEIE = 1;
    // Enable global interrupt
    GIE = 1;
}

// function to disable the CCP1 module
static void disableCCP1()
{
    CCP1CON &= 0b11110000;
}

// ----------------------------------Functions that interface with user----------------------------------------

// Function to initiate the input capture rising edge in PIC16F877A
void captureRisingInit()
{
    // Initiate the timer 1 timer mode
    timer1Init();
    // Configure the C2 bit to be input
    TRISC2 = 1;
    // Set the input capture rising edge mode for CCP1 module
    CCP1M3 = 0;
    CCP1M2 = 1;
    CCP1M1 = 0;
    CCP1M0 = 1;
    // Enable CCP1 interrupt
    ccp1InterruptInit();
}

// Function to initiate the input capture falling edge in PIC16F877A
void captureFallingInit()
{
    // Initiate the timer 1 timer mode
    timer1Init();
    // Configure the C2 bit to be input
    TRISC2 = 1;
    // Set the input capture falling edge mode for CCP1 module
    CCP1M3 = 0;
    CCP1M2 = 1;
    CCP1M1 = 0;
    CCP1M0 = 0;
    // Enable CCP1 interrupt
    ccp1InterruptInit();
}

// Function to switch the pre-scaler from rising edge to falling edge
void changeModeFalling()
{
    // Disable CCP1 interrupt
    CCP1IE = 0;
    // Turn off the CCP1
    disableCCP1();
    // Set the input capture falling edge mode for CCP1 module
    CCP1CON |= 0b00000100;
    // Enable CCP1 interrupt
    CCP1IE = 1;
}

// Function to switch the pre-scaler from falling edge to rising edge
void changeModeRising()
{
    // Disable CCP1 interrupt
    CCP1IE = 0;
    // Turn off the CCP1
    disableCCP1();
    // Set the input capture falling edge mode for CCP1 module
    CCP1CON |= 0b00000101;
    // Enable CCP1 interrupt
    CCP1IE = 1;
}

// Function to read the value of the input capture register
uint16_t readInputCapture1()
{
    uint16_t ccp1 = CCPR1;
    return ccp1;
}