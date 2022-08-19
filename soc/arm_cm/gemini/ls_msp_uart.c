#include "ls_msp_uart.h"
#include "field_manipulate.h"
#include "ls_hal_uart.h"
#include "gemini.h"
#include "sys_stat.h"
#include "HAL_def.h"
#include "platform.h"
#include "reg_sysc_per_type.h"

static UART_HandleTypeDef *UART_inst_env[5];

void UART1_Handler(void)
{
    HAL_UARTx_IRQHandler(UART_inst_env[0]);
}

void UART2_Handler(void)
{
    HAL_UARTx_IRQHandler(UART_inst_env[1]);
}

void UART3_Handler(void)
{
    HAL_UARTx_IRQHandler(UART_inst_env[2]);
}

void UART4_Handler(void)
{
    HAL_UARTx_IRQHandler(UART_inst_env[3]);
}

void UART5_Handler(void)
{
    HAL_UARTx_IRQHandler(UART_inst_env[4]);
}

void HAL_UART_MSP_Init(UART_HandleTypeDef *inst)
{
    switch ((uint32_t)inst->UARTX)
    {
    case (uint32_t)UART1:
        REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1, SYSC_PER_CLKG_SET_UART1, 1);
        arm_cm_set_int_isr(UART1_IRQn, UART1_Handler);
        UART_inst_env[0] = inst;
        __NVIC_ClearPendingIRQ(UART1_IRQn);
        __NVIC_EnableIRQ(UART1_IRQn);

        break;
    case (uint32_t)UART2:
        REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1, SYSC_PER_CLKG_SET_UART2, 1);
        arm_cm_set_int_isr(UART2_IRQn, UART2_Handler);
        UART_inst_env[1] = inst;
        __NVIC_ClearPendingIRQ(UART2_IRQn);
        __NVIC_EnableIRQ(UART2_IRQn);

        break;
    case (uint32_t)UART3:
        REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1, SYSC_PER_CLKG_SET_UART3, 1);
        arm_cm_set_int_isr(UART3_IRQn, UART3_Handler);
        UART_inst_env[2] = inst;
        __NVIC_ClearPendingIRQ(UART3_IRQn);
        __NVIC_EnableIRQ(UART3_IRQn);

        break;
    case (uint32_t)UART4:
        REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1, SYSC_PER_CLKG_SET_UART4, 1);
        arm_cm_set_int_isr(UART4_IRQn, UART4_Handler);
        UART_inst_env[3] = inst;
        __NVIC_ClearPendingIRQ(UART3_IRQn);
        __NVIC_EnableIRQ(UART3_IRQn);
        break;
    case (uint32_t)UART5:
        REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1, SYSC_PER_CLKG_SET_UART5, 1);
        arm_cm_set_int_isr(UART5_IRQn, UART5_Handler);
        UART_inst_env[4] = inst;
        __NVIC_ClearPendingIRQ(UART5_IRQn);
        __NVIC_EnableIRQ(UART5_IRQn);
        break;
    }
}

void HAL_UART_MSP_DeInit(UART_HandleTypeDef *inst)
{
    switch ((uint32_t)inst->UARTX)
    {
    case (uint32_t)UART1:
        REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1, SYSC_PER_CLKG_CLR_UART1, 1);
        __NVIC_DisableIRQ(UART1_IRQn);
        break;
    case (uint32_t)UART2:
        REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1, SYSC_PER_CLKG_CLR_UART2, 1);
        __NVIC_DisableIRQ(UART2_IRQn);
        break;
    case (uint32_t)UART3:
        REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1, SYSC_PER_CLKG_CLR_UART3, 1);
        __NVIC_DisableIRQ(UART3_IRQn);
        break;
    case (uint32_t)UART4:
        REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1, SYSC_PER_CLKG_CLR_UART4, 1);
        __NVIC_DisableIRQ(UART4_IRQn);
        break;
    case (uint32_t)UART5:
        REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1, SYSC_PER_CLKG_CLR_UART5, 1);
        __NVIC_DisableIRQ(UART5_IRQn);
        break;
    }
}

static void uart_status_set(UART_HandleTypeDef *inst, uint8_t status)
{
    switch ((uint32_t)inst->UARTX)
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
    case (uint32_t)UART4:
        uart4_status_set(status);
        break;
    case (uint32_t)UART5:
        uart5_status_set(status);
        break;
    }
}

void HAL_UART_MSP_Busy_Set(UART_HandleTypeDef *inst)
{
    uart_status_set(inst, 1);
}

void HAL_UART_MSP_Idle_Set(UART_HandleTypeDef *inst)
{
    uart_status_set(inst, 0);
}

__attribute__((weak)) void LL_UART1_Handler(){}
void LL_UART1_MSP_Init(void)
{
    arm_cm_set_int_isr(UART1_IRQn,LL_UART1_Handler);
    REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1, SYSC_PER_CLKG_SET_UART1, 1);
}

void LL_UART1_MSP_DeInit(void)
{
        REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1, SYSC_PER_CLKG_CLR_UART1, 1);
}

__attribute__((weak)) void LL_UART2_Handler() {}
void LL_UART2_MSP_Init(void)
{
    arm_cm_set_int_isr(UART2_IRQn, LL_UART2_Handler);
    REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1, SYSC_PER_CLKG_SET_UART2, 1);
}

void LL_UART2_MSP_DeInit(void)
{
        REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1, SYSC_PER_CLKG_CLR_UART2, 1);
}

__attribute__((weak)) void LL_UART3_Handler() {}
void LL_UART3_MSP_Init(void)
{
    arm_cm_set_int_isr(UART3_IRQn, LL_UART3_Handler);
    REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1, SYSC_PER_CLKG_SET_UART3, 1);
}

void LL_UART3_MSP_DeInit(void)
{
        REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1, SYSC_PER_CLKG_CLR_UART3, 1);
}

__attribute__((weak)) void LL_UART4_Handler() {}
void LL_UART4_MSP_Init(void)
{
    arm_cm_set_int_isr(UART4_IRQn, LL_UART4_Handler);
    REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1, SYSC_PER_CLKG_SET_UART4, 1);
}

void LL_UART4_MSP_DeInit(void)
{
        REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1, SYSC_PER_CLKG_CLR_UART4, 1);
}

__attribute__((weak)) void LL_UART5_Handler() {}
void LL_UART5_MSP_Init(void)
{
    arm_cm_set_int_isr(UART5_IRQn, LL_UART5_Handler);
    REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1, SYSC_PER_CLKG_SET_UART5, 1);
}

void LL_UART5_MSP_DeInit(void)
{
        REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1, SYSC_PER_CLKG_CLR_UART5, 1);
}
