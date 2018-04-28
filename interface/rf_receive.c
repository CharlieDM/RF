
#include "rf_receive.h"
#include "data.h"
#include "hal_io.h"

/****   Static variables define   ****/
static uint16 rf_data_buf[RF_REV_DATA_MAX] = {0};
static uint8 rf_data_pos = 0;

/* rf_data_push */
void rf_push(uint8 data)
{
//    rf_data_buf[rf_data_pos++] = data;
//    if(rf_data_pos>=19) rf_data_pos = 0;
}

void rf_clear(void)
{
    uint8 i =0;
    rf_data_pos = 0;
    for(i=0;i<RF_REV_DATA_MAX;i++)
    {
        rf_data_buf[i] = 0;
    }
}

/* rf_message_parse */
uint8 rf_message_parse(void)
{
    uint8 pos = 0;
    /* check rf data lenght is greater than min lenght */


    /* parse guidance code */
//    if(rf_data_buf[RF_DATA_GUIDANCE_CODE] < 437 || rf_data_buf[RF_DATA_GUIDANCE_CODE] > 562)
//    if(rf_data_buf[RF_DATA_GUIDANCE_CODE] > 5000)
//      return FALSE;
//    
//    /* parse data */
//    for(pos=0; pos<8; pos++)
//    {
//        if(rf_data_buf[2*pos] > 312 && rf_data_buf[2*pos] < 437)
//        {
//            if(rf_data_buf[2*pos+1] > 312 && rf_data_buf[2*pos+1] < 437)
//            {
//                gst_rfdata.data &= ~0x01;
//                gst_rfdata.data <<= 1;
//            }
//        }
//        else if(rf_data_buf[pos] > 750 && rf_data_buf[pos] < 875)
//        {
//            if(rf_data_buf[2*pos+1] > 312 && rf_data_buf[2*pos+1] < 437)
//            {
//                gst_rfdata.data |= 0x01;
//                gst_rfdata.data <<= 1;
//            }
//        }
//        else
//        {
//            return FALSE;
//        }   
//    }    
    rf_clear();
    return FALSE;
}
