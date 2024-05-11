#include <limits.h>
#include "FreeRTOS.h"
#include "task.h"
#include "platform.h"
#include "reg_lstim_type.h"
#include "reg_v33_rg_type.h"
#include "field_manipulate.h"
#include "sleep.h"
#include "cpu.h"
#define CYC_PER_TICK (SDK_LCLK_HZ/configTICK_RATE_HZ)
#define REMAINDER_CYC_PER_TICK (SDK_LCLK_HZ%configTICK_RATE_HZ)
#define TIMER_TASK_STACK_SIZE 100
#define IDLE_TASK_STACK_SIZE 100
#define MIN_DEEP_SLEEP_TICKS 5
static StackType_t timer_task_stack[TIMER_TASK_STACK_SIZE];
static StaticTask_t timer_task_buf;
static StackType_t idle_task_stack[IDLE_TASK_STACK_SIZE];
static StaticTask_t idle_task_buf;
void xPortPendSVHandler(void);

#if OS_TICK_SOURCE == LOW_SPEED_TIMER
static TickType_t expected_idle_time;
static uint32_t prev_target;
static uint32_t accumulated_remainder_cyc;

static void lstim_int_clr()
{
    REG_FIELD_WR(LSTIM->TIM_CTRL,TIM_TIM_INTR_CLR,1);
    __NVIC_ClearPendingIRQ(LSTIM_IRQn);
    REG_FIELD_WR(LSTIM->TIM_CTRL,TIM_TIM_INTR_CLR,0);
}

static uint32_t lstim_cnt_get()
{
    uint32_t val1,val2;
    do{
        val1 = LSTIM->TIM_CNT;
        val2 = LSTIM->TIM_CNT;
    }while(val1!=val2);
    return val1;
}

static void os_tick_handler()
{
    portDISABLE_INTERRUPTS();
    lstim_int_clr();
    uint32_t tick_inc = (lstim_cnt_get() - prev_target)/CYC_PER_TICK;
    accumulated_remainder_cyc += tick_inc*REMAINDER_CYC_PER_TICK;
    prev_target += tick_inc*CYC_PER_TICK + accumulated_remainder_cyc/configTICK_RATE_HZ;
    accumulated_remainder_cyc %= configTICK_RATE_HZ;
    LSTIM->TIM_TGT = prev_target + CYC_PER_TICK + 2;
    portENABLE_INTERRUPTS();
    while(tick_inc--)
    {
        portDISABLE_INTERRUPTS();
        {
            /* Increment the RTOS tick. */
            if( xTaskIncrementTick() != pdFALSE )
            {
                /* A context switch is required.  Context switching is performed in
                * the PendSV interrupt.  Pend the PendSV interrupt. */
                portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT;
            }
        }
        portENABLE_INTERRUPTS();
    }

}

void vPortSetupTimerInterrupt( void )
{
    arm_cm_set_int_isr(LSTIM_IRQn,os_tick_handler);
    V33_RG->CLKG_SRST = V33_RG_CLKG_SET_TIM_MASK;
    LSTIM->TIM_CTRL = TIM_TIM_EN_MASK|TIM_TIM_INTR_EN_MASK;
    LSTIM->TIM_TGT = CYC_PER_TICK;
    lstim_int_clr();
    __NVIC_SetPriority(LSTIM_IRQn,255);
    __NVIC_EnableIRQ(LSTIM_IRQn);
    V33_RG->WKUP_CTRL |= 0x4;
}

bool deep_sleep_prepare()
{
    if(expected_idle_time>MIN_DEEP_SLEEP_TICKS)
    {
        LSTIM->TIM_TGT = prev_target + expected_idle_time * CYC_PER_TICK;
        lstim_int_clr();
        return true;
    }else
    {
        return false;
    }
}

void deep_sleep_exit_hook()
{
    __NVIC_SetPendingIRQ(LSTIM_IRQn);
}

void vPortSuppressTicksAndSleep( TickType_t xExpectedIdleTime )
{
    expected_idle_time = xExpectedIdleTime;
    low_power_mode_sched();
}

#else
extern void xPortSysTickHandler(void);

void systick_start(){
    arm_cm_set_int_isr(SysTick_IRQn,xPortSysTickHandler);
}

uint32_t systick_get_value()
{
    if(in_interrupt())
    {
        return xTaskGetTickCountFromISR();
    }else
    {
        return xTaskGetTickCount();
    }
}

#endif

void rtos_init()
{
    arm_cm_set_int_isr(PendSV_IRQn,xPortPendSVHandler);
}

void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer,
                                    StackType_t ** ppxIdleTaskStackBuffer,
                                    uint32_t * pulIdleTaskStackSize )
{
    *ppxIdleTaskTCBBuffer = &idle_task_buf;
    *ppxIdleTaskStackBuffer = idle_task_stack;
    *pulIdleTaskStackSize = IDLE_TASK_STACK_SIZE;
}

void vApplicationGetTimerTaskMemory( StaticTask_t ** ppxTimerTaskTCBBuffer,
                                     StackType_t ** ppxTimerTaskStackBuffer,
                                     uint32_t * pulTimerTaskStackSize )
{
    *ppxTimerTaskTCBBuffer = &timer_task_buf;
    *ppxTimerTaskStackBuffer = timer_task_stack;
    *pulTimerTaskStackSize = TIMER_TASK_STACK_SIZE;
}

void sw_timer_module_init(void){}
