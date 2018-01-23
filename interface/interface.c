
#include "interface.h"
#include "hal_io.h"
#include "hal_timer.h"

void hal_init(void)
{
    hal_ioinit();
    hal_timerinit();
}





