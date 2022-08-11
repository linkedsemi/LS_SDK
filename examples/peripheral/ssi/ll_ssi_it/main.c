
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

/******************************************************************************
 Include
 ******************************************************************************/
#include "platform.h"
#include "log.h"
#include "ls_dbg.h"
#include <string.h>
#include "ls_soc_gpio.h"
#include "SEGGER_RTT.h"
#include "cpu.h"
#include "ls_hal_ssi.h"

/******************************************************************************
 Function declaration
 ******************************************************************************/
static void Error_Handler(void);
void LL_SSI_TxRxCpltCallback(reg_ssi_t *ssi);
void LL_SSI_RxCpltCallback(reg_ssi_t *ssi);
void LL_SSI_TxCpltCallback(reg_ssi_t *ssi);
uint32_t LL_SSI_TransmitReceive_IT(reg_ssi_t *ssi, void *TX_Data, void *RX_Data, uint16_t Count);

/******************************************************************************
 Global variable declaration
 ******************************************************************************/
/* Buffer used for transmission */
static uint8_t ssi_tx_buf[4] = {0x9F, 0xAA, 0x55, 0XAA};

/* Buffer used for reception */
static uint8_t ssi_rx_buf[4] = {0};

/* SSI TX flag */
static uint8_t ssi_txrx_flag = 0;

/*Transfer data cache and data size*/
uint8_t *TxqBuf;
uint8_t *RxqBuf;
uint8_t SizeOfTxqBuf;
uint8_t SizeOfRxqBuf;


/**
 * @brief SSI init
 *
 * @param None
 * @return None
 */
static void ssi_test_init(void)
{
  pinmux_ssi_clk_init(PB09);  /* CLK-------------PB09 */
  pinmux_ssi_nss0_init(PB08); /* SSN-------------PB08 */
  pinmux_ssi_dq0_init(PA07);  /* MOSI------------PA07 */
  pinmux_ssi_dq1_init(PA00);  /* MISO------------PA00 */

  LL_SSI_MSP_Init();
  clr_pending_irq(SPI1_IRQn);
  enable_irq(SPI1_IRQn);
  LL_SSI_SetClockDivider(LSSSI, 128);
  LL_SSI_SetRxdSampleDelay(LSSSI, 0);
  LL_SSI_SetSSTE(LSSSI, 0);
}

/**
 * @brief
 *
 * @param  ssi SSI Instance.
 * @param TX_Data  transtim data buffer
 * @param RX_Data  Receive data buffer
 * @param Count  Data size
 * @return uint32_t
 */
uint32_t LL_SSI_TransmitReceive_IT(reg_ssi_t *ssi, void *TX_Data, void *RX_Data, uint16_t Count)
{
  TxqBuf = TX_Data;
  RxqBuf = RX_Data;
  SizeOfTxqBuf = Count;
  SizeOfRxqBuf = Count;
  LL_SSI_SetClockPhase(ssi, INACTIVE_LOW);
  LL_SSI_SetClockPolarity(ssi, SCLK_TOGGLE_IN_MIDDLE);
  LL_SSI_SetDataFrameSize(ssi, DFS_32_8_BITS);
  LL_SSI_SetFrameFormat(ssi, MOTOROLA_SPI);
  LL_SSI_SetTransferMode(ssi, TRANSMIT_AND_RECEIVE);
  LL_SSI_DisableDMAReq_TX(ssi);
  LL_SSI_DisableDMAReq_RX(ssi);
  LL_SSI_SetTxFifoThreshoid(ssi, 2);
  LL_SSI_SetRxFifoThreshoid(ssi, 0);
  LL_SSI_DisableMaskIT(ssi, SSI_ITIM_MST | SSI_ITIM_RXF | SSI_ITIM_RXO | SSI_ITIM_RXU | SSI_ITIM_TXO | SSI_ITIM_TXE);
  LL_SSI_Enable(ssi);
  LL_SSI_SetSlaveSelect(ssi, 1);

  return SUCCESS;
}

/**
 * @brief main
 *
 * @return int
 */
int main(void)
{
  sys_init_none();
  ssi_test_init();

  /* While the SPI in TransmitReceive process, user can transmit data through
 "aTxBuffer" buffer & receive data through "aRxBuffer" */
  if (LL_SSI_TransmitReceive_IT(LSSSI, (uint8_t *)ssi_tx_buf, (uint8_t *)ssi_rx_buf, 4) != SUCCESS)
  {
    /* Transfer error in transmission process */
    Error_Handler();
  }

  while (1)
  {
    if (ssi_txrx_flag == 1)
    {
      if (LL_SSI_TransmitReceive_IT(LSSSI, (uint8_t *)ssi_tx_buf, (uint8_t *)ssi_rx_buf, 4) != SUCCESS)
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
  while (1)
  {
  }
}

/**
 * @brief Send/receive callback function
 * 
 * @param ssi ssi Instance.
 */
void LL_SSI_TxRxCpltCallback(reg_ssi_t *ssi)
{
  LOG_I("TXRX CMPLT: 0x%x, 0x%x, 0x%x, 0x%x", ssi_rx_buf[0], ssi_rx_buf[1], ssi_rx_buf[2], ssi_rx_buf[3]);
  ssi_txrx_flag = 1;
}

/**
 * @brief Receive the callback function
 * 
 * @param ssi ssi Instance.
 */
void LL_SSI_RxCpltCallback(reg_ssi_t *ssi)
{
  ;
}

/**
 * @brief Receive the callback function
 * 
 * @param ssi ssi Instance.
 */
void LL_SSI_TxCpltCallback(reg_ssi_t *ssi)
{
  ;
}