#ifndef  _STEPPREMOTOR_H_
#define  _STEPPREMOTOR_H_

#include "std_type.h"
#include "bit_math.h"
#include "DIO.h"
#include "steppermotor.c"

#define stepper_port DIO_PORTD 

void stepper_init(void);
void stpbystp(void);
void mood(void);

#endif