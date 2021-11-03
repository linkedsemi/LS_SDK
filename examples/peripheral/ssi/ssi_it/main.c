
/**
  ******************************************************************************
  * @file    dev\examples\peripheral\ssi\ssi_it\main.c
  * @author  LinkedSemi Software
  * @brief   This sample code shows how to use LE501x SSI HAL API to transmit
  *          and receive a data buffer with a communication process based on
  *          Interrupt transfer.
  *          The communication is done using 1 LE5010 board and a SPI Flash module(W25Q128JV).
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#define LOG_TAG "MAIN"
#include "ls_ble.h"
#include "platform.h"
#include "prf_diss.h"
#include "log.h"
#include "ls_dbg.h"
#include "cpu.h"
#include "builtin_timer.h"
#include <string.h>
#include "co_math.h"
#include "io_config.h"
#include "SEGGER_RTT.h"
#include "lsspi.h"
#include "lsssi.h"
#include "lsdmac.h"

/* Private function prototypes -----------------------------------------------*/
static void Error_Handler(void);

/* Private variables ---------------------------------------------------------*/
/* SPI handler declaration */
SSI_HandleTypeDef SsiHandle;

/* Buffer used for transmission */
static uint8_t ssi_tx_buf[4] = {0x9F,0xAA,0x55,0XAA};

/* Buffer used for reception */
static uint8_t ssi_rx_buf[4] = {0};

/* SSI TX flag */
static uint8_t ssi_txrx_flag = 0;


void HAL_SSI_TxRxCpltCallback(SSI_HandleTypeDef *hssi)
{
	LOG_I("TXRX CMPLT: 0x%x, 0x%x, 0x%x, 0x%x", ssi_rx_buf[0],ssi_rx_buf[1],ssi_rx_buf[2],ssi_rx_buf[3]);
	ssi_txrx_flag = 1;
}

static void ssi_test_init(void)
{
    ssi_clk_io_init(PB09);		/* CLK-------------PB09 */	
	ssi_nss0_io_init(PB08);	/* SSN-------------PB08 */	
	ssi_dq0_io_init(PA07);		/* MOSI------------PA07 */	
	ssi_dq1_io_init(PA00);		/* MISO------------PA00 */	
	
	SsiHandle.REG = LSSSI;
	SsiHandle.Init.clk_div = 128;
	SsiHandle.Init.rxsample_dly = 0;
	SsiHandle.Init.ctrl.cph = SCLK_Toggle_In_Middle;
	SsiHandle.Init.ctrl.cpol = Inactive_Low;
	SsiHandle.Init.ctrl.data_frame_size = DFS_32_8_bits;

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

      /* While the SPI in TransmitReceive process, user can transmit data through 
     "aTxBuffer" buffer & receive data through "aRxBuffer" */
    if(HAL_SSI_TransmitReceive_IT(&SsiHandle, (uint8_t*)ssi_tx_buf, (uint8_t *)ssi_rx_buf, 4) != HAL_OK)
    {
        /* Transfer error in transmission process */
        Error_Handler();
    }

	while(1)
	{
		if(ssi_txrx_flag == 1)
		{
			if(HAL_SSI_TransmitReceive_IT(&SsiHandle, (uint8_t*)ssi_tx_buf, (uint8_t *)ssi_rx_buf, 4) != HAL_OK)
            {
                /* Transfer error in transmission process */
                Error_Handler();
            }
			ssi_txrx_flag = 0;
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
