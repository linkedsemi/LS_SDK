
/**
  ******************************************************************************
  * @file    dev\examples\peripheral\ssi\ssi_it\main.c
  * @author  LinkedSemi Software
  * @brief   This sample code shows how to use LE501x SSI HAL API to transmit
  *          and receive a data buffer with a communication process based on
  *          DMA transfer.
  *          The communication is done using 1 LE5010 board and a SPI Flash module(W25Q128JV).
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#define LOG_TAG "MAIN"
#include "platform.h"
#include "log.h"
#include "ls_dbg.h"
#include "cpu.h"
#include <string.h>
#include "co_math.h"
#include "ls_soc_gpio.h"
#include "SEGGER_RTT.h"
#include "ls_hal_spi_i2s.h"
#include "ls_hal_ssi.h"
#if DMACV2
#include "ls_hal_dmacv2.h"
#else
#include "ls_hal_dmac.h"
#endif

/* Private function prototypes -----------------------------------------------*/
static void Error_Handler(void);

/* Private variables ---------------------------------------------------------*/
/* SPI handler declaration */
SSI_HandleTypeDef SsiHandle;

/* SSI TxRx flag */
static uint8_t ssi_txrx_flag = 0;

DMA_RAM_ATTR uint8_t ssi_dma_tx_buf[4];
DMA_RAM_ATTR uint8_t ssi_dma_rx_buf[4];

DEF_DMA_CONTROLLER(dmac1_SSI_inst,DMAC1);

void HAL_SSI_TxRxDMACpltCallback(SSI_HandleTypeDef *hssi)
{
	LOG_I("RX CMPLT: 0x%x, 0x%x, 0x%x, 0x%x", ssi_dma_rx_buf[0],ssi_dma_rx_buf[1],ssi_dma_rx_buf[2],ssi_dma_rx_buf[3]);
	ssi_txrx_flag = 1;
	io_toggle_pin(PA01);
}

static void ssi_test_init(void)
{
    io_cfg_output(PA01);
    io_write_pin(PA01, 1);
    pinmux_ssi_clk_init(PB09);		/* CLK-------------PB09 */	
	pinmux_ssi_nss0_init(PB08);	    /* SSN-------------PB08 */	
	pinmux_ssi_dq0_init(PA07);		/* MOSI------------PA07 */	
	pinmux_ssi_dq1_init(PA00);		/* MISO------------PA00 */	
	
	SsiHandle.REG = LSSSI;
	SsiHandle.Init.clk_div = 128;
	SsiHandle.Init.rxsample_dly = 0;
	SsiHandle.Init.ctrl.cph = SCLK_Toggle_In_Middle;
	SsiHandle.Init.ctrl.cpol = Inactive_Low;
	SsiHandle.Init.ctrl.data_frame_size = DFS_32_8_bits;

    DMA_CONTROLLER_INIT(dmac1_SSI_inst);
	SsiHandle.DMAC_Instance = &dmac1_SSI_inst;
	SsiHandle.Tx_Env.DMA.DMA_Channel = 0;
	SsiHandle.Rx_Env.DMA.DMA_Channel = 1;

	if(HAL_SSI_Init(&SsiHandle) != HAL_OK)
    {
        /* Initialization Error */
        Error_Handler();
    }
}

int main(void)
{
	sys_init_none();
    ssi_test_init();

    ssi_dma_tx_buf[0] = 0x9F;
	ssi_dma_tx_buf[1] = 0xAA;
	ssi_dma_tx_buf[2] = 0x55;
	ssi_dma_tx_buf[3] = 0xAA;

      /* While the SPI in TransmitReceive process, user can transmit data through 
     "aTxBuffer" buffer & receive data through "aRxBuffer" */
    if(HAL_SSI_TransmitReceive_DMA(&SsiHandle, ssi_dma_tx_buf,ssi_dma_rx_buf, 4)!= HAL_OK)
    {
        /* Transfer error in transmission process */
        Error_Handler();
    }

	while(1)
	{
		if(ssi_txrx_flag == 1)
		{
			ssi_txrx_flag = 0;
			if(HAL_SSI_TransmitReceive_DMA(&SsiHandle, ssi_dma_tx_buf,ssi_dma_rx_buf, 4)!= HAL_OK)
            {
                /* Transfer error in transmission process */
                Error_Handler();
            }
		}
		DELAY_US(10000);
	}
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* User may add here some code to deal with this error */
  while(1)
  {
  }
}
