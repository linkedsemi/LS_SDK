#include "ls_hal_otbn.h"
#include "ls_msp_otbn.h"
#include "field_manipulate.h"
#include "reg_sysc_sec_cpu.h"
#include "core_rv32.h"
#include "platform.h"
#include "co_math.h"
#include "qsh.h"

static uint32_t EDN_URND_BUS_IN;

void HAL_LSOTBN_MSP_Init(void)
{
    REG_FIELD_WR(SYSC_SEC_CPU->INTR_CTRL_INTR_MSK, SYSC_SEC_CPU_I_EDN_URND_REQ, 0);
    SYSC_SEC_CPU->PD_CPU_CLKG[1] = SYSC_SEC_CPU_CLKG_CLR_OTBN_MASK;
    SYSC_SEC_CPU->PD_CPU_SRST[1] = SYSC_SEC_CPU_SRST_CLR_OTBN_MASK;
    SYSC_SEC_CPU->PD_CPU_SRST[1] = SYSC_SEC_CPU_SRST_SET_OTBN_MASK;
    SYSC_SEC_CPU->PD_CPU_CLKG[1] = SYSC_SEC_CPU_CLKG_SET_OTBN_MASK;

    for (uint8_t i = 0; i < 16; i++)
    {
        while (!REG_FIELD_RD(SYSC_SEC_CPU->OTBN_INTR_RAW, SYSC_SEC_CPU_I_EDN_URND_REQ)) ;
        SYSC_SEC_CPU->EDN_URND_BUS = ++EDN_URND_BUS_IN;
        REG_FIELD_WR(SYSC_SEC_CPU->OTBN_CTRL2, SYSC_SEC_CPU_EDN_URND_ACK, 1);
        REG_FIELD_WR(SYSC_SEC_CPU->OTBN_CTRL2, SYSC_SEC_CPU_EDN_URND_ACK, 0);
        SYSC_SEC_CPU->INTR_CLR_MSK = SYSC_SEC_CPU_I_EDN_URND_REQ_MASK;
    }

    SYSC_SEC_CPU->INTR_CLR_MSK = FIELD_BUILD(SYSC_SEC_CPU_I_EDN_RND_REQ, 1) |
                              FIELD_BUILD(SYSC_SEC_CPU_I_EDN_URND_REQ, 1) |
                              FIELD_BUILD(SYSC_SEC_CPU_I_OTBN_OTP_REQ, 1);
    SYSC_SEC_CPU->INTR_CTRL_INTR_MSK = FIELD_BUILD(SYSC_SEC_CPU_I_EDN_RND_REQ, 1) |
                              FIELD_BUILD(SYSC_SEC_CPU_I_EDN_URND_REQ, 1) |
                              FIELD_BUILD(SYSC_SEC_CPU_I_OTBN_OTP_REQ, 1);
                              
    rv_set_int_isr(OBTN_IRQN, HAL_OTBN_IRQHandler);
    csi_vic_clear_pending_irq(OBTN_IRQN);
    csi_vic_enable_irq(OBTN_IRQN);
    rv_set_int_isr(OTBN_SYSC_IRQN, HAL_OTBN_SYSC_IRQHandler);
    csi_vic_clear_pending_irq(OTBN_SYSC_IRQN);
    csi_vic_enable_irq(OTBN_SYSC_IRQN);
}

void HAL_LSOTBN_MSP_DeInit(void)
{
    SYSC_SEC_CPU->PD_CPU_CLKG[1] = SYSC_SEC_CPU_CLKG_CLR_OTBN_MASK;
    csi_vic_disable_irq(OBTN_IRQN);
}

void HAL_OTBN_SYSC_IRQHandler()
{
    uint32_t intr = SYSC_SEC_CPU->OTBN_INTR_STT;
    if (intr & CO_BIT(0))
    {
        SYSC_SEC_CPU->INTR_CLR_MSK = CO_BIT(0);
    }
    if (intr & CO_BIT(1))
    {
        SYSC_SEC_CPU->INTR_CLR_MSK = CO_BIT(1);
    }
    if (intr & CO_BIT(2))
    {
        SYSC_SEC_CPU->INTR_CLR_MSK = CO_BIT(2);
    }
    if (intr & CO_BIT(3))
    {
        SYSC_SEC_CPU->INTR_CLR_MSK = CO_BIT(3);
    }
    if (intr & 0xf0)
    {
        SYSC_SEC_CPU->INTR_CLR_MSK = 0xf0;
    }
    if (intr & CO_BIT(8))
    {
        SYSC_SEC_CPU->EDN_RND_BUS = ++EDN_URND_BUS_IN;  // TODO
        SYSC_SEC_CPU->OTBN_CTRL2 |= CO_BIT(8);
        SYSC_SEC_CPU->INTR_CLR_MSK = CO_BIT(8);
    }
    if (intr & CO_BIT(9))
    {
        SYSC_SEC_CPU->EDN_URND_BUS = ++EDN_URND_BUS_IN;  // TODO
        SYSC_SEC_CPU->OTBN_CTRL2 |= CO_BIT(10);
        SYSC_SEC_CPU->INTR_CLR_MSK = CO_BIT(9);
    }
    if (intr & CO_BIT(10))
    {
        SYSC_SEC_CPU->OTBN_OTP_KEY_0 = ++EDN_URND_BUS_IN;  // TODO
        SYSC_SEC_CPU->OTBN_OTP_KEY_1 = ++EDN_URND_BUS_IN;
        SYSC_SEC_CPU->OTBN_OTP_KEY_2 = ++EDN_URND_BUS_IN;
        SYSC_SEC_CPU->OTBN_OTP_KEY_3 = ++EDN_URND_BUS_IN;
        SYSC_SEC_CPU->OTBN_CTRL2 |= CO_BIT(12);
        SYSC_SEC_CPU->INTR_CLR_MSK = CO_BIT(10);
    }
}