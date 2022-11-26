#include "ls_hal_rtcv2.h"
#include "ls_soc_gpio.h"
#include "platform.h"
#include "log.h"
#include <stdio.h>

static uint32_t beforeSec = 100;

static void printf_rtc_info(void)
{
    LOG_I("rtc_ctrl     = %08x[%08x]", (uint32_t)&RTC->CTRL, RTC->CTRL);
    LOG_I("rtc_calib    = %08x[%08x]", (uint32_t)&RTC->CALIB, RTC->CALIB);
    LOG_I("rtc_set_tgt0 = %08x[%08x]", (uint32_t)&RTC->TIME, RTC->TIME);
    LOG_I("rtc_set_tgt1 = %08x[%08x]", (uint32_t)&RTC->CAL, RTC->CAL);
    LOG_I("rtc_cur0     = %08x[%08x]", (uint32_t)&RTC->CURTIME, RTC->CURTIME);
    LOG_I("rtc_cur1     = %08x[%08x]", (uint32_t)&RTC->CURCAL, RTC->CURCAL);
    LOG_I("rtc_intr     = %08x[%08x]\n", (uint32_t)&RTC->INTR, RTC->INTR);
}

static void rtc_test_calendar_set(void)
{
    calendar_cal_t calendar_cal;
    calendar_cal.year = 22;
    calendar_cal.mon = 11;
    calendar_cal.week = 4;
    calendar_time_t calendar_time;
    calendar_time.date = 10;
    calendar_time.hour = 22;
    calendar_time.min = 59;
    calendar_time.sec = 50;
    HAL_RTC_CalendarSet(&calendar_cal, &calendar_time);
    LOG_I("set calendar:\n");
    printf_rtc_info();
    LOG_I("rtc test, calendar set done\n\n");
}

static void rtc_test_calendar_get(void)
{
    calendar_cal_t calendar_cal;
    calendar_time_t calendar_time;
    HAL_RTC_CalendarGet(&calendar_cal, &calendar_time);
    if (calendar_time.sec == beforeSec)
        return;
    beforeSec = calendar_time.sec;
    LOG_I("%02d/%02d/%02d, %02d:%02d:%02d, week=%d", calendar_cal.year,
          calendar_cal.mon, calendar_time.date, calendar_time.hour,
          calendar_time.min, calendar_time.sec, calendar_cal.week);
    printf_rtc_info();
}

static void rtc_test_alarm_set(void)
{
    calendar_cal_t calendar_cal;
    calendar_cal.year = 22;
    calendar_cal.mon = 11;
    calendar_cal.week = 4;
    calendar_time_t calendar_time;
    calendar_time.date = 10;
    calendar_time.hour = 23;
    calendar_time.min = 0;
    calendar_time.sec = 0;
    HAL_RTC_AlarmSet(&calendar_cal, &calendar_time);
    LOG_I("set alarm:\n");
    printf_rtc_info();
    LOG_I("rtc test, alarm set done\n\n");
}

int main(void)
{
    sys_init_none();
    DELAY_US(2000 * 1000);// Delay 2s : LSE starts up for a long time and waits for stability!!!
    HAL_RTC_Init();
    // HAL_RTC_Cycle_Set(SDK_LCLK_HZ, 0, false); /* If you want to modify the modification cycle or calibration */
    rtc_test_calendar_set();
    rtc_test_alarm_set();
    while(1)
    {
        rtc_test_calendar_get();
    }
}

void HAL_RTC_alarm_callback(void)
{
    LOG_I("====== %s ======", __func__);
    printf_rtc_info();
    LOG_I("================================\n");
}
