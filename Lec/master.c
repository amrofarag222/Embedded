#define F_CPU 8000000UL
#include <util/delay.h>
#include "std_type.h"
#include "BIT_MATH.h"
#include "DIO.h"
#include "UART.h"

int main(void)
{

	UART_INIT();

	while (1)
	{
		UART_SendChar('T');
		_delay_ms(1000);
	}
}
