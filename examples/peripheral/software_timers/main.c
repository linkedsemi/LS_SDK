#include "platform.h"
#include "ls_soc_gpio.h"
#include <string.h>
#include <stdlib.h>
#include "log.h"
#include "sw_timer.h"
#include "sleep.h"
#define TIMER0_PERIOD_MS 50
#define TIMER1_PERIOD_MS 70
struct sw_timer_env timer[2];
bool timer_cb(void *param)
{
    if(param == (void *)&timer[0])
    {
        io_toggle_pin(PA00);
        return true;
    }else
    {
        io_toggle_pin(PA01);
        return true;
    }
}

int main()
{
    sys_init_none();
    io_cfg_output(PA00);
    io_cfg_output(PA01);
    sw_timer_callback_set(&timer[0],timer_cb,&timer[0]);
    sw_timer_period_set(&timer[0],MS_2_PERIOD(TIMER0_PERIOD_MS));
    sw_timer_start(&timer[0]);
    sw_timer_callback_set(&timer[1],timer_cb,&timer[1]);
    sw_timer_period_set(&timer[1],MS_2_PERIOD(TIMER1_PERIOD_MS));
    sw_timer_start(&timer[1]);
    while(1)
    {
        low_power_mode_sched();
    }
}




