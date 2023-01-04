#define LOG_TAG "RTC_DEMO"
#include "ls_hal_rtc.h"
#include "le501x.h"
#include "platform.h"
#include "ls_soc_gpio.h"
#include <string.h>
#include "sleep.h"
#include "ls_soc_gpio.h"
#include "reg_syscfg.h"
#include "log.h"

#define RTC_CALENDAR_TEST 1
#define RTC_WAKEUP_LP0_TEST 2
#define RTC_WAKEUP_LP2_TEST 3

#define RTC_TEST_CASE 1

#if SDK_LSI_USED
#define RTC_CLK_SOURCE RTC_CKSEL_LSI
#else
#define RTC_CLK_SOURCE RTC_CKSEL_LSE
#endif

#if RTC_TEST_CASE == RTC_CALENDAR_TEST
static calendar_time_t calendar_time;
static calendar_cal_t calendar_cal;
// set initial value of calendar to 2024/2/28 23:59:57 week = 3
static void rtc_test()
{
    calendar_cal.year = 24;
    calendar_cal.mon = 2;
    calendar_cal.date = 28;
    calendar_time.hour = 23;
    calendar_time.min = 59;
    calendar_time.sec = 55;
    calendar_time.week = 3; 
    RTC_CalendarSet(&calendar_cal,&calendar_time);
} 

int main()
{
    sys_init_none();
    HAL_RTC_Init(RTC_CLK_SOURCE);
    rtc_test();
    while(1)
    {
        RTC_CalendarGet(&calendar_cal,&calendar_time);
        LOG_I("%d : %d : %d  %d/%d/%d week = %d", calendar_time.hour,
                                                  calendar_time.min,
                                                  calendar_time.sec,
                                                  calendar_cal.year,
                                                  calendar_cal.mon,
                                                  calendar_cal.date,
                                                  calendar_time.week);
        DELAY_US(1000000);
    }

}

#elif RTC_TEST_CASE == RTC_WAKEUP_LP0_TEST

#define WAKEUP_MS 1000
#define LED_IO PA01
static volatile bool sleep_flag = false;
void rtc_wkup_callback(void)
{
    io_cfg_output(LED_IO);
    io_set_pin(LED_IO);
    DELAY_US(200*1000);
    io_clr_pin(LED_IO);
    io_cfg_input(LED_IO);
    io_cfg_disable(LED_IO);
    sleep_flag = !sleep_flag;
}

int main(void)
{
    sys_init_none();
    HAL_RTC_Init(RTC_CLK_SOURCE);
    RTC_wkuptime_set(WAKEUP_MS);
    while(1)
    {
        if (sleep_flag)
        {
            low_power_mode_sched();
        }
    }
}
#elif RTC_TEST_CASE == RTC_WAKEUP_LP2_TEST
#if SDK_LSI_USED == 0
#error "RTC under LP2 can't be configured with LSE!!!"
#endif
#define WAKEUP_MS 1000
#define SLEEP_CNT_MAX 10
#define LED_IO PA01

static calendar_time_t calendar_time;
static calendar_cal_t calendar_cal;
static void calendar_init(void)
{
    calendar_cal.year = 24;
    calendar_cal.mon = 2;
    calendar_cal.date = 28;
    calendar_time.hour = 23;
    calendar_time.min = 59;
    calendar_time.sec = 57;
    calendar_time.week = 3; 
    RTC_CalendarSet(&calendar_cal,&calendar_time);
} 

static void rtc_lp2_test(void)
{
    RTC_CalendarGet(&calendar_cal,&calendar_time);
    LOG_I("%d : %d : %d  %d/%d/%d week = %d",calendar_time.hour,calendar_time.min,calendar_time.sec,calendar_cal.year,calendar_cal.mon,calendar_cal.date,calendar_time.week);

    uint8_t wkup_source = get_wakeup_source();
    if ((RTC_WKUP & wkup_source) != 0)
    {
        io_cfg_output(LED_IO);
        io_set_pin(LED_IO);
        DELAY_US(200*1000); // toggle LED IO and delay
        io_clr_pin(LED_IO);
        io_cfg_input(LED_IO);
        io_cfg_disable(LED_IO);

        SYSCFG->BKD[7]++; // record times of entering sleep
    }
    else
    {
        RTC_wkuptime_set(WAKEUP_MS);
        calendar_init(); // set calender at first time
        SYSCFG->BKD[7] = 0;
    }

    if (SYSCFG->BKD[7] == SLEEP_CNT_MAX)
    {
        LOG_I("RTC LP2 calendar test end here~");
        while (1);
    }   

    struct deep_sleep_wakeup wakeup;
    memset(&wakeup,0,sizeof(wakeup));
    wakeup.rtc = 1;
    enter_deep_sleep_mode_lvl2_lvl3(&wakeup);
}

int main(void)
{
    sys_init_none();
    HAL_RTC_Init(RTC_CLK_SOURCE);
    rtc_lp2_test();
    while (1);
}
#endif
