/* Includes ------------------------------------------------------------------*/
#include "ls_hal_spi_i2s.h"

#define SPI_I2S_TX_FIFO_DEPTH 16
#define SPI_I2S_TX_FIFO_NOT_FULL(__HANDLE__) (REG_FIELD_RD((__HANDLE__)->Instance->SR, SPI_SR_TXFLV) < SPI_I2S_TX_FIFO_DEPTH)
#define SPI_I2S_RX_FIFO_NOT_EMPTY(__HANDLE__) (REG_FIELD_RD((__HANDLE__)->Instance->SR, SPI_SR_RXFLV) > 0)

static void SPI_Tx_ISR(SPI_HandleTypeDef *hspi);
static void SPI_Rx_ISR(SPI_HandleTypeDef *hspi);
static void SPI_Close_ISR(SPI_HandleTypeDef *hspi);

HAL_StatusTypeDef HAL_SPI_Init(SPI_HandleTypeDef *hspi)
{
    HAL_SPI_MSP_Init(hspi);
    HAL_SPI_MSP_Busy_Set(hspi);  
    CLEAR_BIT(hspi->Instance->CR1, SPI_CR1_SPE_MASK);

    /*----------------------- SPIx CR1 & CR2 Configuration ---------------------*/
    MODIFY_REG(hspi->Instance->CR1, 
               (SPI_CR1_MSTR_MASK | SPI_CR1_CPOL_MASK | SPI_CR1_CPHA_MASK | SPI_CR1_BR_MASK | SPI_CR1_BIDIMODE_MASK | SPI_CR1_LSBFIRST_MASK), 
               (hspi->Init.Mode | hspi->Init.CLKPolarity | hspi->Init.CLKPhase | hspi->Init.BaudRatePrescaler | hspi->Init.FirstBit));
   
    WRITE_REG(hspi->Instance->CR2, (hspi->Init.DataSize & SPI_CR2_DS_MASK) | SPI_CR2_SSOE_MASK);
    REG_FIELD_WR(hspi->Instance->CR2,SPI_CR2_TXFTH,4);
    hspi->Instance->IER = SPI_IT_ERR;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_SPI_DeInit(SPI_HandleTypeDef *hspi)
{
    CLEAR_BIT(hspi->Instance->CR1, SPI_CR1_SPE_MASK);
    HAL_SPI_MSP_DeInit(hspi);
    HAL_SPI_MSP_Idle_Set(hspi);
    return HAL_OK;
}

static void tx_para_init(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint16_t Size)
{
    hspi->Tx_Env.Interrupt.pBuffPtr = (uint8_t *)pTxData;
    hspi->Tx_Env.Interrupt.Count = Size;
}

static void rx_para_init(SPI_HandleTypeDef *hspi, uint8_t *pRxData,uint16_t Size)
{
    hspi->Rx_Env.Interrupt.pBuffPtr = (uint8_t *)pRxData;
    hspi->Rx_Env.Interrupt.Count = Size;
}

static void spi_tx_load_data_8bit(SPI_HandleTypeDef *hspi)
{
    *((uint8_t *)&hspi->Instance->DR) = *((uint8_t *)hspi->Tx_Env.Interrupt.pBuffPtr);
    hspi->Tx_Env.Interrupt.pBuffPtr += sizeof(uint8_t);
    hspi->Tx_Env.Interrupt.Count--;
}

static void spi_tx_load_data_16bit(SPI_HandleTypeDef *hspi)
{
    hspi->Instance->DR = hspi->Tx_Env.Interrupt.pBuffPtr[1]<<8|hspi->Tx_Env.Interrupt.pBuffPtr[0];
    hspi->Tx_Env.Interrupt.pBuffPtr += sizeof(uint16_t);
    hspi->Tx_Env.Interrupt.Count--;
}

static void spi_rx_load_data_8bit(SPI_HandleTypeDef *hspi)
{
    *((uint8_t *)hspi->Rx_Env.Interrupt.pBuffPtr) = hspi->Instance->DR;
    hspi->Rx_Env.Interrupt.pBuffPtr += sizeof(uint8_t);
    hspi->Rx_Env.Interrupt.Count--;
}

static void spi_rx_load_data_16bit(SPI_HandleTypeDef *hspi)
{
    *((uint16_t *)hspi->Rx_Env.Interrupt.pBuffPtr) = (uint16_t)hspi->Instance->DR;
    hspi->Rx_Env.Interrupt.pBuffPtr += sizeof(uint16_t);
    hspi->Rx_Env.Interrupt.Count--;
}

#ifdef LE501X
static void le501x_rx_load_data_16bit(SPI_HandleTypeDef *hspi)
{
    uint16_t rx = hspi->Instance->DR;
    hspi->Rx_Env.Interrupt.pBuffPtr[0] = rx;
    hspi->Rx_Env.Interrupt.pBuffPtr[1] = rx>>8;
    hspi->Rx_Env.Interrupt.pBuffPtr += sizeof(uint16_t); 
    hspi->Rx_Env.Interrupt.Count -= sizeof(uint16_t);
}

static void le501x_8bit_packing_mode_handle(SPI_HandleTypeDef *hspi)
{
    uint8_t i = REG_FIELD_RD(hspi->Instance->SR, SPI_SR_RXFLV)/2;
    while (i--)
    {
        le501x_rx_load_data_16bit(hspi);
    }
    if ((hspi->Rx_Env.Interrupt.Count == 1U) && (SPI_I2S_RX_FIFO_NOT_EMPTY(hspi)))
    {
        spi_rx_load_data_8bit(hspi);
    }
}

static void le501x_8bit_load_rx_dummy_data(SPI_HandleTypeDef *hspi)
{
    uint8_t i = REG_FIELD_RD(hspi->Instance->SR, SPI_SR_RXFLV)/2;
    while (i--)
    {
        hspi->Instance->DR;
        hspi->Rx_Env.Interrupt.Count -= sizeof(uint16_t);
    }
    if(hspi->Rx_Env.Interrupt.Count == 1U)
    {
        hspi->Instance->DR;
        hspi->Rx_Env.Interrupt.Count--;
    }
}
#endif

static void pre_load_data(SPI_HandleTypeDef *hspi)
{
    uint8_t i = hspi->Tx_Env.Interrupt.Count > SPI_I2S_TX_FIFO_DEPTH? SPI_I2S_TX_FIFO_DEPTH: hspi->Tx_Env.Interrupt.Count;
    while(i--)
    {
        hspi->Tx_Env.Interrupt.transfer_Fun(hspi);
    }
}

static void spi_disable(SPI_HandleTypeDef *hspi)
{
    while (REG_FIELD_RD(hspi->Instance->SR,SPI_SR_BSY) == 1U);
    CLEAR_BIT(hspi->Instance->CR1, SPI_CR1_SPE_MASK);
}

static void load_tx_dummy_data(SPI_HandleTypeDef *hspi)
{
    *((uint8_t *)&hspi->Instance->DR) = 0;
    hspi->Tx_Env.Interrupt.Count--;
}

static void load_rx_dummy_data(SPI_HandleTypeDef *hspi)
{
    hspi->Instance->DR;
    hspi->Rx_Env.Interrupt.Count--;
}

static void spi_config(SPI_HandleTypeDef *hspi, bool itmode)
{
    if (hspi->Init.DataSize > SPI_DATASIZE_8BIT)
    {
        hspi->Tx_Env.Interrupt.transfer_Fun = hspi->Tx_Env.Interrupt.pBuffPtr? spi_tx_load_data_16bit: load_tx_dummy_data;
        hspi->Rx_Env.Interrupt.transfer_Fun = hspi->Rx_Env.Interrupt.pBuffPtr? spi_rx_load_data_16bit: load_rx_dummy_data;
    }
    else  // 8 Bit Mode
    {
        hspi->Tx_Env.Interrupt.transfer_Fun = hspi->Tx_Env.Interrupt.pBuffPtr? spi_tx_load_data_8bit: load_tx_dummy_data;
        #ifdef LE501X
        hspi->Rx_Env.Interrupt.transfer_Fun = hspi->Rx_Env.Interrupt.pBuffPtr? le501x_8bit_packing_mode_handle: le501x_8bit_load_rx_dummy_data;
        #else 
        hspi->Rx_Env.Interrupt.transfer_Fun = hspi->Rx_Env.Interrupt.pBuffPtr? spi_rx_load_data_8bit: load_rx_dummy_data;
        #endif
    }
    
    SET_BIT(hspi->Instance->CR1, SPI_CR1_SPE_MASK);
    pre_load_data(hspi);

    if (itmode)
    {
        hspi->Instance->ICR = SPI_IT_TXE | SPI_IT_RXNE;
        hspi->Instance->IER = SPI_IT_TXE | SPI_IT_RXNE;
    }
}

static HAL_StatusTypeDef spi_timeout_handle(SPI_HandleTypeDef *hspi, uint32_t end_tick)
{
    HAL_StatusTypeDef errorcode = HAL_OK;
    if (hspi->Init.Mode == SPI_MODE_SLAVE)
    {
        if (time_diff(systick_get_value(), end_tick) > 0U)
        {
            errorcode = HAL_TIMEOUT;
        }
    }
    return errorcode;
}

static void spi_data_transfer(SPI_HandleTypeDef *hspi, uint32_t end_tick)
{
    while ((hspi->Tx_Env.Interrupt.Count > 0U) || (hspi->Rx_Env.Interrupt.Count > 0U))
    {
        if (SPI_I2S_TX_FIFO_NOT_FULL(hspi) && (hspi->Tx_Env.Interrupt.Count > 0U))
        {
            hspi->Tx_Env.Interrupt.transfer_Fun(hspi);
        }
        if ((SPI_I2S_RX_FIFO_NOT_EMPTY(hspi)) && (hspi->Rx_Env.Interrupt.Count> 0U))
        {
            hspi->Rx_Env.Interrupt.transfer_Fun(hspi);
        }
        spi_timeout_handle(hspi, end_tick);
    }
}

HAL_StatusTypeDef HAL_SPI_Transmit(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint16_t Size, uint32_t Timeout)
{   
    uint32_t tickstart = systick_get_value();
    uint32_t timeout = SYSTICK_MS2TICKS(Timeout);
    uint32_t end_tick = tickstart + timeout;
    CLEAR_BIT(hspi->Instance->CR1, SPI_CR1_RXONLY_MASK);
    tx_para_init(hspi, pTxData, Size);
    rx_para_init(hspi, NULL, Size);
    spi_config(hspi,false);
    spi_data_transfer(hspi, end_tick);
    spi_disable(hspi);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_SPI_Receive(SPI_HandleTypeDef *hspi, uint8_t *pRxData, uint16_t Size, uint32_t Timeout)
{
    uint32_t tickstart = systick_get_value();
    uint32_t timeout = SYSTICK_MS2TICKS(Timeout);
    uint32_t end_tick = tickstart + timeout;
    SET_BIT(hspi->Instance->CR1, SPI_CR1_RXONLY_MASK);
    tx_para_init(hspi, NULL, Size);
    rx_para_init(hspi, pRxData, Size);
    spi_config(hspi,false);
    spi_data_transfer(hspi, end_tick);
    spi_disable(hspi);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_SPI_TransmitReceive(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size, uint32_t Timeout)
{
    uint32_t tickstart = systick_get_value();
    uint32_t timeout = SYSTICK_MS2TICKS(Timeout);
    uint32_t end_tick = tickstart + timeout;
    CLEAR_BIT(hspi->Instance->CR1, SPI_CR1_RXONLY_MASK);
    tx_para_init(hspi, pTxData, Size);
    rx_para_init(hspi, pRxData, Size);
    spi_config(hspi,false);
    spi_data_transfer(hspi, end_tick);
    spi_disable(hspi);
    return HAL_OK;
}

__attribute__((weak)) void HAL_SPI_CpltCallback(SPI_HandleTypeDef *hspi){}

static void SPI_Tx_ISR(SPI_HandleTypeDef *hspi)
{
    while (SPI_I2S_TX_FIFO_NOT_FULL(hspi) && hspi->Tx_Env.Interrupt.Count > 0U)
    {
        hspi->Tx_Env.Interrupt.transfer_Fun(hspi);
    }
    if (hspi->Tx_Env.Interrupt.Count == 0U)
    {
        hspi->Instance->IDR = SPI_IT_TXE;
    }
}

static void SPI_Close_ISR(SPI_HandleTypeDef *hspi)
{
    if(hspi->Rx_Env.Interrupt.Count == 0U)
    {
        hspi->Instance->IDR = SPI_IT_RXNE;
        spi_disable(hspi);
        HAL_SPI_CpltCallback(hspi);
    }
}
#ifdef LE501X
static void SPI_Rx_ISR(SPI_HandleTypeDef *hspi)
{
    hspi->Instance->ICR = SPI_ICR_RXNEIC_MASK;
    hspi->Rx_Env.Interrupt.transfer_Fun(hspi);
    SPI_Close_ISR(hspi);
}
#else
static void SPI_Rx_ISR(SPI_HandleTypeDef *hspi)
{
    uint8_t i = REG_FIELD_RD(hspi->Instance->SR, SPI_SR_RXFLV);
    while (i--)
    {
        hspi->Rx_Env.Interrupt.transfer_Fun(hspi);
    }
    hspi->Instance->ICR = SPI_ICR_RXNEIC_MASK;
    SPI_Close_ISR(hspi);
}
#endif

HAL_StatusTypeDef HAL_SPI_Transmit_IT(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint16_t Size)
{   
    CLEAR_BIT(hspi->Instance->CR1, SPI_CR1_RXONLY_MASK);
    tx_para_init(hspi, pTxData, Size);
    rx_para_init(hspi, NULL, Size);
    spi_config(hspi,true);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_SPI_Receive_IT(SPI_HandleTypeDef *hspi, uint8_t *pRxData, uint16_t Size)
{
    SET_BIT(hspi->Instance->CR1, SPI_CR1_RXONLY_MASK);
    tx_para_init(hspi, NULL, Size);
    rx_para_init(hspi, pRxData, Size);
    spi_config(hspi,true);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_SPI_TransmitReceive_IT(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size)
{
    CLEAR_BIT(hspi->Instance->CR1, SPI_CR1_RXONLY_MASK);
    tx_para_init(hspi, pTxData, Size);
    rx_para_init(hspi, pRxData, Size);
    spi_config(hspi,true);
    return HAL_OK;
}

void HAL_SPI_IRQHandler(SPI_HandleTypeDef *hspi)
{
    /* SPI in mode Receiver ----------------------------------------------------*/
    if (REG_FIELD_RD(hspi->Instance->IFM, SPI_IFM_RXNEFM) == 1U)
    {
        SPI_Rx_ISR(hspi);
    }

    /* SPI in mode Transmitter -------------------------------------------------*/
    if (REG_FIELD_RD(hspi->Instance->IFM, SPI_IFM_TXEFM) == 1U)
    {
        #ifdef LE501X
        hspi->Instance->ICR = SPI_ICR_TXEIC_MASK;
        SPI_Tx_ISR(hspi);
        #else  
        SPI_Tx_ISR(hspi);
        hspi->Instance->ICR = SPI_ICR_TXEIC_MASK;
        #endif /* LE501X */
    }

    /* SPI in Error Treatment --------------------------------------------------*/
    if (REG_FIELD_RD(hspi->Instance->IFM, SPI_IFM_OVRFM) == 1U)
    {
        LOG_I("fifo overrun error");
        LS_ASSERT(0);
    }
    if (REG_FIELD_RD(hspi->Instance->IFM, SPI_IFM_MODFFM) == 1U)
    {
        LOG_I("spi master mode fault");
        LS_ASSERT(0);
    }
    if (REG_FIELD_RD(hspi->Instance->IFM, SPI_IFM_FREFM) == 1U)
    {
        LOG_I("frame format error");
        LS_ASSERT(0);
    }
}

HAL_StatusTypeDef HAL_I2S_Init(I2S_HandleTypeDef *hi2s)
{
    HAL_I2S_MSP_Init(hi2s);
    HAL_I2S_MSP_Busy_Set(hi2s); 
    CLEAR_BIT(hi2s->Instance->I2SCFGR, SPI_I2SCFGR_I2SE_MASK); 

    /*----------------------- SPIx I2SCFGR & I2SPR Configuration ----------------*/
    MODIFY_REG(hi2s->Instance->I2SPR, (SPI_I2SPR_I2SDIV_MASK | SPI_I2SPR_ODD_MASK | SPI_I2SPR_MCKOE_MASK), \
               (hi2s->Init.DivPrescaler | hi2s->Init.OddPrescaler | hi2s->Init.MCLKOutput));

    MODIFY_REG(hi2s->Instance->I2SCFGR, (SPI_I2SCFGR_CHLEN_MASK | SPI_I2SCFGR_DATLEN_MASK | SPI_I2SCFGR_CKPOL_MASK | SPI_I2SCFGR_I2SSTD_MASK | \
                                        SPI_I2SCFGR_PCMSYNC_MASK | SPI_I2SCFGR_I2SCFG_MASK | SPI_I2SCFGR_I2SE_MASK  | SPI_I2SCFGR_I2SMOD_MASK), \
                (SPI_I2SCFGR_I2SMOD_MASK | hi2s->Init.Mode | hi2s->Init.Standard | hi2s->Init.DataFormat | hi2s->Init.CPOL));

    REG_FIELD_WR(hi2s->Instance->CR2,SPI_CR2_TXFTH,4);
    hi2s->Instance->IER = SPI_IT_ERR;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_I2S_DeInit(I2S_HandleTypeDef *hi2s)
{
    CLEAR_BIT(hi2s->Instance->I2SCFGR, SPI_I2SCFGR_I2SE_MASK);  
    HAL_I2S_MSP_DeInit(hi2s);
    HAL_I2S_MSP_Idle_Set(hi2s);
    return HAL_OK;
}

static void i2s_tx_load_data(I2S_HandleTypeDef *hi2s)
{
    hi2s->Instance->DR =*((uint16_t *)hi2s->Tx_Env.Interrupt.pBuffPtr);
    hi2s->Tx_Env.Interrupt.pBuffPtr += sizeof(uint16_t);
    hi2s->Tx_Env.Interrupt.Count--;
}

static void i2s_rx_load_data(I2S_HandleTypeDef *hi2s)
{
    *((uint16_t *)hi2s->Rx_Env.Interrupt.pBuffPtr) = (uint16_t)hi2s->Instance->DR;
    hi2s->Rx_Env.Interrupt.pBuffPtr += sizeof(uint16_t);
    hi2s->Rx_Env.Interrupt.Count--;
}

static HAL_StatusTypeDef i2s_timeout_handle(I2S_HandleTypeDef *hi2s, uint32_t end_tick)
{
    HAL_StatusTypeDef errorcode = HAL_OK;
    if ((hi2s->Init.Mode == I2S_MODE_SLAVE_TX) || (hi2s->Init.Mode == I2S_MODE_SLAVE_RX))
    {
        if (time_diff(systick_get_value(), end_tick) > 0U)
        {
            errorcode = HAL_TIMEOUT;
        }
    }
    return errorcode;
}

static void i2s_load_tx_dummy_data(I2S_HandleTypeDef *hi2s)
{
    hi2s->Instance->DR = 0;
    hi2s->Tx_Env.Interrupt.Count--;
}

static void i2s_pre_load_data(I2S_HandleTypeDef *hi2s)
{
    uint8_t i = hi2s->Tx_Env.Interrupt.Count > SPI_I2S_TX_FIFO_DEPTH? SPI_I2S_TX_FIFO_DEPTH: hi2s->Tx_Env.Interrupt.Count;
    while(i--)
    {
        hi2s->Tx_Env.Interrupt.i2s_transfer_Fun(hi2s);
    }
}

static void i2s_config(I2S_HandleTypeDef *hi2s, uint16_t *pTxData, uint16_t *pRxData, uint16_t Size, bool itmode)
{
    uint32_t tmp_cfgr = hi2s->Instance->I2SCFGR & (SPI_I2SCFGR_DATLEN_MASK | SPI_I2SCFGR_CHLEN_MASK);
    hi2s->Tx_Env.Interrupt.pBuffPtr = (uint8_t *)pTxData;
    hi2s->Rx_Env.Interrupt.pBuffPtr = (uint8_t *)pRxData;

    if ((tmp_cfgr == I2S_DATAFORMAT_24BIT) || (tmp_cfgr == I2S_DATAFORMAT_32BIT))
    {
        hi2s->Tx_Env.Interrupt.Count  = (Size << 1U);
        hi2s->Rx_Env.Interrupt.Count  = (Size << 1U);
    }
    else
    {
        hi2s->Tx_Env.Interrupt.Count  = Size;
        hi2s->Rx_Env.Interrupt.Count  = Size;
    }
    
    hi2s->Tx_Env.Interrupt.i2s_transfer_Fun = hi2s->Tx_Env.Interrupt.pBuffPtr? i2s_tx_load_data: i2s_load_tx_dummy_data;
    hi2s->Rx_Env.Interrupt.i2s_transfer_Fun = i2s_rx_load_data;
    
    SET_BIT(hi2s->Instance->I2SCFGR, SPI_I2SCFGR_I2SE_MASK);
    i2s_pre_load_data(hi2s);
    if (itmode)
    {
        hi2s->Instance->ICR = SPI_IT_TXE | SPI_IT_RXNE;
        hi2s->Instance->IER = SPI_IT_TXE | SPI_IT_RXNE;
    }
}

static void i2s_tx_data(I2S_HandleTypeDef *hi2s, uint32_t end_tick)
{
    while (hi2s->Tx_Env.Interrupt.Count > 0U)
    {
        if (SPI_I2S_TX_FIFO_NOT_FULL(hi2s))
        {
            hi2s->Tx_Env.Interrupt.i2s_transfer_Fun(hi2s);
        }
        i2s_timeout_handle(hi2s, end_tick);
    }
}

static void i2s_rx_data(I2S_HandleTypeDef *hi2s, uint32_t end_tick)
{
    if (hi2s->Init.Mode == I2S_MODE_MASTER_RX)
    {
        while ((hi2s->Tx_Env.Interrupt.Count > 0U) || (hi2s->Rx_Env.Interrupt.Count > 0U))
        {
            if (SPI_I2S_TX_FIFO_NOT_FULL(hi2s) && (hi2s->Tx_Env.Interrupt.Count > 0U))
            {
                hi2s->Tx_Env.Interrupt.i2s_transfer_Fun(hi2s);
            }
            if ((SPI_I2S_RX_FIFO_NOT_EMPTY(hi2s)) && (hi2s->Rx_Env.Interrupt.Count> 0U))
            {
                hi2s->Rx_Env.Interrupt.i2s_transfer_Fun(hi2s);
            }
            i2s_timeout_handle(hi2s, end_tick);
        }
    }
    else 
    {
        while (hi2s->Rx_Env.Interrupt.Count > 0U)
        {
            if (SPI_I2S_RX_FIFO_NOT_EMPTY(hi2s))
            {
                hi2s->Rx_Env.Interrupt.i2s_transfer_Fun(hi2s);
            }
            i2s_timeout_handle(hi2s, end_tick);
        }
    }
}

static void i2s_disable(I2S_HandleTypeDef *hi2s)
{
    while (REG_FIELD_RD(hi2s->Instance->SR,SPI_SR_BSY) == 1U);
    CLEAR_BIT(hi2s->Instance->I2SCFGR, SPI_I2SCFGR_I2SE_MASK);
}

HAL_StatusTypeDef HAL_I2S_Transmit(I2S_HandleTypeDef *hi2s, uint16_t *pTxData, uint16_t Size, uint32_t Timeout)
{
    uint32_t tickstart = systick_get_value();
    uint32_t timeout = SYSTICK_MS2TICKS(Timeout);
    uint32_t end_tick = tickstart + timeout;
    i2s_config(hi2s, pTxData, NULL, Size, false);
    i2s_tx_data(hi2s,end_tick);
    i2s_disable(hi2s);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_I2S_Receive(I2S_HandleTypeDef *hi2s, uint16_t *pRxData, uint16_t Size, uint32_t Timeout)
{ 
    uint32_t tickstart = systick_get_value();
    uint32_t timeout = SYSTICK_MS2TICKS(Timeout);
    uint32_t end_tick = tickstart + timeout;
    i2s_config(hi2s, NULL, pRxData, Size, false);
    i2s_rx_data(hi2s, end_tick);
    i2s_disable(hi2s);
    return HAL_OK;
}

__attribute__((weak)) void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s){}
__attribute__((weak)) void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef *hi2s){}

static void I2S_Close_ISR(I2S_HandleTypeDef *hi2s)
{
    if (hi2s->Rx_Env.Interrupt.Count == 0U)
    {
        hi2s->Instance->IDR = SPI_IT_RXNE;
        i2s_disable(hi2s);
        HAL_I2S_RxCpltCallback(hi2s);
    }
}

static void I2S_Tx_ISR(I2S_HandleTypeDef *hi2s)
{
    while ((SPI_I2S_TX_FIFO_NOT_FULL(hi2s)) && (hi2s->Tx_Env.Interrupt.Count > 0U))
    {
        hi2s->Tx_Env.Interrupt.i2s_transfer_Fun(hi2s);
    }

    if (hi2s->Tx_Env.Interrupt.Count == 0U)
    {
        hi2s->Instance->IDR = SPI_IT_TXE;
        i2s_disable(hi2s);
        HAL_I2S_TxCpltCallback(hi2s);
    }
}

#ifdef LE501X
static void I2S_Rx_ISR(I2S_HandleTypeDef *hi2s)
{
    hi2s->Instance->ICR = SPI_ICR_RXNEIC_MASK;
    uint8_t i = REG_FIELD_RD(hi2s->Instance->SR, SPI_SR_RXFLV);
    while (i--)
    {
        hi2s->Rx_Env.Interrupt.i2s_transfer_Fun(hi2s);
    }
    I2S_Close_ISR(hi2s);
}
#else
static void I2S_Rx_ISR(I2S_HandleTypeDef *hi2s)
{
    uint8_t i = REG_FIELD_RD(hi2s->Instance->SR, SPI_SR_RXFLV);
    while (i--)
    {
        hi2s->Rx_Env.Interrupt.i2s_transfer_Fun(hi2s);
    }
    hi2s->Instance->ICR = SPI_ICR_RXNEIC_MASK;
    I2S_Close_ISR(hi2s);
}
#endif

HAL_StatusTypeDef HAL_I2S_Transmit_IT(I2S_HandleTypeDef *hi2s, uint16_t *pTxData, uint16_t Size)
{
    i2s_config(hi2s, pTxData, NULL, Size, true);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_I2S_Receive_IT(I2S_HandleTypeDef *hi2s, uint16_t *pRxData, uint16_t Size)
{
    i2s_config(hi2s, NULL, pRxData, Size, true);
    return HAL_OK;
}

void HAL_I2S_IRQHandler(I2S_HandleTypeDef *hi2s)
{
    /* I2S in mode Receiver ----------------------------------------------------*/
    if (REG_FIELD_RD(hi2s->Instance->IFM, SPI_IFM_RXNEFM) == 1U)
    {
        I2S_Rx_ISR(hi2s);
    }

    /* I2S in mode Transmitter -------------------------------------------------*/
    if (REG_FIELD_RD(hi2s->Instance->IFM, SPI_IFM_TXEFM) == 1U)
    {
        #ifdef LE501X
        hi2s->Instance->ICR = SPI_ICR_TXEIC_MASK;
        I2S_Tx_ISR(hi2s);
        #else  
        I2S_Tx_ISR(hi2s);
        hi2s->Instance->ICR = SPI_ICR_TXEIC_MASK;
        #endif /* LE501X */
    }

    /* I2S in Error Treatment --------------------------------------------------*/
    if (REG_FIELD_RD(hi2s->Instance->IFM, SPI_IFM_OVRFM) == 1U)
    {
        LOG_I("fifo overrun error");
        LS_ASSERT(0);
    }
    if (REG_FIELD_RD(hi2s->Instance->IFM, SPI_IFM_UDRFM) == 1U)
    {
        LOG_I("fifo underrun error");
        LS_ASSERT(0);
    }
    if (REG_FIELD_RD(hi2s->Instance->IFM, SPI_IFM_FREFM) == 1U)
    {
        LOG_I("frame format error");
        LS_ASSERT(0);
    }
}