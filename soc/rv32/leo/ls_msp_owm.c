#include "ls_msp_owm.h"
#include "ls_hal_owm.h"
#include "field_manipulate.h"
#include "platform.h"
#include "reg_sysc_per.h"
#include "leo.h"
#include "core_rv32.h"
#include "exception_isr.h"
#include "reg_sysc_cpu.h"
#include "sys_stat.h"

static OWM_HandleTypeDef* owm_inst_env;

void OWM_Handler(void)
{
    HAL_LSOWM_IRQHandler(owm_inst_env);
}

void HAL_LSOWM_MSP_Init(OWM_HandleTypeDef* inst)
{
    owm_inst_env = inst;
    SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_CLR_OWM_MASK;
    SYSC_PER->PD_PER_SRST3 = SYSC_PER_SRST_CLR_OWM_MASK;
    SYSC_PER->PD_PER_SRST3 = SYSC_PER_SRST_SET_OWM_MASK;
    SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_SET_OWM_MASK;
    rv_set_int_isr(OWM_IRQn, OWM_Handler);
    csi_vic_clear_pending_irq(OWM_IRQn);
    csi_vic_enable_irq(OWM_IRQn);                         
}

void HAL_LSOWM_MSP_DeInit(OWM_HandleTypeDef* inst)
{
    SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_CLR_OWM_MASK;
    csi_vic_disable_irq(OWM_IRQn);
}