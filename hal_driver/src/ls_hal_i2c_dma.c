#include <stddef.h>
#include "sdk_config.h"
#include "platform.h"
#include "ls_hal_i2c.h"
#include "ls_msp_i2c.h"
#include "field_manipulate.h"

static void I2C_transmit_init(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint8_t Size)
{
    REG_FIELD_WR(hi2c->Instance->CR1, I2C_CR1_TXDMAEN, 1);
    __HAL_I2C_ENABLE(hi2c);
    hi2c->State       = HAL_I2C_STATE_BUSY_TX;
    hi2c->Mode        = HAL_I2C_MODE_MASTER;
    hi2c->ErrorCode   = HAL_I2C_ERROR_NONE;

    CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_AUTOEND_MASK | I2C_CR2_RELOAD_MASK | I2C_CR2_NBYTES_MASK);
    SET_BIT(hi2c->Instance->CR2, I2C_CR2_AUTOEND_MASK | ((Size) << I2C_CR2_NBYTES_POS));
    __HAL_I2C_CLEAR_IF(hi2c, I2C_ICR_ADDRIC_MASK | I2C_ICR_TXEIC_MASK | I2C_ICR_STOPIC_MASK);
    /* Clear TXFIFO */
    __HAL_I2C_CLR_TXDR(hi2c);
    /* Push the first byte to TXFIFO to trigger handshake signal for LE5010 */
    /* This will not introduce anything imcompatible for other platforms */
    hi2c->Instance->TXDR = *pData;
}

static void I2C_receive_init(I2C_HandleTypeDef *hi2c, uint8_t Size)
{
    REG_FIELD_WR(hi2c->Instance->CR1, I2C_CR1_RXDMAEN, 1);
    __HAL_I2C_ENABLE(hi2c);
    hi2c->State       = HAL_I2C_STATE_BUSY_RX;
    hi2c->Mode        = HAL_I2C_MODE_MASTER;
    hi2c->ErrorCode   = HAL_I2C_ERROR_NONE;

    CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_AUTOEND_MASK | I2C_CR2_RELOAD_MASK | I2C_CR2_NBYTES_MASK);
    SET_BIT(hi2c->Instance->CR2, I2C_CR2_AUTOEND_MASK | ((Size) << I2C_CR2_NBYTES_POS));
    __HAL_I2C_CLEAR_IF(hi2c, I2C_IT_EVT | I2C_IT_RXNE | I2C_IT_ERR);
    /* Clear TXFIFO */
    __HAL_I2C_CLR_TXDR(hi2c);
}

static bool I2C_addr_claim(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, bool Read)
{
    bool result = true;
    
    uint8_t bit_delay_array[I2C_SPEED_MAX] = {10, 3, 1};
    uint32_t cr2_rd_wrn_mask = 0;
    if (Read)
    {
        cr2_rd_wrn_mask = I2C_CR2_RD_WEN_MASK;
    }
    
    if (hi2c->Init.AddressingMode == I2C_ADDRESSINGMODE_7BIT)
    {
        CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_SADD10_MASK);
        MODIFY_REG(hi2c->Instance->CR2, I2C_CR2_RD_WEN_MASK | I2C_CR2_SADD1_7_MASK, cr2_rd_wrn_mask | ((DevAddress<<1)&0xFE));
    }
    else
    {
        SET_BIT(hi2c->Instance->CR2, I2C_CR2_SADD10_MASK);
        MODIFY_REG(hi2c->Instance->CR2, I2C_CR2_RD_WEN_MASK | I2C_CR2_SADD0_MASK | I2C_CR2_SADD1_7_MASK | I2C_CR2_SADD8_9_MASK, cr2_rd_wrn_mask | (DevAddress&0x3FF));
        CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_HEAD10R_MASK);
    }
    
    SET_BIT(hi2c->Instance->CR2, I2C_CR2_START_MASK);
    /* Wait for start flag clear */
    while (__HAL_I2C_GET_CR2_FLAG(hi2c,I2C_CR2_START_MASK) == SET);
    DELAY_US(bit_delay_array[hi2c->Init.ClockSpeed]);
    if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_NACK) == SET)
    {
        __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_NACK);
        hi2c->State               = HAL_I2C_STATE_READY;
        hi2c->Mode                = HAL_I2C_MODE_NONE;
        hi2c->ErrorCode           = HAL_I2C_ERROR_NACKF;
        result = false;
    }
    return result;
}

#if DMACV2
#include "ls_hal_dmacv2.h"
static void I2C_Transmit_DMA_Callback(DMA_Controller_HandleTypeDef *hdma,uint32_t param,uint8_t DMA_channel)
{
    I2C_HandleTypeDef *hi2c = (I2C_HandleTypeDef *)param;
    /* Enable stop irq */
    __HAL_I2C_ENABLE_IT(hi2c, I2C_IER_STOPIE_MASK);
}

static void I2C_Receive_DMA_Callback(DMA_Controller_HandleTypeDef *hdma,uint32_t param,uint8_t DMA_channel)
{
    I2C_HandleTypeDef *hi2c = (I2C_HandleTypeDef *)param;
    /* Enable stop irq */
    __HAL_I2C_ENABLE_IT(hi2c, I2C_IER_STOPIE_MASK);
}

HAL_StatusTypeDef HAL_I2C_Master_Transmit_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint8_t Size)
{
    if (pData == NULL || Size == 0 )
    {
        return HAL_INVALIAD_PARAM;
    }
    I2C_transmit_init(hi2c, pData, Size);
    if (!I2C_addr_claim(hi2c, DevAddress, false))
    {
        return HAL_ERROR;
    }
    if (Size > 1)
    {
        struct DMA_Channel_Config prim = {
            .ctrl.channel_en = 1,
            .ctrl.circular_mode_en = 0,
            .ctrl.peripheral_flow_ctrl = 0,
            .ctrl.direct_mode_en = 0,
            .ctrl.dma_mode_sel = Mem2Peri,
            .ctrl.channel_priority = 0,
            .ctrl.peripheral_handshake = HAL_I2C_TX_DMA_Handshake_Get(hi2c),
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
            .src_addr = (uint32_t)&pData[1],
            .dst_addr = (uint32_t)&hi2c->Instance->TXDR,
            /* The first byte has already been sent in I2C_transmit_init */
            .byte_count = Size - 1,
            .dummy = 0,
        };
        HAL_DMA_Channel_Start_IT(hi2c->DMAC_Instance, hi2c->Tx_Env.DMA.DMA_Channel, &prim, I2C_Transmit_DMA_Callback, (uint32_t)hi2c);
    }
    else
    {
        /* Enable stop irq */
        __HAL_I2C_ENABLE_IT(hi2c, I2C_IER_STOPIE_MASK);
    }
    
    return HAL_OK;
}

HAL_StatusTypeDef HAL_I2C_Master_Receive_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint8_t Size)
{
    if (pData == NULL || Size == 0 )
    {
        return HAL_INVALIAD_PARAM;
    }
    I2C_receive_init(hi2c, Size);
    if (!I2C_addr_claim(hi2c, DevAddress, true))
    {
        return HAL_ERROR;
    }
    struct DMA_Channel_Config prim = {
        .ctrl.channel_en = 1,
        .ctrl.circular_mode_en = 0,
        .ctrl.peripheral_flow_ctrl = 0,
        .ctrl.direct_mode_en = 0,
        .ctrl.dma_mode_sel = Peri2Mem,
        .ctrl.channel_priority = 0,
        .ctrl.peripheral_handshake = HAL_I2C_RX_DMA_Handshake_Get(hi2c),
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
        .src_addr = (uint32_t)&hi2c->Instance->RXDR,
        .dst_addr = (uint32_t)pData,
        .byte_count = Size,
        .dummy = 0,
    };
    HAL_DMA_Channel_Start_IT(hi2c->DMAC_Instance, hi2c->Rx_Env.DMA.DMA_Channel, &prim, I2C_Receive_DMA_Callback, (uint32_t)hi2c);
    return HAL_OK;
}

#else
#include "ls_hal_dmac.h"
static void I2C_Transmit_DMA_Callback(void *hdma,uint32_t param,uint8_t DMA_channel,bool alt)
{
    I2C_HandleTypeDef *hi2c = (I2C_HandleTypeDef *)param;
    /* Enable stop irq */
    __HAL_I2C_ENABLE_IT(hi2c, I2C_IER_STOPIE_MASK);
}

static void I2C_Receive_DMA_Callback(void *hdma,uint32_t param,uint8_t DMA_channel,bool alt)
{
    I2C_HandleTypeDef *hi2c = (I2C_HandleTypeDef *)param;
    /* Enable stop irq */
    __HAL_I2C_ENABLE_IT(hi2c, I2C_IER_STOPIE_MASK);
}

HAL_StatusTypeDef HAL_I2C_Master_Transmit_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint8_t Size)
{
    if (pData == NULL || Size == 0)
    {
        return HAL_INVALIAD_PARAM;
    }
    I2C_transmit_init(hi2c, pData, Size);
    if (!I2C_addr_claim(hi2c, DevAddress, false))
    {
        return HAL_ERROR;
    }
    if (Size > 1)
    {
        struct DMA_Channel_Config prim = {
            .src_data_end_ptr = (uint32_t)&pData[Size-1],
            .dst_data_end_ptr = (uint32_t)&hi2c->Instance->TXDR,
            .ctrl_data = {
                .cycle_ctrl = DMA_Cycle_Basic,
                .next_useburst = 0,
                /* The first byte has already been sent in I2C_transmit_init */
                .n_minus_1 = Size - 2,
                .R_power = 0,
                .src_prot_ctrl = 0,
                .dst_prot_ctrl = 0,
                .src_size = DMA_SIZE_BYTE,
                .src_inc = DMA_INC_BYTE,
                .dst_size = DMA_SIZE_BYTE,
                .dst_inc = DMA_INC_NONE,
            },
            .dummy = (uint32_t)I2C_Transmit_DMA_Callback,
        };
        HAL_DMA_Channel_Config_Set(hi2c->DMAC_Instance,hi2c->Tx_Env.DMA.DMA_Channel,false,&prim);
        HAL_DMA_Channel_Start_IT(hi2c->DMAC_Instance,hi2c->Tx_Env.DMA.DMA_Channel,HAL_I2C_TX_DMA_Handshake_Get(hi2c),(uint32_t)hi2c);
    }
    else
    {
        /* Enable stop irq */
        __HAL_I2C_ENABLE_IT(hi2c, I2C_IER_STOPIE_MASK);
    }
    return HAL_OK;
}

HAL_StatusTypeDef HAL_I2C_Master_Receive_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint8_t Size)
{
    if (pData == NULL || Size == 0)
    {
        return HAL_INVALIAD_PARAM;
    }
    I2C_receive_init(hi2c, Size);
    if (!I2C_addr_claim(hi2c, DevAddress, true))
    {
        return HAL_ERROR;
    }
    struct DMA_Channel_Config prim = {
        .src_data_end_ptr = (uint32_t)&hi2c->Instance->RXDR,
        .dst_data_end_ptr = (uint32_t)&pData[Size-1],
        .ctrl_data = {
            .cycle_ctrl = DMA_Cycle_Basic,
            .next_useburst = 0,
            .n_minus_1 = Size - 1,
            .R_power = 0,
            .src_prot_ctrl = 0,
            .dst_prot_ctrl = 0,
            .src_size = DMA_SIZE_BYTE,
            .src_inc = DMA_INC_NONE,
            .dst_size = DMA_SIZE_BYTE,
            .dst_inc = DMA_INC_BYTE,
        },
        .dummy = (uint32_t)I2C_Receive_DMA_Callback,
    };
    HAL_DMA_Channel_Config_Set(hi2c->DMAC_Instance,hi2c->Rx_Env.DMA.DMA_Channel,false,&prim);
    HAL_DMA_Channel_Start_IT(hi2c->DMAC_Instance,hi2c->Rx_Env.DMA.DMA_Channel,HAL_I2C_RX_DMA_Handshake_Get(hi2c),(uint32_t)hi2c);
    return HAL_OK;
}
#endif
