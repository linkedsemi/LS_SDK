#include "ls_hal_comp.h"
#include "field_manipulate.h"

HAL_StatusTypeDef HAL_COMP_Init(COMP_HandleTypeDef *hcomp)
{
    HAL_COMP_MSP_Init(hcomp);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_COMP_DeInit(void)
{
    HAL_COMP_MSP_DeInit();
    return HAL_OK;
}

static void comp_intr_clr(COMP_HandleTypeDef *hcomp, enum comp_intr_edge edge)
{
    REG_FIELD_WR(hcomp->COMP->COMP_CTRL, COMP_INTR_CLR, edge);
    REG_FIELD_WR(hcomp->COMP->COMP_CTRL, COMP_INTR_CLR, 0);
}

HAL_StatusTypeDef HAL_COMP_Config(COMP_HandleTypeDef *hcomp, COMP_Param *param)
{
    param->comp_en = 0;
    hcomp->COMP->COMP_CTRL = *(uint32_t *)param;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_COMP_Start(COMP_HandleTypeDef *hcomp)
{
    comp_intr_clr(hcomp, COMP_EDGE_BOTH);
    REG_FIELD_WR(hcomp->COMP->COMP_CTRL, COMP_CTRL_EN, 1);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_COMP_Stop(COMP_HandleTypeDef *hcomp)
{
    REG_FIELD_WR(hcomp->COMP->COMP_CTRL, COMP_CTRL_EN, 0);
    return HAL_OK;
}

__attribute__((weak)) void HAL_COMP_Callback(COMP_HandleTypeDef *hcomp, enum comp_intr_edge edge, bool output){}

void HAL_COMP_IRQHandler(COMP_HandleTypeDef *hcomp, enum comp_intr_edge edge, bool output)
{
    comp_intr_clr(hcomp, edge);
    HAL_COMP_Callback(hcomp, edge, output);
}