#include "ls_hal_uart.h"
#include "platform.h"
#include "ls_soc_gpio.h"
#include <string.h>
#include <stdlib.h>
#include "log.h"

#define BUF_SIZE 256
#define RTOvalue 0x05;

UART_HandleTypeDef UART_Config; 
uint8_t test_zone_a[BUF_SIZE];

static void uart_test()
{
#if RTO_OPEN
    static uint16_t length = 0;
    HAL_UART_ReceiveToIdle(&UART_Config, test_zone_a, BUF_SIZE, &length, HAL_MAX_DELAY); // 2、Receive data in RTO mode
    DELAY_US(1000 * 40);
    HAL_UART_Transmit(&UART_Config, test_zone_a, length, HAL_MAX_DELAY);
#else
    HAL_UART_Receive(&UART_Config, test_zone_a, 5, 10000);
    HAL_UART_Transmit(&UART_Config, test_zone_a, 5, 1000);
#endif
}

static void uart_init(void)
{
    UART_Config.UARTX = UART1;
    UART_Config.RTOValue = RTOvalue;      // Configuring the Timeout Period
    UART_Config.Init.BaudRate = UART_BAUDRATE_115200;
    UART_Config.Init.MSBEN = 0;
    UART_Config.Init.Parity = UART_NOPARITY;
    UART_Config.Init.StopBits = UART_STOPBITS1;
    UART_Config.Init.WordLength = UART_BYTESIZE8;
    HAL_UART_Init(&UART_Config);
}

int main()
{
    sys_init_none();
    pinmux_uart1_init(PB00,PB01);
    io_pull_write(PB01, IO_PULL_UP);
    uart_init();
    while(1)
    {
        uart_test();
    }
}




