#include "TC72.h"

// Define the external crystal frequency
#define _XTAL_FREQ 16000000

//----------------------------------------Function used to interface with the users-------------------------------------------

// Function to write to TC72
void TC72_Write(uint8_t address, uint8_t value)
{
    // Enable sensor communication
    CE = 1;
    // Access the register of the sensor
    SPI_Tx_Byte(address);
    // Write the desired value to the register
    SPI_Tx_Byte(value);
    // Stop the communication
    CE = 0;
}

// Function to initiate the TC72
void TC72_Init()
{
    // Initiate the SPI master mode
    SPI_Master_Init();
    // Configure SS pin as output and high active
    TRISCE = 0;
    CE = 0;
    // Wake up the sensor from shutdown mode and prepare for one-shot mode
    TC72_Write(CONTROL_REG, ONE_SHOT);
    // Wait for the sensor to set up completely
    __delay_ms(150);
}

// Function to directly read the data from the TC72 sensor
int TC72_Read()
{
    // Activate one-shot mode
    TC72_Write(CONTROL_REG, SET);
    // Reading operation
    CE = 1;
    SPI_Tx_Byte(TEMPR_REG);
    uint8_t msb = SPI_Rx_byte();
    uint8_t lsb = SPI_Rx_byte();
    // Wait until reading completed
    CE = 0;
    return (msb << 8) + lsb;
}


// Function to convert the sensor output to real temperature value
float TC72_toFloat(signed int temp)
{
    float result = (float)(temp >> 8);      //Discard LSByte (Only holds fraction flag bits)
    char count = temp & FRAC_FLAG;          
    if(count) 
    {
        count = count >> 6; 
        result += (count * 0.25);
    }
    return result;
}

// Function for user to read the temperature of the TC72 sensor in single shot mode
float TC72_readTemp()
{
    int sensor_output = TC72_Read();
    return TC72_toFloat(sensor_output);
}



