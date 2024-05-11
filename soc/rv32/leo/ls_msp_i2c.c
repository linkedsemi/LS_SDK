#include "ls_msp_i2c.h"
#include "reg_sysc_per.h"
#include "field_manipulate.h"
#include "ls_hal_i2c.h"
#include "leo.h"
#include "HAL_def.h"
#include "core_rv32.h"
#include "sys_stat.h"
#include "platform.h"
#include "exception_isr.h"
#include <stddef.h>
#include "dmac_config.h"

static void *i2c_inst_env[6];

void I2C1_Handler(void)
{
    HAL_I2C_IRQHandler( i2c_inst_env[0]);
}

void I2C2_Handler(void)
{
    HAL_I2C_IRQHandler( i2c_inst_env[1]);
}

void I2C3_Handler(void)
{
    HAL_I2C_IRQHandler( i2c_inst_env[2]);
}

void I2C4_Handler(void)
{
    HAL_I2C_IRQHandler( i2c_inst_env[3]);
}

void I2C5_Handler(void)
{
    HAL_I2C_IRQHandler( i2c_inst_env[4]);
}

void I2C6_Handler(void)
{
    HAL_I2C_IRQHandler( i2c_inst_env[5]);
}

void HAL_I2C_MSP_Init(I2C_HandleTypeDef *inst)
{
    switch((uint32_t)inst->Instance)
    {
    case (uint32_t)I2C1:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_I2C1_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_CLR_I2C1_N_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_SET_I2C1_N_MASK;
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_SET_I2C1_MASK;
        i2c_inst_env[0] = inst;
        rv_set_int_isr(I2C1_IRQn,I2C1_Handler);
        csi_vic_clear_pending_irq(I2C1_IRQn);
        csi_vic_enable_irq(I2C1_IRQn);
    break;
    case (uint32_t)I2C2:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_I2C2_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_CLR_I2C2_N_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_SET_I2C2_N_MASK;
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_SET_I2C2_MASK;
        i2c_inst_env[1] = inst;
        rv_set_int_isr(I2C2_IRQn,I2C2_Handler);
        csi_vic_clear_pending_irq(I2C2_IRQn);
        csi_vic_enable_irq(I2C2_IRQn);
    break;
    case (uint32_t)I2C3:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_I2C3_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_CLR_I2C3_N_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_SET_I2C3_N_MASK;
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_SET_I2C3_MASK;
        i2c_inst_env[2] = inst;
        rv_set_int_isr(I2C3_IRQn,I2C3_Handler);
        csi_vic_clear_pending_irq(I2C3_IRQn);
        csi_vic_enable_irq(I2C3_IRQn);
    break;
    case (uint32_t)I2C4:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_I2C4_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_CLR_I2C4_N_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_SET_I2C4_N_MASK;
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_SET_I2C4_MASK;
        i2c_inst_env[3] = inst;
        rv_set_int_isr(I2C4_IRQn,I2C4_Handler);
        csi_vic_clear_pending_irq(I2C4_IRQn);
        csi_vic_enable_irq(I2C4_IRQn);
    break;
    case (uint32_t)I2C5:
        SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_CLR_I2C5_MASK;
        SYSC_PER->PD_PER_SRST1 = SYSC_PER_SRST_CLR_I2C5_N_MASK;
        SYSC_PER->PD_PER_SRST1 = SYSC_PER_SRST_SET_I2C5_N_MASK;
        SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_SET_I2C5_MASK;
        i2c_inst_env[4] = inst;
        rv_set_int_isr(I2C5_IRQn,I2C5_Handler);
        csi_vic_clear_pending_irq(I2C5_IRQn);
        csi_vic_enable_irq(I2C5_IRQn);
    break;
    case (uint32_t)I2C6:
        SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_CLR_I2C6_MASK;
        SYSC_PER->PD_PER_SRST1 = SYSC_PER_SRST_CLR_I2C6_N_MASK;
        SYSC_PER->PD_PER_SRST1 = SYSC_PER_SRST_SET_I2C6_N_MASK;
        SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_SET_I2C6_MASK;
        i2c_inst_env[5] = inst;
        rv_set_int_isr(I2C6_IRQn,I2C6_Handler);
        csi_vic_clear_pending_irq(I2C6_IRQn);
        csi_vic_enable_irq(I2C6_IRQn);
    break;
    }
}

void HAL_I2C_MSP_DeInit(I2C_HandleTypeDef *inst)
{
    switch((uint32_t)inst->Instance)
    {
    case (uint32_t)I2C1:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_I2C1_MASK;
        csi_vic_disable_irq(I2C1_IRQn);
    break;
    case (uint32_t)I2C2:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_I2C2_MASK;
        csi_vic_disable_irq(I2C2_IRQn);
    break;
    case (uint32_t)I2C3:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_I2C3_MASK;
        csi_vic_disable_irq(I2C3_IRQn);
    break;
    case (uint32_t)I2C4:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_I2C4_MASK;
        csi_vic_disable_irq(I2C4_IRQn);
    break;
    case (uint32_t)I2C5:
        SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_CLR_I2C5_MASK;
        csi_vic_disable_irq(I2C5_IRQn);
    break;
    case (uint32_t)I2C6:
        SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_CLR_I2C6_MASK;
        csi_vic_disable_irq(I2C6_IRQn);
    break;
    }
}

static void i2c_status_set(I2C_HandleTypeDef *inst,bool status)
{
    switch((uint32_t)inst->Instance)
    {
    case (uint32_t)I2C1:
        i2c1_status_set(status);
    break;
    case (uint32_t)I2C2:
        i2c2_status_set(status);
    break;
    case (uint32_t)I2C3:
        i2c3_status_set(status);
    break;
    case (uint32_t)I2C4:
        i2c4_status_set(status);
    break;
    case (uint32_t)I2C5:
        i2c5_status_set(status);
    break;
    case (uint32_t)I2C6:
        i2c6_status_set(status);
    break;
    }
}

void HAL_I2C_MSP_Busy_Set(I2C_HandleTypeDef *inst)
{
    i2c_status_set(inst,true);
}

void HAL_I2C_MSP_Idle_Set(I2C_HandleTypeDef *inst)
{
    i2c_status_set(inst,false);
}

uint8_t HAL_I2C_TX_DMA_Handshake_Get(I2C_HandleTypeDef *inst)
{
    uint8_t handshake = 0;
    switch ((uint32_t)inst->Instance)
    {
    case (uint32_t)I2C1:
        handshake = I2C1_TX;
    break;
    case (uint32_t)I2C2:
        handshake = I2C2_TX;
    break;
    case (uint32_t)I2C3:
        handshake = I2C3_TX;
    break;
    case (uint32_t)I2C4:
        handshake = I2C4_TX;
    break;
    case (uint32_t)I2C5:
        handshake = I2C5_TX;
    break;
    case (uint32_t)I2C6:
        handshake = I2C6_TX;
    break;
    default:
        LS_ASSERT(0);
    }
    return handshake;
}

uint8_t HAL_I2C_RX_DMA_Handshake_Get(I2C_HandleTypeDef *inst)
{
    uint8_t handshake = 0;
    switch ((uint32_t)inst->Instance)
    {
    case (uint32_t)I2C1:
        handshake = I2C1_RX;
    break;
    case (uint32_t)I2C2:
        handshake = I2C2_RX;
    break;
    case (uint32_t)I2C3:
        handshake = I2C3_RX;
    break;
    case (uint32_t)I2C4:
        handshake = I2C4_RX;
    break;
    case (uint32_t)I2C5:
        handshake = I2C5_RX;
    break;
    case (uint32_t)I2C6:
        handshake = I2C6_RX;
    break;
    default:
        LS_ASSERT(0);
    }
    return handshake;
}

__attribute__((weak)) void LL_I2C1_IRQHandler(void) {}

void LL_I2C1_MSP_Init(void)
{
    SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_SET_I2C1_MASK;
    rv_set_int_isr(I2C1_IRQn, LL_I2C1_IRQHandler);
}

void LL_I2C1_MSP_DeInit(void)
{
    SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_I2C1_MASK;
}

__attribute__((weak)) void LL_I2C2_IRQHandler(void) {}

void LL_I2C2_MSP_Init(void)
{
    SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_SET_I2C2_MASK;
    rv_set_int_isr(I2C2_IRQn, LL_I2C2_IRQHandler);
}

void LL_I2C2_MSP_DeInit(void)
{
    SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_I2C2_MASK;
}

__attribute__((weak)) void LL_I2C3_IRQHandler(void) {}

void LL_I2C3_MSP_Init(void)
{
    SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_SET_I2C3_MASK;
    rv_set_int_isr(I2C3_IRQn, LL_I2C3_IRQHandler);
}

void LL_I2C3_MSP_DeInit(void)
{
    SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_I2C3_MASK;
}

__attribute__((weak)) void LL_I2C4_IRQHandler(void) {}

void LL_I2C4_MSP_Init(void)
{
    SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_SET_I2C4_MASK;
    rv_set_int_isr(I2C4_IRQn, LL_I2C4_IRQHandler);
}

void LL_I2C4_MSP_DeInit(void)
{
    SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_I2C4_MASK;
}

__attribute__((weak)) void LL_I2C5_IRQHandler(void) {}

void LL_I2C5_MSP_Init(void)
{
    SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_SET_I2C5_MASK;
    rv_set_int_isr(I2C5_IRQn, LL_I2C4_IRQHandler);
}

void LL_I2C5_MSP_DeInit(void)
{
    SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_CLR_I2C5_MASK;
}

__attribute__((weak)) void LL_I2C6_IRQHandler(void) {}

void LL_I2C6_MSP_Init(void)
{
    SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_SET_I2C6_MASK;
    rv_set_int_isr(I2C6_IRQn, LL_I2C6_IRQHandler);
}

void LL_I2C6_MSP_DeInit(void)
{
    SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_CLR_I2C6_MASK;
}