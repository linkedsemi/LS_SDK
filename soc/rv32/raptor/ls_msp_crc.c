#include "ls_msp_crc.h"
#include "field_manipulate.h"
#include "reg_cpu0_sys.h"

void HAL_LSCRC_MSP_Init(void)
{
    REG_FIELD_WR(CPU0_SYS_CFG->CPU0_SYS_CFG_REG5, CPU0_SYS_CALC_CRC_APB_CLK_CLK_CG0_11, 0x1);
}

void HAL_LSCRC_MSP_DeInit(void)
{
    REG_FIELD_WR(CPU0_SYS_CFG->CPU0_SYS_CFG_REG5, CPU0_SYS_CALC_CRC_APB_CLK_CLK_CG0_11, 0x0);
}