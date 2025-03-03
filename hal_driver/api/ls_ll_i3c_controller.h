/**
  **********************************************************************************************************************
  * @file    
  * @brief   Header file of I3C HAL module.
  **********************************************************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _LL_I3C_H_
#define _LL_I3C_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "i3c_misc.h"
#include "reg_i3c.h"
#include "HAL_def.h"
#include "field_manipulate.h"

/** @defgroup I3C_LL I3C
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/
/** @defgroup I3C_LL_Private_Macros I3C Private Macros
  * @{
  */
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup I3C_LL_Exported_Constants I3C Exported Constants
  * @{
  */

/** @defgroup I3C_LL_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LL_I3C_ReadReg function
  * @{
  */
#define LL_I3C_EVR_CFEF                    I3C_EVR_CFEF
#define LL_I3C_EVR_TXFEF                   I3C_EVR_TXFEF
#define LL_I3C_EVR_CFNFF                   I3C_EVR_CFNFF
#define LL_I3C_EVR_SFNEF                   I3C_EVR_SFNEF
#define LL_I3C_EVR_TXFNFF                  I3C_EVR_TXFNFF
#define LL_I3C_EVR_RXFNEF                  I3C_EVR_RXFNEF
#define LL_I3C_EVR_FCF                     I3C_EVR_FCF
#define LL_I3C_EVR_RXTGTENDF               I3C_EVR_RXTGTENDF
#define LL_I3C_EVR_ERRF                    I3C_EVR_ERRF
#define LL_I3C_EVR_IBIF                    I3C_EVR_IBIF
#define LL_I3C_EVR_CRF                     I3C_EVR_CRF
#define LL_I3C_EVR_HJF                     I3C_EVR_HJF
#define LL_I3C_SER_PERR                    I3C_SER_PERR
#define LL_I3C_SER_STALL                   I3C_SER_STALL
#define LL_I3C_SER_DOVR                    I3C_SER_DOVR
#define LL_I3C_SER_COVR                    I3C_SER_COVR
#define LL_I3C_SER_ANACK                   I3C_SER_ANACK
#define LL_I3C_SER_DNACK                   I3C_SER_DNACK
#define LL_I3C_SER_DERR                    I3C_SER_DERR
/**
  * @}
  */

/** @defgroup I3C_LL_EC_IT IT Defines
  * @brief    IT defines which can be used with LL_I3C_ReadReg and  LL_I3C_WriteReg functions
  * @{
  */
#define LL_I3C_IER_CFNFIE                  I3C_IER_CFNFIE
#define LL_I3C_IER_SFNEIE                  I3C_IER_SFNEIE 
#define LL_I3C_IER_TXFNFIE                 I3C_IER_TXFNFIE
#define LL_I3C_IER_RXFNEIE                 I3C_IER_RXFNEIE
#define LL_I3C_IER_FCIE                    I3C_IER_FCIE
#define LL_I3C_IER_RXTGTENDIE              I3C_IER_RXTGTENDIE
#define LL_I3C_IER_ERRIE                   I3C_IER_ERRIE
#define LL_I3C_IER_IBIIE                   I3C_IER_IBIIE
#define LL_I3C_IER_CRIE                    I3C_IER_CRIE
#define LL_I3C_IER_HJIE                    I3C_IER_HJIE
/**
  * @}
  */

/** @defgroup I3C_LL_EC_MODE MODE
  * @{
  */
#define LL_I3C_MODE_CONTROLLER              I3C_CFGR_EN         /*!< I3C Controller mode */
#define LL_I3C_MODE_TARGET                  0x00000000U             /*!< I3C Target (Controller capable) mode */
/**
  * @}
  */

/** @defgroup I3C_LL_EC_DMA_REG_DATA DMA Register Data
  * @{
  */
#define LL_I3C_DMA_REG_DATA_TRANSMIT_BYTE   0x00000000U              /*!< Get address of data register used
                                                                          for transmission in Byte */
#define LL_I3C_DMA_REG_DATA_RECEIVE_BYTE    0x00000001U              /*!< Get address of data register used
                                                                          for reception in Byte */
#define LL_I3C_DMA_REG_DATA_TRANSMIT_WORD   0x00000002U              /*!< Get address of data register used for
                                                                          transmission in Word */
#define LL_I3C_DMA_REG_DATA_RECEIVE_WORD    0x00000003U              /*!< Get address of data register used
                                                                          for reception in Word */
#define LL_I3C_DMA_REG_STATUS               0x00000004U              /*!< Get address of status register used
                                                                          for transfer status in Word */
#define LL_I3C_DMA_REG_CONTROL              0x00000005U              /*!< Get address of control register used
                                                                          for transfer control in Word */
/**
  * @}
  */

/** @defgroup I3C_LL_EC_RX_THRESHOLD RX THRESHOLD
  * @{
  */
#define LL_I3C_RXFIFO_THRESHOLD_1_4         0x00000000U
/*!< Rx Fifo Threshold is 1 byte in a Fifo depth of 4 bytes */
#define LL_I3C_RXFIFO_THRESHOLD_4_4         I3C_CFGR_RXTHRES
/*!< Rx Fifo Threshold is 4 bytes in a Fifo depth of 4 bytes */
/**
  * @}
  */

/** @defgroup I3C_LL_EC_TX_THRESHOLD TX THRESHOLD
  * @{
  */
#define LL_I3C_TXFIFO_THRESHOLD_1_4         0x00000000U
/*!< Tx Fifo Threshold is 1 byte in a Fifo depth of 4 bytes */
#define LL_I3C_TXFIFO_THRESHOLD_4_4         I3C_CFGR_TXTHRES
/*!< Tx Fifo Threshold is 4 bytes in a Fifo depth of 4 bytes */
/**
  * @}
  */

/** @defgroup I3C_LL_EC_SDA_HOLD_TIME SDA HOLD TIME 0
  * @{
  */
#define LL_I3C_SDA_HOLD_TIME_0_5           0x00000000U               /*!< SDA hold time is 0.5 x ti3cclk */
#define LL_I3C_SDA_HOLD_TIME_1_5           I3C_TIMINGR1_SDA_HD       /*!< SDA hold time is 1.5 x ti3cclk */
/**
  * @}
  */

/** @defgroup I3C_LL_EC_OWN_ACTIVITY_STATE OWN ACTIVITY STATE
  * @{
  */
#define LL_I3C_OWN_ACTIVITY_STATE_0        0x00000000U
/*!< Own Controller Activity state 0 */
#define LL_I3C_OWN_ACTIVITY_STATE_1        (0b01U<<I3C_TIMINGR1_ASNCR_POS)
/*!< Own Controller Activity state 1 */
#define LL_I3C_OWN_ACTIVITY_STATE_2        (0b10U<<I3C_TIMINGR1_ASNCR_POS)
/*!< Own Controller Activity state 2 */
#define LL_I3C_OWN_ACTIVITY_STATE_3        (LL_I3C_OWN_ACTIVITY_STATE_1 | LL_I3C_OWN_ACTIVITY_STATE_2)
/*!< Own Controller Activity state 3 */
/**
  * @}
  */

/** @defgroup I3C_LL_EC_DIRECTION DIRECTION
  * @{
  */
#define LL_I3C_DIRECTION_WRITE             0x00000000U               /*!< Write transfer      */
#define LL_I3C_DIRECTION_READ              I3C_CR_RNW                /*!< Read transfer       */
/**
  * @}
  */

/** @defgroup I3C_LL_EC_GENERATE GENERATE
  * @{
  */
#define LL_I3C_GENERATE_STOP               I3C_CR_MEND
/*!< Generate Stop condition after sending a message */
#define LL_I3C_GENERATE_RESTART            0x00000000U
/*!< Generate Restart condition after sending a message */
/**
  * @}
  */

/** @defgroup I3C_LL_EC_CONTROLLER_MTYPE CONTROLLER MTYPE
  * @{
  */
#define LL_I3C_CONTROLLER_MTYPE_RELEASE        0x00000000U
/*!< SCL output clock stops running until next instruction executed       */
#define LL_I3C_CONTROLLER_MTYPE_HEADER         (0b001U<<I3C_CR_MTYPE_POS)
/*!< Header Message */
#define LL_I3C_CONTROLLER_MTYPE_PRIVATE        (0b010U<<I3C_CR_MTYPE_POS)
/*!< Private Message Type */
#define LL_I3C_CONTROLLER_MTYPE_DIRECT         (0b011U<<I3C_CR_MTYPE_POS)
/*!< Direct Message Type */
#define LL_I3C_CONTROLLER_MTYPE_LEGACY_I2C     (0b100U<<I3C_CR_MTYPE_POS)
/*!< Legacy I2C Message Type */
#define LL_I3C_CONTROLLER_MTYPE_CCC            (0b110U<<I3C_CR_MTYPE_POS)
/*!< Common Command Code */
/**
  * @}
  */

/** @defgroup I3C_LL_EC_MESSAGE_DIRECTION MESSAGE DIRECTION
  * @{
  */
#define LL_I3C_MESSAGE_DIRECTION_WRITE     0x00000000U               /*!< Write data or command      */
#define LL_I3C_MESSAGE_DIRECTION_READ      I3C_SR_DIR                /*!< Read data       */
/**
  * @}
  */

/** @defgroup I3C_LL_EC_CONTROLLER_ERROR CONTROLLER ERROR
  * @{
  */
#define LL_I3C_CONTROLLER_ERROR_CE0        0x00000000U
/*!< Controller detected an illegally formatted CCC    */
#define LL_I3C_CONTROLLER_ERROR_CE1        (0b01U<<I3C_SER_CODERR_POS)
/*!< Controller detected that transmitted data on the bus is different than expected    */
#define LL_I3C_CONTROLLER_ERROR_CE2        (0b10U<<I3C_SER_CODERR_POS)
/*!< Controller detected that broadcast address 7'h7E has been nacked    */
#define LL_I3C_CONTROLLER_ERROR_CE3        (0b11U<<I3C_SER_CODERR_POS)
/*!< Controller detected that new Controller did not drive the bus after Controller-role handoff    */
/**
  * @}
  */


/** @defgroup I3C_BCR_IN_PAYLOAD I3C BCR IN PAYLOAD
  * @{
  */
#define LL_I3C_BCR_IN_PAYLOAD_SHIFT        48  /*!< BCR field in target payload */
/**
  * @}
  */

/** @defgroup I3C_LL_EC_IBI_CAPABILITY IBI CAPABILITY
  * @{
  */
#define LL_I3C_IBI_CAPABILITY              I3C_DEVRX_IBIACK
/*!< Controller acknowledge Target In Band Interrupt capable */
#define LL_I3C_IBI_NO_CAPABILITY           0x00000000U
/*!< Controller no acknowledge Target In Band Interrupt capable */
/**
  * @}
  */

/** @defgroup I3C_LL_EC_IBI_ADDITIONAL_DATA IBI ADDITIONAL DATA
  * @{
  */
#define LL_I3C_IBI_DATA_ENABLE             I3C_DEVRX_IBIDEN
/*!< A mandatory data byte follows the IBI acknowledgement */
#define LL_I3C_IBI_DATA_DISABLE            0x00000000U
/*!< No mandatory data byte follows the IBI acknowledgement */
/**
  * @}
  */

/** @defgroup I3C_LL_EC_CR_CAPABILITY CR CAPABILITY
  * @{
  */
#define LL_I3C_CR_CAPABILITY               I3C_DEVRX_CRACK
/*!< Controller acknowledge Target Controller Role capable */
#define LL_I3C_CR_NO_CAPABILITY            0x00000000U
/*!< Controller no acknowledge Target Controller Role capable */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup I3C_LL_Exported_Macros I3C Exported Macros
  * @{
  */

/** @defgroup I3C_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/** @brief  Get Bus Characterics in payload (64bits) receive during ENTDAA procedure.
  * @param  __PAYLOAD__ specifies the Bus Characteristics capabilities retrieve during ENTDAA procedure.
  *         This parameter must be a number between Min_Data=0x00(uint64_t) and Max_Data=0xFFFFFFFFFFFFFFFFFF.
  * @retval The value of BCR Return value between Min_Data=0x00 and Max_Data=0xFF.
  */
#define LL_I3C_GET_BCR(__PAYLOAD__) (((uint32_t)((uint64_t)(__PAYLOAD__) >> LL_I3C_BCR_IN_PAYLOAD_SHIFT)) & \
                                     I3C_BCR_BCR)

/** @brief  Check IBI request capabilities.
  * @param  __BCR__ specifies the Bus Characteristics capabilities retrieve during ENTDAA procedure.
  *         This parameter must be a number between Min_Data=0x00 and Max_Data=0xFF.
  * @retval Value of @ref I3C_LL_EC_IBI_CAPABILITY.
  */
#define LL_I3C_GET_IBI_CAPABLE(__BCR__) (((((__BCR__) & I3C_BCR_BCR1_Msk) >> I3C_BCR_BCR1_POS) == 1U) \
                                         ? LL_I3C_IBI_CAPABILITY : LL_I3C_IBI_NO_CAPABILITY)

/** @brief  Check IBI additional data byte capabilities.
  * @param  __BCR__ specifies the Bus Characteristics capabilities retrieve during ENTDAA procedure.
  *         This parameter must be a number between Min_Data=0x00 and Max_Data=0xFF.
  * @retval Value of @ref I3C_LL_EC_IBI_ADDITIONAL_DATA.
  */
#define LL_I3C_GET_IBI_PAYLOAD(__BCR__) (((((__BCR__) & I3C_BCR_BCR2_Msk) >> I3C_BCR_BCR2_POS) == 1U) \
                                         ? LL_I3C_IBI_DATA_ENABLE : LL_I3C_IBI_DATA_DISABLE)

/** @brief  Check Controller role request capabilities.
  * @param  __BCR__ specifies the Bus Characteristics capabilities retrieve during ENTDAA procedure.
  *         This parameter must be a number between Min_Data=0x00 and Max_Data=0xFF.
  * @retval Value of @ref I3C_LL_EC_CR_CAPABILITY.
  */
#define LL_I3C_GET_CR_CAPABLE(__BCR__) (((((__BCR__) & I3C_BCR_BCR6_Msk) >> I3C_BCR_BCR6_POS) == 1U) \
                                        ? LL_I3C_CR_CAPABILITY : LL_I3C_CR_NO_CAPABILITY)

/**
  * @brief  Write a value in I3C register
  * @param  __INSTANCE__ I3C Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_I3C_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in I3C register
  * @param  __INSTANCE__ I3C Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_I3C_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup I3C_LL_Exported_Functions I3C Exported Functions
  * @{
  */

/** @defgroup I3C_LL_EF_Configuration Configuration
  * @{
  */

/**
  * @brief  Enable I3C peripheral (EN = 1).
  * @rmtoll CFGR      EN            LL_I3C_Enable
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_Enable(I3C_TypeDef *I3Cx)
{
  SET_BIT(I3Cx->CFGR, I3C_CFGR_EN);
}

/**
  * @brief  Disable I3C peripheral (EN = 0).
  * @note   Controller mode: before clearing EN, all possible target requests must be disabled using DISEC CCC.
  *         Target mode: software is not expected clearing EN unless a partial reset of the IP is needed
  * @rmtoll CFGR      EN            LL_I3C_Disable
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_Disable(I3C_TypeDef *I3Cx)
{
  CLEAR_BIT(I3Cx->CFGR, I3C_CFGR_EN);
}

/**
  * @brief  Check if the I3C peripheral is enabled or disabled.
  * @rmtoll CFGR      EN            LL_I3C_IsEnabled
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsEnabled(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->CFGR, I3C_CFGR_EN) == (I3C_CFGR_EN)) ? 1UL : 0UL);
}

/**
  * @brief  An arbitration header (7'h7E) is sent after Start in case of legacy I2C or I3C private transfers.
  * @note   This bit can be modified only when there is no frame ongoing
  * @rmtoll CFGR      NOARBH        LL_I3C_EnableArbitrationHeader
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_EnableArbitrationHeader(I3C_TypeDef *I3Cx)
{
  CLEAR_BIT(I3Cx->CFGR, I3C_CFGR_NOARBH);
}

/**
  * @brief  Target address is sent directly after a Start in case of legacy I2C or I3C private transfers.
  * @note   This bit can be modified only when there is no frame ongoing
  * @rmtoll CFGR      NOARBH        LL_I3C_DisableArbitrationHeader
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_DisableArbitrationHeader(I3C_TypeDef *I3Cx)
{
  SET_BIT(I3Cx->CFGR, I3C_CFGR_NOARBH);
}

/**
  * @brief  Check if the arbitration header is enabled of disabled.
  * @rmtoll CFGR      NOARBH        LL_I3C_IsEnabledArbitrationHeader
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsEnabledArbitrationHeader(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->CFGR, I3C_CFGR_NOARBH) == (I3C_CFGR_NOARBH)) ? 0UL : 1UL);
}

/**
  * @brief  A Reset Pattern is inserted before the STOP at the end of a frame when the last CCC
  *         of the frame was RSTACT CCC.
  * @note   This bit can be modified only when there is no frame ongoing
  * @rmtoll CFGR      RSTPTRN       LL_I3C_EnableResetPattern
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_EnableResetPattern(I3C_TypeDef *I3Cx)
{
  SET_BIT(I3Cx->CFGR, I3C_CFGR_RSTPTRN);
}

/**
  * @brief  A single STOP is emitted at the end of a frame.
  * @note   This bit can be modified only when there is no frame ongoing
  * @rmtoll CFGR      RSTPTRN       LL_I3C_DisableResetPattern
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_DisableResetPattern(I3C_TypeDef *I3Cx)
{
  CLEAR_BIT(I3Cx->CFGR, I3C_CFGR_RSTPTRN);
}

/**
  * @brief  Check if Reset Pattern is enabled of disabled.
  * @rmtoll CFGR      RSTPTRN       LL_I3C_IsEnabledResetPattern
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsEnabledResetPattern(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->CFGR, I3C_CFGR_RSTPTRN) == (I3C_CFGR_RSTPTRN)) ? 1UL : 0UL);
}

/**
  * @brief  An Exit Pattern is sent after header (MTYPE = header) to program an escalation fault.
  * @note   This bit can be modified only when there is no frame ongoing
  * @rmtoll CFGR      EXITPTRN      LL_I3C_EnableExitPattern
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_EnableExitPattern(I3C_TypeDef *I3Cx)
{
  SET_BIT(I3Cx->CFGR, I3C_CFGR_EXITPTRN);
}

/**
  * @brief  An Exit Pattern is not sent after header (MTYPE = header).
  * @note   This bit can be modified only when there is no frame ongoing
  * @rmtoll CFGR      EXITPTRN      LL_I3C_DisableExitPattern
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_DisableExitPattern(I3C_TypeDef *I3Cx)
{
  CLEAR_BIT(I3Cx->CFGR, I3C_CFGR_EXITPTRN);
}

/**
  * @brief  Check if Exit Pattern is enabled or disabled.
  * @rmtoll CFGR      EXITPTRN      LL_I3C_IsEnabledExitPattern
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsEnabledExitPattern(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->CFGR, I3C_CFGR_EXITPTRN) == (I3C_CFGR_EXITPTRN)) ? 1UL : 0UL);
}

/**
  * @brief  High Keeper is enabled and will be used in place of standard Open drain Pull Up device
  *         during handoff procedures.
  * @note   This bit can only be programmed when the I3C is disabled (EN = 0).
  * @rmtoll CFGR      HKSDAEN       LL_I3C_EnableHighKeeperSDA
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_EnableHighKeeperSDA(I3C_TypeDef *I3Cx)
{
  SET_BIT(I3Cx->CFGR, I3C_CFGR_HKSDAEN);
}

/**
  * @brief  High Keeper is disabled.
  * @note   This bit can only be programmed when the I3C is disabled (EN = 0).
  * @rmtoll CFGR      HKSDAEN       LL_I3C_DisableHighKeeperSDA
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_DisableHighKeeperSDA(I3C_TypeDef *I3Cx)
{
  CLEAR_BIT(I3Cx->CFGR, I3C_CFGR_HKSDAEN);
}

/**
  * @brief  Check if High Keeper is enabled or disabled.
  * @rmtoll CFGR      HKSDAEN       LL_I3C_IsEnabledHighKeeperSDA
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsEnabledHighKeeperSDA(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->CFGR, I3C_CFGR_HKSDAEN) == (I3C_CFGR_HKSDAEN)) ? 1UL : 0UL);
}

/**
  * @brief  Hot Join Request is Acked. Current frame on the bus is continued.
  *         An Hot Join interrupt is sent through HJF flag.
  * @note   This bit can be used when I3C is acting as a Controller.
  * @rmtoll CFGR      HJACK         LL_I3C_EnableHJAck
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_EnableHJAck(I3C_TypeDef *I3Cx)
{
  SET_BIT(I3Cx->CFGR, I3C_CFGR_HJACK);
}

/**
  * @brief  Hot Join Request is Nacked. Current frame on the bus is continued.
  *         No Hot Join interrupt is generated.
  * @note   This bit can be used when I3C is acting as a Controller.
  * @rmtoll CFGR      HJACK         LL_I3C_DisableHJAck
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_DisableHJAck(I3C_TypeDef *I3Cx)
{
  CLEAR_BIT(I3Cx->CFGR, I3C_CFGR_HJACK);
}

/**
  * @brief  Check if Hot Join Request Acknowledgement is enabled or disabled.
  * @rmtoll CFGR      HJACK         LL_I3C_IsEnabledHJAck
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsEnabledHJAck(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->CFGR, I3C_CFGR_HJACK) == (I3C_CFGR_HJACK)) ? 1UL : 0UL);
}

/**
  * @brief  Enable DMA FIFO reception requests.
  * @rmtoll CFGR      RXDMAEN       LL_I3C_EnableDMAReq_RX
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_EnableDMAReq_RX(I3C_TypeDef *I3Cx)
{
  SET_BIT(I3Cx->CFGR, I3C_CFGR_RXDMAEN);
}

/**
  * @brief  Disable DMA FIFO reception requests.
  * @rmtoll CFGR      RXDMAEN       LL_I3C_DisableDMAReq_RX
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_DisableDMAReq_RX(I3C_TypeDef *I3Cx)
{
  CLEAR_BIT(I3Cx->CFGR, I3C_CFGR_RXDMAEN);
}

/**
  * @brief  Check if DMA FIFO reception requests are enabled or disabled.
  * @rmtoll CFGR      RXDMAEN       LL_I3C_IsEnabledDMAReq_RX
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsEnabledDMAReq_RX(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->CFGR, I3C_CFGR_RXDMAEN) == (I3C_CFGR_RXDMAEN)) ? 1UL : 0UL);
}

/**
  * @brief  Set the Receive FIFO Threshold level.
  * @rmtoll CFGR      RXTHRES       LL_I3C_SetRxFIFOThreshold
  * @param  I3Cx I3C Instance.
  * @param  RxFIFOThreshold This parameter can be one of the following values:
  *         @arg @ref LL_I3C_RXFIFO_THRESHOLD_1_4
  *         @arg @ref LL_I3C_RXFIFO_THRESHOLD_4_4
  * @retval None
  */
static inline void LL_I3C_SetRxFIFOThreshold(I3C_TypeDef *I3Cx, uint32_t RxFIFOThreshold)
{
  MODIFY_REG(I3Cx->CFGR, I3C_CFGR_RXTHRES, RxFIFOThreshold);
}

/**
  * @brief  Get the Receive FIFO Threshold level.
  * @rmtoll CFGR      RXTHRES       LL_I3C_GetRxFIFOThreshold
  * @param  I3Cx I3C Instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_I3C_RXFIFO_THRESHOLD_1_4
  *         @arg @ref LL_I3C_RXFIFO_THRESHOLD_4_4
  */
static inline uint32_t LL_I3C_GetRxFIFOThreshold(const I3C_TypeDef *I3Cx)
{
  return (uint32_t)(READ_BIT(I3Cx->CFGR, I3C_CFGR_RXTHRES));
}

/**
  * @brief  Enable DMA FIFO transmission requests.
  * @rmtoll CFGR      TXDMAEN       LL_I3C_EnableDMAReq_TX
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_EnableDMAReq_TX(I3C_TypeDef *I3Cx)
{
  SET_BIT(I3Cx->CFGR, I3C_CFGR_TXDMAEN);
}

/**
  * @brief  Disable DMA FIFO transmission requests.
  * @rmtoll CFGR      TXDMAEN       LL_I3C_DisableDMAReq_TX
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_DisableDMAReq_TX(I3C_TypeDef *I3Cx)
{
  CLEAR_BIT(I3Cx->CFGR, I3C_CFGR_TXDMAEN);
}

/**
  * @brief  Check if DMA FIFO transmission requests are enabled or disabled.
  * @rmtoll CFGR      TXDMAEN       LL_I3C_IsEnabledDMAReq_TX
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsEnabledDMAReq_TX(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->CFGR, I3C_CFGR_TXDMAEN) == (I3C_CFGR_TXDMAEN)) ? 1UL : 0UL);
}

/**
  * @brief  Set the Transmit FIFO Threshold level.
  * @rmtoll CFGR      TXTHRES       LL_I3C_SetTxFIFOThreshold
  * @param  I3Cx I3C Instance.
  * @param  TxFIFOThreshold This parameter can be one of the following values:
  *         @arg @ref LL_I3C_TXFIFO_THRESHOLD_1_4
  *         @arg @ref LL_I3C_TXFIFO_THRESHOLD_4_4
  * @retval None
  */
static inline void LL_I3C_SetTxFIFOThreshold(I3C_TypeDef *I3Cx, uint32_t TxFIFOThreshold)
{
  MODIFY_REG(I3Cx->CFGR, I3C_CFGR_TXTHRES, TxFIFOThreshold);
}

/**
  * @brief  Get the Transmit FIFO Threshold level.
  * @rmtoll CFGR      TXTHRES       LL_I3C_GetTxFIFOThreshold
  * @param  I3Cx I3C Instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_I3C_TXFIFO_THRESHOLD_1_4
  *         @arg @ref LL_I3C_TXFIFO_THRESHOLD_4_4
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_GetTxFIFOThreshold(const I3C_TypeDef *I3Cx)
{
  return (uint32_t)(READ_BIT(I3Cx->CFGR, I3C_CFGR_TXTHRES));
}

/**
  * @brief  Enable the Status FIFO.
  * @note   Not applicable in target mode. Status FIFO always disabled in target mode.
  * @rmtoll CFGR      SMODE         LL_I3C_EnableStatusFIFO
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_EnableStatusFIFO(I3C_TypeDef *I3Cx)
{
  SET_BIT(I3Cx->CFGR, I3C_CFGR_SMODE);
}

/**
  * @brief  Disable the Status FIFO Threshold.
  * @rmtoll CFGR      SMODE         LL_I3C_DisableStatusFIFO
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_DisableStatusFIFO(I3C_TypeDef *I3Cx)
{
  CLEAR_BIT(I3Cx->CFGR, I3C_CFGR_SMODE);
}

/**
  * @brief  Check if the Status FIFO Threshold is enabled or disabled.
  * @rmtoll CFGR      SMODE         LL_I3C_IsEnabledStatusFIFO
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsEnabledStatusFIFO(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->CFGR, I3C_CFGR_SMODE) == (I3C_CFGR_SMODE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable DMA FIFO Control word transfer requests.
  * @rmtoll CFGR      CDMAEN        LL_I3C_EnableDMAReq_Control
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_EnableDMAReq_Control(I3C_TypeDef *I3Cx)
{
  SET_BIT(I3Cx->CFGR, I3C_CFGR_CDMAEN);
}

/**
  * @brief  Disable DMA FIFO Control word transfer requests.
  * @rmtoll CFGR      CDMAEN        LL_I3C_DisableDMAReq_Control
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_DisableDMAReq_Control(I3C_TypeDef *I3Cx)
{
  CLEAR_BIT(I3Cx->CFGR, I3C_CFGR_CDMAEN);
}

/**
  * @brief  Check if DMA FIFO Control word transfer requests are enabled or disabled.
  * @rmtoll CFGR      CDMAEN        LL_I3C_IsEnabledDMAReq_Control
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsEnabledDMAReq_Control(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->CFGR, I3C_CFGR_CDMAEN) == (I3C_CFGR_CDMAEN)) ? 1UL : 0UL);
}

/**
  * @brief  Configure the SCL clock signal waveform.
  * @note   This bit can only be programmed when the I3C is disabled (EN = 0).
  * @rmtoll TIMINGR0     TIMINGR0      LL_I3C_ConfigClockWaveForm
  * @param  I3Cx I3C Instance.
  * @param  ClockWaveForm This parameter must be a value between Min_Data=0 and Max_Data=0xFFFFFFFF.
  * @retval None
  */
static inline void LL_I3C_ConfigClockWaveForm(I3C_TypeDef *I3Cx, uint32_t ClockWaveForm)
{
  WRITE_REG(I3Cx->TIMINGR0, ClockWaveForm);
}

/**
  * @brief  Get the SCL clock signal waveform.
  * @rmtoll TIMINGR0     TIMINGR0      LL_I3C_GetClockWaveForm
  * @param  I3Cx I3C Instance.
  * @retval Value between Min_Data=0 and Max_Data=0xFFFFFFFF.
  */
static inline uint32_t LL_I3C_GetClockWaveForm(const I3C_TypeDef *I3Cx)
{
  return (uint32_t)(READ_REG(I3Cx->TIMINGR0));
}

/**
  * @brief  Configure the SCL clock low period during I3C push-pull phases.
  * @note   This bit can only be programmed when the I3C is disabled (EN = 0).
  *
  * @rmtoll TIMINGR0     SCLL_PP       LL_I3C_SetPeriodClockLowPP
  * @param  I3Cx I3C Instance.
  * @param  PeriodClockLowPP This parameter must be a value between Min_Data=0 and Max_Data=0xFF.
  * @retval None
  */
static inline void LL_I3C_SetPeriodClockLowPP(I3C_TypeDef *I3Cx, uint32_t PeriodClockLowPP)
{
  MODIFY_REG(I3Cx->TIMINGR0, I3C_TIMINGR0_SCLL_PP, (PeriodClockLowPP << I3C_TIMINGR0_SCLL_PP_POS));
}

/**
  * @brief  Get the SCL clock low period during I3C push-pull phases.
  * @rmtoll TIMINGR0     SCLL_PP       LL_I3C_GetPeriodClockLowPP
  * @param  I3Cx I3C Instance.
  * @retval Value between Min_Data=0 and Max_Data=0xFF.
  */
static inline uint32_t LL_I3C_GetPeriodClockLowPP(const I3C_TypeDef *I3Cx)
{
  return (uint32_t)(READ_BIT(I3Cx->TIMINGR0, I3C_TIMINGR0_SCLL_PP) >> I3C_TIMINGR0_SCLL_PP_POS);
}

/**
  * @brief  Configure the SCL clock High period during I3C open drain and push-pull phases.
  * @note   This bit can only be programmed when the I3C is disabled (EN = 0).
  *
  * @rmtoll TIMINGR0     SCLH_I3C      LL_I3C_SetPeriodClockHighI3C
  * @param  I3Cx I3C Instance.
  * @param  PeriodClockHighI3C This parameter must be a value between Min_Data=0 and Max_Data=0xFF.
  * @retval None
  */
static inline void LL_I3C_SetPeriodClockHighI3C(I3C_TypeDef *I3Cx, uint32_t PeriodClockHighI3C)
{
  MODIFY_REG(I3Cx->TIMINGR0, I3C_TIMINGR0_SCLH_I3C, (PeriodClockHighI3C << I3C_TIMINGR0_SCLH_I3C_POS));
}

/**
  * @brief  Get the SCL clock high period during I3C open drain and push-pull phases.
  * @rmtoll TIMINGR0     SCLH_I3C      LL_I3C_GetPeriodClockHighI3C
  * @param  I3Cx I3C Instance.
  * @retval Value between Min_Data=0 and Max_Data=0xFF.
  */
static inline uint32_t LL_I3C_GetPeriodClockHighI3C(const I3C_TypeDef *I3Cx)
{
  return (uint32_t)(READ_BIT(I3Cx->TIMINGR0, I3C_TIMINGR0_SCLH_I3C) >> I3C_TIMINGR0_SCLH_I3C_POS);
}

/**
  * @brief  Configure the SCL clock low period during I3C open drain phases.
  * @note   This bit can only be programmed when the I3C is disabled (EN = 0).
  *
  * @rmtoll TIMINGR0     SCLL_OD       LL_I3C_SetPeriodClockLowOD
  * @param  I3Cx I3C Instance.
  * @param  PeriodClockLowOD This parameter must be a value between Min_Data=0 and Max_Data=0xFF.
  * @retval None
  */
static inline void LL_I3C_SetPeriodClockLowOD(I3C_TypeDef *I3Cx, uint32_t PeriodClockLowOD)
{
  MODIFY_REG(I3Cx->TIMINGR0, I3C_TIMINGR0_SCLL_OD, (PeriodClockLowOD << I3C_TIMINGR0_SCLL_OD_POS));
}

/**
  * @brief  Get the SCL clock low period during I3C open phases.
  * @rmtoll TIMINGR0     SCLL_OD       LL_I3C_GetPeriodClockLowOD
  * @param  I3Cx I3C Instance.
  * @retval Value between Min_Data=0 and Max_Data=0xFF.
  */
static inline uint32_t LL_I3C_GetPeriodClockLowOD(const I3C_TypeDef *I3Cx)
{
  return (uint32_t)(READ_BIT(I3Cx->TIMINGR0, I3C_TIMINGR0_SCLL_OD) >> I3C_TIMINGR0_SCLL_OD_POS);
}

/**
  * @brief  Configure the SCL clock High period during I2C open drain phases.
  * @note   This bit can only be programmed when the I3C is disabled (EN = 0).
  *
  * @rmtoll TIMINGR0     SCLH_I2C      LL_I3C_SetPeriodClockHighI2C
  * @param  I3Cx I3C Instance.
  * @param  PeriodClockHighI2C This parameter must be a value between Min_Data=0 and Max_Data=0xFF.
  * @retval None
  */
static inline void LL_I3C_SetPeriodClockHighI2C(I3C_TypeDef *I3Cx, uint32_t PeriodClockHighI2C)
{
  MODIFY_REG(I3Cx->TIMINGR0, I3C_TIMINGR0_SCLH_I2C, PeriodClockHighI2C << I3C_TIMINGR0_SCLH_I2C_POS);
}

/**
  * @brief  Get the SCL clock high period during I2C open drain phases.
  * @rmtoll TIMINGR0     SCLH_I2C      LL_I3C_GetPeriodClockHighI2C
  * @param  I3Cx I3C Instance.
  * @retval Value between Min_Data=0 and Max_Data=0xFF.
  */
static inline uint32_t LL_I3C_GetPeriodClockHighI2C(const I3C_TypeDef *I3Cx)
{
  return (uint32_t)(READ_BIT(I3Cx->TIMINGR0, I3C_TIMINGR0_SCLH_I2C) >> I3C_TIMINGR0_SCLH_I2C_POS);
}

/**
  * @brief  Configure the Controller additional hold time on SDA line.
  * @rmtoll TIMINGR1     SDA_HD        LL_I3C_SetDataHoldTime
  * @param  I3Cx I3C Instance.
  * @param  DataHoldTime This parameter can be one of the following values:
  *         @arg @ref LL_I3C_SDA_HOLD_TIME_0_5
  *         @arg @ref LL_I3C_SDA_HOLD_TIME_1_5
  * @retval None
  */
static inline void LL_I3C_SetDataHoldTime(I3C_TypeDef *I3Cx, uint32_t DataHoldTime)
{
  MODIFY_REG(I3Cx->TIMINGR1, I3C_TIMINGR1_SDA_HD, DataHoldTime);
}

/**
  * @brief  Get the Controller additional hold time on SDA line.
  * @rmtoll TIMINGR1     SDA_HD        LL_I3C_GetDataHoldTime
  * @param  I3Cx I3C Instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_I3C_SDA_HOLD_TIME_0_5
  *         @arg @ref LL_I3C_SDA_HOLD_TIME_1_5
  */
static inline uint32_t LL_I3C_GetDataHoldTime(const I3C_TypeDef *I3Cx)
{
  return (uint32_t)(READ_BIT(I3Cx->TIMINGR1, I3C_TIMINGR1_SDA_HD));
}

/**
  * @brief  Configure the Idle, Available state.
  * @note   This bit can only be programmed when the I3C is disabled (EN = 0).
  *
  * @rmtoll TIMINGR1     AVAL          LL_I3C_SetAvalTiming
  * @param  I3Cx I3C Instance.
  * @param  AvalTiming This parameter must be a value between Min_Data=0 and Max_Data=0xFF.
  * @retval None
  */
static inline void LL_I3C_SetAvalTiming(I3C_TypeDef *I3Cx, uint32_t AvalTiming)
{
  MODIFY_REG(I3Cx->TIMINGR1, I3C_TIMINGR1_AVAL, (AvalTiming << I3C_TIMINGR1_AVAL_POS));
}

/**
  * @brief  Get the Idle, Available integer value state.
  * @rmtoll TIMINGR1     AVAL          LL_I3C_GetAvalTiming
  * @param  I3Cx I3C Instance.
  * @retval Value between Min_Data=0 and Max_Data=0xFF.
  */
static inline uint32_t LL_I3C_GetAvalTiming(const I3C_TypeDef *I3Cx)
{
  return (uint32_t)(READ_BIT(I3Cx->TIMINGR1, I3C_TIMINGR1_AVAL) >> I3C_TIMINGR1_AVAL_POS);
}

/**
  * @brief  Configure the Free state.
  * @note   This bit can only be programmed when the I3C is disabled (EN = 0).
  *
  * @rmtoll TIMINGR1     FREE          LL_I3C_SetFreeTiming
  * @param  I3Cx I3C Instance.
  * @param  FreeTiming This parameter must be a value between Min_Data=0 and Max_Data=0x3F.
  * @retval None
  */
static inline void LL_I3C_SetFreeTiming(I3C_TypeDef *I3Cx, uint32_t FreeTiming)
{
  MODIFY_REG(I3Cx->TIMINGR1, I3C_TIMINGR1_FREE, (FreeTiming << I3C_TIMINGR1_FREE_POS));
}

/**
  * @brief  Get the Free integeter value state.
  * @rmtoll TIMINGR1     FREE          LL_I3C_GetFreeTiming
  * @param  I3Cx I3C Instance.
  * @retval Value between Min_Data=0 and Max_Data=0x3F.
  */
static inline uint32_t LL_I3C_GetFreeTiming(const I3C_TypeDef *I3Cx)
{
  return (uint32_t)(READ_BIT(I3Cx->TIMINGR1, I3C_TIMINGR1_FREE) >> I3C_TIMINGR1_FREE_POS);
}

/**
  * @brief  Configure the activity state of the new controller.
  * @note   Refer to MIPI I3C specification (https:__www.mipi.org_specifications)
  *         for more details related to Activity State.
  * @rmtoll TIMINGR1     ASNCR            LL_I3C_SetControllerActivityState
  * @param  I3Cx I3C Instance.
  * @param  ControllerActivityState This parameter can be one of the following values:
  *         @arg @ref LL_I3C_OWN_ACTIVITY_STATE_0
  *         @arg @ref LL_I3C_OWN_ACTIVITY_STATE_1
  *         @arg @ref LL_I3C_OWN_ACTIVITY_STATE_2
  *         @arg @ref LL_I3C_OWN_ACTIVITY_STATE_3
  * @retval None
  */
static inline void LL_I3C_SetControllerActivityState(I3C_TypeDef *I3Cx, uint32_t ControllerActivityState)
{
  MODIFY_REG(I3Cx->TIMINGR1, I3C_TIMINGR1_ASNCR, ControllerActivityState);
}

/**
  * @brief  Get the activity state of the new controller.
  * @note   Refer to MIPI I3C specification (https:__www.mipi.org_specifications)
  *         for more details related to Activity State.
  * @rmtoll TIMINGR1     ASNCR            LL_I3C_GetControllerActivityState
  * @param  I3Cx I3C Instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_I3C_OWN_ACTIVITY_STATE_0
  *         @arg @ref LL_I3C_OWN_ACTIVITY_STATE_1
  *         @arg @ref LL_I3C_OWN_ACTIVITY_STATE_2
  *         @arg @ref LL_I3C_OWN_ACTIVITY_STATE_3
  */
static inline uint32_t LL_I3C_GetControllerActivityState(const I3C_TypeDef *I3Cx)
{
  return (uint32_t)(READ_BIT(I3Cx->TIMINGR1, I3C_TIMINGR1_ASNCR));
}

/**
  * @brief  Configure the Controller SDA Hold time, Bus Free, Activity state, Idle state.
  * @note   This bit can only be programmed when the I3C is disabled (EN = 0).
  *
  * @rmtoll TIMINGR1     SDA_HD        LL_I3C_SetCtrlBusCharacteristic\n
  *         TIMINGR1     FREE          LL_I3C_SetCtrlBusCharacteristic\n
  *         TIMINGR1     ASNCR         LL_I3C_SetCtrlBusCharacteristic\n
  *         TIMINGR1     IDLE          LL_I3C_SetCtrlBusCharacteristic
  * @param  I3Cx I3C Instance.
  * @param  CtrlBusCharacteristic This parameter must be a value between Min_Data=0 and Max_Data=0x107F03FF.
  * @retval None
  */
static inline void LL_I3C_SetCtrlBusCharacteristic(I3C_TypeDef *I3Cx, uint32_t CtrlBusCharacteristic)
{
  WRITE_REG(I3Cx->TIMINGR1, CtrlBusCharacteristic);
}

/**
  * @brief  Get the Controller SDA Hold time, Bus Free, Activity state, Idle state.
  * @rmtoll TIMINGR1     SDA_HD        LL_I3C_GetCtrlBusCharacteristic\n
  *         TIMINGR1     FREE          LL_I3C_GetCtrlBusCharacteristic\n
  *         TIMINGR1     ASNCR         LL_I3C_GetCtrlBusCharacteristic\n
  *         TIMINGR1     IDLE          LL_I3C_GetCtrlBusCharacteristic
  * @param  I3Cx I3C Instance.
  * @retval Value between Min_Data=0 and Max_Data=0x107F03FF.
  */
static inline uint32_t LL_I3C_GetCtrlBusCharacteristic(const I3C_TypeDef *I3Cx)
{
  return (uint32_t)(READ_REG(I3Cx->TIMINGR1));
}

/**
  * @brief  Configure the Target Available state.
  * @note   This bit can only be programmed when the I3C is disabled (EN = 0).
  *
  * @rmtoll TIMINGR1     IDLE          LL_I3C_SetTgtBusCharacteristic
  * @param  I3Cx I3C Instance.
  * @param  TgtBusCharacteristic This parameter must be a value between Min_Data=0 and Max_Data=0xFF.
  * @retval None
  */
static inline void LL_I3C_SetTgtBusCharacteristic(I3C_TypeDef *I3Cx, uint32_t TgtBusCharacteristic)
{
  MODIFY_REG(I3Cx->TIMINGR1, I3C_TIMINGR1_AVAL, (TgtBusCharacteristic & I3C_TIMINGR1_AVAL));
}

/**
  * @brief  Get the Target Available state.
  * @rmtoll TIMINGR1     IDLE          LL_I3C_GetTgtBusCharacteristic
  * @param  I3Cx I3C Instance.
  * @retval Value between Min_Data=0 and Max_Data=0xFF.
  */
static inline uint32_t LL_I3C_GetTgtBusCharacteristic(const I3C_TypeDef *I3Cx)
{
  return (uint32_t)(READ_BIT(I3Cx->TIMINGR1, I3C_TIMINGR1_AVAL));
}

/**
  * @brief  Configure the SCL clock stalling time on I3C Bus (controller mode).
  * @note   This bit can only be programmed when the I3C is disabled (EN = 0).
  *
  * @rmtoll TIMINGR2     STALL        LL_I3C_SetStallTime
  * @param  I3Cx I3C Instance.
  * @param  ControllerStallTime This parameter must be a value between Min_Data=0 and Max_Data=0xFF.
  * @retval None
  */
static inline void LL_I3C_SetStallTime(I3C_TypeDef *I3Cx, uint32_t ControllerStallTime)
{
  MODIFY_REG(I3Cx->TIMINGR2, I3C_TIMINGR2_STALL, (ControllerStallTime << I3C_TIMINGR2_STALL_POS));
}

/**
  * @brief  Get the SCL clock stalling time on I3C Bus (controller mode).
  * @rmtoll TIMINGR2     STALL        LL_I3C_GetStallTime
  * @param  I3Cx I3C Instance.
  * @retval Value between Min_Data=0 and Max_Data=0xFF.
  */
static inline uint32_t LL_I3C_GetStallTime(const I3C_TypeDef *I3Cx)
{
  return (uint32_t)(READ_BIT(I3Cx->TIMINGR2, I3C_TIMINGR2_STALL));
}

/**
  * @brief  Set stall on ACK bit (controller mode).
  * @note   This bit can be programmed when the I3C is disabled (EN = 0).
  * @rmtoll TIMINGR2     STALLA       LL_I3C_EnableStallACK
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_EnableStallACK(I3C_TypeDef *I3Cx)
{
  SET_BIT(I3Cx->TIMINGR2, I3C_TIMINGR2_STALLA);
}

/**
  * @brief  Disable stall on ACK bit (controller mode).
  * @note   This bit can be programmed when the I3C is disabled (EN = 0).
  * @rmtoll TIMINGR2     STALLA       LL_I3C_DisableStallACK
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_DisableStallACK(I3C_TypeDef *I3Cx)
{
  CLEAR_BIT(I3Cx->TIMINGR2, I3C_TIMINGR2_STALLA);
}

/**
  * @brief  Check if stall on ACK bit is enabled or disabled (controller mode).
  * @rmtoll TIMINGR2     STALLA       LL_I3C_IsEnabledStallACK
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsEnabledStallACK(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->TIMINGR2, I3C_TIMINGR2_STALLA) == (I3C_TIMINGR2_STALLA)) ? 1UL : 0UL);
}

/**
  * @brief  Set stall on Parity bit of Command Code byte (controller mode).
  * @note   This bit can be programmed when the I3C is disabled (EN = 0).
  * @rmtoll TIMINGR2     STALLC       LL_I3C_EnableStallParityCCC
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_EnableStallParityCCC(I3C_TypeDef *I3Cx)
{
  SET_BIT(I3Cx->TIMINGR2, I3C_TIMINGR2_STALLC);
}

/**
  * @brief  Disable stall on Parity bit of Command Code byte (controller mode).
  * @note   This bit can be programmed when the I3C is disabled (EN = 0).
  * @rmtoll TIMINGR2     STALLC       LL_I3C_DisableStallParityCCC
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_DisableStallParityCCC(I3C_TypeDef *I3Cx)
{
  CLEAR_BIT(I3Cx->TIMINGR2, I3C_TIMINGR2_STALLC);
}

/**
  * @brief  Check if stall on Parity bit of Command Code byte is enabled or disabled (controller mode).
  * @rmtoll TIMINGR2     STALLC       LL_I3C_IsEnabledStallParityCCC
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsEnabledStallParityCCC(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->TIMINGR2, I3C_TIMINGR2_STALLC) == (I3C_TIMINGR2_STALLC)) ? 1UL : 0UL);
}

/**
  * @brief  Set stall on Parity bit of Data bytes (controller mode).
  * @note   This bit can be programmed when the I3C is disabled (EN = 0).
  * @rmtoll TIMINGR2     STALLD       LL_I3C_EnableStallParityData
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_EnableStallParityData(I3C_TypeDef *I3Cx)
{
  SET_BIT(I3Cx->TIMINGR2, I3C_TIMINGR2_STALLD);
}

/**
  * @brief  Disable stall on Parity bit of Data bytes (controller mode).
  * @note   This bit can be programmed when the I3C is disabled (EN = 0).
  * @rmtoll TIMINGR2     STALLD       LL_I3C_DisableStallParityData
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_DisableStallParityData(I3C_TypeDef *I3Cx)
{
  CLEAR_BIT(I3Cx->TIMINGR2, I3C_TIMINGR2_STALLD);
}

/**
  * @brief  Check if stall on Parity bit of Data bytes is enabled or disabled (controller mode).
  * @rmtoll TIMINGR2     STALLD       LL_I3C_IsEnabledStallParityData
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsEnabledStallParityData(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->TIMINGR2, I3C_TIMINGR2_STALLD) == (I3C_TIMINGR2_STALLD)) ? 1UL : 0UL);
}

/**
  * @brief  Set stall on T bit (controller mode).
  * @note   This bit can be programmed when the I3C is disabled (EN = 0).
  * @rmtoll TIMINGR2     STALLT       LL_I3C_EnableStallTbit
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_EnableStallTbit(I3C_TypeDef *I3Cx)
{
  SET_BIT(I3Cx->TIMINGR2, I3C_TIMINGR2_STALLT);
}

/**
  * @brief  Disable stall on T bit (controller mode).
  * @note   This bit can be programmed when the I3C is disabled (EN = 0).
  * @rmtoll TIMINGR2     STALLT       LL_I3C_DisableStallTbit
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_DisableStallTbit(I3C_TypeDef *I3Cx)
{
  CLEAR_BIT(I3Cx->TIMINGR2, I3C_TIMINGR2_STALLT);
}

/**
  * @brief  Check if stall on T bit is enabled or disabled (controller mode).
  * @rmtoll TIMINGR2     STALLT       LL_I3C_IsEnabledStallTbit
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsEnabledStallTbit(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->TIMINGR2, I3C_TIMINGR2_STALLT) == (I3C_TIMINGR2_STALLT)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup I3C_LL_EF_Data Management
  * @{
  */

/**
  * @brief  Request a reception Data FIFO Flush.
  * @rmtoll CFGR      RXFLUSH       LL_I3C_RequestRxFIFOFlush
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_RequestRxFIFOFlush(I3C_TypeDef *I3Cx)
{
  SET_BIT(I3Cx->CFGR, I3C_CFGR_RXFLUSH);
}

/**
  * @brief  Request a transmission Data FIFO Flush.
  * @rmtoll CFGR      TXFLUSH       LL_I3C_RequestTxFIFOFlush
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_RequestTxFIFOFlush(I3C_TypeDef *I3Cx)
{
  SET_BIT(I3Cx->CFGR, I3C_CFGR_TXFLUSH);
}

/**
  * @brief  Request a Status Data FIFO Flush.
  * @rmtoll CFGR      SFLUSH        LL_I3C_RequestStatusFIFOFlush
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void  LL_I3C_RequestStatusFIFOFlush(I3C_TypeDef *I3Cx)
{
  SET_BIT(I3Cx->CFGR, I3C_CFGR_SFLUSH);
}

/**
  * @brief  Request a Control word FIFO Flush.
  * @rmtoll CFGR      CFLUSH        LL_I3C_RequestControlFIFOFlush
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_RequestControlFIFOFlush(I3C_TypeDef *I3Cx)
{
  SET_BIT(I3Cx->CFGR, I3C_CFGR_CFLUSH);
}

/**
  * @brief  Request a Transfer start.
  * @note   After request, the current instruction in Control Register is executed on I3C Bus.
  * @rmtoll CFGR      TSFSET        LL_I3C_RequestTransfer
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_RequestTransfer(I3C_TypeDef *I3Cx)
{
  SET_BIT(I3Cx->CFGR, I3C_CFGR_TSFSET);
}

/**
  * @brief  Handles I3C Message content on the I3C Bus as Controller.
  * @rmtoll CR           ADD           LL_I3C_ControllerHandleMessage\n
  *         CR           DCNT          LL_I3C_ControllerHandleMessage\n
  *         CR           RNW           LL_I3C_ControllerHandleMessage\n
  *         CR           MTYPE         LL_I3C_ControllerHandleMessage\n
  *         CR           MEND          LL_I3C_ControllerHandleMessage
  * @param  I3Cx I3C Instance.
  * @param  TargetAddr Specifies the target address to be programmed.
  *               This parameter must be a value between Min_Data=0 and Max_Data=0xFF.
  * @param  TransferSize Specifies the number of bytes to be programmed.
  *               This parameter must be a value between Min_Data=0 and Max_Data=65535.
  * @param  Direction This parameter can be one of the following values:
  *         @arg @ref LL_I3C_DIRECTION_WRITE
  *         @arg @ref LL_I3C_DIRECTION_READ
  * @param  MessageType This parameter can be one of the following values:
  *         @arg @ref LL_I3C_CONTROLLER_MTYPE_RELEASE
  *         @arg @ref LL_I3C_CONTROLLER_MTYPE_HEADER
  *         @arg @ref LL_I3C_CONTROLLER_MTYPE_PRIVATE
  *         @arg @ref LL_I3C_CONTROLLER_MTYPE_DIRECT
  *         @arg @ref LL_I3C_CONTROLLER_MTYPE_LEGACY_I2C
  * @param  EndMode This parameter can be one of the following values:
  *         @arg @ref LL_I3C_GENERATE_STOP
  *         @arg @ref LL_I3C_GENERATE_RESTART
  * @retval None
  */
static inline void LL_I3C_ControllerHandleMessage(I3C_TypeDef *I3Cx, uint32_t TargetAddr, uint32_t TransferSize,
                                                    uint32_t Direction, uint32_t MessageType, uint32_t EndMode)
{
  WRITE_REG(I3Cx->CR, ((TargetAddr << I3C_CR_ADD_POS) | TransferSize | Direction | MessageType | EndMode) \
            & (I3C_CR_ADD | I3C_CR_DCNT | I3C_CR_RNW | I3C_CR_MTYPE | I3C_CR_MEND));
}

/**
  * @brief  Handles I3C Common Command Code content on the I3C Bus as Controller.
  * @rmtoll CR           CCC           LL_I3C_ControllerHandleCCC\n
  *         CR           DCNT          LL_I3C_ControllerHandleCCC\n
  *         CR           MTYPE         LL_I3C_ControllerHandleCCC\n
  *         CR           MEND          LL_I3C_ControllerHandleCCC
  * @param  I3Cx I3C Instance.
  * @param  CCCValue Specifies the Command Code to be programmed.
  *               This parameter must be a value between Min_Data=0 and Max_Data=0x1FF.
  * @param  AddByteSize Specifies the number of CCC additional bytes to be programmed.
  *               This parameter must be a value between Min_Data=0 and Max_Data=65535.
  * @param  EndMode This parameter can be one of the following values:
  *         @arg @ref LL_I3C_GENERATE_STOP
  *         @arg @ref LL_I3C_GENERATE_RESTART
  * @retval None
  */
static inline void LL_I3C_ControllerHandleCCC(I3C_TypeDef *I3Cx, uint32_t CCCValue,
                                                uint32_t AddByteSize, uint32_t EndMode)
{
  WRITE_REG(I3Cx->CR, ((CCCValue << I3C_CR_CCC_POS) | AddByteSize | EndMode | LL_I3C_CONTROLLER_MTYPE_CCC) \
            & (I3C_CR_CCC | I3C_CR_DCNT | I3C_CR_MTYPE | I3C_CR_MEND));
}

/**
  * @}
  */

/** @defgroup I3C_LL_EF_Data_Management Data_Management
  * @{
  */

/**
  * @brief  Read Receive Data Byte register.
  * @rmtoll RDR          RDB0         LL_I3C_ReceiveData8
  * @param  I3Cx I3C Instance.
  * @retval Value between Min_Data=0 to Max_Data=0xFF
  */
static inline uint8_t LL_I3C_ReceiveData8(const I3C_TypeDef *I3Cx)
{
  return (uint8_t)(READ_BIT(I3Cx->RDR, I3C_RDR_RDB0));
}

/**
  * @brief  Write in Transmit Data Byte Register.
  * @rmtoll TDR          TDB0         LL_I3C_TransmitData8
  * @param  I3Cx I3C Instance.
  * @param  Data This parameter must be a value between Min_Data=0 and Max_Data=0xFF.
  * @retval None
  */
static inline void LL_I3C_TransmitData8(I3C_TypeDef *I3Cx, uint8_t Data)
{
  WRITE_REG(I3Cx->TDR, Data);
}

/**
  * @brief  Get the own IBI data payload (target mode), or get the Target IBI received (controller mode).
  * @note   Content of register is filled in Little Endian.
  *         Mean MSB correspond to last IBI data byte,
  *         LSB correspond to first IBI data byte.
  * @rmtoll IBIDR        IBIDR         LL_I3C_GetIBIPayload
  * @param  I3Cx I3C Instance.
  * @retval Value between Min_Data=0 to Max_Data=0xFFFFFFFF
  */
static inline uint32_t LL_I3C_GetIBIPayload(const I3C_TypeDef *I3Cx)
{
  return (uint32_t)(READ_REG(I3Cx->IBIDR));
}

/**
  * @brief  Get the number of data bytes received when reading IBI data (controller mode).
  * @rmtoll RMR         IBIRDCNT     LL_I3C_GetNbIBIAddData
  * @param  I3Cx I3C Instance.
  * @retval Value between Min_Data=0 to Max_Data=0x7
  */
static inline uint32_t LL_I3C_GetNbIBIAddData(const I3C_TypeDef *I3Cx)
{
  return (uint32_t)(READ_BIT(I3Cx->RMR, I3C_RMR_IBIRDCNT));
}

/**
  * @brief  Get the target address received during accepted IBI or Controller-role request.
  * @rmtoll RMR         RADD         LL_I3C_GetIBITargetAddr
  * @param  I3Cx I3C Instance.
  * @retval Value between Min_Data=0 to Max_Data=0x3F
  */
static inline uint32_t LL_I3C_GetIBITargetAddr(const I3C_TypeDef *I3Cx)
{
  return (uint32_t)(READ_BIT(I3Cx->RMR, I3C_RMR_RADD) >> I3C_RMR_RADD_POS);
}

/**
  * @brief  Get the number of data during a Transfer.
  * @note   The return value correspond to number of transmitted bytes reported
  *         during Address Assignment process in Target mode.
  * The return value  correspond to number of target detected
  * during Address Assignment process in Controller mode.
  * The return value  correspond to number of data bytes read from or sent to the I3C bus
  * during the message link to MID current value.
  * @rmtoll SR           XDCNT      LL_I3C_GetXferDataCount
  * @param  I3Cx I3C Instance.
  * @retval Value between Min_Data=0 to Max_Data=0xFFFF
  */
static inline uint32_t LL_I3C_GetXferDataCount(const I3C_TypeDef *I3Cx)
{
  return (uint32_t)(READ_BIT(I3Cx->SR, I3C_SR_XDCNT));
}

/**
  * @brief  Indicates if a Target abort a private read command.
  * @rmtoll SR           ABT           LL_I3C_IsTargetAbortPrivateRead
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsTargetAbortPrivateRead(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->SR, I3C_SR_ABT) == (I3C_SR_ABT)) ? 1UL : 0UL);
}

/**
  * @brief  Get Direction of the Message.
  * @rmtoll SR           DIR           LL_I3C_GetMessageDirection
  * @param  I3Cx I3C Instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_I3C_MESSAGE_DIRECTION_WRITE
  *         @arg @ref LL_I3C_MESSAGE_DIRECTION_READ
  */
static inline uint32_t LL_I3C_GetMessageDirection(const I3C_TypeDef *I3Cx)
{
  return (uint32_t)(READ_BIT(I3Cx->SR, I3C_SR_DIR));
}

/**
  * @brief  Get Message identifier.
  * @rmtoll SR           MID           LL_I3C_GetMessageIdentifier
  * @param  I3Cx I3C Instance.
  * @retval Value between Min_Data=0 to Max_Data=0xFF, representing the internal hardware counter value.
  */
static inline uint32_t LL_I3C_GetMessageIdentifier(const I3C_TypeDef *I3Cx)
{
  return (uint32_t)(READ_BIT(I3Cx->SR, I3C_SR_MID));
}

/**
  * @brief  Get Message error code.
  * @rmtoll SER          CODERR        LL_I3C_GetMessageErrorCode
  * @param  I3Cx I3C Instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_I3C_CONTROLLER_ERROR_CE0
  *         @arg @ref LL_I3C_CONTROLLER_ERROR_CE1
  *         @arg @ref LL_I3C_CONTROLLER_ERROR_CE2
  *         @arg @ref LL_I3C_CONTROLLER_ERROR_CE3
  *         @arg @ref LL_I3C_TARGET_ERROR_TE0
  *         @arg @ref LL_I3C_TARGET_ERROR_TE1
  *         @arg @ref LL_I3C_TARGET_ERROR_TE2
  *         @arg @ref LL_I3C_TARGET_ERROR_TE3
  *         @arg @ref LL_I3C_TARGET_ERROR_TE4
  *         @arg @ref LL_I3C_TARGET_ERROR_TE5
  *         @arg @ref LL_I3C_TARGET_ERROR_TE6
  */
static inline uint32_t LL_I3C_GetMessageErrorCode(const I3C_TypeDef *I3Cx)
{
  return (uint32_t)(READ_BIT(I3Cx->SER, I3C_SER_CODERR));
}

/**
  * @}
  */

/** @defgroup I3C_LL_EF_Target Payload
  * @{
  */

/**
  * @brief  Set Dynamic Address assigned to target x.
  * @rmtoll DEVRX        DA            LL_I3C_SetTargetDynamicAddress
  * @param  I3Cx I3C Instance.
  * @param  TargetId This parameter must be a value between Min_Data=1 and Max_Data=4
  * @param  DynamicAddr Value between Min_Data=0 to Max_Data=0x7F
  * @retval None
  */
static inline void LL_I3C_SetTargetDynamicAddress(I3C_TypeDef *I3Cx, uint32_t TargetId, uint32_t DynamicAddr)
{
  MODIFY_REG(I3Cx->DEVRX[TargetId - 1U], I3C_DEVRX_DA, (DynamicAddr << I3C_DEVRX_DA_POS));
}

/**
  * @brief  Get Dynamic Address assigned to target x.
  * @rmtoll DEVRX        DA            LL_I3C_GetTargetDynamicAddress
  * @param  I3Cx I3C Instance.
  * @param  TargetId This parameter must be a value between Min_Data=1 and Max_Data=4
  * @retval Value between Min_Data=0 to Max_Data=0x7F
  */
static inline uint32_t LL_I3C_GetTargetDynamicAddress(const I3C_TypeDef *I3Cx, uint32_t TargetId)
{
  return (uint32_t)((READ_BIT(I3Cx->DEVRX[TargetId - 1U], I3C_DEVRX_DA)) >> I3C_DEVRX_DA_POS);
}

/**
  * @brief  Enable IBI Acknowledgement from target x(controller mode).
  * @note   The bit DIS is automatically set when CRACK or IBIACK are set.
  *         This mean DEVRX register access is not allowed.
  *         Reset CRACK and IBIACK will reset DIS bit.
  * @rmtoll DEVRX        IBIACK        LL_I3C_EnableTargetIBIAck
  * @param  I3Cx I3C Instance.
  * @param  TargetId This parameter must be a value between Min_Data=1 and Max_Data=4
  * @retval None
  */
static inline void LL_I3C_EnableTargetIBIAck(I3C_TypeDef *I3Cx, uint32_t TargetId)
{
  SET_BIT(I3Cx->DEVRX[TargetId - 1U], I3C_DEVRX_IBIACK);
}

/**
  * @brief  Disable IBI Acknowledgement from target x (controller mode).
  * @rmtoll DEVRX        IBIACK        LL_I3C_DisableTargetIBIAck
  * @param  I3Cx I3C Instance.
  * @param  TargetId This parameter must be a value between Min_Data=1 and Max_Data=4
  * @retval None
  */
static inline void LL_I3C_DisableTargetIBIAck(I3C_TypeDef *I3Cx, uint32_t TargetId)
{
  CLEAR_BIT(I3Cx->DEVRX[TargetId - 1U], I3C_DEVRX_IBIACK);
}

/**
  * @brief  Indicates if IBI from target x will be Acknowledged or Not Acknowledged (controller mode).
  *         RESET: IBI Not Acknowledged.
  *         SET: IBI Acknowledged.
  * @rmtoll DEVRX        IBIACK        LL_I3C_IsEnabledTargetIBIAck
  * @param  I3Cx I3C Instance.
  * @param  TargetId This parameter must be a value between Min_Data=1 and Max_Data=4
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsEnabledTargetIBIAck(const I3C_TypeDef *I3Cx, uint32_t TargetId)
{
  return ((READ_BIT(I3Cx->DEVRX[TargetId - 1U], I3C_DEVRX_IBIACK) == I3C_DEVRX_IBIACK) ? 1UL : 0UL);
}

/**
  * @brief  Enable Controller-role Request Acknowledgement from target x(controller mode).
  * @note   The bit DIS is automatically set when CRACK or IBIACK are set.
  *         This mean DEVRX register access is not allowed.
  *         Reset CRACK and IBIACK will reset DIS bit.
  * @rmtoll DEVRX        CRACK         LL_I3C_EnableTargetCRAck
  * @param  I3Cx I3C Instance.
  * @param  TargetId This parameter must be a value between Min_Data=1 and Max_Data=4
  * @retval None
  */
static inline void LL_I3C_EnableTargetCRAck(I3C_TypeDef *I3Cx, uint32_t TargetId)
{
  SET_BIT(I3Cx->DEVRX[TargetId - 1U], I3C_DEVRX_CRACK);
}

/**
  * @brief  Disable Controller-role Request Acknowledgement from target x (controller mode).
  * @rmtoll DEVRX        CRACK         LL_I3C_DisableTargetCRAck
  * @param  I3Cx I3C Instance.
  * @param  TargetId This parameter must be a value between Min_Data=1 and Max_Data=4
  * @retval None
  */
static inline void LL_I3C_DisableTargetCRAck(I3C_TypeDef *I3Cx, uint32_t TargetId)
{
  CLEAR_BIT(I3Cx->DEVRX[TargetId - 1U], I3C_DEVRX_CRACK);
}

/**
  * @brief  Indicates if Controller-role Request from target x will be
  *         Acknowledged or Not Acknowledged (controller mode).
  *         RESET: Controller-role Request Not Acknowledged.
  *         SET: Controller-role Request Acknowledged.
  * @rmtoll DEVRX        CRACK         LL_I3C_IsEnabledTargetCRAck
  * @param  I3Cx I3C Instance.
  * @param  TargetId This parameter must be a value between Min_Data=1 and Max_Data=4
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsEnabledTargetCRAck(const I3C_TypeDef *I3Cx, uint32_t TargetId)
{
  return ((READ_BIT(I3Cx->DEVRX[TargetId - 1U], I3C_DEVRX_CRACK) == I3C_DEVRX_CRACK) ? 1UL : 0UL);
}

/**
  * @brief  Enable additional Mandatory Data Byte (MDB) follows the accepted IBI from target x.
  * @rmtoll DEVRX        IBIDEN          LL_I3C_EnableIBIAddData
  * @param  I3Cx I3C Instance.
  * @param  TargetId This parameter must be a value between Min_Data=1 and Max_Data=4
  * @retval None
  */
static inline void LL_I3C_EnableIBIAddData(I3C_TypeDef *I3Cx, uint32_t TargetId)
{
  SET_BIT(I3Cx->DEVRX[TargetId - 1U], I3C_DEVRX_IBIDEN);
}

/**
  * @brief  Disable additional Mandatory Data Byte (MDB) follows the accepted IBI from target x.
  * @rmtoll DEVRX        IBIDEN          LL_I3C_DisableIBIAddData
  * @param  I3Cx I3C Instance.
  * @param  TargetId This parameter must be a value between Min_Data=1 and Max_Data=4
  * @retval None
  */
static inline void LL_I3C_DisableIBIAddData(I3C_TypeDef *I3Cx, uint32_t TargetId)
{
  CLEAR_BIT(I3Cx->DEVRX[TargetId - 1U], I3C_DEVRX_IBIDEN);
}

/**
  * @brief  Indicates if additional Mandatory Data Byte (MDB) follows the accepted IBI from target x.
  *         RESET: No Mandatory Data Byte follows IBI.
  *         SET: Mandatory Data Byte follows IBI.
  * @rmtoll DEVRX        IBIDEN          LL_I3C_IsEnabledIBIAddData
  * @param  I3Cx I3C Instance.
  * @param  TargetId This parameter must be a value between Min_Data=1 and Max_Data=4
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsEnabledIBIAddData(const I3C_TypeDef *I3Cx, uint32_t TargetId)
{
  return ((READ_BIT(I3Cx->DEVRX[TargetId - 1U], I3C_DEVRX_IBIDEN) == I3C_DEVRX_IBIDEN) ? 1UL : 0UL);
}

/**
  * @brief  Enable Suspension of Current transfer during IBI treatment.
  * @note   When set, this feature will allow controller to send
  *         a Stop condition and CR FIFO is flushed after IBI treatment.
  *         Software has to rewrite instructions in Control Register to start a new transfer.
  * @rmtoll DEVRX        SUSP          LL_I3C_EnableFrameSuspend
  * @param  I3Cx I3C Instance.
  * @param  TargetId This parameter must be a value between Min_Data=1 and Max_Data=4
  * @retval None
  */
static inline void LL_I3C_EnableFrameSuspend(I3C_TypeDef *I3Cx, uint32_t TargetId)
{
  SET_BIT(I3Cx->DEVRX[TargetId - 1U], I3C_DEVRX_SUSP);
}

/**
  * @brief  Disable Suspension of Current transfer during IBI treatment.
  * @note   When set, this feature will allow controller to continue CR FIFO treatment after IBI treatment.
  * @rmtoll DEVRX        SUSP          LL_I3C_DisableFrameSuspend
  * @param  I3Cx I3C Instance.
  * @param  TargetId This parameter must be a value between Min_Data=1 and Max_Data=4
  * @retval None
  */
static inline void LL_I3C_DisableFrameSuspend(I3C_TypeDef *I3Cx, uint32_t TargetId)
{
  CLEAR_BIT(I3Cx->DEVRX[TargetId - 1U], I3C_DEVRX_SUSP);
}

/**
  * @brief  Indicates if I3C transfer must be Suspended or not Suspended during IBI treatment from target x.
  *         RESET: Transfer is not suspended. Instruction in CR FIFO are executed after IBI.
  *         SET: Transfer is suspended (a Stop condition is sent). CR FIFO is flushed.
  * @rmtoll DEVRX        SUSP          LL_I3C_IsFrameMustBeSuspended
  * @param  I3Cx I3C Instance.
  * @param  TargetId This parameter must be a value between Min_Data=1 and Max_Data=4
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsFrameMustBeSuspended(const I3C_TypeDef *I3Cx, uint32_t TargetId)
{
  return ((READ_BIT(I3Cx->DEVRX[TargetId - 1U], I3C_DEVRX_SUSP) == I3C_DEVRX_SUSP) ? 1UL : 0UL);
}

/**
  * @brief  Indicates if update of the Device Characteristics Register is Allowed or Not Allowed.
  *         RESET: Device Characteristics Register update is Not Allowed.
  *         SET: Device Characteristics Register update is Allowed.
  * @note   Used to prevent software writing during reception of an IBI or Controller-role Request from target x.
  * @rmtoll DEVRX        DIS           LL_I3C_IsAllowedPayloadUpdate
  * @param  I3Cx I3C Instance.
  * @param  TargetId This parameter must be a value between Min_Data=1 and Max_Data=4
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsAllowedPayloadUpdate(const I3C_TypeDef *I3Cx, uint32_t TargetId)
{
  return ((READ_BIT(I3Cx->DEVRX[TargetId - 1U], I3C_DEVRX_DIS) != I3C_DEVRX_DIS) ? 1UL : 0UL);
}

/**
  * @brief  Set I3C bus devices configuration.
  * @note   This function is called only when the I3C instance is initialized as controller.
  *         This function can be called by the controller application to help the automatic treatment when target have
  *         capability of IBI and/or Control-Role.
  * @rmtoll DEVRX        DA            LL_I3C_ConfigDeviceCapabilities
  * @rmtoll DEVRX        IBIACK        LL_I3C_ConfigDeviceCapabilities
  * @rmtoll DEVRX        IBIDEN        LL_I3C_ConfigDeviceCapabilities
  * @rmtoll DEVRX        CRACK         LL_I3C_ConfigDeviceCapabilities
  * @param  I3Cx I3C Instance.
  * @param  TargetId This parameter must be a value between Min_Data=1 and Max_Data=4
  * @param  DynamicAddr Value between Min_Data=0 to Max_Data=0x7F
  * @param  IBIAck Value This parameter can be one of the following values:
  *         @arg @ref LL_I3C_IBI_CAPABILITY
  *         @arg @ref LL_I3C_IBI_NO_CAPABILITY
  * @param  IBIAddData This parameter can be one of the following values:
  *         @arg @ref LL_I3C_IBI_DATA_ENABLE
  *         @arg @ref LL_I3C_IBI_DATA_DISABLE
  * @param  CRAck This parameter can be one of the following values:
  *         @arg @ref LL_I3C_CR_CAPABILITY
  *         @arg @ref LL_I3C_CR_NO_CAPABILITY
  * @retval None
  */
static inline void LL_I3C_ConfigDeviceCapabilities(I3C_TypeDef *I3Cx,
                                                     uint32_t TargetId,
                                                     uint32_t DynamicAddr,
                                                     uint32_t IBIAck,
                                                     uint32_t IBIAddData,
                                                     uint32_t CRAck)
{
  MODIFY_REG(I3Cx->DEVRX[TargetId - 1U], \
             (I3C_DEVRX_DA | I3C_DEVRX_IBIACK | I3C_DEVRX_CRACK | I3C_DEVRX_IBIDEN), \
             ((DynamicAddr << I3C_DEVRX_DA_POS) | IBIAck | IBIAddData | CRAck));
}
/**
  * @}
  */

/** @defgroup I3C_LL_EF_FLAG_management FLAG_management
  * @{
  */

/**
  * @brief  Indicates the status of Control FIFO Empty flag.
  *         RESET: One or more data are available in Control FIFO.
  *         SET: No more data available in Control FIFO.
  * @rmtoll EVR          CFEF          LL_I3C_IsActiveFlag_CFE
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsActiveFlag_CFE(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->EVR, I3C_EVR_CFEF) == (I3C_EVR_CFEF)) ? 1UL : 0UL);
}

/**
  * @brief  Indicates the status of Transmit FIFO Empty flag.
  *         RESET: One or more data are available in Transmit FIFO.
  *         SET: No more data available in Transmit FIFO.
  * @rmtoll EVR          TXFEF         LL_I3C_IsActiveFlag_TXFE
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsActiveFlag_TXFE(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->EVR, I3C_EVR_TXFEF) == (I3C_EVR_TXFEF)) ? 1UL : 0UL);
}

/**
  * @brief  Indicates the status of Control FIFO Not Full flag.
  *         RESET: One or more free space available in Control FIFO.
  *         SET: No more free space available in Control FIFO.
  * @note   When a transfer is ongoing, the Control FIFO shall not be written unless this flag is set.
  * @rmtoll EVR          CFNFF         LL_I3C_IsActiveFlag_CFNF
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsActiveFlag_CFNF(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->EVR, I3C_EVR_CFNFF) == (I3C_EVR_CFNFF)) ? 1UL : 0UL);
}

/**
  * @brief  Indicates the status of Status FIFO Not Empty flag.
  *         RESET: One or more free space available in Status FIFO.
  *         SET: No more free space available in Status FIFO.
  * @note   This flag is updated only when the FIFO is used, mean SMODE = 1.
  * @rmtoll EVR          SFNEF         LL_I3C_IsActiveFlag_SFNE
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsActiveFlag_SFNE(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->EVR, I3C_EVR_SFNEF) == (I3C_EVR_SFNEF)) ? 1UL : 0UL);
}

/**
  * @brief  Indicates the status of Transmit FIFO Not Full flag.
  *         RESET: One or more free space available in Transmit FIFO.
  *         SET: No more free space available in Transmit FIFO.
  * @note   When a transfer is ongoing, the Transmit FIFO shall not be written unless this flag is set.
  * @rmtoll EVR          TXFNFF        LL_I3C_IsActiveFlag_TXFNF
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsActiveFlag_TXFNF(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->EVR, I3C_EVR_TXFNFF) == (I3C_EVR_TXFNFF)) ? 1UL : 0UL);
}

/**
  * @brief  Indicates the status of Receive FIFO Not Full flag.
  *         RESET: One or more data are available in Receive FIFO.
  *         SET: No more data available in Receive FIFO.
  * @rmtoll EVR          RXFNEF        LL_I3C_IsActiveFlag_RXFNE
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsActiveFlag_RXFNE(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->EVR, I3C_EVR_RXFNEF) == (I3C_EVR_RXFNEF)) ? 1UL : 0UL);
}

/**
  * @brief  Indicates the status of Frame Complete flag (controller and target mode).
  *         RESET: Current Frame transfer is not finalized.
  *         SET: Current Frame transfer is completed.
  * @rmtoll EVR          FCF           LL_I3C_IsActiveFlag_FC
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsActiveFlag_FC(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->EVR, I3C_EVR_FCF) == (I3C_EVR_FCF)) ? 1UL : 0UL);
}

/**
  * @brief  Indicates the status of Reception Target End flag (controller mode).
  *         RESET: Clear default value.
  *         SET: Target prematurely ended a Read Command.
  * @note   This flag is set only when status FIFO is not used, mean SMODE = 0.
  * @rmtoll EVR          RXTGTENDF     LL_I3C_IsActiveFlag_RXTGTEND
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsActiveFlag_RXTGTEND(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->EVR, I3C_EVR_RXTGTENDF) == (I3C_EVR_RXTGTENDF)) ? 1UL : 0UL);
}

/**
  * @brief  Indicates the status of Error flag (controller and target mode).
  *         RESET: Clear default value.
  *         SET: One or more Errors are detected.
  * @rmtoll EVR          ERRF          LL_I3C_IsActiveFlag_ERR
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsActiveFlag_ERR(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->EVR, I3C_EVR_ERRF) == (I3C_EVR_ERRF)) ? 1UL : 0UL);
}

/**
  * @brief  Indicates the status of IBI flag (controller mode).
  *         RESET: Clear default value.
  *         SET: An IBI have been received.
  * @rmtoll EVR          IBIF          LL_I3C_IsActiveFlag_IBI
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsActiveFlag_IBI(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->EVR, I3C_EVR_IBIF) == (I3C_EVR_IBIF)) ? 1UL : 0UL);
}

/**
  * @brief  Indicates the status of Controller-role Request flag (controller mode).
  *         RESET: Clear default value.
  *         SET: A Controller-role request procedure have been received.
  * @rmtoll EVR          CRF           LL_I3C_IsActiveFlag_CR
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsActiveFlag_CR(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->EVR, I3C_EVR_CRF) == (I3C_EVR_CRF)) ? 1UL : 0UL);
}

/**
  * @brief  Indicates the status of Hot Join flag (controller mode).
  *         RESET: Clear default value.
  *         SET: A Hot Join request have been received.
  * @rmtoll EVR          HJF           LL_I3C_IsActiveFlag_HJ
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsActiveFlag_HJ(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->EVR, I3C_EVR_HJF) == (I3C_EVR_HJF)) ? 1UL : 0UL);
}

/**
  * @brief  Indicates the status of Protocol Error flag.
  *         RESET: Clear default value.
  *         SET: Protocol error detected.
  * @rmtoll SER          PERR          LL_I3C_IsActiveFlag_PERR
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsActiveFlag_PERR(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->SER, I3C_SER_PERR) == (I3C_SER_PERR)) ? 1UL : 0UL);
}

/**
  * @brief  Indicates the status of SCL Stall Error flag (target mode).
  *         RESET: Clear default value.
  *         SET: Target detected that SCL was stable for more than 125us during I3C SDR read.
  * @rmtoll SER          STALL         LL_I3C_IsActiveFlag_STALL
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsActiveFlag_STALL(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->SER, I3C_SER_STALL) == (I3C_SER_STALL)) ? 1UL : 0UL);
}

/**
  * @brief  Indicates the status of RX or TX FIFO Overrun flag.
  *         RESET: Clear default value.
  *         SET: RX FIFO Full or TX FIFO Empty depending of direction of message.
  * @rmtoll SER          DOVR          LL_I3C_IsActiveFlag_DOVR
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsActiveFlag_DOVR(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->SER, I3C_SER_DOVR) == (I3C_SER_DOVR)) ? 1UL : 0UL);
}

/**
  * @brief  Indicates the status of Control or Status FIFO Overrun flag (controller mode).
  *         RESET: Clear default value.
  *         SET: Status FIFO Full or Control FIFO Empty after Restart.
  * @rmtoll SER          COVR          LL_I3C_IsActiveFlag_COVR
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsActiveFlag_COVR(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->SER, I3C_SER_COVR) == (I3C_SER_COVR)) ? 1UL : 0UL);
}

/**
  * @brief  Indicates the status of Address not acknowledged flag (controller mode).
  *         RESET: Clear default value.
  *         SET: Controller detected that Target nacked static or dynamic address.
  * @rmtoll SER          ANACK         LL_I3C_IsActiveFlag_ANACK
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsActiveFlag_ANACK(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->SER, I3C_SER_ANACK) == (I3C_SER_ANACK)) ? 1UL : 0UL);
}

/**
  * @brief  Indicates the status of Data not acknowledged flag (controller mode).
  *         RESET: Clear default value.
  *         SET: Controller detected that Target nacked Data byte.
  * @rmtoll SER          DNACK         LL_I3C_IsActiveFlag_DNACK
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsActiveFlag_DNACK(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->SER, I3C_SER_DNACK) == (I3C_SER_DNACK)) ? 1UL : 0UL);
}

/**
  * @brief  Indicates the status of Data error flag (controller mode).
  *         RESET: Clear default value.
  *         SET: Controller detected data error during Controller-role handoff process.
  * @rmtoll SER          DERR          LL_I3C_IsActiveFlag_DERR
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsActiveFlag_DERR(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->SER, I3C_SER_DERR) == (I3C_SER_DERR)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup I3C_LL_EF_IT_Management IT_Management
  * @{
  */

/**
  * @brief  Enable Control FIFO Not Full interrupt.
  * @rmtoll IER          CFNFIE        LL_I3C_EnableIT_CFNF
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_EnableIT_CFNF(I3C_TypeDef *I3Cx)
{
  SET_BIT(I3Cx->IER, I3C_IER_CFNFIE);
}

/**
  * @brief  Disable Control FIFO Not Full interrupt.
  * @rmtoll IER          CFNFIE        LL_I3C_DisableIT_CFNF
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_DisableIT_CFNF(I3C_TypeDef *I3Cx)
{
  CLEAR_BIT(I3Cx->IER, I3C_IER_CFNFIE);
}

/**
  * @brief  Check if Control FIFO Not Full interrupt is enabled or disabled.
  * @rmtoll IER          CFNFIE        LL_I3C_IsEnabledIT_CFNF
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsEnabledIT_CFNF(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->IER, I3C_IER_CFNFIE) == (I3C_IER_CFNFIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable Status FIFO Not Empty interrupt.
  * @rmtoll IER          SFNEIE        LL_I3C_EnableIT_SFNE
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_EnableIT_SFNE(I3C_TypeDef *I3Cx)
{
  SET_BIT(I3Cx->IER, I3C_IER_SFNEIE);
}

/**
  * @brief  Disable Status FIFO Not Empty interrupt.
  * @rmtoll IER          SFNEIE        LL_I3C_DisableIT_SFNE
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_DisableIT_SFNE(I3C_TypeDef *I3Cx)
{
  CLEAR_BIT(I3Cx->IER, I3C_IER_SFNEIE);
}

/**
  * @brief  Check if Status FIFO Not Empty interrupt is enabled or disabled.
  * @rmtoll IER          SFNEIE        LL_I3C_IsEnabledIT_SFNE
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsEnabledIT_SFNE(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->IER, I3C_IER_SFNEIE) == (I3C_IER_SFNEIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable Transmit FIFO Not Full interrupt.
  * @rmtoll IER          TXFNFIE       LL_I3C_EnableIT_TXFNF
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_EnableIT_TXFNF(I3C_TypeDef *I3Cx)
{
  SET_BIT(I3Cx->IER, I3C_IER_TXFNFIE);
}

/**
  * @brief  Disable Transmit FIFO Not Full interrupt.
  * @rmtoll IER          TXFNFIE       LL_I3C_DisableIT_TXFNF
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_DisableIT_TXFNF(I3C_TypeDef *I3Cx)
{
  CLEAR_BIT(I3Cx->IER, I3C_IER_TXFNFIE);
}

/**
  * @brief  Check if Transmit FIFO Not Full interrupt is enabled or disabled.
  * @rmtoll IER          TXFNFIE       LL_I3C_IsEnabledIT_TXFNF
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsEnabledIT_TXFNF(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->IER, I3C_IER_TXFNFIE) == (I3C_IER_TXFNFIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable Receive FIFO Not Empty interrupt.
  * @rmtoll IER          RXFNEIE       LL_I3C_EnableIT_RXFNE
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_EnableIT_RXFNE(I3C_TypeDef *I3Cx)
{
  SET_BIT(I3Cx->IER, I3C_IER_RXFNEIE);
}

/**
  * @brief  Disable Receive FIFO Not Empty interrupt.
  * @rmtoll IER          RXFNEIE       LL_I3C_DisableIT_RXFNE
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_DisableIT_RXFNE(I3C_TypeDef *I3Cx)
{
  CLEAR_BIT(I3Cx->IER, I3C_IER_RXFNEIE);
}

/**
  * @brief  Check if Receive FIFO Not Empty interrupt is enabled or disabled.
  * @rmtoll IER          RXFNEIE       LL_I3C_IsEnabledIT_RXFNE
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsEnabledIT_RXFNE(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->IER, I3C_IER_RXFNEIE) == (I3C_IER_RXFNEIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable Frame Complete interrupt.
  * @rmtoll IER          FCIE          LL_I3C_EnableIT_FC
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_EnableIT_FC(I3C_TypeDef *I3Cx)
{
  SET_BIT(I3Cx->IER, I3C_IER_FCIE);
}

/**
  * @brief  Disable Frame Complete interrupt.
  * @rmtoll IER          FCIE          LL_I3C_DisableIT_FC
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_DisableIT_FC(I3C_TypeDef *I3Cx)
{
  CLEAR_BIT(I3Cx->IER, I3C_IER_FCIE);
}

/**
  * @brief  Check if Frame Complete interrupt is enabled or disabled.
  * @rmtoll IER          FCIE          LL_I3C_IsEnabledIT_FC
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsEnabledIT_FC(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->IER, I3C_IER_FCIE) == (I3C_IER_FCIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable Reception Target End interrupt.
  * @rmtoll IER          RXTGTENDIE    LL_I3C_EnableIT_RXTGTEND
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_EnableIT_RXTGTEND(I3C_TypeDef *I3Cx)
{
  SET_BIT(I3Cx->IER, I3C_IER_RXTGTENDIE);
}

/**
  * @brief  Disable Reception Target End interrupt.
  * @rmtoll IER          RXTGTENDIE    LL_I3C_DisableIT_RXTGTEND
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_DisableIT_RXTGTEND(I3C_TypeDef *I3Cx)
{
  CLEAR_BIT(I3Cx->IER, I3C_IER_RXTGTENDIE);
}

/**
  * @brief  Check if Reception Target End interrupt is enabled or disabled.
  * @rmtoll IER          RXTGTENDIE    LL_I3C_IsEnabledIT_RXTGTEND
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsEnabledIT_RXTGTEND(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->IER, I3C_IER_RXTGTENDIE) == (I3C_IER_RXTGTENDIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable Error interrupt.
  * @rmtoll IER          ERRIE         LL_I3C_EnableIT_ERR
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_EnableIT_ERR(I3C_TypeDef *I3Cx)
{
  SET_BIT(I3Cx->IER, I3C_IER_ERRIE);
}

/**
  * @brief  Disable Error interrupt.
  * @rmtoll IER          ERRIE         LL_I3C_DisableIT_ERR
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_DisableIT_ERR(I3C_TypeDef *I3Cx)
{
  CLEAR_BIT(I3Cx->IER, I3C_IER_ERRIE);
}

/**
  * @brief  Check if Error interrupt is enabled or disabled.
  * @rmtoll IER          ERRIE         LL_I3C_IsEnabledIT_ERR
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsEnabledIT_ERR(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->IER, I3C_IER_ERRIE) == (I3C_IER_ERRIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable IBI interrupt.
  * @rmtoll IER          IBIIE         LL_I3C_EnableIT_IBI
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_EnableIT_IBI(I3C_TypeDef *I3Cx)
{
  SET_BIT(I3Cx->IER, I3C_IER_IBIIE);
}

/**
  * @brief  Disable IBI interrupt.
  * @rmtoll IER          IBIIE         LL_I3C_DisableIT_IBI
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_DisableIT_IBI(I3C_TypeDef *I3Cx)
{
  CLEAR_BIT(I3Cx->IER, I3C_IER_IBIIE);
}

/**
  * @brief  Check if IBI interrupt is enabled or disabled.
  * @rmtoll IER          IBIIE         LL_I3C_IsEnabledIT_IBI
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsEnabledIT_IBI(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->IER, I3C_IER_IBIIE) == (I3C_IER_IBIIE)) ? 1UL : 0UL);
}


/**
  * @brief  Enable Controller-role interrupt.
  * @rmtoll IER          CRIE          LL_I3C_EnableIT_CR
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_EnableIT_CR(I3C_TypeDef *I3Cx)
{
  SET_BIT(I3Cx->IER, I3C_IER_CRIE);
}

/**
  * @brief  Disable Controller-role interrupt.
  * @rmtoll IER          CRIE          LL_I3C_DisableIT_CR
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_DisableIT_CR(I3C_TypeDef *I3Cx)
{
  CLEAR_BIT(I3Cx->IER, I3C_IER_CRIE);
}

/**
  * @brief  Check if Controller-role interrupt is enabled or disabled.
  * @rmtoll IER          CRIE          LL_I3C_IsEnabledIT_CR
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsEnabledIT_CR(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->IER, I3C_IER_CRIE) == (I3C_IER_CRIE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable Hot Join interrupt.
  * @rmtoll IER          HJIE          LL_I3C_EnableIT_HJ
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_EnableIT_HJ(I3C_TypeDef *I3Cx)
{
  SET_BIT(I3Cx->IER, I3C_IER_HJIE);
}

/**
  * @brief  Disable Hot Join interrupt.
  * @rmtoll IER          HJIE          LL_I3C_DisableIT_HJ
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_DisableIT_HJ(I3C_TypeDef *I3Cx)
{
  CLEAR_BIT(I3Cx->IER, I3C_IER_HJIE);
}

/**
  * @brief  Check if Hot Join interrupt is enabled or disabled.
  * @rmtoll IER          HJIE          LL_I3C_IsEnabledIT_HJ
  * @param  I3Cx I3C Instance.
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_I3C_IsEnabledIT_HJ(const I3C_TypeDef *I3Cx)
{
  return ((READ_BIT(I3Cx->IER, I3C_IER_HJIE) == (I3C_IER_HJIE)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @addtogroup I3C_LL_EF_FLAG_management FLAG_management
  * @{
  */
/**
  * @brief  Clear Frame Complete flag (controller and target mode).
  * @rmtoll CEVR         CFCF          LL_I3C_ClearFlag_FC
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_ClearFlag_FC(I3C_TypeDef *I3Cx)
{
  WRITE_REG(I3Cx->CEVR, I3C_CEVR_CFCF);
}

/**
  * @brief  Clear Reception Target End flag (controller mode).
  * @rmtoll CEVR         CRXTGTENDF    LL_I3C_ClearFlag_RXTGTEND
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_ClearFlag_RXTGTEND(I3C_TypeDef *I3Cx)
{
  WRITE_REG(I3Cx->CEVR, I3C_CEVR_CRXTGTENDF);
}

/**
  * @brief  Clear Error flag (controller and target mode).
  * @rmtoll CEVR         CERRF         LL_I3C_ClearFlag_ERR
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_ClearFlag_ERR(I3C_TypeDef *I3Cx)
{
  WRITE_REG(I3Cx->CEVR, I3C_CEVR_CERRF);
}

/**
  * @brief  Clear IBI flag (controller mode).
  * @rmtoll CEVR         CIBIF         LL_I3C_ClearFlag_IBI
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_ClearFlag_IBI(I3C_TypeDef *I3Cx)
{
  WRITE_REG(I3Cx->CEVR, I3C_CEVR_CIBIF);
}


/**
  * @brief  Clear Controller-role Request flag (controller mode).
  * @rmtoll CEVR         CCRF          LL_I3C_ClearFlag_CR
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_ClearFlag_CR(I3C_TypeDef *I3Cx)
{
  WRITE_REG(I3Cx->CEVR, I3C_CEVR_CCRF);
}

/**
  * @brief  Clear Hot Join flag (controller mode).
  * @rmtoll CEVR         CHJF          LL_I3C_ClearFlag_HJ
  * @param  I3Cx I3C Instance.
  * @retval None
  */
static inline void LL_I3C_ClearFlag_HJ(I3C_TypeDef *I3Cx)
{
  WRITE_REG(I3Cx->CEVR, I3C_CEVR_CHJF);
}

/**
  * @}
  */

#endif

#ifdef __cplusplus
}
#endif
