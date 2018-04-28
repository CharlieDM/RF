
#include "hal_io.h"
#include "data.h"
#include "rf_receive.h"
#include "hal_timer.h"
    
#define BAUD                        (9600)

#define INT_LOW_LEVEL               (0x00)
#define INT_ANG_CHANGE              (0x01)
#define INT_FALLING_EDGE            (0x02)
#define INT_RASING_EDGE             (0x03)


volatile uint8 rf_data = 0;
uint8 sg_eLed = 0;
uint8 sg_onoff = 0;

void hal_ioinit(void)
{
    /* PB0,PB2,PB3 : Output High */
    DDRB |= BIT(PORTB0)|BIT(PORTB2)|BIT(PORTB3);
    PORTB |= BIT(PORTB0)|BIT(PORTB2)|BIT(PORTB3);    
    
    /* PB1 : Output Low */
    DDRB |= BIT(PORTB1);
    PORTB &= ~BIT(PORTB1);    
    
    /* PC0 - PC5 : Output High */
    DDRC |= BIT(PORTC0)|BIT(PORTC2)|BIT(PORTC3)|BIT(PORTC4)|BIT(PORTC5);
    PORTC |= BIT(PORTC0)|BIT(PORTC2)|BIT(PORTC3)|BIT(PORTC4)|BIT(PORTC5);    
    
    /* PD4,PD7 : Output High  PD5,PD6: Output Low  */
    DDRD |= BIT(PORTD4)|BIT(PORTD5)|BIT(PORTD6)|BIT(PORTD7);
    PORTD |= BIT(PORTD4)|BIT(PORTD7);    
    PORTD &= ~(BIT(PORTD5)|BIT(PORTD6));
    
    /* PD2 PD3: Input INT0  INT1*/
    DDRD &= ~BIT(PORTD3);
     
    EICRA |= INT_RASING_EDGE | (INT_FALLING_EDGE<<ISC10);
    EIMSK |= BIT(INT0) | BIT(INT1);
    
    /* Global interruput enable*/
    SREG = 0x80;
}

/* hal_uartinit function */
void hal_uartinit(void)
{
    DDRD |= BIT(PORTD1);
    PORTD |= BIT(PORTD1); 
    UCSR0B = 0x00;
    UCSR0A = 0x00;
    UCSR0C = (3<<UCSZ00);
    UBRR0 = ((F_CPU/16)/BAUD)-1;
    UCSR0B = BIT(TXEN0);
}

/* putc function */
void putc(uint8 data)
{
    //while ( !( UCSR0A & (1<<UDRE0)) )
    UDR0 = data;
    while( !(UCSR0A & BIT(TXC0)) );
    UCSR0A |= BIT(TXC0);
}

/* rf_getLow function */
uint8 rf_getLow(void)
{
    TCCR0A = 0;
    TCCR0B =0;
    TCNT0 = 0;
    TCCR0B = BIT(CS02);
    while(Rf_Pin_State());    
    return TCNT0;
}

/* rf_getHigh function */
uint8 rf_getHigh(void)
{
    TCCR0A = 0;
    TCCR0B =0;
    TCNT0 = 0;
    TCCR0B = BIT(CS02);
    while(!Rf_Pin_State());     
    return TCNT0;
}

void Led_SetState(uint8 state)
{
    sg_eLed = state;
    switch(state)
    {
        case eRedBlueHalfS:
            BatLedB_On();
          break;
        
        case eLedAllOff:
            StateLed_Off();
            PowerLed_Off();
            BatLed_Off();
            RevLed_Off();
            EmitLed_Off();
          break;
          
        default:
            break;
    }
}

void Led_HalfS_On(void)
{
    switch(sg_eLed)
    {
        case eRedBlueHalfS:
            if(sg_onoff == 0)
            {
                BatLed_Off();
                sg_onoff = 1;
            }
            else
            {
                BatLedB_On();
                sg_onoff = 0;
            }              
          break;  
          
        default:
            break;
    }
}

#pragma vector=INT0_vect
__interrupt void int0_vect()
{ 
    uint8 i=30;    
    while(i--)
    {
        delay8_77us();
    }
    
    if( !Start_Sign() )
    {
        gst_state.start = 0x01;
    }
}

uint8 s_rfbuf[20] = {0};
#pragma vector=INT1_vect
__interrupt void int1_vect()
{ 
    uint8 i = 0, temp = 0;
    SREG &= ~0x80;
    rf_data = 0;       
    gst_rf.connecting = 0x00;
    temp = rf_getHigh();
    s_rfbuf[0] = temp;
    if( temp>139 && temp<159)    // 4ms
    {
        for(i=0;i<4;i++)
        {
            temp = rf_getLow();
            s_rfbuf[1+2*i] = temp;
            if( temp>25 && temp<39)         // 850us ~ 1000us
            {
                temp = rf_getHigh();        // 540us ~ 670us
                s_rfbuf[2+2*i] = temp;
                if( temp>16 && temp<26)     
                {
                    rf_data <<= 1;
                    rf_data |= 0x01;                    
                }
                else
                {
                    break;
                }
            }
            else if( temp>11 && temp<21)
            {
                temp = rf_getHigh();
                s_rfbuf[2+2*i] = temp;
                if( temp<16 || temp>26)
                {
                  break;
                }
                else
                {
                  rf_data <<= 1;
                  rf_data &= ~0x01;                  
                }
            }
        }
    }
    gst_rf.data = rf_data;
    if(rf_data == 0x05)
    {
        gst_rf.state = 0x01;
        StateLedR_On();
        SW_STATE_On();
    }
    else if(rf_data == 0x02)
    {
        gst_rf.state = 0x01;
        SW_STATE_Off();
        StateLedG_On();
    }

#ifdef DEBUG   
    s_rfbuf[9] = rf_data;
    for(i=0;i<10;i++)
    {
      putc(s_rfbuf[i]);
      s_rfbuf[i] = 0;
    }  
#endif
    
    SREG = 0x80;
}




