#ifndef __HAL_IO_H
#define __HAL_IO_H

#include "includes.h"

/****   Marco define   ****/
//LED1
#define LED1R_On()      PORTC |= BIT(1)
#define LED1R_Off()     PORTC &= ~BIT(1)

#define LED1G_On()      PORTC |= BIT(2)
#define LED1G_Off()     PORTC &= ~BIT(2)

//LED2
#define LED2R_On()      PORTD |= BIT(4)
#define LED2R_Off()     PORTD &= ~BIT(4)

#define LED2G_On()      PORTC |= BIT(0)
#define LED2G_Off()     PORTC &= ~BIT(0)

//LED3
#define LED3R_On()      PORTC |= BIT(5)
#define LED3R_Off()     PORTC &= ~BIT(5)

#define LED3G_On()      PORTC |= BIT(4)
#define LED3G_Off()     PORTC &= ~BIT(4)

#define LED3B_On()      PORTC |= BIT(3)
#define LED3B_Off()     PORTC &= ~BIT(3)

//LED4
#define LED4R_On()      PORTD |= BIT(7)
#define LED4R_Off()     PORTD &= ~BIT(7)

#define LED4G_On()      PORTB |= BIT(0)
#define LED4G_Off()     PORTB &= ~BIT(0)

//LED5
#define LED5R_On()      PORTB |= BIT(1)
#define LED5R_Off()     PORTB &= ~BIT(1)

#define LED5G_On()      PORTC |= BIT(5)
#define LED5G_Off()     PORTC &= ~BIT(5)


//SYS_STATE
#define SYS_STATE_On()      PORTD |= BIT(5)
#define SYS_STATE_Off()     PORTD &= ~BIT(5)

//SW_STATE
#define SW_STATE_On()       PORTD |= BIT(6)
#define SW_STATE_Off()      PORTD &= ~BIT(6)

//PWM Send pin
#define PWM_Send_On()       PORTB |= BIT(2)
#define PWM_Send_Off()      PORTB &= ~BIT(2)

/****   Fuction define   ****/
void hal_ioinit(void);

#endif
