#ifndef PIC16F877A_SPI
#define PIC16F877A_SPI

#include <xc.h>

// Maimum number slave can be connected to the MCU
#define MAX_MATRIX 8

// Number of slave interact with the MCU
#define SLAVE_NUM 1

// Define the order of the slaves
#define MAX7219 1

// Array of slave select pins
uint8_t SS_pin[MAX_MATRIX] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

// Variable to keep track the reception via SPI
extern uint16_t spi_str_idx;

void SPI_Master_Init(void);
void SPI_Slave_Init(void);
void SS_Enable(uint8_t slave);
void SS_Disable(uint8_t slave);
void SPI_Tx_Byte(uint8_t data);
void SPI_Tx_String(char* string);
uint8_t SPI_Rx_Byte_Interrupt(void);
uint8_t SPI_Rx_String_Interrupt(uint8_t* string, uint16_t len);
uint8_t SPI_Rx_byte(void);

#endif