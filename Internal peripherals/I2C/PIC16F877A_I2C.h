#ifndef PIC16F877A_I2C_H
#define PIC16F877A_I2C_H

#include <xc.h>

// Define the external crystal frequency
#define _XTAL_FREQ 16000000

// Define the I2C baud rate for standard mode
#define I2C_BAUD_RATE 100000

extern uint8_t I2C_slave_address;

void I2C_Master_Init(void);
void I2C_Slave_Init(uint8_t slave_address);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_ACK(void);
void I2C_NACK(void);
uint8_t I2C_Master_sendByte(uint8_t data);
uint8_t I2C_Master_readByte(uint8_t ack);
void I2C_Slave_dataHandling(uint8_t* rcv_data, uint8_t tx_data);

#endif