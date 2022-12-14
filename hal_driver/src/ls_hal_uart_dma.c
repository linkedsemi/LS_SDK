#include <stddef.h>
#include "sdk_config.h"
#include "ls_hal_uart.h"
#include "ls_msp_uart.h"
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

#if DMACV2
#include "ls_hal_dmacv2.h"
static void UART_Transmit_DMA_Callback(DMA_Controller_HandleTypeDef *hdma,uint32_t param,uint8_t DMA_channel)
{
    UART_HandleTypeDef *huart = (UART_HandleTypeDef *)param;
    huart->UARTX->IER = UART_IT_TXS;
}

static void UART_Recevie_DMA_Callback(DMA_Controller_HandleTypeDef *hdma,uint32_t param,uint8_t DMA_channel)
{
    HAL_UART_DMA_RxCpltCallback((UART_HandleTypeDef *)param);
}

HAL_StatusTypeDef HAL_UART_Transmit_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
    huart->UARTX->ICR = UART_IT_TC | UART_IT_TXS;
    LL_UART_SetTXTL(huart->UARTX, FIFO_TRABSMIT_TRIGGER_0BYTE);
    REG_FIELD_WR(huart->UARTX->MCR, UART_MCR_DMAEN, 1);
    struct DMA_Channel_Config prim = {
        .ctrl.channel_en = 1,
        .ctrl.circular_mode_en = 0,
        .ctrl.peripheral_flow_ctrl = 0,
        .ctrl.direct_mode_en = 0,
        .ctrl.dma_mode_sel = Mem2Peri,
        .ctrl.channel_priority = 0,
        .ctrl.peripheral_handshake = HAL_UART_TX_DMA_Handshake_Get(huart),
        .ctrl.src_inc = 1,
        .ctrl.src_width = DMA_SIZE_BYTE,
        .ctrl.src_burst = 0,
        .ctrl.src_inc_offset = 0,
        .ctrl.rsvd0 = 0,
        .ctrl.dst_inc = 0,
        .ctrl.dst_witdh = DMA_SIZE_BYTE,
        .ctrl.dst_burst = 0,
        .ctrl.dst_inc_offset = 0,
        .ctrl.rsvd1 = 0,
        .src_addr = (uint32_t)pData,
        .dst_addr = (uint32_t)&huart->UARTX->TBR,
        .byte_count = Size,
        .dummy = 0,
    };
    HAL_DMA_Channel_Start_IT(huart->DMAC_Instance, huart->Tx_Env.DMA.DMA_Channel, &prim, UART_Transmit_DMA_Callback, (uint32_t)huart);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_UART_Receive_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
    huart->UARTX->ICR = UART_IT_TC | UART_IT_TXS;
    LL_UART_SetRXTL(huart->UARTX, FIFO_RECEIVE_TRIGGER_14BYTE);
    REG_FIELD_WR(huart->UARTX->MCR, UART_MCR_DMAEN, 1);
    struct DMA_Channel_Config prim = {
        .ctrl.channel_en = 1,
        .ctrl.circular_mode_en = 0,
        .ctrl.peripheral_flow_ctrl = 0,
        .ctrl.direct_mode_en = 0,
        .ctrl.dma_mode_sel = Peri2Mem,
        .ctrl.channel_priority = 0,
        .ctrl.peripheral_handshake = HAL_UART_RX_DMA_Handshake_Get(huart),
        .ctrl.src_inc = 0,
        .ctrl.src_width = DMA_SIZE_BYTE,
        .ctrl.src_burst = 0,
        .ctrl.src_inc_offset = 0,
        .ctrl.rsvd0 = 0,
        .ctrl.dst_inc = 1,
        .ctrl.dst_witdh = DMA_SIZE_BYTE,
        .ctrl.dst_burst = 0,
        .ctrl.dst_inc_offset = 0,
        .ctrl.rsvd1 = 0,
        .src_addr = (uint32_t)&huart->UARTX->RBR,
        .dst_addr = (uint32_t)pData,
        .byte_count = Size,
        .dummy = 0,
    };
    HAL_DMA_Channel_Start_IT(huart->DMAC_Instance, huart->Rx_Env.DMA.DMA_Channel, &prim, UART_Recevie_DMA_Callback, (uint32_t)huart);
    return HAL_OK;
}

#else
#include "ls_hal_dmac.h"
static void UART_Transmit_DMA_Callback(void *hdma,uint32_t param,uint8_t DMA_channel,bool alt)
{
    UART_HandleTypeDef *huart = (UART_HandleTypeDef *)param;
    huart->UARTX->IER = UART_IT_TXS;
}

static void UART_Recevie_DMA_Callback(void *hdma,uint32_t param,uint8_t DMA_channel,bool alt)
{
    HAL_UART_DMA_RxCpltCallback((UART_HandleTypeDef *)param);
}

HAL_StatusTypeDef HAL_UART_Transmit_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
    huart->UARTX->ICR = UART_IT_TC| UART_IT_TXS;
    LL_UART_SetTXTL(huart->UARTX,FIFO_TRABSMIT_TRIGGER_0BYTE);
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

HAL_StatusTypeDef HAL_UART_Receive_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
    LL_UART_SetRXTL(huart->UARTX,FIFO_RECEIVE_TRIGGER_14BYTE);
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
#endif

void UART_Transmit_IT_DMA(UART_HandleTypeDef *huart)
{
    huart->UARTX->IDR = UART_IT_TXS;
    HAL_UART_DMA_TxCpltCallback(huart);
}
