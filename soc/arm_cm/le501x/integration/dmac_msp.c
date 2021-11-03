#include "dmac_msp.h"
#include "reg_rcc.h"
#include "le501x.h"
#include "platform.h"
#include "field_manipulate.h"
#include "sys_stat.h"
#include "dmac_config.h"

static DMA_Controller_HandleTypeDef *dmac_ptr;

void DMAC_Handler()
{
    HAL_DMA_Controller_IRQHandler(dmac_ptr);
}

void HAL_DMA_Controller_MSP_Init(DMA_Controller_HandleTypeDef *hdma)
{
    dmac_ptr = hdma;
    arm_cm_set_int_isr(DMA_IRQn,DMAC_Handler);
    REG_FIELD_WR(RCC->APB2EN,RCC_DMA1,1);
    __NVIC_ClearPendingIRQ(DMA_IRQn);
    __NVIC_EnableIRQ(DMA_IRQn);
}


void HAL_DMA_Controller_MSP_DeInit(DMA_Controller_HandleTypeDef *hdma)
{
    __NVIC_DisableIRQ(DMA_IRQn);
    REG_FIELD_WR(RCC->APB2EN,RCC_DMA1,0);
}

void HAL_DMA_Controller_MSP_Busy_Set(DMA_Controller_HandleTypeDef *hdma)
{
    dma_status_set(true);
}

void HAL_DMA_Controller_MSP_Idle_Set(DMA_Controller_HandleTypeDef *hdma)
{
    dma_status_set(false);
}
