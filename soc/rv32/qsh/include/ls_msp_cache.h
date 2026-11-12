#ifndef LS_MSP_CACHE_H_
#define LS_MSP_CACHE_H_
#include <stdint.h>
#include "reg_cache_type.h"
#include "reg_base_addr.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef SEC_QSPI1_CCH_ADDR
#define LSCACHE ((reg_lscache_t *)SEC_QSPI1_CCH_ADDR)
#endif

#ifdef APP_QSPI2_CCH_ADDR
#define LSCACHE2 ((reg_lscache_t *)APP_QSPI2_CCH_ADDR)
#endif

void lscache_msp_init(void);

void lscache_msp_deinit(void);

void lscache_cachex_msp_init(void *reg);

void lscache_cachex_msp_deinit(void *reg);

#ifdef __cplusplus
}
#endif

#endif

