#ifndef LS_HAL_CACHE_H_
#define LS_HAL_CACHE_H_
#include <stdint.h>
#include "ls_msp_cache.h"

#ifdef __cplusplus
extern "C" {
#endif

void lscache_cache_enable(uint8_t prefetch);

void lscache_cache_disable(void);

#ifdef __cplusplus
}
#endif

#endif
