#include "lscache.h"
#include "lscache_msp.h"
#include "reg_lscache_type.h"
#include "field_manipulate.h"
#include "reg_base_addr.h"
#include "compile_flag.h"
#define LSCACHE ((reg_lscache_t *)CACHE_BASE_ADDR)

XIP_BANNED void lscache_cache_enable(uint8_t prefetch)
{
    lscache_msp_init();
    LSCACHE->CCR = FIELD_BUILD(LSCACHE_SET_PREFETCH, prefetch) | FIELD_BUILD(LSCACHE_EN, 1);
}


void lscache_cache_disable()
{
    LSCACHE->CCR = FIELD_BUILD(LSCACHE_EN, 0);
    lscache_msp_deinit();
}
