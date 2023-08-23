#include "MAX7219_DotMatrix.h"

// ------Static functions which are only called by other main function and not visible to user------

// Function to write a specific data to the MAX7219 register at one time
static void TxByte(uint8_t slave, uint8_t col, uint8_t data)
{
    // Enable data transmission
    SS_Enable(slave);
    // Transmit data
    SPI_Tx_Byte(col);
    SPI_Tx_Byte(data);
    // Disable transmission
    SS_Disable(slave);
}

// ---------------------------------------Functions to be used by user-----------------------------------------

// Function to initiate the dot matrix driver
void Matrix_Init()
{
    // Initiate the SPI module in master mode
    SPI_Master_Init();
    
    // Configure the Max7219 dot matrix
    for(uint8_t i = 1; i <= SLAVE_NUM; ++i)
    {
        // Set the BCD decode mode to no decode
        TxByte(i, 0x09, 0x00);
        
        // Set the unit brightness level
        TxByte(i, 0x0A, 0x08);
        
        // Set display refresh for digit 0-7
        TxByte(i, 0x0B, 0x07);
        
        // Turn on the display
        TxByte(i, 0x0C, 0x01);
        
        // Display test
        TxByte(i, 0x0F, 0x00);
    }
}

// Function to clear the display on the dot matrix
void Matrix_Clear(uint8_t slave)
{
    for(uint8_t j = 1; j < 9; ++j)
        TxByte(slave, j, 0x00);
}

// Function to display a character on the dot matrix
void Matrix_Write_Char(uint8_t slave, uint8_t data)
{
    uint8_t col = 1;
    uint8_t font = 5;
    
    // Limit detection
    if(data > 9)
        return;
    
    TxByte(slave, col, 0x00);
    for(col = 2; col <= font + 1; ++col)
        TxByte(slave, col, FONT_7x5[data][col - 2]);
    TxByte(slave, col, 0x00);
}

// Function to change the brightness intensity ò the dot matrix
void Matrix_Intensity(uint8_t slave, uint8_t intensity)
{
    if(intensity > 15)
        intensity = 15;
    TxByte(slave, 0x0A, intensity);
}