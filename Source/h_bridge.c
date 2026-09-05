/*
 * GccApplication9.c
 *
 * Created: 9/5/2026 3:39:33 PM
 * Author : Amro Farag
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "DIO.h"
int main(void)
{
	DIO_voidSetPortDirection(DIO_PORTD,DIO_OUTPUT);
    /* Replace with your application code */
    while (1) 
    {
		DIO_voidSetPinValue( DIO_PORTD, DIO_PIN0 , DIO_HIGH );
		DIO_voidSetPinValue( DIO_PORTD, DIO_PIN1 , DIO_HIGH );
		_delay_ms(1000);
		DIO_voidSetPinValue( DIO_PORTD, DIO_PIN0 , DIO_LOW );
		DIO_voidSetPinValue( DIO_PORTD, DIO_PIN1 , DIO_LOW );
		_delay_ms(5000);
		DIO_voidSetPinValue( DIO_PORTD, DIO_PIN2 , DIO_HIGH );
		DIO_voidSetPinValue( DIO_PORTD, DIO_PIN3 , DIO_HIGH );
		_delay_ms(1000);
		DIO_voidSetPinValue( DIO_PORTD, DIO_PIN2 , DIO_LOW );
		DIO_voidSetPinValue( DIO_PORTD, DIO_PIN3 , DIO_LOW );
		_delay_ms(5000);
    }
}