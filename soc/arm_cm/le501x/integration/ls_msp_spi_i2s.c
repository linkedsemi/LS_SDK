#include "ls_msp_spi_i2s.h"
#include "reg_rcc.h"
#include "field_manipulate.h"
#include "ls_hal_spi_i2s.h"
#include "le501x.h"
#include "HAL_def.h"
#include "sys_stat.h"
#include "platform.h"
#include "dmac_config.h"
#include "ls_msp_dmac.h"
#include <stddef.h>

static void *spi_inst_env;


void SPI2_Handler(void)
{
    /* code */
    HAL_SPI_IRQHandler(spi_inst_env);   
}
__attribute__((weak)) void csi_spi_isr(void *inst){}

void CSI_SPI_Handler()
{
    csi_spi_isr(spi_inst_env);
}

static void spi_msp_init(void *inst,void (*handler)())
{
    REG_FIELD_WR(RCC->APB1RST, RCC_SPI2, 1);
    REG_FIELD_WR(RCC->APB1RST, RCC_SPI2, 0);
    arm_cm_set_int_isr(SPI2_IRQn,handler);
    spi_inst_env = inst;
    NVIC_ClearPendingIRQ(SPI2_IRQn);
    NVIC_EnableIRQ(SPI2_IRQn);
    REG_FIELD_WR(RCC->APB1EN, RCC_SPI2, 1);
}

void spi_msp_deinit()
{
    REG_FIELD_WR(RCC->APB1EN, RCC_SPI2, 0);
    NVIC_DisableIRQ(SPI2_IRQn);
}

uint32_t CSI_SPI_MSP_Init(void *inst,uint32_t idx)
{
    spi_msp_init(inst,CSI_SPI_Handler);
    return SPI2_BASE_ADDR;
}

void CSI_SPI_MSP_DeInit(uint32_t idx)
{
    spi_msp_deinit();
}

void HAL_SPI_MSP_Init(SPI_HandleTypeDef *inst)
{
    spi_msp_init(inst,SPI2_Handler);
}

void HAL_SPI_MSP_DeInit(SPI_HandleTypeDef *inst)
{
    spi_msp_deinit();
}

static void spi_status_set(SPI_HandleTypeDef *inst,bool status)
{
    switch((uint32_t)inst->Instance)
    {
    case (uint32_t)SPI2:
        spi2_status_set(status);
    break;
    }
}

void HAL_SPI_MSP_Busy_Set(SPI_HandleTypeDef *inst)
{
    spi_status_set(inst,1);
}

void HAL_SPI_MSP_Idle_Set(SPI_HandleTypeDef *inst)
{
    spi_status_set(inst,0);
}


static void *i2s_inst_env;

void I2S2_Handler(void)
{
    HAL_I2S_IRQHandler(i2s_inst_env);   
}
__attribute__((weak)) void csi_i2s_isr(void *inst){}

void CSI_I2S_Handler()
{
    csi_i2s_isr(i2s_inst_env);
}

static void i2s_msp_init(void *inst,void (*handler)())
{
    REG_FIELD_WR(RCC->APB1RST, RCC_SPI2, 1);
    REG_FIELD_WR(RCC->APB1RST, RCC_SPI2, 0);
    arm_cm_set_int_isr(SPI2_IRQn,handler);
    i2s_inst_env = inst;
    NVIC_ClearPendingIRQ(SPI2_IRQn);
    NVIC_EnableIRQ(SPI2_IRQn);
    REG_FIELD_WR(RCC->APB1EN, RCC_SPI2, 1);
}

void i2s_msp_deinit()
{
    REG_FIELD_WR(RCC->APB1EN, RCC_SPI2, 0);
    NVIC_DisableIRQ(SPI2_IRQn);
}

uint32_t CSI_I2S_MSP_Init(void *inst,uint32_t idx)
{
    i2s_msp_init(inst,CSI_I2S_Handler);
    return SPI2_BASE_ADDR;
}

void CSI_I2S_MSP_DeInit(uint32_t idx)
{
    i2s_msp_deinit();
}

void HAL_I2S_MSP_Init(I2S_HandleTypeDef *inst)
{
    i2s_msp_init(inst,I2S2_Handler);
}

void HAL_I2S_MSP_DeInit(I2S_HandleTypeDef *inst)
{
    i2s_msp_deinit();
}

static void i2s_status_set(I2S_HandleTypeDef *inst,bool status)
{
    switch((uint32_t)inst->Instance)
    {
    case (uint32_t)SPI2:
        spi2_status_set(status);
    break;
    }
}

void HAL_I2S_MSP_Busy_Set(I2S_HandleTypeDef *inst)
{
    i2s_status_set(inst,1);
}

void HAL_I2S_MSP_Idle_Set(I2S_HandleTypeDef *inst)
{
    i2s_status_set(inst,0);
}

__attribute__((weak)) void LL_SPI2_IRQHandler(){}
void LL_SPI2_MSP_Init(void)
{
    REG_FIELD_WR(RCC->APB1RST, RCC_SPI2, 1);
    REG_FIELD_WR(RCC->APB1RST, RCC_SPI2, 0);
    arm_cm_set_int_isr(SPI2_IRQn,LL_SPI2_IRQHandler);
    REG_FIELD_WR(RCC->APB1EN, RCC_SPI2, 1);
}

void LL_SPI2_MSP_DeInit(void)
{
    REG_FIELD_WR(RCC->APB1EN, RCC_SPI2, 0);
}
