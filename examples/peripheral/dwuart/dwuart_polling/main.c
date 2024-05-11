#include "ls_hal_dwuart.h"
#include "ls_msp_uart.h"
#include "ls_soc_gpio.h"
#include "platform.h"
#include "log.h"

static DWUART_HandleTypeDef DWUART_Config;
static uint8_t test_zone[256];

static void uart_init()
{
    LOG_I("dwuart_polling init!");
    pinmux_dwuart1_init(PD05, PD07);
    DWUART_Config.DWUARTX = DWUART1;
    DWUART_Config.Init.BaudRate     = DWUART_BAUDRATE_921600;
    DWUART_Config.Init.MSBEN        = 0;
    DWUART_Config.Init.Parity       = DWUART_NOPARITY;
    DWUART_Config.Init.StopBits     = DWUART_STOPBITS1;
    DWUART_Config.Init.WordLength   = DWUART_BYTESIZE8;
    HAL_DWUART_Init(&DWUART_Config);
}

static void uart_test()
{
    HAL_DWUART_Receive(&DWUART_Config, test_zone, 10, HAL_MAX_DELAY);
    HAL_DWUART_Transmit(&DWUART_Config, test_zone, 10, HAL_MAX_DELAY);
}

int main(void)
{
    sys_init_none();
    uart_init();
    while (1)
    {
        uart_test();
    }
}