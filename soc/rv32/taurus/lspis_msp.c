#include "lspis_msp.h"
#include "reg_sysc_per.h"
#include "field_manipulate.h"
void HAL_PIS_MSP_Init(void)
{
    REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1,SYSC_PER_CLKG_SET_PIS,1);
}

void HAL_PIS_MSP_DeInit(void)
{
    REG_FIELD_WR(SYSC_PER->PD_PER_CLKG1,SYSC_PER_CLKG_CLR_PIS,1);
}
