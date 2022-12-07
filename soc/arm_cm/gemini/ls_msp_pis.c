#include "ls_msp_pis.h"
#include "field_manipulate.h"
#include "reg_sysc_per_type.h"
void HAL_PIS_MSP_Init(void)
{
    SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_CLR_PIS_MASK;
    SYSC_PER->PD_PER_SRST3 = SYSC_PER_SRST_CLR_PIS_N_MASK;
    SYSC_PER->PD_PER_SRST3 = SYSC_PER_SRST_SET_PIS_N_MASK;
    SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_SET_PIS_MASK;
}

void HAL_PIS_MSP_DeInit(void)
{
    SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_CLR_PIS_MASK;
}
