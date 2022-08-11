#include "ls_msp_uart.h"
#include "reg_rcc.h"
#include "field_manipulate.h"
#include "ls_hal_uart.h"
#include "le501x.h"
#include "HAL_def.h"
#include "sys_stat.h"
#include "platform.h"
#include "dmac_config.h"
#include "ls_msp_dmac.h"
#include <stddef.h>
static void *uart_inst_env[3];

void HAL_UART1_Handler(void)
{
    HAL_UARTx_IRQHandler( uart_inst_env[0]);
}

void HAL_UART2_Handler(void)
{
    HAL_UARTx_IRQHandler( uart_inst_env[1]);
}

void HAL_UART3_Handler(void)
{
    HAL_UARTx_IRQHandler( uart_inst_env[2]);
}

static void uart1_msp_init(void *inst,void (*handler)())
{
    uart_inst_env[0] = inst;
    arm_cm_set_int_isr(UART1_IRQn,handler);
    REG_FIELD_WR(RCC->APB2RST, RCC_UART1, 1);
    REG_FIELD_WR(RCC->APB2RST, RCC_UART1, 0);
    __NVIC_ClearPendingIRQ(UART1_IRQn);
    __NVIC_EnableIRQ(UART1_IRQn);
    REG_FIELD_WR(RCC->APB2EN, RCC_UART1, 1);
}

static void uart2_msp_init(void *inst,void (*handler)())
{
    uart_inst_env[1] = inst;
    arm_cm_set_int_isr(UART2_IRQn,handler);
    REG_FIELD_WR(RCC->APB1RST, RCC_UART2, 1);
    REG_FIELD_WR(RCC->APB1RST, RCC_UART2, 0);
    __NVIC_ClearPendingIRQ(UART2_IRQn);
    __NVIC_EnableIRQ(UART2_IRQn);
    REG_FIELD_WR(RCC->APB1EN, RCC_UART2, 1);
}

static void uart3_msp_init(void *inst,void (*handler)())
{
    uart_inst_env[2] = inst;
    arm_cm_set_int_isr(UART3_IRQn,handler);
    REG_FIELD_WR(RCC->APB1RST, RCC_UART3, 1);
    REG_FIELD_WR(RCC->APB1RST, RCC_UART3, 0);
    __NVIC_ClearPendingIRQ(UART3_IRQn);
    __NVIC_EnableIRQ(UART3_IRQn);
    REG_FIELD_WR(RCC->APB1EN, RCC_UART3, 1);
}

__attribute__((weak)) void csi_uart_isr(void *inst){}

void CSI_UART1_Handler()
{
    csi_uart_isr(uart_inst_env[0]);
}

void CSI_UART2_Handler()
{
    csi_uart_isr(uart_inst_env[1]);
}

void CSI_UART3_Handler()
{
    csi_uart_isr(uart_inst_env[2]);
}

uint32_t CSI_UART_MSP_Init(void *inst,uint32_t idx)
{
    uint32_t reg_base = 0;
    switch(idx)
    {
    case 0:
        uart1_msp_init(inst,CSI_UART1_Handler);
        reg_base = UART1_BASE_ADDR;
    break;
    case 1:
        uart2_msp_init(inst,CSI_UART2_Handler);
        reg_base = UART2_BASE_ADDR;
    break;
    case 2:
        uart3_msp_init(inst,CSI_UART3_Handler);
        reg_base = UART3_BASE_ADDR;
    break;
    }
    return reg_base;
}

static void uart1_msp_deinit()
{
    REG_FIELD_WR(RCC->APB2EN, RCC_UART1, 0);
    __NVIC_DisableIRQ(UART1_IRQn);
}

static void uart2_msp_deinit()
{
    REG_FIELD_WR(RCC->APB1EN, RCC_UART2, 0);
    __NVIC_DisableIRQ(UART2_IRQn);
}

static void uart3_msp_deinit()
{
    REG_FIELD_WR(RCC->APB1EN, RCC_UART3, 0);
    __NVIC_DisableIRQ(UART3_IRQn);
}

void CSI_UART_MSP_DeInit(uint32_t idx)
{
    switch(idx)
    {
    case 0:
        uart1_msp_deinit();
    break;
    case 1:
        uart2_msp_deinit();
    break;
    case 2:
        uart3_msp_deinit();
    break;
    }
}

void HAL_UART_MSP_Init(UART_HandleTypeDef *inst)
{
    switch((uint32_t)inst->UARTX)
    {
    case (uint32_t)UART1:
        uart1_msp_init(inst,HAL_UART1_Handler);
    break;
    case (uint32_t)UART2:
        uart2_msp_init(inst,HAL_UART2_Handler);
    break;
    case (uint32_t)UART3:
        uart3_msp_init(inst,HAL_UART3_Handler);
    break;
    }
}

void HAL_UART_MSP_DeInit(UART_HandleTypeDef *inst)
{
    switch((uint32_t)inst->UARTX)
    {
    case (uint32_t)UART1:
        uart1_msp_deinit();
    break;
    case (uint32_t)UART2:
        uart2_msp_deinit();
    break;
    case (uint32_t)UART3:
        uart3_msp_deinit();
    break;
    }
}

static void uart_status_set(UART_HandleTypeDef *inst,uint8_t status)
{
    switch((uint32_t)inst->UARTX)
    {
    case (uint32_t)UART1:
        uart1_status_set(status);
    break;
    case (uint32_t)UART2:
        uart2_status_set(status);
    break;
    case (uint32_t)UART3:
        uart3_status_set(status);
    break;
    }
}

void HAL_UART_MSP_Busy_Set(UART_HandleTypeDef *inst)
{
    uart_status_set(inst,1);
}

void HAL_UART_MSP_Idle_Set(UART_HandleTypeDef *inst)
{
    uart_status_set(inst,0);
}

uint8_t HAL_UART_TX_DMA_Handshake_Get(UART_HandleTypeDef *inst)
{
    uint8_t handshake = CH_NONE;
    switch((uint32_t)inst->UARTX)
    {
    case (uint32_t)UART1:
        handshake = CH_UART1_TX;
    break;
    case (uint32_t)UART2:
        handshake = CH_UART2_TX;
    break;
    case (uint32_t)UART3:
        handshake = CH_UART3_TX;
    break;
    }
    return handshake;
}

uint8_t HAL_UART_RX_DMA_Handshake_Get(UART_HandleTypeDef *inst)
{
    uint8_t handshake = CH_NONE;
    switch((uint32_t)inst->UARTX)
    {
    case (uint32_t)UART1:
        handshake = CH_UART1_RX;
    break;
    case (uint32_t)UART2:
        handshake = CH_UART2_RX;
    break;
    case (uint32_t)UART3:
        handshake = CH_UART3_RX;
    break;
    }
    return handshake;
}

__attribute__((weak)) void LL_UART1_Handler(){}

void LL_UART1_MSP_Init(void)
{
    arm_cm_set_int_isr(UART1_IRQn,LL_UART1_Handler);
    REG_FIELD_WR(RCC->APB2RST, RCC_UART1, 1);
    REG_FIELD_WR(RCC->APB2RST, RCC_UART1, 0);

    REG_FIELD_WR(RCC->APB2EN, RCC_UART1, 1);
}

void LL_UART1_MSP_DeInit(void)
{
    REG_FIELD_WR(RCC->APB2EN, RCC_UART1, 0);
}

__attribute__((weak)) void LL_UART2_Handler(){}

void LL_UART2_MSP_Init(void)
{
    arm_cm_set_int_isr(UART2_IRQn,LL_UART2_Handler);
    REG_FIELD_WR(RCC->APB1RST, RCC_UART2, 1);
    REG_FIELD_WR(RCC->APB1RST, RCC_UART2, 0);
    REG_FIELD_WR(RCC->APB1EN, RCC_UART2, 1);
}

void LL_UART2_MSP_DeInit(void)
{
    REG_FIELD_WR(RCC->APB1EN, RCC_UART2, 0);
}

__attribute__((weak)) void LL_UART3_Handler(){}

void LL_UART3_MSP_Init(void)
{
    arm_cm_set_int_isr(UART2_IRQn,LL_UART3_Handler);
    REG_FIELD_WR(RCC->APB1RST, RCC_UART3, 1);
    REG_FIELD_WR(RCC->APB1RST, RCC_UART3, 0);
    REG_FIELD_WR(RCC->APB1EN, RCC_UART3, 1);
}

void LL_UART3_MSP_DeInit(void)
{
    REG_FIELD_WR(RCC->APB1EN, RCC_UART3, 0);
}
