/*
 * GccApplication10.c
 * Author : Amro Farag
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "std_type.h"
#include "bit_math.h"
#include "DIO.h"

void initExternalInterrupts(void);

int main(void)
{   

    DIO_voidSetPortDirection(DIO_PORTC, DIO_OUTPUT);

    DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN2, DIO_INPUT);
    
    DIO_voidSetPinValue(DIO_PORTD, DIO_PIN2, DIO_HIGH);

    initExternalInterrupts();

    while (1) 
    {
		    DIO_voidTogglePin(DIO_PORTC, DIO_PIN0);
		    _delay_ms(1000);
		    DIO_voidTogglePin(DIO_PORTC, DIO_PIN1);
		    _delay_ms(1000);
		    DIO_voidTogglePin(DIO_PORTC, DIO_PIN2);
		    _delay_ms(1000);
		    DIO_voidTogglePin(DIO_PORTC, DIO_PIN3);
		    _delay_ms(1000);
		    DIO_voidTogglePin(DIO_PORTC, DIO_PIN4);
		    _delay_ms(1000);
		    DIO_voidTogglePin(DIO_PORTC, DIO_PIN5);
		    _delay_ms(1000);
		    DIO_voidTogglePin(DIO_PORTC, DIO_PIN6);
		    _delay_ms(1000);
		    DIO_voidTogglePin(DIO_PORTC, DIO_PIN7);
		    _delay_ms(1000);
    }
}

void initExternalInterrupts(void) {

    MCUCR |= ~ (1 << ISC11);
    MCUCR |= (1 << ISC10);
    
    GICR |= (1 << INT1);
	
    sei();
}

ISR(INT1_vect) {
	while(1){
    DIO_voidTogglePin(DIO_PORTC, DIO_PIN7);
    _delay_ms(1000);
    DIO_voidTogglePin(DIO_PORTC, DIO_PIN6);
    _delay_ms(1000);
    DIO_voidTogglePin(DIO_PORTC, DIO_PIN5);
    _delay_ms(1000);
    DIO_voidTogglePin(DIO_PORTC, DIO_PIN4);
    _delay_ms(1000);
    DIO_voidTogglePin(DIO_PORTC, DIO_PIN3);
    _delay_ms(1000);
    DIO_voidTogglePin(DIO_PORTC, DIO_PIN2);
    _delay_ms(1000);
    DIO_voidTogglePin(DIO_PORTC, DIO_PIN1);
    _delay_ms(1000);
    DIO_voidTogglePin(DIO_PORTC, DIO_PIN0);
    _delay_ms(1000);
	}
}