#include "ls_hal_dac.h"
#include "ls_msp_dac.h"
#include "ls_hal_dmacv2.h"
#include "field_manipulate.h"
#include "platform.h"
#include "systick.h"

#define DAC_DISABLE_TIMEOUT     2

static bool dac_isenable_poll(va_list va)
{
    DAC_HandleTypeDef *hdac = va_arg(va, DAC_HandleTypeDef *);
    uint32_t flag = va_arg(va, uint32_t);
    if ((DAC1_IS_ENABLE(hdac) == flag) || (DAC2_IS_ENABLE(hdac) == flag))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void HAL_DAC1_Config(DAC_HandleTypeDef *hdac)
{
     /* DAC1 enable */
        SET_BIT(hdac->Instance->DAC_ANA, DAC_EN_DAC1_MASK);

        /* DAC1 channel enable */
        SET_BIT(hdac->Instance->DAC_CR, DAC_EN1_MASK);

        /* DAC1 trigger enable */
        REG_FIELD_WR(hdac->Instance->DAC_CR, DAC_TEN1, 1);

        /* DAC1 trigger selection */
        REG_FIELD_WR(hdac->Instance->DAC_CR, DAC_TSEL1, hdac->DAC1_Trigger);

        /* DAC1 output switch enable */
        REG_FIELD_WR(hdac->Instance->DAC_CR, DAC_BOFF1, 1);

        /* DAC1 wave select */
        REG_FIELD_WR(hdac->Instance->DAC_CR, DAC_WAVE1, hdac->DAC1_wave);

        /* DAC1 Select the amplitude of the triangular wave */
        REG_FIELD_WR(hdac->Instance->DAC_CR, DAC_MAMP1, hdac->DAC1_Mamp);

        /* DAC1 output gain control */
        REG_FIELD_WR(hdac->Instance->DAC_ANA, DAC_GC_DAC1, 3);
}

void HAL_DAC2_Config(DAC_HandleTypeDef *hdac)
{
     /* DAC2 enable */
        SET_BIT(hdac->Instance->DAC_ANA, DAC_EN_DAC2_MASK);

        /* DAC2 channel enable */
        SET_BIT(hdac->Instance->DAC_CR, DAC_EN2_MASK);

        /* DAC2 trigger enable */
        REG_FIELD_WR(hdac->Instance->DAC_CR, DAC_TEN2, 1);

        /* DAC2 trigger selection */
        REG_FIELD_WR(hdac->Instance->DAC_CR, DAC_TSEL2, hdac->DAC2_Trigger);

        /* DAC2 output switch enable */
        REG_FIELD_WR(hdac->Instance->DAC_CR, DAC_BOFF2, 1);

        /* DAC2 wave select */
        REG_FIELD_WR(hdac->Instance->DAC_CR, DAC_WAVE2, hdac->DAC2_wave);

        /* DAC2 Select the amplitude of the triangular wave */
        REG_FIELD_WR(hdac->Instance->DAC_CR, DAC_MAMP2, hdac->DAC2_Mamp);

        /* DAC2 output gain control */
        REG_FIELD_WR(hdac->Instance->DAC_ANA, DAC_GC_DAC2, 3);
}

HAL_StatusTypeDef HAL_DAC_Init(DAC_HandleTypeDef *hdac)
{
    HAL_LSDAC_MSP_Init();
    HAL_StatusTypeDef status = HAL_OK;
    switch (hdac->DACx)
    {
    case DAC1:
        HAL_DAC1_Config(hdac);
        break;
    case DAC2:
        HAL_DAC2_Config(hdac);
        break;    
    default:
        HAL_DAC1_Config(hdac);
        HAL_DAC2_Config(hdac);
        break;
    }
    return status;
}

HAL_StatusTypeDef HAL_DAC_DeInit()
{
    HAL_LSDAC_MSP_DeInit();
    return HAL_OK;
}

HAL_StatusTypeDef DAC_ConversionStop_Disable(DAC_HandleTypeDef* hdac)
{
    uint32_t tickstart = 0U;
    uint32_t timeout = SYSTICK_MS2TICKS(DAC_DISABLE_TIMEOUT);

    /* Verification if DAC is not already disabled */
    if ((DAC1_IS_ENABLE(hdac) || DAC2_IS_ENABLE(hdac)) != RESET)
    {
        /* Disable the DAC peripheral */
        __HAL_DAC1_DISABLE(hdac);

        /* Get tick count */
        tickstart = systick_get_value();

        /* Wait for DAC effectively disabled */
        if (systick_poll_timeout(tickstart, timeout, dac_isenable_poll, hdac, RESET))
        {
            return HAL_ERROR;
        }
    }
    return HAL_OK;
}

HAL_StatusTypeDef HAL_DAC_Stop(DAC_HandleTypeDef *hdac)
{
    HAL_StatusTypeDef status = HAL_OK;

    /* Disable DAC peripheral */
    status = DAC_ConversionStop_Disable(hdac);

    return status;
}

HAL_StatusTypeDef HAL_DAC_SetValue(DAC_HandleTypeDef *hdac, uint32_t Alignment, uint32_t Data)
{
    uint32_t Val = 0UL;
    /* Check the parameters */
    LS_ASSERT(IS_DAC12_ALIGN(Alignment));
    LS_ASSERT(IS_DAC12_DATA(Data));

    Val = (uint32_t)hdac->Instance;
    switch (hdac->DACx)
    {
    case DAC1:
        Val += DAC_DHR12R1_ALIGNMENT(Alignment);
        break;
    case DAC2:
        Val += DAC_DHR12R2_ALIGNMENT(Alignment);
        break;
    default:
        Val += DAC_DHR12RD_ALIGNMENT(Alignment);
        break;
    }

    *(uint32_t *)Val = Data;
    switch (hdac->DACx)
    {
    case DAC1:
        SET_BIT(hdac->Instance->DAC_SWTRIGR, DAC_SWTRIG1_MASK);
        break;
    case DAC2:
        SET_BIT(hdac->Instance->DAC_SWTRIGR, DAC_SWTRIG2_MASK);
    default:
        WRITE_REG(hdac->Instance->DAC_SWTRIGR,DAC_SWTRIG1_MASK|DAC_SWTRIG2_MASK);
        break;
    }
    return HAL_OK;
}

uint32_t HAL_DAC_GetValue(DAC_HandleTypeDef *hdac)
{
    uint32_t result = 0;
    switch (hdac->DACx)
    {
    case DAC1:
        result = hdac->Instance->DAC_DOR1;
        break;
    case DAC2:
        result = hdac->Instance->DAC_DOR2;
        break;    
    default:
        result = hdac->Instance->DAC_DOR1 | hdac->Instance->DAC_DOR2 << 13;
        break;
    }
    return result;
}