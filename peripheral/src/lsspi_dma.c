#include <stddef.h>
#include "spi_msp.h"
#include "lsdmac.h"
#include "field_manipulate.h"


__attribute__((weak)) void HAL_SPI_TxDMACpltCallback(SPI_HandleTypeDef *hspi){}
__attribute__((weak)) void HAL_SPI_RxDMACpltCallback(SPI_HandleTypeDef *hspi){}
__attribute__((weak)) void HAL_SPI_TxRxDMACpltCallback(SPI_HandleTypeDef *hspi){}

static void spi_enable(SPI_HandleTypeDef *hspi)
{
    /* Enable SPI peripheral */
    __HAL_SPI_ENABLE(hspi);    
}
void spi_tx_empty_dma_isr(SPI_HandleTypeDef *hspi)
{
    REG_FIELD_WR(hspi->Instance->IER, SPI_IER_TXEIE,0);
    CLEAR_BIT(hspi->Instance->CR2, SPI_CR2_TXDMAEN_MASK);
    if(hspi->Rx_Env.DMA.DMA_EN != true)
    {
        while(REG_FIELD_RD(hspi->Instance->SR,SPI_SR_BSY) == SPI_SR_BSY_MASK);
        HAL_SPI_TxDMACpltCallback(hspi);
    }
}

static void SPI_Transmit_DMA_Callback(void *hdma,uint32_t param,uint8_t DMA_channel,bool alt)
{
    SPI_HandleTypeDef *hspi = (SPI_HandleTypeDef *)param;
    REG_FIELD_WR(hspi->Instance->IER, SPI_IER_TXEIE,1);
}

static void SPI_Receive_DMA_Callback(void *hdma,uint32_t param,uint8_t DMA_channel,bool alt)
{
    SPI_HandleTypeDef *hspi = (SPI_HandleTypeDef *)param;
    CLEAR_BIT(hspi->Instance->CR2, SPI_CR2_RXDMAEN_MASK);

    if(hspi->Tx_Env.DMA.DMA_EN == true)
    {
        HAL_SPI_TxRxDMACpltCallback(hspi);
        
    }
    else
    {
        HAL_SPI_RxDMACpltCallback(hspi);
    }
}

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
    hspi->Tx_Env.DMA.DMA_EN = false;
    hspi->Rx_Env.DMA.DMA_EN = false;
    struct DMA_Channel_Config prim;
    if(TX_Data)
    {
        hspi->Tx_Env.DMA.DMA_EN = true;

        prim.src_data_end_ptr = tx_data_end_ptr;
        prim.dst_data_end_ptr = (uint32_t)&hspi->Instance->DR;
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
        prim.dummy = (uint32_t)SPI_Transmit_DMA_Callback;
        HAL_DMA_Channel_Config_Set(hspi->DMAC_Instance,hspi->Tx_Env.DMA.DMA_Channel,false,&prim);
        HAL_DMA_Channel_Start_IT(hspi->DMAC_Instance,hspi->Tx_Env.DMA.DMA_Channel,CH_SPI2_TX,(uint32_t)hspi);
    }
    if(RX_Data)
    {
        hspi->Rx_Env.DMA.DMA_EN = true;

        prim.src_data_end_ptr = (uint32_t)&hspi->Instance->DR;
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
        prim.dummy = (uint32_t)SPI_Receive_DMA_Callback;
        HAL_DMA_Channel_Config_Set(hspi->DMAC_Instance,hspi->Rx_Env.DMA.DMA_Channel,false,&prim);
        HAL_DMA_Channel_Start_IT(hspi->DMAC_Instance,hspi->Rx_Env.DMA.DMA_Channel,CH_SPI2_RX,(uint32_t)hspi);
    }
}

HAL_StatusTypeDef HAL_SPI_Transmit_DMA(SPI_HandleTypeDef *hspi,void *Data,uint16_t Count)
{
    spi_dma_config(hspi,Data,NULL,Count);
    MODIFY_REG(hspi->Instance->CR2, SPI_CR2_TXDMAEN_MASK, SPI_CR2_TXDMAEN_MASK);
    spi_enable(hspi);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_SPI_Receive_DMA(SPI_HandleTypeDef *hspi,void *Data,uint16_t Count)
{
    spi_dma_config(hspi,NULL,Data,Count);
    //MODIFY_REG(hspi->Instance->CR2,SPI_CR2_RXFTH_MASK,7);
    MODIFY_REG(hspi->Instance->CR2, SPI_CR2_RXDMAEN_MASK, SPI_CR2_RXDMAEN_MASK);
    spi_enable(hspi);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_SPI_TransmitReceive_DMA(SPI_HandleTypeDef *hspi,void *TX_Data,void *RX_Data,uint16_t Count)
{
    spi_dma_config(hspi,TX_Data,RX_Data,Count);
    MODIFY_REG(hspi->Instance->CR2, SPI_CR2_TXDMAEN_MASK|SPI_CR2_RXDMAEN_MASK, SPI_CR2_TXDMAEN_MASK|SPI_CR2_RXDMAEN_MASK);
    spi_enable(hspi);
    return HAL_OK;
}

