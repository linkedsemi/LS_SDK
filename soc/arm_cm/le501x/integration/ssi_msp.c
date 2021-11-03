#include "ssi_msp.h"
#include "reg_rcc.h"
#include "field_manipulate.h"
#include "platform.h"
#include "le501x.h"
#include "sys_stat.h"
#include "dmac_config.h"
static SSI_HandleTypeDef *ssi_inst_env[1];

static void SSI_Handler()
{
    HAL_SSI_IRQHandler(ssi_inst_env[0]);
}

void HAL_SSI_MSP_Init(SSI_HandleTypeDef *hssi)
{
    ssi_inst_env[0] = hssi;
    REG_FIELD_WR(RCC->APB2RST,RCC_SPI1,1);
    REG_FIELD_WR(RCC->APB2RST,RCC_SPI1,0);
    arm_cm_set_int_isr(SPI1_IRQn,SSI_Handler);
    __NVIC_ClearPendingIRQ(SPI1_IRQn);
    __NVIC_EnableIRQ(SPI1_IRQn);
    REG_FIELD_WR(RCC->APB2EN,RCC_SPI1,1);
}

void HAL_SSI_MSP_DeInit(SSI_HandleTypeDef *hssi)
{
    REG_FIELD_WR(RCC->APB2EN,RCC_SPI1,0);
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

