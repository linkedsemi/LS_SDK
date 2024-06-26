#include "ls_hal_dwuart.h"
#include "ls_msp_uart.h"
#include "ls_soc_gpio.h"
#include "platform.h"
#include "log.h"

#define BUFFER_SIZE 255

static uint8_t __length;
static uint8_t test_zone[BUFFER_SIZE];
static DWUART_HandleTypeDef DWUART_Config;

static void uart_init()
{
    LOG_I("dwuart_it init!");
    pinmux_dwuart1_init(PD05, PD07);
    DWUART_Config.DWUARTX = DWUART1;
    DWUART_Config.Init.BaudRate = DWUART_BAUDRATE_921600;
    DWUART_Config.Init.MSBEN = 0;
    DWUART_Config.Init.Parity = DWUART_NOPARITY;
    DWUART_Config.Init.StopBits = DWUART_STOPBITS1;
    DWUART_Config.Init.WordLength = DWUART_BYTESIZE8;
    DWUART_Config.RTOEN = true;
    HAL_DWUART_Init(&DWUART_Config);
}

int main(void)
{
    sys_init_none();
    uart_init();
    HAL_DWUART_Receive_IT(&DWUART_Config, test_zone, BUFFER_SIZE);
    while (1)
    {

    }
}

void HAL_DWUART_RxCpltCallback(DWUART_HandleTypeDef *hdwuart)
{
    __length = BUFFER_SIZE;
    LOG_I("RX OK: %d", BUFFER_SIZE);
    HAL_DWUART_Transmit_IT(&DWUART_Config, test_zone, BUFFER_SIZE);
}

void HAL_DWUART_RxRTOCallback(DWUART_HandleTypeDef *hdwuart, uint8_t length)
{
    __length = length;
    LOG_I("RX RTO: %d", length);
    HAL_DWUART_Transmit_IT(&DWUART_Config, test_zone, length);
}

void HAL_DWUART_TxCpltCallback(DWUART_HandleTypeDef *hdwuart)
{
    LOG_I("TX OK: %d", __length);
    HAL_DWUART_Receive_IT(&DWUART_Config, test_zone, BUFFER_SIZE);
}

void HAL_DWUART_RxErrorCallback(DWUART_HandleTypeDef *hdwuart, uint8_t errorMode)
{
    if (errorMode & DWUART_ERROR_FRAMING)
    {
        LOG_I("Receive Framing Error!");
    }
    if (errorMode & DWUART_ERROR_OVERRUN)
    {
        LOG_I("Receive Overrun!");
    }
    if (errorMode & DWUART_ERROR_PARITY)
    {
        LOG_I("Receive Parity Error!");
    }

    io_cfg_output(PH01);
    while (1)
    {
        io_toggle_pin(PH01);
        DELAY_MS(500);
    }
}