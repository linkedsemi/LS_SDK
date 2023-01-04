#include "sw_timer_int.h"
#include "platform.h"
#include "le501x.h"
#include "reg_rcc.h"
#include "sleep.h"
#include "sdk_config.h"

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
#define CLK_TARGET (*(volatile uint32_t *)0x500000f0)
#define CLK_SAMP (*(volatile uint32_t *)0x500000f8)
#define CNT_SAMP (*(volatile uint32_t *)0x500000fc)
static void (*timer_isr)();
static sw_timer_time_t wkup_time;
static uint16_t wkup_cnt;
sw_timer_time_t timer_time_add(sw_timer_time_t a,sw_timer_time_t b)
{
    return (a + b) & 0xfffffff;
}

int timer_time_compare(sw_timer_time_t a,sw_timer_time_t b)
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

sw_timer_time_t timer_time_get()
{
    CLK_SAMP = 0x80000000;
    sw_timer_time_t result;
    do{
        result = CLK_SAMP;
    }while(result & 0x80000000);
    return result;
}

void timer_match_set(sw_timer_time_t match)
{
    CLK_TARGET = match;
}

void timer_irq_unmask()
{
    INT_MASK |= 0x40;
}

void timer_irq_mask()
{
    INT_MASK &= ~0x40;
}

void timer_irq_clr()
{
    INT_CLR = 0x40;
}

__attribute((weak)) void ls_24g_restore_in_wkup(void){}

static void WKUP_Handler_For_SW_Timer()
{
    CNTL = 0x100;
    INT_MASK = 0x2;
    ls_24g_restore_in_wkup();
    ble_irq_clr_and_enable();
    ble_wkup_status_set(false);
    BLE_WKUP_IRQ_DISABLE();
}
__attribute((weak)) void XIP_BANNED_FUNC(PROP_24g_Handler,uint32_t int_stat_24g){}

static void Handler_For_SW_Timer()
{
    static uint32_t error = 0;
    uint32_t int_stat = INT_STAT;
    if(int_stat & 0x40)
    {
        timer_isr();
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
    }
    if(int_stat & 0x1)
    {
        INT_CLR = 0x1;
        INT_MASK &= ~0x1;
        wkup_time = timer_time_get();
        wkup_cnt = 624 - CNT_SAMP;
        timer_isr();
    }
    PROP_24g_Handler(int_stat);
}

static void mac_init_for_sw_timer()
{
    arm_cm_set_int_isr(BLE_WKUP_IRQn,WKUP_Handler_For_SW_Timer);
    arm_cm_set_int_isr(BLE_FIFO_IRQn,Handler_For_SW_Timer);
    arm_cm_set_int_isr(BLE_CRYPT_IRQn,Handler_For_SW_Timer);
    arm_cm_set_int_isr(BLE_IRQn,Handler_For_SW_Timer);
    arm_cm_set_int_isr(BLE_ERR_IRQn,Handler_For_SW_Timer);
    CNTL = 0x100;
    INT_MASK = 0;
    INT_CLR = 0xffffffff;
}

void timer_setup(void (*isr)())
{
    timer_isr = isr;
    mac_init_for_sw_timer();
}

static bool wkup_sleep_interval_enough(sw_timer_time_t time,uint16_t cnt)
{
    int diff_time = timer_time_compare(time,wkup_time);
    int16_t diff_cnt = cnt-wkup_cnt;
    if(diff_time * 625 + diff_cnt > 100)
    {
        return true;
    }else
    {
        return false;
    }
}

bool timer_sleep()
{
    sw_timer_time_t current = timer_time_get();
    uint16_t cnt = 624 - CNT_SAMP;
    if(ble_wkup_status_get()||wkup_sleep_interval_enough(current,cnt)==false||INT_MASK&0x1)
    {
        return false;
    }
    struct sw_timer_env *timer = sw_timer_list_pick();
    if(timer)
    {
        int sleep_time = timer_time_compare(timer->target,current);
        if(sleep_time < SLEEP_MINIMUM_HS_CYCLES)
        {
            return false;
        }
        if(SDK_LSI_USED)
        {
            SLEEP_TIME = lsi_freq_update_and_hs_to_lpcycles(sleep_time) - 1;
        }else
        {
            SLEEP_TIME = ((uint64_t)sleep_time << 10)/100 - 1;
        }
    }
    uint16_t cycles = SDK_LSI_USED ? us_to_lpcycles(wkup_delay_us) : 32768*wkup_delay_us/1000000;
    WKUP_CNTL = 1<<21 | cycles<<10 | 1;
    SLEEP_CNTL |= 0x7;
    return true;
}
