#include "lsi2c.h"
#include "platform.h"
#include "io_config.h"
#include <string.h>
#include <stdlib.h>
#include "log.h"

#define I2C_ADDRESS 0x51			//EEPROM addr


/* I2C handler declaration */
static I2C_HandleTypeDef I2cHandle;

/* Buffer used for transmission */
static uint8_t aTxBuffer[10] = {0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xAA,};

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
    iic1_io_init(PB13, PB12);

        
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
	
    while(HAL_I2C_Mem_Write(&I2cHandle, (uint16_t)I2C_ADDRESS, 0x0040,I2C_MEMADD_SIZE_16BIT,(uint8_t*)aTxBuffer, 10, 1000)!= HAL_OK)
    {
        /* Error_Handler() function is called when Timeout error occurs.
            When Acknowledge failure occurs (Slave don't acknowledge its address)
            Master restarts communication */
        if (HAL_I2C_GetError(&I2cHandle) != HAL_I2C_ERROR_NONE)
        {
            Error_Handler();
        }
    }
    while(HAL_I2C_IsDeviceReady(&I2cHandle, (uint16_t)I2C_ADDRESS, 100, 1000)!= HAL_OK); 
          
    while(HAL_I2C_Mem_Read(&I2cHandle, (uint16_t)I2C_ADDRESS, 0x0040,I2C_MEMADD_SIZE_16BIT,(uint8_t*)aRxBuffer, 10, 1000)!= HAL_OK)
    {
        if (HAL_I2C_GetError(&I2cHandle) != HAL_I2C_ERROR_NONE)
        {
            Error_Handler();
        }
    }
	while( Buffercmp(aTxBuffer, aRxBuffer, 10))
	{
		;
	}

    LOG_I("success!!!");
  /* Infinite loop */
  while (1)
  {
		
  }
}


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

static void Error_Handler(void)
{
  while (1)
  {
		;
  }
}
