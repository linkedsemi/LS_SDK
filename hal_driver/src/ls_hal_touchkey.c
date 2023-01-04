#include "ls_hal_touchkey.h"
#include "ls_msp_touchkey.h"
#include "field_manipulate.h"
#include "co_math.h"
#include "ls_dbg.h"
#include "log.h"

HAL_StatusTypeDef HAL_TOUCHKEY_Init()
{
    HAL_LSTOUCHKEY_MSP_Init();
    return HAL_OK;
}

HAL_StatusTypeDef HAL_TOUCHKEY_DeInit()
{
    HAL_LSTOUCHKEY_MSP_DeInit();
    return HAL_OK;
}

HAL_StatusTypeDef HAL_TOUCHKEY_SetParam(TOUCHKEY_PARAM *param)
{
    LSTOUCHKEY->TOUCHKEY_CLK_CFG = FIELD_BUILD(TOUCHKEY_HPRD, param->clk_hprd) |
                                   FIELD_BUILD(TOUCHKEY_LPRD, param->clk_lprd);
    LSTOUCHKEY->TOUCHKEY_SCAN_MTIM = FIELD_BUILD(TOUCHKEY_SCAN_MTIM, param->scan_mtim);
    LSTOUCHKEY->TOUCHKEY_SCAN_CFG = FIELD_BUILD(TOUCHKEY_CH_EN, param->scan_channel_en) |
                                    FIELD_BUILD(TOUCHKEY_FLT_PRD, param->scan_flt_prd) |
                                    FIELD_BUILD(TOUCHKEY_SCAN_ITER, param->scan_iter) |
                                    FIELD_BUILD(TOUCHKEY_DISCH_PRD, param->scam_disch_prd);
    LSTOUCHKEY->TOUCHKEY_ANA_CFG = FIELD_BUILD(TOUCHKEY_CP_VCTL, param->touchkey_cp_vctl) |
                                   FIELD_BUILD(TOUCHKEY_ANA_EN, 1);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_TOUCHKEY_StartScan(uint32_t cntresult[16])
{
    LSTOUCHKEY->INTR_MSK = 0;
    LSTOUCHKEY->INTR_CLR = TOUCHKEY_INTR_END_MASK | TOUCHKEY_INTR_ERR_MASK;
    REG_FIELD_WR(LSTOUCHKEY->TOUCHKEY_START, TOUCHKEY_START, 1);
    while (!(LSTOUCHKEY->INTR_RAW & TOUCHKEY_INTR_END_MASK))
        ;
    REG_FIELD_WR(LSTOUCHKEY->INTR_CLR, TOUCHKEY_INTR_END, 1);
    uint32_t sccfg = LSTOUCHKEY->TOUCHKEY_SCAN_CFG;
    uint32_t *ptr = (uint32_t *)&LSTOUCHKEY->CH0_CNT;
    for (uint8_t i = 0; i < 16; i++)
    {
        cntresult[i] = sccfg & CO_BIT(i + 12) ? *ptr : 0;
        ptr++;
    };
    return HAL_OK;
}

HAL_StatusTypeDef HAL_TOUCHKEY_StartScan_IT()
{
    LSTOUCHKEY->INTR_MSK = TOUCHKEY_INTR_END_MASK | TOUCHKEY_INTR_ERR_MASK;
    LSTOUCHKEY->INTR_CLR = TOUCHKEY_INTR_END_MASK | TOUCHKEY_INTR_ERR_MASK;
    REG_FIELD_WR(LSTOUCHKEY->TOUCHKEY_START, TOUCHKEY_START, 1);
    return HAL_OK;
}

__attribute__((weak)) void HAL_TOUCHKEY_END_Callback(uint32_t cntresult[16]){}
__attribute__((weak)) void HAL_TOUCHKEY_ERR_Callback(){}

void HAL_TOUCHKEY_IRQHandler()
{
    uint32_t iflag = LSTOUCHKEY->INTR_STT;
    if (iflag & TOUCHKEY_INTR_END_MASK)
    {
        REG_FIELD_WR(LSTOUCHKEY->INTR_CLR, TOUCHKEY_INTR_END, 1);
        uint32_t sccfg = LSTOUCHKEY->TOUCHKEY_SCAN_CFG;
        uint32_t *ptr = (uint32_t *)&LSTOUCHKEY->CH0_CNT;
        uint32_t cntresult[16];
        for (uint8_t i = 0; i < 16; i++)
        {
            cntresult[i] = sccfg & CO_BIT(i + 12) ? *ptr : 0;
            ptr++;
        };
        HAL_TOUCHKEY_END_Callback(cntresult);
    }
    if (iflag & TOUCHKEY_INTR_ERR_MASK)
    {
        REG_FIELD_WR(LSTOUCHKEY->INTR_CLR, TOUCHKEY_INTR_ERR, 1);
        HAL_TOUCHKEY_ERR_Callback();
    }
}