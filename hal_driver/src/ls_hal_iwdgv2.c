#include "ls_hal_iwdgv2.h"
#include "field_manipulate.h"
#include "cpu.h"
#include "ls_msp_iwdg.h"

HAL_StatusTypeDef HAL_IWDG_Init(reg_iwdg_t *iwdg, uint32_t LoadValue)
{
    HAL_IWDG_MSP_Init(iwdg);
    iwdg->IWDT_LOAD = LoadValue;
    iwdg->IWDT_CTRL = FIELD_BUILD(IWDT_RST_EN,1) |FIELD_BUILD(IWDT_EN, 1);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_IWDG_Refresh(reg_iwdg_t *iwdg)
{
    MODIFY_REG(iwdg->IWDT_CTRL, IWDT_CNT_CLR_MASK|IWDT_INTR_CLR_MASK, 1<<IWDT_CNT_CLR_POS | 1<<IWDT_INTR_CLR_POS);
    MODIFY_REG(iwdg->IWDT_CTRL, IWDT_CNT_CLR_MASK|IWDT_INTR_CLR_MASK, 0);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_IWDG_DeInit(reg_iwdg_t *iwdg)
{
    REG_FIELD_WR(iwdg->IWDT_CTRL, IWDT_EN, 0);
    HAL_IWDG_MSP_DeInit(iwdg);
    return HAL_OK;
}
