#ifndef MOTOR_PID_H
#define MOTOR_PID_H

#include <xc.h>

typedef enum
{
    MOTOR_STOP,
    MOTOR_CCW,
    MOTOR_CW
}motor_direction;

// Variable
extern float pid_current_error;
extern float pid_prev_error;
extern float target_position;
extern float current_position;
extern float integral_error;
extern float derivative_error;
extern float delta_time;

extern void (*dutyCycleChange)(uint16_t duty_cycle);
extern void (*motorDirectionControl)(motor_direction direc);

float pidControlValue(float Kp, float Ki, float Kd);
void positionMotorControl(void (*setDutyCycle)(uint16_t duty_cycle), float Kp, float Ki, float Kd);
void setDirectionControlFunction(void (*directionControl)(motor_direction direc));

#endif