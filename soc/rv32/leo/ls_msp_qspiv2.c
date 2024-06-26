#include "ls_msp_qspiv2.h"
#include "reg_sysc_cpu.h"
#include "compile_flag.h"
#include "leo.h"
#include "core_rv32.h"
#include "cpu.h"
#include "compile_flag.h"

ROM_SYMBOL uint32_t (*qspiv2_global_int_disable_fn)();
ROM_SYMBOL void (*qspiv2_global_int_restore_fn)(uint32_t);

#if defined(BOOT_ROM)
void qspiv2_global_int_dummy(){}
void XIP_BANNED_FUNC(lsqspiv2_msp_init)
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

#if FLASH_PROG_ALGO==1
void qspiv2_global_int_ctrl_fn_init(){}
#else
void qspiv2_global_int_ctrl_fn_init()
{
    qspiv2_global_int_disable_fn = enter_critical;
    qspiv2_global_int_restore_fn = exit_critical;
}
#endif

void XIP_BANNED_FUNC(lsqspiv2_msp_init)
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
    qspiv2_global_int_ctrl_fn_init();
}
#endif
