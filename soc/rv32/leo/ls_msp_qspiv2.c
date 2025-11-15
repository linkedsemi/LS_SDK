#include "ls_msp_qspiv2.h"
#include "reg_sysc_cpu.h"
#include "compile_flag.h"
#include "leo.h"
#include "core_rv32.h"
#include "cpu.h"
#include "compile_flag.h"

#if defined(BOOT_ROM)
uint32_t (*qspiv2_global_int_disable_fn)();
void (*qspiv2_global_int_restore_fn)(uint32_t);
void qspiv2_global_int_dummy(){}
void XIP_BANNED_FUNC(lsqspiv2_msp_init,reg_lsqspiv2_t *reg)
{
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_SET_QSPI_MASK;
    __NOP(); __NOP();
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_CLR_QSPI_MASK;
    __NOP(); __NOP();
    SYSC_CPU->PD_CPU_SRST = SYSC_CPU_SRST_CLR_QSPI_N_MASK;
    __NOP(); __NOP();
    SYSC_CPU->PD_CPU_SRST = SYSC_CPU_SRST_SET_QSPI_N_MASK;
    __NOP(); __NOP();
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_SET_QSPI_MASK;
    qspiv2_global_int_disable_fn = (void *)qspiv2_global_int_dummy;
    qspiv2_global_int_restore_fn = (void *)qspiv2_global_int_dummy;
}
#else

uint32_t (*qspiv2_global_int_disable_fn)() = enter_critical;
void (*qspiv2_global_int_restore_fn)(uint32_t) = exit_critical;

void XIP_BANNED_FUNC(lsqspiv2_msp_init,reg_lsqspiv2_t *reg)
{
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_SET_QSPI_MASK;
    __NOP(); __NOP();
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_CLR_QSPI_MASK;
    __NOP(); __NOP();
    SYSC_CPU->PD_CPU_SRST = SYSC_CPU_SRST_CLR_QSPI_N_MASK;
    __NOP(); __NOP();
    SYSC_CPU->PD_CPU_SRST = SYSC_CPU_SRST_SET_QSPI_N_MASK;
    __NOP(); __NOP();
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_SET_QSPI_MASK;
}
#endif
