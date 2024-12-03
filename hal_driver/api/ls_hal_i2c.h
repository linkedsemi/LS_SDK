#ifndef __LS_HAL_I2C_H
#define __LS_HAL_I2C_H

#include <stdbool.h>
#include "HAL_def.h"
#include "ls_dbg.h"
#include "ls_ll_i2c.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup PERIPHERAL
 *  @{
 */

/** \addtogroup LSI2C
 *  @{
 */
                        
/** @defgroup I2C_Error_Code I2C Error Code
  * @{
  */
#define HAL_I2C_ERROR_NONE              0x00000000U    /*!< No error              */
#define HAL_I2C_ERROR_BERR              0x00000001U    /*!< BERR error            */
#define HAL_I2C_ERROR_ARLO              0x00000002U    /*!< ARLO error            */
#define HAL_I2C_ERROR_NACKF             0x00000004U    /*!< NACK error            */
#define HAL_I2C_ERROR_OVR               0x00000008U    /*!< OVR error             */
#define HAL_I2C_ERROR_DMA               0x00000010U    /*!< DMA transfer error    */
#define HAL_I2C_ERROR_TIMEOUT           0x00000020U    /*!< Timeout Error         */
#define HAL_I2C_ERROR_SIZE              0x00000040U    /*!< Size Management error */
#define HAL_I2C_ERROR_DMA_PARAM         0x00000080U    /*!< DMA Parameter Error   */
/**
  * @}
  */

#define HAL_I2C_POLL_TIMEOUT_MS 10

/**
 *  @defgroup I2C_addressing_mode I2C addressing mode.
 */
#define I2C_ADDRESSINGMODE_7BIT         0x00000000U             /*!< 7bits addressing mode   */
#define I2C_ADDRESSINGMODE_10BIT        I2C_OAR1_OA1MODE_MASK   /*!< 10bits addressing mode   */

/**
 *  @defgroup I2C_dual_addressing_mode  I2C dual addressing mode.
 */
#define I2C_DUALADDRESS_DISABLE        0x00000000U              /*!< Disable I2C dual addressing mode   */
#define I2C_DUALADDRESS_ENABLE         I2C_OAR2_OA2EN_MASK      /*!< Enable I2C dual addressing mode   */

/**
 *  @defgroup I2C_general_call_addressing_mode I2C general call addressing mode.
 */
#define I2C_GENERALCALL_DISABLE        0x00000000U              /*!< Disable I2C general call addressing mode   */
#define I2C_GENERALCALL_ENABLE         I2C_CR1_GCEN_MASK        /*!< Enable I2C general call addressing mode   */

/**
 *  @defgroup I2C_nostretch_mode I2C nostretch mode.
 */ 
#define I2C_NOSTRETCH_DISABLE          0x00000000U              /*!< Disable I2C nostretch mode.   */
#define I2C_NOSTRETCH_ENABLE           I2C_CR1_NOSTRETCH_MASK   /*!< Disable I2C nostretch mode.   */

/** 
  * @defgroup I2C_Memory_Address_Size I2C Memory Address Size
  */
#define I2C_MEMADD_SIZE_8BIT            0x00000001U
#define I2C_MEMADD_SIZE_16BIT           0x00000010U

#define __HAL_I2C_CLR_TXDR(__HANDLE__) (((__HANDLE__)->Instance->SR) |= (1 << 0))

 /**
  * @brief  I2C Configuration Structure definition
  */
typedef struct
{
  uint32_t OwnAddress1:10,
          OA1_Enable:1, 
          OA1_10bitMode:1, 
          OA2_Enable:1,
          OwnAddress2:7,
          OA2Mask:3;
  enum i2c_speed ClockSpeed;
} I2C_InitTypeDef;

enum i2c_state
{
  HAL_I2C_STATE_BUSY_TX = 0x1,
  HAL_I2C_STATE_BUSY_RX = 0x2,
  HAL_I2C_STATE_NEED_RESTART = 0x4,
  HAL_I2C_STATE_LISTEN  = 0x8,
};

enum i2c_dir
{
  HAL_I2C_WRITE_DIR = 0x0,
  HAL_I2C_READ_DIR = 0x1,
};

/**
 *  @brief I2C Interrupt Environment.
 */
struct I2cTransferEnv
{
    uint8_t                       *pBuffPtr;      /*!< Pointer to I2C transfer Buffer */
    uint16_t                      XferCount;      /*!< I2C Transfer Counter          */
};

struct i2c_timing
{
    uint8_t scll;
    uint8_t sclh;
    uint8_t sdadel:4,
            scldel:4;
    uint8_t presc:4;
};

/**
 *  @brief I2C_handle_Structure_definition I2C handle Structure definition.
 */
typedef struct __I2C_HandleTypeDef
{
  reg_i2c_t                	*Instance;      /*!< I2C registers base address               */

  I2C_InitTypeDef            Init;           /*!< I2C communication parameters             */

  struct I2cTransferEnv Tx_Env,Rx_Env;

  struct i2c_timing timing_param;

  uint8_t                    State;

} I2C_HandleTypeDef;

 
HAL_StatusTypeDef HAL_I2C_Init(I2C_HandleTypeDef *hi2c);

HAL_StatusTypeDef HAL_I2C_DeInit(I2C_HandleTypeDef *hi2c);

HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint8_t Size);

HAL_StatusTypeDef HAL_I2C_Master_Receive(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint8_t Size);

HAL_StatusTypeDef HAL_I2C_Mem_Read(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress,uint16_t MemAddSize, uint8_t *pData, uint16_t Size);

HAL_StatusTypeDef HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress,uint16_t MemAddSize, uint8_t *pData, uint16_t Size);

HAL_StatusTypeDef HAL_I2C_Master_Transmit_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint8_t Size);

HAL_StatusTypeDef HAL_I2C_Master_Receive_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint8_t Size);

HAL_StatusTypeDef HAL_I2C_Mem_Read_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress,uint16_t MemAddSize, uint8_t *pData, uint16_t Size);

HAL_StatusTypeDef HAL_I2C_Mem_Write_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress,uint16_t MemAddSize, uint8_t *pData, uint16_t Size);

HAL_StatusTypeDef HAL_I2C_EnableListen_IT(I2C_HandleTypeDef *hi2c);

HAL_StatusTypeDef HAL_I2C_DisableListen_IT(I2C_HandleTypeDef *hi2c);

HAL_StatusTypeDef HAL_I2C_Slave_Seq_Receive_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size);

HAL_StatusTypeDef HAL_I2C_Slave_Seq_Transmit_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size);

void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c);

void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c);

void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *hi2c);

void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c);

void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode);

void HAL_I2C_IRQHandler(I2C_HandleTypeDef *hi2c);

/** @}*/


/** @}*/

#ifdef __cplusplus
}
#endif

#endif /* __le501x_HAL_I2C_H */


