
#ifndef _DATA_H_
#define _DATA_H_

#include "type_def.h"

/****   Typedef define   ****/
typedef enum
{
    MODE_SLEEPING   =    0x00,
    MODE_WORKING    =    0x01,
} eRunStatus;

typedef struct st_data
{
    struct 
    {
        volatile uint8 sys_sta;
        volatile uint8 bat_sta;
        volatile uint8 sw_sta;
        volatile uint8 start_sta;
    }status;
    struct
    {
       volatile uint8 cmd;
       volatile uint8 data;
       volatile uint8 oppdata;
    }rfdata;
}data_t;

extern data_t gt_data;

#endif /* _DATA_H_ */
