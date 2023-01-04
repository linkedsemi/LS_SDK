#ifndef LS_HAL_CACHE_H_
#define LS_HAL_CACHE_H_
#include <stdint.h>
#include "ls_msp_cache.h"

void lscache_cache_enable(uint8_t prefetch);

void lscache_cache_disable(void);
#endif
