#ifndef _HAL_I3C_TARGET_H_
#define _HAL_I3C_TARGET_H_


#include "ls_hal_i3c_conmon.h"


/*! @brief I3C HDR modes. */
typedef enum _i3c_hdr_mode
{
    kI3C_HDRModeNone = 0x00U, /* Do not support HDR mode. */
    // kI3C_HDRModeDDR  = 0x01U, /* HDR-DDR Mode. */
    // kI3C_HDRModeTSP  = 0x02U, /* HDR-TSP Mode. */
    // kI3C_HDRModeTSL  = 0x04U, /* HDR-TSL Mode. */
} i3c_hdr_mode_t;

/*! @brief I3C slave.event */
typedef enum _i3c_slave_event
{
    kI3C_TargetEventNormal     = 0U, /*!< Normal mode. */
    kI3C_TargetEventIBI        = 1U, /*!< In band interrupt event. */
    kI3C_TargetEventMasterReq  = 2U, /*!< Master request event. */
    kI3C_TargetEventHotJoinReq = 3U, /*!< Hot-join event. */
} i3c_slave_event_t;

typedef enum _i3c_slave_transfer_event
{
    kI3C_TargetAddressMatchEvent = 0x01U,     /*!< Received the slave address after a start or repeated start. */
    kI3C_TargetTransmitEvent     = 0x02U,     /*!< Callback is requested to provide data to transmit
                                                    (slave-transmitter role). */
    kI3C_TargetReceiveEvent = 0x04U,          /*!< Callback is requested to provide a buffer in which to place received
                                                     data (slave-receiver role). */
    kI3C_TargetRequiredTransmitEvent = 0x08U, /*!< Callback is requested to provide a buffer in which to place received
                                               data (slave-receiver role). */
    kI3C_TargetStartEvent           = 0x10U,  /*!< A start/repeated start was detected. */
    kI3C_TargetHDRCommandMatchEvent = 0x20U,  /*!< Target Match HDR Command. */
    kI3C_TargetCompletionEvent      = 0x40U,  /*!< A stop was detected, completing the transfer. */
    kI3C_TargetRequestSentEvent     = 0x80U,  /*!< Target request event sent. */
    kI3C_TargetReceivedCCCEvent     = 0x100L, /*!< Target received CCC event, need to handle by application. */

    /*! Bit mask of all available events. */
    kI3C_TargetAllEvents = kI3C_TargetAddressMatchEvent | kI3C_TargetTransmitEvent | kI3C_TargetReceiveEvent |
                          kI3C_TargetStartEvent | kI3C_TargetHDRCommandMatchEvent | kI3C_TargetCompletionEvent |
                          kI3C_TargetRequestSentEvent | kI3C_TargetReceivedCCCEvent,
} i3c_slave_transfer_event_t;

enum _i3c_slave_error_flags
{
    kI3C_TargetErrorOverrunFlag  = I3C_SERRWARN_ORUN_MASK, /*!< Target internal from-bus buffer/FIFO overrun. */
    kI3C_TargetErrorUnderrunFlag = I3C_SERRWARN_URUN_MASK, /*!< Target internal to-bus buffer/FIFO underrun */
    kI3C_TargetErrorUnderrunNakFlag =
        I3C_SERRWARN_URUNNACK_MASK, /*!< Target internal from-bus buffer/FIFO underrun and NACK error */
    kI3C_TargetErrorTermFlag         = I3C_SERRWARN_TERM_MASK,     /*!< Terminate error from master */
    kI3C_TargetErrorInvalidStartFlag = I3C_SERRWARN_INVSTART_MASK, /*!< Target invalid start flag */
    kI3C_TargetErrorSdrParityFlag    = I3C_SERRWARN_SPAR_MASK,     /*!< SDR parity error */
    kI3C_TargetErrorHdrParityFlag    = I3C_SERRWARN_HPAR_MASK,     /*!< HDR parity error */
    kI3C_TargetErrorHdrCRCFlag       = I3C_SERRWARN_HCRC_MASK,     /*!< HDR-DDR CRC error */
    kI3C_TargetErrorS0S1Flag         = I3C_SERRWARN_S0S1_MASK,     /*!< S0 or S1 error */
    kI3C_TargetErrorOverreadFlag     = I3C_SERRWARN_OREAD_MASK,    /*!< Over-read error */
    kI3C_TargetErrorOverwriteFlag    = I3C_SERRWARN_OWRITE_MASK,   /*!< Over-write error */
};

enum _i3c_slave_flags
{
    kI3C_TargetNotStopFlag = I3C_SSTATUS_STNOTSTOP_MASK,     /*!< Target status not stop flag */
    kI3C_TargetMessageFlag = I3C_SSTATUS_STMSG_MASK,         /*!< Target status message, indicating slave is
                                                                     listening to the bus traffic or responding */
    kI3C_TargetRequiredReadFlag = I3C_SSTATUS_STREQRD_MASK,  /*!< Target status required, either is master doing SDR
                                                               read from slave, or is IBI pushing out. */
    kI3C_TargetRequiredWriteFlag = I3C_SSTATUS_STREQWR_MASK, /*!< Target status request write, master is doing SDR
                                                               write to slave, except slave in ENTDAA mode */
    kI3C_TargetBusDAAFlag     = I3C_SSTATUS_STDAA_MASK,      /*!< I3C bus is in ENTDAA mode */
    kI3C_TargetBusHDRModeFlag = I3C_SSTATUS_STHDR_MASK,      /*!< I3C bus is in HDR mode */
    kI3C_TargetBusStartFlag = I3C_SSTATUS_START_MASK, /*!< Start/Re-start event is seen since the bus was last cleared */
    kI3C_TargetMatchedFlag  = I3C_SSTATUS_MATCHED_MASK, /*!< Target address(dynamic/static) matched since last cleared */
    kI3C_TargetBusStopFlag  = I3C_SSTATUS_STOP_MASK,    /*!<Stop event is seen since the bus was last cleared */
    kI3C_TargetRxReadyFlag  = I3C_SSTATUS_RXPEND_MASK, /*!< Rx data ready in rx buffer flag */
    kI3C_TargetTxReadyFlag  = I3C_SSTATUS_TXNOTFULL_MASK, /*!< Tx buffer ready for Tx data flag */

    kI3C_TargetHDRCommandMatchFlag = I3C_SSTATUS_HDRMATCH_MASK, /*!< High data rate command match */
    kI3C_TargetCCCHandledFlag =
        I3C_SSTATUS_CHANDLED_MASK, /*!< Target received Common command code is handled by I3C module */
    kI3C_TargetEventSentFlag             = I3C_SSTATUS_EVENT_MASK,  /*!< Target IBI/P2P/MR/HJ event has been sent */
    kI3C_TargetIbiDisableFlag            = I3C_SSTATUS_IBIDIS_MASK, /*!< Target in band interrupt is disabled. */
    kI3C_TargetMasterRequestDisabledFlag = I3C_SSTATUS_MRDIS_MASK,  /*!< Target master request is disabled. */
    kI3C_TargetHotJoinDisabledFlag       = I3C_SSTATUS_HJDIS_MASK,  /*!< Target Hot-Join is disabled. */
    /*! All flags which are cleared by the driver upon starting a transfer. */
    kI3C_TargetClearFlags = kI3C_TargetBusStartFlag | kI3C_TargetMatchedFlag | kI3C_TargetBusStopFlag,

    kI3C_TargetEvent_TargetReset = I3C_SSTATUS_SLVRST_MASK,
    kI3C_TargetReceivedCCCFlag     = I3C_SSTATUS_CCC_MASK,      /*!< Target received Common command code */
    kI3C_TargetErrorFlag           = I3C_SSTATUS_ERRWARN_MASK,  /*!< Error occurred flag */
    kI3C_TargetDynamicAddrChangedFlag =
        I3C_SSTATUS_DACHG_MASK, /*!< Target dynamic address has been assigned, re-assigned, or lost */
    kI3C_TargetCrrReceived = I3C_SSTATUS_CRRQUSET_MASK,
    kI3C_TargetAllIrqFlags = kI3C_TargetBusStartFlag | kI3C_TargetMatchedFlag | kI3C_TargetBusStopFlag |
                            kI3C_TargetRxReadyFlag | kI3C_TargetTxReadyFlag | kI3C_TargetDynamicAddrChangedFlag |
                            kI3C_TargetReceivedCCCFlag | kI3C_TargetErrorFlag | kI3C_TargetHDRCommandMatchFlag |
                            kI3C_TargetCCCHandledFlag | kI3C_TargetCrrReceived | kI3C_TargetEventSentFlag,

};

#define EVENT_ID_CCC            (0x00000001U)
#define EVENT_ID_SRESET         (0x00000002U)
#define EVENT_ID_DACHG          (0x00000004U)
#define EVENT_ID_CRRQUSET       (0x00000008U)
#define EVENT_ID_EVENT_SEND     (0x00000010U)

#define HAL_I3C_IT_EVENT_SEND   I3C_SSTATUS_EVENT_MASK
#define HAL_I3C_IT_CCC          I3C_SSTATUS_CCC_MASK
#define HAL_I3C_IT_SLVRST       I3C_SSTATUS_SLVRST_MASK
#define HAL_I3C_IT_DACHG        I3C_SSTATUS_DACHG_MASK
#define HAL_I3C_IT_CRRQUSET     I3C_SSTATUS_CRRQUSET_MASK
#define HAL_I3C_IT_TARGET_ALL_EVENT  (HAL_I3C_IT_EVENT_SEND|HAL_I3C_IT_CCC|HAL_I3C_IT_SLVRST|HAL_I3C_IT_DACHG|HAL_I3C_IT_CRRQUSET)


/*! @brief I3C target status return codes. */
enum
{
    kStatus_Success,
    kStatus_I3C_Busy, /*!< The master is already performing a transfer. */
    kStatus_I3C_Idle, /*!< The slave driver is idle. */
    kStatus_I3C_Nak, /*!< The slave device sent a NAK in response to an address. */
    kStatus_I3C_WriteAbort, /*!< The slave device sent a NAK in response to a write. */
    kStatus_I3C_Term, /*!< The master terminates slave read. */
    kStatus_I3C_HdrParityError, /*!< Parity error from DDR read. */
    kStatus_I3C_CrcError, /*!< CRC error from DDR read. */
    kStatus_I3C_ReadFifoError, /*!< Read from M/SRDATAB register when FIFO empty. */
    kStatus_I3C_WriteFifoError, /*!< Write to M/SWDATAB register when FIFO full. */
    kStatus_I3C_MsgError, /*!< Message SDR/DDR mismatch or read/write message in wrong state */
    kStatus_I3C_InvalidReq, /*!< Invalid use of request. */
    kStatus_I3C_Timeout, /*!< The module has stalled too long in a frame. */
    kStatus_I3C_TargetCountExceed, /*!< The I3C slave count has exceed the definition in I3C_MAX_DEVCNT. */
    kStatus_I3C_IBIWon, /*!< The I3C slave event IBI or MR or HJ won the arbitration on a header address. */
    kStatus_I3C_OverrunError, /*!< Target internal from-bus buffer/FIFO overrun. */
    kStatus_I3C_UnderrunError, /*!< Target internal to-bus buffer/FIFO underrun */
    kStatus_I3C_UnderrunNak, /*!< Target internal from-bus buffer/FIFO underrun and NACK error */
    kStatus_I3C_InvalidStart, /*!< Target invalid start flag */
    kStatus_I3C_SdrParityError, /*!< SDR parity error */
    kStatus_I3C_S0S1Error, /*!< S0 or S1 error */
};

/*! @brief Common sets of flags used by the driver. */
enum _i3c_flag_constants
{
    /*! All flags which are cleared by the driver upon starting a pXferData. */
    kTargetClearFlags = kI3C_TargetBusStartFlag | kI3C_TargetMatchedFlag | kI3C_TargetBusStopFlag,

    /*! IRQ sources enabled by the non-blocking transactional API. */
    kTargetIrqFlags = kI3C_TargetBusStartFlag | kI3C_TargetMatchedFlag | kI3C_TargetBusStopFlag | kI3C_TargetRxReadyFlag |
                     kI3C_TargetDynamicAddrChangedFlag | kI3C_TargetReceivedCCCFlag | kI3C_TargetErrorFlag |
                     kI3C_TargetHDRCommandMatchFlag | kI3C_TargetCCCHandledFlag | kI3C_TargetEventSentFlag,

    /*! Errors to check for. */
    kTargetErrorFlags = kI3C_TargetErrorOverrunFlag | kI3C_TargetErrorUnderrunFlag | kI3C_TargetErrorUnderrunNakFlag |
                       kI3C_TargetErrorTermFlag | kI3C_TargetErrorInvalidStartFlag | kI3C_TargetErrorSdrParityFlag |
                       kI3C_TargetErrorHdrParityFlag | kI3C_TargetErrorHdrCRCFlag | kI3C_TargetErrorS0S1Flag |
                       kI3C_TargetErrorOverreadFlag | kI3C_TargetErrorOverwriteFlag,
};

HAL_StatusTypeDef HAL_I3C_Tgt_Receive_IT(I3C_HandleTypeDef *hi3c, I3C_XferTypeDef *pXferData);
HAL_StatusTypeDef HAL_I3C_Tgt_Transmit_IT(I3C_HandleTypeDef *hi3c, I3C_XferTypeDef *pXferData);
HAL_StatusTypeDef HAL_I3C_Tgt_IBIReq_IT(I3C_HandleTypeDef *hi3c, const uint8_t *pPayload, uint8_t payloadSize);
HAL_StatusTypeDef HAL_I3C_Tgt_HJReq_IT(I3C_HandleTypeDef *hi3c);
HAL_StatusTypeDef HAL_I3C_Tgt_CRReq_IT(I3C_HandleTypeDef *hi3c);
HAL_StatusTypeDef HAL_I3C_Tgt_Start_DMA_Transmit(I3C_HandleTypeDef *hi3c);
HAL_StatusTypeDef HAL_I3C_Tgt_Start_DMA_Receive(I3C_HandleTypeDef *hi3c);
HAL_StatusTypeDef HAL_I3C_Tgt_Transmit_DMA(I3C_HandleTypeDef *hi3c, I3C_XferTypeDef *pXferData);
HAL_StatusTypeDef HAL_I3C_Tgt_Receive_DMA(I3C_HandleTypeDef *hi3c, I3C_XferTypeDef *pXferData);
HAL_StatusTypeDef HAL_I3C_Target_ActivateNotification(I3C_HandleTypeDef *hi3c,uint32_t interruptMask);
HAL_StatusTypeDef HAL_I3C_Target_Init(I3C_HandleTypeDef *hi3c);

#endif /* _HAL_I3C_TARGET_H_ */
