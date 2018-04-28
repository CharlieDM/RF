
#ifndef _DATA_H_
#define _DATA_H_

#include "type_def.h"

#define F_CPU       (8000000)

/****   Typedef define   ****/
typedef enum
{
    MODE_SLEEPING   =    0x00,
    MODE_WORKING    =    0x01,
} eRunStatus;


typedef struct state_t
{
    uint8 sys;
    uint8 bat;
    uint8 sw;
    volatile uint8 start;
    volatile uint8 time1s;
}state_t;

typedef struct rfdata_t
{
    volatile uint8 state;
    volatile uint8 data;
    volatile uint8 connecting;
}rfdata_t;

extern struct state_t gst_state;
extern struct rfdata_t gst_rf;

#endif /* _DATA_H_ */
