#ifndef LS_HAL_UART_H_
#define LS_HAL_UART_H_
#include <stdbool.h>
#include "HAL_def.h"
#include "sdk_config.h"
#include "ls_ll_uart.h"

/** \addtogroup PERIPHERAL
 *  @{
 */

/** \addtogroup LSUART
 *  @{
 */



/**
  * @brief UART parity type
  */
typedef enum
{
    UART_NOPARITY             = 0x00U,    /*!< Parity diable*/
    UART_ODDPARITY             = 0x01U,    /*!< Parity Odd*/
    UART_EVENPARITY              = 0x03U   /*!< Parity Even*/
} app_uart_paritytype;

/**
  * @brief UART bytesize type
  */
typedef enum
{
    UART_BYTESIZE5             = 0x00U,    /*!< Byte size 5 bits*/
    UART_BYTESIZE6             = 0x01U,    /*!< Byte size 6 bits*/
    UART_BYTESIZE7              = 0x02U,  /*!< Byte size 7 bits*/
    UART_BYTESIZE8             = 0x03U    /*!< Byte size 8 bits*/
} app_uart_bytesizetype;

/**
  * @brief UART stopbit type
  */
typedef enum
{
    UART_STOPBITS1             = 0x00U,    /*!< Stop 1 bits*/
    UART_STOPBITS2             = 0x01U,    /*!< Stop 2 bits*/
} app_uart_stopbittype;

typedef struct
{
    app_uart_baudrate_t BaudRate;

    uint8_t     WordLength:2, /*!< config ls_hal_uart byte size 
                              This parameter can be a value of @ref app_uart_bytesizetype*/
               StopBits:1,    /*!< config ls_hal_uart stop bits.
                              This parameter can be a value of @ref app_uart_stopbittype  */
               Parity:2,      /*!< config ls_hal_uart parity type. 
                              This parameter can be a value of @ref app_uart_paritytype  */
               MSBEN:1,       /*!< config ls_hal_uart msb or lsb */
               HwFlowCtl:1;   /*!< Specifies whether the hardware flow control mode is enabled or disabled. */             
} UART_InitTypeDef;

/**
  * @brief HAL UART State structures definition
  * @note  HAL UART State value is a combination of 2 different substates: gState and RxState.
  *        - gState contains UART state information related to global Handle management
  *          and also information related to Tx operations.
  */
typedef enum
{
    HAL_UART_STATE_RESET             = 0x00U,    /*!< Peripheral is not yet Initialized
                                                    Value is allowed for gState and RxState */
    HAL_UART_STATE_READY             = 0x20U,    /*!< Peripheral Initialized and ready for use
                                                    Value is allowed for gState and RxState */
    HAL_UART_STATE_BUSY              = 0x24U,    /*!< an internal process is ongoing
                                                    Value is allowed for gState only */
    HAL_UART_STATE_BUSY_TX           = 0x21U,    /*!< Data Transmission process is ongoing
                                                    Value is allowed for gState only */
    HAL_UART_STATE_BUSY_RX           = 0x22U,    /*!< Data Reception process is ongoing
                                                    Value is allowed for RxState only */
} HAL_UART_StateTypeDef;


/**
  * @brief  UART DMA TX RX Environment
  */

struct UartDMAEnv
{
    uint8_t                       DMA_Channel;
};

/**
  * @brief  UART Interrupt TX Environment
  */
struct UartInterruptEnv
{
    uint8_t                       *pBuffPtr;      /*!< Pointer to UART Tx transfer Buffer */
    uint16_t                      XferCount;      /*!< UART Tx Transfer Counter           */
};

/**
  * @brief  UART handle Structure definition
  */

typedef struct __UART_HandleTypeDef
{
    reg_uart_t                    *UARTX;           /*!< UART registers base address        */
    UART_InitTypeDef              Init;             /*!< UART communication parameters      */
    void                          *DMAC_Instance;
    union{
        struct UartDMAEnv DMA;
        struct UartInterruptEnv Interrupt;
    }Tx_Env,Rx_Env;

    HAL_UART_StateTypeDef         gState;           /*!< UART state information related to global Handle management
                                                                and also related to Tx operations.
                                                                This parameter can be a value of @ref HAL_UART_StateTypeDef */

    HAL_UART_StateTypeDef         RxState;          /*!< UART state information related to Rx operations.*/
        
} UART_HandleTypeDef;

HAL_StatusTypeDef HAL_UART_AutoBaudRate_Detect(UART_HandleTypeDef *huart,uint8_t mode,uint8_t *detect_byte);

void HAL_UART_BaudRateDetectCpltCallback(UART_HandleTypeDef *huart,uint8_t detect_byte);

HAL_StatusTypeDef HAL_UART_AutoBaudRate_Detect_IT(UART_HandleTypeDef * huart,uint8_t mode);

/* operation functions *******************************************************/
/**
  * @brief  Sends an amount of data in blocking mode.
  * @note   
  * @param  huart Pointer to a UART_HandleTypeDef structure that contains
  *               the configuration information for the specified UART module.
  * @param  pData Pointer to data buffer (uint8_t data elements).
  * @param  Size  Amount of data elements (uint8_t) to be sent
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);

/**
  * @brief  Receives an amount of data in blocking mode.
  * @note   
  * @param  huart Pointer to a UART_HandleTypeDef structure that contains
  *               the configuration information for the specified UART module.
  * @param  pData Pointer to data buffer (uint8_t data elements).
  * @param  Size  Amount of data elements (uint8_t) to be received.
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size,uint32_t Timeout);

/**
  * @brief  Sends an amount of data in non blocking mode.
  * @param  huart Pointer to a UART_HandleTypeDef structure that contains
  *               the configuration information for the specified UART module.int_t
  * @param  pData Pointer to data buffer (uint8_t  data elements).
  * @param  Size  Amount of data elements (uint8_t) to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_UART_Transmit_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);

/**
  * @brief  Receives an amount of data in non blocking mode.
  * @param  huart Pointer to a UART_HandleTypeDef structure that contains
  *               the configuration information for the specified UART module.
  * @param  pData Pointer to data buffer (uint8_t data elements).
  * @param  Size  Amount of data elements (uint8_t) to be received.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);

/**
  * @brief  Sends an amount of data in DMA mode.
  * @param  huart  Pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @param  pData Pointer to data buffer (uint_8 data elements).
  * @param  Size  Amount of data elements (uint_8) to be sent.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_UART_Transmit_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);

/**
  * @brief  Receives an amount of data in DMA mode.
  * @param  huart Pointer to a UART_HandleTypeDef structure that contains
  *               the configuration information for the specified UART module.
  * @param  pData Pointer to data buffer (uint_8  data elements).
  * @param  Size  Amount of data elements (uint_8 ) to be received.
  * @note   When the UART parity is enabled (PCE = 1) the received data contains the parity bit.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_UART_Receive_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);

/**
  * @brief  Initializes the UART mode according to the specified parameters in
  *         the UART_InitTypeDef and create the associated handle.
  * @param  huart  Pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef *huart);

/**
  * @brief  DeInitializes the UART peripheral.
  * @param  huart  Pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_UART_DeInit(UART_HandleTypeDef *huart);

/**
  * @brief  This function handles UARTx interrupt request.
  * @param  huart  Pointer to a UARTx_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  */
void HAL_UARTx_IRQHandler(UART_HandleTypeDef *huart);

/**
  * @brief  Tx Transfer completed callbacks.
  * @note  This function needs to be implemented when the callback is needed,
           the HAL_UART_TxCpltCallback could be implemented in the user file     
  * @param  huart  Pointer to a UARTx_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);

/**
  * @brief  Rx Transfer completed callbacks.
  * @note  This function needs to be implemented when the callback is needed,
           the HAL_UART_RxCpltCallback could be implemented in the user file
  * @param  huart  Pointer to a UARTx_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

/**
  * @brief  DMA UART Tx Transfer completed callbacks.
  * @note   This function needs to be implemented when the callback is needed,
           the HAL_UART_DMA_TxCpltCallback could be implemented in the user file
  * @param  huart  Pointer to a UARTx_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  */
void HAL_UART_DMA_TxCpltCallback(UART_HandleTypeDef *huart);

/**
  * @brief  DMA UART Rx Transfer completed callbacks.
  * @note  This function needs to be implemented when the callback is needed,
           the HAL_UART_DMA_RxCpltCallback could be implemented in the user file
  * @param  huart  Pointer to a UARTx_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  */
void HAL_UART_DMA_RxCpltCallback(UART_HandleTypeDef *huart);

/** @}*/


/** @}*/

#endif // _LSUART_H_

