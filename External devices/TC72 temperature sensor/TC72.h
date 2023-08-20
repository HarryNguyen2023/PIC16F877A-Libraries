#ifndef TC72_H
#define TC72_H

#include <xc.h>
#include "PIC16F877A_SPI.h"

// Define chip select pin for the SPI (Active High)
#define CE RC2
#define TRISCE TRISC2

// Define register and data mode
#define CONTROL_REG   0x80
#define START_CONV    0x10
#define ONE_SHOT      0x05
#define SET           0x15
#define TEMPR_REG     0x02
#define FRAC_FLAG     0x00C0

void TC72_Write(uint8_t address, uint8_t value);
void TC72_Init(void);
int TC72_Read(void);
float TC72_toFloat(signed int temp);
float TC72_readTemp(void);

#endif