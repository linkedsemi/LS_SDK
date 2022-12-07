#include "ls_msp_wwdg.h"
#include "field_manipulate.h"
#include "reg_sysc_per_type.h"
void HAL_WWDG_MSP_Init()
{
    SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_CLR_WWDT_MASK;
    SYSC_PER->PD_PER_SRST3 = SYSC_PER_SRST_CLR_WWDT_N_MASK;
    SYSC_PER->PD_PER_SRST3 = SYSC_PER_SRST_SET_WWDT_N_MASK;
    SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_SET_WWDT_MASK;
}

void HAL_WWDG_MSP_DeInit()
{
    SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_CLR_WWDT_MASK;
}
