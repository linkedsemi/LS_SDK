#include "ls_msp_ssi.h"
#include "ls_hal_ssi.h"
#include "field_manipulate.h"
#include "exception_isr.h"
#include "core_rv32.h"
#include "platform.h"
#include "sys_stat.h"

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

__attribute__((__unused__))
uint8_t HAL_SSI_TX_DMA_Handshake_Get(struct __SSI_HandleTypeDef *hssi)
{
    return 0;
}

__attribute__((__unused__))
uint8_t HAL_SSI_RX_DMA_Handshake_Get(struct __SSI_HandleTypeDef *hssi)
{
    return 0;
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
