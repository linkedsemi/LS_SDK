#include "systick.h"
#include "compile_flag.h"
#include "sdk_config.h"
#include "common.h"
#include "platform.h"

static uint32_t total_ticks;

void XIP_BANNED_FUNC(SysTick_Handler,)
{
    total_ticks += 1;
}

void systick_start()
{
    total_ticks = 0;
    arm_cm_set_int_isr(SysTick_IRQn,SysTick_Handler);
    SysTick->LOAD  = (uint32_t)(SDK_HCLK_MHZ*1000000/SYSTICK_RATE_HZ - 1UL);
    SysTick->VAL   = 0UL;
    SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
                     SysTick_CTRL_TICKINT_Msk   |
                     SysTick_CTRL_ENABLE_Msk;
}

uint32_t XIP_BANNED_FUNC(systick_get_value,)
{
    return total_ticks;
}

bool XIP_BANNED_FUNC(systick_poll_timeout,uint32_t start_tick,uint32_t timeout,bool (*poll)(va_list),...)
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
    SysTick->CTRL = 0;
    SCB->ICSR = SCB_ICSR_PENDSTCLR_Msk;
}
