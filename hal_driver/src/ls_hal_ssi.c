#include "ls_msp_ssi.h"
#include "field_manipulate.h"
#include "log.h"
#include "ls_dbg.h"
#include "ls_hal_ssi.h"
#define SSI_TX_FIFO_DEPTH 4
#define SSI_RX_FIFO_DEPTH 4
HAL_StatusTypeDef HAL_SSI_Init(SSI_HandleTypeDef *hssi)
{
    HAL_SSI_MSP_Init(hssi);
    HAL_SSI_MSP_Busy_Set(hssi);
    hssi->REG->BAUDR = hssi->Init.clk_div;
    hssi->REG->RXSAMPLE_DLY = hssi->Init.rxsample_dly;
    hssi->DR_REG = &hssi->REG->DR;
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

static inline void ssi_ser_cfg(SSI_HandleTypeDef *hssi)
{
    hssi->REG->SER = hssi->Hardware_CS_Mask ? hssi->Hardware_CS_Mask : 0xff;
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
}

static void tx_var_init(SSI_HandleTypeDef *hssi,void *Data,uint16_t Count)
{
    hssi->Tx_Env.Interrupt.Data = Data;
    hssi->Tx_Env.Interrupt.Count = Count;
}

HAL_StatusTypeDef HAL_SSI_Transmit_IT(SSI_HandleTypeDef *hssi,void *Data,uint16_t Count)
{
    tx_var_init(hssi,Data,Count);
    ssi_ctrlr0_set(hssi,Motorola_SPI,Transmit_Only);
    ssi_config_it(hssi,true,false); 
    ssi_ser_cfg(hssi);
    return HAL_OK;
}

__attribute__((weak)) void HAL_SSI_TxCpltCallback(SSI_HandleTypeDef *hssi){}

static void rx_var_init(SSI_HandleTypeDef *hssi,void *Data,uint16_t Count)
{
    hssi->Rx_Env.Interrupt.Data = Data;
    hssi->Rx_Env.Interrupt.Count = Count;
}

HAL_StatusTypeDef HAL_SSI_Receive_IT(SSI_HandleTypeDef *hssi,void *Data,uint16_t Count)
{
    rx_var_init(hssi,Data,Count);
    ssi_ctrlr0_set(hssi,Motorola_SPI,Receive_Only);
    hssi->REG->CTRLR1 = Count - 1;
    ssi_config_it(hssi,false,true);
    ssi_ser_cfg(hssi);
    hssi->DR_REG[0] = 0;
    return HAL_OK;
}

__attribute__((weak)) void HAL_SSI_RxCpltCallback(SSI_HandleTypeDef *hssi){}

HAL_StatusTypeDef HAL_SSI_TransmitReceive_IT(SSI_HandleTypeDef *hssi,void *TX_Data,void *RX_Data,uint16_t Count)
{
    tx_var_init(hssi,TX_Data,Count);
    rx_var_init(hssi,RX_Data,Count);
    ssi_ctrlr0_set(hssi,Motorola_SPI,Transmit_and_Receive);
    ssi_config_it(hssi,true,true);
    ssi_ser_cfg(hssi);
    return HAL_OK;
}

static void ssi_disable(SSI_HandleTypeDef *hssi)
{
    while(REG_FIELD_RD(hssi->REG->SR,SSI_BUSY) == SSI_Busy);
    hssi->REG->SSIENR = SSI_Disabled;
    hssi->REG->SER = 0;
}

void ssi_rx_done(SSI_HandleTypeDef *hssi,void (*rx_callback)(SSI_HandleTypeDef *hssi),void (*txrx_callback)(SSI_HandleTypeDef *hssi),void (*txrx_halfduplex_callback)(SSI_HandleTypeDef *hssi))
{
    ssi_disable(hssi);
    switch(REG_FIELD_RD(hssi->REG->CTRLR0,SSI_TMOD))
    {
    case Receive_Only:
        rx_callback(hssi);
    break;
    case Transmit_and_Receive:
        txrx_callback(hssi);
    break;
    case EEPROM_Read:
        txrx_halfduplex_callback(hssi);
    break;
    }
}

__attribute__((weak)) void HAL_SSI_TxRxCpltCallback(SSI_HandleTypeDef *hssi){}

__attribute__((weak)) void HAL_SSI_TxRxHalfDuplexCpltCallback(SSI_HandleTypeDef *hssi){}

static void ssi_data_rx(SSI_HandleTypeDef *hssi)
{
    while(REG_FIELD_RD(hssi->REG->SR,SSI_RFNE))
    {
        if(hssi->Init.ctrl.data_frame_size <= DFS_32_8_bits)
        {
            *(uint8_t *)hssi->Rx_Env.Interrupt.Data = (uint8_t)hssi->DR_REG[0];
            hssi->Rx_Env.Interrupt.Data += 1;
        }else if(hssi->Init.ctrl.data_frame_size <= DFS_32_16_bits)
        {
            *(uint16_t *)hssi->Rx_Env.Interrupt.Data = (uint16_t)hssi->DR_REG[0];
            hssi->Rx_Env.Interrupt.Data += 2;
        }else
        {
            *(uint32_t *)hssi->Rx_Env.Interrupt.Data = (uint32_t)hssi->DR_REG[0];
            hssi->Rx_Env.Interrupt.Data += 4;
        }
        --hssi->Rx_Env.Interrupt.Count;
    }
}

static void ssi_rx_full_isr(SSI_HandleTypeDef *hssi)
{
    ssi_data_rx(hssi);
    if(hssi->Rx_Env.Interrupt.Count == 0)
    {
        ssi_rx_done(hssi,HAL_SSI_RxCpltCallback,HAL_SSI_TxRxCpltCallback,HAL_SSI_TxRxHalfDuplexCpltCallback);
    }
}

void ssi_tx_done(SSI_HandleTypeDef *hssi,void (*tx_callback)(SSI_HandleTypeDef *hssi))
{
    REG_FIELD_WR(hssi->REG->IMR,SSI_TXEIM,0);
    if(REG_FIELD_RD(hssi->REG->CTRLR0,SSI_TMOD) == Transmit_Only)
    {
        ssi_disable(hssi);
        tx_callback(hssi);
    }
}

static void ssi_data_tx(SSI_HandleTypeDef *hssi)
{
    while(REG_FIELD_RD(hssi->REG->SR,SSI_TFNF)&&hssi->Tx_Env.Interrupt.Count)
    {
        if(hssi->Init.ctrl.data_frame_size <= DFS_32_8_bits)
        {
            hssi->DR_REG[0] = *(uint8_t *)hssi->Tx_Env.Interrupt.Data;
            hssi->Tx_Env.Interrupt.Data += 1;
        }else if(hssi->Init.ctrl.data_frame_size <= DFS_32_16_bits)
        {
            hssi->DR_REG[0] = *(uint16_t *)hssi->Tx_Env.Interrupt.Data;
            hssi->Tx_Env.Interrupt.Data += 2;
        }else
        {
            hssi->DR_REG[0] = *(uint32_t *)hssi->Tx_Env.Interrupt.Data;
            hssi->Tx_Env.Interrupt.Data += 4;
        }
        --hssi->Tx_Env.Interrupt.Count;
    }
}

static void ssi_tx_empty_isr(SSI_HandleTypeDef *hssi)
{
    if(hssi->Tx_Env.Interrupt.Count)
    {
        ssi_data_tx(hssi);
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

HAL_StatusTypeDef HAL_SSI_Transmit(SSI_HandleTypeDef *hssi,void *Data,uint16_t Count)
{
    tx_var_init(hssi,Data,Count);
    ssi_ctrlr0_set(hssi,Motorola_SPI,Transmit_Only);
    ssi_config_it(hssi,false,false);
    ssi_data_tx(hssi);
    ssi_ser_cfg(hssi);
    while(hssi->Tx_Env.Interrupt.Count)
    {
        ssi_data_tx(hssi);
    }
    ssi_disable(hssi);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_SSI_Receive(SSI_HandleTypeDef *hssi,void *Data,uint16_t Count)
{
    rx_var_init(hssi,Data,Count);
    ssi_ctrlr0_set(hssi,Motorola_SPI,Receive_Only);
    hssi->REG->CTRLR1 = Count - 1;
    ssi_config_it(hssi,false,false);
    ssi_ser_cfg(hssi);
    hssi->DR_REG[0] = 0;
    while(hssi->Rx_Env.Interrupt.Count)
    {
        ssi_data_rx(hssi);
    }
    ssi_disable(hssi);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_SSI_TransmitReceive(SSI_HandleTypeDef *hssi,void *TX_Data,void *RX_Data,uint16_t Count)
{
    tx_var_init(hssi,TX_Data,Count);
    rx_var_init(hssi,RX_Data,Count);
    ssi_ctrlr0_set(hssi,Motorola_SPI,Transmit_and_Receive);
    ssi_config_it(hssi,false,false);
    ssi_data_tx(hssi);
    ssi_ser_cfg(hssi);
    while(hssi->Rx_Env.Interrupt.Count)
    {
        while(REG_FIELD_RD(hssi->REG->SR,SSI_RFNE)==0);
        ssi_data_rx(hssi);
        ssi_data_tx(hssi);
    }
    ssi_disable(hssi);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_SSI_TransmitReceive_HalfDuplex(SSI_HandleTypeDef *hssi,void *TX_Data,uint16_t TX_Count,void *RX_Data,uint16_t RX_Count)
{
    tx_var_init(hssi,TX_Data,TX_Count);
    rx_var_init(hssi,RX_Data,RX_Count);
    ssi_ctrlr0_set(hssi,Motorola_SPI,EEPROM_Read);
    hssi->REG->CTRLR1 = RX_Count - 1;
    ssi_config_it(hssi,false,false);
    ssi_data_tx(hssi);
    ssi_ser_cfg(hssi);
    while(hssi->Tx_Env.Interrupt.Count)
    {
        ssi_data_tx(hssi);
    }
    while(hssi->Rx_Env.Interrupt.Count)
    {
        ssi_data_rx(hssi);
    }
    ssi_disable(hssi);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_SSI_TransmitReceive_HalfDuplex_IT(SSI_HandleTypeDef *hssi,void *TX_Data,uint16_t TX_Count,void *RX_Data,uint16_t RX_Count)
{
    tx_var_init(hssi,TX_Data,TX_Count);
    rx_var_init(hssi,RX_Data,RX_Count);
    ssi_ctrlr0_set(hssi,Motorola_SPI,EEPROM_Read);
    hssi->REG->CTRLR1 = RX_Count - 1;
    ssi_config_it(hssi,true,true);
    ssi_ser_cfg(hssi);
    return HAL_OK;
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

HAL_StatusTypeDef HAL_SSI_Use_Reversed_Data_Reg(SSI_HandleTypeDef *hssi,bool reversed_data_reg)
{
    hssi->DR_REG = reversed_data_reg? &hssi->REG->DR_REVERSED : &hssi->REG->DR;
    return HAL_OK;
}
