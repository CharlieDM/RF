
#include "rf_receive.h"
#include "data.h"

/****   Static variables define   ****/
static uint16 rf_data_buf[RF_REV_DATA_MAX] = {0};
static uint8 rf_data_pos = 0;

/* rf_data_push */
void rf_push(uint8 data)
{
    rf_data_buf[rf_data_pos++] = data;
}

/* rf_message_parse */
uint8 rf_message_parse(void)
{
    uint8 pos = 0;
    /* check rf data lenght is greater than min lenght */
    if( rf_data_pos < RF_REV_DATA_MAX )
      return FALSE;
    
    /* parse guidance code */
    if(rf_data_buf[RF_DATA_GUIDANCE_CODE] < 1200 || rf_data_buf[RF_DATA_GUIDANCE_CODE] > 1500)
      return FALSE;
    
    /* parse cmd */
    for(pos=2; pos<10; pos++)
    {
        if(rf_data_buf[pos] > 2000 && rf_data_buf[pos] < 2500)
        {
            gt_data.rfdata.cmd >>= 1;
            gt_data.rfdata.cmd |= 0x80;
        }
        else if(rf_data_buf[pos] > 1000 && rf_data_buf[pos] < 1250)
        {
            gt_data.rfdata.cmd >>= 1;
            gt_data.rfdata.cmd &= ~0x80;
        }
        else
        {
            return FALSE;
        }   
    }
    
    /* parse data */
    for(pos=10; pos<18; pos++)
    {
        if(rf_data_buf[pos] > 2000 && rf_data_buf[pos] < 2500)
        {
            gt_data.rfdata.data >>= 1;
            gt_data.rfdata.data |= 0x80;
        }
        else if(rf_data_buf[pos] > 1000 && rf_data_buf[pos] < 1250)
        {
            gt_data.rfdata.data >>= 1;
            gt_data.rfdata.data &= ~0x80;
        }
        else
        {
            return FALSE;
        }   
    }
    
    /* parse opposite data */
    for(pos=18; pos<26; pos++)
    {
        if(rf_data_buf[pos] > 2000 && rf_data_buf[pos] < 2500)
        {
            gt_data.rfdata.oppdata >>= 1;
            gt_data.rfdata.oppdata |= 0x80;
        }
        else if(rf_data_buf[pos] > 1000 && rf_data_buf[pos] < 1250)
        {
            gt_data.rfdata.oppdata >>= 1;
            gt_data.rfdata.oppdata &= ~0x80;
        }
        else
        {
            return FALSE;
        }   
    }
    
    return TRUE;
}
