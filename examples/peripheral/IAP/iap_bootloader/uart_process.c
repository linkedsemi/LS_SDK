#include "ls_soc_gpio.h"
// #include "io_config.h"
#include "platform.h"
#include <string.h>
#include "ls_hal_uart.h"
#include "systick.h"
#include "uart_process.h"
#include "log.h"

uart_receive_data_t uart_buffer;
uart_receive_data_t uart_cmd;

UART_HandleTypeDef UART_Config;
uint8_t uart_recv_char;

// uint32_t uart_recv_ticker;
// uint8_t uart_rx_flag_step;

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

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    uint16_t len;
    uint8_t rx_char;

    if (huart->UARTX == UART1)
    {
        rx_char = uart_recv_char;
        HAL_UART_Receive_IT(&UART_Config, &uart_recv_char, 1);

        if (uart_buffer.uRxFlag == RX_FLAG_HEAD)
        {
            uart_buffer.uRxSize = 0;
            uart_buffer.uRxFlag = RX_FLAG_RECEIVING;
        }
        else if (uart_buffer.uRxSize >= BUF_SIZE)
        {
            uart_buffer.uRxSize = 0;
            uart_buffer.uRxFlag = RX_FLAG_RECEIVING;
        }
        uart_buffer.aRxBuff[uart_buffer.uRxSize++] = rx_char;

        if (uart_buffer.uRxSize >= 8)
        {
            if (uart_buffer.aRxBuff[0] == SOD)
            {
                uart_buffer.uDataLen = (((uint16_t)uart_buffer.aRxBuff[2]) << 8) + ((uint16_t)uart_buffer.aRxBuff[3]);
                len = uart_buffer.uDataLen + 6 - 1;
                //len = uart_buffer.uRxSize - 1; // last char

                if (uart_buffer.aRxBuff[len] == EOD)
                {
                    uart_buffer.uRxFlag = RX_FLAG_COMPLETION;
                    memcpy(&uart_cmd, &uart_buffer, sizeof(uart_receive_data_t));
                    memset(&uart_buffer, 0x00, sizeof(uart_receive_data_t));
                    // uart_buffer.uRxSize=0;
                    uart_buffer.uRxFlag = RX_FLAG_RECEIVING;
                }
            }
        }
    }
}

void uart_receive_init(void)
{
    memset(&uart_buffer, 0, sizeof(uart_buffer));
    uart_buffer.uRxFlag = RX_FLAG_HEAD;

    HAL_UART_Receive_IT(&UART_Config, &uart_recv_char, 1);
}

void uart_send(uint8_t *data, uint16_t data_len)
{
    if ((NULL == data) || (0 == data_len))
    {
        return;
    }
    #if defined(LE501X)
    HAL_UART_Transmit_IT(&UART_Config, data, data_len);
    #elif defined(LM3050)
    HAL_UART_Transmit(&UART_Config, data, data_len,1000);
    #endif
    
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
    // HAL_UART_Transmit(&UART_Config, data, data_len, 1000);
    HAL_UART_Transmit_IT(&UART_Config, data, data_len);
    DELAY_US(50000);
}
/*
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
*/
