#include "ls_msp_i2c.h"
#include "reg_rcc.h"
#include "field_manipulate.h"
#include "ls_hal_i2c.h"
#include "le501x.h"
#include "HAL_def.h"
#include "sys_stat.h"
#include "platform.h"
#include "dmac_config.h"
#include "ls_msp_dmac.h"
#include <stddef.h>

static void *i2c_inst_env[2];

void HAL_I2C1_Handler(void)
{
    HAL_I2C_IRQHandler( i2c_inst_env[0]);
}

void HAL_I2C2_Handler(void)
{
    HAL_I2C_IRQHandler( i2c_inst_env[1]);
}

static void iic1_msp_init(void *inst,void (*handler)())
{
    i2c_inst_env[0] = inst;
    arm_cm_set_int_isr(I2C1_IRQn, handler);
    REG_FIELD_WR(RCC->APB1RST, RCC_I2C1, 1);
    REG_FIELD_WR(RCC->APB1RST, RCC_I2C1, 0);
    __NVIC_ClearPendingIRQ(I2C1_IRQn);
    __NVIC_EnableIRQ(I2C1_IRQn);
    REG_FIELD_WR(RCC->APB1EN, RCC_I2C1, 1);
}

static void iic2_msp_init(void *inst,void (*handler)())
{
    i2c_inst_env[1] = inst;
    arm_cm_set_int_isr(I2C2_IRQn, handler);
    REG_FIELD_WR(RCC->APB1RST, RCC_I2C2, 1);
    REG_FIELD_WR(RCC->APB1RST, RCC_I2C2, 0);
    __NVIC_ClearPendingIRQ(I2C2_IRQn);
    __NVIC_EnableIRQ(I2C2_IRQn);
    REG_FIELD_WR(RCC->APB1EN, RCC_I2C2, 1);
}

__attribute__((weak)) void csi_iic_isr(void *inst){}

void CSI_IIC1_Handler()
{
    csi_iic_isr(i2c_inst_env[0]);
}

void CSI_IIC2_Handler()
{
    csi_iic_isr(i2c_inst_env[1]);
}

uint32_t CSI_IIC_MSP_Init(void *inst,uint32_t idx)
{
    uint32_t reg_base = 0;
    switch(idx)
    {
    case 0:
        iic1_msp_init(inst,CSI_IIC1_Handler);
        reg_base = I2C1_BASE_ADDR;
        break;
    case 1:
        iic2_msp_init(inst,CSI_IIC2_Handler);
        reg_base = I2C2_BASE_ADDR;
        break;
    }
    return reg_base;
}

void HAL_I2C_MSP_Init(I2C_HandleTypeDef *inst)
{
    switch((uint32_t)inst->Instance)
    {
    case (uint32_t)I2C1:
        iic1_msp_init(inst,HAL_I2C1_Handler);
        break;
    case (uint32_t)I2C2:
        iic2_msp_init(inst,HAL_I2C2_Handler);
        break;
    }
}

static void iic1_msp_deinit(void)
{
    REG_FIELD_WR(RCC->APB1EN, RCC_I2C1, 0);
    __NVIC_DisableIRQ(I2C1_IRQn);
}

static void iic2_msp_deinit(void)
{
    REG_FIELD_WR(RCC->APB1EN, RCC_I2C2, 0);
    __NVIC_DisableIRQ(I2C2_IRQn);
}

void HAL_I2C_MSP_DeInit(I2C_HandleTypeDef *inst)
{
    switch((uint32_t)inst->Instance)
    {
    case (uint32_t)I2C1:
        iic1_msp_deinit();
        break;
    case (uint32_t)I2C2:
        iic2_msp_deinit();
        break;
    }
}

void CSI_IIC_MSP_DeInit(uint32_t idx)
{
    switch(idx)
    {
    case 0:
        iic1_msp_deinit();
        break;
    case 1:
        iic2_msp_deinit();
        break;
    }
}

static void i2c_status_set(I2C_HandleTypeDef *inst, bool status)
{
    switch((uint32_t)inst->Instance)
    {
    case (uint32_t)I2C1:
        i2c1_status_set(status);
        break;
    case (uint32_t)I2C2:
        i2c2_status_set(status);
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
    uint8_t handshake = CH_NONE;
    switch((uint32_t)inst->Instance)
    {
    case (uint32_t)I2C1:
        handshake = CH_I2C1_TX;
        break;
    case (uint32_t)I2C2:
        handshake = CH_I2C2_TX;
        break;
    }
    return handshake;
}

uint8_t HAL_I2C_RX_DMA_Handshake_Get(I2C_HandleTypeDef *inst)
{
    uint8_t handshake = CH_NONE;
    switch((uint32_t)inst->Instance)
    {
    case (uint32_t)I2C1:
        handshake = CH_I2C1_RX;
        break;
    case (uint32_t)I2C2:
        handshake = CH_I2C2_RX;
        break;
    }
    return handshake;
}

__attribute__((weak)) void LL_I2C1_IRQHandler(void) {}


void LL_I2C1_MSP_Init(void)
{
    arm_cm_set_int_isr(I2C1_IRQn, LL_I2C1_IRQHandler);
    REG_FIELD_WR(RCC->APB1RST, RCC_I2C1, 1);
    REG_FIELD_WR(RCC->APB1RST, RCC_I2C1, 0);

    REG_FIELD_WR(RCC->APB1EN, RCC_I2C1, 1);
}

void LL_I2C1_MSP_DeInit(void)
{
    REG_FIELD_WR(RCC->APB1EN, RCC_I2C1, 0);
}

__attribute__((weak)) void LL_I2C2_IRQHandler(void) {}

void LL_I2C2_MSP_Init(void)
{
    arm_cm_set_int_isr(I2C2_IRQn, LL_I2C2_IRQHandler);
    REG_FIELD_WR(RCC->APB1RST, RCC_I2C2, 1);
    REG_FIELD_WR(RCC->APB1RST, RCC_I2C2, 0);
    REG_FIELD_WR(RCC->APB1EN, RCC_I2C2, 1);
}

void LL_I2C2_MSP_DeInit(void)
{
    REG_FIELD_WR(RCC->APB1EN, RCC_I2C2, 0);
}

