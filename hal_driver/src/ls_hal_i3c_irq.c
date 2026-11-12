#ifndef __I3C_IRQ__
#define __I3C_IRQ__

#include "ls_hal_i3c_controller.h"
#include "ls_hal_i3c_conmon.h"
#include "ls_hal_i3c_target.h"
#include "ls_ll_i3c_controller.h"
#include "ls_ll_i3c_target.h"

#include "log.h"
#include "ls_msp_i3c.h"

void HAL_I3C_ER_IRQHandler(I3C_HandleTypeDef *hi3c);


struct sr_status_t
{
  uint16_t idx;
  uint32_t status;
  uint32_t irq;
  uint32_t ier;
  uint32_t sr;
};
struct sr_status_t sr_state[400];
struct sr_status_t sr_state2[400];
extern volatile uint16_t irq_idx;
extern volatile uint16_t irq_idx2;

#define I3C_CHECK_IT_SOURCE(__IER__, __IT__)  ((((__IER__) & (__IT__)) == (__IT__)) ? SET : RESET)
#define I3C_CHECK_FLAG(__ISR__, __FLAG__) ((((__ISR__) & (__FLAG__)) == (__FLAG__)) ? SET : RESET)

void  enter_daa(I3C_HandleTypeDef *hi3cx);
void i3c_controller_handler(I3C_HandleTypeDef *hi3c);
void i3c_target_handler(I3C_HandleTypeDef *hi3c);
void dis_status(void);
void dis_status2(void);

void I3C_IRQHandler(I3C_HandleTypeDef *hi3cx)
{
    // uint32_t it_flags   = READ_REG(hi3cx->Instance->EVR);
    // uint32_t it_sources = READ_REG(hi3cx->Instance->IER);
    // uint32_t it_mask = it_sources&it_flags;
    // if(it_mask & 0x800)
    // {
    //     uint32_t error_code = READ_REG(hi3cx->Instance->SER);
    //     if(error_code == 0x13)
    //     {
    //         LOG_I("controller role ce3 ERROR ,device : 0x%lx",hi3cx->Instance);
    //         uint32_t irq_enabled = I3C_TargetGetEnabledInterrupts(hi3cx->Instance);
    //         I3C_TargetDisableInterrupts(hi3cx->Instance,irq_enabled);
    //         I3C_TargetClearStatusFlags(hi3cx->Instance, it_flags);
    //         HAL_I3C_ER_IRQHandler(hi3cx);
    //         return;
    //     }
    // }

    if(hi3cx->Mode == HAL_I3C_MODE_CONTROLLER)
    {
        i3c_controller_handler(hi3cx);

    }else
    {
        i3c_target_handler(hi3cx);
    }
}

void i3c_controller_handler(I3C_HandleTypeDef *hi3c)
{
    uint32_t it_flags   = READ_REG(hi3c->Instance->EVR);
    uint32_t it_sources = READ_REG(hi3c->Instance->IER);
    uint32_t it_mask = it_sources & it_flags;

    if(it_mask & I3C_EVR_ERRF_MASK)
    {      
        HAL_I3C_ER_IRQHandler(hi3c);
        return;
    }

    if(hi3c->XferISR !=  NULL )
    {
        hi3c->XferISR(hi3c, it_mask);
    }
}

#define I3C_TX_DATA_MODE (uint32_t)(kI3C_TargetMatchedFlag|kI3C_TargetBusStopFlag|kI3C_TargetTxReadyFlag|kI3C_TargetErrorFlag)
#define I3C_RX_DATA_MODE (uint32_t)(kI3C_TargetMatchedFlag|kI3C_TargetBusStopFlag|kI3C_TargetRxReadyFlag|kI3C_TargetErrorFlag)
#define I3C_SLVAE_LISTEN_MODE (uint32_t)(kI3C_TargetRxReadyFlag|kI3C_TargetReceivedCCCFlag|kI3C_TargetCCCHandledFlag|kI3C_TargetBusStopFlag|kI3C_TargetErrorFlag)
#define I3C_SLVAE_IBI_HJ_CR_MODE (uint32_t)(kI3C_TargetEventSentFlag|kI3C_TargetIbiDisableFlag|kI3C_TargetMasterRequestDisabledFlag|kI3C_TargetHotJoinDisabledFlag|kI3C_TargetErrorFlag)
uint32_t I3C_TargetCheckAndClearError(I3C_TypeDef *base, uint32_t status);
HAL_StatusTypeDef I3C_Tgt_Event_ISR(struct __I3C_HandleTypeDef *hi3c, uint32_t itMasks);
void i3c_target_handler(I3C_HandleTypeDef *hi3cx)
{
    uint32_t error_flag = I3C_TargetGetErrorStatusFlags(hi3cx->Instance);
    uint32_t it_flags = I3C_TargetGetStatusFlags(hi3cx->Instance);
    uint32_t it_pending = I3C_TargetGetPendingInterrupts(hi3cx->Instance);

    if((error_flag&kTargetErrorFlags) !=0)
    {
        error_flag = error_flag & kTargetErrorFlags;
        I3C_TargetCheckAndClearError(hi3cx->Instance, error_flag);
    }

    if(hi3cx->Instance->SCONFIG & I3C_SCONFIG_MATCHSS_MASK)
    {
        I3C_TargetClearStatusFlags(hi3cx->Instance, it_flags & ~kI3C_TargetMatchedFlag);
    }
    else
    {
        I3C_TargetClearStatusFlags(hi3cx->Instance, it_flags);
    }

    if ((0UL != (it_flags & (uint32_t)kI3C_TargetBusStartFlag)) &&
        (0UL != (it_pending & (uint32_t)kI3C_TargetBusStartFlag)))
    {
        /*not to do*/
    }

    if ((0UL != (it_flags & (uint32_t)kI3C_TargetEventSentFlag)) &&
        (0UL != (it_pending & (uint32_t)kI3C_TargetEventSentFlag)))
    {
        /*not to do*/
    }

    if ((0UL != (it_flags & (uint32_t)kI3C_TargetReceivedCCCFlag)) &&
        (0UL != (it_pending & (uint32_t)kI3C_TargetReceivedCCCFlag)))
    {
        /*not to do*/
    }

    if ((0UL != (it_flags & (uint32_t)kI3C_TargetMatchedFlag)) &&
        (0UL != (it_pending & (uint32_t)kI3C_TargetMatchedFlag)))
    {
        /*not to do*/
    }

    if ((0UL != (it_flags & (uint32_t)kI3C_TargetReceivedCCCFlag)) &&
        (0UL != (it_pending & (uint32_t)kI3C_TargetReceivedCCCFlag)))
    {
        /*not to do*/
    }

    /* Handle transmit and receive. */
    if ((0UL != (it_flags & (uint32_t)kI3C_TargetRxReadyFlag)) &&
        (0UL != (it_pending & (uint32_t)kI3C_TargetRxReadyFlag)))
    {
        uint16_t rxFifoCount = (hi3cx->Instance->SDATACTRL & I3C_SDATACTRL_RXCOUNT_MASK) >> I3C_SDATACTRL_RXCOUNT_POS;
        while(rxFifoCount != 0 && hi3cx->RxXferCount > 0)// && (stateParams.flags & (uint32_t)kI3C_TargetRxReadyFlag)
        {
            *hi3cx->pXferData->RxBuf.pBuffer = (uint8_t)hi3cx->Instance->SRDATAB;
            hi3cx->pXferData->RxBuf.pBuffer ++;
            hi3cx->RxXferCount--;
            rxFifoCount--;
        }
    }

    /* Handle transmit and receive. */
    if ((0UL != (it_flags & (uint32_t)kI3C_TargetTxReadyFlag)) &&
        (0UL != (it_pending & (uint32_t)kI3C_TargetTxReadyFlag)))
    {

        while((I3C_TargetGetStatusFlags(hi3cx->Instance) & (uint32_t)kI3C_TargetTxReadyFlag)
            && (hi3cx->TxXferCount > 0) )
        {
            if(hi3cx->TxXferCount == 1)
            {
                hi3cx->Instance->SWDATAB = *hi3cx->pXferData->TxBuf.pBuffer|I3C_SWDATAB_END1_MASK;
                I3C_TargetDisableInterrupts(hi3cx->Instance, (uint32_t)kI3C_TargetTxReadyFlag);
            }
            else
            {
                hi3cx->Instance->SWDATAB = *hi3cx->pXferData->TxBuf.pBuffer;
            }
            hi3cx->pXferData->TxBuf.pBuffer++;
            hi3cx->TxXferCount--;
        }
    }

    /* Handle stop event. */
    if (0UL != (it_flags & (uint32_t)kI3C_TargetBusStopFlag))
    {
        if(hi3cx->PreviousState == HAL_I3C_STATE_LISTEN)
        {
            I3C_TargetDisableInterrupts(hi3cx->Instance, (uint32_t)kI3C_TargetAllIrqFlags & ~HAL_I3C_IT_TARGET_ALL_EVENT);
            hi3cx->State = HAL_I3C_STATE_LISTEN;
        }
        else
        {
            I3C_TargetDisableInterrupts(hi3cx->Instance, (uint32_t)kI3C_TargetAllIrqFlags);
            hi3cx->State = HAL_I3C_STATE_READY;
        }

    }
    if(hi3cx->XferISR ==  I3C_Tgt_Event_ISR)
    {
        hi3cx->XferISR(hi3cx, it_flags);
    }

}






#endif