#include "ls_hal_mjtag.h"
#include "ls_msp_mjtag.h"
#include "field_manipulate.h"

#define MJTAG_TDO_FIFO_DEPTH (0x10)
#define MJTAG_FIFO_STATE_WRITE (true)
#define MJTAG_FIFO_STATE_START (false)

__attribute__((weak)) void HAL_MJTAG_Transmit_CallBack(void){}

void HAL_MJTAG_Init(MJTAG_HandleTypeDef *mjtag_h, MJTAG_Init_Param *init_param)
{
    HAL_MJTAG_MSP_Init(mjtag_h);

    mjtag_h->MJtag->CTRL = *(uint32_t *)init_param;
    mjtag_h->MJtag->TDO_FT = MJTAG_TDO_FIFO_DEPTH/2;

    mjtag_h->state = HAL_MJTAG_STATE_READY;
}

void HAL_MJTAG_DeInit(MJTAG_HandleTypeDef *mjtag_h)
{
    HAL_MJTAG_MSP_DeInit(mjtag_h);
}

static void mjtag_config(MJTAG_HandleTypeDef *mjtag_h, MJTAG_Frame_Param *param)
{
    mjtag_h->MJtag->INTR_MSK = 0x0;
    mjtag_h->MJtag->INTR_CLR = MJTAG_INTR_ALL_MASK;
    mjtag_h->state = HAL_MJTAG_STATE_BUSY;
    mjtag_h->Interuupt = *param;
    mjtag_h->rx_count = param->count;
}

static void mjtag_fifo_push(MJTAG_HandleTypeDef *mjtag_h)
{
    mjtag_h->Interuupt.count--;
    mjtag_h->MJtag->FIFO_WREN = MJTAG_FIFO_STATE_WRITE;
    mjtag_h->MJtag->TMS = *mjtag_h->Interuupt.tms++;
    mjtag_h->MJtag->TDI = *mjtag_h->Interuupt.tdi++;
    mjtag_h->MJtag->DW = *mjtag_h->Interuupt.bitnum++;
    mjtag_h->MJtag->FIFO_PUSH = MJTAG_FIFO_PUSH_ALL_MASK;
    mjtag_h->MJtag->FIFO_WREN = MJTAG_FIFO_STATE_START;
}

HAL_StatusTypeDef HAL_MJTAG_Transmit_Polling(MJTAG_HandleTypeDef *mjtag_h, MJTAG_Frame_Param *param)
{
    if (mjtag_h->state == HAL_MJTAG_STATE_BUSY)
        return HAL_BUSY;
    
    mjtag_config(mjtag_h, param);

    while (mjtag_h->Interuupt.count || mjtag_h->rx_count)
    {
        if (mjtag_h->Interuupt.count)
        {
            mjtag_h->MJtag->INTR_CLR = MJTAG_INTR_TX_FIFO_FULL_MASK;
            if (!(mjtag_h->MJtag->INTR_RAW & MJTAG_INTR_TX_FIFO_FULL_MASK))
                mjtag_fifo_push(mjtag_h);
        }
        if (mjtag_h->rx_count)
        {
            mjtag_h->MJtag->INTR_CLR = MJTAG_INTR_RX_FIFO_EMPTY_MASK;
            if (!(mjtag_h->MJtag->INTR_RAW & MJTAG_INTR_RX_FIFO_EMPTY_MASK))
            {
                mjtag_h->rx_count--;
                *mjtag_h->Interuupt.tdo++ = mjtag_h->MJtag->TDO;
            }
        }
    }
    mjtag_h->state = HAL_MJTAG_STATE_READY;
    return HAL_OK;
}

static void mjtag_it(MJTAG_HandleTypeDef *mjtag_h)
{
    while (mjtag_h->rx_count)
    {
        mjtag_h->MJtag->INTR_CLR = MJTAG_INTR_RX_FIFO_EMPTY_MASK;
        if (mjtag_h->MJtag->INTR_RAW & MJTAG_INTR_RX_FIFO_EMPTY_MASK)
            break;
        
        *mjtag_h->Interuupt.tdo++ = mjtag_h->MJtag->TDO;
        if (--mjtag_h->rx_count == 0)
        {
            mjtag_h->state = HAL_MJTAG_STATE_READY;
            HAL_MJTAG_Transmit_CallBack();
            return;
        }
    }

    uint32_t count = (mjtag_h->Interuupt.count <= (MJTAG_TDO_FIFO_DEPTH/2)) ? mjtag_h->Interuupt.count : (MJTAG_TDO_FIFO_DEPTH/2);
    mjtag_h->MJtag->TDO_FT = count - 1;
    for (uint8_t i = 0; i < count; i++)
    {
        mjtag_fifo_push(mjtag_h);
    }
}

HAL_StatusTypeDef HAL_MJTAG_Transmit_IT(MJTAG_HandleTypeDef *mjtag_h, MJTAG_Frame_Param *param)
{
    if (mjtag_h->state == HAL_MJTAG_STATE_BUSY)
        return HAL_BUSY;

    mjtag_config(mjtag_h, param);
    mjtag_it(mjtag_h);

    mjtag_h->MJtag->INTR_MSK = MJTAG_INTR_RX_FIFO_ALMOST_FULL_MASK;
    return HAL_OK;
}

void HAL_MJTAG_IRQHandler(MJTAG_HandleTypeDef *mjtag_h)
{
    uint32_t status = mjtag_h->MJtag->INTR_STT;
    if (status & MJTAG_INTR_RX_FIFO_ALMOST_FULL_MASK)
    {
        mjtag_h->MJtag->INTR_CLR = MJTAG_INTR_RX_FIFO_ALMOST_FULL_MASK;
        mjtag_it(mjtag_h);
    }
}