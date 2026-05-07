#include "ls_hal_cache.h"
#include "ls_msp_cache.h"
#include "field_manipulate.h"
#include "compile_flag.h"


void XIP_BANNED_FUNC(lscache_cache_enable,uint8_t prefetch)
{
    lscache_msp_init();
    LSCACHE->CCR = FIELD_BUILD(LSCACHE_SET_PREFETCH, prefetch) | FIELD_BUILD(LSCACHE_EN, 1);
    while (!(LSCACHE->SR & 0x4));
    while ((LSCACHE->SR & 0x4));
}


void lscache_cache_disable()
{
    LSCACHE->CCR = FIELD_BUILD(LSCACHE_EN, 0);
    lscache_msp_deinit();
}

void XIP_BANNED_FUNC(lscache_cachex_enable,reg_lscache_t *reg,uint8_t prefetch)
{
    lscache_cachex_msp_init((void *)reg);
    reg->CCR = FIELD_BUILD(LSCACHE_SET_PREFETCH, prefetch) | FIELD_BUILD(LSCACHE_EN, 1);
    while (!(reg->SR & 0x4));
    while ((reg->SR & 0x4));
}

void XIP_BANNED_FUNC(lscache_cachex_stat_enable,reg_lscache_t *reg)
{
    reg->CCR |= FIELD_BUILD(LSCACHE_STATISTIC_EN, 1);
}

void lscache_cachex_disable(reg_lscache_t *reg)
{
    reg->CCR = FIELD_BUILD(LSCACHE_EN, 0);
    lscache_cachex_msp_deinit((void *)reg);
}
