#ifndef COMPRESSOR_MOTOR_H
#define COMPRESSOR_MOTOR_H

#include <xc.h>

#define TRISDC1 TRISD1
#define TRISDC2 TRISD2
#define DC1 RD1
#define DC2 RD2

void compressorMotor_Init(void);
void SpeedControl(float Kp, float targetVal, float nowVal);

#endif