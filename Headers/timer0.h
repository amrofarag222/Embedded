#ifndef TIMER0_H_
#define TIMER0_H_

#include "std_type.h"

#define TIMER0_NORMAL_MODE 0
#define TIMER0_CTC_MODE 1
#define FAST_PWM_MODE 2


void timer0_init(u8 mode);
void timer0_setCompareValue(u8 Copy_u8Value);

#endif
