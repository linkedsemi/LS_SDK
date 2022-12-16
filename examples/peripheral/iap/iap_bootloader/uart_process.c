#include "ls_soc_gpio.h"
// #include "io_config.h"
#include "platform.h"
#include <string.h>
#include "ls_hal_uart.h"
#include "systick.h"
#include "uart_process.h"

UART_HandleTypeDef UART_Config;

uint8_t uart_buffer[BUF_SIZE];
uint16_t uart_buffer_len = 0;

uint8_t uart_recv_char;

void uart_var_init(void)
{
    memset(uart_buffer, 0, BUF_SIZE);
    uart_buffer_len = 0;
}
void uart_init(uint8_t txd, uint8_t rxd)
{
    // pinmux_uart1_init(PA09,PA10);
    // io_pull_write(PA10, IO_PULL_UP);

    pinmux_uart1_init(txd, rxd);
    io_pull_write(rxd, IO_PULL_UP);

    UART_Config.UARTX = UART1;
    UART_Config.Init.BaudRate = UART_BAUDRATE_115200;
    UART_Config.Init.MSBEN = 0;
    UART_Config.Init.Parity = UART_NOPARITY;
    UART_Config.Init.StopBits = UART_STOPBITS1;
    UART_Config.Init.WordLength = UART_BYTESIZE8;
    HAL_UART_Init(&UART_Config);
}

void uart_rx(void)
{
    HAL_UART_Receive_IT(&UART_Config, &uart_recv_char, 1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (uart_buffer_len >= BUF_SIZE)
    {
        uart_var_init();
    }
    uart_buffer[uart_buffer_len++] = uart_recv_char;
    uart_rx();
}

void uart_receive_init(void)
{
    uart_var_init();
    uart_rx();
}
void uart_send_receive_data(void)
{
    uart_send(uart_buffer, uart_buffer_len);
}
void uart_send(uint8_t *data, uint16_t data_len)
{
    if ((NULL == data) || (0 == data_len))
    {
        return;
    }
    HAL_UART_Transmit(&UART_Config, data, data_len, 1000);
}
void uart_send_string(uint8_t *str)
{
    uint8_t *data = str;
    uint16_t data_len = 0;
    while (*str != '\0')
    {
        str++;
        data_len++;
    }
    HAL_UART_Transmit(&UART_Config, data, data_len, 1000);
}

int32_t ticker_out(uint32_t *ticker, uint32_t compare_value)
{
    uint32_t ticks = 0;

    ticks = systick_get_value();

    if (0 == compare_value)
    {
        *ticker = ticks;
        return 1;
    }
    else
    {
        if (ticks >= (*ticker))
        {
            ticks = ticks - (*ticker);
        }
        else
        {
            ticks = (0xFFFFFFFF - (*ticker)) + ticks;
        }

        if (ticks >= compare_value)
        {
            return 1;
        }
    }

    return 0;
}
