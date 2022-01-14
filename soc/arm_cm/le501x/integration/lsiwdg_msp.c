#include "reg_rcc.h"
#include "field_manipulate.h"
void HAL_IWDG_MSP_Init()
{
    REG_FIELD_WR(RCC->AHBEN, RCC_IWDT, 1);
}

void HAL_IWDG_MSP_DeInit()
{
    REG_FIELD_WR(RCC->AHBEN, RCC_IWDT, 0);
}
