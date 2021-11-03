#include "io_config.h"
#include "platform.h"
#include <string.h>

void gpio_init(void)
{
    io_cfg_output(PB09);   //PB09 config output
    io_write_pin(PB09,0);  //PB09 write low level
    io_cfg_output(PB10);   //PB10 config output
    io_write_pin(PB10,1);  //PB10 write high level
}
 
void exti_test(void)
{
    io_cfg_input(PB11);    //PB11 config input
    io_pull_write(PB11, IO_PULL_UP);    //PB11 config pullup
    io_exti_config(PB11,INT_EDGE_FALLING);    //PB11 interrupt falling edge
    io_exti_enable(PB11,true);    //PB11 interrupt enable
}
int main(void)
{
    sys_init_none();
    gpio_init();
    exti_test();
    while (1)
    {
        io_write_pin(PB09,io_read_pin(PB11));
    }
}

void io_exti_callback(uint8_t pin) 
{
    switch (pin)
    {
    case PB11:
        // do something
        io_toggle_pin(PB10);  
        break;
    default:
        break;
    }
}
