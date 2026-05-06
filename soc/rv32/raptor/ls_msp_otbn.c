#include "ls_hal_otbn.h"
#include "ls_msp_otbn.h"
#include "field_manipulate.h"
#include "reg_cpu0_sys.h"
#include "core_rv32.h"
#include "platform.h"
#include "co_math.h"
#include "raptor.h"
#include <stdint.h>

static uint32_t EDN_URND_BUS_IN;

void HAL_LSOTBN_MSP_Init(void)
{
    REG_FIELD_WR(CPU0_SYS_CFG->CPU0_SYS_CFG_REG2, CPU0_SYS_OTBN_EDN_APB_CLK_CLK_CG0_16, 0x1);
    REG_FIELD_WR(CPU0_SYS_CFG->CPU0_SYS_CFG_REG2, CPU0_SYS_OTBN_OTP_APB_CLK_CLK_CG0_4, 0x1);
    REG_FIELD_WR(CPU0_SYS_CFG->CPU0_SYS_CFG_REG1, CPU0_SYS_OTBN_AHB_CLK_CLK_CG0_18, 0x1);
    CPU0_SYS_CFG->OTBN_INTR_MASK = 0x0;
    CPU0_SYS_CFG -> CPU0_SYS_CRG_CPU0_SYS_AHB_CLK_TOP_RST_N_REG0_CLR = 0x00040000;
    CPU0_SYS_CFG -> CPU0_SYS_CRG_CPU0_SYS_AHB_CLK_TOP_RST_N_REG0 = 0xffffffff;

    for (uint8_t i = 0; i < 16; i++)
    {
        while (!REG_FIELD_RD(CPU0_SYS_CFG->OTBN_CFG_RO, CPU0_SYS_EDN_URND_REQ)) ;
        CPU0_SYS_CFG->EDN_URND_BUS = ++EDN_URND_BUS_IN;
        REG_FIELD_WR(CPU0_SYS_CFG->OTBN_CFG_RW, CPU0_SYS_EDN_URND_ACK, 1);
    }

    CPU0_SYS_CFG->OTBN_INTR_CLR = 0x700;
    CPU0_SYS_CFG->OTBN_INTR_MASK = 0x700;

    rv_set_int_isr(CPU_OTBN_IRQn, HAL_OTBN_IRQHandler);
    csi_vic_clear_pending_irq(CPU_OTBN_IRQn);
    csi_vic_enable_irq(CPU_OTBN_IRQn);
    rv_set_int_isr(CPU_OTBN_SYSC_IRQn, HAL_OTBN_SYSC_IRQHandler);
    csi_vic_clear_pending_irq(CPU_OTBN_SYSC_IRQn);
    csi_vic_enable_irq(CPU_OTBN_SYSC_IRQn);
}

void HAL_LSOTBN_MSP_DeInit(void)
{
    REG_FIELD_WR(CPU0_SYS_CFG->CPU0_SYS_CFG_REG1, CPU0_SYS_OTBN_AHB_CLK_CLK_CG0_18, 0x0);
    REG_FIELD_WR(CPU0_SYS_CFG->CPU0_SYS_CFG_REG2, CPU0_SYS_OTBN_EDN_APB_CLK_CLK_CG0_16, 0x0);
    REG_FIELD_WR(CPU0_SYS_CFG->CPU0_SYS_CFG_REG2, CPU0_SYS_OTBN_OTP_APB_CLK_CLK_CG0_4, 0x0);
    csi_vic_disable_irq(CPU_OTBN_IRQn);
    csi_vic_disable_irq(CPU_OTBN_SYSC_IRQn);
}

void HAL_OTBN_SYSC_IRQHandler(void)
{
    uint32_t rand_data[4];
    uint32_t intr = CPU0_SYS_CFG->OTBN_INTR_STT;
    if (intr & CO_BIT(0))
    {
        CPU0_SYS_CFG->OTBN_INTR_CLR = CO_BIT(0);
    }
    if (intr & CO_BIT(1))
    {
        CPU0_SYS_CFG->OTBN_INTR_CLR = CO_BIT(1);
    }
    if (intr & CO_BIT(2))
    {
        CPU0_SYS_CFG->OTBN_INTR_CLR = CO_BIT(2);
    }
    if (intr & CO_BIT(3))
    {
        CPU0_SYS_CFG->OTBN_INTR_CLR = CO_BIT(3);
    }
    if (intr & 0xf0)
    {
        CPU0_SYS_CFG->OTBN_INTR_CLR = 0xf0;
    }
    if (intr & CO_BIT(8))
    { 
        rand_data[0] = ++EDN_URND_BUS_IN;
        CPU0_SYS_CFG->EDN_RND_BUS = rand_data[0];  
        CPU0_SYS_CFG->OTBN_CFG_RW |= CO_BIT(8);
        CPU0_SYS_CFG->OTBN_INTR_CLR = CO_BIT(8);
    }
    if (intr & CO_BIT(9))
    {
        rand_data[0] = ++EDN_URND_BUS_IN;
        CPU0_SYS_CFG->EDN_URND_BUS = rand_data[0]; 
        CPU0_SYS_CFG->OTBN_CFG_RW |= CO_BIT(10);
        CPU0_SYS_CFG->OTBN_INTR_CLR = CO_BIT(9);
    }
    if (intr & CO_BIT(10))
    {
        CPU0_SYS_CFG->OTBN_OTP_KEY_0 = ++EDN_URND_BUS_IN;  
        CPU0_SYS_CFG->OTBN_OTP_KEY_1 = ++EDN_URND_BUS_IN;
        CPU0_SYS_CFG->OTBN_OTP_KEY_2 = ++EDN_URND_BUS_IN;
        CPU0_SYS_CFG->OTBN_OTP_KEY_3 = ++EDN_URND_BUS_IN;
        CPU0_SYS_CFG->OTBN_CFG_RW |= CO_BIT(12);
        CPU0_SYS_CFG->OTBN_INTR_CLR = CO_BIT(10);
    }
}
