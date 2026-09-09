#include <avr/io.h>
#include <avr/interrupt.h>
#include "std_type.h"
#include "bit_math.h"
#include "DIO.h"
#include "timer0.h"

void timer0_init(u8 mode) {
    switch (mode) {
        case TIMER0_NORMAL_MODE: // Normal Mode (Overflow Mode)
            CLR_BIT(TCCR0, WGM00);
            CLR_BIT(TCCR0, WGM01);

            // Prescaler = 8 time =1us 
            CLR_BIT(TCCR0, CS00);
            SET_BIT(TCCR0, CS01);
            CLR_BIT(TCCR0, CS02);

            TCNT0 = 0;

            // Enable Overflow Interrupt
            SET_BIT(TIMSK, TOIE0);

            // Enable Global Interrupt
            sei();
            break;

        case TIMER0_CTC_MODE: // CTC Mode (Clear Timer on Compare Match)
            CLR_BIT(TCCR0, WGM00);
            SET_BIT(TCCR0, WGM01);

            // Initial OCR0 Value
            OCR0 = 249; //page 80

            // Prescaler = 8
            CLR_BIT(TCCR0, CS00);
            SET_BIT(TCCR0, CS01);
            CLR_BIT(TCCR0, CS02);

            TCNT0 = 0;//page 80

            // Enable Compare Match Interrupt
            SET_BIT(TIMSK, OCIE0);

            // Enable Global Interrupt
            sei();
            break;

        case FAST_PWM_MODE: //fast pwm
            SET_BIT(TCCR0, WGM00);
            SET_BIT(TCCR0, WGM01);
            //Compare Output Mode, Fast PWM Mode ,Clear OC0 on compare match, set OC0 at TOP
            CLR_BIT(TCCR0, COM00);
            SET_BIT(TCCR0, COM01);

            CLR_BIT(TCCR0, CS00);
            SET_BIT(TCCR0, CS01);
            CLR_BIT(TCCR0, CS02);
            
            OCR0 = 249; //page 80

            SET_BIT(TIMSK, OCIE0);

            sei();
            break;
    }
}

void timer0_setCompareValue(u8 compare_value) {
    OCR0 = compare_value;
}
