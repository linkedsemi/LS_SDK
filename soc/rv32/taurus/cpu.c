#include "core_rv32.h"
#include "cpu.h"
#include "compile_flag.h"
#if defined(FLASH_PROG_ALGO) || BOOT_RAM==1
XIP_BANNED uint32_t enter_critical()
{
    uint32_t stat = __get_MSTATUS();
    __disable_irq();
    return stat;
}

XIP_BANNED void exit_critical(uint32_t prev_stat)
{
    if(prev_stat&0x8)
    {
        __enable_irq();
    }
}
#else
XIP_BANNED uint32_t enter_critical()
{
    uint32_t stat = CLIC->MINTTHRESH;
    CLIC->MINTTHRESH = 254<<24;
    return stat;
}

XIP_BANNED void exit_critical(uint32_t prev_stat)
{
    if(prev_stat==0)
    {
        CLIC->MINTTHRESH = 0;
    }
}
#endif

bool in_interrupt()
{
    return false;
}

XIP_BANNED void disable_global_irq()
{
    __disable_irq();
}

void enable_global_irq()
{
    __enable_irq();
}
