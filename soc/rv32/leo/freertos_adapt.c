#include <limits.h>
#include "FreeRTOS.h"
#include "task.h"
#include "platform.h"
#include "reg_lstim_type.h"
#include "field_manipulate.h"
#include "sleep.h"
#include "cpu.h"

#define TIMER_TASK_STACK_SIZE 100
#define IDLE_TASK_STACK_SIZE 100

static StackType_t timer_task_stack[TIMER_TASK_STACK_SIZE];
static StaticTask_t timer_task_buf;
static StackType_t idle_task_stack[IDLE_TASK_STACK_SIZE];
static StaticTask_t idle_task_buf;

void rtos_init()
{
    // arm_cm_set_int_isr(PendSV_IRQn,xPortPendSVHandler);
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
