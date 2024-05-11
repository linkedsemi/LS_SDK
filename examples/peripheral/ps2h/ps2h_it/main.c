#include "ls_hal_ps2h.h"
#include "ls_msp_ps2h.h"
#include "ls_soc_gpio.h"
#include "ls_soc_pinmux.h"
#include "platform.h"
#include "log.h"

static uint8_t test_zone[16] = {0};
static PS2H_HandleTypeDef PS2H_Config;
static volatile bool tx_flag = false;
static volatile bool rx_flag = true;

static void ps2h_init(void)
{
    pinmux_ps2h1_init(PH06, PH07);
    PS2H_Param param;
    param.err_mode             = PS2_TO_IDLE_SATE;
    param.flt_num              = PS2_FLTNUM_5CLK;
    param.tx_mode              = PS2_TXMODE_WAIT_RXEND;
    PS2H_Config.PS2HX          = PS2H1;
    HAL_PS2H_Init(&PS2H_Config, &param);
}

int main()
{
    sys_init_none();
    ps2h_init();
    while (1)
    {
        if (rx_flag)
        {
            rx_flag = false;
            HAL_PS2H_Receive_IT(&PS2H_Config, test_zone, 1);
        }
        if (tx_flag)
        {
            tx_flag = false;
            HAL_PS2H_Transmit_IT(&PS2H_Config, test_zone, 1);
        }
    }
}

static void led_breathe(uint8_t led_pin)
{
    io_cfg_output(led_pin);
    while (1)
    {
        io_toggle_pin(led_pin);
        DELAY_MS(500);
    }
}

void HAL_PS2H_RxCpltCallback(PS2H_HandleTypeDef *hps2h)
{
    LOG_I("receive data:  0x%x", test_zone[0]);
    tx_flag = true;
}

void HAL_PS2H_TxCpltCallback(PS2H_HandleTypeDef *hps2h)
{
    LOG_I("transmit successful!");
    rx_flag = true;
}

void HAL_PS2H_TxErrorCallBack(PS2H_HandleTypeDef *hps2h)
{
    LOG_I("An error (ack bit) was found during transmit!");
    led_breathe(PH04);
}

void HAL_PS2H_RxErrorCallBack(PS2H_HandleTypeDef *hps2h, RxErrorMode errmode)
{
    switch (errmode)
    {
    case PS2_ERROR_START_BIT:
        LOG_I("program stop: An START_BIT error was found during receiving!");
        break;
    case PS2_ERROR_STOP_BIT:
        LOG_I("program stop: An STOP_BIT error was found during receiving!");
        break;
    case PS2_ERROR_PARITY_BIT:
        LOG_I("program stop: An PARITY_BIT error was found during receiving!");
        break;
    case PS2_ERROR_RXFIFO_OVERRUN:
        LOG_I("program continu: An RXFIFO_OVERRUN error was found during receiving!");
        return;
    }
    led_breathe(PH04);
}