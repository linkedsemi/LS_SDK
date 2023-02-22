#ifndef LS_HAL_CAN_H_
#define LS_HAL_CAN_H_
#include <stdint.h>
#include <stdbool.h>
#include "HAL_def.h"
#include "field_manipulate.h"
#include "ls_msp_can.h"

/** @addtogroup PERIPHERAL
  * @{
  */

/** @addtogroup CAN
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup CAN_Exported_Types CAN Exported Types
  * @{
  */

/**
  * @brief  HAL State structures definition
  */
typedef enum
{
  HAL_CAN_STATE_RESET             = 0x00U,  /*!< CAN not yet initialized or disabled */
  HAL_CAN_STATE_READY             = 0x01U,  /*!< CAN initialized and ready for use   */
  HAL_CAN_STATE_BUSY              = 0x02U,  /*!< CAN process is ongoing              */
  HAL_CAN_STATE_BUSY_TX           = 0x12U,  /*!< CAN process is ongoing              */
  HAL_CAN_STATE_BUSY_RX0          = 0x22U,  /*!< CAN process is ongoing              */
  HAL_CAN_STATE_BUSY_RX1          = 0x32U,  /*!< CAN process is ongoing              */
  HAL_CAN_STATE_BUSY_TX_RX0       = 0x42U,  /*!< CAN process is ongoing              */
  HAL_CAN_STATE_BUSY_TX_RX1       = 0x52U,  /*!< CAN process is ongoing              */
  HAL_CAN_STATE_BUSY_RX0_RX1      = 0x62U,  /*!< CAN process is ongoing              */
  HAL_CAN_STATE_BUSY_TX_RX0_RX1   = 0x72U,  /*!< CAN process is ongoing              */
  HAL_CAN_STATE_TIMEOUT           = 0x03U,  /*!< CAN in Timeout state                */
  HAL_CAN_STATE_ERROR             = 0x04U   /*!< CAN error state                     */

}HAL_CAN_StateTypeDef;

/**
  * @brief  CAN init structure definition
  */
typedef struct
{
  uint32_t Prescaler;  /*!< Specifies the length of a time quantum.
                            This parameter must be a number between Min_Data = 1 and Max_Data = 1024 */

  uint32_t Mode;       /*!< Specifies the CAN operating mode.
                            This parameter can be a value of @ref CAN_operating_mode */

  uint32_t SJW;        /*!< Specifies the maximum number of time quanta
                            the CAN hardware is allowed to lengthen or
                            shorten a bit to perform resynchronization.
                            This parameter can be a value of @ref CAN_synchronisation_jump_width */

  uint32_t BS1;        /*!< Specifies the number of time quanta in Bit Segment 1.
                            This parameter can be a value of @ref CAN_time_quantum_in_bit_segment_1 */

  uint32_t BS2;        /*!< Specifies the number of time quanta in Bit Segment 2.
                            This parameter can be a value of @ref CAN_time_quantum_in_bit_segment_2 */

  uint32_t TTCM;       /*!< Enable or disable the time triggered communication mode.
                            This parameter can be set to ENABLE or DISABLE. */

  uint32_t ABOM;       /*!< Enable or disable the automatic bus-off management.
                            This parameter can be set to ENABLE or DISABLE */

  uint32_t AWUM;       /*!< Enable or disable the automatic wake-up mode.
                            This parameter can be set to ENABLE or DISABLE */

  uint32_t NART;       /*!< Enable or disable the non-automatic retransmission mode.
                            This parameter can be set to ENABLE or DISABLE */

  uint32_t RFLM;       /*!< Enable or disable the receive FIFO Locked mode.
                            This parameter can be set to ENABLE or DISABLE */

  uint32_t TXFP;       /*!< Enable or disable the transmit FIFO priority.
                            This parameter can be set to ENABLE or DISABLE */
}CAN_InitTypeDef;

/** 
  * @brief  CAN filter configuration structure definition
  */
typedef struct
{
  uint32_t FilterIdHigh;          /*!< Specifies the filter identification number (MSBs for a 32-bit
                                       configuration, first one for a 16-bit configuration).
                                       This parameter must be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF. */ 
                                              
  uint32_t FilterIdLow;           /*!< Specifies the filter identification number (LSBs for a 32-bit
                                       configuration, second one for a 16-bit configuration).
                                       This parameter must be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF. */ 

  uint32_t FilterMaskIdHigh;      /*!< Specifies the filter mask number or identification number,
                                       according to the mode (MSBs for a 32-bit configuration,
                                       first one for a 16-bit configuration).
                                       This parameter must be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF. */ 

  uint32_t FilterMaskIdLow;       /*!< Specifies the filter mask number or identification number,
                                       according to the mode (LSBs for a 32-bit configuration,
                                       second one for a 16-bit configuration).
                                       This parameter must be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF. */ 

  uint32_t FilterFIFOAssignment;  /*!< Specifies the FIFO (0 or 1) which will be assigned to the filter.
                                       This parameter can be a value of @ref CAN_filter_FIFO */

  uint32_t FilterNumber;          /*!< Specifies the filter which will be initialized. 
                                       This parameter must be a number between Min_Data = 0 and Max_Data = 13. */

  uint32_t FilterMode;            /*!< Specifies the filter mode to be initialized.
                                       This parameter can be a value of @ref CAN_filter_mode */

  uint32_t FilterScale;           /*!< Specifies the filter scale.
                                       This parameter can be a value of @ref CAN_filter_scale */

  uint32_t FilterActivation;      /*!< Enable or disable the filter.
                                       This parameter can be set to ENABLE or DISABLE. */
  
}CAN_FilterConfTypeDef;

/** 
  * @brief  CAN Tx message structure definition  
  */
typedef struct
{
  uint32_t StdId;    /*!< Specifies the standard identifier.
                          This parameter must be a number between Min_Data = 0 and Max_Data = 0x7FF */

  uint32_t ExtId;    /*!< Specifies the extended identifier.
                          This parameter must be a number between Min_Data = 0 and Max_Data = 0x1FFFFFFF */

  uint32_t IDE;      /*!< Specifies the type of identifier for the message that will be transmitted.
                          This parameter can be a value of @ref CAN_Identifier_Type */

  uint32_t RTR;      /*!< Specifies the type of frame for the message that will be transmitted.
                          This parameter can be a value of @ref CAN_remote_transmission_request */

  uint32_t DLC;      /*!< Specifies the length of the frame that will be transmitted.
                          This parameter must be a number between Min_Data = 0 and Max_Data = 8 */

  uint8_t Data[8];   /*!< Contains the data to be transmitted.
                          This parameter must be a number between Min_Data = 0 and Max_Data = 0xFF */

}CanTxMsgTypeDef;

/**
  * @brief  CAN Rx message structure definition
  */
typedef struct
{
  uint32_t StdId;       /*!< Specifies the standard identifier.
                             This parameter must be a number between Min_Data = 0 and Max_Data = 0x7FF */

  uint32_t ExtId;       /*!< Specifies the extended identifier.
                             This parameter must be a number between Min_Data = 0 and Max_Data = 0x1FFFFFFF */

  uint32_t IDE;         /*!< Specifies the type of identifier for the message that will be received.
                             This parameter can be a value of @ref CAN_Identifier_Type */

  uint32_t RTR;         /*!< Specifies the type of frame for the received message.
                             This parameter can be a value of @ref CAN_remote_transmission_request */

  uint32_t DLC;         /*!< Specifies the length of the frame that will be received.
                             This parameter must be a number between Min_Data = 0 and Max_Data = 8 */

  uint8_t Data[8];      /*!< Contains the data to be received.
                             This parameter must be a number between Min_Data = 0 and Max_Data = 0xFF */

  uint32_t FMI;         /*!< Specifies the index of the filter the message stored in the mailbox passes through.
                             This parameter must be a number between Min_Data = 0 and Max_Data = 0xFF */

  uint32_t FIFONumber;  /*!< Specifies the receive FIFO number.
                             This parameter can be CAN_FIFO0 or CAN_FIFO1 */

}CanRxMsgTypeDef;

/**
  * @brief  CAN handle Structure definition
  */
typedef struct __CAN_HandleTypeDef
{
  reg_bxcan_t                 *Instance;  /*!< Register base address          */

  CAN_InitTypeDef             Init;       /*!< CAN required parameters        */

  CanTxMsgTypeDef*            pTxMsg;     /*!< Pointer to transmit structure  */

  CanRxMsgTypeDef*            pRxMsg;     /*!< Pointer to reception structure for RX FIFO0 msg */

  CanRxMsgTypeDef*            pRx1Msg;    /*!< Pointer to reception structure for RX FIFO1 msg */

  HAL_CAN_StateTypeDef        State;      /*!< CAN communication state        */

  HAL_LockTypeDef             Lock;       /*!< CAN locking object             */

  uint32_t                    ErrorCode;  /*!< CAN Error code                 */

}CAN_HandleTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup CAN_Exported_Constants CAN Exported Constants
  * @{
  */

/** @defgroup CAN_Error_Code CAN Error Code
  * @{
  */
#define   HAL_CAN_ERROR_NONE      0x00000000U    /*!< No error             */
#define   HAL_CAN_ERROR_EWG       0x00000001U    /*!< EWG error            */
#define   HAL_CAN_ERROR_EPV       0x00000002U    /*!< EPV error            */
#define   HAL_CAN_ERROR_BOF       0x00000004U    /*!< BOF error            */
#define   HAL_CAN_ERROR_STF       0x00000008U    /*!< Stuff error          */
#define   HAL_CAN_ERROR_FOR       0x00000010U    /*!< Form error           */
#define   HAL_CAN_ERROR_ACK       0x00000020U    /*!< Acknowledgment error */
#define   HAL_CAN_ERROR_BR        0x00000040U    /*!< Bit recessive        */
#define   HAL_CAN_ERROR_BD        0x00000080U    /*!< LEC dominant         */
#define   HAL_CAN_ERROR_CRC       0x00000100U    /*!< LEC transfer error   */
#define   HAL_CAN_ERROR_FOV0      0x00000200U    /*!< FIFO0 overrun error  */
#define   HAL_CAN_ERROR_FOV1      0x00000400U    /*!< FIFO1 overrun error  */
#define   HAL_CAN_ERROR_TXFAIL    0x00000800U    /*!< Transmit failure     */
/**
  * @}
  */

/** @defgroup CAN_InitStatus CAN initialization Status
  * @{
  */
#define CAN_INITSTATUS_FAILED       0x00000000U  /*!< CAN initialization failed */
#define CAN_INITSTATUS_SUCCESS      0x00000001U  /*!< CAN initialization OK */
/**
  * @}
  */

/** @defgroup CAN_operating_mode CAN Operating Mode
  * @{
  */
#define CAN_MODE_NORMAL             0x00000000U                                /*!< Normal mode   */
#define CAN_MODE_LOOPBACK           ((uint32_t)BXCAN_LBKM_MASK)                   /*!< Loopback mode */
#define CAN_MODE_SILENT             ((uint32_t)BXCAN_SILM_MASK)                   /*!< Silent mode   */
#define CAN_MODE_SILENT_LOOPBACK    ((uint32_t)(BXCAN_LBKM_MASK | BXCAN_SILM_MASK))  /*!< Loopback combined with silent mode */
/**
  * @}
  */

/** @defgroup CAN_synchronisation_jump_width CAN Synchronization Jump Width
  * @{
  */
#define CAN_SJW_1TQ                 0x00000000U                        /*!< 1 time quantum */
#define CAN_SJW_2TQ                 ((uint32_t)0x1U << BXCAN_SJW_POS)  /*!< 2 time quantum */
#define CAN_SJW_3TQ                 ((uint32_t)0x2U << BXCAN_SJW_POS)  /*!< 3 time quantum */
#define CAN_SJW_4TQ                 ((uint32_t)BXCAN_SJW_MASK)         /*!< 4 time quantum */
/**
  * @}
  */

/** @defgroup CAN_time_quantum_in_bit_segment_1 CAN Time Quantum in Bit Segment 1
  * @{
  */
#define CAN_BS1_1TQ                 0x00000000U                                            /*!< 1 time quantum  */
#define CAN_BS1_2TQ                 ((uint32_t)BXCAN_TS1_0)                                /*!< 2 time quantum  */
#define CAN_BS1_3TQ                 ((uint32_t)BXCAN_TS1_1)                                /*!< 3 time quantum  */
#define CAN_BS1_4TQ                 ((uint32_t)(BXCAN_TS1_1 | BXCAN_TS1_0))                /*!< 4 time quantum  */
#define CAN_BS1_5TQ                 ((uint32_t)BXCAN_TS1_2)                                /*!< 5 time quantum  */
#define CAN_BS1_6TQ                 ((uint32_t)(BXCAN_TS1_2 | BXCAN_TS1_0))                /*!< 6 time quantum  */
#define CAN_BS1_7TQ                 ((uint32_t)(BXCAN_TS1_2 | BXCAN_TS1_1))                /*!< 7 time quantum  */
#define CAN_BS1_8TQ                 ((uint32_t)(BXCAN_TS1_2 | BXCAN_TS1_1 | BXCAN_TS1_0))  /*!< 8 time quantum  */
#define CAN_BS1_9TQ                 ((uint32_t)BXCAN_TS1_3)                                /*!< 9 time quantum  */
#define CAN_BS1_10TQ                ((uint32_t)(BXCAN_TS1_3 | BXCAN_TS1_0))                /*!< 10 time quantum */
#define CAN_BS1_11TQ                ((uint32_t)(BXCAN_TS1_3 | BXCAN_TS1_1))                /*!< 11 time quantum */
#define CAN_BS1_12TQ                ((uint32_t)(BXCAN_TS1_3 | BXCAN_TS1_1 | BXCAN_TS1_0))  /*!< 12 time quantum */
#define CAN_BS1_13TQ                ((uint32_t)(BXCAN_TS1_3 | BXCAN_TS1_2))                /*!< 13 time quantum */
#define CAN_BS1_14TQ                ((uint32_t)(BXCAN_TS1_3 | BXCAN_TS1_2 | BXCAN_TS1_0))  /*!< 14 time quantum */
#define CAN_BS1_15TQ                ((uint32_t)(BXCAN_TS1_3 | BXCAN_TS1_2 | BXCAN_TS1_1))  /*!< 15 time quantum */
#define CAN_BS1_16TQ                ((uint32_t)BXCAN_TS1_MASK)                             /*!< 16 time quantum */
/**
  * @}
  */

/** @defgroup CAN_time_quantum_in_bit_segment_2 CAN Time Quantum in bit segment 2
  * @{
  */
#define CAN_BS2_1TQ                 0x00000000U                              /*!< 1 time quantum */
#define CAN_BS2_2TQ                 ((uint32_t)BXCAN_TS2_0)                  /*!< 2 time quantum */
#define CAN_BS2_3TQ                 ((uint32_t)BXCAN_TS2_1)                  /*!< 3 time quantum */
#define CAN_BS2_4TQ                 ((uint32_t)(BXCAN_TS2_1 | BXCAN_TS2_0))  /*!< 4 time quantum */
#define CAN_BS2_5TQ                 ((uint32_t)BXCAN_TS2_2)                  /*!< 5 time quantum */
#define CAN_BS2_6TQ                 ((uint32_t)(BXCAN_TS2_2 | BXCAN_TS2_0))  /*!< 6 time quantum */
#define CAN_BS2_7TQ                 ((uint32_t)(BXCAN_TS2_2 | BXCAN_TS2_1))  /*!< 7 time quantum */
#define CAN_BS2_8TQ                 ((uint32_t)BXCAN_TS2_MASK)               /*!< 8 time quantum */
/**
  * @}
  */

/** @defgroup CAN_filter_mode  CAN Filter Mode
  * @{
  */
#define CAN_FILTERMODE_IDMASK       ((uint8_t)0x00)  /*!< Identifier mask mode */
#define CAN_FILTERMODE_IDLIST       ((uint8_t)0x01)  /*!< Identifier list mode */
/**
  * @}
  */

/** @defgroup CAN_filter_scale CAN Filter Scale
  * @{
  */
#define CAN_FILTERSCALE_16BIT       ((uint8_t)0x00)  /*!< Two 16-bit filters */
#define CAN_FILTERSCALE_32BIT       ((uint8_t)0x01)  /*!< One 32-bit filter  */
/**
  * @}
  */

/** @defgroup CAN_filter_FIFO CAN Filter FIFO
  * @{
  */
#define CAN_FILTER_FIFO0             ((uint8_t)0x00)  /*!< Filter FIFO 0 assignment for filter x */
#define CAN_FILTER_FIFO1             ((uint8_t)0x01)  /*!< Filter FIFO 1 assignment for filter x */
/**
  * @}
  */

/** @defgroup CAN_Identifier_Type CAN Identifier Type
  * @{
  */
#define CAN_ID_STD                  0x00000000U  /*!< Standard Id */
#define CAN_ID_EXT                  0x00000004U  /*!< Extended Id */
/**
  * @}
  */

/** @defgroup CAN_remote_transmission_request CAN Remote Transmission Request
  * @{
  */
#define CAN_RTR_DATA                0x00000000U  /*!< Data frame */
#define CAN_RTR_REMOTE              0x00000002U  /*!< Remote frame */
/**
  * @}
  */

/** @defgroup CAN_transmit_constants CAN Transmit Constants
  * @{
  */
#define CAN_TXSTATUS_NOMAILBOX      ((uint8_t)0x04)  /*!< CAN cell did not provide CAN_TxStatus_NoMailBox */
/**
  * @}
  */

/** @defgroup CAN_receive_FIFO_number_constants CAN Receive FIFO Number
  * @{
  */
#define CAN_FIFO0                   ((uint8_t)0x00)  /*!< CAN FIFO 0 used to receive */
#define CAN_FIFO1                   ((uint8_t)0x01)  /*!< CAN FIFO 1 used to receive */
/**
  * @}
  */

 /** @defgroup CAN_flags CAN Flags
  * @{
  */
/* Transmit Flags */
#define CAN_FLAG_RQCP0             ((uint32_t)((TSR_REGISTER_INDEX << 8U) | CAN_TSR_RQCP0_BIT_POSITION))  /*!< Request MailBox0 flag         */
#define CAN_FLAG_RQCP1             ((uint32_t)((TSR_REGISTER_INDEX << 8U) | CAN_TSR_RQCP1_BIT_POSITION))  /*!< Request MailBox1 flag         */
#define CAN_FLAG_RQCP2             ((uint32_t)((TSR_REGISTER_INDEX << 8U) | CAN_TSR_RQCP2_BIT_POSITION))  /*!< Request MailBox2 flag         */
#define CAN_FLAG_TXOK0             ((uint32_t)((TSR_REGISTER_INDEX << 8U) | CAN_TSR_TXOK0_BIT_POSITION))  /*!< Transmission OK MailBox0 flag */
#define CAN_FLAG_TXOK1             ((uint32_t)((TSR_REGISTER_INDEX << 8U) | CAN_TSR_TXOK1_BIT_POSITION))  /*!< Transmission OK MailBox1 flag */
#define CAN_FLAG_TXOK2             ((uint32_t)((TSR_REGISTER_INDEX << 8U) | CAN_TSR_RQCP0_BIT_POSITION))  /*!< Transmission OK MailBox2 flag */
#define CAN_FLAG_TME0              ((uint32_t)((TSR_REGISTER_INDEX << 8U) | CAN_TSR_TME0_BIT_POSITION))   /*!< Transmit mailbox 0 empty flag */
#define CAN_FLAG_TME1              ((uint32_t)((TSR_REGISTER_INDEX << 8U) | CAN_TSR_TME1_BIT_POSITION))   /*!< Transmit mailbox 0 empty flag */
#define CAN_FLAG_TME2              ((uint32_t)((TSR_REGISTER_INDEX << 8U) | CAN_TSR_TME2_BIT_POSITION))   /*!< Transmit mailbox 0 empty flag */

/* Receive Flags */
#define CAN_FLAG_FF0               ((uint32_t)((RF0R_REGISTER_INDEX << 8U) | CAN_RF0R_FF0_BIT_POSITION))  /*!< FIFO 0 Full flag    */
#define CAN_FLAG_FOV0              ((uint32_t)((RF0R_REGISTER_INDEX << 8U) | CAN_RF0R_FOV0_BIT_POSITION)) /*!< FIFO 0 Overrun flag */

#define CAN_FLAG_FF1               ((uint32_t)((RF1R_REGISTER_INDEX << 8U) | CAN_RF1R_FF1_BIT_POSITION))  /*!< FIFO 1 Full flag    */
#define CAN_FLAG_FOV1              ((uint32_t)((RF1R_REGISTER_INDEX << 8U) | CAN_RF1R_FOV1_BIT_POSITION)) /*!< FIFO 1 Overrun flag */

/* Operating Mode Flags */
#define CAN_FLAG_WKU               ((uint32_t)((MSR_REGISTER_INDEX << 8U) | CAN_MSR_WKU_BIT_POSITION))    /*!< Wake up flag           */
#define CAN_FLAG_SLAK              ((uint32_t)((MSR_REGISTER_INDEX << 8U) | CAN_MSR_SLAK_BIT_POSITION))   /*!< Sleep acknowledge flag */
#define CAN_FLAG_SLAKI             ((uint32_t)((MSR_REGISTER_INDEX << 8U) | CAN_MSR_SLAKI_BIT_POSITION))  /*!< Sleep acknowledge flag */

/* @note When SLAK interrupt is disabled (SLKIE=0), no polling on SLAKI is possible. 
         In this case the SLAK bit can be polled.*/

/* Error Flags */
#define CAN_FLAG_EWG               ((uint32_t)((ESR_REGISTER_INDEX << 8U) | CAN_ESR_EWG_BIT_POSITION))    /*!< Error warning flag   */
#define CAN_FLAG_EPV               ((uint32_t)((ESR_REGISTER_INDEX << 8U) | CAN_ESR_EPV_BIT_POSITION))    /*!< Error passive flag   */
#define CAN_FLAG_BOF               ((uint32_t)((ESR_REGISTER_INDEX << 8U) | CAN_ESR_BOF_BIT_POSITION))    /*!< Bus-Off flag         */

/**
  * @}
  */

 /** @defgroup CAN_Interrupts CAN Interrupts
  * @{
  */
#define CAN_IT_TME                  ((uint32_t)BXCAN_TMEIE_MASK)   /*!< Transmit mailbox empty interrupt */

/* Receive Interrupts */
#define CAN_IT_FMP0                 ((uint32_t)BXCAN_FMPIE0_MASK)  /*!< FIFO 0 message pending interrupt */
#define CAN_IT_FF0                  ((uint32_t)BXCAN_FFIE0_MASK)   /*!< FIFO 0 full interrupt            */
#define CAN_IT_FOV0                 ((uint32_t)BXCAN_FOVIE0_MASK)  /*!< FIFO 0 overrun interrupt         */
#define CAN_IT_FMP1                 ((uint32_t)BXCAN_FMPIE1_MASK)  /*!< FIFO 1 message pending interrupt */
#define CAN_IT_FF1                  ((uint32_t)BXCAN_FFIE1_MASK)   /*!< FIFO 1 full interrupt            */
#define CAN_IT_FOV1                 ((uint32_t)BXCAN_FOVIE1_MASK)  /*!< FIFO 1 overrun interrupt         */

/* Operating Mode Interrupts */
#define CAN_IT_WKU                  ((uint32_t)BXCAN_WKUIE_MASK)  /*!< Wake-up interrupt           */
#define CAN_IT_SLK                  ((uint32_t)BXCAN_SLKIE_MASK)  /*!< Sleep acknowledge interrupt */

/* Error Interrupts */
#define CAN_IT_EWG                  ((uint32_t)BXCAN_EWGIE_MASK) /*!< Error warning interrupt   */
#define CAN_IT_EPV                  ((uint32_t)BXCAN_EPVIE_MASK) /*!< Error passive interrupt   */
#define CAN_IT_BOF                  ((uint32_t)BXCAN_BOFIE_MASK) /*!< Bus-off interrupt         */
#define CAN_IT_LEC                  ((uint32_t)BXCAN_LECIE_MASK) /*!< Last error code interrupt */
#define CAN_IT_ERR                  ((uint32_t)BXCAN_ERRIE_MASK) /*!< Error Interrupt           */
/**
  * @}
  */


/** @defgroup CAN_Private_Constants CAN Private Constants
  * @{
  */

/* CAN intermediate shift values used for CAN flags */
#define TSR_REGISTER_INDEX      0x5U
#define RF0R_REGISTER_INDEX     0x2U
#define RF1R_REGISTER_INDEX     0x4U
#define MSR_REGISTER_INDEX      0x1U
#define ESR_REGISTER_INDEX      0x3U

/* CAN flags bits position into their respective register (TSR, RF0R, RF1R or MSR regsiters) */
/* Transmit Flags */
#define CAN_TSR_RQCP0_BIT_POSITION     0x00000000U
#define CAN_TSR_RQCP1_BIT_POSITION     0x00000008U
#define CAN_TSR_RQCP2_BIT_POSITION     0x00000010U
#define CAN_TSR_TXOK0_BIT_POSITION     0x00000001U
#define CAN_TSR_TXOK1_BIT_POSITION     0x00000009U
#define CAN_TSR_TXOK2_BIT_POSITION     0x00000011U
#define CAN_TSR_TME0_BIT_POSITION      0x0000001AU
#define CAN_TSR_TME1_BIT_POSITION      0x0000001BU
#define CAN_TSR_TME2_BIT_POSITION      0x0000001CU

/* Receive Flags */
#define CAN_RF0R_FF0_BIT_POSITION      0x00000003U
#define CAN_RF0R_FOV0_BIT_POSITION     0x00000004U

#define CAN_RF1R_FF1_BIT_POSITION      0x00000003U
#define CAN_RF1R_FOV1_BIT_POSITION     0x00000004U

/* Operating Mode Flags */
#define CAN_MSR_WKU_BIT_POSITION       0x00000003U
#define CAN_MSR_SLAK_BIT_POSITION      0x00000001U
#define CAN_MSR_SLAKI_BIT_POSITION     0x00000004U

/* Error Flags */
#define CAN_ESR_EWG_BIT_POSITION       0x00000000U
#define CAN_ESR_EPV_BIT_POSITION       0x00000001U
#define CAN_ESR_BOF_BIT_POSITION       0x00000002U

/* Mask used by macro to get/clear CAN flags*/
#define CAN_FLAG_MASK                  0x000000FFU

/* Mailboxes definition */
#define CAN_TXMAILBOX_0   ((uint8_t)0x00)
#define CAN_TXMAILBOX_1   ((uint8_t)0x01)
#define CAN_TXMAILBOX_2   ((uint8_t)0x02)
/**
  * @}
  */

/**
  * @brief  Enable the specified CAN interrupts
  * @param  __HANDLE__: CAN handle.
  * @param  __INTERRUPT__: CAN Interrupt.
  *         This parameter can be one of the following values:
  *            @arg CAN_IT_TME: Transmit mailbox empty interrupt enable
  *            @arg CAN_IT_FMP0: FIFO 0 message pending interrupt
  *            @arg CAN_IT_FF0 : FIFO 0 full interrupt
  *            @arg CAN_IT_FOV0: FIFO 0 overrun interrupt
  *            @arg CAN_IT_FMP1: FIFO 1 message pending interrupt
  *            @arg CAN_IT_FF1 : FIFO 1 full interrupt
  *            @arg CAN_IT_FOV1: FIFO 1 overrun interrupt
  *            @arg CAN_IT_WKU : Wake-up interrupt
  *            @arg CAN_IT_SLK : Sleep acknowledge interrupt
  *            @arg CAN_IT_EWG : Error warning interrupt
  *            @arg CAN_IT_EPV : Error passive interrupt
  *            @arg CAN_IT_BOF : Bus-off interrupt
  *            @arg CAN_IT_LEC : Last error code interrupt
  *            @arg CAN_IT_ERR : Error Interrupt
  * @retval None.
  */
#define __HAL_CAN_ENABLE_IT(__HANDLE__, __INTERRUPT__) (((__HANDLE__)->Instance->CAN_IER) |= (__INTERRUPT__))

/**
  * @brief  Disable the specified CAN interrupts
  * @param  __HANDLE__: CAN handle.
  * @param  __INTERRUPT__: CAN Interrupt.
  *         This parameter can be one of the following values:
  *            @arg CAN_IT_TME: Transmit mailbox empty interrupt enable
  *            @arg CAN_IT_FMP0: FIFO 0 message pending interrupt
  *            @arg CAN_IT_FF0 : FIFO 0 full interrupt
  *            @arg CAN_IT_FOV0: FIFO 0 overrun interrupt
  *            @arg CAN_IT_FMP1: FIFO 1 message pending interrupt
  *            @arg CAN_IT_FF1 : FIFO 1 full interrupt
  *            @arg CAN_IT_FOV1: FIFO 1 overrun interrupt
  *            @arg CAN_IT_WKU : Wake-up interrupt
  *            @arg CAN_IT_SLK : Sleep acknowledge interrupt
  *            @arg CAN_IT_EWG : Error warning interrupt
  *            @arg CAN_IT_EPV : Error passive interrupt
  *            @arg CAN_IT_BOF : Bus-off interrupt
  *            @arg CAN_IT_LEC : Last error code interrupt
  *            @arg CAN_IT_ERR : Error Interrupt
  * @retval None.
  */
#define __HAL_CAN_DISABLE_IT(__HANDLE__, __INTERRUPT__) (((__HANDLE__)->Instance->CAN_IER) &= ~(__INTERRUPT__))

/**
  * @brief  Return the number of pending received messages.
  * @param  __HANDLE__: CAN handle.
  * @param  __FIFONUMBER__: Receive FIFO number, CAN_FIFO0 or CAN_FIFO1.
  * @retval The number of pending message.
  */
#define __HAL_CAN_MSG_PENDING(__HANDLE__, __FIFONUMBER__) (((__FIFONUMBER__) == CAN_FIFO0)? \
((uint8_t)((__HANDLE__)->Instance->CAN_RF0R & 0x03U)) : ((uint8_t)((__HANDLE__)->Instance->CAN_RF1R & 0x03U)))

/** @brief  Check whether the specified CAN flag is set or not.
  * @param  __HANDLE__: specifies the CAN Handle.
  * @param  __FLAG__: specifies the flag to check.
  *         This parameter can be one of the following values:
  *            @arg CAN_TSR_RQCP0: Request MailBox0 Flag
  *            @arg CAN_TSR_RQCP1: Request MailBox1 Flag
  *            @arg CAN_TSR_RQCP2: Request MailBox2 Flag
  *            @arg CAN_FLAG_TXOK0: Transmission OK MailBox0 Flag
  *            @arg CAN_FLAG_TXOK1: Transmission OK MailBox1 Flag
  *            @arg CAN_FLAG_TXOK2: Transmission OK MailBox2 Flag
  *            @arg CAN_FLAG_TME0: Transmit mailbox 0 empty Flag
  *            @arg CAN_FLAG_TME1: Transmit mailbox 1 empty Flag
  *            @arg CAN_FLAG_TME2: Transmit mailbox 2 empty Flag
  *            @arg CAN_FLAG_FMP0: FIFO 0 Message Pending Flag
  *            @arg CAN_FLAG_FF0: FIFO 0 Full Flag
  *            @arg CAN_FLAG_FOV0: FIFO 0 Overrun Flag
  *            @arg CAN_FLAG_FMP1: FIFO 1 Message Pending Flag
  *            @arg CAN_FLAG_FF1: FIFO 1 Full Flag
  *            @arg CAN_FLAG_FOV1: FIFO 1 Overrun Flag
  *            @arg CAN_FLAG_WKU: Wake up Flag
  *            @arg CAN_FLAG_SLAK: Sleep acknowledge Flag
  *            @arg CAN_FLAG_SLAKI: Sleep acknowledge Flag
  *            @arg CAN_FLAG_EWG: Error Warning Flag
  *            @arg CAN_FLAG_EPV: Error Passive Flag
  *            @arg CAN_FLAG_BOF: Bus-Off Flag
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_CAN_GET_FLAG(__HANDLE__, __FLAG__) \
((((__FLAG__) >> 8U) == 5U)? ((((__HANDLE__)->Instance->CAN_TSR) & (1U << ((__FLAG__) & CAN_FLAG_MASK))) == (1U << ((__FLAG__) & CAN_FLAG_MASK))): \
 (((__FLAG__) >> 8U) == 2U)? ((((__HANDLE__)->Instance->CAN_RF0R) & (1U << ((__FLAG__) & CAN_FLAG_MASK))) == (1U << ((__FLAG__) & CAN_FLAG_MASK))): \
 (((__FLAG__) >> 8U) == 4U)? ((((__HANDLE__)->Instance->CAN_RF1R) & (1U << ((__FLAG__) & CAN_FLAG_MASK))) == (1U << ((__FLAG__) & CAN_FLAG_MASK))): \
 (((__FLAG__) >> 8U) == 1U)? ((((__HANDLE__)->Instance->CAN_MSR) & (1U << ((__FLAG__) & CAN_FLAG_MASK))) == (1U << ((__FLAG__) & CAN_FLAG_MASK))): \
 ((((__HANDLE__)->Instance->CAN_ESR) & (1U << ((__FLAG__) & CAN_FLAG_MASK))) == (1U << ((__FLAG__) & CAN_FLAG_MASK))))

 /** @brief  Clear the specified CAN pending flag.
  * @param  __HANDLE__: specifies the CAN Handle.
  * @param  __FLAG__: specifies the flag to check.
  *         This parameter can be one of the following values:
  *            @arg CAN_TSR_RQCP0: Request MailBox0 Flag
  *            @arg CAN_TSR_RQCP1: Request MailBox1 Flag
  *            @arg CAN_TSR_RQCP2: Request MailBox2 Flag
  *            @arg CAN_FLAG_TXOK0: Transmission OK MailBox0 Flag
  *            @arg CAN_FLAG_TXOK1: Transmission OK MailBox1 Flag
  *            @arg CAN_FLAG_TXOK2: Transmission OK MailBox2 Flag
  *            @arg CAN_FLAG_TME0: Transmit mailbox 0 empty Flag
  *            @arg CAN_FLAG_TME1: Transmit mailbox 1 empty Flag
  *            @arg CAN_FLAG_TME2: Transmit mailbox 2 empty Flag
  *            @arg CAN_FLAG_FMP0: FIFO 0 Message Pending Flag
  *            @arg CAN_FLAG_FF0: FIFO 0 Full Flag
  *            @arg CAN_FLAG_FOV0: FIFO 0 Overrun Flag
  *            @arg CAN_FLAG_FMP1: FIFO 1 Message Pending Flag
  *            @arg CAN_FLAG_FF1: FIFO 1 Full Flag
  *            @arg CAN_FLAG_FOV1: FIFO 1 Overrun Flag
  *            @arg CAN_FLAG_WKU: Wake up Flag
  *            @arg CAN_FLAG_SLAKI: Sleep acknowledge Flag
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_CAN_CLEAR_FLAG(__HANDLE__, __FLAG__) \
((((__FLAG__) >> 8U) == TSR_REGISTER_INDEX) ? (((__HANDLE__)->Instance->CAN_TSR)  = (1U << ((__FLAG__) & CAN_FLAG_MASK))): \
 (((__FLAG__) >> 8U) == RF0R_REGISTER_INDEX)? (((__HANDLE__)->Instance->CAN_RF0R) = (1U << ((__FLAG__) & CAN_FLAG_MASK))): \
 (((__FLAG__) >> 8U) == RF1R_REGISTER_INDEX)? (((__HANDLE__)->Instance->CAN_RF1R) = (1U << ((__FLAG__) & CAN_FLAG_MASK))): \
 (((__FLAG__) >> 8U) == MSR_REGISTER_INDEX) ? (((__HANDLE__)->Instance->CAN_MSR)  = (1U << ((__FLAG__) & CAN_FLAG_MASK))): 0U)

 /** @brief  Check if the specified CAN interrupt source is enabled or disabled.
  * @param  __HANDLE__: specifies the CAN Handle.
  * @param  __INTERRUPT__: specifies the CAN interrupt source to check.
  *         This parameter can be one of the following values:
  *            @arg CAN_IT_TME: Transmit mailbox empty interrupt enable
  *            @arg CAN_IT_FMP0: FIFO 0 message pending interrupt
  *            @arg CAN_IT_FF0 : FIFO 0 full interrupt
  *            @arg CAN_IT_FOV0: FIFO 0 overrun interrupt
  *            @arg CAN_IT_FMP1: FIFO 1 message pending interrupt
  *            @arg CAN_IT_FF1 : FIFO 1 full interrupt
  *            @arg CAN_IT_FOV1: FIFO 1 overrun interrupt
  *            @arg CAN_IT_WKU : Wake-up interrupt
  *            @arg CAN_IT_SLK : Sleep acknowledge interrupt
  *            @arg CAN_IT_EWG : Error warning interrupt
  *            @arg CAN_IT_EPV : Error passive interrupt
  *            @arg CAN_IT_BOF : Bus-off interrupt
  *            @arg CAN_IT_LEC : Last error code interrupt
  *            @arg CAN_IT_ERR : Error Interrupt
  * @retval The new state of __IT__ (TRUE or FALSE).
  */
#define __HAL_CAN_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) ((((__HANDLE__)->Instance->CAN_IER & (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)

/**
  * @brief  Check the transmission status of a CAN Frame.
  * @param  __HANDLE__: specifies the CAN Handle.
  * @param  __TRANSMITMAILBOX__: the number of the mailbox that is used for transmission.
  * @retval The new status of transmission  (TRUE or FALSE).
  */
#define __HAL_CAN_TRANSMIT_STATUS(__HANDLE__, __TRANSMITMAILBOX__)\
(((__TRANSMITMAILBOX__) == CAN_TXMAILBOX_0)? ((((__HANDLE__)->Instance->CAN_TSR) & (BXCAN_RQCP0_MASK | BXCAN_TME0_MASK)) == (BXCAN_RQCP0_MASK | BXCAN_TME0_MASK)) :\
 ((__TRANSMITMAILBOX__) == CAN_TXMAILBOX_1)? ((((__HANDLE__)->Instance->CAN_TSR) & (BXCAN_RQCP1_MASK | BXCAN_TME1_MASK)) == (BXCAN_RQCP1_MASK | BXCAN_TME1_MASK)) :\
 ((((__HANDLE__)->Instance->CAN_TSR) & (BXCAN_RQCP2_MASK | BXCAN_TME2_MASK)) == (BXCAN_RQCP2_MASK | BXCAN_TME2_MASK)))

/**
  * @brief  Release the specified receive FIFO.
  * @param  __HANDLE__: CAN handle.
  * @param  __FIFONUMBER__: Receive FIFO number, CAN_FIFO0 or CAN_FIFO1.
  * @retval None.
  */
#define __HAL_CAN_FIFO_RELEASE(__HANDLE__, __FIFONUMBER__) (((__FIFONUMBER__) == CAN_FIFO0)? \
((__HANDLE__)->Instance->CAN_RF0R = BXCAN_RFOM0_MASK) : ((__HANDLE__)->Instance->CAN_RF1R = BXCAN_RFOM1_MASK))

/**
  * @brief  Cancel a transmit request.
  * @param  __HANDLE__: specifies the CAN Handle.
  * @param  __TRANSMITMAILBOX__: the number of the mailbox that is used for transmission.
  * @retval None.
  */
#define __HAL_CAN_CANCEL_TRANSMIT(__HANDLE__, __TRANSMITMAILBOX__)\
(((__TRANSMITMAILBOX__) == CAN_TXMAILBOX_0)? ((__HANDLE__)->Instance->CAN_TSR = BXCAN_ABRQ0_MASK) :\
 ((__TRANSMITMAILBOX__) == CAN_TXMAILBOX_1)? ((__HANDLE__)->Instance->CAN_TSR = BXCAN_ABRQ1_MASK) :\
 ((__HANDLE__)->Instance->CAN_TSR = BXCAN_ABRQ2_MASK))

/**
  * @brief  Enable or disables the DBG Freeze for CAN.
  * @param  __HANDLE__: specifies the CAN Handle.
  * @param  __NEWSTATE__: new state of the CAN peripheral.
  *         This parameter can be: ENABLE (CAN reception/transmission is frozen
  *         during debug. Reception FIFOs can still be accessed/controlled normally)
  *         or DISABLE (CAN is working during debug).
  * @retval None
  */
#define __HAL_CAN_DBG_FREEZE(__HANDLE__, __NEWSTATE__) (((__NEWSTATE__) == ENABLE)? \
((__HANDLE__)->Instance->CAN_MCR |= BXCAN_DBF_MASK) : ((__HANDLE__)->Instance->CAN_MCR &= ~BXCAN_DBF_MASK))


/**
  * @brief  Initializes the CAN peripheral according to the specified
  *         parameters in the CAN_InitStruct.
  * @param  hcan: pointer to a CAN_HandleTypeDef structure that contains
  *         the configuration information for the specified CAN.  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CAN_Init(CAN_HandleTypeDef* hcan);

/**
  * @brief  Deinitializes the CANx peripheral registers to their default reset values. 
  * @param  hcan: pointer to a CAN_HandleTypeDef structure that contains
  *         the configuration information for the specified CAN.  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CAN_DeInit(CAN_HandleTypeDef* hcan);

/**
  * @brief  Configures the CAN reception filter according to the specified
  *         parameters in the CAN_FilterInitStruct.
  * @param  hcan: pointer to a CAN_HandleTypeDef structure that contains
  *         the configuration information for the specified CAN.
  * @param  sFilterConfig: pointer to a CAN_FilterConfTypeDef structure that
  *         contains the filter configuration information.
  * @retval None
  */
HAL_StatusTypeDef HAL_CAN_ConfigFilter(CAN_HandleTypeDef* hcan, CAN_FilterConfTypeDef* sFilterConfig);

/**
  * @brief  Initiates and transmits a CAN frame message.
  * @param  hcan: pointer to a CAN_HandleTypeDef structure that contains
  *         the configuration information for the specified CAN.  
  * @param  Timeout: Specify Timeout value   
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CAN_Transmit(CAN_HandleTypeDef *hcan, uint32_t Timeout);

/**
  * @brief  Initiates and transmits a CAN frame message.
  * @param  hcan: pointer to a CAN_HandleTypeDef structure that contains
  *         the configuration information for the specified CAN.  
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CAN_Transmit_IT(CAN_HandleTypeDef *hcan);

/**
  * @brief  Receives a correct CAN frame.
  * @param  hcan: pointer to a CAN_HandleTypeDef structure that contains
  *         the configuration information for the specified CAN.  
  * @param  FIFONumber: FIFO Number value
  * @param  Timeout: Specify Timeout value 
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CAN_Receive(CAN_HandleTypeDef *hcan, uint8_t FIFONumber, uint32_t Timeout);

/**
  * @brief  Receives a correct CAN frame.
  * @param  hcan:       Pointer to a CAN_HandleTypeDef structure that contains
  *         the configuration information for the specified CAN.  
  * @param  FIFONumber: Specify the FIFO number    
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CAN_Receive_IT(CAN_HandleTypeDef *hcan, uint8_t FIFONumber);

/**
  * @brief  Enters the Sleep (low power) mode.
  * @param  hcan: pointer to a CAN_HandleTypeDef structure that contains
  *         the configuration information for the specified CAN.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_CAN_Sleep(CAN_HandleTypeDef *hcan);

/**
  * @brief  Wakes up the CAN peripheral from sleep mode, after that the CAN peripheral
  *         is in the normal mode.
  * @param  hcan: pointer to a CAN_HandleTypeDef structure that contains
  *         the configuration information for the specified CAN.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_CAN_WakeUp(CAN_HandleTypeDef *hcan);

/**
  * @brief  Handles CAN interrupt request  
  * @param  hcan: pointer to a CAN_HandleTypeDef structure that contains
  *         the configuration information for the specified CAN.
  * @retval None
  */
void HAL_CAN_IRQHandler(CAN_HandleTypeDef* hcan);

/**
  * @brief  Transmission  complete callback in non blocking mode 
  * @param  hcan: pointer to a CAN_HandleTypeDef structure that contains
  *         the configuration information for the specified CAN.
  * @retval None
  */
void HAL_CAN_TxCpltCallback(CAN_HandleTypeDef* hcan);

/**
  * @brief  Transmission  complete callback in non blocking mode 
  * @param  hcan: pointer to a CAN_HandleTypeDef structure that contains
  *         the configuration information for the specified CAN.
  * @retval None
  */
void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* hcan);

/**
  * @brief  Error CAN callback.
  * @param  hcan: pointer to a CAN_HandleTypeDef structure that contains
  *         the configuration information for the specified CAN.
  * @retval None
  */
void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan);
#endif
