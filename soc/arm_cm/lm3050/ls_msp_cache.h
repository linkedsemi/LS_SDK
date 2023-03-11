#ifndef LS_MSP_CACHE_H_
#define LS_MSP_CACHE_H_
#include <stdint.h>
#include "reg_cache_type.h"
#include "reg_base_addr.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LSCACHE ((reg_lscache_t *)CACHE_BASE_ADDR)

void lscache_msp_init(void);

void lscache_msp_deinit(void);

#ifdef __cplusplus
}
#endif

#endif

