#include <avr/io.h>
#include <avr/interrupt.h>
#include "DIO.h"
#include "timer0.h"

void timer0_init(void) {
    // 1. Normal Mode (Overflow Mode)
    CLR_BIT(TCCR0, WGM00);
    CLR_BIT(TCCR0, WGM01);

    // 2. Prescaler 64
    SET_BIT(TCCR0, CS00);
    SET_BIT(TCCR0, CS01);
    CLR_BIT(TCCR0, CS02);

    // 3. Initial value
    TCNT0 = 0;

    // 4. Enable Timer0 Overflow Interrupt (TIMSK)
    SET_BIT(TIMSK, TOIE0);

    // 5. Enable Global Interrupt
    sei();
}
