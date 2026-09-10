#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <util/delay.h>

#include "Std_Types.h"
#include "Dio.h"
#include "Keys.h"
#include "LCD.h"
#include "Timer0.h"
#include "INTERRUPT.h"
#include "Motor.h"
#include "UART.h"


#define PASSWORD_LENGTH 4
#define TIMEOUT_SECONDS 5
#define OVERFLOWS_PER_SECOND 31

#define REMOTE_SWITCH_COMMAND 'T'


volatile u16 g_u16OverflowCount = 0;
volatile u8 g_u8SecondsCounter = 0;
volatile u8 g_u8TimeoutFlag = 0;
volatile u8 g_u8ScreenActive = 1;
volatile u8 g_u8WakeupFlag = 0;


void TIMER_voidTickCallback(void)
{
	if (g_u8ScreenActive == 1)
	{
		g_u16OverflowCount++;

		if (g_u16OverflowCount >= OVERFLOWS_PER_SECOND)
		{
			g_u16OverflowCount = 0;
			g_u8SecondsCounter++;

			if (g_u8SecondsCounter >= TIMEOUT_SECONDS)
			{
				g_u8TimeoutFlag = 1;
				g_u8SecondsCounter = 0;
			}
		}
	}
}


void WAKEUP_voidSwitchCallback(void)
{
	g_u8WakeupFlag = 1;
}


int main(void)
{
	u8 password[PASSWORD_LENGTH] = {1,2,3,4};
	u8 enteredPassword[PASSWORD_LENGTH];

	u8 index = 0;
	u8 key;
	u8 correct = 1;
	u8 receivedData;


	/* Drivers Initialization */

	KEYS_voidInit();

	LCD_init();

	MOTOR_voidInit();

	UART_voidInit();


	/* Original physical switch on PD2 */

	DIO_voidSetPinDirection(PORT_D, PIN2, INPUT);

	DIO_voidSetPinValue(PORT_D, PIN2, HIGH);


	/* External Interrupt INT0 */

	INT0_voidSetCallBack(WAKEUP_voidSwitchCallback);

	initExternalInterupts();


	/* Timer0 */

	TIMER0_voidSetCallBackOverflow(TIMER_voidTickCallback);

	TIMER0_voidInitNormalMode(TIMER0_PRESCALER_1024);


	/* Initial LCD */

	LCD_SendCommand(0x01);

	LCD_SendString((u8 *)"Enter PIN: ");


	while (1)
	{
		/* =========================================
		   MASTER PD3 REMOTE SWITCH
		   ========================================= */

		if (UART_u8DataAvailable())
		{
			receivedData = UART_u8ReceiveData();

			if (receivedData == REMOTE_SWITCH_COMMAND)
			{
				/* EXACTLY SAME FLAG USED BY PD2 */

				 g_u8WakeupFlag = 1;
			}
		}


		/* =========================================
		   ORIGINAL PD2 SWITCH
		   ========================================= */

		if (g_u8WakeupFlag == 1)
		{
			g_u8WakeupFlag = 0;

			g_u16OverflowCount = 0;
			g_u8SecondsCounter = 0;
			g_u8TimeoutFlag = 0;

			index = 0;
			correct = 1;

			/* Toggle ON / OFF */

			if (g_u8ScreenActive == 1)
			{
				/* ON -> OFF */

				g_u8ScreenActive = 0;

				LCD_SendCommand(0x08);
			}
			else
			{
				/* OFF -> ON */

				g_u8ScreenActive = 1;

				LCD_SendCommand(0x0C);
				LCD_SendCommand(0x01);
				LCD_SendString((u8 *)"Enter PIN: ");
			}
		}


		/* =========================================
		   TIMER TIMEOUT
		   ========================================= */

		if (g_u8TimeoutFlag == 1)
		{
			g_u8TimeoutFlag = 0;

			g_u8ScreenActive = 0;

			LCD_SendCommand(0x08);
		}


		/* =========================================
		   KEYPAD
		   ========================================= */

		if (g_u8ScreenActive == 1)
		{
			key = KEYS_u8GetKey();

			if (key == 255)
			{
				continue;
			}


			g_u16OverflowCount = 0;

			g_u8SecondsCounter = 0;


			/* CLEAR */

			if (key == KEY_CLEAR)
			{
				if (index > 0)
				{
					index--;

					LCD_SendCommand(0x10);
					LCD_sendChar(' ');
					LCD_SendCommand(0x10);

					correct = 1;

					for (u8 i = 0; i < index; i++)
					{
						if (enteredPassword[i] != password[i])
						{
							correct = 0;
							break;
						}
					}
				}

				continue;
			}


			/* ENTER */

			if (key == KEY_ENTER)
			{
				if (index == PASSWORD_LENGTH)
				{
					correct = 1;

					for (u8 i = 0; i < PASSWORD_LENGTH; i++)
					{
						if (enteredPassword[i] != password[i])
						{
							correct = 0;

							break;
						}
					}


					if (correct == 1)
					{
						g_u8ScreenActive = 0;

						LCD_SendCommand(0x01);

						LCD_SendString((u8 *)"Access Granted!");


						MOTOR_voidOpenAndCloseDoor();


						g_u8ScreenActive = 1;

						g_u16OverflowCount = 0;

						g_u8SecondsCounter = 0;

						g_u8TimeoutFlag = 0;


						LCD_SendCommand(0x01);

						LCD_SendString((u8 *)"Enter PIN: ");
					}
					else
					{
						LCD_SendCommand(0x01);

						LCD_SendString((u8 *)"Access Denied!");

						_delay_ms(1000);

						LCD_SendCommand(0x01);

						LCD_SendString((u8 *)"Enter PIN: ");
					}
				}
				else
				{
					LCD_SendCommand(0x01);

					LCD_SendString((u8 *)"Enter PIN: ");
				}


				index = 0;

				correct = 1;

				continue;
			}


			/* NUMBER */

			if (key <= 9)
			{
				if (index < PASSWORD_LENGTH)
				{
					enteredPassword[index] = key;

					LCD_sendChar('0' + key);

					index++;
				}
			}
		}
	}


	return 0;
}