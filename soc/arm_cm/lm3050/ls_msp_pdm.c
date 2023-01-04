#include "ls_msp_pdm.h"
#include "platform.h"
#include "lm3050.h"
#include "reg_sysc_per_type.h"
#include "field_manipulate.h"
#include "sys_stat.h"
#include "dmac_config.h"
#include "ls_hal_pdm.h"

static PDM_HandleTypeDef *pdm_inst;

void PDM_Handler()
{
    HAL_PDM_IRQHandler(pdm_inst);
}

void HAL_PDM_MSP_Init(PDM_HandleTypeDef *hpdm)
{
    SYSC_PER->PD_PER_CLKG2 = SYSC_PER_CLKG_SET_PDM_MASK;
    arm_cm_set_int_isr(PDM_IRQn, PDM_Handler);
    pdm_inst = hpdm;
    __NVIC_ClearPendingIRQ(PDM_IRQn);
    __NVIC_EnableIRQ(PDM_IRQn);
}

void HAL_PDM_MSP_DeInit(PDM_HandleTypeDef *hpdm)
{
    __NVIC_DisableIRQ(PDM_IRQn);
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
    return CH_PDMCH0_RX;
}

uint8_t HAL_PDM_CH1_Handshake_Get(PDM_HandleTypeDef *hpdm)
{
    return CH_PDMCH1_RX;
}