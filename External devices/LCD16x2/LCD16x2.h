#ifndef LCD16X2_H
#define LCD16X2_H

#include <xc.h>

#define LCD_EN_Delay 500
#define LCD_DATA_PORT_D TRISD
#define LCD_RS_D TRISD2
#define LCD_EN_D TRISD3
#define RS RD2
#define EN RD3
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7

void LCD_Init(void);
void LCD_Write_Char(char Data);
void LCD_Write_String(char *str);
void LCD_Clear(void);
void LCD_Set_Cursor(uint8_t r, uint8_t c);
void LCD_SR(void);
void LCD_SL(void);

#endif