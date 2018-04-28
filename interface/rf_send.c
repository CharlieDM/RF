
#include "rf_send.h"
#include "hal_timer.h"
#include "hal_io.h"

/****   Define define   ****/
#define DELAY_8_77US            delay8_77us()
#define DELAY_17_53US           delay17_53us()

/* rf_send_one function */
void rf_send_one(void)
{
    uint8 i = 0;
    
    /* notransmitted-carrier: 105us */
    for(i=0;i<36;i++)
    {
        PWM_Send_Off();
        DELAY_8_77US;
        PWM_Send_Off();
        DELAY_17_53US;
    }
    
    /* transmitted-carrier: 420us */
    for(i=0;i<12;i++)
    {
        PWM_Send_On();
        DELAY_8_77US;
        PWM_Send_Off();
        DELAY_17_53US;
    }
}

/* rf_send_zero function */
void rf_send_zero(void)
{
    uint8 i = 0;
    
    /* notransmitted-carrier: 420us */
    for(i=0; i<12; i++)
    {
        PWM_Send_Off();
        DELAY_8_77US;
        PWM_Send_Off();
        DELAY_17_53US;
    }
    
    /* transmitted-carrier: 105us */
    for(i=0; i<12; i++)
    {
        PWM_Send_On();
        DELAY_8_77US;
        PWM_Send_Off();
        DELAY_17_53US;
    }
}

/* rf_send_data function */
void rf_send_data(uint8 _data)
{
    uint8 i = 0;
    
    for(i=0; i<8; i++)
    {
        if(_data & 0x80)
            rf_send_one();
        else
            rf_send_zero();
        
        _data <<= 1;
    }
}

/* rf_send_message function: */
void rf_send_message(uint8 _data)
{
    uint8 i = 0;
    /* guidance code: 1998ms*/    
    for(i=0; i<152; i++)
    {
        PWM_Send_On();
        DELAY_8_77US;
        PWM_Send_Off();
        DELAY_17_53US;
    }
        
    /* data */
    rf_send_data(_data);
}

/* rf_wakeup function: */
void rf_wakeup(void)
{
    uint8 i=0;
    for(i=0;i<30;i++)
    {
        rf_send_message(0xaa);
    }
}

