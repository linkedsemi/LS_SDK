#include "ls_hal_i2c.h"

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
    hi2c->Instance->CFR = 0xffff;
    hi2c->Instance->CR1 |= I2C_CR1_PE_MASK;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_I2C_DeInit(I2C_HandleTypeDef *hi2c)
{
    HAL_I2C_MSP_DeInit(hi2c);
    HAL_I2C_MSP_Idle_Set(hi2c);
    return HAL_OK;
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
    hi2c->Instance->IER = I2C_IER_ADDRIE_MASK|I2C_IER_STOPIE_MASK;
    return HAL_OK;

}

HAL_StatusTypeDef HAL_I2C_DisableListen_IT(I2C_HandleTypeDef *hi2c)
{
    hi2c->Instance->OAR1 = 0;
    hi2c->Instance->OAR2 = 0;
    hi2c->Instance->IDR = I2C_IDR_ADDRID_MASK|I2C_IDR_STOPID_MASK|I2C_IDR_TXEID_MASK|I2C_IDR_RXNEID_MASK;
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
    hi2c->Tx_Env.pBuffPtr = pData;
    hi2c->Tx_Env.XferCount = Size;
    hi2c->State |= HAL_I2C_STATE_BUSY_TX;
    hi2c->Instance->ICR = I2C_ICR_TXEIC_MASK;
    i2c_tx_byte(hi2c);
    hi2c->Instance->IER = I2C_IER_TXEIE_MASK;
    return HAL_OK;

}

HAL_StatusTypeDef HAL_I2C_Slave_Seq_Receive_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size)
{
    LS_ASSERT(hi2c->State == HAL_I2C_STATE_LISTEN);
    hi2c->Rx_Env.pBuffPtr = pData;
    hi2c->Rx_Env.XferCount = Size;
    hi2c->State |= HAL_I2C_STATE_BUSY_RX;
    hi2c->Instance->ICR = I2C_ICR_RXNEIC_MASK;
    hi2c->Instance->IER = I2C_IER_RXNEIE_MASK;
    return HAL_OK;

}

static void i2c_master_start(I2C_HandleTypeDef *hi2c,uint16_t DevAddress,uint8_t Size,bool read,bool reload)
{
    if(reload)
    {
        hi2c->Instance->CR2_3 |= I2C_CR2_RELOAD_MASK;
    }else
    {
        hi2c->Instance->CR2_3 &= ~I2C_CR2_RELOAD_MASK;
    }
    hi2c->Instance->CR2_2 = Size;
    if(read)
    {
        hi2c->Instance->CR2_0_1 = DevAddress<<I2C_CR2_SADD1_7_POS | I2C_CR2_START_MASK | I2C_CR2_RD_WEN_MASK;
    }else
    {
        hi2c->Instance->CR2_0_1 = DevAddress<<I2C_CR2_SADD1_7_POS | I2C_CR2_START_MASK;
    }
}

static bool i2c_tx_polling(I2C_HandleTypeDef *hi2c)
{
    while(hi2c->Tx_Env.XferCount)
    {
        if(hi2c->Instance->RIF&I2C_RIF_NACKRI_MASK)
        {
            hi2c->Instance->ICR = I2C_ICR_NACKIC_MASK;
            return false;
        }else
        {
            while((hi2c->Instance->RIF&I2C_RIF_TXERI_MASK)==0);
            i2c_tx_byte(hi2c);
        }
    }
    return true;
}

static void wait_for_tc(I2C_HandleTypeDef *hi2c)
{
    while((hi2c->Instance->RIF&I2C_RIF_TCRI_MASK)==0);
    hi2c->Instance->ICR = I2C_ICR_TCIC_MASK;
}

HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint8_t Size)
{
    hi2c->Tx_Env.pBuffPtr = pData;
    hi2c->Tx_Env.XferCount = Size;
    i2c_master_start(hi2c,DevAddress,Size,false,false);
    if(i2c_tx_polling(hi2c)==false)
    {
        return HAL_ERROR;
    }
    wait_for_tc(hi2c);
    return HAL_OK;
}

static bool i2c_rx_polling(I2C_HandleTypeDef *hi2c)
{
    while(hi2c->Rx_Env.XferCount)
    {
        if(hi2c->Instance->RIF&I2C_RIF_NACKRI_MASK)
        {
            hi2c->Instance->ICR = I2C_ICR_NACKIC_MASK;
            return false;
        }else
        {
            while((hi2c->Instance->RIF&I2C_RIF_RXNERI_MASK)==0);
            *hi2c->Rx_Env.pBuffPtr++ = hi2c->Instance->RXDR;
            hi2c->Rx_Env.XferCount--;
        }
    }
    return true;
}

HAL_StatusTypeDef HAL_I2C_Master_Receive(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint8_t Size)
{
    hi2c->Rx_Env.pBuffPtr = pData;
    hi2c->Rx_Env.XferCount = Size;
    i2c_master_start(hi2c,DevAddress,Size,true,false);
    if(i2c_rx_polling(hi2c)==false)
    {
        return HAL_ERROR;
    }
    wait_for_tc(hi2c);
    return HAL_OK;
}

static void i2c_mem_start(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress,uint16_t MemAddSize)
{
    i2c_master_start(hi2c,DevAddress,MemAddSize,false,true);
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

static void wait_for_tcr(I2C_HandleTypeDef *hi2c)
{
    while((hi2c->Instance->RIF&I2C_RIF_TCRRI_MASK)==0);
    hi2c->Instance->ICR = I2C_ICR_TCRIC_MASK;
}

static bool wait_before_restart(I2C_HandleTypeDef *hi2c)
{
    while(1)
    {
        if(hi2c->Instance->RIF&I2C_RIF_NACKRI_MASK)
        {
            hi2c->Instance->ICR = I2C_ICR_NACKIC_MASK;
            return false;
        }
        if(hi2c->Instance->RIF&I2C_RIF_TCRRI_MASK)
        {
            break;
        }
    }
    return true;
}

HAL_StatusTypeDef HAL_I2C_Mem_Read(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress,uint16_t MemAddSize, uint8_t *pData, uint16_t Size)
{
    hi2c->Rx_Env.pBuffPtr = pData;
    hi2c->Rx_Env.XferCount = Size;
    i2c_mem_start(hi2c,DevAddress,MemAddress,MemAddSize);
    if(wait_before_restart(hi2c)==false)
    {
        return HAL_ERROR;
    }
    restart_transfer(hi2c,false);
    if(i2c_rx_polling(hi2c)==false)
    {
        return HAL_ERROR;
    }
    wait_for_tcr(hi2c);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress,uint16_t MemAddSize, uint8_t *pData, uint16_t Size)
{
    hi2c->Tx_Env.pBuffPtr = pData;
    hi2c->Tx_Env.XferCount = Size;
    i2c_mem_start(hi2c,DevAddress,MemAddress,MemAddSize);
    if(wait_before_restart(hi2c)==false)
    {
        return HAL_ERROR;
    }
    restart_transfer(hi2c,true);
    if(i2c_tx_polling(hi2c)==false)
    {
        return HAL_ERROR;
    }
    wait_for_tcr(hi2c);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_I2C_Master_Transmit_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint8_t Size)
{
    LS_ASSERT(hi2c->State == 0);
    hi2c->Tx_Env.pBuffPtr = pData;
    hi2c->Tx_Env.XferCount = Size;
    hi2c->State = HAL_I2C_STATE_BUSY_TX;
    i2c_master_start(hi2c,DevAddress,Size,false,false);
    #ifdef LE501X
    i2c_tx_byte(hi2c);
    #endif
    hi2c->Instance->IER = I2C_IER_TXEIE_MASK|I2C_IER_NACKIE_MASK|I2C_IER_STOPIE_MASK;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_I2C_Master_Receive_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint8_t Size)
{
    LS_ASSERT(hi2c->State == 0);
    hi2c->Rx_Env.pBuffPtr = pData;
    hi2c->Rx_Env.XferCount = Size;
    hi2c->State = HAL_I2C_STATE_BUSY_RX;
    i2c_master_start(hi2c,DevAddress,Size,true,false);
    hi2c->Instance->IER = I2C_IER_RXNEIE_MASK|I2C_IER_NACKIE_MASK|I2C_IER_STOPIE_MASK;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_I2C_Mem_Read_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress,uint16_t MemAddSize, uint8_t *pData, uint16_t Size)
{
    LS_ASSERT(hi2c->State == 0);
    hi2c->Rx_Env.pBuffPtr = pData;
    hi2c->Rx_Env.XferCount = Size;
    hi2c->State = HAL_I2C_STATE_BUSY_RX;
    i2c_mem_start(hi2c,DevAddress,MemAddress,MemAddSize);
    hi2c->Instance->IER = I2C_IER_TCRIE_MASK |I2C_IER_NACKIE_MASK|I2C_IER_STOPIE_MASK;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_I2C_Mem_Write_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress,uint16_t MemAddSize, uint8_t *pData, uint16_t Size)
{
    LS_ASSERT(hi2c->State == 0);
    hi2c->Tx_Env.pBuffPtr = pData;
    hi2c->Tx_Env.XferCount = Size;
    hi2c->State = HAL_I2C_STATE_BUSY_TX;
    i2c_mem_start(hi2c,DevAddress,MemAddress,MemAddSize);
    hi2c->Instance->IER = I2C_IER_TCRIE_MASK |I2C_IER_NACKIE_MASK|I2C_IER_STOPIE_MASK;
    return HAL_OK;
}

static inline void i2c_clr_tx_fifo(I2C_HandleTypeDef *hi2c)
{
    hi2c->Instance->SR = 1;
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
    if(irq&I2C_IFM_TXEFM_MASK)
    {
        if(hi2c->Tx_Env.XferCount)
        {
            i2c_tx_byte(hi2c);
        }
        hi2c->Instance->ICR = I2C_ICR_TXEIC_MASK;
        if(hi2c->Tx_Env.XferCount == 0)
        {
            hi2c->Instance->IDR = I2C_IDR_TXEID_MASK;
            if(hi2c->State & HAL_I2C_STATE_LISTEN)
            {
                hi2c->State &= ~HAL_I2C_STATE_BUSY_TX;
                HAL_I2C_SlaveTxCpltCallback(hi2c);
            }else
            {
			    hi2c->Instance->IER = I2C_IER_TCIE_MASK|I2C_IER_TCRIE_MASK;
            }
        }
    }
    if(irq&I2C_IFM_RXNEFM_MASK)
    {
        i2c_slave_addr_reenable(hi2c);
        if(hi2c->Rx_Env.XferCount--)
        {
            LS_ASSERT(hi2c->Rx_Env.pBuffPtr);
            *hi2c->Rx_Env.pBuffPtr++ = hi2c->Instance->RXDR;
        }
        hi2c->Instance->ICR = I2C_ICR_RXNEIC_MASK;
        if(hi2c->Rx_Env.XferCount == 0)
        {
            hi2c->Instance->IDR = I2C_IDR_RXNEID_MASK;
            if(hi2c->State & HAL_I2C_STATE_LISTEN)
            {
                hi2c->State &= ~HAL_I2C_STATE_BUSY_RX;
                HAL_I2C_SlaveRxCpltCallback(hi2c);
            }else
            {
			    hi2c->Instance->IER = I2C_IER_TCIE_MASK|I2C_IER_TCRIE_MASK;
            }
        }
    }
    if(irq&I2C_IFM_ADDRFM_MASK)
    {
        hi2c->Instance->ICR = I2C_ICR_ADDRIC_MASK;
        hi2c->Instance->CFR = I2C_CFR_ADDRCF_MASK;
        HAL_I2C_AddrCallback(hi2c,(status&I2C_SR_DIR_MASK)>>I2C_SR_DIR_POS,(status&I2C_SR_ADDCODE_MASK)>>I2C_SR_ADDCODE_POS);
    }
    if(irq&I2C_IFM_NACKFM_MASK)
    {
        hi2c->Instance->ICR = I2C_ICR_NACKIC_MASK;
        hi2c->Instance->IDR = I2C_IDR_TXEID_MASK|I2C_IDR_RXNEID_MASK|I2C_IDR_NACKID_MASK|I2C_IDR_TCID_MASK|I2C_IDR_TCRID_MASK;
        HAL_I2C_ErrorCallback(hi2c,HAL_I2C_ERROR_NACKF);
    }
    if(irq&I2C_IFM_STOPFM_MASK)
    {
        hi2c->Instance->ICR = I2C_ICR_STOPIC_MASK;
        hi2c->Instance->CFR = I2C_CFR_STOPCF_MASK;
        i2c_clr_tx_fifo(hi2c);
        if(hi2c->State&HAL_I2C_STATE_LISTEN)
        {
            if(hi2c->Tx_Env.XferCount||hi2c->Rx_Env.XferCount)
            {
                hi2c->Instance->IDR = I2C_IDR_TXEID_MASK | I2C_IDR_RXNEID_MASK;
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
    if(irq&I2C_IFM_TCFM_MASK)
    {
        hi2c->Instance->ICR = I2C_ICR_TCIC_MASK;
        hi2c->Instance->IDR = I2C_IDR_TCID_MASK|I2C_IDR_TCRID_MASK;
        hi2c->Instance->CR2_0_1 |= I2C_CR2_STOP_MASK;
    }
    if(irq&I2C_IFM_TCRFM_MASK)
    {
        hi2c->Instance->ICR = I2C_ICR_TCRIC_MASK;
        hi2c->Instance->IDR = I2C_IDR_TCID_MASK|I2C_IDR_TCRID_MASK;
        if(hi2c->State&HAL_I2C_STATE_BUSY_TX)
        {
            LS_ASSERT(hi2c->Tx_Env.XferCount);
            restart_transfer(hi2c,true);
            hi2c->Instance->IER = I2C_IER_TXEIE_MASK;
        }else
        {
            LS_ASSERT(hi2c->Rx_Env.XferCount);
            restart_transfer(hi2c,false);
            hi2c->Instance->IER = I2C_IER_RXNEIE_MASK;
        }
    }
    if(irq&I2C_IFM_BERRFM_MASK)
    {
        LS_ASSERT(0);
    }
    if(irq&I2C_IFM_ARLOFM_MASK)
    {
        LS_ASSERT(0);
    }
    if(irq&I2C_IFM_OVRFM_MASK)
    {
        LS_ASSERT(0);
    }
    if(irq&I2C_IFM_PECEFM_MASK)
    {
        LS_ASSERT(0);

    }
    if(irq&I2C_IFM_TOUTFM_MASK)
    {
        LS_ASSERT(0);

    }
    if(irq&I2C_IFM_ALERTFM_MASK)
    {
        LS_ASSERT(0);

    }
}
