/******************************************************************************
 Include
 ******************************************************************************/
#include "ls_hal_i2c.h"
#include "platform.h"
#include "ls_soc_gpio.h"
#include <string.h>
#include <stdlib.h>
#include "log.h"
#include "cpu.h"

/******************************************************************************
 Macro definition
 ******************************************************************************/
#define I2C_ADDRESS 0x51 // EEPROM addr

/******************************************************************************
 Function declaration
 ******************************************************************************/
static void Error_Handler(void);
static uint16_t Buffercmp(uint8_t *pBuff1, uint8_t *pBuff2, uint16_t Length);
uint32_t LL_I2C_Master_Tx(reg_i2c_t *I2Cx, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
uint32_t LL_I2C_Master_Rx(reg_i2c_t *I2Cx, uint16_t DevAddress, uint8_t *pData, uint16_t Size);

/******************************************************************************
 Global variable declaration
 ******************************************************************************/

/* Buffer used for transmission */
static uint8_t aTxBuffer[12] = {0x00, 0x10, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA};
/* Buffer used for reception */
static uint8_t aRxBuffer[10];

/* Private function prototypes -----------------------------------------------*/
// static void Error_Handler(void);

/**
 * @brief  Main program
 * @param  None
 * @retval None
 */
int main(void)
{
  /* system init app     */
  sys_init_none();

  /* Configure the GPIO AF */
  /* SDA-------------PB12 */
  /* SCL-------------PB13 */
  pinmux_iic1_init(PB13, PB12);

  LL_I2C1_MSP_Init();
  /* Disable the selected I2Cx Peripheral */
  LL_I2C_Disable(I2C1);

  /*set digital filter*/
  LL_I2C_SetDigitalFilter(I2C1, 0);

  /*---------------------------- I2Cx SCL Clock Speed Configuration ------------*/
  LL_I2C_SetClockPeriod(I2C1, 100000);

  /*---------------------------- I2Cx OAR1 Configuration -----------------------*/
  LL_I2C_SetOwnAddress1(I2C1, I2C_ADDRESS, LL_I2C_OWNADDRESS1_7BIT);

  /*---------------------------- I2Cx CR2 Configuration ------------------------*/
  LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_ACK);

  // /*---------------------------- I2Cx Enable the selected I2Cx Peripheral -----------------------*/
  LL_I2C_Enable(I2C1);

  while (LL_I2C_Master_Tx(I2C1, (uint16_t)I2C_ADDRESS, (uint8_t *)aTxBuffer, 12) != SUCCESS)
  {
    Error_Handler();
  }
  for (uint32_t i = 0; i < 100; i++)
    DELAY_US(500);

  while (LL_I2C_Master_Tx(I2C1, (uint16_t)I2C_ADDRESS, (uint8_t *)aTxBuffer, 2) != SUCCESS)
  {
    Error_Handler();
  }
  for (uint32_t i = 0; i < 100; i++)
    DELAY_US(500);

  while (LL_I2C_Master_Rx(I2C1, (uint16_t)I2C_ADDRESS, (uint8_t *)aRxBuffer, 10) != SUCCESS)
  {
    Error_Handler();
  }
    for (uint16_t i = 0; i < 10; i++)
  {
    LOG_I("%d", aRxBuffer[i]);
  }
  while (Buffercmp(aTxBuffer + 2, aRxBuffer, 10))
  {
    ;
  }

  LOG_I("Success!!!");
  /* Infinite loop */
  while (1)
  {
  }
}

/**
 * @brief  Compares two buffers.
 * @param  pBuff1, pBuff2: buffers to be compared.
 * @param  Length: buffer's length
 * @retval 0  : pBuff1 identical to pBuff2
 *         >0 : pBuff1 differs from pBuff2
 */
static uint16_t Buffercmp(uint8_t *pBuff1, uint8_t *pBuff2, uint16_t Length)
{
  while (Length--)
  {
    if ((*pBuff1) != *pBuff2)
    {
      return Length;
    }
    pBuff1++;
    pBuff2++;
  }

  return 0;
}

/**
 * @brief Host send function
 *
 * @param I2Cx I2C Instance.
 * @param DevAddress Slave address
 * @param pData Data of send
 * @param Size Data size of send
 * @return uint32_t state
 */
uint32_t LL_I2C_Master_Tx(reg_i2c_t *I2Cx, uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
  uint32_t TxCount = 0;
  /* Check the I2C handle allocation */
  if (I2Cx == NULL)
  {
    return ERROR;
  }
  if (!LL_I2C_IsActiveFlag(I2Cx, I2C_SR_BUSY))
  {
    /* Check if the I2C is already enabled */
    if (!LL_I2C_IsEnabled(I2Cx))
    {
      /* Enable I2C peripheral */
      LL_I2C_Enable(I2C1);
    }

        /* Clear SR Flag */
    LL_I2C_ClearSR(I2Cx);

    /* (1) Initiate a Start condition to the Slave device ***********************/
    /* Set Reload */
    /*Set the address mode, slave address, transmission direction, and number of bytes to be transmitted*/
    LL_I2C_DisableAutoEnd(I2Cx);
    LL_I2C_DisableRELOAD(I2Cx);
    LL_I2C_SetNumberOfByte(I2Cx, 0);
    if (Size > 0xFF)
    {
      LL_I2C_EnableRELOAD(I2Cx);
      LL_I2C_SetNumberOfByte(I2Cx, 0xff);
    }
    else
    {
      LL_I2C_SetNumberOfByte(I2Cx, Size);
    }

    /* Send slave address */
    LL_I2C_SetAddressToSlave(I2Cx, DevAddress, 0, LL_I2C_OWNADDRESS1_7BIT);

    /* Master Generate Start condition */
    LL_I2C_GenerateStartCondition(I2Cx);

    while (Size > 0)
    {
      /* (6.1) Transmit data (TXE flag raised) **********************************/
      /* Check TXE flag value in ISR register */
      if (LL_I2C_IsActiveFlag(I2Cx, I2C_SR_NACKF))
      {
        LL_I2C_GenerateStopCondition(I2Cx);
        LL_I2C_Disable(I2Cx);
        return ERROR;
      }
      if (LL_I2C_IsActiveFlag(I2Cx, I2C_SR_TXE))
      {
        /* Write data in Transmit Data register.
        TXE flag is cleared by writing data in TXDR register */
        LL_I2C_TransmitData8(I2Cx, (*pData));
        /* Increment Buffer pointer */
        pData++;
        /* Update counter */
        Size--;
        TxCount++;
      }

      /* Updata NBYTES */
      if ((TxCount == 255) && (LL_I2C_IsEnabledRELOAD(I2Cx)))
      {
        if (LL_I2C_IsActiveFlag(I2Cx, I2C_SR_TCR))
        {
          TxCount = 0;
            LL_I2C_DisableRELOAD(I2Cx);
            LL_I2C_SetNumberOfByte(I2Cx, Size);
        }
      }
    }
    LL_I2C_GenerateStopCondition(I2Cx);
    while (!LL_I2C_IsActiveFlag(I2Cx, I2C_SR_STOPF))
    {
      ;
    }

    return SUCCESS;
  }
  else
  {
    return ERROR;
  }
}

/**
 * @brief Host receiving function
 *
 * @param I2Cx I2C Instance.
 * @param DevAddress Slave address
 * @param pData Data of send
 * @param Size Data size of send
 * @return uint32_t state
 */
uint32_t LL_I2C_Master_Rx(reg_i2c_t *I2Cx, uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
  uint32_t RxCount = 0;
  /* Check the I2C handle allocation */
  if (I2Cx == NULL)
  {
    return ERROR;
  }

  if (!LL_I2C_IsActiveFlag(I2Cx, I2C_SR_BUSY))
  {
    /* Check if the I2C is already enabled */
    if (!LL_I2C_IsEnabled(I2Cx))
    {
      /* Enable I2C peripheral */
      LL_I2C_Enable(I2C1);
    }

    /* (1) Initiate a Start condition to the Slave device ***********************/
    /* Set Reload */
    /*Set the address mode, slave address, transmission direction, number of bytes to be transmitted */
    if (Size == 1)
    {
      /* NAck generation*/
      LL_I2C_AcknowledgeNextData(I2Cx, LL_I2C_NACK);
      /* Generate Stop */
      LL_I2C_GenerateStopCondition(I2Cx);
    }

    /* Clear SR Flag */
    LL_I2C_ClearSR(I2Cx);

    LL_I2C_DisableAutoEnd(I2Cx);
    LL_I2C_DisableRELOAD(I2Cx);
    LL_I2C_SetNumberOfByte(I2Cx, 0);
    if (Size > 0xFF)
    {
      LL_I2C_EnableRELOAD(I2Cx);
      LL_I2C_SetNumberOfByte(I2Cx, 0xff);
    }
    else
    {
      LL_I2C_SetNumberOfByte(I2Cx, Size);
    }

    /* Send slave address */
    LL_I2C_SetAddressToSlave(I2Cx, I2C_ADDRESS, 1, LL_I2C_OWNADDRESS1_7BIT);

    /* Master Generate Start condition */
    LL_I2C_GenerateStartCondition(I2Cx);

    while (Size > 0U)
    {
      /* Wait until RXNE flag is set */
      while (!LL_I2C_IsActiveFlag(I2Cx, I2C_SR_RXNE))
      {
        ;
      }

      /* Read data from RXDR */
      *pData = LL_I2C_ReceiveData8(I2Cx);

      /* Increment Buffer pointer */
      pData++;
      RxCount++;

      /* Update counter */
      Size--;

      if (Size == 1U)
      {
        /* NAck generation*/
        LL_I2C_AcknowledgeNextData(I2Cx, LL_I2C_NACK);
        /* Generate Stop */
        LL_I2C_GenerateStopCondition(I2Cx);
      }
      /* Updata NBYTES */
      if ((RxCount == 255) && (LL_I2C_IsEnabledRELOAD(I2Cx)))
      {
        /* Wait until TCR flag is set */
        if (!LL_I2C_IsActiveFlag(I2Cx, I2C_SR_TCR))
        {
          LL_I2C_Disable(I2C1);
          return HAL_ERROR;
        }
        else
        {
          RxCount = 0;
          if (Size > 0xFF)
          {
            LL_I2C_EnableRELOAD(I2Cx);
            LL_I2C_SetNumberOfByte(I2Cx, 0xff);
          }
          else
          {
            LL_I2C_DisableRELOAD(I2Cx);
            LL_I2C_SetNumberOfByte(I2Cx, Size);
          }
        }
      }
    }
    LL_I2C_DisableAutoEnd(I2Cx);
    LL_I2C_DisableRELOAD(I2Cx);
    LL_I2C_SetNumberOfByte(I2Cx, 0);

    while (!LL_I2C_IsActiveFlag(I2Cx, I2C_SR_STOPF))
    {
      ;
    }
    return SUCCESS;
  }
  else
  {
    return ERROR;
  }
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
static void Error_Handler(void)
{
  while (1)
  {
    ;
  }
}
