#include <stddef.h>
#include "ssi_msp.h"
#include "lsdmac.h"
#include "ssi_misc.h"
#include "field_manipulate.h"

void ssi_ctrlr0_set(SSI_HandleTypeDef *hssi,uint8_t frame_format,uint8_t mode);
void ssi_tx_done(SSI_HandleTypeDef *hssi,void (*tx_callback)(SSI_HandleTypeDef *hssi));
void ssi_rx_done(SSI_HandleTypeDef *hssi,void (*rx_callback)(SSI_HandleTypeDef *hssi),void (*txrx_callback)(SSI_HandleTypeDef *hssi));

__attribute__((weak)) void HAL_SSI_TxDMACpltCallback(SSI_HandleTypeDef *hssi){}
__attribute__((weak)) void HAL_SSI_RxDMACpltCallback(SSI_HandleTypeDef *hssi){}
__attribute__((weak)) void HAL_SSI_TxRxDMACpltCallback(SSI_HandleTypeDef *hssi){}

void ssi_tx_empty_dma_isr(SSI_HandleTypeDef *hssi)
{
    ssi_tx_done(hssi,HAL_SSI_TxDMACpltCallback);
}

static void SSI_Transmit_DMA_Callback(void *hdma,uint32_t param,uint8_t DMA_channel,bool alt)
{
    SSI_HandleTypeDef *hssi = (SSI_HandleTypeDef *)param;
    hssi->REG->TXFTLR = 0;
    REG_FIELD_WR(hssi->REG->IMR, SSI_TXEIM,1);
}

static void SSI_Receive_DMA_Callback(void *hdma,uint32_t param,uint8_t DMA_channel,bool alt)
{
    SSI_HandleTypeDef *hssi = (SSI_HandleTypeDef *)param;
    ssi_rx_done(hssi,HAL_SSI_RxDMACpltCallback,HAL_SSI_TxRxDMACpltCallback);
}

static void ssi_dma_config(SSI_HandleTypeDef *hssi,void *TX_Data,void *RX_Data,uint16_t Count)
{
    hssi->REG->IMR = FIELD_BUILD(SSI_MSTIM,1) | FIELD_BUILD(SSI_RXFIM,0)|
        FIELD_BUILD(SSI_RXOIM,1) | FIELD_BUILD(SSI_RXUIM,1) | FIELD_BUILD(SSI_TXOIM,1) |
        FIELD_BUILD(SSI_TXEIM,0);
    hssi->REG->SSIENR = SSI_Enabled;
    uint32_t tx_data_end_ptr = (uint32_t)TX_Data;
    uint32_t rx_data_end_ptr = (uint32_t)RX_Data;
    uint8_t data_size;
    uint8_t inc;
    if(hssi->Init.ctrl.data_frame_size <= DFS_32_8_bits)
    {
        tx_data_end_ptr += Count - 1;
        rx_data_end_ptr += Count - 1;
        data_size = DMA_SIZE_BYTE;
        inc = DMA_INC_BYTE;
    }else if(hssi->Init.ctrl.data_frame_size <= DFS_32_16_bits)
    {
        tx_data_end_ptr += (Count - 1) * 2;
        rx_data_end_ptr += (Count - 1) * 2;
        data_size = DMA_SIZE_HALFWORD;
        inc = DMA_INC_HALFWORD;
    }else
    {
        tx_data_end_ptr += (Count - 1)* 4;
        rx_data_end_ptr += (Count - 1)* 4;
        data_size = DMA_SIZE_WORD;
        inc = DMA_INC_WORD;
    }
    struct DMA_Channel_Config prim;
    if(TX_Data)
    {
        prim.src_data_end_ptr = tx_data_end_ptr;
        prim.dst_data_end_ptr = (uint32_t)&hssi->REG->DR;
        prim.ctrl_data.cycle_ctrl = DMA_Cycle_Basic,
        prim.ctrl_data.next_useburst = 0;
        prim.ctrl_data.n_minus_1 = Count - 1;
        prim.ctrl_data.R_power = 0;
        prim.ctrl_data.src_prot_ctrl = 0;
        prim.ctrl_data.dst_prot_ctrl = 0;
        prim.ctrl_data.src_size = data_size;
        prim.ctrl_data.src_inc = inc;
        prim.ctrl_data.dst_size = data_size;
        prim.ctrl_data.dst_inc = DMA_INC_NONE;
        prim.dummy = (uint32_t)SSI_Transmit_DMA_Callback;
        HAL_DMA_Channel_Config_Set(hssi->DMAC_Instance,hssi->Tx_Env.DMA.DMA_Channel,false,&prim);
        HAL_DMA_Channel_Start_IT(hssi->DMAC_Instance,hssi->Tx_Env.DMA.DMA_Channel,HAL_SSI_TX_DMA_Handshake_Get(hssi),(uint32_t)hssi);
    }
    if(RX_Data)
    {
        prim.src_data_end_ptr = (uint32_t)&hssi->REG->DR;
        prim.dst_data_end_ptr = rx_data_end_ptr;
        prim.ctrl_data.cycle_ctrl = DMA_Cycle_Basic;
        prim.ctrl_data.next_useburst = 0;
        prim.ctrl_data.n_minus_1 = Count - 1;
        prim.ctrl_data.R_power = 0;
        prim.ctrl_data.src_prot_ctrl = 0;
        prim.ctrl_data.dst_prot_ctrl = 0;
        prim.ctrl_data.src_size = data_size;
        prim.ctrl_data.src_inc = DMA_INC_NONE;
        prim.ctrl_data.dst_size = data_size;
        prim.ctrl_data.dst_inc = inc;
        prim.dummy = (uint32_t)SSI_Receive_DMA_Callback;
        HAL_DMA_Channel_Config_Set(hssi->DMAC_Instance,hssi->Rx_Env.DMA.DMA_Channel,false,&prim);
        HAL_DMA_Channel_Start_IT(hssi->DMAC_Instance,hssi->Rx_Env.DMA.DMA_Channel,HAL_SSI_RX_DMA_Handshake_Get(hssi),(uint32_t)hssi);
    }
    hssi->REG->SER = hssi->Hardware_CS_Mask ? hssi->Hardware_CS_Mask : 0xff;
}

HAL_StatusTypeDef HAL_SSI_Transmit_DMA(SSI_HandleTypeDef *hssi,void *Data,uint16_t Count)
{
    ssi_ctrlr0_set(hssi,Motorola_SPI,Transmit_Only);
    hssi->REG->DMACR = SSI_TDMAE_MASK;
    hssi->REG->DMATDLR = 2;
    ssi_dma_config(hssi,Data,NULL,Count);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_SSI_Receive_DMA(SSI_HandleTypeDef *hssi,void *Data,uint16_t Count)
{
    ssi_ctrlr0_set(hssi,Motorola_SPI,Receive_Only);
    hssi->REG->CTRLR1 = Count - 1;
    hssi->REG->DMACR = SSI_RDMAE_MASK;
    hssi->REG->DMARDLR = 1;
    ssi_dma_config(hssi,NULL,Data,Count);
    hssi->REG->DR = 0;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_SSI_TransmitReceive_DMA(SSI_HandleTypeDef *hssi,void *TX_Data,void *RX_Data,uint16_t Count)
{
    ssi_ctrlr0_set(hssi,Motorola_SPI,Transmit_and_Receive);
    hssi->REG->DMACR = SSI_TDMAE_MASK|SSI_RDMAE_MASK;
    hssi->REG->DMATDLR = 2;
    hssi->REG->DMARDLR = 1;
    ssi_dma_config(hssi,TX_Data,RX_Data,Count);
    return HAL_OK;
}

