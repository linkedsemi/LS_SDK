#include "sw_timer_int.h"
#include "reg_lstim_type.h"
#include "field_manipulate.h"
#include "exception_isr.h"
#include "reg_v33_rg.h"
#include "core_rv32.h"
#include "platform.h"

sw_timer_time_t timer_time_add(sw_timer_time_t a, sw_timer_time_t b)
{
    return (a + b);
}

int timer_time_compare(sw_timer_time_t a, sw_timer_time_t b)
{
    return a - b;
}

sw_timer_time_t timer_time_get()
{
    return LSTIM->TIM_CNT;
}

void timer_match_set(sw_timer_time_t match)
{
    LSTIM->TIM_TGT = match;
}

void timer_irq_unmask()
{
    csi_vic_enable_irq(TIM_IRQn);
    V33_RG->WKUP_CTRL |= 0x4;
}

void timer_irq_mask()
{
    csi_vic_disable_irq(TIM_IRQn);
    V33_RG->WKUP_CTRL &= ~0x4;
}

void timer_irq_clr()
{
    REG_FIELD_WR(LSTIM->TIM_CTRL, TIM_TIM_INTR_CLR, 1);
    csi_vic_clear_pending_irq(TIM_IRQn);
    REG_FIELD_WR(LSTIM->TIM_CTRL, TIM_TIM_INTR_CLR, 0);
}

void timer_setup(void (*isr)())
{
    rv_set_int_isr(TIM_IRQn, isr);
    V33_RG->CLKG_SRST = V33_RG_CLKG_SET_TIM_MASK;
    LSTIM->TIM_CTRL = TIM_TIM_EN_MASK | TIM_TIM_INTR_EN_MASK;
}
