#include "ls_msp_sm4.h"
#include "ls_hal_sm4.h"
#include "field_manipulate.h"
#include "exception_isr.h"
// #include "reg_sysc_sec_cpu.h"
#include "reg_cpu0_sys.h"
#include "core_rv32.h"
#include "platform.h"
#include "raptor.h"

void HAL_LSSM4_MSP_Init(void)
{
    REG_FIELD_WR(CPU0_SYS_CFG->CPU0_SYS_CFG_REG5, CPU0_SYS_CALC_SM4_APB_CLK_CLK_CG0_14, 0x1);
    CPU0_SYS_CFG -> CPU0_SYS_CRG_SYS3_APB_CLK_TOP_RST_N_REG0_CLR = 0x4000;
    CPU0_SYS_CFG -> CPU0_SYS_CRG_SYS3_APB_CLK_TOP_RST_N_REG0 = 0x4000;
    rv_set_int_isr(CPU_CALC_SM4_IRQn, HAL_SM4_IRQHandler);
    csi_vic_clear_pending_irq(CPU_CALC_SM4_IRQn);
    csi_vic_enable_irq(CPU_CALC_SM4_IRQn);
}

void HAL_LSSM4_MSP_DeInit(void)
{
    REG_FIELD_WR(CPU0_SYS_CFG->CPU0_SYS_CFG_REG5, CPU0_SYS_CALC_SM4_APB_CLK_CLK_CG0_14, 0x0);
    csi_vic_disable_irq(CPU_CALC_SM4_IRQn);
}