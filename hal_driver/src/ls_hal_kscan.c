#include <string.h>
#include <stddef.h>
#include "ls_msp_kscan.h"
#include "ls_hal_kscan.h"
#include "field_manipulate.h"
#include "co_math.h"

static uint16_t row_en;
static uint8_t col_en;
static uint8_t scan_cnt;
static uint8_t scan_cnt_stop;

uint8_t kscan_matrix[ROW_MAX];

__attribute__((weak)) void HAL_KSCAN_Press_callback(uint8_t col, uint8_t row, uint8_t pressed) {}

static void KSCAN_SetConfig(KSCAN_PARAM *param)
{
    KSCAN->KSCAN_EN = 0;
    KSCAN->INTR_MSK = 0;
    KSCAN->KSCAN_ITV = param->itv;
    KSCAN->CYC_CTRL = FIELD_BUILD(KSCAN_CYC_CTRL_CAP_IDX, param->cyc_cap) |
                      FIELD_BUILD(KSCAN_CYC_CTRL_UDRV_IDX, param->cyc_udrv) |
                      FIELD_BUILD(KSCAN_CYC_CTRL_CYC_LEN, param->cyc_len);
    KSCAN->KEY_CTRL = FIELD_BUILD(KSCAN_KEY_CTRL_KEYO_VLD, param->row_en) |
                      FIELD_BUILD(KSCAN_KEY_CTRL_KEYI_VLD, param->col_en) |
                      FIELD_BUILD(KSCAN_KEY_CTRL_KEYO_VAL, 0U) |
                      FIELD_BUILD(KSCAN_KEY_CTRL_KEYI_VAL, 1U);
    scan_cnt_stop   = param->scan_cnt_nopress;
    row_en          = param->row_en;
    col_en          = param->col_en;
}

static inline void KSCAN_EN(bool wait, bool scan)
{
    KSCAN->KSCAN_EN = FIELD_BUILD(KSCAN_SCAN_EN,scan)|FIELD_BUILD(KSCAN_WAIT_EN,wait);
}

HAL_StatusTypeDef HAL_KSCAN_Init(KSCAN_PARAM *param)
{
    HAL_KSCAN_MSP_Init();
    KSCAN_SetConfig(param);

    return HAL_OK;
}

HAL_StatusTypeDef HAL_KSCAN_DeInit(void)
{
    HAL_KSCAN_Stop();
    HAL_KSCAN_MSP_DeInit();
    return HAL_OK;
}

HAL_StatusTypeDef HAL_KSCAN_Start()
{
    scan_cnt = 0;
    memset(kscan_matrix, 0, sizeof(kscan_matrix));
    KSCAN->INTR_CLR = KSCAN_INTR_STT_ALL_MASK;
    KSCAN->INTR_MSK = KSCAN_INTR_STT_WAIT_MASK;
    KSCAN_EN(1,0);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_KSCAN_Stop()
{
    KSCAN_EN(0, 0);
    KSCAN->INTR_MSK = 0;
    KSCAN->INTR_CLR = KSCAN_INTR_STT_ALL_MASK;
    return HAL_OK;
}

static void KSCAN_IT()
{
    uint8_t *rowPtr = (uint8_t *)&KSCAN->CAP_VAL0;
    uint8_t data, i, j;

    for (uint8_t _row = 0; _row < ROW_MAX; _row++)
    {
        data = *rowPtr++;
        if (!(row_en & CO_BIT(_row)))
            continue;
        for (uint8_t _col = 0; _col < COL_MAX; _col++)
        {
            if (!(col_en & CO_BIT(_col)))
                continue;
            i = kscan_matrix[_row] & CO_BIT(_col);     // previous status
            j = ~data & CO_BIT(_col);                   // scan key status
            if (i != j)
            {
                kscan_matrix[_row] = j | (kscan_matrix[_row] & ~CO_BIT(_col));
                HAL_KSCAN_Press_callback(_col, _row, j ? 1 : 0);
            }
        }
    }
}

void HAL_KSCAN_IRQHandler()
{
    uint32_t status = KSCAN->INTR_STT;
    if (status & KSCAN_INTR_STT_WAIT_MASK)
    {
        KSCAN->INTR_CLR = KSCAN_INTR_STT_ALL_MASK;
        KSCAN->INTR_MSK = KSCAN_INTR_STT_KEY_MASK | KSCAN_INTR_STT_END_MASK;
        KSCAN_EN(0, 1);
    }
    if (status & KSCAN_INTR_STT_END_MASK)
    {
        KSCAN->INTR_CLR = KSCAN_INTR_STT_END_MASK;
        if (status & KSCAN_INTR_STT_KEY_MASK)
        {
            KSCAN->INTR_CLR = KSCAN_INTR_STT_KEY_MASK;
            scan_cnt = 0;
            KSCAN_IT();
        }
        else
        {
            if (scan_cnt++ == 0)
            {
                KSCAN_IT();
            }
            else
            {
                if (scan_cnt_stop == scan_cnt)
                    HAL_KSCAN_Start();
            }
        }
    }
}