#include <limits.h>
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "platform.h"
#include "common.h"
#include "le501x.h"
#include "sleep.h"
#include "ls_dbg.h"
#include "ls_sys.h"
#include "cpu.h"
#define BLE_TASK_STACK_SIZE 200
#define TIMER_TASK_STACK_SIZE 100
#define IDLE_TASK_STACK_SIZE 100
static StackType_t timer_task_stack[TIMER_TASK_STACK_SIZE];
static StaticTask_t timer_task_buf;
static StackType_t idle_task_stack[IDLE_TASK_STACK_SIZE];
static StaticTask_t idle_task_buf;
static StackType_t ble_task_stack[BLE_TASK_STACK_SIZE];
static StaticTask_t ble_task_buf;
static uint32_t expected_idle_time;
static bool os_tick_updated;
void ke_timer_os_tick_start(uint32_t hs,uint32_t hus);
uint32_t ke_timer_os_tick_inc(uint32_t hs,uint32_t hus,bool compensation);
void ke_timer_os_wrapper_init(void (*start)(void **,uint32_t),void (*stop)(void **),void (*tick_handler)(),void (*wakeup_compensate)(uint32_t));
void os_wrapped_timer_callback(uint32_t);
uint32_t ble_isr(void);
void ble_sched(void);
void xPortPendSVHandler(void);

void vPortSetupTimerInterrupt( void )
{
    ke_timer_os_tick_start(OSTICK_HS_INC(configTICK_RATE_HZ),OSTICK_HUS_INC(configTICK_RATE_HZ));
}

void vPortSuppressTicksAndSleep( TickType_t xExpectedIdleTime )
{
    expected_idle_time = xExpectedIdleTime;
    sleep_process();
}

void check_and_sleep()
{
    if(os_tick_updated&&mac_sleep_check())
    {
        os_tick_updated = false;
        deep_sleep();
    }
}

static void ble_stack_task_notify_give_from_isr()
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    vTaskNotifyGiveFromISR((void *)&ble_task_buf,&xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void ble_stack_isr()
{
    uint32_t irq_stat = ble_isr();
    if(irq_stat != 0x40)
    {
        ble_stack_task_notify_give_from_isr();
    }
}

static void ble_stack_task(void *param)
{
    while(1)
    {
        ble_sched();
        ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
    }
}

static void timer_callback(TimerHandle_t xTimer)
{
    void *arg = pvTimerGetTimerID(xTimer);
    os_wrapped_timer_callback((uint32_t)arg);
    xTimerDelete(xTimer,portMAX_DELAY);
}

static void timer_start(void **p_timer_hdl,uint32_t delay)
{
    *p_timer_hdl = xTimerCreate("ke",pdMS_TO_TICKS(delay),pdFALSE,p_timer_hdl,timer_callback);
    xTimerStart(*p_timer_hdl,portMAX_DELAY);
}

static void timer_stop(void **timer_hdl)
{
    taskENTER_CRITICAL();
    xTimerStop(*timer_hdl,portMAX_DELAY);
    xTimerStart(*timer_hdl,portMAX_DELAY);
    taskEXIT_CRITICAL();
}

static void os_tick_handler()
{
    uint32_t tick_inc = ke_timer_os_tick_inc(OSTICK_HS_INC(configTICK_RATE_HZ),OSTICK_HUS_INC(configTICK_RATE_HZ),false);
    while(tick_inc--)
    {
        uint32_t ulPreviousMask = portSET_INTERRUPT_MASK_FROM_ISR();
        if(xTaskIncrementTick())
        {
            portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT;
        }
        portCLEAR_INTERRUPT_MASK_FROM_ISR( ulPreviousMask );
    }
    os_tick_updated = true;
}

static void wakeup_compensation(uint32_t hus)
{
    uint32_t ticks = CEILING(hus,2*1000000/configTICK_RATE_HZ);
    vTaskStepTick(ticks);
    ke_timer_os_tick_inc(OSTICK_HS_STEP_INC(configTICK_RATE_HZ,ticks),OSTICK_HUS_STEP_INC(configTICK_RATE_HZ,ticks),true);
}

static void stack_reset_hook()
{
    ke_timer_os_tick_start(OSTICK_HS_INC(configTICK_RATE_HZ),OSTICK_HUS_INC(configTICK_RATE_HZ));
}

static int32_t os_sleep_dur_get()
{
    eSleepModeStatus eSleepStatus = eTaskConfirmSleepModeStatus();
    int32_t dur = 0;
    switch(eSleepStatus)
    {
    case eStandardSleep:
        dur = OSTICK_HS_STEP_INC(configTICK_RATE_HZ,expected_idle_time-1);
    break;
    case eNoTasksWaitingTimeout:
        dur = INT_MAX;
    break;
    case eAbortSleep:
        dur = 0;
    break;
    }
    return dur;
}

extern void (*stack_reset_hook_fn)(void);
extern int32_t (*os_sleep_duration_get_fn)();
void ble_task_init()
{
    os_sleep_duration_get_fn = os_sleep_dur_get;
    stack_reset_hook_fn = stack_reset_hook;
    ke_timer_os_wrapper_init(timer_start,timer_stop,os_tick_handler,wakeup_compensation);
    xTaskCreateStatic(ble_stack_task,"ble",BLE_TASK_STACK_SIZE,NULL,configTIMER_TASK_PRIORITY-1,ble_task_stack,&ble_task_buf);
}


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

void rtos_ble_task_func_post(void (*func)(void *),void *param)
{
    func_post(func,param);
    if(in_interrupt())
    {
        ble_stack_task_notify_give_from_isr();
    }else
    {
        xTaskNotifyGive((void *)&ble_task_buf);
    }
}
