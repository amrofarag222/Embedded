#define F_CPU 8000000UL
#include <avr/io.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO.h"
#include "UART.h"
/*TX (Transmit): إرسال البيانات (في ATmega32 متصل بـ PD1).

RX (Receive): استقبال البيانات (في ATmega32 متصل بـ PD0).*/
void UART_INIT(void)
{   
    DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN0, DIO_INPUT);
    DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN1, DIO_OUTPUT);

    //بفعل الاستقبال والارسال
    SET_BIT(UCSRB, RXEN);//استقيال
    SET_BIT(UCSRB, TXEN);//ارسال

    SET_BIT(UCSRC, URSEL);//لازم يتفعل عشان اكتب UCSRCع 

    CLR_BIT(UCSRC,UMSEL);//Asynchronous

    CLR_BIT(UCSRC,UPM0);//disable parity
    CLR_BIT(UCSRC,UPM1);

    CLR_BIT(UCSRC,USBS);//1 ending bit

    //8bit
    SET_BIT(UCSRC, UCSZ0);
    SET_BIT(UCSRC, UCSZ1);
    SET_BIT(UCSRC, UCSZ2);

    UBRRL = 51;//بحدد سرعه  الاستقبال والارسال  للاتنين
}

void UART_SendChar(u8 data)
{
    while (GET_BIT(UCSRA, UDRE) == 0);
    UDR = data;
}

u8 UART_GetChar(void)
{

    while (GET_BIT(UCSRA, RXC) == 0);
    return UDR;
}