#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "keypad.h"

static const char keypad[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

void KEYPAD_Init(void) {
    /* 1. Columns -> Output (PIN0 to PIN3) */
    DIO_voidSetPinDirection(KEYPAD_PORT, DIO_PIN0, DIO_OUTPUT);
    DIO_voidSetPinDirection(KEYPAD_PORT, DIO_PIN1, DIO_OUTPUT);
    DIO_voidSetPinDirection(KEYPAD_PORT, DIO_PIN2, DIO_OUTPUT);
    DIO_voidSetPinDirection(KEYPAD_PORT, DIO_PIN3, DIO_OUTPUT);

    /* 2. Rows -> Input (PIN4 to PIN7) */
    DIO_voidSetPinDirection(KEYPAD_PORT, DIO_PIN4, DIO_INPUT);
    DIO_voidSetPinDirection(KEYPAD_PORT, DIO_PIN5, DIO_INPUT);
    DIO_voidSetPinDirection(KEYPAD_PORT, DIO_PIN6, DIO_INPUT);
    DIO_voidSetPinDirection(KEYPAD_PORT, DIO_PIN7, DIO_INPUT);

    /* 3. Activate Internal Pull-up Resistance for Rows */
    DIO_voidSetPinValue(KEYPAD_PORT, DIO_PIN4, DIO_HIGH);
    DIO_voidSetPinValue(KEYPAD_PORT, DIO_PIN5, DIO_HIGH);
    DIO_voidSetPinValue(KEYPAD_PORT, DIO_PIN6, DIO_HIGH);
    DIO_voidSetPinValue(KEYPAD_PORT, DIO_PIN7, DIO_HIGH);

    /* 4. Set Columns Initially to HIGH (Deactivated) */
    DIO_voidSetPinValue(KEYPAD_PORT, DIO_PIN0, DIO_HIGH);
    DIO_voidSetPinValue(KEYPAD_PORT, DIO_PIN1, DIO_HIGH);
    DIO_voidSetPinValue(KEYPAD_PORT, DIO_PIN2, DIO_HIGH);
    DIO_voidSetPinValue(KEYPAD_PORT, DIO_PIN3, DIO_HIGH);
}

char KEYPAD_GetKey(void) {
    u8 PressedKey = 0xFF; //NO pressed key
    u8 row_value = DIO_HIGH;

    u8 ColsPins[4] = {DIO_PIN0, DIO_PIN1, DIO_PIN2, DIO_PIN3};
    u8 RowsPins[4] = {DIO_PIN4, DIO_PIN5, DIO_PIN6, DIO_PIN7};

    for (u8 col = 0; col < 4; col++) {
        /* Activate current Column by driving it LOW */
        DIO_voidSetPinValue(KEYPAD_PORT, ColsPins[col], DIO_LOW);

        for (u8 row = 0; row < 4; row++) {
            /* Pass variable address to store the pin reading */
            row_value=DIO_voidGetPinValue(KEYPAD_PORT, RowsPins[row]);

            if (row_value == DIO_LOW) {
                PressedKey = keypad[row][col];

                /* Wait until key is released (Debouncing & Polling protection) */
                while (row_value == DIO_LOW) {
                    row_value=DIO_voidGetPinValue(KEYPAD_PORT, RowsPins[row]);
                }

                /* Reset active column to HIGH before exit */
                DIO_voidSetPinValue(KEYPAD_PORT, ColsPins[col], DIO_HIGH);
                return PressedKey;
            }
        }

        /* Deactivate Column before moving to the next one */
        DIO_voidSetPinValue(KEYPAD_PORT, ColsPins[col], DIO_HIGH);
    }

    return PressedKey;
}
