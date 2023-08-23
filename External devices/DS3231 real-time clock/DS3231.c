#include "DS3231.h"

// ---------------------------------------- Static functions hidden from users ------------------------------------------

// Function to convert data from BCD to decimal
static uint8_t BCD_2_DEC(uint8_t to_convert)
{
    return (to_convert >> 4) * 10 + (to_convert & 0x0F); 
}

// Function to convert data from decimal to BCD
static uint8_t DEC_2_BCD(uint8_t to_convert)
{
    return ((to_convert / 10) << 4) + (to_convert % 10);
}

// Function to initiate set the time for the real-time clock module for the first timer power up
static void DS3231_setTime(DS3231_time initial_time)
{
    I2C_Start();       
    I2C_Master_sendByte(DS3231_SLAVE_ADD); 
    // Send the register to start writing 
    I2C_Master_sendByte(0);  
    I2C_Master_sendByte(DEC_2_BCD(initial_time.second));    //update sec
    I2C_Master_sendByte(DEC_2_BCD(initial_time.minute));    //update min
    I2C_Master_sendByte(DEC_2_BCD(initial_time.hour));      //update hour
    I2C_Master_sendByte(0);                                 //ignore updating day in week
    I2C_Master_sendByte(DEC_2_BCD(initial_time.date));                   //update date
    I2C_Master_sendByte(DEC_2_BCD(initial_time.month));                  //update month
    I2C_Master_sendByte(DEC_2_BCD(initial_time.year));                   //update year
    I2C_Stop();
}

// ------------------------------------------ General functions interface with the user ------------------------------------------

// Function to initiate the DS3231 real-time clock module
void DS3231_Init(DS3231_time initial_time)
{
    // Initiate the I2C communication
    I2C_Master_Init();
    // Set the initial time for the real-time clock
    DS3231_setTime(initial_time);
    return;
}

// Function to get the current time from the real-time clock
void DS3231_getCurrentTime(DS3231_time* ds3231_time)
{
    // Start by writing the register we want to start to read
    I2C_Start();       
    I2C_Master_sendByte(DS3231_SLAVE_ADD); 
    I2C_Master_sendByte(0);
    I2C_Stop();
    
     //Start the reading process
    I2C_Start(); 
    I2C_Master_sendByte(DS3231_SLAVE_ADD + 1);   
    // // Read from the second register to year register
    ds3231_time->second = BCD_2_DEC(I2C_Master_readByte(1));        
    ds3231_time->minute = BCD_2_DEC(I2C_Master_readByte(1)); 
    ds3231_time->hour = BCD_2_DEC(I2C_Master_readByte(1));  
    I2C_Master_readByte(1);
    ds3231_time->date = BCD_2_DEC(I2C_Master_readByte(1));  
    ds3231_time->month = BCD_2_DEC(I2C_Master_readByte(1));  
    ds3231_time->year = BCD_2_DEC(I2C_Master_readByte(0));
    I2C_Stop(); 
}