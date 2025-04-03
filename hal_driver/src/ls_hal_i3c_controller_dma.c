#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "platform.h"
#include "compile_flag.h"
#include "dmac_config.h"
#include "reg_i3c.h"
#include "ls_hal_i3c_controller.h"
#include "ls_ll_i3c_controller.h"
#include "platform.h"
#include "field_manipulate.h"
#include "ls_hal_dmacv3.h"
#include "ls_msp_i3c.h"
#include "ls_dbg.h"
uint32_t coount  = 0;
static uint16_t HAL_DMA_Controller_Peek_BLOCK_TS(DMA_Controller_HandleTypeDef *hdma, uint8_t ch_idx)
{
    volatile uint64_t *CTL = (void *)hdma->Instance->CH[ch_idx].CTL;
    return (*CTL >> 32) & DMAC_BLOCK_TS_MASK;
}

#define GET_DMA_XFER_COUNT(hdmax,ch_idx)  HAL_DMA_Controller_Peek_BLOCK_TS(hdmax,ch_idx)

void I3C_ControlDataTreatment(I3C_HandleTypeDef *hi3c);
void I3C_ErrorTreatment(I3C_HandleTypeDef *hi3c);
void I3C_StateUpdate(I3C_HandleTypeDef *hi3c);
void I3C_Enable_IRQ(I3C_HandleTypeDef *hi3c, uint32_t InterruptRequest);
void I3C_Disable_IRQ(I3C_HandleTypeDef *hi3c, uint32_t InterruptRequest);

void i3c_dma_tx_callback(DMA_Controller_HandleTypeDef *hdma,uint32_t param,uint8_t ch_idx,uint32_t *lli,uint32_t status_int)
{

    I3C_HandleTypeDef *hi3cx = (I3C_HandleTypeDef *)param;
    LL_I3C_DisableDMAReq_TX(hi3cx->Instance);
}

void i3c_dma_ctrl_rx_callback(DMA_Controller_HandleTypeDef *hdma,uint32_t param,uint8_t ch_idx,uint32_t *lli,uint32_t status_int)
{
  I3C_HandleTypeDef *hi3cx = (I3C_HandleTypeDef *)param;
  LL_I3C_DisableDMAReq_RX(hi3cx->Instance);
}

void i3c_dma_ctrl_tx_callback(DMA_Controller_HandleTypeDef *hdma,uint32_t param,uint8_t ch_idx,uint32_t *lli,uint32_t status_int)
{
  I3C_HandleTypeDef *hi3cx = (I3C_HandleTypeDef *)param;
  /* Disable Rx DMA Request */
  LL_I3C_DisableDMAReq_TX(hi3cx->Instance);
}

/**
  * @brief  Interrupt Sub-Routine which handles controller transmit data in DMA mode.
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                            for the specified I3C.
  * @param  itMasks    : [IN]  Flag Interrupt Masks flags to handle.
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
static HAL_StatusTypeDef I3C_Ctrl_Tx_DMA_ISR(struct __I3C_HandleTypeDef *hi3c, uint32_t itMasks)
{
  /* Check that a Tx process is ongoing */
  if (hi3c->State == HAL_I3C_STATE_BUSY_TX)
  {
    /* Check if Control FIFO requests data */
    if (I3C_CHECK_FLAG(itMasks, I3C_EVR_CFNFF) != RESET)
    {
      if (hi3c->ControlXferCount > 0U)
      {
        /* Call control data treatment function */
        I3C_ControlDataTreatment(hi3c);
      }
    }

    /* I3C target frame complete event Check */
    if (I3C_CHECK_FLAG(itMasks, I3C_EVR_FCF) != RESET)
    {
      /* Clear frame complete flag */
      LL_I3C_ClearFlag_FC(hi3c->Instance);
      if (hi3c->ControlXferCount == 0U)
      {
        LL_I3C_DisableDMAReq_TX(hi3c->Instance);
        /* Check if all data bytes are transmitted */
        if(GET_DMA_XFER_COUNT(hi3c->DMAC_Instance,hi3c->DMA_channel.TX_DMA_Channel) == hi3c->TxXferCount)
        {
          /* Disable Tx process interrupts */
          I3C_Disable_IRQ(hi3c, I3C_XFER_DMA);

          /* Update handle state parameter */
          I3C_StateUpdate(hi3c);

          hi3c->ErrorCode = HAL_I3C_ERROR_NONE;

          /* Update the number of remaining data bytes */
          hi3c->TxXferCount = 0U;

          /* Call controller transmit complete callback to inform upper layer of End of Transfer */
          HAL_I3C_CtrlTxCpltCallback(hi3c);

        }
        else
        {
          hi3c->ErrorCode = HAL_I3C_ERROR_SIZE;
          /* Call error treatment function */
          I3C_ErrorTreatment(hi3c);
        }
      }
      else
      {
        hi3c->ErrorCode = HAL_I3C_ERROR_NONE;
        /* Call the transmit complete callback */
        HAL_I3C_CtrlTxCpltCallback(hi3c);
        /* Then Initiate a Start condition */
        LL_I3C_RequestTransfer(hi3c->Instance);
      }
    }
  }
  return HAL_OK;
}

HAL_StatusTypeDef HAL_I3C_Ctrl_Start_DMA_Transmit(I3C_HandleTypeDef   *hi3c)
{
  REG_FIELD_WR(I3C10->CFGR,I3C_CFGR_TXDMAEN,1);

  struct ch_reg cfg;
  DMA_CHANNEL_CFG(cfg,
      hi3c->DMA_channel.TX_DMA_Channel,
      (uint32_t)hi3c->pXferData->TxBuf.pBuffer,
      (uint32_t)&hi3c->Instance->TDR,
      TRANSFER_WIDTH_8BITS,
      hi3c->pXferData->TxBuf.Size,
      M2P,
      0,
      HAL_I3C_TX_DMA_Handshake_Get(hi3c->Instance),
      0,0,0,0);
      
  HAL_DMA_Channel_Start_IT(hi3c->DMAC_Instance, &cfg, i3c_dma_ctrl_rx_callback, (uint32_t)hi3c);
  return HAL_OK;
}

HAL_StatusTypeDef HAL_I3C_Ctrl_Transmit_DMA(I3C_HandleTypeDef   *hi3c,
                                            I3C_XferTypeDef     *pXferData)
{
  HAL_I3C_StateTypeDef handle_state;
  HAL_StatusTypeDef status = HAL_OK;

  /* check on the handle */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the instance and the mode parameters */

    LS_ASSERT(IS_I3C_MODE(hi3c->Mode));

    /* Get I3C handle state */
    handle_state = hi3c->State;

    /* Check on user parameters */
    if ((pXferData == NULL) ||
        ((hi3c->TxXferCount != 0U) && (pXferData->TxBuf.pBuffer == NULL)))
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_PARAM;
      status = HAL_ERROR;
    }
    /* Check on hdmatx and hdmacr handle */
    else if (hi3c->DMAC_Instance == NULL)
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_DMA_PARAM;
      status = HAL_ERROR;
    }
    /* check on the Mode */
    else if (hi3c->Mode != HAL_I3C_MODE_CONTROLLER)
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
      status = HAL_ERROR;
    }
    /* check on the State */
    else if ((handle_state != HAL_I3C_STATE_READY) && (handle_state != HAL_I3C_STATE_LISTEN))
    {
      status = HAL_BUSY;
    }
    else
    {
      /* Set handle transfer parameters */
      hi3c->ErrorCode     = HAL_I3C_ERROR_NONE;
      hi3c->XferISR       = I3C_Ctrl_Tx_DMA_ISR;
      hi3c->State         = HAL_I3C_STATE_BUSY_TX;
      hi3c->pXferData     = pXferData;
    }

    HAL_I3C_Ctrl_Start_DMA_Transmit(hi3c);

    I3C_Enable_IRQ(hi3c, I3C_XFER_DMA);

    LL_I3C_RequestTransfer(hi3c->Instance);

    }
    return status;
}


/**
  * @brief  Interrupt Sub-Routine which handles controller receive data in DMA mode.
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                            for the specified I3C.
  * @param  itMasks    : [IN]  Flag Interrupt Masks flags to handle.
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
static HAL_StatusTypeDef I3C_Ctrl_Rx_DMA_ISR(struct __I3C_HandleTypeDef *hi3c, uint32_t itMasks)
{
  /* Check that an Rx process is ongoing */
  if (hi3c->State == HAL_I3C_STATE_BUSY_RX)
  {
    /* Check if Control FIFO requests data */
    if (I3C_CHECK_FLAG(itMasks, I3C_EVR_CFNFF) != RESET)
    {
      if (hi3c->ControlXferCount > 0U)
      {
        /* Call control data treatment function */
        I3C_ControlDataTreatment(hi3c);
      }
    }

    /* I3C target frame complete event Check */
    if (I3C_CHECK_FLAG(itMasks, I3C_EVR_FCF) != RESET)
    {
      /* Clear frame complete flag */
      LL_I3C_ClearFlag_FC(hi3c->Instance);

      if (hi3c->ControlXferCount == 0U)
      {
        if(GET_DMA_XFER_COUNT(hi3c->DMAC_Instance,hi3c->DMA_channel.RX_DMA_Channel) == hi3c->RxXferCount)
        {
            /* Disable Rx process interrupts */
            I3C_Disable_IRQ(hi3c, I3C_XFER_DMA);

            /* Update handle state parameter */
            I3C_StateUpdate(hi3c);

            hi3c->ErrorCode = HAL_I3C_ERROR_NONE;

            /* Update the number of remaining data bytes */
            hi3c->RxXferCount = 0U;

            HAL_I3C_CtrlRxCpltCallback(hi3c);
        }else
        {
            hi3c->ErrorCode = HAL_I3C_ERROR_SIZE;
            /* Call error treatment function */
            I3C_ErrorTreatment(hi3c);
        }
      }
      else
      {
        hi3c->ErrorCode = HAL_I3C_ERROR_NONE;
        /* Call the transmit complete callback */
        HAL_I3C_CtrlRxCpltCallback(hi3c);
        /* Then Initiate a Start condition */
        LL_I3C_RequestTransfer(hi3c->Instance);
      }
    }

  }
  return HAL_OK;
}

HAL_StatusTypeDef HAL_I3C_Ctrl_Start_DMA_Receive(I3C_HandleTypeDef   *hi3c)
{
    REG_FIELD_WR(I3C10->CFGR,I3C_CFGR_RXDMAEN,1);
    
    struct ch_reg cfg;
    DMA_CHANNEL_CFG(cfg,
        hi3c->DMA_channel.RX_DMA_Channel,
        (uint32_t)&hi3c->Instance->RDR,
        (uint32_t)hi3c->pXferData->RxBuf.pBuffer,
        TRANSFER_WIDTH_8BITS,
        hi3c->pXferData->RxBuf.Size,
        P2M,
        0,
        HAL_I3C_RX_DMA_Handshake_Get(hi3c->Instance),
        0,0,0,0);
    HAL_DMA_Channel_Start_IT(hi3c->DMAC_Instance, &cfg, i3c_dma_ctrl_rx_callback, (uint32_t)hi3c);
    return HAL_OK;
}


HAL_StatusTypeDef HAL_I3C_Ctrl_Receive_DMA(I3C_HandleTypeDef   *hi3c,
                                           I3C_XferTypeDef     *pXferData)
{
  HAL_I3C_StateTypeDef handle_state;
  HAL_StatusTypeDef status = HAL_OK;

  /* check on the handle */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the instance and the mode parameters */

    LS_ASSERT(IS_I3C_MODE(hi3c->Mode));

    /* Get I3C handle state */
    handle_state = hi3c->State;

    /* Check on user parameters */
    if ((pXferData == NULL) ||
        ((hi3c->TxXferCount != 0U) && (pXferData->TxBuf.pBuffer == NULL)))
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_PARAM;
      status = HAL_ERROR;
    }
    /* Check on hdmatx and hdmacr handle */
    else if (hi3c->DMAC_Instance == NULL)
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_DMA_PARAM;
      status = HAL_ERROR;
    }
    /* check on the Mode */
    else if (hi3c->Mode != HAL_I3C_MODE_CONTROLLER)
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
      status = HAL_ERROR;
    }
    /* check on the State */
    else if ((handle_state != HAL_I3C_STATE_READY) && (handle_state != HAL_I3C_STATE_LISTEN))
    {
      status = HAL_BUSY;
    }
    else
    {
      /* Set handle transfer parameters */
      hi3c->ErrorCode     = HAL_I3C_ERROR_NONE;
      hi3c->XferISR       = I3C_Ctrl_Rx_DMA_ISR;
      hi3c->State         = HAL_I3C_STATE_BUSY_RX;
      hi3c->pXferData     = pXferData;
    }

    HAL_I3C_Ctrl_Start_DMA_Receive(hi3c);
    
    I3C_Enable_IRQ(hi3c, I3C_XFER_DMA);

    LL_I3C_RequestTransfer(hi3c->Instance);

    }
    return status;
}

static HAL_StatusTypeDef I3C_Ctrl_Multiple_Xfer_DMA_ISR(struct __I3C_HandleTypeDef *hi3c, uint32_t itMasks)
{
  /* Check that an Rx or Tx process is ongoing */
  if (hi3c->State == HAL_I3C_STATE_BUSY_TX_RX)
  {
      /* Check if Control FIFO requests data */
    if (I3C_CHECK_FLAG(itMasks, I3C_EVR_CFNFF) != RESET)
    {
      if (hi3c->ControlXferCount > 0U)
      {
        /* Call control data treatment function */
        I3C_ControlDataTreatment(hi3c);
      }
    }

    /* I3C target frame complete event Check */
    if (I3C_CHECK_FLAG(itMasks, I3C_EVR_FCF) != RESET)
    {
      /* Clear frame complete flag */
      LL_I3C_ClearFlag_FC(hi3c->Instance);
      if (hi3c->ControlXferCount == 0U)
      {
        if(GET_DMA_XFER_COUNT(hi3c->DMAC_Instance,hi3c->DMA_channel.RX_DMA_Channel) == hi3c->RxXferCount)
        {
          if(GET_DMA_XFER_COUNT(hi3c->DMAC_Instance,hi3c->DMA_channel.TX_DMA_Channel) == hi3c->TxXferCount)
          {

            /* Disable transfer Tx/Rx process interrupts */
            I3C_Disable_IRQ(hi3c, I3C_XFER_DMA);

            /* Update handle state parameter */
            I3C_StateUpdate(hi3c);

            hi3c->ErrorCode = HAL_I3C_ERROR_NONE;

            /* Update the number of remaining data bytes */
            hi3c->RxXferCount = 0U;

            /* Update the number of remaining data bytes */
            hi3c->TxXferCount = 0U;

            /* Call controller transmit, receive complete callback to inform upper layer of End of Transfer */
            HAL_I3C_CtrlMultipleXferCpltCallback(hi3c);
          }
          else
          {
            hi3c->ErrorCode = HAL_I3C_ERROR_SIZE;
            /* Call error treatment function */
            I3C_ErrorTreatment(hi3c);
          }
        }
        else
        {
          hi3c->ErrorCode = HAL_I3C_ERROR_SIZE;
          /* Call error treatment function */
          I3C_ErrorTreatment(hi3c);
        }
      }
      else
      {
        hi3c->ErrorCode = HAL_I3C_ERROR_NONE;

        /* Then Initiate a Start condition */
        LL_I3C_RequestTransfer(hi3c->Instance);
      }
    }
  }
  return HAL_OK;
}

HAL_StatusTypeDef HAL_I3C_Ctrl_MultipleTransfer_DMA(I3C_HandleTypeDef   *hi3c, I3C_XferTypeDef     *pXferData)
{
  HAL_I3C_StateTypeDef handle_state;
  HAL_StatusTypeDef status = HAL_OK;

  /* check on the handle */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the instance and the mode parameters */
    LS_ASSERT(IS_I3C_MODE(hi3c->Mode));

    /* Get I3C handle state */
    handle_state = hi3c->State;

    /* Check on user parameters */
    if ((pXferData == NULL)                                               ||
        ((pXferData->RxBuf.pBuffer == NULL) && (hi3c->RxXferCount != 0U)) ||
        ((pXferData->TxBuf.pBuffer == NULL) && (hi3c->TxXferCount != 0U)))
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_PARAM;
      status = HAL_ERROR;
    }
    /* Check on hdmatx, hdmarx and hdmacr handle */
    else if ((hi3c->DMAC_Instance == NULL))
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_DMA_PARAM;
      status = HAL_ERROR;
    }
    /* check on the Mode */
    else if (hi3c->Mode != HAL_I3C_MODE_CONTROLLER)
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
      status = HAL_ERROR;
    }
    /* check on the State */
    else if ((handle_state != HAL_I3C_STATE_READY) && (handle_state != HAL_I3C_STATE_LISTEN))
    {
      status = HAL_BUSY;
    }
    else
    {
      /* Set handle transfer parameters */
      hi3c->ErrorCode     = HAL_I3C_ERROR_NONE;
      hi3c->XferISR       = I3C_Ctrl_Multiple_Xfer_DMA_ISR;
      hi3c->pXferData     = pXferData;
      hi3c->RxXferCount   = hi3c->pXferData->RxBuf.Size;
      hi3c->TxXferCount   = hi3c->pXferData->TxBuf.Size;
      hi3c->State         = HAL_I3C_STATE_BUSY_TX_RX;

      if (hi3c->RxXferCount != 0U)
      {

      }

      /*------------------------------------ I3C DMA channel for the Tx Data --------------------------------*/
      /* Check if Tx counter different from zero */
      if (hi3c->TxXferCount != 0U)
      {
      }

        /* Enable Tx process interrupts */
        I3C_Enable_IRQ(hi3c, I3C_XFER_DMA);

        /* Update the number of remaining data bytes */
        hi3c->ControlXferCount = 0U;

        /* Enable control DMA Request */
        LL_I3C_EnableDMAReq_Control(hi3c->Instance);

        /* Check if Rx counter different from zero */
        if (hi3c->RxXferCount != 0U)
        {
          /* Update the number of remaining data bytes */
          hi3c->RxXferCount = 0U;

          /* Enable Rx data DMA Request */
          LL_I3C_EnableDMAReq_RX(hi3c->Instance);
          HAL_I3C_Ctrl_Start_DMA_Receive(hi3c);
        }

        /* Check if Tx counter different from zero */
        if (hi3c->TxXferCount != 0U)
        {
          /* Update the number of remaining data bytes */
          hi3c->TxXferCount = 0U;

          /* Enable Tx data DMA Request */
          LL_I3C_EnableDMAReq_TX(hi3c->Instance);
          HAL_I3C_Ctrl_Start_DMA_Transmit(hi3c);
        }

        /* Initiate a Start condition */
        LL_I3C_RequestTransfer(hi3c->Instance);
    }
  }
  return status;
}