
#include "hal_timer.h"
#include "rf_receive.h"

/* timer init  */
void hal_timerinit(void)
{
    SREG = 0x80; 
    TCCR0B = 0x00;
    TCCR0A = 0x00;
    TCNT0 = 0xFF;
    TIMSK0 = 0x01;
    TCCR0B = 0x02;
}

/* delay 8.77us */
void delay8_77us(void)
{
    uint8 i = 68;
    while(i--);
}

/* delay 17.53us */
void delay17_53us(void)
{
    uint8 i = 136;
    while(i--);
}

#pragma vector=TIMER0_OVF_vect
__interrupt void timer0_ovf_vect()
{ 
    rf_push(TCNT0);
}

