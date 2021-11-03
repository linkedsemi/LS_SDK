#include "lsuart.h"
#include "platform.h"
#include "io_config.h"
#include <string.h>
#include <stdlib.h>
#include "log.h"
#include "lsdmac.h"

#define BUF_SIZE 256
#define DMA_UART

UART_HandleTypeDef UART_Config; 
DMA_RAM_ATTR uint8_t test_zone_a[BUF_SIZE];

DEF_DMA_CONTROLLER(dmac1_inst,DMAC1);

static void uart_dma_channel_init(void)
{
    DMA_CONTROLLER_INIT(dmac1_inst);
    UART_Config.DMAC_Instance = &dmac1_inst;
    UART_Config.Tx_Env.DMA.DMA_Channel = 0;
    UART_Config.Rx_Env.DMA.DMA_Channel = 1;
}

void HAL_UART_DMA_TxCpltCallback(UART_HandleTypeDef *huart)
{
    // LOG_I("%s",__FUNCTION__);
    HAL_UART_Receive_DMA(&UART_Config,test_zone_a,1);
}

void HAL_UART_DMA_RxCpltCallback(UART_HandleTypeDef *huart)
{
    // LOG_I("%s",__FUNCTION__);
    HAL_UART_Transmit_DMA(&UART_Config,test_zone_a,1);
}

static void uart_rx_dma_test()
{
    HAL_UART_Receive_DMA(&UART_Config,test_zone_a,1);
}

static void uart_init(void)
{
    UART_Config.UARTX = UART1;
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
    uart1_io_init(PB00,PB01);
    uart_init();
    uart_dma_channel_init();
    uart_rx_dma_test();
    while(1)
    {
    }
}




