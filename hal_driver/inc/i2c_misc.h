#ifndef __I2C_MISC_H
#define __I2C_MISC_H

typedef enum
{
  HAL_I2C_MODE_NONE               = 0x00U,   /*!< No I2C communication on going             */
  HAL_I2C_MODE_MASTER             = 0x10U,   /*!< I2C communication is in Master Mode       */
  HAL_I2C_MODE_SLAVE              = 0x20U,   /*!< I2C communication is in Slave Mode        */

} HAL_I2C_ModeTypeDef;
typedef enum
{
  HAL_I2C_STATE_RESET             = 0x00U,   /*!< Peripheral is not yet Initialized         */
  HAL_I2C_STATE_READY             = 0x20U,   /*!< Peripheral Initialized and ready for use  */
  HAL_I2C_STATE_BUSY              = 0x24U,   /*!< An internal process is ongoing            */
  HAL_I2C_STATE_BUSY_TX           = 0x21U,   /*!< Data Transmission process is ongoing      */
  HAL_I2C_STATE_BUSY_RX           = 0x22U,   /*!< Data Reception process is ongoing         */
  HAL_I2C_STATE_LISTEN            = 0x28U,   /*!< Address Listen Mode is ongoing            */
  HAL_I2C_STATE_BUSY_TX_LISTEN    = 0x29U,   /*!< Address Listen Mode and Data Transmission
                                                 process is ongoing                         */
  HAL_I2C_STATE_BUSY_RX_LISTEN    = 0x2AU,   /*!< Address Listen Mode and Data Reception
                                                 process is ongoing                         */
  HAL_I2C_STATE_ABORT             = 0x60U,   /*!< Abort user request ongoing                */
  HAL_I2C_STATE_TIMEOUT           = 0xA0U,   /*!< Timeout state                             */
  HAL_I2C_STATE_ERROR             = 0xE0U    /*!< Error                                     */

} HAL_I2C_StateTypeDef;

enum
{
    I2C_SPEED_NORMAL_100K = 0,
    I2C_SPEED_FAST_400K,
    I2C_SPEED_FAST_ULTRA_1M,
    I2C_SPEED_MAX
};

#define I2C_DIRECTION_RECEIVE           0x00000000U
#define I2C_DIRECTION_TRANSMIT          0x00000001U
#define  I2C_FIRST_FRAME                0x00000001U
#define  I2C_FIRST_AND_NEXT_FRAME       0x00000002U
#define  I2C_NEXT_FRAME                 0x00000004U
#define  I2C_FIRST_AND_LAST_FRAME       0x00000008U
#define  I2C_LAST_FRAME_NO_STOP         0x00000010U
#define  I2C_LAST_FRAME                 0x00000020U

#define  I2C_OTHER_FRAME                (0x00AA0000U)
#define  I2C_OTHER_AND_LAST_FRAME       (0xAA000000U)

#define I2C_IT_RXNE                     I2C_IER_RXNEIE_MASK
#define I2C_IT_TXE                      I2C_IER_TXEIE_MASK
#define I2C_IT_TC                       I2C_IER_TCIE_MASK
#define I2C_IT_TCR                      I2C_IER_TCRIE_MASK
#define I2C_IT_EVT                      I2C_IER_ADDRIE_MASK | I2C_IER_NACKIE_MASK | I2C_IER_STOPIE_MASK
#define I2C_IT_ERR                      I2C_IER_BERRIE_MASK
#define I2C_FLAG_TXE                    I2C_SR_TXE_MASK
#define I2C_FLAG_RXNE                   I2C_SR_RXNE_MASK
#define I2C_FLAG_ADDR                   I2C_SR_ADDR_MASK
#define I2C_FLAG_NACK                   I2C_SR_NACKF_MASK
#define I2C_FLAG_STOPF                  I2C_SR_STOPF_MASK
#define I2C_FLAG_TC                     I2C_SR_TC_MASK
#define I2C_FLAG_TCR                    I2C_SR_TCR_MASK
#define I2C_FLAG_BERR                   I2C_SR_BERR_MASK
#define I2C_FLAG_ARLO                   I2C_SR_ARLO_MASK
#define I2C_FLAG_OVR                    I2C_SR_OVR_MASK
#define I2C_FLAG_PECERR                 I2C_SR_PECERR_MASK
#define I2C_FLAG_BUSY                   I2C_SR_BUSY_MASK
#define I2C_FLAG_TIMEOUT                I2C_SR_TIMEOUT_MASK
#define I2C_FLAG_ALERT                  I2C_SR_ALERT_MASK
#define I2C_FLAG_DIR                    I2C_SR_DIR_MASK

#define I2C_MIN_FREQ       32000U     /*!< 32kHz                     */

#define I2C_FREQRANGE(__PCLK__,__SPEED__)                            ((__PCLK__)/(__SPEED__))

#define __HAL_I2C_RESET_HANDLE_STATE(__HANDLE__)                ((__HANDLE__)->State = HAL_I2C_STATE_RESET)
#define __HAL_I2C_ENABLE_IT(__HANDLE__, __INTERRUPT__)   SET_BIT((__HANDLE__)->Instance->IER,(__INTERRUPT__))
#define __HAL_I2C_DISABLE_IT(__HANDLE__, __INTERRUPT__)  SET_BIT((__HANDLE__)->Instance->IDR,(__INTERRUPT__))
#define __HAL_I2C_GET_IT_RIF(__HANDLE__, __INTERRUPT__) ((((__HANDLE__)->Instance->RIF & (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)
#define __HAL_I2C_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) ((((__HANDLE__)->Instance->IVS & (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)
#define __HAL_I2C_GET_CR2_FLAG(__HANDLE__, __INTERRUPT__)  ((((__HANDLE__)->Instance->CR2 & (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)
#define __HAL_I2C_GET_FLAG(__HANDLE__, __FLAG__) (((((__HANDLE__)->Instance->SR) & (__FLAG__)) == (__FLAG__)) ? SET : RESET)
#define __HAL_I2C_CLEAR_IF(__HANDLE__, __FLAG__)      SET_BIT((__HANDLE__)->Instance->ICR, (__FLAG__))
#define __HAL_I2C_CLEAR_FLAG(__HANDLE__, __FLAG__)    SET_BIT((__HANDLE__)->Instance->CFR, (__FLAG__))
#define __HAL_I2C_CLEAR_ADDRFLAG(__HANDLE__)          SET_BIT((__HANDLE__)->Instance->CFR, I2C_CFR_ADDRCF_MASK)   
#define __HAL_I2C_CLEAR_STOPFLAG(__HANDLE__)          SET_BIT((__HANDLE__)->Instance->CFR, I2C_CFR_STOPCF_MASK) 
#define __HAL_I2C_CLEAR_SR(__HANDLE__)                SET_BIT((__HANDLE__)->Instance->CFR, 0x3F38) 
#define __HAL_I2C_ENABLE(__HANDLE__)                  SET_BIT((__HANDLE__)->Instance->CR1, I2C_CR1_PE_MASK)
#define __HAL_I2C_DISABLE(__HANDLE__)                 CLEAR_BIT((__HANDLE__)->Instance->CR1, I2C_CR1_PE_MASK)
#define __HAL_I2C_SBC_ENABLE(__HANDLE__)                  SET_BIT((__HANDLE__)->Instance->CR1, I2C_CR1_SBC_MASK)
#define __HAL_I2C_SBC_DISABLE(__HANDLE__)                 CLEAR_BIT((__HANDLE__)->Instance->CR1, I2C_CR1_SBC_MASK)
#define __HAL_I2C_RXFTH_SET(__HANDLE__, val)                  REG_FIELD_WR((__HANDLE__)->Instance->CR1, I2C_CR1_RXFTH, val)
#define __HAL_I2C_NBYTES_SET(__HANDLE__, val)                  REG_FIELD_WR((__HANDLE__)->Instance->CR2, I2C_CR2_NBYTES, val)
#define __HAL_I2C_RELOAD_ENABLE(__HANDLE__)                  SET_BIT((__HANDLE__)->Instance->CR2, I2C_CR2_RELOAD_MASK)
#define __HAL_I2C_RELOAD_DISABLE(__HANDLE__)                 CLEAR_BIT((__HANDLE__)->Instance->CR2, I2C_CR2_RELOAD_MASK)
#define I2C_MEM_ADD_MSB(__ADDRESS__)                  ((uint8_t)((uint16_t)(((uint16_t)((__ADDRESS__) & (uint16_t)0xFF00)) >> 8)))
#define I2C_MEM_ADD_LSB(__ADDRESS__)                  ((uint8_t)((uint16_t)((__ADDRESS__) & (uint16_t)0x00FF)))

#define I2C_MIN_PCLK_FREQ_STANDARD       400000U      /*!< 400 kHz                     */
#define I2C_MIN_PCLK_FREQ_FAST           1000000U     /*!< 1 MHz                     */
#define IS_I2C_ALL_INSTANCE(INSTANCE) (((INSTANCE) == I2C1) || \
                                       ((INSTANCE) == I2C2))
#define IS_I2C_ADDRESSING_MODE(ADDRESS) (((ADDRESS) == I2C_ADDRESSINGMODE_7BIT) || \
                                         ((ADDRESS) == I2C_ADDRESSINGMODE_10BIT))
#define IS_I2C_DUAL_ADDRESS(ADDRESS) (((ADDRESS) == I2C_DUALADDRESS_DISABLE) || \
                                      ((ADDRESS) == I2C_DUALADDRESS_ENABLE))
#define IS_I2C_GENERAL_CALL(CALL) (((CALL) == I2C_GENERALCALL_DISABLE) || \
                                   ((CALL) == I2C_GENERALCALL_ENABLE))
#define IS_I2C_NO_STRETCH(STRETCH) (((STRETCH) == I2C_NOSTRETCH_DISABLE) || \
                                    ((STRETCH) == I2C_NOSTRETCH_ENABLE))
#define IS_I2C_MEMADD_SIZE(SIZE) (((SIZE) == I2C_MEMADD_SIZE_8BIT) || \
                                  ((SIZE) == I2C_MEMADD_SIZE_16BIT))

#define IS_I2C_CLOCK_SPEED(SPEED) (((SPEED) == I2C_SPEED_NORMAL_100K) || ((SPEED) == I2C_SPEED_FAST_400K) || ((SPEED) == I2C_SPEED_FAST_ULTRA_1M))
#define IS_I2C_OWN_ADDRESS1(ADDRESS1) (((ADDRESS1) & 0xFFFFFC00U) == 0U)
#define IS_I2C_OWN_ADDRESS2(ADDRESS2) (((ADDRESS2<<1) & 0xFFFFFF01U) == 0U)
#define IS_I2C_TRANSFER_OPTIONS_REQUEST(REQUEST)      (((REQUEST) == I2C_FIRST_FRAME)              || \
                                                       ((REQUEST) == I2C_FIRST_AND_NEXT_FRAME)     || \
                                                       ((REQUEST) == I2C_NEXT_FRAME)               || \
                                                       ((REQUEST) == I2C_FIRST_AND_LAST_FRAME)     || \
                                                       ((REQUEST) == I2C_LAST_FRAME)               || \
                                                       ((REQUEST) == I2C_LAST_FRAME_NO_STOP)       || \
                                                       IS_I2C_TRANSFER_OTHER_OPTIONS_REQUEST(REQUEST))

#define IS_I2C_TRANSFER_OTHER_OPTIONS_REQUEST(REQUEST) (((REQUEST) == I2C_OTHER_FRAME)     || \
                                                        ((REQUEST) == I2C_OTHER_AND_LAST_FRAME))

#define I2C_CHECK_FLAG(__ISR__, __FLAG__)         ((((__ISR__) & (__FLAG__)) == (__FLAG__)) ? SET : RESET)
#define I2C_CHECK_IT_SOURCE(__CR1__, __IT__)      ((((__CR1__) & (__IT__)) == (__IT__)) ? SET : RESET)


#endif


