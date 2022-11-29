#include <stddef.h>
#include "ls_msp_spi.h"
#include "field_manipulate.h"
#include "ls_hal_spi.h"

__attribute__((weak)) void HAL_SPI_DMACpltCallback(SPI_HandleTypeDef *hspi){}

static void SPI_Transmit_DMA_Callback(void *hdma,uint32_t param,uint8_t DMA_channel,bool alt)
{
    SPI_HandleTypeDef *hspi = (SPI_HandleTypeDef *)param;
    CLEAR_BIT(hspi->Instance->CR2, SPI_CR2_TXDMAEN_MASK);
}

static void SPI_Receive_DMA_Callback(void *hdma,uint32_t param,uint8_t DMA_channel,bool alt)
{
    SPI_HandleTypeDef *hspi = (SPI_HandleTypeDef *)param;
    CLEAR_BIT(hspi->Instance->CR2, SPI_CR2_RXDMAEN_MASK);
    while (REG_FIELD_RD(hspi->Instance->SR,SPI_SR_BSY) == SPI_SR_BSY_MASK);
    CLEAR_BIT(hspi->Instance->CR1, SPI_CR1_SPE_MASK);
    HAL_SPI_DMACpltCallback(hspi);
}

#if  DMACV2
#include "ls_hal_dmacv2.h"
static void spi_dma_config(SPI_HandleTypeDef *hspi,void *TX_Data,void *RX_Data,uint16_t Count)
{
    uint8_t data_width;
    uint8_t *pTxData, *pRxData; 
    pTxData = TX_Data? TX_Data: &hspi->Tx_Env.DMA.dummy;
    pRxData = RX_Data? RX_Data: &hspi->Rx_Env.DMA.dummy;

    if(hspi->Init.DataSize == SPI_DATASIZE_16BIT)
    {
        data_width = DMA_SIZE_HALFWORD;
        Count *= 2;
    }
    else
    {
        data_width = DMA_SIZE_BYTE;
    }

    struct DMA_Channel_Config cfg;
    /* Tx parameter initialize*/
    cfg.ctrl.channel_en = 1;
    cfg.ctrl.circular_mode_en = 0;
    cfg.ctrl.peripheral_flow_ctrl = 0;
    cfg.ctrl.direct_mode_en = 0;
    cfg.ctrl.dma_mode_sel = Mem2Peri;
    cfg.ctrl.channel_priority = 0;
    cfg.ctrl.peripheral_handshake = HAL_SPI_TX_DMA_Handshake_Get(hspi);
    cfg.ctrl.src_inc = TX_Data? 1: 0;
    cfg.ctrl.src_width = data_width;
    cfg.ctrl.src_burst = 0;
    cfg.ctrl.src_inc_offset = 0;
    cfg.ctrl.rsvd0 = 0;
    cfg.ctrl.dst_inc = 0;
    cfg.ctrl.dst_witdh = data_width;
    cfg.ctrl.dst_burst = 0;
    cfg.ctrl.dst_inc_offset = 0;
    cfg.ctrl.rsvd1 = 0;
    cfg.src_addr = (uint32_t)pTxData;
    cfg.dst_addr = (uint32_t)&hspi->Instance->DR;
    cfg.byte_count = Count;
    cfg.dummy = 0;
    HAL_DMA_Channel_Start_IT(hspi->DMAC_Instance,hspi->Tx_Env.DMA.DMA_Channel,&cfg,(void *)SPI_Transmit_DMA_Callback,(uint32_t)hspi);

    /* Rx parameter initialize*/
    cfg.ctrl.dma_mode_sel = Peri2Mem;
    cfg.ctrl.peripheral_handshake = HAL_SPI_RX_DMA_Handshake_Get(hspi);
    cfg.ctrl.src_inc = 0;
    cfg.ctrl.dst_inc = RX_Data? 1: 0;
    cfg.src_addr = (uint32_t)&hspi->Instance->DR;
    cfg.dst_addr = (uint32_t)pRxData;
    HAL_DMA_Channel_Start_IT(hspi->DMAC_Instance,hspi->Rx_Env.DMA.DMA_Channel,&cfg,(void *)SPI_Receive_DMA_Callback,(uint32_t)hspi);

    MODIFY_REG(hspi->Instance->CR2, SPI_CR2_TXDMAEN_MASK|SPI_CR2_RXDMAEN_MASK, SPI_CR2_TXDMAEN_MASK|SPI_CR2_RXDMAEN_MASK);
    SET_BIT(hspi->Instance->CR1, SPI_CR1_SPE_MASK);
}
#else
#include "ls_hal_dmac.h"
static void spi_dma_config(SPI_HandleTypeDef *hspi,void *TX_Data,void *RX_Data,uint16_t Count)
{
    uint32_t tx_data_end_ptr = (uint32_t)TX_Data;
    uint32_t rx_data_end_ptr = (uint32_t)RX_Data;
    uint8_t data_size;
    uint8_t inc;

    if(hspi->Init.DataSize == SPI_DATASIZE_16BIT)
    {
        tx_data_end_ptr += (Count - 1) * 2;
        rx_data_end_ptr += (Count - 1) * 2;
        data_size = DMA_SIZE_HALFWORD;
        inc = DMA_INC_HALFWORD;
    }
    else
    {
        tx_data_end_ptr += Count - 1;
        rx_data_end_ptr += Count - 1;
        data_size = DMA_SIZE_BYTE;
        inc = DMA_INC_BYTE;
    }
   
    struct DMA_Channel_Config prim;
    /* Tx parameter initialize*/
    prim.src_data_end_ptr = TX_Data? tx_data_end_ptr: (uint32_t)&hspi->Tx_Env.DMA.dummy;
    prim.dst_data_end_ptr = (uint32_t)&hspi->Instance->DR;
    prim.ctrl_data.cycle_ctrl = DMA_Cycle_Basic,
    prim.ctrl_data.next_useburst = 0;
    prim.ctrl_data.n_minus_1 = Count - 1;
    prim.ctrl_data.R_power = 0;
    prim.ctrl_data.src_prot_ctrl = 0;
    prim.ctrl_data.dst_prot_ctrl = 0;
    prim.ctrl_data.src_size = data_size;
    prim.ctrl_data.src_inc = TX_Data? inc: DMA_INC_NONE;
    prim.ctrl_data.dst_size = data_size;
    prim.ctrl_data.dst_inc = DMA_INC_NONE;
    prim.dummy = (uint32_t)SPI_Transmit_DMA_Callback;
    HAL_DMA_Channel_Config_Set(hspi->DMAC_Instance,hspi->Tx_Env.DMA.DMA_Channel,false,&prim);
    HAL_DMA_Channel_Start_IT(hspi->DMAC_Instance,hspi->Tx_Env.DMA.DMA_Channel,CH_SPI2_TX,(uint32_t)hspi);

    /* Rx parameter initialize*/
    prim.src_data_end_ptr = (uint32_t)&hspi->Instance->DR;
    prim.dst_data_end_ptr = RX_Data? rx_data_end_ptr: (uint32_t)&hspi->Rx_Env.DMA.dummy;
    prim.ctrl_data.src_inc = DMA_INC_NONE;
    prim.ctrl_data.dst_inc = RX_Data? inc: DMA_INC_NONE;
    prim.dummy = (uint32_t)SPI_Receive_DMA_Callback;
    HAL_DMA_Channel_Config_Set(hspi->DMAC_Instance,hspi->Rx_Env.DMA.DMA_Channel,false,&prim);
    HAL_DMA_Channel_Start_IT(hspi->DMAC_Instance,hspi->Rx_Env.DMA.DMA_Channel,CH_SPI2_RX,(uint32_t)hspi);

    MODIFY_REG(hspi->Instance->CR2, SPI_CR2_TXDMAEN_MASK|SPI_CR2_RXDMAEN_MASK, SPI_CR2_TXDMAEN_MASK|SPI_CR2_RXDMAEN_MASK);
    SET_BIT(hspi->Instance->CR1, SPI_CR1_SPE_MASK);
}
#endif

HAL_StatusTypeDef HAL_SPI_Transmit_DMA(SPI_HandleTypeDef *hspi,void *Data,uint16_t Count)
{
    spi_dma_config(hspi,Data,NULL,Count);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_SPI_Receive_DMA(SPI_HandleTypeDef *hspi,void *Data,uint16_t Count)
{
    spi_dma_config(hspi,NULL,Data,Count);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_SPI_TransmitReceive_DMA(SPI_HandleTypeDef *hspi,void *TX_Data,void *RX_Data,uint16_t Count)
{
    spi_dma_config(hspi,TX_Data,RX_Data,Count);
    return HAL_OK;
}