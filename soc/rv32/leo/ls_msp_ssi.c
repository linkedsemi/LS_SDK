#include "ls_msp_ssi.h"
#include "ls_hal_ssi.h"
#include "field_manipulate.h"
#include "exception_isr.h"
#include "reg_sysc_per.h"
#include "dmac_config.h"
#include "core_rv32.h"
#include "platform.h"
#include "sys_stat.h"

static SSI_HandleTypeDef *ssi_inst_env[1];

static void SSI_Handler()
{
    HAL_SSI_IRQHandler(ssi_inst_env[0]);
}

void HAL_SSI_MSP_Init(struct __SSI_HandleTypeDef *hssi)
{
    SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_CLR_SPI1_MASK;
    SYSC_PER->PD_PER_SRST1 = SYSC_PER_SRST_CLR_SPI1_N_MASK;
    SYSC_PER->PD_PER_SRST1 = SYSC_PER_SRST_SET_SPI1_N_MASK;
    SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_SET_SPI1_MASK;
    rv_set_int_isr(SPI1_IRQn, SSI_Handler);
    ssi_inst_env[0] = hssi;
    csi_vic_clear_pending_irq(SPI1_IRQn);
    csi_vic_enable_irq(SPI1_IRQn);
}

void HAL_SSI_MSP_DeInit(struct __SSI_HandleTypeDef *hssi)
{
    SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_CLR_SPI1_MASK;
    csi_vic_disable_irq(SPI1_IRQn);
}

void HAL_SSI_MSP_Busy_Set(struct __SSI_HandleTypeDef *hssi)
{
    spi1_status_set(true);
}

void HAL_SSI_MSP_Idle_Set(struct __SSI_HandleTypeDef *hssi)
{
    spi1_status_set(false);
}

uint8_t HAL_SSI_TX_DMA_Handshake_Get(struct __SSI_HandleTypeDef *hssi)
{
    return SPI1_TX;
}

uint8_t HAL_SSI_RX_DMA_Handshake_Get(struct __SSI_HandleTypeDef *hssi)
{
    return SPI1_RX;
}

__attribute__((weak)) void LL_SSI_IRQHandler() {}

void LL_SSI_MSP_Init(void)
{
    rv_set_int_isr(SPI1_IRQn, LL_SSI_IRQHandler);
    SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_SET_SPI1_MASK;
}

void LL_SSI_MSP_DeInit(void)
{
    SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_CLR_SPI1_MASK;
}