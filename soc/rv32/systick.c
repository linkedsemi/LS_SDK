#include "systick.h"
#include "core_rv32.h"
#include "compile_flag.h"
#include "common.h"
#include "exception_isr.h"
#define RV_TIME_IRQ_IDX 7
static uint32_t total_ticks;

XIP_BANNED void SysTick_Handler()
{
    unsigned long long target;
    do{
        total_ticks += 1;
        target = CORET->MTIMECMP + SDK_HCLK_MHZ*1000000/SYSTICK_RATE_HZ;
        CORET->MTIMECMP = target;
    }while(target<CORET->MTIME);
}

void systick_start(void)
{
    total_ticks = 0;
    rv_set_int_isr(RV_TIME_IRQ_IDX,SysTick_Handler);
    CORET->MTIMECMP = SDK_HCLK_MHZ*1000000/SYSTICK_RATE_HZ + CORET->MTIME;
    csi_vic_clear_pending_irq(RV_TIME_IRQ_IDX);
    csi_vic_enable_irq(RV_TIME_IRQ_IDX);
}

XIP_BANNED uint32_t systick_get_value(void)
{
    return total_ticks;
}

XIP_BANNED bool systick_poll_timeout(uint32_t start_tick,uint32_t timeout,bool (*poll)(va_list),...)
{
    va_list ap;
    uint32_t end_tick = start_tick + timeout;
    do{
        if(poll)
        {
            va_start(ap,poll);
            if(poll(ap))
            {
                return false;
            }
        }
    }while(time_diff(systick_get_value(),end_tick)<0);
    return true;
}

void systick_stop()
{
    csi_vic_disable_irq(RV_TIME_IRQ_IDX);
}
