#include "ls_hal_fdcan.h"
#include "ls_msp_fdcan.h"
#include "ls_dbg.h"
#include "systick.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "csi_rv32_gcc.h"
#include "log.h"

#define IS_FDCAN_FRAME_FORMAT(FORMAT) (((FORMAT) == FDCAN_FRAME_CLASSIC  ) || \
                                       ((FORMAT) == FDCAN_FRAME_FD_NO_BRS) || \
                                       ((FORMAT) == FDCAN_FRAME_FD_BRS   ) || \
                                       ((FORMAT) == FDCAN_FRAME_FD_BRS_PEX))

#define IS_FDCAN_MODE(MODE) (((MODE) == FDCAN_MODE_NORMAL              ) || \
                             ((MODE) == FDCAN_MODE_LOOPBACK            ) || \
                             ((MODE) == FDCAN_MODE_ACK_FORBIDDEN       ) || \
                             ((MODE) == FDCAN_MODE_SELF_ACK            ) || \
                             ((MODE) == FDCAN_MODE_BUS_MONITORING      ) || \
                             ((MODE) == FDCAN_MODE_RESTRICTED_OPERATION) || \
                             ((MODE) == FDCAN_MODE_TEST))

#define IS_FDCAN_ID_TYPE(ID_TYPE) (((ID_TYPE) == FDCAN_STANDARD_ID) || \
                                   ((ID_TYPE) == FDCAN_EXTENDED_ID))

#define IS_FDCAN_FRAME_TYPE(TYPE) (((TYPE) == FDCAN_DATA_FRAME  ) || \
                                   ((TYPE) == FDCAN_REMOTE_FRAME))

#define IS_FDCAN_DLC(DLC) (((DLC) == FDCAN_DLC_BYTES_0 ) || \
                           ((DLC) == FDCAN_DLC_BYTES_1 ) || \
                           ((DLC) == FDCAN_DLC_BYTES_2 ) || \
                           ((DLC) == FDCAN_DLC_BYTES_3 ) || \
                           ((DLC) == FDCAN_DLC_BYTES_4 ) || \
                           ((DLC) == FDCAN_DLC_BYTES_5 ) || \
                           ((DLC) == FDCAN_DLC_BYTES_6 ) || \
                           ((DLC) == FDCAN_DLC_BYTES_7 ) || \
                           ((DLC) == FDCAN_DLC_BYTES_8 ) || \
                           ((DLC) == FDCAN_DLC_BYTES_12) || \
                           ((DLC) == FDCAN_DLC_BYTES_16) || \
                           ((DLC) == FDCAN_DLC_BYTES_20) || \
                           ((DLC) == FDCAN_DLC_BYTES_24) || \
                           ((DLC) == FDCAN_DLC_BYTES_32) || \
                           ((DLC) == FDCAN_DLC_BYTES_48) || \
                           ((DLC) == FDCAN_DLC_BYTES_64))
#define IS_FDCAN_ESI(ESI) (((ESI) == FDCAN_ESI_ACTIVE ) || \
                           ((ESI) == FDCAN_ESI_PASSIVE))
#define IS_FDCAN_BRS(BRS) (((BRS) == FDCAN_BRS_OFF) || \
                           ((BRS) == FDCAN_BRS_ON ))
#define IS_FDCAN_FDF(FDF) (((FDF) == FDCAN_CLASSIC_CAN) || \
                           ((FDF) == FDCAN_FD_CAN     )) 
#define IS_FDCAN_TX_LOCATION(LOCATION) (((LOCATION) == FDCAN_TX_BUFFER1) || \
                                        ((LOCATION) == FDCAN_TX_BUFFER2) || \
                                        ((LOCATION) == FDCAN_TX_BUFFER3) || \
                                        ((LOCATION) == FDCAN_TX_BUFFER4))
#define IS_FDCAN_FILTERINDEX(INDEX) (((INDEX) == FDCAN_FILTER_BIT_A) || \
                                     ((INDEX) == FDCAN_FILTER_BIT_B) || \
                                     ((INDEX) == FDCAN_FILTER_BIT_C) || \
                                     ((INDEX) == FDCAN_FILTER_RANG))
#define IS_FDCAN_FILTERTYPE(TYPE) (((TYPE) == FDCAN_FILTER_CLASSIC_BASIC) || \
                                   ((TYPE) == FDCAN_FILTER_CLASSIC_EXTEND) || \
                                   ((TYPE) == FDCAN_FILTER_FD_BASIC) || \
                                   ((TYPE) == FDCAN_FILTER_FD_EXTEND))                                     

#define IS_FDCAN_MAX_VALUE(VALUE, MAX) ((VALUE) <= (MAX))

#define FDCAN_TIMEOUT_VALUE  50U

static const uint8_t DLCtoBytes[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20, 24, 32, 48, 64};

static bool FDCAN_BusState_poll(va_list va)
{
    FDCAN_HandleTypeDef *hfdcan = va_arg(va,FDCAN_HandleTypeDef *);
    uint32_t flag = va_arg(va,uint32_t);
    if(hfdcan->Instance->EWL_ERP & flag)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool FDCAN_State_poll(va_list va)
{
    FDCAN_HandleTypeDef *hfdcan = va_arg(va,FDCAN_HandleTypeDef *);
    uint32_t flag = va_arg(va,uint32_t);

    if(hfdcan->Instance->INT_STT & flag)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool FDCAN_RXstatus_poll(va_list va)
{
    FDCAN_HandleTypeDef *hfdcan = va_arg(va,FDCAN_HandleTypeDef *);
    uint32_t flag = va_arg(va,uint32_t);
    uint32_t value = va_arg(va,uint32_t);

    if((hfdcan->Instance->RX_STT & flag ) == value)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static void FDCAN_SetNominalBittiming(reg_fdcan_t *FDCANx,FDCAN_ClockConfigTypeDef *NominalBittiming)
{
    uint32_t prop_seg = NominalBittiming->PROP;
    uint32_t phase_seg1 = NominalBittiming->PH1;

    LS_ASSERT(REG_FIELD_RD(FDCANx->MODE_CFG,FDCAN_ENA) == 0);

    if( phase_seg1 > 63)
    {
        prop_seg += phase_seg1 - 63;
        phase_seg1 = 63;
        NominalBittiming->PROP = prop_seg;
        NominalBittiming->PH1 = phase_seg1;
    }

    FDCANx->BTR = (FIELD_BUILD(FDCAN_SJW,NominalBittiming->SJW)
                    |FIELD_BUILD(FDCAN_BRP,NominalBittiming->Prescaler)
                    |FIELD_BUILD(FDCAN_PH2,NominalBittiming->PH2)
                    |FIELD_BUILD(FDCAN_PH1,NominalBittiming->PH1)
                    |FIELD_BUILD(FDCAN_RPOP,NominalBittiming->PROP));
}

static void FDCAN_SetDataBittiming(reg_fdcan_t *FDCANx,FDCAN_ClockConfigTypeDef *DataBitting)
{
    uint32_t prop_seg = DataBitting->PROP;
    uint32_t phase_seg1 = DataBitting->PH1;

    if( phase_seg1 > 31)
    {
        prop_seg += phase_seg1 - 31;
        phase_seg1 = 31;
        DataBitting->PROP = prop_seg;
        DataBitting->PH1 = phase_seg1;
    }

    FDCANx->BTR_FD = (FIELD_BUILD(FDCAN_SJW_FD,DataBitting->SJW)
                    |FIELD_BUILD(FDCAN_BRP_FD,DataBitting->Prescaler)
                    |FIELD_BUILD(FDCAN_PH2_FD,DataBitting->PH2)
                    |FIELD_BUILD(FDCAN_PH1_FD,DataBitting->PH1)
                    |FIELD_BUILD(FDCAN_PROP_FD,DataBitting->PROP));
}

static void FDCAN_Base_SetConfig(FDCAN_HandleTypeDef *hfdcan)
{
    uint32_t tmpcfg = 0;
    LS_ASSERT(IS_FDCAN_FRAME_FORMAT(hfdcan->Init.FrameFormat));
    LS_ASSERT(IS_FDCAN_MODE(hfdcan->Init.Mode));

    /* Set the nominal bit timing register */
    FDCAN_SetNominalBittiming(hfdcan->Instance,&hfdcan->Init.NominalBittiming);

    /* If FD operation with BRS is selected, set the data bit timing register */
    if(hfdcan->Init.FrameFormat & FDCAN_FRAME_FD_BRS)
    {
        FDCAN_SetDataBittiming(hfdcan->Instance,&hfdcan->Init.DataBitting);
    }

    /* Get the MODE_CFG register value */
    tmpcfg = hfdcan->Instance->MODE_CFG;

    /* Set FDCAN Frame Format */
    MODIFY_REG(tmpcfg,FDCAN_FRAME_FD_BRS_PEX,hfdcan->Init.FrameFormat);

    if(hfdcan->Init.FilterEnble == ENABLE)
    {
        SET_BIT(tmpcfg,FDCAN_AFM_MASK);
    }
    else
    {
        CLEAR_BIT(tmpcfg,FDCAN_AFM_MASK);
    }

    if(hfdcan->Init.FDRF == ENABLE)
    {
        SET_BIT(tmpcfg,FDCAN_FDRF_MASK);
    }
    else
    {
        CLEAR_BIT(tmpcfg,FDCAN_FDRF_MASK);
    }

    /* Set FDCAN ISO FDCAD mode */
    if(hfdcan->Init.ISOFD == ENABLE)
    {
        CLEAR_BIT(tmpcfg,FDCAN_NISOFD_MASK);
    }
    else
    {
        SET_BIT(tmpcfg,FDCAN_NISOFD_MASK);
    }
    
    /* Set FDCAN Operating Mode */
    if(hfdcan->Init.Mode != FDCAN_MODE_NORMAL)
    {
        MODIFY_REG(tmpcfg,
            FDCAN_MODE_LOOPBACK|FDCAN_MODE_ACK_FORBIDDEN|FDCAN_MODE_SELF_ACK| \
            FDCAN_MODE_BUS_MONITORING|FDCAN_MODE_RESTRICTED_OPERATION|FDCAN_MODE_TEST,
            hfdcan->Init.Mode);
    }

    if(hfdcan->Init.TTCM == ENABLE)
    {
        SET_BIT(tmpcfg,FDCAN_TTTM_MASK);
        /*  SYS_AWO->FD_CAN
         *  bit00: timestamp_enable
         *  bit01: timestamp_clear
         *  bit15: timestamp_precaler
         *  bit23: timestamp_step
         *  bit24: fdcan_scs
         */ 
        SYSC_AWO->FD_CAN = 0x01010001;
    }
    else
    {
        CLEAR_BIT(tmpcfg,FDCAN_TTTM_MASK);
    }

    if(hfdcan->Init.AutoRetransmission == ENABLE)
    {
        SET_BIT(tmpcfg,FDCAN_RTRLE_MASK);
        MODIFY_REG(tmpcfg,FDCAN_RTRTH_MASK,(hfdcan->Init.reTransNbr << FDCAN_RTRTH_POS)&FDCAN_RTRTH_MASK);
    }
    else
    {
        CLEAR_BIT(tmpcfg,FDCAN_RTRLE_MASK);
    }

    /* When RX_DATA register is read, read pointer of RX buﬀer FIFO is automatically */
    SET_BIT(tmpcfg,FDCAN_RXBAM_MASK);

    /* Set MODE_CFG */
    hfdcan->Instance->MODE_CFG = tmpcfg;

    __HAL_FDCAN_CMD_SET(hfdcan,FDCAN_FLUSH_RXBUF_FLAG);
} 

static bool FDCAN_GetDeviceID(reg_fdcan_t *FDCANx)
{
    /*Device Default ID is 0xCAFD*/
    return (REG_FIELD_RD(FDCANx->ID_VER,FDCAN_DEV_ID) == 0xCAFD);
}

HAL_StatusTypeDef HAL_FDCAN_Init(FDCAN_HandleTypeDef *hfdcan)
{
    if(hfdcan == NULL)
    {
        return HAL_ERROR;
    }

    if(hfdcan->State == HAL_FDCAN_STATE_RESET)
    {
        /* Allocate lock resource and initialize it */
        hfdcan->Lock = HAL_UNLOCKED;

        /* Init the low level hardware */
        HAL_FDCAN_MSP_Init(hfdcan);
        HAL_FDCAN_MSP_Busy_Set();
    }

    /*After power-up CTU CAN FD shall be reset*/
    SET_BIT(hfdcan->Instance->MODE_CFG,FDCAN_RST_MASK);

    __NOP(); __NOP(); __NOP(); __NOP();

    if(FDCAN_GetDeviceID(hfdcan->Instance) != true)
    {
        hfdcan->ErrorCode = HAL_FDCAN_ERROR_NOT_READY;
        hfdcan->State = HAL_FDCAN_STATE_ERROR;
        return HAL_ERROR;
    }

    FDCAN_Base_SetConfig(hfdcan);

    /* Initialize the error code */
    hfdcan->ErrorCode = HAL_FDCAN_ERROR_NONE;

    /* Initialize the FDCAN state */
    hfdcan->State = HAL_FDCAN_STATE_READY;

    /* Return function status */
    return HAL_OK;
}

HAL_StatusTypeDef HAL_FDCAN_DeInit(FDCAN_HandleTypeDef* hfdcan)
{
    /* Check FDCAN handle */
    if(hfdcan == NULL)
    {
        return HAL_ERROR;
    }

    /* Stop the FDCAN module */
    HAL_FDCAN_Stop(hfdcan);

    /* DeInit the low level hardware */
    HAL_FDCAN_MSP_DeInit(hfdcan);

    /* Reset the FDCAN ErrorCode */
    hfdcan->ErrorCode = HAL_FDCAN_ERROR_NONE;

    /* Change FDCAN state */
    hfdcan->State = HAL_FDCAN_STATE_RESET;

    /* Return function status */
    return HAL_OK;
}

HAL_StatusTypeDef HAL_FDCAN_Start(FDCAN_HandleTypeDef *hfdcan)
{
    uint32_t tickstart = 0U;
    uint32_t timeout = SYSTICK_MS2TICKS(FDCAN_TIMEOUT_VALUE);

    if(hfdcan->State == HAL_FDCAN_STATE_READY)
    {
        /* Change FDCAN peripheral state */
        hfdcan->State = HAL_FDCAN_STATE_BUSY;

        __HAL_FDCAN_ENABLE(hfdcan);

        /* Get timeout */
        tickstart = systick_get_value();

        if(systick_poll_timeout(tickstart,timeout,FDCAN_BusState_poll,hfdcan,FDCAN_ERA_MASK))
        {
            /* Update error code */
            hfdcan->ErrorCode |= HAL_FDCAN_ERROR_TIMEOUT;

            /* Change FDCAN state */
            hfdcan->State = HAL_FDCAN_STATE_ERROR;

            return HAL_ERROR;
        }

        /* Reset the FDCAN ErrorCode */
        hfdcan->ErrorCode = HAL_FDCAN_ERROR_NONE;

        /* Return function status */
        return HAL_OK;
    }
    else
    {
        /* Update error code */
        hfdcan->ErrorCode |= HAL_FDCAN_ERROR_NOT_READY;

        return HAL_ERROR;
    }
}

void FDCAN_Check_TXTBUF_Wait_Abort(FDCAN_HandleTypeDef *hfdcan)
{
    uint32_t TXTBufferNb = 0;
    uint32_t buf_status = 0;

    TXTBufferNb = REG_FIELD_RD(hfdcan->Instance->TX_CMD_INFO,FDCAN_BUF_CNT);

    for(uint8_t i = 0; i < TXTBufferNb; i++)
    {
        buf_status = (READ_REG(hfdcan->Instance->TX_STT)>>(i*4))&0xf;
        if(buf_status & 0x03) // FDCAN_TX_READY、FDCAN_TX_TRANSMITTING、FDCAN_TX_ABORTTING
        {
            HAL_FDCAN_AbortTxRequest(hfdcan,i);
        }
    }
}

HAL_StatusTypeDef HAL_FDCAN_Stop(FDCAN_HandleTypeDef *hfdcan)
{
    if(hfdcan->State == HAL_FDCAN_STATE_BUSY)
    {
        FDCAN_Check_TXTBUF_Wait_Abort(hfdcan);

        __HAL_FDCAN_DISABLE(hfdcan);

        /* Change FDCAN peripheral state */
        hfdcan->State = HAL_FDCAN_STATE_READY;

        /* Return function status */
        return HAL_OK;
    }
    else
    {
        /* Update error code */
        hfdcan->ErrorCode |= HAL_FDCAN_ERROR_NOT_STARTED;
        return HAL_ERROR;
    }
}

bool HAL_FDCAN_TXT_Buffer_Accessible(FDCAN_HandleTypeDef *hfdcan,uint32_t BufferIndex)
{
    uint32_t buf_status = 0;
    buf_status = (READ_REG(hfdcan->Instance->TX_STT)>>(BufferIndex*4))&0xf;
    if (buf_status == FDCAN_TX_READY || buf_status == FDCAN_TX_TRANSMITTING || buf_status == FDCAN_TX_ABORTTING)
        return false;

    return true;
}

static HAL_StatusTypeDef FDCAN_CopyMessageToBuffer(FDCAN_HandleTypeDef *hfdcan, FDCAN_TxMSGTypeDef *pTxMsg, uint8_t *pTxData)
{
    uint32_t TxElementW1 = 0;
    uint32_t TxElementW2 = 0;
    uint32_t *TxAddress;
    uint32_t ByteCounter;

    /* Build first word of Tx header element */
    TxElementW1 = pTxMsg->DataLength | 
                  pTxMsg->TxFrameType |
                  pTxMsg->IdType |
                  pTxMsg->FDFormat |
                  pTxMsg->BitRateSwitch |
                  pTxMsg->ErrorStateIndicator;
    
    /* Build second word of Tx header element */
    if(pTxMsg->IdType == FDCAN_STANDARD_ID)
    {
        TxElementW2 = pTxMsg->Identifier << FDCAN_TXTB_DATA_2_IDENTIFIER_BASE_POS;
    }
    else /* pTxHeader->IdType == FDCAN_EXTENDED_ID */
    {
        TxElementW2 = pTxMsg->Identifier;
    }

    /* Calculate Tx element address */
    TxAddress = (uint32_t *)(&(hfdcan->Instance->TXTB1_DATA_1) + (pTxMsg->BufferIndex*0x100));

    /* Write Tx element header to the message RAM */
    *TxAddress++ = TxElementW1;
    *TxAddress++ = TxElementW2;
    *TxAddress++ = pTxMsg->TimestampLow;
    *TxAddress++ = pTxMsg->TimestampUpper;

    if(pTxMsg->FDFormat != FDCAN_REMOTE_FRAME)
    {
        for(ByteCounter = 0; ByteCounter < DLCtoBytes[pTxMsg->DataLength]; ByteCounter += 4)
        {
            *TxAddress++ = ((pTxData[ByteCounter+3] << 24) |
                            (pTxData[ByteCounter+2] << 16) |
                            (pTxData[ByteCounter+1] << 8) |
                            pTxData[ByteCounter]);
        }
    }

    /* Return function status */
    return HAL_OK;
}

HAL_StatusTypeDef HAL_FDCAN_AddMessageToTxBuffer(FDCAN_HandleTypeDef *hfdcan, FDCAN_TxMSGTypeDef *pTxMsg, uint8_t *pTxData)
{
    /* Check function parameters */
    LS_ASSERT(IS_FDCAN_ID_TYPE(pTxMsg->IdType));
    if(pTxMsg->IdType == FDCAN_STANDARD_ID)
    {
        LS_ASSERT(IS_FDCAN_MAX_VALUE(pTxMsg->Identifier, 0x7FF));
    }
    else /* pTxMsg->IdType == FDCAN_EXTENDED_ID */
    {
        LS_ASSERT(IS_FDCAN_MAX_VALUE(pTxMsg->Identifier, 0x1FFFFFFF));
    }
    LS_ASSERT(IS_FDCAN_FRAME_TYPE(pTxMsg->TxFrameType));
    LS_ASSERT(IS_FDCAN_DLC(pTxMsg->DataLength));
    LS_ASSERT(IS_FDCAN_ESI(pTxMsg->ErrorStateIndicator));
    LS_ASSERT(IS_FDCAN_BRS(pTxMsg->BitRateSwitch));
    LS_ASSERT(IS_FDCAN_FDF(pTxMsg->FDFormat));
    LS_ASSERT(IS_FDCAN_TX_LOCATION(pTxMsg->BufferIndex));

    if((hfdcan->State == HAL_FDCAN_STATE_READY) || (hfdcan->State == HAL_FDCAN_STATE_BUSY))
    {
        if(HAL_FDCAN_TXT_Buffer_Accessible(hfdcan,pTxMsg->BufferIndex) == false)
        {
            return HAL_ERROR;
        }

        /* Add the message to the Tx buffer */
        FDCAN_CopyMessageToBuffer(hfdcan, pTxMsg, pTxData);

        return HAL_OK;
    }
    else
    {
        /* Update error code */
        hfdcan->ErrorCode |= HAL_FDCAN_ERROR_NOT_INITIALIZED;
        return HAL_ERROR;
    }
}

HAL_StatusTypeDef HAL_FDCAN_EnableTxBufferRequest(FDCAN_HandleTypeDef *hfdcan, uint32_t BufferIndex)
{
    uint32_t txcmdtmp = 0;
    uint32_t TXTBufferNb = 0;

    txcmdtmp = hfdcan->Instance->TX_CMD_INFO;

    TXTBufferNb = REG_FIELD_RD(txcmdtmp,FDCAN_BUF_CNT);

    if((BufferIndex > FDCAN_TX_BUFFER2)&&(TXTBufferNb < BufferIndex))
    {
        return HAL_ERROR;
    }
    
    SET_BIT(txcmdtmp,FDCAN_TXCR_MASK);

    SET_BIT(txcmdtmp,(1 <<(FDCAN_TXB1_POS+BufferIndex)));

    hfdcan->Instance->TX_CMD_INFO = txcmdtmp;

    return HAL_OK;
}

HAL_StatusTypeDef HAL_FDCAN_Transmit(FDCAN_HandleTypeDef *hfdcan, uint32_t Timeout)
{
    uint32_t timeout = SYSTICK_MS2TICKS(Timeout);
    uint32_t tickstart = 0U;

    if(HAL_FDCAN_AddMessageToTxBuffer(hfdcan,hfdcan->pTxMsg,hfdcan->pTxMsg->TxData) == HAL_OK)
    {
        HAL_FDCAN_EnableTxBufferRequest(hfdcan,hfdcan->pTxMsg->BufferIndex);

        /* Get tick */
        tickstart = systick_get_value();

        /* Check End of transmission flag */
        if(systick_poll_timeout(tickstart,timeout,FDCAN_State_poll,hfdcan,FDCAN_TXI_MASK))
        {
            return HAL_TIMEOUT;
        }

        return HAL_OK;
    }
    else
    {
        return HAL_ERROR;
    }

    
}

HAL_StatusTypeDef HAL_FDCAN_Transmit_IT(FDCAN_HandleTypeDef *hfdcan)
{
    if(HAL_FDCAN_AddMessageToTxBuffer(hfdcan,hfdcan->pTxMsg,hfdcan->pTxMsg->TxData) == HAL_OK)
    {
        __HAL_FDCAN_ENABLE_IT(hfdcan,FDCAN_IT_TXI);
        HAL_FDCAN_EnableTxBufferRequest(hfdcan,hfdcan->pTxMsg->BufferIndex);

        return HAL_OK;
    }
    else
    {
        return HAL_ERROR;
    }
}

HAL_StatusTypeDef HAL_FDCAN_AbortTxRequest(FDCAN_HandleTypeDef *hfdcan, uint32_t BufferIndex)
{
    uint32_t txcmdtmp = 0;
    uint32_t TXTBufferNb = 0;

    txcmdtmp = hfdcan->Instance->TX_CMD_INFO;

    TXTBufferNb = REG_FIELD_RD(txcmdtmp,FDCAN_BUF_CNT);

    if((BufferIndex > FDCAN_TX_BUFFER2)&&(TXTBufferNb < BufferIndex))
    {
        return HAL_ERROR;
    }
    
    SET_BIT(txcmdtmp,FDCAN_TXCA_MASK);

    SET_BIT(txcmdtmp,(1 <<(FDCAN_TXB1_POS+BufferIndex)));

    hfdcan->Instance->TX_CMD_INFO = txcmdtmp;

    return HAL_OK;
}

HAL_StatusTypeDef HAL_FDCAN_ConfigFilter(FDCAN_HandleTypeDef* hfdcan, FDCAN_FilterTypeDef* sFilterConfig)
{
    uint32_t ftctemp = 0;
    uint32_t *FilterAddress;
    
    LS_ASSERT(IS_FDCAN_FILTERINDEX(sFilterConfig->FilterIndex));
    LS_ASSERT(IS_FDCAN_FILTERTYPE(sFilterConfig->FilterType));

    FilterAddress = (uint32_t *)(&(hfdcan->Instance->FILTER_A_MSK) + (sFilterConfig->FilterIndex * 4 * 2));

    if(sFilterConfig->FilterType == FDCAN_FILTER_CLASSIC_BASIC || 
        sFilterConfig->FilterType == FDCAN_FILTER_FD_BASIC)
    {
        LS_ASSERT(IS_FDCAN_MAX_VALUE(sFilterConfig->FilterValue1, 0x7FF));
        LS_ASSERT(IS_FDCAN_MAX_VALUE(sFilterConfig->FilterValue2, 0x7FF));

        *FilterAddress++ = sFilterConfig->FilterValue1 << 18;
        *FilterAddress = sFilterConfig->FilterValue2 << 18;
    }
    else
    {
        LS_ASSERT(IS_FDCAN_MAX_VALUE(sFilterConfig->FilterValue1, 0x1FFFFFFF));
        LS_ASSERT(IS_FDCAN_MAX_VALUE(sFilterConfig->FilterValue2, 0x1FFFFFFF));
    }

    ftctemp = hfdcan->Instance->FILTER_CTRL_STT;

    MODIFY_REG(ftctemp, 0xf<<(sFilterConfig->FilterIndex*4), sFilterConfig->FilterType);

    SET_BIT(ftctemp,(1 << (FDCAN_SFA_POS + sFilterConfig->FilterIndex)));

    hfdcan->Instance->FILTER_CTRL_STT = ftctemp;

    return HAL_ERROR;
}

HAL_StatusTypeDef HAL_FDCAN_GetRxMessage(FDCAN_HandleTypeDef *hfdcan, FDCAN_RxMsgTypeDef *pRxMsg, uint8_t *pRxData)
{
    uint32_t RXdatatmp = 0;
    uint32_t dlctmp = 0;
    uint32_t rwcnt = 0;

    /*Read FRAME_FORMAT_W*/
    RXdatatmp = hfdcan->Instance->RX_DATA;

    dlctmp = REG_FIELD_RD(RXdatatmp,FDCAN_TXTB_DATA_1_DLC);
    pRxMsg->DataLength = DLCtoBytes[dlctmp];
    pRxMsg->RxFrameType = REG_FIELD_RD(RXdatatmp,FDCAN_TXTB_DATA_1_RTR);
    pRxMsg->IdType = REG_FIELD_RD(RXdatatmp,FDCAN_TXTB_DATA_1_IDE);
    pRxMsg->FDFormat = REG_FIELD_RD(RXdatatmp,FDCAN_TXTB_DATA_1_FDF);
    pRxMsg->BitRateSwitch = REG_FIELD_RD(RXdatatmp,FDCAN_TXTB_DATA_1_BRS);
    pRxMsg->ErrorStateIndicator = REG_FIELD_RD(RXdatatmp,FDCAN_TXTB_DATA_1_ESIRSV);

    rwcnt = REG_FIELD_RD(RXdatatmp,FDCAN_TXTB_DATA_1_RWCNT);

    /*Read IDENTIFIER_W*/
    RXdatatmp = hfdcan->Instance->RX_DATA;
    if(pRxMsg->IdType == 1)
    {
        pRxMsg->Identifier = REG_FIELD_RD(RXdatatmp,FDCAN_TXTB_DATA_2_IDENTIFIER_EXT);
        pRxMsg->Identifier |= REG_FIELD_RD(RXdatatmp,FDCAN_TXTB_DATA_2_IDENTIFIER_BASE) << 18;
    }
    else
    {
        pRxMsg->Identifier = REG_FIELD_RD(RXdatatmp,FDCAN_TXTB_DATA_2_IDENTIFIER_BASE);
    }

    /*Read Timestamp*/
    pRxMsg->RxTimestampLow = hfdcan->Instance->RX_DATA;
    pRxMsg->RxTimestampUpper = hfdcan->Instance->RX_DATA;

    /*Read Data*/
    // for(uint8_t i = 0;i < pRxMsg->DataLength; i+=4)
    // {
    //     RXdatatmp = hfdcan->Instance->RX_DATA;
    //     pRxData[i] = RXdatatmp&0xff;
    //     pRxData[i+1] = (RXdatatmp>>8)&0xff;
    //     pRxData[i+2] = (RXdatatmp>>16)&0xff;
    //     pRxData[i+3] = (RXdatatmp>>24)&0xff;
    // }
    for(uint8_t i = 0;i < (rwcnt - 3); i++)
    {
        RXdatatmp = hfdcan->Instance->RX_DATA;
        pRxData[i*4] = RXdatatmp&0xff;
        pRxData[i*4+1] = (RXdatatmp>>8)&0xff;
        pRxData[i*4+2] = (RXdatatmp>>16)&0xff;
        pRxData[i*4+3] = (RXdatatmp>>24)&0xff;
    }

    /* Return function status */
    return HAL_OK;
}

HAL_StatusTypeDef HAL_FDCAN_Receive(FDCAN_HandleTypeDef *hfdcan,uint32_t Timeout)
{
    uint32_t RXMemInfoTmp = 0;
    uint32_t rxsz = 0;
    uint32_t timeout = SYSTICK_MS2TICKS(Timeout);
    uint32_t tickstart = 0U;

    /* Get tick */
    tickstart = systick_get_value();

    /* Check End of transmission flag */
    if(systick_poll_timeout(tickstart,timeout,FDCAN_RXstatus_poll,hfdcan,FDCAN_RX_EMPTY,RESET))
    {
        return HAL_TIMEOUT;
    }

    while(__HAL_FDCAN_RXSTATUS_GET(hfdcan,FDCAN_RX_MID_FRAM))
    {
        hfdcan->Instance->RX_DATA;
    }

    RXMemInfoTmp = hfdcan->Instance->RX_MEM_INFO;
    rxsz = REG_FIELD_RD(RXMemInfoTmp,FDCAN_BUF_SIZE) - REG_FIELD_RD(RXMemInfoTmp,FDCAN_MEM_FREE);

    if(rxsz)
    {
        HAL_FDCAN_GetRxMessage(hfdcan,hfdcan->pRxMsg,hfdcan->pRxMsg->RxData);
        return HAL_OK;
    }
    else
    {
        return HAL_ERROR;
    }
}

HAL_StatusTypeDef HAL_FDCAN_Receive_IT(FDCAN_HandleTypeDef *hfdcan)
{
    __HAL_FDCAN_ENABLE_IT(hfdcan,FDCAN_IT_RXI);
    return HAL_OK;
}

static void FDCAN_Transmit_IT(FDCAN_HandleTypeDef *hfdcan)
{
    __HAL_FDCAN_DISABLE_IT(hfdcan,FDCAN_IT_TXI);
    HAL_FDCAN_TxCpltCallback(hfdcan);
}

static void FDCAN_Receive_IT(FDCAN_HandleTypeDef *hfdcan)
{
    uint32_t rxFrameCount = 0;
    uint32_t RXMemInfoTmp = 0;
    uint32_t rxsz = 0;

    __HAL_FDCAN_DISABLE_IT(hfdcan,FDCAN_IT_RXI);

    rxFrameCount = __HAL_FDCAN_RXSTATUS_GET(hfdcan,FDCAN_RX_FCOUNT);
    RXMemInfoTmp = hfdcan->Instance->RX_MEM_INFO;
    rxsz = REG_FIELD_RD(RXMemInfoTmp,FDCAN_BUF_SIZE) - REG_FIELD_RD(RXMemInfoTmp,FDCAN_MEM_FREE);
    if(rxFrameCount || rxsz)
    {
        HAL_FDCAN_GetRxMessage(hfdcan,hfdcan->pRxMsg,hfdcan->pRxMsg->RxData);

        HAL_FDCAN_RxCpltCallback(hfdcan);
    }
}

void HAL_FDCAN_IRQHandler(FDCAN_HandleTypeDef *hfdcan)
{
    if(__HAL_TIM_GET_FLAG(hfdcan,FDCAN_IT_TXI))
    {
        if(__HAL_FDCAN_GET_IT_SOURCE(hfdcan,FDCAN_IT_TXI))
        {
            __HAL_FDCAN_CLEAR_IT(hfdcan,FDCAN_IT_TXI);
            FDCAN_Transmit_IT(hfdcan);
        }
    }
    
    if(__HAL_TIM_GET_FLAG(hfdcan,FDCAN_IT_RXI))
    {
        if(__HAL_FDCAN_GET_IT_SOURCE(hfdcan,FDCAN_IT_RXI))
        {
            __HAL_FDCAN_CLEAR_IT(hfdcan,FDCAN_IT_RXI);
            FDCAN_Receive_IT(hfdcan);
        }
    }

    if(__HAL_FDCAN_GET_IT_SOURCE(hfdcan,FDCAN_IT_DOI))
    {
        __HAL_FDCAN_CLEAR_IT(hfdcan,FDCAN_IT_DOI);
        LOG_RAW("Data overrun\n");
        if(hfdcan->Instance->STT&FDCAN_DOR_MASK)
        {
            __HAL_FDCAN_CMD_SET(hfdcan,FDCAN_CLEAR_OVERRUN_FLAG);
        }
    }
    if(__HAL_FDCAN_GET_IT_SOURCE(hfdcan,FDCAN_IT_FCSI))
    {
        __HAL_FDCAN_CLEAR_IT(hfdcan,FDCAN_IT_FCSI);
    }
    if(__HAL_FDCAN_GET_IT_SOURCE(hfdcan,FDCAN_IT_ALI))
    {
        __HAL_FDCAN_CLEAR_IT(hfdcan,FDCAN_IT_ALI);
        LOG_RAW("Arbitration lost\n");
    }
    if(__HAL_FDCAN_GET_IT_SOURCE(hfdcan,FDCAN_IT_BEI))
    {
        __HAL_FDCAN_CLEAR_IT(hfdcan,FDCAN_IT_BEI);
        LOG_RAW("Bus error\n");
    }
    if(__HAL_FDCAN_GET_IT_SOURCE(hfdcan,FDCAN_IT_OFI))
    {
        __HAL_FDCAN_CLEAR_IT(hfdcan,FDCAN_IT_OFI);
        LOG_RAW("Overload frame\n");
    }
}

__weak void HAL_FDCAN_TxCpltCallback(FDCAN_HandleTypeDef* hcan){}
__weak void HAL_FDCAN_RxCpltCallback(FDCAN_HandleTypeDef* hcan){}
