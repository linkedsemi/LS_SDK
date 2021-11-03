#include "ssi_msp.h"
#include "field_manipulate.h"
#include "log.h"
#include "ls_dbg.h"
#define SSI_TX_FIFO_DEPTH 4
#define SSI_RX_FIFO_DEPTH 4
HAL_StatusTypeDef HAL_SSI_Init(SSI_HandleTypeDef *hssi)
{
    HAL_SSI_MSP_Init(hssi);
    HAL_SSI_MSP_Busy_Set(hssi);
    hssi->REG->BAUDR = hssi->Init.clk_div;
    hssi->REG->RXSAMPLE_DLY = hssi->Init.rxsample_dly;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_SSI_Deinit(SSI_HandleTypeDef *hssi)
{
    HAL_SSI_MSP_DeInit(hssi);
    HAL_SSI_MSP_Idle_Set(hssi);
    return HAL_OK;
}

void ssi_ctrlr0_set(SSI_HandleTypeDef *hssi,uint8_t frame_format,uint8_t mode)
{
    void *ctrl = &hssi->Init.ctrl;
    uint32_t ctrlr0 = *(uint32_t *)ctrl;
    MODIFY_REG(ctrlr0,SSI_FRF_MASK|SSI_TMOD_MASK,frame_format<<SSI_FRF_POS|mode<<SSI_TMOD_POS);
    hssi->REG->CTRLR0 = ctrlr0;
}

static void ssi_config_it(SSI_HandleTypeDef *hssi,bool tx,bool rx)
{
    hssi->REG->DMACR = 0;
    hssi->REG->TXFTLR = SSI_TX_FIFO_DEPTH/2;
    //hssi->REG->RXFTLR = hssi->Rx_Env.Interrupt.Count > SSI_RX_FIFO_DEPTH ? 0 : hssi->Rx_Env.Interrupt.Count - 1;
    hssi->REG->RXFTLR = 0; //rx full -> rx overflow issue workaround
    hssi->REG->IMR = FIELD_BUILD(SSI_MSTIM,1) | FIELD_BUILD(SSI_RXFIM,rx)|
        FIELD_BUILD(SSI_RXOIM,1) | FIELD_BUILD(SSI_RXUIM,1) | FIELD_BUILD(SSI_TXOIM,1) |
        FIELD_BUILD(SSI_TXEIM,tx);
    hssi->REG->SSIENR = SSI_Enabled;
    hssi->REG->SER = hssi->Hardware_CS_Mask ? hssi->Hardware_CS_Mask : 0xff;
}

HAL_StatusTypeDef HAL_SSI_Transmit_IT(SSI_HandleTypeDef *hssi,void *Data,uint16_t Count)
{
    hssi->Tx_Env.Interrupt.Data = Data;
    hssi->Tx_Env.Interrupt.Count = Count;
    ssi_ctrlr0_set(hssi,Motorola_SPI,Transmit_Only);
    ssi_config_it(hssi,true,false); 
    return HAL_OK;
}

__attribute__((weak)) void HAL_SSI_TxCpltCallback(SSI_HandleTypeDef *hssi){}

HAL_StatusTypeDef HAL_SSI_Receive_IT(SSI_HandleTypeDef *hssi,void *Data,uint16_t Count)
{
    hssi->Rx_Env.Interrupt.Data = Data;
    hssi->Rx_Env.Interrupt.Count = Count;
    ssi_ctrlr0_set(hssi,Motorola_SPI,Receive_Only);
    hssi->REG->CTRLR1 = Count - 1;
    ssi_config_it(hssi,false,true);
    hssi->REG->DR = 0;
    return HAL_OK;
}

__attribute__((weak)) void HAL_SSI_RxCpltCallback(SSI_HandleTypeDef *hssi){}

HAL_StatusTypeDef HAL_SSI_TransmitReceive_IT(SSI_HandleTypeDef *hssi,void *TX_Data,void *RX_Data,uint16_t Count)
{
    hssi->Tx_Env.Interrupt.Data = TX_Data;
    hssi->Rx_Env.Interrupt.Data = RX_Data;
    hssi->Tx_Env.Interrupt.Count = Count;
    hssi->Rx_Env.Interrupt.Count = Count;
    ssi_ctrlr0_set(hssi,Motorola_SPI,Transmit_and_Receive);
    ssi_config_it(hssi,true,true);
    return HAL_OK;
}

void ssi_rx_done(SSI_HandleTypeDef *hssi,void (*rx_callback)(SSI_HandleTypeDef *hssi),void (*txrx_callback)(SSI_HandleTypeDef *hssi))
{
    hssi->REG->SSIENR = SSI_Disabled;
    hssi->REG->SER = 0;
    if(REG_FIELD_RD(hssi->REG->CTRLR0,SSI_TMOD) == Receive_Only)
    {
        rx_callback(hssi);
    }else if(REG_FIELD_RD(hssi->REG->CTRLR0,SSI_TMOD) == Transmit_and_Receive)
    {
        txrx_callback(hssi);
    }
}

__attribute__((weak)) void HAL_SSI_TxRxCpltCallback(SSI_HandleTypeDef *hssi){}

static void ssi_rx_full_isr(SSI_HandleTypeDef *hssi)
{
    do
    {
        if(hssi->Init.ctrl.data_frame_size <= DFS_32_8_bits)
        {
            *(uint8_t *)hssi->Rx_Env.Interrupt.Data = (uint8_t)hssi->REG->DR;
            hssi->Rx_Env.Interrupt.Data += 1;
        }else if(hssi->Init.ctrl.data_frame_size <= DFS_32_16_bits)
        {
            *(uint16_t *)hssi->Rx_Env.Interrupt.Data = (uint16_t)hssi->REG->DR;
            hssi->Rx_Env.Interrupt.Data += 2;
        }else
        {
            *(uint32_t *)hssi->Rx_Env.Interrupt.Data = (uint32_t)hssi->REG->DR;
            hssi->Rx_Env.Interrupt.Data += 4;
        }
        --hssi->Rx_Env.Interrupt.Count;
    }while(REG_FIELD_RD(hssi->REG->SR,SSI_RFNE));
    if(hssi->Rx_Env.Interrupt.Count == 0)
    {
        ssi_rx_done(hssi,HAL_SSI_RxCpltCallback,HAL_SSI_TxRxCpltCallback);
    }
}

void ssi_tx_done(SSI_HandleTypeDef *hssi,void (*tx_callback)(SSI_HandleTypeDef *hssi))
{
    REG_FIELD_WR(hssi->REG->IMR,SSI_TXEIM,0);
    if(REG_FIELD_RD(hssi->REG->CTRLR0,SSI_TMOD) == Transmit_Only)
    {
        while(REG_FIELD_RD(hssi->REG->SR,SSI_BUSY) == SSI_Busy);
        hssi->REG->SSIENR = SSI_Disabled;
        hssi->REG->SER = 0;
        tx_callback(hssi);
    }
}

static void ssi_tx_empty_isr(SSI_HandleTypeDef *hssi)
{
    if(hssi->Tx_Env.Interrupt.Count)
    {
        do{
            if(hssi->Init.ctrl.data_frame_size <= DFS_32_8_bits)
            {
                hssi->REG->DR = *(uint8_t *)hssi->Tx_Env.Interrupt.Data;
                hssi->Tx_Env.Interrupt.Data += 1;
            }else if(hssi->Init.ctrl.data_frame_size <= DFS_32_16_bits)
            {
                hssi->REG->DR = *(uint16_t *)hssi->Tx_Env.Interrupt.Data;
                hssi->Tx_Env.Interrupt.Data += 2;
            }else
            {
                hssi->REG->DR = *(uint32_t *)hssi->Tx_Env.Interrupt.Data;
                hssi->Tx_Env.Interrupt.Data += 4;
            }
            --hssi->Tx_Env.Interrupt.Count;
        }while(REG_FIELD_RD(hssi->REG->SR,SSI_TFNF)&&hssi->Tx_Env.Interrupt.Count);
    }else{
        if(hssi->REG->TXFLR)
        {
            hssi->REG->TXFTLR = 0;
        }else
        {
            ssi_tx_done(hssi,HAL_SSI_TxCpltCallback);
        }
    }
}

__attribute__((weak)) void ssi_tx_empty_dma_isr(SSI_HandleTypeDef *hssi){}

void HAL_SSI_IRQHandler(SSI_HandleTypeDef *hssi)
{
    while(1)
    {
        uint8_t irq = hssi->REG->ISR;
        if(irq == 0) break;
        if(irq & SSI_MSTIS_MASK)
        {
            LOG_W("ssi0x%x,multi_master contention",hssi->REG);
            hssi->REG->MSTICR;
            LS_ASSERT(0);
        }
        if(irq & SSI_RXFIS_MASK)
        {
            ssi_rx_full_isr(hssi);
        }
        if(irq & SSI_RXOIS_MASK)
        {
            LOG_W("ssi0x%x,Receive FIFO Overflow",hssi->REG);
            hssi->REG->RXOICR;
            LS_ASSERT(0);
        }
        if(irq & SSI_RXUIS_MASK)
        {
            LOG_W("ssi0x%x,Receive FIFO Underflow",hssi->REG);
            hssi->REG->RXUICR;
            LS_ASSERT(0);
        }
        if(irq & SSI_TXOIS_MASK)
        {
            LOG_W("si0x%x,Transmit FIFO Overflow",hssi->REG);
            hssi->REG->TXOICR;
            LS_ASSERT(0);
        }
        if(irq & SSI_TXEIS_MASK)
        {
            if(REG_FIELD_RD(hssi->REG->DMACR,SSI_TDMAE))
            {
                ssi_tx_empty_dma_isr(hssi);
            }else{
                ssi_tx_empty_isr(hssi);
            }
        }    
    }
}
