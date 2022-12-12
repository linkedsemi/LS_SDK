#include "lm3050.h"
#include "cpu.h"
#include "compile_flag.h"

ROM_SYMBOL uint32_t XIP_BANNED_FUNC(enter_critical,)
{
    uint32_t stat = __get_PRIMASK();
    __disable_irq();
    return stat;
}

ROM_SYMBOL void XIP_BANNED_FUNC(exit_critical,uint32_t prev_stat)
{
    if(prev_stat==0)
    {
        __enable_irq();
    }
}

bool in_interrupt()
{
    return (SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) != 0;
}

void XIP_BANNED_FUNC(disable_global_irq,)
{
    __disable_irq();
}

void enable_global_irq()
{
    __enable_irq();
}

void clr_pending_irq(int32_t irq)
{
    __NVIC_ClearPendingIRQ(irq);
}

uint32_t get_pending_irq(int32_t irq)
{
    return __NVIC_GetPendingIRQ(irq);
}

void enable_irq(int32_t irq)
{
    __NVIC_EnableIRQ(irq);
}

void disable_irq(int32_t irq)
{
    __NVIC_DisableIRQ(irq);
}

