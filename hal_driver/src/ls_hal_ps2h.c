#include "ls_hal_ps2h.h"
#include "ls_msp_ps2h.h"
#include "field_manipulate.h"
#include "systick.h"
#include <stddef.h>

static void PS2H_Transmit_IT(PS2H_HandleTypeDef *hps2h);
static void PS2H_Receive_IT(PS2H_HandleTypeDef *hps2h);

__attribute__((weak)) void HAL_PS2H_TxCpltCallback(PS2H_HandleTypeDef *hps2h) {}
__attribute__((weak)) void HAL_PS2H_RxCpltCallback(PS2H_HandleTypeDef *hps2h) {}
__attribute__((weak)) void HAL_PS2H_TxErrorCallBack(PS2H_HandleTypeDef *hps2h) {}
__attribute__((weak)) void HAL_PS2H_RxErrorCallBack(PS2H_HandleTypeDef *hps2h, RxErrorMode errmode) {}

static bool ps2h_flag_poll(va_list va)
{
    PS2H_HandleTypeDef *ps2h = va_arg(va, PS2H_HandleTypeDef *);
    uint32_t flag = va_arg(va, uint32_t);
    if ((ps2h->PS2HX->RX_FLVL & flag) > 0U)
    {
        return true;
    }
    else
    {
        return false;
    }
}

HAL_StatusTypeDef HAL_PS2H_Init(PS2H_HandleTypeDef *hps2h, PS2H_Param *param)
{
    if (hps2h == NULL)
    {
        return HAL_INVALIAD_PARAM;
    }

    HAL_PS2H_MSP_Init(hps2h);
    hps2h->PS2HX->PS2H_CTRL0 = FIELD_BUILD(PS2H_CTRL0_FIL_NUM, param->flt_num) |
                               FIELD_BUILD(PS2H_CTRL0_CYC_1US, SDK_HCLK_MHZ - 1) |
                               FIELD_BUILD(PS2H_CTRL0_DRV_DLY, PS2H_INIT_DRIVER_DELY) |
                               FIELD_BUILD(PS2H_CTRL0_CAP_DLY, PS2H_INIT_CAPTURE_DELY);
    hps2h->PS2HX->PS2H_CTRL1 = FIELD_BUILD(PS2H_CTRL1_ERR_MODE, param->err_mode) |
                               FIELD_BUILD(PS2H_CTRL1_TX_MODE, param->tx_mode) |
                               FIELD_BUILD(PS2H_CTRL1_RX_THR, FIFO_RECEIVE_TRIGGER_0BYTE);

    hps2h->State = HAL_PS2H_STATE_READY;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_PS2H_DeInit(PS2H_HandleTypeDef *hps2h)
{
    HAL_PS2H_DeInit(hps2h);

    hps2h->State = HAL_PS2H_STATE_RESET;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_PS2H_Transmit(PS2H_HandleTypeDef *hps2h, uint8_t *pData, uint16_t Size)
{
    if (hps2h->State == HAL_PS2H_STATE_READY)
    {
        if ((pData == NULL) || (Size == 0U))
        {
            return HAL_INVALIAD_PARAM;
        }
        hps2h->State = HAL_PS2H_STATE_BUSY;

        hps2h->PS2HX->INTR_MSK = 0;
        hps2h->PS2HX->INTR_CLR = PS2H_INTR_ALL_MASK;

        while (Size > 0U)
        {
            while (hps2h->PS2HX->TX_REQ & PS2H_TX_REQ_MASK) ;
            hps2h->PS2HX->TX_DAT = *pData & (uint8_t)0xFF;
            hps2h->PS2HX->TX_REQ = PS2H_TX_REQ_MASK;

            /* Wait for transmit finishes */
            while ((hps2h->PS2HX->INTR_RAW & PS2H_INTR_TX_END_MASK) == 0) ;
            hps2h->PS2HX->INTR_CLR = PS2H_INTR_TX_END_MASK;

            /* Check ack bit */
            if (hps2h->PS2HX->INTR_MSK & PS2H_INTR_ERR_ACK_MASK)
            {
                hps2h->PS2HX->INTR_CLR = PS2H_INTR_ERR_ACK_MASK;
                if (REG_FIELD_RD(hps2h->PS2HX->PS2H_CTRL1, PS2H_CTRL1_ERR_MODE) == PS2_TO_ERROR_SATE)
                {
                    hps2h->PS2HX->ERR_CLR = PS2H_ERR_CLR_MASK;
                    hps2h->State = HAL_PS2H_STATE_READY;
                    return HAL_ERROR;
                }
            }
            else
            {
                Size--;
                pData++;
            }
        }

        hps2h->State = HAL_PS2H_STATE_READY;
        return HAL_OK;
    }
    else
    {
        return HAL_BUSY;
    }
}

HAL_StatusTypeDef HAL_PS2H_Receive(PS2H_HandleTypeDef *hps2h, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    uint32_t timeout = SYSTICK_MS2TICKS(Timeout);
    uint32_t tickstart = systick_get_value();

    if (hps2h->State == HAL_PS2H_STATE_READY)
    {
        if ((pData == NULL) || (Size == 0U))
        {
            return HAL_INVALIAD_PARAM;
        }

        hps2h->State = HAL_PS2H_STATE_BUSY;

        hps2h->PS2HX->INTR_MSK = 0;
        hps2h->PS2HX->INTR_CLR = PS2H_INTR_ALL_MASK;

        if (Timeout != HAL_MAX_DELAY)
        {
            while (Size > 0)
            {
                if (systick_poll_timeout(tickstart, timeout, ps2h_flag_poll, hps2h, PS2H_RX_FLVL_MASK))
                {
                    hps2h->State = HAL_PS2H_STATE_READY;
                    return HAL_TIMEOUT;
                }
                else
                {
                    *pData++ = (uint8_t)(hps2h->PS2HX->RX_DAT & PS2H_RX_DAT_MASK);
                    Size--;
                    if (hps2h->PS2HX->INTR_RAW & PS2H_INTR_RXERROR_MASK)
                    {
                        hps2h->PS2HX->INTR_CLR = PS2H_INTR_RXERROR_MASK;
                        if (REG_FIELD_RD(hps2h->PS2HX->PS2H_CTRL1, PS2H_CTRL1_ERR_MODE) == PS2_TO_ERROR_SATE)
                        {
                            hps2h->PS2HX->ERR_CLR = PS2H_ERR_CLR_MASK;
                        }
                        hps2h->State = HAL_PS2H_STATE_READY;
                        return HAL_ERROR;
                    }
                }
            }
        }
        else
        {
            while (Size > 0)
            {
                if (REG_FIELD_RD(hps2h->PS2HX->RX_FLVL, PS2H_RX_FLVL) > 0U)
                {
                    *pData++ = (uint8_t)(hps2h->PS2HX->RX_DAT & PS2H_RX_DAT_MASK);
                    Size--;
                    if (hps2h->PS2HX->INTR_RAW & PS2H_INTR_RXERROR_MASK)
                    {
                        hps2h->PS2HX->INTR_CLR = PS2H_INTR_RXERROR_MASK;
                        if (REG_FIELD_RD(hps2h->PS2HX->PS2H_CTRL1, PS2H_CTRL1_ERR_MODE) == PS2_TO_ERROR_SATE)
                        {
                            hps2h->PS2HX->ERR_CLR = PS2H_ERR_CLR_MASK;
                        }
                        hps2h->State = HAL_PS2H_STATE_READY;
                        return HAL_ERROR;
                    }
                }
            }
        }

        hps2h->State = HAL_PS2H_STATE_READY;
        return HAL_OK;
    }
    else
    {
        return HAL_BUSY;
    }
}

HAL_StatusTypeDef HAL_PS2H_Transmit_IT(PS2H_HandleTypeDef *hps2h, uint8_t *pData, uint16_t Size)
{
    if (hps2h->State == HAL_PS2H_STATE_READY)
    {
        if ((pData == NULL) || (Size == 0U))
        {
            return HAL_INVALIAD_PARAM;
        }
        hps2h->State = HAL_PS2H_STATE_BUSY;

        hps2h->pBuffPtr = pData;
        hps2h->XferCount = Size;

        hps2h->PS2HX->INTR_CLR = PS2H_INTR_TX_END_MASK | PS2H_INTR_ERR_ACK_MASK;
        hps2h->PS2HX->INTR_MSK = PS2H_INTR_TX_END_MASK | PS2H_INTR_ERR_ACK_MASK;

        PS2H_Transmit_IT(hps2h);
        return HAL_OK;
    }
    else
    {
        return HAL_BUSY;
    }
}

HAL_StatusTypeDef HAL_PS2H_Receive_IT(PS2H_HandleTypeDef *hps2h, uint8_t *pData, uint16_t Size)
{
    if (hps2h->State == HAL_PS2H_STATE_READY)
    {
        if ((pData == NULL) || (Size == 0U))
        {
            return HAL_INVALIAD_PARAM;
        }
        hps2h->State = HAL_PS2H_STATE_BUSY;

        hps2h->pBuffPtr = pData;
        hps2h->XferCount = Size;

        if (Size >= 4)
        {
            REG_FIELD_WR(hps2h->PS2HX->PS2H_CTRL1, PS2H_CTRL1_RX_THR, FIFO_RECEIVE_TRIGGER_3BYTE);
        }
        else
        {
            REG_FIELD_WR(hps2h->PS2HX->PS2H_CTRL1, PS2H_CTRL1_RX_THR, FIFO_RECEIVE_TRIGGER_0BYTE);
        }

        hps2h->PS2HX->INTR_CLR = PS2H_INTR_RXERROR_MASK | PS2H_INTR_RX_FIFO_MASK | PS2H_INTR_RX_FIFO_OVER_MASK;
        hps2h->PS2HX->INTR_MSK = PS2H_INTR_RXERROR_MASK | PS2H_INTR_RX_FIFO_MASK | PS2H_INTR_RX_FIFO_OVER_MASK;
        return HAL_OK;
    }
    else
    {
        return HAL_BUSY;
    }
}

static void PS2H_Transmit_IT(PS2H_HandleTypeDef *hps2h)
{
    if (hps2h->XferCount > 0U)
    {
        hps2h->XferCount--;
        hps2h->PS2HX->TX_DAT = *hps2h->pBuffPtr++ & (uint8_t)0xFF;
        hps2h->PS2HX->TX_REQ = PS2H_TX_REQ_MASK;
    }
    else
    {
        hps2h->PS2HX->INTR_MSK = 0;
        hps2h->State = HAL_PS2H_STATE_READY;
        HAL_PS2H_TxCpltCallback(hps2h);
    }
}

static void PS2H_Receive_IT(PS2H_HandleTypeDef *hps2h)
{
    uint8_t fifo_level = (uint8_t)(hps2h->PS2HX->RX_FLVL & PS2H_RX_FLVL_MASK);
    for (uint8_t i = 0; i < fifo_level; i++)
    {
        *hps2h->pBuffPtr++ = (uint8_t)(hps2h->PS2HX->RX_DAT & (uint8_t)0xFF);
        if (--hps2h->XferCount == 0U)
        {
            hps2h->PS2HX->INTR_MSK = 0;
            hps2h->State = HAL_PS2H_STATE_READY;
            HAL_PS2H_RxCpltCallback(hps2h);
            return;
        }
    }
    if (hps2h->XferCount < 4)
    {
        REG_FIELD_WR(hps2h->PS2HX->PS2H_CTRL1, PS2H_CTRL1_RX_THR, FIFO_RECEIVE_TRIGGER_0BYTE);
    }
}

void HAL_PS2H_IRQHandler(PS2H_HandleTypeDef *hps2h)
{
    uint32_t intr_state = hps2h->PS2HX->INTR_STT;

    /* transmit interrupt processing  */
    if (intr_state & PS2H_INTR_TX_END_MASK)
    {
        hps2h->PS2HX->INTR_CLR = PS2H_INTR_TX_END_MASK;
        PS2H_Transmit_IT(hps2h);
    }
    if (intr_state & PS2H_INTR_ERR_ACK_MASK)
    {
        hps2h->PS2HX->INTR_CLR = PS2H_INTR_ERR_ACK_MASK;
        hps2h->PS2HX->INTR_MSK = 0;
        hps2h->State = HAL_PS2H_STATE_READY;
        HAL_PS2H_TxErrorCallBack(hps2h);
    }

    /* receive interrupt processing  */
    if (intr_state & PS2H_INTR_RX_FIFO_MASK)
    {
        hps2h->PS2HX->INTR_CLR = PS2H_INTR_RX_FIFO_MASK;
        PS2H_Receive_IT(hps2h);
    }
    if (intr_state & PS2H_INTR_ERR_START_MASK)
    {
        hps2h->PS2HX->INTR_CLR = PS2H_INTR_ERR_START_MASK;
        hps2h->PS2HX->INTR_MSK = 0;
        hps2h->State = HAL_PS2H_STATE_READY;
        HAL_PS2H_RxErrorCallBack(hps2h, PS2_ERROR_START_BIT);
    }
    if (intr_state & PS2H_INTR_ERR_STOP_MASK)
    {
        hps2h->PS2HX->INTR_CLR = PS2H_INTR_ERR_STOP_MASK;
        hps2h->PS2HX->INTR_MSK = 0;
        hps2h->State = HAL_PS2H_STATE_READY;
        HAL_PS2H_RxErrorCallBack(hps2h, PS2_ERROR_STOP_BIT);
    }
    if (intr_state & PS2H_INTR_ERR_PAR_MASK)
    {
        hps2h->PS2HX->INTR_CLR = PS2H_INTR_ERR_PAR_MASK;
        hps2h->PS2HX->INTR_MSK = 0;
        hps2h->State = HAL_PS2H_STATE_READY;
        HAL_PS2H_RxErrorCallBack(hps2h, PS2_ERROR_PARITY_BIT);
    }
    if (intr_state & PS2H_INTR_RX_FIFO_OVER_MASK)
    {
        hps2h->PS2HX->INTR_CLR = PS2H_INTR_RX_FIFO_OVER_MASK;
        HAL_PS2H_RxErrorCallBack(hps2h, PS2H_INTR_RX_FIFO_OVER_MASK);
    }
}