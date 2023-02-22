#include "ls_hal_wwdg.h"
#include "field_manipulate.h"

HAL_StatusTypeDef HAL_WWDG_Init(uint32_t LoadValue,enum no_feeding_win win)
{
    HAL_WWDG_MSP_Init();
    LSWWDG->WWDG_LOCK = 0x1ACCE551;
    LSWWDG->WWDG_LOAD = LoadValue;
    LSWWDG->WWDG_CON = FIELD_BUILD(REG_WWDG_CLKS,1) |
                       FIELD_BUILD(REG_WWDG_WIN,win) |
                       FIELD_BUILD(REG_WWDG_RSTEN,1) |
                       FIELD_BUILD(REG_WWDG_EN,1);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_WWDG_Refresh(void)
{
    LSWWDG->WWDG_INTCLR = 1;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_WWDG_Get_Count(uint8_t *window_cnt,uint32_t *value)
{ 
    uint32_t reg_wwdg_value = 0;

    reg_wwdg_value = LSWWDG->WWDG_CNT;
    *window_cnt = reg_wwdg_value >> 30;
    *value = reg_wwdg_value&0x3fffffff;
    return HAL_OK;
}


HAL_StatusTypeDef HAL_WWDG_DeInit(void)
{
    REG_FIELD_WR(LSWWDG->WWDG_CON, REG_WWDG_EN, 0);
    HAL_WWDG_MSP_DeInit();
    return HAL_OK;
}
