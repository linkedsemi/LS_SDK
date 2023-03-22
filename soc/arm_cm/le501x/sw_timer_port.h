#ifndef SW_TIMER_PORT_H_
#define SW_TIMER_PORT_H_
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t sw_timer_time_t;

#define MS_2_PERIOD(x) (2000*(uint64_t)(x)/625)
#define PERIOD_2_MS(x) (625*(uint64_t)(x)/2000)

#ifdef __cplusplus
}
#endif

#endif
