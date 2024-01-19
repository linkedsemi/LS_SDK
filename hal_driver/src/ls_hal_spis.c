#include "ls_msp_spis.h"
#include "ls_hal_spis.h"
#include "field_manipulate.h"
#include "ls_soc_gpio.h"
#include "platform.h"
#include "systick.h"
#include "app_config.h"
#include "common.h"

HAL_StatusTypeDef HAL_SPIS_Init(SPIS_HandleTypeDef *spis)
{
	HAL_LSSPIS_MSP_Init(spis);
	return HAL_OK;
}

void spis_tx_cfg(SPIS_HandleTypeDef *spis)
{
    MODIFY_REG(spis->Instance->TX_CTRL, SPIS_TX_POL_MASK | SPIS_TX_START_IDX_MASK | SPIS_TX_MSB_MASK | SPIS_TX_DMA_EN_MASK | SPIS_TX_SZ_MASK | SPIS_DRV_DIS_MASK | SPIS_DRV_IDX_MASK,
               spis->Init.CLKPhase | spis->Init.FirstBit | spis->Init.Frame_Size << SPIS_TX_SZ_POS | SPIS_TX_EN | 0 << SPIS_DRV_IDX_POS);

    WRITE_REG(spis->Instance->RX_CTRL, SPIS_RX_DIS);

    if(((spis->Init.CLKPolarity == SPIS_POLARITY_LOW) && (spis->Init.CLKPhase == SPIS_PHASE_1EDGE)) || ((spis->Init.CLKPolarity == SPIS_POLARITY_HIGH) && (spis->Init.CLKPhase == SPIS_PHASE_2EDGE)))
    {
        REG_FIELD_WR(spis->Instance->TX_CTRL, SPIS_TX_POL, SPIS_POLARITY_HIGH);
    }
    else
    {
        REG_FIELD_WR(spis->Instance->TX_CTRL, SPIS_TX_POL, SPIS_POLARITY_LOW);
    }
}

void spis_rx_cfg(SPIS_HandleTypeDef *spis)
{
    MODIFY_REG(spis->Instance->RX_CTRL, SPIS_RX_POL_MASK | SPIS_RX_START_IDX_MASK | SPIS_RX_MSB_MASK | SPIS_RX_DMA_EN_MASK | SPIS_RX_SZ_MASK | SPIS_CAP_DIS_MASK | SPIS_CAP_IDX_MASK | SPIS_CAP_INFNT_MASK,
               spis->Init.CLKPhase | spis->Init.FirstBit | spis->Init.Frame_Size << SPIS_RX_SZ_POS | SPIS_RX_EN | RECEIVE_ALL_FRAMES);

    WRITE_REG(spis->Instance->TX_CTRL, SPIS_TX_DIS);

    if(((spis->Init.CLKPolarity == SPIS_POLARITY_LOW) && (spis->Init.CLKPhase == SPIS_PHASE_1EDGE)) || ((spis->Init.CLKPolarity == SPIS_POLARITY_HIGH) && (spis->Init.CLKPhase == SPIS_PHASE_2EDGE)))
    {
        REG_FIELD_WR(spis->Instance->RX_CTRL, SPIS_RX_POL, SPIS_POLARITY_LOW);
    }
    else
    {
        REG_FIELD_WR(spis->Instance->RX_CTRL, SPIS_RX_POL, SPIS_POLARITY_HIGH);
    }  
}

void spis_tx_rx_cfg(SPIS_HandleTypeDef *spis)
{
    MODIFY_REG(spis->Instance->TX_CTRL, SPIS_TX_POL_MASK | SPIS_TX_START_IDX_MASK | SPIS_TX_MSB_MASK | SPIS_TX_DMA_EN_MASK | SPIS_TX_SZ_MASK | SPIS_DRV_DIS_MASK | SPIS_DRV_IDX_MASK,
               spis->Init.CLKPhase | spis->Init.FirstBit | spis->Init.Frame_Size << SPIS_TX_SZ_POS | SPIS_TX_EN | 0 << SPIS_DRV_IDX_POS);

    MODIFY_REG(spis->Instance->RX_CTRL, SPIS_RX_POL_MASK | SPIS_RX_START_IDX_MASK | SPIS_RX_MSB_MASK | SPIS_RX_DMA_EN_MASK | SPIS_RX_SZ_MASK | SPIS_CAP_DIS_MASK | SPIS_CAP_IDX_MASK | SPIS_CAP_INFNT_MASK,
               spis->Init.CLKPhase | spis->Init.FirstBit | spis->Init.Frame_Size << SPIS_RX_SZ_POS | SPIS_RX_EN | RECEIVE_ALL_FRAMES);

    if(((spis->Init.CLKPolarity == SPIS_POLARITY_LOW) && (spis->Init.CLKPhase == SPIS_PHASE_1EDGE)) || ((spis->Init.CLKPolarity == SPIS_POLARITY_HIGH) && (spis->Init.CLKPhase == SPIS_PHASE_2EDGE)))
    {
        REG_FIELD_WR(spis->Instance->TX_CTRL, SPIS_TX_POL, SPIS_POLARITY_HIGH);
        REG_FIELD_WR(spis->Instance->RX_CTRL, SPIS_RX_POL, SPIS_POLARITY_LOW);
    }
    else
    {
        REG_FIELD_WR(spis->Instance->TX_CTRL, SPIS_TX_POL, SPIS_POLARITY_LOW);
        REG_FIELD_WR(spis->Instance->RX_CTRL, SPIS_RX_POL, SPIS_POLARITY_HIGH);
    }
}

HAL_StatusTypeDef HAL_LSSPIS_DeInit(SPIS_HandleTypeDef *spis)
{
	HAL_LSSPIS_MSP_DeInit(spis);
	return HAL_OK;
}

static void tx_para_init(SPIS_HandleTypeDef *spis, uint8_t *pTxData, uint16_t Size)
{
    spis->Tx_Env.Interrupt.pBuffPtr = (uint8_t*)pTxData;
    spis->Tx_Env.Interrupt.XferCount = Size;
}

static void rx_para_init(SPIS_HandleTypeDef *spis, uint8_t *pRxData, uint16_t Size)
{
    spis->Rx_Env.Interrupt.pBuffPtr = (uint8_t*)pRxData;
    spis->Rx_Env.Interrupt.XferCount = Size;
}

static void spis_tx_load_data_32bit(SPIS_HandleTypeDef *spis)
{
    spis->Instance->TX_FIFO_DAT = *((uint32_t *)spis->Tx_Env.Interrupt.pBuffPtr);
    spis->Tx_Env.Interrupt.pBuffPtr += sizeof(uint32_t);
    spis->Tx_Env.Interrupt.XferCount -= 4;
}

static void spis_rx_load_data_32bit(SPIS_HandleTypeDef *spis)
{
    *(uint32_t *)spis->Rx_Env.Interrupt.pBuffPtr = spis->Instance->RX_FIFO_DAT;
    spis->Rx_Env.Interrupt.pBuffPtr += sizeof(uint32_t);
    spis->Rx_Env.Interrupt.XferCount -= 4;
}

static void spis_rx_flvl_set(SPIS_HandleTypeDef *spis)
{
    if (spis->Rx_Env.Interrupt.XferCount <= 16)
    {
        WRITE_REG(spis->Instance->RX_FIFO_THR, 1);
    }
    else
    {
        WRITE_REG(spis->Instance->RX_FIFO_THR, 4);
    }
}

static HAL_StatusTypeDef spis_timeout_handle(SPIS_HandleTypeDef *spis, uint32_t end_tick)
{
    HAL_StatusTypeDef errorcode = HAL_OK;
    if (time_diff(systick_get_value(), end_tick) > 0U)
    {
        errorcode = HAL_TIMEOUT;
    }
    return errorcode;
}

static void spis_data_transfer(SPIS_HandleTypeDef *spis, uint32_t end_tick)
{
    while((spis->Tx_Env.Interrupt.XferCount > 0U) || (spis->Rx_Env.Interrupt.XferCount > 0U))
    {
        if((spis->Tx_Env.Interrupt.XferCount > 0U) && (READ_REG(spis->Instance->TX_FIFO_FLVL) != SPIS_FIFO_DEPTH))
        {
                io_toggle_pin(PH07);
                spis_tx_load_data_32bit(spis);
        }
        if((spis->Rx_Env.Interrupt.XferCount > 0U) && (READ_REG(spis->Instance->RX_FIFO_FLVL) != 0))
        {
            spis_rx_load_data_32bit(spis);
        }
        spis_timeout_handle(spis, end_tick);
    }
}

HAL_StatusTypeDef HAL_SPIS_Transmit(SPIS_HandleTypeDef *spis, uint8_t *pTxData, uint16_t Size, uint32_t Timeout)
{
    uint32_t tickstart = systick_get_value();
    uint32_t timeout = SYSTICK_MS2TICKS(Timeout);
    uint32_t end_tick = tickstart + timeout;
    spis_tx_cfg(spis);
    tx_para_init(spis, pTxData, Size);
    spis_data_transfer(spis, end_tick);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_SPIS_Receive(SPIS_HandleTypeDef *spis, uint8_t *pRxData, uint16_t Size, uint32_t Timeout)
{
    uint32_t tickstart = systick_get_value();
    uint32_t timeout = SYSTICK_MS2TICKS(Timeout);
    uint32_t end_tick = tickstart + timeout;        
    spis_rx_cfg(spis);
    rx_para_init(spis, pRxData, Size);
    spis_data_transfer(spis, end_tick);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_SPIS_TransmitReceive(SPIS_HandleTypeDef *spis, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size, uint32_t Timeout)
{
    uint32_t tickstart = systick_get_value();
    uint32_t timeout = SYSTICK_MS2TICKS(Timeout);
    uint32_t end_tick = tickstart + timeout;
    spis_tx_rx_cfg(spis);
    tx_para_init(spis, pTxData, Size);
    rx_para_init(spis, pRxData, Size);
    spis_data_transfer(spis, end_tick);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_SPIS_Transmit_IT(SPIS_HandleTypeDef *spis, uint8_t *pTxData, uint16_t Size)
{
    spis_tx_cfg(spis);
    tx_para_init(spis, pTxData, Size);
    spis_tx_load_data_32bit(spis);
    WRITE_REG(spis->Instance->TX_FIFO_THR, 1);
    WRITE_REG(spis->Instance->INTR_CLR, SPIS_INTR_TX_FIFO_MASK | SPIS_INTR_TX_UDR_MASK);
    WRITE_REG(spis->Instance->INTR_MSK, SPIS_INTR_TX_FIFO_MASK | SPIS_INTR_TX_UDR_MASK);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_SPIS_Receive_IT(SPIS_HandleTypeDef *spis, uint8_t *pRxData, uint16_t Size)
{
    spis_rx_cfg(spis);
    rx_para_init(spis, pRxData, Size);
    spis_rx_flvl_set(spis);
    WRITE_REG(spis->Instance->INTR_CLR, SPIS_INTR_RX_FIFO_MASK | SPIS_INTR_RX_OVR_MASK);
    WRITE_REG(spis->Instance->INTR_MSK, SPIS_INTR_RX_FIFO_MASK | SPIS_INTR_RX_OVR_MASK);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_SPIS_TransmitReceive_IT(SPIS_HandleTypeDef *spis, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size)
{
    spis_tx_rx_cfg(spis);
    tx_para_init(spis, pTxData, Size);
    rx_para_init(spis, pRxData, Size);
    WRITE_REG(spis->Instance->INTR_CLR, SPIS_INTR_TX_FIFO_MASK | SPIS_INTR_TX_UDR_MASK | SPIS_INTR_RX_FIFO_MASK | SPIS_INTR_RX_OVR_MASK);
    WRITE_REG(spis->Instance->INTR_MSK, SPIS_INTR_TX_FIFO_MASK | SPIS_INTR_TX_UDR_MASK | SPIS_INTR_RX_FIFO_MASK | SPIS_INTR_RX_OVR_MASK);
    return HAL_OK;
}

__attribute__((weak)) void HAL_SPIS_TxCpltCallback(){}
__attribute__((weak)) void HAL_SPIS_RxCpltCallback(){}
__attribute__((weak)) void HAL_SPIS_Tx_UDR_Callback(){}
__attribute__((weak)) void HAL_SPIS_Rx_OVR_Callback(){}
void HAL_LSSPIS_IRQHandler(SPIS_HandleTypeDef* spis)
{
    uint32_t isrflags = spis->Instance->INTR_STT;

    if(isrflags & SPIS_INTR_TX_UDR_MASK)
    {
        spis->Instance->INTR_CLR = SPIS_INTR_TX_UDR_MASK;
		HAL_SPIS_Tx_UDR_Callback();
    }
    if (isrflags & SPIS_INTR_RX_OVR_MASK)
    {
        spis->Instance->INTR_CLR = SPIS_INTR_RX_OVR_MASK;
        REG_FIELD_WR( spis->Instance->INTR_MSK, SPIS_INTR_RX_OVR, 0);
		HAL_SPIS_Rx_OVR_Callback();
    }
    if(isrflags & SPIS_INTR_TX_FIFO_MASK)
    {
        spis->Instance->INTR_CLR = SPIS_INTR_TX_FIFO_MASK;
        if(spis->Tx_Env.Interrupt.XferCount>0)
        {        
            spis_tx_load_data_32bit(spis);
        }
        else
        {
            REG_FIELD_WR( spis->Instance->INTR_MSK, SPIS_INTR_TX_FIFO, 0);
            HAL_SPIS_TxCpltCallback();
        }
    }

    if ((isrflags & SPIS_INTR_RX_FIFO_MASK))
    {
        uint8_t fifo_level = spis->Instance->RX_FIFO_FLVL;
        spis->Instance->INTR_CLR = SPIS_INTR_RX_FIFO_MASK;
        for(uint8_t i = 0; i<fifo_level; i++)
        {
            spis_rx_load_data_32bit(spis);
            if(spis->Rx_Env.Interrupt.XferCount == 0U)
            { 
                REG_FIELD_WR( spis->Instance->INTR_MSK, SPIS_INTR_RX_FIFO, 0);
                HAL_SPIS_RxCpltCallback();
                return;
            }
        }
        spis_rx_flvl_set(spis);
    }
}