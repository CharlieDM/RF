
#include "interface.h"
#include "data.h"
#include "rf_receive.h"
#include "rf_send.h"

/* global variables */
data_t gt_data = {0};

static eRunStatus sg_runStatus = MODE_SLEEPING;
/* main function */
int main(void)
{    
    uint8 temp = 0;
    
    /* hal init */
    hal_init();
  
    /* main loop */
    while(1)
    {
        switch(sg_runStatus)
        {
            /* wait for low edge sign */
            case MODE_SLEEPING:
                if(gt_data.status.start_sta == 0x01)
                {
                    /* change status */
                    sg_runStatus = MODE_WORKING;
                    gt_data.status.start_sta = 0;
                    
                    /* send 2 times start sign to sender board */
                    
                }
              break;
            
            /* wait for the rf data of sender board */
            case MODE_WORKING:              
                /* check if haven received the sender board data */
                if( rf_message_parse() )
                {
                    temp = gt_data.rfdata.oppdata;
                    if( (gt_data.rfdata.data + temp) == 0xFF)
                    {
                        if(gt_data.rfdata.data == RF_SYSTEM_ON)
                        {
                            
                        }
                        else if(gt_data.rfdata.data == RF_SYSTEM_OFF)
                        {
                            
                        }
                    }
                }
              
                /* wait for low edge sign, then send stop sign to sender board */
                if(gt_data.status.start_sta == 0x01)
                {
                    /* change status */
                    sg_runStatus = MODE_SLEEPING;
                    gt_data.status.start_sta = 0;
                }
              break;
              
            default:
              break;
        }
    }
}