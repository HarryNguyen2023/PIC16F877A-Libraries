#include "LCD16x2.h"

// Use external crystal
#define _XTAL_FREQ 16000000

// --------------------------------Static private functions hidden from user------------------------------------------------

// Function to transmit data to LCD
static void LCD_DATA(uint8_t Data)
{
  if(Data & 1)
    D4 = 1;
  else
    D4 = 0;
  if(Data & 2)
    D5 = 1;
  else
    D5 = 0;
  if(Data & 4)
    D6 = 1;
  else
    D6 = 0;
  if(Data & 8)
    D7 = 1;
  else
    D7 = 0;
  return;
}

// Function for sending command
static void LCD_CMD(uint8_t CMD)
{
  // Select Command Register
  RS = 0;
  // Move The Command Data To LCD
  LCD_DATA(CMD);
  // Send The EN Clock Signal
  EN = 1;
  __delay_us(LCD_EN_Delay);
  EN = 0;
  return;
}

// ---------------------------------Public function to interface with user---------------------------------------------------

// Function for LCD initialization
void LCD_Init()
{
  // IO Pin Configurations
  LCD_DATA_PORT_D = 0x00;
  LCD_RS_D = 0;
  LCD_EN_D = 0;
  // The initialization procedure
  LCD_DATA(0x00);
  __delay_ms(30);
  __delay_us(LCD_EN_Delay);
  LCD_CMD(0x03);
  __delay_ms(5);
  LCD_CMD(0x03);
  __delay_us(150);
  LCD_CMD(0x03);
  LCD_CMD(0x02);
  LCD_CMD(0x02);
  LCD_CMD(0x08);
  LCD_CMD(0x00);
  LCD_CMD(0x0C);
  LCD_CMD(0x00);
  LCD_CMD(0x06);
}

// Function to write character to LCD
void LCD_Write_Char(char Data)
{
  char Low4, High4;
  Low4 = Data & 0x0F;
  High4 = Data & 0xF0;
  RS = 1;
  LCD_DATA(High4>>4);
  EN = 1;
  __delay_us(LCD_EN_Delay);
  EN = 0;
  __delay_us(LCD_EN_Delay);
  LCD_DATA(Low4);
  EN = 1;
  __delay_us(LCD_EN_Delay);
  EN = 0;
  __delay_us(LCD_EN_Delay);
}

// Function to write text to LCD
void LCD_Write_String(char *str)
{
  int i;
  for(i=0;str[i]!='\0';i++)
    LCD_Write_Char(str[i]);
}

// Function to clear the screen
void LCD_Clear()
{
  LCD_CMD(0);
  LCD_CMD(1);
  return;
}

// Function to set cursor position 
void LCD_Set_Cursor(uint8_t r, uint8_t c)
{
  uint8_t Temp, Low4, High4;
  if(r == 1)
  {
    Temp = 0x80 + c - 1; //0x80 is used to move the cursor
    High4 = Temp >> 4;
    Low4 = Temp & 0x0F;
    LCD_CMD(High4);
    LCD_CMD(Low4);
  }
  if(r == 2)
  {
    Temp = 0xC0 + c - 1;
    High4 = Temp >> 4;
    Low4 = Temp & 0x0F;
    LCD_CMD(High4);
    LCD_CMD(Low4);
  }
}

// Function to shift right entire display
void LCD_SR()
{
  LCD_CMD(0x01);
  LCD_CMD(0x0C);
  return;
}

// Function to shift left entire display
void LCD_SL()
{
  LCD_CMD(0x01);
  LCD_CMD(0x08);
  return;
}