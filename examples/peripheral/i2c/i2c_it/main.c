#include "lsi2c.h"
#include "platform.h"
#include "io_config.h"
#include <string.h>
#include <stdlib.h>
#include "log.h"

#define I2C_ADDRESS 0x51			//EEPROM addr

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

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* I2C handler declaration */
static I2C_HandleTypeDef I2cHandle;

/* Buffer used for transmission */
static uint8_t aTxBuffer[12] = {0x00,0x10,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xAA,};

/* Buffer used for reception */
static uint8_t aRxBuffer[10];

/* Private function prototypes -----------------------------------------------*/
static void Error_Handler(void);
static uint16_t Buffercmp(uint8_t* pBuff1, uint8_t* pBuff2, uint16_t Length);

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
  iic1_io_init( PB13, PB12);

	
  /*##-1- Configure the I2C peripheral ######################################*/
  I2cHandle.Instance             = I2C1;
  I2cHandle.Init.ClockSpeed      = 100000;
  I2cHandle.Init.OwnAddress1     = I2C_ADDRESS;
  I2cHandle.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
  I2cHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  I2cHandle.Init.OwnAddress2     = 0xFE;
  I2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  I2cHandle.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;  
  
  if(HAL_I2C_Init(&I2cHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
	
  /* The board sends the message and expects to receive it back */
  
  /*##-2- Start the transmission process #####################################*/  
  /* While the I2C in reception process, user can transmit data through 
     "aTxBuffer" buffer */
  /* Timeout is set to 1S */
	Com_Sta = txing;
    while(HAL_I2C_Master_Transmit_IT(&I2cHandle, (uint16_t)I2C_ADDRESS, (uint8_t*)aTxBuffer, 12)!= HAL_OK)
    {
            ;
    }

	while(Com_Sta == txing);
	
	for(uint32_t i=0;i<100;i++)
		DELAY_US(500);

	Com_Sta = txaddr;
    while(HAL_I2C_Master_Transmit_IT(&I2cHandle, (uint16_t)I2C_ADDRESS, (uint8_t*)aTxBuffer, 2)!= HAL_OK)
    {
        ;
    }
 	while(Com_Sta == txaddr);
	Com_Sta = rxing;
    while(HAL_I2C_Master_Receive_IT(&I2cHandle, (uint16_t)I2C_ADDRESS, (uint8_t*)aRxBuffer, 10)!= HAL_OK)
    {
        ;
    }
	while(Com_Sta == rxing);	

	while( Buffercmp(aTxBuffer+2, aRxBuffer, 10))
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
static uint16_t Buffercmp(uint8_t* pBuff1, uint8_t* pBuff2, uint16_t Length)
{
  while (Length--)
  {
    if((*pBuff1) != *pBuff2)
    {
      return Length;
    }
    pBuff1++;
    pBuff2++;
  }

  return 0;
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

void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
  if(Com_Sta == txing)
     Com_Sta = txover;
  if(Com_Sta == txaddr)
     Com_Sta = addrover;
}
 void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
{	
  Com_Sta = rxover;
}
