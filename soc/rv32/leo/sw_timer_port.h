#ifndef SW_TIMER_PORT_H_
#define SW_TIMER_PORT_H_
#include <stdint.h>
#include "sdk_config.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t sw_timer_time_t;

#define MS_2_PERIOD(x) ((x)*SDK_LCLK_HZ/1000)
#define PERIOD_2_MS(x) ((x)*1000/SDK_LCLK_HZ)

#ifdef __cplusplus
}
#endif

#endif
