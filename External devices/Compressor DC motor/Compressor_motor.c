#include "Compressor_motor.h"

#define _XTAL_FREQ 16000000
#define PWM_FREQ 2000
#define PWM_RANGE _XTAL_FREQ/(16*PWM_FREQ)

// ----------------------------------------------Static functions hidden from user---------------------------------------------------

// Function to configure PWM mode for CCP1
static void PWM_Init(void){
    // Configure RC2 as output pin
    TRISC2 = 0;
    // Configure PWM mode in CCPCON
    CCP1M3 = 1;
    CCP1M2 = 1;
}

// Function to configure Timer2 
static void Timer2_Init(void){
    // Assign the PWM frequency to be 2kHz at pre-scaler 16
    PR2 = (PWM_RANGE / 4) - 1;
    // Use pre-scaler 1:16
    T2CKPS1 = 1;
    T2CKPS0 = 1;
}

// Function to calculate the output value of the P controller for the compressor motor
static uint16_t proportionalControl(float Kp, float targetVal, float nowVal){
    // Get the output value of the P controller
    uint16_t controlSignal = Kp * (targetVal - nowVal);
    return controlSignal;
}

// Function to control the speed of the motor based on the duty cycle
static void DC_Speed(uint16_t dutyCycle){
    if(dutyCycle <= PWM_RANGE)
    {
        // Get the 2 LSB-bit
        CCP1CONbits.CCP1Y = (dutyCycle) & 1;
        CCP1CONbits.CCP1X = (dutyCycle) & 2;
        // Move 8 MSB-bit to CCPRL
        CCPR1L = (dutyCycle) >> 2;
        // Activate Timer 2
        TMR2ON = 1;
    }  
}

//------------------------------------------------General functions to interface with users----------------------------------------

// Function to initiate the PID module
void compressorMotor_Init()
{
    // Configure I/O pins to control the motor
    TRISDC1 = 0;
    TRISDC2 = 0;
    DC1 = 0;
    DC2 = 0;
    // Peripherals initialization
    PWM_Init();
    Timer2_Init();
}


void SpeedControl(float Kp, float targetVal, float nowVal)
{
    // Get the PID value
    uint16_t PWMval = proportionalControl(Kp, targetVal, nowVal);
    // Re-scale the PWM signal
    if(PWMval > PWM_RANGE)
        PWMval = PWM_RANGE;
    else if(PWMval < 70)
        PWMval = 0;
    // Turn on the motor
    if(PWMval == 0)
    {
        DC1 = 0;
        DC2 = 0;
    }
    else
    {
        DC1 = 1;
        DC2 = 0;
    }
    DC_Speed(PWMval);
}
