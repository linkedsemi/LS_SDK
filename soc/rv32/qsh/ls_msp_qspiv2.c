#include "ls_msp_qspiv2.h"
#include "reg_sysc_sec_cpu.h"
#include "compile_flag.h"
#include "core_rv32.h"
#include "cpu.h"
#include "compile_flag.h"

ROM_SYMBOL uint32_t (*qspiv2_global_int_disable_fn)();
ROM_SYMBOL void (*qspiv2_global_int_restore_fn)(uint32_t);

#if defined(BOOT_ROM)
void qspiv2_global_int_dummy(){}
void qspiv2_global_int_ctrl_fn_init()
{
    qspiv2_global_int_disable_fn = (void *)qspiv2_global_int_dummy;
    qspiv2_global_int_restore_fn = (void *)qspiv2_global_int_dummy;
}
#elif defined(FLASH_PROG_ALGO)
void qspiv2_global_int_dummy(){}
void qspiv2_global_int_ctrl_fn_init(){
    qspiv2_global_int_disable_fn = (void *)qspiv2_global_int_dummy;
    qspiv2_global_int_restore_fn = (void *)qspiv2_global_int_dummy;
}
#else
void qspiv2_global_int_ctrl_fn_init()
{
    qspiv2_global_int_disable_fn = enter_critical;
    qspiv2_global_int_restore_fn = exit_critical;
}
#endif

void XIP_BANNED_FUNC(lsqspiv2_msp_init,reg_lsqspiv2_t *reg)
{
    SYSC_SEC_CPU->PD_CPU_CLKG[0] = SYSC_SEC_CPU_CLKG_SET_QSPI1_MASK;
    __NOP(); __NOP();
    SYSC_SEC_CPU->PD_CPU_CLKG[0] = SYSC_SEC_CPU_CLKG_CLR_QSPI1_MASK;
    __NOP(); __NOP();
    SYSC_SEC_CPU->PD_CPU_SRST[0] = SYSC_SEC_CPU_SRST_CLR_QSPI1_MASK;
    __NOP(); __NOP();
    SYSC_SEC_CPU->PD_CPU_SRST[0] = SYSC_SEC_CPU_SRST_SET_QSPI1_MASK;
    __NOP(); __NOP();
    SYSC_SEC_CPU->PD_CPU_CLKG[0] = SYSC_SEC_CPU_CLKG_SET_QSPI1_MASK;
    qspiv2_global_int_ctrl_fn_init();
}
