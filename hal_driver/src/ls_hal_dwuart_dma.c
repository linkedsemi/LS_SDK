#include "ls_msp_uart.h"
#include "ls_hal_dwuart.h"
#include "ls_hal_dmacv3.h"
#include "field_manipulate.h"

__attribute__((weak)) void HAL_DWUART_DMA_TxCpltCallback(DWUART_HandleTypeDef *huart) {}
__attribute__((weak)) void HAL_DWUART_DMA_RxCpltCallback(DWUART_HandleTypeDef *huart) {}

static void DWUART_Transmit_DMA_Callback(DMA_Controller_HandleTypeDef *hdma, uint32_t param, uint8_t ch_idx, uint32_t *lli, bool tfr_end)
{
    if (tfr_end == false)
    {
        DWUART_HandleTypeDef *hdwuart = (DWUART_HandleTypeDef *)param;
        hdwuart->Tx_Env.DMA.Channel_Done = true;
        HAL_DWUART_DMA_TxCpltCallback(hdwuart);
    }
}

static void DWUART_Recevie_DMA_Callback(DMA_Controller_HandleTypeDef *hdma, uint32_t param, uint8_t ch_idx, uint32_t *lli, bool tfr_end)
{
    if (tfr_end == false)
    {
        DWUART_HandleTypeDef *hdwuart = (DWUART_HandleTypeDef *)param;
        hdwuart->Rx_Env.DMA.Channel_Done = true;
        HAL_DWUART_DMA_RxCpltCallback(hdwuart);
    }
}

HAL_StatusTypeDef HAL_DWUART_Transmit_DMA(DWUART_HandleTypeDef *hdwuart, uint8_t *pData, uint16_t Size)
{
    REG_FIELD_WR(hdwuart->DWUARTX->IIR_FCR, DWUART_RCVR, DWUART_FIFO_TRANSMIT_TRIGGER_0BYTE);
    hdwuart->Tx_Env.DMA.Channel_Done = false;
    struct ch_reg cfg;
    DMA_CHANNEL_CFG(cfg,
                      hdwuart->Tx_Env.DMA.DMA_Channel,
                      pData,
                      &hdwuart->DWUARTX->RBR_THR_DLL,
                      TRANSFER_WIDTH_8BITS,
                      Size,
                      M2P,
                      0,
                      HAL_DWUART_TX_DMA_Handshake_Get(hdwuart),
                      0, 0, 0, 0);
    HAL_DMA_Channel_Start_IT(hdwuart->DMAC_Instance, &cfg, DWUART_Transmit_DMA_Callback, (uint32_t)hdwuart);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_DWUART_Receive_DMA(DWUART_HandleTypeDef *hdwuart, uint8_t *pData, uint16_t Size)
{
    hdwuart->Rx_Env.DMA.Channel_Done = false;
    REG_FIELD_WR(hdwuart->DWUARTX->IIR_FCR, DWUART_RCVR, DWUART_FIFO_RECEIVE_TRIGGER_1BYTE);
    struct ch_reg cfg;
    DMA_CHANNEL_CFG(cfg,
                      hdwuart->Rx_Env.DMA.DMA_Channel,
                      &hdwuart->DWUARTX->RBR_THR_DLL,
                      pData,
                      TRANSFER_WIDTH_8BITS,
                      Size,
                      P2M,
                      0,
                      HAL_DWUART_RX_DMA_Handshake_Get(hdwuart),
                      0, 0, 0, 0);
    HAL_DMA_Channel_Start_IT(hdwuart->DMAC_Instance, &cfg, DWUART_Recevie_DMA_Callback, (uint32_t)hdwuart);
    return HAL_OK;
}

uint32_t HAL_DWUART_Receive_DMA_Abort(DWUART_HandleTypeDef *hdwuart)
{
    return HAL_DMA_Channel_Abort(hdwuart->DMAC_Instance, hdwuart->Rx_Env.DMA.DMA_Channel);
}
