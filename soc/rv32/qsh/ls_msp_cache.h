#ifndef LS_MSP_CACHE_H_
#define LS_MSP_CACHE_H_
#include <stdint.h>
#include "reg_cache_type.h"
#include "reg_base_addr.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef QSH_SYSC_CACHE1_ADDR
#define LSCACHE ((reg_lscache_t *)QSH_SYSC_CACHE1_ADDR)
#endif

#ifdef QSH_SYSC_CACHE2_ADDR
#define LSCACHE2 ((reg_lscache_t *)QSH_SYSC_CACHE2_ADDR)
#endif

void lscache_msp_init(void);

void lscache_msp_deinit(void);

#ifdef __cplusplus
}
#endif

#endif

