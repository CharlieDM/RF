
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
    
    /* transmitted-carrier: */
    for(i=0;i<22;i++)
    {
        PWM_Send_On();
        DELAY_8_77US;
        PWM_Send_Off();
        DELAY_17_53US;
    }
    
    /* notransmitted-carrier: */
    for(i=0;i<22;i++)
    {
        PWM_Send_Off();
        DELAY_8_77US;
        PWM_Send_Off();
        DELAY_17_53US;
    }
}

/* rf_send_zero function */
void rf_send_zero(void)
{
    uint8 i = 0;
    
    /* transmitted-carrier: */
    for(i=0; i<22; i++)
    {
        PWM_Send_On();
        DELAY_8_77US;
        PWM_Send_Off();
        DELAY_17_53US;
    }
    
    /* notransmitted-carrier: */
    for(i=0; i<64; i++)
    {
        PWM_Send_Off();
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
        if(_data & 0x01)
            rf_send_one();
        else
            rf_send_zero();
        
        _data >>= 1;
    }
}

/* rf_send_message function: */
void rf_send_message(uint8 cmd, uint8 data)
{
    uint8 i = 0;
    /* guidance code */
    for(i=0; i<200; i++)
    {
        PWM_Send_On();
        DELAY_8_77US;
        PWM_Send_Off();
        DELAY_17_53US;
    }
    
    for(i=0; i<200; i++)
    {
        PWM_Send_Off();
        DELAY_8_77US;
        PWM_Send_Off();
        DELAY_17_53US;
    }
    
    /* cmd */
    rf_send_data(cmd);
    
    /* data */
    rf_send_data(data);
    
    /* opposite data */
    rf_send_data(~data);
}


