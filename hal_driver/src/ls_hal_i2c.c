#include <stdio.h>
#include "ls_hal_i2c.h"
#include "ls_msp_i2c.h" 
#include "field_manipulate.h"
#include "systick.h"
#include "platform.h"
#include "cpu.h"
#include "ls_ll_i2c.h"

#define I2C_FIFO_DEPTH 8
#define I2C_TIMEOUT_FLAG          35U         /*!< Timeout 35 ms             */
#define I2C_TIMEOUT_BUSY_FLAG     25U         /*!< Timeout 25 ms             */

#define __HAL_I2C_GET_TXFLV(__HANDLE__) (REG_FIELD_RD((__HANDLE__)->Instance->SR, I2C_SR_TXFLV))
#define __HAL_I2C_GET_RXFLV(__HANDLE__) (REG_FIELD_RD((__HANDLE__)->Instance->SR, I2C_SR_RXFLV))
// #define __HAL_I2C_CLR_TXDR(__HANDLE__) (((__HANDLE__)->Instance->SR) |= (1 << 0))

#define I2C_FIFO_TX(__HANDLE__) while (__HAL_I2C_GET_TXFLV(__HANDLE__) < I2C_FIFO_DEPTH && (__HANDLE__)->XferCount > 0)           \
                                {                                                                                                 \
                                    (__HANDLE__)->Instance->TXDR = *(__HANDLE__)->pBuffPtr;                                       \
                                    (__HANDLE__)->pBuffPtr++;                                                                     \
                                    (__HANDLE__)->XferCount--;                                                                    \
                                }
#define I2C_FIFO_RX(__HANDLE__) while (__HAL_I2C_GET_RXFLV(__HANDLE__) > 0 && (__HANDLE__)->XferCount > 0)                        \
                                {                                                                                                 \
                                    *(__HANDLE__)->pBuffPtr = (uint8_t)(__HANDLE__)->Instance->RXDR;                              \
                                    (__HANDLE__)->pBuffPtr++;                                                                     \
                                    (__HANDLE__)->XferCount--;                                                                    \
                                }
struct i2c_speed_config_t
{
    uint32_t scll     : 8;
    uint32_t sclh     : 8;
    uint32_t sdadel   : 4;
    uint32_t scldel   : 4;
    uint32_t role : 4;
    uint32_t presc    : 4;
};
static const uint8_t i2c_hw_state_switch_delay_us[I2C_SPEED_MAX] = {10, 3, 1};
static struct i2c_speed_config_t speed_config;
static void I2C_ITError(I2C_HandleTypeDef *hi2c);
static HAL_StatusTypeDef I2C_MasterRequestRead_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint32_t Timeout, uint32_t Tickstart, bool Read);
static HAL_StatusTypeDef I2C_WaitOnFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Flag, FlagStatus Status, uint32_t Timeout, uint32_t Tickstart);
static HAL_StatusTypeDef I2C_WaitOnItSourceUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t ItSource, FlagStatus Status, uint32_t Timeout, uint32_t Tickstart);
static HAL_StatusTypeDef I2C_WaitOnMasterAddressFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Flag, uint32_t Timeout, uint32_t Tickstart);
static HAL_StatusTypeDef I2C_WaitOnFLVUntilTimeout(bool (*poll)(va_list), ...);
static HAL_StatusTypeDef I2C_WaitOnRxFifoFullUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Timeout, uint32_t Tickstart);

static void I2C_MasterTransmit_TXE(I2C_HandleTypeDef *hi2c);
static void I2C_MasterReceive_RXNE(I2C_HandleTypeDef *hi2c);
static void I2C_SlaveTransmit_TXE(I2C_HandleTypeDef *hi2c);
static void I2C_SlaveReceive_RXNE(I2C_HandleTypeDef *hi2c);

static void I2C_ADDR(I2C_HandleTypeDef *hi2c, uint32_t sr1itflags);
static void I2C_STOPF(I2C_HandleTypeDef *hi2c);
static bool i2c_rxflvnzandstop_poll(va_list va);
static bool i2c_txflvnfandstop_poll(va_list va);
static bool i2c_txflveandstop_poll(va_list va);
static bool i2c_flag_poll(va_list va);
// extern void toggle_debug_IO(uint16_t);

__attribute__((weak)) void HAL_I2C_DMA_TxCpltCallback(I2C_HandleTypeDef *hi2c)
{
  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_I2C_DMA_TxCpltCallback could be implemented in the user file
   */
}

__attribute__((weak)) void HAL_I2C_DMA_RxCpltCallback(I2C_HandleTypeDef *hi2c)
{
  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_I2C_DMA_RxCpltCallback could be implemented in the user file
   */
}

static bool I2C_speed_config_calc_master_dft(uint8_t speed, struct i2c_speed_config_t *speed_config)
{
    /* When calculating master speed config, it should be in init state */
    if (0 == speed_config->role)
    {
        uint32_t speed_array[I2C_SPEED_MAX] = {100*1000, 400*1000, 1000*1000};
        uint16_t cycle_count = I2C_CLOCK / speed_array[speed];
        int16_t scll, sclh, scldel, sdadel;
        uint8_t prescaler = 0;
        if (cycle_count > 256)
        {
            for (uint8_t i = 1; prescaler < 16; i++)
            {
                /* For easier calculating, just set prescaler to an odd number. */
                prescaler = 2 * i - 1;
                cycle_count = (I2C_CLOCK / speed_array[speed]) / (prescaler + 1);
                if (cycle_count <= 256)
                {
                    break;
                }
            }
            if (prescaler >= 16)
            {
                return false;
            }
        }
        if (cycle_count < 16)
        {
            return false;
        }
        /* Set SCL dutycycle to about 30% */
        scll = (cycle_count * 2) / 3;
        sclh = cycle_count / 3 - 1 - 4;
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
        if (sdadel > 4)
        {
            /* We should set a ceiling for SDADEL. This is unnecessary, and will reduce compatibility if we are IIC slave */
            sdadel = 4;
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
        speed_config->presc = prescaler;
        speed_config->scll = scll;
        speed_config->sclh = sclh;
        speed_config->scldel = scldel;
        speed_config->sdadel = sdadel;
        speed_config->role = 1;
    }
    return true;
}

static void I2C_speed_config_calc_slave(I2C_HandleTypeDef *hi2c)
{
    /* When calculating slave speed config, it should NOT be in init state */
    LS_ASSERT(speed_config.role > 0);
    /* Only in master mode should we re-calculate config for slave */
    if (1 == speed_config.role)
    {
        /* Switch scll with sclh for slave. */
        uint16_t half_sclk = ((uint16_t)speed_config.sclh + (uint16_t)speed_config.scll + 5) / 2;
        speed_config.sclh = (uint8_t)half_sclk - 5;
        speed_config.scll = (uint8_t)half_sclk;
        speed_config.role = 2;
        __HAL_I2C_DISABLE(hi2c);
        MODIFY_REG(hi2c->Instance->TIMINGR, (I2C_TIMINGR_SCLH_MASK | I2C_TIMINGR_SCLL_MASK), 
                                            (speed_config.sclh<<I2C_TIMINGR_SCLH_POS\
                                            |speed_config.scll<<I2C_TIMINGR_SCLL_POS));
    }
    // __HAL_I2C_ENABLE(hi2c);
}

static void HAL_I2C_hw_Init(I2C_HandleTypeDef *hi2c)
{
    HAL_I2C_MSP_Init(hi2c);
    HAL_I2C_MSP_Busy_Set(hi2c);
    bool re_enable = (hi2c->Instance->CR1 & I2C_CR1_PE_MASK) == I2C_CR1_PE_MASK;

    __HAL_I2C_DISABLE(hi2c);

    bool config_result = I2C_speed_config_calc_master_dft(hi2c->Init.ClockSpeed, &speed_config);
    LS_ASSERT(config_result);

    MODIFY_REG(hi2c->Instance->TIMINGR, I2C_TIMINGR_PRESC_MASK, speed_config.presc << I2C_TIMINGR_PRESC_POS); 
    MODIFY_REG(hi2c->Instance->TIMINGR, (I2C_TIMINGR_SCLH_MASK | I2C_TIMINGR_SCLL_MASK | I2C_TIMINGR_SDADEL_MASK | I2C_TIMINGR_SCLDEL_MASK), 
                                        (speed_config.sclh<<I2C_TIMINGR_SCLH_POS\
                                        |speed_config.scll<<I2C_TIMINGR_SCLL_POS\
                                        |speed_config.sdadel<<I2C_TIMINGR_SDADEL_POS\
                                        |speed_config.scldel<<I2C_TIMINGR_SCLDEL_POS));

    /*---------------------------- I2Cx CR1 Configuration ----------------------*/
    /* Configure I2Cx: Generalcall and NoStretch mode */
    MODIFY_REG(hi2c->Instance->CR1, (I2C_CR1_GCEN_MASK | I2C_CR1_NOSTRETCH_MASK), (hi2c->Init.GeneralCallMode | hi2c->Init.NoStretchMode));
    /*---------------------------- I2Cx OAR1 Configuration ---------------------*/
    /* Configure I2Cx: Own Address1 and addressing mode */
    REG_FIELD_WR(hi2c->Instance->OAR1, I2C_OAR1_OA1EN, 0);
    if (hi2c->Init.AddressingMode == I2C_ADDRESSINGMODE_7BIT)
    {
        MODIFY_REG(hi2c->Instance->OAR1, (I2C_OAR1_OA1MODE_MASK | I2C_OAR1_OA18_9_MASK | I2C_OAR1_OA11_7_MASK | I2C_OAR1_OA10_MASK), (hi2c->Init.AddressingMode | (hi2c->Init.OwnAddress1<<1)));
    }
    else
    {
        MODIFY_REG(hi2c->Instance->OAR1, (I2C_OAR1_OA1MODE_MASK | I2C_OAR1_OA18_9_MASK | I2C_OAR1_OA11_7_MASK | I2C_OAR1_OA10_MASK), (hi2c->Init.AddressingMode | hi2c->Init.OwnAddress1));
    }
    REG_FIELD_WR(hi2c->Instance->OAR1, I2C_OAR1_OA1EN, 1);
    /*---------------------------- I2Cx OAR2 Configuration ---------------------*/
    /* Configure I2Cx: Dual mode and Own Address2 */
    if (hi2c->Init.DualAddressMode == I2C_DUALADDRESS_ENABLE)
    {
        REG_FIELD_WR(hi2c->Instance->OAR2, I2C_OAR2_OA2EN, 0);
        MODIFY_REG(hi2c->Instance->OAR2, (I2C_OAR2_OA21_7_MASK | I2C_OAR2_OA2MSK_MASK), ((hi2c->Init.OwnAddress2<<1) | hi2c->Init.Oar2msk_Mask<<8));
        REG_FIELD_WR(hi2c->Instance->OAR2, I2C_OAR2_OA2EN, 1);
    }
    __HAL_I2C_SBC_ENABLE(hi2c); // Enable SBC for slave by default
    __HAL_I2C_RXFTH_SET(hi2c, I2C_FIFO_DEPTH-1);
    
    if (re_enable)
    {
        __HAL_I2C_ENABLE(hi2c);
    }
}

HAL_StatusTypeDef HAL_I2C_Init(I2C_HandleTypeDef *hi2c)
{
    if (hi2c == NULL)
    {
        return HAL_ERROR;
    }
    LS_ASSERT(IS_I2C_ALL_INSTANCE(hi2c->Instance));
    LS_ASSERT(IS_I2C_CLOCK_SPEED(hi2c->Init.ClockSpeed));
    LS_ASSERT(IS_I2C_OWN_ADDRESS1(hi2c->Init.OwnAddress1));
    LS_ASSERT(IS_I2C_ADDRESSING_MODE(hi2c->Init.AddressingMode));
    LS_ASSERT(IS_I2C_DUAL_ADDRESS(hi2c->Init.DualAddressMode));
    LS_ASSERT(IS_I2C_OWN_ADDRESS2(hi2c->Init.OwnAddress2));
    LS_ASSERT(IS_I2C_GENERAL_CALL(hi2c->Init.GeneralCallMode));
    LS_ASSERT(IS_I2C_NO_STRETCH(hi2c->Init.NoStretchMode));

    hi2c->State = HAL_I2C_STATE_BUSY;
    HAL_I2C_hw_Init(hi2c);

    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
    hi2c->State = HAL_I2C_STATE_READY;
    hi2c->Mode = HAL_I2C_MODE_NONE;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_I2C_DeInit(I2C_HandleTypeDef *hi2c)
{
    if (hi2c == NULL)
    {
        return HAL_ERROR;
    }
    LS_ASSERT(IS_I2C_ALL_INSTANCE(hi2c->Instance));

    hi2c->State = HAL_I2C_STATE_BUSY;
    __HAL_I2C_DISABLE(hi2c);

    HAL_I2C_MSP_DeInit(hi2c);
    HAL_I2C_MSP_Idle_Set(hi2c);
    speed_config.role = 0;

    hi2c->ErrorCode     = HAL_I2C_ERROR_NONE;
    hi2c->State         = HAL_I2C_STATE_RESET;
    hi2c->Mode          = HAL_I2C_MODE_NONE;

    return HAL_OK;
}

HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint8_t Size, uint32_t Timeout)
{
    uint32_t tickstart = systick_get_value();
    if (hi2c->State == HAL_I2C_STATE_READY)
    {
        if (pData == NULL || Size == 0  || Timeout == 0)
        {
            return HAL_INVALIAD_PARAM;
        }
        __HAL_I2C_ENABLE(hi2c);
        if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG, tickstart) != HAL_OK)
        {
            __HAL_I2C_DISABLE(hi2c);
            return HAL_BUSY;
        }
        
        hi2c->State       = HAL_I2C_STATE_BUSY_TX;
        hi2c->Mode        = HAL_I2C_MODE_MASTER;
        hi2c->ErrorCode   = HAL_I2C_ERROR_NONE;

        hi2c->pBuffPtr    = pData;
        hi2c->XferCount   = Size;
        hi2c->XferSize    = hi2c->XferCount;

        __HAL_I2C_CLEAR_SR(hi2c);
        CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_AUTOEND_MASK | I2C_CR2_RELOAD_MASK | I2C_CR2_NBYTES_MASK);
        SET_BIT(hi2c->Instance->CR2, I2C_CR2_AUTOEND_MASK | (((uint32_t)hi2c->XferSize) << I2C_CR2_NBYTES_POS));
        /* Clear TXFIFO */
        __HAL_I2C_CLR_TXDR(hi2c);

        if (I2C_MasterRequestRead_Write(hi2c, DevAddress, Timeout, tickstart, false) != HAL_OK)
        {
            __HAL_I2C_DISABLE(hi2c);
            return HAL_ERROR;
        }

        while (1)
        {
            I2C_FIFO_TX(hi2c);
            if (0 == hi2c->XferCount)
            {
                break;
            }
            /* Timeout check is necessary for I2C master, because I2C slave can hold bus which will lead to timeout */
            if (I2C_WaitOnFLVUntilTimeout(i2c_txflvnfandstop_poll, hi2c, Timeout, tickstart) != HAL_OK)
            {
                /* Stop event is detected in I2C_WaitOnFLVUntilTimeout. We handle this case out of the while loop */
                if (hi2c->ErrorCode == HAL_I2C_ERROR_BERR)
                {
                    break; 
                }
                /* Master failed send data to bus in time. It's likely to happen when the bus is hold by slave.*/
                hi2c->XferCount += __HAL_I2C_GET_TXFLV(hi2c);
                __HAL_I2C_DISABLE(hi2c);
                return HAL_ERROR;
            }
        }
        if (I2C_WaitOnItSourceUntilTimeout(hi2c, I2C_RIF_STOPRI_MASK, RESET, Timeout, tickstart) != HAL_OK)
        {
            /* Stop event timeout. It's likely to happen when the bus is hold by slave.*/
            hi2c->XferCount += __HAL_I2C_GET_TXFLV(hi2c);
            __HAL_I2C_DISABLE(hi2c);
            return HAL_ERROR;
        }
        hi2c->XferCount += __HAL_I2C_GET_TXFLV(hi2c);
        if (0 == hi2c->XferCount)
        {
            hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
        }
        else
        {
            hi2c->ErrorCode = HAL_I2C_ERROR_BERR;
        }
        __HAL_I2C_CLEAR_FLAG(hi2c, I2C_CFR_STOPCF_MASK);
        hi2c->State = HAL_I2C_STATE_READY;
        hi2c->Mode = HAL_I2C_MODE_NONE;
        __HAL_I2C_DISABLE(hi2c);
        return hi2c->ErrorCode == HAL_I2C_ERROR_NONE ? HAL_OK : HAL_ERROR;
    }
    else
    {
        return HAL_BUSY;
    }
}

HAL_StatusTypeDef HAL_I2C_Master_Receive(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint8_t Size, uint32_t Timeout)
{
    uint32_t tickstart = systick_get_value();
    if (hi2c->State == HAL_I2C_STATE_READY)
    {
        if (pData == NULL || Size == 0 || Timeout == 0)
        {
            return HAL_INVALIAD_PARAM;
        }
        __HAL_I2C_ENABLE(hi2c);
        if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG, tickstart) != HAL_OK)
        {
            __HAL_I2C_DISABLE(hi2c);
            return HAL_BUSY;
        }
        
        hi2c->State       = HAL_I2C_STATE_BUSY_RX;
        hi2c->Mode        = HAL_I2C_MODE_MASTER;
        hi2c->ErrorCode   = HAL_I2C_ERROR_NONE;

        hi2c->pBuffPtr    = pData;
        hi2c->XferCount   = Size;
        hi2c->XferSize    = hi2c->XferCount;

        /* Clear TXFIFO */
        __HAL_I2C_CLR_TXDR(hi2c); 
        __HAL_I2C_CLEAR_SR(hi2c);    
        CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_AUTOEND_MASK | I2C_CR2_RELOAD_MASK | I2C_CR2_NBYTES_MASK);
        SET_BIT(hi2c->Instance->CR2, I2C_CR2_AUTOEND_MASK | (((uint32_t)hi2c->XferSize) << I2C_CR2_NBYTES_POS));

        if (I2C_MasterRequestRead_Write(hi2c, DevAddress, Timeout, tickstart, true) != HAL_OK)
        {
            __HAL_I2C_DISABLE(hi2c);
            return HAL_ERROR;
        }
        while (1)
        {
            while (__HAL_I2C_GET_RXFLV(hi2c) > 0 && (hi2c)->XferCount > 0)
            {
                *hi2c->pBuffPtr = (uint8_t)(hi2c->Instance->RXDR);
                hi2c->pBuffPtr++;
                hi2c->XferCount--;
            }
            if (0 == hi2c->XferCount)
            {
                break;
            }
            if (I2C_WaitOnFLVUntilTimeout(i2c_rxflvnzandstop_poll, hi2c, Timeout, tickstart) != HAL_OK) 
            {
                __HAL_I2C_DISABLE(hi2c);
                return HAL_ERROR;
            }
        }
        if (I2C_WaitOnItSourceUntilTimeout(hi2c, I2C_RIF_STOPRI_MASK, RESET, Timeout, tickstart) != HAL_OK)
        {
            __HAL_I2C_DISABLE(hi2c);
            return HAL_ERROR;
        }
        __HAL_I2C_CLEAR_FLAG(hi2c, I2C_CFR_STOPCF_MASK);
        hi2c->State = HAL_I2C_STATE_READY;
        hi2c->Mode = HAL_I2C_MODE_NONE;
        hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
        __HAL_I2C_DISABLE(hi2c);
        return HAL_OK;
    }
    else
    {
        return HAL_BUSY;
    }
}

HAL_StatusTypeDef HAL_I2C_Master_Transmit_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint8_t Size)
{
    if (hi2c->State == HAL_I2C_STATE_READY)
    {
        if (pData == NULL || Size == 0)
        {
            return HAL_INVALIAD_PARAM;
        }
        __HAL_I2C_ENABLE(hi2c);

        hi2c->State     = HAL_I2C_STATE_BUSY_TX;
        hi2c->Mode      = HAL_I2C_MODE_MASTER;
        hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

        hi2c->pBuffPtr    = pData;
        hi2c->XferCount   = Size;
        hi2c->XferSize    = hi2c->XferCount;
        hi2c->Devaddress  = DevAddress;

        CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_AUTOEND_MASK | I2C_CR2_RELOAD_MASK | I2C_CR2_NBYTES_MASK);
        SET_BIT(hi2c->Instance->CR2, I2C_CR2_AUTOEND_MASK | (((uint32_t)hi2c->XferSize)<<I2C_CR2_NBYTES_POS));

        if (hi2c->Init.AddressingMode == I2C_ADDRESSINGMODE_7BIT)
        {
            CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_SADD10_MASK);
            MODIFY_REG(hi2c->Instance->CR2, I2C_CR2_RD_WEN_MASK | I2C_CR2_SADD1_7_MASK,(DevAddress<<1)&0xFE);
        }
        else
        {
            SET_BIT(hi2c->Instance->CR2, I2C_CR2_SADD10_MASK);
            MODIFY_REG(hi2c->Instance->CR2, I2C_CR2_RD_WEN_MASK | I2C_CR2_SADD0_MASK | I2C_CR2_SADD1_7_MASK | I2C_CR2_SADD8_9_MASK,DevAddress&0x3FF);
            CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_HEAD10R_MASK);
        }
        /* Clear TXFIFO */
        __HAL_I2C_CLR_TXDR(hi2c);
        __HAL_I2C_CLEAR_SR(hi2c);
        __HAL_I2C_CLEAR_IF(hi2c, I2C_IT_EVT | I2C_IT_TXE | I2C_IT_ERR | I2C_IT_TCR | I2C_IT_TC);
        if ((hi2c->XferCount > 0U) && (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_TXE) == SET))
        {
            hi2c->Instance->TXDR = *hi2c->pBuffPtr;
            hi2c->pBuffPtr++;
            hi2c->XferCount--;
        }
        __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_TXE | I2C_IT_ERR);
            
        SET_BIT(hi2c->Instance->CR2, I2C_CR2_START_MASK);
        return HAL_OK;
    }
    else
    {
        return HAL_BUSY;
    }
}

HAL_StatusTypeDef HAL_I2C_Master_Receive_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint8_t Size)
{
    if (hi2c->State == HAL_I2C_STATE_READY)
    {
        if (pData == NULL || Size == 0)
        {
            return HAL_INVALIAD_PARAM;
        }
        __HAL_I2C_ENABLE(hi2c);

        hi2c->State     = HAL_I2C_STATE_BUSY_RX;
        hi2c->Mode      = HAL_I2C_MODE_MASTER;
        hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

        hi2c->pBuffPtr    = pData;
        hi2c->XferCount   = Size;
        hi2c->XferSize    = hi2c->XferCount;
        hi2c->Devaddress  = DevAddress;

        /* Clear TXFIFO */
        __HAL_I2C_CLR_TXDR(hi2c);

        CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_AUTOEND_MASK | I2C_CR2_RELOAD_MASK | I2C_CR2_NBYTES_MASK);
        SET_BIT(hi2c->Instance->CR2, I2C_CR2_AUTOEND_MASK | (((uint32_t)hi2c->XferSize)<<I2C_CR2_NBYTES_POS));
        
        if (hi2c->Init.AddressingMode == I2C_ADDRESSINGMODE_7BIT)
        {
            CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_SADD10_MASK);
            MODIFY_REG(hi2c->Instance->CR2, I2C_CR2_RD_WEN_MASK | I2C_CR2_SADD1_7_MASK,I2C_CR2_RD_WEN_MASK | ((DevAddress<<1)&0xFE));
        }
        else
        {
            SET_BIT(hi2c->Instance->CR2, I2C_CR2_SADD10_MASK);
            MODIFY_REG(hi2c->Instance->CR2, I2C_CR2_RD_WEN_MASK | I2C_CR2_SADD0_MASK | I2C_CR2_SADD1_7_MASK | I2C_CR2_SADD8_9_MASK,\
                                                                            I2C_CR2_RD_WEN_MASK | (DevAddress&0x3FF));
            CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_HEAD10R_MASK);

        }
        __HAL_I2C_CLEAR_SR(hi2c);
        __HAL_I2C_CLEAR_IF(hi2c, I2C_IT_EVT | I2C_IT_RXNE | I2C_IT_ERR);
        __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_RXNE | I2C_IT_ERR);

        SET_BIT(hi2c->Instance->CR2, I2C_CR2_START_MASK);
        return HAL_OK;
    }
    else
    {
        return HAL_BUSY;
    }
}

HAL_StatusTypeDef HAL_I2C_Slave_Transmit_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint8_t Size)
{
    if (hi2c->State == HAL_I2C_STATE_READY)
    {
        if (pData == NULL || Size == 0)
        {
            return HAL_ERROR;
        }
        I2C_speed_config_calc_slave(hi2c);
        __HAL_I2C_ENABLE(hi2c);

        hi2c->State = HAL_I2C_STATE_BUSY_TX;
        hi2c->Mode = HAL_I2C_MODE_SLAVE;
        hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

        hi2c->pBuffPtr = pData;
        hi2c->XferCount = Size;
        hi2c->XferSize = hi2c->XferCount;

        __HAL_I2C_CLEAR_SR(hi2c);
        __HAL_I2C_CLEAR_IF(hi2c, I2C_IT_EVT | I2C_IT_TXE | I2C_IT_ERR);

        /* Clear TXFIFO */
        __HAL_I2C_CLR_TXDR(hi2c);
        
        if ((hi2c->XferCount > 0U) && (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_TXE) == SET))
        {
            hi2c->Instance->TXDR = *hi2c->pBuffPtr;
            hi2c->pBuffPtr++;
            hi2c->XferCount--;
        }
        #ifndef LE501X
        /* Clear TXE irq on platforms except for LE501X */
        __HAL_I2C_CLEAR_IF(hi2c, I2C_IT_TXE);
        #endif

        __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_TXE | I2C_IT_ERR);
        return HAL_OK;
    }
    else
    {
        return HAL_BUSY;
    }
}

HAL_StatusTypeDef HAL_I2C_Slave_Transmit(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint8_t Size, uint32_t Timeout)
{
    uint32_t tickstart = systick_get_value();
    if (hi2c->State == HAL_I2C_STATE_READY)
    {
        if (pData == NULL || Size == 0U || 0 == Timeout)
        {
            return HAL_ERROR;
        }
        I2C_speed_config_calc_slave(hi2c);
        /* Don't check busy flag here. The slave might be in working(addr matched) status. */
        /* The slave can't ensure the function is being excuted when address is matched. */
        /* So the app may need to call this function periodically to check addr matched event while
           the busy flag might have already been set.*/
        // if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG, tickstart) != HAL_OK)
        // {
        //     return HAL_BUSY;
        // }
        __HAL_I2C_ENABLE(hi2c);

        hi2c->State = HAL_I2C_STATE_BUSY_TX;
        hi2c->Mode = HAL_I2C_MODE_SLAVE;
        hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

        hi2c->pBuffPtr = pData;
        hi2c->XferCount = Size;
        hi2c->XferSize = hi2c->XferCount;

        __HAL_I2C_CLR_TXDR(hi2c);
        __HAL_I2C_CLEAR_IF(hi2c, I2C_IT_EVT | I2C_IT_TXE | I2C_IT_ERR);

        if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_ADDR, RESET, Timeout, tickstart) != HAL_OK)
        {
            __HAL_I2C_DISABLE(hi2c);
            return HAL_ERROR;
        }
        __HAL_I2C_CLEAR_ADDRFLAG(hi2c);

        while (1)
        {
            DELAY_US(i2c_hw_state_switch_delay_us[hi2c->Init.ClockSpeed]); // wait for S_HOLD state
            uint32_t cpu_stat = enter_critical();
            I2C_FIFO_TX(hi2c);
            exit_critical(cpu_stat);
            if (0 == hi2c->XferCount)
            {
                break;
            }
            /* We can't use i2c_txflvnfandstop_poll, because we have to monitor and skip the ACK before TXFIFO empty. */
            if (I2C_WaitOnFLVUntilTimeout(i2c_txflveandstop_poll, hi2c, Timeout, tickstart) != HAL_OK)
            {
                /* Stop event is detected in I2C_WaitOnFLVUntilTimeout. We handle this out of the while loop */
                if (hi2c->ErrorCode == HAL_I2C_ERROR_BERR)
                {
                    break; 
                }
                /* Slave failed to send data to bus in time. It's likely to happen when the bus is hold by master.*/
                hi2c->XferCount += __HAL_I2C_GET_TXFLV(hi2c);
                __HAL_I2C_DISABLE(hi2c);
                return HAL_ERROR;
            }
        }
        /* Wait for stop sent */
        if (I2C_WaitOnItSourceUntilTimeout(hi2c, I2C_RIF_STOPRI_MASK, RESET, Timeout, tickstart) != HAL_OK)
        {
            /* Stop event timeout. It's likely to happen when the bus is hold by master.*/
            hi2c->XferCount += __HAL_I2C_GET_TXFLV(hi2c);
            __HAL_I2C_DISABLE(hi2c);
            return HAL_ERROR;
        }
        hi2c->XferCount += __HAL_I2C_GET_TXFLV(hi2c);
        if (0 == hi2c->XferCount)
        {
            hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
        }
        else
        {
            hi2c->ErrorCode = HAL_I2C_ERROR_BERR;
        }
        __HAL_I2C_CLEAR_FLAG(hi2c, I2C_CFR_STOPCF_MASK);

        hi2c->State = HAL_I2C_STATE_READY;
        hi2c->Mode = HAL_I2C_MODE_NONE;
        __HAL_I2C_DISABLE(hi2c);
        return hi2c->ErrorCode == HAL_I2C_ERROR_NONE ? HAL_OK : HAL_ERROR;
    }
    else
    {
        return HAL_BUSY;
    }
}

HAL_StatusTypeDef HAL_I2C_Slave_Receive_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint8_t Size)
{
    if (hi2c->State == HAL_I2C_STATE_READY)
    {
        if (pData == NULL || Size == 0)
        {
            return HAL_ERROR;
        }
        I2C_speed_config_calc_slave(hi2c);
        __HAL_I2C_ENABLE(hi2c);

        hi2c->State = HAL_I2C_STATE_BUSY_RX;
        hi2c->Mode = HAL_I2C_MODE_SLAVE;
        hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

        hi2c->pBuffPtr = pData;
        hi2c->XferCount = Size;
        hi2c->XferSize    = hi2c->XferCount;

        CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_AUTOEND_MASK | I2C_CR2_RELOAD_MASK | I2C_CR2_NBYTES_MASK);
        if (1 == Size)
        {
            SET_BIT(hi2c->Instance->CR2, I2C_CR2_NACK_MASK);
        }
        else
        {
            __HAL_I2C_NBYTES_SET(hi2c, Size - 1);
        }
        __HAL_I2C_CLEAR_SR(hi2c);
        __HAL_I2C_CLEAR_IF(hi2c, I2C_IT_EVT | I2C_IT_RXNE | I2C_IT_ERR);
        __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_RXNE | I2C_IT_ERR);

        return HAL_OK;
    }
    else
    {
        return HAL_BUSY;
    }
}

HAL_StatusTypeDef HAL_I2C_Slave_Receive(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint8_t Size, uint32_t Timeout)
{
    uint32_t tickstart = systick_get_value();
    if (hi2c->State == HAL_I2C_STATE_READY)
    {
        if (pData == NULL || Size == 0U || 0 == Timeout)
        {
            return HAL_INVALIAD_PARAM;
        }
        I2C_speed_config_calc_slave(hi2c);
        /* Don't check busy flag here. The reason is similar with HAL_I2C_Slave_Transmit */
        // if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG, tickstart) != HAL_OK)
        // {
        //     return HAL_BUSY;
        // }
        __HAL_I2C_ENABLE(hi2c);

        hi2c->State       = HAL_I2C_STATE_BUSY_RX;
        hi2c->Mode        = HAL_I2C_MODE_MASTER;
        hi2c->ErrorCode   = HAL_I2C_ERROR_NONE;

        hi2c->pBuffPtr    = pData;
        hi2c->XferCount   = Size;
        hi2c->XferSize    = hi2c->XferCount;

        CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_AUTOEND_MASK | I2C_CR2_RELOAD_MASK | I2C_CR2_NBYTES_MASK);
        if (1 == Size)
        {
            SET_BIT(hi2c->Instance->CR2, I2C_CR2_NACK_MASK);
        }
        else
        {
            __HAL_I2C_NBYTES_SET(hi2c, Size - 1);
        }
        if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_ADDR, RESET, Timeout, tickstart) != HAL_OK)
        {
            return HAL_ERROR;
        }

        __HAL_I2C_CLEAR_ADDRFLAG(hi2c);
        if (hi2c->XferCount >= I2C_FIFO_DEPTH)
        {
            while (1)
            {
                /* Ensure the RXFIFO is full */
                if (I2C_WaitOnRxFifoFullUntilTimeout(hi2c, Timeout, tickstart) != HAL_OK)
                {
                    /* Timeout is detected. We still check if there is any data unread in RXFIFO */
                    I2C_FIFO_RX(hi2c);
                    if (0 == hi2c->XferCount)
                    {
                        break;
                    }
                    __HAL_I2C_DISABLE(hi2c);
                    goto RECEIVE_FINISH;
                }
                uint32_t cpu_stat = enter_critical();
                if (hi2c->XferCount <= I2C_FIFO_DEPTH + I2C_FIFO_DEPTH && hi2c->XferCount > I2C_FIFO_DEPTH)
                {
                    __HAL_I2C_RELOAD_ENABLE(hi2c);
                    __HAL_I2C_NBYTES_SET(hi2c, hi2c->XferCount - 1 - I2C_FIFO_DEPTH);
                    __HAL_I2C_RELOAD_DISABLE(hi2c);
                }
                else if (hi2c->XferCount == I2C_FIFO_DEPTH)
                {
                    __HAL_I2C_RELOAD_ENABLE(hi2c);
                    __HAL_I2C_NBYTES_SET(hi2c, 0);
                    __HAL_I2C_RELOAD_DISABLE(hi2c);
                }
                /* Don't read data without checking XferCount. Refer to I2C_SlaveReceive_RXNE. */
                for (uint8_t i = 0; i < I2C_FIFO_DEPTH; i++)
                {
                    *hi2c->pBuffPtr = (uint8_t)(hi2c->Instance->RXDR);
                    hi2c->pBuffPtr++;
                    hi2c->XferCount--;
                }
                exit_critical(cpu_stat);
                if (hi2c->XferCount < I2C_FIFO_DEPTH)
                {
                    break;
                }
            }
        }
        /* Wait for stop sent */
        if (I2C_WaitOnItSourceUntilTimeout(hi2c, I2C_RIF_STOPRI_MASK, RESET, Timeout, tickstart) != HAL_OK)
        {
            __HAL_I2C_DISABLE(hi2c);
            goto RECEIVE_FINISH;
        }

        I2C_FIFO_RX(hi2c);

        if (0 == hi2c->XferCount)
        {
            hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
        }
        __HAL_I2C_CLEAR_FLAG(hi2c, I2C_CFR_STOPCF_MASK);
        hi2c->State = HAL_I2C_STATE_READY;
        hi2c->Mode = HAL_I2C_MODE_NONE;

RECEIVE_FINISH:
        __HAL_I2C_DISABLE(hi2c);
        HAL_I2C_hw_Init(hi2c); // workaround xxx

        return hi2c->ErrorCode == HAL_I2C_ERROR_NONE ? HAL_OK : HAL_ERROR;
    }
    else
    {
        return HAL_BUSY;
    }
}

void HAL_I2C_IRQHandler(I2C_HandleTypeDef *hi2c)
{
    uint32_t sr1itflags = hi2c->Instance->SR;
    uint32_t itsources  = hi2c->Instance->IFM;
    HAL_I2C_StateTypeDef CurrentState = hi2c->State;

    if (hi2c->Mode == HAL_I2C_MODE_MASTER)
    {
        if (I2C_CHECK_IT_SOURCE(itsources, I2C_IER_ADDRIE_MASK) != RESET)
        {
            I2C_ADDR(hi2c, sr1itflags);
        }
        else if (I2C_CHECK_IT_SOURCE(itsources, I2C_IER_STOPIE_MASK) != RESET)
        {
            __HAL_I2C_CLEAR_IF(hi2c, I2C_ICR_STOPIC_MASK); 
            I2C_STOPF(hi2c);
        }
        else if (CurrentState == HAL_I2C_STATE_BUSY_TX)
        {
            if (I2C_CHECK_IT_SOURCE(itsources, I2C_IT_TXE) != RESET)
            {
                I2C_MasterTransmit_TXE(hi2c);
            }
        }
        else if (CurrentState == HAL_I2C_STATE_BUSY_RX)
        {
            if (I2C_CHECK_IT_SOURCE(itsources, I2C_IT_RXNE) != RESET)
            {
                I2C_MasterReceive_RXNE(hi2c);
            }
        }
    }
    else
    {
        /* Check ADDR flag */
        if (I2C_CHECK_IT_SOURCE(itsources, I2C_IER_ADDRIE_MASK) != RESET)
        {
            I2C_ADDR(hi2c, sr1itflags);
        }
        else if (I2C_CHECK_IT_SOURCE(itsources, I2C_IER_STOPIE_MASK) != RESET)
        {
            __HAL_I2C_CLEAR_IF(hi2c, I2C_ICR_STOPIC_MASK);
            I2C_STOPF(hi2c);
        }/* Slave transmit */
        else if (CurrentState == HAL_I2C_STATE_BUSY_TX)
        {
            if (I2C_CHECK_IT_SOURCE(itsources, I2C_IT_TXE) != RESET)
            { 
                I2C_SlaveTransmit_TXE(hi2c);
            }
        }/* Slave receive */
        else if (CurrentState == HAL_I2C_STATE_BUSY_RX)
        {
            if (I2C_CHECK_IT_SOURCE(itsources, I2C_IT_RXNE) != RESET)
            { 
                I2C_SlaveReceive_RXNE(hi2c);
            }
        }
    }
    /* Check NACK flag */
    if (I2C_CHECK_IT_SOURCE(itsources, I2C_IER_NACKIE_MASK) != RESET)
    {
        __HAL_I2C_CLEAR_IF(hi2c, I2C_ICR_NACKIC_MASK); 
        if (I2C_CHECK_FLAG(sr1itflags, I2C_FLAG_NACK) != RESET)
        {
            __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_NACK);
        }
    }
    /* Call the Error Callback in case of Error detected */
    if (hi2c->ErrorCode != HAL_I2C_ERROR_NONE)
    {
        // hi2c->ErrorCode |= error;
        I2C_ITError(hi2c);
    }
}

__weak void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    UNUSED(hi2c);
}

__weak void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    UNUSED(hi2c);
}

__weak void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    UNUSED(hi2c);
}

__weak void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    UNUSED(hi2c);
}

__weak void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode)
{
    UNUSED(hi2c);
    UNUSED(TransferDirection);
    UNUSED(AddrMatchCode);
}

__weak void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c)
{
    UNUSED(hi2c);
}

HAL_I2C_StateTypeDef HAL_I2C_GetState(I2C_HandleTypeDef *hi2c)
{
    return hi2c->State;
}

HAL_I2C_ModeTypeDef HAL_I2C_GetMode(I2C_HandleTypeDef *hi2c)
{
    return hi2c->Mode;
}

uint32_t HAL_I2C_GetError(I2C_HandleTypeDef *hi2c)
{
    return hi2c->ErrorCode;
}

static void I2C_MasterTransmit_TXE(I2C_HandleTypeDef *hi2c)
{
#ifdef LE501X
    __HAL_I2C_CLEAR_IF(hi2c, I2C_ICR_TXEIC_MASK);
    I2C_FIFO_TX(hi2c);
#else
    I2C_FIFO_TX(hi2c);
    __HAL_I2C_CLEAR_IF(hi2c, I2C_ICR_TXEIC_MASK);
#endif
}

static void I2C_MasterReceive_RXNE(I2C_HandleTypeDef *hi2c)
{
#ifdef LE501X
    __HAL_I2C_CLEAR_IF(hi2c, I2C_ICR_RXNEIC_MASK);
    I2C_FIFO_RX(hi2c);
#else
    I2C_FIFO_RX(hi2c);
    __HAL_I2C_CLEAR_IF(hi2c, I2C_ICR_RXNEIC_MASK); 
#endif
}

static void I2C_SlaveTransmit_TXE(I2C_HandleTypeDef *hi2c)
{
    DELAY_US(i2c_hw_state_switch_delay_us[hi2c->Init.ClockSpeed]); // wait for S_HOLD state
    uint32_t cpu_stat = enter_critical();
    while (__HAL_I2C_GET_TXFLV(hi2c) < I2C_FIFO_DEPTH && hi2c->XferCount > 0)
    {
        hi2c->Instance->TXDR = (uint8_t)(*hi2c->pBuffPtr);
        hi2c->pBuffPtr++;
        hi2c->XferCount--;
    }
    __HAL_I2C_CLEAR_IF(hi2c, I2C_ICR_TXEIC_MASK);
    exit_critical(cpu_stat);
}

static void I2C_SlaveReceive_RXNE(I2C_HandleTypeDef *hi2c)
{
    uint32_t cpu_stat = enter_critical();
    if (hi2c->XferCount <= I2C_FIFO_DEPTH + I2C_FIFO_DEPTH && hi2c->XferCount > I2C_FIFO_DEPTH)
    {
        __HAL_I2C_RELOAD_ENABLE(hi2c);
        __HAL_I2C_NBYTES_SET(hi2c, hi2c->XferCount - 1 - I2C_FIFO_DEPTH);
        __HAL_I2C_RELOAD_DISABLE(hi2c);
    }
    else if (hi2c->XferCount == I2C_FIFO_DEPTH)
    {
        __HAL_I2C_RELOAD_ENABLE(hi2c);
        __HAL_I2C_NBYTES_SET(hi2c, 0);
        __HAL_I2C_RELOAD_DISABLE(hi2c);
    }
    // I2C_FIFO_RX(hi2c);
    /* Don't read data from RXFIFO without checking XferCount like code above. */
    /* So we just read I2C_FIFO_DEPTH data in case we miss the length we are monitoring. */
    for (uint8_t i = 0; i < I2C_FIFO_DEPTH; i++)
    {
        *hi2c->pBuffPtr = (uint8_t)(hi2c->Instance->RXDR);
        hi2c->pBuffPtr++;
        hi2c->XferCount--;
    }
    __HAL_I2C_CLEAR_IF(hi2c, I2C_ICR_RXNEIC_MASK);
    exit_critical(cpu_stat);
}

static void I2C_ADDR(I2C_HandleTypeDef *hi2c, uint32_t sr1itflags)
{ 
    __HAL_I2C_CLEAR_IF(hi2c, I2C_ICR_ADDRIC_MASK);
    __HAL_I2C_CLEAR_ADDRFLAG(hi2c);
    uint8_t dir = ((sr1itflags & I2C_SR_DIR_MASK) >> I2C_SR_DIR_POS) == 0? I2C_DIRECTION_RECEIVE : I2C_DIRECTION_TRANSMIT;
    uint16_t addrCode = (sr1itflags & I2C_SR_ADDCODE_MASK) >> I2C_SR_ADDCODE_POS;
    HAL_I2C_AddrCallback(hi2c, dir, addrCode);
    if (hi2c->State == HAL_I2C_STATE_BUSY_TX)
    {
        if (hi2c->Mode == HAL_I2C_MODE_MASTER)
        {
            I2C_FIFO_TX(hi2c);
        }
    }
}

static void I2C_STOPF(I2C_HandleTypeDef *hi2c)
{
    HAL_I2C_StateTypeDef CurrentState = hi2c->State;
    HAL_I2C_ModeTypeDef CurrentMode = hi2c->Mode;
    __HAL_I2C_DISABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_RXNE | I2C_IT_TXE | I2C_IT_TC | I2C_IT_ERR);
    __HAL_I2C_CLEAR_STOPFLAG(hi2c);

    bool tx_dma_en = LL_I2C_IsEnabledDMAReq_TX(hi2c->Instance);
    bool rx_dma_en = LL_I2C_IsEnabledDMAReq_RX(hi2c->Instance);

    if (!tx_dma_en && !rx_dma_en)
    {
        if (CurrentState == HAL_I2C_STATE_BUSY_RX)
        {
            I2C_FIFO_RX(hi2c);
        }
        else if (CurrentState == HAL_I2C_STATE_BUSY_TX)
        {
            hi2c->XferCount += __HAL_I2C_GET_TXFLV(hi2c);
        }

        if (hi2c->XferCount != 0U)
        {
            hi2c->ErrorCode |= HAL_I2C_ERROR_SIZE;
        }
    }

    if (hi2c->ErrorCode != HAL_I2C_ERROR_NONE)
    {
        /* handle error at the end of irq handler. */
        // I2C_ITError(hi2c);
    }
    else
    {
        __HAL_I2C_DISABLE(hi2c);
        HAL_I2C_hw_Init(hi2c); // workaround xxx
        hi2c->Mode = HAL_I2C_MODE_NONE;
        hi2c->State = HAL_I2C_STATE_READY;
        if (CurrentState == HAL_I2C_STATE_BUSY_TX)
        {
            if (CurrentMode == HAL_I2C_MODE_MASTER)
            {
                if (tx_dma_en)
                {
                    REG_FIELD_WR(hi2c->Instance->CR1, I2C_CR1_TXDMAEN, 0);
                    HAL_I2C_DMA_TxCpltCallback(hi2c);
                }
                else
                {
                    HAL_I2C_MasterTxCpltCallback(hi2c);
                }
            }
            else
            {
                HAL_I2C_SlaveTxCpltCallback(hi2c);
            }
        }
        else if (CurrentState == HAL_I2C_STATE_BUSY_RX)
        {
            if (CurrentMode == HAL_I2C_MODE_MASTER)
            {
                if (rx_dma_en)
                {
                    REG_FIELD_WR(hi2c->Instance->CR1, I2C_CR1_RXDMAEN, 0);
                    HAL_I2C_DMA_RxCpltCallback(hi2c);
                }
                else
                {
                    HAL_I2C_MasterRxCpltCallback(hi2c);
                }
            }
            else
            {
                HAL_I2C_SlaveRxCpltCallback(hi2c);
            }
        }
        // HAL_I2C_hw_Init(hi2c); // workaround xxx
        // hi2c->Mode = HAL_I2C_MODE_NONE;
        // hi2c->State = HAL_I2C_STATE_READY;
    }
}

static void I2C_ITError(I2C_HandleTypeDef *hi2c)
{
    /* Handle last data if any */
    if (hi2c->XferCount > 0)
    {
        if (hi2c->State == HAL_I2C_STATE_BUSY_RX)
        {
            I2C_FIFO_RX(hi2c);
        }
    }
    hi2c->State = HAL_I2C_STATE_READY;
    __HAL_I2C_DISABLE(hi2c);
    HAL_I2C_hw_Init(hi2c); // workaround xxx
    HAL_I2C_ErrorCallback(hi2c);
    // HAL_I2C_hw_Init(hi2c); // workaround xxx
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
}

static HAL_StatusTypeDef I2C_MasterRequestRead_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint32_t Timeout, uint32_t Tickstart, bool Read)
{
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
    if (I2C_WaitOnMasterAddressFlagUntilTimeout(hi2c, I2C_CR2_START_MASK, Timeout, Tickstart) != HAL_OK)
    {
        return HAL_ERROR;
    }
    return HAL_OK;
}

static bool i2c_flag_rxfifo_full_poll(va_list va)
{
    I2C_HandleTypeDef *hi2c = va_arg(va,I2C_HandleTypeDef *);
    return __HAL_I2C_GET_RXFLV(hi2c) == I2C_FIFO_DEPTH ? true : false;
}

static bool i2c_flag_poll(va_list va)
{
    I2C_HandleTypeDef *hi2c = va_arg(va,I2C_HandleTypeDef *);
    uint32_t flag = va_arg(va,uint32_t);
    uint32_t Status = va_arg(va,uint32_t);
    return __HAL_I2C_GET_FLAG(hi2c, flag) != Status ? true : false;
}

static bool i2c_itsource_poll(va_list va)
{
    I2C_HandleTypeDef *hi2c = va_arg(va,I2C_HandleTypeDef *);
    uint32_t itsource = va_arg(va,uint32_t);
    uint32_t Status = va_arg(va,uint32_t);
    return __HAL_I2C_GET_IT_RIF(hi2c, itsource) != Status ? true : false;
}

static HAL_StatusTypeDef I2C_WaitOnRxFifoFullUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Timeout, uint32_t Tickstart)
{
    uint32_t timeout = SYSTICK_MS2TICKS(Timeout);
    if (Timeout != HAL_MAX_DELAY)
    {
        if(systick_poll_timeout(Tickstart,timeout,i2c_flag_rxfifo_full_poll,hi2c))
        {
            hi2c->State             = HAL_I2C_STATE_READY;
            hi2c->Mode              = HAL_I2C_MODE_NONE;
            hi2c->ErrorCode         |= HAL_I2C_ERROR_TIMEOUT;
            return HAL_ERROR;
        }
    }
    else
    {
        while (__HAL_I2C_GET_RXFLV(hi2c) < I2C_FIFO_DEPTH);
    }
    return HAL_OK;
}

static HAL_StatusTypeDef I2C_WaitOnFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Flag, FlagStatus Status, uint32_t Timeout, uint32_t Tickstart)
{
    uint32_t timeout = SYSTICK_MS2TICKS(Timeout);
    if (Timeout != HAL_MAX_DELAY)
    {
        if(systick_poll_timeout(Tickstart,timeout,i2c_flag_poll,hi2c,Flag,Status))
        {
            hi2c->State             = HAL_I2C_STATE_READY;
            hi2c->Mode              = HAL_I2C_MODE_NONE;
            hi2c->ErrorCode         |= HAL_I2C_ERROR_TIMEOUT;
            return HAL_ERROR;
        }
    }
    else
    {
        while (__HAL_I2C_GET_FLAG(hi2c, Flag) == Status);
    }
    return HAL_OK;
}

static HAL_StatusTypeDef I2C_WaitOnItSourceUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t ItSource, FlagStatus Status, uint32_t Timeout, uint32_t Tickstart)
{
    uint32_t timeout = SYSTICK_MS2TICKS(Timeout);
    if (Timeout != HAL_MAX_DELAY)
    {
        if(systick_poll_timeout(Tickstart,timeout,i2c_itsource_poll,hi2c,ItSource,Status))
        {
            hi2c->State             = HAL_I2C_STATE_READY;
            hi2c->Mode              = HAL_I2C_MODE_NONE;
            hi2c->ErrorCode         |= HAL_I2C_ERROR_TIMEOUT;
            return HAL_ERROR;
        }
    }
    else
    {
        while (__HAL_I2C_GET_IT_RIF(hi2c, ItSource) == Status);
    }
    return HAL_OK;
}

static bool i2c_CR2flag_poll(va_list va)
{
    I2C_HandleTypeDef *hi2c = va_arg(va,I2C_HandleTypeDef *);
    uint32_t flag = va_arg(va,uint32_t);
    return __HAL_I2C_GET_CR2_FLAG(hi2c, flag) == RESET ? true : false;
}

static HAL_StatusTypeDef I2C_WaitOnMasterAddressFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Flag, uint32_t Timeout, uint32_t Tickstart)
{
    uint32_t timeout = SYSTICK_MS2TICKS(Timeout);
    if (Timeout != HAL_MAX_DELAY)
    {
        if(systick_poll_timeout(Tickstart,timeout,i2c_CR2flag_poll,hi2c,Flag))
        {
            hi2c->State               = HAL_I2C_STATE_READY;
            hi2c->Mode                = HAL_I2C_MODE_NONE;
            hi2c->ErrorCode           |= HAL_I2C_ERROR_TIMEOUT;
            return HAL_ERROR;
        }
    }
    else
    {
        while (__HAL_I2C_GET_CR2_FLAG(hi2c,Flag)  == SET)
        {
            if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_NACK) == SET)
            {
                __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_NACK);
                hi2c->State               = HAL_I2C_STATE_READY;
                hi2c->Mode                = HAL_I2C_MODE_NONE;
                hi2c->ErrorCode           = HAL_I2C_ERROR_NACKF;
                return HAL_ERROR;
            }
        }
    }   
   return HAL_OK;
}

static bool i2c_check_stop_return_berr(I2C_HandleTypeDef *hi2c)
{
    if (__HAL_I2C_GET_IT_RIF(hi2c, I2C_RIF_STOPRI_MASK) == SET)
    {
        // hi2c->State = HAL_I2C_STATE_READY;
        // hi2c->Mode = HAL_I2C_MODE_NONE;
        hi2c->ErrorCode = HAL_I2C_ERROR_BERR;
        return true;
    }
    return false;
}

static bool i2c_rxflvnzandstop_poll(va_list va)
{
    I2C_HandleTypeDef *hi2c = va_arg(va,I2C_HandleTypeDef *);
    if (__HAL_I2C_GET_RXFLV(hi2c) > 0)
    {
        return true;
    }
    else
    {
        /* When read, I2C master will never detect stop event unless all the data receiving is finished */
        /* So stop event check is only necessary for I2C slave */
        if (hi2c->Mode == HAL_I2C_MODE_SLAVE)
        {
            return i2c_check_stop_return_berr(hi2c);
        }
        return false;
    }
}

static bool i2c_txflveandstop_poll(va_list va)
{
    I2C_HandleTypeDef *hi2c = va_arg(va,I2C_HandleTypeDef *);
    if (__HAL_I2C_GET_TXFLV(hi2c) == 0)
    {
        return true;
    }
    else
    {
        /* When write, I2C master is likely to receive NACK and transmit stop before all data sent */
        // if (hi2c->Mode == HAL_I2C_MODE_SLAVE)
        {
            return i2c_check_stop_return_berr(hi2c);
        }
    }
}

static bool i2c_txflvnfandstop_poll(va_list va)
{
    I2C_HandleTypeDef *hi2c = va_arg(va,I2C_HandleTypeDef *);
    if (__HAL_I2C_GET_TXFLV(hi2c) < I2C_FIFO_DEPTH)
    {
        return true;
    }
    else
    {
        /* When write, I2C master is likely to receive NACK and transmit stop before all data sent */
        // if (hi2c->Mode == HAL_I2C_MODE_SLAVE)
        {
            return i2c_check_stop_return_berr(hi2c);
        }
    }
}

static HAL_StatusTypeDef I2C_WaitOnFLVUntilTimeout(bool (*poll)(va_list), ...)
{
    va_list va;
    va_start(va, poll);
    I2C_HandleTypeDef *hi2c = va_arg(va, I2C_HandleTypeDef *);
    uint32_t Timeout = va_arg(va, uint32_t);
    uint32_t timeout = SYSTICK_MS2TICKS(Timeout);
    uint32_t Tickstart = va_arg(va, uint32_t);

    if (Timeout != HAL_MAX_DELAY)
    {
        if(systick_poll_timeout(Tickstart,timeout,poll,hi2c))
        {
            hi2c->State               = HAL_I2C_STATE_READY;
            hi2c->Mode                = HAL_I2C_MODE_NONE;
            hi2c->ErrorCode           |= HAL_I2C_ERROR_TIMEOUT;
            return HAL_ERROR;
        }
    }
    else
    {
        va_start(va, poll);
        while (!poll(va));
    }
    va_end(va);
    if(hi2c->ErrorCode == HAL_I2C_ERROR_BERR)
    {
        return HAL_ERROR;
    }
    else
    {
        return HAL_OK;
    }
}
