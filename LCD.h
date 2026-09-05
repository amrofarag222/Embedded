#ifndef LCD_H_
#define LCD_H_

#include "std_type.h"
#include "bit_math.h"
#include "DIO.h"

#define LCD_CTRL_PORT    DIO_PORTD
#define LCD_RS_PIN       DIO_PIN0
#define LCD_RW_PIN       DIO_PIN1
#define LCD_E_PIN        DIO_PIN2

#define LCD_DATA_PORT    DIO_PORTC

void LCD_init(void);
void LCD_sendCommand(u8 command);
void LCD_sendChar(u8 Data);
void LCD_sendString(u8 *str);

#endif