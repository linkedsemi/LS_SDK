#include "ls_msp_touchkey.h"
#include "field_manipulate.h"
#include "platform.h"
#include "lm3050.h"
#include "reg_sysc_per_type.h"
#include "ls_hal_touchkey.h"
#include "sys_stat.h"
#include "reg_v33_rg_type.h"

void HAL_LSTOUCHKEY_MSP_Init(void)
{
    MODIFY_REG(V33_RG->MISC_CTRL1, V33_RG_PD_TK_MASK, 0 << V33_RG_PD_TK_POS);
    SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_CLR_TK_MASK;
    SYSC_PER->PD_PER_SRST3 = SYSC_PER_SRST_CLR_TK_N_MASK;
    SYSC_PER->PD_PER_SRST3 = SYSC_PER_SRST_SET_TK_N_MASK;
    SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_SET_TK_MASK;
    arm_cm_set_int_isr(TK_IRQn, HAL_TOUCHKEY_IRQHandler);
    __NVIC_ClearPendingIRQ(TK_IRQn);
    __NVIC_EnableIRQ(TK_IRQn);
}
void HAL_LSTOUCHKEY_MSP_DeInit(void)
{
    SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_CLR_TK_MASK;
    __NVIC_DisableIRQ(TK_IRQn);
    MODIFY_REG(V33_RG->MISC_CTRL1, V33_RG_PD_TK_MASK, 1 << V33_RG_PD_TK_POS);
}