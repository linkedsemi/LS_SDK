#include "platform.h"
#include "ls_hal_pdm.h"
#include "ls_hal_dmac.h"
#include "log.h"
#include "ls_soc_gpio.h"
#include "ls_hal_uart.h"
#include "cpu.h"
#define PDM_CLK_KHZ 1024
#define PDM_SAMPLE_RATE_HZ 16000
#define FRAME_BUF_SIZE 256
DEF_DMA_CONTROLLER(dmac1_inst,DMAC1);
PDM_HandleTypeDef pdm;
DMA_RAM_ATTR uint16_t Buf0[FRAME_BUF_SIZE];
DMA_RAM_ATTR uint16_t Buf1[FRAME_BUF_SIZE];

static struct PDM_PingPong_Bufptr pdm_data_receive;
static UART_HandleTypeDef UART_PDM_Config; 
static bool buf0_flag = false;
static bool buf1_flag = false;

static void ls_pdm_uart_init(void)
{

    pinmux_uart1_init(PB00, PB01);
    io_pull_write(PB01, IO_PULL_UP);
    UART_PDM_Config.UARTX = UART1;
    UART_PDM_Config.DMAC_Instance = &dmac1_inst;
    UART_PDM_Config.Tx_Env.DMA.DMA_Channel = 3;
    UART_PDM_Config.Init.BaudRate = UART_BAUDRATE_500000;
    UART_PDM_Config.Init.MSBEN = 0;
    UART_PDM_Config.Init.Parity = UART_NOPARITY;
    UART_PDM_Config.Init.StopBits = UART_STOPBITS1;
    UART_PDM_Config.Init.WordLength = UART_BYTESIZE8;
    HAL_UART_Init(&UART_PDM_Config);
}


void HAL_UART_DMA_TxCpltCallback(UART_HandleTypeDef *huart)
{
    LOG_I("uart send Done");
}

void HAL_PDM_DMA_CpltCallback(PDM_HandleTypeDef *hpdm,uint8_t ch_idx,uint8_t buf_idx)
{
    if(buf_idx)
    {
        buf1_flag = true;
    }
    else
    {
        buf0_flag = true;
    }
}
   
void pdm_dma_test()
{
    
    pdm.DMAC_Instance = &dmac1_inst; 
    pdm.Env.DMA.Channel[0] = 1; ///Configure the DMA channel to receive PDM data
    // pdm.Env.DMA.Channel[1] = 2; ///Only when PDM_MODE_STEREO mode is configured will two DMA channels be used to receive PDM data
    pdm_data_receive.Bufptr[0] = Buf0;
    pdm_data_receive.Bufptr[1] = Buf1;
    HAL_PDM_PingPong_Transfer_Config_DMA(&pdm,&pdm_data_receive,NULL,FRAME_BUF_SIZE); ///DMA receives PDM data streams in Ping-Pong mode
    HAL_PDM_Start(&pdm);
}

void pdm_init()
{
    pinmux_pdm_clk_init(PB10);
    pinmux_pdm_data0_init(PB09);
    pdm.Instance = LSPDM;
    PDM_Init_TypeDef Init = 
    {
        .fir = PDM_FIR_COEF_16KHZ,
        .cfg = {
            .clk_ratio = PDM_CLK_RATIO(PDM_CLK_KHZ),
            .sample_rate = PDM_SAMPLE_RATE(PDM_CLK_KHZ,PDM_SAMPLE_RATE_HZ),
            .cap_delay = 30,
            .data_gain = 5,
        },
        .mode = PDM_MODE_Mono,
    };
    HAL_PDM_Init(&pdm,&Init);
}

int main()
{
    sys_init_none();   
    DMA_CONTROLLER_INIT(dmac1_inst);
    ls_pdm_uart_init();
    pdm_init();
    pdm_dma_test(); 
    while(1)
    {
        if(buf0_flag)
        {
            buf0_flag = false;
            HAL_UART_Transmit_DMA(&UART_PDM_Config,(uint8_t *)&Buf0,FRAME_BUF_SIZE*2);   
        }

        if (buf1_flag)
        {  
            buf1_flag = false;
            HAL_UART_Transmit_DMA(&UART_PDM_Config, (uint8_t *)&Buf1,FRAME_BUF_SIZE*2);
        }
    }
}

