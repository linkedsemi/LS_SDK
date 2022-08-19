#include "ls_msp_ssi.h"
#include "field_manipulate.h"
#include "platform.h"
#include "gemini.h"
#include "sys_stat.h"
#include "reg_sysc_per_type.h"
#include "ls_hal_ssi.h"
static SSI_HandleTypeDef *ssi_inst_env[1];

static void SSI_Handler()
{
    HAL_SSI_IRQHandler(ssi_inst_env[0]);
}

void HAL_SSI_MSP_Init(SSI_HandleTypeDef *hssi)
{
    REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1, SYSC_PER_CLKG_SET_SPI1, 1);
    arm_cm_set_int_isr(I2C1_IRQn, SSI_Handler);
    ssi_inst_env[0] = hssi;
    __NVIC_ClearPendingIRQ(SPI1_IRQn);
    __NVIC_EnableIRQ(SPI1_IRQn);
}

void HAL_SSI_MSP_DeInit(SSI_HandleTypeDef *hssi)
{
    REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1, SYSC_PER_CLKG_CLR_UART1, 1);
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

__attribute__((weak)) void LL_SSI_IRQHandler(){}
void LL_SSI_MSP_Init(void)
{

    REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1, SYSC_PER_CLKG_SET_SPI1, 1);
    arm_cm_set_int_isr(SPI1_IRQn,LL_SSI_IRQHandler);
}

void LL_SSI_MSP_DeInit(void)
{
    REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1, SYSC_PER_CLKG_CLR_UART1, 1);
}