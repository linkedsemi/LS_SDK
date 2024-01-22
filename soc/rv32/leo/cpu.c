#include "core_rv32.h"
#include "cpu.h"
#include "compile_flag.h"
uint32_t XIP_BANNED_FUNC(enter_critical,)
{
    uint32_t stat = __get_MSTATUS();
    __disable_irq();
    return stat;
}

void XIP_BANNED_FUNC(exit_critical,uint32_t prev_stat)
{
    if(prev_stat&0x8)
    {
        __enable_irq();
    }
}

bool in_interrupt()
{
    return false;
}

void XIP_BANNED_FUNC(disable_global_irq)
{
    __disable_irq();
}

void enable_global_irq()
{
    __enable_irq();
}

void clr_pending_irq(int32_t irq)
{

}

uint32_t get_pending_irq(int32_t irq)
{
    return 0;
}

void enable_irq(int32_t irq)
{

}

void disable_irq(int32_t irq)
{

}