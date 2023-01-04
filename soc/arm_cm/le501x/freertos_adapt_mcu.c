#include <limits.h>
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "platform.h"
#include "common.h"
#include "le501x.h"
#include "sys_stat.h"
#include "sleep.h"
#include "ls_dbg.h"
#include "ls_sys.h"
#include "cpu.h"
#include "ls_24g_common_freertos.h"
#include "ls_soc_gpio.h"

#define LS_24G_VERSION_ADDR 0x50000004

#define HALF_SLOT_TIME_MAX 624

#define MS_2_PERIOD(x) (2000*(uint64_t)(x)/625)
#define PERIOD_2_MS(x) (625*(uint64_t)(x)/2000)

#define SLEEP_MINIMUM_HS_CYCLES 10
#define CNTL (*(volatile uint32_t *)0x50000000)
#define INT_MASK (*(volatile uint32_t *)0x50000018)
#define INT_STAT (*(volatile uint32_t *)0x5000001c)
#define INT_CLR (*(volatile uint32_t *)0x50000020)
#define SLEEP_CNTL (*(volatile uint32_t *)0x50000030)
#define SLEEP_TIME (*(volatile uint32_t *)0x50000034)
#define SLEEP_DUR (*(volatile uint32_t *)0x50000038)
#define WKUP_CNTL (*(volatile uint32_t *)0x5000003c)
#define TIME_CORR (*(volatile uint32_t *)0x50000040)
#define TIME_CORR2 (*(volatile uint32_t *)0x50000044)
#define CLK_TARGET_HS (*(volatile uint32_t *)0x500000f0)
#define CLK_TARGET_HUS (*(volatile uint32_t *)0x500000f4)
#define CLK_SAMP (*(volatile uint32_t *)0x500000f8)
#define CNT_SAMP (*(volatile uint32_t *)0x500000fc)

#define MAC_MAX_CLOCK_TIME              ((1L<<28) - 1)
/**
 ****************************************************************************************
 * @brief Clocks addition with 2 operands
 *
 * @param[in]   clock_a   1st operand value (in BT half-slots)
 * @param[in]   clock_b   2nd operand value (in BT half-slots)
 * @return      result    operation result (in BT half-slots)
 ****************************************************************************************
 */
#define CLK_ADD_2(clock_a, clock_b)     ((uint32_t)(((clock_a) + (clock_b)) & MAC_MAX_CLOCK_TIME))

/**
 ****************************************************************************************
 * @brief Clocks subtraction
 *
 * @param[in]   clock_a   1st operand value (in BT half-slots)
 * @param[in]   clock_b   2nd operand value (in BT half-slots)
 * @return      result    operation result (in BT half-slots)
 ****************************************************************************************
 */
#define CLK_SUB(clock_a, clock_b)     ((uint32_t)(((clock_a) - (clock_b)) & MAC_MAX_CLOCK_TIME))

/**
 ****************************************************************************************
 * @brief Check if clock_a is lower than or equal to clock_b
 *
 * @param[in]   clock_a   Clock A value (in BT half-slots)
 * @param[in]   clock_b   Clock B value (in BT half-slots)
 * @return      result    True: clock_a lower than or equal to clock_b | False: else
 ****************************************************************************************
 */
#define CLK_LOWER_EQ(clock_a, clock_b)      (CLK_SUB(clock_b, clock_a) < (MAC_MAX_CLOCK_TIME >> 1))

/**
 ****************************************************************************************
 * @brief Check if clock_a is greater than clock_b
 *
 * @param[in]   clock_a   Clock A value (in BT half-slots)
 * @param[in]   clock_b   Clock B value (in BT half-slots)
 * @return      result    True: clock_a is greater than clock_b | False: else
 ****************************************************************************************
 */
#define CLK_GREATER_THAN(clock_a, clock_b)    !(CLK_LOWER_EQ(clock_a, clock_b))

/**
 ****************************************************************************************
 * @brief Clocks time difference
 *
 * @param[in]   clock_a   1st operand value (in BT half-slots)
 * @param[in]   clock_b   2nd operand value (in BT half-slots)
 * @return      result    return the time difference from clock A to clock B
 *                           - result < 0  => clock_b is in the past
 *                           - result == 0 => clock_a is equal to clock_b
 *                           - result > 0  => clock_b is in the future
 ****************************************************************************************
 */
#define CLK_DIFF(clock_a, clock_b)     ( (CLK_SUB((clock_b), (clock_a)) > ((MAC_MAX_CLOCK_TIME+1) >> 1)) ?                      \
                          ((int32_t)((-CLK_SUB((clock_a), (clock_b))))) : ((int32_t)((CLK_SUB((clock_b), (clock_a))))) )

static uint32_t wkup_time;
static uint16_t wkup_cnt;
static uint32_t target_hs;
static uint16_t target_hus;
static bool os_tick_updated;

#define TIMER_TASK_STACK_SIZE 256
#define IDLE_TASK_STACK_SIZE 256

static StackType_t timer_task_stack[TIMER_TASK_STACK_SIZE];
static StaticTask_t timer_task_buf;
static StackType_t idle_task_stack[IDLE_TASK_STACK_SIZE];
static StaticTask_t idle_task_buf;
static uint32_t expected_idle_time;
static bool os_tick_updated;
static volatile uint8_t wakeup_status = 0;

const static uint16_t wkup_delay_us_mcu = 1500;

extern void xPortPendSVHandler( void );
static int32_t os_sleep_dur_get(void);
static void mac_timer_match_set(uint32_t match_hs, uint32_t match_hus);
static int32_t timer_time_compare_mcu(uint32_t a,uint32_t b);
static void mac_time_sync(uint32_t *hs, uint16_t *hus);

// void io_toggle_log(uint8_t pin, uint16_t count)
// {
//     io_clr_pin(pin);
//     io_cfg_output(pin);
//     for (size_t i = 0; i < count; i++)
//     {
//         io_set_pin(pin);
//         DELAY_US(1);
//         io_clr_pin(pin);
//         DELAY_US(1);
//     }
// }

static void os_tick_target_update_mcu(uint32_t hs, uint32_t hus)
{
    uint32_t abs_time_hs;
    uint32_t abs_time_hus;
    abs_time_hs = CLK_ADD_2(target_hs, hs);
    abs_time_hus = target_hus + hus;
    if (abs_time_hus > HALF_SLOT_TIME_MAX)
    {
        abs_time_hs = CLK_ADD_2(abs_time_hs, 1);
        abs_time_hus -= HALF_SLOT_TIME_MAX;
    }
    target_hs = abs_time_hs;
    target_hus = abs_time_hus;
}

static uint32_t os_tick_inc_mcu(uint32_t hs, uint16_t hus, bool compensation)
{
    uint32_t count = 0;
    do{
        count += 1;
        os_tick_target_update_mcu(hs, hus);
        mac_timer_match_set(target_hs, target_hus);
        uint32_t current_hs;
        uint16_t current_hus;
        mac_time_sync(&current_hs, &current_hus);
        if(compensation)
        {
            if(!CLK_GREATER_THAN(target_hs, current_hs))
            {
                uint32_t temp_target_hs = current_hs;
                temp_target_hs = CLK_ADD_2(temp_target_hs,1);
                mac_timer_match_set(temp_target_hs, target_hus);
            }
            break;
        }else
        {
            if(CLK_GREATER_THAN(target_hs, current_hs)) break;
        }
    }while(1);
    return count;    
}

static void os_tick_start_mcu(uint32_t hs, uint16_t hus)
{
    mac_time_sync(&target_hs, &target_hus);
    os_tick_inc_mcu(hs, hus, false);
}

static void os_tick_mcu_handler(void)
{
    uint32_t tick_inc = os_tick_inc_mcu(OSTICK_HS_INC(configTICK_RATE_HZ),OSTICK_HUS_INC(configTICK_RATE_HZ),false);
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

// uint32_t timer_time_add(uint32_t a,uint32_t b)
// {
//     return (a + b) & 0xfffffff;
// }

static int32_t timer_time_compare_mcu(uint32_t a,uint32_t b)
{
    uint32_t diff = (a - b) &0xfffffff;
    if(diff&0x8000000)
    {
        return diff|0xf0000000;
    }else
    {
        return diff;
    }
}

static void mac_time_sync(uint32_t *hs, uint16_t *hus)
{
    vPortEnterCritical();
    CLK_SAMP = 0x80000000;
    do{
        *hs = CLK_SAMP;
    }while(*hs & 0x80000000);
    *hus = HALF_SLOT_TIME_MAX - CNT_SAMP;
    vPortExitCritical();
}

static void timer_irq_unmask()
{
    INT_MASK |= 0x40;
}

static void timer_irq_mask()
{
    INT_MASK &= ~0x40;
}

static void timer_irq_clr()
{
    INT_CLR = 0x40;
}

static void mac_timer_match_set(uint32_t match_hs, uint32_t match_hus)
{
    vPortEnterCritical();
    CLK_TARGET_HS = match_hs;
    CLK_TARGET_HUS = HALF_SLOT_TIME_MAX - match_hus;
    timer_irq_clr();
    timer_irq_unmask();
    vPortExitCritical();
}

static void wakeup_compensation_for_mcu(void)
{
    uint32_t current_time_hs;
    uint16_t current_time_hus;
    mac_time_sync(&current_time_hs, &current_time_hus);
    int32_t hs_diff = CLK_DIFF(target_hs, current_time_hs);
    if (hs_diff > 0)
    {
        uint32_t ticks = CEILING((uint32_t)hs_diff*625, 2*1000000/configTICK_RATE_HZ);
        vTaskStepTick(ticks);
        os_tick_inc_mcu(OSTICK_HS_STEP_INC(configTICK_RATE_HZ, ticks),OSTICK_HUS_STEP_INC(configTICK_RATE_HZ, ticks),true);
    }
    else
    {
        mac_timer_match_set(target_hs, target_hus);
    }
}
static volatile uint32_t int_stat = 0;
__attribute((weak)) void ls_24g_restore_in_wkup(void){}
static void WKUP_Handler_For_mcu(void)
{
    while(*(volatile uint32_t*)LS_24G_VERSION_ADDR == 0);
    CNTL = 0x100;
    // INT_MASK = 0x2;
    ls_24g_restore_in_wkup();
    ble_irq_clr_and_enable();
    ble_wkup_status_set(false);
    INT_MASK |= 0x2;
    BLE_WKUP_IRQ_DISABLE();
}
bool ls_mcu_wkup_end(void)
{
    return wakeup_status == 2;
}
void clr_mcu_wkup_status(void)
{
    wakeup_status = 0;
}
__attribute((weak)) void XIP_BANNED_FUNC(PROP_24g_Handler,uint32_t int_stat_24g){}
static void Mac_Handler_For_mcu()
{
    static uint32_t error = 0;
    uint32_t int_stat = INT_STAT;
    if(int_stat & 0x40)
    {
        timer_irq_mask();
        timer_irq_clr();
        os_tick_mcu_handler();
        timer_irq_unmask();
    }
    if(int_stat & 0x2)
    {
        INT_CLR = 0x2;
        uint32_t dur = SLEEP_DUR;
        uint64_t total;
        if(SDK_LSI_USED)
        {
            total = lpcycles_to_hus(dur);
        }else
        {
            total = (uint64_t)dur*1000000/16384;
            error += (uint64_t)dur*1000000%16384;
            total += error/16384;
            error %= 16384;
        }
        TIME_CORR2 = 0x80000000 | total/625;
        TIME_CORR = 624 - (total - total/625*625);
        SLEEP_CNTL |= 0x8;
        INT_MASK |= 0x1;
        INT_CLR = 0x1;
        wakeup_status = 1;
    }
    if(int_stat & 0x1) // wakeup end handle
    {
        INT_CLR = 0x1;
        INT_MASK &= ~0x1;
        mac_time_sync(&wkup_time, &wkup_cnt);
        wakeup_compensation_for_mcu();
        LS_ASSERT(1 == wakeup_status);
        wakeup_status = 2;
    }
    PROP_24g_Handler(int_stat);
    if(int_stat & 0x1)
    {
        portYIELD_FROM_ISR(true);
    }
}

static bool wkup_sleep_interval_enough(uint32_t time,uint16_t cnt)
{
    int diff_time = timer_time_compare_mcu(time,wkup_time);
    int16_t diff_cnt = cnt-wkup_cnt;
    if(diff_time * 625 + diff_cnt > 100)
    {
        return true;
    }else
    {
        return false;
    }
}

bool mac_sleep(void)
{
    uint32_t current;
    uint16_t cnt;
    mac_time_sync(&current, &cnt);
    if(ble_wkup_status_get()||wkup_sleep_interval_enough(current,cnt)==false||INT_MASK&0x1)
    {
        return false;
    }
    int32_t os_sleep_dur = os_sleep_dur_get();
    if(os_sleep_dur != 0)
    {
        if(os_sleep_dur < SLEEP_MINIMUM_HS_CYCLES)
        {
            return false;
        }
        if(SDK_LSI_USED)
        {
            SLEEP_TIME = lsi_freq_update_and_hs_to_lpcycles(os_sleep_dur) - 1;
        }else
        {
            SLEEP_TIME = ((uint64_t)os_sleep_dur << 10)/100 - 1;
        }
        uint16_t cycles = SDK_LSI_USED ? us_to_lpcycles(wkup_delay_us_mcu) : 32768*wkup_delay_us_mcu/1000000;
        WKUP_CNTL = 1<<21 | cycles<<10 | 1;
        SLEEP_CNTL |= 0x7;
        return true;
    }
    return false;
}
__attribute((weak)) void ls24_reg_store(void){}
extern void uart_log_pause(void);
extern void uart_log_resume(void);
static bool ls_mcu_sleep_wakeup_freertos(void)
{
    bool enter_sleep = false;
    if (!peri_status_busy() && !app_event_status_busy())
    {
        vPortEnterCritical();
        uart_log_pause();
        if(mac_sleep())
        {
            ls24_reg_store();
            deep_sleep();
            clr_mcu_wkup_status();
            enter_sleep = true;
        }
        uart_log_resume();
        vPortExitCritical();
        
        if (enter_sleep)
        {
            // while(ble_wkup_status_get());
            while(!ls_mcu_wkup_end());
        }
    }
    return enter_sleep;
}

static int32_t os_sleep_dur_get(void)
{
    eSleepModeStatus eSleepStatus = eTaskConfirmSleepModeStatus();
    int32_t dur = 0;
    switch(eSleepStatus)
    {
    case eStandardSleep:
        dur = OSTICK_HS_STEP_INC(configTICK_RATE_HZ, expected_idle_time-1);
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

void vPortSetupTimerInterrupt( void )
{
    os_tick_start_mcu(OSTICK_HS_INC(configTICK_RATE_HZ), OSTICK_HUS_INC(configTICK_RATE_HZ));
}

void rtos_init(void)
{
    arm_cm_set_int_isr(BLE_WKUP_IRQn,WKUP_Handler_For_mcu);
    arm_cm_set_int_isr(BLE_FIFO_IRQn,Mac_Handler_For_mcu);
    arm_cm_set_int_isr(BLE_CRYPT_IRQn,Mac_Handler_For_mcu);
    arm_cm_set_int_isr(BLE_IRQn,Mac_Handler_For_mcu);
    arm_cm_set_int_isr(BLE_ERR_IRQn,Mac_Handler_For_mcu);
    CNTL = 0x100;
    INT_MASK = 0;
    INT_CLR = 0xffffffff;
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

void vPortSuppressTicksAndSleep( TickType_t xExpectedIdleTime )
{
    expected_idle_time = xExpectedIdleTime;
    if (os_tick_updated)
    {
        bool sleep_status = ls_mcu_sleep_wakeup_freertos();
        if (sleep_status)
        {
            os_tick_updated = false;
        }
    }
}
