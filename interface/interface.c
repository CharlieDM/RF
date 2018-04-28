
#include "interface.h"

void hal_init(void)
{
    hal_ioinit();
    hal_uartinit();
    hal_timerinit();
}





