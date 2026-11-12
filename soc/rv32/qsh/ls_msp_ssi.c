#include "ls_msp_ssi.h"
#include "ls_hal_ssi.h"
#include "field_manipulate.h"
#include "exception_isr.h"
#include "core_rv32.h"
#include "platform.h"
#include "sys_stat.h"
#include "dmac_config.h"

__attribute__((__unused__))
static SSI_HandleTypeDef *ssi_inst_env[1];

__attribute__((__unused__))
static void SSI_Handler()
{
}

__attribute__((__unused__))
void HAL_SSI_MSP_Init(struct __SSI_HandleTypeDef *hssi)
{
}

__attribute__((__unused__))
void HAL_SSI_MSP_DeInit(struct __SSI_HandleTypeDef *hssi)
{
}

__attribute__((__unused__))
void HAL_SSI_MSP_Busy_Set(struct __SSI_HandleTypeDef *hssi)
{
}

__attribute__((__unused__))
void HAL_SSI_MSP_Idle_Set(struct __SSI_HandleTypeDef *hssi)
{
}

uint8_t HAL_SSI_TX_DMA_Handshake_Get(struct __SSI_HandleTypeDef *hssi)
{
    uint8_t ret = 0;
    switch((uint32_t)hssi->REG) {
        case APP_DWSPI3_ADDR: ret = DMA_SPI3_TX; break;
        case APP_DWSPI4_ADDR: ret = DMA_SPI4_TX; break;
        default: break;
    }

    return ret;
}

uint8_t HAL_SSI_RX_DMA_Handshake_Get(struct __SSI_HandleTypeDef *hssi)
{
    uint8_t ret = 0;
    switch((uint32_t)hssi->REG) {
        case APP_DWSPI3_ADDR: ret = DMA_SPI3_RX; break;
        case APP_DWSPI4_ADDR: ret = DMA_SPI4_RX; break;
        default: break;
    }

    return ret;
}

__attribute__((weak))
void LL_SSI_IRQHandler() {}

__attribute__((__unused__))
void LL_SSI_MSP_Init(void)
{
}

__attribute__((__unused__))
void LL_SSI_MSP_DeInit(void)
{
}
