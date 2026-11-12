#include "ls_msp_iwdg.h"
#include "field_manipulate.h"
#include "reg_v33_rg_type.h"
void HAL_IWDG_MSP_Init(reg_iwdg_t *iwdg)
{
    if (iwdg == LSIWDG) {
        V33_RG->CLKG_SRST = V33_RG_CLKG_SET_WDT_MASK;
    }
}

void HAL_IWDG_MSP_DeInit(reg_iwdg_t *iwdg)
{
    if (iwdg == LSIWDG) {
        V33_RG->CLKG_SRST = V33_RG_CLKG_CLR_WDT_MASK;
    }
}
