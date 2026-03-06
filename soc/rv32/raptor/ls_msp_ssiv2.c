#include "ls_msp_ssiv2.h"
#include "reg_cpu0_sys.h"
#include "reg_cpu1_sys.h"
#include "field_manipulate.h"

void HAL_LSSSIV2_MSP_Init()
{
    REG_FIELD_WR(CPU0_SYS_CFG->CPU1_SYS_CFG_REG1, CPU1_SYS_FWSPI_AHB_CLK_CLK_CG0_3, 0x1);
    REG_FIELD_WR(CPU1_SYS_CFG->FWSPI_SSI_CLK_CLK_CG0_REG, CPU1_SYS_FWSPI_SSI_CLK_CLK_CG0_REG, 0x1);
}

void HAL_LSSSIV2_MSP_DeInit()
{

}
