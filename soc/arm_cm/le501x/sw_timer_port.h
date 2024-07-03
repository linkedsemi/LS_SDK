#ifndef SW_TIMER_PORT_H_
#define SW_TIMER_PORT_H_
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t sw_timer_time_t;

#define MS_2_PERIOD(x) ms_2_period(x)
#define PERIOD_2_MS(x) period_2_ms(x)

uint32_t ms_2_period(uint32_t x);
uint32_t period_2_ms(uint32_t x);
#ifdef __cplusplus
}
#endif

#endif
