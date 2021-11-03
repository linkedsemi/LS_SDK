#ifndef SYSTICK_H_
#define SYSTICK_H_
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include "sdk_config.h"

#ifndef SYSTICK_RATE_HZ
#define SYSTICK_RATE_HZ (1000)
#endif

#define SYSTICK_MS2TICKS(ms) ((ms)*SYSTICK_RATE_HZ/1000)

#define SYSTICK_TICKS2MS(ticks) ((ticks)*1000/SYSTICK_RATE_HZ)

void systick_start(void);

uint32_t systick_get_value(void);

bool systick_poll_timeout(uint32_t start_tick,uint32_t timeout,bool (*poll)(va_list),...);

void systick_stop(void);
#endif
