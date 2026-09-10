#define F_CPU 8000000UL
#include <avr/io.h>
#include "std_type.h"
#include "bit_math.h"
#include "DIO.h"
#include "UART.h"

int main(void)
{
	u8 rec= 0;

	DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN0, DIO_OUTPUT);
	DIO_voidSetPinValue(DIO_PORTA, DIO_PIN0, DIO_LOW); // إطفاء الـ LED في البداية

	UART_INIT();

	while (1)
	{
		rec = UART_GetChar();

		if (local_u8ReceivedData == 'T')
		{
			TOGGLE_BIT(PORTA, DIO_PIN0);
		}
	}
}