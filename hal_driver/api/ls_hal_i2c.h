#ifndef __LS_HAL_I2C_H
#define __LS_HAL_I2C_H

#include <stdbool.h>
#include "HAL_def.h"
#include "ls_dbg.h"
#include "ls_ll_i2c.h"

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
  uint32_t ClockSpeed;       /*!< Specifies the clock frequency.
                                  This parameter must be set to a value lower than 1MHz */

  uint32_t OwnAddress1;      /*!< Specifies the first device own address.
                                  This parameter can be a 7-bit or 10-bit address. */

  uint32_t AddressingMode;   /*!< Specifies if 7-bit or 10-bit addressing mode is selected.
                                  This parameter can be a value of @ref I2C_addressing_mode */

  uint32_t DualAddressMode;  /*!< Specifies if dual addressing mode is selected.
                                  This parameter can be a value of @ref I2C_dual_addressing_mode */

  uint32_t OwnAddress2;      /*!< Specifies the second device own address if dual addressing mode is selected
                                  This parameter can be a 7-bit address. */
	
  uint32_t Oar2msk_Mask;

  uint32_t GeneralCallMode;  /*!< Specifies if general call mode is selected.
                                  This parameter can be a value of @ref I2C_general_call_addressing_mode */

  uint32_t NoStretchMode;    /*!< Specifies if nostretch mode is selected.
                                  This parameter can be a value of @ref I2C_nostretch_mode */
} I2C_InitTypeDef;

/**
 *  @brief I2C DMA Environment.
 */
 struct I2cDMAEnv
{
    void                          (*Callback)();
    uint8_t                       DMA_Channel;
};

/**
 *  @brief I2C Interrupt Environment.
 */
struct I2cInterruptEnv
{
    uint8_t                       *pBuffPtr;      /*!< Pointer to I2C transfer Buffer */
    uint16_t                      XferCount;      /*!< I2C Transfer Counter           */
};

/**
 *  @brief I2C_handle_Structure_definition I2C handle Structure definition.
 */
typedef struct __I2C_HandleTypeDef
{
  reg_i2c_t                	*Instance;      /*!< I2C registers base address               */

  I2C_InitTypeDef            Init;           /*!< I2C communication parameters             */

  uint8_t                    *pBuffPtr;      /*!< Pointer to I2C transfer buffer           */

  uint16_t                   XferSize;       /*!< I2C transfer size                        */

  uint16_t                  XferCount;       /*!< I2C transfer counter                     */

  // uint32_t                  XferOptions;     /*!< I2C transfer options                     */

  // uint32_t                  PreviousState;  /*!< I2C communication Previous state and mode
                                                  // context for internal usage               */
  void                          *DMAC_Instance;
  union{
        struct I2cDMAEnv DMA;
        struct I2cInterruptEnv Interrupt;
  }Tx_Env,Rx_Env;                           /*!< I2C Tx/Rx DMA handle parameters             */

  HAL_LockTypeDef            Lock;           /*!< I2C locking object                       */

  HAL_I2C_StateTypeDef  State;          /*!< I2C communication state                  */

  HAL_I2C_ModeTypeDef   Mode;           /*!< I2C communication mode                   */

  uint32_t              ErrorCode;      /*!< I2C Error code                           */

  uint32_t              Devaddress;     /*!< I2C Target device address                */

  uint32_t              EventCount;     /*!< I2C Event counter                        */
} I2C_HandleTypeDef;


/**
  ****************************************************************************************
  * @brief  Initializes the I2C according to the specified parameters
  *         in the I2C_InitTypeDef and initialize the associated handle.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @return HAL status            returned HAL_OK/HAL_ERROR information
  ****************************************************************************************
  */
HAL_StatusTypeDef HAL_I2C_Init(I2C_HandleTypeDef *hi2c);
/**
  ****************************************************************************************
  * @brief  DeInitialize the I2C peripheral.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *         the configuration information for the specified I2C.
  * @return HAL status            returned HAL_OK/HAL_ERROR information
  ****************************************************************************************
  */
HAL_StatusTypeDef HAL_I2C_DeInit(I2C_HandleTypeDef *hi2c);
/**
  ****************************************************************************************
  * @brief Transmits in master mode an amount of data in blocking mode.(Blocking mode: Polling)
  *
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *              the configuration information for the specified I2C.
  * @param  DevAddress Target device address: The device 7 bits address value
  *                    in datasheet must be shifted to the left before calling the interface
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @param  Timeout Timeout duration.note：when Timeout = HAL_MAX_DELAY，that means the timeout is not valid.
  *
  * @return HAL status            returned HAL_BUSY/HAL_OK/HAL_ERROR information
  ****************************************************************************************
  */
HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint8_t Size, uint32_t Timeout);
/**
  ****************************************************************************************
  * @brief  Receives in master mode an amount of data in blocking mode.(Blocking mode: Polling)
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *              the configuration information for the specified I2C.
  * @param  DevAddress Target device address: The device 7 bits address value
  *                    in datasheet must be shifted to the left before calling the interface
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @param  Timeout Timeout duration。note：when Timeout = HAL_MAX_DELAY，that means the timeout is not valid.
  * @return HAL status            returned HAL_BUSY/HAL_OK/HAL_ERROR information
  ****************************************************************************************
  */
HAL_StatusTypeDef HAL_I2C_Master_Receive(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint8_t Size, uint32_t Timeout);
/**
  * @brief  Transmits in slave mode an amount of data in blocking mode.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2C_Slave_Transmit(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint8_t Size, uint32_t Timeout);
/**
  * @brief  Receive in slave mode an amount of data in blocking mode
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *         the configuration information for the specified I2C.
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2C_Slave_Receive(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint8_t Size, uint32_t Timeout);
/**
  ****************************************************************************************
  * @brief  Transmit in master mode an amount of data in non-blocking mode with Interrupt(Non-Blocking mode: Interrupt)
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *              the configuration information for the specified I2C.
  * @param  DevAddress Target device address: The device 7 bits address value
  *                    in datasheet must be shifted to the left before calling the interface
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @return HAL status            returned HAL_BUSY/HAL_OK/HAL_ERROR information
  ****************************************************************************************
  */
HAL_StatusTypeDef HAL_I2C_Master_Transmit_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint8_t Size);
/**
  ****************************************************************************************
  * @brief  Receive in master mode an amount of data in non-blocking mode with Interrupt(Non-Blocking mode: Interrupt)
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  DevAddress Target device address: The device 7 bits address value
  *         in datasheet must be shifted to the left before calling the interface
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @return HAL status            returned HAL_BUSY/HAL_OK/HAL_ERROR information
  ****************************************************************************************
  */
HAL_StatusTypeDef HAL_I2C_Master_Receive_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint8_t Size);
/**
 * @brief   * @brief  Transmit in slave mode an amount of data in non-blocking mode with Interrupt
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *         the configuration information for the specified I2C.
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2C_Slave_Transmit_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint8_t Size);
/**
  * @brief  Receive in slave mode an amount of data in non-blocking mode with Interrupt
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2C_Slave_Receive_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint8_t Size);
/**
  ****************************************************************************************
  * @brief  Transmit in master mode an amount of data in DMA mode
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *              the configuration information for the specified I2C.
  * @param  DevAddress Target device address: The device 7 bits address value
  *                    in datasheet must be shifted to the left before calling the interface
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @return HAL status            returned HAL_BUSY/HAL_OK/HAL_ERROR information
  ****************************************************************************************
  */
HAL_StatusTypeDef HAL_I2C_Master_Transmit_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint8_t Size);
/**
  ****************************************************************************************
  * @brief  Receive in master mode an amount of data in DMA mode
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  DevAddress Target device address: The device 7 bits address value
  *         in datasheet must be shifted to the left before calling the interface
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @return HAL status            returned HAL_BUSY/HAL_OK/HAL_ERROR information
  ****************************************************************************************
  */
HAL_StatusTypeDef HAL_I2C_Master_Receive_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint8_t Size);
/**
  ****************************************************************************************
  * @brief  This function handles I2C event interrupt request.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *              the configuration information for the specified I2C.
  ****************************************************************************************
  */
void HAL_I2C_IRQHandler(I2C_HandleTypeDef *hi2c);
/**
  ****************************************************************************************
  * @brief  Master Tx Transfer completed callback.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *              the configuration information for the specified I2C.
  ****************************************************************************************
  */
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c);
/**
  ****************************************************************************************
  * @brief  Master Rx Transfer completed callback.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  ****************************************************************************************
  */
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c);
/**
  ****************************************************************************************
  * @brief  Slave Tx Transfer completed callback.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  ****************************************************************************************
  */
void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *hi2c);
/**
 * 
    ****************************************************************************************
  * @brief  Slave Rx Transfer completed callback.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
    ****************************************************************************************
  */
void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c);
/**
  ****************************************************************************************  
  * @brief  Slave Address Match callback.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  TransferDirection Master request Transfer Direction (Write/Read)
  * @param  AddrMatchCode Address Match Code
  ****************************************************************************************
  */
void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode);
/**
  ****************************************************************************************
  * @brief  I2C error callback.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  ****************************************************************************************
  */
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c);
/**
  * @brief  DMA I2C Tx Transfer completed callbacks.
  * @note   This function needs to be implemented when the callback is needed,
           the HAL_I2C_DMA_TxCpltCallback could be implemented in the user file
  * @param  hi2c  Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C module.
  */
void HAL_I2C_DMA_TxCpltCallback(I2C_HandleTypeDef *hi2c);
/**
  * @brief  DMA I2C Rx Transfer completed callbacks.
  * @note  This function needs to be implemented when the callback is needed,
           the HAL_I2C_DMA_RxCpltCallback could be implemented in the user file
  * @param  hi2c  Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C module.
  */
void HAL_I2C_DMA_RxCpltCallback(I2C_HandleTypeDef *hi2c);
/**
  ****************************************************************************************
  * @brief  Return the I2C handle state.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @retval HAL state
  ****************************************************************************************
  */
HAL_I2C_StateTypeDef HAL_I2C_GetState(I2C_HandleTypeDef *hi2c);
/**
  ****************************************************************************************
  * @brief  Returns the I2C Master, Slave, Memory or no mode.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *         the configuration information for I2C module
  * @retval HAL mode
  ****************************************************************************************
  */
HAL_I2C_ModeTypeDef HAL_I2C_GetMode(I2C_HandleTypeDef *hi2c);
/**
  ****************************************************************************************
  * @brief  Return the I2C error code.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *              the configuration information for the specified I2C.
  * @retval I2C Error Code
  ****************************************************************************************
  */
uint32_t HAL_I2C_GetError(I2C_HandleTypeDef *hi2c);

#ifdef __cplusplus
}
#endif

/** @}*/


/** @}*/

#endif /* __le501x_HAL_I2C_H */


