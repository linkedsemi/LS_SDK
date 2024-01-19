#ifndef LS_HAL_DWUART_H_
#define LS_HAL_DWUART_H_
#include "reg_dwuart_type.h"
#include "sdk_config.h"
#include "HAL_def.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DWUART_FIFO_RECEIVE_TRIGGER_1BYTE   0x00U
#define DWUART_FIFO_RECEIVE_TRIGGER_8BYTE   0x01U
#define DWUART_FIFO_RECEIVE_TRIGGER_16BYTE  0x02U
#define DWUART_FIFO_RECEIVE_TRIGGER_30BYTE  0x03U

#define DWUART_FIFO_TRANSMIT_TRIGGER_0BYTE  0x00U
#define DWUART_FIFO_TRANSMIT_TRIGGER_2BYTE  0x01U
#define DWUART_FIFO_TRANSMIT_TRIGGER_8BYTE  0x02U
#define DWUART_FIFO_TRANSMIT_TRIGGER_16BYTE 0x03U

#define DWUART_INTERRUPT_ID_MODEMSTATUS             0x00U
#define DWUART_INTERRUPT_ID_NO_PENDING              0x01U
#define DWUART_INTERRUPT_ID_THR_EMPTY               0x02U
#define DWUART_INTERRUPT_ID_RECEIVE_DATA_AVAILABLE  0x04U
#define DWUART_INTERRUPT_ID_RECEIVE_LINE_STATUS     0x06U
#define DWUART_INTERRUPT_ID_BUSY_DETECT             0x07U
#define DWUART_INTERRUPT_ID_CHARACTER_TIMEOUT       0x0CU

#define DWUART_CLOCK (SDK_PCLK_MHZ * 1000000)
#define DWUART_BUADRATE_ENUM_GEN(BAUD) (((DWUART_CLOCK / (BAUD)) / 16) << 16) | (((DWUART_CLOCK / (BAUD)) % 16))

typedef enum 
{
    DWUART_ERROR_OVERRUN               = 0x2,
    DWUART_ERROR_PARITY                = 0x4,
    DWUART_ERROR_FRAMING               = 0x8,
} dwuart_errorMode;

typedef enum 
{
    DWUART_BAUDRATE_1200               = DWUART_BUADRATE_ENUM_GEN(1200),
    DWUART_BAUDRATE_2400               = DWUART_BUADRATE_ENUM_GEN(2400),
    DWUART_BAUDRATE_4800               = DWUART_BUADRATE_ENUM_GEN(4800),
    DWUART_BAUDRATE_9600               = DWUART_BUADRATE_ENUM_GEN(9600),
    DWUART_BAUDRATE_14400              = DWUART_BUADRATE_ENUM_GEN(14400),
    DWUART_BAUDRATE_19200              = DWUART_BUADRATE_ENUM_GEN(19200),
    DWUART_BAUDRATE_28800              = DWUART_BUADRATE_ENUM_GEN(28800),
    DWUART_BAUDRATE_38400              = DWUART_BUADRATE_ENUM_GEN(38400),
    DWUART_BAUDRATE_57600              = DWUART_BUADRATE_ENUM_GEN(57600),
    DWUART_BAUDRATE_76800              = DWUART_BUADRATE_ENUM_GEN(76800),
    DWUART_BAUDRATE_115200             = DWUART_BUADRATE_ENUM_GEN(115200),
    DWUART_BAUDRATE_230400             = DWUART_BUADRATE_ENUM_GEN(230400),
    DWUART_BAUDRATE_250000             = DWUART_BUADRATE_ENUM_GEN(250000),
    DWUART_BAUDRATE_460800             = DWUART_BUADRATE_ENUM_GEN(460800),
    DWUART_BAUDRATE_500000             = DWUART_BUADRATE_ENUM_GEN(500000),
    DWUART_BAUDRATE_750000             = DWUART_BUADRATE_ENUM_GEN(750000),
    DWUART_BAUDRATE_921600             = DWUART_BUADRATE_ENUM_GEN(921600),
    DWUART_BAUDRATE_1000000            = DWUART_BUADRATE_ENUM_GEN(1000000),
    DWUART_BAUDRATE_2000000            = DWUART_BUADRATE_ENUM_GEN(2000000),
} dwuart_baudrate_t;

typedef enum
{
    DWUART_ODDPARITY                   = 0x00U,    /*!< Parity Odd*/
    DWUART_EVENPARITY                  = 0x01U,    /*!< Parity Even*/
    DWUART_NOPARITY                    = 0x03U,    /*!< Parity diable*/
} dwuart_paritytype;

typedef enum
{
    DWUART_BYTESIZE5                   = 0x00U,    /*!< Byte size 5 bits*/
    DWUART_BYTESIZE6                   = 0x01U,    /*!< Byte size 6 bits*/
    DWUART_BYTESIZE7                   = 0x02U,    /*!< Byte size 7 bits*/
    DWUART_BYTESIZE8                   = 0x03U,    /*!< Byte size 8 bits*/
} dwuart_bytesizetype;

typedef enum
{
    DWUART_STOPBITS1                   = 0x00U,    /*!< Stop 1 bits*/
    DWUART_STOPBITS1P5                 = 0x01U,    /*!< Stop 1.5 bits*/
    DWUART_STOPBITS2                   = 0x01U,    /*!< Stop 2 bits*/
} dwuart_stopbittype;

typedef enum
{
    HAL_DWUART_STATE_RESET             = 0x00U,    /*!< Peripheral is not yet Initialized
                                                    Value is allowed for gState and RxState */
    HAL_DWUART_STATE_READY             = 0x20U,    /*!< Peripheral Initialized and ready for use
                                                    Value is allowed for gState and RxState */
    HAL_DWUART_STATE_BUSY              = 0x24U,    /*!< an internal process is ongoing
                                                    Value is allowed for gState only */
    HAL_DWUART_STATE_BUSY_TX           = 0x21U,    /*!< Data Transmission process is ongoing
                                                    Value is allowed for gState only */
    HAL_DWUART_STATE_BUSY_RX           = 0x22U,    /*!< Data Reception process is ongoing
                                                    Value is allowed for RxState only */
} HAL_DWUART_StateTypeDef;

typedef struct
{
    uint32_t                           BaudRate;
    uint8_t                            WordLength  : 2,  /*!< config ls_hal_uart byte size
                                                            This parameter can be a value of @ref app_uart_bytesizetype*/
                                       StopBits    : 1,  /*!< config ls_hal_uart stop bits.
                                                            This parameter can be a value of @ref app_uart_stopbittype  */
                                       Parity      : 2,  /*!< config ls_hal_uart parity type.
                                                            This parameter can be a value of @ref app_uart_paritytype  */
                                       MSBEN       : 1,  /*!< config ls_hal_uart msb or lsb */
                                       HwFlowCtl   : 1;  /*!< Specifies whether the hardware flow control mode is enabled or disabled. */
} DWUART_InitTypeDef;

struct DWUartDMAEnv
{
    uint8_t                            DMA_Channel;
    bool                               Channel_Done;
};

struct DWUartInterruptEnv
{
    uint8_t                            *pBuffPtr;      /*!< Pointer to DWUART Tx transfer Buffer */
    uint16_t                           XferCount;      /*!< DWUART Tx Transfer Counter           */
    uint16_t                           OriginalLength;
};

typedef struct __DWUART_HandleTypeDef
{
    reg_dwuart_t                       *DWUARTX;
    DWUART_InitTypeDef                 Init;
    void                               *DMAC_Instance;
    union
    {
        struct DWUartDMAEnv            DMA;
        struct DWUartInterruptEnv      Interrupt;
    } Tx_Env, Rx_Env;
    HAL_DWUART_StateTypeDef            gState; /*!< DWUART state information related to global Handle management
                                              and also related to Tx operations.
                                              This parameter can be a value of @ref HAL_DWUART_StateTypeDef */
    HAL_DWUART_StateTypeDef            RxState; /*!< DWUART state information related to Rx operations.*/
    bool                               RTOEN;
} DWUART_HandleTypeDef;

/**
  * @brief  Initializes the DWUART mode according to the specified parameters in
  *         the UART_InitTypeDef and create the associated handle.
  * @param  hdwuart  Pointer to a DWUART_HandleTypeDef structure that contains
  *                the configuration information for the specified DWUART module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DWUART_Init(DWUART_HandleTypeDef *hdwuart);

/**
  * @brief  DeInitializes the DWUART peripheral.
  * @param  hdwuart  Pointer to a DWUART_HandleTypeDef structure that contains
  *                the configuration information for the specified DWUART module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DWUART_DeInit(DWUART_HandleTypeDef *hdwuart);

/**
  * @brief  Sends an amount of data in blocking mode.
  * @note   
  * @param  hdwuart Pointer to a DWUART_HandleTypeDef structure that contains
  *               the configuration information for the specified DWUART module.
  * @param  pData Pointer to data buffer (uint8_t data elements).
  * @param  Size  Amount of data elements (uint8_t) to be sent
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DWUART_Transmit(DWUART_HandleTypeDef *hdwuart, uint8_t *pData, uint16_t Size, uint32_t Timeout);

/**
  * @brief  Receives an amount of data in blocking mode.
  * @note   
  * @param  dwuart Pointer to a DWUART_HandleTypeDef structure that contains
  *               the configuration information for the specified DWUART module.
  * @param  pData Pointer to data buffer (uint8_t data elements).
  * @param  Size  Amount of data elements (uint8_t) to be received.
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DWUART_Receive(DWUART_HandleTypeDef *hdwuart, uint8_t *pData, uint16_t Size,uint32_t Timeout);

/**
  * @brief  Sends an amount of data in non blocking mode.
  * @param  dwuart Pointer to a DWUART_HandleTypeDef structure that contains
  *               the configuration information for the specified DWUART module.int_t
  * @param  pData Pointer to data buffer (uint8_t  data elements).
  * @param  Size  Amount of data elements (uint8_t) to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DWUART_Transmit_IT(DWUART_HandleTypeDef *hdwuart, uint8_t *pData, uint16_t Size);

/**
  * @brief  Receives an amount of data in non blocking mode.
  * @param  dwuart Pointer to a DWUART_HandleTypeDef structure that contains
  *               the configuration information for the specified DWUART module.
  * @param  pData Pointer to data buffer (uint8_t data elements).
  * @param  Size  Amount of data elements (uint8_t) to be received.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DWUART_Receive_IT(DWUART_HandleTypeDef *hdwuart, uint8_t *pData, uint16_t Size);

/**
  * @brief  Sends an amount of data in DMA mode.
  * @param  dwuart  Pointer to a DWUART_HandleTypeDef structure that contains
  *                the configuration information for the specified DWUART module.
  * @param  pData Pointer to data buffer (uint_8 data elements).
  * @param  Size  Amount of data elements (uint_8) to be sent.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DWUART_Transmit_DMA(DWUART_HandleTypeDef *hdwuart, uint8_t *pData, uint16_t Size);

/**
  * @brief  Receives an amount of data in DMA mode.
  * @param  dwuart Pointer to a DWUART_HandleTypeDef structure that contains
  *               the configuration information for the specified DWUART module.
  * @param  pData Pointer to data buffer (uint_8  data elements).
  * @param  Size  Amount of data elements (uint_8 ) to be received.
  * @note   When the DWUART parity is enabled (PCE = 1) the received data contains the parity bit.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DWUART_Receive_DMA(DWUART_HandleTypeDef *hdwuart, uint8_t *pData, uint16_t Size);

/**
  * @brief  Stop receiving data in DMA mode.
  * @param  hdwuart Pointer to a DWUART_HandleTypeDef structure that contains
  *               the configuration information for the specified UART module.
  * @retval The length of the data received
  */
uint32_t HAL_DWUART_Receive_DMA_Abort(DWUART_HandleTypeDef *hdwuart);

/**
  * @brief  Rx Transfer completed callbacks.
  * @note  This function needs to be implemented when the callback is needed,
           the HAL_UART_RxCpltCallback could be implemented in the user file
  * @param  dwuart  Pointer to a DWUARTx_HandleTypeDef structure that contains
  *                the configuration information for the specified DWUART module.
  */
void HAL_DWUART_RxCpltCallback(DWUART_HandleTypeDef *hdwuart);

/**
 * @brief  Rx Transfer timeout completed callbacks.
 * @note   This function needs to be implemented when the callback is needed,
           the HAL_UART_RxToIdleCpltCallback could be implemented in the user file
 * @param dwuart Pointer to a DWUARTx_HandleTypeDef structure that contains
 *             the configuration information for the specified DWUART module.
 * @param length The length of the data received
 */
void HAL_DWUART_RxRTOCallback(DWUART_HandleTypeDef *hdwuart, uint8_t length);

/**
  * @brief  Tx Transfer Error callbacks.
  * @note  This function needs to be implemented when the callback is needed,
           the HAL_UART_TxCpltCallback could be implemented in the user file     
  * @param  dwuart  Pointer to a DWUARTx_HandleTypeDef structure that contains
  *                the configuration information for the specified DWUART module.
  * @param  errorMode  Error Mode, dwuart_errorMode.
  */
void HAL_DWUART_RxErrorCallback(DWUART_HandleTypeDef *hdwuart, uint8_t errorMode);

/**
  * @brief  Tx Transfer completed callbacks.
  * @note  This function needs to be implemented when the callback is needed,
           the HAL_UART_TxCpltCallback could be implemented in the user file     
  * @param  dwuart  Pointer to a DWUARTx_HandleTypeDef structure that contains
  *                the configuration information for the specified DWUART module.
  */
void HAL_DWUART_TxCpltCallback(DWUART_HandleTypeDef *hdwuart);

/**
  * @brief  DMA DWUART Rx Transfer completed callbacks.
  * @note  This function needs to be implemented when the callback is needed,
           the HAL_UART_DMA_RxCpltCallback could be implemented in the user file
  * @param  dwuart  Pointer to a DWUARTx_HandleTypeDef structure that contains
  *                the configuration information for the specified DWUART module.
  */
void HAL_DWUART_DMA_RxCpltCallback(DWUART_HandleTypeDef *hdwuart);

/**
  * @brief  DMA DWUART Tx Transfer completed callbacks.
  * @note   This function needs to be implemented when the callback is needed,
           the HAL_UART_DMA_TxCpltCallback could be implemented in the user file
  * @param  dwuart  Pointer to a DWUARTx_HandleTypeDef structure that contains
  *                the configuration information for the specified DWUART module.
  */
void HAL_DWUART_DMA_TxCpltCallback(DWUART_HandleTypeDef *hdwuart);

void HAL_DWUARTx_IRQHandler(DWUART_HandleTypeDef *hdwuart);

#ifdef __cplusplus
}
#endif
#endif
