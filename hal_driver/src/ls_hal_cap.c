#include <string.h>
#include <stddef.h>
#include "ls_hal_cap.h"
#include "field_manipulate.h"
#include "reg_sysc_awo.h"
#include "reg_sysc_per.h"
#include "co_math.h"

static void CAP_SetConfig(CAP_Param *cap_param)
{
    CAP->CAP_CNT_EN = 1;
    CAP->CAP_PRE_DIV = cap_param->cap_pre_div;
}

static void CAP_Channel_Init(uint8_t channel, uint8_t cap_mode)
{
    CAP->CAP_CTRL[channel] = FIELD_BUILD(CAP_EN, 1) | FIELD_BUILD(CAP_MODE, cap_mode);
}

HAL_StatusTypeDef HAL_CAP_Init(CAP_Param *cap_param)
{
    HAL_LSCAP_MSP_Init();
    CAP_SetConfig(cap_param);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_CAP_DeInit()
{
    HAL_LSCAP_MSP_DeInit();
    return HAL_OK;
}

HAL_StatusTypeDef HAL_CAP_Start(uint8_t channel, uint8_t cap_mode, bool enable_it)
{
    if(channel >= CAP_CHANNEL)
    {
        return HAL_INVALIAD_PARAM;
    }
    CAP_Channel_Init(channel, cap_mode);
    CAP->INTR_CLR = CO_BIT(channel)| CO_BIT(channel+8) | CO_BIT(channel+16);

    if(enable_it == false)
    {
        CAP->INTR_MSK &= ~(CO_BIT(channel) | CO_BIT(channel+8) | CO_BIT(channel+16));
    }
    else
    {
        CAP->INTR_MSK = CO_BIT(channel) | CO_BIT(channel+8) | CO_BIT(channel+16);
    }
    return HAL_OK;
}

void HAL_CAP_Stop(uint8_t channel)
{
    CAP->CAP_CTRL[channel] = FIELD_BUILD(CAP_EN, 0);
}

HAL_StatusTypeDef HAL_CAP_GetCount(uint8_t channel, cap_count_t *capcount)
{
    while ((CAP->INTR_RAW & (CO_BIT(channel)|CO_BIT(channel + 8)|CO_BIT(channel + 16))) == 0){}
    if ((CAP->INTR_RAW & CO_BIT(channel + 8)) || (CAP->INTR_RAW & CO_BIT(channel + 16)))
    {
        CAP->INTR_CLR = CO_BIT(channel + 8) | CO_BIT(channel + 16);
        return HAL_ERROR;
    }
    do
    {
        capcount->cap_high = CAP->CAP_COUNT[channel*2];
        capcount->cap_low = CAP->CAP_COUNT[channel*2 + 1];
    } while (capcount->cap_high != CAP->CAP_COUNT[channel*2]);
    return HAL_OK;
}

__attribute__((weak)) void HAL_CAP_END_Callback(uint8_t channel, cap_count_t cap_count){}
__attribute__((weak)) void HAL_CAP_ERR_HIGH_Callback(uint8_t channel){}
__attribute__((weak)) void HAL_CAP_ERR_LOW_Callback(uint8_t channel){}

void HAL_LSCAP_IRQHandler()
{
    uint32_t isrflags = CAP->INTR_STT;
    cap_count_t capcount;
    if(isrflags & 0xff)
    {
        for (uint8_t j = 0; j < 8; j++)
        {
            if (CO_BIT(j) & isrflags)
            {
                CAP->INTR_CLR = CO_BIT(j);
                do
                {
                    capcount.cap_high = CAP->CAP_COUNT[(j)*2];
                    capcount.cap_low = CAP->CAP_COUNT[(j)*2 + 1];
                } while (capcount.cap_high != CAP->CAP_COUNT[(j)*2]);
                HAL_CAP_END_Callback(j, capcount);
            }
        }
    }
    else if(isrflags & 0xff00)
    {
        for (uint8_t j = 0; j < 8; j++)
        {
            if (CO_BIT(j) & (isrflags>>8))
            {
                CAP->INTR_CLR = CO_BIT(j + 8);
                HAL_CAP_ERR_HIGH_Callback(j);
            }
        }
    }
    else
    {
        for (uint8_t j = 0; j < 8; j++)
        {
            if (CO_BIT(j) & (isrflags >> 16))
            {
                CAP->INTR_CLR = CO_BIT(j + 16);
                HAL_CAP_ERR_HIGH_Callback(j);
            }
        }
    }
}