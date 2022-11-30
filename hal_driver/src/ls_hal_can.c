#include "ls_hal_can.h"
#include "ls_msp_can.h"
#include "ls_dbg.h"
#include "systick.h"
#include <stddef.h>
#include "log.h"

#define CAN_TIMEOUT_VALUE  50U

/* Private macros --------------------------------------------------------*/
/** @defgroup CAN_Private_Macros   CAN Private Macros
  * @{
  */

#define IS_CAN_MODE(MODE) (((MODE) == CAN_MODE_NORMAL) || \
                           ((MODE) == CAN_MODE_LOOPBACK)|| \
                           ((MODE) == CAN_MODE_SILENT) || \
                           ((MODE) == CAN_MODE_SILENT_LOOPBACK))
#define IS_CAN_SJW(SJW) (((SJW) == CAN_SJW_1TQ) || ((SJW) == CAN_SJW_2TQ)|| \
                         ((SJW) == CAN_SJW_3TQ) || ((SJW) == CAN_SJW_4TQ))
#define IS_CAN_BS1(BS1) ((BS1) <= CAN_BS1_16TQ)
#define IS_CAN_BS2(BS2) ((BS2) <= CAN_BS2_8TQ)
#define IS_CAN_PRESCALER(PRESCALER) (((PRESCALER) >= 1U) && ((PRESCALER) <= 1024U))

#define IS_CAN_FILTER_MODE(MODE) (((MODE) == CAN_FILTERMODE_IDMASK) || \
                                  ((MODE) == CAN_FILTERMODE_IDLIST))
#define IS_CAN_FILTER_SCALE(SCALE) (((SCALE) == CAN_FILTERSCALE_16BIT) || \
                                    ((SCALE) == CAN_FILTERSCALE_32BIT))
#define IS_CAN_FILTER_FIFO(FIFO) (((FIFO) == CAN_FILTER_FIFO0) || \
                                  ((FIFO) == CAN_FILTER_FIFO1))
#define IS_CAN_BANKNUMBER(BANKNUMBER) ((BANKNUMBER) <= 28U)

#define IS_CAN_TRANSMITMAILBOX(TRANSMITMAILBOX) ((TRANSMITMAILBOX) <= ((uint8_t)0x02))
#define IS_CAN_STDID(STDID)   ((STDID) <= 0x00007FFU)
#define IS_CAN_EXTID(EXTID)   ((EXTID) <= 0x1FFFFFFFU)
#define IS_CAN_DLC(DLC)       ((DLC) <= ((uint8_t)0x08))

#define IS_CAN_IDTYPE(IDTYPE)  (((IDTYPE) == CAN_ID_STD) || \
                                ((IDTYPE) == CAN_ID_EXT))
#define IS_CAN_RTR(RTR) (((RTR) == CAN_RTR_DATA) || ((RTR) == CAN_RTR_REMOTE))
#define IS_CAN_FIFO(FIFO) (((FIFO) == CAN_FIFO0) || ((FIFO) == CAN_FIFO1))
#define IS_CAN_FILTER_NUMBER(NUMBER) ((NUMBER) <= 13U)
/**
  * @}
  */

static HAL_StatusTypeDef CAN_Receive_IT(CAN_HandleTypeDef* hcan, uint8_t FIFONumber);
static HAL_StatusTypeDef CAN_Transmit_IT(CAN_HandleTypeDef* hcan);

enum
{
    TX_POLLING,
    RX_POLLING,
    SLEEP_POLLING,
    WKUP_POLLING,
};

static bool can_msr_inak_poll(va_list va)
{
    bool state = false;
    CAN_HandleTypeDef* hcan = va_arg(va,CAN_HandleTypeDef*);
    uint32_t flag = va_arg(va,uint32_t);
    if(flag)
    {
        if(HAL_IS_BIT_SET(hcan->Instance->CAN_MSR,BXCAN_INAK_MASK))
        {
            state = true;
        }
    }
    else
    {
        if(HAL_IS_BIT_CLR(hcan->Instance->CAN_MSR,BXCAN_INAK_MASK))
        {
            state = true;
        }
    }

    return state;
}

static bool can_flag_poll(va_list va)
{
    bool state = false;
    CAN_HandleTypeDef* hcan = va_arg(va,CAN_HandleTypeDef*);
    uint32_t value = va_arg(va,uint32_t);
    uint32_t mode = va_arg(va,uint32_t);
    
    switch(mode)
    {
        case TX_POLLING:
        {
            if(__HAL_CAN_TRANSMIT_STATUS(hcan, value) != true)
            {
                state = true;
            }
        }
        break;
        case RX_POLLING:
        {
            if(__HAL_CAN_MSG_PENDING(hcan, value) == true)
            {
                state = true;
            }
        }
        break;
        case SLEEP_POLLING:
        {
            if((hcan->Instance->CAN_MSR & (BXCAN_SLAK_MASK|BXCAN_INAK_MASK))==BXCAN_SLAK_MASK)
            {
                state = true;
            }
        }
        break;
        case WKUP_POLLING:
        {
            if((hcan->Instance->CAN_MSR & BXCAN_SLAK_MASK) != BXCAN_SLAK_MASK)
            {
                state = true;
            }
        }
        break;
        default:
        LS_ASSERT(0);
        break;
    }
    
    return state;
}

HAL_StatusTypeDef HAL_CAN_Init(CAN_HandleTypeDef* hcan)
{
    uint32_t status = CAN_INITSTATUS_FAILED; /* Default init status */
    uint32_t tickstart = 0U;
    uint32_t tmp_mcr = 0U;
    uint32_t timeout = SYSTICK_MS2TICKS(CAN_TIMEOUT_VALUE);

    /* Check CAN handle */
    if (hcan == NULL)
    {
        return HAL_ERROR;
    }

    /* Check the parameters */
    LS_ASSERT(IS_CAN_MODE(hcan->Init.Mode));
    LS_ASSERT(IS_CAN_SJW(hcan->Init.SJW));
    LS_ASSERT(IS_CAN_BS1(hcan->Init.BS1));
    LS_ASSERT(IS_CAN_BS2(hcan->Init.BS2));
    LS_ASSERT(IS_CAN_PRESCALER(hcan->Init.Prescaler));

    if (hcan->State == HAL_CAN_STATE_RESET)
    {
        /* Allocate lock resource and initialize it */
        hcan->Lock = HAL_UNLOCKED;
        /* Init the low level hardware */
        HAL_BXCAN_MSP_Init(hcan);
        HAL_BXCAN_MSP_Busy_Set();
    }

    /* Initialize the CAN state*/
    hcan->State = HAL_CAN_STATE_BUSY;

    /* Exit from sleep mode */
    CLEAR_BIT(hcan->Instance->CAN_MCR, BXCAN_SLEEP_MASK);

    /* Request initialisation */
    SET_BIT(hcan->Instance->CAN_MCR, BXCAN_INRQ_MASK);

    /* Get timeout */
    tickstart = systick_get_value();

    /* Wait the acknowledge */
    // while(HAL_IS_BIT_CLR(hcan->Instance->CAN_MSR, BXCAN_INAK_MASK));
    if(systick_poll_timeout(tickstart,timeout,can_msr_inak_poll,hcan,SET))
    {
        hcan->State = HAL_CAN_STATE_TIMEOUT;
        /* Process unlocked */
        __HAL_UNLOCK(hcan);
        return HAL_TIMEOUT;
    }

    /* Check acknowledge */
    if ((hcan->Instance->CAN_MSR & BXCAN_INAK_MASK) == BXCAN_INAK_MASK)
    {
        /* Set the time triggered communication mode */
        if (hcan->Init.TTCM == ENABLE)
        {
            SET_BIT(tmp_mcr, BXCAN_TTCM_MASK);
        }
        else
        {
            CLEAR_BIT(tmp_mcr, BXCAN_TTCM_MASK);
        }

        /* Set the automatic bus-off management */
        if (hcan->Init.ABOM == ENABLE)
        {
            SET_BIT(tmp_mcr, BXCAN_ABOM_MASK);
        }
        else
        {
            CLEAR_BIT(tmp_mcr, BXCAN_ABOM_MASK);
        }

        /* Set the automatic wake-up mode */
        if (hcan->Init.AWUM == ENABLE)
        {
            SET_BIT(tmp_mcr, BXCAN_AWUM_MASK);
        }
        else
        {
            CLEAR_BIT(tmp_mcr, BXCAN_AWUM_MASK);
        }
        /* Set the no automatic retransmission */
        if (hcan->Init.NART == ENABLE)
        {
            SET_BIT(tmp_mcr, BXCAN_NART_MASK);
        }
        else
        {
            CLEAR_BIT(tmp_mcr, BXCAN_NART_MASK);
        }

        /* Set the receive FIFO locked mode */
        if (hcan->Init.RFLM == ENABLE)
        {
            SET_BIT(tmp_mcr, BXCAN_RFLM_MASK);
        }
        else
        {
            CLEAR_BIT(tmp_mcr, BXCAN_RFLM_MASK);
        }
        /* Set the transmit FIFO priority */
        if (hcan->Init.TXFP == ENABLE)
        {
            SET_BIT(tmp_mcr, BXCAN_TXFP_MASK);
        }
        else
        {
            CLEAR_BIT(tmp_mcr, BXCAN_TXFP_MASK);
        }

        /* Update register MCR */
        MODIFY_REG(hcan->Instance->CAN_MCR,
                    BXCAN_TTCM_MASK |
                    BXCAN_ABOM_MASK |
                    BXCAN_AWUM_MASK |
                    BXCAN_NART_MASK |
                    BXCAN_RFLM_MASK |
                    BXCAN_TXFP_MASK,
                    tmp_mcr);

        /* Set the bit timing register */
        WRITE_REG(hcan->Instance->CAN_BTR, (uint32_t)(hcan->Init.Mode |
                                                  hcan->Init.SJW |
                                                  hcan->Init.BS1 |
                                                  hcan->Init.BS2 |
                                                  hcan->Init.Prescaler));

        /* Request leave initialisation */
        CLEAR_BIT(hcan->Instance->CAN_MCR, BXCAN_INRQ_MASK);

        /* Get timeout */
        tickstart = systick_get_value();

        /* Wait the acknowledge */
        // while(HAL_IS_BIT_SET(hcan->Instance->CAN_MSR, BXCAN_INAK_MASK));
        if(systick_poll_timeout(tickstart,timeout,can_msr_inak_poll,hcan,RESET))
        {
            hcan->State = HAL_CAN_STATE_TIMEOUT;
            /* Process unlocked */
            __HAL_UNLOCK(hcan);
            return HAL_TIMEOUT;
        }

        /* Check acknowledged */
        if (HAL_IS_BIT_CLR(hcan->Instance->CAN_MSR,BXCAN_INAK_MASK))
        {
            status = CAN_INITSTATUS_SUCCESS;
        }
    }

    if (status == CAN_INITSTATUS_SUCCESS)
    {
        /* Set CAN error code to none */
        hcan->ErrorCode = HAL_CAN_ERROR_NONE;

        /* Initialize the CAN state */
        hcan->State = HAL_CAN_STATE_READY;

        /* Return function status */
        return HAL_OK;
    }
    else
    {
        /* Initialize the CAN state */
        hcan->State = HAL_CAN_STATE_ERROR;

        /* Return function status */
        return HAL_ERROR;
    }
}

HAL_StatusTypeDef HAL_CAN_DeInit(CAN_HandleTypeDef* hcan)
{
    /* Check CAN handle */
    if (hcan == NULL)
    {
        return HAL_ERROR;
    }

    /* Change CAN state */
    hcan->State = HAL_CAN_STATE_BUSY;

    /* DeInit the low level hardware */
    HAL_BXCAN_MSP_DeInit(hcan);
    HAL_BXCAN_MSP_Idle_Set();

    /* Change CAN state */
    hcan->State = HAL_CAN_STATE_RESET;

    /* Release Lock */
    __HAL_UNLOCK(hcan);

    /* Return function status */
    return HAL_OK;
}

HAL_StatusTypeDef HAL_CAN_ConfigFilter(CAN_HandleTypeDef* hcan, CAN_FilterConfTypeDef* sFilterConfig)
{
    uint32_t filternbrbitpos = 0U;

    /* Check the parameters */
    LS_ASSERT(IS_CAN_FILTER_NUMBER(sFilterConfig->FilterNumber));
    LS_ASSERT(IS_CAN_FILTER_MODE(sFilterConfig->FilterMode));
    LS_ASSERT(IS_CAN_FILTER_SCALE(sFilterConfig->FilterScale));
    LS_ASSERT(IS_CAN_FILTER_FIFO(sFilterConfig->FilterFIFOAssignment));

    /* Initialisation mode for the filter */
    SET_BIT(hcan->Instance->CAN_FMR, ((uint32_t)BXCAN_FINIT_MASK));

    filternbrbitpos = (1U) << sFilterConfig->FilterNumber;

    /* Filter Deactivation */
    CLEAR_BIT(hcan->Instance->CAN_FA1R, filternbrbitpos);

    /* Filter Scale */
    if (sFilterConfig->FilterScale == CAN_FILTERSCALE_16BIT)
    {
        /* 16-bit scale for the filter */
        CLEAR_BIT(hcan->Instance->CAN_FS1R, filternbrbitpos);

        /* First 16-bit identifier and First 16-bit mask */
        /* Or First 16-bit identifier and Second 16-bit identifier */
        hcan->Instance->sFilterRegister[sFilterConfig->FilterNumber].FR1 =
            ((0x0000FFFFU & (uint32_t)sFilterConfig->FilterMaskIdLow) << 16U) |
            (0x0000FFFFU & (uint32_t)sFilterConfig->FilterIdLow);

        /* Second 16-bit identifier and Second 16-bit mask */
        /* Or Third 16-bit identifier and Fourth 16-bit identifier */
        hcan->Instance->sFilterRegister[sFilterConfig->FilterNumber].FR2 =
            ((0x0000FFFFU & (uint32_t)sFilterConfig->FilterMaskIdHigh) << 16U) |
            (0x0000FFFFU & (uint32_t)sFilterConfig->FilterIdHigh);
    }

    if (sFilterConfig->FilterScale == CAN_FILTERSCALE_32BIT)
    {
        /* 32-bit scale for the filter */
        SET_BIT(hcan->Instance->CAN_FS1R, filternbrbitpos);
        /* 32-bit identifier or First 32-bit identifier */
        hcan->Instance->sFilterRegister[sFilterConfig->FilterNumber].FR1 =
            ((0x0000FFFFU & (uint32_t)sFilterConfig->FilterIdHigh) << 16U) |
            (0x0000FFFFU & (uint32_t)sFilterConfig->FilterIdLow);
        /* 32-bit mask or Second 32-bit identifier */
        hcan->Instance->sFilterRegister[sFilterConfig->FilterNumber].FR2 =
            ((0x0000FFFFU & (uint32_t)sFilterConfig->FilterMaskIdHigh) << 16U) |
            (0x0000FFFFU & (uint32_t)sFilterConfig->FilterMaskIdLow);
    }

    /* Filter Mode */
    if (sFilterConfig->FilterMode == CAN_FILTERMODE_IDMASK)
    {
        /*Id/Mask mode for the filter*/
        CLEAR_BIT(hcan->Instance->CAN_FM1R, filternbrbitpos);
    }
    else /* CAN_FilterInitStruct->CAN_FilterMode == CAN_FilterMode_IdList */
    {
        /*Identifier list mode for the filter*/
        SET_BIT(hcan->Instance->CAN_FM1R, filternbrbitpos);
    }

    /* Filter FIFO assignment */
    if (sFilterConfig->FilterFIFOAssignment == CAN_FILTER_FIFO0)
    {
        /* FIFO 0 assignation for the filter */
        CLEAR_BIT(hcan->Instance->CAN_FFA1R, filternbrbitpos);
    }
    else
    {
        /* FIFO 1 assignation for the filter */
        SET_BIT(hcan->Instance->CAN_FFA1R, filternbrbitpos);
    }

    /* Filter activation */
    if (sFilterConfig->FilterActivation == ENABLE)
    {
        SET_BIT(hcan->Instance->CAN_FA1R, filternbrbitpos);
    }

    /* Leave the initialisation mode for the filter */
    CLEAR_BIT(hcan->Instance->CAN_FMR, ((uint32_t)BXCAN_FINIT_MASK));

    /* Return function status */
    return HAL_OK;
}

static uint32_t HAL_CAN_Transmit_Mailbox_Config(CAN_HandleTypeDef* hcan)
{
    uint32_t transmitmailbox = CAN_TXSTATUS_NOMAILBOX;

    /* Check the parameters */
    LS_ASSERT(IS_CAN_IDTYPE(hcan->pTxMsg->IDE));
    LS_ASSERT(IS_CAN_RTR(hcan->pTxMsg->RTR));
    LS_ASSERT(IS_CAN_DLC(hcan->pTxMsg->DLC));

    /* Change CAN state */
    switch (hcan->State)
    {
    case (HAL_CAN_STATE_BUSY_RX0):
        hcan->State = HAL_CAN_STATE_BUSY_TX_RX0;
        break;
    case (HAL_CAN_STATE_BUSY_RX1):
        hcan->State = HAL_CAN_STATE_BUSY_TX_RX1;
        break;
    case (HAL_CAN_STATE_BUSY_RX0_RX1):
        hcan->State = HAL_CAN_STATE_BUSY_TX_RX0_RX1;
        break;
    default: /* HAL_CAN_STATE_READY */
        hcan->State = HAL_CAN_STATE_BUSY_TX;
        break;
    }

    /* Select one empty transmit mailbox */
    if (HAL_IS_BIT_SET(hcan->Instance->CAN_TSR, BXCAN_TME0_MASK))
    {
        transmitmailbox = CAN_TXMAILBOX_0;
    }
    else if (HAL_IS_BIT_SET(hcan->Instance->CAN_TSR, BXCAN_TME1_MASK))
    {
        transmitmailbox = CAN_TXMAILBOX_1;
    }
    else
    {
        transmitmailbox = CAN_TXMAILBOX_2;
    }

    /* Set up the Id */
    hcan->Instance->sTxMailBox[transmitmailbox].TIR &= ~BXCAN_T0TXRQ_MASK;
    if (hcan->pTxMsg->IDE == CAN_ID_STD)
    {
        LS_ASSERT(IS_CAN_STDID(hcan->pTxMsg->StdId));
        hcan->Instance->sTxMailBox[transmitmailbox].TIR |= ((hcan->pTxMsg->StdId << BXCAN_T0STID_POS) |
                                                            hcan->pTxMsg->RTR);
    }
    else
    {
        LS_ASSERT(IS_CAN_EXTID(hcan->pTxMsg->ExtId));
        hcan->Instance->sTxMailBox[transmitmailbox].TIR |= ((hcan->pTxMsg->ExtId << BXCAN_T0EXID_POS) |
                                                            hcan->pTxMsg->IDE |
                                                            hcan->pTxMsg->RTR);
    }

    /* Set up the DLC */
    hcan->pTxMsg->DLC &= (uint8_t)0x0000000F;
    hcan->Instance->sTxMailBox[transmitmailbox].TDTR &= 0xFFFFFFF0U;
    hcan->Instance->sTxMailBox[transmitmailbox].TDTR |= hcan->pTxMsg->DLC;

    /* Set up the data field */
    WRITE_REG(hcan->Instance->sTxMailBox[transmitmailbox].TDLR, ((uint32_t)hcan->pTxMsg->Data[3] << CAN_TDLR_DATA3_POS) |
                                                                    ((uint32_t)hcan->pTxMsg->Data[2] << CAN_TDLR_DATA2_POS) |
                                                                    ((uint32_t)hcan->pTxMsg->Data[1] << CAN_TDLR_DATA1_POS) |
                                                                    ((uint32_t)hcan->pTxMsg->Data[0] << CAN_TDLR_DATA0_POS));
    WRITE_REG(hcan->Instance->sTxMailBox[transmitmailbox].TDHR, ((uint32_t)hcan->pTxMsg->Data[7] << CAN_TDHR_DATA3_POS) |
                                                                    ((uint32_t)hcan->pTxMsg->Data[6] << CAN_TDHR_DATA2_POS) |
                                                                    ((uint32_t)hcan->pTxMsg->Data[5] << CAN_TDHR_DATA1_POS) |
                                                                    ((uint32_t)hcan->pTxMsg->Data[4] << CAN_TDHR_DATA0_POS));
    
    return transmitmailbox;
}

HAL_StatusTypeDef HAL_CAN_Transmit(CAN_HandleTypeDef* hcan, uint32_t Timeout)
{
    uint32_t timeout = SYSTICK_MS2TICKS(Timeout);
    uint32_t tickstart = 0U;
    uint32_t transmitmailbox = 0U;

    if (((hcan->Instance->CAN_TSR & BXCAN_TME0_MASK) == BXCAN_TME0_MASK) ||
        ((hcan->Instance->CAN_TSR & BXCAN_TME1_MASK) == BXCAN_TME1_MASK) ||
        ((hcan->Instance->CAN_TSR & BXCAN_TME2_MASK) == BXCAN_TME2_MASK))
    {
        /* Process locked */
        __HAL_LOCK(hcan);

        transmitmailbox = HAL_CAN_Transmit_Mailbox_Config(hcan);

        /* Request transmission */
        SET_BIT(hcan->Instance->sTxMailBox[transmitmailbox].TIR, BXCAN_T0TXRQ_MASK);

        /* Get tick */
        tickstart = systick_get_value();

        /* Check End of transmission flag */
        if(systick_poll_timeout(tickstart,timeout,can_flag_poll,hcan,transmitmailbox,TX_POLLING))
        {
            hcan->State = HAL_CAN_STATE_TIMEOUT;

            /* Cancel transmission */
            __HAL_CAN_CANCEL_TRANSMIT(hcan, transmitmailbox);

            /* Process unlocked */
            __HAL_UNLOCK(hcan);
            return HAL_TIMEOUT;
        }

        /* Change CAN state */
        switch (hcan->State)
        {
        case (HAL_CAN_STATE_BUSY_TX_RX0):
            hcan->State = HAL_CAN_STATE_BUSY_RX0;
            break;
        case (HAL_CAN_STATE_BUSY_TX_RX1):
            hcan->State = HAL_CAN_STATE_BUSY_RX1;
            break;
        case (HAL_CAN_STATE_BUSY_TX_RX0_RX1):
            hcan->State = HAL_CAN_STATE_BUSY_RX0_RX1;
            break;
        default: /* HAL_CAN_STATE_BUSY_TX */
            hcan->State = HAL_CAN_STATE_READY;
            break;
        }

        /* Process unlocked */
        __HAL_UNLOCK(hcan);

        /* Return function status */
        return HAL_OK;
    }
    else
    {
        /* Change CAN state */
        hcan->State = HAL_CAN_STATE_ERROR;

        /* Return function status */
        return HAL_ERROR;
    }
}

HAL_StatusTypeDef HAL_CAN_Transmit_IT(CAN_HandleTypeDef* hcan)
{
    uint32_t transmitmailbox = 0U;
    if (((hcan->Instance->CAN_TSR & BXCAN_TME0_MASK) == BXCAN_TME0_MASK) ||
        ((hcan->Instance->CAN_TSR & BXCAN_TME1_MASK) == BXCAN_TME1_MASK) ||
        ((hcan->Instance->CAN_TSR & BXCAN_TME2_MASK) == BXCAN_TME2_MASK))
    {
        /* Process Locked */
        __HAL_LOCK(hcan);

        transmitmailbox = HAL_CAN_Transmit_Mailbox_Config(hcan);

        /* Set CAN error code to none */
        hcan->ErrorCode = HAL_CAN_ERROR_NONE;

        /* Process Unlocked */
        __HAL_UNLOCK(hcan);

        /* Enable interrupts: */
        /*  - Enable Error warning Interrupt */
        /*  - Enable Error passive Interrupt */
        /*  - Enable Bus-off Interrupt */
        /*  - Enable Last error code Interrupt */
        /*  - Enable Error Interrupt */
        /*  - Enable Transmit mailbox empty Interrupt */
        __HAL_CAN_ENABLE_IT(hcan, CAN_IT_EWG |
                                  CAN_IT_EPV |
                                  CAN_IT_BOF |
                                  CAN_IT_LEC |
                                  CAN_IT_ERR |
                                  CAN_IT_TME);

        /* Request transmission */
        SET_BIT(hcan->Instance->sTxMailBox[transmitmailbox].TIR, BXCAN_T0TXRQ_MASK);
    }
    else
    {
        /* Change CAN state */
        hcan->State = HAL_CAN_STATE_ERROR;

        /* Return function status */
        return HAL_ERROR;
    }

    return HAL_OK;
}

static HAL_StatusTypeDef HAL_CAN_Receive_Before_State_Change(CAN_HandleTypeDef* hcan, uint8_t FIFONumber)
{
    /* Check if CAN state is not busy for RX FIFO0 */
    if ((FIFONumber == CAN_FIFO0) && ((hcan->State == HAL_CAN_STATE_BUSY_RX0) ||
                                      (hcan->State == HAL_CAN_STATE_BUSY_TX_RX0) ||
                                      (hcan->State == HAL_CAN_STATE_BUSY_RX0_RX1) ||
                                      (hcan->State == HAL_CAN_STATE_BUSY_TX_RX0_RX1)))
    {
        return HAL_BUSY;
    }

    /* Check if CAN state is not busy for RX FIFO1 */
    if ((FIFONumber == CAN_FIFO1) && ((hcan->State == HAL_CAN_STATE_BUSY_RX1) ||
                                      (hcan->State == HAL_CAN_STATE_BUSY_TX_RX1) ||
                                      (hcan->State == HAL_CAN_STATE_BUSY_RX0_RX1) ||
                                      (hcan->State == HAL_CAN_STATE_BUSY_TX_RX0_RX1)))
    {
        return HAL_BUSY;
    }

    /* Change CAN state */
    if (FIFONumber == CAN_FIFO0)
    {
        switch (hcan->State)
        {
        case (HAL_CAN_STATE_BUSY_TX):
            hcan->State = HAL_CAN_STATE_BUSY_TX_RX0;
            break;
        case (HAL_CAN_STATE_BUSY_RX1):
            hcan->State = HAL_CAN_STATE_BUSY_RX0_RX1;
            break;
        case (HAL_CAN_STATE_BUSY_TX_RX1):
            hcan->State = HAL_CAN_STATE_BUSY_TX_RX0_RX1;
            break;
        default: /* HAL_CAN_STATE_READY */
            hcan->State = HAL_CAN_STATE_BUSY_RX0;
            break;
        }
    }
    else /* FIFONumber == CAN_FIFO1 */
    {
        switch (hcan->State)
        {
        case (HAL_CAN_STATE_BUSY_TX):
            hcan->State = HAL_CAN_STATE_BUSY_TX_RX1;
            break;
        case (HAL_CAN_STATE_BUSY_RX0):
            hcan->State = HAL_CAN_STATE_BUSY_RX0_RX1;
            break;
        case (HAL_CAN_STATE_BUSY_TX_RX0):
            hcan->State = HAL_CAN_STATE_BUSY_TX_RX0_RX1;
            break;
        default: /* HAL_CAN_STATE_READY */
            hcan->State = HAL_CAN_STATE_BUSY_RX1;
            break;
        }
    }

    return HAL_OK;
}

static void HAL_CAN_Receive_Data_Pack(CAN_HandleTypeDef* hcan, uint8_t FIFONumber)
{
    CanRxMsgTypeDef *pRxMsg = NULL;

    /* Set RxMsg pointer */
    if (FIFONumber == CAN_FIFO0)
    {
        pRxMsg = hcan->pRxMsg;
    }
    else /* FIFONumber == CAN_FIFO1 */
    {
        pRxMsg = hcan->pRx1Msg;
    }

    /* Get the Id */
    pRxMsg->IDE = (uint8_t)CAN_ID_EXT & hcan->Instance->sFIFOMailBox[FIFONumber].RIR;
    if (pRxMsg->IDE == CAN_ID_STD)
    {
        pRxMsg->StdId = 0x000007FFU & (hcan->Instance->sFIFOMailBox[FIFONumber].RIR >> 21U);
    }
    else
    {
        pRxMsg->ExtId = 0x1FFFFFFFU & (hcan->Instance->sFIFOMailBox[FIFONumber].RIR >> 3U);
    }

    pRxMsg->RTR = (uint8_t)CAN_RTR_REMOTE & hcan->Instance->sFIFOMailBox[FIFONumber].RIR;
    /* Get the DLC */
    pRxMsg->DLC = (uint8_t)0x0FU & hcan->Instance->sFIFOMailBox[FIFONumber].RDTR;
    /* Get the FMI */
    pRxMsg->FMI = (uint8_t)0xFFU & (hcan->Instance->sFIFOMailBox[FIFONumber].RDTR >> 8U);
    /* Get the FIFONumber */
    pRxMsg->FIFONumber = FIFONumber;
    /* Get the data field */
    pRxMsg->Data[0] = (uint8_t)0xFFU & hcan->Instance->sFIFOMailBox[FIFONumber].RDLR;
    pRxMsg->Data[1] = (uint8_t)0xFFU & (hcan->Instance->sFIFOMailBox[FIFONumber].RDLR >> 8U);
    pRxMsg->Data[2] = (uint8_t)0xFFU & (hcan->Instance->sFIFOMailBox[FIFONumber].RDLR >> 16U);
    pRxMsg->Data[3] = (uint8_t)0xFFU & (hcan->Instance->sFIFOMailBox[FIFONumber].RDLR >> 24U);
    pRxMsg->Data[4] = (uint8_t)0xFFU & hcan->Instance->sFIFOMailBox[FIFONumber].RDHR;
    pRxMsg->Data[5] = (uint8_t)0xFFU & (hcan->Instance->sFIFOMailBox[FIFONumber].RDHR >> 8U);
    pRxMsg->Data[6] = (uint8_t)0xFFU & (hcan->Instance->sFIFOMailBox[FIFONumber].RDHR >> 16U);
    pRxMsg->Data[7] = (uint8_t)0xFFU & (hcan->Instance->sFIFOMailBox[FIFONumber].RDHR >> 24U);
}

static void HAL_CAN_Receive_End_State_Change(CAN_HandleTypeDef* hcan, uint8_t FIFONumber)
{
    /* Change CAN state */
    if (FIFONumber == CAN_FIFO0)
    {
        switch (hcan->State)
        {
        case (HAL_CAN_STATE_BUSY_TX_RX0):
            hcan->State = HAL_CAN_STATE_BUSY_TX;
            break;
        case (HAL_CAN_STATE_BUSY_RX0_RX1):
            hcan->State = HAL_CAN_STATE_BUSY_RX1;
            break;
        case (HAL_CAN_STATE_BUSY_TX_RX0_RX1):
            hcan->State = HAL_CAN_STATE_BUSY_TX_RX1;
            break;
        default: /* HAL_CAN_STATE_BUSY_RX0 */
            hcan->State = HAL_CAN_STATE_READY;
            break;
        }
    }
    else /* FIFONumber == CAN_FIFO1 */
    {
        switch (hcan->State)
        {
        case (HAL_CAN_STATE_BUSY_TX_RX1):
            hcan->State = HAL_CAN_STATE_BUSY_TX;
            break;
        case (HAL_CAN_STATE_BUSY_RX0_RX1):
            hcan->State = HAL_CAN_STATE_BUSY_RX0;
            break;
        case (HAL_CAN_STATE_BUSY_TX_RX0_RX1):
            hcan->State = HAL_CAN_STATE_BUSY_TX_RX0;
            break;
        default: /* HAL_CAN_STATE_BUSY_RX1 */
            hcan->State = HAL_CAN_STATE_READY;
            break;
        }
    }
}

HAL_StatusTypeDef HAL_CAN_Receive(CAN_HandleTypeDef* hcan, uint8_t FIFONumber, uint32_t Timeout)
{
    uint32_t timeout = SYSTICK_MS2TICKS(Timeout);
    uint32_t tickstart = 0U;
    
    /* Check the parameters */
    LS_ASSERT(IS_CAN_FIFO(FIFONumber));

    if(HAL_CAN_Receive_Before_State_Change(hcan,FIFONumber)!=HAL_OK)
    {
        return HAL_BUSY;
    }

    /* Get tick */
    tickstart = systick_get_value();

    /* Check pending message */
    if(systick_poll_timeout(tickstart,timeout,can_flag_poll,hcan,FIFONumber,RX_POLLING))
    {
        hcan->State = HAL_CAN_STATE_TIMEOUT;
        return HAL_TIMEOUT;
    }

    HAL_CAN_Receive_Data_Pack(hcan,FIFONumber);
    HAL_CAN_Receive_End_State_Change(hcan,FIFONumber);

    /* Release the FIFO */
    if (FIFONumber == CAN_FIFO0)
    {
        /* Release FIFO0 */
        __HAL_CAN_FIFO_RELEASE(hcan, CAN_FIFO0);
    }
    else /* FIFONumber == CAN_FIFO1 */
    {
        /* Release FIFO1 */
        __HAL_CAN_FIFO_RELEASE(hcan, CAN_FIFO1);
    }

    /* Return function status */
    return HAL_OK;
}

HAL_StatusTypeDef HAL_CAN_Receive_IT(CAN_HandleTypeDef* hcan, uint8_t FIFONumber)
{
    /* Check the parameters */
    LS_ASSERT(IS_CAN_FIFO(FIFONumber));

    if(HAL_CAN_Receive_Before_State_Change(hcan,FIFONumber)!=HAL_OK)
    {
        return HAL_BUSY;
    }
    /* Set CAN error code to none */
    hcan->ErrorCode = HAL_CAN_ERROR_NONE;

    /* Enable interrupts: */
    /*  - Enable Error warning Interrupt */
    /*  - Enable Error passive Interrupt */
    /*  - Enable Bus-off Interrupt */
    /*  - Enable Last error code Interrupt */
    /*  - Enable Error Interrupt */
    /*  - Enable Transmit mailbox empty Interrupt */
    __HAL_CAN_ENABLE_IT(hcan, CAN_IT_EWG |
                                  CAN_IT_EPV |
                                  CAN_IT_BOF |
                                  CAN_IT_LEC |
                                  CAN_IT_ERR);

    if (FIFONumber == CAN_FIFO0)
    {
        /* Enable FIFO 0 overrun and message pending Interrupt */
        __HAL_CAN_ENABLE_IT(hcan, CAN_IT_FOV0 | CAN_IT_FMP0);
    }
    else
    {
        /* Enable FIFO 1 overrun and message pending Interrupt */
        __HAL_CAN_ENABLE_IT(hcan, CAN_IT_FOV1 | CAN_IT_FMP1);
    }

    /* Return function status */
    return HAL_OK;
}

HAL_StatusTypeDef HAL_CAN_Sleep(CAN_HandleTypeDef* hcan)
{
    uint32_t tickstart = 0U;
    uint32_t timeout = SYSTICK_MS2TICKS(CAN_TIMEOUT_VALUE);

    /* Process locked */
    __HAL_LOCK(hcan);

    /* Change CAN state */
    hcan->State = HAL_CAN_STATE_BUSY;

    /* Request Sleep mode */
    MODIFY_REG(hcan->Instance->CAN_MCR,
               BXCAN_INRQ_MASK,
               BXCAN_SLEEP_MASK);

    /* Get tick */
    tickstart = systick_get_value();

    /* Wait the acknowledge */
    if(systick_poll_timeout(tickstart,timeout,can_flag_poll,hcan,NULL,SLEEP_POLLING))
    {
        hcan->State = HAL_CAN_STATE_TIMEOUT;
        /* Process unlocked */
        __HAL_UNLOCK(hcan);

        return HAL_TIMEOUT;
    }

    /* Sleep mode status */
    if ((hcan->Instance->CAN_MSR & (BXCAN_SLAK_MASK|BXCAN_INAK_MASK))!=BXCAN_SLAK_MASK)
    {
        /* Process unlocked */
        __HAL_UNLOCK(hcan);

        /* Return function status */
        return HAL_ERROR;
    }

    /* Change CAN state */
    hcan->State = HAL_CAN_STATE_READY;

    /* Process unlocked */
    __HAL_UNLOCK(hcan);

    /* Return function status */
    return HAL_OK;
}

HAL_StatusTypeDef HAL_CAN_WakeUp(CAN_HandleTypeDef* hcan)
{
    uint32_t tickstart = 0U;
    uint32_t timeout = SYSTICK_MS2TICKS(CAN_TIMEOUT_VALUE);

    /* Process locked */
    __HAL_LOCK(hcan);

    /* Change CAN state */
    hcan->State = HAL_CAN_STATE_BUSY;

    /* Wake up request */
    CLEAR_BIT(hcan->Instance->CAN_MCR, BXCAN_SLEEP_MASK);

    /* Get timeout */
    tickstart = systick_get_value();

    /* Sleep mode status */
    if(systick_poll_timeout(tickstart,timeout,can_flag_poll,hcan,NULL,WKUP_POLLING))
    {
        hcan->State = HAL_CAN_STATE_TIMEOUT;
        /* Process unlocked */
        __HAL_UNLOCK(hcan);

        return HAL_TIMEOUT;
    }

    if (HAL_IS_BIT_SET(hcan->Instance->CAN_MSR, BXCAN_SLAK_MASK))
    {
        /* Process unlocked */
        __HAL_UNLOCK(hcan);

        /* Return function status */
        return HAL_ERROR;
    }

    /* Change CAN state */
    hcan->State = HAL_CAN_STATE_READY;

    /* Process unlocked */
    __HAL_UNLOCK(hcan);

    /* Return function status */
    return HAL_OK;
}

void HAL_CAN_IRQHandler(CAN_HandleTypeDef* hcan)
{
    uint32_t tmp1 = 0U, tmp2 = 0U, tmp3 = 0U;
    uint32_t errorcode = HAL_CAN_ERROR_NONE;

    /* Check Overrun flag for FIFO0 */
    tmp1 = __HAL_CAN_GET_FLAG(hcan, CAN_FLAG_FOV0);
    tmp2 = __HAL_CAN_GET_IT_SOURCE(hcan, CAN_IT_FOV0);
    if((tmp1 != 0U) && tmp2)
    {
        /* Set CAN error code to FOV0 error */
        errorcode |= HAL_CAN_ERROR_FOV0;

        /* Clear FIFO0 Overrun Flag */
        __HAL_CAN_CLEAR_FLAG(hcan, CAN_FLAG_FOV0);
    }

    /* Check Overrun flag for FIFO1 */
    tmp1 = __HAL_CAN_GET_FLAG(hcan, CAN_FLAG_FOV1);
    tmp2 = __HAL_CAN_GET_IT_SOURCE(hcan, CAN_IT_FOV1);
    if((tmp1 != 0U) && tmp2)
    {
        /* Set CAN error code to FOV1 error */
        errorcode |= HAL_CAN_ERROR_FOV1;

        /* Clear FIFO1 Overrun Flag */
        __HAL_CAN_CLEAR_FLAG(hcan, CAN_FLAG_FOV1);
    }

    /* Check End of transmission flag */
    if(__HAL_CAN_GET_IT_SOURCE(hcan, CAN_IT_TME))
    {
        /* Check Transmit request completion status */
        tmp1 = __HAL_CAN_TRANSMIT_STATUS(hcan, CAN_TXMAILBOX_0);
        tmp2 = __HAL_CAN_TRANSMIT_STATUS(hcan, CAN_TXMAILBOX_1);
        tmp3 = __HAL_CAN_TRANSMIT_STATUS(hcan, CAN_TXMAILBOX_2);
        if(tmp1 || tmp2 || tmp3)  
        {
        tmp1 = __HAL_CAN_GET_FLAG(hcan, CAN_FLAG_TXOK0);
        tmp2 = __HAL_CAN_GET_FLAG(hcan, CAN_FLAG_TXOK1);
        tmp3 = __HAL_CAN_GET_FLAG(hcan, CAN_FLAG_TXOK2);
        /* Check Transmit success */
        if((tmp1) || (tmp2) || (tmp3))
        {
            /* Call transmit function */
            CAN_Transmit_IT(hcan);
        }
        else /* Transmit failure */
        {
            /* Set CAN error code to TXFAIL error */
            errorcode |= HAL_CAN_ERROR_TXFAIL;
        }

        /* Clear transmission status flags (RQCPx and TXOKx) */
        SET_BIT(hcan->Instance->CAN_TSR, BXCAN_RQCP0_MASK  | BXCAN_RQCP1_MASK  | BXCAN_RQCP2_MASK | \
                                         CAN_FLAG_TXOK0 | CAN_FLAG_TXOK1 | CAN_FLAG_TXOK2);
        }
    }

    tmp1 = __HAL_CAN_MSG_PENDING(hcan, CAN_FIFO0);
    tmp2 = __HAL_CAN_GET_IT_SOURCE(hcan, CAN_IT_FMP0);
    /* Check End of reception flag for FIFO0 */
    if ((tmp1 != 0U) && tmp2)
    {
        /* Call receive function */
        CAN_Receive_IT(hcan, CAN_FIFO0);
    }

    tmp1 = __HAL_CAN_MSG_PENDING(hcan, CAN_FIFO1);
    tmp2 = __HAL_CAN_GET_IT_SOURCE(hcan, CAN_IT_FMP1);
    /* Check End of reception flag for FIFO1 */
    if ((tmp1 != 0U) && tmp2)
    {
        /* Call receive function */
        CAN_Receive_IT(hcan, CAN_FIFO1);
    }

    /* Set error code in handle */
    hcan->ErrorCode |= errorcode;

    tmp1 = __HAL_CAN_GET_FLAG(hcan, CAN_FLAG_EWG);
    tmp2 = __HAL_CAN_GET_IT_SOURCE(hcan, CAN_IT_EWG);
    tmp3 = __HAL_CAN_GET_IT_SOURCE(hcan, CAN_IT_ERR);
    /* Check Error Warning Flag */
    if (tmp1 && tmp2 && tmp3)
    {
        /* Set CAN error code to EWG error */
        hcan->ErrorCode |= HAL_CAN_ERROR_EWG;
        /* No need for clear of Error Warning Flag as read-only */
    }

    tmp1 = __HAL_CAN_GET_FLAG(hcan, CAN_FLAG_EPV);
    tmp2 = __HAL_CAN_GET_IT_SOURCE(hcan, CAN_IT_EPV);
    tmp3 = __HAL_CAN_GET_IT_SOURCE(hcan, CAN_IT_ERR);
    /* Check Error Passive Flag */
    if (tmp1 && tmp2 && tmp3)
    {
        /* Set CAN error code to EPV error */
        hcan->ErrorCode |= HAL_CAN_ERROR_EPV;
        /* No need for clear of Error Passive Flag as read-only */
    }

    tmp1 = __HAL_CAN_GET_FLAG(hcan, CAN_FLAG_BOF);
    tmp2 = __HAL_CAN_GET_IT_SOURCE(hcan, CAN_IT_BOF);
    tmp3 = __HAL_CAN_GET_IT_SOURCE(hcan, CAN_IT_ERR);
    /* Check Bus-Off Flag */
    if (tmp1 && tmp2 && tmp3)
    {
        /* Set CAN error code to BOF error */
        hcan->ErrorCode |= HAL_CAN_ERROR_BOF;
        /* No need for clear of Bus-Off Flag as read-only */
    }

    tmp1 = HAL_IS_BIT_CLR(hcan->Instance->CAN_ESR, BXCAN_LEC_MASK);
    tmp2 = __HAL_CAN_GET_IT_SOURCE(hcan, CAN_IT_LEC);
    tmp3 = __HAL_CAN_GET_IT_SOURCE(hcan, CAN_IT_ERR);
    /* Check Last error code Flag */
    if ((!tmp1) && tmp2 && tmp3)
    {
        tmp1 = (hcan->Instance->CAN_ESR & BXCAN_LEC_MASK);
        switch (tmp1)
        {
        case (BXCAN_LEC_0):
            /* Set CAN error code to STF error */
            hcan->ErrorCode |= HAL_CAN_ERROR_STF;
            break;
        case (BXCAN_LEC_1):
            /* Set CAN error code to FOR error */
            hcan->ErrorCode |= HAL_CAN_ERROR_FOR;
            break;
        case (BXCAN_LEC_1 | BXCAN_LEC_0):
            /* Set CAN error code to ACK error */
            hcan->ErrorCode |= HAL_CAN_ERROR_ACK;
            break;
        case (BXCAN_LEC_2):
            /* Set CAN error code to BR error */
            hcan->ErrorCode |= HAL_CAN_ERROR_BR;
            break;
        case (BXCAN_LEC_2 | BXCAN_LEC_0):
            /* Set CAN error code to BD error */
            hcan->ErrorCode |= HAL_CAN_ERROR_BD;
            break;
        case (BXCAN_LEC_2 | BXCAN_LEC_1):
            /* Set CAN error code to CRC error */
            hcan->ErrorCode |= HAL_CAN_ERROR_CRC;
            break;
        default:
            break;
        }

        /* Clear Last error code Flag */
        CLEAR_BIT(hcan->Instance->CAN_ESR, BXCAN_LEC_MASK);
    }

    /* Call the Error call Back in case of Errors */
    if (hcan->ErrorCode != HAL_CAN_ERROR_NONE)
    {
        /* Clear ERRI Flag */
        hcan->Instance->CAN_MSR = BXCAN_ERRI_MASK;
        /* Set the CAN state ready to be able to start again the process */
        hcan->State = HAL_CAN_STATE_READY;

        /* Call Error callback function */
        HAL_CAN_ErrorCallback(hcan);
    }
}

static HAL_StatusTypeDef CAN_Receive_IT(CAN_HandleTypeDef* hcan, uint8_t FIFONumber)
{
    uint32_t tmp1 = 0U;
    
    HAL_CAN_Receive_Data_Pack(hcan,FIFONumber);

    /* Release the FIFO */
    /* Release FIFO0 */
    if (FIFONumber == CAN_FIFO0)
    {
        __HAL_CAN_FIFO_RELEASE(hcan, CAN_FIFO0);

        /* Disable FIFO 0 overrun and message pending Interrupt */
        __HAL_CAN_DISABLE_IT(hcan, CAN_IT_FOV0 | CAN_IT_FMP0);
    }
    /* Release FIFO1 */
    else /* FIFONumber == CAN_FIFO1 */
    {
        __HAL_CAN_FIFO_RELEASE(hcan, CAN_FIFO1);

        /* Disable FIFO 1 overrun and message pending Interrupt */
        __HAL_CAN_DISABLE_IT(hcan, CAN_IT_FOV1 | CAN_IT_FMP1);
    }

    tmp1 = hcan->State;
    if ((tmp1 == HAL_CAN_STATE_BUSY_RX0) || (tmp1 == HAL_CAN_STATE_BUSY_RX1))
    {
        /* Disable interrupts: */
        /*  - Disable Error warning Interrupt */
        /*  - Disable Error passive Interrupt */
        /*  - Disable Bus-off Interrupt */
        /*  - Disable Last error code Interrupt */
        /*  - Disable Error Interrupt */
        __HAL_CAN_DISABLE_IT(hcan, CAN_IT_EWG |
                                       CAN_IT_EPV |
                                       CAN_IT_BOF |
                                       CAN_IT_LEC |
                                       CAN_IT_ERR);
    }

    HAL_CAN_Receive_End_State_Change(hcan,FIFONumber);

    /* Receive complete callback */
    HAL_CAN_RxCpltCallback(hcan);

    /* Return function status */
    return HAL_OK;
}

static HAL_StatusTypeDef CAN_Transmit_IT(CAN_HandleTypeDef* hcan)
{
    /* Disable Transmit mailbox empty Interrupt */
    __HAL_CAN_DISABLE_IT(hcan, CAN_IT_TME);

    if (hcan->State == HAL_CAN_STATE_BUSY_TX)
    {
        /* Disable interrupts: */
        /*  - Disable Error warning Interrupt */
        /*  - Disable Error passive Interrupt */
        /*  - Disable Bus-off Interrupt */
        /*  - Disable Last error code Interrupt */
        /*  - Disable Error Interrupt */
        __HAL_CAN_DISABLE_IT(hcan, CAN_IT_EWG |
                                       CAN_IT_EPV |
                                       CAN_IT_BOF |
                                       CAN_IT_LEC |
                                       CAN_IT_ERR);
    }

    /* Change CAN state */
    switch (hcan->State)
    {
    case (HAL_CAN_STATE_BUSY_TX_RX0):
        hcan->State = HAL_CAN_STATE_BUSY_RX0;
        break;
    case (HAL_CAN_STATE_BUSY_TX_RX1):
        hcan->State = HAL_CAN_STATE_BUSY_RX1;
        break;
    case (HAL_CAN_STATE_BUSY_TX_RX0_RX1):
        hcan->State = HAL_CAN_STATE_BUSY_RX0_RX1;
        break;
    default: /* HAL_CAN_STATE_BUSY_TX */
        hcan->State = HAL_CAN_STATE_READY;
        break;
    }

    /* Transmission complete callback */
    HAL_CAN_TxCpltCallback(hcan);

    return HAL_OK;
}
__weak void HAL_CAN_TxCpltCallback(CAN_HandleTypeDef* hcan){}
__weak void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* hcan){}
__weak void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan){}
