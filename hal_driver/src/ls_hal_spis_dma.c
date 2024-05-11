#include "ls_msp_spis.h"
#include "ls_hal_spis.h"
#include "ls_hal_dmacv3.h"
#include "field_manipulate.h"
#include <stddef.h>

__attribute__((weak)) void  HAL_SPIS_DMA_TxCpltCallback(){};
__attribute__((weak)) void  HAL_SPIS_DMA_RxCpltCallback(){};
__attribute__((weak)) void  HAL_SPIS_DMA_TxRxCpltCallback(){};
static void SPIS_Transmit_DMA_Callback(DMA_Controller_HandleTypeDef *hdma, uint32_t param, uint8_t ch_idx, uint32_t *lli, bool tfr_end)
{
    if(tfr_end == false)
    {
        HAL_SPIS_DMA_TxCpltCallback();
    }
}

static void SPIS_Receive_DMA_Callback(DMA_Controller_HandleTypeDef *hdma, uint32_t param, uint8_t ch_idx, uint32_t *lli, bool tfr_end)
{
    if(tfr_end == false)
    {
        SPIS_HandleTypeDef *spis = (SPIS_HandleTypeDef *)param;        
        if(!READ_BIT(spis->Instance->TX_CTRL,SPIS_TX_DIS))
        {
            HAL_SPIS_DMA_TxRxCpltCallback();
        }
        else
        {
            HAL_SPIS_DMA_RxCpltCallback();
        }
    }
}

static void spis_dma_config(SPIS_HandleTypeDef *spis, void *Tx_Data, void *Rx_Data, uint16_t Count)
{
    uint8_t *pTxData, *pRxData;
    pTxData = Tx_Data;
    pRxData = Rx_Data;
    struct ch_reg cfg;
    /* Tx parameter initialize*/
    if(pTxData)
    {  
        DMA_CHANNEL_CFG(cfg,
            spis->Tx_Env.DMA.Channel,
            (uint32_t)pTxData,
            &spis->Instance->TX_FIFO_DAT,
            TRANSFER_WIDTH_32BITS,
            Count/4,
            M2P,
            0,
            HAL_SPIS_TX_DMA_Handshake_Get(spis),
            0,0,0,0);
        HAL_DMA_Channel_Start_IT(spis->DMAC_Instance, &cfg, SPIS_Transmit_DMA_Callback, (uint32_t)spis);
    }

    /* Rx parameter initialize*/
    if(pRxData)
    {
        DMA_CHANNEL_CFG(cfg,
            spis->Rx_Env.DMA.Channel,
            &spis->Instance->RX_FIFO_DAT,
            (uint32_t)pRxData,
            TRANSFER_WIDTH_32BITS,
            Count/4,
            P2M,
            0,
            HAL_SPIS_RX_DMA_Handshake_Get(spis),
            0,0,0,0);    
        HAL_DMA_Channel_Start_IT(spis->DMAC_Instance, &cfg, SPIS_Receive_DMA_Callback, (uint32_t)spis);
    }

}

HAL_StatusTypeDef HAL_SPIS_Transmit_DMA(SPIS_HandleTypeDef *spis, uint8_t *pTxData, uint16_t Size)
{
    spis_tx_cfg(spis);
    REG_FIELD_WR(spis->Instance->TX_CTRL, SPIS_TX_DMA_EN, 1);
    spis_dma_config(spis, pTxData, NULL, Size);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_SPIS_Receive_DMA(SPIS_HandleTypeDef *spis, uint8_t *pRxData, uint16_t Size)
{
    spis_rx_cfg(spis);
    REG_FIELD_WR(spis->Instance->RX_CTRL, SPIS_RX_DMA_EN, 1);
    spis_dma_config(spis, NULL, pRxData, Size);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_SPIS_TransmitReceive_DMA(SPIS_HandleTypeDef *spis, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size)
{
    spis_tx_rx_cfg(spis);
    REG_FIELD_WR(spis->Instance->TX_CTRL, SPIS_TX_DMA_EN, 1);
    REG_FIELD_WR(spis->Instance->RX_CTRL, SPIS_RX_DMA_EN, 1);
    spis_dma_config(spis, pTxData, pRxData, Size);
    return HAL_OK;
}

uint32_t HAL_SPIS_Transmit_DMA_Abort(SPIS_HandleTypeDef *spis)
{
    REG_FIELD_WR(spis->Instance->TX_CTRL, SPIS_TX_DMA_EN, 0);
    return HAL_DMA_Channel_Abort(spis->DMAC_Instance, spis->Tx_Env.DMA.Channel);
}

uint32_t HAL_SPIS_Receive_DMA_Abort(SPIS_HandleTypeDef *spis)
{
    REG_FIELD_WR(spis->Instance->RX_CTRL, SPIS_RX_DMA_EN, 0);
    return HAL_DMA_Channel_Abort(spis->DMAC_Instance, spis->Rx_Env.DMA.Channel);
}
