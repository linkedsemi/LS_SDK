#include "ls_hal_ps2h.h"
#include "ls_msp_ps2h.h"
#include "field_manipulate.h"
#include "systick.h"
#include <stddef.h>

__attribute__((weak)) void HAL_PS2H_TxCpltCallback(PS2H_HandleTypeDef *hps2h) {}
__attribute__((weak)) void HAL_PS2H_TxErrorCallBack(PS2H_HandleTypeDef *hps2h) {}
__attribute__((weak)) void HAL_PS2H_RxCpltCallback(PS2H_HandleTypeDef *hps2h, uint8_t data) {}
__attribute__((weak)) void HAL_PS2H_RxErrorCallBack(PS2H_HandleTypeDef *hps2h, RxErrorMode errmode) {}

static bool ps2h_flag_poll(va_list va)
{
    PS2H_HandleTypeDef *ps2h = va_arg(va, PS2H_HandleTypeDef *);
    if (ps2h->PS2HX->RX_FLVL)
        return true;
    if (ps2h->PS2HX->INTR_RAW & PS2H_INTR_RXERROR_MASK)
        return true;
    return false;
}

static bool timer_cb(void *param)
{
    PS2H_HandleTypeDef *hps2h = param;
    if (hps2h->TxCompleteFlag == PS2_TX_IDLE)
    {
        uint32_t intr_mask = hps2h->PS2HX->INTR_MSK;
        uint32_t temp_ctrl0 = hps2h->PS2HX->PS2H_CTRL0;
        uint32_t temp_ctrl1 = hps2h->PS2HX->PS2H_CTRL1;
        HAL_PS2H_MSP_Init(hps2h);
        hps2h->PS2HX->PS2H_CTRL0 = temp_ctrl0;
        hps2h->PS2HX->PS2H_CTRL1 = temp_ctrl1;
        hps2h->PS2HX->INTR_MSK = intr_mask;

        hps2h->TxCompleteFlag = PS2_TX_TIMEOUT;
        hps2h->State = HAL_PS2H_STATE_READY;
        HAL_PS2H_TxErrorCallBack(hps2h);
    }
    return 0;
}

HAL_StatusTypeDef HAL_PS2H_Init(PS2H_HandleTypeDef *hps2h, PS2H_Param *param)
{
    if (hps2h == NULL)
        return HAL_INVALIAD_PARAM;

    HAL_PS2H_MSP_Init(hps2h);
    hps2h->PS2HX->PS2H_CTRL0 = FIELD_BUILD(PS2H_CTRL0_FIL_NUM, param->flt_num) |
                               FIELD_BUILD(PS2H_CTRL0_CYC_1US, SDK_HCLK_MHZ - 1) |
                               FIELD_BUILD(PS2H_CTRL0_DRV_DLY, PS2H_INIT_DRIVER_DELY) |
                               FIELD_BUILD(PS2H_CTRL0_CAP_DLY, PS2H_INIT_CAPTURE_DELY);
    hps2h->PS2HX->PS2H_CTRL1 = FIELD_BUILD(PS2H_CTRL1_ERR_MODE, param->err_mode) |
                               FIELD_BUILD(PS2H_CTRL1_TX_MODE, param->tx_mode) |
                               FIELD_BUILD(PS2H_CTRL1_RX_THR, FIFO_RECEIVE_TRIGGER_0BYTE);

    hps2h->State = HAL_PS2H_STATE_READY;
    hps2h->TxCompleteFlag = PS2_TX_IDLE;
    
    sw_timer_callback_set(&hps2h->swTimer, timer_cb, &hps2h->swTimer);
    sw_timer_period_set(&hps2h->swTimer, MS_2_PERIOD(15));

    return HAL_OK;
}

HAL_StatusTypeDef HAL_PS2H_DeInit(PS2H_HandleTypeDef *hps2h)
{
    HAL_PS2H_DeInit(hps2h);

    hps2h->State = HAL_PS2H_STATE_RESET;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_PS2H_Transmit(PS2H_HandleTypeDef *hps2h, uint8_t Data)
{
    if (hps2h->State != HAL_PS2H_STATE_READY)
        return HAL_BUSY;

    hps2h->State = HAL_PS2H_STATE_BUSY;
    hps2h->TxCompleteFlag = PS2_TX_IDLE;

    MODIFY_REG(hps2h->PS2HX->INTR_MSK, (PS2H_INTR_TX_END_MASK | PS2H_INTR_ERR_ACK_MASK), 0);
    hps2h->PS2HX->INTR_CLR = PS2H_INTR_TX_END_MASK | PS2H_INTR_ERR_ACK_MASK;

    while (hps2h->PS2HX->TX_REQ & PS2H_TX_REQ_MASK) ;

    hps2h->PS2HX->TX_DAT = Data;
    hps2h->PS2HX->TX_REQ = PS2H_TX_REQ_MASK;
    sw_timer_start(&hps2h->swTimer);
    
    while (1)
    {
        if (hps2h->PS2HX->INTR_RAW & PS2H_INTR_TX_END_MASK)
        {
            hps2h->State = HAL_PS2H_STATE_READY;
            hps2h->TxCompleteFlag = PS2_TX_COMPLETE;
            sw_timer_stop(&hps2h->swTimer);
            return HAL_OK;
        }
        if (hps2h->PS2HX->INTR_RAW & PS2H_INTR_ERR_ACK_MASK)
        {
            hps2h->State = HAL_PS2H_STATE_READY;
            hps2h->TxCompleteFlag = PS2_TX_ERROR;
            sw_timer_stop(&hps2h->swTimer);
            return HAL_ERROR;
        }
        if (hps2h->TxCompleteFlag == PS2_TX_TIMEOUT)
        {
            hps2h->State = HAL_PS2H_STATE_READY;
            return HAL_TIMEOUT;
        }
    }

}

HAL_StatusTypeDef HAL_PS2H_Receive(PS2H_HandleTypeDef *hps2h, uint8_t *pData, uint32_t Timeout)
{
    if (hps2h->State != HAL_PS2H_STATE_READY)
        return HAL_BUSY;

    if (pData == NULL)
        return HAL_INVALIAD_PARAM;

    uint32_t timeout = SYSTICK_MS2TICKS(Timeout);
    uint32_t tickstart = systick_get_value();

    MODIFY_REG(hps2h->PS2HX->INTR_MSK, PS2H_INTR_RXERROR_MASK | PS2H_INTR_RX_FIFO_MASK | PS2H_INTR_RX_FIFO_OVER_MASK, 0);
    hps2h->PS2HX->INTR_CLR = PS2H_INTR_ALL_MASK;

    if (Timeout != HAL_MAX_DELAY)
    {
        while (1)
        {
            if (systick_poll_timeout(tickstart, timeout, ps2h_flag_poll, hps2h))
            {
                return HAL_TIMEOUT;
            }
            else
            {
                if (hps2h->PS2HX->RX_FLVL)
                {
                    *pData = (uint8_t)hps2h->PS2HX->RX_DAT;
                    return HAL_OK;
                }
                if (hps2h->PS2HX->INTR_RAW & PS2H_INTR_RXERROR_MASK)
                {
                    hps2h->PS2HX->INTR_CLR = PS2H_INTR_RXERROR_MASK;
                    if (REG_FIELD_RD(hps2h->PS2HX->PS2H_CTRL1, PS2H_CTRL1_ERR_MODE) == PS2_TO_ERROR_STATE)
                    {
                        hps2h->PS2HX->ERR_CLR = PS2H_ERR_CLR_MASK;
                    }
                    return HAL_ERROR;
                }
            }
        }
    }
    else
    {
        while (1)
        {
            if (hps2h->PS2HX->RX_FLVL)
            {
                *pData = (uint8_t)hps2h->PS2HX->RX_DAT;
                return HAL_OK;
            }
            if (hps2h->PS2HX->INTR_RAW & PS2H_INTR_RXERROR_MASK)
            {
                hps2h->PS2HX->INTR_CLR = PS2H_INTR_RXERROR_MASK;
                if (REG_FIELD_RD(hps2h->PS2HX->PS2H_CTRL1, PS2H_CTRL1_ERR_MODE) == PS2_TO_ERROR_STATE)
                {
                    hps2h->PS2HX->ERR_CLR = PS2H_ERR_CLR_MASK;
                }
                return HAL_ERROR;
            }
        }
    }
}

HAL_StatusTypeDef HAL_PS2H_Transmit_IT(PS2H_HandleTypeDef *hps2h, uint8_t data)
{
    if (hps2h->State != HAL_PS2H_STATE_READY)
        return HAL_BUSY;

    hps2h->State = HAL_PS2H_STATE_BUSY;
    hps2h->TxCompleteFlag = PS2_TX_IDLE;

    hps2h->PS2HX->INTR_CLR = PS2H_INTR_TX_END_MASK | PS2H_INTR_ERR_ACK_MASK;
    hps2h->PS2HX->INTR_MSK |= PS2H_INTR_TX_END_MASK | PS2H_INTR_ERR_ACK_MASK;

    while (hps2h->PS2HX->TX_REQ & PS2H_TX_REQ_MASK) ;

    hps2h->PS2HX->TX_DAT = (uint32_t)data;
    hps2h->PS2HX->TX_REQ = PS2H_TX_REQ_MASK;
    sw_timer_start(&hps2h->swTimer);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_PS2H_Receive_IT_Start(PS2H_HandleTypeDef *hps2h)
{
    if (hps2h->State != HAL_PS2H_STATE_READY)
        return HAL_BUSY;

    REG_FIELD_WR(hps2h->PS2HX->PS2H_CTRL1, PS2H_CTRL1_RX_THR, FIFO_RECEIVE_TRIGGER_0BYTE);
    hps2h->PS2HX->INTR_CLR = PS2H_INTR_RXERROR_MASK | PS2H_INTR_RX_FIFO_MASK | PS2H_INTR_RX_FIFO_OVER_MASK;
    hps2h->PS2HX->INTR_MSK |= PS2H_INTR_RXERROR_MASK | PS2H_INTR_RX_FIFO_MASK | PS2H_INTR_RX_FIFO_OVER_MASK;

    return HAL_OK;
}

HAL_StatusTypeDef HAL_PS2H_Receive_IT_Stop(PS2H_HandleTypeDef *hps2h)
{
    hps2h->PS2HX->INTR_MSK &= ~(PS2H_INTR_RXERROR_MASK | PS2H_INTR_RX_FIFO_MASK | PS2H_INTR_RX_FIFO_OVER_MASK);
    return HAL_OK;
}

static void PS2H_Receive_IT(PS2H_HandleTypeDef *hps2h)
{
    uint8_t data;
    uint8_t fifo_level = (uint8_t)(hps2h->PS2HX->RX_FLVL & PS2H_RX_FLVL_MASK);
    for (uint8_t i = 0; i < fifo_level; i++)
    {
        data = (uint8_t)(hps2h->PS2HX->RX_DAT & 0xFF);
        HAL_PS2H_RxCpltCallback(hps2h, data);
    }
}

void HAL_PS2H_IRQHandler(PS2H_HandleTypeDef *hps2h)
{
    uint32_t intr_state = hps2h->PS2HX->INTR_STT;

    /* transmit interrupt processing  */
    if (intr_state & PS2H_INTR_TX_END_MASK)
    {
        hps2h->PS2HX->INTR_CLR = PS2H_INTR_TX_END_MASK;
        hps2h->State = HAL_PS2H_STATE_READY;
        hps2h->TxCompleteFlag = PS2_TX_COMPLETE;
        sw_timer_stop(&hps2h->swTimer);
        HAL_PS2H_TxCpltCallback(hps2h);
    }
    if (intr_state & PS2H_INTR_ERR_ACK_MASK)
    {
        hps2h->PS2HX->INTR_CLR = PS2H_INTR_ERR_ACK_MASK;
        hps2h->State = HAL_PS2H_STATE_READY;
        hps2h->TxCompleteFlag = PS2_TX_ERROR;
        sw_timer_stop(&hps2h->swTimer);
        HAL_PS2H_TxErrorCallBack(hps2h);
    }

    /* receive interrupt processing  */
    if (intr_state & PS2H_INTR_RX_FIFO_MASK)
    {
        hps2h->PS2HX->INTR_CLR = PS2H_INTR_RX_FIFO_MASK;
        PS2H_Receive_IT(hps2h);
    }
    if (intr_state & PS2H_INTR_RXERROR_MASK)
    {
        hps2h->PS2HX->INTR_CLR = PS2H_INTR_RXERROR_MASK;
        HAL_PS2H_RxErrorCallBack(hps2h, intr_state & PS2H_INTR_RXERROR_MASK);
        if (REG_FIELD_RD(hps2h->PS2HX->PS2H_CTRL1, PS2H_CTRL1_ERR_MODE) == PS2_TO_ERROR_STATE)
            hps2h->PS2HX->ERR_CLR = PS2H_ERR_CLR_MASK;
    }
    if (intr_state & PS2H_INTR_RX_FIFO_OVER_MASK)
    {
        hps2h->PS2HX->INTR_CLR = PS2H_INTR_RX_FIFO_OVER_MASK;
        HAL_PS2H_RxErrorCallBack(hps2h, PS2H_INTR_RX_FIFO_OVER_MASK);
    }
}