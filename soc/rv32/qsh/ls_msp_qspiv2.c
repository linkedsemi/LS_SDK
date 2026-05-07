#include "ls_msp_qspiv2.h"
#include "reg_sysc_sec_cpu.h"
#include "reg_sysc_app_cpu.h"
#include "compile_flag.h"
#include "core_rv32.h"
#include "cpu.h"
#include "compile_flag.h"

void XIP_BANNED_FUNC(lsqspiv2_msp_init,reg_lsqspiv2_t *reg)
{
    if (LSQSPIV2 == reg) {
        SYSC_SEC_CPU->PD_CPU_CLKG[0] = SYSC_SEC_CPU_CLKG_SET_QSPI1_MASK;
        __NOP(); __NOP();
        SYSC_SEC_CPU->PD_CPU_CLKG[0] = SYSC_SEC_CPU_CLKG_CLR_QSPI1_MASK;
        __NOP(); __NOP();
        SYSC_SEC_CPU->PD_CPU_SRST[0] = SYSC_SEC_CPU_SRST_CLR_QSPI1_MASK;
        __NOP(); __NOP();
        SYSC_SEC_CPU->PD_CPU_SRST[0] = SYSC_SEC_CPU_SRST_SET_QSPI1_MASK;
        __NOP(); __NOP();
        SYSC_SEC_CPU->PD_CPU_CLKG[0] = SYSC_SEC_CPU_CLKG_SET_QSPI1_MASK;
    } else if (LSQSPIV2_2 == reg) {
        SYSC_APP_CPU->PD_CPU_CLKG[0] = SYSC_APP_CPU_CLKG_SET_QSPI2_MASK;
        __NOP(); __NOP();
        SYSC_APP_CPU->PD_CPU_CLKG[0] = SYSC_APP_CPU_CLKG_CLR_QSPI2_MASK;
        __NOP(); __NOP();
        SYSC_APP_CPU->PD_CPU_SRST[0] = SYSC_APP_CPU_SRST_CLR_QSPI2_MASK;
        __NOP(); __NOP();
        SYSC_APP_CPU->PD_CPU_SRST[0] = SYSC_APP_CPU_SRST_SET_QSPI2_MASK;
        __NOP(); __NOP();
        SYSC_APP_CPU->PD_CPU_CLKG[0] = SYSC_APP_CPU_CLKG_SET_QSPI2_MASK;
    }
}
