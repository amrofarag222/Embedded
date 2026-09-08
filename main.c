#include <avr/io.h>
#include "DIO.h"

void ADC_Init(void) {
	DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN0, DIO_INPUT);
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	ADMUX = (1 << REFS0);
}

uint16_t ADC_Read(uint8_t channel) {
	ADMUX = (ADMUX & 0xE0) | (channel & 0x07);
	ADCSRA |= (1 << ADSC);
	while (!(ADCSRA & (1 << ADIF)));
	ADCSRA |= (1 << ADIF);
	return ADC;
}

int main(void) {
	ADC_Init();
	
	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN0, DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN1, DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN2, DIO_OUTPUT);
	
	uint16_t adc_value = 0;

	while (1) {
		adc_value = ADC_Read(0);
		
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN0, DIO_LOW);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN1, DIO_LOW);
		DIO_voidSetPinValue(DIO_PORTB, DIO_PIN2, DIO_LOW);
		
		if (adc_value > 0 && adc_value < 307) {
			DIO_voidSetPinValue(DIO_PORTB, DIO_PIN0, DIO_HIGH);
		}
		else if (adc_value >= 307 && adc_value <= 614) {
			DIO_voidSetPinValue(DIO_PORTB, DIO_PIN1, DIO_HIGH);
		}
		else if (adc_value > 614) {
			DIO_voidSetPinValue(DIO_PORTB, DIO_PIN2, DIO_HIGH);
		}
	}
}