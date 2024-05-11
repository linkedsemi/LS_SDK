/*
 * Copyright (c) 2013-2019 Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020-2021 Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "los_timer.h"
#include "los_config.h"
#include "los_tick.h"
#include "los_arch_interrupt.h"
#include "los_context.h"
#include "los_sched.h"
#include "los_debug.h"

#include "platform.h"
#include "sleep.h"
#include "field_manipulate.h"
#include "reg_lstim_type.h"
#include "sdk_default_config.h"
#include "reg_v33_rg_type.h"
#include "log.h"
#include "ls_soc_gpio.h"
/* ****************************************************************************
Function    : HalTickStart
Description : Configure Tick Interrupt Start
Input       : none
output      : none
return      : LOS_OK - Success , or LOS_ERRNO_TICK_CFG_INVALID - failed
**************************************************************************** */
#if LITEOS_TICK_SOURE == TICK_SOURCE_LSTIMER
uint32_t next_period = 0;
uint32_t pre_start_time = 0;
uint32_t target_time = 0;
static uint32_t compensate = 0;
UINT32 GetLStimerCycle(VOID);

UINT32 HalTickStart(OS_TICK_HANDLER handler)
{
    if ((OS_SYS_CLOCK == 0) ||
        (LOSCFG_BASE_CORE_TICK_PER_SECOND == 0) ||
        (LOSCFG_BASE_CORE_TICK_PER_SECOND > OS_SYS_CLOCK)) {
        return LOS_ERRNO_TICK_CFG_INVALID;
    }
    HalTickLock();
    OsSetVector(LSTIM_IRQn, (HWI_PROC_FUNC)handler);
    g_sysClock = SDK_LCLK_HZ;
    g_cyclesPerTick = SDK_LCLK_HZ / LOSCFG_BASE_CORE_TICK_PER_SECOND;
    LSTIM->TIM_TGT = g_cyclesPerTick;
    V33_RG->CLKG_SRST = V33_RG_CLKG_SET_TIM_MASK;
    next_period = g_cyclesPerTick;
    // HalTickUnlock();
    REG_FIELD_WR(LSTIM->TIM_CTRL,TIM_TIM_INTR_CLR,1);
    __NVIC_ClearPendingIRQ(LSTIM_IRQn);
    REG_FIELD_WR(LSTIM->TIM_CTRL,TIM_TIM_INTR_CLR,0);
    NVIC_SetPriority(PendSV_IRQn,0xff);
    NVIC_SetPriority(LSTIM_IRQn,0xff);
    __NVIC_EnableIRQ(LSTIM_IRQn);
    REG_FIELD_WR(LSTIM->TIM_CTRL,TIM_TIM_EN,1);
    V33_RG->WKUP_CTRL |= 0x4;
    return LOS_OK;
}

WEAK VOID HalSysTickReload(UINT64 nextResponseTime)
{
    HalTickLock();
    compensate = ((nextResponseTime/g_cyclesPerTick)*(SDK_LCLK_HZ%LOSCFG_BASE_CORE_TICK_PER_SECOND))/LOSCFG_BASE_CORE_TICK_PER_SECOND;
    pre_start_time = GetLStimerCycle();
    next_period = nextResponseTime;
    LSTIM->TIM_TGT = nextResponseTime + pre_start_time + compensate;
    // LOG_I("compensate_a = %d",compensate);
    // LOG_I("STIM->TIM_CNT = %ld,LSTIM->TIM_TGT =%ld,   %d", LSTIM->TIM_CNT,LSTIM->TIM_TGT,nextResponseTime);
    REG_FIELD_WR(LSTIM->TIM_CTRL,TIM_TIM_INTR_CLR,1);
    __NVIC_ClearPendingIRQ(LSTIM_IRQn);
    REG_FIELD_WR(LSTIM->TIM_CTRL,TIM_TIM_INTR_CLR,0);
    V33_RG->WKUP_CTRL |= 0x4;
    LSTIM->TIM_CTRL = TIM_TIM_EN_MASK|TIM_TIM_INTR_EN_MASK;
}

WEAK UINT64 HalGetTickCycle(UINT32 *period)
{
    UINT32 hwCycle = 0;
    UINT32 intSave = LOS_IntLock();
    UINT32 val = GetLStimerCycle() - pre_start_time;
    *period = next_period;
    if(val >= next_period)
    {
        hwCycle = val - next_period;
    }
    // LOG_I("hwCycle = %d,val =%d,period = %d,target_time = %d",hwCycle,val,*period,target_time);
    LOS_IntRestore(intSave);
    return (UINT64)hwCycle;
}

WEAK VOID HalTickLock(VOID)
{
    // LSTIM->TIM_CTRL &= ~(TIM_TIM_INTR_EN_MASK|TIM_TIM_EN_MASK);
    LSTIM->TIM_CTRL &= ~(TIM_TIM_INTR_EN_MASK);
}

WEAK VOID HalTickUnlock(VOID)
{
    LSTIM->TIM_CTRL |=TIM_TIM_INTR_EN_MASK;
}

UINT32 GetLStimerCycle(VOID)
{
    UINT32 val1 = 0;
    UINT32 val2 = 0;
    do{
        val1 = LSTIM->TIM_CNT;
        val2 = LSTIM->TIM_CNT;
    }while(val1 != val2);
    return  val1;
}

#define MIN_DEEP_SLEEP_TICKS 20
bool deep_sleep_prepare()
{
    if(next_period>MIN_DEEP_SLEEP_TICKS)
    {
        return true;
    }else
    {
        return false;
    }
}
extern HWI_PROC_FUNC __attribute__((aligned(0x100))) g_hwiForm[OS_VECTOR_CNT];
void deep_sleep_exit_hook()
{
    SCB->VTOR = (UINT32)(UINTPTR)g_hwiForm;
    NVIC_SetPriority(PendSV_IRQn,0xff);
    NVIC_SetPriority(LSTIM_IRQn,0xff);
}

UINT32 HalEnterSleep(VOID)
{
    // __DSB();
    // __WFI();
    // __ISB();
    low_power_mode_sched();
    return LOS_OK;
}

#else
WEAK UINT32 HalTickStart(OS_TICK_HANDLER handler)
{
    UINT32 ret;

    if ((OS_SYS_CLOCK == 0) ||
        (LOSCFG_BASE_CORE_TICK_PER_SECOND == 0) ||
        (LOSCFG_BASE_CORE_TICK_PER_SECOND > OS_SYS_CLOCK)) {
        return LOS_ERRNO_TICK_CFG_INVALID;
    }
#if (LOSCFG_USE_SYSTEM_DEFINED_INTERRUPT == 1)
#if (OS_HWI_WITH_ARG == 1)
    OsSetVector(SysTick_IRQn, (HWI_PROC_FUNC)handler, NULL);
#else
    OsSetVector(SysTick_IRQn, (HWI_PROC_FUNC)handler);
#endif
#endif

    g_sysClock = OS_SYS_CLOCK;
    g_cyclesPerTick = OS_SYS_CLOCK / LOSCFG_BASE_CORE_TICK_PER_SECOND;

    ret = SysTick_Config(LOSCFG_BASE_CORE_TICK_RESPONSE_MAX);
    if (ret == 1) {
        return LOS_ERRNO_TICK_PER_SEC_TOO_SMALL;
    }

    return LOS_OK;
}

WEAK VOID HalSysTickReload(UINT64 nextResponseTime)
{
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    SysTick->LOAD = (UINT32)(nextResponseTime - 1UL); /* set reload register */
    SysTick->VAL = 0UL; /* Load the SysTick Counter Value */
    NVIC_ClearPendingIRQ(SysTick_IRQn);
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

WEAK UINT64 HalGetTickCycle(UINT32 *period)
{
    UINT32 hwCycle = 0;
    UINT32 intSave = LOS_IntLock();
    UINT32 val = SysTick->VAL;
    *period = SysTick->LOAD;
    if (val != 0) {
        hwCycle = *period - val;
    }
    LOS_IntRestore(intSave);
    return (UINT64)hwCycle;
}

WEAK VOID HalTickLock(VOID)
{
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

WEAK VOID HalTickUnlock(VOID)
{
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

UINT32 HalEnterSleep(VOID)
{
    __DSB();
    __WFI();
    __ISB();

    return LOS_OK;
}

#endif