#include <string.h>
#include <stddef.h>
#include "ls_hal_cec.h"
#include "field_manipulate.h"
#include "reg_sysc_awo.h"
#include "reg_sysc_per.h"
#include "common.h"
#include "ls_msp_cec.h"

static void CEC_SetConfig(CEC_HandleTypeDef *hcec)
{
    hcec->Instance->CEC_LOG_ADDR = 1 << hcec->Init.MasterAddress;
    hcec->Instance->TX_DATA[0] = (hcec->Init.MasterAddress << 4) | (hcec->Init.SlaveAddress);
    hcec->Instance->TX_BUF_CNT = 0;
    hcec->Instance->CEC_CTRL = FIELD_BUILD(CEC_SEND, 1) | FIELD_BUILD(CEC_FRAME_TYPE, hcec->Init.FrameType)
                               | FIELD_BUILD(BC_NACK, 0) | FIELD_BUILD(CEC_STANDY, 0)
                               | FIELD_BUILD(CEC_EN, CEC_ENABLE) | FIELD_BUILD(CEC_CLK_RATE, CEC_CLKRATE);
}

HAL_StatusTypeDef HAL_CEC_Init(CEC_HandleTypeDef *hcec)
{
    if (hcec == NULL)
    {
        return HAL_INVALIAD_PARAM;
    }
    HAL_CEC_MSP_Init(hcec);
    CEC_SetConfig(hcec);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_CEC_DeInit(CEC_HandleTypeDef *hcec)
{
    HAL_CEC_MSP_DeInit(hcec);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_CEC_Transmit(CEC_HandleTypeDef *hcec, uint8_t SlaveAddress, uint32_t *buffer, uint8_t Size)
{
    hcec->Instance->TX_DATA[0] = (hcec->Init.MasterAddress << 4) | SlaveAddress;
    while (Size)
    {
        if (Size > MAXNUM_RECEIVE_ONCE - 1)
        {
            hcec->Instance->TX_BUF_CNT = MAXNUM_RECEIVE_ONCE;
        }
        else
        {
            hcec->Instance->TX_BUF_CNT = Size;
        }
        memcpy32((uint32_t *)(hcec->Instance->TX_DATA) + 1, buffer, hcec->Instance->TX_BUF_CNT-1);
        REG_FIELD_WR(hcec->Instance->CEC_CTRL, CEC_SEND, 1);
        if((READ_BIT(hcec->Instance->INTR_STT, TX_ERR_RAW_MASK) == 0) && (READ_BIT(hcec->Instance->INTR_STT, NACK_RAW_MASK) == 0))
        {
            while (READ_BIT(hcec->Instance->INTR_STT, TX_DONE_RAW_MASK) == 0);
            REG_FIELD_WR(hcec->Instance->INTR_MSK, TX_DONE_CLR, 1); 
            REG_FIELD_WR(hcec->Instance->CEC_CTRL, CEC_SEND, 0);
            Size -= hcec->Instance->TX_BUF_CNT;
        }
        else
        {
            REG_FIELD_WR(hcec->Instance->INTR_MSK, TX_ERR_CLR, 1);
            REG_FIELD_WR(hcec->Instance->INTR_MSK, NACK, 1);
            return HAL_ERROR;
        }
    }
    return HAL_OK;
}

HAL_StatusTypeDef HAL_CEC_Receive(CEC_HandleTypeDef *hcec, uint32_t *buffer, uint8_t* Size)
{
    *Size = hcec->Instance->RX_BUF_CNT;
    if(*Size)
    {
        if(READ_BIT(hcec->Instance->INTR_STT, LBIT_ERR_RAW_MASK) == 0)
        {
            while(REG_FIELD_RD(hcec->Instance->INTR_STT,  RX_FINISH_RAW) == 0);
            REG_FIELD_WR(hcec->Instance->INTR_MSK, RX_FINISH_CLR, 1);
            memcpy32(buffer, (uint32_t *)hcec->Instance->RX_DATA, *Size);
            REG_FIELD_WR(hcec->Instance->CEC_CTRL, CEC_EN, CEC_DISABLE);
            REG_FIELD_WR(hcec->Instance->CEC_CTRL, CEC_EN, CEC_ENABLE);
            hcec->Instance->BUF_LOCK = 0x00;
            return HAL_OK;
        }
        else
        {
            REG_FIELD_WR(hcec->Instance->INTR_MSK, LBIT_ERR_CLR, 1);
            return HAL_ERROR;
        }
    }
    else
    {
        return HAL_ERROR;
    }
}

static void CEC_Transmit_IT(CEC_HandleTypeDef *hcec)
{
    hcec->cbk_index ++;
    if (hcec->recv.size > MAXNUM_RECEIVE_ONCE-1)
    {
        hcec->Instance->TX_BUF_CNT = MAXNUM_RECEIVE_ONCE;
        memcpy32((uint32_t *)(hcec->Instance->TX_DATA) + 1, (hcec->recv.txbuf) + (hcec->cbk_index * 15), hcec->Instance->TX_BUF_CNT - 1);
        hcec->recv.size -= 15;
    }
    else
    {
        hcec->Instance->TX_BUF_CNT = hcec->recv.size + 1;
        memcpy32((uint32_t *)(hcec->Instance->TX_DATA) + 1, (hcec->recv.txbuf) + (hcec->cbk_index * 15), hcec->Instance->TX_BUF_CNT - 1);
        hcec->recv.size = 0;
    }
    REG_FIELD_WR(hcec->Instance->CEC_CTRL, CEC_SEND, 1);
}

static void CEC_Receive_IT(CEC_HandleTypeDef *hcec)
{
    hcec->recv.size = hcec->Instance->RX_BUF_CNT;
    memcpy32(hcec->recv.rxbuf, (uint32_t *)hcec->Instance->RX_DATA, hcec->recv.size);
    REG_FIELD_WR(hcec->Instance->CEC_CTRL, CEC_EN, CEC_DISABLE);
    REG_FIELD_WR(hcec->Instance->CEC_CTRL, CEC_EN, CEC_ENABLE);
    hcec->Instance->BUF_LOCK = 0x00;
}

HAL_StatusTypeDef HAL_CEC_Transmit_IT( CEC_HandleTypeDef *hcec,uint8_t SlaveAddress, uint32_t *buffer, uint16_t Size)
{
    if ((buffer == NULL) || (Size == 0U))
    {
        return HAL_INVALIAD_PARAM;
    }
    hcec->cbk_index = 0;
    hcec->recv.txbuf = buffer;
    hcec->recv.size = Size;
    hcec->Instance->TX_DATA[0] = (hcec->Init.MasterAddress << 4) | SlaveAddress;
    
    if(hcec->recv.size > MAXNUM_RECEIVE_ONCE-1)
    {
        hcec->Instance->TX_BUF_CNT = MAXNUM_RECEIVE_ONCE;
        memcpy32((uint32_t *)(hcec->Instance->TX_DATA) + 1, hcec->recv.txbuf, hcec->Instance->TX_BUF_CNT - 1);
        hcec->recv.size -= MAXNUM_RECEIVE_ONCE;
    }
    else
    {
        hcec->Instance->TX_BUF_CNT = Size;
        memcpy32((uint32_t *)(hcec->Instance->TX_DATA) + 1, hcec->recv.txbuf, hcec->Instance->TX_BUF_CNT - 1);
        hcec->recv.size = 0;
    }
    WRITE_REG(hcec->Instance->INTR_MSK, TX_DONE_CLR_MASK | TX_ERR_CLR_MASK);
    WRITE_REG(hcec->Instance->INTR_MSK, TX_DONE_MASK | TX_ERR_MASK);
    REG_FIELD_WR(hcec->Instance->CEC_CTRL, CEC_SEND, 1);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_CEC_Receive_IT( CEC_HandleTypeDef *hcec, uint32_t *buffer)
{	
    if (hcec == NULL)
    {
        return HAL_INVALIAD_PARAM;
    }
    hcec->recv.rxbuf = buffer;
    WRITE_REG(hcec->Instance->INTR_MSK, RX_FINISH_CLR_MASK | LBIT_ERR_CLR_MASK);
    WRITE_REG(hcec->Instance->INTR_MSK, RX_FINISH_MASK | LBIT_ERR_MASK);
    return HAL_OK;
}

__attribute__((weak)) void HAL_CEC_TX_DONE_Callback(void){}
__attribute__((weak)) void HAL_CEC_RX_FINISH_Callback(uint8_t count){}
__attribute__((weak)) void HAL_CEC_NACK_Callback(void){}
__attribute__((weak)) void HAL_CEC_ARB_LOST_Callback(void){}
__attribute__((weak)) void HAL_CEC_TX_ERR_Callback(void){}
__attribute__((weak)) void HAL_CEC_LBIT_ERR_Callback(void){}
__attribute__((weak)) void HAL_CEC_WAKE_EN_Callback(void){}
void HAL_CEC_IRQHandler(CEC_HandleTypeDef *hcec)
{
    uint32_t cec_isrflags = hcec->Instance->INTR_STT;
    if((cec_isrflags & TX_DONE_STT_MASK))
    {
        hcec->Instance->INTR_MSK = TX_DONE_CLR_MASK | TX_DONE_MASK;
        if(hcec->recv.size)
        {
            CEC_Transmit_IT(hcec);
        }
        else
        {
            HAL_CEC_TX_DONE_Callback();
        }
    }

    if(cec_isrflags & RX_FINISH_STT_MASK)
    {
        hcec->Instance->INTR_MSK = RX_FINISH_CLR_MASK | RX_FINISH_MASK;
        CEC_Receive_IT(hcec);
        HAL_CEC_RX_FINISH_Callback( hcec->recv.size);
    }

    if(cec_isrflags & NACK_STT_MASK)
    {
        hcec->Instance->INTR_MSK = NACK_CLR_MASK | NACK_MASK;
        HAL_CEC_NACK_Callback();
    }

    if(cec_isrflags & ARB_LOST_STT_MASK)
    {
        hcec->Instance->INTR_MSK = ARB_LOST_CLR_MASK | ARB_LOST_MASK;
        HAL_CEC_ARB_LOST_Callback();
    }

    if(cec_isrflags & TX_ERR_STT_MASK)
    {
        hcec->Instance->INTR_MSK = TX_ERR_CLR_MASK | TX_ERR_MASK;
        HAL_CEC_TX_ERR_Callback();
    }
    
    if(cec_isrflags & LBIT_ERR_STT_MASK)
    {
        hcec->Instance->INTR_MSK = LBIT_ERR_CLR_MASK | LBIT_ERR_MASK;
        HAL_CEC_LBIT_ERR_Callback();
    }

    if(cec_isrflags & WAKE_INT_STT_MASK)
    {
        hcec->Instance->INTR_MSK = WAKE_INT_CLR_MASK | WAKE_INT_MASK;
        HAL_CEC_WAKE_EN_Callback();
    }	
}