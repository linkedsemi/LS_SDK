#define LOG_TAG "MAIN"
#include "string.h"
#include "platform.h"
#include "ls_soc_gpio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "log.h"
#include "ls_dbg.h"
#include "ls_hal_flash.h"

extern void rtos_init(void);
#define LED0_TASK_STACK_SIZE 200
static StackType_t led0_task_stack[LED0_TASK_STACK_SIZE];
static StaticTask_t led0_task_buf;

#define LED0 PE09
#define LED1 PE10
#define LED2 PE11

void LED_init(void)
{
    io_cfg_output(LED0);
    io_cfg_output(LED1);
    io_cfg_output(LED2);
}

static void LED0_Task(void *args)
{
    while (1)
    {
        LOG_I("LED0_Task\n");
        io_toggle_pin(LED0);
        vTaskDelay(1000);    //delay 1000 ms
    }
}

static void LED1_Task(void *args)
{
    while (1)
    {
        LOG_I("LED1_Task\n");
        io_toggle_pin(LED1);
        vTaskDelay(1000);
    }
}

static void LED2_Task(void *args)
{
    while (1)
    {
        LOG_I("LED2_Task\n");
        io_toggle_pin(LED2);
        vTaskDelay(1000);
    }
}

int main()
{
    sys_init_none();
    LOG_I("Free RTOS TEST Start......");
    LED_init();
    rtos_init();
    xTaskCreateStatic(LED0_Task, "LED0", LED0_TASK_STACK_SIZE, NULL, 3, led0_task_stack, &led0_task_buf);
    xTaskCreate(LED1_Task, "LED1", 128, NULL, 2, NULL);
    xTaskCreate(LED2_Task, "LED2", 128, NULL, 1, NULL);
    vTaskStartScheduler();
}
