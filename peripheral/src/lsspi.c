/* Includes ------------------------------------------------------------------*/
#include "lsspi.h"
#include "spi_msp.h"
#include "field_manipulate.h"
#include <stdio.h>
#include "log.h"
#include "systick.h"
#include "ls_dbg.h"

#define SPI_DEFAULT_TIMEOUT 100U

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup SPI_Private_Functions SPI Private Functions
  * @{
  */
static void SPI_TxISR_8BIT(struct __SPI_HandleTypeDef *hspi);
static void SPI_TxISR_16BIT(struct __SPI_HandleTypeDef *hspi);
static void SPI_RxISR_8BIT(struct __SPI_HandleTypeDef *hspi);
static void SPI_RxISR_16BIT(struct __SPI_HandleTypeDef *hspi);
static void SPI_2linesRxISR_8BIT(struct __SPI_HandleTypeDef *hspi);
static void SPI_2linesTxISR_8BIT(struct __SPI_HandleTypeDef *hspi);
static void SPI_2linesTxISR_16BIT(struct __SPI_HandleTypeDef *hspi);
static void SPI_2linesRxISR_16BIT(struct __SPI_HandleTypeDef *hspi);

static void SPI_CloseRxTx_ISR(SPI_HandleTypeDef *hspi);
static void SPI_CloseRx_ISR(SPI_HandleTypeDef *hspi);
static void SPI_CloseTx_ISR(SPI_HandleTypeDef *hspi);
static HAL_StatusTypeDef SPI_EndRxTransaction(SPI_HandleTypeDef *hspi, uint32_t Timeout, uint32_t Tickstart);
static HAL_StatusTypeDef SPI_EndRxTxTransaction(SPI_HandleTypeDef *hspi, uint32_t Timeout, uint32_t Tickstart);
/**
  * @}
  */
/**
  * @brief  Initialize the SPI according to the specified parameters
  *         in the SPI_InitTypeDef and initialize the associated handle.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_Init(SPI_HandleTypeDef *hspi)
{
  /* Check the SPI handle allocation */
  if (hspi == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
 // LS_ASSERT(IS_SPI_ALL_INSTANCE(hspi->Instance));
  LS_ASSERT(IS_SPI_MODE(hspi->Init.Mode));
  LS_ASSERT(IS_SPI_DIRECTION(hspi->Init.Direction));
  LS_ASSERT(IS_SPI_DATASIZE(hspi->Init.DataSize));
  LS_ASSERT(IS_SPI_NSS(hspi->Init.NSS));
  LS_ASSERT(IS_SPI_BAUDRATE_PRESCALER(hspi->Init.BaudRatePrescaler));
  LS_ASSERT(IS_SPI_FIRST_BIT(hspi->Init.FirstBit));
  /* TI mode is not supported on this device.
     TIMode parameter is mandatory equal to SPI_TIMODE_DISABLE */
  LS_ASSERT(IS_SPI_TIMODE(hspi->Init.TIMode));
	
  if (hspi->Init.TIMode == SPI_TIMODE_DISABLE)
  {
    LS_ASSERT(IS_SPI_CPOL(hspi->Init.CLKPolarity));
    LS_ASSERT(IS_SPI_CPHA(hspi->Init.CLKPhase));
  }

  if (hspi->State == HAL_SPI_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    hspi->Lock = HAL_UNLOCKED;

    /* Init the low level hardware : GPIO, CLOCK, NVIC... */
    HAL_SPI_MspInit(hspi);
  }

  hspi->State = HAL_SPI_STATE_BUSY;

    HAL_SPI_MSP_Init(hspi);
    HAL_SPI_MSP_Busy_Set(hspi);
        
  /* Disable the selected SPI peripheral */
  __HAL_SPI_DISABLE(hspi);

  /*----------------------- SPIx CR1 & CR2 Configuration ---------------------*/
  /* Configure : SPI Mode, Communication Mode, Data size, Clock polarity and phase, NSS management,
  Communication speed, First bit and CRC calculation state */
  WRITE_REG(hspi->Instance->CR1, (hspi->Init.Mode | hspi->Init.Direction | hspi->Init.CLKPolarity | 
																	hspi->Init.CLKPhase | 
                                  hspi->Init.BaudRatePrescaler | hspi->Init.FirstBit));

	/* Enable the SPI Peripheral Clock */
	__HAL_SPI_ENABLE(hspi);

	SET_BIT(hspi->Instance->CR1, (hspi->Init.NSS & SPI_CR1_SSM_MASK));
  
	/* Disable the SPI Peripheral Clock */
    __HAL_SPI_DISABLE(hspi);
	
    /* Configure : NSS management */
    WRITE_REG(hspi->Instance->CR2, (((hspi->Init.NSS >> 16U) & SPI_CR2_SSOE_MASK) | hspi->Init.DataSize)); //???16

	MODIFY_REG(hspi->Instance->CR1, SPI_CR1_SSM_MASK, hspi->Init.NSS);	


#if defined(SPI_I2SCFGR_I2SMOD)
  /* Activate the SPI mode (Make sure that I2SMOD bit in I2SCFGR register is reset) */
  CLEAR_BIT(hspi->Instance->I2SCFGR, SPI_I2SCFGR_I2SMOD);
#endif /* SPI_I2SCFGR_I2SMOD */

  hspi->ErrorCode = HAL_SPI_ERROR_NONE;
  hspi->State     = HAL_SPI_STATE_READY;

  return HAL_OK;
}

/**
  * @brief  De-Initialize the SPI peripheral.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_DeInit(SPI_HandleTypeDef *hspi)
{
  /* Check the SPI handle allocation */
  if (hspi == NULL)
  {
    return HAL_ERROR;
  }

  /* Check SPI Instance parameter */
 // LS_ASSERT(IS_SPI_ALL_INSTANCE(hspi->Instance));

  hspi->State = HAL_SPI_STATE_BUSY;

  /* Disable the SPI Peripheral Clock */
  __HAL_SPI_DISABLE(hspi);

  /* DeInit the low level hardware: GPIO, CLOCK, NVIC... */
  HAL_SPI_MSP_DeInit(hspi);
  HAL_SPI_MSP_Idle_Set(hspi);
  hspi->ErrorCode = HAL_SPI_ERROR_NONE;
  hspi->State = HAL_SPI_STATE_RESET;

  /* Release Lock */
  __HAL_UNLOCK(hspi);

  return HAL_OK;
}

/**
  * @brief  Initialize the SPI MSP.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
__weak void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hspi);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SPI_MspInit should be implemented in the user file
   */
}

/**
  * @brief  De-Initialize the SPI MSP.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
__weak void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hspi);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SPI_MspDeInit should be implemented in the user file
   */
}


static bool spi_flag_poll(va_list va)
{
      SPI_HandleTypeDef * hspi = va_arg(va,SPI_HandleTypeDef *);
      uint32_t flag = va_arg(va,uint32_t);
      if (__HAL_SPI_GET_FLAG(hspi, flag))
      {
        return true;
      }
      else
      {
        hspi->State = HAL_SPI_STATE_READY;
        return false;
      }
}
static bool spi_flag_poll1(va_list va)
{
      SPI_HandleTypeDef * hspi = va_arg(va,SPI_HandleTypeDef *);
      uint32_t flag = va_arg(va,uint32_t);
      if (__HAL_SPI_GET_FLAG(hspi, flag))
      {
        hspi->State = HAL_SPI_STATE_READY;
        return false;
      }
      else
      {
        return true;
      }
}
static bool spi_flag_poll2(va_list va)
{
      SPI_HandleTypeDef * hspi = va_arg(va,SPI_HandleTypeDef *);
      uint32_t flag1 = va_arg(va,uint32_t);
      uint32_t flag2 = va_arg(va,uint32_t);
      if (__HAL_SPI_GET_FLAG(hspi, flag1) || __HAL_SPI_GET_FLAG(hspi, flag2))
      {
        return true;
      }
      else
      {
        hspi->State = HAL_SPI_STATE_READY;
        return false;
      }
}

/**
  * @brief  Transmit an amount of data in blocking mode.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @param  pData pointer to data buffer
  * @param  Size amount of data to be sent
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_Transmit(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
  uint32_t tickstart;
  HAL_StatusTypeDef errorcode = HAL_OK;
  uint32_t             txallowed = 1U;
  uint32_t timeout = Timeout * SDK_PCLK_MHZ * 1000;
  /* Check Direction parameter */
  LS_ASSERT(IS_SPI_DIRECTION_2LINES_OR_1LINE(hspi->Init.Direction));

  /* Process Locked */
  __HAL_LOCK(hspi);

  /* Init tickstart for timeout management*/
  tickstart = systick_get_value();

  if (hspi->State != HAL_SPI_STATE_READY)
  {
    errorcode = HAL_BUSY;
    goto error;
  }

  if ((pData == NULL) || (Size == 0U))
  {
    errorcode = HAL_ERROR;
    goto error;
  }

  /* Set the transaction information */
  hspi->State       = HAL_SPI_STATE_BUSY_TX;
  hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
  hspi->pTxBuffPtr  = (uint8_t *)pData;
  hspi->TxXferSize  = Size;
  hspi->TxXferCount = Size;

  /*Init field not used in handle to zero */
  hspi->pRxBuffPtr  = (uint8_t *)NULL;
  hspi->RxXferSize  = 0U;
  hspi->RxXferCount = 0U;
  hspi->TxISR       = NULL;
  hspi->RxISR       = NULL;

  /* Configure communication direction : 1Line */
  if (hspi->Init.Direction == SPI_DIRECTION_1LINE)
  {
    SPI_1LINE_TX(hspi);
  }

  /* Check if the SPI is already enabled */
  if ((hspi->Instance->CR1 & SPI_CR1_SPE_MASK) != SPI_CR1_SPE_MASK)
  {
    /* Enable SPI peripheral */
    __HAL_SPI_ENABLE(hspi);
  }

  /* Transmit data in 16 Bit mode */
  if (hspi->Init.DataSize == SPI_DATASIZE_16BIT)
  {
    if (hspi->Init.Mode == SPI_MODE_SLAVE) //|| (initial_TxXferCount == 0x01U))
    {
      hspi->Instance->DR = *((uint16_t *)hspi->pTxBuffPtr);
      hspi->pTxBuffPtr += sizeof(uint16_t);
      hspi->TxXferCount--;
      txallowed = 0U;
    }
    /* Transmit data in 16 Bit mode */
    while (hspi->TxXferCount > 0U)
    {
        if(systick_poll_timeout(tickstart,timeout,spi_flag_poll,hspi,SPI_FLAG_TXE))
        {
            errorcode = HAL_TIMEOUT;
            goto error;
        }
        else
        {
            //while((REG_FIELD_RD(hspi->Instance->SR,SPI_SR_TXFLV) != 0X0F)&&(hspi->TxXferCount > 0U))
            {
                hspi->Instance->DR = *((uint16_t *)hspi->pTxBuffPtr);
                hspi->pTxBuffPtr += sizeof(uint16_t);
                hspi->TxXferCount--;
            }
        }
    }
  }
  /* Transmit data in 8 Bit mode */
  else
  {
    //if (hspi->Init.Mode == SPI_MODE_SLAVE) //|| (initial_TxXferCount == 0x01U))
    if(hspi->TxXferCount >0)
    {
      *((uint8_t *)&hspi->Instance->DR) = *((uint8_t *)hspi->pTxBuffPtr);
      hspi->pTxBuffPtr += sizeof(uint8_t);
      hspi->TxXferCount--;
      txallowed = 0U;
    }
    while (hspi->TxXferCount > 0U)
    {
        if(systick_poll_timeout(tickstart,timeout,spi_flag_poll2,hspi,SPI_FLAG_TXE,SPI_FLAG_RXNE))
        {
            errorcode = HAL_TIMEOUT;
            goto error;
        }
        else
        {
            if ((__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_TXE)) && (hspi->TxXferCount > 0U) && (txallowed == 1U))
            {
                *((uint8_t *)&hspi->Instance->DR) =  *((uint8_t *)hspi->pTxBuffPtr);
                hspi->pTxBuffPtr += 1;
                hspi->TxXferCount--;
                txallowed = 0U;
            }
              /* Check RXNE flag */
            if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_RXNE))
            {
                txallowed = hspi->Instance->DR; //clear RXNE flag
                txallowed = 1U;
            }
        }

    }
  }

  /* Check the end of the transaction */
  if (SPI_EndRxTxTransaction(hspi, timeout, tickstart) != HAL_OK)
  {
    hspi->ErrorCode = HAL_SPI_ERROR_FLAG;
  }

  /* Clear overrun flag in 2 Lines communication mode because received is not read */
  if (hspi->Init.Direction == SPI_DIRECTION_2LINES)
  {
    __HAL_SPI_CLEAR_OVRFLAG(hspi);
  }

  if (hspi->ErrorCode != HAL_SPI_ERROR_NONE)
  {
    errorcode = HAL_ERROR;
  }
error:
  hspi->State = HAL_SPI_STATE_READY;
  /* Process Unlocked */
  __HAL_UNLOCK(hspi);
  return errorcode;
}

/**
  * @brief  Receive an amount of data in blocking mode.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @param  pData pointer to data buffer
  * @param  Size amount of data to be received
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_Receive(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
  uint32_t tickstart;
  HAL_StatusTypeDef errorcode = HAL_OK;
  uint32_t timeout = Timeout * SDK_PCLK_MHZ * 1000;
  if ((hspi->Init.Mode == SPI_MODE_MASTER) && (hspi->Init.Direction == SPI_DIRECTION_2LINES))
  {
    hspi->State = HAL_SPI_STATE_BUSY_RX;
    /* Call transmit-receive function to send Dummy data on Tx line and generate clock on CLK line */
    return HAL_SPI_TransmitReceive(hspi, pData, pData, Size, Timeout);
  }

  /* Process Locked */
  __HAL_LOCK(hspi);

  /* Init tickstart for timeout management*/
  tickstart = systick_get_value();

  if (hspi->State != HAL_SPI_STATE_READY)
  {
    errorcode = HAL_BUSY;
    goto error;
  }

  if ((pData == NULL) || (Size == 0U))
  {
    errorcode = HAL_ERROR;
    goto error;
  }

  /* Set the transaction information */
  hspi->State       = HAL_SPI_STATE_BUSY_RX;
  hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
  hspi->pRxBuffPtr  = (uint8_t *)pData;
  hspi->RxXferSize  = Size;
  hspi->RxXferCount = Size;

  /*Init field not used in handle to zero */
  hspi->pTxBuffPtr  = (uint8_t *)NULL;
  hspi->TxXferSize  = 0U;
  hspi->TxXferCount = 0U;
  hspi->RxISR       = NULL;
  hspi->TxISR       = NULL;

  /* Configure communication direction: 1Line */
  if (hspi->Init.Direction == SPI_DIRECTION_1LINE)
  {
    SPI_1LINE_RX(hspi);
  }

  /* Check if the SPI is already enabled */
  if ((hspi->Instance->CR1 & SPI_CR1_SPE_MASK) != SPI_CR1_SPE_MASK)
  {
    /* Enable SPI peripheral */
    __HAL_SPI_ENABLE(hspi);
  }

  /* Receive data in 8 Bit mode */
  if (hspi->Init.DataSize == SPI_DATASIZE_8BIT)
  {
    /* Transfer loop */
    while (hspi->RxXferCount > 0U)
    {
      /* Check the RXNE flag */
     if(systick_poll_timeout(tickstart,timeout,spi_flag_poll,hspi,SPI_FLAG_RXNE))
      {
          errorcode = HAL_TIMEOUT;
          goto error;
      }
      else
      {
        (* (uint8_t *)hspi->pRxBuffPtr) = hspi->Instance->DR;
        hspi->pRxBuffPtr += sizeof(uint8_t);
        hspi->RxXferCount--;
      }
    }
  }
  else
  {
    /* Transfer loop */
    while (hspi->RxXferCount > 0U)
    {

     if(systick_poll_timeout(tickstart,timeout,spi_flag_poll,hspi,SPI_FLAG_RXNE))
      {
          errorcode = HAL_TIMEOUT;
          goto error;
      }
      else
      {
          /* read the received data */
        (* (uint16_t *)hspi->pRxBuffPtr) = hspi->Instance->DR;
        hspi->pRxBuffPtr += sizeof(uint16_t);
        hspi->RxXferCount--;
      }
    }
  }

  /* Check the end of the transaction */
  if (SPI_EndRxTransaction(hspi, timeout, tickstart) != HAL_OK)
  {
    hspi->ErrorCode = HAL_SPI_ERROR_FLAG;
  }

  if (hspi->ErrorCode != HAL_SPI_ERROR_NONE)
  {
    errorcode = HAL_ERROR;
  }

error :
  hspi->State = HAL_SPI_STATE_READY;
  __HAL_UNLOCK(hspi);
  return errorcode;
}

/**
  * @brief  Transmit and Receive an amount of data in blocking mode.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @param  pTxData pointer to transmission data buffer
  * @param  pRxData pointer to reception data buffer
  * @param  Size amount of data to be sent and received
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_TransmitReceive(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size,
                                          uint32_t Timeout)
{
  uint16_t             initial_TxXferCount;
  uint32_t             tmp_mode;
  HAL_SPI_StateTypeDef tmp_state;
  uint32_t             tickstart;
  uint32_t             txallowed = 1U;
  uint32_t timeout = Timeout * SDK_PCLK_MHZ * 1000;
  /* Variable used to alternate Rx and Tx during transfer */
  HAL_StatusTypeDef    errorcode = HAL_OK;

  /* Check Direction parameter */
  LS_ASSERT(IS_SPI_DIRECTION_2LINES(hspi->Init.Direction));

  /* Process Locked */
  __HAL_LOCK(hspi);

  /* Init tickstart for timeout management*/
  tickstart = systick_get_value();

  /* Init temporary variables */
  tmp_state           = hspi->State;
  tmp_mode            = hspi->Init.Mode;
  initial_TxXferCount = Size;

  if (!((tmp_state == HAL_SPI_STATE_READY) || \
        ((tmp_mode == SPI_MODE_MASTER) && (hspi->Init.Direction == SPI_DIRECTION_2LINES) && (tmp_state == HAL_SPI_STATE_BUSY_RX))))
  {
    errorcode = HAL_BUSY;
    goto error;
  }

  if ((pTxData == NULL) || (pRxData == NULL) || (Size == 0U))
  {
    errorcode = HAL_ERROR;
    goto error;
  }

  /* Don't overwrite in case of HAL_SPI_STATE_BUSY_RX */
  if (hspi->State != HAL_SPI_STATE_BUSY_RX)
  {
    hspi->State = HAL_SPI_STATE_BUSY_TX_RX;
  }

  /* Set the transaction information */
  hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
  hspi->pRxBuffPtr  = (uint8_t *)pRxData;
  hspi->RxXferCount = Size;
  hspi->RxXferSize  = Size;
  hspi->pTxBuffPtr  = (uint8_t *)pTxData;
  hspi->TxXferCount = Size;
  hspi->TxXferSize  = Size;

  /*Init field not used in handle to zero */
  hspi->RxISR       = NULL;
  hspi->TxISR       = NULL;

  /* Check if the SPI is already enabled */
  if ((hspi->Instance->CR1 & SPI_CR1_SPE_MASK) != SPI_CR1_SPE_MASK)
  {
    /* Enable SPI peripheral */
    __HAL_SPI_ENABLE(hspi);
  }

  /* Transmit and Receive data in 16 Bit mode */
  if (hspi->Init.DataSize == SPI_DATASIZE_16BIT)
  {
    if ((hspi->Init.Mode == SPI_MODE_SLAVE) || (initial_TxXferCount == 0x01U))
    {
      hspi->Instance->DR = *((uint16_t *)hspi->pTxBuffPtr);
      hspi->pTxBuffPtr += sizeof(uint16_t);
      hspi->TxXferCount--;
    }
    while ((hspi->TxXferCount > 0U) || (hspi->RxXferCount > 0U))
    {
        if(systick_poll_timeout(tickstart,timeout,spi_flag_poll2,hspi,SPI_FLAG_TXE,SPI_FLAG_RXNE))
        {
            errorcode = HAL_TIMEOUT;
            goto error;
        }
        else
        {
            /* Check TXE flag */
            if ((__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_TXE)) && (hspi->TxXferCount > 0U) )
            {
               while((REG_FIELD_RD(hspi->Instance->SR,SPI_SR_TXFLV) != 0X0F)&&(hspi->TxXferCount > 0U))
               {
                   hspi->Instance->DR = *((uint16_t *)hspi->pTxBuffPtr);
                   hspi->pTxBuffPtr += sizeof(uint16_t);
                   hspi->TxXferCount--;
               }
            }
              /* Check RXNE flag */
            if ((__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_RXNE)) && (hspi->RxXferCount > 0U))
            {
                *((uint16_t *)hspi->pRxBuffPtr) = (uint16_t)hspi->Instance->DR;
                hspi->pRxBuffPtr += sizeof(uint16_t);
                hspi->RxXferCount--;
            }
        }
    }
  }
  /* Transmit and Receive data in 8 Bit mode */
  else
  {
    if ((hspi->Init.Mode == SPI_MODE_SLAVE) || (initial_TxXferCount == 0x01U))
    {
      *(( uint8_t *)&hspi->Instance->DR) = (*hspi->pTxBuffPtr);
      hspi->pTxBuffPtr += sizeof(uint8_t);
      hspi->TxXferCount--;
      txallowed = 0U;
    }
    while ((hspi->TxXferCount > 0U) || (hspi->RxXferCount > 0U))
    {
        if(systick_poll_timeout(tickstart,timeout,spi_flag_poll2,hspi,SPI_FLAG_TXE,SPI_FLAG_RXNE))
        {
            errorcode = HAL_TIMEOUT;
            goto error;
        }
        else
        {
            /* Check TXE flag */
            if ((__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_TXE)) && (hspi->TxXferCount > 0U) && (txallowed == 1U))
            {
                *(( uint8_t *)&hspi->Instance->DR) = (*hspi->pTxBuffPtr);
                hspi->pTxBuffPtr += sizeof(uint8_t);
                hspi->TxXferCount--;
                /* Next Data is a reception (Rx). Tx not allowed */
                txallowed = 0U;

            }
            /* Check RXNE flag */
            if ((__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_RXNE)) && (hspi->RxXferCount > 0U))
            {
                *((uint8_t *)hspi->pRxBuffPtr) = (uint8_t)hspi->Instance->DR;
                hspi->pRxBuffPtr += sizeof(uint8_t);
                hspi->RxXferCount--;
                /* Next Data is a Transmission (Tx). Tx is allowed */
                txallowed = 1U;
            }
        }
    }
  }

  /* Check the end of the transaction */
  if (SPI_EndRxTxTransaction(hspi, timeout, tickstart) != HAL_OK)
  {
    errorcode = HAL_ERROR;
    hspi->ErrorCode = HAL_SPI_ERROR_FLAG;
    goto error;
  }

  /* Clear overrun flag in 2 Lines communication mode because received is not read */
  if (hspi->Init.Direction == SPI_DIRECTION_2LINES)
  {
    __HAL_SPI_CLEAR_OVRFLAG(hspi);
  }

error :
  hspi->State = HAL_SPI_STATE_READY;
  __HAL_UNLOCK(hspi);
  return errorcode;
}

/**
  * @brief  Transmit an amount of data in non-blocking mode with Interrupt.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @param  pData pointer to data buffer
  * @param  Size amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_Transmit_IT(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size)
{
  HAL_StatusTypeDef errorcode = HAL_OK;

  /* Check Direction parameter */
  LS_ASSERT(IS_SPI_DIRECTION_2LINES_OR_1LINE(hspi->Init.Direction));

  /* Process Locked */
  __HAL_LOCK(hspi);

  if ((pData == NULL) || (Size == 0U))
  {
    errorcode = HAL_ERROR;
    goto error;
  }

  if (hspi->State != HAL_SPI_STATE_READY)
  {
    errorcode = HAL_BUSY;
    goto error;
  }

  /* Set the transaction information */
  hspi->State       = HAL_SPI_STATE_BUSY_TX;
  hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
  hspi->pTxBuffPtr  = (uint8_t *)pData;
  hspi->TxXferSize  = Size;
  hspi->TxXferCount = Size;

  /* Init field not used in handle to zero */
  hspi->pRxBuffPtr  = (uint8_t *)NULL;
  hspi->RxXferSize  = 0U;
  hspi->RxXferCount = 0U;
  hspi->RxISR       = NULL;

  /* Set the function for IT treatment */
  if (hspi->Init.DataSize > SPI_DATASIZE_8BIT)
  {
    hspi->TxISR = SPI_TxISR_16BIT;
  }
  else
  {
    hspi->TxISR = SPI_TxISR_8BIT;
  }

  /* Configure communication direction : 1Line */
  if (hspi->Init.Direction == SPI_DIRECTION_1LINE)
  {
    SPI_1LINE_TX(hspi);
  }

  /* Enable TXE and ERR interrupt */
//  __HAL_SPI_ENABLE_IT(hspi, (SPI_IT_TXE | SPI_IT_ERR));
	__HAL_SPI_CLEAR_IF(hspi, SPI_IT_TXE);
  __HAL_SPI_ENABLE_IT(hspi, SPI_IT_TXE);

  /* Check if the SPI is already enabled */
  if ((hspi->Instance->CR1 & SPI_CR1_SPE_MASK) != SPI_CR1_SPE_MASK)
  {
    /* Enable SPI peripheral */
    __HAL_SPI_ENABLE(hspi);
  }
	
  /* Transmit and Receive data in 16 Bit mode */
  if (hspi->Init.DataSize == SPI_DATASIZE_16BIT)
  {
      /* Check TXE flag */
      if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_TXE))
      {
        hspi->Instance->DR = *((uint16_t *)hspi->pTxBuffPtr);
        hspi->pTxBuffPtr += sizeof(uint16_t);
        hspi->TxXferCount--;
			}

  }
  /* Transmit and Receive data in 8 Bit mode */
  else
  {
      /* Check TXE flag */
      if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_TXE))
      {
        *( uint8_t *)&hspi->Instance->DR = (*hspi->pTxBuffPtr);
        hspi->pTxBuffPtr++;
        hspi->TxXferCount--;
			}
  }
	
error :
  __HAL_UNLOCK(hspi);
  return errorcode;
}

/**
  * @brief  Receive an amount of data in non-blocking mode with Interrupt.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @param  pData pointer to data buffer
  * @param  Size amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_Receive_IT(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size)
{
  HAL_StatusTypeDef errorcode = HAL_OK;

  if ((hspi->Init.Direction == SPI_DIRECTION_2LINES) && (hspi->Init.Mode == SPI_MODE_MASTER))
  {
    hspi->State = HAL_SPI_STATE_BUSY_RX;
    /* Call transmit-receive function to send Dummy data on Tx line and generate clock on CLK line */
    return HAL_SPI_TransmitReceive_IT(hspi, pData, pData, Size);
  }

  /* Process Locked */
  __HAL_LOCK(hspi);

  if (hspi->State != HAL_SPI_STATE_READY)
  {
    errorcode = HAL_BUSY;
    goto error;
  }

  if ((pData == NULL) || (Size == 0U))
  {
    errorcode = HAL_ERROR;
    goto error;
  }

  /* Set the transaction information */
  hspi->State       = HAL_SPI_STATE_BUSY_RX;
  hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
  hspi->pRxBuffPtr  = (uint8_t *)pData;
  hspi->RxXferSize  = Size;
  hspi->RxXferCount = Size;

  /* Init field not used in handle to zero */
  hspi->pTxBuffPtr  = (uint8_t *)NULL;
  hspi->TxXferSize  = 0U;
  hspi->TxXferCount = 0U;
  hspi->TxISR       = NULL;

  /* Set the function for IT treatment */
  if (hspi->Init.DataSize > SPI_DATASIZE_8BIT)
  {
    hspi->RxISR = SPI_RxISR_16BIT;
  }
  else
  {
    hspi->RxISR = SPI_RxISR_8BIT;
  }

  /* Configure communication direction : 1Line */
  if (hspi->Init.Direction == SPI_DIRECTION_1LINE)
  {
    SPI_1LINE_RX(hspi);
  }

  /* Enable TXE and ERR interrupt */
	__HAL_SPI_CLEAR_IF(hspi, SPI_IT_RXNE);
  __HAL_SPI_ENABLE_IT(hspi, SPI_IT_RXNE);
 // __HAL_SPI_ENABLE_IT(hspi, (SPI_IT_RXNE | SPI_IT_ERR));
  /* Note : The SPI must be enabled after unlocking current process
            to avoid the risk of SPI interrupt handle execution before current
            process unlock */

  /* Check if the SPI is already enabled */
  if ((hspi->Instance->CR1 & SPI_CR1_SPE_MASK) != SPI_CR1_SPE_MASK)
  {
    /* Enable SPI peripheral */
    __HAL_SPI_ENABLE(hspi);
  }

error :
  /* Process Unlocked */
  __HAL_UNLOCK(hspi);
  return errorcode;
}

/**
  * @brief  Transmit and Receive an amount of data in non-blocking mode with Interrupt.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @param  pTxData pointer to transmission data buffer
  * @param  pRxData pointer to reception data buffer
  * @param  Size amount of data to be sent and received
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_TransmitReceive_IT(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size)
{
  uint32_t             tmp_mode;
  HAL_SPI_StateTypeDef tmp_state;
  HAL_StatusTypeDef    errorcode = HAL_OK;

  /* Check Direction parameter */
  LS_ASSERT(IS_SPI_DIRECTION_2LINES(hspi->Init.Direction));

  /* Process locked */
  __HAL_LOCK(hspi);

  /* Init temporary variables */
  tmp_state           = hspi->State;
  tmp_mode            = hspi->Init.Mode;

  if (!((tmp_state == HAL_SPI_STATE_READY) || \
        ((tmp_mode == SPI_MODE_MASTER) && (hspi->Init.Direction == SPI_DIRECTION_2LINES) && (tmp_state == HAL_SPI_STATE_BUSY_RX))))
  {
    errorcode = HAL_BUSY;
    goto error;
  }

  if ((pTxData == NULL) || (pRxData == NULL) || (Size == 0U))
  {
    errorcode = HAL_ERROR;
    goto error;
  }

  /* Don't overwrite in case of HAL_SPI_STATE_BUSY_RX */
  if (hspi->State != HAL_SPI_STATE_BUSY_RX)
  {
    hspi->State = HAL_SPI_STATE_BUSY_TX_RX;
  }

  /* Set the transaction information */
  hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
  hspi->pTxBuffPtr  = (uint8_t *)pTxData;
  hspi->TxXferSize  = Size;
  hspi->TxXferCount = Size;
  hspi->pRxBuffPtr  = (uint8_t *)pRxData;
  hspi->RxXferSize  = Size;
  hspi->RxXferCount = Size;

  /* Set the function for IT treatment */
  if (hspi->Init.DataSize > SPI_DATASIZE_8BIT)
  {
    hspi->RxISR     = SPI_2linesRxISR_16BIT;
    hspi->TxISR     = SPI_2linesTxISR_16BIT;
  }
  else
  {
    hspi->RxISR     = SPI_2linesRxISR_8BIT;
    hspi->TxISR     = SPI_2linesTxISR_8BIT;
  }

  /* Enable TXE, RXNE and ERR interrupt */
//	__HAL_SPI_CLEAR_IF(hspi, (SPI_IT_TXE | SPI_IT_RXNE | SPI_IT_ERR));
//  __HAL_SPI_ENABLE_IT(hspi, (SPI_IT_TXE | SPI_IT_RXNE | SPI_IT_ERR));

	__HAL_SPI_CLEAR_IF(hspi, (SPI_IT_TXE | SPI_IT_RXNE ));
  __HAL_SPI_ENABLE_IT(hspi, (SPI_IT_TXE | SPI_IT_RXNE ));
	
  /* Check if the SPI is already enabled */
  if ((hspi->Instance->CR1 & SPI_CR1_SPE_MASK) != SPI_CR1_SPE_MASK)
  {
    /* Enable SPI peripheral */
    __HAL_SPI_ENABLE(hspi);
  }
  /* Transmit and Receive data in 16 Bit mode */
  if (hspi->Init.DataSize == SPI_DATASIZE_16BIT)
  {
      /* Check TXE flag */
      if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_TXE))
      {
        hspi->Instance->DR = *((uint16_t *)hspi->pTxBuffPtr);
        hspi->pTxBuffPtr += sizeof(uint16_t);
        hspi->TxXferCount--;
			}

  }
  /* Transmit and Receive data in 8 Bit mode */
  else
  {
      /* Check TXE flag */
      if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_TXE))
      {
        *( uint8_t *)&hspi->Instance->DR = (*hspi->pTxBuffPtr);
        hspi->pTxBuffPtr++;
        hspi->TxXferCount--;
			}
  }
error :
  /* Process Unlocked */
  __HAL_UNLOCK(hspi);
  return errorcode;
}


__attribute__((weak))  void spi_tx_empty_dma_isr(SPI_HandleTypeDef *hspi){}

void HAL_SPI_IRQHandler(SPI_HandleTypeDef *hspi)
{
  uint32_t itsource = hspi->Instance->IVS;
  uint32_t itflag   = hspi->Instance->SR;

  /* SPI in mode Receiver ----------------------------------------------------*/
  if ((SPI_CHECK_FLAG(itflag, SPI_FLAG_OVR) == RESET) &&
      (SPI_CHECK_FLAG(itflag, SPI_FLAG_RXNE) != RESET) && (SPI_CHECK_IT_SOURCE(itsource, SPI_IT_RXNE) != RESET))
  {
		SET_BIT(hspi->Instance->ICR,SPI_IT_RXNE);
        hspi->RxISR(hspi);

   // return;
  }

  /* SPI in mode Transmitter -------------------------------------------------*/
  if ((SPI_CHECK_FLAG(itflag, SPI_FLAG_TXE) != RESET) && (SPI_CHECK_IT_SOURCE(itsource, SPI_IT_TXE) != RESET))
  {
		SET_BIT(hspi->Instance->ICR,SPI_IT_TXE);

        if(REG_FIELD_RD(hspi->Instance->CR2,SPI_CR2_TXDMAEN))
        {
            spi_tx_empty_dma_isr(hspi);
        }
        else
        {
            hspi->TxISR(hspi);

        }
    //return;
  }

  /* SPI in Error Treatment --------------------------------------------------*/
  if (((SPI_CHECK_FLAG(itflag, SPI_FLAG_MODF) != RESET) || (SPI_CHECK_FLAG(itflag, SPI_FLAG_OVR) != RESET))
       && (SPI_CHECK_IT_SOURCE(itsource, SPI_IT_ERR) != RESET))
  {
    /* SPI Overrun error interrupt occurred ----------------------------------*/
    if (SPI_CHECK_FLAG(itflag, SPI_FLAG_OVR) != RESET)
    {
        if (hspi->State != HAL_SPI_STATE_BUSY_TX)
        {
            SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_OVR);
            __HAL_SPI_CLEAR_OVRFLAG(hspi);
        }
        else
        {
            return;
        }
    }

    /* SPI Mode Fault error interrupt occurred -------------------------------*/
    if (SPI_CHECK_FLAG(itflag, SPI_FLAG_MODF) != RESET)
    {
      SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_MODF);
      __HAL_SPI_CLEAR_MODFFLAG(hspi);
    }

    /* SPI Frame error interrupt occurred ------------------------------------*/

	SET_BIT(hspi->Instance->ICR,SPI_IT_ERR);
    return;
  }
}

/**
  * @brief  Tx Transfer completed callback.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
__weak void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hspi);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SPI_TxCpltCallback should be implemented in the user file
   */
}

/**
  * @brief  Rx Transfer completed callback.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
__weak void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hspi);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SPI_RxCpltCallback should be implemented in the user file
   */
}

/**
  * @brief  Tx and Rx Transfer completed callback.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
__weak void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hspi);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SPI_TxRxCpltCallback should be implemented in the user file
   */
}

/**
  * @brief  SPI error callback.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
__weak void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hspi);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SPI_ErrorCallback should be implemented in the user file
   */
  /* NOTE : The ErrorCode parameter in the hspi handle is updated by the SPI processes
            and user can use HAL_SPI_GetError() API to check the latest error occurred
   */
}

/**
  * @brief  Return the SPI handle state.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval SPI state
  */
HAL_SPI_StateTypeDef HAL_SPI_GetState(SPI_HandleTypeDef *hspi)
{
  /* Return SPI handle state */
  return hspi->State;
}

/**
  * @brief  Return the SPI error code.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval SPI error code in bitmap format
  */
uint32_t HAL_SPI_GetError(SPI_HandleTypeDef *hspi)
{
  /* Return SPI ErrorCode */
  return hspi->ErrorCode;
}

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup SPI_Private_Functions
  * @brief   Private functions
  * @{
  */

/**
  * @brief  Rx 8-bit handler for Transmit and Receive in Interrupt mode.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
static void SPI_2linesRxISR_8BIT(struct __SPI_HandleTypeDef *hspi)
{
  /* Receive data in 8bit mode */
  *hspi->pRxBuffPtr = *((uint8_t *)&hspi->Instance->DR);
  hspi->pRxBuffPtr++;
  hspi->RxXferCount--;

  /* Check end of the reception */
  if (hspi->RxXferCount == 0U)
  {

    /* Disable RXNE  and ERR interrupt */
    __HAL_SPI_DISABLE_IT(hspi, (SPI_IT_RXNE | SPI_IT_ERR));

    if (hspi->TxXferCount == 0U)
    {
      SPI_CloseRxTx_ISR(hspi);
    }
  }
}

/**
  * @brief  Tx 8-bit handler for Transmit and Receive in Interrupt mode.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
static void SPI_2linesTxISR_8BIT(struct __SPI_HandleTypeDef *hspi)
{
  *(uint8_t *)&hspi->Instance->DR = (*hspi->pTxBuffPtr);
  hspi->pTxBuffPtr++;
  hspi->TxXferCount--;

  /* Check the end of the transmission */
  if (hspi->TxXferCount == 0U)
  {

    /* Disable TXE interrupt */
    __HAL_SPI_DISABLE_IT(hspi, SPI_IT_TXE);

    if (hspi->RxXferCount == 0U)
    {
      SPI_CloseRxTx_ISR(hspi);
    }
  }
}

/**
  * @brief  Rx 16-bit handler for Transmit and Receive in Interrupt mode.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
static void SPI_2linesRxISR_16BIT(struct __SPI_HandleTypeDef *hspi)
{
  /* Receive data in 16 Bit mode */
  *((uint16_t *)hspi->pRxBuffPtr) = (uint16_t)(hspi->Instance->DR);
  hspi->pRxBuffPtr += sizeof(uint16_t);
  hspi->RxXferCount--;

  if (hspi->RxXferCount == 0U)
  {

    /* Disable RXNE interrupt */
    __HAL_SPI_DISABLE_IT(hspi, SPI_IT_RXNE);

    if (hspi->TxXferCount == 0U)
    {
      SPI_CloseRxTx_ISR(hspi);
    }
  }
}

/**
  * @brief  Tx 16-bit handler for Transmit and Receive in Interrupt mode.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
static void SPI_2linesTxISR_16BIT(struct __SPI_HandleTypeDef *hspi)
{
  /* Transmit data in 16 Bit mode */
  hspi->Instance->DR = *((uint16_t *)hspi->pTxBuffPtr);
  hspi->pTxBuffPtr += sizeof(uint16_t);
  hspi->TxXferCount--;

  /* Enable CRC Transmission */
  if (hspi->TxXferCount == 0U)
  {

    /* Disable TXE interrupt */
    __HAL_SPI_DISABLE_IT(hspi, SPI_IT_TXE);

    if (hspi->RxXferCount == 0U)
    {
      SPI_CloseRxTx_ISR(hspi);
    }
  }
}

/**
  * @brief  Manage the receive 8-bit in Interrupt context.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
static void SPI_RxISR_8BIT(struct __SPI_HandleTypeDef *hspi)
{
  *hspi->pRxBuffPtr = (*(uint8_t *)&hspi->Instance->DR);
  hspi->pRxBuffPtr++;
  hspi->RxXferCount--;

  if (hspi->RxXferCount == 0U)
  {
    SPI_CloseRx_ISR(hspi);
  }
}

/**
  * @brief  Manage the 16-bit receive in Interrupt context.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
static void SPI_RxISR_16BIT(struct __SPI_HandleTypeDef *hspi)
{
  *((uint16_t *)hspi->pRxBuffPtr) = (uint16_t)(hspi->Instance->DR);
  hspi->pRxBuffPtr += sizeof(uint16_t);
  hspi->RxXferCount--;

  if (hspi->RxXferCount == 0U)
  {
    SPI_CloseRx_ISR(hspi);
  }
}

/**
  * @brief  Handle the data 8-bit transmit in Interrupt mode.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
static void SPI_TxISR_8BIT(struct __SPI_HandleTypeDef *hspi)
{
  *(uint8_t *)&hspi->Instance->DR = (*hspi->pTxBuffPtr);
  hspi->pTxBuffPtr++;
  hspi->TxXferCount--;

  if (hspi->TxXferCount == 0U)
  {
    SPI_CloseTx_ISR(hspi);
  }
}

/**
  * @brief  Handle the data 16-bit transmit in Interrupt mode.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
static void SPI_TxISR_16BIT(struct __SPI_HandleTypeDef *hspi)
{
  /* Transmit data in 16 Bit mode */
  hspi->Instance->DR = *((uint16_t *)hspi->pTxBuffPtr);
  hspi->pTxBuffPtr += sizeof(uint16_t);
  hspi->TxXferCount--;

  if (hspi->TxXferCount == 0U)
  {
    SPI_CloseTx_ISR(hspi);
  }
}

/**
  * @brief  Handle the check of the RX transaction complete.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @param  Timeout Timeout duration
  * @param  Tickstart tick start value
  * @retval HAL status
  */
static HAL_StatusTypeDef SPI_EndRxTransaction(SPI_HandleTypeDef *hspi,  uint32_t Timeout, uint32_t Tickstart)
{
  if ((hspi->Init.Mode == SPI_MODE_MASTER) && ((hspi->Init.Direction == SPI_DIRECTION_1LINE)
                                               || (hspi->Init.Direction == SPI_DIRECTION_2LINES_RXONLY)))
  {
    /* Disable SPI peripheral */
    __HAL_SPI_DISABLE(hspi);
  }

  if ((hspi->Init.Mode == SPI_MODE_MASTER) && (hspi->Init.Direction == SPI_DIRECTION_2LINES_RXONLY))
  {
    /* Wait the RXNE reset */
    if(systick_poll_timeout(Tickstart,Timeout,spi_flag_poll1,hspi,SPI_FLAG_RXNE))
    {
      SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
      return HAL_TIMEOUT;
    }
  }
  else
  {
    /* Control the BSY flag */
    if(systick_poll_timeout(Tickstart,Timeout,spi_flag_poll1,hspi,SPI_FLAG_BSY))
    {
      SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
      return HAL_TIMEOUT;

    }
  }
  return HAL_OK;
}

/**
  * @brief  Handle the check of the RXTX or TX transaction complete.
  * @param  hspi SPI handle
  * @param  Timeout Timeout duration
  * @param  Tickstart tick start value
  * @retval HAL status
  */
static HAL_StatusTypeDef SPI_EndRxTxTransaction(SPI_HandleTypeDef *hspi, uint32_t Timeout, uint32_t Tickstart)
{

  /* Control the BSY flag */
  if(systick_poll_timeout(Tickstart,Timeout,spi_flag_poll1,hspi,SPI_FLAG_BSY))
  {
    SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
    return HAL_TIMEOUT;
  }
  return HAL_OK;
}

/**
  * @brief  Handle the end of the RXTX transaction.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
static void SPI_CloseRxTx_ISR(SPI_HandleTypeDef *hspi)
{
  uint32_t tickstart;
  uint32_t count = SPI_DEFAULT_TIMEOUT * (SPI_CLOCK / 24U / 1000U);

  /* Init tickstart for timeout managment*/
  tickstart = systick_get_value();

  /* Disable ERR interrupt */
  __HAL_SPI_DISABLE_IT(hspi, SPI_IT_ERR);

  /* Wait until TXE flag is set */
  do
  {
    if (count == 0U)
    {
      SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
      break;
    }
    count--;
  } while ((hspi->Instance->SR & SPI_FLAG_TXE) == RESET);

  /* Check the end of the transaction */
  if (SPI_EndRxTxTransaction(hspi, SPI_DEFAULT_TIMEOUT * (SPI_CLOCK / 24U / 1000U), tickstart) != HAL_OK)
  {
    SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
  }

  /* Clear overrun flag in 2 Lines communication mode because received is not read */
  if (hspi->Init.Direction == SPI_DIRECTION_2LINES)
  {
    __HAL_SPI_CLEAR_OVRFLAG(hspi);
  }
    if (hspi->ErrorCode == HAL_SPI_ERROR_NONE)
    {
      if (hspi->State == HAL_SPI_STATE_BUSY_RX)
      {
        hspi->State = HAL_SPI_STATE_READY;
        /* Call user Rx complete callback */
        HAL_SPI_RxCpltCallback(hspi);
      }
      else
      {
        hspi->State = HAL_SPI_STATE_READY;
        /* Call user TxRx complete callback */
        HAL_SPI_TxRxCpltCallback(hspi);
      }
    }
    else
    {
      hspi->State = HAL_SPI_STATE_READY;
      /* Call user error callback */
      HAL_SPI_ErrorCallback(hspi);
    }
}

/**
  * @brief  Handle the end of the RX transaction.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
static void SPI_CloseRx_ISR(SPI_HandleTypeDef *hspi)
{
  /* Disable RXNE and ERR interrupt */
  __HAL_SPI_DISABLE_IT(hspi, (SPI_IT_RXNE | SPI_IT_ERR));

  /* Check the end of the transaction */
  if (SPI_EndRxTransaction(hspi, SPI_DEFAULT_TIMEOUT * (SPI_CLOCK / 24U / 1000U), systick_get_value()) != HAL_OK)
  {
    SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
  }

  /* Clear overrun flag in 2 Lines communication mode because received is not read */
  if (hspi->Init.Direction == SPI_DIRECTION_2LINES)
  {
    __HAL_SPI_CLEAR_OVRFLAG(hspi);
  }
  hspi->State = HAL_SPI_STATE_READY;

    if (hspi->ErrorCode == HAL_SPI_ERROR_NONE)
    {
      /* Call user Rx complete callback */
      HAL_SPI_RxCpltCallback(hspi);
    }
    else
    {
      /* Call user error callback */
      HAL_SPI_ErrorCallback(hspi);
    }
}

/**
  * @brief  Handle the end of the TX transaction.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
static void SPI_CloseTx_ISR(SPI_HandleTypeDef *hspi)
{
  uint32_t tickstart;
  uint32_t count = SPI_DEFAULT_TIMEOUT * (SPI_CLOCK / 24U / 1000U);

  /* Init tickstart for timeout management*/
  tickstart = systick_get_value();

  /* Wait until TXE flag is set */
  do
  {
    if (count == 0U)
    {
      SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
      break;
    }
    count--;
  } while ((hspi->Instance->SR & SPI_FLAG_TXE) == RESET);

  /* Disable TXE and ERR interrupt */
  __HAL_SPI_DISABLE_IT(hspi, (SPI_IT_TXE | SPI_IT_ERR));

  /* Check the end of the transaction */
  if (SPI_EndRxTxTransaction(hspi, SPI_DEFAULT_TIMEOUT * (SPI_CLOCK / 24U / 1000U), tickstart) != HAL_OK)
  {
    SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
  }

  /* Clear overrun flag in 2 Lines communication mode because received is not read */
  if (hspi->Init.Direction == SPI_DIRECTION_2LINES)
  {
    __HAL_SPI_CLEAR_OVRFLAG(hspi);
  }

  hspi->State = HAL_SPI_STATE_READY;
  if (hspi->ErrorCode != HAL_SPI_ERROR_NONE)
  {
    /* Call user error callback */
    HAL_SPI_ErrorCallback(hspi);
  }
  else
  {
    /* Call user Rx complete callback */
    HAL_SPI_TxCpltCallback(hspi);
  }
}

/************************ (C) COPYRIGHT linkedsemi *****END OF FILE****/
