#include "PIC16F877A_I2C.h"

uint8_t I2C_slave_address;

// -------------------------------------------Static functions hidden form users---------------------------------------------

// Function to wait for the previous transmission to complete and the SDA line is in IDLE state for transmission
static void I2C_Wait()
{
    while((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}

// Function to get the data sent by the master in slave mode
static uint8_t I2C_Slave_readByte()
{
    // Read the data
    char dummy = SSPBUF;
    // Wait for read complete
    while(!BF);
    // Replace data by your data storage variable
    uint8_t rcv_data = SSPBUF;
    // Release the clock line
    CKP = 1;
    // Get the data
    return rcv_data;
}

// Function to transmit data asked by the master
static void I2C_Slave_sendByte(uint8_t tx_data)
{
    char dummy = SSPBUF;
    // Replace data by your data t be transmit
    SSPBUF = tx_data;
    // Release the clock line
    CKP = 1;
    // Wait for transmit to be completed
    while(BF);
}

// Function to handle collision bus problem 
static void I2C_collisionHandling()
{
    // Read the data
    char dummy = SSPBUF;
    // Clear the error flag bits
    WCOL = 0;
    SSPOV = 0;
    // Release the clock line
    CKP = 1;
}

// ----------------------------------------General functions to interface with users-----------------------------------------

// Function to initiate the I2C master mode
void I2C_Master_Init()
{
    // Configures the SDA and SCL pins
    TRISC3 = 1;
    TRISC4 = 1;
    // Enable synchronous serial port
    SSPEN = 1;
    // Configure I2C master mode
    SSPM3 = 1;
    SSPM2 = 0;
    SSPM1 = 0;
    SSPM0 = 0;
    // Configure other registers
    SSPCON2 = 0x00;
    SSPSTAT = 0x80;
    // Configure the baud rate register
    SSPADD = ((_XTAL_FREQ / 4) / I2C_BAUD_RATE) - 1;
}

// Function to initiate I2C slave mode
void I2C_Slave_Init(uint8_t slave_address)
{
    // Configure SDA and SCL pins
    TRISC3 = 1;
    TRISC4 = 1;
    // Configure the address of the slave
    SSPADD = slave_address;
    I2C_slave_address = slave_address;
    // Configure the I2C slave 7-bit mode
    SSPM3 = 0;
    SSPM2 = 1;
    SSPM1 = 1;
    SSPM0 = 0;
    // Release the clock 
    CKP = 1;
    // Enable synchronous serial port
    SSPEN = 1;
    // Enable slave transmit and slave receive clock stretch
    SSPCON2 = 0x01;
    // Disable slew rate control for standard mode
    SSPSTAT = 0x80;
    // Enable synchronous serial interrupt
    SSPIF = 0;
    SSPIE = 1;
    PEIE = 1;
    GIE = 1;
}

// Function to generate the start bit of the I2C protocol
void I2C_Start()
{
    I2C_Wait();
    SEN = 1;
}

// Function to generate the restart bit of the I2C protocol
void I2C_Restart()
{
    I2C_Wait();
    RSEN = 1;
}

// Function to generate the stop bit of the I2C protocol 
void I2C_Stop()
{
    I2C_Wait();
    PEN = 1;
}

// Function to generate the ACK in master receive mode in which the reception is not supported by hardware
void I2C_ACK()
{
    I2C_Wait();
    ACKDT = 0;
    ACKEN = 1;
}

// Function to generate the NACK in master receive mode in which the reception is not supported by hardware
void I2C_NACK()
{
    I2C_Wait();
    ACKDT = 1;
    ACKEN = 1;
}

// Function to write a data byte via I2C
uint8_t I2C_Master_sendByte(uint8_t data)
{
    I2C_Wait();
    SSPBUF = data;
    // Check for write collision
    if(WCOL)
    {
        WCOL = 0;
        return 0;
    }
    I2C_Wait();
    // Check if the ACK is sent by the slave
    return ~(ACKSTAT);
}

// Function to read data sent by slave in master receive mode
uint8_t I2C_Master_readByte(uint8_t ack)
{
    I2C_Wait();
    // Enable master reception 
    RCEN = 1;
    // Wait till buffer full flag bit is set
    I2C_Wait();
    // Get the data
    uint8_t data = SSPBUF;
    // Continue to wait
    I2C_Wait();
    // Send an NACK to terminate the slave transmission
    if(ack)
        I2C_ACK();
    else
        I2C_NACK();
    return data;
}

// Function to receive data via I2C in slave mode using service interrupt routine (Uncomment and put it inside application code)
void I2C_Slave_dataHandling(uint8_t* rcv_data, uint8_t tx_data)
{
    // Stretch the clock so that the slave have time to handle the data reception
    CKP = 0;
    // Check for bus collision or buffer overflow 
    if(WCOL || SSPOV)
    {
        I2C_collisionHandling();
    }
    // Case the master want to write
    if(!R_nW)
    {
        *rcv_data = I2C_Slave_readByte();
    }
    // Case master want to read
    else
    {
        I2C_Slave_sendByte(tx_data);
    }
}

