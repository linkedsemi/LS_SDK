#include "ls_msp_ssi.h"
#include "field_manipulate.h"
#include "platform.h"
#include "lm3050.h"
#include "sys_stat.h"
#include "reg_sysc_per_type.h"
#include "ls_hal_ssi.h"
#include "dmac_config.h"
static SSI_HandleTypeDef *ssi_inst_env[1];

static void SSI_Handler()
{
    HAL_SSI_IRQHandler(ssi_inst_env[0]);
}

void HAL_SSI_MSP_Init(SSI_HandleTypeDef *hssi)
{
    SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_CLR_SPI1_MASK;
    SYSC_PER->PD_PER_SRST1 = SYSC_PER_SRST_CLR_SPI1_N_MASK;
    SYSC_PER->PD_PER_SRST1 = SYSC_PER_SRST_SET_SPI1_N_MASK;
    SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_SET_SPI1_MASK;
    arm_cm_set_int_isr(SPI1_IRQn, SSI_Handler);
    ssi_inst_env[0] = hssi;
    __NVIC_ClearPendingIRQ(SPI1_IRQn);
    __NVIC_EnableIRQ(SPI1_IRQn);
}

void HAL_SSI_MSP_DeInit(SSI_HandleTypeDef *hssi)
{
    SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_CLR_SPI1_MASK;
    __NVIC_DisableIRQ(SPI1_IRQn);
}

void HAL_SSI_MSP_Busy_Set(SSI_HandleTypeDef *hssi)
{
    spi1_status_set(true);
}

void HAL_SSI_MSP_Idle_Set(SSI_HandleTypeDef *hssi)
{
    spi1_status_set(false);
}

uint8_t HAL_SSI_TX_DMA_Handshake_Get(SSI_HandleTypeDef *hssi)
{
    return CH_SPI1_TX;
}

uint8_t HAL_SSI_RX_DMA_Handshake_Get(SSI_HandleTypeDef *hssi)
{
    return CH_SPI1_RX;
}

__attribute__((weak)) void LL_SSI_IRQHandler(){}
void LL_SSI_MSP_Init(void)
{

    SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_SET_SPI1_MASK;
        arm_cm_set_int_isr(SPI1_IRQn, LL_SSI_IRQHandler);
}

void LL_SSI_MSP_DeInit(void)
{
    SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_CLR_SPI1_MASK;
}