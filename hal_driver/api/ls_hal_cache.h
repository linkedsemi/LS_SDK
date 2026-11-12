#ifndef LS_HAL_CACHE_H_
#define LS_HAL_CACHE_H_
#include <stdint.h>
#include "ls_msp_cache.h"

#ifdef __cplusplus
extern "C" {
#endif

void lscache_cache_enable(uint8_t prefetch);

void lscache_cache_disable(void);

void lscache_cachex_enable(reg_lscache_t *reg, uint8_t prefetch);

void lscache_cachex_disable(reg_lscache_t *reg);

void lscache_cachex_stat_enable(reg_lscache_t *reg);

#ifdef __cplusplus
}
#endif

#endif
