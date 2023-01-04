#include "ls_msp_wwdg.h"
#include "field_manipulate.h"
#include "reg_rcc.h"

void HAL_WWDG_MSP_Init()
{
    REG_FIELD_WR(RCC->APB1EN, RCC_WWDG, 1);
}

void HAL_WWDG_MSP_DeInit()
{
    REG_FIELD_WR(RCC->APB1EN, RCC_WWDG, 0);
}
