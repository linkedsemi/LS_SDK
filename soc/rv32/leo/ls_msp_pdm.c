#include "platform.h"
#include "leo.h"
#include "reg_sysc_per.h"
#include "field_manipulate.h"
#include "sys_stat.h"
#include "dmac_config.h"
#include "ls_hal_pdm.h"
#include "core_rv32.h"
#include "exception_isr.h"

static PDM_HandleTypeDef *pdm_inst;

void PDM_Handler()
{
    HAL_PDM_IRQHandler(pdm_inst);
}

void HAL_PDM_MSP_Init(PDM_HandleTypeDef *hpdm)
{
    SYSC_PER->PD_PER_CLKG2 = SYSC_PER_CLKG_SET_PDM_MASK;
    rv_set_int_isr(PDM_IRQn, PDM_Handler);
    pdm_inst = hpdm;
    csi_vic_clear_pending_irq(PDM_IRQn);
    csi_vic_enable_irq(PDM_IRQn);
}

void HAL_PDM_MSP_DeInit(PDM_HandleTypeDef *hpdm)
{
    csi_vic_disable_irq(PDM_IRQn);
    SYSC_PER->PD_PER_CLKG2 = SYSC_PER_CLKG_CLR_PDM_MASK;
}

void HAL_PDM_MSP_Busy_Set(PDM_HandleTypeDef *hpdm)
{
    pdm_status_set(true);
}

void HAL_PDM_MSP_Idle_Set(PDM_HandleTypeDef *hpdm)
{
    pdm_status_set(false);
}

uint8_t HAL_PDM_CH0_Handshake_Get(PDM_HandleTypeDef *hpdm)
{
    return PDM_CH0;
}

uint8_t HAL_PDM_CH1_Handshake_Get(PDM_HandleTypeDef *hpdm)
{
    return PDM_CH1;
}