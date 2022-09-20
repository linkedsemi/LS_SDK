#include <stdio.h>
#include "ls_hal_i2c.h"
#include "ls_msp_i2c.h" 
#include "field_manipulate.h"
#include "log.h"
#include "systick.h"

#define I2C_FIFO_DEPTH 8
// #define I2C_CLOCK   (SDK_PCLK_MHZ*1000000)

#define I2C_TIMEOUT_FLAG          35U         /*!< Timeout 35 ms             */
#define I2C_TIMEOUT_BUSY_FLAG     25U         /*!< Timeout 25 ms             */
#define I2C_NO_OPTION_FRAME       0xFFFF0000U /*!< XferOptions default value */

#define I2C_STATE_MSK             ((uint32_t)((uint32_t)((uint32_t)HAL_I2C_STATE_BUSY_TX | (uint32_t)HAL_I2C_STATE_BUSY_RX) & (uint32_t)(~((uint32_t)HAL_I2C_STATE_READY)))) /*!< Mask State define, keep only RX and TX bits            */
#define I2C_STATE_NONE            ((uint32_t)(HAL_I2C_MODE_NONE))                                                        /*!< Default Value                                          */
#define I2C_STATE_MASTER_BUSY_TX  ((uint32_t)(((uint32_t)HAL_I2C_STATE_BUSY_TX & I2C_STATE_MSK) | (uint32_t)HAL_I2C_MODE_MASTER))            /*!< Master Busy TX, combinaison of State LSB and Mode enum */
#define I2C_STATE_MASTER_BUSY_RX  ((uint32_t)(((uint32_t)HAL_I2C_STATE_BUSY_RX & I2C_STATE_MSK) | (uint32_t)HAL_I2C_MODE_MASTER))            /*!< Master Busy RX, combinaison of State LSB and Mode enum */
#define I2C_STATE_SLAVE_BUSY_TX   ((uint32_t)(((uint32_t)HAL_I2C_STATE_BUSY_TX & I2C_STATE_MSK) | (uint32_t)HAL_I2C_MODE_SLAVE))             /*!< Slave Busy TX, combinaison of State LSB and Mode enum  */
#define I2C_STATE_SLAVE_BUSY_RX   ((uint32_t)(((uint32_t)HAL_I2C_STATE_BUSY_RX & I2C_STATE_MSK) | (uint32_t)HAL_I2C_MODE_SLAVE))             /*!< Slave Busy RX, combinaison of State LSB and Mode enum  */
#define __HAL_I2C_GET_TXFLV(__HANDLE__) (REG_FIELD_RD((__HANDLE__)->Instance->SR, I2C_SR_TXFLV))
#define __HAL_I2C_GET_RXFLV(__HANDLE__) (REG_FIELD_RD((__HANDLE__)->Instance->SR, I2C_SR_RXFLV))

#define I2C_FIFO_TX(__HANDLE__) while (__HAL_I2C_GET_TXFLV(__HANDLE__) < I2C_FIFO_DEPTH && (__HANDLE__)->XferCount > 0)           \
                                {                                                                                                 \
                                    (__HANDLE__)->Instance->TXDR = *(__HANDLE__)->pBuffPtr;                                       \
                                    (__HANDLE__)->pBuffPtr++;                                                                     \
                                    (__HANDLE__)->XferCount--;                                                                    \
                                }                                                                                                 

#define I2C_FIFO_RX(__HANDLE__) while (__HAL_I2C_GET_RXFLV(__HANDLE__) > 0 && (__HANDLE__)->XferCount > 0)                        \
                                {                                                                                                 \
                                    *(__HANDLE__)->pBuffPtr = (uint8_t)(__HANDLE__)->Instance->RXDR;                              \
                                    (__HANDLE__)->pBuffPtr++;                                                                     \
                                    (__HANDLE__)->XferCount--;                                                                    \
                                }

struct i2c_speed_config_t
{
    uint32_t scll     : 8;
    uint32_t sclh     : 8;
    uint32_t sdadel   : 4;
    uint32_t scldel   : 4;
    uint32_t reserved : 4;
    uint32_t presc    : 4;
};

struct i2c_speed_config_t i2c_speed_config_array[I2C_SPEED_MAX] = {
#if I2C_CLOCK == (64 * 1000000)
    [I2C_SPEED_NORMAL_100K] = {
        .scll = 212,
        .sclh = 101,
        .scldel = 15,
        .sdadel = 6,
        .presc = 1,
    },
    [I2C_SPEED_FAST_400K] = {
        .scll = 106,
        .sclh = 48,
        .scldel = 15,
        .sdadel = 4,
        .presc = 0,
    },
    [I2C_SPEED_FAST_ULTRA_1M] = {
        .scll = 38,
        .sclh = 19,
        .scldel = 11,
        .sdadel = 4,
        .presc = 0,
    },
#elif I2C_CLOCK == (16 * 1000000)
    [I2C_SPEED_NORMAL_100K] = {
        .scll = 106,
        .sclh = 48,
        .scldel = 15,
        .sdadel = 3,
        .presc = 0,
    },
    [I2C_SPEED_FAST_400K] = {
        .scll = 26,
        .sclh = 8,
        .scldel = 9,
        .sdadel = 2,
        .presc = 0,
    },
    [I2C_SPEED_FAST_ULTRA_1M] = {
        .scll = 10,
        .sclh = 0,
        .scldel = 5,
        .sdadel = 1,
        .presc = 0,
    },
#else

#endif
};

// volatile uint8_t TransferDirection = 0xff;
static void I2C_ITError(I2C_HandleTypeDef *hi2c);

static HAL_StatusTypeDef I2C_MasterRequestWrite(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint32_t Timeout, uint32_t Tickstart);
static HAL_StatusTypeDef I2C_MasterRequestRead(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint32_t Timeout, uint32_t Tickstart);
static HAL_StatusTypeDef I2C_RequestMemoryWrite(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint32_t Timeout, uint32_t Tickstart);
static HAL_StatusTypeDef I2C_RequestMemoryRead(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint32_t Timeout, uint32_t Tickstart);

static HAL_StatusTypeDef I2C_WaitOnFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Flag, FlagStatus Status, uint32_t Timeout, uint32_t Tickstart);
static HAL_StatusTypeDef I2C_WaitOnMasterAddressFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Flag, uint32_t Timeout, uint32_t Tickstart);
static HAL_StatusTypeDef I2C_WaitOnTXEFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Timeout, uint32_t Tickstart);
static HAL_StatusTypeDef I2C_WaitOnRXNEFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Timeout, uint32_t Tickstart);
static HAL_StatusTypeDef I2C_IsAcknowledgeFailed(I2C_HandleTypeDef *hi2c);
// static HAL_StatusTypeDef I2C_WaitOnSTOPFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Timeout, uint32_t Tickstart);
static HAL_StatusTypeDef I2C_WaitOnTCRFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Timeout, uint32_t Tickstart);

static void I2C_MasterTransmit_TXE(I2C_HandleTypeDef *hi2c);
static void I2C_MasterReceive_RXNE(I2C_HandleTypeDef *hi2c);
// static void I2C_Master_TCR(I2C_HandleTypeDef *hi2c);
static void I2C_SlaveTransmit_TXE(I2C_HandleTypeDef *hi2c);
static void I2C_SlaveReceive_RXNE(I2C_HandleTypeDef *hi2c);
// static void I2C_Slave_Receive_TCR(I2C_HandleTypeDef *hi2c);
// static void I2C_SlaveTransmit_TCR(I2C_HandleTypeDef *hi2c);
// static void I2C_SlaveReceive_TCR(I2C_HandleTypeDef *hi2c);
// static void I2C_Slave_ADDR(I2C_HandleTypeDef *hi2c, uint32_t IT2Flags);
static void I2C_ADDR(I2C_HandleTypeDef *hi2c, uint32_t sr1itflags);
static void I2C_STOPF(I2C_HandleTypeDef *hi2c);
// static void I2C_Slave_STOPF(I2C_HandleTypeDef *hi2c);
// static void I2C_Master_STOPF(I2C_HandleTypeDef *hi2c);
// static void I2C_Slave_NACK(I2C_HandleTypeDef *hi2c);

static bool i2c_flag_poll(va_list va);
// uint32_t ora2_data=0;
HAL_StatusTypeDef HAL_I2C_Init(I2C_HandleTypeDef *hi2c)
{
    /* Check the I2C handle allocation */
    if (hi2c == NULL)
    {
        return HAL_ERROR;
    }

    /* Check the parameters */
    LS_ASSERT(IS_I2C_ALL_INSTANCE(hi2c->Instance));
    LS_ASSERT(IS_I2C_CLOCK_SPEED(hi2c->Init.ClockSpeed));
    LS_ASSERT(IS_I2C_OWN_ADDRESS1(hi2c->Init.OwnAddress1));
    LS_ASSERT(IS_I2C_ADDRESSING_MODE(hi2c->Init.AddressingMode));
    LS_ASSERT(IS_I2C_DUAL_ADDRESS(hi2c->Init.DualAddressMode));
    LS_ASSERT(IS_I2C_OWN_ADDRESS2(hi2c->Init.OwnAddress2));
    LS_ASSERT(IS_I2C_GENERAL_CALL(hi2c->Init.GeneralCallMode));
    LS_ASSERT(IS_I2C_NO_STRETCH(hi2c->Init.NoStretchMode));

    if (hi2c->State == HAL_I2C_STATE_RESET)
    {
        /* Allocate lock resource and initialize it */
        hi2c->Lock = HAL_UNLOCKED;
    }

    HAL_I2C_MSP_Init(hi2c);
    HAL_I2C_MSP_Busy_Set(hi2c);

    hi2c->State = HAL_I2C_STATE_BUSY;

    /* Disable the selected I2C peripheral */
    __HAL_I2C_DISABLE(hi2c);

    struct i2c_speed_config_t speed_config = i2c_speed_config_array[hi2c->Init.ClockSpeed];

    MODIFY_REG(hi2c->Instance->TIMINGR, I2C_TIMINGR_PRESC_MASK, speed_config.presc << I2C_TIMINGR_PRESC_POS); 
    MODIFY_REG(hi2c->Instance->TIMINGR, (I2C_TIMINGR_SCLH_MASK | I2C_TIMINGR_SCLL_MASK | I2C_TIMINGR_SDADEL_MASK | I2C_TIMINGR_SCLDEL_MASK), 
                                        (speed_config.sclh<<I2C_TIMINGR_SCLH_POS\
                                        |speed_config.scll<<I2C_TIMINGR_SCLL_POS\
                                        |speed_config.sdadel<<I2C_TIMINGR_SDADEL_POS\
                                        |speed_config.scldel<<I2C_TIMINGR_SCLDEL_POS));

    /*---------------------------- I2Cx CR1 Configuration ----------------------*/
    /* Configure I2Cx: Generalcall and NoStretch mode */
    MODIFY_REG(hi2c->Instance->CR1, (I2C_CR1_GCEN_MASK | I2C_CR1_NOSTRETCH_MASK), (hi2c->Init.GeneralCallMode | hi2c->Init.NoStretchMode));

    /*---------------------------- I2Cx OAR1 Configuration ---------------------*/
    /* Configure I2Cx: Own Address1 and addressing mode */
    REG_FIELD_WR(hi2c->Instance->OAR1, I2C_OAR1_OA1EN, 0);
        
    if (hi2c->Init.AddressingMode == I2C_ADDRESSINGMODE_7BIT)
    {
        MODIFY_REG(hi2c->Instance->OAR1, (I2C_OAR1_OA1MODE_MASK | I2C_OAR1_OA18_9_MASK | I2C_OAR1_OA11_7_MASK | I2C_OAR1_OA10_MASK), (hi2c->Init.AddressingMode | (hi2c->Init.OwnAddress1<<1)));
    }
    else
    {
        MODIFY_REG(hi2c->Instance->OAR1, (I2C_OAR1_OA1MODE_MASK | I2C_OAR1_OA18_9_MASK | I2C_OAR1_OA11_7_MASK | I2C_OAR1_OA10_MASK), (hi2c->Init.AddressingMode | hi2c->Init.OwnAddress1));

    }
    REG_FIELD_WR(hi2c->Instance->OAR1, I2C_OAR1_OA1EN, 1);
    /*---------------------------- I2Cx OAR2 Configuration ---------------------*/
    /* Configure I2Cx: Dual mode and Own Address2 */
    if (hi2c->Init.DualAddressMode == I2C_DUALADDRESS_ENABLE)
    {
        REG_FIELD_WR(hi2c->Instance->OAR2, I2C_OAR2_OA2EN, 0);
        // ora2_data = (hi2c->Init.OwnAddress2 | hi2c->Init.Oar2msk_Mask);
        MODIFY_REG(hi2c->Instance->OAR2, (I2C_OAR2_OA21_7_MASK | I2C_OAR2_OA2MSK_MASK), ((hi2c->Init.OwnAddress2<<1) | hi2c->Init.Oar2msk_Mask<<8));
        REG_FIELD_WR(hi2c->Instance->OAR2, I2C_OAR2_OA2EN, 1);
    }

    __HAL_I2C_SBC_ENABLE(hi2c); // Enable SBC for slave by default

    __HAL_I2C_RXFTH_SET(hi2c, I2C_FIFO_DEPTH-1);
    
    /* Enable the selected I2C peripheral */
    __HAL_I2C_ENABLE(hi2c);

    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
    hi2c->State = HAL_I2C_STATE_READY;
    hi2c->PreviousState = I2C_STATE_NONE;
    hi2c->Mode = HAL_I2C_MODE_NONE;

    return HAL_OK;
}

HAL_StatusTypeDef HAL_I2C_DeInit(I2C_HandleTypeDef *hi2c)
{
    /* Check the I2C handle allocation */
    if (hi2c == NULL)
    {
        return HAL_ERROR;
    }

    /* Check the parameters */
    LS_ASSERT(IS_I2C_ALL_INSTANCE(hi2c->Instance));

    hi2c->State = HAL_I2C_STATE_BUSY;

    /* Disable the I2C Peripheral Clock */
    __HAL_I2C_DISABLE(hi2c);

    HAL_I2C_MSP_DeInit(hi2c);
    HAL_I2C_MSP_Idle_Set(hi2c);

    hi2c->ErrorCode     = HAL_I2C_ERROR_NONE;
    hi2c->State         = HAL_I2C_STATE_RESET;
    hi2c->PreviousState = I2C_STATE_NONE;
    hi2c->Mode          = HAL_I2C_MODE_NONE;

    /* Release Lock */
    __HAL_UNLOCK(hi2c);

    return HAL_OK;
}

HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
  /* Init tickstart for timeout management*/
  uint32_t tickstart = systick_get_value();
  uint32_t TxCount=0;
  if (hi2c->State == HAL_I2C_STATE_READY)
  {
    /* Wait until BUSY flag is reset */
    if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG, tickstart) != HAL_OK)
    {
      return HAL_BUSY;
    }

    /* Process Locked */
    __HAL_LOCK(hi2c);

    /* Check if the I2C is already enabled */
    if ((hi2c->Instance->CR1 & I2C_CR1_PE_MASK) != I2C_CR1_PE_MASK)
    {
      /* Enable I2C peripheral */
      __HAL_I2C_ENABLE(hi2c);
    }

    hi2c->State       = HAL_I2C_STATE_BUSY_TX;
    hi2c->Mode        = HAL_I2C_MODE_MASTER;
    hi2c->ErrorCode   = HAL_I2C_ERROR_NONE;

    /* Prepare transfer parameters */
    hi2c->pBuffPtr    = pData;
    hi2c->XferCount   = Size;
    hi2c->XferSize    = hi2c->XferCount;
    hi2c->XferOptions = I2C_NO_OPTION_FRAME;

    /* Clear SR Flag */   
    __HAL_I2C_CLEAR_SR(hi2c);
        
    /* Set NBYTES */        
    CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_AUTOEND_MASK | I2C_CR2_RELOAD_MASK | I2C_CR2_NBYTES_MASK);
    if(hi2c->XferSize > 0xFF)        
    {
        SET_BIT(hi2c->Instance->CR2, I2C_CR2_RELOAD_MASK | 0xFF0000);
    }
    else
        SET_BIT(hi2c->Instance->CR2, (((uint32_t)hi2c->XferSize)<<I2C_CR2_NBYTES_POS));
        
    /* Send Slave Address */
    if (I2C_MasterRequestWrite(hi2c, DevAddress, Timeout, tickstart) != HAL_OK)
    {
        __HAL_I2C_DISABLE(hi2c);
        return HAL_ERROR;
    }

    while (hi2c->XferCount > 0U)
    {
        /* Wait until TXE flag is set */
        if (I2C_WaitOnTXEFlagUntilTimeout(hi2c, Timeout, tickstart) != HAL_OK)
        {
            if (hi2c->ErrorCode == HAL_I2C_ERROR_NACKF)
            {
                /* Generate Stop */
                SET_BIT(hi2c->Instance->CR2, I2C_CR2_STOP_MASK);
            }
            __HAL_I2C_DISABLE(hi2c);
            return HAL_ERROR;
        }
        /* Write data to TXDR */
        hi2c->Instance->TXDR = *hi2c->pBuffPtr;

        /* Increment Buffer pointer */
        hi2c->pBuffPtr++;
        TxCount ++;

        /* Update counter */
        hi2c->XferCount--;

        /* Updata NBYTES */            
        if((TxCount == 255)&&(hi2c->Instance->CR2 & I2C_CR2_RELOAD_MASK))    
        {
            /* Wait until TCR flag is set */
            if (I2C_WaitOnTCRFlagUntilTimeout(hi2c, Timeout, tickstart) != HAL_OK)
            {
                __HAL_I2C_DISABLE(hi2c);
                return HAL_ERROR;
            }
            else
            {    
                TxCount = 0;    
                if(hi2c->XferCount > 0xFF)        
                {
                    MODIFY_REG(hi2c->Instance->CR2, I2C_CR2_NBYTES_MASK, 0xFF0000);
                }
                else
                {
                    MODIFY_REG(hi2c->Instance->CR2, I2C_CR2_NBYTES_MASK, (((uint32_t)hi2c->XferCount)<<I2C_CR2_NBYTES_POS));
                    CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_RELOAD_MASK);
                }    
                __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_TCR);        
            }
        }    
    }

    /* Generate Stop */
    SET_BIT(hi2c->Instance->CR2, I2C_CR2_STOP_MASK);

    /* Wait until STOP flag is set */
    if (I2C_WaitOnMasterAddressFlagUntilTimeout(hi2c, I2C_CR2_STOP_MASK, Timeout, tickstart) != HAL_OK)
    {
        __HAL_I2C_DISABLE(hi2c);
        return HAL_ERROR;
    }

    hi2c->State = HAL_I2C_STATE_READY;
    hi2c->Mode = HAL_I2C_MODE_NONE;

    /* Process Unlocked */
    __HAL_UNLOCK(hi2c);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_I2C_Master_Receive(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
  /* Init tickstart for timeout management*/
  uint32_t tickstart = systick_get_value();
  uint32_t RxCount=0;
  if (hi2c->State == HAL_I2C_STATE_READY)
  {
    if (Size == 0U)
    {
        return HAL_OK;
    }
        
    /* Wait until BUSY flag is reset */
    if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG, tickstart) != HAL_OK)
    {
      return HAL_BUSY;
    }

    /* Process Locked */
    __HAL_LOCK(hi2c);

    /* Check if the I2C is already enabled */
    if ((hi2c->Instance->CR1 & I2C_CR1_PE_MASK) != I2C_CR1_PE_MASK)
    {
      /* Enable I2C peripheral */
      __HAL_I2C_ENABLE(hi2c);
    }

    hi2c->State       = HAL_I2C_STATE_BUSY_RX;
    hi2c->Mode        = HAL_I2C_MODE_MASTER;
    hi2c->ErrorCode   = HAL_I2C_ERROR_NONE;

    /* Prepare transfer parameters */
    hi2c->pBuffPtr    = pData;
    hi2c->XferCount   = Size;
    hi2c->XferSize    = hi2c->XferCount;
    hi2c->XferOptions = I2C_NO_OPTION_FRAME;

         /* Clear SR Flag */   
    __HAL_I2C_CLEAR_SR(hi2c);
        
         /* Set NBYTES */        
    CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_AUTOEND_MASK | I2C_CR2_RELOAD_MASK | I2C_CR2_NBYTES_MASK);
    if(hi2c->XferSize > 0xFF)        
    {
        SET_BIT(hi2c->Instance->CR2, I2C_CR2_RELOAD_MASK | 0xFF0000);
    }
    else
        SET_BIT(hi2c->Instance->CR2, (((uint32_t)hi2c->XferSize)<<I2C_CR2_NBYTES_POS));
        
    /* Send Slave Address */
    if (I2C_MasterRequestRead(hi2c, DevAddress, Timeout, tickstart) != HAL_OK)
    {
        __HAL_I2C_DISABLE(hi2c);
        return HAL_ERROR;
    }
        
    if (hi2c->XferSize == 1U)
    {
        /* Disable NAck*/
        SET_BIT(hi2c->Instance->CR2, I2C_CR2_NACK_MASK);

        /* Generate Stop */
        SET_BIT(hi2c->Instance->CR2, I2C_CR2_STOP_MASK);

    }

    while (hi2c->XferCount > 0U)
    {
        /* Wait until RXNE flag is set */
        if (I2C_WaitOnRXNEFlagUntilTimeout(hi2c, Timeout, tickstart) != HAL_OK)
        {
            __HAL_I2C_DISABLE(hi2c);
            return HAL_ERROR;
        }

        /* Read data from DR */
        *hi2c->pBuffPtr = (uint8_t)hi2c->Instance->RXDR;

        /* Increment Buffer pointer */
        hi2c->pBuffPtr++;
        RxCount ++;

        /* Update counter */
        hi2c->XferCount--;
        
        if (hi2c->XferCount == 1U)
        {
            /* Disable NAck*/
            SET_BIT(hi2c->Instance->CR2, I2C_CR2_NACK_MASK);
            /* Generate Stop */
            SET_BIT(hi2c->Instance->CR2, I2C_CR2_STOP_MASK);

        }                
        /* Updata NBYTES */        
        if((RxCount == 255)&&(hi2c->Instance->CR2 & I2C_CR2_RELOAD_MASK))    
        {
            /* Wait until TCR flag is set */
            if (I2C_WaitOnTCRFlagUntilTimeout(hi2c, Timeout, tickstart) != HAL_OK)
            {
                __HAL_I2C_DISABLE(hi2c);
                return HAL_ERROR;
            }
            else
            {    
                RxCount = 0;    
                if(hi2c->XferCount > 0xFF)        
                {
                    MODIFY_REG(hi2c->Instance->CR2, I2C_CR2_NBYTES_MASK, 0xFF0000);
                }
                else
                {
                    MODIFY_REG(hi2c->Instance->CR2, I2C_CR2_NBYTES_MASK, (((uint32_t)hi2c->XferCount)<<I2C_CR2_NBYTES_POS));
                    CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_RELOAD_MASK);
                }    
                __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_TCR);        
            }
        }                
    }
    CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_AUTOEND_MASK | I2C_CR2_RELOAD_MASK | I2C_CR2_NBYTES_MASK);

    /* Wait until STOP flag is set */
    if (I2C_WaitOnMasterAddressFlagUntilTimeout(hi2c, I2C_CR2_STOP_MASK, Timeout, tickstart) != HAL_OK)
    {
        __HAL_I2C_DISABLE(hi2c);
        return HAL_ERROR;
    }

    hi2c->State = HAL_I2C_STATE_READY;
    hi2c->Mode = HAL_I2C_MODE_NONE;

    /* Process Unlocked */
    __HAL_UNLOCK(hi2c);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
  /* Init tickstart for timeout management*/
  uint32_t tickstart = systick_get_value();
  uint32_t TxCount=0;

  /* Check the parameters */
  LS_ASSERT(IS_I2C_MEMADD_SIZE(MemAddSize));

  if (hi2c->State == HAL_I2C_STATE_READY)
  {
    /* Wait until BUSY flag is reset */
    if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG, tickstart) != HAL_OK)
    {
      return HAL_BUSY;
    }

    /* Process Locked */
    __HAL_LOCK(hi2c);

    /* Check if the I2C is already enabled */
    if ((hi2c->Instance->CR1 & I2C_CR1_PE_MASK) != I2C_CR1_PE_MASK)
    {
      /* Enable I2C peripheral */
      __HAL_I2C_ENABLE(hi2c);
    }

    hi2c->State       = HAL_I2C_STATE_BUSY_TX;
    hi2c->Mode        = HAL_I2C_MODE_MASTER;
    hi2c->ErrorCode   = HAL_I2C_ERROR_NONE;

    /* Prepare transfer parameters */
    hi2c->pBuffPtr    = pData;
    hi2c->XferCount   = Size;
    hi2c->XferSize    = hi2c->XferCount;
    hi2c->XferOptions = I2C_NO_OPTION_FRAME;

    /* Clear SR Flag */   
    __HAL_I2C_CLEAR_SR(hi2c);

    /* Send Slave Address and Memory Address */
    if (I2C_RequestMemoryWrite(hi2c, DevAddress, MemAddress, MemAddSize, Timeout, tickstart) != HAL_OK)
    {
        __HAL_I2C_DISABLE(hi2c);
        return HAL_ERROR;
    }
    /* Wait until TCR flag is set */
    if (I2C_WaitOnTCRFlagUntilTimeout(hi2c, Timeout, tickstart) != HAL_OK)
    {
        __HAL_I2C_DISABLE(hi2c);
        return HAL_ERROR;
    }
    else
    {    
        TxCount = 0;    
        if(hi2c->XferCount > 0xFF)        
        {
            MODIFY_REG(hi2c->Instance->CR2, I2C_CR2_NBYTES_MASK, 0xFF0000);
        }
        else
        {
            MODIFY_REG(hi2c->Instance->CR2, I2C_CR2_NBYTES_MASK, (((uint32_t)hi2c->XferCount)<<I2C_CR2_NBYTES_POS));
            CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_RELOAD_MASK);
        }    
        __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_TCR);        
    }

    while (hi2c->XferCount > 0U)
    {
        /* Wait until TXE flag is set */
        if (I2C_WaitOnTXEFlagUntilTimeout(hi2c, Timeout, tickstart) != HAL_OK)
        {
            if (hi2c->ErrorCode == HAL_I2C_ERROR_NACKF)
            {
                /* Generate Stop */
                SET_BIT(hi2c->Instance->CR2, I2C_CR2_STOP_MASK);
            }
            __HAL_I2C_DISABLE(hi2c);
            return HAL_ERROR;
        }

        /* Write data to TXDR */
        hi2c->Instance->TXDR = *hi2c->pBuffPtr;

        /* Increment Buffer pointer */
        hi2c->pBuffPtr++;
        TxCount ++;

        /* Update counter */
        hi2c->XferCount--;
            
        /* Updata NBYTES */            
        if((TxCount == 255)&&(hi2c->Instance->CR2 & I2C_CR2_RELOAD_MASK))    
        {
            /* Wait until TCR flag is set */
            if (I2C_WaitOnTCRFlagUntilTimeout(hi2c, Timeout, tickstart) != HAL_OK)
            {
                __HAL_I2C_DISABLE(hi2c);
                return HAL_ERROR;
            }
            else
            {    
                TxCount = 0;    
                if(hi2c->XferCount > 0xFF)        
                {
                    MODIFY_REG(hi2c->Instance->CR2, I2C_CR2_NBYTES_MASK, 0xFF0000);
                }
                else
                {
                    MODIFY_REG(hi2c->Instance->CR2, I2C_CR2_NBYTES_MASK, (((uint32_t)hi2c->XferCount)<<I2C_CR2_NBYTES_POS));
                    CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_RELOAD_MASK);
                }    
                __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_TCR);        
            }
        }    
    }
    /* Generate Stop */
    SET_BIT(hi2c->Instance->CR2, I2C_CR2_STOP_MASK);

    /* Wait until STOP flag is set */
    if (I2C_WaitOnMasterAddressFlagUntilTimeout(hi2c, I2C_CR2_STOP_MASK, Timeout, tickstart) != HAL_OK)
    {
        __HAL_I2C_DISABLE(hi2c);
        return HAL_ERROR;
    }

    hi2c->State = HAL_I2C_STATE_READY;
    hi2c->Mode = HAL_I2C_MODE_NONE;

    /* Process Unlocked */
    __HAL_UNLOCK(hi2c);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}
HAL_StatusTypeDef HAL_I2C_Mem_Read(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
  /* Init tickstart for timeout management*/
  uint32_t tickstart = systick_get_value();
  uint32_t RxCount=0;

  /* Check the parameters */
  LS_ASSERT(IS_I2C_MEMADD_SIZE(MemAddSize));

  if (hi2c->State == HAL_I2C_STATE_READY)
  {
    if (Size == 0U)
    {
        return HAL_OK;
    }
    /* Wait until BUSY flag is reset */
    if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG, tickstart) != HAL_OK)
    {
        hi2c->ErrorCode   = HAL_I2C_ERROR_ARLO;
      return HAL_BUSY;
    }
    /* Process Locked */
    __HAL_LOCK(hi2c);
 
    /* Check if the I2C is already enabled */
    if ((hi2c->Instance->CR1 & I2C_CR1_PE_MASK) != I2C_CR1_PE_MASK)
    {
      /* Enable I2C peripheral */
      __HAL_I2C_ENABLE(hi2c);
    }

    hi2c->State       = HAL_I2C_STATE_BUSY_RX;
    hi2c->Mode        = HAL_I2C_MODE_MASTER;
    hi2c->ErrorCode   = HAL_I2C_ERROR_NONE;

    /* Prepare transfer parameters */
    hi2c->pBuffPtr    = pData;
    hi2c->XferCount   = Size;
    hi2c->XferSize    = hi2c->XferCount;
    hi2c->XferOptions = I2C_NO_OPTION_FRAME;

         /* Clear SR Flag */   
    __HAL_I2C_CLEAR_SR(hi2c);
    
    /* Send Slave Address and Memory Address */
    if (I2C_RequestMemoryRead(hi2c, DevAddress, MemAddress, MemAddSize, Timeout, tickstart) != HAL_OK)
    {
        __HAL_I2C_DISABLE(hi2c);
        return HAL_ERROR;
    }

    /* Set NBYTES */        
    CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_AUTOEND_MASK | I2C_CR2_RELOAD_MASK | I2C_CR2_NBYTES_MASK);
    if(hi2c->XferSize > 0xFF)        
    {
        SET_BIT(hi2c->Instance->CR2, I2C_CR2_RELOAD_MASK | 0xFF0000);
    }
    else
        SET_BIT(hi2c->Instance->CR2, (((uint32_t)hi2c->XferSize)<<I2C_CR2_NBYTES_POS));

    /* Send Slave Address */
    if (I2C_MasterRequestRead(hi2c, DevAddress, Timeout, tickstart) != HAL_OK)
    {
        return HAL_ERROR;
    }

    if (hi2c->XferSize == 1U)
    {
        /* Disable NAck*/
        SET_BIT(hi2c->Instance->CR2, I2C_CR2_NACK_MASK);
        /* Generate Stop */
        SET_BIT(hi2c->Instance->CR2, I2C_CR2_STOP_MASK);
    }

    while (hi2c->XferCount > 0U)
    {
        /* Wait until RXNE flag is set */
        if (I2C_WaitOnRXNEFlagUntilTimeout(hi2c, Timeout, tickstart) != HAL_OK)
        {
            __HAL_I2C_DISABLE(hi2c);
            return HAL_ERROR;
        }

        /* Read data from DR */
        *hi2c->pBuffPtr = (uint8_t)hi2c->Instance->RXDR;

        /* Increment Buffer pointer */
        hi2c->pBuffPtr++;
        RxCount ++;

        /* Update counter */
        hi2c->XferCount--;
        
        if (hi2c->XferCount == 1U)
        {
            /* Disable NAck*/
            SET_BIT(hi2c->Instance->CR2, I2C_CR2_NACK_MASK);
            /* Generate Stop */
            SET_BIT(hi2c->Instance->CR2, I2C_CR2_STOP_MASK);

        }                
        /* Updata NBYTES */        
        if((RxCount == 255)&&(hi2c->Instance->CR2 & I2C_CR2_RELOAD_MASK))    
        {
            /* Wait until TCR flag is set */
            if (I2C_WaitOnTCRFlagUntilTimeout(hi2c, Timeout, tickstart) != HAL_OK)
            {
                __HAL_I2C_DISABLE(hi2c);
                return HAL_ERROR;
            }
            else
            {    
                RxCount = 0;    
                if(hi2c->XferCount > 0xFF)        
                {
                    MODIFY_REG(hi2c->Instance->CR2, I2C_CR2_NBYTES_MASK, 0xFF0000);
                }
                else
                {
                    MODIFY_REG(hi2c->Instance->CR2, I2C_CR2_NBYTES_MASK, (((uint32_t)hi2c->XferCount)<<I2C_CR2_NBYTES_POS));
                    CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_RELOAD_MASK);
                }    
                __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_TCR);        
            }
        }                
    }
    CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_AUTOEND_MASK | I2C_CR2_RELOAD_MASK | I2C_CR2_NBYTES_MASK);

    /* Wait until STOP flag is set */
    if (I2C_WaitOnMasterAddressFlagUntilTimeout(hi2c, I2C_CR2_STOP_MASK, Timeout, tickstart) != HAL_OK)
    {
        __HAL_I2C_DISABLE(hi2c);
        return HAL_ERROR;
    }

    hi2c->State = HAL_I2C_STATE_READY;
    hi2c->Mode = HAL_I2C_MODE_NONE;

    /* Process Unlocked */
    __HAL_UNLOCK(hi2c);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_I2C_IsDeviceReady(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint32_t Trials, uint32_t Timeout)
{
  /* Get tick */
  uint32_t tickstart = systick_get_value();
  uint32_t I2C_Trials = 1U;


  if (hi2c->State == HAL_I2C_STATE_READY)
  {
    /* Wait until BUSY flag is reset */
    if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG, tickstart) != HAL_OK)
    {
      return HAL_BUSY;
    }

    /* Process Locked */
    __HAL_LOCK(hi2c);

    /* Check if the I2C is already enabled */
    if ((hi2c->Instance->CR1 & I2C_CR1_PE_MASK) != I2C_CR1_PE_MASK)
    {
      /* Enable I2C peripheral */
      __HAL_I2C_ENABLE(hi2c);
    }

    hi2c->State = HAL_I2C_STATE_BUSY;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
    hi2c->XferOptions = I2C_NO_OPTION_FRAME;

    do
    {
        /* Clear SR Flag */   
        __HAL_I2C_CLEAR_SR(hi2c);
        /* Send Slave Address */
        if (I2C_MasterRequestWrite(hi2c, DevAddress, Timeout, tickstart) != HAL_OK)
        {
            /* Generate Stop */
            SET_BIT(hi2c->Instance->CR2, I2C_CR2_STOP_MASK);

            __HAL_I2C_DISABLE(hi2c);
            /* Process Unlocked */
            __HAL_UNLOCK(hi2c);
            return HAL_ERROR;
        }
        if(systick_poll_timeout(tickstart,Timeout,i2c_flag_poll,hi2c,I2C_FLAG_TXE,RESET))
        {
            hi2c->PreviousState       = I2C_STATE_NONE;
            hi2c->State               = HAL_I2C_STATE_READY;
            hi2c->Mode                = HAL_I2C_MODE_NONE;
            hi2c->ErrorCode           |= HAL_I2C_ERROR_TIMEOUT;

            /* Process Unlocked */
            __HAL_UNLOCK(hi2c);

            return HAL_ERROR;
        }
        /* Generate Stop */
        SET_BIT(hi2c->Instance->CR2, I2C_CR2_STOP_MASK);
        /* Wait until STOP flag is set */
        if(systick_poll_timeout(tickstart,Timeout,i2c_flag_poll,hi2c,I2C_SR_STOPF_MASK,RESET))
        {
            __HAL_I2C_DISABLE(hi2c);
            /* Process Unlocked */
            __HAL_UNLOCK(hi2c);
            return HAL_ERROR;
        }

        /* Check if a NACK is detected */
        if (I2C_IsAcknowledgeFailed(hi2c) == HAL_OK)
        {
            break;
        }

        /* Increment Trials */
        I2C_Trials++;
    }
    while (I2C_Trials < Trials);

    hi2c->State = HAL_I2C_STATE_READY;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
    /* Process Unlocked */
    __HAL_UNLOCK(hi2c);

    if(I2C_Trials < Trials)
        return HAL_OK;
    else
        return HAL_ERROR;
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_I2C_Master_Transmit_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
    if (hi2c->State == HAL_I2C_STATE_READY)
    {
        /* Process Locked */
        __HAL_LOCK(hi2c);

        /* Check if the I2C is already enabled */
        if ((hi2c->Instance->CR1 & I2C_CR1_PE_MASK) != I2C_CR1_PE_MASK)
        {
            /* Enable I2C peripheral */
            __HAL_I2C_ENABLE(hi2c);
        }

        hi2c->State     = HAL_I2C_STATE_BUSY_TX;
        hi2c->Mode      = HAL_I2C_MODE_MASTER;
        hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

        /* Prepare transfer parameters */
        hi2c->pBuffPtr    = pData;
        hi2c->XferCount   = Size;
        hi2c->XferSize    = hi2c->XferCount;
        hi2c->XferOptions = I2C_NO_OPTION_FRAME;
        hi2c->Devaddress  = DevAddress;

        /* Set Reload */  
        CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_AUTOEND_MASK | I2C_CR2_RELOAD_MASK | I2C_CR2_NBYTES_MASK);
        if(hi2c->XferSize > 0xFF)        
        {
            SET_BIT(hi2c->Instance->CR2, I2C_CR2_RELOAD_MASK | 0xFF0000);
        }
        else
            SET_BIT(hi2c->Instance->CR2, I2C_CR2_AUTOEND_MASK | (((uint32_t)hi2c->XferSize)<<I2C_CR2_NBYTES_POS));

        if (hi2c->Init.AddressingMode == I2C_ADDRESSINGMODE_7BIT)
        {
            /* Send slave address */
            CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_SADD10_MASK);
            MODIFY_REG(hi2c->Instance->CR2, I2C_CR2_RD_WEN_MASK | I2C_CR2_SADD1_7_MASK,(DevAddress<<1)&0xFE);
        }
        else
        {
            /* Send header of slave address */
            SET_BIT(hi2c->Instance->CR2, I2C_CR2_SADD10_MASK);
            MODIFY_REG(hi2c->Instance->CR2, I2C_CR2_RD_WEN_MASK | I2C_CR2_SADD0_MASK | I2C_CR2_SADD1_7_MASK | I2C_CR2_SADD8_9_MASK,DevAddress&0x3FF);
            CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_HEAD10R_MASK);

        }
        /* Clear SR Flag */   
        __HAL_I2C_CLEAR_SR(hi2c);
        /* Clear interrupt Flag */   
        __HAL_I2C_CLEAR_IF(hi2c, I2C_IT_EVT | I2C_IT_TXE | I2C_IT_ERR | I2C_IT_TCR | I2C_IT_TC);

        // __HAL_I2C_DISABLE_IT(hi2c, I2C_IDR_ADDRID_MASK); 

        if ((hi2c->XferCount > 0U) && (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_TXE) == SET))
        {
            /* Write data to TXDR */
            hi2c->Instance->TXDR = *hi2c->pBuffPtr;

            /* Increment Buffer pointer */
            hi2c->pBuffPtr++;

            /* Update counter */
            hi2c->XferCount--;
        }
            
        /* Enable EVT, TXE and ERR interrupt */
        __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_TXE | I2C_IT_ERR);
            
        if(hi2c->XferSize > 0xFF)        
            __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_TCR);
        else        
            __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_TC);
            
        /* Generate Start */
        SET_BIT(hi2c->Instance->CR2, I2C_CR2_START_MASK);

        /* Process Unlocked */
        __HAL_UNLOCK(hi2c);

        return HAL_OK;
    }
    else
    {
        return HAL_BUSY;
    }
}

HAL_StatusTypeDef HAL_I2C_Master_Receive_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
    if (hi2c->State == HAL_I2C_STATE_READY)
    {
        /* Process Locked */
        __HAL_LOCK(hi2c);

        /* Check if the I2C is already enabled */
        if ((hi2c->Instance->CR1 & I2C_CR1_PE_MASK) != I2C_CR1_PE_MASK)
        {
        /* Enable I2C peripheral */
        __HAL_I2C_ENABLE(hi2c);
        }

        hi2c->State     = HAL_I2C_STATE_BUSY_RX;
        hi2c->Mode      = HAL_I2C_MODE_MASTER;
        hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

        /* Prepare transfer parameters */
        hi2c->pBuffPtr    = pData;
        hi2c->XferCount   = Size;
        hi2c->XferSize    = hi2c->XferCount;
        hi2c->XferOptions = I2C_NO_OPTION_FRAME;
        hi2c->Devaddress  = DevAddress;

        /* Set Reload */  
        CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_AUTOEND_MASK | I2C_CR2_RELOAD_MASK | I2C_CR2_NBYTES_MASK);

        if(hi2c->XferSize > 0xFF)        
        {
            SET_BIT(hi2c->Instance->CR2, I2C_CR2_RELOAD_MASK | 0xFF0000);
        }
        else
            SET_BIT(hi2c->Instance->CR2, I2C_CR2_AUTOEND_MASK | (((uint32_t)hi2c->XferSize)<<I2C_CR2_NBYTES_POS));
        
        if (hi2c->Init.AddressingMode == I2C_ADDRESSINGMODE_7BIT)
        {
            /* Send slave address */
            CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_SADD10_MASK);
            MODIFY_REG(hi2c->Instance->CR2, I2C_CR2_RD_WEN_MASK | I2C_CR2_SADD1_7_MASK,I2C_CR2_RD_WEN_MASK | ((DevAddress<<1)&0xFE));
        }
        else
        {
            /* Send header of slave address */
            SET_BIT(hi2c->Instance->CR2, I2C_CR2_SADD10_MASK);
            MODIFY_REG(hi2c->Instance->CR2, I2C_CR2_RD_WEN_MASK | I2C_CR2_SADD0_MASK | I2C_CR2_SADD1_7_MASK | I2C_CR2_SADD8_9_MASK,\
                                                                            I2C_CR2_RD_WEN_MASK | (DevAddress&0x3FF));
            CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_HEAD10R_MASK);

        }
            
        /* Generate Start */
        SET_BIT(hi2c->Instance->CR2, I2C_CR2_START_MASK);

        /* Process Unlocked */
        __HAL_UNLOCK(hi2c);

            /* Clear SR Flag */   
        __HAL_I2C_CLEAR_SR(hi2c);
            /* Clear interrupt Flag */   
        __HAL_I2C_CLEAR_IF(hi2c, I2C_IT_EVT | I2C_IT_RXNE | I2C_IT_ERR);
            
        /* Enable EVT, RXNE and ERR interrupt */
        __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_RXNE | I2C_IT_ERR);
            
        // if(hi2c->XferSize >255)        
        //     __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_TCR);
        // else        
        //     __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_TC);
        return HAL_OK;
    }
    else
    {
        return HAL_BUSY;
    }
}

HAL_StatusTypeDef HAL_I2C_Slave_Transmit_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size)
{
    if (hi2c->State == HAL_I2C_STATE_READY)
    {
        if (pData == NULL)
        {
            return HAL_ERROR;
        }

        /* Process Locked */
        __HAL_LOCK(hi2c);

        /* Check if the I2C is already enabled */
        if ((hi2c->Instance->CR1 & I2C_CR1_PE_MASK) != I2C_CR1_PE_MASK)
        {
            /* Enable I2C peripheral */
            __HAL_I2C_ENABLE(hi2c);
        }

        hi2c->State = HAL_I2C_STATE_BUSY_TX;
        hi2c->Mode = HAL_I2C_MODE_SLAVE;
        hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

        /* Prepare transfer parameters */
        hi2c->pBuffPtr = pData;
        hi2c->XferCount = Size;
        hi2c->XferSize = hi2c->XferCount;
        hi2c->XferOptions = I2C_NO_OPTION_FRAME;

        /* Process Unlocked */
        __HAL_UNLOCK(hi2c);

        /* Enable Address Acknowledge */
        CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_NACK_MASK);

        /* Clear SR Flag */
        __HAL_I2C_CLEAR_SR(hi2c);
        /* Clear interrupt Flag */
        __HAL_I2C_CLEAR_IF(hi2c, I2C_IT_EVT | I2C_IT_TXE | I2C_IT_ERR);
        
        if ((hi2c->XferCount > 0U) && (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_TXE) == SET))
        {
            /* Write data to TXDR */
            hi2c->Instance->TXDR = *hi2c->pBuffPtr;

            /* Increment Buffer pointer */
            hi2c->pBuffPtr++;

            /* Update counter */
            hi2c->XferCount--;
        }
        __HAL_I2C_DISABLE_IT(hi2c, I2C_IT_TCR); 
        /* Enable EVT, TXE and ERR interrupt */
        __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_TXE | I2C_IT_ERR);
        return HAL_OK;
    }
    else
    {
        return HAL_BUSY;
    }
}

HAL_StatusTypeDef HAL_I2C_Slave_Receive_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size)
{
    if (hi2c->State == HAL_I2C_STATE_READY)
    {
        if ((pData == NULL) || (Size == 0))
        {
            return HAL_ERROR;
        }

        /* Process Locked */
        __HAL_LOCK(hi2c);

        if ((hi2c->Instance->CR1 & I2C_CR1_PE_MASK) != I2C_CR1_PE_MASK)
        {
            /* Enable I2C peripheral */
            __HAL_I2C_ENABLE(hi2c);
        }

        hi2c->State = HAL_I2C_STATE_BUSY_RX;
        hi2c->Mode = HAL_I2C_MODE_SLAVE;
        hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

        /* Prepare transfer parameters */
        hi2c->pBuffPtr = pData;
        hi2c->XferCount = Size;
        hi2c->XferSize    = hi2c->XferCount;
        hi2c->XferOptions = I2C_NO_OPTION_FRAME;

        if (1 == Size)
        {
            SET_BIT(hi2c->Instance->CR2, I2C_CR2_NACK_MASK); // Enable data NAK
        }
        else
        {
            __HAL_I2C_NBYTES_SET(hi2c, Size - 1);
        }

        __HAL_I2C_ENABLE(hi2c);

        /* Enable Address Acknowledge */
        CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_NACK_MASK);
        
        /* Process Unlocked */
        __HAL_UNLOCK(hi2c);
        
        /* Clear SR Flag */
        __HAL_I2C_CLEAR_SR(hi2c);
        /* Clear interrupt Flag */
        __HAL_I2C_CLEAR_IF(hi2c, I2C_IT_EVT | I2C_IT_RXNE | I2C_IT_TCR | I2C_IT_ERR);
        /* Enable EVT, RXNE and ERR interrupt */
        __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_RXNE | I2C_IT_TCR | I2C_IT_ERR);

        return HAL_OK;
    }
    else
    {
        return HAL_BUSY;
    }
}

HAL_StatusTypeDef HAL_I2C_EnableListen_IT(I2C_HandleTypeDef *hi2c)
{
    if (hi2c->State == HAL_I2C_STATE_READY)
    {
        hi2c->Mode = HAL_I2C_MODE_SLAVE; // set mode to slave
        hi2c->State = HAL_I2C_STATE_LISTEN;
        /* Check if the I2C is already enabled */
        if ((hi2c->Instance->CR1 & I2C_CR1_PE_MASK) != I2C_CR1_PE_MASK)
        {
            /* Enable I2C peripheral */
            __HAL_I2C_ENABLE(hi2c);
        }
        /* Enable Address Acknowledge */
        CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_NACK_MASK);

        __HAL_I2C_NBYTES_SET(hi2c, 1);
        // __HAL_I2C_RELOAD_ENABLE(hi2c);

        /* Enable EVT and ERR interrupt */
        __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_ERR);

        return HAL_OK;
    }
    else
    {
        return HAL_BUSY;
    }
}

HAL_StatusTypeDef HAL_I2C_DisableListen_IT(I2C_HandleTypeDef *hi2c)
{
    /* Declaration of tmp to prevent undefined behavior of volatile usage */
    uint32_t tmp;

    /* Disable Address listen mode only if a transfer is not ongoing */
    if (hi2c->State == HAL_I2C_STATE_LISTEN)
    {
        tmp = (uint32_t)(hi2c->State) & I2C_STATE_MSK;
        hi2c->PreviousState = tmp | (uint32_t)(hi2c->Mode);
        hi2c->State = HAL_I2C_STATE_READY;
        hi2c->Mode = HAL_I2C_MODE_NONE;

        /* Disable Address Acknowledge */
        SET_BIT(hi2c->Instance->CR2, I2C_CR2_NACK_MASK);

        /* Disable EVT and ERR interrupt */
        __HAL_I2C_DISABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_ERR);

        return HAL_OK;
    }
    else
    {
        return HAL_BUSY;
    }
}

HAL_StatusTypeDef HAL_I2C_Master_Abort_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(DevAddress);

  /* Abort Master transfer during Receive or Transmit process    */
  if (hi2c->Mode == HAL_I2C_MODE_MASTER)
  {
    /* Process Locked */
    __HAL_LOCK(hi2c);

    hi2c->PreviousState = I2C_STATE_NONE;
    hi2c->State = HAL_I2C_STATE_ABORT;

    /* Disable Acknowledge */
    SET_BIT(hi2c->Instance->CR2, I2C_CR2_NACK_MASK);

    /* Generate Stop */
    SET_BIT(hi2c->Instance->CR2, I2C_CR2_STOP_MASK);

    hi2c->XferCount = 0U;

    /* Clear SR Flag */
    __HAL_I2C_CLEAR_SR(hi2c);
    /* Clear interrupt Flag */
    __HAL_I2C_CLEAR_IF(hi2c, I2C_IT_EVT | I2C_IT_RXNE | I2C_IT_TXE | I2C_IT_ERR);

    /* Disable EVT, I2C_IT_RXNE, I2C_IT_TXE and ERR interrupt */
    __HAL_I2C_DISABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_RXNE | I2C_IT_TXE | I2C_IT_ERR);

    /* Process Unlocked */
    __HAL_UNLOCK(hi2c);

    /* Call the corresponding callback to inform upper layer of End of Transfer */
    I2C_ITError(hi2c);

    return HAL_OK;
  }
  else
  {
    /* Wrong usage of abort function */
    /* This function should be used only in case of abort monitored by master device */
    return HAL_ERROR;
  }
}

void HAL_I2C_IRQHandler(I2C_HandleTypeDef *hi2c)
{
    uint32_t sr1itflags = hi2c->Instance->SR;
    uint32_t itsources  = hi2c->Instance->IFM;
    // uint32_t cr1 = hi2c->Instance->CR1;

    HAL_I2C_StateTypeDef CurrentState = hi2c->State;
    uint32_t error      = HAL_I2C_ERROR_NONE;

    if (hi2c->Mode == HAL_I2C_MODE_MASTER)
    {
        if (I2C_CHECK_IT_SOURCE(itsources, I2C_IER_ADDRIE_MASK) != RESET)
        {
            I2C_ADDR(hi2c, sr1itflags);
        }
        else if (I2C_CHECK_IT_SOURCE(itsources, I2C_IER_STOPIE_MASK) != RESET)
        {
            __HAL_I2C_CLEAR_IF(hi2c, I2C_ICR_STOPIC_MASK); 
            I2C_STOPF(hi2c);
        }
        else if (CurrentState == HAL_I2C_STATE_BUSY_TX)
        {
            if (I2C_CHECK_IT_SOURCE(itsources, I2C_IT_TXE) != RESET)
            {
                __HAL_I2C_CLEAR_IF(hi2c, I2C_ICR_TXEIC_MASK);
                I2C_MasterTransmit_TXE(hi2c);
            }
        }
        else if (CurrentState == HAL_I2C_STATE_BUSY_RX)
        {
            if (I2C_CHECK_IT_SOURCE(itsources, I2C_IT_RXNE) != RESET)
            {
                __HAL_I2C_CLEAR_IF(hi2c, I2C_ICR_RXNEIC_MASK); 
                I2C_MasterReceive_RXNE(hi2c);
            }
        }
    }
    else
    {
        /* Check ADDR flag */
        if (I2C_CHECK_IT_SOURCE(itsources, I2C_IER_ADDRIE_MASK) != RESET)
        {
            I2C_ADDR(hi2c, sr1itflags);
        }
        else if (I2C_CHECK_IT_SOURCE(itsources, I2C_IER_STOPIE_MASK) != RESET)
        {
            /* Clear interrupt Flag */   
            __HAL_I2C_CLEAR_IF(hi2c, I2C_ICR_STOPIC_MASK);
            I2C_STOPF(hi2c);
        }/* Slave transmit*/
        else if (CurrentState == HAL_I2C_STATE_BUSY_TX)
        {
            if (I2C_CHECK_IT_SOURCE(itsources, I2C_IT_TXE) != RESET)
            {
                __HAL_I2C_CLEAR_IF(hi2c, I2C_ICR_TXEIC_MASK); 
                I2C_SlaveTransmit_TXE(hi2c);
            }
        }/* Slave receive*/
        else if (CurrentState == HAL_I2C_STATE_BUSY_RX)
        {
            if (I2C_CHECK_IT_SOURCE(itsources, I2C_IT_RXNE) != RESET)
            {
                __HAL_I2C_CLEAR_IF(hi2c, I2C_ICR_RXNEIC_MASK); 
                I2C_SlaveReceive_RXNE(hi2c);
            }
        }
    }

    /* Check NACK flag */
    if (I2C_CHECK_IT_SOURCE(itsources, I2C_IER_NACKIE_MASK) != RESET)
    {
        __HAL_I2C_CLEAR_IF(hi2c, I2C_ICR_NACKIC_MASK); 
        if (I2C_CHECK_FLAG(sr1itflags, I2C_FLAG_NACK) != RESET)
        {
            __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_NACK);
        }
    }
    
    /* Call the Error Callback in case of Error detected -----------------------*/
    if (error != HAL_I2C_ERROR_NONE)
    {
        hi2c->ErrorCode |= error;
        I2C_ITError(hi2c);
    }    
}

__weak void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hi2c);
}

__weak void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hi2c);
}

__weak void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hi2c);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_I2C_SlaveTxCpltCallback could be implemented in the user file
   */
}

__weak void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hi2c);
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_I2C_SlaveRxCpltCallback could be implemented in the user file
   */
}

__weak void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hi2c);
  UNUSED(TransferDirection);
  UNUSED(AddrMatchCode);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_I2C_AddrCallback() could be implemented in the user file
   */
}

__weak void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hi2c);
}

__weak void HAL_I2C_AbortCpltCallback(I2C_HandleTypeDef *hi2c)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hi2c);
}

HAL_I2C_StateTypeDef HAL_I2C_GetState(I2C_HandleTypeDef *hi2c)
{
  /* Return I2C handle state */
  return hi2c->State;
}

HAL_I2C_ModeTypeDef HAL_I2C_GetMode(I2C_HandleTypeDef *hi2c)
{
  return hi2c->Mode;
}

uint32_t HAL_I2C_GetError(I2C_HandleTypeDef *hi2c)
{
  return hi2c->ErrorCode;
}

static void I2C_MasterTransmit_TXE(I2C_HandleTypeDef *hi2c)
{
    I2C_FIFO_TX(hi2c);
}

static void I2C_MasterReceive_RXNE(I2C_HandleTypeDef *hi2c)
{
    I2C_FIFO_RX(hi2c);
}

// static void I2C_Master_TCR(I2C_HandleTypeDef *hi2c)
// {
//     if (hi2c->XferCount > 0xFF)
//     {
//         MODIFY_REG(hi2c->Instance->CR2, I2C_CR2_NBYTES_MASK, ((uint32_t)0x0000FF)<<I2C_CR2_NBYTES_POS);
//         SET_BIT(hi2c->Instance->CR2, I2C_CR2_RELOAD_MASK);
//     }
//     else 
//     {
//         MODIFY_REG(hi2c->Instance->CR2, I2C_CR2_NBYTES_MASK, ((uint32_t)hi2c->XferCount)<<I2C_CR2_NBYTES_POS);
//         CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_RELOAD_MASK);
//         SET_BIT(hi2c->Instance->CR2, I2C_CR2_AUTOEND_MASK);
//     }
// }

/**
  * @brief  Handle TXE flag for Slave
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *         the configuration information for I2C module
  * @retval None
  */
static void I2C_SlaveTransmit_TXE(I2C_HandleTypeDef *hi2c)
{
    I2C_FIFO_TX(hi2c);
}

/**
  * @brief  Handle RXNE flag for Slave
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *         the configuration information for I2C module
  * @retval None
  */
static void I2C_SlaveReceive_RXNE(I2C_HandleTypeDef *hi2c)
{
    if (hi2c->XferCount <= I2C_FIFO_DEPTH + I2C_FIFO_DEPTH && hi2c->XferCount > I2C_FIFO_DEPTH)
    {
        __HAL_I2C_RELOAD_ENABLE(hi2c);
        __HAL_I2C_NBYTES_SET(hi2c, hi2c->XferCount - 1 - I2C_FIFO_DEPTH);
        __HAL_I2C_RELOAD_DISABLE(hi2c);
    }
    else if (hi2c->XferCount == I2C_FIFO_DEPTH)
    {
        __HAL_I2C_RELOAD_ENABLE(hi2c);
        __HAL_I2C_NBYTES_SET(hi2c, 0);
        __HAL_I2C_RELOAD_DISABLE(hi2c);
    }

    I2C_FIFO_RX(hi2c);
}

static void I2C_ADDR(I2C_HandleTypeDef *hi2c, uint32_t sr1itflags)
{ 
    __HAL_I2C_CLEAR_IF(hi2c, I2C_ICR_ADDRIC_MASK);
    __HAL_I2C_CLEAR_ADDRFLAG(hi2c);
    uint8_t dir = ((sr1itflags & I2C_SR_DIR_MASK) >> I2C_SR_DIR_POS) == 0? I2C_DIRECTION_RECEIVE : I2C_DIRECTION_TRANSMIT;
    uint16_t addrCode = (sr1itflags & I2C_SR_ADDCODE_MASK) >> I2C_SR_ADDCODE_POS;
    HAL_I2C_AddrCallback(hi2c, dir, addrCode);
    if (hi2c->State == HAL_I2C_STATE_BUSY_TX)
    {
        I2C_FIFO_TX(hi2c);
    }
}

static void I2C_STOPF(I2C_HandleTypeDef *hi2c)
{
    HAL_I2C_StateTypeDef CurrentState = hi2c->State;

    /* Disable EVT and ERR interrupt */
        __HAL_I2C_DISABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_RXNE | I2C_IT_TXE | I2C_IT_TC | I2C_IT_ERR);
        __HAL_I2C_CLEAR_STOPFLAG(hi2c);

    if (hi2c->XferCount != 0U)
    {
        if (CurrentState == HAL_I2C_STATE_BUSY_RX)
        {
            I2C_FIFO_RX(hi2c); // read remained data in RX FIFO if any
        }
        else if (CurrentState == HAL_I2C_STATE_BUSY_TX)
        {
            hi2c->XferCount += __HAL_I2C_GET_TXFLV(hi2c); // check bytes unsent in FIFO
        }

        if (hi2c->XferCount != 0U)
        {
            hi2c->ErrorCode |= HAL_I2C_ERROR_SIZE;
        }
    }

    if (hi2c->ErrorCode != HAL_I2C_ERROR_NONE)
    {
        // I2C_ITError(hi2c); // handle error at the end of irq handler
    }
    else
    {
        if (CurrentState == HAL_I2C_STATE_BUSY_TX)
        {
            if (hi2c->Mode == HAL_I2C_MODE_MASTER)
            {
                HAL_I2C_MasterTxCpltCallback(hi2c);
            }
            else
            {
                HAL_I2C_SlaveTxCpltCallback(hi2c);
                // HAL_I2C_Init(hi2c); // workaround xxx
            }
        }
        else if (CurrentState == HAL_I2C_STATE_BUSY_RX)
        {
            if (hi2c->Mode == HAL_I2C_MODE_MASTER)
            {
                HAL_I2C_MasterRxCpltCallback(hi2c);
            }
            else
            {
                HAL_I2C_SlaveRxCpltCallback(hi2c);
                HAL_I2C_Init(hi2c); // workaround xxx
            }
        }
        hi2c->PreviousState = I2C_STATE_NONE;
        hi2c->Mode = HAL_I2C_MODE_NONE;
        hi2c->State = HAL_I2C_STATE_READY;
        }
    }
static void I2C_ITError(I2C_HandleTypeDef *hi2c)
{
    if (hi2c->State == HAL_I2C_STATE_ABORT)
    {
        hi2c->State = HAL_I2C_STATE_READY;
        hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

        if (hi2c->XferCount > 0)
        {
            I2C_FIFO_RX(hi2c);
        }

        __HAL_I2C_DISABLE(hi2c);

        HAL_I2C_AbortCpltCallback(hi2c);
    }
    else
    {
        /* Handle last data if any */
        if (hi2c->XferCount > 0)
        {
            if (hi2c->State == HAL_I2C_STATE_BUSY_TX)
            {
                I2C_FIFO_TX(hi2c);
            }
            else if (hi2c->State == HAL_I2C_STATE_BUSY_RX)
            {
                I2C_FIFO_RX(hi2c);
            }
        }
        /* Call user error callback */
        HAL_I2C_ErrorCallback(hi2c);
    }
}

static HAL_StatusTypeDef I2C_MasterRequestWrite(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint32_t Timeout, uint32_t Tickstart)
{
  /* Declaration of temporary variable to prevent undefined behavior of volatile usage */
  uint32_t CurrentXferOptions = hi2c->XferOptions;

  if (hi2c->Init.AddressingMode == I2C_ADDRESSINGMODE_7BIT)
  {
    /* Send slave address */
    CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_SADD10_MASK);
    MODIFY_REG(hi2c->Instance->CR2, I2C_CR2_RD_WEN_MASK | I2C_CR2_SADD1_7_MASK,(DevAddress<<1)&0xFE);
  }
  else
  {
    /* Send header of slave address */
    SET_BIT(hi2c->Instance->CR2, I2C_CR2_SADD10_MASK);
    MODIFY_REG(hi2c->Instance->CR2, I2C_CR2_RD_WEN_MASK | I2C_CR2_SADD0_MASK | I2C_CR2_SADD1_7_MASK | I2C_CR2_SADD8_9_MASK,DevAddress&0x3FF);
    CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_HEAD10R_MASK);

  }

  /* Generate Start condition if first transfer */
  if ((CurrentXferOptions == I2C_FIRST_AND_LAST_FRAME) || (CurrentXferOptions == I2C_FIRST_FRAME) || (CurrentXferOptions == I2C_NO_OPTION_FRAME))
  {
    /* Generate Start */
    SET_BIT(hi2c->Instance->CR2, I2C_CR2_START_MASK);
  }
  else if (hi2c->PreviousState == I2C_STATE_MASTER_BUSY_RX)
  {
    /* Generate ReStart */
    SET_BIT(hi2c->Instance->CR2, I2C_CR2_START_MASK);
  }
  else
  {
    /* Do nothing */
  }

  /* Wait until ADDR flag is set */
  if (I2C_WaitOnMasterAddressFlagUntilTimeout(hi2c, I2C_CR2_START_MASK, Timeout, Tickstart) != HAL_OK)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

static HAL_StatusTypeDef I2C_MasterRequestRead(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint32_t Timeout, uint32_t Tickstart)
{
  /* Declaration of temporary variable to prevent undefined behavior of volatile usage */
  uint32_t CurrentXferOptions = hi2c->XferOptions;

  /* Enable Ack*/
  // CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_NACK_MASK);

  if (hi2c->Init.AddressingMode == I2C_ADDRESSINGMODE_7BIT)
  {
    /* Send slave address */
    CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_SADD10_MASK);
    MODIFY_REG(hi2c->Instance->CR2, I2C_CR2_RD_WEN_MASK | I2C_CR2_SADD1_7_MASK,I2C_CR2_RD_WEN_MASK | ((DevAddress<<1)&0xFE));
  }
  else
  {
    /* Send header of slave address */
    SET_BIT(hi2c->Instance->CR2, I2C_CR2_SADD10_MASK);
    MODIFY_REG(hi2c->Instance->CR2, I2C_CR2_RD_WEN_MASK | I2C_CR2_SADD0_MASK | I2C_CR2_SADD1_7_MASK | I2C_CR2_SADD8_9_MASK,I2C_CR2_RD_WEN_MASK | (DevAddress&0x3FF));
    CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_HEAD10R_MASK);
  }

  /* Generate Start condition if first transfer */
  if ((CurrentXferOptions == I2C_FIRST_AND_LAST_FRAME) || (CurrentXferOptions == I2C_FIRST_FRAME)  || (CurrentXferOptions == I2C_NO_OPTION_FRAME))
  {
    /* Generate Start */
    SET_BIT(hi2c->Instance->CR2, I2C_CR2_START_MASK);
  }
  else if (hi2c->PreviousState == I2C_STATE_MASTER_BUSY_TX)
  {
    /* Generate ReStart */
    SET_BIT(hi2c->Instance->CR2, I2C_CR2_START_MASK);
  }
  else
  {
    /* Do nothing */
  }

  /* Wait until ADDR flag is set */
  if (I2C_WaitOnMasterAddressFlagUntilTimeout(hi2c, I2C_CR2_START_MASK, Timeout, Tickstart) != HAL_OK)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

static bool i2c_flag_poll(va_list va)
{
    I2C_HandleTypeDef *hi2c = va_arg(va,I2C_HandleTypeDef *);
    uint32_t flag = va_arg(va,uint32_t);
    uint32_t Status = va_arg(va,uint32_t);
    if (__HAL_I2C_GET_FLAG(hi2c, flag) != Status)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static HAL_StatusTypeDef I2C_WaitOnFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Flag, FlagStatus Status, uint32_t Timeout, uint32_t Tickstart)
{
    uint32_t timeout = SYSTICK_MS2TICKS(Timeout);

    /* Wait until flag is set */
    if (Timeout != HAL_MAX_DELAY)
    {
        if(systick_poll_timeout(Tickstart,timeout,i2c_flag_poll,hi2c,Flag,Status))
        {
            hi2c->PreviousState     = I2C_STATE_NONE;
            hi2c->State             = HAL_I2C_STATE_READY;
            hi2c->Mode              = HAL_I2C_MODE_NONE;
            hi2c->ErrorCode         |= HAL_I2C_ERROR_TIMEOUT;

            /* Process Unlocked */
            __HAL_UNLOCK(hi2c);

            return HAL_ERROR;
        }
    }
    else
    {
        while (__HAL_I2C_GET_FLAG(hi2c, Flag) == Status)
        {
            ;
        }

    }
    return HAL_OK;
}

static bool i2c_CR2flag_poll(va_list va)
{
      I2C_HandleTypeDef *hi2c = va_arg(va,I2C_HandleTypeDef *);
      uint32_t flag = va_arg(va,uint32_t);
      if (__HAL_I2C_GET_CR2_FLAG(hi2c, flag) == RESET)
      {
        return true;
      }
      else
      {
        return false;
      }
}

static HAL_StatusTypeDef I2C_WaitOnMasterAddressFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Flag, uint32_t Timeout, uint32_t Tickstart)
{
    uint32_t timeout = SYSTICK_MS2TICKS(Timeout);

    /* Check for the Timeout */
    if (Timeout != HAL_MAX_DELAY)
    {
        if(systick_poll_timeout(Tickstart,timeout,i2c_CR2flag_poll,hi2c,Flag))
        {
            hi2c->PreviousState       = I2C_STATE_NONE;
            hi2c->State               = HAL_I2C_STATE_READY;
            hi2c->Mode                = HAL_I2C_MODE_NONE;
            hi2c->ErrorCode           |= HAL_I2C_ERROR_TIMEOUT;

            /* Process Unlocked */
            __HAL_UNLOCK(hi2c);

            return HAL_ERROR;
        }
    }
    else
    {
        while (__HAL_I2C_GET_CR2_FLAG(hi2c,Flag)  == SET)
        {
            /* Check if a NACK is detected */
            if (I2C_IsAcknowledgeFailed(hi2c) != HAL_OK)
            {
                return HAL_ERROR;
            }
        }

    }   
   return HAL_OK;
}

static bool i2c_flagandnack_poll(va_list va)
{
    I2C_HandleTypeDef *hi2c = va_arg(va, I2C_HandleTypeDef *);
    uint32_t flag = va_arg(va, uint32_t);
    if (__HAL_I2C_GET_FLAG(hi2c, flag) != RESET)
    {
        return true;
    }
    else
    {
        /* Check if a NACK is detected */
        if (I2C_IsAcknowledgeFailed(hi2c) != HAL_OK)
        {
            return true;
        }
        return false;
    }
}

static HAL_StatusTypeDef I2C_WaitOnTXEFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Timeout, uint32_t Tickstart)
{
    uint32_t timeout = SYSTICK_MS2TICKS(Timeout);

    /* Wait until flag is set */
    if (Timeout != HAL_MAX_DELAY)
    {
        if(systick_poll_timeout(Tickstart,timeout,i2c_flagandnack_poll,hi2c,I2C_FLAG_TXE))
        {
            hi2c->PreviousState       = I2C_STATE_NONE;
            hi2c->State               = HAL_I2C_STATE_READY;
            hi2c->Mode                = HAL_I2C_MODE_NONE;
            hi2c->ErrorCode           |= HAL_I2C_ERROR_TIMEOUT;

            /* Process Unlocked */
            __HAL_UNLOCK(hi2c);

            return HAL_ERROR;
        }
        if(hi2c->ErrorCode == HAL_I2C_ERROR_NACKF)
        {
            return HAL_ERROR;
        }
    }
    else
    {
        while (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_TXE) == RESET)
        {
            /* Check if a NACK is detected */
            if (I2C_IsAcknowledgeFailed(hi2c) != HAL_OK)
            {
                return HAL_ERROR;
            }
        }

    }
    return HAL_OK;
}

/**
  * @brief  This function handles I2C Communication Timeout for specific usage of STOP flag.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  Timeout Timeout duration
  * @param  Tickstart Tick start value
  * @retval HAL status
  */
// static HAL_StatusTypeDef I2C_WaitOnSTOPFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Timeout, uint32_t Tickstart)
// {
//   while (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_STOPF) == RESET)
//   {
//     /* Check if a NACK is detected */
//     if (I2C_IsAcknowledgeFailed(hi2c) != HAL_OK)
//     {
//       return HAL_ERROR;
//     }

//     /* Check for the Timeout */
//     if (((systick_get_value() - Tickstart) > Timeout) || (Timeout == 0U))
//     {
//       hi2c->PreviousState = I2C_STATE_NONE;
//       hi2c->State = HAL_I2C_STATE_READY;
//       hi2c->Mode = HAL_I2C_MODE_NONE;
//       hi2c->ErrorCode |= HAL_I2C_ERROR_TIMEOUT;

//       /* Process Unlocked */
//       __HAL_UNLOCK(hi2c);

//       return HAL_ERROR;
//     }
//   }
//   return HAL_OK;
// }

static bool i2c_flagandstop_poll(va_list va)
{
    I2C_HandleTypeDef *hi2c = va_arg(va,I2C_HandleTypeDef *);
    uint32_t flag = va_arg(va,uint32_t);
    if (__HAL_I2C_GET_FLAG(hi2c, flag) != RESET)
    {
        return true;
    }
    else
    {
        /* Check if a STOPF is detected */
        if (__HAL_I2C_GET_FLAG(hi2c, I2C_SR_STOPF_MASK) == SET)
        {
            /* Clear STOP Flag */
            __HAL_I2C_CLEAR_FLAG(hi2c, I2C_CFR_STOPCF_MASK);

            hi2c->PreviousState = I2C_STATE_NONE;
            hi2c->State = HAL_I2C_STATE_READY;
            hi2c->Mode = HAL_I2C_MODE_NONE;
            hi2c->ErrorCode = HAL_I2C_ERROR_BERR;

            /* Process Unlocked */
            __HAL_UNLOCK(hi2c);

            return true;
        }
        return false;
    }
}


static HAL_StatusTypeDef I2C_WaitOnRXNEFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Timeout, uint32_t Tickstart)
{
    uint32_t timeout = SYSTICK_MS2TICKS(Timeout);

    if (Timeout != HAL_MAX_DELAY)
    {
        if(systick_poll_timeout(Tickstart,timeout,i2c_flagandstop_poll,hi2c,I2C_SR_RXNE_MASK))
        {
            hi2c->PreviousState       = I2C_STATE_NONE;
            hi2c->State               = HAL_I2C_STATE_READY;
            hi2c->Mode                = HAL_I2C_MODE_NONE;
            hi2c->ErrorCode           |= HAL_I2C_ERROR_TIMEOUT;

            /* Process Unlocked */
            __HAL_UNLOCK(hi2c);

            return HAL_ERROR;
        }
        if(hi2c->ErrorCode == HAL_I2C_ERROR_BERR)
        {
            hi2c->ErrorCode |= HAL_I2C_ERROR_NONE;
            return HAL_ERROR;
        }
    }
    else
    {
        while (__HAL_I2C_GET_FLAG(hi2c, I2C_SR_RXNE_MASK) == RESET)
        {
            /* Check if a NACK is detected */
            if (I2C_IsAcknowledgeFailed(hi2c) != HAL_OK)
            {
                return HAL_ERROR;
            }
        }

    }  
    return HAL_OK;
}

static HAL_StatusTypeDef I2C_IsAcknowledgeFailed(I2C_HandleTypeDef *hi2c)
{
  if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_NACK) == SET)
  {
    /* Clear NACKF Flag */
    __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_NACK);

    hi2c->PreviousState       = I2C_STATE_NONE;
    hi2c->State               = HAL_I2C_STATE_READY;
    hi2c->Mode                = HAL_I2C_MODE_NONE;
    hi2c->ErrorCode           = HAL_I2C_ERROR_NACKF;

    /* Process Unlocked */
    __HAL_UNLOCK(hi2c);

    return HAL_ERROR;
  }
  return HAL_OK;
}

static HAL_StatusTypeDef I2C_WaitOnTCRFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Timeout, uint32_t Tickstart)
{
    uint32_t timeout = SYSTICK_MS2TICKS(Timeout);

    if (Timeout != HAL_MAX_DELAY)
    {
        if(systick_poll_timeout(Tickstart,timeout,i2c_flagandstop_poll,hi2c,I2C_SR_TCR_MASK))
        {
            hi2c->PreviousState       = I2C_STATE_NONE;
            hi2c->State               = HAL_I2C_STATE_READY;
            hi2c->Mode                = HAL_I2C_MODE_NONE;
            hi2c->ErrorCode           |= HAL_I2C_ERROR_TIMEOUT;

            /* Process Unlocked */
            __HAL_UNLOCK(hi2c);

            return HAL_ERROR;
        }
        if(hi2c->ErrorCode == HAL_I2C_ERROR_BERR)
        {
            hi2c->ErrorCode |= HAL_I2C_ERROR_NONE;
            return HAL_ERROR;
        }
    }
    else
    {
        while (__HAL_I2C_GET_FLAG(hi2c, I2C_SR_TCR_MASK) == RESET)
        {

        }

    }  
    return HAL_OK;
}

static HAL_StatusTypeDef I2C_RequestMemoryWrite(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint32_t Timeout, uint32_t Tickstart)
{
    /* Set NBYTES */        
    CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_AUTOEND_MASK | I2C_CR2_RELOAD_MASK | I2C_CR2_NBYTES_MASK);
    SET_BIT(hi2c->Instance->CR2, I2C_CR2_RELOAD_MASK);
    if(MemAddSize == I2C_MEMADD_SIZE_8BIT)        
    {
        SET_BIT(hi2c->Instance->CR2, 0x010000);
    }
    else
    {
        SET_BIT(hi2c->Instance->CR2, 0x020000);
    }
    
    /* Send Slave Address */
    if (I2C_MasterRequestWrite(hi2c, DevAddress, Timeout, Tickstart) != HAL_OK)
    {
        __HAL_I2C_DISABLE(hi2c);
        return HAL_ERROR;
    }
    /* Wait until TXE flag is set */
    if (I2C_WaitOnTXEFlagUntilTimeout(hi2c, Timeout, Tickstart) != HAL_OK)
    {
        if (hi2c->ErrorCode == HAL_I2C_ERROR_NACKF)
        {
            /* Generate Stop */
            SET_BIT(hi2c->Instance->CR2, I2C_CR2_STOP_MASK);
        }
        return HAL_ERROR;
    }

    if(MemAddSize == I2C_MEMADD_SIZE_8BIT)        
    {
        /* Send Memory Address */
        hi2c->Instance->TXDR = I2C_MEM_ADD_LSB(MemAddress);
    }
    /* If Memory address size is 16Bit */
    else
    {
        /* Send MSB of Memory Address */
        hi2c->Instance->TXDR = I2C_MEM_ADD_MSB(MemAddress);

        /* Wait until TXE flag is set */
        if (I2C_WaitOnTXEFlagUntilTimeout(hi2c, Timeout, Tickstart) != HAL_OK)
        {
            if (hi2c->ErrorCode == HAL_I2C_ERROR_NACKF)
            {
                /* Generate Stop */
                SET_BIT(hi2c->Instance->CR2, I2C_CR2_STOP_MASK);
            }
            return HAL_ERROR;
        }
        /* Send LSB of Memory Address */
        hi2c->Instance->TXDR = I2C_MEM_ADD_LSB(MemAddress);
    }

  return HAL_OK;
}

static HAL_StatusTypeDef I2C_RequestMemoryRead(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint32_t Timeout, uint32_t Tickstart)
{

    /* Set NBYTES */        
  CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_AUTOEND_MASK | I2C_CR2_RELOAD_MASK | I2C_CR2_NBYTES_MASK);
  /* If Memory address size is 8Bit */
  if (MemAddSize == I2C_MEMADD_SIZE_8BIT)
  {
    SET_BIT(hi2c->Instance->CR2, 0x010000);
  }
  else
    SET_BIT(hi2c->Instance->CR2, 0x020000);

  /* Send Slave Address */
  if (I2C_MasterRequestWrite(hi2c, DevAddress, Timeout, Tickstart) != HAL_OK)
  {
    __HAL_I2C_DISABLE(hi2c);
    return HAL_ERROR;
  }
  /* Clear ADDR flag */
  __HAL_I2C_CLEAR_ADDRFLAG(hi2c);

  /* Wait until TXE flag is set */
  if (I2C_WaitOnTXEFlagUntilTimeout(hi2c, Timeout, Tickstart) != HAL_OK)
  {
    if (hi2c->ErrorCode == HAL_I2C_ERROR_NACKF)
    {
        /* Generate Stop */
        SET_BIT(hi2c->Instance->CR2, I2C_CR2_STOP_MASK);
    }
    return HAL_ERROR;
  }

  /* If Memory address size is 8Bit */
  if (MemAddSize == I2C_MEMADD_SIZE_8BIT)
  {
    /* Send Memory Address */
    hi2c->Instance->TXDR = I2C_MEM_ADD_LSB(MemAddress);
  }
  /* If Memory address size is 16Bit */
  else
  {
    /* Send MSB of Memory Address */
    hi2c->Instance->TXDR = I2C_MEM_ADD_MSB(MemAddress);

    /* Wait until TXE flag is set */
    if (I2C_WaitOnTXEFlagUntilTimeout(hi2c, Timeout, Tickstart) != HAL_OK)
    {
        if (hi2c->ErrorCode == HAL_I2C_ERROR_NACKF)
        {
            /* Generate Stop */
            SET_BIT(hi2c->Instance->CR2, I2C_CR2_STOP_MASK);
        }
        return HAL_ERROR;
    }
    /* Send LSB of Memory Address */
    hi2c->Instance->TXDR = I2C_MEM_ADD_LSB(MemAddress);
  }

  /* Wait until TXE flag is set */
  if (I2C_WaitOnTXEFlagUntilTimeout(hi2c, Timeout, Tickstart) != HAL_OK)
  {
    if (hi2c->ErrorCode == HAL_I2C_ERROR_NACKF)
    {
        /* Generate Stop */
        SET_BIT(hi2c->Instance->CR2, I2C_CR2_STOP_MASK);
    }
    return HAL_ERROR;
  }

  return HAL_OK;
}



