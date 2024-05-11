#include "ls_msp_cec.h"
#include "field_manipulate.h"
#include "ls_hal_cec.h"
#include "leo.h"
#include "core_rv32.h"
#include "reg_sysc_awo.h"
#include "reg_sysc_per.h"
#include "exception_isr.h"

static CEC_HandleTypeDef *CEC_inst_env;

void CEC_Handler(void)
{
    HAL_CEC_IRQHandler(CEC_inst_env);
}

void HAL_CEC_MSP_Init(CEC_HandleTypeDef *inst)
{	
    CEC_inst_env = inst;
    SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_CLR_CEC_MASK;
    SYSC_PER->PD_PER_SRST3 = SYSC_PER_SRST_CLR_CEC_MASK;
    SYSC_PER->PD_PER_SRST3 = SYSC_PER_SRST_SET_CEC_MASK;
    SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_SET_CEC_MASK;
    rv_set_int_isr(CEC_IRQn, CEC_Handler);	
    csi_vic_clear_pending_irq(CEC_IRQn);
    csi_vic_enable_irq(CEC_IRQn);
}

void HAL_CEC_MSP_DeInit(CEC_HandleTypeDef *inst)
{
    SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_CLR_CEC_MASK;
    csi_vic_disable_irq(CEC_IRQn);
}


