#include "ls_msp_iwdg.h"
#include "field_manipulate.h"
#include "reg_rcc.h"
void HAL_IWDG_MSP_Init(reg_iwdg_t *iwdg)
{
    if (iwdg == LSIWDG) {
        REG_FIELD_WR(RCC->AHBEN, RCC_IWDT, 1);
    }
}

void HAL_IWDG_MSP_DeInit(reg_iwdg_t *iwdg)
{
    if (iwdg == LSIWDG) {
        REG_FIELD_WR(RCC->AHBEN, RCC_IWDT, 0);
    }
}
