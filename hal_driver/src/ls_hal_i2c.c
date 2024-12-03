#include "ls_hal_i2c.h"
#include "systick.h"
#include "platform.h"

__attribute__((always_inline)) static inline uint8_t i2c_isTime0Big(uint32_t time0, uint32_t time1, uint8_t isRewind)
{
    if (isRewind == 0) {
        if (time0 >= time1) {
            return true;
        }
    } else {
        if (time1 >= time0) {
            return true;
        }
    }
    return false;
}

void HAL_I2C_Enable_Rstart(I2C_HandleTypeDef *hi2c)
{
    hi2c->State = 0;
    // hi2c->Instance->ICR = 0xFFFF;
    hi2c->Instance->CR1 &= ~I2C_CR1_PE_MASK;
    hi2c->Instance->CR1 |= I2C_CR1_PE_MASK;
}

void i2c_timing_param_get(uint32_t pclk,uint32_t i2c_clk,struct i2c_timing *param)
{
	uint16_t cycle_count;
	uint8_t prescalar = 0;
	do{
		prescalar += 2;
		cycle_count = pclk/i2c_clk/prescalar;
	}while(cycle_count>256);
	LS_ASSERT(cycle_count>=16&&prescalar<=16);
    int16_t scll, sclh, scldel, sdadel;
	scll = cycle_count/2;
    sclh = cycle_count/2 - 1 - 4;
    if (scll < 1)
    {
        scll = 1;
    }
    if (sclh < 0)
    {
        sclh = 0;
    }
    scldel = scll / 3;
    if (scldel > 15)
    {
        scldel = 15;
    }
    else if (scldel < 5)
    {
        /* SCLDEL should not bee too small to keep campatible with different resistance */
        scldel = 5;
    }
    sdadel = scldel - 4;
    if (sdadel > 10)
    {
        /* We should set a ceiling for SDADEL. This is unnecessary, and will reduce compatibility if we are IIC slave */
        sdadel = 10;
    }
    else if (sdadel < 1)
    {
        sdadel = 1;
    }
    /* HW design requires that SCLDEL should be no less than SDADEL + 5 */
    if (scldel <= sdadel + 5)
    {
        scldel = sdadel + 5;
    }
    param->presc = prescalar - 1;
    param->scll = scll;
    param->sclh = sclh;
    param->scldel = scldel;
    param->sdadel = sdadel;
}

static inline void i2c_timing_set(I2C_HandleTypeDef *hi2c)
{
    MODIFY_REG(hi2c->Instance->TIMINGR,I2C_TIMINGR_PRESC_MASK|I2C_TIMINGR_SCLH_MASK | I2C_TIMINGR_SCLL_MASK | I2C_TIMINGR_SDADEL_MASK|I2C_TIMINGR_SCLDEL_MASK,
        hi2c->timing_param.presc<<I2C_TIMINGR_PRESC_POS|hi2c->timing_param.sclh<<I2C_TIMINGR_SCLH_POS|hi2c->timing_param.scll<<I2C_TIMINGR_SCLL_POS
        |hi2c->timing_param.sdadel<<I2C_TIMINGR_SDADEL_POS|hi2c->timing_param.scldel<<I2C_TIMINGR_SCLDEL_POS);
}

HAL_StatusTypeDef HAL_I2C_Init(I2C_HandleTypeDef *hi2c)
{
    uint32_t i2c_clk=0;
    hi2c->State = 0;
    HAL_I2C_MSP_Init(hi2c);
    HAL_I2C_MSP_Busy_Set(hi2c);
    hi2c->Instance->CR1 &= ~I2C_CR1_PE_MASK;
    switch(hi2c->Init.ClockSpeed)
    {
    case I2C_SPEED_NORMAL_100K:
        i2c_clk = 100000;
    break;
    case I2C_SPEED_FAST_400K:
        i2c_clk = 400000;
    break;
    case I2C_SPEED_FAST_ULTRA_1M:
        i2c_clk = 1000000;
    break;
    default:
        LS_ASSERT(0);
    break;
    }
    i2c_timing_param_get(I2C_CLOCK,i2c_clk,&hi2c->timing_param);
    i2c_timing_set(hi2c);
    hi2c->Instance->ICR = 0xFFFF;
    hi2c->Instance->IDR = 0xFFFF;
    hi2c->Instance->CFR = 0xFFFF;
    hi2c->Instance->CR1 |= I2C_CR1_SBC_MASK | I2C_CR1_PE_MASK;
    hi2c->Instance->CR2_3 |= 1<<3; // slv nbytes upd hw workaround
    return HAL_OK;
}

HAL_StatusTypeDef HAL_I2C_DeInit(I2C_HandleTypeDef *hi2c)
{
    hi2c->State = 0;
    HAL_I2C_MSP_DeInit(hi2c);
    HAL_I2C_MSP_Idle_Set(hi2c);
    return HAL_OK;
}

static inline void i2c_clr_tx_fifo(I2C_HandleTypeDef *hi2c)
{
    hi2c->Instance->SR = 1;
}

HAL_StatusTypeDef HAL_I2C_EnableListen_IT(I2C_HandleTypeDef *hi2c)
{
    LS_ASSERT(hi2c->State == 0);
    hi2c->State = HAL_I2C_STATE_LISTEN;
    if(hi2c->Init.OA1_10bitMode)
    {
        hi2c->Instance->OAR1 = hi2c->Init.OA1_Enable<<I2C_OAR1_OA1EN_POS|1<<I2C_OAR1_OA1MODE_POS|hi2c->Init.OwnAddress1<<I2C_OAR1_OA10_POS;
    }else
    {
        hi2c->Instance->OAR1 = hi2c->Init.OA1_Enable<<I2C_OAR1_OA1EN_POS|hi2c->Init.OwnAddress1<<I2C_OAR1_OA11_7_POS;
    }
    hi2c->Instance->OAR2 = hi2c->Init.OA2_Enable<<I2C_OAR2_OA2EN_POS|hi2c->Init.OA2Mask<<I2C_OAR2_OA2MSK_POS|hi2c->Init.OwnAddress2<<I2C_OAR2_OA21_7_POS;
    hi2c->Instance->CR2_2 = 1;
    hi2c->Instance->CR2_3 |= I2C_CR2_RELOAD_MASK;
    hi2c->Instance->IER = I2C_INT_ADDR_MASK|I2C_INT_STOP_MASK;
    return HAL_OK;

}

HAL_StatusTypeDef HAL_I2C_DisableListen_IT(I2C_HandleTypeDef *hi2c)
{
    hi2c->Instance->OAR1 = 0;
    hi2c->Instance->OAR2 = 0;
    hi2c->Instance->IDR = I2C_INT_ADDR_MASK|I2C_INT_STOP_MASK|I2C_INT_TXE_MASK|I2C_INT_RXNE_MASK;
    hi2c->State = 0;
    return HAL_OK;
}

static void i2c_tx_byte(I2C_HandleTypeDef *hi2c)
{
    hi2c->Tx_Env.XferCount--;
    hi2c->Instance->TXDR = *hi2c->Tx_Env.pBuffPtr++;
}

HAL_StatusTypeDef HAL_I2C_Slave_Seq_Transmit_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size)
{
    LS_ASSERT(hi2c->State == HAL_I2C_STATE_LISTEN);
    /* 发送前，清空对应的buffer */
    i2c_clr_tx_fifo(hi2c);
    hi2c->Tx_Env.pBuffPtr = pData;
    hi2c->Tx_Env.XferCount = Size;
    hi2c->State |= HAL_I2C_STATE_BUSY_TX;
    hi2c->Instance->ICR = I2C_INT_TXE_MASK;
    i2c_tx_byte(hi2c);
    hi2c->Instance->IER = I2C_INT_TXE_MASK;
    return HAL_OK;

}

HAL_StatusTypeDef HAL_I2C_Slave_Seq_Receive_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size)
{
    LS_ASSERT(hi2c->State == HAL_I2C_STATE_LISTEN);
    hi2c->Rx_Env.pBuffPtr = pData;
    hi2c->Rx_Env.XferCount = Size;
    hi2c->State |= HAL_I2C_STATE_BUSY_RX;
    if(Size == 1)
    {
        hi2c->Instance->CR2_0_1 |= I2C_CR2_NACK_MASK;
    }
    // hi2c->Instance->CR2_2 = 1;
    // hi2c->Instance->ICR = I2C_INT_RXNE_MASK;
    // hi2c->Instance->TXDR = 0x0; /* 5010必须要有这个动作，才能触发发送中断 */
    hi2c->Instance->IER = I2C_INT_RXNE_MASK;
    return HAL_OK;
    

}

static void i2c_master_start(I2C_HandleTypeDef *hi2c,uint16_t DevAddress,uint8_t Size,bool read)
{
    hi2c->Instance->CR2_3 &= ~I2C_CR2_RELOAD_MASK;
    hi2c->Instance->CR2_2 = Size;
    uint16_t CR2_0_1BitMask =  DevAddress<<I2C_CR2_SADD1_7_POS | I2C_CR2_START_MASK;
    if(hi2c->Init.OA1_10bitMode)
    {
        CR2_0_1BitMask = DevAddress << I2C_CR2_SADD0_POS | I2C_CR2_HEAD10R_MASK | I2C_CR2_SADD10_MASK | I2C_CR2_START_MASK;
    }
    if(read)
    {
        hi2c->Instance->CR2_0_1 = CR2_0_1BitMask | I2C_CR2_RD_WEN_MASK;
    }else
    {
        hi2c->Instance->CR2_0_1 = CR2_0_1BitMask;
    }
}

static HAL_StatusTypeDef i2c_tx_polling(I2C_HandleTypeDef *hi2c)
{
    uint32_t tickStart = systick_get_value();
    uint32_t endTick = tickStart + SYSTICK_MS2TICKS(HAL_I2C_POLL_TIMEOUT_MS);
    uint8_t isRewind = false;
    if (tickStart > endTick) {
        isRewind = true;
    }
    while(hi2c->Tx_Env.XferCount)
    {
        if(hi2c->Instance->RIF&I2C_INT_NACK_MASK)
        {
            hi2c->Instance->ICR = I2C_INT_NACK_MASK;
            return HAL_ERROR;
        }else
        {

            while((hi2c->Instance->SR&I2C_INT_TXE_MASK)==0) {
                if (i2c_isTime0Big(systick_get_value(), endTick, isRewind) == true) {
                    return HAL_TIMEOUT;
                }
            };
            i2c_tx_byte(hi2c);
            endTick += SYSTICK_MS2TICKS(HAL_I2C_POLL_TIMEOUT_MS);
        }
        if (i2c_isTime0Big(systick_get_value(), endTick, isRewind) == true) {
            return HAL_TIMEOUT;
        }
    }
    return HAL_OK;
}

static HAL_StatusTypeDef wait_for_tc_stop(I2C_HandleTypeDef *hi2c)
{
    uint32_t tickStart = systick_get_value();
    uint32_t endTick = tickStart + SYSTICK_MS2TICKS(HAL_I2C_POLL_TIMEOUT_MS);
    uint8_t isRewind = false;
    if (tickStart > endTick) {
        isRewind = true;
    }
    while ((hi2c->Instance->RIF&(I2C_INT_TC_MASK | I2C_INT_TCR_MASK))==0) {
        if (i2c_isTime0Big(systick_get_value(), endTick, isRewind) == true) {
            return HAL_TIMEOUT;
        }
    };
    hi2c->Instance->ICR = I2C_INT_TC_MASK|I2C_INT_TCR_MASK;
    hi2c->Instance->CR2_0_1 |= I2C_CR2_STOP_MASK;
    endTick += SYSTICK_MS2TICKS(HAL_I2C_POLL_TIMEOUT_MS);
    while ((hi2c->Instance->RIF & I2C_INT_STOP_MASK) == 0) {
        if (i2c_isTime0Big(systick_get_value(), endTick, isRewind) == true) {
            LOG_RAW("timerout\r\n");
            return HAL_TIMEOUT;
        }
    }
    hi2c->Instance->ICR = I2C_INT_STOP_MASK;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint8_t Size)
{
    hi2c->Tx_Env.pBuffPtr = pData;
    hi2c->Tx_Env.XferCount = Size;
    i2c_master_start(hi2c, DevAddress, Size, false);
    HAL_StatusTypeDef status = i2c_tx_polling(hi2c);
    if(status != HAL_OK)
    {
        HAL_I2C_Enable_Rstart(hi2c);
        return status;
    }
    status = wait_for_tc_stop(hi2c);
    if(status != HAL_OK)
    {
        HAL_I2C_Enable_Rstart(hi2c);
        return status;
    }
    return HAL_OK;
}

static HAL_StatusTypeDef i2c_rx_polling(I2C_HandleTypeDef *hi2c)
{
    uint32_t tickStart = systick_get_value();
    uint32_t endTick = tickStart + SYSTICK_MS2TICKS(HAL_I2C_POLL_TIMEOUT_MS);
    uint8_t isRewind = false;
    if (tickStart > endTick) {
        isRewind = true;
    }
    while(hi2c->Rx_Env.XferCount)
    {
        if (hi2c->Instance->RIF&I2C_INT_NACK_MASK)
        {
            hi2c->Instance->ICR = I2C_INT_NACK_MASK;
            return HAL_ERROR;
        } else {
            hi2c->Instance->ICR = I2C_INT_RXNE_MASK;
            while((hi2c->Instance->RIF&I2C_INT_RXNE_MASK)==0) {
                if (i2c_isTime0Big(systick_get_value(), endTick, isRewind) == true) {
                    return HAL_TIMEOUT;
                }
            }
            *hi2c->Rx_Env.pBuffPtr++ = hi2c->Instance->RXDR;
            hi2c->Rx_Env.XferCount--;
        }
        endTick += SYSTICK_MS2TICKS(HAL_I2C_POLL_TIMEOUT_MS);
        if (i2c_isTime0Big(systick_get_value(), endTick, isRewind) == true) {
            return HAL_TIMEOUT;
        }
    }
    return HAL_OK;
}

HAL_StatusTypeDef HAL_I2C_Master_Receive(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint8_t Size)
{
    hi2c->Rx_Env.pBuffPtr = pData;
    hi2c->Rx_Env.XferCount = Size;
    i2c_master_start(hi2c,DevAddress,Size,true);
    HAL_StatusTypeDef status = i2c_rx_polling(hi2c);
    if(status != HAL_OK)
    {
        HAL_I2C_Enable_Rstart(hi2c);
        return status;
    }
    status = wait_for_tc_stop(hi2c);
    if(status != HAL_OK)
    {
        HAL_I2C_Enable_Rstart(hi2c);
        return status;
    }
    return HAL_OK;
}

static void i2c_mem_start(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress,uint16_t MemAddSize)
{
    i2c_master_start(hi2c,DevAddress,MemAddSize,false);
    if(MemAddSize==2)
    {
        hi2c->Instance->TXDR = MemAddress>>8;
    }
    hi2c->Instance->TXDR = MemAddress&0xff;
}

static void restart_transfer(I2C_HandleTypeDef *hi2c,bool tx)
{
    hi2c->Instance->CR2_3 &= ~I2C_CR2_RELOAD_MASK;
    hi2c->Instance->CR2_2 = tx?hi2c->Tx_Env.XferCount:hi2c->Rx_Env.XferCount;
    if(tx)
    {
        MODIFY_REG(hi2c->Instance->CR2_0_1,I2C_CR2_RD_WEN_MASK,I2C_CR2_START_MASK);
    }else
    {
        MODIFY_REG(hi2c->Instance->CR2_0_1,0,I2C_CR2_RD_WEN_MASK|I2C_CR2_START_MASK);
    }
}

static HAL_StatusTypeDef wait_before_restart(I2C_HandleTypeDef *hi2c)
{
    uint32_t tickStart = systick_get_value();
    uint32_t endTick = tickStart + SYSTICK_MS2TICKS(HAL_I2C_POLL_TIMEOUT_MS);
    uint8_t isRewind = false;
    if (tickStart > endTick) {
        isRewind = true;
    }
    while (1) {
        if (hi2c->Instance->RIF & I2C_INT_NACK_MASK) {
            hi2c->Instance->ICR = I2C_INT_NACK_MASK;
            return HAL_ERROR;
        }
        if(hi2c->Instance->RIF & (I2C_INT_TCR_MASK | I2C_INT_TC_MASK)) {
            return HAL_OK;
        }
        
        if (i2c_isTime0Big(systick_get_value(), endTick, isRewind) == true) {
            return HAL_TIMEOUT;
        }
    }
    

    return HAL_OK;
}

HAL_StatusTypeDef HAL_I2C_Mem_Read(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress,uint16_t MemAddSize, uint8_t *pData, uint16_t Size)
{
    hi2c->Rx_Env.pBuffPtr = pData;
    hi2c->Rx_Env.XferCount = Size;

    i2c_mem_start(hi2c,DevAddress,MemAddress,MemAddSize);

    HAL_StatusTypeDef status = wait_before_restart(hi2c);
    if(status != HAL_OK)
    {
        return status;
    }

    restart_transfer(hi2c,false);

    status = i2c_rx_polling(hi2c);
    if(status != HAL_OK)
    {
        return status;
    }

    status = wait_for_tc_stop(hi2c);
    if(status != HAL_OK)
    {
        return status;
    }
    return HAL_OK;
}

HAL_StatusTypeDef HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress,uint16_t MemAddSize, uint8_t *pData, uint16_t Size)
{
    hi2c->Tx_Env.pBuffPtr = pData;
    hi2c->Tx_Env.XferCount = Size;
    i2c_mem_start(hi2c,DevAddress,MemAddress,MemAddSize);

    HAL_StatusTypeDef status = wait_before_restart(hi2c);
    if(status != HAL_OK)
    {
        return status;
    }

    restart_transfer(hi2c,true);

    status = i2c_tx_polling(hi2c);
    if(status != HAL_OK)
    {
        return status;
    }
    status = wait_for_tc_stop(hi2c);
    if(status != HAL_OK)
    {
        return status;
    }
    return HAL_OK;
}

HAL_StatusTypeDef HAL_I2C_Master_Transmit_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint8_t Size)
{
    LS_ASSERT(hi2c->State == 0);
    hi2c->Tx_Env.pBuffPtr = pData;
    hi2c->Tx_Env.XferCount = Size;
    hi2c->State = HAL_I2C_STATE_BUSY_TX;
    i2c_master_start(hi2c,DevAddress,Size,false);
    #ifdef LE501X
    i2c_tx_byte(hi2c);
    #endif
    hi2c->Instance->IER = I2C_INT_TXE_MASK|I2C_INT_NACK_MASK|I2C_INT_STOP_MASK;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_I2C_Master_Receive_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint8_t Size)
{
    LS_ASSERT(hi2c->State == 0);
    hi2c->Rx_Env.pBuffPtr = pData;
    hi2c->Rx_Env.XferCount = Size;
    hi2c->State = HAL_I2C_STATE_BUSY_RX;
    i2c_master_start(hi2c,DevAddress,Size,true);
    hi2c->Instance->IER = I2C_INT_RXNE_MASK|I2C_INT_NACK_MASK|I2C_INT_STOP_MASK;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_I2C_Mem_Read_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress,uint16_t MemAddSize, uint8_t *pData, uint16_t Size)
{
    LS_ASSERT(hi2c->State == 0);
    hi2c->Rx_Env.pBuffPtr = pData;
    hi2c->Rx_Env.XferCount = Size;
    hi2c->State = HAL_I2C_STATE_NEED_RESTART | HAL_I2C_STATE_BUSY_RX;
    i2c_mem_start(hi2c,DevAddress,MemAddress,MemAddSize);
    hi2c->Instance->IER = I2C_INT_TC_MASK |I2C_INT_NACK_MASK|I2C_INT_STOP_MASK;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_I2C_Mem_Write_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress,uint16_t MemAddSize, uint8_t *pData, uint16_t Size)
{
    LS_ASSERT(hi2c->State == 0);
    hi2c->Tx_Env.pBuffPtr = pData;
    hi2c->Tx_Env.XferCount = Size;
    hi2c->State = HAL_I2C_STATE_NEED_RESTART | HAL_I2C_STATE_BUSY_TX;
    i2c_mem_start(hi2c,DevAddress,MemAddress,MemAddSize);
    hi2c->Instance->IER = I2C_INT_TC_MASK |I2C_INT_NACK_MASK|I2C_INT_STOP_MASK;
    return HAL_OK;
}

static void i2c_slave_addr_reenable(I2C_HandleTypeDef *hi2c)
{
    uint32_t oar1 = hi2c->Instance->OAR1;
    uint32_t oar2 = hi2c->Instance->OAR2;
    hi2c->Instance->OAR1 = oar1 & ~I2C_OAR1_OA1EN_MASK;
    hi2c->Instance->OAR2 = oar2 & ~I2C_OAR2_OA2EN_MASK;
    hi2c->Instance->OAR1 = oar1;
    hi2c->Instance->OAR2 = oar2;
}

__attribute__((weak)) void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c){}

__attribute__((weak)) void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c){}

__attribute__((weak)) void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *hi2c){}

__attribute__((weak)) void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c){}

__attribute__((weak)) void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode){}

__attribute__((weak)) void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c,uint8_t error){}

void HAL_I2C_IRQHandler(I2C_HandleTypeDef *hi2c)
{
    uint32_t irq = hi2c->Instance->IFM;
    uint32_t status = hi2c->Instance->SR;
    if(irq&I2C_INT_TXE_MASK)
    {
        if(hi2c->Tx_Env.XferCount)
        {
            i2c_tx_byte(hi2c);
        }
        hi2c->Instance->ICR = I2C_INT_TXE_MASK;
        if(hi2c->Tx_Env.XferCount == 0) {
            hi2c->Instance->IDR = I2C_INT_TXE_MASK;
            if(hi2c->State & HAL_I2C_STATE_LISTEN) {
                hi2c->State &= ~HAL_I2C_STATE_BUSY_TX;
                HAL_I2C_SlaveTxCpltCallback(hi2c);
            } else {
                hi2c->Instance->IER = I2C_INT_TC_MASK|I2C_INT_TCR_MASK;
            }
        }
    }
    if(irq&I2C_INT_RXNE_MASK)
    {
        i2c_slave_addr_reenable(hi2c);
        if(hi2c->Rx_Env.XferCount == 0)
        {
            hi2c->Instance->RXDR;
            hi2c->Instance->ICR = I2C_INT_RXNE_MASK;
        }else
        {
            hi2c->Rx_Env.XferCount--;
            LS_ASSERT(hi2c->Rx_Env.pBuffPtr);
            *hi2c->Rx_Env.pBuffPtr++ = hi2c->Instance->RXDR;
            hi2c->Instance->ICR = I2C_INT_RXNE_MASK;
            if(hi2c->State & HAL_I2C_STATE_LISTEN)
            {
                hi2c->Instance->CR2_2 = 1;
                if(hi2c->Rx_Env.XferCount == 0)
                {
                    hi2c->State &= ~HAL_I2C_STATE_BUSY_RX;
                    HAL_I2C_SlaveRxCpltCallback(hi2c);
                }else if(hi2c->Rx_Env.XferCount == 1)
                {
                    DELAY_US(10);
                    hi2c->Instance->CR2_0_1 |= I2C_CR2_NACK_MASK;
                }
            }else
            {
                if(hi2c->Rx_Env.XferCount == 0)
                {
                    hi2c->Instance->IDR = I2C_INT_RXNE_MASK;
                    hi2c->Instance->IER = I2C_INT_TC_MASK|I2C_INT_TCR_MASK;
                }
            }
        }
    }

    if(irq&I2C_INT_ADDR_MASK)
    {
        hi2c->Instance->ICR = I2C_INT_ADDR_MASK;
        hi2c->Instance->CFR = I2C_CFR_ADDRCF_MASK;
        hi2c->State &= ~(HAL_I2C_STATE_BUSY_RX | HAL_I2C_STATE_BUSY_TX);
        HAL_I2C_AddrCallback(hi2c,(status&I2C_SR_DIR_MASK)>>I2C_SR_DIR_POS,(status&I2C_SR_ADDCODE_MASK)>>I2C_SR_ADDCODE_POS);
    }
    if(irq&I2C_INT_NACK_MASK)
    {
        hi2c->Instance->ICR = I2C_INT_NACK_MASK;
        hi2c->Instance->IDR = I2C_INT_TXE_MASK|I2C_INT_RXNE_MASK|I2C_INT_NACK_MASK|I2C_INT_TC_MASK|I2C_INT_TCR_MASK;
        HAL_I2C_ErrorCallback(hi2c,HAL_I2C_ERROR_NACKF);
    }
    if(irq&I2C_INT_STOP_MASK)
    {
        hi2c->Instance->ICR = I2C_INT_STOP_MASK;
        hi2c->Instance->CFR = I2C_CFR_STOPCF_MASK;

        i2c_clr_tx_fifo(hi2c);
        if(hi2c->State&HAL_I2C_STATE_LISTEN) {
            hi2c->Instance->IDR = I2C_INT_TXE_MASK | I2C_INT_RXNE_MASK;
            #if defined(LE501X)||defined(LM3050)
            HAL_I2C_Init(hi2c);
            hi2c->State = 0;
            HAL_I2C_EnableListen_IT(hi2c);
            #endif
            if(hi2c->Tx_Env.XferCount||hi2c->Rx_Env.XferCount)
            {
                hi2c->State &= ~(HAL_I2C_STATE_BUSY_RX|HAL_I2C_STATE_BUSY_TX);
                HAL_I2C_ErrorCallback(hi2c,HAL_I2C_ERROR_SIZE);
            }
        }else
        {
            if(hi2c->State&HAL_I2C_STATE_BUSY_TX)
            {
                hi2c->State &= ~HAL_I2C_STATE_BUSY_TX;
                HAL_I2C_MasterTxCpltCallback(hi2c);
            }else
            {
                hi2c->State &= ~HAL_I2C_STATE_BUSY_RX;
                HAL_I2C_MasterRxCpltCallback(hi2c);
            }
        }
    }
    if(irq&I2C_INT_TC_MASK)
    {
        hi2c->Instance->ICR = I2C_INT_TC_MASK;
        hi2c->Instance->IDR = I2C_INT_TC_MASK|I2C_INT_TCR_MASK;
        if(hi2c->State & HAL_I2C_STATE_NEED_RESTART)
        {
            hi2c->State &= ~HAL_I2C_STATE_NEED_RESTART;
            if(hi2c->State&HAL_I2C_STATE_BUSY_TX)
            {
                LS_ASSERT(hi2c->Tx_Env.XferCount);
                restart_transfer(hi2c,true);
                hi2c->Instance->IER = I2C_INT_TXE_MASK;
            }else
            {
                LS_ASSERT(hi2c->Rx_Env.XferCount);
                restart_transfer(hi2c,false);
                hi2c->Instance->IER = I2C_INT_RXNE_MASK;
            }
        }else
        {
            hi2c->Instance->CR2_0_1 |= I2C_CR2_STOP_MASK;
        }
    }
    if(irq&I2C_INT_TCR_MASK)
    {
        LS_ASSERT(0);
    }
    if(irq&I2C_INT_BERR_MASK)
    {
        LS_ASSERT(0);
    }
    if(irq&I2C_INT_ARLO_MASK)
    {
        LS_ASSERT(0);
    }
    if(irq&I2C_INT_OVR_MASK)
    {
        LS_ASSERT(0);
    }
    if(irq&I2C_INT_PECE_MASK)
    {
        LS_ASSERT(0);

    }
    if(irq&I2C_INT_TOUT_MASK)
    {
        LS_ASSERT(0);

    }
    if(irq&I2C_INT_ALERT_MASK)
    {
        LS_ASSERT(0);

    }
}
