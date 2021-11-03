#include <stddef.h>
#include "lsuart.h"
#include "lsdmac.h"
#include "uart_msp.h"
#include "uart_misc.h"
#include "field_manipulate.h"


__attribute__((weak)) void HAL_UART_DMA_TxCpltCallback(UART_HandleTypeDef *huart)
{
  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_UART_DMA_TxCpltCallback could be implemented in the user file
   */
}

__attribute__((weak)) void HAL_UART_DMA_RxCpltCallback(UART_HandleTypeDef *huart)
{
  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_UART_DMA_RxCpltCallback could be implemented in the user file
   */
}

static void UART_Transmit_DMA_Callback(void *hdma,uint32_t param,uint8_t DMA_channel,bool alt)
{
    UART_HandleTypeDef *huart = (UART_HandleTypeDef *)param;
    huart->UARTX->IER = UART_IT_TXS;
}

HAL_StatusTypeDef HAL_UART_Transmit_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
    huart->UARTX->ICR = UART_IT_TC| UART_IT_TXS;
    REG_FIELD_WR(huart->UARTX->FCR,UART_FCR_TXTL,UART_FIFO_TL_0);
    REG_FIELD_WR(huart->UARTX->MCR,UART_MCR_DMAEN,1);
    struct DMA_Channel_Config prim = {
        .src_data_end_ptr = (uint32_t)&pData[Size-1],
        .dst_data_end_ptr = (uint32_t)&huart->UARTX->TBR,
        .ctrl_data = {
            .cycle_ctrl = DMA_Cycle_Basic,
            .next_useburst = 0,
            .n_minus_1 = Size - 1,
            .R_power = 0,
            .src_prot_ctrl = 0,
            .dst_prot_ctrl = 0,
            .src_size = 0,
            .src_inc = 0,
            .dst_size = 0,
            .dst_inc = 3,
        },
        .dummy = (uint32_t)UART_Transmit_DMA_Callback,
    };
    HAL_DMA_Channel_Config_Set(huart->DMAC_Instance,huart->Tx_Env.DMA.DMA_Channel,false,&prim);
    HAL_DMA_Channel_Start_IT(huart->DMAC_Instance,huart->Tx_Env.DMA.DMA_Channel,HAL_UART_TX_DMA_Handshake_Get(huart),(uint32_t)huart);
    return HAL_OK;
}

static void UART_Recevie_DMA_Callback(void *hdma,uint32_t param,uint8_t DMA_channel,bool alt)
{
    HAL_UART_DMA_RxCpltCallback((UART_HandleTypeDef *)param);
}

HAL_StatusTypeDef HAL_UART_Receive_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
    REG_FIELD_WR(huart->UARTX->FCR,UART_FCR_RXTL,UART_FIFO_RL_14);
    REG_FIELD_WR(huart->UARTX->MCR,UART_MCR_DMAEN,1);
    struct DMA_Channel_Config prim = {
        .src_data_end_ptr = (uint32_t)&huart->UARTX->RBR,
        .dst_data_end_ptr = (uint32_t)&pData[Size-1],
        .ctrl_data = {
            .cycle_ctrl = DMA_Cycle_Basic,
            .next_useburst = 0,
            .n_minus_1 = Size - 1,
            .R_power = 0,
            .src_prot_ctrl = 0,
            .dst_prot_ctrl = 0,
            .src_size = 0,
            .src_inc = 3,
            .dst_size = 0,
            .dst_inc = 0,
        },
        .dummy = (uint32_t)UART_Recevie_DMA_Callback,
    };
    HAL_DMA_Channel_Config_Set(huart->DMAC_Instance,huart->Rx_Env.DMA.DMA_Channel,false,&prim);
    HAL_DMA_Channel_Start_IT(huart->DMAC_Instance,huart->Rx_Env.DMA.DMA_Channel,HAL_UART_RX_DMA_Handshake_Get(huart),(uint32_t)huart);
    return HAL_OK;
}

void UART_Transmit_IT_DMA(UART_HandleTypeDef *huart)
{
    huart->UARTX->IDR = UART_IT_TXS;
    huart->UARTX->IER = UART_IT_TC;
}

void UART_EndTransmit_IT_DMA(UART_HandleTypeDef *huart)
{
    huart->UARTX->IDR = UART_IT_TC;
    HAL_UART_DMA_TxCpltCallback(huart);
}
