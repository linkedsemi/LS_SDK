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
void LL_I2C_MasterNACKCpltCallback(reg_i2c_t *I2Cx);
void LL_I2C_MasterTXECpltCallback(reg_i2c_t *I2Cx);
void LL_I2C_MasterTCRCpltCallback(reg_i2c_t *I2Cx);
void LL_I2C_MasterRXNECpltCallback(reg_i2c_t *I2Cx);
static uint16_t Buffercmp(uint8_t *pBuff1, uint8_t *pBuff2, uint16_t Length);
uint32_t LL_I2C_Master_Tx(reg_i2c_t *I2Cx, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
uint32_t LL_I2C_Master_Rx(reg_i2c_t *I2Cx, uint16_t DevAddress, uint8_t *pData, uint16_t Size);

/******************************************************************************
 Global variable declaration
 ******************************************************************************/
enum
{
  start = 0,
  txing,
  txover,
  txaddr,
  addrover,
  rxing,
  rxover,
};
static volatile uint8_t Com_Sta = start;

/* Buffer used for transmission */
static uint8_t aTxBuffer[12] = {0x00, 0x10, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA};

/* Buffer used for reception */
static uint8_t aRxBuffer[10];

/*Transfer data cache and data size*/
uint8_t *qBuf;
uint8_t DataOfSize;

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
  
  clr_pending_irq(I2C1_IRQn);
  enable_irq(I2C1_IRQn);
  /* Disable the selected I2Cx Peripheral */
  LL_I2C_Disable(I2C1);

  /*set digital filter*/
  LL_I2C_SetDigitalFilter(I2C1, 0);

  /*---------------------------- I2Cx SCL Clock Speed Configuration ------------*/
  LL_I2C_SetClockPeriod(I2C1, 200000);

  /*---------------------------- I2Cx OAR1 Configuration -----------------------*/
  LL_I2C_SetOwnAddress1(I2C1, I2C_ADDRESS, LL_I2C_OWNADDRESS1_7BIT);

  // /*---------------------------- I2Cx Enable the selected I2Cx Peripheral -----------------------*/
  LL_I2C_Enable(I2C1);

  /*---------------------------- I2Cx CR2 Configuration ------------------------*/
  LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_ACK);

  Com_Sta = txing;
  while (LL_I2C_Master_Tx(I2C1, I2C_ADDRESS, aTxBuffer, 12) != SUCCESS)
  {
    Error_Handler();
  }
  while (Com_Sta == txing)
    ;

  for (uint32_t i = 0; i < 100; i++)
    DELAY_US(500);

  Com_Sta = txaddr;
  while (LL_I2C_Master_Tx(I2C1, I2C_ADDRESS, aTxBuffer, 2) != SUCCESS)
  {
    Error_Handler();
  }
  while (Com_Sta == txaddr)
    ;

  for (uint32_t i = 0; i < 100; i++)
    DELAY_US(500);

  Com_Sta = rxing;
  while (LL_I2C_Master_Rx(I2C1, I2C_ADDRESS, aRxBuffer, 10) != SUCCESS)
  {
    Error_Handler();
  }
  while (Com_Sta == rxing)
    ;

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
 * @brief 主机发送函数
 *
 * @param I2Cx
 * @param DevAddress
 * @param pData
 * @param Size
 * @return uint32_t
 */
uint32_t LL_I2C_Master_Tx(reg_i2c_t *I2Cx, uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
  /* Check the I2C handle allocation */
  if (I2Cx == NULL)
  {
    return ERROR;
  }
  DataOfSize = Size;
  qBuf = pData;
  /* (1) Initiate a Start condition to the Slave device ***********************/
  /* Set Reload */
  /*Set the address mode, slave address, transmission direction, and number of bytes to be transmitted*/
  LL_I2C_DisableAutoEnd(I2Cx);
  LL_I2C_DisableRELOAD(I2Cx);
  LL_I2C_SetNumberOfByte(I2Cx, 0);
  LL_I2C_EnableAutoEnd(I2Cx);
  LL_I2C_SetNumberOfByte(I2Cx, DataOfSize);

  /* Send slave address */
  LL_I2C_SetAddressToSlave(I2Cx, DevAddress, 0, LL_I2C_OWNADDRESS1_7BIT);

  /* Master Generate Start condition */
  LL_I2C_GenerateStartCondition(I2Cx);

  /* Clear SR Flag */
  LL_I2C_ClearSR(I2Cx);

    /*Send 8bit data*/
  if ((DataOfSize > 0U) && (LL_I2C_IsActiveFlag(I2Cx, I2C_SR_TXE) == SET))
  {
    /* Write data to TXDR */
    LL_I2C_TransmitData8(I2Cx, *qBuf);

    /* Increment Buffer pointer */
    qBuf++;

    /* Update counter */
    DataOfSize--;
  }

  /* Clear interrupt Flag */
  LL_I2C_ClearFlagIT(I2Cx, I2C_ITIC_TXE | I2C_ITIC_ADDR | I2C_ITIC_NACK | I2C_ITIC_STOP | I2C_ITIC_ERR);

  /* Enable EVT, TXE and ERR interrupt */
  LL_I2C_EnableIT(I2Cx, I2C_ITEN_ADDR | I2C_ITEN_NACK | I2C_ITEN_STOP | I2C_ITEN_TXE | I2C_ITEN_ERR);
  /*Disable the sending completion interrupt*/
  LL_I2C_EnableIT(I2Cx, I2C_ITEN_TC);



  return SUCCESS;
}

/**
 * @brief Host receiving function
 *
 * @param I2Cx
 * @param DevAddress
 * @param pData
 * @param Size
 * @return uint32_t
 */
uint32_t LL_I2C_Master_Rx(reg_i2c_t *I2Cx, uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
  /* Check the I2C handle allocation */
  if (I2Cx == NULL)
  {
    return ERROR;
  }
  DataOfSize = Size;
  qBuf = pData;
  /* (1) Initiate a Start condition to the Slave device ***********************/
  /* Set Reload */
  /*Set the address mode, slave address, transmission direction, number of bytes to be transmitted */
  if (Size == 1)
    LL_I2C_AcknowledgeNextData(I2Cx, LL_I2C_NACK);
  else
    LL_I2C_AcknowledgeNextData(I2Cx, LL_I2C_ACK);
  LL_I2C_DisableAutoEnd(I2Cx);
  LL_I2C_DisableRELOAD(I2Cx);
  LL_I2C_SetNumberOfByte(I2Cx, 0);
  LL_I2C_EnableAutoEnd(I2Cx);
  LL_I2C_SetNumberOfByte(I2Cx, DataOfSize);

  /* Send slave address */
  LL_I2C_SetAddressToSlave(I2Cx, I2C_ADDRESS, 1, LL_I2C_OWNADDRESS1_7BIT);

  /* Master Generate Start condition */
  LL_I2C_GenerateStartCondition(I2Cx);

  /* Clear SR Flag */
  LL_I2C_ClearSR(I2Cx);

  /*Disable the sending completion interrupt*/
  LL_I2C_EnableIT(I2Cx, I2C_ITEN_TC);

  /* Clear interrupt Flag */
  LL_I2C_ClearFlagIT(I2Cx, I2C_ITIC_RXNE | I2C_ITIC_ADDR | I2C_ITIC_NACK | I2C_ITIC_STOP | I2C_ITIC_ERR);

  /* Enable EVT, RXNE and ERR interrupt */
  LL_I2C_EnableIT(I2Cx, I2C_ITEN_ADDR | I2C_ITEN_NACK | I2C_ITEN_STOP | I2C_ITEN_RXNE | I2C_ITEN_ERR);

  return SUCCESS;
}

/**
 * @brief NACK callback function
 * @param I2Cx 
 */
void LL_I2C_MasterNACKCpltCallback(reg_i2c_t *I2Cx)
{
  /* Clear AF flag */
  LL_I2C_Clearflag(I2Cx, I2C_CFR_NACKCF);

  /* Clear interrupt Flag */
  LL_I2C_ClearFlagIT(I2Cx, I2C_ICR_NACKIC_MASK);

  if (DataOfSize != 0)
  {
    /* Do not generate a STOP in case of Slave receive non acknowledge during transfer (mean not at the end of transfer) */
    /* Generate Stop */
    LL_I2C_GenerateStopCondition(I2Cx);
  }
}

/**
 * @brief Send  empty callback function
 * 
 * @param I2Cx 
 */
void LL_I2C_MasterTXECpltCallback(reg_i2c_t *I2Cx)
{
  if (DataOfSize == 0U)
  {
    /* Clear interrupt Flag */
    LL_I2C_ClearFlagIT(I2Cx, I2C_ITIC_TXE | I2C_ITIC_TC | I2C_ITIC_TCR);

    /* Disable EVT, TXE and ERR interrupt */
    LL_I2C_DisableIT(I2Cx, I2C_ITDEN_ADDR | I2C_ITDEN_STOP | I2C_ITDEN_TXE | I2C_ITDEN_ERR | I2C_ITDEN_TC);
    if (Com_Sta == txing)
    {
      Com_Sta = txover;
    }
    if (Com_Sta == txaddr)
    {
      Com_Sta = addrover;
    }
  }
  else
  {
    /* Write data to TXDR */
    LL_I2C_TransmitData8(I2Cx, *qBuf);

    /* Increment Buffer pointer */
    qBuf++;

    /* Update counter */
    DataOfSize--;
  }
}

/**
 * @brief Send the completion callback function
 * 
 * @param I2Cx 
 */
void LL_I2C_MasterTCRCpltCallback(reg_i2c_t *I2Cx)
{
  /* Clear interrupt Flag */
  // LL_I2C_ClearFlagIT_TCR(I2Cx);
  LL_I2C_ClearFlagIT(I2Cx, I2C_ITIC_TCR);

  LL_I2C_SetNumberOfByte(I2Cx, DataOfSize);
  LL_I2C_DisableRELOAD(I2Cx);
  LL_I2C_EnableAutoEnd(I2Cx);
}

/**
 * @brief Receive non-empty callback function
 * 
 * @param I2Cx 
 */
void LL_I2C_MasterRXNECpltCallback(reg_i2c_t *I2Cx)
{
  if (DataOfSize > 0)
  {
    /* Read data from RXDR */
    *qBuf = LL_I2C_ReceiveData8(I2Cx);
    DELAY_US(50);

    /* Increment Buffer pointer */
    qBuf++;

    /* Update counter */
    DataOfSize--;
  }
  if (DataOfSize == 0)
  {
    /* Clear interrupt Flag */
    LL_I2C_ClearFlagIT(I2Cx, I2C_ITIC_RXNE);

    /* Disable EVT, II2C_ITDEN_RXNE and ERR interrupt */
    LL_I2C_DisableIT(I2Cx, I2C_ITDEN_ADDR | I2C_ITDEN_NACK | I2C_ITDEN_STOP  | I2C_ITDEN_RXNE | I2C_ITDEN_ERR | I2C_ITDEN_TC | I2C_ITDEN_TCR);

    Com_Sta = rxover;
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
