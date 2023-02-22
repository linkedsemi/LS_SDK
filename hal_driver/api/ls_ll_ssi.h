#ifndef LS_LL_SSI_H_
#define LS_LL_SSI_H_
#include "HAL_def.h"
#include "ssi_misc.h"
#include "field_manipulate.h"
#include "ls_msp_ssi.h"
/** \addtogroup PERIPHERAL
 *  @{
 */

/** \addtogroup LSSSI
 *  @{
 */
/******************************************************************************
 External Variable Definition
 ******************************************************************************/
#define MOTOROLA_SPI    0x00000000U
#define TEXAS_SSP      (0x00000001U << SSI_FRF_POS)
#define NS_MICROWIRE    SSI_FRF_MASK

#define INACTIVE_LOW     0x00000000U
#define INACTIVE_HIGH   (0x00000001U << SSI_SCPH_POS)

#define SCLK_TOGGLE_IN_MIDDLE   0x00000000U
#define SCLK_TOGGLE_AT_START   (0x00000001U << SSI_SCPOL_POS)

#define TRANSMIT_AND_RECEIVE    0x00000000U
#define TRANSMIT_ONLY          (0x00000001U << SSI_TMOD_POS)
#define RECEIVE_ONLY           (0x00000002U << SSI_TMOD_POS)
#define EEPROM_READ            SSI_TMOD_MASK

#define TESTING_MODE    0x00000000U
#define NORNAL_MODE    (0x00000001U << SSI_SRL_POS)

#define CONTROL_WORD_1_BIT    0x00000000U
#define CONTROL_WORD_2_BIT   (0x00000001U << SSI_CFS_POS)
#define CONTROL_WORD_3_BIT   (0x00000002U << SSI_CFS_POS)
#define CONTROL_WORD_4_BIT   (0x00000003U << SSI_CFS_POS)
#define CONTROL_WORD_5_BIT   (0x00000004U << SSI_CFS_POS)
#define CONTROL_WORD_6_BIT   (0x00000005U << SSI_CFS_POS)
#define CONTROL_WORD_7_BIT   (0x00000006U << SSI_CFS_POS)
#define CONTROL_WORD_8_BIT   (0x00000007U << SSI_CFS_POS)
#define CONTROL_WORD_9_BIT   (0x00000008U << SSI_CFS_POS)
#define CONTROL_WORD_10_BIT  (0x00000009U << SSI_CFS_POS)
#define CONTROL_WORD_11_BIT  (0x0000000aU << SSI_CFS_POS)
#define CONTROL_WORD_12_BIT  (0x0000000bU << SSI_CFS_POS)
#define CONTROL_WORD_13_BIT  (0x0000000cU << SSI_CFS_POS)
#define CONTROL_WORD_14_BIT  (0x0000000dU << SSI_CFS_POS)
#define CONTROL_WORD_15_BIT  (0x0000000eU << SSI_CFS_POS)
#define CONTROL_WORD_16_BIT  (0x0000000fU << SSI_CFS_POS)

#define DFS_32_4_BITS        (0x00000003U << SSI_DFS_POS)
#define DFS_32_5_BITS        (0x00000004U << SSI_DFS_POS)
#define DFS_32_6_BITS        (0x00000005U << SSI_DFS_POS)
#define DFS_32_7_BITS        (0x00000006U << SSI_DFS_POS)
#define DFS_32_8_BITS        (0x00000007U << SSI_DFS_POS)
#define DFS_32_9_BITS        (0x00000008U << SSI_DFS_POS)
#define DFS_32_10_BITS       (0x00000009U << SSI_DFS_POS)
#define DFS_32_11_BITS       (0x0000000aU << SSI_DFS_POS)
#define DFS_32_12_BITS       (0x0000000bU << SSI_DFS_POS)
#define DFS_32_13_BITS       (0x0000000cU << SSI_DFS_POS)
#define DFS_32_14_BITS       (0x0000000dU << SSI_DFS_POS)
#define DFS_32_15_BITS       (0x0000000eU << SSI_DFS_POS)
#define DFS_32_16_BITS       (0x0000000fU << SSI_DFS_POS)
#define DFS_32_17_BITS       (0x00000010U << SSI_DFS_POS)
#define DFS_32_18_BITS       (0x00000011U << SSI_DFS_POS)
#define DFS_32_19_BITS       (0x00000012U << SSI_DFS_POS)
#define DFS_32_20_BITS       (0x00000013U << SSI_DFS_POS)
#define DFS_32_21_BITS       (0x00000014U << SSI_DFS_POS)
#define DFS_32_22_BITS       (0x00000015U << SSI_DFS_POS)
#define DFS_32_23_BITS       (0x00000016U << SSI_DFS_POS)
#define DFS_32_24_BITS       (0x00000017U << SSI_DFS_POS)
#define DFS_32_25_BITS       (0x00000018U << SSI_DFS_POS)
#define DFS_32_26_BITS       (0x00000019U << SSI_DFS_POS)
#define DFS_32_27_BITS       (0x0000001aU << SSI_DFS_POS)
#define DFS_32_28_BITS       (0x0000001bU << SSI_DFS_POS)
#define DFS_32_29_BITS       (0x0000001cU << SSI_DFS_POS)
#define DFS_32_30_BITS       (0x0000001dU << SSI_DFS_POS)
#define DFS_32_31_BITS       (0x0000001eU << SSI_DFS_POS)
#define DFS_32_32_BITS       (0x0000001fU << SSI_DFS_POS)

#define STD_SPI_FRF           0x00000000U
#define DUAL_SPI_FRF         (0x00000001U << SSI_SPI_FRF_POS)
#define QUAD_SPI_FORMAT      (0x00000002U << SSI_SPI_FRF_POS)
#define OCTAL_SPI_FRF        (0x00000003U << SSI_SPI_FRF_POS)

#define NON_SEQUENTIAL_TRANSFER    0x00000000U
#define SEQUENTIAL_TRANSFER       (0x00000001U << SSI_MWMOD_POS)

#define RECEIVE     0x00000000U
#define TRANSMIT    (0x00000001U << SSI_MOD_POS)

#define SSI_FLAG_DCOL   SSI_DCOL_MASK 
#define SSI_FLAG_TXE   SSI_TXE_MASK 
#define SSI_FLAG_RFF   SSI_RFF_MASK 
#define SSI_FLAG_RFNE   SSI_RFNE_MASK 
#define SSI_FLAG_TFE   SSI_TFE_MASK 
#define SSI_FLAG_TFNF   SSI_TFNF_MASK 
#define SSI_FLAG_BUSY   SSI_BUSY_MASK
#define SSI_ITIM_MST   SSI_MSTIM_MASK 
#define SSI_ITIM_RXF   SSI_RXFIM_MASK 
#define SSI_ITIM_RXO   SSI_RXOIM_MASK 
#define SSI_ITIM_RXU   SSI_RXUIM_MASK 
#define SSI_ITIM_TXO   SSI_TXOIM_MASK 
#define SSI_ITIM_TXE   SSI_TXEIM_MASK
#define SSI_ITIS_MST   SSI_MSTIS_MASK 
#define SSI_ITIS_RXF   SSI_RXFIS_MASK 
#define SSI_ITIS_RXO   SSI_RXOIS_MASK 
#define SSI_ITIS_RXU   SSI_RXUIS_MASK 
#define SSI_ITIS_TXO   SSI_TXOIS_MASK 
#define SSI_ITIS_TXE   SSI_TXEIS_MASK
#define SSI_ITIR_MST   SSI_MSTIR_MASK 
#define SSI_ITIR_RXF   SSI_RXFIR_MASK 
#define SSI_ITIR_RXO   SSI_RXOIR_MASK 
#define SSI_ITIR_RXU   SSI_RXUIR_MASK 
#define SSI_ITIR_TXO   SSI_TXOIR_MASK 
#define SSI_ITIR_TXE   SSI_TXEIR_MASK

#define ALL_SPIMODE           0x00000000U
#define INSTMODE_ADDRSPIFRF  (0x00000001U << SSI_TRANS_TYPE_POS)
#define All_SPIFRF           (0x00000002U << SSI_TRANS_TYPE_POS)

#define ADDR_L_0   0x00000000U
#define ADDR_L_1  (0x00000001U << SSI_ADDR_L_POS)
#define ADDR_L_2  (0x00000002U << SSI_ADDR_L_POS)
#define ADDR_L_3  (0x00000003U << SSI_ADDR_L_POS)
#define ADDR_L_4  (0x00000004U << SSI_ADDR_L_POS)
#define ADDR_L_5  (0x00000005U << SSI_ADDR_L_POS)
#define ADDR_L_6  (0x00000006U << SSI_ADDR_L_POS)
#define ADDR_L_7  (0x00000007U << SSI_ADDR_L_POS)
#define ADDR_L_8  (0x00000008U << SSI_ADDR_L_POS)
#define ADDR_L_9  (0x00000009U << SSI_ADDR_L_POS)
#define ADDR_L_10  (0x0000000aU << SSI_ADDR_L_POS)
#define ADDR_L_11  (0x0000000bU << SSI_ADDR_L_POS)
#define ADDR_L_12  (0x0000000cU << SSI_ADDR_L_POS)
#define ADDR_L_13  (0x0000000dU << SSI_ADDR_L_POS)
#define ADDR_L_14  (0x0000000eU << SSI_ADDR_L_POS)
#define ADDR_L_15  (0x0000000fU << SSI_ADDR_L_POS)

#define INST_L_0   0x00000000U
#define INST_L_1  (0x00000001U << SSI_INST_L_POS)
#define INST_L_2  (0x00000002U << SSI_INST_L_POS)
#define INST_L_3  (0x00000003U << SSI_INST_L_POS)
/******************************************************************************
 External Function Definition
 ******************************************************************************/

/******************************************CTRLR0**************************************/
/*                                                                                    */
/*                                                                                    */
/*                                                                                    */
/*                                                                                    */
/******************************************CTRLR0**************************************/

/**
 * @brief Select which serial protocol transmits data
 * @param ssi SSI Instance
 * @param FrameFormat  This parameter can be one of the following values:
 *         @arg MOTOROLA_SPI
 *         @arg TEXAS_SSP
 *         @arg NS_MICROWIRE
 */
static inline void LL_SSI_SetFrameFormat(reg_ssi_t *ssi, uint32_t FrameFormat)
{
    MODIFY_REG(ssi->CTRLR0, SSI_FRF_MASK, FrameFormat);
}
/**
 * @brief Get protocol.
 * @param ssi SSI Instance
 * @retval Returned value can be one of the following values:
 *         @arg MOTOROLA_SPI
 *         @arg TEXAS_SSP
 *         @arg NS_MICROWIRE
 */
static inline uint32_t LL_SSI_GetFrameFormat(reg_ssi_t *ssi)
{
    return (uint32_t)(READ_BIT(ssi->CTRLR0, SSI_FRF_MASK));
}

/**
 * @brief Serial clock phase.
 * @param ssi SSI Instance
 * @param ClockPhase  This parameter can be one of the following values:
 *         @arg INACTIVE_LOW
 *         @arg INACTIVE_HIGH
 */
static inline void LL_SSI_SetClockPhase(reg_ssi_t *ssi, uint32_t ClockPhase)
{
    MODIFY_REG(ssi->CTRLR0, SSI_SCPH_MASK, ClockPhase);
}

/**
 * @brief Get clock phase.
 * @param ssi SSI Instance
 * @retval Returned value can be one of the following values:
 *         @arg INACTIVE_LOW
 *         @arg INACTIVE_HIGH
 */
static inline uint32_t LL_SSI_GetClockPhase(reg_ssi_t *ssi)
{
    return (uint32_t)(READ_BIT(ssi->CTRLR0, SSI_SCPH_MASK));
}

/**
 * @brief Serial clock polarity.
 * @param ssi SSI Instance
 * @param ClockPolarity  This parameter can be one of the following values:
 *         @arg SCLK_TOGGLE_IN_MIDDLE
 *         @arg SCLK_TOGGLE_AT_START
 */
static inline void LL_SSI_SetClockPolarity(reg_ssi_t *ssi, uint32_t ClockPolarity)
{
    MODIFY_REG(ssi->CTRLR0, SSI_SCPOL_MASK, ClockPolarity );
}

/**
 * @brief Get  clock polarity.
 * @param ssi SSI Instance
 * @retval Returned value can be one of the following values:
 *         @arg SCLK_TOGGLE_IN_MIDDLE
 *         @arg SCLK_TOGGLE_AT_START
 */
static inline uint32_t LL_SSI_GetClockPolarity(reg_ssi_t *ssi)
{
    return (uint32_t)(READ_BIT(ssi->CTRLR0, SSI_SCPOL_MASK));
}

/**
 * @brief Set transfer mode.
 * @param ssi SSI Instance
 * @param TransferMode  This parameter can be one of the following values:
 *         @arg TRANSMIT_AND_RECEIVE
 *         @arg RECEIVE_ONLY
 *         @arg TRANSMIT_ONLY
 *         @arg EEPROM_READ
 */
static inline void LL_SSI_SetTransferMode(reg_ssi_t *ssi, uint32_t TransferMode)
{
    MODIFY_REG(ssi->CTRLR0, SSI_TMOD_MASK, TransferMode);
}

/**
 * @brief Get  transfer mode.
 * @param ssi SSI Instance
 * @retval Returned value can be one of the following values:
 *         @arg TRANSMIT_AND_RECEIVE
 *         @arg RECEIVE_ONLY
 *         @arg TRANSMIT_ONLY
 *         @arg EEPROM_READ
 */
static inline uint32_t LL_SSI_GetTransferMode(reg_ssi_t *ssi)
{
    return (uint32_t)(READ_BIT(ssi->CTRLR0, SSI_TMOD_MASK));
}

/**
 * @brief  Enable SSI Slave Output.
 * @param  ssi SSI Instance.
 * @retval None
 */
static inline void LL_SSI_EnableSlaveOutput(reg_ssi_t *ssi)
{
    SET_BIT(ssi->CTRLR0, SSI_SLV_OE_MASK);
}

/**
 * @brief  Disable SSI Slave Output.
 * @param  ssi SSI Instance.
 * @retval None
 */
static inline void LL_SSI_DisableSlaveOutput(reg_ssi_t *ssi)
{
    CLEAR_BIT(ssi->CTRLR0, SSI_SLV_OE_MASK);
}

/**
 * @brief Set Shift Register Loop.
 * @param ssi SSI Instance
 * @param ShiftRegisterLoop  This parameter can be one of the following values:
 *         @arg TESTING_MODE
 *         @arg NORNAL_MODE
 */
static inline void LL_SSI_SetShiftRegisterLoop(reg_ssi_t *ssi, uint32_t ShiftRegisterLoop)
{
    MODIFY_REG(ssi->CTRLR0, SSI_SRL_MASK, ShiftRegisterLoop);
}

/**
 * @brief Get  Shift Register Loop.
 * @param ssi SSI Instance
 * @retval Returned value can be one of the following values:
 *         @arg TESTING_MODE
 *         @arg NORNAL_MODE
 */
static inline uint32_t LL_SSI_GetShiftRegisterLoop(reg_ssi_t *ssi)
{
    return (uint32_t)(READ_BIT(ssi->CTRLR0, SSI_SRL_MASK));
}

/**
 * @brief Select the length of the control word in microlead format.
 * @param ssi SSI Instance
 * @param ControlFrameSize  This parameter can be one of the following values:
 *         @arg CONTROL_WORD_1_BIT
 *         @arg CONTROL_WORD_2_BIT
 *         @arg CONTROL_WORD_3_BIT
 *         @arg CONTROL_WORD_4_BIT
 *         @arg CONTROL_WORD_5_BIT
 *         @arg CONTROL_WORD_6_BIT
 *         @arg CONTROL_WORD_7_BIT
 *         @arg CONTROL_WORD_8_BIT
 *         @arg CONTROL_WORD_9_BIT
 *         @arg CONTROL_WORD_10_BIT
 *         @arg CONTROL_WORD_11_BIT
 *         @arg CONTROL_WORD_12_BIT
 *         @arg CONTROL_WORD_13_BIT
 *         @arg CONTROL_WORD_14_BIT
 *         @arg CONTROL_WORD_15_BIT
 *         @arg CONTROL_WORD_16_BIT
 */
static inline void LL_SSI_SetControlFrameSize(reg_ssi_t *ssi, uint32_t ControlFrameSize)
{
    MODIFY_REG(ssi->CTRLR0, SSI_CFS_MASK, ControlFrameSize);
}

/**
 * @brief Select the length of the control word in microlead format.
 * @param ssi SSI Instance
 * @retval Returned value can be one of the following values:
 *         @arg CONTROL_WORD_1_BIT
 *         @arg CONTROL_WORD_2_BIT
 *         @arg CONTROL_WORD_3_BIT
 *         @arg CONTROL_WORD_4_BIT
 *         @arg CONTROL_WORD_5_BIT
 *         @arg CONTROL_WORD_6_BIT
 *         @arg CONTROL_WORD_7_BIT
 *         @arg CONTROL_WORD_8_BIT
 *         @arg CONTROL_WORD_9_BIT
 *         @arg CONTROL_WORD_10_BIT
 *         @arg CONTROL_WORD_11_BIT
 *         @arg CONTROL_WORD_12_BIT
 *         @arg CONTROL_WORD_13_BIT
 *         @arg CONTROL_WORD_14_BIT
 *         @arg CONTROL_WORD_15_BIT
 *         @arg CONTROL_WORD_16_BIT
 */
static inline uint32_t LL_SSI_GetControlFrameSize(reg_ssi_t *ssi)
{
    return (uint32_t)(READ_BIT(ssi->CTRLR0, SSI_CFS_MASK));
}

/**
 * @brief Select the data frame size to send/receive data.
 * @param ssi SSI Instance
 * @param DataFrameSize  This parameter can be one of the following values:
 *         @arg DFS_32_4_BITS
 *         @arg DFS_32_5_BITS
 *         @arg DFS_32_6_BITS
 *         @arg DFS_32_7_BITS
 *         @arg DFS_32_8_BITS
 *         @arg DFS_32_9_BITS
 *         @arg DFS_32_10_BITS
 *         @arg DFS_32_11_BITS
 *         @arg DFS_32_12_BITS
 *         @arg DFS_32_13_BITS
 *         @arg DFS_32_14_BITS
 *         @arg DFS_32_15_BITS
 *         @arg DFS_32_16_BITS
 *         @arg DFS_32_17_BITS
 *         @arg DFS_32_18_BITS
 *         @arg DFS_32_19_BITS
 *         @arg DFS_32_20_BITS
 *         @arg DFS_32_21_BITS
 *         @arg DFS_32_22_BITS
 *         @arg DFS_32_23_BITS
 *         @arg DFS_32_24_BITS
 *         @arg DFS_32_25_BITS
 *         @arg DFS_32_26_BITS
 *         @arg DFS_32_27_BITS
 *         @arg DFS_32_28_BITS
 *         @arg DFS_32_29_BITS
 *         @arg DFS_32_30_BITS
 *         @arg DFS_32_31_BITS
 *         @arg DFS_32_32_BITS
 */
static inline void LL_SSI_SetDataFrameSize(reg_ssi_t *ssi, uint32_t DataFrameSize)
{
    MODIFY_REG(ssi->CTRLR0, SSI_DFS_MASK, DataFrameSize );
}

/**
 * @brief Get the data frame size to send/receive data.
 * @param ssi SSI Instance
 * @retval Returned value can be one of the following values:
 *         @arg DFS_32_4_BITS
 *         @arg DFS_32_5_BITS
 *         @arg DFS_32_6_BITS
 *         @arg DFS_32_7_BITS
 *         @arg DFS_32_8_BITS
 *         @arg DFS_32_9_BITS
 *         @arg DFS_32_10_BITS
 *         @arg DFS_32_11_BITS
 *         @arg DFS_32_12_BITS
 *         @arg DFS_32_13_BITS
 *         @arg DFS_32_14_BITS
 *         @arg DFS_32_15_BITS
 *         @arg DFS_32_16_BITS
 *         @arg DFS_32_17_BITS
 *         @arg DFS_32_18_BITS
 *         @arg DFS_32_19_BITS
 *         @arg DFS_32_20_BITS
 *         @arg DFS_32_21_BITS
 *         @arg DFS_32_22_BITS
 *         @arg DFS_32_23_BITS
 *         @arg DFS_32_24_BITS
 *         @arg DFS_32_25_BITS
 *         @arg DFS_32_26_BITS
 *         @arg DFS_32_27_BITS
 *         @arg DFS_32_28_BITS
 *         @arg DFS_32_29_BITS
 *         @arg DFS_32_30_BITS
 *         @arg DFS_32_31_BITS
 *         @arg DFS_32_32_BITS
 */
static inline uint32_t LL_SSI_GetDataFrameSize(reg_ssi_t *ssi)
{
    return (uint32_t)(READ_BIT(ssi->CTRLR0, SSI_DFS_MASK));
}

/**
 * @brief Select the data frame format to send/receive data.
 * @param ssi SSI Instance
 * @param SpiFrameFormat  This parameter can be one of the following values:
 *         @arg STD_SPI_FRF
 *         @arg DUAL_SPI_FRF
 *         @arg QUAD_SPI_FORMAT
 *         @arg OCTAL_SPI_FRF
 */
static inline void LL_SSI_SetSpiFrameFormat(reg_ssi_t *ssi, uint32_t SpiFrameFormat)
{
    MODIFY_REG(ssi->CTRLR0, SSI_SPI_FRF_MASK, SpiFrameFormat);
}

/**
 * @brief Get the data frame format to send/receive data.
 * @param ssi SSI Instance
 * @retval Returned value can be one of the following values:
 *         @arg STD_SPI_FRF
 *         @arg DUAL_SPI_FRF
 *         @arg QUAD_SPI_FORMAT
 *         @arg OCTAL_SPI_FRF
 */
static inline uint32_t LL_SSI_GetSpiFrameFormat(reg_ssi_t *ssi)
{
    return (uint32_t)(READ_BIT(ssi->CTRLR0, SSI_SPI_FRF_MASK) );
}

/**
 * @brief Select the data frame format to send/receive data.
 * @param ssi SSI Instance
 * @param Value  This parameter can be one of the following values:
 *         @arg 0
 *         @arg 1
 */
static inline void LL_SSI_SetSSTE(reg_ssi_t *ssi, uint32_t Value)
{
    MODIFY_REG(ssi->CTRLR0, SSI_SSTE_MASK, Value);
}

/******************************************CTRLR1**************************************/
/*                                                                                    */
/*                                                                                    */
/*                                                                                    */
/*                                                                                    */
/******************************************CTRLR1**************************************/

/**
 * @brief Set Number of data frames.
 * @param ssi SSI Instance
 * @param NumberOfEData  Value between Min_Data=0x0 and Max_Data=0xFFFF
 */
static inline void LL_SSI_SetNumberOfEData(reg_ssi_t *ssi, uint32_t NumberOfEData)
{
    MODIFY_REG(ssi->CTRLR1, SSI_NDF_MASK, NumberOfEData << SSI_NDF_POS);
}

/**
 * @brief Get Number of data frames.
 * @param ssi SSI Instance
 * @retval Value between Min_Data=0x0 and Max_Data=0xFFFF
 */
static inline uint32_t LL_SSI_GetNumberOfEData(reg_ssi_t *ssi)
{
    return (uint32_t)(READ_BIT(ssi->CTRLR1, SSI_NDF_MASK) >> SSI_NDF_POS);
}

/******************************************SSIENR**************************************/
/*                                                                                    */
/*                                                                                    */
/*                                                                                    */
/*                                                                                    */
/******************************************SSIENR**************************************/

/**
 * @brief  Enable SSI peripheral.
 * @param  ssi SSI Instance.
 * @retval None
 */
static inline void LL_SSI_Enable(reg_ssi_t *ssi)
{
    SET_BIT(ssi->SSIENR, SSI_SSI_EN_MASK);
}

/**
 * @brief  Disable SSI peripheral.
 * @param  ssi SSI Instance.
 * @retval None
 */
static inline void LL_SSI_Disable(reg_ssi_t *ssi)
{
    CLEAR_BIT(ssi->SSIENR, SSI_SSI_EN_MASK);
}

/**
 * @brief  Check if SSI peripheral is enabled
 * @param  ssi SPI Instance
 * @retval State of bit (1 or 0).
 */
static inline uint32_t LL_SSI_IsEnabled(reg_ssi_t *ssi)
{
    return ((READ_BIT(ssi->SSIENR, SSI_SSI_EN_MASK) == (SSI_SSI_EN_MASK)) ? 1UL : 0UL);
}

/******************************************MWCR**************************************/
/*                                                                                  */
/*                                                                                  */
/*                                                                                  */
/*                                                                                  */
/******************************************MWCR**************************************/
/**
 * @brief Set Microwire Transfer Mode.
 * @param ssi SSI Instance
 * @param MicrowireTransferMode  This parameter can be one of the following values:
 *         @arg NON_SEQUENTIAL_TRANSFER
 *         @arg SEQUENTIAL_TRANSFER
 */
static inline void LL_SSI_SetMicrowireTransferMode(reg_ssi_t *ssi, uint32_t MicrowireTransferMode)
{
    MODIFY_REG(ssi->MWCR, SSI_MWMOD_MASK, MicrowireTransferMode);
}

/**
 * @brief Get Microwire Transfer Mode.
 * @param ssi SSI Instance
 * @retval Returned value can be one of the following values:
 *         @arg NON_SEQUENTIAL_TRANSFER
 *         @arg SEQUENTIAL_TRANSFER
 */
static inline uint32_t LL_SSI_GetMicrowireTransferMode(reg_ssi_t *ssi)
{
    return (uint32_t)(READ_BIT(ssi->MWCR, SSI_MWMOD_MASK));
}

/**
 * @brief Set Direction of transfer data.
 * @param ssi SSI Instance
 * @param DirectionControl  This parameter can be one of the following values:
 *         @arg RECEIVE
 *         @arg TRANSMIT
 */
static inline void LL_SSI_SetDirectionControl(reg_ssi_t *ssi, uint32_t DirectionControl)
{
    MODIFY_REG(ssi->MWCR, SSI_MOD_MASK, DirectionControl );
}

/**
 * @brief Get Direction of transfer data.
 * @param ssi SSI Instance
 * @retval Returned value can be one of the following values:
 *         @arg RECEIVE
 *         @arg TRANSMIT
 */
static inline uint32_t LL_SSI_GetDirectionControl(reg_ssi_t *ssi)
{
    return (uint32_t)(READ_BIT(ssi->MWCR, SSI_MOD_MASK));
}

/**
 * @brief  Enable hand shaking.
 * @param  ssi SSI Instance.
 * @retval None
 */
static inline void LL_SSI_EnableHandShaking(reg_ssi_t *ssi)
{
    SET_BIT(ssi->MWCR, SSI_MHS_MASK);
}

/**
 * @brief  Disable hand shaking.
 * @param  ssi SSI Instance.
 * @retval None
 */
static inline void LL_SSI_DisableHandShaking(reg_ssi_t *ssi)
{
    CLEAR_BIT(ssi->MWCR, SSI_MHS_MASK);
}

/**
 * @brief  Check if hand shaking is enabled
 * @param  ssi ssi Instance
 * @retval State of bit (1 or 0).
 */
static inline uint32_t LL_SSI_IsEnabledHandShaking(reg_ssi_t *ssi)
{
    return ((READ_BIT(ssi->MWCR, SSI_MHS_MASK) == (SSI_MHS_MASK)) ? 1UL : 0UL);
}

/******************************************SER**************************************/
/*                                                                                 */
/*                                                                                 */
/*                                                                                 */
/*                                                                                 */
/******************************************SER**************************************/
/**
 * @brief  Set Slave Select.
 * @param  ssi SSI Instance.
 * @param SerValue  Value between Min_Data=0x0 and Max_Data=0x3
 * @retval None
 */
static inline void LL_SSI_SetSlaveSelect(reg_ssi_t *ssi, uint32_t SerValue)
{
    MODIFY_REG(ssi->SER, SSI_SER_MASK, SerValue << SSI_SER_POS);
}

/**
 * @brief  Get Slave Select.
 * @param  ssi SSI Instance.
 * @retval Value between Min_Data=0x0 and Max_Data=0x3
 */
static inline uint32_t LL_SSI_GetSlaveSelect(reg_ssi_t *ssi)
{
    return (uint32_t)(READ_BIT(ssi->SER, SSI_SER_MASK) >> SSI_SER_POS);
}

/******************************************BAUDR**************************************/
/*                                                                                   */
/*                                                                                   */
/*                                                                                   */
/*                                                                                   */
/******************************************BAUDR**************************************/
/**
 * @brief Set Direction of transfer data.
 * @param ssi SSI Instance
 * @param ClockDivider  Value between Min_Data=0x0 and Max_Data=0xFFFF
 */
static inline void LL_SSI_SetClockDivider(reg_ssi_t *ssi, uint32_t ClockDivider)
{
    MODIFY_REG(ssi->BAUDR, SSI_SCKDV_MASK, ClockDivider << SSI_SCKDV_POS);
}

/**
 * @brief Get Direction of transfer data.
 * @param ssi SSI Instance
 * @retval Value between Min_Data=0x0 and Max_Data=0xFFFF
 */
static inline uint32_t LL_SSI_GetClockDivider(reg_ssi_t *ssi)
{
    return (uint32_t)(READ_BIT(ssi->BAUDR, SSI_SCKDV_MASK) >> SSI_SCKDV_POS);
}

/******************************************TXFTLR**************************************/
/*                                                                                    */
/*                                                                                    */
/*                                                                                    */
/*                                                                                    */
/******************************************TXFTLR**************************************/
/**
 * @brief Set Direction of transfer data.
 * @param ssi SSI Instance
 * @param TxFifoThreshoid  Value between Min_Data=0x0 and Max_Data=0x3F
 */
static inline void LL_SSI_SetTxFifoThreshoid(reg_ssi_t *ssi, uint32_t TxFifoThreshoid)
{
    MODIFY_REG(ssi->TXFTLR, SSI_TFT_MASK, TxFifoThreshoid << SSI_TFT_POS);
}

/**
 * @brief Get Direction of transfer data.
 * @param ssi SSI Instance
 * @retval Value between Min_Data=0x0 and Max_Data=0x3F
 */
static inline uint32_t LL_SSI_GetTxFifoThreshoid(reg_ssi_t *ssi)
{
    return (uint32_t)(READ_BIT(ssi->TXFTLR, SSI_TFT_MASK) >> SSI_TFT_POS);
}

/******************************************RXFTLR**************************************/
/*                                                                                    */
/*                                                                                    */
/*                                                                                    */
/*                                                                                    */
/******************************************RXFTLR**************************************/
/**
 * @brief Set Direction of transfer data.
 * @param ssi SSI Instance
 * @param RxFifoThreshoid  Value between Min_Data=0x0 and Max_Data=0x3
 */
static inline void LL_SSI_SetRxFifoThreshoid(reg_ssi_t *ssi, uint32_t RxFifoThreshoid)
{
    MODIFY_REG(ssi->RXFTLR, SSI_RFT_MASK, RxFifoThreshoid << SSI_RFT_POS);
}

/**
 * @brief Get Direction of transfer data.
 * @param ssi SSI Instance
 * @retval Value between Min_Data=0x0 and Max_Data=0x3
 */
static inline uint32_t LL_SSI_GetRxFifoThreshoid(reg_ssi_t *ssi)
{
    return (uint32_t)(READ_BIT(ssi->RXFTLR, SSI_RFT_MASK) >> SSI_RFT_POS);
}

/******************************************TXFLR**************************************/
/*                                                                                   */
/*                                                                                   */
/*                                                                                   */
/*                                                                                   */
/******************************************TXFLR**************************************/

/**
 * @brief Get Direction of transfer data.
 * @param ssi SSI Instance
 * @retval Value between Min_Data=0x0 and Max_Data=0x7
 */
static inline uint32_t LL_SSI_GetTxFifoLevel(reg_ssi_t *ssi)
{
    return (uint32_t)(READ_BIT(ssi->TXFLR, SSI_TXTFL_MASK) >> SSI_TXTFL_POS);
}

/******************************************RXFLR**************************************/
/*                                                                                   */
/*                                                                                   */
/*                                                                                   */
/*                                                                                   */
/******************************************RXFLR**************************************/

/**
 * @brief Get Direction of transfer data.
 * @param ssi SSI Instance
 * @retval Value between Min_Data=0x0 and Max_Data=0x7
 */
static inline uint32_t LL_SSI_GetRxFifoLevel(reg_ssi_t *ssi)
{
    return (uint32_t)(READ_BIT(ssi->RXFLR, SSI_RXTFL_MASK) >> SSI_RXTFL_POS);
}
/******************************************SR*****************************************/
/*                                                                                   */
/*                                                                                   */
/*                                                                                   */
/*                                                                                   */
/******************************************SR*****************************************/
/**
 * @brief  Check register flag
 * @param  ssi SSI Instance
 * @param RegisterBit  This parameter can be one of the following values:
 *         @arg SSI_FLAG_DCOL
 *         @arg SSI_FLAG_TXE
 *         @arg SSI_FLAG_RFF
 *         @arg SSI_FLAG_RFNE
 *         @arg SSI_FLAG_TFE
 *         @arg SSI_FLAG_TFNF
 *         @arg SSI_FLAG_BUSY
 * @retval State of bit (1 or 0).
 */
static inline uint32_t LL_SSI_IsActiveFlag(reg_ssi_t *ssi, uint32_t RegisterBit)
{
    return ((READ_BIT(ssi->SR, RegisterBit) == (RegisterBit)) ? 1UL : 0UL);
}

/*****************************************IMR*****************************************/
/*                                                                                   */
/*                                                                                   */
/*                                                                                   */
/*                                                                                   */
/*****************************************IMR*****************************************/
// /**
//  * @brief  Check if Interrupt mask
//  * @rmtoll IMR           IMR          LL_SSI_DisableMaskIT
//  * @param  ssi SSI Instance
//  * @retval Returned value can be one of the following values:
//  *         @arg SSI_ITIM_MST
//  *         @arg SSI_ITIM_RXF
//  *         @arg SSI_ITIM_RXO
//  *         @arg SSI_ITIM_RXU
//  *         @arg SSI_ITIM_TXO
//  *         @arg SSI_ITIM_TXE
//  */
// static inline uint32_t LL_SSI_DisableMaskIT(reg_ssi_t *ssi, uint32_t RegisterBit)
// {
//     return ((READ_BIT(ssi->IMR, RegisterBit) == (RegisterBit)) ? 0UL : 1UL);
// }

/**
 * @brief  Disable Interrupt mask
 * @param  ssi SSI Instance
 * @param RegisterBit  This parameter can be one of the following values:
 *         @arg SSI_ITIM_MST
 *         @arg SSI_ITIM_RXF
 *         @arg SSI_ITIM_RXO
 *         @arg SSI_ITIM_RXU
 *         @arg SSI_ITIM_TXO
 *         @arg SSI_ITIM_TXE
 */
static inline void LL_SSI_DisableMaskIT(reg_ssi_t *ssi, uint32_t RegisterBit)
{
    SET_BIT(ssi->IMR, RegisterBit);
}

/*****************************************ISR*****************************************/
/*                                                                                   */
/*                                                                                   */
/*                                                                                   */
/*                                                                                   */
/*****************************************ISR*****************************************/
/**
 * @brief  Check if Interrupt active
 * @param  ssi SSI Instance
 * @param RegisterBit  This parameter can be one of the following values:
 *         @arg SSI_ITIS_MST
 *         @arg SSI_ITIS_RXF
 *         @arg SSI_ITIS_RXO
 *         @arg SSI_ITIS_RXU
 *         @arg SSI_ITIS_TXO
 *         @arg SSI_ITIS_TXE
 * @return 0 or 1
 */
static inline uint32_t LL_SSI_IsActiveFlagIT_Mask(reg_ssi_t *ssi, uint32_t RegisterBit)
{
    return ((READ_BIT(ssi->ISR, RegisterBit) == (RegisterBit)) ? 1UL : 0UL);
}
/*****************************************RISR****************************************/
/*                                                                                   */
/*                                                                                   */
/*                                                                                   */
/*                                                                                   */
/*****************************************RISR****************************************/
/**
 * @brief  Check if generate interrupt flag
 * @param  ssi SSI Instance
 * @param RegisterBit  This parameter can be one of the following values:
 *         @arg SSI_ITIR_MST
 *         @arg SSI_ITIR_RXF
 *         @arg SSI_ITIR_RXO
 *         @arg SSI_ITIR_RXU
 *         @arg SSI_ITIR_TXO
 *         @arg SSI_ITIR_TXE
 * @return 0 or 1
 */
static inline uint32_t LL_SSI_IsActiveFlagIT(reg_ssi_t *ssi, uint32_t RegisterBit)
{
    return ((READ_BIT(ssi->RISR, RegisterBit) == (RegisterBit)) ? 1UL : 0UL);
}

/***************************************TXOICR****************************************/
/*                                                                                   */
/*                                                                                   */
/*                                                                                   */
/*                                                                                   */
/***************************************TXOICR****************************************/
/**
 * @brief  Clear Receive Fifo OverFlow interrupt
 * @param  ssi SSI Instance
 * @retval 1 or 0
 */
static inline uint32_t LL_SSI_ClearReceiveFifoOverFlow(reg_ssi_t *ssi)
{
    return ((READ_BIT(ssi->TXOICR, SSI_TXOICR_MASK) == (SSI_TXOICR_MASK)) ? 1UL : 0UL);
}

/***************************************RXOICR****************************************/
/*                                                                                   */
/*                                                                                   */
/*                                                                                   */
/*                                                                                   */
/***************************************RXOICR****************************************/
/**
 * @brief  Clear Receive Fifo UnderFlow interrupt
 * @param  ssi SSI Instance
 * @retval 1 or 0
 */
static inline uint32_t LL_SSI_ClearReceiveFifoUnderFlow(reg_ssi_t *ssi)
{
    return ((READ_BIT(ssi->RXOICR, SSI_RXOICR_MASK) == (SSI_RXOICR_MASK)) ? 1UL : 0UL);
}

/***************************************MSTICR****************************************/
/*                                                                                   */
/*                                                                                   */
/*                                                                                   */
/*                                                                                   */
/***************************************MSTICR****************************************/
/**
 * @brief  Clear Multi-Master Contention interrupt
 * @param  ssi SSI Instance
 * @retval 1 or 0
 */
static inline uint32_t LL_SSI_ClearMultiMasterContention(reg_ssi_t *ssi)
{
    return ((READ_BIT(ssi->MSTICR, SSI_MSTICR_MASK) == (SSI_MSTICR_MASK)) ? 1UL : 0UL);
}

/***************************************ICR*******************************************/
/*                                                                                   */
/*                                                                                   */
/*                                                                                   */
/*                                                                                   */
/***************************************ICR*******************************************/
/**
 * @brief  Clear (ssi_txo_intr,ssi_rxu_intr,ssi_rxo_intr,ssi_mst_intr) interrupt
 * @param  ssi SSI Instance
 * @retval 1 or 0
 */
static inline uint32_t LL_SSI_ClearIntr(reg_ssi_t *ssi)
{
    return ((READ_BIT(ssi->ICR, SSI_ICR_MASK) == (SSI_ICR_MASK)) ? 1UL : 0UL);
}

/*************************************DMACR*******************************************/
/*                                                                                   */
/*                                                                                   */
/*                                                                                   */
/*                                                                                   */
/*************************************DMACR*******************************************/

/**
 * @brief  Enable SSI DMA Transmit.
 * @param  ssi SSI Instance.
 * @retval None
 */
static inline void LL_SSI_EnableDMAReq_TX(reg_ssi_t *ssi)
{
    SET_BIT(ssi->DMACR, SSI_TDMAE_MASK);
}

/**
 * @brief  Disable SSI DMA Transmit.
 * @param  ssi SSI Instance.
 * @retval None
 */
static inline void LL_SSI_DisableDMAReq_TX(reg_ssi_t *ssi)
{
    CLEAR_BIT(ssi->DMACR, SSI_TDMAE_MASK);
}

/**
 * @brief  Check if SSI DMA Transmit is enabled
 * @param  ssi SPI Instance
 * @retval State of bit (1 or 0).
 */
static inline uint32_t LL_SSI_IsEnabledDMAReq_TX(reg_ssi_t *ssi)
{
    return ((READ_BIT(ssi->DMACR, SSI_TDMAE_MASK) == (SSI_TDMAE_MASK)) ? 1UL : 0UL);
}

/**
 * @brief  Enable SSI DMA Receive.
 * @param  ssi SSI Instance.
 * @retval None
 */
static inline void LL_SSI_EnableDMAReq_RX(reg_ssi_t *ssi)
{
    SET_BIT(ssi->DMACR, SSI_RDMAE_MASK);
}

/**
 * @brief  Disable SSI DMA Transmit.
 * @param  ssi SSI Instance.
 * @retval None
 */
static inline void LL_SSI_DisableDMAReq_RX(reg_ssi_t *ssi)
{
    CLEAR_BIT(ssi->DMACR, SSI_RDMAE_MASK);
}

/**
 * @brief  Check if SSI DMA Transmit is enabled
 * @param  ssi SPI Instance
 * @retval State of bit (1 or 0).
 */
static inline uint32_t LL_SSI_IsEnabledDMAReq_RX(reg_ssi_t *ssi)
{
    return ((READ_BIT(ssi->DMACR, SSI_RDMAE_MASK) == (SSI_RDMAE_MASK)) ? 1UL : 0UL);
}

/*************************************DMATDLR*****************************************/
/*                                                                                   */
/*                                                                                   */
/*                                                                                   */
/*                                                                                   */
/*************************************DMATDLR*****************************************/

/**
 * @brief Set transmit data leve.
 * @param ssi SSI Instance
 * @param TransmitDataLeve  Value between Min_Data=0x0 and Max_Data=0x3
 */
static inline void LL_SSI_SetTransmitDataLeve(reg_ssi_t *ssi, uint32_t TransmitDataLeve)
{
    MODIFY_REG(ssi->DMATDLR, SSI_DMATDL_MASK, TransmitDataLeve << SSI_DMATDL_POS);
}

/**
 * @brief Get Direction of transfer data.
 * @param ssi SSI Instance
 * @retval Value between Min_Data=0x0 and Max_Data=0x3
 */
static inline uint32_t LL_SSI_GetTransmitDataLeve(reg_ssi_t *ssi)
{
    return (uint32_t)(READ_BIT(ssi->DMATDLR, SSI_DMATDL_MASK) >> SSI_DMATDL_POS);
}

/*************************************DMARDLR*****************************************/
/*                                                                                   */
/*                                                                                   */
/*                                                                                   */
/*                                                                                   */
/*************************************DMARDLR*****************************************/

/**
 * @brief Set reveive data leve.
 * @param ssi SSI Instance
 * @param ReveiveDataLeve  Value between Min_Data=0x0 and Max_Data=0x3
 */
static inline void LL_SSI_SetReveiveDataLeve(reg_ssi_t *ssi, uint32_t ReveiveDataLeve)
{
    MODIFY_REG(ssi->DMARDLR, SSI_DMARDL_MASK, ReveiveDataLeve << SSI_DMARDL_POS);
}

/**
 * @brief Get Direction of transfer data.
 * @param ssi SSI Instance
 * @retval Value between Min_Data=0x0 and Max_Data=0x3
 */
static inline uint32_t LL_SSI_GetReveiveDataLeve(reg_ssi_t *ssi)
{
    return (uint32_t)(READ_BIT(ssi->DMARDLR, SSI_DMARDL_MASK) >> SSI_DMARDL_POS);
}

/****************************************DR*******************************************/
/*                                                                                   */
/*                                                                                   */
/*                                                                                   */
/*                                                                                   */
/****************************************DR*******************************************/

/**
 * @brief Set data register.
 * @param ssi SSI Instance
 * @param data  Value between Min_Data=0x0 and Max_Data=0xffffffffL
 */
static inline void LL_SSI_SetDataRegister8(reg_ssi_t *ssi, uint8_t data)
{
    ssi->DR = data;
}
static inline void LL_SSI_SetDataRegister16(reg_ssi_t *ssi, uint16_t data)
{
    ssi->DR = data;
}
static inline void LL_SSI_SetDataRegister32(reg_ssi_t *ssi, uint32_t data)
{
    ssi->DR = data;
}
/**
 * @brief Get Direction of transfer data.
 * @param ssi SSI Instance
 * @retval Value between Min_Data=0x0 and Max_Data=0xffffffffL
 */
static inline uint8_t LL_SSI_GetDataRegister8(reg_ssi_t *ssi)
{
    return (uint8_t)ssi->DR;
}

static inline uint16_t LL_SSI_GetDataRegister16(reg_ssi_t *ssi)
{
    return (uint16_t)ssi->DR;
}

static inline uint32_t LL_SSI_GetDataRegister32(reg_ssi_t *ssi)
{
    return (uint32_t)ssi->DR;
}

/****************************************RXSAMPLE_DLY*********************************/
/*                                                                                   */
/*                                                                                   */
/*                                                                                   */
/*                                                                                   */
/****************************************RXSAMPLE_DLY*********************************/

/**
 * @brief Set Rxd Sample Delay.
 * @param ssi SSI Instance
 * @param RxdSampleDelay  Value between Min_Data=0x0 and Max_Data=0xff
 */
static inline void LL_SSI_SetRxdSampleDelay(reg_ssi_t *ssi, uint32_t RxdSampleDelay)
{
    MODIFY_REG(ssi->RXSAMPLE_DLY, SSI_RSD_MASK, RxdSampleDelay << SSI_RSD_POS);
}

/**
 * @brief Get Rxd Sample Delay.
 * @param ssi SSI Instance
 * @retval Value between Min_Data=0x0 and Max_Data=0xff
 */
static inline uint32_t LL_SSI_GetRxdSampleDelay(reg_ssi_t *ssi)
{
    return (uint32_t)(READ_BIT(ssi->RXSAMPLE_DLY, SSI_RSD_MASK) >> SSI_RSD_POS);
}

/****************************************SPI_CTRLR0*********************************/
/*                                                                                   */
/*                                                                                   */
/*                                                                                   */
/*                                                                                   */
/****************************************SPI_CTRLR0*********************************/

/**
 * @brief Set Addr And Instruction Transfer mode.
 * @param ssi SSI Instance
 * @param TransferMode  This parameter can be one of the following values:
 *         @arg ALL_SPIMODE
 *         @arg INSTMODE_ADDRSPIFRF
 *         @arg All_SPIFRF
 */
static inline void LL_SSI_SetAddrAndInstructionTransfer(reg_ssi_t *ssi, uint32_t TransferMode)
{
    MODIFY_REG(ssi->SPI_CTRLR0, SSI_TRANS_TYPE_MASK, TransferMode << SSI_TRANS_TYPE_POS);
}

/**
 * @brief Get Addr And Instruction Transfer mode.
 * @param ssi SSI Instance
 * @retval Returned value can be one of the following values:
 *         @arg ALL_SPIMODE
 *         @arg INSTMODE_ADDRSPIFRF
 *         @arg All_SPIFRF
 */
static inline uint32_t LL_SSI_GetAddrAndInstructionTransfer(reg_ssi_t *ssi)
{
    return (uint32_t)(READ_BIT(ssi->SPI_CTRLR0, SSI_TRANS_TYPE_MASK));
}

/**
 * @brief Set Addr Length.
 * @param ssi SSI Instance
 * @param AddrLength  This parameter can be one of the following values:
 *         @arg ADDR_L_0
 *         @arg ADDR_L_1
 *         @arg ADDR_L_2
 *         @arg ADDR_L_3
 *         @arg ADDR_L_4
 *         @arg ADDR_L_5
 *         @arg ADDR_L_6
 *         @arg ADDR_L_7
 *         @arg ADDR_L_8
 *         @arg ADDR_L_9
 *         @arg ADDR_L_10
 *         @arg ADDR_L_11
 *         @arg ADDR_L_12
 *         @arg ADDR_L_13
 *         @arg ADDR_L_14
 *         @arg ADDR_L_15
 */
static inline void LL_SSI_SetAddrLength(reg_ssi_t *ssi, uint32_t AddrLength)
{
    MODIFY_REG(ssi->SPI_CTRLR0, SSI_ADDR_L_MASK, AddrLength );
}

/**
 * @brief Get Addr Length.
 * @param ssi SSI Instance
 * @retval Returned value can be one of the following values:
 *         @arg ADDR_L_0
 *         @arg ADDR_L_1
 *         @arg ADDR_L_2
 *         @arg ADDR_L_3
 *         @arg ADDR_L_4
 *         @arg ADDR_L_5
 *         @arg ADDR_L_6
 *         @arg ADDR_L_7
 *         @arg ADDR_L_8
 *         @arg ADDR_L_9
 *         @arg ADDR_L_10
 *         @arg ADDR_L_11
 *         @arg ADDR_L_12
 *         @arg ADDR_L_13
 *         @arg ADDR_L_14
 *         @arg ADDR_L_15
 */
static inline uint32_t LL_SSI_GetAddrLength(reg_ssi_t *ssi)
{
    return (uint32_t)(READ_BIT(ssi->SPI_CTRLR0, SSI_ADDR_L_MASK));
}

/**
 * @brief Set Instruction Length.
 * @param ssi SSI Instance
 * @param InstructionLength  This parameter can be one of the following values:
 *         @arg INST_L_0
 *         @arg INST_L_1
 *         @arg INST_L_2
 *         @arg INST_L_3
 */
static inline void LL_SSI_SetInstructionLengthDual(reg_ssi_t *ssi, uint32_t InstructionLength)
{
    MODIFY_REG(ssi->SPI_CTRLR0, SSI_INST_L_MASK, InstructionLength);
}

/**
 * @brief Get Instruction Length.
 * @param ssi SSI Instance
 * @retval Returned value can be one of the following values:
 *         @arg INST_L_0
 *         @arg INST_L_1
 *         @arg INST_L_2
 *         @arg INST_L_3
 */
static inline uint32_t LL_SSI_GetInstructionLengthDual(reg_ssi_t *ssi)
{
    return (uint32_t)(READ_BIT(ssi->SPI_CTRLR0, SSI_INST_L_MASK));
}

/**
 * @brief Set Wait Cycles.
 * @param ssi SSI Instance
 * @param WaitCycles  Value between Min_Data=0x0 and Max_Data=0xf
 */
static inline void LL_SSI_SetWaitCycles(reg_ssi_t *ssi, uint32_t WaitCycles)
{
    MODIFY_REG(ssi->SPI_CTRLR0, SSI_WAIT_CYCLES_MASK, WaitCycles << SSI_WAIT_CYCLES_POS);
}

/**
 * @brief Get Wait Cycles.
 * @param ssi SSI Instance
 * @retval Value between Min_Data=0x0 and Max_Data=0xf
 */
static inline uint32_t LL_SSI_GetWaitCycles(reg_ssi_t *ssi)
{
    return (uint32_t)(READ_BIT(ssi->SPI_CTRLR0, SSI_WAIT_CYCLES_MASK) >> SSI_WAIT_CYCLES_POS);
}
/*******************************************************************************
 End of File
 ******************************************************************************/

/** @}*/

/** @}*/


#endif
