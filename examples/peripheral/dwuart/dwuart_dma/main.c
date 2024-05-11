#include "ls_hal_dwuart.h"
#include "ls_hal_dmacv3.h"
#include "ls_msp_uart.h"
#include "ls_soc_gpio.h"
#include "platform.h"
#include "log.h"

#define BUFFER_SIZE 8

static DEF_DMA_CONTROLLER(dmac1_inst,DMAC2)
static DWUART_HandleTypeDef DWUART_Config;
static  uint8_t test_zone[BUFFER_SIZE];
static volatile bool rx_flag = true;
static volatile bool tx_flag = false;

static void uart_init()
{
    LOG_I("dwuart_dma init!");
    pinmux_dwuart1_init(PD05, PD07);
    DWUART_Config.DWUARTX = DWUART1;
    DWUART_Config.Init.BaudRate = DWUART_BAUDRATE_115200;
    DWUART_Config.Init.MSBEN = 0;
    DWUART_Config.Init.Parity = DWUART_NOPARITY;
    DWUART_Config.Init.StopBits = DWUART_STOPBITS1;
    DWUART_Config.Init.WordLength = DWUART_BYTESIZE8;
    DWUART_Config.RTOEN = false;
    HAL_DWUART_Init(&DWUART_Config);
}

static void uart_dma_init()
{
    HAL_DMA_Controller_Init(&dmac1_inst);
    DWUART_Config.DMAC_Instance = &dmac1_inst;
    DWUART_Config.Tx_Env.DMA.DMA_Channel = 2;
    DWUART_Config.Rx_Env.DMA.DMA_Channel = 0;
}

int main(void)
{
    sys_init_none();
    uart_dma_init();
    uart_init();
    while (1)
    {
        if (rx_flag)
        {
            rx_flag = false;
            HAL_DWUART_Receive_DMA(&DWUART_Config, test_zone, BUFFER_SIZE);
        }
        if (tx_flag)
        {
            tx_flag = false;
            HAL_DWUART_Transmit_DMA(&DWUART_Config, test_zone, BUFFER_SIZE);
        }
    }
}

void HAL_DWUART_DMA_RxCpltCallback(DWUART_HandleTypeDef *hdwuart)
{
    tx_flag = true;
    LOG_I("rx successful, length : %d" , BUFFER_SIZE);
}

void HAL_DWUART_DMA_TxCpltCallback(DWUART_HandleTypeDef *hdwuart)
{
    rx_flag = true;
    LOG_I("tx successful, length : %d" , BUFFER_SIZE);
}