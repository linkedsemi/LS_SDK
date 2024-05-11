#include "ls_msp_touchkey.h"
#include "ls_hal_touchkey.h"
#include "field_manipulate.h"
#include "exception_isr.h"
#include "reg_sysc_per.h"
#include "reg_v33_rg.h"
#include "core_rv32.h"
#include "platform.h"
#include "sys_stat.h"
#include "leo.h"

void HAL_LSTOUCHKEY_MSP_Init(void)
{
    MODIFY_REG(V33_RG->MISC_CTRL1, V33_RG_PD_TK_MASK, 0 << V33_RG_PD_TK_POS);
    SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_CLR_TK_MASK;
    SYSC_PER->PD_PER_SRST3 = SYSC_PER_SRST_CLR_TK_N_MASK;
    SYSC_PER->PD_PER_SRST3 = SYSC_PER_SRST_SET_TK_N_MASK;
    SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_SET_TK_MASK;
    rv_set_int_isr(TK_IRQn, HAL_TOUCHKEY_IRQHandler);
    csi_vic_clear_pending_irq(TK_IRQn);
    csi_vic_enable_irq(TK_IRQn);
}
void HAL_LSTOUCHKEY_MSP_DeInit(void)
{
    SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_CLR_TK_MASK;
    csi_vic_disable_irq(TK_IRQn);
    MODIFY_REG(V33_RG->MISC_CTRL1, V33_RG_PD_TK_MASK, 1 << V33_RG_PD_TK_POS);
}

void HAL_LSTOUCHKEY_MSP_Busy_Set(void)
{
    touchkey_status_set(true);
}

void HAL_LSTOUCHKEY_MSP_Idle_Set(void)
{
    touchkey_status_set(false);
}
