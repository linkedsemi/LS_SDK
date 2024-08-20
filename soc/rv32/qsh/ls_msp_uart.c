#include "ls_msp_uart.h"
#include "ls_hal_uart.h"
#include "ls_hal_dwuart.h"
#include "field_manipulate.h"
#include "exception_isr.h"
#include "reg_sysc_per.h"
#include "dmac_config.h"
#include "core_rv32.h"
#include "sys_stat.h"
#include "ls_dbg.h"
#include "qsh.h"

#if defined(BOOT_ROM)
static UART_HandleTypeDef *UART_inst_env[1];
void UART1_Handler(void)
{
    HAL_UARTx_IRQHandler( UART_inst_env[0]);
}

void HAL_UART_MSP_Init(UART_HandleTypeDef *inst)
{
    switch((uint32_t)inst->UARTX)
    {
    case (uint32_t)UART1:
        SYSC_PER->PD_PER_SRST1 = SYSC_PER_SRST_CLR_UART1_N_MASK;
        SYSC_PER->PD_PER_SRST1 = SYSC_PER_SRST_SET_UART1_N_MASK;
        rv_set_int_isr(UART1_IRQn,UART1_Handler);
        UART_inst_env[0] = inst;
        csi_vic_clear_pending_irq(UART1_IRQn);
        csi_vic_enable_irq(UART1_IRQn);
        SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_SET_UART1_MASK;
    break;
    default:
    break;
    }
}
#else
static UART_HandleTypeDef *UART_inst_env[2];
static DWUART_HandleTypeDef *DWUART_inst_env[4];

void UART1_Handler(void)
{
    HAL_UARTx_IRQHandler( UART_inst_env[0]);
}

void UART2_Handler(void)
{
    HAL_UARTx_IRQHandler( UART_inst_env[1]);
}

void UART3_Handler(void)
{
    HAL_DWUARTx_IRQHandler( DWUART_inst_env[0]);
}

void DWUART1_Handler(void)
{
    HAL_DWUARTx_IRQHandler( DWUART_inst_env[1]);
}

void DWUART2_Handler(void)
{
    HAL_DWUARTx_IRQHandler( DWUART_inst_env[2]);
}

void HAL_UART_MSP_Init(UART_HandleTypeDef *inst)
{
    switch((uint32_t)inst->UARTX)
    {
    case (uint32_t)UART1:
        SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_CLR_UART1_MASK;
        SYSC_PER->PD_PER_SRST1 = SYSC_PER_SRST_CLR_UART1_N_MASK;
        SYSC_PER->PD_PER_SRST1 = SYSC_PER_SRST_SET_UART1_N_MASK;
        SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_SET_UART1_MASK;
        rv_set_int_isr(BMC_UART1_IRQn,UART1_Handler);
        UART_inst_env[0] = inst;
        csi_vic_clear_pending_irq(BMC_UART1_IRQn);
        csi_vic_enable_irq(BMC_UART1_IRQn);
        SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_SET_UART1_MASK;
    break;
   case (uint32_t)UART2:
        SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_CLR_UART2_MASK;
        SYSC_PER->PD_PER_SRST1 = SYSC_PER_SRST_CLR_UART2_N_MASK;
        SYSC_PER->PD_PER_SRST1 = SYSC_PER_SRST_SET_UART2_N_MASK;
        SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_SET_UART2_MASK;
        rv_set_int_isr(BMC_UART2_IRQn,UART2_Handler);
        UART_inst_env[1] = inst;
        csi_vic_clear_pending_irq(BMC_UART2_IRQn);
        csi_vic_enable_irq(BMC_UART2_IRQn);
        SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_SET_UART2_MASK;
    break;
    }
}

void HAL_UART_MSP_DeInit(UART_HandleTypeDef *inst)
{
    switch((uint32_t)inst->UARTX)
    {
    case (uint32_t)UART1:
        REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1, SYSC_PER_CLKG_CLR_UART1, 1);
        csi_vic_disable_irq(BMC_UART1_IRQn);
    break;
    case (uint32_t)UART2:
        REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1, SYSC_PER_CLKG_CLR_UART2, 1);
        csi_vic_disable_irq(BMC_UART2_IRQn);
    break;
    }
}

void HAL_DWUART_MSP_Init(DWUART_HandleTypeDef *inst)
{
    switch ((uint32_t)inst->DWUARTX)
    {
    // case (uint32_t)DWUART1:
    //     SYSC_PER->PD_PER_SRST1 = SYSC_PER_SRST_CLR_DWUART1_N_MASK;
    //     SYSC_PER->PD_PER_SRST1 = SYSC_PER_SRST_SET_DWUART1_N_MASK;
    //     rv_set_int_isr(BMC_DWUART1_IRQn, DWUART1_Handler);
    //     DWUART_inst_env[0] = inst;
    //     csi_vic_clear_pending_irq(BMC_DWUART1_IRQn);
    //     csi_vic_enable_irq(BMC_DWUART1_IRQn);
    //     SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_SET_DWUART1_MASK;
    // break;
    // case (uint32_t)DWUART2:
    //     SYSC_PER->PD_PER_SRST1 = SYSC_PER_SRST_CLR_DWUART2_N_MASK;
    //     SYSC_PER->PD_PER_SRST1 = SYSC_PER_SRST_SET_DWUART2_N_MASK;
    //     rv_set_int_isr(DWUART2_IRQn, DWUART2_Handler);
    //     DWUART_inst_env[1] = inst;
    //     csi_vic_clear_pending_irq(DWUART2_IRQn);
    //     csi_vic_enable_irq(DWUART2_IRQn);
    //     SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_SET_DWUART2_MASK;
    // break;
    }
}

void HAL_DWUART_MSP_DeInit(DWUART_HandleTypeDef *inst)
{
    switch ((uint32_t)inst->DWUARTX)
    {
    // case (uint32_t)DWUART1:
    //     REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1, SYSC_PER_CLKG_CLR_DWUART1, 1);
    //     csi_vic_disable_irq(BMC_DWUART1_IRQn);
    //     break;
    // case (uint32_t)DWUART2:
    //     REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1, SYSC_PER_CLKG_CLR_DWUART2, 1);
    //     csi_vic_disable_irq(DWUART2_IRQn);
    //     break;
    }
}

#endif

void HAL_UART_MSP_Busy_Set(UART_HandleTypeDef *inst)
{
    switch ((uint32_t)inst->UARTX)
    {
    case (uint32_t)UART1:
        uart1_status_set(true);
    break;
    case (uint32_t)UART2:
        uart2_status_set(true);
    break;
    // case (uint32_t)UART3:
    //     uart3_status_set(true);
    // break;
    }
}

void HAL_UART_MSP_Idle_Set(UART_HandleTypeDef *inst)
{
    switch ((uint32_t)inst->UARTX)
    {
    case (uint32_t)UART1:
        uart1_status_set(false);
    break;
    case (uint32_t)UART2:
        uart2_status_set(false);
    break;
    // case (uint32_t)UART3:
    //     uart3_status_set(false);
    // break;
    }
}

void HAL_DWUART_MSP_Busy_Set(DWUART_HandleTypeDef *inst)
{
    switch ((uint32_t)inst->DWUARTX)
    {
    case (uint32_t)DWUART1:
        dwuart1_status_set(true);
        break;
    case (uint32_t)DWUART2:
        dwuart2_status_set(true);
        break;
    }
}

void HAL_DWUART_MSP_Idle_Set(DWUART_HandleTypeDef *inst)
{
    switch ((uint32_t)inst->DWUARTX)
    {
    case (uint32_t)DWUART1:
        dwuart1_status_set(false);
        break;
    case (uint32_t)DWUART2:
        dwuart2_status_set(false);
        break;
    }
}

uint8_t HAL_UART_TX_DMA_Handshake_Get(UART_HandleTypeDef *inst)
{
    uint8_t handshake = 0;
    switch((uint32_t)inst->UARTX)
    {
    case (uint32_t)UART1:
        handshake = UART1_TX;
    break;
    case (uint32_t)UART2:
        handshake = UART2_TX;
    break;
    // case (uint32_t)UART3:
    //     handshake = UART3_TX;
    // break;
    default:
        LS_ASSERT(0);
    }
    return handshake;
}

uint8_t HAL_UART_RX_DMA_Handshake_Get(UART_HandleTypeDef *inst)
{
    uint8_t handshake = 0;
    switch((uint32_t)inst->UARTX)
    {
    case (uint32_t)UART1:
        handshake = UART1_RX;
    break;
    case (uint32_t)UART2:
        handshake = UART2_RX;
    break;
    // case (uint32_t)UART3:
    //     handshake = UART3_RX;
    // break;
    default:
        LS_ASSERT(0);
    }
    return handshake;
}

uint8_t HAL_DWUART_TX_DMA_Handshake_Get(DWUART_HandleTypeDef *inst)
{
    uint8_t handshake = 0;
    switch((uint32_t)inst->DWUARTX)
    {
    case (uint32_t)DWUART1:
        handshake = DWUART1_TX;
    break;
    case (uint32_t)DWUART2:
        handshake = DWUART2_TX;
    break;
    default:
        LS_ASSERT(0);
    }
    return handshake;
}

uint8_t HAL_DWUART_RX_DMA_Handshake_Get(DWUART_HandleTypeDef *inst)
{
    uint8_t handshake = 0;
    switch((uint32_t)inst->DWUARTX)
    {
    case (uint32_t)DWUART1:
        handshake = DWUART1_RX;
    break;
    case (uint32_t)DWUART2:
        handshake = DWUART2_RX;
    break;
    default:
        LS_ASSERT(0);
    }
    return handshake;
}

__attribute__((weak)) void LL_UART1_Handler() {}

// void LL_UART1_MSP_Init(void)
// {
//     rv_set_int_isr(UART1_IRQn, LL_UART1_Handler);
//     REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1, SYSC_PER_CLKG_SET_UART1, 1);
// }

// void LL_UART1_MSP_DeInit(void)
// {
//     REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1, SYSC_PER_CLKG_CLR_UART1, 1);
// }

__attribute__((weak)) void LL_UART2_Handler() {}

void LL_UART2_MSP_Init(void)
{
    rv_set_int_isr(BMC_UART2_IRQn, LL_UART2_Handler);
    SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_SET_UART2_MASK;
}

// void LL_UART2_MSP_DeInit(void)
// {
//     REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1, SYSC_PER_CLKG_CLR_UART2, 1);
// }

// __attribute__((weak)) void LL_UART3_Handler() {}

// void LL_UART3_MSP_Init(void)
// {
//     rv_set_int_isr(UART3_IRQn, LL_UART3_Handler);
//     REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1, SYSC_PER_CLKG_SET_UART3, 1);
// }

// void LL_UART3_MSP_DeInit(void)
// {
//     REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1, SYSC_PER_CLKG_CLR_UART3, 1);
// }

// __attribute__((weak)) void LL_DWUART1_Handler() {}

// void LL_DWUART1_MSP_Init(void)
// {
//     rv_set_int_isr(BMC_DWUART1_IRQn, LL_DWUART1_Handler);
//     REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1, SYSC_PER_CLKG_SET_DWUART1, 1);
// }

// void LL_DWUART1_MSP_DeInit(void)
// {
//     REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1, SYSC_PER_CLKG_CLR_DWUART1, 1);
// }

// __attribute__((weak)) void LL_DWUART2_Handler() {}

// void LL_DWUART2_MSP_Init(void)
// {
//     rv_set_int_isr(DWUART2_IRQn, LL_DWUART2_Handler);
//     REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1, SYSC_PER_CLKG_SET_DWUART2, 1);
// }

// void LL_DWUART2_MSP_DeInit(void)
// {
//     REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1, SYSC_PER_CLKG_CLR_DWUART2, 1);
// }