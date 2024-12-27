#include "field_manipulate.h"
#include "compile_flag.h"
#include "reg_sysc_sec_cpu.h"
#include "reg_sysc_app_cpu.h"

void XIP_BANNED_FUNC(lscache_msp_init,)
{
    SYSC_SEC_CPU->PD_CPU_CLKG[0] = SYSC_SEC_CPU_CLKG_CLR_CACHE1_MASK;
    SYSC_SEC_CPU->PD_CPU_SRST[0] = SYSC_SEC_CPU_SRST_CLR_CACHE1_MASK;
    SYSC_SEC_CPU->PD_CPU_SRST[0] = SYSC_SEC_CPU_SRST_SET_CACHE1_MASK;
    SYSC_SEC_CPU->PD_CPU_CLKG[0] = SYSC_SEC_CPU_CLKG_SET_CACHE1_MASK;
}

void lscache_msp_deinit()
{
    SYSC_SEC_CPU->PD_CPU_CLKG[0] = SYSC_SEC_CPU_CLKG_CLR_CACHE1_MASK;
}
