#include <stdbool.h>
#include "systick.h"
#include "platform.h"
#include "ls_soc_pinmux.h"

void board_init(void)
{
    sys_init_none();
    pinmux_usb_init();
}

void board_led_write(bool state)
{

}

uint32_t board_millis(void)
{
    return systick_get_value();
}

uint32_t board_button_read(void)
{
    static uint32_t button = 0;
    if (button > 4)
    {
        button = 0;
    }
    else
    {
        button++;
    }
    
    return button;
}