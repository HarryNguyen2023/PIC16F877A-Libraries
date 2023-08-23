#include "LCD16x2_I2C.h"
 
uint8_t RS, i2c_add, BackLight_State = LCD_BACKLIGHT;

//---------------[ Static functions ]----------------
//---------------------------------------------------

static void IO_Expander_Write(uint8_t Data)
{
  I2C_Start();
  while(! I2C_Master_sendByte(i2c_add));
  while(! I2C_Master_sendByte(Data | BackLight_State));
  I2C_Stop();
}

static void LCD_Write_4Bit(uint8_t Nibble)
{
  // Get The RS Value To LSB OF Data
  Nibble |= RS;
  IO_Expander_Write(Nibble | 0x04);
  IO_Expander_Write(Nibble & 0xFB);
  __delay_us(50);
}

static void LCD_CMD(uint8_t CMD)
{
  RS = 0; // Command Register Select
  LCD_Write_4Bit(CMD & 0xF0);
  LCD_Write_4Bit((CMD << 4) & 0xF0);
}

static void LCD_Write_Char(char Data)
{
  RS = 1; // Data Register Select
  LCD_Write_4Bit(Data & 0xF0);
  LCD_Write_4Bit((Data << 4) & 0xF0);
}
 
//--------------[ General functions ]----------------
//---------------------------------------------------
 
void LCD_Init()
{
    // Initiate the I2C master mode
    I2C_Master_Init();
    // Initiate the LCD module
    i2c_add = LCD_SLAVE_ADD;
    IO_Expander_Write(0x00);
    __delay_ms(30);
    LCD_CMD(0x03);
    __delay_ms(5);
    LCD_CMD(0x03);
    __delay_ms(5);
    LCD_CMD(0x03);
    __delay_ms(5);
    LCD_CMD(LCD_RETURN_HOME);
    __delay_ms(5);
    LCD_CMD(0x20 | (LCD_TYPE << 2));
    __delay_ms(50);
    LCD_CMD(LCD_TURN_ON);
    __delay_ms(50);
    LCD_CMD(LCD_CLEAR);
    __delay_ms(50);
    LCD_CMD(LCD_ENTRY_MODE_SET | LCD_RETURN_HOME);
    __delay_ms(50);
}
 
void LCD_Write_String(char* str)
{
    for(int i=0; str[i]!='\0'; i++)
      LCD_Write_Char(str[i]);
}
 
void LCD_Set_Cursor(uint8_t ROW, uint8_t COL)
{
    switch(ROW)
    {
      case 2:
        LCD_CMD(0xC0 + COL-1);
        break;
      case 3:
        LCD_CMD(0x94 + COL-1);
        break;
      case 4:
        LCD_CMD(0xD4 + COL-1);
        break;
      // Case 1
      default:
        LCD_CMD(0x80 + COL-1);
    }
}
 
void Backlight()
{
    BackLight_State = LCD_BACKLIGHT;
    IO_Expander_Write(0);
}
 
void noBacklight()
{
    BackLight_State = LCD_NOBACKLIGHT;
    IO_Expander_Write(0);
}
 
void LCD_SL()
{
    LCD_CMD(0x18);
    __delay_us(40);
}
 
void LCD_SR()
{
    LCD_CMD(0x1C);
    __delay_us(40);
}
 
void LCD_Clear()
{
    LCD_CMD(0x01);
    __delay_us(40);
}
