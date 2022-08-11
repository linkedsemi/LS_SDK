#include "ls_msp_dmac.h"
#include "gemini.h"
#include "platform.h"
#include "field_manipulate.h"
#include "reg_sysc_cpu_type.h"
#include "sys_stat.h"
#include "ls_hal_dmac.h"


static DMA_Controller_HandleTypeDef *dmac_ptr;

void DMAC_Handler()
{
    HAL_DMA_Controller_IRQHandler(dmac_ptr);
}

void HAL_DMA_Controller_MSP_Init(DMA_Controller_HandleTypeDef *hdma)
{
    dmac_ptr = hdma;
    arm_cm_set_int_isr(DMAC_IRQn, DMAC_Handler);
    REG_FIELD_WR(SYSC_CPU->PD_CPU_CLKG, SYSC_CPU_CLKG_SET_DMAC, 1);
    __NVIC_ClearPendingIRQ(DMAC_IRQn);
    __NVIC_EnableIRQ(DMAC_IRQn);
}

void HAL_DMA_Controller_MSP_DeInit(DMA_Controller_HandleTypeDef *hdma)
{
    __NVIC_DisableIRQ(DMAC_IRQn);
    REG_FIELD_WR(SYSC_CPU->PD_CPU_CLKG, SYSC_CPU_CLKG_CLR_DMAC, 1);
}

void HAL_DMA_Controller_MSP_Busy_Set(DMA_Controller_HandleTypeDef *hdma)
{
    dma_status_set(true);
}

void HAL_DMA_Controller_MSP_Idle_Set(DMA_Controller_HandleTypeDef *hdma)
{
    dma_status_set(false);
}
