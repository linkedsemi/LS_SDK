/**
  **********************************************************************************************************************
  * @file    
  * @brief   Header file of I3C HAL module.
  **********************************************************************************************************************
*/

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef HAL_I3C_CTRL_H
#define HAL_I3C_CTRL_H

#ifdef __cplusplus
extern "C" {
#endif


/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "ls_ll_i3c_controller.h"
#include "ls_hal_i3c_conmon.h"


/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup I3C_Exported_Constants I3C Exported Constants
  * @{
  */

/** @defgroup HAL_I3C_Notification_ID_definition I3C Notification ID definition
  * @brief    HAL I3C Notification ID definition
  * @{
  */

#define EVENT_ID_GETACCCR   (0x00000001U)
/*!< I3C target complete controller-role hand-off (direct GETACCR CCC) event         */
#define EVENT_ID_IBIEND     (0x00000002U)
/*!< I3C target IBI end process event                                                */
#define EVENT_ID_DAU        (0x00000004U)
/*!< I3C target receive a dynamic address update (ENTDAA/RSTDAA/SETNEWDA CCC) event  */
#define EVENT_ID_GETx       (0x00000008U)
/*!< I3C target receive any direct GETxxx CCC event                                  */
#define EVENT_ID_GETSTATUS  (0x00000010U)
/*!< I3C target receive get status command (direct GETSTATUS CCC) event              */
#define EVENT_ID_SETMWL     (0x00000020U)
/*!< I3C target receive maximum write length update (direct SETMWL CCC) event        */
#define EVENT_ID_SETMRL     (0x00000040U)
/*!< I3C target receive maximum read length update(direct SETMRL CCC) event          */
#define EVENT_ID_RSTACT     (0x00000080U)
/*!< I3C target detect reset pattern (broadcast or direct RSTACT CCC) event          */
#define EVENT_ID_ENTASx     (0x00000100U)
/*!< I3C target receive activity state update (direct or broadcast ENTASx) event     */
#define EVENT_ID_ENEC_DISEC (0x00000200U)
/*!< I3C target receive a direct or broadcast ENEC/DISEC CCC event                   */
#define EVENT_ID_DEFTGTS    (0x00000400U)
/*!< I3C target receive a broadcast DEFTGTS CCC event                                */
#define EVENT_ID_DEFGRPA    (0x00000800U)
/*!< I3C target receive a group addressing (broadcast DEFGRPA CCC) event             */
#define EVENT_ID_WKP        (0x00001000U)
/*!< I3C target wakeup event                                                         */
#define EVENT_ID_IBI        (0x00002000U)
/*!< I3C controller receive IBI event                                                */
#define EVENT_ID_CR         (0x00004000U)
/*!< I3C controller controller-role request event                                    */
#define EVENT_ID_HJ         (0x00008000U)
/*!< I3C controller hot-join event                                                   */
/**
  * @}
  */

/** @defgroup I3C_OPTION_DEFINITION OPTION DEFINITION
  * @note     HAL I3C option value coding follow below described bitmap:
  *           b31
  *                0  : message end type restart
  *                1  : message end type stop
  *           b30-b29-b28-b27
  *                0010  : I3C private message
  *                0011  : direct CCC message
  *                0110  : broadcast CCC message
  *                0100  : I2C private message
  *           b4
  *                0  : message without arbitration header
  *                1  : message with arbitration header
  *           b0
  *                0  : message without defining byte
  *                1  : message with defining byte
  *
  *           other bits (not used)
  * @{
  */
#define I3C_DIRECT_WITH_DEFBYTE_RESTART       (0x18000001U) /*!< Restart between each Direct Command then Stop
                                                                 request for last command.
                                                                 Each Command have an associated defining byte        */
#define I3C_DIRECT_WITH_DEFBYTE_STOP          (0x98000001U) /*!< Stop between each Direct Command.
                                                                 Each Command have an associated defining byte        */
#define I3C_DIRECT_WITHOUT_DEFBYTE_RESTART    (0x18000000U) /*!< Restart between each Direct Command then Stop
                                                                 request for last command.
                                                                 Each Command have not an associated defining byte    */
#define I3C_DIRECT_WITHOUT_DEFBYTE_STOP       (0x98000000U) /*!< Stop between each Direct Command.
                                                                 Each Command have not an associated defining byte    */
#define I3C_BROADCAST_WITH_DEFBYTE_RESTART    (0x30000001U) /*!< Restart between each Broadcast Command then Stop
                                                                 request for last command.
                                                                 Each Command have an associated defining byte        */
#define I3C_BROADCAST_WITH_DEFBYTE_STOP       (0xB0000001U) /*!< Stop between each Broadcast Command.
                                                                 Each Command have an associated defining byte        */
#define I3C_BROADCAST_WITHOUT_DEFBYTE_RESTART (0x30000000U) /*!< Restart between each Broadcast Command then Stop
                                                                 request for last command.
                                                                 Each Command have not an associated defining byte    */
#define I3C_BROADCAST_WITHOUT_DEFBYTE_STOP    (0xB0000000U) /*!< Stop between each Broadcast Command.
                                                                 Each Command have not an associated defining byte    */
#define I3C_PRIVATE_WITH_ARB_RESTART          (0x10000000U) /*!< Restart between each I3C Private message then Stop
                                                                 request for last message.
                                                                 Each Message start with an arbitration header after
                                                                 start bit condition                                  */
#define I3C_PRIVATE_WITH_ARB_STOP             (0x90000000U) /*!< Stop between each I3C Private message.
                                                                 Each Message start with an arbitration header after
                                                                 start bit condition                                  */
#define I3C_PRIVATE_WITHOUT_ARB_RESTART       (0x10000004U) /*!< Restart between each I3C message then Stop request
                                                                 for last message.
                                                                 Each Message start with Target address after start
                                                                 bit condition                                        */
#define I3C_PRIVATE_WITHOUT_ARB_STOP          (0x90000004U) /*!< Stop between each I3C Private message.
                                                                 Each Message start with Target address after
                                                                 start bit condition                                  */
#define I2C_PRIVATE_WITH_ARB_RESTART          (0x20000000U) /*!< Restart between each I2C Private message then Stop
                                                                 request for last message.
                                                                 Each Message start with an arbitration header after
                                                                 start bit condition                                  */
#define I2C_PRIVATE_WITH_ARB_STOP             (0xA0000000U) /*!< Stop between each I2C Private message.
                                                                 Each Message start with an arbitration header after
                                                                 start bit condition                                  */
#define I2C_PRIVATE_WITHOUT_ARB_RESTART       (0x20000004U) /*!< Restart between each I2C message then Stop request
                                                                 for last message.
                                                                 Each Message start with Target address after start
                                                                 bit condition                                        */
#define I2C_PRIVATE_WITHOUT_ARB_STOP          (0xA0000004U) /*!< Stop between each I2C Private message.
                                                                 Each Message start with Target address after start
                                                                 bit condition                                        */
/**
  * @}
  */

/** @defgroup I3C_DYNAMIC_ADDRESS_OPTION_DEFINITION I3C DYNAMIC ADDRESS OPTION DEFINITION
  * @{
  */
#define I3C_RSTDAA_THEN_ENTDAA  (0x00000001U) /*!< Initiate a RSTDAA before a ENTDAA procedure */
#define I3C_ONLY_ENTDAA         (0x00000002U) /*!< Initiate a ENTDAA without RSTDAA            */
/**
  * @}
  */

/* Private define to centralize the enable/disable of Interrupts */
#define I3C_XFER_LISTEN_IT            (0x00000001U)
#define I3C_XFER_TARGET_TX_IT         (0x00000002U)
#define I3C_XFER_TARGET_RX_IT         (0x00000004U)
#define I3C_XFER_DMA                  (0x00000008U)
#define I3C_XFER_TARGET_CTRLROLE      (0x00000010U)
#define I3C_XFER_TARGET_HOTJOIN       (0x00000020U)
#define I3C_XFER_TARGET_IBI           (0x00000040U)
#define I3C_XFER_CONTROLLER_TX_IT     (0x00000080U)
#define I3C_XFER_CONTROLLER_RX_IT     (0x00000100U)
#define I3C_XFER_CONTROLLER_RX_CCC_IT (0x00000400U)
#define I3C_XFER_CONTROLLER_DAA_IT    (0x00001000U)


/** @defgroup I3C_ERROR_CODE_DEFINITION ERROR CODE DEFINITION
  * @{
  */
#define HAL_I3C_ERROR_NONE (0x00000000U)                                /*!< No error                                 */

#define HAL_I3C_ERROR_CE0  (I3C_SER_PERR_MASK | LL_I3C_CONTROLLER_ERROR_CE0) /*!< Controller detected an illegally
                                                                             formatted CCC                            */
#define HAL_I3C_ERROR_CE1  (I3C_SER_PERR_MASK | LL_I3C_CONTROLLER_ERROR_CE1) /*!< Controller detected that transmitted data
                                                                             on the bus is different than expected    */
#define HAL_I3C_ERROR_CE2  (I3C_SER_PERR_MASK | LL_I3C_CONTROLLER_ERROR_CE2) /*!< Controller detected that broadcast address
                                                                             7'h7E has been nacked                    */
#define HAL_I3C_ERROR_CE3  (I3C_SER_PERR_MASK | LL_I3C_CONTROLLER_ERROR_CE3) /*!< Controller detected that new Controller
                                                                             did not drive the bus after
                                                                             Controller-role handoff                  */
#define HAL_I3C_ERROR_TE0  (I3C_SER_PERR_MASK | LL_I3C_TARGET_ERROR_TE0)     /*!< Target detected an invalid broadcast
                                                                             address                                  */
#define HAL_I3C_ERROR_TE1  (I3C_SER_PERR_MASK | LL_I3C_TARGET_ERROR_TE1)     /*!< Target detected an invalid CCC Code      */
#define HAL_I3C_ERROR_TE2  (I3C_SER_PERR_MASK | LL_I3C_TARGET_ERROR_TE2)     /*!< Target detected a parity error during
                                                                             a write data                             */
#define HAL_I3C_ERROR_TE3  (I3C_SER_PERR_MASK | LL_I3C_TARGET_ERROR_TE3)     /*!< Target detected a parity error on assigned
                                                                             address during dynamic address
                                                                             arbitration                              */
#define HAL_I3C_ERROR_TE4  (I3C_SER_PERR_MASK | LL_I3C_TARGET_ERROR_TE4)     /*!< Target detected 7'h7E missing after Restart
                                                                             during Dynamic Address Assignment
                                                                             procedure                                */
#define HAL_I3C_ERROR_TE5  (I3C_SER_PERR_MASK | LL_I3C_TARGET_ERROR_TE5)     /*!< Target detected an illegally
                                                                             formatted CCC                            */
#define HAL_I3C_ERROR_TE6  (I3C_SER_PERR_MASK | LL_I3C_TARGET_ERROR_TE6)     /*!< Target detected that transmitted data on
                                                                             the bus is different than expected       */
#define HAL_I3C_ERROR_DATA_HAND_OFF (I3C_SER_DERR_MASK)  /*!< I3C data error during controller-role hand-off process       */
#define HAL_I3C_ERROR_DATA_NACK     (I3C_SER_DNACK_MASK) /*!< I3C data not acknowledged error                              */
#define HAL_I3C_ERROR_ADDRESS_NACK  (I3C_SER_ANACK_MASK) /*!< I3C address not acknowledged error                           */
#define HAL_I3C_ERROR_COVR          (I3C_SER_COVR_MASK)  /*!< I3C S FIFO Over-Run or C FIFO Under-Run error                */
#define HAL_I3C_ERROR_DOVR          (I3C_SER_DOVR_MASK)  /*!< I3C Rx FIFO Over-Run or Tx FIFO Under-Run error              */
#define HAL_I3C_ERROR_STALL         (I3C_SER_STALL_MASK) /*!< I3C SCL stall error                                          */
#define HAL_I3C_ERROR_DMA           (0x00010000U)   /*!< DMA transfer error                                           */
#define HAL_I3C_ERROR_TIMEOUT       (0x00020000U)   /*!< Timeout error                                                */
#define HAL_I3C_ERROR_DMA_PARAM     (0x00040000U)   /*!< DMA Parameter Error                                          */
#define HAL_I3C_ERROR_INVALID_PARAM (0x00080000U)   /*!< Invalid Parameters error                                     */
#define HAL_I3C_ERROR_SIZE          (0x00100000U)   /*!< I3C size management error                                    */
#define HAL_I3C_ERROR_NOT_ALLOWED   (0x00200000U)   /*!< I3C operation is not allowed                                 */
#define HAL_I3C_ERROR_DYNAMIC_ADDR  (0x00400000U)   /*!< I3C dynamic address error                                    */

#if (USE_HAL_I3C_REGISTER_CALLBACKS == 1U)
#define HAL_I3C_ERROR_INVALID_CALLBACK (0x00800000U) /*!< Invalid Callback error                                      */
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS == 1U */
/**
  * @}
  */

/** @defgroup I3C_SDA_HOLD_TIME SDA HOLD TIME
  * @{
  */
#define HAL_I3C_SDA_HOLD_TIME_0_5  LL_I3C_SDA_HOLD_TIME_0_5 /*!< SDA hold time equal to 0.5 x ti3cclk */
#define HAL_I3C_SDA_HOLD_TIME_1_5  LL_I3C_SDA_HOLD_TIME_1_5 /*!< SDA hold time equal to 1.5 x ti3cclk */
/**
  * @}
  */

/** @defgroup I3C_OWN_ACTIVITY_STATE OWN ACTIVITY STATE
  * @{
  */
#define HAL_I3C_OWN_ACTIVITY_STATE_0  LL_I3C_OWN_ACTIVITY_STATE_0 /*!< Own Controller Activity state 0 */
#define HAL_I3C_OWN_ACTIVITY_STATE_1  LL_I3C_OWN_ACTIVITY_STATE_1 /*!< Own Controller Activity state 1 */
#define HAL_I3C_OWN_ACTIVITY_STATE_2  LL_I3C_OWN_ACTIVITY_STATE_2 /*!< Own Controller Activity state 2 */
#define HAL_I3C_OWN_ACTIVITY_STATE_3  LL_I3C_OWN_ACTIVITY_STATE_3 /*!< Own Controller Activity state 3 */
/**
  * @}
  */

/** @defgroup I3C_RX_FIFO_THRESHOLD RX FIFO THRESHOLD
  * @{
  */
#define HAL_I3C_RXFIFO_THRESHOLD_1_4  LL_I3C_RXFIFO_THRESHOLD_1_4  /*!< Rx Fifo Threshold is 1 byte  */
#define HAL_I3C_RXFIFO_THRESHOLD_4_4  LL_I3C_RXFIFO_THRESHOLD_4_4  /*!< Rx Fifo Threshold is 4 bytes */
/**
  * @}
  */

/** @defgroup I3C_TX_FIFO_THRESHOLD TX FIFO THRESHOLD
  * @{
  */
#define HAL_I3C_TXFIFO_THRESHOLD_1_4  LL_I3C_TXFIFO_THRESHOLD_1_4  /*!< Tx Fifo Threshold is 1 byte  */
#define HAL_I3C_TXFIFO_THRESHOLD_4_4  LL_I3C_TXFIFO_THRESHOLD_4_4  /*!< Tx Fifo Threshold is 4 bytes */
/**
  * @}
  */

/** @defgroup I3C_STATUS_FIFO_STATE STATUS FIFO STATE
  * @{
  */
#define HAL_I3C_STATUSFIFO_DISABLE  0x00000000U      /*!< Status FIFO mode disable */
#define HAL_I3C_STATUSFIFO_ENABLE   I3C_CFGR_SMODE   /*!< Status FIFO mode enable  */
/**
  * @}
  */

/** @defgroup I3C_DIRECTION DIRECTION
  * @{
  */
#define HAL_I3C_DIRECTION_WRITE     LL_I3C_DIRECTION_WRITE       /*!< Write transfer          */
#define HAL_I3C_DIRECTION_READ      LL_I3C_DIRECTION_READ        /*!< Read transfer           */
#define HAL_I3C_DIRECTION_BOTH      (LL_I3C_DIRECTION_READ | 1U) /*!< Read and Write transfer */
/**
  * @}
  */


/** @defgroup I3C_COMMON_INTERRUPT I3C COMMON INTERRUPT
  * @{
  */
#define HAL_I3C_IT_TXFNFIE      LL_I3C_IER_TXFNFIE /*!< Tx FIFO not full interrupt enable      */
#define HAL_I3C_IT_RXFNEIE      LL_I3C_IER_RXFNEIE /*!< Rx FIFO not empty interrupt enable     */
#define HAL_I3C_IT_FCIE         LL_I3C_IER_FCIE    /*!< Frame complete interrupt enable        */
#define HAL_I3C_IT_ERRIE        LL_I3C_IER_ERRIE   /*!< Error interrupt enable                 */
#define HAL_I3C_ALL_COMMON_ITS  (uint32_t)(LL_I3C_IER_TXFNFIE | LL_I3C_IER_RXFNEIE | \
                                           LL_I3C_IER_FCIE    | LL_I3C_IER_ERRIE)
/**
  * @}
  */

#define HAL_I3C_ALL_TGT_ITS  0

/**
  * @}
  */

/** @defgroup I3C_CONTROLLER_INTERRUPT I3C CONTROLLER INTERRUPT
  * @{
  */
#define HAL_I3C_IT_CFNFIE      LL_I3C_IER_CFNFIE     /*!< Control FIFO not full interrupt enable     */
#define HAL_I3C_IT_SFNEIE      LL_I3C_IER_SFNEIE     /*!< Status FIFO not empty interrupt enable     */
#define HAL_I3C_IT_HJIE        LL_I3C_IER_HJIE       /*!< Hot-join interrupt enable                  */
#define HAL_I3C_IT_CRIE        LL_I3C_IER_CRIE       /*!< Controller-role request interrupt enable   */
#define HAL_I3C_IT_IBIIE       LL_I3C_IER_IBIIE      /*!< IBI request interrupt enable               */
#define HAL_I3C_IT_RXTGTENDIE  LL_I3C_IER_RXTGTENDIE /*!< Target-initiated read end interrupt enable */
#define HAL_I3C_ALL_CTRL_ITS   (uint32_t)(LL_I3C_IER_CFNFIE | LL_I3C_IER_SFNEIE | LL_I3C_IER_HJIE | \
                                          LL_I3C_IER_CRIE  | LL_I3C_IER_IBIIE  | LL_I3C_IER_RXTGTENDIE)
/**
  * @}
  */

/** @defgroup I3C_FLAGS I3C FLAGS
  * @{
  */
#define HAL_I3C_FLAG_CFEF       LL_I3C_EVR_CFEF      /*!< Control FIFO not empty flag      */
#define HAL_I3C_FLAG_TXFEF      LL_I3C_EVR_TXFEF     /*!< Tx FIFO empty flag               */
#define HAL_I3C_FLAG_CFNFF      LL_I3C_EVR_CFNFF     /*!< Control FIFO not full flag       */
#define HAL_I3C_FLAG_SFNEF      LL_I3C_EVR_SFNEF     /*!< Status FIFO not empty flag       */
#define HAL_I3C_FLAG_TXFNFF     LL_I3C_EVR_TXFNFF    /*!< Tx FIFO not full flag            */
#define HAL_I3C_FLAG_RXFNEF     LL_I3C_EVR_RXFNEF    /*!< Rx FIFO not empty flag           */
#define HAL_I3C_FLAG_FCF        LL_I3C_EVR_FCF       /*!< Frame complete flag              */
#define HAL_I3C_FLAG_RXTGTENDF  LL_I3C_EVR_RXTGTENDF /*!< Target-initiated read end flag   */
#define HAL_I3C_FLAG_ERRF       LL_I3C_EVR_ERRF      /*!< Error flag                       */
#define HAL_I3C_FLAG_IBIF       LL_I3C_EVR_IBIF      /*!< IBI request flag                 */
#define HAL_I3C_FLAG_CRF        LL_I3C_EVR_CRF       /*!< Controller-role request flag     */
#define HAL_I3C_FLAG_HJF        LL_I3C_EVR_HJF       /*!< Hot-join flag                    */

/**
  * @}
  */

/** @defgroup I3C_BCR_IN_PAYLOAD I3C BCR IN PAYLOAD
  * @{
  */
#define HAL_I3C_BCR_IN_PAYLOAD_SHIFT    48  /*!< BCR field in target payload */
/**
  * @}
  */

/** @defgroup I3C_PATTERN_CONFIGURATION I3C PATTERN CONFIGURATION
  * @{
  */
#define HAL_I3C_TARGET_RESET_PATTERN             0x00000001U        /*!< Target reset pattern */
#define HAL_I3C_HDR_EXIT_PATTERN                 0x00000002U        /*!< HDR exit pattern */
/**
  * @}
  */

/** @defgroup I3C_RESET_PATTERN RESET PATTERN
  * @{
  */
#define HAL_I3C_RESET_PATTERN_DISABLE            0x00000000U
/*!< Standard STOP condition emitted at the end of a frame */
#define HAL_I3C_RESET_PATTERN_ENABLE             I3C_CFGR_RSTPTRN
/*!< Reset pattern is inserted before the STOP condition of any emitted frame */
/**
  * @}
  */

/* Exported macros ---------------------------------------------------------------------------------------------------*/
/** @defgroup I3C_Exported_Macros I3C Exported Macros
  * @{
  */

/** @brief Reset I3C handle state.
  * @param  __HANDLE__ specifies the I3C Handle.
  * @retval None
  */
#if (USE_HAL_I3C_REGISTER_CALLBACKS == 1)
#define __HAL_I3C_RESET_HANDLE_STATE(__HANDLE__)                do{                                             \
                                                                    (__HANDLE__)->State = HAL_I3C_STATE_RESET;  \
                                                                    (__HANDLE__)->MspInitCallback = NULL;       \
                                                                    (__HANDLE__)->MspDeInitCallback = NULL;     \
                                                                  } while(0)
#else
#define __HAL_I3C_RESET_HANDLE_STATE(__HANDLE__)                ((__HANDLE__)->State = HAL_I3C_STATE_RESET)
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS */

/** @brief  Enable the specified I3C interrupt.
  * @param  __HANDLE__ specifies the I3C Handle.
  * @param  __INTERRUPT__ specifies the interrupt source to enable.
  *         This parameter can be one value or a combination of the following group's values:
  *            @arg @ref I3C_CONTROLLER_INTERRUPT
  *            @arg @ref I3C_TARGET_INTERRUPT
  *            @arg @ref I3C_COMMON_INTERRUPT
  * @retval None
  */
#define __HAL_I3C_ENABLE_IT(__HANDLE__, __INTERRUPT__)   ((__HANDLE__)->Instance->IER |= (__INTERRUPT__))

/** @brief  Disable the specified I3C interrupt.
  * @param  __HANDLE__ specifies the I3C Handle.
  * @param  __INTERRUPT__ specifies the interrupt source to disable.
  *         This parameter can be one value or a combination of the following group's values:
  *            @arg @ref I3C_CONTROLLER_INTERRUPT
  *            @arg @ref I3C_TARGET_INTERRUPT
  *            @arg @ref I3C_COMMON_INTERRUPT
  * @retval None
  */
#define __HAL_I3C_DISABLE_IT(__HANDLE__, __INTERRUPT__)  ((__HANDLE__)->Instance->IER &= (~(__INTERRUPT__)))

/** @brief  Check whether the specified I3C flag is set or not.
  * @param  __HANDLE__ specifies the I3C Handle.
  * @param  __FLAG__ specifies the flag to check.
  *         This parameter can be one value of the group @arg @ref I3C_FLAGS values.
  * @retval The new state of __FLAG__ (SET or RESET).
  */
#define __HAL_I3C_GET_FLAG(__HANDLE__, __FLAG__) (((((__HANDLE__)->Instance->EVR) &\
                                                    (__FLAG__)) == (__FLAG__)) ? SET : RESET)

/** @brief  Get Bus Characterics in payload (64bits) receive during ENTDAA procedure.
  * @param  __PAYLOAD__ specifies the Bus Characteristics capabilities retrieve during ENTDAA procedure.
  *         This parameter must be a number between Min_Data=0x00(uint64_t) and Max_Data=0xFFFFFFFFFFFFFFFFFF.
  * @retval The value of BCR Return value between Min_Data=0x00 and Max_Data=0xFF.
  */
#define __HAL_I3C_GET_BCR(__PAYLOAD__) (((uint32_t)((uint64_t)(__PAYLOAD__) >> HAL_I3C_BCR_IN_PAYLOAD_SHIFT)) & \
                                        I3C_BCR_BCR)

/** @brief  Check IBI request capabilities.
  * @param  __BCR__ specifies the Bus Characteristics capabilities retrieve during ENTDAA procedure.
  *         This parameter must be a number between Min_Data=0x00 and Max_Data=0xFF.
  * @retval The state of IBI request capabilities (ENABLE or DISABLE).
  */
#define __HAL_I3C_GET_IBI_CAPABLE(__BCR__) (((((__BCR__) & I3C_BCR_BCR1_Msk) >> I3C_BCR_BCR1_POS) == 1U) \
                                            ? ENABLE : DISABLE)

/** @brief  Check IBI additional data byte capabilities.
  * @param  __BCR__ specifies the Bus Characteristics capabilities retrieve during ENTDAA procedure.
  *         This parameter must be a number between Min_Data=0x00 and Max_Data=0xFF.
  * @retval The state of IBI additional data byte capabilities (ENABLE or DISABLE).
  */
#define __HAL_I3C_GET_IBI_PAYLOAD(__BCR__) (((((__BCR__) & I3C_BCR_BCR2_Msk) >> I3C_BCR_BCR2_POS) == 1U) \
                                            ? ENABLE : DISABLE)

/** @brief  Check Controller role request capabilities.
  * @param  __BCR__ specifies the Bus Characteristics capabilities retrieve during ENTDAA procedure.
  *         This parameter must be a number between Min_Data=0x00 and Max_Data=0xFF.
  * @retval The state of Controller role request capabilities (ENABLE or DISABLE).
  */
#define __HAL_I3C_GET_CR_CAPABLE(__BCR__) (((((__BCR__) & I3C_BCR_BCR6_Msk) >> I3C_BCR_BCR6_POS) == 1U) \
                                           ? ENABLE : DISABLE)

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup I3C_Exported_Functions
  * @{
  */

/** @addtogroup I3C_Exported_Functions_Group1 Initialization and de-initialization functions.
  * @{
  */
HAL_StatusTypeDef HAL_I3C_Controller_Init(I3C_HandleTypeDef *hi3c);
HAL_StatusTypeDef HAL_I3C_DeInit(I3C_HandleTypeDef *hi3c);
void HAL_I3C_MspInit(I3C_HandleTypeDef *hi3c);
void HAL_I3C_MspDeInit(I3C_HandleTypeDef *hi3c);
/**
  * @}
  */

HAL_StatusTypeDef HAL_I3C_Controller_ActivateNotification(I3C_HandleTypeDef *hi3c, I3C_XferTypeDef *pXferData,
                                               uint32_t interruptMask);
HAL_StatusTypeDef HAL_I3C_Controller_DeactivateNotification(I3C_HandleTypeDef *hi3c, uint32_t interruptMask);
void HAL_I3C_CtrlTxCpltCallback(I3C_HandleTypeDef *hi3c);
void HAL_I3C_CtrlRxCpltCallback(I3C_HandleTypeDef *hi3c);
void HAL_I3C_CtrlMultipleXferCpltCallback(I3C_HandleTypeDef *hi3c);
void HAL_I3C_CtrlDAACpltCallback(I3C_HandleTypeDef *hi3c);
void HAL_I3C_TgtReqDynamicAddrCallback(I3C_HandleTypeDef *hi3c, uint64_t targetPayload);
void HAL_I3C_TgtTxCpltCallback(I3C_HandleTypeDef *hi3c);
void HAL_I3C_TgtRxCpltCallback(I3C_HandleTypeDef *hi3c);
void HAL_I3C_TgtHotJoinCallback(I3C_HandleTypeDef *hi3c, uint8_t dynamicAddress);
void HAL_I3C_NotifyCallback(I3C_HandleTypeDef *hi3c, uint32_t eventId);
void HAL_I3C_AbortCpltCallback(I3C_HandleTypeDef *hi3c);
void HAL_I3C_ErrorCallback(I3C_HandleTypeDef *hi3c);
void HAL_I3C_ER_IRQHandler(I3C_HandleTypeDef *hi3c);
void HAL_I3C_EV_IRQHandler(I3C_HandleTypeDef *hi3c);
/**
  * @}
  */

/** @addtogroup I3C_Exported_Functions_Group3 Configuration functions.
  * @{
  */
HAL_StatusTypeDef HAL_I3C_Ctrl_BusCharacteristicConfig(I3C_HandleTypeDef *hi3c,
                                                       const LL_I3C_CtrlBusConfTypeDef *pConfig);
HAL_StatusTypeDef HAL_I3C_Tgt_BusCharacteristicConfig(I3C_HandleTypeDef *hi3c,
                                                      const LL_I3C_TgtBusConfTypeDef *pConfig);
HAL_StatusTypeDef HAL_I3C_SetConfigFifo(I3C_HandleTypeDef *hi3c, const I3C_FifoConfTypeDef *pConfig);
HAL_StatusTypeDef HAL_I3C_Ctrl_Config(I3C_HandleTypeDef *hi3c, const I3C_CtrlConfTypeDef *pConfig);
HAL_StatusTypeDef HAL_I3C_Tgt_Config(I3C_HandleTypeDef *hi3c, const I3C_TgtConfTypeDef *pConfig);
HAL_StatusTypeDef HAL_I3C_Ctrl_ConfigBusDevices(I3C_HandleTypeDef           *hi3c,
                                                const I3C_DeviceConfTypeDef *pDesc,
                                                uint8_t                      nbDevice);
HAL_StatusTypeDef HAL_I3C_AddDescToFrame(I3C_HandleTypeDef         *hi3c,
                                         const I3C_CCCTypeDef      *pCCCDesc,
                                         const I3C_PrivateTypeDef  *pPrivateDesc,
                                         I3C_XferTypeDef           *pXferData,
                                         uint8_t                   nbFrame,
                                         uint32_t                  option);
/**
  * @}
  */

/** @addtogroup I3C_Exported_Functions_Group4 FIFO Management functions.
  * @{
  */
HAL_StatusTypeDef HAL_I3C_FlushAllFifo(I3C_HandleTypeDef *hi3c);
HAL_StatusTypeDef HAL_I3C_FlushTxFifo(I3C_HandleTypeDef *hi3c);
HAL_StatusTypeDef HAL_I3C_FlushRxFifo(I3C_HandleTypeDef *hi3c);
HAL_StatusTypeDef HAL_I3C_FlushControlFifo(I3C_HandleTypeDef *hi3c);
HAL_StatusTypeDef HAL_I3C_FlushStatusFifo(I3C_HandleTypeDef *hi3c);
HAL_StatusTypeDef HAL_I3C_ClearConfigFifo(I3C_HandleTypeDef *hi3c);
HAL_StatusTypeDef HAL_I3C_GetConfigFifo(I3C_HandleTypeDef *hi3c, I3C_FifoConfTypeDef *pConfig);
/**
  * @}
  */

/** @addtogroup I3C_Exported_Functions_Group5 Controller operational functions.
  * @{
  */
/* Controller transmit direct write or a broadcast CCC command APIs */
HAL_StatusTypeDef HAL_I3C_Ctrl_TransmitCCC(I3C_HandleTypeDef *hi3c,
                                           I3C_XferTypeDef   *pXferData,
                                           uint32_t           timeout);
HAL_StatusTypeDef HAL_I3C_Ctrl_TransmitCCC_IT(I3C_HandleTypeDef *hi3c,
                                              I3C_XferTypeDef   *pXferData);
HAL_StatusTypeDef HAL_I3C_Ctrl_TransmitCCC_DMA(I3C_HandleTypeDef *hi3c,
                                               I3C_XferTypeDef   *pXferData);

/* Controller transmit direct read CCC command APIs */
HAL_StatusTypeDef HAL_I3C_Ctrl_ReceiveCCC(I3C_HandleTypeDef *hi3c,
                                          I3C_XferTypeDef   *pXferData,
                                          uint32_t           timeout);
HAL_StatusTypeDef HAL_I3C_Ctrl_ReceiveCCC_IT(I3C_HandleTypeDef *hi3c,
                                             I3C_XferTypeDef   *pXferData);
HAL_StatusTypeDef HAL_I3C_Ctrl_ReceiveCCC_DMA(I3C_HandleTypeDef *hi3c,
                                              I3C_XferTypeDef   *pXferData);

/* Controller private write APIs */
HAL_StatusTypeDef HAL_I3C_Ctrl_Transmit(I3C_HandleTypeDef   *hi3c,
                                        I3C_XferTypeDef     *pXferData,
                                        uint32_t             timeout);
HAL_StatusTypeDef HAL_I3C_Ctrl_Transmit_IT(I3C_HandleTypeDef   *hi3c,
                                           I3C_XferTypeDef     *pXferData);
HAL_StatusTypeDef HAL_I3C_Ctrl_Transmit_DMA(I3C_HandleTypeDef   *hi3c,
                                            I3C_XferTypeDef     *pXferData);

/* Controller private read APIs */
HAL_StatusTypeDef HAL_I3C_Ctrl_Receive(I3C_HandleTypeDef   *hi3c,
                                       I3C_XferTypeDef     *pXferData,
                                       uint32_t             timeout);
HAL_StatusTypeDef HAL_I3C_Ctrl_Receive_IT(I3C_HandleTypeDef   *hi3c,
                                          I3C_XferTypeDef     *pXferData);
HAL_StatusTypeDef HAL_I3C_Ctrl_Receive_DMA(I3C_HandleTypeDef   *hi3c,
                                           I3C_XferTypeDef     *pXferData);

/* Controller multiple Direct CCC Command, I3C private or I2C transfer APIs */
HAL_StatusTypeDef HAL_I3C_Ctrl_MultipleTransfer_IT(I3C_HandleTypeDef   *hi3c,
                                                   I3C_XferTypeDef     *pXferData);
HAL_StatusTypeDef HAL_I3C_Ctrl_MultipleTransfer_DMA(I3C_HandleTypeDef   *hi3c,
                                                    I3C_XferTypeDef     *pXferData);

/* Controller assign dynamic address APIs */
HAL_StatusTypeDef HAL_I3C_Ctrl_SetDynAddr(I3C_HandleTypeDef *hi3c, uint8_t devAddress);
HAL_StatusTypeDef HAL_I3C_Ctrl_DynAddrAssign_IT(I3C_HandleTypeDef *hi3c, uint32_t dynOption);
HAL_StatusTypeDef HAL_I3C_Ctrl_DynAddrAssign(I3C_HandleTypeDef *hi3c,
                                             uint64_t          *target_payload,
                                             uint32_t           dynOption,
                                             uint32_t           timeout);
/* Controller check device ready APIs */
HAL_StatusTypeDef HAL_I3C_Ctrl_IsDeviceI3C_Ready(I3C_HandleTypeDef *hi3c,
                                                 uint8_t            devAddress,
                                                 uint32_t           trials,
                                                 uint32_t           timeout);
HAL_StatusTypeDef HAL_I3C_Ctrl_IsDeviceI2C_Ready(I3C_HandleTypeDef *hi3c,
                                                 uint8_t            devAddress,
                                                 uint32_t           trials,
                                                 uint32_t           timeout);
/**
  * @}
  */

/** @addtogroup I3C_Exported_Functions_Group6 Target operational functions.
  * @{
  */
HAL_StatusTypeDef HAL_I3C_Tgt_Transmit_IT(I3C_HandleTypeDef *hi3c, I3C_XferTypeDef *pXferData);
HAL_StatusTypeDef HAL_I3C_Tgt_Receive_IT(I3C_HandleTypeDef *hi3c, I3C_XferTypeDef *pXferData);
HAL_StatusTypeDef HAL_I3C_Tgt_IBIReq_IT(I3C_HandleTypeDef *hi3c, const uint8_t *pPayload, uint8_t payloadSize);
/**
  * @}
  */

/** @addtogroup I3C_Exported_Functions_Group7 Generic and Common functions.
  * @{
  */
HAL_StatusTypeDef HAL_I3C_Abort_IT(I3C_HandleTypeDef *hi3c);
HAL_I3C_StateTypeDef HAL_I3C_GetState(const I3C_HandleTypeDef *hi3c);
HAL_I3C_ModeTypeDef HAL_I3C_GetMode(const I3C_HandleTypeDef *hi3c);
uint32_t HAL_I3C_GetError(const I3C_HandleTypeDef *hi3c);
HAL_StatusTypeDef HAL_I3C_GetCCCInfo(I3C_HandleTypeDef *hi3c,
                                     uint32_t notifyId,
                                     I3C_CCCInfoTypeDef *pCCCInfo);
/**
  * @}
  */


/* Private macros ----------------------------------------------------------------------------------------------------*/
/** @defgroup I3C_Private_Macro I3C Private Macros
  * @{
  */
#define IS_I3C_MODE(__MODE__) (((__MODE__) == HAL_I3C_MODE_NONE)       || \
                               ((__MODE__) == HAL_I3C_MODE_CONTROLLER) || \
                               ((__MODE__) == HAL_I3C_MODE_TARGET))

#define IS_I3C_RESET_PATTERN(__RSTPTRN__) (((__RSTPTRN__) == HAL_I3C_RESET_PATTERN_ENABLE)   || \
                                           ((__RSTPTRN__) == HAL_I3C_RESET_PATTERN_DISABLE))

#define IS_I3C_INTERRUPTMASK(__MODE__, __ITMASK__) (((__MODE__) == HAL_I3C_MODE_CONTROLLER)             ? \
                                                    ((((__ITMASK__) & HAL_I3C_ALL_CTRL_ITS) != 0x0U)   || \
                                                     (((__ITMASK__) & HAL_I3C_ALL_COMMON_ITS) != 0x0U)) : \
                                                    ((((__ITMASK__) & HAL_I3C_ALL_TGT_ITS) != 0x0U)    || \
                                                     (((__ITMASK__) & HAL_I3C_ALL_COMMON_ITS) != 0x0U)))

#define IS_I3C_ENTDAA_OPTION(__OPTION__) (((__OPTION__) == I3C_RSTDAA_THEN_ENTDAA) || \
                                          ((__OPTION__) == I3C_ONLY_ENTDAA))

#define IS_I3C_SDAHOLDTIME_VALUE(__VALUE__) (((__VALUE__) == HAL_I3C_SDA_HOLD_TIME_0_5) || \
                                             ((__VALUE__) == HAL_I3C_SDA_HOLD_TIME_1_5))

#define IS_I3C_WAITTIME_VALUE(__VALUE__) (((__VALUE__) == HAL_I3C_OWN_ACTIVITY_STATE_0) || \
                                          ((__VALUE__) == HAL_I3C_OWN_ACTIVITY_STATE_1) || \
                                          ((__VALUE__) == HAL_I3C_OWN_ACTIVITY_STATE_2) || \
                                          ((__VALUE__) == HAL_I3C_OWN_ACTIVITY_STATE_3))

#define IS_I3C_TXFIFOTHRESHOLD_VALUE(__VALUE__) (((__VALUE__) == HAL_I3C_TXFIFO_THRESHOLD_1_4) || \
                                                 ((__VALUE__) == HAL_I3C_TXFIFO_THRESHOLD_4_4))

#define IS_I3C_RXFIFOTHRESHOLD_VALUE(__VALUE__) (((__VALUE__) == HAL_I3C_RXFIFO_THRESHOLD_1_4) || \
                                                 ((__VALUE__) == HAL_I3C_RXFIFO_THRESHOLD_4_4))

#define IS_I3C_STATUSFIFOSTATE_VALUE(__VALUE__) (((__VALUE__) == HAL_I3C_STATUSFIFO_DISABLE) || \
                                                 ((__VALUE__) == HAL_I3C_STATUSFIFO_ENABLE))

#define IS_I3C_DEVICE_VALUE(__VALUE__) (((__VALUE__) >= 1U) && ((__VALUE__) <= 4U))

#define IS_I3C_DYNAMICADDRESS_VALUE(__VALUE__) ((__VALUE__) <= 0x7FU)

#define IS_I3C_FUNCTIONALSTATE_VALUE(__VALUE__) (((__VALUE__) == DISABLE) || \
                                                 ((__VALUE__) == ENABLE))

#define I3C_CHECK_IT_SOURCE(__IER__, __IT__)  ((((__IER__) & (__IT__)) == (__IT__)) ? SET : RESET)

#define I3C_CHECK_FLAG(__ISR__, __FLAG__) ((((__ISR__) & (__FLAG__)) == (__FLAG__)) ? SET : RESET)

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* HAL_I3C_CTRL_H */
