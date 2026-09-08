/*
 * timer0.c
 *default f=1MHz
 * Created: 9/8/2026 5:44:06 PM
 * Author : Amro Farag
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "DIO.h"
#include "timer0.h"

//time tick =64/1M	t overflow =t tick*256 over flow=1/time over flow
volatile u32 overflow_counter = 0;

int main(void)
{	
	DIO_voidSetPinDirection(DIO_PORTA,DIO_PIN0,DIO_OUTPUT);
	DIO_voidSetPinValue(DIO_PORTA,DIO_PIN0,0);
	
	timer0_init();

    while (1) 
    {
		
    }
}
ISR(TIMER0_OVF_vect) {
	overflow_counter++;
	

	if (overflow_counter >= 61) {
		DIO_voidTogglePin(DIO_PORTA, DIO_PIN0);
		overflow_counter = 0;                   
	}
}
