#include <stdint.h>
#include "cpu.h"
#include "platform.h"
#include "sleep.h"
#include "sys_stat.h"
#include "modem_rf_le501x_24g.h"
#include "ls_24g.h"
#include "log.h"

#define LS_24G_VERSION_ADDR 0x50000004
void ls_24g_restore_in_wkup(void)
{
    while(*(volatile uint32_t*)LS_24G_VERSION_ADDR == 0);
    extern void RF_24g_restore(void);
    RF_24g_restore();
    modem_rf_init_24g();
}

extern bool timer_sleep(void);
extern void uart_log_pause(void);
extern void uart_log_resume(void);
extern void ls24_reg_store(void);
extern void clr_24g_wkup_status(void);
extern bool ls_24g_wkup_end(void);

void ls_24g_sleep_wakeup(void)
{
    if (!peri_status_busy() && !app_event_status_busy() && PROP_24G_STATE_ADV != get_cur_prop_24g_state())
    {
        if (PROP_24G_STATE_SCAN == get_cur_prop_24g_state())
        {
            RF_24g_Stop();
        }
        bool enter_sleep = false;
        uint32_t cpu_stat = enter_critical();
        uart_log_pause();
        if(timer_sleep())
        {
            ls24_reg_store();
            deep_sleep();
            clr_24g_wkup_status();
            enter_sleep = true;
        }
        uart_log_resume();
        exit_critical(cpu_stat);
        
        if (enter_sleep)
        {
            while(ble_wkup_status_get());
            while(!ls_24g_wkup_end());
        }
    }
}
