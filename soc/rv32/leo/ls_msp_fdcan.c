#include "ls_msp_fdcan.h"
#include "ls_hal_fdcan.h"
#include "exception_isr.h"
#include "reg_sysc_cpu.h"
#include "core_rv32.h"
#include "platform.h"
#include "sys_stat.h"
#include "leo.h"

static FDCAN_HandleTypeDef* can_inst_env;

void FDCAN_Handler(void)
{
    HAL_FDCAN_IRQHandler(can_inst_env);
}

void HAL_FDCAN_MSP_Init(FDCAN_HandleTypeDef* inst)
{
    can_inst_env = inst;
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_CLR_BXCAN_MASK;
    SYSC_CPU->PD_CPU_SRST = SYSC_CPU_SRST_CLR_BXCAN_MASK;
    SYSC_CPU->PD_CPU_SRST = SYSC_CPU_SRST_SET_BXCAN_MASK;
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_SET_BXCAN_MASK;
    rv_set_int_isr(BXCAN_IRQn, FDCAN_Handler);
    csi_vic_clear_pending_irq(BXCAN_IRQn);
    csi_vic_enable_irq(BXCAN_IRQn);
}

void HAL_FDCAN_MSP_DeInit(FDCAN_HandleTypeDef* inst)
{
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_CLR_BXCAN_MASK;
    csi_vic_disable_irq(BXCAN_IRQn);
}

void HAL_FDCAN_MSP_Busy_Set(void)
{
    bxcan_status_set(true);
}

void HAL_FDCAN_MSP_Idle_Set(void)
{
    bxcan_status_set(false);
}