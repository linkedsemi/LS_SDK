#include "ls_msp_ltpi.h"
#include "reg_sysc_app_cpu.h"
#include "core_rv32.h"
#include "platform.h"
#include "qsh.h"

void LTPI_IRQHandler()
{}

void HAL_MSP_LTPI_PHY_Init()
{
    SYSC_APP_CPU->PD_CPU_CLKG1 = SYSC_APP_CPU_CLKG_CLR_LTPI_HPM_MASK;
    SYSC_APP_CPU->PD_CPU_CLKG1 = SYSC_APP_CPU_CLKG_CLR_LTPI_PHY_MASK;
    SYSC_APP_CPU->PD_CPU_SRST1 = SYSC_APP_CPU_SRST_CLR_LTPI_HPM_MASK;
    SYSC_APP_CPU->PD_CPU_CLKG1 = SYSC_APP_CPU_CLKG_SET_LTPI_HPM_MASK;
    SYSC_APP_CPU->PD_CPU_CLKG1 = SYSC_APP_CPU_CLKG_SET_LTPI_PHY_MASK;
    SYSC_APP_CPU->PD_CPU_SRST1 = SYSC_APP_CPU_SRST_SET_LTPI_HPM_MASK;

    rv_set_int_isr(LTPI_IRQN, LTPI_IRQHandler);
    csi_vic_clear_pending_irq(LTPI_IRQN);
    csi_vic_enable_irq(LTPI_IRQN);
}

void HAL_MSP_LTPI_PHY_DeInit()
{
    csi_vic_disable_irq(LTPI_IRQN);
}