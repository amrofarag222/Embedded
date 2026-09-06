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

    DIO_voidSetPinDirection(DIO_PORTC, DIO_PIN0, DIO_OUTPUT);
    DIO_voidSetPinDirection(DIO_PORTC, DIO_PIN5, DIO_OUTPUT);

    DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN2, DIO_INPUT);
    DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN3, DIO_INPUT);

    DIO_voidSetPinValue(DIO_PORTD, DIO_PIN2, DIO_HIGH);
    DIO_voidSetPinValue(DIO_PORTD, DIO_PIN3, DIO_HIGH);

    initExternalInterrupts();

    while (1) 
    {

    }
}

void initExternalInterrupts(void) {

    MCUCR |= ~ (1 << ISC11);
    MCUCR |= (1 << ISC10);
    
    GICR |= (1 << INT0) | (1 << INT1);
	

    sei();
}

ISR(INT0_vect) {
    DIO_voidTogglePin(DIO_PORTC, DIO_PIN0);
}

ISR(INT1_vect) {
    DIO_voidTogglePin(DIO_PORTC, DIO_PIN5);
}
