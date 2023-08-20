#include "PIC16F877A_SPI.h"

uint16_t spi_str_idx = 0;

// Function to initiate MCU in SPI master mode
void SPI_Master_Init()
{
    // Configure PORTD to output 
    TRISD = 0x00;
    // Initiate the master mode with data rate Fosc/16
    SSPM3 = 0;
    SSPM2 = 0;
    SSPM1 = 0;
    SSPM0 = 0;
    // Enable SPI module
    SSPEN = 1;
    // Clock edge configuration (SPI mode num. 1)
    CKP = 0;
    CKE = 0;
    // Sample at middle 
    SMP = 0;
    // Configure I/O pins
    TRISC5 = 0;     // SDO
    TRISC4 = 1;      // SDI
    TRISC3 = 0;     // SCK
    // Enable SPI interrupt
//    SSPIE = 1;
//    PEIE = 1;
//    GIE = 1;
}

// Function to initiate MCU in SPI slave mode
void SPI_Slave_Init()
{
    // Initiate the master mode with data rate Fosc/16
    SSPM3 = 0;
    SSPM2 = 1;
    SSPM1 = 0;
    SSPM0 = 0;
    // Enable SPI module
    SSPEN = 1;
    // Clear the SMP bit
    SMP = 0;
    // Clock edge configuration (SPI mode num. 1)
    CKP = 0;
    CKE = 0;
    // Configure I/O pins
    TRISC5 = 0;     // SDO
    TRISC4 = 1;     // SDI
    TRISC3 = 0;     // SCK
    TRISA5 = 1;     // SS
    // Configure the A/D converter
    PCFG3 = 0;
    PCFG2 = 1;
    PCFG1 = 0;
    PCFG0 = 0;
    // Enable SPI interrupt
    SSPIE = 1;
    PEIE = 1;
    GIE = 1;
}

// Function to enable the serial line with the specific slave
void SS_Enable(uint8_t slave)
{
    if(slave < 1)
        return;
    PORTD = ~SS_pin[slave - 1];
}

// Function to disable the serial line with the specific slave
void SS_Disable(uint8_t slave)
{
    if(slave < 1)
        return;
    PORTD = 0xFF;
}

// Function to transmit a byte via SPI
void SPI_Tx_Byte(uint8_t data)
{
    SSPBUF = data;
    while(!SSPSTATbits.BF);
    // Clear write collision bit
    if(WCOL)
        WCOL = 0;
}

// Function to transmit a string via SPI
void SPI_Tx_String(char* string)
{
    for(uint16_t i = 0; string[i] != '\0'; ++i)
        SPI_Tx_Byte(string[i]);
}

// Function to receive data via SPI
uint8_t SPI_Rx_Byte_Interrupt()
{
    uint8_t rcv_char = SSPBUF;
    return rcv_char;
}

// Function to receive a string via SPI
uint8_t SPI_Rx_String_Interrupt(uint8_t* string, uint16_t len)
{
    if(spi_str_idx == len - 1)
    {
        string[spi_str_idx++] = SSPBUF;
        string[spi_str_idx] = 0;
        return 1;
    }
    else
    {
        string[spi_str_idx++] = SSPBUF;
        return 0;
    }
}

// Function to read SPI without using interrupt
uint8_t SPI_Rx_byte()
{
    SSPBUF = 0;
    while(!SSPSTATbits.BF);
    return SSPBUF;
}