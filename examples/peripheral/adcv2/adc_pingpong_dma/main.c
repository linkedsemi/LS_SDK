#include "platform.h"
#include "ls_soc_gpio.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ls_hal_adcv2.h"
#include "log.h"
#include "ls_hal_uart.h"
#ifdef DMACV3
#include "ls_hal_dmacv3.h"


DEF_DMA_CONTROLLER(dmac1_inst, DMAC1)

static UART_HandleTypeDef UART_ADC_Config;

static void LS_ADC_Uart_Init(void)
{

    pinmux_uart1_init(PH08, PH09);
    io_pull_write(PH09, IO_PULL_UP);
    UART_ADC_Config.UARTX = UART1;
    UART_ADC_Config.DMAC_Instance = &dmac1_inst;
    UART_ADC_Config.Tx_Env.DMA.DMA_Channel = 3;
    UART_ADC_Config.Init.BaudRate = UART_BAUDRATE_921600;
    UART_ADC_Config.Init.MSBEN = 0;
    UART_ADC_Config.Init.Parity = UART_NOPARITY;
    UART_ADC_Config.Init.StopBits = UART_STOPBITS1;
    UART_ADC_Config.Init.WordLength = UART_BYTESIZE8;
    HAL_UART_Init(&UART_ADC_Config);
}

void HAL_UART_DMA_TxCpltCallback(UART_HandleTypeDef *huart)
{
    // LOG_I("uart send Done");
}

#define BUF_SIZE 2
char log_buf[256];

DMA_RAM_ATTR uint16_t Buf0[BUF_SIZE];
DMA_RAM_ATTR uint16_t Buf1[BUF_SIZE];

static struct ADC_PingPong_Bufptr adc_data_receive;
static bool buf0_flag = false;
static bool buf1_flag = false;

static ADC_HandleTypeDef ADCx_Hdl;

void ADC_DMA_PINGPONG_Test()
{
    ADCx_Hdl.DMAC_Instance = &dmac1_inst;
    ADCx_Hdl.Env.DMA.DMA_Channel = 0; /// Configure the DMA channel to receive PDM data
    adc_data_receive.Bufptr[0] = Buf0;
    adc_data_receive.Bufptr[1] = Buf1;
    HAL_ADC_PingPong_Transfer_Config_DMA(&ADCx_Hdl, &adc_data_receive, BUF_SIZE); // DMA receives ADC data in Ping-Pong mode
}

void Error_Handler(void)
{
    while (1)
    {
        ;
    }
}

void ADC_Init_Func(void)
{
    pinmux_adc1_in5_init(); // PA14

    DMA_CONTROLLER_INIT(dmac1_inst);
    ADCx_Hdl.Env.DMA.DMA_Channel = 0;
    ADCx_Hdl.DMAC_Instance = &dmac1_inst;

    ADCx_Hdl.Instance = LSADC1;
    ADCx_Hdl.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    ADCx_Hdl.Init.ContinuousConvMode = DISABLE;
    ADCx_Hdl.Init.NbrOfConversion = 0;
    ADCx_Hdl.Init.DiscontinuousConvMode = DISABLE;
    ADCx_Hdl.Init.NbrOfDiscConversion = 0;
    ADCx_Hdl.Init.TrigType = ADC_SOFTWARE_TRIGT;
    ADCx_Hdl.Init.Vref = ADC_VREF_INSIDE;
    ADCx_Hdl.Init.AdcDriveType = BINBUF_DIRECT_DRIVE_ADC;
    ADCx_Hdl.Init.AdcCkDiv = 256;
    if (HAL_ADC_Init(&ADCx_Hdl) != HAL_OK)
    {
        LOG_I("HAL_ADC_Init ERROR!");
        Error_Handler();
    }

    ADC_LoopConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_5;
    sConfig.Rank = ADC_LOOP_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;
    sConfig.LoopClk = ADC_CH_CLOCK_DIV8;
    sConfig.NbrOfConversion = 4;
    sConfig.CapIntv = 0xFFFF;
    if (HAL_ADC_LoopConfigChannel(&ADCx_Hdl, &sConfig) != HAL_OK)
    {
        LOG_I("HAL_ADC_ConfigChannel ERROR!");
        Error_Handler();
    }
}

void HAL_ADC_DMA_CpltCallback(ADC_HandleTypeDef *hadc, uint8_t ch_idx, uint8_t buf_idx)
{
    if (buf_idx)
    {
        buf1_flag = true;
    }
    else
    {
        buf0_flag = true;
    }
}

int main(void)
{
    uint32_t len = 0;

    sys_init_none();
    LOG_I("ADC PINGPONG Test Start...");

    ADC_Init_Func();
    LS_ADC_Uart_Init();
    ADC_DMA_PINGPONG_Test();

    while (1)
    {
        if (buf0_flag)
        {
            buf0_flag = false;
            len = sprintf(log_buf, "buf0:%d\t%d\tbuf1:%d\t%d\n", Buf0[0], Buf0[1], Buf1[0], Buf1[1]);
            HAL_UART_Transmit_DMA(&UART_ADC_Config, (uint8_t *)log_buf, len);

            // HAL_UART_Transmit_DMA(&UART_ADC_Config,(uint8_t *)&Buf0,BUF_SIZE*2);
        }

        if (buf1_flag)
        {
            buf1_flag = false;
            len = sprintf(log_buf, "buf1:%d\t%d\tbuf0:%d\t%d\n", Buf1[0], Buf1[1], Buf0[0], Buf0[1]);
            HAL_UART_Transmit_DMA(&UART_ADC_Config, (uint8_t *)log_buf, len);

            // HAL_UART_Transmit_DMA(&UART_ADC_Config, (uint8_t *)&Buf1,BUF_SIZE*2);
        }
    }
}
#endif
