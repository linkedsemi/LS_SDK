#include "ls_hal_ps2h.h"
#include "ls_msp_ps2h.h"
#include "ls_soc_gpio.h"
#include "ls_soc_pinmux.h"
#include "platform.h"
#include "log.h"

static PS2H_HandleTypeDef PS2H_Config;
static uint8_t test_zone[16] = {0};
static void led_breathe();

static void ps2h_init(void)
{
    pinmux_ps2h1_init(PH06, PH07);
    LOG_I("ps2_polling init started");
    PS2H_Param param;
    param.err_mode             = PS2_TO_IDLE_SATE;
    param.flt_num              = PS2_FLTNUM_5CLK;
    param.tx_mode              = PS2_TXMODE_WAIT_RXEND;
    PS2H_Config.PS2HX          = PS2H1;
    HAL_PS2H_Init(&PS2H_Config, &param);
}

static void ps2h_test(void)
{
    HAL_StatusTypeDef status = HAL_PS2H_Receive(&PS2H_Config, test_zone, 1, HAL_MAX_DELAY);
    if (status != HAL_OK)
    {
        led_breathe();
    }
    LOG_I("receive data:  0x%x", test_zone[0]);
    status = HAL_PS2H_Transmit(&PS2H_Config, test_zone, 1);
    if (status != HAL_OK)
    {
        led_breathe();
    }
}

int main()
{
    sys_init_none();
    ps2h_init();
    while (1)
    {
        ps2h_test();
    }
}

static void led_breathe()
{
    io_cfg_output(PH04);
    while (1)
    {
        io_toggle_pin(PH04);
        DELAY_MS(500);
    }
}