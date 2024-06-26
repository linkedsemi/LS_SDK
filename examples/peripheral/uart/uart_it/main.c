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

static void uart_rx_test()
{
#if (RTO_OPEN == 1)
    HAL_UART_ReceiveToIdle_IT(&UART_Config, test_zone_a, BUF_SIZE);
#else
    HAL_UART_Receive_IT(&UART_Config, test_zone_a, 1);
#endif
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->UARTX == UART1)
    {
        uart_rx_test();
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->UARTX == UART1)
    {
        HAL_UART_Transmit_IT(&UART_Config,test_zone_a,1);       
    }
}

void HAL_UART_RxToIdleCpltCallback(UART_HandleTypeDef *huart, uint16_t loseLength)
{
    uint8_t length = BUF_SIZE - loseLength;
    HAL_UART_Transmit_IT(&UART_Config,test_zone_a,length);
}

static void uart_init(void)
{
    UART_Config.UARTX = UART1;
    UART_Config.Init.BaudRate = UART_BAUDRATE_115200;
    UART_Config.RTOValue = RTOvalue; 
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
    uart_rx_test();
    while(1)
    {
    }
}




