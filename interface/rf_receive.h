#ifndef __RF_RECEIVE_H
#define __RF_RECEIVE_H

#include "includes.h"

/****   Marco define   ****/
#define RF_REV_DATA_MAX             (19)
#define RF_DATA_GUIDANCE_CODE       (1)

#define RF_SYSTEM_ON                (0xAA)
#define RF_SYSTEM_OFF               (0x55)

/****   Function define   ****/
void rf_push(uint8 data);
uint8 rf_message_parse(void);
void rf_clear(void);

#endif
