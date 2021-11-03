#include "lspis_msp.h"
#include "reg_rcc.h"
#include "field_manipulate.h"
void HAL_PIS_MSP_Init(void)
{
    REG_FIELD_WR(RCC->APB2EN,RCC_PIS,1);
}

void HAL_PIS_MSP_DeInit(void)
{
    REG_FIELD_WR(RCC->APB2EN,RCC_PIS,0);
}
