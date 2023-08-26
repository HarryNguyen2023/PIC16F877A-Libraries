#ifndef SERVO_MOTOR_COMPARE_H
#define SERVO_MOTOR_COMPARE_H

#include "PIC16F877A_timer_1.h"

// Define the pin to control the servo motor
#define TRISM TRISC2
#define MOTOR RC2

// Variable to initiate the servo motor frequency 
uint16_t TIME1 = 55536;
uint16_t DC_RANGE = 10000;

void servoInit(void);
void servoAngle(uint8_t angle);
void servoShiftHigh(void);

#endif