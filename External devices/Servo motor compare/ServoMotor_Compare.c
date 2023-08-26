#include "ServoMotor_compare.h"

// Function to configure Capture Mode
static void compareInit()
{
    // Set compare mode with clear output
    CCP1M3 = 1;
    CCP1M2 = 0;
    CCP1M1 = 0;
    CCP1M0 = 1;
    // Set the desired compare value so that the motor is position at 0 degree
    CCPR1 = TIME1 + (DC_RANGE / 20);
}

// Function to initiate servo motor
void servoInit()
{
    // Configure I/O pins
    TRISM = 0;
    MOTOR = 1;
    // Initiate the timer 1 timer module
    TMR1 = TIME1;
    timer1TimerInit(TIMER1_DIV_8);
    // Initiate the compare module
    compareInit();
}

// Function to drive the servo motor to desired angle position
void servoAngle(uint8_t angle)
{
    if(angle <= 180)
    {
        uint16_t duty_cycle = (uint16_t)((100 * angle) / 36.0) + TIME1 + (DC_RANGE / 20);
        CCPR1 = duty_cycle;
    }
}

// Function to be called inside of the interrupt service routine to change the edge of the pulse
void servoShiftHigh()
{
    // Reload the pre-load value of the timer1 register
    TMR1 = TIME1;
    // Disable the compare module for a quite
    CCP1CON = 0x00;
    // Change the status to HIGH
    MOTOR = 1;
    // Reset the compare module
    CCP1CON = 0x09;
}