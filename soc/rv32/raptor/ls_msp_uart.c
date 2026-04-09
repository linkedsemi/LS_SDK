#include "ls_msp_uart.h"
#include "ls_hal_dwuart.h"
#include "field_manipulate.h"
#include "exception_isr.h"
#include "core_rv32.h"
#include "sys_stat.h"
#include "ls_dbg.h"
#include "raptor.h"
#include "reg_cpu0_sys.h"
#include "reg_cpu1_sys.h"

static DWUART_HandleTypeDef *DWUART_inst_env[16];

void DWUART0_Handler(void)
{
    HAL_DWUARTx_IRQHandler(DWUART_inst_env[0]);
}

void DWUART1_Handler(void)
{
    HAL_DWUARTx_IRQHandler(DWUART_inst_env[1]);
}

void DWUART2_Handler(void)
{
    HAL_DWUARTx_IRQHandler(DWUART_inst_env[2]);
}

void DWUART3_Handler(void)
{
    HAL_DWUARTx_IRQHandler(DWUART_inst_env[3]);
}

void DWUART4_Handler(void)
{
    HAL_DWUARTx_IRQHandler(DWUART_inst_env[4]);
}

void DWUART5_Handler(void)
{
    HAL_DWUARTx_IRQHandler(DWUART_inst_env[5]);
}

void DWUART6_Handler(void)
{
    HAL_DWUARTx_IRQHandler(DWUART_inst_env[6]);
}

void DWUART7_Handler(void)
{
    HAL_DWUARTx_IRQHandler(DWUART_inst_env[7]);
}

void DWUART8_Handler(void)
{
    HAL_DWUARTx_IRQHandler(DWUART_inst_env[8]);
}

void DWUART9_Handler(void)
{
    HAL_DWUARTx_IRQHandler(DWUART_inst_env[9]);
}

void DWUART10_Handler(void)
{
    HAL_DWUARTx_IRQHandler(DWUART_inst_env[10]);
}

void DWUART11_Handler(void)
{
    HAL_DWUARTx_IRQHandler(DWUART_inst_env[11]);
}

void DWUART12_Handler(void)
{
    HAL_DWUARTx_IRQHandler(DWUART_inst_env[12]);
}

void DWUART13_Handler(void)
{
    HAL_DWUARTx_IRQHandler(DWUART_inst_env[13]);
}

void DWUART14_Handler(void)
{
    HAL_DWUARTx_IRQHandler(DWUART_inst_env[14]);
}

void DWUART15_Handler(void)
{
    HAL_DWUARTx_IRQHandler(DWUART_inst_env[15]);
}

void HAL_DWUART_MSP_Init(DWUART_HandleTypeDef *inst)
{
    switch((uint32_t)inst->DWUARTX)
    {
    case (uint32_t)DWUART0:
        REG_FIELD_WR(CPU0_SYS_CFG->CPU1_SYS_CFG_REG3, CPU1_SYS_UART0_APB_CLK_CLK_CG0_6, 0x1);
        rv_set_int_isr(CPU_DWUART0_IRQn, DWUART0_Handler);
        csi_vic_clear_pending_irq(CPU_DWUART0_IRQn);
        csi_vic_enable_irq(CPU_DWUART0_IRQn);
        DWUART_inst_env[0] = inst;
    break;
    case (uint32_t)DWUART1:
        REG_FIELD_WR(CPU0_SYS_CFG->CPU1_SYS_CFG_REG3, CPU1_SYS_UART1_APB_CLK_CLK_CG0_7, 0x1);
        rv_set_int_isr(CPU_DWUART1_IRQn, DWUART1_Handler);
        csi_vic_clear_pending_irq(CPU_DWUART1_IRQn);
        csi_vic_enable_irq(CPU_DWUART1_IRQn);
        DWUART_inst_env[1] = inst;
    break;
   case (uint32_t)DWUART2:
        REG_FIELD_WR(CPU0_SYS_CFG->CPU1_SYS_CFG_REG3, CPU1_SYS_UART2_APB_CLK_CLK_CG0_8, 0x1);
        rv_set_int_isr(CPU_DWUART2_IRQn, DWUART2_Handler);
        csi_vic_clear_pending_irq(CPU_DWUART2_IRQn);
        csi_vic_enable_irq(CPU_DWUART2_IRQn);
        DWUART_inst_env[2] = inst;
    break;
   case (uint32_t)DWUART3:
        REG_FIELD_WR(CPU0_SYS_CFG->CPU1_SYS_CFG_REG3, CPU1_SYS_UART3_APB_CLK_CLK_CG0_9, 0x1);
        rv_set_int_isr(CPU_DWUART3_IRQn, DWUART3_Handler);
        csi_vic_clear_pending_irq(CPU_DWUART3_IRQn);
        csi_vic_enable_irq(CPU_DWUART3_IRQn);
        DWUART_inst_env[3] = inst;
    break;
    case (uint32_t)DWUART4:
        REG_FIELD_WR(CPU0_SYS_CFG->CPU1_SYS_CFG_REG3, CPU1_SYS_UART4_APB_CLK_CLK_CG0_10, 0x1);
        rv_set_int_isr(CPU_DWUART4_IRQn, DWUART4_Handler);
        csi_vic_clear_pending_irq(CPU_DWUART4_IRQn);
        csi_vic_enable_irq(CPU_DWUART4_IRQn);
        DWUART_inst_env[4] = inst;
    break;
    case (uint32_t)DWUART5:
        REG_FIELD_WR(CPU0_SYS_CFG->CPU1_SYS_CFG_REG3, CPU1_SYS_UART5_APB_CLK_CLK_CG0_11, 0x1);
        rv_set_int_isr(CPU_DWUART5_IRQn, DWUART5_Handler);
        csi_vic_clear_pending_irq(CPU_DWUART5_IRQn);
        csi_vic_enable_irq(CPU_DWUART5_IRQn);
        DWUART_inst_env[5] = inst;
    break;
    case (uint32_t)DWUART6: 
        REG_FIELD_WR(CPU0_SYS_CFG->CPU1_SYS_CFG_REG3, CPU1_SYS_UART6_APB_CLK_CLK_CG0_12, 0x1);
        rv_set_int_isr(CPU_DWUART6_IRQn, DWUART6_Handler);
        csi_vic_clear_pending_irq(CPU_DWUART6_IRQn);
        csi_vic_enable_irq(CPU_DWUART6_IRQn);
        DWUART_inst_env[6] = inst;
    break;
    case (uint32_t)DWUART7:
        REG_FIELD_WR(CPU0_SYS_CFG->CPU1_SYS_CFG_REG3, CPU1_SYS_UART7_APB_CLK_CLK_CG0_13, 0x1);
        rv_set_int_isr(CPU_DWUART7_IRQn, DWUART7_Handler);
        csi_vic_clear_pending_irq(CPU_DWUART7_IRQn);
        csi_vic_enable_irq(CPU_DWUART7_IRQn);
        DWUART_inst_env[7] = inst;
    break;
    case (uint32_t)DWUART8:
        REG_FIELD_WR(CPU0_SYS_CFG->CPU0_SYS_CFG_REG4, CPU0_SYS_UART8_APB_CLK_CLK_CG0_1, 0x1);
        rv_set_int_isr(CPU_DWUART8_IRQn, DWUART8_Handler);
        csi_vic_clear_pending_irq(CPU_DWUART8_IRQn);
        csi_vic_enable_irq(CPU_DWUART8_IRQn);
        DWUART_inst_env[8] = inst;
    break;
    case (uint32_t)DWUART9:
        REG_FIELD_WR(CPU0_SYS_CFG->CPU0_SYS_CFG_REG4, CPU0_SYS_UART9_APB_CLK_CLK_CG0_2, 0x1);
        rv_set_int_isr(CPU_DWUART9_IRQn, DWUART9_Handler);
        csi_vic_clear_pending_irq(CPU_DWUART9_IRQn);
        csi_vic_enable_irq(CPU_DWUART9_IRQn);
        DWUART_inst_env[9] = inst;
    break;
    case (uint32_t)DWUART10:
        REG_FIELD_WR(CPU0_SYS_CFG->CPU0_SYS_CFG_REG4, CPU0_SYS_UART10_APB_CLK_CLK_CG0_3, 0x1);
        rv_set_int_isr(CPU_DWUART10_IRQn, DWUART10_Handler);
        csi_vic_clear_pending_irq(CPU_DWUART10_IRQn);
        csi_vic_enable_irq(CPU_DWUART10_IRQn);
        DWUART_inst_env[10] = inst;
    break;
    case (uint32_t)DWUART11:
        REG_FIELD_WR(CPU0_SYS_CFG->CPU0_SYS_CFG_REG4, CPU0_SYS_UART11_APB_CLK_CLK_CG0_4, 0x1);
        rv_set_int_isr(CPU_DWUART11_IRQn, DWUART11_Handler);
        csi_vic_clear_pending_irq(CPU_DWUART11_IRQn);
        csi_vic_enable_irq(CPU_DWUART11_IRQn);
        DWUART_inst_env[11] = inst;
    break;
    case (uint32_t)DWUART12:
        REG_FIELD_WR(CPU1_SYS_CFG->PERIPH_SYS_CFG_REG2, PERIPH_SYS_UART12_APB_CLK_CLK_CG0_3, 0x1);
        rv_set_int_isr(PERIPH_DWUART12_IRQn, DWUART12_Handler);
        csi_vic_clear_pending_irq(PERIPH_DWUART12_IRQn);
        csi_vic_enable_irq(PERIPH_DWUART12_IRQn);
        DWUART_inst_env[12] = inst;
    break;
    case (uint32_t)DWUART13:
        REG_FIELD_WR(CPU1_SYS_CFG->PERIPH_SYS_CFG_REG2, PERIPH_SYS_UART13_APB_CLK_CLK_CG0_4, 0x1);
        rv_set_int_isr(PERIPH_DWUART13_IRQn, DWUART13_Handler);
        csi_vic_clear_pending_irq(PERIPH_DWUART13_IRQn);
        csi_vic_enable_irq(PERIPH_DWUART13_IRQn);
        DWUART_inst_env[13] = inst;
    break;
    case (uint32_t)DWUART14:
        REG_FIELD_WR(CPU1_SYS_CFG->PERIPH_SYS_CFG_REG3, PERIPH_SYS_UART14_APB_CLK_CLK_CG0_1, 0x1);
        rv_set_int_isr(PERIPH_DWUART14_IRQn, DWUART14_Handler);
        csi_vic_clear_pending_irq(PERIPH_DWUART14_IRQn);
        csi_vic_enable_irq(PERIPH_DWUART14_IRQn);
        DWUART_inst_env[14] = inst;
    break;
    case (uint32_t)DWUART15:
        REG_FIELD_WR(CPU1_SYS_CFG->PERIPH_SYS_CFG_REG3, PERIPH_SYS_UART15_APB_CLK_CLK_CG0_2, 0x1);
        rv_set_int_isr(PERIPH_DWUART15_IRQn, DWUART15_Handler);
        csi_vic_clear_pending_irq(PERIPH_DWUART15_IRQn);
        csi_vic_enable_irq(PERIPH_DWUART15_IRQn);
        DWUART_inst_env[15] = inst;
    break;
    }
}

void HAL_DWUART_MSP_DeInit(DWUART_HandleTypeDef *inst)
{
    switch((uint32_t)inst->DWUARTX)
    {
    case (uint32_t)DWUART1:
        REG_FIELD_WR(CPU0_SYS_CFG->CPU1_SYS_CFG_REG3, CPU1_SYS_UART1_APB_CLK_CLK_CG0_7, 0x0);
        csi_vic_disable_irq(CPU_DWUART1_IRQn);
    break;
    case (uint32_t)DWUART2:
        REG_FIELD_WR(CPU0_SYS_CFG->CPU1_SYS_CFG_REG3, CPU1_SYS_UART2_APB_CLK_CLK_CG0_8, 0x0);
        csi_vic_disable_irq(CPU_DWUART2_IRQn);
    break;
    case (uint32_t)DWUART3:
        REG_FIELD_WR(CPU0_SYS_CFG->CPU1_SYS_CFG_REG3, CPU1_SYS_UART3_APB_CLK_CLK_CG0_9, 0x0);
        csi_vic_disable_irq(CPU_DWUART3_IRQn);
    break;
    case (uint32_t)DWUART4:
        REG_FIELD_WR(CPU0_SYS_CFG->CPU1_SYS_CFG_REG3, CPU1_SYS_UART4_APB_CLK_CLK_CG0_10, 0x0);
        csi_vic_disable_irq(CPU_DWUART4_IRQn);
    break;
    case (uint32_t)DWUART5:
        REG_FIELD_WR(CPU0_SYS_CFG->CPU1_SYS_CFG_REG3, CPU1_SYS_UART5_APB_CLK_CLK_CG0_11, 0x0);
        csi_vic_disable_irq(CPU_DWUART5_IRQn);
    break;
    case (uint32_t)DWUART6:
        REG_FIELD_WR(CPU0_SYS_CFG->CPU1_SYS_CFG_REG3, CPU1_SYS_UART6_APB_CLK_CLK_CG0_12, 0x0);
        csi_vic_disable_irq(CPU_DWUART6_IRQn);
    break;
    case (uint32_t)DWUART7:
        REG_FIELD_WR(CPU0_SYS_CFG->CPU1_SYS_CFG_REG3, CPU1_SYS_UART7_APB_CLK_CLK_CG0_13, 0x0);
        csi_vic_disable_irq(CPU_DWUART7_IRQn);
    break;
    case (uint32_t)DWUART8:
        REG_FIELD_WR(CPU0_SYS_CFG->CPU0_SYS_CFG_REG4, CPU0_SYS_UART8_APB_CLK_CLK_CG0_1, 0x0);
        csi_vic_disable_irq(CPU_DWUART8_IRQn);
    break;
    case (uint32_t)DWUART9:
        REG_FIELD_WR(CPU0_SYS_CFG->CPU0_SYS_CFG_REG4, CPU0_SYS_UART9_APB_CLK_CLK_CG0_2, 0x0);
        csi_vic_disable_irq(CPU_DWUART9_IRQn);
    break;
    case (uint32_t)DWUART10:
        REG_FIELD_WR(CPU0_SYS_CFG->CPU0_SYS_CFG_REG4, CPU0_SYS_UART10_APB_CLK_CLK_CG0_3, 0x0);
        csi_vic_disable_irq(CPU_DWUART10_IRQn);
    break;
    case (uint32_t)DWUART11:
        REG_FIELD_WR(CPU0_SYS_CFG->CPU0_SYS_CFG_REG4, CPU0_SYS_UART11_APB_CLK_CLK_CG0_4, 0x0);
        csi_vic_disable_irq(CPU_DWUART11_IRQn);
    break;
    case (uint32_t)DWUART12:
        REG_FIELD_WR(CPU1_SYS_CFG->PERIPH_SYS_CFG_REG2, PERIPH_SYS_UART12_APB_CLK_CLK_CG0_3, 0x0);
        csi_vic_disable_irq(PERIPH_DWUART12_IRQn);
    break;
    case (uint32_t)DWUART13:
        REG_FIELD_WR(CPU1_SYS_CFG->PERIPH_SYS_CFG_REG2, PERIPH_SYS_UART13_APB_CLK_CLK_CG0_4, 0x0);
        csi_vic_disable_irq(PERIPH_DWUART13_IRQn);
    break;
    case (uint32_t)DWUART14:
        REG_FIELD_WR(CPU1_SYS_CFG->PERIPH_SYS_CFG_REG3, PERIPH_SYS_UART14_APB_CLK_CLK_CG0_1, 0x0);
        csi_vic_disable_irq(PERIPH_DWUART14_IRQn);
    break;
    case (uint32_t)DWUART15:
        REG_FIELD_WR(CPU1_SYS_CFG->PERIPH_SYS_CFG_REG3, PERIPH_SYS_UART15_APB_CLK_CLK_CG0_2, 0x0);
        csi_vic_disable_irq(PERIPH_DWUART15_IRQn);
    break;
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

uint8_t HAL_DWUART_TX_DMA_Handshake_Get(DWUART_HandleTypeDef *inst)
{
    uint8_t handshake = 0;

    return handshake;
}

uint8_t HAL_DWUART_RX_DMA_Handshake_Get(DWUART_HandleTypeDef *inst)
{
    uint8_t handshake = 0;

    return handshake;
}


__attribute__((weak)) void LL_DWUART1_Handler() {}

void LL_DWUART1_MSP_Init(void)
{
    rv_set_int_isr(CPU_DWUART1_IRQn, LL_DWUART1_Handler);
    REG_FIELD_WR(CPU0_SYS_CFG->CPU1_SYS_CFG_REG3, CPU1_SYS_UART1_APB_CLK_CLK_CG0_7, 0x1);
}

void LL_DWUART1_MSP_DeInit(void)
{
    REG_FIELD_WR(CPU0_SYS_CFG->CPU1_SYS_CFG_REG3, CPU1_SYS_UART1_APB_CLK_CLK_CG0_7, 0x0);
}

__attribute__((weak)) void LL_DWUART2_Handler() {}

void LL_DWUART2_MSP_Init(void)
{
    rv_set_int_isr(CPU_DWUART2_IRQn, LL_DWUART2_Handler);
    REG_FIELD_WR(CPU0_SYS_CFG->CPU1_SYS_CFG_REG3, CPU1_SYS_UART2_APB_CLK_CLK_CG0_8, 0x1);
}

void LL_DWUART2_MSP_DeInit(void)
{
    REG_FIELD_WR(CPU0_SYS_CFG->CPU1_SYS_CFG_REG3, CPU1_SYS_UART2_APB_CLK_CLK_CG0_8, 0x0);
}


//uart_log
__attribute__((weak)) void LL_DWUART8_Handler() {}

void LL_DWUART8_MSP_Init(void)
{
    rv_set_int_isr(CPU_DWUART8_IRQn, LL_DWUART8_Handler);
    // REG_FIELD_WR(CPU0_SYS_CFG->CPU0_SYS_CFG_REG4, CPU0_SYS_UART8_APB_CLK_CLK_CG0_1, 0x0);
    // CPU1_SYS_CFG->TOP_DIG_CRG_TOP_SYS0_APB_CLK_TOP_RST_N_REG0_CLR = 0x8;
    // CPU1_SYS_CFG->TOP_DIG_CRG_TOP_SYS0_APB_CLK_TOP_RST_N_REG0 = 0x8;
    REG_FIELD_WR(CPU0_SYS_CFG->CPU0_SYS_CFG_REG4, CPU0_SYS_UART8_APB_CLK_CLK_CG0_1, 0x1);
}

void LL_DWUART8_MSP_DeInit(void)
{
    REG_FIELD_WR(CPU0_SYS_CFG->CPU0_SYS_CFG_REG4, CPU0_SYS_UART8_APB_CLK_CLK_CG0_1, 0x0);
}