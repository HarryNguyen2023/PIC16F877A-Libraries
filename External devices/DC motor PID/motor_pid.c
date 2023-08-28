#include "motor_pid.h"
#include <math.h>

// Define the function to vary the speed of the motor by changing the PWM duty cycle
void (*dutyCycleChange)(uint16_t duty_cycle);
// Define the function to control the direction of the motor
void (*motorDirectionControl)(motor_direction direc);

// Define some variables
float pid_current_error = 0;
float pid_prev_error = 0;
float integral_error = 0;
float derivative_error = 0;

// Function to calculate the output of the PID controller
float pidControlValue(float Kp, float Ki, float Kd)
{
    // Get the current error of the controller
    pid_current_error = target_position - current_position;
    // Get the integral of error using trapezoidal principle
    integral_error += delta_time * (pid_current_error + pid_prev_error) / 2;
    // Get the derivative of the error using backward derivative theorem
    derivative_error = (pid_current_error - pid_prev_error) / delta_time;
    // Assign the new value of the previous error
    pid_prev_error = pid_current_error;
    // Get the output value of the PID controller
    return (Kp * pid_current_error) + (Ki * integral_error) + (Kd * derivative_error);
}

// Function to control the position of the motor
void positionMotorControl(void (*setDutyCycle)(uint16_t duty_cycle), float Kp, float Ki, float Kd)
{
    dutyCycleChange = setDutyCycle;
    // Get the output value of the PID controller
    float pid_control_value = pidControlValue(Kp, Ki, Kd);
    // Define the direction of the motor
    motor_direction direction;
    if(pid_control_value > 0)
        direction = MOTOR_CCW;
    else if(pid_control_value < 0)
        direction = MOTOR_CW;
    else
        direction = MOTOR_STOP;
    // Get the absolute value of the controller as well as the duty cycle value
    uint16_t pwm_duty_cycle = (uint16_t)fabs(pid_control_value);
    // Rescale the duty cycle value to avoid motor backlash
    if(pwm_duty_cycle > 1023)
        pwm_duty_cycle = 1023;
    else if(pwm_duty_cycle < 85)
        pwm_duty_cycle = 85;
    // Control the speed as well as the direction of the motor
    if(motorDirectionControl)
        motorDirectionControl(direction);
    // Set the value of the duty cycle for the PWM
    if(dutyCycleChange)
        setDutyCycle(pwm_duty_cycle);
}

// Function to set the function to control the direction of the motor
void setDirectionControlFunction(void (*directionControl)(motor_direction direc))
{
    motorDirectionControl = directionControl;
}