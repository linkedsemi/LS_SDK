#include "ls_hal_owm.h"
#include "ls_msp_owm.h"
#include "field_manipulate.h"
#include "ls_soc_gpio.h"
#include "platform.h"
#include "systick.h"
#include "app_config.h"

void HAL_OWM_Init(OWM_HandleTypeDef* owm)
{
    HAL_LSOWM_MSP_Init(owm);
}

void HAL_OWM_DeInit(OWM_HandleTypeDef* owm)
{
    HAL_LSOWM_MSP_DeInit(owm);
}

void OwmRst_Cfg(OWM_HandleTypeDef *owm)
{
    MODIFY_REG(owm->Instance->OWM_CTRL0,OWM_DAT_LEN_MASK|OWM_FLT_NUM_MASK|OWM_PRE_DIV_MASK,RST_DAT_LEN<<OWM_DAT_LEN_POS|owm->flt_num<<OWM_FLT_NUM_POS|owm->per_div<<OWM_PRE_DIV_POS);
    MODIFY_REG(owm->Instance->OWM_CTRL1,OWM_BIT_CYC_MASK|OWM_SMP_IDX_MASK,(RST_WRITE_BIT_CYC*SDK_HCLK_MHZ/(owm->per_div+1))<<OWM_BIT_CYC_POS|(RST_WRITE_SMP_IDX*SDK_HCLK_MHZ/(owm->per_div+1))<<OWM_SMP_IDX_POS);
    MODIFY_REG(owm->Instance->OWM_TGL,OWM_TGL0_IDX_MASK|OWM_TGL1_IDX_MASK,(RST_TGL0_IDX*SDK_HCLK_MHZ/(owm->per_div+1))<<OWM_TGL0_IDX_POS);
}

void OwmReadWrite_Cfg(OWM_HandleTypeDef *owm)
{
    MODIFY_REG(owm->Instance->OWM_CTRL0,OWM_DAT_LEN_MASK|OWM_FLT_NUM_MASK|OWM_PRE_DIV_MASK,owm->dat_len<<OWM_DAT_LEN_POS|owm->flt_num<<OWM_FLT_NUM_POS|owm->per_div<<OWM_PRE_DIV_POS);
    MODIFY_REG(owm->Instance->OWM_CTRL1,OWM_BIT_CYC_MASK|OWM_SMP_IDX_MASK,(BIT_CYC*SDK_HCLK_MHZ/(owm->per_div+1))<<OWM_BIT_CYC_POS | (SMP_IDX*SDK_HCLK_MHZ/(owm->per_div+1))<<OWM_SMP_IDX_POS);
    MODIFY_REG(owm->Instance->OWM_TGL,OWM_TGL0_IDX_MASK|OWM_TGL1_IDX_MASK,(TGL0_IDX*SDK_HCLK_MHZ/(owm->per_div+1))<<OWM_TGL0_IDX_POS | (TGL1_IDX*SDK_HCLK_MHZ/(owm->per_div+1))<<OWM_TGL1_IDX_POS);
}

static void wait_trans_fini(OWM_HandleTypeDef *owm)
{
    WRITE_REG(owm->Instance->TXRX_REQ, OWM_TXRX_REQ_MASK);
    while (READ_REG(owm->Instance->TXRX_REQ));
}

static void WriteData(OWM_HandleTypeDef *owm, uint8_t* pData,uint32_t numbytes)
{
    LS_ASSERT(numbytes > 0);
    volatile uint32_t write_count = (numbytes*8)%(owm->dat_len+1) == 0? ((numbytes*8)/(owm->dat_len+1)) : ((numbytes*8)/(owm->dat_len+1)+1) ;
    if(owm->dat_len <= 7)
    {
        if(owm->State == HAL_OWM_RESET_WRITE)
        {
            WRITE_REG(owm->Instance->TX_DAT, *pData++);
            wait_trans_fini(owm);
        }
        else
        {
            for (uint32_t i = 0; i < write_count; i++)
            {
                WRITE_REG(owm->Instance->TX_DAT, *pData++);
                wait_trans_fini(owm);
            }
        }
    }
    else if(owm->dat_len <= 16)
    {
        for (uint32_t i = 0; i < write_count; i++)
        {
            WRITE_REG(owm->Instance->TX_DAT, *(uint16_t *)pData);
            pData += sizeof(uint16_t);
            wait_trans_fini(owm);
        }

    }
    else
    {
        for (uint32_t i = 0; i < write_count; i++)
        {
            WRITE_REG(owm->Instance->TX_DAT, *(uint32_t*)pData);
            pData += sizeof(uint32_t);
            wait_trans_fini(owm);
        }
    }
}

static void ReadData(OWM_HandleTypeDef *owm, uint8_t* pData,uint32_t numbytes)
{
    LS_ASSERT(numbytes > 0);
    volatile uint32_t read_count = (numbytes*8)%(owm->dat_len+1) == 0? ((numbytes*8)/(owm->dat_len+1)) : ((numbytes*8)/(owm->dat_len+1)+1) ;
    owm->pBuffPtr = pData;
    if(owm->dat_len <= 7)
    {
        if(owm->State == HAL_OWM_RESET_READ)
        {
            WRITE_REG(owm->Instance->TX_DAT, 0xffffffff);
            wait_trans_fini(owm);
            *owm->pBuffPtr = (uint8_t)READ_REG(owm->Instance->RX_DAT);
        }
        else 
        {
            for (uint32_t i = 0; i < read_count; i++)
            {
                WRITE_REG(owm->Instance->TX_DAT, 0xffffffff);
                wait_trans_fini(owm);
                *owm->pBuffPtr = (uint8_t)READ_REG(owm->Instance->RX_DAT);
                owm->pBuffPtr += sizeof(uint8_t);
            }
        }
    }
    else if (owm->dat_len <= 15)
    {
        for(uint32_t i = 0; i < read_count; i++)
        {
            WRITE_REG(owm->Instance->TX_DAT, 0xffffffff);
            wait_trans_fini(owm);
            *(uint16_t*)owm->pBuffPtr = (uint16_t)READ_REG(owm->Instance->RX_DAT);
            owm->pBuffPtr += sizeof(uint16_t);
        }
    }
    else
    {
        for (uint32_t i = 0; i < read_count; i++)
        {
            WRITE_REG(owm->Instance->TX_DAT, 0xffffffff);
            wait_trans_fini(owm);
            *(uint32_t*)owm->pBuffPtr = (uint32_t)READ_REG(owm->Instance->RX_DAT);
            owm->pBuffPtr += sizeof(uint32_t);
        }
    }
}

uint8_t HAL_OneWireRst(OWM_HandleTypeDef *owm)
{
    uint8_t ack = 0;
    uint8_t MASTER_LOW = 0x00;
    owm->State = HAL_OWM_RESET_WRITE;
    OwmRst_Cfg(owm);
    WriteData(owm,&MASTER_LOW,1);
    MODIFY_REG(owm->Instance->OWM_CTRL1,OWM_BIT_CYC_MASK|OWM_SMP_IDX_MASK,(RST_READ_BIT_CYC*SDK_HCLK_MHZ/(owm->per_div+1))<<OWM_BIT_CYC_POS|(RST_READ_SMP_IDX*SDK_HCLK_MHZ/(owm->per_div+1))<<OWM_SMP_IDX_POS);
    owm->State = HAL_OWM_RESET_READ;
    ReadData(owm,&ack,1);
    return ack;
}

void HAL_OWM_WriteData(OWM_HandleTypeDef *owm, uint8_t *pData, uint32_t numbytes)
{
    LS_ASSERT(numbytes > 0);
    OwmReadWrite_Cfg(owm);
    WriteData(owm,pData,numbytes);
}

void HAL_OWM_ReadData(OWM_HandleTypeDef *owm, uint8_t* pData,uint32_t numbytes)
{
    LS_ASSERT(numbytes > 0);
    OwmReadWrite_Cfg(owm);
    ReadData(owm,pData,numbytes);    
}

static void HAL_WriteOneWire_IT(OWM_HandleTypeDef *owm)
{
    owm->Instance->INTR_CLR = OWM_INTR_CLR_MASK;
    WRITE_REG(owm->Instance->INTR_MSK,OWM_INTR_MSK_MASK);
    if(owm->dat_len <= 7)
    {
        WRITE_REG(owm->Instance->TX_DAT, *owm->pBuffPtr++);
    }
    else if(owm->dat_len <= 15)
    {
        WRITE_REG(owm->Instance->TX_DAT, *(uint16_t*)owm->pBuffPtr);
        owm->pBuffPtr += sizeof(uint16_t);
    }
    else
    {
        WRITE_REG(owm->Instance->TX_DAT, *(uint32_t*)owm->pBuffPtr);
        owm->pBuffPtr += sizeof(uint32_t);
    }
    WRITE_REG(owm->Instance->TXRX_REQ,OWM_TXRX_REQ_MASK);
}

static void WriteData_IT(OWM_HandleTypeDef *owm, uint8_t *pData, uint32_t numbytes)
{
    LS_ASSERT(numbytes > 0);
    owm->pBuffPtr = pData;
    owm->XferCount = (numbytes*8)%(owm->dat_len+1) == 0? ((numbytes*8)/(owm->dat_len+1)) : ((numbytes*8)/(owm->dat_len+1)+1);
    HAL_WriteOneWire_IT(owm);
}

void HAL_OneWireRst_IT(OWM_HandleTypeDef *owm)
{
    owm->Instance->INTR_CLR = OWM_INTR_CLR_MASK;
    uint8_t MASTER_LOW = 0x00;
    owm->State = HAL_OWM_RESET_WRITE;
    OwmRst_Cfg(owm);
    WriteData_IT(owm,&MASTER_LOW,1);
}

void HAL_OWM_WriteData_IT(OWM_HandleTypeDef *owm, uint8_t *pData, uint32_t numbytes)
{
    owm->State = HAL_OWM_WRITE;
    OwmReadWrite_Cfg(owm);
    WriteData_IT(owm,pData,numbytes);
}

static void HAL_ReadOneWire_IT(OWM_HandleTypeDef *owm)
{
    owm->Instance->INTR_CLR = OWM_INTR_CLR_MASK;
    WRITE_REG(owm->Instance->INTR_MSK,OWM_INTR_MSK_MASK);
    WRITE_REG(owm->Instance->TX_DAT,0xffffffff);
    WRITE_REG(owm->Instance->TXRX_REQ,OWM_TXRX_REQ_MASK);
}

static void ReadData_IT(OWM_HandleTypeDef *owm, uint8_t* pData, uint32_t numbytes)
{
    LS_ASSERT(numbytes > 0);
    owm->XferCount = (numbytes*8)%(owm->dat_len+1) == 0? ((numbytes*8)/(owm->dat_len+1)) : ((numbytes*8)/(owm->dat_len+1)+1);
    owm->pBuffPtr = pData;
    HAL_ReadOneWire_IT(owm);
}

void HAL_OWM_ReadData_IT(OWM_HandleTypeDef *owm, uint8_t* pData, uint32_t numbytes)
{
    owm->State = HAL_OWM_READ;
    OwmReadWrite_Cfg(owm);
    ReadData_IT(owm,pData,numbytes);
}

static void HAL_OneWireRst_Read_IT(OWM_HandleTypeDef *owm, uint8_t* pData, uint32_t numbytes)
{
    owm->State = HAL_OWM_RESET_READ;
    ReadData_IT(owm,pData,numbytes);
}

__attribute__((weak)) void HAL_LSOWM_RstComplete_Callback(OWM_HandleTypeDef* owm, uint8_t ack){}
__attribute__((weak)) void HAL_LSOWM_TxComplete_Callback(OWM_HandleTypeDef* owm){}
__attribute__((weak)) void HAL_LSOWM_RxComplete_Callback(OWM_HandleTypeDef* owm){}
void HAL_LSOWM_IRQHandler(OWM_HandleTypeDef* owm)
{
    if(owm->Instance->INTR_STT & OWM_INTR_FSM_END_MASK)
    {
        owm->Instance->INTR_CLR = OWM_INTR_CLR_MASK;
        if(owm->State == HAL_OWM_WRITE)
        {
            if (owm->XferCount > 1)
            {
                owm->XferCount--;
                HAL_WriteOneWire_IT(owm);
            }
            else 
            {
                WRITE_REG(owm->Instance->INTR_MSK, 0);
                HAL_LSOWM_TxComplete_Callback(owm);
            }
        }
        else if(owm->State == HAL_OWM_READ)
        {
            if (owm->dat_len <= 7)
            {
                *owm->pBuffPtr = (uint8_t)READ_REG(owm->Instance->RX_DAT);
                owm->pBuffPtr += sizeof(uint8_t);
            }
            else if (owm->dat_len <= 15)
            {
                *(uint16_t*)owm->pBuffPtr = (uint16_t)READ_REG(owm->Instance->RX_DAT);
                owm->pBuffPtr += sizeof(uint16_t);
            }
            else
            {
                *(uint32_t*)owm->pBuffPtr = (uint32_t)READ_REG(owm->Instance->RX_DAT);
                owm->pBuffPtr += sizeof(uint32_t);
            }
            owm->XferCount--;
            if (owm->XferCount > 0)
            {
                HAL_ReadOneWire_IT(owm);
            }
            else
            {
                WRITE_REG(owm->Instance->INTR_MSK, 0);
                HAL_LSOWM_RxComplete_Callback(owm);
            }
        }
        else if (owm->State == HAL_OWM_RESET_WRITE)
        {
            WRITE_REG(owm->Instance->INTR_MSK, 0);
            MODIFY_REG(owm->Instance->OWM_CTRL1,OWM_BIT_CYC_MASK|OWM_SMP_IDX_MASK,(RST_READ_BIT_CYC*SDK_HCLK_MHZ/(owm->per_div+1))<<OWM_BIT_CYC_POS|(RST_READ_SMP_IDX*SDK_HCLK_MHZ/(owm->per_div+1))<<OWM_SMP_IDX_POS);
            HAL_OneWireRst_Read_IT(owm,&owm->owm_ack,1);
        }
        else
        {
            WRITE_REG(owm->Instance->INTR_MSK, 0);
            *owm->pBuffPtr = (uint8_t)READ_REG(owm->Instance->RX_DAT);
            HAL_LSOWM_RstComplete_Callback(owm,owm->owm_ack);
        }
    }
}