
#include "interface.h"
#include "data.h"
#include "rf_receive.h"
#include "rf_send.h"

/* global variables */
struct state_t gst_state = {0};
struct rfdata_t gst_rf = {0};

/* static variables */
static eRunStatus sg_runStatus = MODE_SLEEPING;

/* main function */
int main(void)
{    
    /* init */
    hal_init();
    PowerLedB_On();
    RevLedG_On();    
    BatLedG_On();
    
    /* main loop */
    while(1)
    {
        switch(sg_runStatus)
        {
            case MODE_SLEEPING:
                if( gst_state.start )
                {
                    EmitLedB_On();
                    rf_wakeup();
                }
                
                if( gst_rf.state )
                {
                    gst_state.start = 0;
                    RevLedG_On();
                    SYS_STATE_Off();
                    if(gst_rf.data & 0x08)
                    {
                        Led_SetState(eRedBlueHalfS);
                    }                    
                    gst_rf.state = 0;
                    sg_runStatus = MODE_WORKING;
                    
                }
                else
                {
                    RevLedR_On();
                    SYS_STATE_On();
                }
              break;
              
            case MODE_WORKING:
                if( gst_state.start )
                {
                    Led_SetState(eLedAllOff);
                    PowerLedB_On();
                    RevLedG_On();    
                    BatLedG_On();
                    sg_runStatus = MODE_SLEEPING;
                }
                
                if( gst_state.time1s )
                {
                    gst_state.time1s = 0;
                    if( gst_rf.connecting )
                    {
                        SYS_STATE_Off();
                        gst_rf.connecting = 0;
                    }
                    else
                    {
                        SYS_STATE_On();
                    }
                }
              break;
                
        }
    }
}