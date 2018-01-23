
#include "hal_io.h"
#include "data.h"

void hal_ioinit(void)
{
    /* PB0,PB2,PB5 : Output High */
    PORTB |= 0x25;
    DDRB |= 0x25;
    
    /* PB1 : Output Low */
    PORTB |= 0x02;
    DDRB &= ~0x02;
    
    /* PC0 - PC5 : Output High */
    PORTC |= 0x3F;
    DDRC |= 0x3F;
    
    /* PD4,PD5,PD6,PD7 : Output High */
    PORTD |= 0xF0;
    DDRD |= 0xF0;
    
    /* PD2 : Input INT0 Falling_edge */
    DDRD &= ~BIT(2);
    EICRA = 0x02;
    EIMSK = 0x01;
}

#pragma vector=INT0_vect
__interrupt void int0_vect()
{ 
    gt_data.status.start_sta = 0x01;
}



