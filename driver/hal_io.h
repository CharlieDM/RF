#ifndef __HAL_IO_H
#define __HAL_IO_H

#include "includes.h"

/****   Marco define   ****/
//Emit led 
#define EmitR_Off()     PORTC |= BIT(1)
#define EmitR_On()      PORTC &= ~BIT(1)

#define EmitG_Off()     PORTC |= BIT(4)
#define EmitG_On()      PORTC &= ~BIT(4)

#define EmitB_Off()     PORTC |= BIT(3)
#define EmitB_On()      PORTC &= ~BIT(3)

#define EmitLedR_On()   {EmitR_On();EmitG_Off();EmitB_Off();}
#define EmitLedG_On()   {EmitR_Off();EmitG_On();EmitG_Off();}
#define EmitLedB_On()   {EmitR_Off();EmitG_Off();EmitB_On();}
#define EmitLed_Off()   {EmitR_Off();EmitG_Off();EmitB_Off();}

//Rev led
#define RevR_Off()      PORTC |= BIT(2)
#define RevR_On()       PORTC &= ~BIT(2)

#define RevG_Off()      PORTC |= BIT(5)
#define RevG_On()       PORTC &= ~BIT(5)

#define RevLedR_On()          {RevR_On();RevG_Off();}
#define RevLedG_On()          {RevR_Off();RevG_On();}
#define RevLed_Off()          {RevR_Off();RevG_Off();}

//Bat led
#define BatG_Off()      PORTB |= BIT(2)
#define BatG_On()       PORTB &= ~BIT(2)

#define BatB_Off()      PORTB |= BIT(3)
#define BatB_On()       PORTB &= ~BIT(3)

#define BatLed_Off()          {BatG_Off();BatB_Off();}
#define BatLedG_On()          {BatG_On();BatB_Off();}
#define BatLedB_On()          {BatG_Off();BatB_On();}

//Power led
#define PowerR_Off()    PORTD |= BIT(4)
#define PowerR_On()     PORTD &= ~BIT(4)

#define PowerB_Off()    PORTC |= BIT(0)
#define PowerB_On()     PORTC &= ~BIT(0)

#define PowerLed_Off()        {PowerR_Off();PowerB_Off();}
#define PowerLedR_On()        {PowerR_On();PowerB_Off();}
#define PowerLedB_On()        {PowerR_Off();PowerB_On();}

//State led
#define StateR_Off()    PORTD |= BIT(7)
#define StateR_On()     PORTD &= ~BIT(7)

#define StateG_Off()    PORTB |= BIT(0)
#define StateG_On()     PORTB &= ~BIT(0)

#define StateLed_Off()        {StateR_Off();StateG_Off();}
#define StateLedR_On()        {StateR_On();StateG_Off();}
#define StateLedG_On()        {StateR_Off();StateG_On();}

//SYS_STATE
#define SYS_STATE_On()      PORTD |= BIT(5)
#define SYS_STATE_Off()     PORTD &= ~BIT(5)

//SW_STATE
#define SW_STATE_On()       PORTD |= BIT(6)
#define SW_STATE_Off()      PORTD &= ~BIT(6)

//PWM Send pin
#define PWM_Send_On()       PORTB |= BIT(1)
#define PWM_Send_Off()      PORTB &= ~BIT(1)

//Start Sign
#define Start_Sign()        (PIND & BIT(PORTD2))   
#define Rf_Pin_State()      (PIND & BIT(PORTD3))  

typedef enum
{
    eRedBlueHalfS = 0,
    eLedAllOff = 0xFF
} eLedState;

/****   Fuction define   ****/
void hal_ioinit(void);
void hal_uartinit(void);
void Led_SetState(uint8 state);
void Led_HalfS_On(void);

#endif
