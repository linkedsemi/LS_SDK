#include "field_manipulate.h"
#include "compile_flag.h"
#include "reg_sysc_cpu_type.h"

void XIP_BANNED_FUNC(lscache_msp_init,)
{
    REG_FIELD_WR(SYSC_CPU->PD_CPU_CLKG,SYSC_CPU_CLKG_SET_CACHE,1);
}

void lscache_msp_deinit()
{
    REG_FIELD_WR(SYSC_CPU->PD_CPU_CLKG,SYSC_CPU_CLKG_CLR_CACHE,1);
}