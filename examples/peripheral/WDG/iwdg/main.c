#include "ls_hal_iwdg.h" 
#include "ls_soc_gpio.h"
#include "platform.h"
#include <string.h>

#define IWDG_LOAD_VALUE 32768

int main(void)
{
    sys_init_none();
    io_cfg_output(PA00);
    io_cfg_output(PA01);

    io_clr_pin(PA00);
    HAL_IWDG_Init(IWDG_LOAD_VALUE); 
    while (1)
    {
        DELAY_US(1000000);
        io_toggle_pin(PA01);
        HAL_IWDG_Refresh();
    }
}
