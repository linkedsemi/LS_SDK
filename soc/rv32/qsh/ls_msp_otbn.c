#include "ls_hal_otbn.h"
#include "ls_msp_otbn.h"
#include "reg_sysc_cpu.h"
#include "core_rv32.h"
#include "platform.h"
#include "qsh.h"

#define CO_BIT(pos) (1UL<<(pos))

void HAL_LSOTBN_MSP_Init(void)
{
    SYSC_CPU->PD_CPU_CLKG[1] = SYSC_CPU_CLKG_CLR_OTBN_MASK;
    SYSC_CPU->PD_CPU_SRST[1] = SYSC_CPU_SRST_CLR_OTBN_MASK;
    SYSC_CPU->PD_CPU_SRST[1] = SYSC_CPU_SRST_SET_OTBN_MASK;
    SYSC_CPU->PD_CPU_CLKG[1] = SYSC_CPU_CLKG_SET_OTBN_MASK;
    rv_set_int_isr(QSH_OTBN_IRQn, HAL_OTBN_IRQHandler);
    csi_vic_clear_pending_irq(QSH_OTBN_IRQn);
    csi_vic_enable_irq(QSH_OTBN_IRQn);
    rv_set_int_isr(QSH_SYSC_OTBN_IRQn, HAL_OTBN_SYSC_IRQHandler);
    csi_vic_clear_pending_irq(QSH_SYSC_OTBN_IRQn);
    csi_vic_enable_irq(QSH_SYSC_OTBN_IRQn);
    
    SYSC_CPU->OTBN_CTRL1 |= SYSC_CPU_EDN_URND_FIPS_MASK;
    for (uint8_t i = 0; i < 8; i++)
    {
        SYSC_CPU->EDN_URND_BUS = i;
        SYSC_CPU->OTBN_CTRL1 |= SYSC_CPU_EDN_URND_ACK_MASK;
        SYSC_CPU->OTBN_CTRL1 &= ~SYSC_CPU_EDN_URND_ACK_MASK;
        __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
        __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    }
    for (uint8_t i = 0; i < 8; i++)
    {
        SYSC_CPU->EDN_URND_BUS = i;
        SYSC_CPU->OTBN_CTRL1 |= SYSC_CPU_EDN_URND_ACK_MASK;
        SYSC_CPU->OTBN_CTRL1 &= ~SYSC_CPU_EDN_URND_ACK_MASK;
        __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
        __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    }

    SYSC_CPU->INTR_CTRL_CLR = 0x7ff;
    SYSC_CPU->INTR_CTRL_MSK = 0x700;
}


void HAL_LSOTBN_MSP_DeInit(void)
{
    SYSC_CPU->PD_CPU_CLKG[1] = SYSC_CPU_CLKG_CLR_OTBN_MASK;
    csi_vic_disable_irq(QSH_OTBN_IRQn);
}

void HAL_OTBN_SYSC_IRQHandler()
{
    uint32_t intr = SYSC_CPU->INTR_CTRL_STT;
    if (intr & CO_BIT(0))
    {
        SYSC_CPU->INTR_CTRL_CLR = CO_BIT(0);
    }
    if (intr & CO_BIT(1))
    {
        SYSC_CPU->INTR_CTRL_CLR = CO_BIT(1);
    }
    if (intr & CO_BIT(2))
    {
        SYSC_CPU->INTR_CTRL_CLR = CO_BIT(2);
    }
    if (intr & CO_BIT(3))
    {
        SYSC_CPU->INTR_CTRL_CLR = CO_BIT(3);
    }
    if (intr & 0xf0)
    {
        SYSC_CPU->INTR_CTRL_CLR = 0xf0;
    }
    if (intr & CO_BIT(8))
    {
        SYSC_CPU->INTR_CTRL_CLR = CO_BIT(8);
        SYSC_CPU->EDN_RND_BUS = 0x3c3c5a5a;  // TODO
        SYSC_CPU->OTBN_CTRL1 |= CO_BIT(8);
    }
    if (intr & CO_BIT(9))
    {
        SYSC_CPU->INTR_CTRL_CLR = CO_BIT(9);
        SYSC_CPU->EDN_URND_BUS = 0x3c3c5a5a;  // TODO
        SYSC_CPU->OTBN_CTRL1 |= CO_BIT(10);
    }
    if (intr & CO_BIT(10))
    {
        SYSC_CPU->OTBN_OTP_KEY_0 = 0x3c3c5a5a;  // TODO
        SYSC_CPU->OTBN_OTP_KEY_1 = 0x3c3c5a5a;
        SYSC_CPU->OTBN_OTP_KEY_2 = 0x3c3c5a5a;
        SYSC_CPU->OTBN_OTP_KEY_3 = 0x3c3c5a5a;
        SYSC_CPU->OTBN_CTRL1 |= CO_BIT(12);
        SYSC_CPU->INTR_CTRL_CLR = CO_BIT(10);
    }
}