#ifndef DS3231_H
#define DS3231_H

#include "PIC16F877A_I2C.h"

// Define the slave address
#define DS3231_SLAVE_ADD 0xD0

// Initiate the structure to store the time information 
typedef struct DS3231_time
{
    uint8_t second;
    uint8_t minute;
    uint8_t hour;
    uint8_t date;
    uint8_t month;
    uint8_t year;
}DS3231_time;

void DS3231_Init(DS3231_time initial_time);
void DS3231_getCurrentTime(DS3231_time* ds3231_time);

#endif