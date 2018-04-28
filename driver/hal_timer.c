
#include "hal_timer.h"
#include "rf_receive.h"
#include "hal_io.h"
#include "data.h"

uint16 g_delaytick = 0;
uint8 g_ledtick = 0;
uint8 g_tick = 0;

/* timer init  */
void hal_timerinit(void)
{
    TCCR1A = 0;
    TCCR1B = 0;    
    OCR1A = 12500;   
    TCNT1 = 0x00;
    TIMSK1 = (1<<OCIE1A);   
    TCCR1B = (1<<WGM12) | (1<<CS11) | (1<<CS10);    
    SREG = 0x80;
}

/* delay 8.77us */
void delay8_77us(void)
{
    uint8 i = 40;
    while(i--);
}

/* delay 17.53us */
void delay17_53us(void)
{
    uint8 i = 40;
    while(i--);
}

void delay_100ms(uint8 nms)
{
    g_delaytick = nms;
    while(g_delaytick);
}

#pragma vector=TIMER1_COMPA_vect
__interrupt void timer1_compa_vect()
{ 
    if(g_delaytick)
    {
        g_delaytick--;
    }
    
    if(g_ledtick++ >= 4)
    {
        g_ledtick = 0;
        Led_HalfS_On();
    }
    
    if(g_tick++ >= 9)
    {
        g_tick = 0;
        gst_state.time1s = 0x01;
    }
}

