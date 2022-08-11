#include "ls_hal_cache.h"
#include "ls_msp_cache.h"
#include "field_manipulate.h"
#include "compile_flag.h"


void XIP_BANNED_FUNC(lscache_cache_enable,uint8_t prefetch)
{
    lscache_msp_init();
    LSCACHE->CCR = FIELD_BUILD(LSCACHE_SET_PREFETCH, prefetch) | FIELD_BUILD(LSCACHE_EN, 1);
}


void lscache_cache_disable()
{
    LSCACHE->CCR = FIELD_BUILD(LSCACHE_EN, 0);
    lscache_msp_deinit();
}
