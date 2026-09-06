#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "DIO.h"

#define KEYPAD_PORT DIO_PORTA
#define KEYPAD_DDR  DIO_DDRA

void KEYPAD_Init(void);
char KEYPAD_GetKey(void);

#endif 