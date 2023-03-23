#include <stdbool.h>
#include "systick.h"
#include "platform.h"
#include "ls_soc_pinmux.h"
#include "ls_soc_gpio.h"

#define LED_BLUE PB14

void bsp_init(void)
{
    sys_init_none();

    pinmux_usb_init(false);

    io_cfg_output(LED_BLUE);
    io_set_pin(LED_BLUE);
}

uint32_t bsp_millis(void)
{
    return systick_get_value();
}

void bsp_blue_led_write(bool state)
{
    if (state)
    {
        io_clr_pin(LED_BLUE);
    }
    else
    {
        io_set_pin(LED_BLUE);
    }
}
