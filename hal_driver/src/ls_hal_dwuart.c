#include "field_manipulate.h"
#include "ls_hal_dwuart.h"
#include "ls_msp_uart.h"
#include "ls_soc_gpio.h"
#include "systick.h"
#include <stddef.h>

__attribute__((weak)) void HAL_DWUART_TxCpltCallback(DWUART_HandleTypeDef *hdwuart) {}
__attribute__((weak)) void HAL_DWUART_RxCpltCallback(DWUART_HandleTypeDef *hdwuart) {}
__attribute__((weak)) void HAL_DWUART_RxRTOCallback(DWUART_HandleTypeDef *hdwuart, uint8_t length) {}
__attribute__((weak)) void HAL_DWUART_RxErrorCallback(DWUART_HandleTypeDef *hdwuart, uint8_t errorMode) {}

static void DWUART_SetConfig(DWUART_HandleTypeDef *hdwuart)
{
    // Bautrate
    REG_FIELD_WR(hdwuart->DWUARTX->LCR, DWUART_DLAB, 1);
    hdwuart->DWUARTX->DLF = hdwuart->Init.BaudRate & 0xf;
    hdwuart->DWUARTX->RBR_THR_DLL = (hdwuart->Init.BaudRate >> 16) & DWUART_DIVISOR_LATCH_LOW_MASK;
    hdwuart->DWUARTX->DLH_IER = (hdwuart->Init.BaudRate >> 24) & DWUART_DIVISOR_LATCH_HIGH_MASK;
    REG_FIELD_WR(hdwuart->DWUARTX->LCR, DWUART_DLAB, 0);
    // Line Controller
    hdwuart->DWUARTX->LCR = FIELD_BUILD(DWUART_DLS, hdwuart->Init.WordLength) |
                            FIELD_BUILD(DWUART_STOP, hdwuart->Init.StopBits) |
                            FIELD_BUILD(DWUART_PEN, (hdwuart->Init.Parity == DWUART_NOPARITY) ? 0 : 1) |
                            FIELD_BUILD(DWUART_EPS, hdwuart->Init.Parity);
    // FIFO Controller
    hdwuart->DWUARTX->IIR_FCR = FIELD_BUILD(DWUART_FIFOE, 1) |
                                FIELD_BUILD(DWUART_RFIFOR, 1) |
                                FIELD_BUILD(DWUART_XFIFOR, 1) |
                                FIELD_BUILD(DWUART_DMAM, 0) |
                                FIELD_BUILD(DWUART_TET, DWUART_FIFO_TRANSMIT_TRIGGER_0BYTE) |
                                FIELD_BUILD(DWUART_RCVR, DWUART_FIFO_RECEIVE_TRIGGER_1BYTE);
    hdwuart->DWUARTX->DLH_IER = 0;
}

HAL_StatusTypeDef HAL_DWUART_Init(DWUART_HandleTypeDef *hdwuart)
{
    if (hdwuart == NULL)
    {
        return HAL_INVALIAD_PARAM;
    }
    if (hdwuart->DWUARTX->USR & DWUART_BUSY_MASK)
    {
        return HAL_BUSY;
    }

    HAL_DWUART_MSP_Init(hdwuart);
    HAL_DWUART_MSP_Busy_Set(hdwuart);
    DWUART_SetConfig(hdwuart);

    hdwuart->gState = HAL_DWUART_STATE_READY;
    hdwuart->RxState = HAL_DWUART_STATE_READY;

    return HAL_OK;
}

HAL_StatusTypeDef HAL_DWUART_DeInit(DWUART_HandleTypeDef *hdwuart)
{
    if (hdwuart == NULL)
    {
        return HAL_INVALIAD_PARAM;
    }

    HAL_DWUART_MSP_DeInit(hdwuart);
    HAL_DWUART_MSP_Idle_Set(hdwuart);

    hdwuart->gState = HAL_DWUART_STATE_RESET;
    hdwuart->RxState = HAL_DWUART_STATE_RESET;

    return HAL_OK;
}

static bool uart_flag_poll(va_list va)
{
    DWUART_HandleTypeDef *hdwuart = va_arg(va, DWUART_HandleTypeDef *);
    uint32_t flag = va_arg(va, uint32_t);
    if (hdwuart->DWUARTX->USR & flag)
    {
        return true;
    }
    else
    {
        return false;
    }
}

HAL_StatusTypeDef HAL_DWUART_Transmit(DWUART_HandleTypeDef *hdwuart, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    uint32_t timeout = SYSTICK_MS2TICKS(Timeout);
    uint32_t tickstart = systick_get_value();
    if (hdwuart->gState == HAL_DWUART_STATE_READY)
    {
        if ((pData == NULL) || (Size == 0U))
        {
            return HAL_INVALIAD_PARAM;
        }

        hdwuart->gState = HAL_DWUART_STATE_BUSY_TX;
        if (Timeout != HAL_MAX_DELAY)
        {
            while (Size > 0)
            {
                if (systick_poll_timeout(tickstart, timeout, uart_flag_poll, hdwuart, DWUART_TFNF_MASK))
                {
                    hdwuart->gState = HAL_DWUART_STATE_READY;
                    return HAL_TIMEOUT;
                }
                else
                {
                    hdwuart->DWUARTX->RBR_THR_DLL = (*pData++ & (uint8_t)0xFF);
                    if (--Size == 0)
                    {
                        break;
                    }
                }
            }
        }
        else
        {
            while (Size > 0)
            {
                if (hdwuart->DWUARTX->USR & DWUART_TFNF_MASK)
                {
                    Size--;
                    hdwuart->DWUARTX->RBR_THR_DLL = (*pData++ & 0xff);
                }
            }
            while ((hdwuart->DWUARTX->USR & DWUART_TFE_MASK) == 0)
                ;
        }

        hdwuart->gState = HAL_DWUART_STATE_READY;
        return HAL_OK;
    }
    else
    {
        return HAL_BUSY;
    }
}

HAL_StatusTypeDef HAL_DWUART_Receive(DWUART_HandleTypeDef *hdwuart, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    uint32_t timeout = SYSTICK_MS2TICKS(Timeout);
    uint32_t tickstart = systick_get_value();
    if (hdwuart->RxState == HAL_DWUART_STATE_READY)
    {
        if ((pData == NULL) || (Size == 0U))
        {
            return HAL_INVALIAD_PARAM;
        }
        hdwuart->RxState = HAL_DWUART_STATE_BUSY_RX;

        if (Timeout != HAL_MAX_DELAY)
        {
            while (Size > 0)
            {
                if (systick_poll_timeout(tickstart, timeout, uart_flag_poll, hdwuart, DWUART_RFNE_MASK))
                {
                    hdwuart->RxState = HAL_DWUART_STATE_READY;
                    return HAL_TIMEOUT;
                }
                else
                {
                    *pData++ = (uint8_t)(hdwuart->DWUARTX->RBR_THR_DLL & 0xff);
                    Size--;
                }
            }
        }
        else
        {
            while (Size > 0)
            {
                if (hdwuart->DWUARTX->USR & DWUART_RFNE_MASK)
                {
                    *pData++ = (uint8_t)(hdwuart->DWUARTX->RBR_THR_DLL & 0xff);
                    Size--;
                }
            }
        }

        hdwuart->RxState = HAL_DWUART_STATE_READY;
        return HAL_OK;
    }
    else
    {
        return HAL_BUSY;
    }
}

void DWUART_RXFIFO_Change(DWUART_HandleTypeDef *hdwuart)
{
    if (hdwuart->Rx_Env.Transfer.XferCount >= 16)
    {
        REG_FIELD_WR(hdwuart->DWUARTX->IIR_FCR, DWUART_RCVR, DWUART_FIFO_RECEIVE_TRIGGER_16BYTE);
    }
    else
    {
        REG_FIELD_WR(hdwuart->DWUARTX->IIR_FCR, DWUART_RCVR, DWUART_FIFO_RECEIVE_TRIGGER_8BYTE);
    }
}

HAL_StatusTypeDef HAL_DWUART_Transmit_IT(DWUART_HandleTypeDef *hdwuart, uint8_t *pData, uint16_t Size)
{
    if (hdwuart->gState == HAL_DWUART_STATE_READY)
    {
        if ((pData == NULL) || (Size == 0U))
        {
            return HAL_INVALIAD_PARAM;
        }

        hdwuart->Tx_Env.Transfer.pBuffPtr = pData;
        hdwuart->Tx_Env.Transfer.XferCount = Size;
        hdwuart->Tx_Env.Transfer.OriginalLength = Size;
        hdwuart->gState = HAL_DWUART_STATE_BUSY_TX;

        REG_FIELD_WR(hdwuart->DWUARTX->DLH_IER, DWUART_ETBEI, 1);
        return HAL_OK;
    }
    else
    {
        return HAL_BUSY;
    }
}

HAL_StatusTypeDef HAL_DWUART_Receive_IT(DWUART_HandleTypeDef *hdwuart, uint8_t *pData, uint16_t Size)
{
    if (hdwuart->RxState == HAL_DWUART_STATE_READY)
    {
        if ((pData == NULL) || (Size == 0U))
        {
            return HAL_INVALIAD_PARAM;
        }

        hdwuart->Rx_Env.Transfer.pBuffPtr = pData;
        hdwuart->Rx_Env.Transfer.XferCount = Size;
        hdwuart->Rx_Env.Transfer.OriginalLength = Size;
        hdwuart->RxState = HAL_DWUART_STATE_BUSY_RX;

        DWUART_RXFIFO_Change(hdwuart);
        REG_FIELD_WR(hdwuart->DWUARTX->DLH_IER, DWUART_ERBFI, 1);
        REG_FIELD_WR(hdwuart->DWUARTX->DLH_IER, DWUART_ELSI, 1);
        return HAL_OK;
    }
    else
    {
        return HAL_BUSY;
    }
}

static void DWUART_Receive_IT(DWUART_HandleTypeDef *hdwuart, bool timeout)
{
    if (hdwuart->RxState == HAL_DWUART_STATE_BUSY_RX)
    {
        if (hdwuart->RTOEN)
        {
            while (hdwuart->DWUARTX->RFL > 1U)
            {
                *hdwuart->Rx_Env.Transfer.pBuffPtr++ = (uint8_t)(hdwuart->DWUARTX->RBR_THR_DLL & 0xff);
                if (--hdwuart->Rx_Env.Transfer.XferCount == 1U)
                {
                    *hdwuart->Rx_Env.Transfer.pBuffPtr++ = (uint8_t)(hdwuart->DWUARTX->RBR_THR_DLL & 0xff);
                    hdwuart->RxState = HAL_DWUART_STATE_READY;
                    REG_FIELD_WR(hdwuart->DWUARTX->DLH_IER, DWUART_ERBFI, 0);
                    REG_FIELD_WR(hdwuart->DWUARTX->DLH_IER, DWUART_ELSI, 0);
                    HAL_DWUART_RxCpltCallback(hdwuart);
                    return;
                }
            }
            if (timeout)
            {
                *hdwuart->Rx_Env.Transfer.pBuffPtr++ = (uint8_t)(hdwuart->DWUARTX->RBR_THR_DLL & 0xff);
                hdwuart->Rx_Env.Transfer.XferCount--;
                hdwuart->RxState = HAL_DWUART_STATE_READY;
                REG_FIELD_WR(hdwuart->DWUARTX->DLH_IER, DWUART_ERBFI, 0);
                REG_FIELD_WR(hdwuart->DWUARTX->DLH_IER, DWUART_ELSI, 0);
                HAL_DWUART_RxRTOCallback(hdwuart, hdwuart->Rx_Env.Transfer.OriginalLength - hdwuart->Rx_Env.Transfer.XferCount);
                return;
            }
        }
        else
        {
            while (hdwuart->DWUARTX->RFL > 0U)
            {
                *hdwuart->Rx_Env.Transfer.pBuffPtr++ = (uint8_t)(hdwuart->DWUARTX->RBR_THR_DLL & 0xff);
                if (--hdwuart->Rx_Env.Transfer.XferCount == 0U)
                {
                    hdwuart->RxState = HAL_DWUART_STATE_READY;
                    REG_FIELD_WR(hdwuart->DWUARTX->DLH_IER, DWUART_ERBFI, 0);
                    REG_FIELD_WR(hdwuart->DWUARTX->DLH_IER, DWUART_ELSI, 0);
                    HAL_DWUART_RxCpltCallback(hdwuart);
                    return;
                }
            }
        }
        DWUART_RXFIFO_Change(hdwuart);
    }
}

static void DWUART_Transmit_IT(DWUART_HandleTypeDef *hdwuart)
{
    if (hdwuart->gState == HAL_DWUART_STATE_BUSY_TX)
    {
        if (hdwuart->Tx_Env.Transfer.XferCount == 0U)
        {
            REG_FIELD_WR(hdwuart->DWUARTX->DLH_IER, DWUART_ETBEI, 0);
            hdwuart->gState = HAL_DWUART_STATE_READY;
            HAL_DWUART_TxCpltCallback(hdwuart);
            return;
        }
        else
        {
            hdwuart->DWUARTX->RBR_THR_DLL = *hdwuart->Tx_Env.Transfer.pBuffPtr++ & 0xff;
            hdwuart->Tx_Env.Transfer.XferCount--;
        }
    }
}

void HAL_DWUARTx_IRQHandler(DWUART_HandleTypeDef *hdwuart)
{
    uint8_t temp;
    switch ((uint8_t)(hdwuart->DWUARTX->IIR_FCR & DWUART_IID_MASK))
    {
    case DWUART_INTERRUPT_ID_RECEIVE_LINE_STATUS:
        temp = (uint8_t)(hdwuart->DWUARTX->LSR & 0xe);
        if (temp != 0)
        {
            hdwuart->RxState = HAL_DWUART_STATE_READY;
            REG_FIELD_WR(hdwuart->DWUARTX->DLH_IER, DWUART_ERBFI, 0);
            REG_FIELD_WR(hdwuart->DWUARTX->DLH_IER, DWUART_ELSI, 0);
            HAL_DWUART_RxErrorCallback(hdwuart, temp);
        }
        break;
    case DWUART_INTERRUPT_ID_RECEIVE_DATA_AVAILABLE:
        DWUART_Receive_IT(hdwuart, false);
        break;
    case DWUART_INTERRUPT_ID_CHARACTER_TIMEOUT:
        DWUART_Receive_IT(hdwuart, true);
        break;
    case DWUART_INTERRUPT_ID_THR_EMPTY:
        DWUART_Transmit_IT(hdwuart);
        break;
    }
}