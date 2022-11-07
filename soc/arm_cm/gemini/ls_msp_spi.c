#include "ls_msp_spi.h"
#include "field_manipulate.h"
#include "ls_hal_spi.h"
#include "gemini.h"
#include "HAL_def.h"
#include "platform.h"
#include <stddef.h>
#include "sys_stat.h"
#include "reg_sysc_per_type.h"
#include "dmac_config.h"

static SPI_HandleTypeDef *spi_inst_env[2];

void SPI2_Handler(void)
{
    HAL_SPI_IRQHandler(spi_inst_env[0]);
}

void SPI3_Handler(void)
{
    HAL_SPI_IRQHandler(spi_inst_env[1]);
}

void HAL_SPI_MSP_Init(SPI_HandleTypeDef *inst)
{
    switch ((uint32_t)inst->Instance)
    {
    case (uint32_t)SPI2:
        SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_SET_SPI2_MASK;
        arm_cm_set_int_isr(SPI2_IRQn, SPI2_Handler);
        spi_inst_env[0] = inst;
        __NVIC_ClearPendingIRQ(SPI2_IRQn);
        __NVIC_EnableIRQ(SPI2_IRQn);
        break;
    case (uint32_t)SPI3:
        SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_SET_SPI3_MASK;
        arm_cm_set_int_isr(SPI3_IRQn, SPI3_Handler);
        spi_inst_env[1] = inst;
        __NVIC_ClearPendingIRQ(SPI3_IRQn);
        __NVIC_EnableIRQ(SPI3_IRQn);
        break;
    }
}

void HAL_SPI_MSP_DeInit(SPI_HandleTypeDef *inst)
{
    switch ((uint32_t)inst->Instance)
    {
    case (uint32_t)SPI2:
        SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_CLR_SPI2_MASK;
        __NVIC_DisableIRQ(SPI2_IRQn);
        break;
    case (uint32_t)SPI3:
        SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_CLR_SPI3_MASK;
        __NVIC_DisableIRQ(SPI3_IRQn);
        break;
    }
}

static void spi_status_set(SPI_HandleTypeDef *inst, bool status)
{
    switch ((uint32_t)inst->Instance)
    {
    case (uint32_t)SPI2:
        spi2_status_set(status);
        break;
    case (uint32_t)SPI3:
        spi3_status_set(status);
        break;
    }
}

void HAL_SPI_MSP_Busy_Set(SPI_HandleTypeDef *inst)
{
    spi_status_set(inst, 1);
}

void HAL_SPI_MSP_Idle_Set(SPI_HandleTypeDef *inst)
{
    spi_status_set(inst, 0);
}

uint8_t HAL_SPI_TX_DMA_Handshake_Get(SPI_HandleTypeDef *hspi)
{
    switch ((uint32_t)hspi->Instance)
    {
    case (uint32_t)SPI2:
        return CH_SPI2_TX;
        break;
    case (uint32_t)SPI3:
        return CH_SPI3_TX;
        break;
    }
}

uint8_t HAL_SPI_RX_DMA_Handshake_Get(SPI_HandleTypeDef *hspi)
{
    switch ((uint32_t)hspi->Instance)
    {
    case (uint32_t)SPI2:
        return CH_SPI2_RX;
        break;
    case (uint32_t)SPI3:
        return CH_SPI3_RX;
        break;
    }
}

__attribute__((weak)) void LL_SPI2_IRQHandler(){}
void LL_SPI2_MSP_Init(void)
{
    SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_SET_SPI2_MASK;
    arm_cm_set_int_isr(SPI2_IRQn, LL_SPI2_IRQHandler);
}

void LL_SPI2_MSP_DeInit(void)
{
    SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_CLR_SPI2_MASK;

}

__attribute__((weak)) void LL_SPI3_IRQHandler(){}
void LL_SPI3_MSP_Init(void)
{
    SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_SET_SPI3_MASK;
    arm_cm_set_int_isr(SPI3_IRQn, LL_SPI3_IRQHandler);
}

void LL_SPI_MSP_DeInit(void)
{
    SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_CLR_SPI3_MASK;
}