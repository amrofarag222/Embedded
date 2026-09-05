#include <util/delay.h>
#include "std_type.h"
#include "bit_math.h"
#include "DIO.h"
#include "steppermotor.h"

void stepper_init(void){
    DIO_voidSetPinDirection(stepper_port, DIO_PIN0, DIO_OUTPUT);
    DIO_voidSetPinDirection(stepper_port, DIO_PIN1, DIO_OUTPUT);
    DIO_voidSetPinDirection(stepper_port, DIO_PIN2, DIO_OUTPUT);
    DIO_voidSetPinDirection(stepper_port, DIO_PIN3, DIO_OUTPUT);
}


void stpbystp(void)
{
    DIO_voidSetPinValue(stepper_port, DIO_PIN0, DIO_HIGH);
    _delay_ms (1000);
    DIO_voidSetPinValue(stepper_port, DIO_PIN1, DIO_HIGH);
    _delay_ms (1000);
    DIO_voidSetPinValue(stepper_port, DIO_PIN2, DIO_HIGH);
    _delay_ms (1000);
    DIO_voidSetPinValue(stepper_port, DIO_PIN3, DIO_HIGH);
    _delay_ms (1000);
}

void mood(void)
{   
    u8 sequence[8][4] = {
        {DIO_HIGH, DIO_LOW,  DIO_LOW,  DIO_HIGH}, /* 1001 */
        {DIO_LOW,  DIO_LOW,  DIO_LOW,  DIO_HIGH}, /* 0001 */
        {DIO_LOW,  DIO_LOW,  DIO_HIGH, DIO_HIGH}, /* 0011 */
        {DIO_LOW,  DIO_LOW,  DIO_HIGH, DIO_LOW }, /* 0010 */
        {DIO_LOW,  DIO_HIGH, DIO_HIGH, DIO_LOW }, /* 0110 */
        {DIO_LOW,  DIO_HIGH, DIO_LOW,  DIO_LOW }, /* 0100 */
        {DIO_HIGH, DIO_HIGH, DIO_LOW,  DIO_LOW }, /* 1100 */
        {DIO_HIGH, DIO_LOW,  DIO_LOW,  DIO_LOW }  /* 1000 */
    };
    
    for(u8 row=0;row<8;row++){
        for(u8 clm=0;clm<4;clm++){
            DIO_voidSetPinValue(stepper_port,clm,sequence[row][clm]);
    }
    _delay_ms(10);
    }
} 
