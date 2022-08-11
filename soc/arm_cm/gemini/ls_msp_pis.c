#include "ls_msp_pis.h"
#include "field_manipulate.h"
#include "reg_sysc_per_type.h"
void HAL_PIS_MSP_Init(void)
{
    REG_FIELD_WR(SYSC_PER->PD_PER_CLKG3, SYSC_PER_CLKG_SET_PIS, 1);
}

void HAL_PIS_MSP_DeInit(void)
{
    REG_FIELD_WR(SYSC_PER->PD_PER_CLKG3, SYSC_PER_CLKG_CLR_PIS, 1);
}
