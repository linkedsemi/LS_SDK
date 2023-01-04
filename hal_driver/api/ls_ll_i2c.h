#ifndef _LS_LL_I2C_H
#define _LS_LL_I2C_H
#include <stdbool.h>
#include "reg_i2c_type.h"
#include "HAL_def.h"
#include "ls_dbg.h"
#include "sdk_config.h"
#include "i2c_misc.h"
#include "ls_msp_i2c.h"
#include "reg_base_addr.h"
#include "field_manipulate.h"
#include "log.h"

/** \addtogroup PERIPHERAL
 *  @{
 */

/** \addtogroup LSI2C
 *  @{
 */


/******************************************************************************
 External Macro Definition
 ******************************************************************************/

/**
 * @brief i2c closk
 * 
 */
#define I2C_CLOCK (SDK_PCLK_MHZ * 1000000)  /*!<  i2c closk           */
/******************************************************************************
 External Variable Definition
 ******************************************************************************/

/**
 * @brief i2c date dirction
 * 
 */
#define WRITEFERDIRECTION 0x00000000U       /* !<  i2c Writefer Direction       */
#define READDIRECTION I2C_CR2_RD_WEN_MASK   /* !<  i2c Read Direction           */

/**
 * @brief i2c ack mode
 * 
 */
#define LL_I2C_ACK 0x00000000U          /* !<  i2c ack mode        */
#define LL_I2C_NACK I2C_CR2_NACK_MASK   /* !<  i2c nack mode       */

/**
 * @brief i2c address lenght
 * 
 */
#define LL_I2C_OWNADDRESS1_7BIT 0x00000000U              /* !<  i2c 7bit address         */
#define LL_I2C_OWNADDRESS1_10BIT I2C_OAR1_OA1MODE_MASK   /* !<  i2c 10bit address        */

/**
 * @brief i2c bus timeout A
 * 
 */
#define LL_I2C_TIMEOUTR_TIMEOUTA0 0x00000000U                  /* !<  i2c scl low speed timeout        */
#define LL_I2C_TIMEOUTR_TIMEOUTA1 I2C_TIMEOUTR_TIMEOUTA_MASK   /* !<  i2c bus idla timeout             */

/**
 * @brief i2c check idle sck timeout 
 * 
 */
#define LL_I2C_TIMEOUTR_SCL_LOWTIMEOUT 0x00000000U                    /* !<  i2c scl low  timeout check        */ 
#define LL_I2C_TIMEOUTR_SCL_SDA_HIGHTIMEOUT I2C_TIMEOUTR_TIDLE_MASK   /* !<  i2c scl and sda high  timeout check       */

/**
 * @brief i2c resigest bit 
 * 
 */
#define I2C_SR_TXE      I2C_SR_TXE_MASK
#define I2C_SR_RXNE     I2C_SR_RXNE_MASK
#define I2C_SR_ADDR     I2C_SR_ADDR_MASK
#define I2C_SR_NACKF    I2C_SR_NACKF_MASK
#define I2C_SR_STOPF    I2C_SR_STOPF_MASK
#define I2C_SR_TC       I2C_SR_TC_MASK
#define I2C_SR_TCR      I2C_SR_TCR_MASK
#define I2C_SR_BERR     I2C_SR_BERR_MASK
#define I2C_SR_ARLO     I2C_SR_ARLO_MASK
#define I2C_SR_OVR      I2C_SR_OVR_MASK
#define I2C_SR_PECERR   I2C_SR_PECERR_MASK
#define I2C_SR_TIMEOUT  I2C_SR_TIMEOUT_MASK
#define I2C_SR_ALERT    I2C_SR_ALERT_MASK
#define I2C_SR_BUSY     I2C_SR_BUSY_MASK
#define I2C_SR_DIR      I2C_SR_DIR_MASK
#define I2C_SR_ADDCODE  I2C_SR_ADDCODE_MASK
#define I2C_SR_TXFLV    I2C_SR_TXFLV_MASK
#define I2C_SR_RXFLV    I2C_SR_RXFLV_MASK

#define I2C_CFR_ADDRCF  I2C_CFR_ADDRCF_MASK
#define I2C_CFR_NACKCF  I2C_CFR_NACKCF_MASK
#define I2C_CFR_STOPCF  I2C_CFR_STOPCF_MASK
#define I2C_CFR_BERRCF  I2C_CFR_BERRCF_MASK
#define I2C_CFR_ARLOCF  I2C_CFR_ARLOCF_MASK
#define I2C_CFR_OVRCF   I2C_CFR_OVRCF_MASK
#define I2C_CFR_FECCF   I2C_CFR_FECCF_MASK
#define I2C_CFR_TIMEOUTCF I2C_CFR_TIMEOUTCF_MASK
#define I2C_CFR_ALERTCF I2C_CFR_ALERTCF_MASK

#define I2C_ITEN_RXNE   I2C_IER_RXNEIE_MASK
#define I2C_ITEN_TXE    I2C_IER_TXEIE_MASK
#define I2C_ITEN_ADDR   I2C_IER_ADDRIE_MASK
#define I2C_ITEN_NACK   I2C_IER_NACKIE_MASK
#define I2C_ITEN_STOP   I2C_IER_STOPIE_MASK
#define I2C_ITEN_TC     I2C_IER_TCIE_MASK
#define I2C_ITEN_TCR    I2C_IER_TCRIE_MASK
#define I2C_ITEN_ERR    I2C_IER_BERRIE_MASK
#define I2C_ITEN_ARLO   I2C_IER_ARLOIE_MASK
#define I2C_ITEN_OVR    I2C_IER_OVRIE_MASK
#define I2C_ITEN_PECE   I2C_IER_PECEIE_MASK
#define I2C_ITEN_TOUT   I2C_IER_TOUTIE_MASK
#define I2C_ITEN_ALERT  I2C_IER_ALERTIE_MASK

#define I2C_ITDEN_RXNE  I2C_IDR_RXNEID_MASK
#define I2C_ITDEN_TXE   I2C_IDR_TXEID_MASK
#define I2C_ITDEN_ADDR  I2C_IDR_ADDRID_MASK
#define I2C_ITDEN_NACK  I2C_IDR_NACKID_MASK
#define I2C_ITDEN_STOP  I2C_IDR_STOPID_MASK
#define I2C_ITDEN_TC    I2C_IDR_TCID_MASK
#define I2C_ITDEN_TCR   I2C_IDR_TCRID_MASK
#define I2C_ITDEN_ERR   I2C_IDR_BERRID_MASK
#define I2C_ITDEN_ARLO  I2C_IDR_ARLOID_MASK
#define I2C_ITDEN_OVR   I2C_IDR_OVRID_MASK
#define I2C_ITDEN_PECE  I2C_IDR_PECEID_MASK
#define I2C_ITDEN_TOUT  I2C_IDR_TOUTID_MASK
#define I2C_ITDEN_ALERT I2C_IDR_ALERTID_MASK

#define I2C_ITVS_RXNE   I2C_IVS_RXNEIV_MASK
#define I2C_ITVS_TXE    I2C_IVS_TXEIV_MASK
#define I2C_ITVS_ADDR   I2C_IVS_ADDRIV_MASK
#define I2C_ITVS_NACK   I2C_IVS_NACKIV_MASK
#define I2C_ITVS_STOP   I2C_IVS_STOPIV_MASK
#define I2C_ITVS_TC     I2C_IVS_TCIV_MASK
#define I2C_ITVS_TCR    I2C_IVS_TCRIV_MASK
#define I2C_ITVS_ERR    I2C_IVS_BERRIV_MASK
#define I2C_ITVS_ARLO   I2C_IVS_ARLOIV_MASK
#define I2C_ITVS_OVR    I2C_IVS_OVRIV_MASK
#define I2C_ITVS_PECE   I2C_IVS_PECEIV_MASK
#define I2C_ITVS_TOUT   I2C_IVS_TOUTIV_MASK
#define I2C_ITVS_ALERT  I2C_IVS_ALERTIV_MASK

#define I2C_ITRI_RXNE   I2C_RIF_RXNERI_MASK
#define I2C_ITRI_TXE    I2C_RIF_TXERI_MASK
#define I2C_ITRI_ADDR   I2C_RIF_ADDRRI_MASK
#define I2C_ITRI_NACK   I2C_RIF_NACKRI_MASK
#define I2C_ITRI_STOP   I2C_RIF_STOPRI_MASK
#define I2C_ITRI_TC     I2C_RIF_TCRI_MASK
#define I2C_ITRI_TCR    I2C_RIF_TCRRI_MASK
#define I2C_ITRI_ERR    I2C_RIF_BERRRI_MASK
#define I2C_ITRI_ARLO   I2C_RIF_ARLORI_MASK
#define I2C_ITRI_OVR    I2C_RIF_OVRRI_MASK
#define I2C_ITRI_PECE   I2C_RIF_PECERI_MASK
#define I2C_ITRI_TOUT   I2C_RIF_TOUTRI_MASK
#define I2C_ITRI_ALERT  I2C_RIF_ALERTRI_MASK

#define I2C_ITFM_RXNE   I2C_IFM_RXNEFM_MASK
#define I2C_ITFM_TXE    I2C_IFM_TXEFM_MASK
#define I2C_ITFM_ADDR   I2C_IFM_ADDRFM_MASK
#define I2C_ITFM_NACK   I2C_IFM_NACKFM_MASK
#define I2C_ITFM_STOP   I2C_IFM_STOPFM_MASK
#define I2C_ITFM_TC     I2C_IFM_TCFM_MASK
#define I2C_ITFM_TCR    I2C_IFM_TCRFM_MASK
#define I2C_ITFM_ERR    I2C_IFM_BERRFM_MASK
#define I2C_ITFM_ARLO   I2C_IFM_ARLOFM_MASK
#define I2C_ITFM_OVR    I2C_IFM_OVRFM_MASK
#define I2C_ITFM_PECE   I2C_IFM_PECEFM_MASK
#define I2C_ITFM_TOUT   I2C_IFM_TOUTFM_MASK
#define I2C_ITFM_ALERT  I2C_IFM_ALERTFM_MASK

#define I2C_ITIC_RXNE   I2C_ICR_RXNEIC_MASK
#define I2C_ITIC_TXE    I2C_ICR_TXEIC_MASK
#define I2C_ITIC_ADDR   I2C_ICR_ADDRIC_MASK
#define I2C_ITIC_NACK   I2C_ICR_NACKIC_MASK
#define I2C_ITIC_STOP   I2C_ICR_STOPIC_MASK
#define I2C_ITIC_TC     I2C_ICR_TCIC_MASK
#define I2C_ITIC_TCR    I2C_ICR_TCRIC_MASK
#define I2C_ITIC_ERR    I2C_ICR_BERRIC_MASK
#define I2C_ITIC_ARLO   I2C_ICR_ARLOIC_MASK
#define I2C_ITIC_OVR    I2C_ICR_OVRIC_MASK
#define I2C_ITIC_PECE   I2C_ICR_PECEIC_MASK
#define I2C_ITIC_TOUT   I2C_ICR_TOUTIC_MASK
#define I2C_ITIC_ALERT  I2C_ICR_ALERTIC_MASK



/******************************************************************************
 External Function Definition
 ******************************************************************************/
/******************************************CR1*******************************************/
/*                                                                                      */
/*                                                                                      */
/*                                                                                      */
/*                                                                                      */
/******************************************CR1*******************************************/

/**
 * @brief  Enable I2C peripheral (PE = 1).
 * @param  I2Cx I2C Instance.
 * @retval None
 */
static inline void LL_I2C_Enable(reg_i2c_t *I2Cx)
{
    SET_BIT(I2Cx->CR1, I2C_CR1_PE_MASK);
}

/**
 * @brief  Disable I2C peripheral (PE = 0).
 * @param  I2Cx I2C Instance.
 * @retval None
 */
static inline void LL_I2C_Disable(reg_i2c_t *I2Cx)
{
    CLEAR_BIT(I2Cx->CR1, I2C_CR1_PE_MASK);
}

/**
 * @brief  Check if I2C peripheral is enabled
 * @param  I2Cx I2C Instance
 * @retval State of bit (1 or 0).
 */
static inline uint32_t LL_I2C_IsEnabled(reg_i2c_t *I2Cx)
{
    return ((READ_BIT(I2Cx->CR1, I2C_CR1_PE_MASK) == (I2C_CR1_PE_MASK)) ? 1UL : 0UL);
}

/**
 * @brief  Configure Digital Noise Filter.
 * @note   This filter can only be programmed when the I2C is disabled (PE = 0).
 * @param  I2Cx I2C Instance.
 * @param  DigitalFilter This parameter must be a value between Min_Data=0x00 (Digital filter disabled) and Max_Data=0x0F (Digital filter enabled and filtering capability up to 15*TPCLK1)
 *               This parameter is used to configure the digital noise filter on SDA and SCL input. The digital filter will suppress the I2Ckes with a length of up to DNF[3:0]*TPCLK1.
 * @retval None
 */
static inline void LL_I2C_SetDigitalFilter(reg_i2c_t *I2Cx, uint32_t DigitalFilter)
{
    MODIFY_REG(I2Cx->CR1, I2C_CR1_DNF_MASK, DigitalFilter << I2C_CR1_DNF_POS);
}

/**
 * @brief  Get the current Digital Noise Filter configuration.
 * @param  I2Cx I2C Instance.
 * @retval Value between Min_Data=0x0 and Max_Data=0xF
 */
static inline uint32_t LL_I2C_GetDigitalFilter(reg_i2c_t *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->CR1, I2C_CR1_DNF_MASK) >> I2C_CR1_DNF_POS);
}
/**
 * @brief  Enable DMA transmission requests.
 * @param  I2Cx I2C Instance.
 * @retval None
 */
static inline void LL_I2C_EnableDMAReq_TX(reg_i2c_t *I2Cx)
{
    SET_BIT(I2Cx->CR1, I2C_CR1_TXDMAEN_MASK);
}

/**
 * @brief  Disable DMA transmission requests.
 * @param  I2Cx I2C Instance.
 * @retval None
 */
static inline void LL_I2C_DisableDMAReq_TX(reg_i2c_t *I2Cx)
{
    CLEAR_BIT(I2Cx->CR1, I2C_CR1_TXDMAEN_MASK);
}
/**
 * @brief  Check if DMA transmission requests are enabled or disabled.
 * @param  I2Cx I2C Instance.
 * @retval State of bit (1 or 0).
 */
static inline uint32_t LL_I2C_IsEnabledDMAReq_TX(reg_i2c_t *I2Cx)
{
    return (READ_BIT(I2Cx->CR1, I2C_CR1_TXDMAEN_MASK) == (I2C_CR1_TXDMAEN_MASK));
}

/**
 * @brief  Enable DMA reception requests.
 * @param  I2Cx I2C Instance.
 * @retval None
 */
static inline void LL_I2C_EnableDMAReq_RX(reg_i2c_t *I2Cx)
{
    SET_BIT(I2Cx->CR1, I2C_CR1_RXDMAEN_MASK);
}
/**
 * @brief  Disable DMA reception requests.
 * @param  I2Cx I2C Instance.
 * @retval None
 */
static inline void LL_I2C_DisableDMAReq_RX(reg_i2c_t *I2Cx)
{
    CLEAR_BIT(I2Cx->CR1, I2C_CR1_RXDMAEN_MASK);
}

/**
 * @brief  Check if DMA reception requests are enabled or disabled.
 * @param  I2Cx I2C Instance.
 * @retval State of bit (1 or 0).
 */
static inline uint32_t LL_I2C_IsEnabledDMAReq_RX(reg_i2c_t *I2Cx)
{
    return (READ_BIT(I2Cx->CR1, I2C_CR1_RXDMAEN_MASK) == (I2C_CR1_RXDMAEN_MASK));
}
/**
 * @brief  Enable Slave byte conteol.
 * @param  I2Cx I2C Instance.
 * @retval None
 */
static inline void LL_I2C_EnableDMAReq_SBC(reg_i2c_t *I2Cx)
{
    SET_BIT(I2Cx->CR1, I2C_CR1_SBC_MASK);
}
/**
 * @brief  Disable Slave byte conteol.
 * @param  I2Cx I2C Instance.
 * @retval None
 */
static inline void LL_I2C_DisableDMAReq_SBC(reg_i2c_t *I2Cx)
{
    CLEAR_BIT(I2Cx->CR1, I2C_CR1_SBC_MASK);
}

/**
 * @brief  Check if Slave byte conteol are enabled or disabled.
 * @param  I2Cx I2C Instance.
 * @retval State of bit (1 or 0).
 */
static inline uint32_t LL_I2C_IsEnabledDMAReq_SBC(reg_i2c_t *I2Cx)
{
    return (READ_BIT(I2Cx->CR1, I2C_CR1_SBC_MASK) == (I2C_CR1_SBC_MASK));
}
/**
 * @brief  Get the data register address used for DMA transfer.
 * @param  I2Cx I2C Instance.
 * @retval Address of data register
 */
static inline uint32_t LL_I2C_DMA_GetReceiveRegAddr(reg_i2c_t *I2Cx)
{
    return (uint32_t) & (I2Cx->RXDR);
}

/**
 * @brief  Get the data register address used for DMA transfer.
 * @param  I2Cx I2C Instance.
 * @retval Address of data register
 */
static inline uint32_t LL_I2C_DMA_GetTransmitRegAddr(reg_i2c_t *I2Cx)
{
    return (uint32_t) & (I2Cx->TXDR);
}
/**
 * @brief  Enable Clock stretching.
 * @note   This bit can only be programmed when the I2C is disabled (PE = 0).
 * @param  I2Cx I2C Instance.
 * @retval None
 */
static inline void LL_I2C_EnableClockStretching(reg_i2c_t *I2Cx)
{
    CLEAR_BIT(I2Cx->CR1, I2C_CR1_NOSTRETCH_MASK);
}

/**
 * @brief  Disable Clock stretching.
 * @note   This bit can only be programmed when the I2C is disabled (PE = 0).
 * @param  I2Cx I2C Instance.
 * @retval None
 */
static inline void LL_I2C_DisableClockStretching(reg_i2c_t *I2Cx)
{
    SET_BIT(I2Cx->CR1, I2C_CR1_NOSTRETCH_MASK);
}

/**
 * @brief  Check if Clock stretching is enabled or disabled.
 * @param  I2Cx I2C Instance.
 * @retval State of bit (1 or 0).
 */
static inline uint32_t LL_I2C_IsEnabledClockStretching(reg_i2c_t *I2Cx)
{
    return (READ_BIT(I2Cx->CR1, I2C_CR1_NOSTRETCH_MASK) != (I2C_CR1_NOSTRETCH_MASK));
}

/**
 * @brief  Enable General Call.
 * @note   When enabled the Address 0x00 is ACKed.
 * @param  I2Cx I2C Instance.
 * @retval None
 */
static inline void LL_I2C_EnableGeneralCall(reg_i2c_t *I2Cx)
{
    SET_BIT(I2Cx->CR1, I2C_CR1_GCEN_MASK);
}

/**
 * @brief  Disable General Call.
 * @note   When disabled the Address 0x00 is NACKed.
 * @param  I2Cx I2C Instance.
 * @retval None
 */
static inline void LL_I2C_DisableGeneralCall(reg_i2c_t *I2Cx)
{
    CLEAR_BIT(I2Cx->CR1, I2C_CR1_GCEN_MASK);
}

/**
 * @brief  Check if General Call is enabled or disabled.
 * @param  I2Cx I2C Instance.
 * @retval State of bit (1 or 0).
 */
static inline uint32_t LL_I2C_IsEnableGeneralCall(reg_i2c_t *I2Cx)
{
    return (READ_BIT(I2Cx->CR1, I2C_CR1_GCEN_MASK) == (I2C_CR1_GCEN_MASK));
}
/**
 * @brief  Enable SMBus host address.
 * @param  I2Cx I2C Instance.
 * @retval None
 */
static inline void LL_I2C_EnableSMBHEN(reg_i2c_t *I2Cx)
{
    SET_BIT(I2Cx->CR1, I2C_CR1_SMBHEN_MASK);
}

/**
 * @brief  Disable SMBus host address.
 * @param  I2Cx I2C Instance.
 * @retval None
 */
static inline void LL_I2C_DisableSMBHEN(reg_i2c_t *I2Cx)
{
    CLEAR_BIT(I2Cx->CR1, I2C_CR1_SMBHEN_MASK);
}

/**
 * @brief  Check if SMBus host address is enabled or disabled.
 * @param  I2Cx I2C Instance.
 * @retval State of bit (1 or 0).
 */
static inline uint32_t LL_I2C_IsEnableSMBHEN(reg_i2c_t *I2Cx)
{
    return (READ_BIT(I2Cx->CR1, I2C_CR1_SMBHEN_MASK) == (I2C_CR1_SMBHEN_MASK));
}
/**
 * @brief  Enable SMBus device default address.
 * @param  I2Cx I2C Instance.
 * @retval None
 */
static inline void LL_I2C_EnableSMBDEN(reg_i2c_t *I2Cx)
{
    SET_BIT(I2Cx->CR1, I2C_CR1_SMBDEN_MASK);
}

/**
 * @brief  Disable SMBus device default address.
 * @param  I2Cx I2C Instance.
 * @retval None
 */
static inline void LL_I2C_DisableSMBDEN(reg_i2c_t *I2Cx)
{
    CLEAR_BIT(I2Cx->CR1, I2C_CR1_SMBDEN_MASK);
}

/**
 * @brief  Check if SMBus device default address is enabled or disabled.
 * @param  I2Cx I2C Instance.
 * @retval State of bit (1 or 0).
 */
static inline uint32_t LL_I2C_IsEnableSMBDEN(reg_i2c_t *I2Cx)
{
    return (READ_BIT(I2Cx->CR1, I2C_CR1_SMBDEN_MASK) == (I2C_CR1_SMBDEN_MASK));
}

/**
 * @brief  Enable SMBus alert (Host or Device mode)
 * @note   SMBus Device mode:
 *         - SMBus Alert pin is drived low and
 *           Alert Response Address Header acknowledge is enabled.
 *         SMBus Host mode:
 *         - SMBus Alert pin management is supported.
 * @param  I2Cx I2C Instance.
 * @retval None
 */
static inline void LL_I2C_EnableSMBusALERT(reg_i2c_t *I2Cx)
{
    SET_BIT(I2Cx->CR1, I2C_CR1_ALERTEN_MASK);
}

/**
 * @brief  Disable SMBus alert (Host or Device mode)
 * @note   SMBus Device mode:
 *         - SMBus Alert pin is not drived (can be used as a standard GPIO) and
 *           Alert Response Address Header acknowledge is disabled.
 *         SMBus Host mode:
 *         - SMBus Alert pin management is not supported.
 * @param  I2Cx I2C Instance.
 * @retval None
 */
static inline void LL_I2C_DisableSMBusALERT(reg_i2c_t *I2Cx)
{
    CLEAR_BIT(I2Cx->CR1, I2C_CR1_ALERTEN_MASK);
}

/**
 * @brief  Check if SMBus alert (Host or Device mode) is enabled or disabled.
 * @param  I2Cx I2C Instance.
 * @retval State of bit (1 or 0).
 */
static inline uint32_t LL_I2C_IsEnabledSMBusALERT(reg_i2c_t *I2Cx)
{
    return (READ_BIT(I2Cx->CR1, I2C_CR1_ALERTEN_MASK) == (I2C_CR1_ALERTEN_MASK));
}

/**
 * @brief  Enable SMBus Packet Error Calculation (PEC).
 * @param  I2Cx I2C Instance.
 * @retval None
 */
static inline void LL_I2C_EnableSMBusPEC(reg_i2c_t *I2Cx)
{
    SET_BIT(I2Cx->CR1, I2C_CR1_PECEN_MASK);
}

/**
 * @brief  Disable SMBus Packet Error Calculation (PEC).
 * @param  I2Cx I2C Instance.
 * @retval None
 */
static inline void LL_I2C_DisableSMBusPEC(reg_i2c_t *I2Cx)
{
    CLEAR_BIT(I2Cx->CR1, I2C_CR1_PECEN_MASK);
}

/**
 * @brief  Check if SMBus Packet Error Calculation (PEC) is enabled or disabled.
 * @param  I2Cx I2C Instance.
 * @retval State of bit (1 or 0).
 */
static inline uint32_t LL_I2C_IsEnabledSMBusPEC(reg_i2c_t *I2Cx)
{
    return (READ_BIT(I2Cx->CR1, I2C_CR1_PECEN_MASK) == (I2C_CR1_PECEN_MASK));
}

/**
 * @brief  Set Tx FIFO threshold
 * @param  I2Cx I2C Instance.
 * @param  TXFTH This parameter must be a value between Min_Data=0 and Max_Data=0x7.
 * @retval None
 */
static inline void LL_I2C_SetTXFTH(reg_i2c_t *I2Cx, uint32_t TXFTH)
{
    MODIFY_REG(I2Cx->CR1, I2C_CR1_TXFTH_MASK, (TXFTH << I2C_CR1_TXFTH_POS) & I2C_CR1_TXFTH_MASK);
}

/**
 * @brief  Get Tx FIFO threshold.
 * @param  I2Cx I2C Instance.
 * @retval Value between Min_Data=0x0 and Max_Data=0x7
 */
static inline uint32_t LL_I2C_GetTXFTH(reg_i2c_t *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->CR1, I2C_CR1_TXFTH_MASK) >> I2C_CR1_TXFTH_POS);
}

/**
 * @brief  Set Rx FIFO threshold .
 * @param  I2Cx I2C Instance.
 * @param  RXFTH This parameter must be a value between Min_Data=0 and Max_Data=0x7.
 * @retval None
 */
static inline void LL_I2C_SetRXFTH(reg_i2c_t *I2Cx, uint32_t RXFTH)
{
    MODIFY_REG(I2Cx->CR1, I2C_CR1_RXFTH_MASK, (RXFTH << I2C_CR1_RXFTH_POS) & I2C_CR1_RXFTH_MASK);
}

/**
 * @brief  Get Rx FIFO threshold.
 * @param  I2Cx I2C Instance.
 * @retval Value between Min_Data=0x0 and Max_Data=0x7
 */
static inline uint32_t LL_I2C_GetRXFTH(reg_i2c_t *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->CR1, I2C_CR1_RXFTH_MASK) >> I2C_CR1_RXFTH_POS);
}

/******************************************CR2*******************************************/
/*                                                                                      */
/*                                                                                      */
/*                                                                                      */
/*                                                                                      */
/******************************************CR2*******************************************/
/**
 * @brief  Set the Own Address1.
 * @param  I2Cx I2C Instance.
 * @param  Address This parameter must be a value between Min_Data=0 and Max_Data=0x3FF.
 * @param  RWDirection This parameter can be one of the following values:
 *         @arg WRITEFERDIRECTION
 *         @arg READDIRECTION
 * @param  OwnAddrSize This parameter can be one of the following values:
 *         @arg LL_I2C_OWNADDRESS1_7BIT
 *         @arg LL_I2C_OWNADDRESS1_10BIT
 * @retval None
 */
static inline void LL_I2C_SetAddressToSlave(reg_i2c_t *I2Cx, uint32_t Address, uint8_t RWDirection, uint32_t OwnAddrSize)
{
    if (OwnAddrSize == LL_I2C_OWNADDRESS1_7BIT)
    {
        /* Send slave address */
        CLEAR_BIT(I2Cx->CR2, I2C_CR2_SADD10_MASK);
        MODIFY_REG(I2Cx->CR2, I2C_CR2_RD_WEN_MASK | I2C_CR2_SADD1_7_MASK, ((Address << 1) & 0xFE) | ((RWDirection << 10) & I2C_CR2_RD_WEN_MASK));
    }
    else
    {
        /* Send header of slave address */
        SET_BIT(I2Cx->CR2, I2C_CR2_SADD10_MASK);
        MODIFY_REG(I2Cx->CR2, I2C_CR2_RD_WEN_MASK | I2C_CR2_SADD0_MASK | I2C_CR2_SADD1_7_MASK | I2C_CR2_SADD8_9_MASK, (Address & 0x3FF) | ((RWDirection << 10) & I2C_CR2_RD_WEN_MASK));
        CLEAR_BIT(I2Cx->CR2, I2C_CR2_HEAD10R_MASK);
    }
}

/**
 * @brief  Set transfer direction(master mode).
 * @param  I2Cx I2C Instance.
 * @param  TransferDirection This parameter can be one of the following values:
 *         @arg ReadDirection
 *         @arg WriteferDirection
 * @retval None
 */
static inline void LL_I2C_SetTransferDirection(reg_i2c_t *I2Cx, uint8_t TransferDirection)
{
    MODIFY_REG(I2Cx->CR2, I2C_CR2_RD_WEN_MASK, (TransferDirection << I2C_CR2_RD_WEN_POS) & I2C_CR2_RD_WEN_MASK);
}

/**
 * @brief  Set 10-bit address header onlt read direction.
 * @param  I2Cx I2C Instance.
 * @retval None
 */
static inline void LL_I2C_SetHEAD10R(reg_i2c_t *I2Cx)
{
    SET_BIT(I2Cx->CR2, I2C_CR2_HEAD10R_MASK);
}

/**
 * @brief  Generate a START or RESTART condition
 * @note   The START bit can be set even if bus is BUSY or I2C is in slave mode.
 *         This action has no effect when RELOAD is set.
 * @param  I2Cx I2C Instance.
 * @retval None
 */
static inline void LL_I2C_GenerateStartCondition(reg_i2c_t *I2Cx)
{
    SET_BIT(I2Cx->CR2, I2C_CR2_START_MASK);
}

/**
 * @brief  Generate a STOP condition after the current byte transfer (master mode).
 * @param  I2Cx I2C Instance.
 * @retval None
 */
static inline void LL_I2C_GenerateStopCondition(reg_i2c_t *I2Cx)
{
    SET_BIT(I2Cx->CR2, I2C_CR2_STOP_MASK);
}

/**
 * @brief  Prepare the generation of a ACKnowledge or Non ACKnowledge condition after the address receive match code or next received byte.
 * @note   Usage in Slave or Master mode.
 * @param  I2Cx I2C Instance.
 * @param  TypeAcknowledge This parameter can be one of the following values:
 *         @arg LL_I2C_ACK
 *         @arg LL_I2C_NACK
 * @retval None
 */
static inline void LL_I2C_AcknowledgeNextData(reg_i2c_t *I2Cx, uint32_t TypeAcknowledge)
{
    MODIFY_REG(I2Cx->CR2, I2C_CR2_NACK_MASK, TypeAcknowledge);
}

/**
 * @brief  Set number of bytes.
 * @param  I2Cx I2C Instance.
 * @param  NumberOfByte This parameter must be a value between Min_Data=0 and Max_Data=0xff.
 * @retval None
 */
static inline void LL_I2C_SetNumberOfByte(reg_i2c_t *I2Cx, uint8_t NumberOfByte)
{
    MODIFY_REG(I2Cx->CR2, I2C_CR2_NBYTES_MASK, (NumberOfByte << I2C_CR2_NBYTES_POS) & I2C_CR2_NBYTES_MASK);
}

/**
 * @brief  Enable NBYTES reload mode.
 * @param  I2Cx I2C Instance.
 * @retval None
 */
static inline void LL_I2C_EnableRELOAD(reg_i2c_t *I2Cx)
{
    SET_BIT(I2Cx->CR2, I2C_CR2_RELOAD_MASK);
}

/**
 * @brief  Disable NBYTES reload mode.
 * @param  I2Cx I2C Instance.
 * @retval None
 */
static inline void LL_I2C_DisableRELOAD(reg_i2c_t *I2Cx)
{
    CLEAR_BIT(I2Cx->CR2, I2C_CR2_RELOAD_MASK);
}

/**
 * @brief  Check if NBYTES reload mode. is enabled
 * @param  I2Cx I2C Instance
 * @retval State of bit (1 or 0).
 */
static inline uint32_t LL_I2C_IsEnabledRELOAD(reg_i2c_t *I2Cx)
{
    return ((READ_BIT(I2Cx->CR2, I2C_CR2_RELOAD_MASK) == (I2C_CR2_RELOAD_MASK)) ? 1UL : 0UL);
}

/**
 * @brief  Automatic end mode.
 * @param  I2Cx I2C Instance.
 * @retval None
 */
static inline void LL_I2C_EnableAutoEnd(reg_i2c_t *I2Cx)
{
    SET_BIT(I2Cx->CR2, I2C_CR2_AUTOEND_MASK);
}

/**
 * @brief  Software end mode.
 * @param  I2Cx I2C Instance.
 * @retval None
 */
static inline void LL_I2C_DisableAutoEnd(reg_i2c_t *I2Cx)
{
    CLEAR_BIT(I2Cx->CR2, I2C_CR2_AUTOEND_MASK);
}

/**
 * @brief  Disable packet error checking byte.
 * @param  I2Cx I2C Instance.
 * @retval None
 */
static inline void LL_I2C_EnablePECByte(reg_i2c_t *I2Cx)
{
    SET_BIT(I2Cx->CR2, I2C_CR2_PECBYTE_MASK);
}

/**
 * @brief  Disable packet error checking byte.
 * @param  I2Cx I2C Instance.
 * @retval None
 */
static inline void LL_I2C_DisablePECByte(reg_i2c_t *I2Cx)
{
    CLEAR_BIT(I2Cx->CR2, I2C_CR2_PECBYTE_MASK);
}

/******************************************OAR1******************************************/
/*                                                                                      */
/*                                                                                      */
/*                                                                                      */
/*                                                                                      */
/******************************************OAR1******************************************/

/**
 * @brief  Set the Own Address2.
 * @param  I2Cx I2C Instance.
 * @param  OwnAddress1 This parameter must be a value between Min_Data=0 and Max_Data=0x3FF.
 * @param  OwnAddrSize This parameter can be one of the following values:
 *         @arg LL_I2C_OWNADDRESS1_7BIT
 *         @arg LL_I2C_OWNADDRESS1_10BIT
 * @retval None
 */
static inline void LL_I2C_SetOwnAddress1(reg_i2c_t *I2Cx, uint32_t OwnAddress1, uint32_t OwnAddrSize)
{
    MODIFY_REG(I2Cx->OAR1, I2C_OAR1_OA10_MASK | I2C_OAR1_OA11_7_MASK | I2C_OAR1_OA18_9_MASK | I2C_OAR1_OA1MODE_MASK, OwnAddress1 | OwnAddrSize);
}

/**
 * @brief  Enable slave interface address1.
 * @param  I2Cx I2C Instance.
 * @retval None
 */
static inline void LL_I2C_EnableOAR1(reg_i2c_t *I2Cx)
{
    SET_BIT(I2Cx->OAR1, I2C_OAR1_OA1EN_MASK);
}

/******************************************OAR2******************************************/
/*                                                                                      */
/*                                                                                      */
/*                                                                                      */
/*                                                                                      */
/******************************************OAR2******************************************/
/**
 * @brief  Set the Own Address2.
 * @param  I2Cx I2C Instance.
 * @param  OwnAddress2 This parameter must be a value between Min_Data=0 and Max_Data=0xFE.
 * @retval None
 */
static inline void LL_I2C_SetOwnAddress2(reg_i2c_t *I2Cx, uint32_t OwnAddress2)
{
    MODIFY_REG(I2Cx->OAR2, I2C_OAR2_OA21_7_MASK, (OwnAddress2 << I2C_OAR2_OA21_7_POS) & I2C_OAR2_OA21_7_MASK);
}

/**
 * @brief  Set mask of slave interface address 2.
 * @param  I2Cx I2C Instance.
 * @param  OwnAddress2MASK This parameter must be a value between Min_Data=0 and Max_Data=0x7.
 * @retval None
 */
static inline void LL_I2C_SetOwnAddress2MASK(reg_i2c_t *I2Cx, uint32_t OwnAddress2MASK)
{
    MODIFY_REG(I2Cx->OAR2, I2C_OAR2_OA2MSK_MASK, (OwnAddress2MASK << I2C_OAR2_OA2MSK_POS) & I2C_OAR2_OA2MSK_MASK);
}

/**
 * @brief  Enable slave interface address2.
 * @param  I2Cx I2C Instance.
 * @retval None
 */
static inline void LL_I2C_EnableOAR2(reg_i2c_t *I2Cx)
{
    SET_BIT(I2Cx->OAR2, I2C_OAR2_OA2EN_MASK);
}
/******************************************TIMING******************************************/
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/******************************************TIMING******************************************/

/**
 * @brief  Set scl low period.
 * @param  I2Cx I2C Instance.
 * @param  SclLowPeriod This parameter must be a value between Min_Data=0 and Max_Data=0xFF.
 * @retval None
 */
static inline void LL_I2C_SetSclLowPeriod(reg_i2c_t *I2Cx, uint32_t SclLowPeriod)
{
    MODIFY_REG(I2Cx->TIMINGR, I2C_TIMINGR_SCLL_MASK, (SclLowPeriod & I2C_TIMINGR_SCLL_MASK) & I2C_TIMINGR_SCLL_MASK);
}

/**
 * @brief  Set scl high period.
 * @param  I2Cx I2C Instance.
 * @param  SclHighPeriod This parameter must be a value between Min_Data=0 and Max_Data=0xFF.
 * @retval None
 */
static inline void LL_I2C_SetSclHighPeriod(reg_i2c_t *I2Cx, uint32_t SclHighPeriod)
{
    MODIFY_REG(I2Cx->TIMINGR, I2C_TIMINGR_SCLH_MASK, (SclHighPeriod << I2C_TIMINGR_SCLH_POS) & I2C_TIMINGR_SCLH_MASK);
}

/**
 * @brief  Set data hold time.
 * @param  I2Cx I2C Instance.
 * @param  DataHoldTime This parameter must be a value between Min_Data=0 and Max_Data=0xF.
 * @retval None
 */
static inline void LL_I2C_SetDataHoldTime(reg_i2c_t *I2Cx, uint32_t DataHoldTime)
{
    MODIFY_REG(I2Cx->TIMINGR, I2C_TIMINGR_SDADEL_MASK, (DataHoldTime << I2C_TIMINGR_SDADEL_POS) & I2C_TIMINGR_SDADEL_MASK);
}

/**
 * @brief  Set data setup time.
 * @param  I2Cx I2C Instance.
 * @param  DataSetupTime This parameter must be a value between Min_Data=0 and Max_Data=0xF.
 * @retval None
 */
static inline void LL_I2C_SetDataSetupTime(reg_i2c_t *I2Cx, uint32_t DataSetupTime)
{
    MODIFY_REG(I2Cx->TIMINGR, I2C_TIMINGR_SCLDEL_MASK, (DataSetupTime << I2C_TIMINGR_SCLDEL_POS) & I2C_TIMINGR_SCLDEL_MASK);
}

/**
 * @brief  Set Preassigned frequency.
 * @param  I2Cx I2C Instance.
 * @param  TimingPrescaler Value between Min_Data=0x0 and Max_Data=0xF
 * @retval None
 */
static inline void LL_I2C_SetTimingPrescaler(reg_i2c_t *I2Cx, uint32_t TimingPrescaler)
{
    MODIFY_REG(I2Cx->TIMINGR, I2C_TIMINGR_PRESC_MASK, (TimingPrescaler << I2C_TIMINGR_PRESC_POS) & I2C_TIMINGR_PRESC_MASK);
}

/**
 * @brief  Set Transmission rate.
 * @param  I2Cx I2C Instance.
 * @param  ClockSpeed Value between Min_Data=0x0 and Max_Data=400000
 * @retval None
 */
static inline void LL_I2C_SetClockPeriod(reg_i2c_t *I2Cx, uint32_t ClockSpeed)

{
    uint32_t freq, SCLH, SCLL, sdadel, scldel;
    uint32_t pclk1;
    /* Calculate frequency value */
    if (ClockSpeed < I2C_MIN_FREQ)
        pclk1 = I2C_CLOCK >> 5;
    else
    {
        pclk1 = I2C_CLOCK;
    }
    freq = I2C_FREQRANGE(pclk1, ClockSpeed);
    SCLL = freq / 2;
    SCLH = freq - SCLL; // If it's not divisible,The remainder is added to SCLH
    sdadel = SCLH / 4;
    scldel = SCLH / 4;
    /*---------------------------- I2Cx TIMINGR Configuration ----------------------*/
    /* Configure I2Cx: Frequency range */
    if (ClockSpeed < I2C_MIN_FREQ)
    {
        MODIFY_REG(I2Cx->TIMINGR, I2C_TIMINGR_PRESC_MASK, 4 << I2C_TIMINGR_PRESC_POS);
    }
    else
    {
        CLEAR_BIT(I2Cx->TIMINGR, I2C_TIMINGR_PRESC_MASK);
    }
    MODIFY_REG(I2Cx->TIMINGR, (I2C_TIMINGR_SCLH_MASK | I2C_TIMINGR_SCLL_MASK), (SCLH << I2C_TIMINGR_SCLH_POS | SCLL << I2C_TIMINGR_SCLL_POS | sdadel << I2C_TIMINGR_SDADEL_POS | scldel << I2C_TIMINGR_SCLDEL_POS));
}
/******************************************TIMEOUTR******************************************/
/*                                                                                          */
/*                                                                                          */
/*                                                                                          */
/*                                                                                          */
/******************************************TIMEOUTR******************************************/

/**
 * @brief  Set Bus timeout A.
 * @param  I2Cx I2C Instance.
 * @param  TimeOutA Value between Min_Data=0x0 and Max_Data=0xFFF
 * @retval None
 */
static inline void LL_I2C_SetTimeOutA(reg_i2c_t *I2Cx, uint32_t TimeOutA)
{
    MODIFY_REG(I2Cx->TIMEOUTR, I2C_TIMEOUTR_TIMEOUTA_MASK, (TimeOutA << I2C_TIMEOUTR_TIMEOUTA_POS) & I2C_TIMEOUTR_TIMEOUTA_MASK);
}

/**
 * @brief  Set Idle time timeout detection.
 * @param  I2Cx I2C Instance.
 * @param  DetectionType This parameter can be one of the following values:
 *         @arg LL_I2C_TIMEOUTR_SCL_LOWTIMEOUT
 *         @arg LL_I2C_TIMEOUTR_SCL_SDA_HIGHTIMEOUT
 * @retval None
 */
static inline void LL_I2C_SetTimeIdle(reg_i2c_t *I2Cx, uint32_t DetectionType)
{
    MODIFY_REG(I2Cx->TIMEOUTR, I2C_TIMEOUTR_TIDLE_MASK, DetectionType);
}

/**
 * @brief  Enable TimeOut.
 * @param  I2Cx I2C Instance.
 * @retval None
 */
static inline void LL_I2C_EnableTimeOut(reg_i2c_t *I2Cx)
{
    SET_BIT(I2Cx->TIMEOUTR, I2C_TIMEOUTR_TIMEOUTEN_MASK);
}

/**
 * @brief  Disable TimeOut.
 * @param  I2Cx I2C Instance.
 * @retval None
 */
static inline void LL_I2C_DisableTimeOut(reg_i2c_t *I2Cx)
{
    CLEAR_BIT(I2Cx->TIMEOUTR, I2C_TIMEOUTR_TIMEOUTEN_MASK);
}

/**
 * @brief  Check if TimeOut is enabled or disabled.
 * @param  I2Cx I2C Instance.
 * @retval State of bit (1 or 0).
 */
static inline uint32_t LL_I2C_IsEnableTimeOut(reg_i2c_t *I2Cx)
{
    return (READ_BIT(I2Cx->TIMEOUTR, I2C_TIMEOUTR_TIMEOUTEN_MASK) == (I2C_TIMEOUTR_TIMEOUTEN_MASK));
}

/**
 * @brief  Set TimeOutB.
 * @param  I2Cx I2C Instance.
 * @param  TimeOutB Value between Min_Data=0x0 and Max_Data=0xFFF0000
 * @retval None
 */
static inline void LL_I2C_SetTimeOutB(reg_i2c_t *I2Cx, uint32_t TimeOutB)
{
    MODIFY_REG(I2Cx->TIMEOUTR, I2C_TIMEOUTR_TIMEOUTB_MASK, (TimeOutB << I2C_TIMEOUTR_TIMEOUTB_POS) & I2C_TIMEOUTR_TIMEOUTB_MASK);
}

/**
 * @brief  Enable TimeExten.
 * @param  I2Cx I2C Instance.
 * @retval None
 */
static inline void LL_I2C_EnableTimeExten(reg_i2c_t *I2Cx)
{
    SET_BIT(I2Cx->TIMEOUTR, I2C_TIMEOUTR_TEXTEN_MASK);
}

/**
 * @brief  Disable TimeExten .
 * @param  I2Cx I2C Instance.
 * @retval None
 */
static inline void LL_I2C_DisableTimeExten(reg_i2c_t *I2Cx)
{
    CLEAR_BIT(I2Cx->TIMEOUTR, I2C_TIMEOUTR_TEXTEN_MASK);
}

/**
 * @brief  Check if TimeExten is enabled or disabled.
 * @param  I2Cx I2C Instance.
 * @retval State of bit (1 or 0).
 */
static inline uint32_t LL_I2C_IsEnableTimeExten(reg_i2c_t *I2Cx)
{
    return (READ_BIT(I2Cx->TIMEOUTR, I2C_TIMEOUTR_TEXTEN_MASK) == (I2C_TIMEOUTR_TEXTEN_MASK));
}
/******************************************SR******************************************/
/*                                                                                    */
/*                                                                                    */
/*                                                                                    */
/*                                                                                    */
/******************************************SR******************************************/
/**
 * @brief  Get sr flag.
 * @param  I2Cx I2C Instance.
 * @param RegisterBit  This parameter can be one of the following values:
 *         @arg I2C_SR_TXE
 *         @arg I2C_SR_RXNE
 *         @arg I2C_SR_ADDR
 *         @arg I2C_SR_NACKF
 *         @arg I2C_SR_STOPF
 *         @arg I2C_SR_TC
 *         @arg I2C_SR_TCR
 *         @arg I2C_SR_BERR
 *         @arg I2C_SR_ARLO
 *         @arg I2C_SR_OVR
 *         @arg I2C_SR_PECERR
 *         @arg I2C_SR_TIMEOUT
 *         @arg I2C_SR_ALERT
 *         @arg I2C_SR_BUSY
 *         @arg I2C_SR_DIR
 *         @arg I2C_SR_ADDCODE
 *         @arg I2C_SR_TXFLV
 *         @arg I2C_SR_RXFLV
 * @retval State of bit (1 or 0).
 */
static inline uint32_t LL_I2C_IsActiveFlag(reg_i2c_t *I2Cx, uint32_t RegisterBit)
{
    return ((READ_BIT(I2Cx->SR, RegisterBit) == (RegisterBit)) ? 1UL : 0UL);
}

/******************************************CFR******************************************/
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/******************************************CFR******************************************/

/**
 * @brief  Clear sr flag.
 * @param  I2Cx I2C Instance.
 * @param RegisterBit  This parameter can be one of the following values:
 *         @arg I2C_CFR_ADDRCF
 *         @arg I2C_CFR_NACKCF
 *         @arg I2C_CFR_STOPCF
 *         @arg I2C_CFR_BERRCF
 *         @arg I2C_CFR_ARLOCF
 *         @arg I2C_CFR_OVRCF
 *         @arg I2C_CFR_FECCF
 *         @arg I2C_CFR_TIMEOUTCF
 *         @arg I2C_CFR_ALERTCF
 * @retval None
 */
static inline void LL_I2C_Clearflag(reg_i2c_t *I2Cx, uint32_t RegisterBit)
{
    SET_BIT(I2Cx->CFR, RegisterBit);
}

/**
 * @brief  Clear sr flag.
 * @param  I2Cx I2C Instance.
 * @retval None
 */
static inline void LL_I2C_ClearSR(reg_i2c_t *I2Cx)
{
    SET_BIT(I2Cx->CFR, 0xffff);
}
/******************************************PECR******************************************/
/*                                                                                      */
/*                                                                                      */
/*                                                                                      */
/*                                                                                      */
/******************************************PECR******************************************/

/**
 * @brief  packet error checking register .
 * @param  I2Cx I2C Instance.
 * @retval Value between Min_Data=0x0 and Max_Data=0xff
 */
static inline uint32_t LL_I2C_ReceivePECR(reg_i2c_t *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->PECR, I2C_PECR_PEC_MASK));
}

/******************************************RXDR******************************************/
/*                                                                                      */
/*                                                                                      */
/*                                                                                      */
/*                                                                                      */
/******************************************RXDR******************************************/
/**
 * @brief  Read in Transmit Data Register .
 * @param  I2Cx I2C Instance.
 * @retval Value between Min_Data=0x0 and Max_Data=0xff
 */
static inline uint32_t LL_I2C_ReceiveData8(reg_i2c_t *I2Cx)
{
    return (uint32_t)(READ_BIT(I2Cx->RXDR, I2C_RXDR_RXDATA_MASK));
}
/******************************************TXDR******************************************/
/*                                                                                      */
/*                                                                                      */
/*                                                                                      */
/*                                                                                      */
/******************************************TXDR******************************************/
/**
 * @brief  Write in Transmit Data Register .
 * @param  I2Cx I2C Instance.
 * @param  Data Value between Min_Data=0x0 and Max_Data=0xff
 * @retval None
 */
static inline void LL_I2C_TransmitData8(reg_i2c_t *I2Cx, uint8_t Data)
{
    MODIFY_REG(I2Cx->TXDR, I2C_TXDR_TXDATA_MASK, Data);
}
/******************************************IER******************************************/
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/******************************************IER******************************************/
/**
 * @brief  Enable interrupt.
 * @param  I2Cx I2C Instance.
 * @param RegisterBit  This parameter can be one of the following values:
 *         @arg I2C_ITEN_RXNE
 *         @arg I2C_ITEN_TXE
 *         @arg I2C_ITEN_ADDR
 *         @arg I2C_ITEN_NACK
 *         @arg I2C_ITEN_STOP
 *         @arg I2C_ITEN_TC
 *         @arg I2C_ITEN_TCR
 *         @arg I2C_ITEN_ERR
 *         @arg I2C_ITEN_ARLO
 *         @arg I2C_ITEN_OVR
 *         @arg I2C_ITEN_PECE
 *         @arg I2C_ITEN_TOUT
 *         @arg I2C_ITEN_ALERT
 * @retval None
 */
static inline void LL_I2C_EnableIT(reg_i2c_t *I2Cx, uint32_t RegisterBit)
{
    SET_BIT(I2Cx->IER, RegisterBit);
}

/******************************************IDR******************************************/
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/******************************************IDR******************************************/
/**
 * @brief  Disable interrupt.
 * @param  I2Cx I2C Instance.
 * @param RegisterBit  This parameter can be one of the following values:
 *         @arg I2C_ITDEN_RXNE
 *         @arg I2C_ITDEN_TXE
 *         @arg I2C_ITDEN_ADDR
 *         @arg I2C_ITDEN_NACK
 *         @arg I2C_ITDEN_STOP
 *         @arg I2C_ITDEN_TC
 *         @arg I2C_ITDEN_TCR
 *         @arg I2C_ITDEN_ERR
 *         @arg I2C_ITDEN_ARLO
 *         @arg I2C_ITDEN_OVR
 *         @arg I2C_ITDEN_PECE
 *         @arg I2C_ITDEN_TOUT
 *         @arg I2C_ITDEN_ALERT
 * @retval None
 */
static inline void LL_I2C_DisableIT(reg_i2c_t *I2Cx, uint32_t RegisterBit)
{
    SET_BIT(I2Cx->IDR, RegisterBit);
}

/******************************************IVS******************************************/
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/******************************************IVS******************************************/

/**
 * @brief  Check if  enable the interrupt.
 * @param  I2Cx I2C Instance
 * @param RegisterBit  This parameter can be one of the following values:
 *         @arg I2C_ITVS_RXNE
 *         @arg I2C_ITVS_TXE
 *         @arg I2C_ITVS_ADDR
 *         @arg I2C_ITVS_NACK
 *         @arg I2C_ITVS_STOP
 *         @arg I2C_ITVS_TC
 *         @arg I2C_ITVS_TCR
 *         @arg I2C_ITVS_ERR
 *         @arg I2C_ITVS_ARLO
 *         @arg I2C_ITVS_OVR
 *         @arg I2C_ITVS_PECE
 *         @arg I2C_ITVS_TOUT
 *         @arg I2C_ITVS_ALERT
 * @retval State of bit (1 or 0).
 */
static inline uint32_t LL_I2C_IsEnableIT(reg_i2c_t *I2Cx, uint32_t RegisterBit)
{
    // LOG_I("is enable tx !\n");
    return ((READ_BIT(I2Cx->IVS, RegisterBit) == (RegisterBit)) ? 1UL : 0UL);
}

/******************************************RIF******************************************/
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/******************************************RIF******************************************/

/**
 * @brief  Check if Generate the interrupt
 * @param  I2Cx I2C Instance
 * @param RegisterBit  This parameter can be one of the following values:
 *         @arg I2C_ITRI_RXNE
 *         @arg I2C_ITRI_TXE
 *         @arg I2C_ITRI_ADDR
 *         @arg I2C_ITRI_NACK
 *         @arg I2C_ITRI_STOP
 *         @arg I2C_ITRI_TC
 *         @arg I2C_ITRI_TCR
 *         @arg I2C_ITRI_ERR
 *         @arg I2C_ITRI_ARLO
 *         @arg I2C_ITRI_OVR
 *         @arg I2C_ITRI_PECE
 *         @arg I2C_ITRI_TOUT
 *         @arg I2C_ITRI_ALERT
 * @retval State of bit (1 or 0).
 */
static inline uint32_t LL_I2C_IsActiveFlagIT(reg_i2c_t *I2Cx, uint32_t RegisterBit)
{
    //   LOG_I("flag tx !\n");
    return ((READ_BIT(I2Cx->RIF, RegisterBit) == (RegisterBit)) ? 1UL : 0UL);
}

/******************************************IFM******************************************/
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/******************************************IFM******************************************/
/**
 * @brief  Check if interrupt mask.
 * @param  I2Cx I2C Instance
 * @param RegisterBit  This parameter can be one of the following values:
 *         @arg I2C_ITFM_RXNE
 *         @arg I2C_ITFM_TXE
 *         @arg I2C_ITFM_ADDR
 *         @arg I2C_ITFM_NACK
 *         @arg I2C_ITFM_STOP
 *         @arg I2C_ITFM_TC
 *         @arg I2C_ITFM_TCR
 *         @arg I2C_ITFM_ERR
 *         @arg I2C_ITFM_ARLO
 *         @arg I2C_ITFM_OVR
 *         @arg I2C_ITFM_PECE
 *         @arg I2C_ITFM_TOUT
 *         @arg I2C_ITFM_ALERT
 * @retval State of bit (1 or 0).
 */
static inline uint32_t LL_I2C_IsActiveFlagIT_Mask(reg_i2c_t *I2Cx, uint32_t RegisterBit)
{
    return ((READ_BIT(I2Cx->IFM, RegisterBit) == (RegisterBit)) ? 1UL : 0UL);
}

/******************************************ICR******************************************/
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/******************************************ICR******************************************/
/**
 * @brief  Clear interrupt flag
 * @param  I2Cx I2C Instance
 * @param RegisterBit  This parameter can be one of the following values:
 *         @arg I2C_ITIC_RXNE
 *         @arg I2C_ITIC_TXE
 *         @arg I2C_ITIC_ADDR
 *         @arg I2C_ITIC_NACK
 *         @arg I2C_ITIC_STOP
 *         @arg I2C_ITIC_TC
 *         @arg I2C_ITIC_TCR
 *         @arg I2C_ITIC_ERR
 *         @arg I2C_ITIC_ARLO
 *         @arg I2C_ITIC_OVR
 *         @arg I2C_ITIC_PECE
 *         @arg I2C_ITIC_TOUT
 *         @arg I2C_ITIC_ALERT
 * @retval None
 */
static inline void LL_I2C_ClearFlagIT(reg_i2c_t *I2Cx, uint32_t RegisterBit)
{
    SET_BIT(I2Cx->ICR, RegisterBit);
}

/*******************************************************************************
 End of File
 ******************************************************************************/

/** @}*/

/** @}*/
#endif