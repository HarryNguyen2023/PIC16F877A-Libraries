#include "PIC16F877A_HCSR04.h"

// ------------------Static functions used only by internal functions and hidden from user---------------------

// Trigger pins configuration
static void trigConfig()
{
    // Sequentially define the trigger pins of each HCSR04 sensor
    TRISD0 = 0;
    TRIG1 = 0;
}

// Function to calculate the distance from the HCSR04 sensor
static float calDistance()
{
    float time = ((fallT2 - riseT1) / 2.0) / _XTAL_FREQ * 4;
    float distance = SOUND_SPEED * time;
    return distance;
}

// Define some private variables
uint8_t hcsr04_state = IDLE;
uint16_t riseT1 = 0;
uint16_t fallT2 = 0;
float hcsr04_distance = 0;

// ----------------------------------Functions that interface with user----------------------------------------

// Function to initiate the HCSR04 sensor
void hcsr04Init()
{
    // configure trigger pins
    trigConfig();
    // Initiate the input capture CCP1 module
    captureRisingInit();
}

// Function to send the trigger pulse to the HCSR04
void hcsr04Trigger()
{
    TRIG1 = 1;
    __delay_us(10);
    TRIG1 = 0;
    // Set the timer 1 pre load register to 0
    TMR1 = 0;
}

// Function to get the value of the distance from the HCSR04 sensor and will be called inside the interrupt function
uint8_t hcsr04Distance()
{
    if (hcsr04_state == IDLE)
    {
        riseT1 = CCPR1;
        // Change input capture mode to falling edge
        changeModeFalling();
        hcsr04_state = DONE;
        return IDLE;
    }
    else if (hcsr04_state == DONE)
    {
        fallT2 = CCPR1;
        hcsr04_distance = calDistance();
        // Change input capture mode to rising edge
        changeModeRising();
        hcsr04_state = IDLE;
        return DONE;
    }
}

// Function to get the distance of the HCSR04 sensor
float getDistance()
{
    return hcsr04_distance;
}