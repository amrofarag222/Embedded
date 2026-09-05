#include <util/delay.h>
#include "std_type.h"
#include "bit_math.h"
#include "DIO.h"
#include "LCD.h"

void LCD_sendCommand(u8 command) {
    // RS = 0 , RW = 0 send command
    DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_RS_PIN, DIO_LOW);
    DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_RW_PIN, DIO_LOW);

    //Send Command Bits to Data Port 
    DIO_voidSetPinValue(LCD_DATA_PORT, DIO_PIN0, GET_BIT(command, 0));
    DIO_voidSetPinValue(LCD_DATA_PORT, DIO_PIN1, GET_BIT(command, 1));
    DIO_voidSetPinValue(LCD_DATA_PORT, DIO_PIN2, GET_BIT(command, 2));
    DIO_voidSetPinValue(LCD_DATA_PORT, DIO_PIN3, GET_BIT(command, 3));
    DIO_voidSetPinValue(LCD_DATA_PORT, DIO_PIN4, GET_BIT(command, 4));
    DIO_voidSetPinValue(LCD_DATA_PORT, DIO_PIN5, GET_BIT(command, 5));
    DIO_voidSetPinValue(LCD_DATA_PORT, DIO_PIN6, GET_BIT(command, 6));
    DIO_voidSetPinValue(LCD_DATA_PORT, DIO_PIN7, GET_BIT(command, 7));

    // Enable Pulse 
    DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_E_PIN, DIO_HIGH);
    _delay_ms(2);
    DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_E_PIN, DIO_LOW);
}

void LCD_init(void) {
    // Set Directions 
    DIO_voidSetPortDirection(LCD_DATA_PORT, DIO_OUTPUT);
    DIO_voidSetPinDirection(LCD_CTRL_PORT, LCD_RS_PIN, DIO_OUTPUT);
    DIO_voidSetPinDirection(LCD_CTRL_PORT, LCD_RW_PIN, DIO_OUTPUT);
    DIO_voidSetPinDirection(LCD_CTRL_PORT, LCD_E_PIN, DIO_OUTPUT);

    _delay_ms(50);

    // Commands to start 
    LCD_sendCommand(0x30); // 8-bit mode, 2 lines, 5x7 font
    _delay_ms(1);

    LCD_sendCommand(0x8); // Display ON, Cursor OFF
    _delay_ms(1);

    LCD_sendCommand(0x1); // Clear Display
    _delay_ms(2);
}

void LCD_sendChar(u8 Data) {
    // RS = 1 , RW = 0 (Write)
    DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_RS_PIN, DIO_HIGH);
    DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_RW_PIN, DIO_LOW);

    DIO_voidSetPinValue(LCD_DATA_PORT, DIO_PIN0, GET_BIT(Data, 0));
    DIO_voidSetPinValue(LCD_DATA_PORT, DIO_PIN1, GET_BIT(Data, 1));
    DIO_voidSetPinValue(LCD_DATA_PORT, DIO_PIN2, GET_BIT(Data, 2));
    DIO_voidSetPinValue(LCD_DATA_PORT, DIO_PIN3, GET_BIT(Data, 3));
    DIO_voidSetPinValue(LCD_DATA_PORT, DIO_PIN4, GET_BIT(Data, 4));
    DIO_voidSetPinValue(LCD_DATA_PORT, DIO_PIN5, GET_BIT(Data, 5));
    DIO_voidSetPinValue(LCD_DATA_PORT, DIO_PIN6, GET_BIT(Data, 6));
    DIO_voidSetPinValue(LCD_DATA_PORT, DIO_PIN7, GET_BIT(Data, 7));

    //Enable Pulse 
    DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_E_PIN, DIO_HIGH);
    _delay_ms(2);
    DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_E_PIN, DIO_LOW);
}

void LCD_sendString(u8 *str) {
    u8 i = 0;
    while (str[i] != '\0') {
        LCD_sendChar(str[i]);
        i++;
    }
}