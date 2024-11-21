#include "ls_msp_iwdg.h"
#include "reg_pmu.h"
void HAL_IWDG_MSP_Init()
{
    PMU->CLKG_SRST = PMU_RG_CLKG_CLR_WDT_MASK;
    PMU->CLKG_SRST = PMU_RG_CLKG_SET_WDT_MASK;
}

void HAL_IWDG_MSP_DeInit()
{
    PMU->CLKG_SRST = PMU_RG_CLKG_CLR_WDT_MASK;
}
