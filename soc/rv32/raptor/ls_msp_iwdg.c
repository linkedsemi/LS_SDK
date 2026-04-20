#include "ls_msp_iwdg.h"
#include "reg_cpu0_sys.h"
#include "field_manipulate.h"
void HAL_IWDG_MSP_Init(reg_iwdg_t *iwdg)
{
    switch ((uint32_t)iwdg)
    {
    case (uint32_t)IWDT0:
        CPU0_SYS_CFG -> WDT0_LRC_CLK_CLK_DEGLITCH_SW2_REG = 0x1; //0x1:32Khz 0x2:50Mhz //TODO
        CPU0_SYS_CFG -> WDT0_LRC_CLK_CLK_CG0_REG = 0x1;
        REG_FIELD_WR(CPU0_SYS_CFG -> CPU0_SYS_CFG_REG2, CPU0_SYS_WDT0_APB_CLK_CLK_CG0_2, 0x1);
        break;
    case (uint32_t)IWDT1:
        break;
    default:
        break;
    }
}

void HAL_IWDG_MSP_DeInit(reg_iwdg_t *iwdg)
{
    switch ((uint32_t)iwdg)
    {
    case (uint32_t)IWDT0:
        CPU0_SYS_CFG -> WDT0_LRC_CLK_CLK_CG0_REG = 0x0;
        break;
    case (uint32_t)IWDT1:
        break;
    default:
        break;
    }
}
