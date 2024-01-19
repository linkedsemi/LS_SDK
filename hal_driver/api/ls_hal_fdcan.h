#ifndef LS_HAL_CAN_H_
#define LS_HAL_CAN_H_
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "HAL_def.h"
#include "field_manipulate.h"
#include "ls_msp_fdcan.h"
#include "log.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* Exported types ------------------------------------------------------------*/

/**
  * @brief HAL State structures definition
  */
typedef enum
{
  HAL_FDCAN_STATE_RESET      = 0x00U, /*!< FDCAN not yet initialized or disabled */
  HAL_FDCAN_STATE_READY      = 0x01U, /*!< FDCAN initialized and ready for use   */
  HAL_FDCAN_STATE_BUSY       = 0x02U, /*!< FDCAN process is ongoing              */
  HAL_FDCAN_STATE_ERROR      = 0x03U, /*!< FDCAN error state                     */
}HAL_FDCAN_StateTypeDef;

typedef struct
{
  uint32_t Prescaler;  /*!< Specifies the length of a time quantum. */

  uint32_t SJW;        /*!< Specifies the maximum number of time quanta
                            the CAN hardware is allowed to lengthen or
                            shorten a bit to perform resynchronization. */

  uint32_t PH1;        /*!< Specifies the number of time quanta in Phase 1 Segment.*/

  uint32_t PH2;        /*!< Specifies the number of time quanta in Phase 2 Segment. */

  uint32_t PROP;       /*!< Specifies the number of time quanta in Propagation segment.*/
}FDCAN_ClockConfigTypeDef;

/**
  * @brief  CAN init structure definition
  */
typedef struct
{
  uint32_t FrameFormat;                  /*!< Specifies the FDCAN frame format.
                                              This parameter can be a value of @ref FDCAN_frame_format     */
  uint32_t Mode;                         /*!< Specifies the FDCAN mode.
                                              This parameter can be a value of @ref FDCAN_operating_mode   */
  FDCAN_ClockConfigTypeDef NominalBittiming;

  FDCAN_ClockConfigTypeDef DataBitting;

  FunctionalState FilterEnble;           /*!< Enable or disable the Filter mode.
                                              This parameter can be set to ENABLE or DISABLE. */

  FunctionalState FDRF;                  /*!< Enable or disable the Filter drop RTR frames.
                                              This parameter can be set to ENABLE or DISABLE. */

  FunctionalState ISOFD;                 /*!< Enable or disable the ISO FDCAD mode.
                                              This parameter can be set to ENABLE or DISABLE. */
 
  FunctionalState TTCM;                  /*!< Enable or disable the time triggered communication mode.
                                              This parameter can be set to ENABLE or DISABLE. */

  FunctionalState AutoRetransmission;    /*!< Enable or disable the automatic retransmission mode.
                                              This parameter can be set to ENABLE or DISABLE               */

  uint32_t reTransNbr;                   /*!< automatic retransmission number 
                                              This parameter must be a number between 0 and 15. */                                                                     
}FDCAN_InitTypeDef;

/**
  * @brief  FDCAN Tx header structure definition
  */
typedef struct
{
  uint32_t Identifier;          /*!< Specifies the identifier.
                                     This parameter must be a number between:
                                      - 0 and 0x7FF, if IdType is FDCAN_STANDARD_ID
                                      - 0 and 0x1FFFFFFF, if IdType is FDCAN_EXTENDED_ID               */

  uint32_t IdType;              /*!< Specifies the identifier type for the message that will be
                                     transmitted.
                                     This parameter can be a value of @ref FDCAN_id_type               */

  uint32_t TxFrameType;         /*!< Specifies the frame type of the message that will be transmitted.
                                     This parameter can be a value of @ref FDCAN_frame_type            */

  uint32_t DataLength;          /*!< Specifies the length of the frame that will be transmitted.
                                      This parameter can be a value of @ref FDCAN_data_length_code     */

  uint32_t ErrorStateIndicator; /*!< Specifies the error state indicator.
                                     This parameter can be a value of @ref FDCAN_error_state_indicator */                                  

  uint32_t BitRateSwitch;       /*!< Specifies whether the Tx frame will be transmitted with or without
                                     bit rate switching.
                                     This parameter can be a value of @ref FDCAN_bit_rate_switching    */

  uint32_t FDFormat;            /*!< Specifies whether the Tx frame will be transmitted in classic or
                                     FD format.
                                     This parameter can be a value of @ref FDCAN_format                */                               

  uint32_t TimestampLow;                 /*!< Lower 32 bits of timestamp when the frame should be transmitted*/

  uint32_t TimestampUpper;               /*!< Upper 32 bits of timestamp when the frame should be transmitted*/

  uint32_t BufferIndex;

  uint8_t *TxData;
}FDCAN_TxMSGTypeDef;

/**
  * @brief  FDCAN Rx header structure definition
  */
typedef struct
{
  uint32_t Identifier;            /*!< Specifies the identifier.
                                       This parameter must be a number between:
                                        - 0 and 0x7FF, if IdType is FDCAN_STANDARD_ID
                                        - 0 and 0x1FFFFFFF, if IdType is FDCAN_EXTENDED_ID               */

  uint32_t IdType;                /*!< Specifies the identifier type of the received message.
                                       This parameter can be a value of @ref FDCAN_id_type               */

  uint32_t RxFrameType;           /*!< Specifies the the received message frame type.
                                       This parameter can be a value of @ref FDCAN_frame_type            */

  uint32_t DataLength;            /*!< Specifies the received frame length.
                                        This parameter can be a value of @ref FDCAN_data_length_code     */

  uint32_t ErrorStateIndicator;   /*!< Specifies the error state indicator.
                                       This parameter can be a value of @ref FDCAN_error_state_indicator */

  uint32_t BitRateSwitch;         /*!< Specifies whether the Rx frame is received with or without bit
                                       rate switching.
                                       This parameter can be a value of @ref FDCAN_bit_rate_switching    */

  uint32_t FDFormat;              /*!< Specifies whether the Rx frame is received in classic or FD
                                       format.
                                       This parameter can be a value of @ref FDCAN_format                */

  uint32_t RxTimestampLow;        /*!< Specifies the timestamp counter value captured on start of frame
                                       reception.    */
  
  uint32_t RxTimestampUpper;      /*!< Specifies the timestamp counter value captured on start of frame
                                       reception.             */
  uint8_t *RxData;
}FDCAN_RxMsgTypeDef;

/**
 * @brief  CAN handle Structure definition
 */
typedef struct __FDCAN_HandleTypeDef
{
  reg_fdcan_t *Instance; /*!< Register base address          */

  FDCAN_InitTypeDef      Init;       /*!< CAN required parameters */

  FDCAN_TxMSGTypeDef    *pTxMsg;

  FDCAN_RxMsgTypeDef    *pRxMsg;

  HAL_FDCAN_StateTypeDef State;      /*!< FDCAN communication state */

  HAL_LockTypeDef        Lock;       /*!< FDCAN locking object      */

  uint32_t ErrorCode; /*!< CAN Error code                 */

} FDCAN_HandleTypeDef;

/**
  * @brief  FDCAN filter structure definition
  */
typedef struct
{
  uint32_t FilterIndex; /*!< This parameter can be a value of @ref FDCAN_Select_Filter*/
  uint32_t FilterType;  /*!< This parameter can be a value of @ref FDCAN_FilterType*/                                 
  uint32_t FilterValue1;
  uint32_t FilterValue2;
}FDCAN_FilterTypeDef;

/** @defgroup HAL_FDCAN_Error_Code HAL FDCAN Error Code
  * @{
  */
#define HAL_FDCAN_ERROR_NONE            ((uint32_t)0x00000000U) /*!< No error                                                               */
#define HAL_FDCAN_ERROR_TIMEOUT         ((uint32_t)0x00000001U) /*!< Timeout error                                                          */
#define HAL_FDCAN_ERROR_NOT_INITIALIZED ((uint32_t)0x00000002U) /*!< Peripheral not initialized                                             */
#define HAL_FDCAN_ERROR_NOT_READY       ((uint32_t)0x00000004U) /*!< Peripheral not ready                                                   */
#define HAL_FDCAN_ERROR_NOT_STARTED     ((uint32_t)0x00000008U) /*!< Peripheral not started                                                 */
#define HAL_FDCAN_ERROR_NOT_SUPPORTED   ((uint32_t)0x00000010U) /*!< Mode not supported                                                     */
#define HAL_FDCAN_ERROR_PARAM           ((uint32_t)0x00000020U) /*!< Parameter error                                                        */
#define HAL_FDCAN_ERROR_PENDING         ((uint32_t)0x00000040U) /*!< Pending operation                                                      */
#define HAL_FDCAN_ERROR_RAM_ACCESS      ((uint32_t)0x00000080U) /*!< Message RAM Access Failure                                             */
/**
  * @}
  */


/** @defgroup FDCAN_frame_format FDCAN Frame Format
  * @{
  */
#define FDCAN_FRAME_CLASSIC       ((uint32_t)0x00000000U)                         /*!< Classic mode                      */
#define FDCAN_FRAME_FD_NO_BRS     ((uint32_t)FDCAN_PEX_MASK)                      /*!< FD mode without BitRate Switshing */
#define FDCAN_FRAME_FD_BRS        ((uint32_t)FDCAN_FDE_MASK)                      /*!< FD mode with BitRate Switshing    */
#define FDCAN_FRAME_FD_BRS_PEX    ((uint32_t)(FDCAN_PEX_MASK | FDCAN_FDE_MASK))   /*!< FD mode with BitRate Switshing and Protocol Exception */
/**
  * @}
  */

/** @defgroup FDCAN_operating_mode FDCAN Operating Mode
  * @{
  */
#define FDCAN_MODE_NORMAL               ((uint32_t)0x00000000U) /*!< Normal mode               */
#define FDCAN_MODE_LOOPBACK             ((uint32_t)(FDCAN_ILBP_MASK | FDCAN_STM_MASK)) /*!< LoopBack mode */    
#define FDCAN_MODE_ACK_FORBIDDEN        ((uint32_t)FDCAN_ACF_MASK) /*!< Self Test mode            */
#define FDCAN_MODE_SELF_ACK             ((uint32_t)FDCAN_SAM_MASK) /*!< Self Test mode            */
#define FDCAN_MODE_BUS_MONITORING       ((uint32_t)FDCAN_BMM_MASK) /*!< Bus Monitoring mode       */
#define FDCAN_MODE_RESTRICTED_OPERATION ((uint32_t)FDCAN_ROM_MASK) /*!< Restricted Operation mode */
#define FDCAN_MODE_TEST                 ((uint32_t)FDCAN_TSTM_MASK) /*!< Restricted Operation mode */
/**
  * @}
  */

/** @defgroup FDCAN_data_field_size FDCAN Data Field Size
  * @{
  */
#define FDCAN_DATA_BYTES_8  ((uint32_t)0x00000004U) /*!< 8 bytes data field  */
#define FDCAN_DATA_BYTES_12 ((uint32_t)0x00000005U) /*!< 12 bytes data field */
#define FDCAN_DATA_BYTES_16 ((uint32_t)0x00000006U) /*!< 16 bytes data field */
#define FDCAN_DATA_BYTES_20 ((uint32_t)0x00000007U) /*!< 20 bytes data field */
#define FDCAN_DATA_BYTES_24 ((uint32_t)0x00000008U) /*!< 24 bytes data field */
#define FDCAN_DATA_BYTES_32 ((uint32_t)0x0000000AU) /*!< 32 bytes data field */
#define FDCAN_DATA_BYTES_48 ((uint32_t)0x0000000EU) /*!< 48 bytes data field */
#define FDCAN_DATA_BYTES_64 ((uint32_t)0x00000012U) /*!< 64 bytes data field */
/**
  * @}
  */

/** @defgroup FDCAN_id_type FDCAN ID Type
  * @{
  */
#define FDCAN_STANDARD_ID ((uint32_t)0x00000000U)                /*!< Standard ID element */
#define FDCAN_EXTENDED_ID ((uint32_t)FDCAN_TXTB_DATA_1_IDE_MASK) /*!< Extended ID element */
/**
  * @}
  */

/** @defgroup FDCAN_frame_type FDCAN Frame Type
  * @{
  */
#define FDCAN_DATA_FRAME   ((uint32_t)0x00000000U)  /*!< Data frame   */
#define FDCAN_REMOTE_FRAME ((uint32_t)FDCAN_TXTB_DATA_1_RTR_MASK)  /*!< Remote frame */
/**
  * @}
  */

/** @defgroup FDCAN_data_length_code FDCAN Data Length Code
  * @{
  */
#define FDCAN_DLC_BYTES_0  ((uint32_t)0x00000000U) /*!< 0 bytes data field  */
#define FDCAN_DLC_BYTES_1  ((uint32_t)0x00000001U) /*!< 1 bytes data field  */
#define FDCAN_DLC_BYTES_2  ((uint32_t)0x00000002U) /*!< 2 bytes data field  */
#define FDCAN_DLC_BYTES_3  ((uint32_t)0x00000003U) /*!< 3 bytes data field  */
#define FDCAN_DLC_BYTES_4  ((uint32_t)0x00000004U) /*!< 4 bytes data field  */
#define FDCAN_DLC_BYTES_5  ((uint32_t)0x00000005U) /*!< 5 bytes data field  */
#define FDCAN_DLC_BYTES_6  ((uint32_t)0x00000006U) /*!< 6 bytes data field  */
#define FDCAN_DLC_BYTES_7  ((uint32_t)0x00000007U) /*!< 7 bytes data field  */
#define FDCAN_DLC_BYTES_8  ((uint32_t)0x00000008U) /*!< 8 bytes data field  */
#define FDCAN_DLC_BYTES_12 ((uint32_t)0x00000009U) /*!< 12 bytes data field */
#define FDCAN_DLC_BYTES_16 ((uint32_t)0x0000000AU) /*!< 16 bytes data field */
#define FDCAN_DLC_BYTES_20 ((uint32_t)0x0000000BU) /*!< 20 bytes data field */
#define FDCAN_DLC_BYTES_24 ((uint32_t)0x0000000CU) /*!< 24 bytes data field */
#define FDCAN_DLC_BYTES_32 ((uint32_t)0x0000000DU) /*!< 32 bytes data field */
#define FDCAN_DLC_BYTES_48 ((uint32_t)0x0000000EU) /*!< 48 bytes data field */
#define FDCAN_DLC_BYTES_64 ((uint32_t)0x0000000FU) /*!< 64 bytes data field */
/**
  * @}
  */

/** @defgroup FDCAN_error_state_indicator FDCAN Error State Indicator
  * @{
  */
#define FDCAN_ESI_ACTIVE  ((uint32_t)0x00000000U)                   /*!< Transmitting node is error active  */
#define FDCAN_ESI_PASSIVE ((uint32_t)FDCAN_TXTB_DATA_1_ESIRSV_MASK) /*!< Transmitting node is error passive */
/**
  * @}
  */

/** @defgroup FDCAN_bit_rate_switching FDCAN Bit Rate Switching
  * @{
  */
#define FDCAN_BRS_OFF ((uint32_t)0x00000000U)                /*!< FDCAN frames transmitted/received without bit rate switching */
#define FDCAN_BRS_ON  ((uint32_t)FDCAN_TXTB_DATA_1_BRS_MASK) /*!< FDCAN frames transmitted/received with bit rate switching    */
/**
  * @}
  */

/** @defgroup FDCAN_format FDCAN format
  * @{
  */
#define FDCAN_CLASSIC_CAN ((uint32_t)0x00000000U)                /*!< Frame transmitted/received in Classic CAN format */
#define FDCAN_FD_CAN      ((uint32_t)FDCAN_TXTB_DATA_1_FDF_MASK) /*!< Frame transmitted/received in FDCAN format       */
/**
  * @}
  */

/** @defgroup FDCAN_Tx_location FDCAN Tx Location
  * @{
  */
#define FDCAN_TX_BUFFER1  ((uint32_t)0x00000000U) /*!< Add message to Tx Buffer 1  */
#define FDCAN_TX_BUFFER2  ((uint32_t)0x00000001U) /*!< Add message to Tx Buffer 2  */
#define FDCAN_TX_BUFFER3  ((uint32_t)0x00000002U) /*!< Add message to Tx Buffer 3  */
#define FDCAN_TX_BUFFER4  ((uint32_t)0x00000003U) /*!< Add message to Tx Buffer 4  */
/**
  * @}
  */

/** @defgroup FDCAN_Select_Filter FDCAN Select Filter
  * @{
  */
#define FDCAN_FILTER_BIT_A    ((uint32_t)0x00000000U)
#define FDCAN_FILTER_BIT_B    ((uint32_t)0x00000001U)
#define FDCAN_FILTER_BIT_C    ((uint32_t)0x00000002U)
#define FDCAN_FILTER_RANG     ((uint32_t)0x00000003U)
/**
  * @}
  */

/** @defgroup FDCAN_FilterType FDCAN FilterType
  * @{
  */
#define FDCAN_FILTER_CLASSIC_BASIC      ((uint32_t)0x00000001U)
#define FDCAN_FILTER_CLASSIC_EXTEND     ((uint32_t)0x00000002U)
#define FDCAN_FILTER_FD_BASIC           ((uint32_t)0x00000004U)
#define FDCAN_FILTER_FD_EXTEND          ((uint32_t)0x00000008U)
/**
  * @}
  */

/** @defgroup FDCAN_Command FDCAN Command
  * @{
  */
#define FDCAN_RXRPMV_FLAG               ((uint32_t)FDCAN_RXRPMV_MASK)
#define FDCAN_FLUSH_RXBUF_FLAG          ((uint32_t)FDCAN_RRB_MASK)
#define FDCAN_CLEAR_OVERRUN_FLAG        ((uint32_t)FDCAN_CDO_MASK)
#define FDCAN_ERROR_COUNTER_RESET_FLAG  ((uint32_t)FDCAN_ERCRST_MASK)
#define FDCAN_CLEAR_RXFCRST_FLAG        ((uint32_t)FDCAN_RXFCRST_MASK)
#define FDCAN_CLEAR_TXFCRST_FLAG        ((uint32_t)FDCAN_TXFCRST_MASK)
#define FDCAN_CLEAR_PEXS_FLAG           ((uint32_t)FDCAN_CPEXS_MASK)
#define FDCAN_CLEAR_CRXPE_FLAG          ((uint32_t)FDCAN_CRXPE_MASK)
#define FDCAN_CLEAR_CTXPE_FLAG          ((uint32_t)FDCAN_CTXPE_MASK)
#define FDCAN_CLEAR_TXDPE_FLAG          ((uint32_t)FDCAN_TXDPE_MASK)
/**
  * @}
  */

/** @defgroup RX_Status RX Status
  * @{
  */
#define FDCAN_RX_EMPTY      ((uint32_t)FDCAN_RXE_MASK)
#define FDCAN_RX_FULL       ((uint32_t)FDCAN_RXF_MASK)
#define FDCAN_RX_MID_FRAM   ((uint32_t)FDCAN_RXMOF_MASK)
#define FDCAN_RX_FCOUNT     ((uint32_t)FDCAN_RXFRC_MASK)
/**
  * @}
  */

/** @defgroup TX_Status TX Status
  * @{
  */
#define FDCAN_TX_NOT_EXIST      ((uint32_t)0X00000000U)
#define FDCAN_TX_READY          ((uint32_t)0X00000001U)
#define FDCAN_TX_TRANSMITTING   ((uint32_t)0X00000002U)
#define FDCAN_TX_ABORTTING      ((uint32_t)0X00000003U)
#define FDCAN_TX_OK             ((uint32_t)0X00000004U)
#define FDCAN_TX_FAILED         ((uint32_t)0X00000006U)
#define FDCAN_TX_ABORTED        ((uint32_t)0X00000007U)
#define FDCAN_TX_EMPTY          ((uint32_t)0X00000008U)
#define FDCAN_TX_PARITY_ERROR   ((uint32_t)0X00000009U)
/**
  * @}
  */

/** @defgroup FDCAN_Interrupts FDCAN Interrupts
* @{
*/
#define FDCAN_IT_RXI    ((uint32_t)FDCAN_RXI_MASK)    /*Frame received interrupt*/
#define FDCAN_IT_TXI    ((uint32_t)FDCAN_TXI_MASK)    /*Frame transmitted interrupt*/
#define FDCAN_IT_EWLI   ((uint32_t)FDCAN_EWLI_MASK)   /*Error warning limit interrupt*/
#define FDCAN_IT_DOI    ((uint32_t)FDCAN_DOI_MASK)    /*Data overrun interrupt*/
#define FDCAN_IT_FCSI   ((uint32_t)FDCAN_FCSI_MASK)   /*Fault confinement state changed interrupt*/
#define FDCAN_IT_ALI    ((uint32_t)FDCAN_ALI_MASK)    /*Arbitration lost interrupt*/
#define FDCAN_IT_BEI    ((uint32_t)FDCAN_BEI_MASK)    /*Bus error interrupt*/
#define FDCAN_IT_OFI    ((uint32_t)FDCAN_OFI_MASK)    /*Overload frame interrupt*/
#define FDCAN_IT_RXFI   ((uint32_t)FDCAN_RXFI_MASK)   /*RX buﬀer full interrupt*/
#define FDCAN_IT_BSI    ((uint32_t)FDCAN_BSI_MASK)    /*Bit rate shifted interrupt*/
#define FDCAN_IT_RBNEI  ((uint32_t)FDCAN_RBNEI_MASK)  /*RX buﬀer not empty interrupt.*/
#define FDCAN_IT_TXBHCI ((uint32_t)FDCAN_TXBHCI_MASK) /*TXT buﬀer HW command interrupt*/
/**
  * @}
  */

/** @brief Enable FDCAN.
  * @param  __HANDLE__: FDCAN handle.
  * @retval None
  */
#define __HAL_FDCAN_ENABLE(__HANDLE__) (SET_BIT((__HANDLE__)->Instance->MODE_CFG,FDCAN_ENA_MASK))

/** @brief Disable FDCAN.
  * @param  __HANDLE__: FDCAN handle.
  * @retval None
  */
#define __HAL_FDCAN_DISABLE(__HANDLE__) (CLEAR_BIT((__HANDLE__)->Instance->MODE_CFG,FDCAN_ENA_MASK))

/**
  * @brief  Enable the specified FDCAN Command.
  * @param  __HANDLE__: FDCAN handle.
  * @param  FLAG: FDCAN Command flag.
  *          This parameter can be any combination of @arg FDCAN_Command
  * @retval None
  */
#define __HAL_FDCAN_CMD_SET(__HANDLE__,FLAG) (SET_BIT((__HANDLE__)->Instance->CMD,FLAG))

/**
  * @brief  Check whether the specified FDCAN RX Status is set or not.
  * @param  __HANDLE__: FDCAN handle.
  * @param  STATUS: FDCAN RX STATUS.
  *          This parameter can be one of @arg RX_Status
  * @retval None
  */
#define __HAL_FDCAN_RXSTATUS_GET(__HANDLE__,STATUS) ((__HANDLE__)->Instance->RX_STT & (STATUS))

/** @brief  Enable the specified FDCAN interrupt.
 */
#define __HAL_FDCAN_ENABLE_IT(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->INT_SET |= (__INTERRUPT__))

/** @brief  Check whether the specified FDCAN interrupt flag is set or not.
 */
#define __HAL_TIM_GET_FLAG(__HANDLE__, __FLAG__)  (((__HANDLE__)->Instance->INT_SET & (__FLAG__)) == (__FLAG__))

/** @brief  Disable the specified FDCAN interrupt.
 */
#define __HAL_FDCAN_DISABLE_IT(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->INT_CLR |= (__INTERRUPT__))

/** @brief  Check whether the specified FDCAN interrupt flag is set or not.
 */
#define __HAL_FDCAN_GET_IT_SOURCE(__HANDLE__, __FLAG__) (((__HANDLE__)->Instance->INT_STT & (__FLAG__)) == (__FLAG__))

/** @brief  Clear the specified FDCAN interrupt flag.
 */
#define __HAL_FDCAN_CLEAR_IT(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->INT_STT = (__FLAG__))

HAL_StatusTypeDef HAL_FDCAN_Init(FDCAN_HandleTypeDef *hfdcan);

HAL_StatusTypeDef HAL_FDCAN_DeInit(FDCAN_HandleTypeDef* hfdcan);

HAL_StatusTypeDef HAL_FDCAN_Start(FDCAN_HandleTypeDef *hfdcan);

HAL_StatusTypeDef HAL_FDCAN_Stop(FDCAN_HandleTypeDef *hfdcan);

HAL_StatusTypeDef HAL_FDCAN_Transmit(FDCAN_HandleTypeDef *hfdcan, uint32_t Timeout);

HAL_StatusTypeDef HAL_FDCAN_EnableTxBufferRequest(FDCAN_HandleTypeDef *hfdcan, uint32_t BufferIndex);

HAL_StatusTypeDef HAL_FDCAN_AbortTxRequest(FDCAN_HandleTypeDef *hfdcan, uint32_t BufferIndex);

HAL_StatusTypeDef HAL_FDCAN_ConfigFilter(FDCAN_HandleTypeDef* hfdcan, FDCAN_FilterTypeDef* sFilterConfig);

HAL_StatusTypeDef HAL_FDCAN_Receive(FDCAN_HandleTypeDef *hfdcan, uint32_t Timeout);

void HAL_FDCAN_IRQHandler(FDCAN_HandleTypeDef *fdcan);

HAL_StatusTypeDef HAL_FDCAN_Transmit_IT(FDCAN_HandleTypeDef *hfdcan);

HAL_StatusTypeDef HAL_FDCAN_Receive_IT(FDCAN_HandleTypeDef *hfdcan);

void HAL_FDCAN_TxCpltCallback(FDCAN_HandleTypeDef* hcan);

void HAL_FDCAN_RxCpltCallback(FDCAN_HandleTypeDef* hcan);

#ifdef __cplusplus
}
#endif

#endif
