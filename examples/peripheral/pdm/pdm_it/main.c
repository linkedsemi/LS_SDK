#include "ls_hal_pdm.h"
#include "ls_soc_gpio.h"
#include "ls_hal_uart.h"
#include "platform.h"
#include "log.h"
#include "cpu.h"

#ifdef LE501X
#include "ls_hal_dmac.h"
#else
#include "ls_hal_dmacv2.h"
#endif

#define PDM_CLK_KHZ 1024
#define PDM_SAMPLE_RATE_HZ 16000
#define FRAME_BUF_SIZE 256
DEF_DMA_CONTROLLER(dmac1_inst, DMAC1);
PDM_HandleTypeDef pdm;
DMA_RAM_ATTR uint16_t Buffer0[FRAME_BUF_SIZE];
DMA_RAM_ATTR uint16_t Buffer1[FRAME_BUF_SIZE];

static UART_HandleTypeDef UART_PDM_Config;
volatile static bool Buffer0_flag = false;
volatile static bool Buffer1_flag = false;

static void ls_pdm_uart_init(void)
{
    pinmux_uart1_init(PB00, PB01);
    io_pull_write(PB01, IO_PULL_UP);
    UART_PDM_Config.UARTX = UART1;
    UART_PDM_Config.DMAC_Instance = &dmac1_inst;
    UART_PDM_Config.Tx_Env.DMA.DMA_Channel = 3;
    UART_PDM_Config.Init.BaudRate = UART_BAUDRATE_921600;
    UART_PDM_Config.Init.MSBEN = 0;
    UART_PDM_Config.Init.Parity = UART_NOPARITY;
    UART_PDM_Config.Init.StopBits = UART_STOPBITS1;
    UART_PDM_Config.Init.WordLength = UART_BYTESIZE8;
    HAL_UART_Init(&UART_PDM_Config);
}

void pdm_init()
{
    pinmux_pdm_clk_init(PB09);
    pinmux_pdm_data0_init(PB08);
    pdm.Instance = LSPDM;
    PDM_Init_TypeDef Init =
        {
            .fir = PDM_FIR_COEF_16KHZ,
            .cfg = {
                .clk_ratio = PDM_CLK_RATIO(PDM_CLK_KHZ),
                .sample_rate = PDM_SAMPLE_RATE(PDM_CLK_KHZ, PDM_SAMPLE_RATE_HZ),
                .cap_delay = 30,
                .data_gain = 5,
            },
            .mode = PDM_MODE_Mono,
        };
    HAL_PDM_Init(&pdm, &Init);
}

void pdm_dma_test()
{
    HAL_PDM_Transfer_Config_IT(&pdm, Buffer0, NULL, FRAME_BUF_SIZE);
    HAL_PDM_Start(&pdm);
}

int main()
{
    sys_init_none();
    DMA_CONTROLLER_INIT(dmac1_inst);
    ls_pdm_uart_init();
    pdm_init();
    pdm_dma_test();
    while (1)
    {
        if (Buffer0_flag)
        {
            Buffer0_flag = false;
            HAL_UART_Transmit_DMA(&UART_PDM_Config, (uint8_t *)&Buffer0, FRAME_BUF_SIZE * 2);
        }
        if (Buffer1_flag)
        {
            Buffer1_flag = false;
            HAL_UART_Transmit_DMA(&UART_PDM_Config, (uint8_t *)&Buffer1, FRAME_BUF_SIZE * 2);
        }
    }
}

void HAL_UART_DMA_TxCpltCallback(UART_HandleTypeDef *huart)
{
    LOG_I("uart send Done");
}

void HAL_PDM_CpltCallback(PDM_HandleTypeDef *hpdm)
{
    uint16_t *ptr1 = &Buffer0[FRAME_BUF_SIZE];
    if (((uint32_t)*hpdm->Env.Interrupt.pFrameBuffer) == ((uint32_t)ptr1))
    {
        Buffer0_flag = true;
        HAL_PDM_Transfer_Config_IT(&pdm, Buffer1, NULL, FRAME_BUF_SIZE);
    }
    else
    {
        Buffer1_flag = true;
        HAL_PDM_Transfer_Config_IT(&pdm, Buffer0, NULL, FRAME_BUF_SIZE);
    }
}