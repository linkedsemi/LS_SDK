#include "ls_msp_crypt.h"
#include "ls_hal_crypt.h"
#include "field_manipulate.h"
#include "exception_isr.h"
#include "reg_cpu0_sys.h"
#include "core_rv32.h"
#include "sys_stat.h"
#include "raptor.h"

void HAL_LSCRYPT_MSP_Init(void)
{
    REG_FIELD_WR(CPU0_SYS_CFG->CPU0_SYS_CFG_REG5, CPU0_SYS_CRYPT_APB_CLK_CLK_CG0_13, 0x1);
    CPU0_SYS_CFG -> CPU0_SYS_CRG_SYS3_APB_CLK_TOP_RST_N_REG0_CLR = 0x2000;
    CPU0_SYS_CFG -> CPU0_SYS_CRG_SYS3_APB_CLK_TOP_RST_N_REG0 = 0x2000;
    rv_set_int_isr(CPU_CRYPT_IRQn, HAL_LSCRYPT_IRQHandler);
    csi_vic_clear_pending_irq(CPU_CRYPT_IRQn);
    csi_vic_enable_irq(CPU_CRYPT_IRQn);
}

void HAL_LSCRYPT_MSP_DeInit(void)
{
    REG_FIELD_WR(CPU0_SYS_CFG->CPU0_SYS_CFG_REG5, CPU0_SYS_CRYPT_APB_CLK_CLK_CG0_13, 0x0);
    csi_vic_disable_irq(CPU_CRYPT_IRQn);
}

void HAL_LSCRYPT_MSP_Busy_Set(void)
{
    // crypt_status_set(true);
}

void HAL_LSCRYPT_MSP_Idle_Set(void)
{
    // crypt_status_set(false);
}


