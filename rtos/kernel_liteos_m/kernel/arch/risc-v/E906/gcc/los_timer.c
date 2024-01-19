/*
 * Copyright (c) 2013-2020, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020-2021 Huawei Device Co., Ltd. All rights reserved.
 * Copyright (c) 2021 Nuclei Limited. All rights reserved.
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
#include "los_reg.h"
#include "los_arch_interrupt.h"
#include "los_sched.h"
#include "los_arch_timer.h"
#include "los_compiler.h"

#include "platform.h"
#include "core_rv32.h"
#include "field_manipulate.h"
#include "sw_timer_int.h"
#include "reg_lstim_type.h"
#include "reg_v33_rg.h"
#include "sleep.h"
#include "leo.h"
#include "log.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define configKERNEL_INTERRUPT_PRIORITY         0

#if LITEOS_TICK_SOURE == TICK_SOURCE_LSTIMER
#define RV_TIME_IRQ_IDX    TIM_IRQn
#else
#define RV_TIME_IRQ_IDX    RV_TIME_IRQn
#endif
#define RV_SOFT_IRQ_IDX    23   // IRQ_IDX 3 was already used flash_controler  RV_SOFT_IRQn

void HalTickSysTickHandler(void);

static OS_TICK_HANDLER systick_handler = (OS_TICK_HANDLER)NULL;

extern UINT32 g_intCount;
extern void SW_handler(void);

#if LITEOS_TICK_SOURE == TICK_SOURCE_LSTIMER
uint32_t next_period = 0;
uint32_t pre_start_time = 0;
uint32_t target_time = 0;
static uint32_t compensate = 0;
UINT32 GetLStimerCycle(VOID);
#endif

STATIC VOID cpu_sleep_mode_config(UINT8 deep)
{
    uint32_t mextstaus = __get_MEXSTATUS();
    MODIFY_REG(mextstaus,MEXSTATUS_SLEEP_Msk,(!deep)<<MEXSTATUS_SLEEP_Pos);
    __set_MEXSTATUS(mextstaus);
}

WEAK UINT32 HalTickStart(OS_TICK_HANDLER handler)
{
    g_sysClock = OS_SYS_CLOCK;
    g_cyclesPerTick = g_sysClock / LOSCFG_BASE_CORE_TICK_PER_SECOND;
    g_intCount = 0;
    cpu_sleep_mode_config(0);
    MODIFY_REG(CLIC->CLICCFG,CLIC_CLICCFG_NLBIT_Msk,0xf<<CLIC_CLICCFG_NLBIT_Pos);
    LOG_I("cliccfg = %x",*(uint32_t *)0xe0800000); //bit 1-4
    csi_vic_set_vector(RV_SOFT_IRQ_IDX,(uint32_t)SW_handler);
    CLIC->CLICINT[RV_SOFT_IRQ_IDX].ATTR = (1 << CLIC_INTATTR_TRIG_Pos)| (1 << CLIC_INTATTR_SHV_Pos);
    csi_vic_clear_pending_irq(RV_SOFT_IRQ_IDX);
    csi_vic_set_prio(RV_SOFT_IRQ_IDX,1);
    csi_vic_enable_irq(RV_SOFT_IRQ_IDX);
#if LITEOS_TICK_SOURE == TICK_SOURCE_LSTIMER
    LOG_I("ls timer START");
    csi_vic_set_vector(RV_TIME_IRQ_IDX,(uint32_t)HalTickSysTickHandler);
    V33_RG->CLKG_SRST = V33_RG_CLKG_SET_TIM_MASK;
    next_period = g_cyclesPerTick;
    REG_FIELD_WR(LSTIM->TIM_CTRL,TIM_TIM_INTR_CLR,1);
    csi_vic_clear_pending_irq(RV_TIME_IRQ_IDX);
    REG_FIELD_WR(LSTIM->TIM_CTRL,TIM_TIM_INTR_CLR,0);
    csi_vic_set_prio(RV_TIME_IRQ_IDX,1);
    csi_vic_enable_irq(RV_TIME_IRQ_IDX);
    REG_FIELD_WR(LSTIM->TIM_CTRL,TIM_TIM_EN,1);
    V33_RG->WKUP_CTRL |= 0x4;
#else
    LOG_I("systic START");
    csi_vic_set_vector(RV_TIME_IRQ_IDX,(uint32_t)HalTickSysTickHandler);
    csi_vic_clear_pending_irq(RV_TIME_IRQ_IDX);
    csi_vic_set_prio(RV_TIME_IRQ_IDX,0xf);
    CORET->MTIMECMP = g_cyclesPerTick + CORET->MTIME;
    csi_vic_enable_irq(RV_TIME_IRQ_IDX);
#endif
    systick_handler = handler;
    return LOS_OK; /* never return */
}

void HalTickSysTickHandler(void)
{
    /* Do systick handler registered in HalTickStart. */
    if ((void *)systick_handler != NULL) {
        HalTickLock();
        systick_handler();
    }
}
#if LITEOS_TICK_SOURE == TICK_SOURCE_LSTIMER
WEAK VOID HalSysTickReload(UINT64 nextResponseTime)
{
    HalTickLock();
    compensate = ((nextResponseTime/g_cyclesPerTick)*(SDK_LCLK_HZ%LOSCFG_BASE_CORE_TICK_PER_SECOND))/LOSCFG_BASE_CORE_TICK_PER_SECOND;
    pre_start_time = GetLStimerCycle();
    next_period = nextResponseTime;
    LSTIM->TIM_TGT = nextResponseTime + pre_start_time + compensate;
    // LOG_I("compensate_a = %d",compensate);
    // LOG_I("LSTIM->TIM_CNT = %ld,LSTIM->TIM_TGT =%ld,   %d", LSTIM->TIM_CNT,LSTIM->TIM_TGT,nextResponseTime);
    REG_FIELD_WR(LSTIM->TIM_CTRL,TIM_TIM_INTR_CLR,1);
    csi_vic_clear_pending_irq(RV_TIME_IRQ_IDX);
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

void deep_sleep_exit_hook()
{

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
UINT32 HalEnterSleep(VOID)
{
    low_power_mode_sched();
    return LOS_OK;
}
#else
WEAK VOID HalSysTickReload(UINT64 nextResponseTime)
{
    // LOG_I("nextResponseTime: %ld ",nextResponseTime*1000000/OS_SYS_CLOCK);
    unsigned long long target;
    do{
        // target = CORET->MTIMECMP + nextResponseTime;
        target = CORET->MTIME + nextResponseTime;
        CORET->MTIMECMP = target;
    }while(target<CORET->MTIME);
    HalTickUnlock();
}

WEAK UINT64 HalGetTickCycle(UINT32 *period)
{
    UINT64 ticks;
    UINT32 intSave = LOS_IntLock();
    ticks = CORET->MTIME;
    if(period != NULL)
        *period = (UINT32)CORET->MTIME;
    LOS_IntRestore(intSave);
    return ticks;
}

WEAK VOID HalTickLock(VOID)
{
    csi_vic_disable_irq(RV_TIME_IRQ_IDX);
    csi_vic_clear_pending_irq(RV_TIME_IRQ_IDX);
}

WEAK VOID HalTickUnlock(VOID)
{
    csi_vic_clear_pending_irq(RV_TIME_IRQ_IDX);
    csi_vic_enable_irq(RV_TIME_IRQ_IDX);
}

UINT32 HalEnterSleep(VOID)
{
    // __WFI();
    return LOS_OK;
}
#endif

#include <signal.h>
int _kill(int pid, int sig) {
    // Your implementation here
    // You may want to use the kill system call or provide a custom behavior
    // depending on your requirements.
    return -1; // Returning -1 indicates failure (as _kill is expected to do on failure)
}

pid_t _getpid(void) {
    // Your implementation here
    // You may want to use the getpid system call or provide a custom behavior
    // depending on your requirements.
    return -1; // Returning -1 indicates failure (as getpid is expected to do on failure)
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
