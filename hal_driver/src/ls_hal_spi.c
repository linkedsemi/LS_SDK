/* Includes ------------------------------------------------------------------*/
#include "ls_hal_spi.h"

#define SPI_TX_FIFO_DEPTH 16
#define SPI_TX_FIFO_NOT_FULL(__HANDLE__) (REG_FIELD_RD((__HANDLE__)->Instance->SR, SPI_SR_TXFLV) < SPI_TX_FIFO_DEPTH)
#define SPI_RX_FIFO_NOT_EMPTY(__HANDLE__) (REG_FIELD_RD((__HANDLE__)->Instance->SR, SPI_SR_RXFLV) > 0)

static void SPI_Tx_ISR(struct __SPI_HandleTypeDef *hspi);
static void SPI_Rx_ISR(struct __SPI_HandleTypeDef *hspi);
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
    SET_BIT(hspi->Instance->IFM, SPI_IT_ERR);
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
    hspi->pTxBuffPtr  = (uint8_t *)pTxData;
    hspi->TxXferCount = Size; 
}

static void rx_para_init(SPI_HandleTypeDef *hspi, uint8_t *pRxData,uint16_t Size)
{
    hspi->pRxBuffPtr  = (uint8_t *)pRxData;
    hspi->RxXferCount = Size;
}

static void spi_tx_load_data_8bit(SPI_HandleTypeDef *hspi)
{
    *((uint8_t *)&hspi->Instance->DR) = *((uint8_t *)hspi->pTxBuffPtr);
    hspi->pTxBuffPtr += sizeof(uint8_t);
    hspi->TxXferCount--;
}

static void spi_tx_load_data_16bit(SPI_HandleTypeDef *hspi)
{
    hspi->Instance->DR = hspi->pTxBuffPtr[1]<<8|hspi->pTxBuffPtr[0];
    hspi->pTxBuffPtr += sizeof(uint16_t);
    hspi->TxXferCount--;
}

static void spi_rx_load_data_8bit(SPI_HandleTypeDef *hspi)
{
    *((uint8_t *)hspi->pRxBuffPtr) = hspi->Instance->DR;
    hspi->pRxBuffPtr += sizeof(uint8_t);
    hspi->RxXferCount--;
}

static void spi_rx_load_data_16bit(SPI_HandleTypeDef *hspi)
{
    uint16_t rx = hspi->Instance->DR;
    hspi->pRxBuffPtr[0] = rx;
    hspi->pRxBuffPtr[1] = rx>>8;
    hspi->pRxBuffPtr += sizeof(uint16_t); 
    hspi->RxXferCount -= sizeof(uint16_t);
}

#ifdef LE501X
static void le501x_8bit_packing_mode_handle(SPI_HandleTypeDef *hspi)
{
    uint8_t i = REG_FIELD_RD(hspi->Instance->SR, SPI_SR_RXFLV)/2;
    while (i--)
    {
        spi_rx_load_data_16bit(hspi);
    }
    if(hspi->RxXferCount == 1U)
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
        hspi->Instance->DR;
        hspi->RxXferCount -= sizeof(uint16_t);
    }
    if(hspi->RxXferCount == 1U)
    {
        hspi->Instance->DR;
        hspi->RxXferCount--;
    }
}
#endif

static void pre_load_data(SPI_HandleTypeDef *hspi)
{
    uint8_t i = hspi->TxXferCount > SPI_TX_FIFO_DEPTH? SPI_TX_FIFO_DEPTH: hspi->TxXferCount;
    while(i--)
    {
        hspi->Tx_Fun(hspi);
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
    hspi->TxXferCount--;
}

static void load_rx_dummy_data(SPI_HandleTypeDef *hspi)
{
    hspi->Instance->DR;
    hspi->RxXferCount--;
}

static void spi_config(SPI_HandleTypeDef *hspi, bool itmode)
{
    if (hspi->Init.DataSize > SPI_DATASIZE_8BIT)
    {
        hspi->Tx_Fun = hspi->pTxBuffPtr? spi_tx_load_data_16bit: load_tx_dummy_data;
        hspi->Rx_Fun = hspi->pRxBuffPtr? spi_rx_load_data_16bit: load_rx_dummy_data;
    }
    else  // 8 Bit Mode
    {
        hspi->Tx_Fun = hspi->pTxBuffPtr? spi_tx_load_data_8bit: load_tx_dummy_data;
        #ifdef LE501X
        hspi->Rx_Fun = hspi->pRxBuffPtr? le501x_8bit_packing_mode_handle: le501x_8bit_load_rx_dummy_data;
        #else 
        hspi->Rx_Fun = hspi->pRxBuffPtr? spi_rx_load_data_8bit: load_rx_dummy_data;
        #endif
    }
    
    SET_BIT(hspi->Instance->CR1, SPI_CR1_SPE_MASK);
    pre_load_data(hspi);

    if (itmode)
    {
        SET_BIT(hspi->Instance->ICR, SPI_IT_TXE | SPI_IT_RXNE);
        SET_BIT(hspi->Instance->IER, SPI_IT_TXE | SPI_IT_RXNE);
    }
}

static void spi_data_transfer(SPI_HandleTypeDef *hspi)
{
    while ((hspi->TxXferCount > 0U) || (hspi->RxXferCount > 0U))
    {
        if (SPI_TX_FIFO_NOT_FULL(hspi) && (hspi->TxXferCount > 0U))
        {
            hspi->Tx_Fun(hspi);
        }
        if ((SPI_RX_FIFO_NOT_EMPTY(hspi)) && (hspi->RxXferCount > 0U))
        {
            hspi->Rx_Fun(hspi);
        }
    }
}

static HAL_StatusTypeDef timeout_handle(SPI_HandleTypeDef *hspi, uint32_t end_tick)
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

HAL_StatusTypeDef HAL_SPI_Transmit(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint16_t Size, uint32_t Timeout)
{   
    uint32_t tickstart = systick_get_value();
    uint32_t timeout = SYSTICK_MS2TICKS(Timeout);
    uint32_t end_tick = tickstart + timeout;
    CLEAR_BIT(hspi->Instance->CR1, SPI_CR1_RXONLY_MASK);
    tx_para_init(hspi, pTxData, Size);
    rx_para_init(hspi, NULL, Size);
    spi_config(hspi,false);
    spi_data_transfer(hspi);
    timeout_handle(hspi,end_tick);
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
    spi_data_transfer(hspi);
    timeout_handle(hspi,end_tick);
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
    spi_data_transfer(hspi);
    timeout_handle(hspi,end_tick);
    spi_disable(hspi);
    return HAL_OK;
}

__weak void HAL_SPI_CpltCallback(SPI_HandleTypeDef *hspi)
{
    UNUSED(hspi);
}

static void SPI_Tx_ISR(struct __SPI_HandleTypeDef *hspi)
{
    while (SPI_TX_FIFO_NOT_FULL(hspi) && hspi->TxXferCount > 0U)
    {
        hspi->Tx_Fun(hspi);
    }
    if (hspi->TxXferCount == 0U)
    {
        SET_BIT(hspi->Instance->IDR, SPI_IT_TXE);
    }
}

static void SPI_Close_ISR(struct __SPI_HandleTypeDef *hspi)
{
    if(hspi->RxXferCount == 0U)
    {
        SET_BIT(hspi->Instance->IDR, SPI_IT_RXNE);
        spi_disable(hspi);
        HAL_SPI_CpltCallback(hspi);
    }
}
#ifdef LE501X
static void SPI_Rx_ISR(struct __SPI_HandleTypeDef *hspi)
{
    WRITE_REG(hspi->Instance->ICR,SPI_ICR_RXNEIC_MASK);
    hspi->Rx_Fun(hspi);
    SPI_Close_ISR(hspi);
}
#else
static void SPI_Rx_ISR(struct __SPI_HandleTypeDef *hspi)
{
    while (SPI_RX_FIFO_NOT_EMPTY(hspi) && hspi->RxXferCount > 0U)
    {
        hspi->Rx_Fun(hspi);
    }
    WRITE_REG(hspi->Instance->ICR,SPI_ICR_RXNEIC_MASK);
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
    if (REG_FIELD_RD(hspi->Instance->IFM, SPI_IFM_RXNEFM) == 1)
    {
        SPI_Rx_ISR(hspi);
    }

    /* SPI in mode Transmitter -------------------------------------------------*/
    if (REG_FIELD_RD(hspi->Instance->IFM, SPI_IFM_TXEFM) == 1)
    {
        #ifdef LE501X
        WRITE_REG(hspi->Instance->ICR,SPI_ICR_TXEIC_MASK);
        SPI_Tx_ISR(hspi);
        #else 
        SPI_Tx_ISR(hspi);
        WRITE_REG(hspi->Instance->ICR,SPI_ICR_TXEIC_MASK);
        #endif
    }

    /* SPI in Error Treatment --------------------------------------------------*/
    if (REG_FIELD_RD(hspi->Instance->IFM, SPI_IFM_OVRFM) == 1)
    {
        LOG_I("spi fifo overrun error");
        LS_ASSERT(0);
    }
    if (REG_FIELD_RD(hspi->Instance->IFM, SPI_IFM_MODFFM) == 1)
    {
        LOG_I("spi master mode fault");
        LS_ASSERT(0);
    }
    if (REG_FIELD_RD(hspi->Instance->IFM, SPI_IFM_UDRFM) == 1)
    {
        LOG_I("spi fifo underrun error");
        LS_ASSERT(0);
    }
    if (REG_FIELD_RD(hspi->Instance->IFM, SPI_IFM_FREFM) == 1)
    {
        LOG_I("spi frame format error");
        LS_ASSERT(0);
    }
}