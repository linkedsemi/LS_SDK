#include "ls_msp_iwdg.h"
#include "reg_sec_pmu_rg.h"
#include "reg_sysc_sec_per.h"
#include "reg_sysc_app_per.h"

void HAL_IWDG_MSP_Init(reg_iwdg_t *iwdg)
{
    switch ((uint32_t)iwdg)
    {
    case (uint32_t)SEC_IWDG:
        SYSC_SEC_PER->PD_PER_CLKG0 = SYSC_SEC_PER_CLKG_CLR_IWDT1_MASK;
        SYSC_SEC_PER->PD_PER_SRST0 = SYSC_SEC_PER_SRST_CLR_IWDT1_N_MASK;
        SYSC_SEC_PER->PD_PER_SRST0 = SYSC_SEC_PER_SRST_SET_IWDT1_N_MASK;
        SYSC_SEC_PER->PD_PER_CLKG0 = SYSC_SEC_PER_CLKG_SET_IWDT1_MASK;
        break;
    case (uint32_t)APP_IWDG:
        SYSC_APP_PER->PD_PER_CLKG2 = SYSC_APP_PER_CLKG_CLR_IWDT2_MASK;
        SYSC_APP_PER->PD_PER_SRST2 = SYSC_APP_PER_SRST_CLR_IWDT2_N_MASK;
        SYSC_APP_PER->PD_PER_SRST2 = SYSC_APP_PER_SRST_SET_IWDT2_N_MASK;
        SYSC_APP_PER->PD_PER_CLKG2 = SYSC_APP_PER_CLKG_SET_IWDT2_MASK;
        break;
    default:
        break;
    }
}

void HAL_IWDG_MSP_DeInit(reg_iwdg_t *iwdg)
{
    switch ((uint32_t)iwdg)
    {
    case (uint32_t)SEC_IWDG:
        SYSC_SEC_PER->PD_PER_CLKG0 = SYSC_SEC_PER_CLKG_CLR_IWDT1_MASK;
        break;
    case (uint32_t)APP_IWDG:
        SYSC_APP_PER->PD_PER_CLKG2 = SYSC_APP_PER_CLKG_CLR_IWDT2_MASK;
        break;
    default:
        break;
    }
}
