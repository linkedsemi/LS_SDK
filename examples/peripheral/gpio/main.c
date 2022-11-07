#include "ls_soc_gpio.h"
#include "platform.h"
#include <string.h>

void gpio_init(void)
{
    io_cfg_output(PB08);   //PB08 config output
    io_write_pin(PB08,1);  //PB08 write low level
    io_cfg_output(PB09);   //PB09 config output
    io_write_pin(PB09,1);  //PB09 write high level
}
 
void exti_test(void)
{
    io_cfg_input(PB01);    //PB01 config input  pb07
    io_pull_write(PB01, IO_PULL_UP);    //PB01 config pullup
    io_exti_config(PB01,INT_EDGE_FALLING);    //PB01 interrupt falling edge
}

int main(void)
{
    sys_init_none();
    gpio_init();
    exti_test();
    while (1)
    {
        io_write_pin(PB08,io_read_pin(PB01));
    }
}

void io_exti_callback(uint8_t pin,exti_edge_t edge) 
{
    switch (pin)
    {
    case PB01:
        // do something
        io_toggle_pin(PB09);  
        io_exti_config(PB01,INT_EDGE_DISABLE);
        break;
    default:
        break;
    }
}
