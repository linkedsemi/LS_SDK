#ifndef LS_LL_UART_H_
#define LS_LL_UART_H_
#include "field_manipulate.h"
#include "ls_msp_uart.h"

/** \addtogroup PERIPHERAL
 *  @{
 */

/** \addtogroup LSI2C
 *  @{
 */
/******************************************************************************
 External Variable Definition
 ******************************************************************************/
#if FPGA
#define UART_CLOCK 16000000
#else
#define UART_CLOCK (SDK_PCLK_MHZ * 1000000)
#endif
/// Baud rate calculation
#define UART_BUADRATE_ENUM_GEN(BAUD) ((((UART_CLOCK << 4) / BAUD) + 8) >> 4)

typedef enum LL_uart_baudrate_t
{
    UART_BAUDRATE_1200 = UART_BUADRATE_ENUM_GEN(1200),
    UART_BAUDRATE_2400 = UART_BUADRATE_ENUM_GEN(2400),
    UART_BAUDRATE_4800 = UART_BUADRATE_ENUM_GEN(4800),
    UART_BAUDRATE_9600 = UART_BUADRATE_ENUM_GEN(9600),
    UART_BAUDRATE_14400 = UART_BUADRATE_ENUM_GEN(14400),
    UART_BAUDRATE_19200 = UART_BUADRATE_ENUM_GEN(19200),
    UART_BAUDRATE_28800 = UART_BUADRATE_ENUM_GEN(28800),
    UART_BAUDRATE_38400 = UART_BUADRATE_ENUM_GEN(38400),
    UART_BAUDRATE_57600 = UART_BUADRATE_ENUM_GEN(57600),
    UART_BAUDRATE_76800 = UART_BUADRATE_ENUM_GEN(76800),
    UART_BAUDRATE_115200 = UART_BUADRATE_ENUM_GEN(115200),
    UART_BAUDRATE_230400 = UART_BUADRATE_ENUM_GEN(230400),
    UART_BAUDRATE_250000 = UART_BUADRATE_ENUM_GEN(250000),
    UART_BAUDRATE_500000 = UART_BUADRATE_ENUM_GEN(500000),
    UART_BAUDRATE_460800 = UART_BUADRATE_ENUM_GEN(460800),
    UART_BAUDRATE_750000 = UART_BUADRATE_ENUM_GEN(750000),
    UART_BAUDRATE_921600 = UART_BUADRATE_ENUM_GEN(921600),
    UART_BAUDRATE_1000000 = UART_BUADRATE_ENUM_GEN(1000000),
    UART_BAUDRATE_2000000 = UART_BUADRATE_ENUM_GEN(2000000),
}app_uart_baudrate_t;

#define LL_UART_DATAWIDTH_5B 0x00000000U
#define LL_UART_DATAWIDTH_6B 0x00000001U
#define LL_UART_DATAWIDTH_7B 0x00000002U
#define LL_UART_DATAWIDTH_8B 0x00000003U

#define LL_UART_STOPBITS_1 0x00000000U
#define LL_UART_STOPBITS_2 UART_LCR_STOP_MASK

#define LL_UART_PARITY_NONE 0x00000000U
#define LL_UART_PARITY_EVEN UART_LCR_PE_MASK
#define LL_UART_PARITY_ODD (UART_LCR_PE_MASK | UART_LCR_PS_MASK)

#define DISCONNECT_DETECTION_10BIT 0x00000000U
#define DISCONNECT_DETECTION_11BIT UART_MCR_LBDL_MASK

#define FIFO_RECEIVE_TRIGGER_1BYTE 0x00000000U
#define FIFO_RECEIVE_TRIGGER_4BYTE 0x00000010U
#define FIFO_RECEIVE_TRIGGER_8BYTE 0x00000020U
#define FIFO_RECEIVE_TRIGGER_14BYTE UART_MCR_LBDL_MASK

#define FIFO_TRABSMIT_TRIGGER_0BYTE 0x00000000U
#define FIFO_TRABSMIT_TRIGGER_1BYTE 0x00000040U
#define FIFO_TRABSMIT_TRIGGER_4BYTE 0x00000080U
#define FIFO_TRABSMIT_TRIGGER_8BYTE UART_FCR_TXTL_MASK

#define UART_SR_DR      UART_SR_DR_MASK
#define UART_SR_OE      UART_SR_OE_MASK
#define UART_SR_PE      UART_SR_PE_MASK
#define UART_SR_FE      UART_SR_FE_MASK
#define UART_SR_BI      UART_SR_BI_MASK
#define UART_SR_TBEM    UART_SR_TBEM_MASK
#define UART_SR_TEMT    UART_SR_TEMT_MASK
#define UART_SR_RFE     UART_SR_RFE_MASK
#define UART_SR_BUSY    UART_SR_BUSY_MASK
#define UART_SR_TFNF    UART_SR_TFNF_MASK
#define UART_SR_TFEM    UART_SR_TFEM_MASK
#define UART_SR_RFNE    UART_SR_RFNE_MASK
#define UART_SR_RFF     UART_SR_RFF_MASK
#define UART_SR_DCTS    UART_SR_DCTS_MASK
#define UART_SR_CTS     UART_SR_CTS_MASK

#define UART_IT_RXRD    UART_RXRD_MASK
#define UART_IT_TXS     UART_TXS_MASK
#define UART_IT_RXS     UART_RXS_MASK
#define UART_IT_MDDS    UART_MDDS_MASK
#define UART_IT_RTO     UART_RTO_MASK
#define UART_IT_BUSY    UART_BUSY_MASK
#define UART_IT_ABE     UART_ABE_MASK
#define UART_IT_ABTO    UART_ABTO_MASK
#define UART_IT_LINBK   UART_LINBK_MASK
#define UART_IT_TC      UART_TC_MASK
#define UART_IT_EOB     UART_EOB_MASK
#define UART_IT_CM      UART_CM_MASK

/******************************************************************************
 External Function Definition
 ******************************************************************************/

/******************************************RBR******************************************/
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/******************************************RBR******************************************/

/*
 * @brief  Read Receiver Data register (Receive Data value, 8 bits)
 * @param  UARTx UART Instance
 * @retval Value between Min_Data=0x00 and Max_Data=0xFF
 */
static inline uint8_t LL_UART_ReceiveData(reg_uart_t *UARTx)
{
    return (uint8_t)(READ_BIT(UARTx->RBR, UART_RBR_MASK));
}

/******************************************TBR******************************************/
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/******************************************TBR******************************************/
/**
 * @brief  Write in Transmitter Data Register (Transmit Data value, 8 bits)
 * @param  UARTx UART Instance
 * @param  Value between Min_Data=0x00 and Max_Data=0xFF
 * @retval None
 */
static inline void LL_UART_TransmitData(reg_uart_t *UARTx, uint8_t Value)
{
    UARTx->TBR = Value;
}

/******************************************TBR******************************************/
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/******************************************TBR******************************************/
/**
 * @brief  Configure UART BRR register for achieving expected Baud Rate value.
 * @param  UARTx UART Instance
 * @param  BaudRate This parameter can be one of the following values:
 *         @arg UART_BAUDRATE_1200 
 *         @arg UART_BAUDRATE_2400 
 *         @arg UART_BAUDRATE_4800 
 *         @arg UART_BAUDRATE_9600 
 *         @arg UART_BAUDRATE_14400 
 *         @arg UART_BAUDRATE_19200 
 *         @arg UART_BAUDRATE_28800 
 *         @arg UART_BAUDRATE_38400 
 *         @arg UART_BAUDRATE_57600 
 *         @arg UART_BAUDRATE_76800 
 *         @arg UART_BAUDRATE_115200 
 *         @arg UART_BAUDRATE_230400 
 *         @arg UART_BAUDRATE_250000 
 *         @arg UART_BAUDRATE_500000 
 *         @arg UART_BAUDRATE_460800 
 *         @arg UART_BAUDRATE_750000 
 *         @arg UART_BAUDRATE_921600 
 *         @arg UART_BAUDRATE_1000000
 *         @arg UART_BAUDRATE_2000000
 * @retval None
 */
static inline void LL_UART_SetBaudRate(reg_uart_t *UARTx, uint32_t BaudRate)
{
    REG_FIELD_WR(UARTx->LCR, UART_LCR_BRWEN, 1);
    UARTx->BRR = BaudRate;
    REG_FIELD_WR(UARTx->LCR, UART_LCR_BRWEN, 0);
}

/******************************************LCR******************************************/
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/******************************************LCR******************************************/
/**
 * @brief  Set Word length (i.e. nb of data bits, excluding start and stop bits)
 * @param  UARTx UART Instance
 * @param  DataWidth This parameter can be one of the following values:
 *         @arg LL_UART_DATAWIDTH_5B
 *         @arg LL_UART_DATAWIDTH_6B
 *         @arg LL_UART_DATAWIDTH_7B
 *         @arg LL_UART_DATAWIDTH_8B
 * @retval None
 */
static inline void LL_UART_SetDataWidth(reg_uart_t *UARTx, uint32_t DataWidth)
{
    MODIFY_REG(UARTx->LCR, UART_LCR_DLS_MASK, DataWidth);
}

/**
 * @brief  Return Word length (i.e. nb of data bits, excluding start and stop bits)
 * @param  UARTx UART Instance
 * @retval Returned value can be one of the following values:
 *         @arg LL_UART_DATAWIDTH_5B
 *         @arg LL_UART_DATAWIDTH_6B
 *         @arg LL_UART_DATAWIDTH_7B
 *         @arg LL_UART_DATAWIDTH_8B
 */
static inline uint32_t LL_UART_GetDataWidth(reg_uart_t *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->LCR, UART_LCR_DLS_MASK));
}

/**
 * @brief  Set the length of the stop bits
 * @param  UARTx UART Instance
 * @param  StopBits This parameter can be one of the following values:
 *         @arg LL_UART_STOPBITS_1
 *         @arg LL_UART_STOPBITS_2
 * @retval None
 */
static inline void LL_UART_SetStopBitsLength(reg_uart_t *UARTx, uint32_t StopBits)
{
    MODIFY_REG(UARTx->LCR, UART_LCR_STOP_MASK, StopBits);
}

/**
 * @brief  Retrieve the length of the stop bits
 * @param  UARTx UART Instance
 * @retval Returned value can be one of the following values:
 *         @arg LL_UART_STOPBITS_1
 *         @arg LL_UART_STOPBITS_2
 */
static inline uint32_t LL_UART_GetStopBitsLength(reg_uart_t *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->LCR, UART_LCR_STOP_MASK));
}

/**
 * @brief  Configure Parity (enabled/disabled and parity mode if enabled).
 * @param  UARTx UART Instance
 * @param  Parity This parameter can be one of the following values:
 *         @arg LL_UART_PARITY_NONE
 *         @arg LL_UART_PARITY_EVEN
 *         @arg LL_UART_PARITY_ODD
 * @retval None
 */
static inline void LL_UART_SetParity(reg_uart_t *UARTx, uint32_t Parity)
{
    MODIFY_REG(UARTx->LCR, UART_LCR_PS_MASK | UART_LCR_PE_MASK, Parity);
}

/**
 * @brief  Return Parity configuration (enabled/disabled and parity mode if enabled)
 * @param  UARTx UART Instance
 * @retval Returned value can be one of the following values:
 *         @arg LL_UART_PARITY_NONE
 *         @arg LL_UART_PARITY_EVEN
 *         @arg LL_UART_PARITY_ODD
 */
static inline uint32_t LL_UART_GetParity(reg_uart_t *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->LCR, UART_LCR_PS_MASK | UART_LCR_PE_MASK));
}
/**
 * @brief  Configure Character frame format (Datawidth, Parity control, Stop Bits)
 * @param  UARTx UART Instance
 * @param  DataWidth This parameter can be one of the following values:
 *         @arg LL_UART_DATAWIDTH_5B
 *         @arg LL_UART_DATAWIDTH_6B
 *         @arg LL_UART_DATAWIDTH_7B
 *         @arg LL_UART_DATAWIDTH_8B
 * @param  Parity This parameter can be one of the following values:
 *         @arg LL_UART_PARITY_NONE
 *         @arg LL_UART_PARITY_EVEN
 *         @arg LL_UART_PARITY_ODD
 * @param  StopBits This parameter can be one of the following values:
 *         @arg LL_UART_STOPBITS_1
 *         @arg LL_UART_STOPBITS_2
 * @retval None
 */
static inline void LL_UART_ConfigCharacter(reg_uart_t *UARTx, uint32_t DataWidth, uint32_t Parity,
                                           uint32_t StopBits)
{
    MODIFY_REG(UARTx->LCR, UART_LCR_PS_MASK | UART_LCR_PE_MASK | UART_LCR_DLS_MASK | UART_LCR_STOP_MASK, Parity | DataWidth | StopBits);
}
/**
 * @brief  Receiver Enable (Receiver is enabled and begins searching for a start bit)
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_EnableDirectionRx(reg_uart_t *UARTx)
{
    SET_BIT(UARTx->LCR, UART_LCR_RXEN_MASK);
}
/**
 * @brief  Receiver Disable
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_DisableDirectionRx(reg_uart_t *UARTx)
{
    CLEAR_BIT(UARTx->LCR, UART_LCR_RXEN_MASK);
}

/**
 * @brief Enable Disconnect 
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_EnableBC(reg_uart_t *UARTx)
{
    SET_BIT(UARTx->LCR, UART_LCR_BC_MASK);
}

/**
 * @brief  Disable Disconnect
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_DisableBC(reg_uart_t *UARTx)
{
    CLEAR_BIT(UARTx->LCR, UART_LCR_BC_MASK);
}

/**
 * @brief Enable Baud rate set
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_EnableBRWEN(reg_uart_t *UARTx)
{
    SET_BIT(UARTx->LCR, UART_LCR_BRWEN_MASK);
}

/**
 * @brief Disable Baud rate set
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_DisableBRWEN(reg_uart_t *UARTx)
{
    CLEAR_BIT(UARTx->LCR, UART_LCR_BRWEN_MASK);
}

/**
 * @brief Enable Receive  timeout
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_EnableRTOEN(reg_uart_t *UARTx)
{
    SET_BIT(UARTx->LCR, UART_LCR_RTOEN_MASK);
}

/**
 * @brief Disable Receive  timeout
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_DisableRTOEN(reg_uart_t *UARTx)
{
    CLEAR_BIT(UARTx->LCR, UART_LCR_RTOEN_MASK);
}

/**
 * @brief Enable High in the former
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_EnableMSB(reg_uart_t *UARTx)
{
    SET_BIT(UARTx->LCR, UART_LCR_MSB_MASK);
}

/**
 * @brief Disable Low in the former
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_EnableLSB(reg_uart_t *UARTx)
{
    CLEAR_BIT(UARTx->LCR, UART_LCR_MSB_MASK);
}

/**
 * @brief Enable Binary data reversal
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_EnableDATAINV(reg_uart_t *UARTx)
{
    SET_BIT(UARTx->LCR, UART_LCR_DATAINV_MASK);
}

/**
 * @brief Disable Binary data reversal
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_DisableDATAINV(reg_uart_t *UARTx)
{
    CLEAR_BIT(UARTx->LCR, UART_LCR_DATAINV_MASK);
}

/**
 * @brief Enable reverse RX pin level
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_EnableRXINV(reg_uart_t *UARTx)
{
    SET_BIT(UARTx->LCR, UART_LCR_RXINV_MASK);
}

/**
 * @brief Disable reverse RX pin level
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_DisableRXINV(reg_uart_t *UARTx)
{
    CLEAR_BIT(UARTx->LCR, UART_LCR_RXINV_MASK);
}

/**
 * @brief Reverse TX pin level is enabled
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_EnableTXINV(reg_uart_t *UARTx)
{
    SET_BIT(UARTx->LCR, UART_LCR_TXINV_MASK);
}

/**
 * @brief Reverse TX pin level is disabled
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_DisableTXINV(reg_uart_t *UARTx)
{
    CLEAR_BIT(UARTx->LCR, UART_LCR_TXINV_MASK);
}

/**
 * @brief Enabled the TX/RX pin exchange function
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_EnableSWAP(reg_uart_t *UARTx)
{
    SET_BIT(UARTx->LCR, UART_LCR_SWAP_MASK);
}

/**
 * @brief  Disable the TX/RX pin exchange function
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_DisableSWAP(reg_uart_t *UARTx)
{
    CLEAR_BIT(UARTx->LCR, UART_LCR_SWAP_MASK);
}

/******************************************MCR******************************************/
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/******************************************MCR******************************************/
/**
 * @brief  Enable IrDA mode
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_EnableIrda(reg_uart_t *UARTx)
{
    SET_BIT(UARTx->MCR, UART_MCR_IREN_MASK);
}

/**
 * @brief  Disable IrDA mode
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_DisableIrda(reg_uart_t *UARTx)
{
    CLEAR_BIT(UARTx->MCR, UART_MCR_IREN_MASK);
}
/**
 * @brief  Enable loopback mode
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_EnableLB(reg_uart_t *UARTx)
{
    SET_BIT(UARTx->MCR, UART_MCR_LBEN_MASK);
}

/**
 * @brief  Disable loopback mode
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_DisableLB(reg_uart_t *UARTx)
{
    CLEAR_BIT(UARTx->MCR, UART_MCR_LBEN_MASK);
}

/**
 * @brief  Enable automatic flow control
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_EnableHWFlowCtrl(reg_uart_t *UARTx)
{
    SET_BIT(UARTx->MCR, UART_MCR_AFCEN_MASK);
}

/**
 * @brief  Disable automatic flow control
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_DisableHWFlowCtrl(reg_uart_t *UARTx)
{
    CLEAR_BIT(UARTx->MCR, UART_MCR_AFCEN_MASK);
}

/**
 * @brief RTSn setting control
 * @param  UARTx UART Instance
 * @param RegisterBit  This parameter can be one of the following values:
 *         @arg  0: automatic flow control is prohibited, RTSn level for high
 *         @arg  1: automatic flow control can make, RTSn level is low
 * @retval None
 */
static inline void LL_UART_SetIrdaRTSCTRL(reg_uart_t *UARTx, uint32_t RegisterBit)
{
    MODIFY_REG(UARTx->MCR, UART_MCR_RTSCTRL_MASK, (RegisterBit << UART_MCR_RTSCTRL_POS)&UART_MCR_RTSCTRL_MASK);
}

/**
 * @brief Enable automatic address detection mode
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_EnableAADEN(reg_uart_t *UARTx)
{
    SET_BIT(UARTx->MCR, UART_MCR_AADEN_MASK);
}

/**
 * @brief Disnable automatic address detection mode
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_DisableAADEN(reg_uart_t *UARTx)
{
    CLEAR_BIT(UARTx->MCR, UART_MCR_AADEN_MASK);
}

/**
 * @brief Enable automatic address detection in common mode
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_EnableAADNOR(reg_uart_t *UARTx)
{
    SET_BIT(UARTx->MCR, UART_MCR_AADNOR_MASK);
}

/**
 * @brief Disable automatic address detection in common mode
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_DisableAADNOR(reg_uart_t *UARTx)
{
    CLEAR_BIT(UARTx->MCR, UART_MCR_AADNOR_MASK);
}

/**
 * @brief Enable the automatic address detection automatic control mode
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_EnableAADDIR(reg_uart_t *UARTx)
{
    SET_BIT(UARTx->MCR, UART_MCR_AADDIR_MASK);
}

/**
 * @brief Disable the automatic address detection automatic control mode
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_DisableAADDIR(reg_uart_t *UARTx)
{
    CLEAR_BIT(UARTx->MCR, UART_MCR_AADDIR_MASK);
}

/**
 * @brief Enable automatic address detection in reverse mode
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_EnableAADINV(reg_uart_t *UARTx)
{
    SET_BIT(UARTx->MCR, UART_MCR_AADINV_MASK);
}

/**
 * @brief Disable automatic address detection in reverse mode
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_DisableAADINV(reg_uart_t *UARTx)
{
    CLEAR_BIT(UARTx->MCR, UART_MCR_AADINV_MASK);
}

/**
 * @brief Enable LIN mode
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_EnableLINEN(reg_uart_t *UARTx)
{
    SET_BIT(UARTx->MCR, UART_MCR_LINEN_MASK);
}

/**
 * @brief Disable LIN mode
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_DisableLINEN(reg_uart_t *UARTx)
{
    CLEAR_BIT(UARTx->MCR, UART_MCR_LINEN_MASK);
}

/**
 * @brief  Indicate if LIN mode is enabled
 * @param  UARTx UART Instance
 * @retval State of bit (1 or 0).
 */
static inline uint32_t LL_UART_IsEnabledLIN(reg_uart_t *UARTx)
{
    return (READ_BIT(UARTx->MCR, UART_MCR_LINEN_MASK) == (UART_MCR_LINEN_MASK));
}

/**
 * @brief Enable LIN mode disconnection requests
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_EnableBKREQ(reg_uart_t *UARTx)
{
    SET_BIT(UARTx->MCR, UART_MCR_BKREQ_MASK);
}

/**
 * @brief Disallow LIN mode disconnection requests
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_DisableBKREQ(reg_uart_t *UARTx)
{
    CLEAR_BIT(UARTx->MCR, UART_MCR_BKREQ_MASK);
}

/**
 * @brief  LIN disconnects the detection word length
 * @param  UARTx UART Instance
 * @param  LINBDLength This parameter can be one of the following values:
 *         @arg DISCONNECT_DETECTION_10BIT
 *         @arg DISCONNECT_DETECTION_11BIT
 * @retval None
 */
static inline void LL_UART_SetLINBrkDetectionLen(reg_uart_t *UARTx, uint32_t LINBDLength)
{
    MODIFY_REG(UARTx->MCR, UART_MCR_LBDL_MASK, LINBDLength);
}

/**
 * @brief  LIN is disconnected from the detection word length
 * @param  UARTx UART Instance
 * @retval Returned value can be one of the following values:
 *         @arg DISCONNECT_DETECTION_10BIT
 *         @arg DISCONNECT_DETECTION_11BIT
 */
static inline uint32_t LL_UART_GetLINBrkDetectionLen(reg_uart_t *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->MCR, UART_MCR_LBDL_MASK));
}
/**
 * @brief Enable the DMA
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_EnableDMAEN(reg_uart_t *UARTx)
{
    SET_BIT(UARTx->MCR, UART_MCR_DMAEN_MASK);
}

/**
 * @brief Disable the DMA
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_DisableDMAEN(reg_uart_t *UARTx)
{
    CLEAR_BIT(UARTx->MCR, UART_MCR_DMAEN_MASK);
}
/**
 * @brief  Indicate if DMA is enabled
 * @param  UARTx UART Instance
 * @retval State of bit (1 or 0).
 */
static inline uint32_t LL_UART_IsEnabledDMAEN(reg_uart_t *UARTx)
{
    return (READ_BIT(UARTx->MCR, UART_MCR_DMAEN_MASK) == (UART_MCR_DMAEN_MASK));
}

/**
 * @brief  Get the data register address used for DMA transfer
 * @param  UARTx UART Instance
 * @retval Address of data register
 */
static inline uint32_t LL_UART_DMA_GetTransmitRegAddr(reg_uart_t *UARTx)
{
    /* return address of DR register */
    return ((uint32_t) & (UARTx->TBR));
}
/**
 * @brief  Get the data register address used for DMA transfer
 * @param  UARTx UART Instance
 * @retval Address of data register
 */
static inline uint32_t LL_UART_DMA_GetReceiveRegAddr(reg_uart_t *UARTx)
{
    /* return address of DR register */
    return ((uint32_t) & (UARTx->RBR));
}
/**
 * @brief Enable automatic baud rate detection
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_EnableABREN(reg_uart_t *UARTx)
{
    SET_BIT(UARTx->MCR, UART_MCR_ABREN_MASK);
}

/**
 * @brief Disable automatic baud rate detection
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_DisableABREN(reg_uart_t *UARTx)
{
    CLEAR_BIT(UARTx->MCR, UART_MCR_ABREN_MASK);
}

/**
 * @brief Enable the automatic baud rate mode
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_EnableABRMOD(reg_uart_t *UARTx)
{
    SET_BIT(UARTx->MCR, UART_MCR_ABRMOD_MASK);
}

/**
 * @brief Disable the automatic baud rate mode
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_DisableABRMOD(reg_uart_t *UARTx)
{
    CLEAR_BIT(UARTx->MCR, UART_MCR_ABRMOD_MASK);
}

/**
 * @brief Enable repetitive automatic baud rate detection
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_EnableABRRST(reg_uart_t *UARTx)
{
    SET_BIT(UARTx->MCR, UART_MCR_ABRRST_MASK);
}

/**
 * @brief Disable repetitive automatic baud rate detection
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_DisableABRRST(reg_uart_t *UARTx)
{
    CLEAR_BIT(UARTx->MCR, UART_MCR_ABRRST_MASK);
}

/**
 * @brief Enable the smart card mode
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_EnableSmartcard(reg_uart_t *UARTx)
{
    SET_BIT(UARTx->MCR, UART_MCR_SCEN_MASK);
}

/**
 * @brief Disable the smart card mode
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_DisableSmartcard(reg_uart_t *UARTx)
{
    CLEAR_BIT(UARTx->MCR, UART_MCR_SCEN_MASK);
}

/**
 * @brief Check if the smart card mode is enable
 * @param  UARTx UART Instance
 * @retval None
 */
static inline uint32_t LL_UART_IsEnabledSmartcard(reg_uart_t *UARTx)
{
    return (READ_BIT(UARTx->MCR, UART_MCR_SCEN_MASK) == (UART_MCR_SCEN_MASK));
}

/**
 * @brief Enable The smart card NACK function i
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_EnableSmartcardNACK(reg_uart_t *UARTx)
{
    SET_BIT(UARTx->MCR, UART_MCR_SCNACK_MASK);
}

/**
 * @brief Disable The smart card NACK function i
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_DisableSmartcardNACK(reg_uart_t *UARTx)
{
    CLEAR_BIT(UARTx->MCR, UART_MCR_SCNACK_MASK);
}

/**
 * @brief  Set Smartcard Retry Count.
 * @param  UARTx UART Instance
 * @param SCCNTValue  Value between Min_Data=0x0 and Max_Data=0x1c
 * @retval None
 */
static inline void LL_UART_SetNodeSCCNT(reg_uart_t *UARTx, uint32_t SCCNTValue)
{
    MODIFY_REG(UARTx->MCR, UART_MCR_SCCNT_MASK, ((SCCNTValue << UART_MCR_SCCNT_POS) & UART_MCR_SCCNT_MASK));
}

/**
 * @brief  Get Smartcard Retry Count.
 * @param  UARTx UART Instance
 * @retval Value between Min_Data=0x0 and Max_Data=0x1c
 */
static inline uint32_t LL_UART_GetNodeSCCNT(reg_uart_t *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->MCR, UART_MCR_SCCNT_MASK) >> UART_MCR_SCCNT_POS);
}

/**
 * @brief Enable the smartcard clock
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_EnableCLKEN(reg_uart_t *UARTx)
{
    SET_BIT(UARTx->MCR, UART_MCR_CLKEN_MASK);
}

/**
 * @brief Enable the smartcard clock
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_DisableCLKEN(reg_uart_t *UARTx)
{
    CLEAR_BIT(UARTx->MCR, UART_MCR_CLKEN_MASK);
}

/**
 * @brief  Enable Single Wire Half-Duplex mode
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_EnableHalfDuplex(reg_uart_t *UARTx)
{
    SET_BIT(UARTx->MCR, UART_MCR_HDSEL_MASK);
}

/**
 * @brief  Disable Single Wire Half-Duplex mode
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_DisableHalfDuplex(reg_uart_t *UARTx)
{
    CLEAR_BIT(UARTx->MCR, UART_MCR_HDSEL_MASK);
}

/**
 * @brief  Indicate if Single Wire Half-Duplex mode is enabled
 * @param  UARTx UART Instance
 * @retval State of bit (1 or 0).
 */
static inline uint32_t LL_UART_IsEnabledHalfDuplex(reg_uart_t *UARTx)
{
    return (READ_BIT(UARTx->MCR, UART_MCR_HDSEL_MASK) == (UART_MCR_HDSEL_MASK));
}

/**
 * @brief  Perform basic configuration of UART for enabling use in Asynchronous Mode (UART)
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_ConfigAsyncMode(reg_uart_t *UARTx)
{
    /* In Asynchronous mode, the following bits must be kept cleared:
    - LINEN, CLKEN bits in the UART_CR2 register,
    - SCEN, IREN and HDSEL bits in the UART_CR3 register.*/
    CLEAR_BIT(UARTx->MCR, (UART_MCR_LINEN_MASK | UART_MCR_CLKEN_MASK | UART_MCR_HDSEL_MASK | UART_MCR_SCEN_MASK | UART_MCR_IREN_MASK));
}

/**
 * @brief  Perform basic configuration of UART for enabling use in Synchronous Mode
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_ConfigSyncMode(reg_uart_t *UARTx)
{
    /* In Synchronous mode, the following bits must be kept cleared:
    - LINEN bit in the UART_CR2 register,
    - SCEN, IREN and HDSEL bits in the UART_CR3 register.*/
    CLEAR_BIT(UARTx->MCR, (UART_MCR_LINEN_MASK | UART_MCR_HDSEL_MASK | UART_MCR_SCEN_MASK | UART_MCR_IREN_MASK));
    /* set the UART/UART in Synchronous mode */
    SET_BIT(UARTx->MCR, UART_MCR_CLKEN_MASK);
}

/**
 * @brief  Perform basic configuration of UART for enabling use in LIN Mode
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_ConfigLINMode(reg_uart_t *UARTx)
{
    /* In LIN mode, the following bits must be kept cleared:
    - STOP and CLKEN bits in the UART_CR2 register,
    - IREN, SCEN and HDSEL bits in the UART_CR3 register.*/
    CLEAR_BIT(UARTx->MCR, (UART_MCR_CLKEN_MASK | UART_MCR_HDSEL_MASK | UART_MCR_SCEN_MASK | UART_MCR_IREN_MASK));
    /* Set the UART/UART in LIN mode */
    SET_BIT(UARTx->MCR, UART_MCR_LINEN_MASK);
}

/**
 * @brief  Perform basic configuration of UART for enabling use in Half Duplex Mode
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_ConfigHalfDuplexMode(reg_uart_t *UARTx)
{
    /* In Half Duplex mode, the following bits must be kept cleared:
    - LINEN and CLKEN bits in the UART_CR2 register,
    - SCEN and IREN bits in the UART_CR3 register.*/
    CLEAR_BIT(UARTx->MCR, (UART_MCR_LINEN_MASK | UART_MCR_CLKEN_MASK | UART_MCR_SCEN_MASK | UART_MCR_IREN_MASK));
    /* set the UART/UART in Half Duplex mode */
    SET_BIT(UARTx->MCR, UART_MCR_HDSEL_MASK);
}

/**
 * @brief  Perform basic configuration of UART for enabling use in Smartcard Mode
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_ConfigSmartcardMode(reg_uart_t *UARTx)
{
    /* In Smartcard mode, the following bits must be kept cleared:
    - LINEN,IREN and HDSEL bits in the MCR register.*/
    /* set the UART/UART in Smartcard mode */
    SET_BIT(UARTx->LCR, UART_LCR_PS_MASK | UART_LCR_PE_MASK);
    SET_BIT(UARTx->MCR, UART_MCR_SCEN_MASK);
    CLEAR_BIT(UARTx->MCR, (UART_MCR_LINEN_MASK | UART_MCR_HDSEL_MASK | UART_MCR_IREN_MASK));
    /* Configure Stop bits to 1.5 bits */
    SET_BIT(UARTx->MCR, UART_MCR_HDSEL_MASK);
    SET_BIT(UARTx->LCR, (UART_LCR_STOP_MASK | UART_MCR_CLKEN_MASK));
}

/**
 * @brief  Perform basic configuration of UART for enabling use in Irda Mode
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_ConfigIrdaMode(reg_uart_t *UARTx)
{
    /* In IRDA mode, the following bits must be kept cleared:
    - LINEN, STOP and CLKEN bits in the UART_CR2 register,
    - SCEN and HDSEL bits in the UART_CR3 register.*/
    CLEAR_BIT(UARTx->MCR, (UART_MCR_LINEN_MASK | UART_MCR_CLKEN_MASK | UART_MCR_SCEN_MASK | UART_MCR_HDSEL_MASK));
    CLEAR_BIT(UARTx->LCR, (UART_LCR_STOP_MASK));
    /* set the UART/UART in IRDA mode */
    SET_BIT(UARTx->MCR, UART_MCR_IREN_MASK);
}

/**
 * @brief  Perform basic configuration of UART for enabling use in Multi processor Mode
 *         (several UARTs connected in a network, one of the UARTs can be the master,
 *         its TX output connected to the RX inputs of the other slaves UARTs).
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_ConfigMultiProcessMode(reg_uart_t *UARTx)
{
    /* In Multi Processor mode, the following bits must be kept cleared:
    - LINEN and CLKEN bits in the UART_CR2 register,
    - IREN, SCEN and HDSEL bits in the UART_CR3 register.*/
    CLEAR_BIT(UARTx->MCR, (UART_MCR_LINEN_MASK | UART_MCR_CLKEN_MASK | UART_MCR_SCEN_MASK | UART_MCR_HDSEL_MASK | UART_MCR_IREN_MASK));
}

/******************************************CR*******************************************/
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/******************************************CR******************************************/
/**
 * @brief  Set Address of the UART node.
 * @param  UARTx UART Instance
 * @param NodeAddress  Value between Min_Data=0x0 and Max_Data=0xFF
 * @retval None
 */
static inline void LL_UART_SetNodeAddress(reg_uart_t *UARTx, uint32_t NodeAddress)
{
    MODIFY_REG(UARTx->CR, UART_CR_ADDR_MASK, (NodeAddress & UART_CR_ADDR_MASK));
}

/**
 * @brief  Return 8 bit Address of the UART node as set in ADD field of CR2.
 * @param  UARTx UART Instance
 * @retval Value between Min_Data=0x0 and Max_Data=0xFF
 */
static inline uint32_t LL_UART_GetNodeAddress(reg_uart_t *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->CR, UART_CR_ADDR_MASK));
}
/**
 * @brief  Set delay numerical.
 * @param  UARTx UART Instance
 * @param DIYNum  Value between Min_Data=0x0 and Max_Data=0xFF
 * @retval None
 */
static inline void LL_UART_SetDLY(reg_uart_t *UARTx, uint32_t DIYNum)
{
    MODIFY_REG(UARTx->CR, UART_CR_DLY_MASK, ((DIYNum << UART_CR_DLY_POS) & UART_CR_DLY_MASK));
}

/**
 * @brief  get delay numerical.
 * @param  UARTx UART Instance
 * @retval Value between Min_Data=0x0 and Max_Data=0xFF
 */
static inline uint32_t LL_UART_GetDLY(reg_uart_t *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->CR, UART_CR_DLY_MASK) >> UART_CR_DLY_POS);
}

/**
 * @brief  Set Irda prescaler value, used for dividing the UART clock source
 *         to achieve the Irda Low Power frequency (8 bits value)
 * @param  UARTx UART Instance
 * @param  PrescalerValue Value between Min_Data=0x00 and Max_Data=0xFF
 * @retval None
 */
static inline void LL_UART_SetIrdaPrescaler(reg_uart_t *UARTx, uint32_t PrescalerValue)
{
    MODIFY_REG(UARTx->CR, UART_CR_PSC_MASK, (PrescalerValue << UART_CR_PSC_POS) & UART_CR_PSC_MASK);
}

/**
 * @brief  Return Irda prescaler value, used for dividing the UART clock source
 *         to achieve the Irda Low Power frequency (8 bits value)
 * @param  UARTx UART Instance
 * @retval Irda prescaler value (Value between Min_Data=0x00 and Max_Data=0xFF)
 */
static inline uint32_t LL_UART_GetIrdaPrescaler(reg_uart_t *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->CR, UART_CR_PSC_MASK));
}

/**
 * @brief  Set Smartcard Guard time value, expressed in nb of baud clocks periods
 *         (GT[7:0] bits : Guard time value)
 * @param  UARTx UART Instance
 * @param  GuardTime Value between Min_Data=0x00 and Max_Data=0xFF
 * @retval None
 */
static inline void LL_UART_SetSmartcardGuardTime(reg_uart_t *UARTx, uint32_t GuardTime)
{
    MODIFY_REG(UARTx->CR, UART_CR_GT_MASK, GuardTime << UART_CR_GT_POS);
}

/**
 * @brief  Return Smartcard Guard time value, expressed in nb of baud clocks periods
 *         (GT[7:0] bits : Guard time value)
 * @param  UARTx UART Instance
 * @retval Smartcard Guard time value (Value between Min_Data=0x00 and Max_Data=0xFF)
 */
static inline uint32_t LL_UART_GetSmartcardGuardTime(reg_uart_t *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->CR, UART_CR_GT_MASK) >> UART_CR_GT_POS);
}

/******************************************RTOR*****************************************/
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/******************************************RTOR*****************************************/
/**
 * @brief  Set Receiver timeout value
 * @param  UARTx UART Instance
 * @param  RTOValue Value between Min_Data=0x00 and Max_Data=0xFFFFFF
 * @retval None
 */
static inline void LL_UART_SetSRTO(reg_uart_t *UARTx, uint32_t RTOValue)
{
    MODIFY_REG(UARTx->RTOR, UART_RTOR_RTO_MASK, RTOValue & UART_RTOR_RTO_MASK);
}

/**
 * @brief  Get Receiver timeout value
 * @param  UARTx UART Instance
 * @retval Smartcard Guard time value (Value between Min_Data=0x00 and Max_Data=0xFFFFFF)
 */
static inline uint32_t LL_UART_GetRTO(reg_uart_t *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->RTOR, UART_RTOR_RTO_MASK));
}

/**
 * @brief  Set Block length
 * @param  UARTx UART Instance
 * @param  BLENvalue Value between Min_Data=0x00 and Max_Data=0xFF
 * @retval None
 */
static inline void LL_UART_SetBLEN(reg_uart_t *UARTx, uint32_t BLENvalue)
{
    MODIFY_REG(UARTx->RTOR, UART_RTOR_BLEN_MASK, (BLENvalue << UART_RTOR_BLEN_POS) & UART_RTOR_BLEN_MASK);
}

/**
 * @brief  Get Block length
 * @param  UARTx UART Instance
 * @retval Smartcard Guard time value (Value between Min_Data=0x00 and Max_Data=0xFF)
 */
static inline uint32_t LL_UART_GetBLEN(reg_uart_t *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->RTOR, UART_RTOR_BLEN_MASK) >> UART_RTOR_BLEN_POS);
}
/******************************************FCR*****************************************/
/*                                                                                    */
/*                                                                                    */
/*                                                                                    */
/*                                                                                    */
/******************************************FCR*****************************************/

/**
 * @brief  Enable the FIFO function
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_EnableFIFO(reg_uart_t *UARTx)
{
    SET_BIT(UARTx->FCR, UART_FCR_FIFOEN_MASK);
}

/**
 * @brief  Disable the FIFO function
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_DisableFIFO(reg_uart_t *UARTx)
{
    CLEAR_BIT(UARTx->FCR, UART_FCR_FIFOEN_MASK);
}

/**
 * @brief  Enable the receiving FIFO reset function
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_EnableRFRST(reg_uart_t *UARTx)
{
    SET_BIT(UARTx->FCR, UART_FCR_RFRST_MASK);
}

/**
 * @brief  Disable the receiving FIFO reset function
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_DisableRFRST(reg_uart_t *UARTx)
{
    CLEAR_BIT(UARTx->FCR, UART_FCR_RFRST_MASK);
}

/**
 * @brief  Enable  the sending FIFO reset function
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_EnableTFRST(reg_uart_t *UARTx)
{
    SET_BIT(UARTx->FCR, UART_FCR_TFRST_MASK);
}

/**
 * @brief  Disable  the sending FIFO reset function
 * @param  UARTx UART Instance
 * @retval None
 */
static inline void LL_UART_DisableTFRST(reg_uart_t *UARTx)
{
    CLEAR_BIT(UARTx->FCR, UART_FCR_TFRST_MASK);
}

/**
 * @brief  Set Receive FIFO trigger threshold
 * @param  UARTx UART Instance
 * @param RXTLValue  This parameter can be one of the following values:
 *         @arg FIFO_TRIGGER_1BYTE
 *         @arg FIFO_TRIGGER_4BYTE
 *         @arg FIFO_TRIGGER_8BYTE
 *         @arg FIFO_TRIGGER_14BYTE
 * @retval None
 */
static inline void LL_UART_SetRXTL(reg_uart_t *UARTx, uint32_t RXTLValue)
{
    MODIFY_REG(UARTx->FCR, UART_FCR_RXTL_MASK, RXTLValue );
}

/**
 * @brief  Return Receive FIFO departure threshold
 * @param  UARTx UART Instance
 * @retval Returned value can be one of the following values:
 *         @arg FIFO_RECEIVE_TRIGGER_1BYTE
 *         @arg FIFO_RECEIVE_TRIGGER_4BYTE
 *         @arg FIFO_RECEIVE_TRIGGER_8BYTE
 *         @arg FIFO_RECEIVETRIGGER_14BYTE
 */
static inline uint32_t LL_UART_GetRXTL(reg_uart_t *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->FCR, UART_FCR_RXTL_MASK));
}

/**
 * @brief  Set transmit FIFO trigger threshold
 * @param  UARTx UART Instance
 * @param TXTLValue  This parameter can be one of the following values:
 *         @arg FIFO_TRABSMIT_TRIGGER_0BYTE
 *         @arg FIFO_TRABSMIT_TRIGGER_1BYTE
 *         @arg FIFO_TRABSMIT_TRIGGER_4BYTE
 *         @arg FIFO_TRABSMIT_TRIGGER_8BYTE
 * @retval None
 */
static inline void LL_UART_SetTXTL(reg_uart_t *UARTx, uint32_t TXTLValue)
{
    MODIFY_REG(UARTx->FCR, UART_FCR_TXTL_MASK, TXTLValue);
}

/**
 * @brief  Return transmit FIFO departure threshold
 * @param  UARTx UART Instance
 * @retval Returned value can be one of the following values:
 *         @arg FIFO_TRABSMIT_TRIGGER_0BYTE
 *         @arg FIFO_TRABSMIT_TRIGGER_1BYTE
 *         @arg FIFO_TRABSMIT_TRIGGER_4BYTE
 *         @arg FIFO_TRABSMIT_TRIGGER_8BYTE
 */
static inline uint32_t LL_UART_GetTXTL(reg_uart_t *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->FCR, UART_FCR_TXTL_MASK));
}

/**
 * @brief  Return Number of data received in FIFO
 * @param  UARTx UART Instance
 * @retval Smartcard Guard time value (Value between Min_Data=0x00 and Max_Data=0x1F)
 */
static inline uint32_t LL_UART_GetRXFL(reg_uart_t *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->FCR, UART_FCR_RXFL_MASK) >> UART_FCR_RXFL_POS);
}

/**
 * @brief  Return Number of data transmit in FIFO
 * @param  UARTx UART Instance
 * @retval Smartcard Guard time value (Value between Min_Data=0x00 and Max_Data=0x3E)
 */
static inline uint32_t LL_UART_GetTXFL(reg_uart_t *UARTx)
{
    return (uint32_t)(READ_BIT(UARTx->FCR, UART_FCR_TXFL_MASK) >> UART_FCR_TXFL_POS);
}

/******************************************SR*****************************************/
/*                                                                                   */
/*                                                                                   */
/*                                                                                   */
/*                                                                                   */
/******************************************SR*****************************************/
/**
 * @brief  Return SR flag
 * @param  UARTx UART Instance
 * @param RegisterBit  This parameter can be one of the following values:
 *        @arg UART_SR_DR
 *        @arg UART_SR_OE
 *        @arg UART_SR_PE
 *        @arg UART_SR_FE
 *        @arg UART_SR_BI
 *        @arg UART_SR_TBEM
 *        @arg UART_SR_TEMT
 *        @arg UART_SR_RFE
 *        @arg UART_SR_BUSY
 *        @arg UART_SR_TFNF
 *        @arg UART_SR_TFEM
 *        @arg UART_SR_RFNE
 *        @arg UART_SR_RFF
 *        @arg UART_SR_DCTS
 *        @arg UART_SR_CTS
 */
static inline uint32_t LL_UART_IsActiveFlag(reg_uart_t *UARTx, uint32_t RegisterBit)
{
    return (uint32_t)(READ_BIT(UARTx->SR, RegisterBit));
}

/******************************************IER*****************************************/
/*                                                                                    */
/*                                                                                    */
/*                                                                                    */
/*                                                                                    */
/******************************************IER*****************************************/
/**
 * @brief  Enable interrupt
 * @param  UARTx UART Instance
 * @param RegisterBit  This parameter can be one of the following values:
 *        @arg UART_IT_RXRD
 *        @arg UART_IT_TXS
 *        @arg UART_IT_RXS
 *        @arg UART_IT_MDDS
 *        @arg UART_IT_RTO
 *        @arg UART_IT_BUSY
 *        @arg UART_IT_ABE
 *        @arg UART_IT_ABTO
 *        @arg UART_IT_LINBK
 *        @arg UART_IT_TC
 *        @arg UART_IT_EOB
 *        @arg UART_IT_CM
 * @retval None
 */
static inline void LL_UART_EnableIT(reg_uart_t *UARTx, uint32_t RegisterBit)
{
    SET_BIT(UARTx->IER, RegisterBit);
}
/******************************************IDR*****************************************/
/*                                                                                    */
/*                                                                                    */
/*                                                                                    */
/*                                                                                    */
/******************************************IDR*****************************************/
/**
 * @brief  Disable interrupt
 * @param  UARTx UART Instance
 * @param RegisterBit  This parameter can be one of the following values:
 *        @arg UART_IT_RXRD
 *        @arg UART_IT_TXS
 *        @arg UART_IT_RXS
 *        @arg UART_IT_MDDS
 *        @arg UART_IT_RTO
 *        @arg UART_IT_BUSY
 *        @arg UART_IT_ABE
 *        @arg UART_IT_ABTO
 *        @arg UART_IT_LINBK
 *        @arg UART_IT_TC
 *        @arg UART_IT_EOB
 *        @arg UART_IT_CM
 * @retval None
 */
static inline void LL_UART_DisableIT(reg_uart_t *UARTx, uint32_t RegisterBit)
{
    SET_BIT(UARTx->IDR, RegisterBit);
}

/******************************************IVC*****************************************/
/*                                                                                    */
/*                                                                                    */
/*                                                                                    */
/*                                                                                    */
/******************************************IVC*****************************************/
/**
 * @brief   Return the interrupt status in effect
 * @param  UARTx UART Instance
 * @param RegisterBit  This parameter can be one of the following values:
 *        @arg UART_IT_RXRD
 *        @arg UART_IT_TXS
 *        @arg UART_IT_RXS
 *        @arg UART_IT_MDDS
 *        @arg UART_IT_RTO
 *        @arg UART_IT_BUSY
 *        @arg UART_IT_ABE
 *        @arg UART_IT_ABTO
 *        @arg UART_IT_LINBK
 *        @arg UART_IT_TC
 *        @arg UART_IT_EOB
 *        @arg UART_IT_CM
 * @retval State of bit (1 or 0).
 */
static inline uint32_t LL_UART_IsEnabledIT(reg_uart_t *UARTx, uint32_t RegisterBit)
{
    return (READ_BIT(UARTx->IVS, RegisterBit) == (RegisterBit));
}

/******************************************RIF*****************************************/
/*                                                                                    */
/*                                                                                    */
/*                                                                                    */
/*                                                                                    */
/******************************************RIF*****************************************/
/**
 * @brief  Returns the interrupt flag bit
 * @param  UARTx UART Instance
 * @param RegisterBit  This parameter can be one of the following values:
 *        @arg UART_IT_RXRD
 *        @arg UART_IT_TXS
 *        @arg UART_IT_RXS
 *        @arg UART_IT_MDDS
 *        @arg UART_IT_RTO
 *        @arg UART_IT_BUSY
 *        @arg UART_IT_ABE
 *        @arg UART_IT_ABTO
 *        @arg UART_IT_LINBK
 *        @arg UART_IT_TC
 *        @arg UART_IT_EOB
 *        @arg UART_IT_CM
 * @retval State of bit (1 or 0).
 */
static inline uint32_t LL_UART_IsActiveFlagIT(reg_uart_t *UARTx, uint32_t RegisterBit)
{
    return (READ_BIT(UARTx->RIF, RegisterBit) == (RegisterBit));
}

/******************************************IFM*****************************************/
/*                                                                                    */
/*                                                                                    */
/*                                                                                    */
/*                                                                                    */
/******************************************IFM*****************************************/

/**
 * @brief  Returns the mask interrupt flag bit
 * @param  UARTx UART Instance
 * @param RegisterBit  This parameter can be one of the following values:
 *        @arg UART_IT_RXRD
 *        @arg UART_IT_TXS
 *        @arg UART_IT_RXS
 *        @arg UART_IT_MDDS
 *        @arg UART_IT_RTO
 *        @arg UART_IT_BUSY
 *        @arg UART_IT_ABE
 *        @arg UART_IT_ABTO
 *        @arg UART_IT_LINBK
 *        @arg UART_IT_TC
 *        @arg UART_IT_EOB
 *        @arg UART_IT_CM
 * @retval State of bit (1 or 0).
 */
static inline uint32_t LL_UART_IsMaskIT(reg_uart_t *UARTx, uint32_t RegisterBit)
{
    return (READ_BIT(UARTx->IFM, RegisterBit) == (RegisterBit));
}

/******************************************ICR*****************************************/
/*                                                                                    */
/*                                                                                    */
/*                                                                                    */
/*                                                                                    */
/******************************************ICR*****************************************/

/**
 * @brief  Clear the interrupt flag bit
 * @param  UARTx UART Instance
 * @param RegisterBit  This parameter can be one of the following values:
 *        @arg UART_IT_RXRD
 *        @arg UART_IT_TXS
 *        @arg UART_IT_RXS
 *        @arg UART_IT_MDDS
 *        @arg UART_IT_RTO
 *        @arg UART_IT_BUSY
 *        @arg UART_IT_ABE
 *        @arg UART_IT_ABTO
 *        @arg UART_IT_LINBK
 *        @arg UART_IT_TC
 *        @arg UART_IT_EOB
 *        @arg UART_IT_CM
 * @retval None
 */
static inline void LL_UART_ClearFlagIT(reg_uart_t *UARTx, uint32_t RegisterBit)
{
    SET_BIT(UARTx->ICR, RegisterBit);
}

/*******************************************************************************
 End of File
 ******************************************************************************/

/** @}*/

/** @}*/

#endif
