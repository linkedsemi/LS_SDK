#include "ls_msp_iwdg.h"
#include "reg_sec_pmu_rg.h"

void HAL_IWDG_MSP_Init()
{
    SEC_PMU->CLKG_SRST = SEC_PMU_RG_CLKG_CLR_WDT_MASK;
    SEC_PMU->CLKG_SRST = SEC_PMU_RG_CLKG_SET_WDT_MASK;
}

void HAL_IWDG_MSP_DeInit()
{
    SEC_PMU->CLKG_SRST = SEC_PMU_RG_CLKG_CLR_WDT_MASK;
}
