#ifndef _LS_LL_SPI_H_
#define _LS_LL_SPI_H_
#include <stdbool.h>
#include "HAL_def.h"
#include "sdk_config.h"
#include "field_manipulate.h"
#include "ls_msp_spi_i2s.h"

/** \addtogroup PERIPHERAL
 *  @{
 */

/** \addtogroup LSSPI
 *  @{
 */

/// SPI CLOCK
#define SPI_CLOCK (SDK_PCLK_MHZ * 1000000)
/******************************************************************************
 External Variable Definition
 ******************************************************************************/
#define LL_SPI_PHASE_1EDGE 0x00000000U         /*!< First clock transition is the first data capture edge  */
#define LL_SPI_PHASE_2EDGE (SPI_CR1_CPHA_MASK) /*!< Second clock transition is the first data capture edge */

#define LL_SPI_POLARITY_LOW 0x00000000U          /*!< Clock to 0 when idle */
#define LL_SPI_POLARITY_HIGH (SPI_CR1_CPOL_MASK) /*!< Clock to 1 when idle */

#define LL_SPI_MODE_MASTER (SPI_CR1_MSTR_MASK | SPI_CR1_SSI_MASK) /*!< Master configuration  */
#define LL_SPI_MODE_SLAVE 0x00000000U                             /*!< Slave configuration   */

#define LL_SPI_PULSE_NONE  0x00000000U 
#define LL_SPI_PULSE_GENERATED SPI_CR2_NSSP_MASK                         

#define LL_SPI_BAUDRATEPRESCALER_8  (0x00000002 << SPI_CR1_BR_POS)   /*!< The BaudRate is 8 frequency of the SPI clock   */
#define LL_SPI_BAUDRATEPRESCALER_16 (0x00000003 << SPI_CR1_BR_POS)  /*!< The BaudRate is 16 frequency of the SPI clock  */
#define LL_SPI_BAUDRATEPRESCALER_32 (0x00000004 << SPI_CR1_BR_POS)  /*!< The BaudRate is 32 frequency of the SPI clock  */
#define LL_SPI_BAUDRATEPRESCALER_64 (0x00000005 << SPI_CR1_BR_POS)  /*!< The BaudRate is 64 frequency of the SPI clock  */
#define LL_SPI_BAUDRATEPRESCALER_128 (0x00000006 << SPI_CR1_BR_POS) /*!< The BaudRate is 128 frequency of the SPI clock */
#define LL_SPI_BAUDRATEPRESCALER_256 (0x00000007 << SPI_CR1_BR_POS) /*!< The BaudRate is 256 frequency of the SPI clock */

#define LL_SPI_LSB_FIRST (SPI_CR1_LSBFIRST_MASK) /*!< Data is transmitted/received with the LSB first */
#define LL_SPI_MSB_FIRST 0x00000000U             /*!< Data is transmitted/received with the MSB first */

#define LL_SPI_NSS_SOFT (SPI_CR1_SSM_MASK)                            /*!< NSS managed internally. NSS pin not used and free              */
#define LL_SPI_NSS_HARD_INPUT 0x00000000U                             /*!< NSS pin used in Input. Only used in Master mode                */
#define LL_SPI_NSS_HARD_OUTPUT (((uint32_t)SPI_CR2_SSOE_MASK << 16U)) /*!< NSS pin used in Output. Only used in Slave mode as chip select */

#define LL_SPI_FULL_DUPLEX 0x00000000U                            /*!< Full-Duplex mode. Rx and Tx transfer on 2 lines */
#define LL_SPI_SIMPLEX_RX (SPI_CR1_RXONLY)                        /*!< Simplex Rx mode.  Rx transfer only on 1 line    */
#define LL_SPI_HALF_DUPLEX_RX (SPI_CR1_BIDIMODE)                  /*!< Half-Duplex Rx mode. Rx transfer on 1 line      */
#define LL_SPI_HALF_DUPLEX_TX (SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE) /*!< Half-Duplex Tx mode. Tx transfer on 1 line      */

#define LL_SPI_DATASIZE_8BIT (0x00000007U << SPI_CR2_DS_POS) /*!< The SPI Data Size is 8BIT     */
#define LL_SPI_DATASIZE_16BIT SPI_CR2_DS_MASK                /*!< The SPI Data Size is 16BIT    */

#define SPI_FLAG_RXNE   SPI_SR_RXNE_MASK
#define SPI_FLAG_TXE    SPI_SR_TXE_MASK
#define SPI_FLAG_UDR    SPI_SR_UDR_MASK
#define SPI_FLAG_CRCERR SPI_SR_CRCERR_MASK
#define SPI_FLAG_MODF   SPI_SR_MODF_MASK
#define SPI_FLAG_OVR    SPI_SR_OVR_MASK
#define SPI_FLAG_BSY    SPI_SR_BSY_MASK
#define SPI_FLAG_FRE    SPI_SR_FRE_MASK
#define SPI_FLAG_TXFLV  SPI_SR_TXFLV_MASK
#define SPI_FLAG_RXFLV  SPI_SR_RXFLV_MASK

#define SPI_ITEN_RXNE   SPI_IER_RXNEIE_MASK
#define SPI_ITEN_TXE    SPI_IER_TXEIE_MASK
#define SPI_ITEN_UDR    SPI_IER_UDRIE_MASK
#define SPI_ITEN_CRCERR SPI_IER_CRCERRIE_MASK
#define SPI_ITEN_MODF   SPI_IER_MODFIE_MASK
#define SPI_ITEN_OVR    SPI_IER_OVRIE_MASK
#define SPI_ITEN_FRE    SPI_IER_FREIE_MASK

#define SPI_ITDEN_RXNE  SPI_IDR_RXNEID_MASK
#define SPI_ITDEN_TXE   SPI_IDR_TXEID_MASK
#define SPI_ITDEN_UDR   SPI_IDR_UDRID_MASK
#define SPI_ITDEN_CRCERR SPI_IDR_CRCERRID_MASK
#define SPI_ITDEN_MODF  SPI_IDR_MODFID_MASK
#define SPI_ITDEN_OVR   SPI_IDR_OVRID_MASK
#define SPI_ITDEN_FRE   SPI_IDR_FREID_MASK

#define SPI_ITVS_RXNE   SPI_IVS_RXNEIV_MASK
#define SPI_ITVS_TXE    SPI_IVS_TXEIV_MASK
#define SPI_ITVS_UDR    SPI_IVS_UDRIV_MASK
#define SPI_ITVS_CRCERR SPI_IVS_CRCERRIV_MASK
#define SPI_ITVS_MODF   SPI_IVS_MODFIV_MASK
#define SPI_ITVS_OVR    SPI_IVS_OVRIV_MASK
#define SPI_ITVS_FRE    SPI_IVS_FREIV_MASK

#define SPI_ITRI_RXNE   SPI_RIF_RXNERI_MASK
#define SPI_ITRI_TXE    SPI_RIF_TXERI_MASK
#define SPI_ITRI_UDR    SPI_RIF_UDRRI_MASK
#define SPI_ITRI_CRCERR SPI_RIF_CRCERRRI_MASK
#define SPI_ITRI_MODF   SPI_RIF_MODFRI_MASK
#define SPI_ITRI_OVR    SPI_RIF_OVRRI_MASK
#define SPI_ITRI_FRE    SPI_RIF_FRERI_MASK

#define SPI_ITFM_RXNE   SPI_IFM_RXNEFM_MASK
#define SPI_ITFM_TXE    SPI_IFM_TXEFM_MASK
#define SPI_ITFM_UDR    SPI_IFM_UDRFM_MASK
#define SPI_ITFM_CRCERR SPI_IFM_CRCERRFM_MASK
#define SPI_ITFM_MODF   SPI_IFM_MODFFM_MASK
#define SPI_ITFM_OVR    SPI_IFM_OVRFM_MASK
#define SPI_ITFM_FRE    SPI_IFM_FREFM_MASK

#define SPI_ITIC_RXNE   SPI_ICR_RXNEIC_MASK
#define SPI_ITIC_TXE    SPI_ICR_TXEIC_MASK
#define SPI_ITIC_UDR    SPI_IDR_UDRID_MASK
#define SPI_ITIC_CRCERR SPI_ICR_CRCERRIC_MASK
#define SPI_ITIC_MODF   SPI_ICR_MODFIC_MASK
#define SPI_ITIC_OVR    SPI_ICR_OVRIC_MASK
#define SPI_ITIC_FRE    SPI_ICR_FREIC_MASK

/******************************************************************************
 External Function Definition
 ******************************************************************************/
/******************************************CR1******************************************/
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/******************************************CR1******************************************/
/**
 * @brief  Set clock phase
 * @note   This bit should not be changed when communication is ongoing.
 *         This bit is not used in SPI TI mode.
 * @param  SPIx SPI Instance
 * @param  ClockPhase This parameter can be one of the following values:
 *        @arg LL_SPI_PHASE_1EDGE
 *        @arg LL_SPI_PHASE_2EDGE
 * @retval None
 */
static inline void LL_SPI_SetClockPhase(reg_spi_t *SPIx, uint32_t ClockPhase)
{
    MODIFY_REG(SPIx->CR1, SPI_CR1_CPHA_MASK, ClockPhase);
}

/**
 * @brief  Get clock phase
 * @param  SPIx SPI Instance
 * @retval Returned value can be one of the following values:
 *        @arg LL_SPI_PHASE_1EDGE
 *        @arg LL_SPI_PHASE_2EDGE
 */
static inline uint32_t LL_SPI_GetClockPhase(reg_spi_t *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_CPHA_MASK));
}

/**
 * @brief  Set clock polarity
 * @note   This bit should not be changed when communication is ongoing.
 *         This bit is not used in SPI TI mode.
 * @param  SPIx SPI Instance
 * @param  ClockPolarity This parameter can be one of the following values:
 *        @arg LL_SPI_POLARITY_LOW
 *        @arg LL_SPI_POLARITY_HIGH
 * @retval None
 */
static inline void LL_SPI_SetClockPolarity(reg_spi_t *SPIx, uint32_t ClockPolarity)
{
    MODIFY_REG(SPIx->CR1, SPI_CR1_CPOL_MASK, ClockPolarity);
}

/**
 * @brief  Get clock polarity
 * @param  SPIx SPI Instance
 * @retval Returned value can be one of the following values:
 *        @arg LL_SPI_POLARITY_LOW
 *        @arg LL_SPI_POLARITY_HIGH
 */
static inline uint32_t LL_SPI_GetClockPolarity(reg_spi_t *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_CPOL_MASK));
}

/**
 * @brief  Set SPI operation mode to Master or Slave
 * @note   This bit should not be changed when communication is ongoing.      
 * @param  SPIx SPI Instance
 * @param  Mode This parameter can be one of the following values:
 *        @arg LL_SPI_MODE_MASTER
 *        @arg LL_SPI_MODE_SLAVE
 * @retval None
 */
static inline void LL_SPI_SetMode(reg_spi_t *SPIx, uint32_t Mode)
{
    MODIFY_REG(SPIx->CR1, SPI_CR1_MSTR_MASK | SPI_CR1_SSI_MASK, Mode);
}

/**
 * @brief  Get SPI operation mode (Master or Slave)
 * @param  SPIx SPI Instance
 * @retval Returned value can be one of the following values:
 *        @arg LL_SPI_MODE_MASTER
 *        @arg LL_SPI_MODE_SLAVE
 */
static inline uint32_t LL_SPI_GetMode(reg_spi_t *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->CR1, (SPI_CR1_MSTR_MASK | SPI_CR1_SSI_MASK)));
}

/**
 * @brief  Set baud rate prescaler
 * @note   These bits should not be changed when communication is ongoing. SPI BaudRate = fPCLK/Prescaler.
 * @param  SPIx SPI Instance
 * @param  BaudRate This parameter can be one of the following values:
 *        @arg SPI_BAUDRATEPRESCALER_8
 *        @arg SPI_BAUDRATEPRESCALER_16
 *        @arg SPI_BAUDRATEPRESCALER_32
 *        @arg SPI_BAUDRATEPRESCALER_64
 *        @arg SPI_BAUDRATEPRESCALER_128
 *        @arg SPI_BAUDRATEPRESCALER_256

 * @retval None
 */
static inline void LL_SPI_SetBaudRatePrescaler(reg_spi_t *SPIx, uint32_t BaudRate)
{
    MODIFY_REG(SPIx->CR1, SPI_CR1_BR_MASK, BaudRate);
}

/**
 * @brief  Get baud rate prescaler
 * @param  SPIx SPI Instance
 * @retval Returned value can be one of the following values:
 *        @arg SPI_BAUDRATEPRESCALER_8
 *        @arg SPI_BAUDRATEPRESCALER_16
 *        @arg SPI_BAUDRATEPRESCALER_32
 *        @arg SPI_BAUDRATEPRESCALER_64
 *        @arg SPI_BAUDRATEPRESCALER_128
 *        @arg SPI_BAUDRATEPRESCALER_256
 */
static inline uint32_t LL_SPI_GetBaudRatePrescaler(reg_spi_t *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_BR_MASK));
}

/**
 * @brief  Enable SPI peripheral
 * @param  SPIx SPI Instance
 * @retval None
 */
static inline void LL_SPI_Enable(reg_spi_t *SPIx)
{
    SET_BIT(SPIx->CR1, SPI_CR1_SPE_MASK);
}

/**
 * @brief  Disable SPI peripheral
 * @note   When disabling the SPI, follow the procedure described in the Reference Manual.
 * @param  SPIx SPI Instance
 * @retval None
 */
static inline void LL_SPI_Disable(reg_spi_t *SPIx)
{
    CLEAR_BIT(SPIx->CR1, SPI_CR1_SPE_MASK);
}

/**
 * @brief  Check if SPI peripheral is enabled
 * @param  SPIx SPI Instance
 * @retval State of bit (1 or 0).
 */
static inline uint32_t LL_SPI_IsEnabled(reg_spi_t *SPIx)
{
    return ((READ_BIT(SPIx->CR1, SPI_CR1_SPE_MASK) == (SPI_CR1_SPE_MASK)) ? 1UL : 0UL);
}

/**
 * @brief  Set transfer bit order
 * @note   This bit should not be changed when communication is ongoing. This bit is not used in SPI TI mode.
 * @param  SPIx SPI Instance
 * @param  BitOrder This parameter can be one of the following values:
 *        @arg LL_SPI_LSB_FIRST
 *        @arg LL_SPI_MSB_FIRST
 * @retval None
 */
static inline void LL_SPI_SetTransferBitOrder(reg_spi_t *SPIx, uint32_t BitOrder)
{
    MODIFY_REG(SPIx->CR1, SPI_CR1_LSBFIRST_MASK, BitOrder);
}

/**
 * @brief  Get transfer bit order
 * @param  SPIx SPI Instance
 * @retval Returned value can be one of the following values:
 *        @arg LL_SPI_LSB_FIRST
 *        @arg LL_SPI_MSB_FIRST
 */
static inline uint32_t LL_SPI_GetTransferBitOrder(reg_spi_t *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_LSBFIRST_MASK));
}

/**
 * @brief  Set NSS mode
 * @note   LL_SPI_NSS_SOFT Mode is not used in SPI TI mode.
 * @param  SPIx SPI Instance
 * @param  NSS This parameter can be one of the following values:
 *        @arg LL_SPI_NSS_SOFT
 *        @arg LL_SPI_NSS_HARD_INPUT
 *        @arg LL_SPI_NSS_HARD_OUTPUT
 * @retval None
 */
static inline void LL_SPI_SetNSSMode(reg_spi_t *SPIx, uint32_t NSS)
{
    SET_BIT(SPIx->CR1, SPI_CR1_SSM_MASK & NSS);
    WRITE_REG(SPIx->CR2, ((NSS >> 16U) & SPI_CR2_SSOE_MASK));
}

/**
 * @brief  Get NSS mode
 * @param  SPIx SPI Instance
 * @retval Returned value can be one of the following values:
 *        @arg LL_SPI_NSS_SOFT
 *        @arg LL_SPI_NSS_HARD_INPUT
 *        @arg LL_SPI_NSS_HARD_OUTPUT
 */
static inline uint32_t LL_SPI_GetNSSMode(reg_spi_t *SPIx)
{
    uint32_t Ssm = (READ_BIT(SPIx->CR1, SPI_CR1_SSM_MASK));
    uint32_t Ssoe = (READ_BIT(SPIx->CR2, SPI_CR2_SSOE_MASK) << 16U);
    return (Ssm | Ssoe);
}

/**
 * @brief  Set transfer direction mode
 * @note   For LLf-Duplex mode, Rx Direction is set by default.
 *         In master mode, the MOSI pin is used and in slave mode, the MISO pin is used for LLf-Duplex.
 * @param  SPIx SPI Instance
 * @param  TransferDirection This parameter can be one of the following values:
 *        @arg LL_SPI_FULL_DUPLEX
 *        @arg LL_SPI_SIMPLEX_RX
 *        @arg LL_SPI_LLF_DUPLEX_RX
 *        @arg LL_SPI_LLF_DUPLEX_TX
 * @retval None
 */
static inline void LL_SPI_SetTransferDirection(reg_spi_t *SPIx, uint32_t TransferDirection)
{
    MODIFY_REG(SPIx->CR1, SPI_CR1_RXONLY_MASK | SPI_CR1_BIDIMODE_MASK | SPI_CR1_BIDIOE_MASK, TransferDirection);
}

/**
 * @brief  Get transfer direction mode
 * @param  SPIx SPI Instance
 * @retval Returned value can be one of the following values:
 *        @arg LL_SPI_FULL_DUPLEX
 *        @arg LL_SPI_SIMPLEX_RX
 *        @arg LL_SPI_LLF_DUPLEX_RX
 *        @arg LL_SPI_LLF_DUPLEX_TX
 */
static inline uint32_t LL_SPI_GetTransferDirection(reg_spi_t *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_RXONLY_MASK | SPI_CR1_BIDIMODE_MASK | SPI_CR1_BIDIOE_MASK));
}

/**
 * @brief  Set frame data width
 * @param  SPIx SPI Instance
 * @param  CRCLength This parameter can be one of the following values:
 *        @arg LL_SPI_DATAWIDTH_8BIT
 *        @arg LL_SPI_DATAWIDTH_16BIT
 * @retval None
 */
static inline void LL_SPI_SetCRCLength(reg_spi_t *SPIx, uint32_t CRCLength)
{
    MODIFY_REG(SPIx->CR1, SPI_CR1_CRCL_MASK, CRCLength);
}

/**
 * @brief  Get frame data width
 * @param  SPIx SPI Instance
 * @retval Returned value can be one of the following values:
 *        @arg LL_SPI_DATAWIDTH_8BIT
 *        @arg LL_SPI_DATAWIDTH_16BIT
 */
static inline uint32_t LL_SPI_GetCRCLength(reg_spi_t *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_CRCL_MASK));
}

/**
 * @brief  Enable CRC
 * @note   This bit should be written only when SPI is disabled (SPE = 0) for correct operation.
 * @param  SPIx SPI Instance
 * @retval None
 */
static inline void LL_SPI_EnableCRC(reg_spi_t *SPIx)
{
    SET_BIT(SPIx->CR1, SPI_CR1_CRCEN_MASK);
}

/**
 * @brief  Disable CRC
 * @note   This bit should be written only when SPI is disabled (SPE = 0) for correct operation.
 * @param  SPIx SPI Instance
 * @retval None
 */
static inline void LL_SPI_DisableCRC(reg_spi_t *SPIx)
{
    CLEAR_BIT(SPIx->CR1, SPI_CR1_CRCEN_MASK);
}

/**
 * @brief  Check if CRC is enabled
 * @note   This bit should be written only when SPI is disabled (SPE = 0) for correct operation.
 * @param  SPIx SPI Instance
 * @retval State of bit (1 or 0).
 */
static inline uint32_t LL_SPI_IsEnabledCRC(reg_spi_t *SPIx)
{
    return ((READ_BIT(SPIx->CR1, SPI_CR1_CRCEN_MASK) == (SPI_CR1_CRCEN_MASK)) ? 1UL : 0UL);
}

/**
 * @brief  Set CRCNext to transfer CRC on the line
 * @note   This bit has to be written as soon as the last data is written in the SPIx_DR register.
 * @param  SPIx SPI Instance
 * @retval None
 */
static inline void LL_SPI_SetCRCNext(reg_spi_t *SPIx)
{
    SET_BIT(SPIx->CR1, SPI_CR1_CRCNEXT_MASK);
}

/**
 * @brief  Set polynomial for CRC calculation
 * @param  SPIx SPI Instance
 * @param  CRCPoly This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFFFF
 * @retval None
 */
static inline void LL_SPI_SetCRCPolynomial(reg_spi_t *SPIx, uint32_t CRCPoly)
{
    WRITE_REG(SPIx->CRCPR, (uint16_t)CRCPoly);
}

/**
 * @brief  Get polynomial for CRC calculation
 * @param  SPIx SPI Instance
 * @retval Returned value is a number between Min_Data = 0x00 and Max_Data = 0xFFFF
 */
static inline uint32_t LL_SPI_GetCRCPolynomial(reg_spi_t *SPIx)
{
    return (uint32_t)(READ_REG(SPIx->CRCPR));
}

/**
 * @brief  Get Rx CRC
 * @param  SPIx SPI Instance
 * @retval Returned value is a number between Min_Data = 0x00 and Max_Data = 0xFFFF
 */
static inline uint32_t LL_SPI_GetRxCRC(reg_spi_t *SPIx)
{
    return (uint32_t)(READ_REG(SPIx->RXCRCR));
}

/**
 * @brief  Get Tx CRC
 * @param  SPIx SPI Instance
 * @retval Returned value is a number between Min_Data = 0x00 and Max_Data = 0xFFFF
 */
static inline uint32_t LL_SPI_GetTxCRC(reg_spi_t *SPIx)
{
    return (uint32_t)(READ_REG(SPIx->TXCRCR));
}

/******************************************CR2******************************************/
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/******************************************CR2******************************************/

/**
 * @brief  Enable DMA Rx
 * @param  SPIx SPI Instance
 * @retval None
 */
static inline void LL_SPI_EnableDMAReq_RX(reg_spi_t *SPIx)
{
    SET_BIT(SPIx->CR2, SPI_CR2_RXDMAEN_MASK);
}

/**
 * @brief  Disable DMA Rx
 * @param  SPIx SPI Instance
 * @retval None
 */
static inline void LL_SPI_DisableDMAReq_RX(reg_spi_t *SPIx)
{
    CLEAR_BIT(SPIx->CR2, SPI_CR2_RXDMAEN_MASK);
}

/**
 * @brief  Check if DMA Rx is enabled
 * @param  SPIx SPI Instance
 * @retval State of bit (1 or 0).
 */
static inline uint32_t LL_SPI_IsEnabledDMAReq_RX(reg_spi_t *SPIx)
{
    return ((READ_BIT(SPIx->CR2, SPI_CR2_RXDMAEN_MASK) == (SPI_CR2_RXDMAEN_MASK)) ? 1UL : 0UL);
}

/**
 * @brief  Enable DMA Tx
 * @param  SPIx SPI Instance
 * @retval None
 */
static inline void LL_SPI_EnableDMAReq_TX(reg_spi_t *SPIx)
{
    SET_BIT(SPIx->CR2, SPI_CR2_TXDMAEN_MASK);
}

/**
 * @brief  Disable DMA Tx
 * @param  SPIx SPI Instance
 * @retval None
 */
static inline void LL_SPI_DisableDMAReq_TX(reg_spi_t *SPIx)
{
    CLEAR_BIT(SPIx->CR2, SPI_CR2_TXDMAEN_MASK);
}

/**
 * @brief  Check if DMA Tx is enabled
 * @param  SPIx SPI Instance
 * @retval State of bit (1 or 0).
 */
static inline uint32_t LL_SPI_IsEnabledDMAReq_TX(reg_spi_t *SPIx)
{
    return ((READ_BIT(SPIx->CR2, SPI_CR2_TXDMAEN_MASK) == (SPI_CR2_TXDMAEN_MASK)) ? 1UL : 0UL);
}

/**
 * @brief  Set if pulse is generated
 * @note   This bit should not be changed when communication is ongoing.
 *         This bit is not used in SPI TI mode.
 * @param  SPIx SPI Instance
 * @param  pulse This parameter can be one of the following values:
 *        @arg LL_SPI_PULSE_NONE
 *        @arg LL_SPI_PULSE_GENERATED
 * @retval None
 */
static inline void LL_SPI_SetNSSP(reg_spi_t *SPIx, uint32_t pulse)
{
    MODIFY_REG(SPIx->CR2, SPI_CR2_NSSP_MASK, pulse);
}

/**
 * @brief  Get if pulse is generated
 * @param  SPIx SPI Instance
 * @retval Returned value can be one of the following values:
 *        @arg LL_SPI_PULSE_NONE
 *        @arg LL_SPI_PULSE_GENERATED
 */
static inline uint32_t LL_SPI_GetNSSP(reg_spi_t *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->CR2, SPI_CR2_NSSP_MASK));
}

/**
 * @brief  Set serial protocol used
 * @note   This bit should be written only when SPI is disabled (SPE = 0) for correct operation.
 * @param  SPIx SPI Instance
 * @param  FrameFormat This parameter can be one of the following values:
 *        @arg LL_SPI_PROTOCOL_MOTOROLA
 *        @arg LL_SPI_PROTOCOL_TI
 * @retval None
 */
static inline void LL_SPI_SetFrameFormat(reg_spi_t *SPIx, uint32_t FrameFormat)
{
    MODIFY_REG(SPIx->CR2, SPI_CR2_FRF_MASK, FrameFormat);
}

/**
 * @brief  Get serial protocol used
 * @param  SPIx SPI Instance
 * @retval Returned value can be one of the following values:
 *        @arg LL_SPI_PROTOCOL_MOTOROLA
 *        @arg LL_SPI_PROTOCOL_TI
 */
static inline uint32_t LL_SPI_GetFrameFormat(reg_spi_t *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->CR2, SPI_CR2_FRF_MASK));
}

/**
 * @brief
 * @param  SPIx SPI Instance
 * @param  DataSize This parameter can be one of the following values:
 *        @arg SPI_DATASIZE_8BIT
 *        @arg SPI_DATASIZE_16BIT
 * @retval None
 */
static inline void LL_SPI_SetDataSize(reg_spi_t *SPIx, uint32_t DataSize)
{
    MODIFY_REG(SPIx->CR2, SPI_CR2_DS_MASK, DataSize);
}

/**
 * @brief
 * @param  SPIx SPI Instance
 * @retval Returned value can be one of the following values:
 *        @arg SPI_DATASIZE_8BIT
 *        @arg SPI_DATASIZE_16BIT
 */
static inline uint32_t LL_SPI_GetDataSize(reg_spi_t *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->CR2, SPI_CR2_DS_MASK));
}

/**
 * @brief Set Send the FIFO triggers the TXE status threshold
 * @param SPIx  SPI Instance
 * @param TxFifoThreshoid  Value between Min_Data=0x0 and Max_Data=0xf
 */
static inline void LL_SPI_SetTxFifoThreshoid(reg_spi_t *SPIx, uint32_t TxFifoThreshoid)
{
    MODIFY_REG(SPIx->CR2, SPI_CR2_TXFTH_MASK, TxFifoThreshoid);
}

/**
 * @brief Get Send the FIFO triggers the TXE status threshold
 * @param SPIx  SPI Instance
 * @retval RxData Value between Min_Data=0x00 and Max_Data=0xF
 */
static inline uint32_t LL_SPI_GetTxFifoThreshoid(reg_spi_t *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->CR2, SPI_CR2_TXFTH_MASK) >> SPI_CR2_TXFTH_POS);
}

/**
 * @brief Set recrption the FIFO triggers the TXE status threshold
 * @param SPIx  SPI Instance
 * @param RxFifoThreshoid  Value between Min_Data=0x0 and Max_Data=0xf
 */
static inline void LL_SPI_SetRxFifoThreshoid(reg_spi_t *SPIx, uint32_t RxFifoThreshoid)
{
    MODIFY_REG(SPIx->CR2, SPI_CR2_RXFTH_MASK, RxFifoThreshoid);
}

/**
 * @brief Get recrption the FIFO triggers the TXE status threshold
 * @param SPIx  SPI Instance
 * @retval RxData Value between Min_Data=0x00 and Max_Data=0xF
 */
static inline uint32_t LL_SPI_GetRxFifoThreshoid(reg_spi_t *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->CR2, SPI_CR2_RXFTH_MASK) >> SPI_CR2_RXFTH_POS);
}

/******************************************SR*******************************************/
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/******************************************SR*******************************************/
/**
 * @brief  Check SR Flag
 * @param  SPIx SPI Instance
 * @param RegisterBit  This parameter can be one of the following values:
 *        @arg SPI_FLAG_RXNE
 *        @arg SPI_FLAG_TXE
 *        @arg SPI_FLAG_UDR
 *        @arg SPI_FLAG_CRCERR
 *        @arg SPI_FLAG_MODF
 *        @arg SPI_FLAG_OVR
 *        @arg SPI_FLAG_BSY
 *        @arg SPI_FLAG_FRE
 *        @arg SPI_FLAG_TXFLV
 *        @arg SPI_FLAG_RXFLV
 * @retval State of bit (1 or 0).
 */
static inline uint32_t LL_SPI_IsActiveFlag(reg_spi_t *SPIx, uint32_t RegisterBit)
{
    return ((READ_BIT(SPIx->SR, RegisterBit) == (RegisterBit)) ? 1UL : 0UL);
}
/******************************************DR*******************************************/
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/******************************************DR*******************************************/
/**
 * @brief  Get the data register address used for DMA transfer
 * @param  SPIx SPI Instance
 * @retval Address of data register
 */
static inline uint32_t LL_SPI_DMA_GetRegAddr(reg_spi_t *SPIx)
{
    return (uint32_t) & (SPIx->DR);
}

/**
 * @brief  Read 8-Bits in the data register
 * @param  SPIx SPI Instance
 * @retval RxData Value between Min_Data=0x00 and Max_Data=0xFF
 */
static inline uint8_t LL_SPI_ReceiveData8(reg_spi_t *SPIx)
{
    return (*(uint8_t *)&SPIx->DR);
}

/**
 * @brief  Read 16-Bits in the data register
 * @param  SPIx SPI Instance
 * @retval RxData Value between Min_Data=0x00 and Max_Data=0xFFFF
 */
static inline uint16_t LL_SPI_ReceiveData16(reg_spi_t *SPIx)
{
    return (uint16_t)(READ_REG(SPIx->DR));
}

/**
 * @brief  Write 8-Bits in the data register
 * @param  SPIx SPI Instance
 * @param  TxData Value between Min_Data=0x00 and Max_Data=0xFF
 * @retval None
 */
static inline void LL_SPI_TransmitData8(reg_spi_t *SPIx, uint8_t TxData)
{
    *((uint8_t *)&SPIx->DR) = TxData;
}

/**
 * @brief  Write 16-Bits in the data register
 * @param  SPIx SPI Instance
 * @param  TxData Value between Min_Data=0x00 and Max_Data=0xFFFF
 * @retval None
 */
static inline void LL_SPI_TransmitData16(reg_spi_t *SPIx, uint16_t TxData)
{
    SPIx->DR = TxData;
}
/******************************************LL_I2S*******************************************/
/*                                                                                         */
/*                                                                                         */
/*                                                                                         */
/*                                                                                         */
/******************************************LL_I2S*******************************************/

enum ll_spi_data_format
{
    LL_I2S_DATAFORMAT_16B = 0,
    LL_I2S_DATAFORMAT_16B_EXTENDED = (SPI_I2SCFGR_CHLEN_MASK),
    LL_I2S_DATAFORMAT_24B = (SPI_I2SCFGR_CHLEN_MASK | 0X00000002),
    LL_I2S_DATAFORMAT_32B = (SPI_I2SCFGR_CHLEN_MASK | 0X00000004)
};

enum ll_spi_clock_polarity
{
    LL_I2S_POLARITY_LOW = 0,
    LL_I2S_POLARITY_HIGH = (SPI_I2SCFGR_CKPOL_MASK),
};

enum ll_spi_Standard
{
    LL_I2S_STANDARD_PHILIPS = 0,
    LL_I2S_STANDARD_MSB = 0x00000010,
    LL_I2S_STANDARD_LSB = 0x00000020,
    LL_I2S_STANDARD_PCM_SHORT = 0x00000030,
    LL_I2S_STANDARD_PCM_LONG = (0x00000030 | SPI_I2SCFGR_PCMSYNC_MASK)
};

enum ll_spi_operation_mode
{
    LL_I2S_MODE_SLAVE_TX = 0x00000000,
    LL_I2S_MODE_SLAVE_RX = 0x00000100,
    LL_I2S_MODE_MASTER_TX = 0x00000200,
    LL_I2S_MODE_MASTER_RX = (SPI_I2SCFGR_I2SCFG_MASK)
};

enum ll_spi_prescaler_factor
{
    LL_I2S_PRESCALER_PARITY_EVEN = 0x00000000U,
    LL_I2S_PRESCALER_PARITY_ODD = (SPI_I2SPR_ODD_MASK >> 8U),

};
/**
 * @brief  Select I2S mode and Enable I2S peripheral
 * @param  SPIx SPI Instance
 * @retval None
 */
static inline void
LL_I2S_Enable(reg_spi_t *SPIx)
{
    SET_BIT(SPIx->I2SCFGR, SPI_I2SCFGR_I2SMOD_MASK | SPI_I2SCFGR_I2SE_MASK);
}

/**
 * @brief  Disable I2S peripheral
 * @param  SPIx SPI Instance
 * @retval None
 */
static inline void LL_I2S_Disable(reg_spi_t *SPIx)
{
    CLEAR_BIT(SPIx->I2SCFGR, SPI_I2SCFGR_I2SMOD_MASK | SPI_I2SCFGR_I2SE_MASK);
}

/**
 * @brief  Check if I2S peripheral is enabled
 * @param  SPIx SPI Instance
 * @retval State of bit (1 or 0).
 */
static inline uint32_t LL_I2S_IsEnabled(reg_spi_t *SPIx)
{
    return ((READ_BIT(SPIx->I2SCFGR, SPI_I2SCFGR_I2SE_MASK) == (SPI_I2SCFGR_I2SE_MASK)) ? 1UL : 0UL);
}

/**
 * @brief  Set I2S data frame length
 * @param  SPIx SPI Instance
 * @param  DataFormat This parameter can be one of the following values:
 *        @arg LL_I2S_DATAFORMAT_16B
 *        @arg LL_I2S_DATAFORMAT_16B_EXTENDED
 *        @arg LL_I2S_DATAFORMAT_24B
 *        @arg LL_I2S_DATAFORMAT_32B
 * @retval None
 */
static inline void LL_I2S_SetDataFormat(reg_spi_t *SPIx, uint32_t DataFormat)
{
    MODIFY_REG(SPIx->I2SCFGR, SPI_I2SCFGR_DATLEN_MASK | SPI_I2SCFGR_CHLEN_MASK, DataFormat);
}

/**
 * @brief  Get I2S data frame length
 * @param  SPIx SPI Instance
 * @retval Returned value can be one of the following values:
 *        @arg LL_I2S_DATAFORMAT_16B
 *        @arg LL_I2S_DATAFORMAT_16B_EXTENDED
 *        @arg LL_I2S_DATAFORMAT_24B
 *        @arg LL_I2S_DATAFORMAT_32B
 */
static inline uint32_t LL_I2S_GetDataFormat(reg_spi_t *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->I2SCFGR, SPI_I2SCFGR_DATLEN_MASK | SPI_I2SCFGR_CHLEN_MASK));
}

/**
 * @brief  Set I2S clock polarity
 * @param  SPIx SPI Instance
 * @param  ClockPolarity This parameter can be one of the following values:
 *        @arg LL_I2S_POLARITY_LOW
 *        @arg LL_I2S_POLARITY_HIGH
 * @retval None
 */
static inline void LL_I2S_SetClockPolarity(reg_spi_t *SPIx, uint32_t ClockPolarity)
{
    SET_BIT(SPIx->I2SCFGR, ClockPolarity);
}

/**
 * @brief  Get I2S clock polarity
 * @param  SPIx SPI Instance
 * @retval Returned value can be one of the following values:
 *        @arg LL_I2S_POLARITY_LOW
 *        @arg LL_I2S_POLARITY_HIGH
 */
static inline uint32_t LL_I2S_GetClockPolarity(reg_spi_t *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->I2SCFGR, SPI_I2SCFGR_CKPOL_MASK));
}

/**
 * @brief  Set I2S standard protocol
 * @param  SPIx SPI Instance
 * @param  Standard This parameter can be one of the following values:
 *        @arg LL_I2S_STANDARD_PHILIPS
 *        @arg LL_I2S_STANDARD_MSB
 *        @arg LL_I2S_STANDARD_LSB
 *        @arg LL_I2S_STANDARD_PCM_SHORT
 *        @arg LL_I2S_STANDARD_PCM_LONG
 * @retval None
 */
static inline void LL_I2S_SetStandard(reg_spi_t *SPIx, uint32_t Standard)
{
    MODIFY_REG(SPIx->I2SCFGR, SPI_I2SCFGR_I2SSTD_MASK | SPI_I2SCFGR_PCMSYNC_MASK, Standard);
}

/**
 * @brief  Get I2S standard protocol
 * @param  SPIx SPI Instance
 * @retval Returned value can be one of the following values:
 *        @arg LL_I2S_STANDARD_PHILIPS
 *        @arg LL_I2S_STANDARD_MSB
 *        @arg LL_I2S_STANDARD_LSB
 *        @arg LL_I2S_STANDARD_PCM_SHORT
 *        @arg LL_I2S_STANDARD_PCM_LONG
 */
static inline uint32_t LL_I2S_GetStandard(reg_spi_t *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->I2SCFGR, SPI_I2SCFGR_I2SSTD_MASK | SPI_I2SCFGR_PCMSYNC_MASK));
}

/**
 * @brief  Set I2S transfer mode
 * @param  SPIx SPI Instance
 * @param  Mode This parameter can be one of the following values:
 *        @arg LL_I2S_MODE_SLAVE_TX
 *        @arg LL_I2S_MODE_SLAVE_RX
 *        @arg LL_I2S_MODE_MASTER_TX
 *        @arg LL_I2S_MODE_MASTER_RX
 * @retval None
 */
static inline void LL_I2S_SetTransferMode(reg_spi_t *SPIx, uint32_t Mode)
{
    MODIFY_REG(SPIx->I2SCFGR, SPI_I2SCFGR_I2SCFG_MASK, Mode);
}

/**
 * @brief  Get I2S transfer mode
 * @param  SPIx SPI Instance
 * @retval Returned value can be one of the following values:
 *        @arg LL_I2S_MODE_SLAVE_TX
 *        @arg LL_I2S_MODE_SLAVE_RX
 *        @arg LL_I2S_MODE_MASTER_TX
 *        @arg LL_I2S_MODE_MASTER_RX
 */
static inline uint32_t LL_I2S_GetTransferMode(reg_spi_t *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->I2SCFGR, SPI_I2SCFGR_I2SCFG_MASK));
}
/******************************************I2SPR*******************************************/
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/*                                                                                        */
/******************************************I2SPR*******************************************/

/**
 * @brief  Get I2S linear prescaler
 * @param  SPIx SPI Instance
 * @retval PrescalerLinear Value between Min_Data=0x02 and Max_Data=0xFF
 */
static inline uint32_t LL_I2S_GetPrescalerLinear(reg_spi_t *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->I2SPR, SPI_I2SPR_I2SDIV_MASK));
}

/**
 * @brief  Set I2S parity prescaler
 * @param  SPIx SPI Instance
 * @param  PrescalerParity This parameter can be one of the following values:
 *        @arg LL_I2S_PRESCALER_PARITY_EVEN
 *        @arg LL_I2S_PRESCALER_PARITY_ODD
 * @retval None
 */
static inline void LL_I2S_SetPrescalerParity(reg_spi_t *SPIx, uint32_t PrescalerParity)
{
    MODIFY_REG(SPIx->I2SPR, SPI_I2SPR_ODD_MASK, PrescalerParity << 8U);
}

/**
 * @brief  Get I2S parity prescaler
 * @param  SPIx SPI Instance
 * @retval Returned value can be one of the following values:
 *        @arg LL_I2S_PRESCALER_PARITY_EVEN
 *        @arg LL_I2S_PRESCALER_PARITY_ODD
 */
static inline uint32_t LL_I2S_GetPrescalerParity(reg_spi_t *SPIx)
{
    return (uint32_t)(READ_BIT(SPIx->I2SPR, SPI_I2SPR_ODD_MASK) >> 8U);
}

/**
 * @brief  Enable the master clock output (Pin MCK)
 * @param  SPIx SPI Instance
 * @retval None
 */
static inline void LL_I2S_EnableMasterClock(reg_spi_t *SPIx)
{
    SET_BIT(SPIx->I2SPR, SPI_I2SPR_MCKOE_MASK);
}

/**
 * @brief  Disable the master clock output (Pin MCK)
 * @param  SPIx SPI Instance
 * @retval None
 */
static inline void LL_I2S_DisableMasterClock(reg_spi_t *SPIx)
{
    CLEAR_BIT(SPIx->I2SPR, SPI_I2SPR_MCKOE_MASK);
}

static inline void LL_I2S_EnableExternalClock(reg_spi_t *SPIx)
{
    SET_BIT(SPIx->I2SPR, SPI_I2SPR_EXTCKEN_MASK);
}

static inline void LL_I2S_DisableExternalClock(reg_spi_t *SPIx)
{
    CLEAR_BIT(SPIx->I2SPR, SPI_I2SPR_EXTCKEN_MASK);
}


/******************************************IER******************************************/
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/******************************************IER******************************************/

/**
 * @brief  Enable interrupt
 * @param  SPIx SPI Instance
 * @param  RegisterBit This parameter can be one of the following values:
 *        @arg SPI_ITEN_RXNE
 *        @arg SPI_ITEN_TXE
 *        @arg SPI_ITEN_UDR
 *        @arg SPI_ITEN_CRCERR
 *        @arg SPI_ITEN_MODF
 *        @arg SPI_ITEN_OVR
 *        @arg SPI_ITEN_FRE
 * @retval None
 */
static inline void LL_I2S_EnableIT(reg_spi_t *SPIx, uint32_t RegisterBit)
{
    SET_BIT(SPIx->IER, RegisterBit);
}

/******************************************IDR******************************************/
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/******************************************IDR******************************************/
/**
 * @brief  Disable interrupt 
 * @param  SPIx SPI Instance
 * @param  RegisterBit This parameter can be one of the following values:
 *        @arg SPI_ITDEN_RXNE
 *        @arg SPI_ITDEN_TXE
 *        @arg SPI_ITDEN_UDR
 *        @arg SPI_ITDEN_CRCERR
 *        @arg SPI_ITDEN_MODF
 *        @arg SPI_ITDEN_OVR
 *        @arg SPI_ITDEN_FRE
 * @retval None
 */
static inline void LL_SPI_DisableIT(reg_spi_t *SPIx, uint32_t RegisterBit)
{
    SET_BIT(SPIx->IDR, RegisterBit);
}
/******************************************IVS******************************************/
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/******************************************IVS******************************************/
/**
 * @brief  Check if interrupt is enabled
 * @param  SPIx SPI Instance
 * @param  RegisterBit This parameter can be one of the following values:
 *        @arg SPI_ITVS_RXNE
 *        @arg SPI_ITVS_TXE
 *        @arg SPI_ITVS_UDR
 *        @arg SPI_ITVS_CRCERR
 *        @arg SPI_ITVS_MODF
 *        @arg SPI_ITVS_OVR
 *        @arg SPI_ITVS_FRE
 * @retval State of bit (1 or 0).
 */
static inline uint32_t LL_SPI_IsEnabledIT(reg_spi_t *SPIx, uint32_t RegisterBit)
{
    return ((READ_BIT(SPIx->IVS, RegisterBit) == (RegisterBit)) ? 1UL : 0UL);
}
/******************************************RIF******************************************/
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/******************************************RIF******************************************/
/**
 * @brief  Get interrupt raw flag
 * @param  SPIx SPI Instance
 * @param  RegisterBit This parameter can be one of the following values:
 *        @arg SPI_ITRI_RXNE
 *        @arg SPI_ITRI_TXE
 *        @arg SPI_ITRI_UDR
 *        @arg SPI_ITRI_CRCERR
 *        @arg SPI_ITRI_MODF
 *        @arg SPI_ITRI_OVR
 *        @arg SPI_ITRI_FRE
 * @retval State of bit (1 or 0).
 */
static inline uint32_t LL_SPI_IsActiveFlagIT(reg_spi_t *SPIx, uint32_t RegisterBit)
{
    return ((READ_BIT(SPIx->RIF, RegisterBit) == (RegisterBit)) ? 1UL : 0UL);
}
/******************************************IFM******************************************/
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/******************************************IFM******************************************/
/**
 * @brief  Get interrupt flag  after mask
 * @param  SPIx SPI Instance
 * @param  RegisterBit This parameter can be one of the following values:
 *        @arg SPI_ITFM_RXNE
 *        @arg SPI_ITFM_TXE
 *        @arg SPI_ITFM_UDR
 *        @arg SPI_ITFM_CRCERR
 *        @arg SPI_ITFM_MODF
 *        @arg SPI_ITFM_OVR
 *        @arg SPI_ITFM_FRE
 * @retval State of bit (1 or 0).
 */
static inline uint32_t LL_SPI_IsActiveFlagIT_Mask(reg_spi_t *SPIx, uint32_t RegisterBit)
{
    return ((READ_BIT(SPIx->IFM, RegisterBit) == (RegisterBit)) ? 1UL : 0UL);
}
/******************************************ICR******************************************/
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/******************************************ICR******************************************/
/**
 * @brief Clear interrupt flag 
 * @param  SPIx SPI Instance
 * @param  RegisterBit This parameter can be one of the following values:
 *        @arg SPI_ITIC_RXNE
 *        @arg SPI_ITIC_TXE
 *        @arg SPI_ITIC_UDR
 *        @arg SPI_ITIC_CRCERR
 *        @arg SPI_ITIC_MODF
 *        @arg SPI_ITIC_OVR
 *        @arg SPI_ITIC_FRE
 * @retval None
 */
static inline void LL_SPI_ClearFlagIT(reg_spi_t *SPIx, uint32_t RegisterBit)
{
    SET_BIT(SPIx->ICR, RegisterBit);
}

/*******************************************************************************
 End of File
 ******************************************************************************/

/** @}*/

/** @}*/

#endif

