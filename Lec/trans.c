 * Author : Amro Farag
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "DIO.h"
int main(void)
{
	DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN0, DIO_OUTPUT );
    /* Replace with your application code */
    while (1) 
    {
		DIO_voidSetPinValue( DIO_PORTD, DIO_PIN0 , DIO_HIGH );
		_delay_ms(1000);
		DIO_voidSetPinValue( DIO_PORTD, DIO_PIN0 , DIO_LOW );
		_delay_ms(10000);
    }
}
