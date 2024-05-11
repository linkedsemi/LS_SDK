#include <string.h>
#include <stddef.h>
#include "ls_hal_pwm.h"
#include "field_manipulate.h"
#include "reg_sysc_awo.h"
#include "reg_sysc_per.h"
#include "ls_msp_pwm.h"
#include "co_math.h"

__attribute__((weak)) void HAL_PWM_START_Callback(pwm_channel_t channel) {}
__attribute__((weak)) void HAL_PWM_STOP_Callback(pwm_channel_t channel) {}

HAL_StatusTypeDef HAL_PWM_Init(uint8_t pwm_pre_div)
{
    if (pwm_pre_div == 0)
    {
        return HAL_INVALIAD_PARAM;
    }
    
    HAL_PWM_MSP_Init();
    PWM->INTR_MSK = 0;
    PWM->PWM_PRE_DIV = pwm_pre_div - 1;

    return HAL_OK;
}

HAL_StatusTypeDef HAL_PWM_DeInit(void)
{
    HAL_PWM_MSP_DeInit();
    return HAL_OK;
}

HAL_StatusTypeDef HAL_PWM_SetConfig(pwm_channel_t channel, PWM_Param *param)
{
    PWM->PWM_PARAM[channel].PWM_NUM = param->pwm_num;
    PWM->PWM_PARAM[channel].PWM_CYC = param->pwm_cyc;
    PWM->PWM_PARAM[channel].PWM_HIGH = param->pol == param->cmp ? param->pwm_high : param->pwm_cyc - param->pwm_high;
    PWM->PWM_CTRL[channel] = FIELD_BUILD(PWM_POL, 0) |
                             FIELD_BUILD(PWM_CMP, 0) |
                             FIELD_BUILD(PWM_MODE, param->mode) |
                             FIELD_BUILD(PWM_DMA_EN, param->dma_en);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_PWM_Start(pwm_channel_t channel)
{
    PWM->INTR_CLR = CO_BIT(channel * 2);
    PWM->INTR_MSK |= CO_BIT(channel * 2);
    PWM->PWM_EN |= CO_BIT(channel);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_PWM_Stop(pwm_channel_t channel)
{
    PWM->INTR_CLR = CO_BIT(channel * 2 + 1);
    PWM->INTR_MSK |= CO_BIT(channel * 2 + 1);
    PWM->PWM_EN |= CO_BIT(channel + 16);
    return HAL_OK;
}

void HAL_PWM_IRQHandler()
{
    uint32_t isrflags = PWM->INTR_STT;
    for (uint8_t i = 0; i < 8; i++)
    {
        if (isrflags & CO_BIT(i * 2))
        {
            PWM->INTR_MSK &= ~CO_BIT(i * 2);
            PWM->INTR_CLR = CO_BIT(i * 2);
            HAL_PWM_START_Callback(i);
        }
        if (isrflags & CO_BIT(i * 2 + 1))
        {
            PWM->INTR_MSK &= ~CO_BIT(i * 2 + 1);
            PWM->INTR_CLR = CO_BIT(i * 2 + 1);
            HAL_PWM_STOP_Callback(i);
        }
    }
}