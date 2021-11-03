#include "lsiwdg.h"
#include "field_manipulate.h"
#include "cpu.h"
#include "lsiwdg_msp.h"

HAL_StatusTypeDef HAL_IWDG_Init(uint32_t LoadValue)
{
    HAL_IWDG_MSP_Init();
    LSIWDG->IWDG_LOAD = LoadValue;
    LSIWDG->IWDG_CON = FIELD_BUILD(IWDG_CLKS,2) | FIELD_BUILD(IWDG_RSTEN,1) | FIELD_BUILD(IWDG_IE,1) | FIELD_BUILD(IWDG_EN, 1);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_IWDG_Refresh(void)
{
    LSIWDG->IWDG_INTCLR = 1;
    for (uint8_t i = 0; i < 200; i++)  //200 delay count
    {
        LSIWDG->IWDG_INTCLR;
    }
    return HAL_OK;
}


