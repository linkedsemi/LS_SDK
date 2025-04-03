#include <string.h>
#include <stdlib.h>
#include "platform.h"
#include "compile_flag.h"
#include "log.h"
#include "reg_i3c.h"
#include "field_manipulate.h"
#include "core_rv32.h"
#include "ls_hal_i3c_target.h"
#include "ls_hal_i3c_controller.h"
#include "ls_ll_i3c_target.h"
#include "ls_hal_i3c_conmon.h"
#include "ls_hal_dmacv3.h"
#include "ls_msp_i3c.h"
#include "ls_dbg.h"

#define BCR_IBI_CAPABLE_MASK    1<<0x1
#define BCR_IBI_PAYLOAD_MASK    1<<0x2

#define I3C_TX_DATA_MODE (uint32_t)(kI3C_TargetMatchedFlag|kI3C_TargetBusStopFlag|kI3C_TargetTxReadyFlag|kI3C_TargetErrorFlag)
#define I3C_RX_DATA_MODE (uint32_t)(kI3C_TargetMatchedFlag|kI3C_TargetBusStopFlag|kI3C_TargetRxReadyFlag|kI3C_TargetErrorFlag)
#define I3C_SLVAE_LISTEN_MODE (uint32_t)(kI3C_TargetRxReadyFlag|kI3C_TargetReceivedCCCFlag|kI3C_TargetCCCHandledFlag|kI3C_TargetBusStopFlag|kI3C_TargetErrorFlag)
#define I3C_SLVAE_IBI_HJ_CR_MODE (uint32_t)(kI3C_TargetEventSentFlag|kI3C_TargetIbiDisableFlag|kI3C_TargetMasterRequestDisabledFlag|kI3C_TargetHotJoinDisabledFlag|kI3C_TargetErrorFlag|kI3C_TargetBusStopFlag)

#define GET_DMA_XFER_COUNT(hdmax,ch_idx)  HAL_DMA_Controller_Peek_BLOCK_TS(hdmax,ch_idx)

HAL_StatusTypeDef I3C_Tgt_Event_ISR(struct __I3C_HandleTypeDef *hi3c, uint32_t itMasks);

uint16_t HAL_DMA_Controller_Peek_BLOCK_TS(DMA_Controller_HandleTypeDef *hdma, uint8_t ch_idx)
{
    volatile uint64_t *CTL = (void *)hdma->Instance->CH[ch_idx].CTL;
    return (*CTL >> 32) & DMAC_BLOCK_TS_MASK;
}


uint32_t I3C_TargetCheckAndClearError(I3C_HandleTypeDef *hi3c, uint32_t status)
{
    uint32_t result = kStatus_Success;

    /* Check for error. These errors cause a stop to automatically be sent. We must */
    /* clear the errors before a new pXferData can start. */
    status &= (uint32_t)kTargetErrorFlags;

    if (0UL != status)
    {
        /* Select the correct error code. Ordered by severity, with bus issues first. */
        if (0UL != (status & (uint32_t)kI3C_TargetErrorOverrunFlag))
        {
            result = kI3C_TargetErrorOverrunFlag;
        }
        else if (0UL != (status & (uint32_t)kI3C_TargetErrorUnderrunFlag))
        {
            result = kI3C_TargetErrorUnderrunFlag;
        }
        else if (0UL != (status & (uint32_t)kI3C_TargetErrorUnderrunNakFlag))
        {
            result = kI3C_TargetErrorUnderrunNakFlag;
        }
        else if (0UL != (status & (uint32_t)kI3C_TargetErrorTermFlag))
        {
            result = kI3C_TargetErrorTermFlag;
        }
        else if (0UL != (status & (uint32_t)kI3C_TargetErrorInvalidStartFlag))
        {
            result = kI3C_TargetErrorInvalidStartFlag;
        }
        else if (0UL != (status & (uint32_t)kI3C_TargetErrorSdrParityFlag))
        {
            result = kI3C_TargetErrorSdrParityFlag;
        }
        else if (0UL != (status & (uint32_t)kI3C_TargetErrorHdrParityFlag))
        {
            result = kI3C_TargetErrorHdrParityFlag;
        }
        else if (0UL != (status & (uint32_t)kI3C_TargetErrorHdrCRCFlag))
        {
            result = kI3C_TargetErrorHdrCRCFlag;
        }
        else if (0UL != (status & (uint32_t)kI3C_TargetErrorS0S1Flag))
        {
            result = kI3C_TargetErrorS0S1Flag;
        }
        else if (0UL != (status & (uint32_t)kI3C_TargetErrorOverreadFlag))
        {
            result = kI3C_TargetErrorOverreadFlag;
        }
        else if (0UL != (status & (uint32_t)kI3C_TargetErrorOverwriteFlag))
        {
            result = kI3C_TargetErrorOverwriteFlag;
        }
        else
        {
            LS_ASSERT(false); 
        }

        /* Clear the flags. */
        I3C_TargetClearErrorStatusFlags(hi3c->Instance, status);

        /* Reset fifos. These flags clear automatically. */
        hi3c->Instance->SDATACTRL |= I3C_SDATACTRL_FLUSHTB_MASK|I3C_SDATACTRL_FLUSHFB_MASK;

        if(I3C_TargetEnabledRxDMA(hi3c->Instance))
        {
            HAL_DMA_Channel_Abort(hi3c->DMAC_Instance,hi3c->DMA_channel.RX_DMA_Channel);
            I3C_TargetEnableDMA(hi3c->Instance,false,false);
        }

        if(I3C_TargetEnabledTxDMA(hi3c->Instance))
        {
            HAL_DMA_Channel_Abort(hi3c->DMAC_Instance,hi3c->DMA_channel.TX_DMA_Channel);
            I3C_TargetEnableDMA(hi3c->Instance,false,false);
        }

        I3C_TargetDisableInterrupts(hi3c->Instance, (uint32_t)kI3C_TargetAllIrqFlags);
        I3C_TargetClearStatusFlags(hi3c->Instance, I3C_TargetGetStatusFlags(hi3c->Instance));
        hi3c->ErrorCode = result;

        if(hi3c->PreviousState == HAL_I3C_STATE_LISTEN)
        {
            hi3c->State = HAL_I3C_STATE_LISTEN;
            hi3c->XferISR = I3C_Tgt_Event_ISR;
        }else
        {
            hi3c->State = HAL_I3C_STATE_READY;
            hi3c->XferISR = NULL;
        }
        HAL_I3C_ErrorCallback(hi3c);
    }

    return result;
}

HAL_StatusTypeDef I3C_Tgt_Event_ISR(struct __I3C_HandleTypeDef *hi3c, uint32_t itMasks)
{
    uint32_t tmpevent = 0U;
    uint32_t enabled_it = I3C_TargetGetEnabledInterrupts(hi3c->Instance);
    if((I3C_CHECK_FLAG(itMasks,HAL_I3C_IT_CCC) != RESET) && (enabled_it & (HAL_I3C_IT_CRRQUSET)))
    {
        tmpevent|=EVENT_ID_CCC;
    }

    if((I3C_CHECK_FLAG(itMasks,HAL_I3C_IT_SLVRST) != RESET) && (enabled_it & (HAL_I3C_IT_CRRQUSET)))
    {
        tmpevent|=EVENT_ID_SRESET;
    }

    if((I3C_CHECK_FLAG(itMasks,HAL_I3C_IT_DACHG) != RESET) && (enabled_it & (HAL_I3C_IT_CRRQUSET)))
    {
        tmpevent|=EVENT_ID_DACHG;
    }

    if((I3C_CHECK_FLAG(itMasks,HAL_I3C_IT_CRRQUSET) != RESET) && (enabled_it & (HAL_I3C_IT_CRRQUSET)))
    {
        tmpevent|=EVENT_ID_CRRQUSET;
    }

    if (tmpevent != 0U)
    {
        /* Asynchronous receive CCC event Callback */
        HAL_I3C_NotifyCallback(hi3c, tmpevent);
    }
    return HAL_OK;
}

HAL_StatusTypeDef HAL_I3C_Target_Init(I3C_HandleTypeDef *hi3c)
{
    HAL_StatusTypeDef status = HAL_OK;
    uint32_t addr_val;
    /* Check the I3C handle allocation */
    if (hi3c == NULL)
    {
        status = HAL_ERROR;
    }
    else
    {
        /* Check the instance and the mode parameters */

        LS_ASSERT(IS_I3C_MODE(hi3c->Mode));
        if(hi3c->Mode != HAL_I3C_MODE_TARGET)
        {
            status = HAL_INVALIAD_PARAM;
        }
        else
        {
            /* Check the I3C state */
            if (hi3c->State == HAL_I3C_STATE_RESET)
            {
                HAL_I3C_MspInit(hi3c);
            }

            if(hi3c->Init.TgtBusCharacteristic.dnamicAddress!= 0)
            {
                if((!I3C_TargetDynAddressValid(hi3c->Instance)))
                {
                    addr_val = 0xa4d9<<I3C_SDYNADDR_KEY_POS | 0x0<<I3C_SDYNADDR_MAPIDX_POS 
                                            | (hi3c->Init.TgtBusCharacteristic.dnamicAddress&0x7f)<<I3C_SDYNADDR_DADDR_POS | 0x1 <<I3C_SDYNADDR_DAVALID_POS;

                    hi3c->Instance->SDYNADDR = addr_val;
                }else
                {
                    if(hi3c->Init.TgtBusCharacteristic.dnamicAddress != 
                        (hi3c->Instance->SDYNADDR&I3C_SDYNADDR_DADDR_MASK >> I3C_SDYNADDR_DADDR_POS))
                    {
                        /**/
                        status = HAL_INVALIAD_PARAM;
                        hi3c->ErrorCode = HAL_I3C_ERROR_DYNAMIC_ADDR;
                    }
                }
            }

            if(status == HAL_OK)
            {
                /* Update the I3C state to busy */
                hi3c->State = HAL_I3C_STATE_BUSY;

                uint32_t configValue;
                configValue = hi3c->Instance->SCONFIG;
                configValue &= 
                    ~(I3C_SCONFIG_SADDR_MASK|I3C_SCONFIG_BAMATCH_MASK
                    |I3C_SCONFIG_OFFLINE_MASK|I3C_SCONFIG_IDRAND_MASK
                    |I3C_SCONFIG_DDROK_MASK);
                
                configValue |=
                (hi3c->Init.TgtBusCharacteristic.staticAddr<<I3C_SCONFIG_SADDR_POS)
                |(hi3c->Init.TgtBusCharacteristic.matchCount << I3C_SCONFIG_BAMATCH_POS)|(hi3c->Init.TgtBusCharacteristic.offline <<I3C_SCONFIG_OFFLINE_POS)
                |(hi3c->Init.TgtBusCharacteristic.enableRandomPart <<I3C_SCONFIG_IDRAND_POS)
                |(hi3c->Init.TgtBusCharacteristic.ignoreS0S1Error <<I3C_SCONFIG_S0IGNORE_POS)|(hi3c->Init.TgtBusCharacteristic.matchTargetStartStop << I3C_SCONFIG_MATCHSS_POS)
                |(hi3c->Init.TgtBusCharacteristic.nakAllRequest <<I3C_SCONFIG_SLVNACK_POS) |
                (hi3c->EnableTarget <<I3C_SCONFIG_SLVENA_POS);

                hi3c->Instance->SVENDORID &= ~I3C_SIDVID_VID_MASK;
                hi3c->Instance->SVENDORID |= hi3c->Init.TgtBusCharacteristic.vendorID;
                if(!hi3c->Init.TgtBusCharacteristic.enableRandomPart)
                {
                    hi3c->Instance->SIDPARTNO = hi3c->Init.TgtBusCharacteristic.partNumber;
                }

                hi3c->Instance->SIDEXT &= ~(I3C_SIDEXT_BCR_MASK | I3C_SIDEXT_DCR_MASK);
                hi3c->Instance->SIDEXT |= (hi3c->Init.TgtBusCharacteristic.bcr << I3C_SIDEXT_BCR_POS) | (hi3c->Init.TgtBusCharacteristic.dcr << I3C_SIDEXT_DCR_POS);

                hi3c->Instance->SMAXLIMITS &= ~(I3C_SMAXLIMITS_MAXRD_MASK | I3C_SMAXLIMITS_MAXWR_MASK);
                hi3c->Instance->SMAXLIMITS |= (hi3c->Init.TgtBusCharacteristic.maxReadLength <<I3C_SMAXLIMITS_MAXRD_POS)|(hi3c->Init.TgtBusCharacteristic.maxWriteLength <<I3C_SMAXLIMITS_MAXWR_POS);

                if (hi3c->Init.TgtBusCharacteristic.isHotJoin)
                {
                    uint32_t ctrlValue = hi3c->Instance->SCTRL;
                    ctrlValue &= ~I3C_SCTRL_EVENT_MASK;
                    ctrlValue |= (kI3C_TargetEventHotJoinReq <<I3C_SCTRL_EVENT_POS);

                    hi3c->Instance->SCTRL |= ctrlValue;
                }
                WRITE_REG(hi3c->Instance->SCONFIG2,I3C_SCONFIG2_TARGET_CLOCK_EN_MASK);
                hi3c->Instance->SCONFIG = configValue;

                hi3c->ErrorCode = HAL_I3C_ERROR_NONE;
                /* Update I3C state */
                hi3c->State = HAL_I3C_STATE_READY;
                hi3c->PreviousState = HAL_I3C_STATE_READY;
            }
        }
    }
    return status;
}



HAL_StatusTypeDef HAL_I3C_Tgt_Receive_IT(I3C_HandleTypeDef *hi3c, I3C_XferTypeDef *pXferData)
{
    HAL_I3C_StateTypeDef handle_state;
    HAL_StatusTypeDef status = HAL_OK;
    if(hi3c == NULL)
    {
        status = HAL_ERROR;
    }
    else
    {
        /* Get I3C handle state */
        handle_state = hi3c->State;

        /* Check on user parameters */
        if ((pXferData == NULL) ||
            ((hi3c->RxXferCount != 0U) && (pXferData->RxBuf.pBuffer == NULL)))
        {
            hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_PARAM;
            status = HAL_ERROR;
        }
        /* Check on hdmatx and hdmacr handle */
        else if (hi3c->DMAC_Instance == NULL)
        {
            hi3c->ErrorCode = HAL_I3C_ERROR_DMA_PARAM;
            status = HAL_ERROR;
        }
        /* check on the Mode */
        else if (hi3c->Mode != HAL_I3C_MODE_TARGET)
        {
            hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
            status = HAL_ERROR;
        }
        /* check on the State */
        else if ((handle_state != HAL_I3C_STATE_READY) && (handle_state != HAL_I3C_STATE_LISTEN))
        {
            status = HAL_BUSY;
        }
        else
        {
            /* Set handle pXferData parameters */
            hi3c->PreviousState = hi3c->State;
            hi3c->ErrorCode   = HAL_I3C_ERROR_NONE;
            hi3c->State       = HAL_I3C_STATE_BUSY_RX;
            hi3c->pXferData   = pXferData;
            hi3c->RxXferCount = pXferData->RxBuf.Size;

            /* Clear all flags. */
            I3C_TargetClearStatusFlags(hi3c->Instance, (uint32_t)kTargetIrqFlags);

            /* Enable I3C internal IRQ sources.*/
            I3C_TargetEnableInterrupts(hi3c->Instance, (uint32_t)I3C_RX_DATA_MODE);
        }

    }

    return status;
}

HAL_StatusTypeDef HAL_I3C_Tgt_Transmit_IT(I3C_HandleTypeDef *hi3c, I3C_XferTypeDef *pXferData)
{
    HAL_I3C_StateTypeDef handle_state;
    HAL_StatusTypeDef status = HAL_OK;
    if(hi3c == NULL)
    {
        status = HAL_ERROR;
    }
    else
    {
        /* Get I3C handle state */
        handle_state = hi3c->State;

        /* Check on user parameters */
        if ((pXferData == NULL) ||
            ((hi3c->TxXferCount != 0U) && (pXferData->TxBuf.pBuffer == NULL)))
        {
            hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_PARAM;
            status = HAL_ERROR;
        }
        /* Check on hdmatx and hdmacr handle */
        else if (hi3c->DMAC_Instance == NULL)
        {
            hi3c->ErrorCode = HAL_I3C_ERROR_DMA_PARAM;
            status = HAL_ERROR;
        }
        /* check on the Mode */
        else if (hi3c->Mode != HAL_I3C_MODE_TARGET)
        {
            hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
            status = HAL_ERROR;
        }
        /* check on the State */
        else if ((handle_state != HAL_I3C_STATE_READY) && (handle_state != HAL_I3C_STATE_LISTEN))
        {
            status = HAL_BUSY;
        }
        else
        {
            /* Set handle pXferData parameters */
            hi3c->PreviousState = hi3c->State;
            hi3c->ErrorCode   = HAL_I3C_ERROR_NONE;
            hi3c->State       = HAL_I3C_STATE_BUSY_TX;
            hi3c->pXferData   = pXferData;
            hi3c->TxXferCount = pXferData->TxBuf.Size;


            /* Clear all flags. */
            I3C_TargetClearStatusFlags(hi3c->Instance, (uint32_t)kTargetIrqFlags);


            I3C_TargetFlushTxFifo(hi3c->Instance);
            I3C_TargetFlushRxFifo(hi3c->Instance);

            while((hi3c->Instance->SDATACTRL&I3C_SDATACTRL_TXFULL_MASK) == 0 && hi3c->TxXferCount > 0)
            {
                if(hi3c->TxXferCount > 1)
                {
                    hi3c->Instance->SWDATAB = *hi3c->pXferData->TxBuf.pBuffer;
                }
                else if(hi3c->TxXferCount == 1)
                {
                    hi3c->Instance->SWDATAB = *hi3c->pXferData->TxBuf.pBuffer|I3C_SWDATAB_END1_MASK;
                }
                hi3c->TxXferCount--;
                hi3c->pXferData->TxBuf.pBuffer++;
            }
            /* Enable I3C internal IRQ sources. NVIC IRQ was enabled in CreateHandle() */
            if(hi3c->TxXferCount > 0)
            {
                I3C_TargetEnableInterrupts(hi3c->Instance, I3C_TX_DATA_MODE);
            }else
            {
                I3C_TargetEnableInterrupts(hi3c->Instance, I3C_TX_DATA_MODE & ~((uint32_t)kI3C_TargetTxReadyFlag));
            }

        }
    }

    return status;
}

HAL_StatusTypeDef HAL_I3C_Tgt_IBIReq_IT(I3C_HandleTypeDef *hi3c, const uint8_t *pPayload, uint8_t payloadSize)
{
    uint32_t bcr= 0;

    if((hi3c->State != HAL_I3C_STATE_READY) && (hi3c->State != HAL_I3C_STATE_LISTEN))
    {
        hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
        return  HAL_INVALIAD_PARAM;
    }

    if(hi3c->Mode != HAL_I3C_MODE_TARGET)
    {
        hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
        return  HAL_INVALIAD_PARAM;
    }

    if(payloadSize > 8)
    {
        //LOG_I("The Ibi data size cannot exceed 8 bytes");
        hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
        return  HAL_INVALIAD_PARAM;
    }

    bcr =  REG_FIELD_RD(hi3c->Instance->SIDEXT,I3C_SIDEXT_BCR);
    if((BCR_IBI_CAPABLE_MASK & bcr) != BCR_IBI_CAPABLE_MASK)
    {
        hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
        return  HAL_INVALIAD_PARAM;
    }

    if(((BCR_IBI_PAYLOAD_MASK & bcr) != BCR_IBI_PAYLOAD_MASK))
    {
        if(payloadSize != 0)
        {
            hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
            return  HAL_INVALIAD_PARAM;
        }
    }
    else
    {
        if(payloadSize == 0)
        {
            hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
            return  HAL_INVALIAD_PARAM;
        } 
    }

    if (!I3C_TargetDynAddressValid(hi3c->Instance))
    {
        /* not have dynamic address */
        hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
        return HAL_STATE_ERROR;
    }

    hi3c->PreviousState = hi3c->State;
    hi3c->State         = HAL_I3C_STATE_BUSY;
    hi3c->ErrorCode     = HAL_I3C_ERROR_NONE;

    uint32_t ctrlValue = hi3c->Instance->SCTRL;
    ctrlValue &= ~I3C_SCTRL_EVENT_MASK;
    ctrlValue |= (kI3C_TargetEventIBI << I3C_SCTRL_EVENT_POS) & I3C_SCTRL_EVENT_MASK;

    hi3c->Instance->IBIEXTIDATA |= I3C_SIBIEXTIDATA_CLR_MASK;

    if(payloadSize != 0)
    {
        ctrlValue |= (((uint32_t)*pPayload<<I3C_SCTRL_IBIDATA_POS) & I3C_SCTRL_IBIDATA_MASK);
        payloadSize --;
        pPayload++;
        if(payloadSize > 0)
        {
            ctrlValue |= I3C_SCTRL_EXTDATA_MASK;
        }
        while((payloadSize > 0) && (hi3c->Instance->IBIEXTIDATA&I3C_SIBIEXTIDATA_FREE_MASK))
        {
            if(payloadSize > 1)
            {
                hi3c->Instance->IBIEXTIDATA = (uint32_t)*pPayload;
            }else
            {
                hi3c->Instance->IBIEXTIDATA = (uint32_t)*pPayload|I3C_SIBIEXTIDATA_END1_MASK;
            }
            payloadSize --;
            pPayload++;
        }
    }
    
    I3C_TargetEnableInterrupts(hi3c->Instance, (I3C_SLVAE_IBI_HJ_CR_MODE) & ~((uint32_t)kI3C_TargetTxReadyFlag));
    hi3c->Instance->SCTRL = ctrlValue;
    return HAL_OK;
}


HAL_StatusTypeDef HAL_I3C_Tgt_HJReq_IT(I3C_HandleTypeDef *hi3c)
{

    HAL_I3C_StateTypeDef handle_state;
    HAL_StatusTypeDef status = HAL_OK;

    /* check on the handle */
    if (hi3c == NULL)
    {
        status = HAL_ERROR;
    }
    else
    {
        /* Get I3C handle state */
        handle_state = hi3c->State;

        if (hi3c->Mode != HAL_I3C_MODE_TARGET)
        {
            hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
            status = HAL_ERROR;
        }
        /* check on the State */
        else if ((handle_state != HAL_I3C_STATE_READY) && (handle_state != HAL_I3C_STATE_LISTEN))
        {
            status = HAL_BUSY;
        }
        else if (I3C_TargetDynAddressValid(hi3c->Instance))
        {
            /* already have dynamic address */
            hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
            status = HAL_STATE_ERROR;
        }
        else
        {
            hi3c->PreviousState = hi3c->State;
            hi3c->State         = HAL_I3C_STATE_BUSY;
            hi3c->ErrorCode     = HAL_I3C_ERROR_NONE;

            uint32_t ctrlValue = hi3c->Instance->SCTRL;
            ctrlValue &= ~I3C_SCTRL_EVENT_MASK;
            ctrlValue |= (kI3C_TargetEventHotJoinReq << I3C_SCTRL_EVENT_POS) & I3C_SCTRL_EVENT_MASK;
            
            I3C_TargetEnableInterrupts(hi3c->Instance, I3C_SLVAE_IBI_HJ_CR_MODE& ~((uint32_t)kI3C_TargetTxReadyFlag));
            hi3c->Instance->SCTRL = ctrlValue;
        }
        
    }

    return status;
}

HAL_StatusTypeDef HAL_I3C_Tgt_CRReq_IT(I3C_HandleTypeDef *hi3c)
{
    HAL_I3C_StateTypeDef handle_state;
    HAL_StatusTypeDef status = HAL_OK;

    /* check on the handle */
    if (hi3c == NULL)
    {
        status = HAL_ERROR;
    }
    else
    {
        /* Get I3C handle state */
        handle_state = hi3c->State;

        if (hi3c->Mode != HAL_I3C_MODE_TARGET)
        {
            hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
            status = HAL_ERROR;
        }
        /* check on the State */
        else if ((handle_state != HAL_I3C_STATE_READY) && (handle_state != HAL_I3C_STATE_LISTEN))
        {
            status = HAL_BUSY;
        }
        else if (!I3C_TargetDynAddressValid(hi3c->Instance))
        {
            /* not have dynamic address */
            hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
            status = HAL_STATE_ERROR;
        }
        else
        {
            hi3c->PreviousState = hi3c->State;
            hi3c->State         = HAL_I3C_STATE_BUSY;
            hi3c->ErrorCode     = HAL_I3C_ERROR_NONE;

            uint32_t ctrlValue = hi3c->Instance->SCTRL;
            ctrlValue &= ~I3C_SCTRL_EVENT_MASK;
            ctrlValue |= (kI3C_TargetEventMasterReq << I3C_SCTRL_EVENT_POS) & I3C_SCTRL_EVENT_MASK;
            
            I3C_TargetEnableInterrupts(hi3c->Instance, I3C_SLVAE_IBI_HJ_CR_MODE & ~((uint32_t)kI3C_TargetTxReadyFlag));
            hi3c->Instance->SCTRL = ctrlValue;
        }
    }

    return status;
}

void i3c_dma_tgt_rx_callback(DMA_Controller_HandleTypeDef *hdma,uint32_t param,uint8_t ch_idx,uint32_t *lli,uint32_t status_int)
{
    I3C_HandleTypeDef *hi3cx = (I3C_HandleTypeDef *)param;
    if(status_int & DMAC_TFR_MASK)
    {
        I3C_TargetEnableDMA(hi3cx->Instance,false,false);
    }
}

void i3c_dma_tgt_tx_callback(DMA_Controller_HandleTypeDef *hdma,uint32_t param,uint8_t ch_idx,uint32_t *lli,uint32_t status_int)
{
  I3C_HandleTypeDef *hi3cx = (I3C_HandleTypeDef *)param;
  if(status_int & DMAC_TFR_MASK)
  {
    I3C_TargetEnableDMA(hi3cx->Instance,false,false);
    hi3cx->Instance->SWDATAB = hi3cx->pXferData->TxBuf.pBuffer[hi3cx->TxXferCount-1]|I3C_SWDATAB_END1_MASK;   
  }
}

HAL_StatusTypeDef HAL_I3C_Tgt_Start_DMA_Transmit(I3C_HandleTypeDef *hi3c)
{
    if(hi3c->DMAC_Instance == NULL)
    {
        return HAL_INVALIAD_PARAM;
    }
    if(hi3c->TxXferCount <=1)
    {
        return HAL_INVALIAD_PARAM;
    }
    struct ch_reg cfg;
    DMA_CHANNEL_CFG(cfg,
        hi3c->DMA_channel.TX_DMA_Channel,
        (uint32_t)hi3c->pXferData->TxBuf.pBuffer,
        (uint32_t)&hi3c->Instance->SWDATAB,
        TRANSFER_WIDTH_8BITS,
        hi3c->TxXferCount-1,
        M2P,
        0,
        HAL_I3C_TX_DMA_Handshake_Get(hi3c->Instance),
        0,0,0,0);
        
    HAL_DMA_Channel_Start_IT(hi3c->DMAC_Instance, &cfg, i3c_dma_tgt_tx_callback, (uint32_t)hi3c);
    return HAL_OK;
} 

HAL_StatusTypeDef HAL_I3C_Tgt_Start_DMA_Receive(I3C_HandleTypeDef *hi3c)
{
    if(hi3c->DMAC_Instance == NULL)
    {
        return HAL_INVALIAD_PARAM;
    }
    if(hi3c->RxXferCount == 0)
    {
        return HAL_INVALIAD_PARAM;
    }
    struct ch_reg cfg;
    DMA_CHANNEL_CFG(cfg,
        hi3c->DMA_channel.RX_DMA_Channel,
        (uint32_t)&hi3c->Instance->SRDATAB,
        (uint32_t)hi3c->pXferData->RxBuf.pBuffer,
        TRANSFER_WIDTH_8BITS,
        hi3c->RxXferCount,
        P2M,
        0,
        HAL_I3C_RX_DMA_Handshake_Get(hi3c->Instance),
        0,0,0,0);

    HAL_DMA_Channel_Start_IT(hi3c->DMAC_Instance, &cfg, i3c_dma_tgt_rx_callback, (uint32_t)hi3c);
    return HAL_OK;
} 

HAL_StatusTypeDef HAL_I3C_Tgt_Transmit_DMA(I3C_HandleTypeDef *hi3c, I3C_XferTypeDef *pXferData)
{
    HAL_I3C_StateTypeDef handle_state;
    HAL_StatusTypeDef status = HAL_OK;
    if(hi3c == NULL)
    {
        status = HAL_ERROR;
    }
    else
    {
        /* Get I3C handle state */
        handle_state = hi3c->State;

        /* Check on user parameters */
        if ((pXferData == NULL) ||
            ((hi3c->TxXferCount != 0U) && (pXferData->TxBuf.pBuffer == NULL)))
        {
            hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_PARAM;
            status = HAL_ERROR;
        }
        /* Check on hdmatx and hdmacr handle */
        else if (hi3c->DMAC_Instance == NULL)
        {
        hi3c->ErrorCode = HAL_I3C_ERROR_DMA_PARAM;
        status = HAL_ERROR;
        }
        /* check on the Mode */
        else if (hi3c->Mode != HAL_I3C_MODE_TARGET)
        {
        hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
        status = HAL_ERROR;
        }
        /* check on the State */
        else if ((handle_state != HAL_I3C_STATE_READY) && (handle_state != HAL_I3C_STATE_LISTEN))
        {
        status = HAL_BUSY;
        }
        else
        {
            /* Set handle transfer parameters */
            hi3c->ErrorCode     = HAL_I3C_ERROR_NONE;
            hi3c->State         = HAL_I3C_STATE_BUSY_TX;
            hi3c->pXferData     = pXferData;
            hi3c->TxXferCount   = pXferData->TxBuf.Size;

            I3C_TargetEnableDMA(hi3c->Instance,true,false);
            /* Clear all flags. */
            I3C_TargetClearStatusFlags(hi3c->Instance, (uint32_t)kTargetIrqFlags);
            while((hi3c->Instance->SDATACTRL&I3C_SDATACTRL_TXFULL_MASK) == 0 && hi3c->TxXferCount > 0)
            {
                if(hi3c->TxXferCount > 1)
                {
                    hi3c->Instance->SWDATAB = *hi3c->pXferData->TxBuf.pBuffer;
                }
                else if(hi3c->TxXferCount == 1)
                {
                    hi3c->Instance->SWDATAB = *hi3c->pXferData->TxBuf.pBuffer|I3C_SWDATAB_END1_MASK;
                }
                hi3c->TxXferCount--;
                hi3c->pXferData->TxBuf.pBuffer++;
            }

            if(hi3c->TxXferCount > 1)
            {
                I3C_TargetEnableDMA(hi3c->Instance,true,false);
                HAL_I3C_Tgt_Start_DMA_Transmit(hi3c);

                /* Enable I3C internal IRQ sources. */
                I3C_TargetEnableInterrupts(hi3c->Instance, (uint32_t)kI3C_TargetMatchedFlag
                        |kI3C_TargetBusStopFlag|kI3C_TargetErrorFlag);
            }else if(hi3c->TxXferCount == 1)
            {
                /* Enable I3C internal IRQ sources. */
                I3C_TargetEnableInterrupts(hi3c->Instance, (uint32_t)kI3C_TargetMatchedFlag
                        |kI3C_TargetBusStopFlag|kI3C_TargetErrorFlag|kI3C_TargetTxReadyFlag);
            }else
            {
                /* Enable I3C internal IRQ sources. */
                I3C_TargetEnableInterrupts(hi3c->Instance, (uint32_t)kI3C_TargetMatchedFlag
                        |kI3C_TargetBusStopFlag|kI3C_TargetErrorFlag);
            }
        }


    }
    return status;
}

HAL_StatusTypeDef HAL_I3C_Tgt_Receive_DMA(I3C_HandleTypeDef *hi3c, I3C_XferTypeDef *pXferData)
{

    HAL_I3C_StateTypeDef handle_state;
    HAL_StatusTypeDef status = HAL_OK;
    if(hi3c == NULL)
    {
        status = HAL_ERROR;
    }
    else
    {
        /* Get I3C handle state */
        handle_state = hi3c->State;

        /* Check on user parameters */
        if ((pXferData == NULL) ||
            ((hi3c->RxXferCount != 0U) && (pXferData->RxBuf.pBuffer == NULL)))
        {
            hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_PARAM;
            status = HAL_ERROR;
        }
        /* Check on hdmatx and hdmacr handle */
        else if (hi3c->DMAC_Instance == NULL)
        {
            hi3c->ErrorCode = HAL_I3C_ERROR_DMA_PARAM;
            status = HAL_ERROR;
        }
        /* check on the Mode */
        else if (hi3c->Mode != HAL_I3C_MODE_TARGET)
        {
            hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
            status = HAL_ERROR;
        }
        /* check on the State */
        else if ((handle_state != HAL_I3C_STATE_READY) && (handle_state != HAL_I3C_STATE_LISTEN))
        {
            status = HAL_BUSY;
        }
        else
        {
            /* Set handle transfer parameters */
            // hi3c->PreviousState = hi3c->State;
            hi3c->ErrorCode   = HAL_I3C_ERROR_NONE;
            hi3c->State       = HAL_I3C_STATE_BUSY_RX;
            hi3c->pXferData   = pXferData;
            hi3c->RxXferCount = pXferData->RxBuf.Size;

            /* Clear all flags. */
            I3C_TargetClearStatusFlags(hi3c->Instance, (uint32_t)kTargetIrqFlags);
            
            I3C_TargetEnableDMA(hi3c->Instance,false,true);
            HAL_I3C_Tgt_Start_DMA_Receive(hi3c);

            /* Enable I3C internal IRQ sources. NVIC IRQ was enabled in CreateHandle() */
            I3C_TargetEnableInterrupts(hi3c->Instance, (uint32_t)kI3C_TargetMatchedFlag
                    |kI3C_TargetBusStopFlag|kI3C_TargetErrorFlag);
        }

    }
    return status;
}


HAL_StatusTypeDef HAL_I3C_Target_ActivateNotification(I3C_HandleTypeDef *hi3c,uint32_t interruptMask)
{
    HAL_StatusTypeDef status = HAL_OK;
    /* Check on the handle */
    if (hi3c == NULL)
    {
        status = HAL_ERROR;
    }else
    {
        if(hi3c->Mode != HAL_I3C_MODE_TARGET)
        {
            hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
            status = HAL_ERROR;
        }
        else if(hi3c->Instance == NULL)
        {
            hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
            status = HAL_ERROR;
        }
        else
        {
            hi3c->XferISR = I3C_Tgt_Event_ISR;
            hi3c->ErrorCode     = HAL_I3C_ERROR_NONE;
            hi3c->PreviousState = HAL_I3C_STATE_LISTEN;
            hi3c->State         = HAL_I3C_STATE_LISTEN;

            /* Enable selected notifications */
            I3C_TargetEnableInterrupts(hi3c->Instance, interruptMask|kI3C_TargetErrorFlag);
        }
    }

    return status;
}