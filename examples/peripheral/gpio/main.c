#include "ls_soc_gpio.h"
#include "platform.h"
#include "sleep.h"
#include <string.h>
#define WKUP_IO PA00
#define LOWPOWER_M0_BTN PB08
#define LOWPOWER_M3_BTN PB09
#define LED1 PA01
#define LED2 PA02

bool lp0_flag=false;
bool lp3_flag=false;

void gpio_init(void)
{
    io_cfg_output(LED1);   //LED1 config output
    io_write_pin(LED1,0);  //LED1 write low level
    io_write_pin(LED1,1);  //LED1 write high level
    io_write_pin(LED1,0);  //LED1 write low level
    io_cfg_output(LED2);   //LED2 config output
    io_write_pin(LED2,1);  //LED2 write high level
}
 
void wkup_io_init(void)
{
    io_cfg_input(WKUP_IO);    //WKUP_IO config input  
    io_pull_write(WKUP_IO, IO_PULL_DOWN);    //WKUP_IO config pull down
    io_exti_config(WKUP_IO,INT_EDGE_RISING);    //WKUP_IO interrupt Rising edge
}

void exti_test(void)
{
    io_cfg_input(LOWPOWER_M0_BTN);    //LOWPOWER_M0_BTN config input  
    io_pull_write(LOWPOWER_M0_BTN, IO_PULL_DOWN);    //LOWPOWER_M0_BTN config pull down
    io_exti_config(LOWPOWER_M0_BTN,INT_EDGE_RISING);    //LOWPOWER_M0_BTN interrupt Rising edge
    io_cfg_input(LOWPOWER_M3_BTN);    //LOWPOWER_M3_BTN config input  
    io_pull_write(LOWPOWER_M3_BTN, IO_PULL_DOWN);    //LOWPOWER_M3_BTN config pull down
    io_exti_config(LOWPOWER_M3_BTN,INT_EDGE_RISING);    //LOWPOWER_M3_BTN interrupt Rising edge
}

int main(void)
{
    sys_init_none();
    gpio_init();
    exti_test();
    wkup_io_init();
    while (1)
    {
        if(lp0_flag)
        {
            low_power_mode_sched();
            lp0_flag=false;
            io_toggle_pin(LED1);
            DELAY_US(500*1000);
            io_toggle_pin(LED1);
            DELAY_US(500*1000);
            io_toggle_pin(LED1);
        }
        if(lp3_flag)
        {
            #if defined(LM3050)
            bool lp2=false;
            enter_deep_sleep_mode_lvl2_lvl3(lp2);
            #else
            struct deep_sleep_wakeup wakeup;
            memset(&wakeup,0,sizeof(wakeup));
            enter_deep_sleep_mode_lvl2_lvl3(&wakeup);
            #endif 
        }
    }
}

void io_exti_callback(uint8_t pin,exti_edge_t edge) 
{
    switch (pin)
    {
    case LOWPOWER_M0_BTN:
        lp0_flag=true;
        break;
    case LOWPOWER_M3_BTN:
        lp3_flag=true;
        break;
    default:
        break;
    }
}
