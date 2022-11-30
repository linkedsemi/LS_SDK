#include "sw_timer_int.h"
#include "reg_lstim_type.h"
#include "field_manipulate.h"
#include "platform.h"
#include "reg_v33_rg_type.h"

sw_timer_time_t timer_time_add(sw_timer_time_t a,sw_timer_time_t b)
{
    return (a + b);
}

int timer_time_compare(sw_timer_time_t a,sw_timer_time_t b)
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
    __NVIC_EnableIRQ(LSTIM_IRQn);
}

void timer_irq_mask()
{
    __NVIC_DisableIRQ(LSTIM_IRQn);
}

void timer_irq_clr()
{
    REG_FIELD_WR(LSTIM->TIM_CTRL,TIM_TIM_INTR_CLR,1);
    __NVIC_ClearPendingIRQ(LSTIM_IRQn);
    REG_FIELD_WR(LSTIM->TIM_CTRL,TIM_TIM_INTR_CLR,0);
}

void timer_setup(void (*isr)())
{
    arm_cm_set_int_isr(LSTIM_IRQn,isr);
    V33_RG->CLKG_SRST = V33_RG_CLKG_SET_TIM_MASK;
    LSTIM->TIM_CTRL = TIM_TIM_EN_MASK|TIM_TIM_INTR_EN_MASK;
}

