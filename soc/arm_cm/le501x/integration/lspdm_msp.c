#include "lspdm_msp.h"
#include "platform.h"
#include "le501x.h"
#include "field_manipulate.h"
#include "reg_rcc.h"
#include "sys_stat.h"
#include "dmac_config.h"
static PDM_HandleTypeDef *pdm_inst;

void PDM_Handler()
{
    HAL_PDM_IRQHandler(pdm_inst);
}

void HAL_PDM_MSP_Init(PDM_HandleTypeDef *hpdm)
{
    pdm_inst = hpdm;
    arm_cm_set_int_isr(PDM_IRQn,PDM_Handler);
    REG_FIELD_WR(RCC->APB1EN, RCC_PDM, 1);
    __NVIC_ClearPendingIRQ(PDM_IRQn);
    __NVIC_EnableIRQ(PDM_IRQn);
}

void HAL_PDM_MSP_DeInit(PDM_HandleTypeDef *hpdm)
{
    __NVIC_DisableIRQ(PDM_IRQn);
    REG_FIELD_WR(RCC->APB1EN,RCC_PDM,0);
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
