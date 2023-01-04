#include "ls_msp_i2c.h"
#include "field_manipulate.h"
#include "lm3050.h"
#include "HAL_def.h"
#include "platform.h"
#include "reg_sysc_per_type.h"
#include "sys_stat.h"
#include "ls_hal_i2c.h"
#include <stddef.h>
#include "dmac_config.h"

static I2C_HandleTypeDef *i2c_inst_env[3];

void I2C1_Handler(void)
{
    HAL_I2C_IRQHandler(i2c_inst_env[0]);
}

void I2C2_Handler(void)
{
    HAL_I2C_IRQHandler(i2c_inst_env[1]);
}

void I2C3_Handler(void)
{
    HAL_I2C_IRQHandler(i2c_inst_env[2]);
}

void HAL_I2C_MSP_Init(I2C_HandleTypeDef *inst)
{
    switch ((uint32_t)inst->Instance)
    {
    case (uint32_t)I2C1:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_I2C1_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_CLR_I2C1_N_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_SET_I2C1_N_MASK;       
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_SET_I2C1_MASK;
        arm_cm_set_int_isr(I2C1_IRQn, I2C1_Handler);
        i2c_inst_env[0] = inst;
        __NVIC_ClearPendingIRQ(I2C1_IRQn);
        __NVIC_EnableIRQ(I2C1_IRQn);
        break;
    case (uint32_t)I2C2:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_I2C2_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_CLR_I2C2_N_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_SET_I2C2_N_MASK;       
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_SET_I2C2_MASK;
        arm_cm_set_int_isr(I2C2_IRQn, I2C2_Handler);
        i2c_inst_env[1] = inst;
        __NVIC_ClearPendingIRQ(I2C2_IRQn);
        __NVIC_EnableIRQ(I2C2_IRQn);

        break;
    case (uint32_t)I2C3:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_I2C3_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_CLR_I2C3_N_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_SET_I2C3_N_MASK;        
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_SET_I2C3_MASK;
        arm_cm_set_int_isr(I2C3_IRQn, I2C3_Handler);
        i2c_inst_env[2] = inst;
        __NVIC_ClearPendingIRQ(I2C3_IRQn);
        __NVIC_EnableIRQ(I2C3_IRQn);

        break;
    }
}

void HAL_I2C_MSP_DeInit(I2C_HandleTypeDef *inst)
{
    switch ((uint32_t)inst->Instance)
    {
    case (uint32_t)I2C1:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_I2C1_MASK;
        __NVIC_DisableIRQ(I2C1_IRQn);
        break;
    case (uint32_t)I2C2:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_I2C2_MASK;
        __NVIC_DisableIRQ(I2C2_IRQn);
        break;
    case (uint32_t)I2C3:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_I2C3_MASK;
        __NVIC_DisableIRQ(I2C3_IRQn);
        break;
    }
}

static void i2c_status_set(I2C_HandleTypeDef *inst, bool status)
{
    switch ((uint32_t)inst->Instance)
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
    }
}

void HAL_I2C_MSP_Busy_Set(I2C_HandleTypeDef *inst)
{
    i2c_status_set(inst, true);
}

void HAL_I2C_MSP_Idle_Set(I2C_HandleTypeDef *inst)
{
    i2c_status_set(inst, false);
}

uint8_t HAL_I2C_TX_DMA_Handshake_Get(I2C_HandleTypeDef *inst)
{
    uint8_t handshake = 0;
    switch ((uint32_t)inst->Instance)
    {
    case (uint32_t)I2C1:
        handshake = CH_I2C1_TX;
    break;
    case (uint32_t)I2C2:
        handshake = CH_I2C2_TX;
    break;
    case (uint32_t)I2C3:
        handshake = CH_I2C3_TX;
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
        handshake = CH_I2C1_RX;
    break;
    case (uint32_t)I2C2:
        handshake = CH_I2C2_RX;
    break;
    case (uint32_t)I2C3:
        handshake = CH_I2C3_RX;
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
    arm_cm_set_int_isr(I2C1_IRQn, LL_I2C1_IRQHandler);
}

void LL_I2C1_MSP_DeInit(void)
{
    SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_I2C1_MASK;
}

__attribute__((weak)) void LL_I2C2_IRQHandler(void) {}

void LL_I2C2_MSP_Init(void)
{
    SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_SET_I2C2_MASK;
    arm_cm_set_int_isr(I2C2_IRQn, LL_I2C2_IRQHandler);
}

void LL_I2C2_MSP_DeInit(void)
{
    SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_I2C2_MASK;
}


// __attribute__((weak)) void LL_I2C3_IRQHandler(void) {}

// void LL_I2C3_MSP_Init(void)
// {
//     arm_cm_set_int_isr(I2C3_IRQn, LL_I2C3_IRQHandler);
//     REG_FIELD_WR(RCC->APB1RST, RCC_I2C3, 1);
//     REG_FIELD_WR(RCC->APB1RST, RCC_I2C3, 0);
//     REG_FIELD_WR(RCC->APB1EN, RCC_I2C3, 1);
// }

// void LL_I2C3_MSP_DeInit(void)
// {
//         REG_FIELD_WR(SYSC_PER->PD_PER_CLKG0, SYSC_PER_CLKG_CLR_I2C3, 1);
// }