#ifndef PIC16F877A_INPUT_CAPTURE_H
#define PIC16F877A_INPUT_CAPTURE_H

#include <xc.h>

void captureRisingInit(void);
void captureFallingInit(void);
void changeModeRising(void);
void changeModeFalling(void);
uint16_t readInputCapture1();

#endif