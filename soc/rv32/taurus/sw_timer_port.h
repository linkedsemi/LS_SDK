#ifndef SW_TIMER_PORT_H_
#define SW_TIMER_PORT_H_
#include <stdint.h>
#include "ll_port.h"
typedef uint32_t sw_timer_time_t;

#define MS_2_PERIOD(x) (MAC_CLK_MHZ*(x)*1000)
#define PERIOD_2_MS(x) ((x)/1000/MAC_CLK_MHZ)

#endif
