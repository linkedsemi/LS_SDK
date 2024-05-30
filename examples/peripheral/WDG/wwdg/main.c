#include "ls_hal_wwdg.h"
#include "ls_soc_gpio.h"
#include "platform.h"
#include <string.h>
#include "log.h"

#define WWDG_LOAD_VALUE 32768

uint8_t win_cnt = 0;
uint32_t value = 0;

int main(void)
{
    sys_init_none();
    io_cfg_output(PA00);
    io_cfg_output(PA01);

    io_clr_pin(PA00);
    HAL_WWDG_Init(WWDG_LOAD_VALUE,NO_FEEDING_WWDG_2_4);
    while (1)
    {
        HAL_WWDG_Get_Count(&win_cnt,&value);
        if(win_cnt>=2 && value<2000)
        {
            io_toggle_pin(PA01);
            HAL_WWDG_Refresh();
        }
    }
}
