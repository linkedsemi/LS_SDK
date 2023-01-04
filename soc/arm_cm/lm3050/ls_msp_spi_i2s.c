#include "ls_msp_spi_i2s.h"
#include "field_manipulate.h"
#include "ls_hal_spi_i2s.h"
#include "lm3050.h"
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
        SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_CLR_SPI2_MASK;
        SYSC_PER->PD_PER_SRST1 = SYSC_PER_SRST_CLR_SPI2_N_MASK;
        SYSC_PER->PD_PER_SRST1 = SYSC_PER_SRST_SET_SPI2_N_MASK;
        SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_SET_SPI2_MASK;
        arm_cm_set_int_isr(SPI2_IRQn, SPI2_Handler);
        spi_inst_env[0] = inst;
        __NVIC_ClearPendingIRQ(SPI2_IRQn);
        __NVIC_EnableIRQ(SPI2_IRQn);
        break;
    case (uint32_t)SPI3:
        SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_CLR_SPI3_MASK;
        SYSC_PER->PD_PER_SRST1 = SYSC_PER_SRST_CLR_SPI3_N_MASK;
        SYSC_PER->PD_PER_SRST1 = SYSC_PER_SRST_SET_SPI3_N_MASK;
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
    uint8_t handshake = 0;
    switch ((uint32_t)hspi->Instance)
    {
    case (uint32_t)SPI2:
        handshake = CH_SPI2_TX;
        break;
    case (uint32_t)SPI3:
        handshake = CH_SPI3_TX;
        break;
    default :
       LS_ASSERT(0);
    }
    return handshake;
}

uint8_t HAL_SPI_RX_DMA_Handshake_Get(SPI_HandleTypeDef *hspi)
{
    uint8_t handshake = 0;
    switch ((uint32_t)hspi->Instance)
    {
    case (uint32_t)SPI2:
        handshake = CH_SPI2_RX ;
        break;
    case (uint32_t)SPI3:
        handshake = CH_SPI3_RX;
        break;
    default:
        LS_ASSERT(0);
    }
    return handshake;
}

uint8_t HAL_I2S_TX_DMA_Handshake_Get(I2S_HandleTypeDef *hi2s)
{
    uint8_t handshake = 0;
    switch ((uint32_t)hi2s->Instance)
    {
    case (uint32_t)SPI2:
        handshake = CH_SPI2_TX;
        break;
    case (uint32_t)SPI3:
        handshake = CH_SPI3_TX;
        break;
    default :
       LS_ASSERT(0);
    }
    return handshake;
}

uint8_t HAL_I2S_RX_DMA_Handshake_Get(I2S_HandleTypeDef *hi2s)
{
    uint8_t handshake = 0;
    switch ((uint32_t)hi2s->Instance)
    {
    case (uint32_t)SPI2:
        handshake = CH_SPI2_RX ;
        break;
    case (uint32_t)SPI3:
        handshake = CH_SPI3_RX;
        break;
    default:
        LS_ASSERT(0);
    }
    return handshake;
}

static I2S_HandleTypeDef *i2s_inst_env[2];

void I2S2_Handler(void)
{
    HAL_I2S_IRQHandler(i2s_inst_env[0]);
}

void I2S3_Handler(void)
{
    HAL_I2S_IRQHandler(i2s_inst_env[1]);
}

void HAL_I2S_MSP_Init(I2S_HandleTypeDef *inst)
{
    switch ((uint32_t)inst->Instance)
    {
    case (uint32_t)SPI2:
        SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_SET_SPI2_MASK;
        arm_cm_set_int_isr(SPI2_IRQn, I2S2_Handler);
        i2s_inst_env[0] = inst;
        __NVIC_ClearPendingIRQ(SPI2_IRQn);
        __NVIC_EnableIRQ(SPI2_IRQn);
        break;
    case (uint32_t)SPI3:
        SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_SET_SPI3_MASK;
        arm_cm_set_int_isr(SPI3_IRQn, I2S3_Handler);
        i2s_inst_env[1] = inst;
        __NVIC_ClearPendingIRQ(SPI3_IRQn);
        __NVIC_EnableIRQ(SPI3_IRQn);
        break;
    }
}

void HAL_I2S_MSP_DeInit(I2S_HandleTypeDef *inst)
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

static void i2s_status_set(I2S_HandleTypeDef *inst, bool status)
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

void HAL_I2S_MSP_Busy_Set(I2S_HandleTypeDef *inst)
{
    i2s_status_set(inst, 1);
}

void HAL_I2S_MSP_Idle_Set(I2S_HandleTypeDef *inst)
{
    i2s_status_set(inst, 0);
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