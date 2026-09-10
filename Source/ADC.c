#include <avr/io.h>
#include "std_type.h"
#include "bit_math.h"
#include "DIO.h"
#include "ADC.h"

void ADC_Init(void) {

    // VREF = AVCC (5V)
    SET_BIT(ADMUX, REFS0);
    CLR_BIT(ADMUX, REFS1);

    // Right Adjust (10-bit result)
    CLR_BIT(ADMUX, ADLAR);

    // Prescaler = 128
    SET_BIT(ADCSRA, ADPS0);
    SET_BIT(ADCSRA, ADPS1);
    SET_BIT(ADCSRA, ADPS2);

    // Enable ADC
    SET_BIT(ADCSRA, ADEN);
}

u16 ADC_ReadChannel(u8 ChannelNum) {
    // Set Pin as Input using DIO Driver
    DIO_voidSetPinDirection(DIO_PORTA, ChannelNum, DIO_INPUT);
    
    // MUX Selection (Channels 0 to 7) using switch
    switch(ChannelNum) {
        case 0: CLR_BIT(ADMUX, MUX0); CLR_BIT(ADMUX, MUX1); CLR_BIT(ADMUX, MUX2); CLR_BIT(ADMUX, MUX3); break;
        case 1: SET_BIT(ADMUX, MUX0); CLR_BIT(ADMUX, MUX1); CLR_BIT(ADMUX, MUX2); CLR_BIT(ADMUX, MUX3); break;    
        case 2: CLR_BIT(ADMUX, MUX0); SET_BIT(ADMUX, MUX1); CLR_BIT(ADMUX, MUX2); CLR_BIT(ADMUX, MUX3); break;
        case 3: SET_BIT(ADMUX, MUX0); SET_BIT(ADMUX, MUX1); CLR_BIT(ADMUX, MUX2); CLR_BIT(ADMUX, MUX3); break;
        case 4: CLR_BIT(ADMUX, MUX0); CLR_BIT(ADMUX, MUX1); SET_BIT(ADMUX, MUX2); CLR_BIT(ADMUX, MUX3); break;
        case 5: SET_BIT(ADMUX, MUX0); CLR_BIT(ADMUX, MUX1); SET_BIT(ADMUX, MUX2); CLR_BIT(ADMUX, MUX3); break;
        case 6: CLR_BIT(ADMUX, MUX0); SET_BIT(ADMUX, MUX1); SET_BIT(ADMUX, MUX2); CLR_BIT(ADMUX, MUX3); break;
        case 7: SET_BIT(ADMUX, MUX0); SET_BIT(ADMUX, MUX1); SET_BIT(ADMUX, MUX2); CLR_BIT(ADMUX, MUX3); break;
    }

    // Start Conversion
    SET_BIT(ADCSRA, ADSC);

    // Polling until conversion completes
    while (GET_BIT(ADCSRA, ADSC) == 1);

    return ADC;
}