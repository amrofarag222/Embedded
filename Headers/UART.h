#ifndef USART_H_
#define USART_H_

#include "std_type.h"

void UART_voidInit(void);
void UART_voidSendData(u8 Data);
u8   UART_u8ReceiveData(void);

#endif