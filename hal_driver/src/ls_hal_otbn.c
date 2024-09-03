#include "ls_hal_otbn.h"
#include "ls_msp_otbn.h"
#include "field_manipulate.h"
#include "common.h"

void HAL_OTBN_Init(void)
{
    HAL_LSOTBN_MSP_Init();
}

void HAL_OTBN_DeInit(void)
{
    HAL_LSOTBN_MSP_DeInit();
}

void HAL_OTBN_INTR_EN(bool enable)
{
    LSOTBN->INTR_ENABLE = enable;
}

void HAL_OTBN_INTR_Test(bool enable)
{
    LSOTBN->INTR_TEST = enable;
}

bool HAL_OTBN_WRITE_IMEM(uint32_t offset, uint32_t *src, uint32_t size)
{
    if (size > 0x800)
        return 0;

    memcpy32((uint32_t *)&LSOTBN->IMEM[offset], src, size);
    return 1;
}

bool HAL_OTBN_WRITE_DMEM(uint32_t offset, uint32_t *src, uint32_t size)
{
    if (size > 0x300)
        return 0;

    memcpy32((uint32_t *)&LSOTBN->DMEM[offset], src, size);
    return 1;
}

void HAL_OTBN_CMD_Write_Polling(enum OTBN_CMD cmd)
{
    if (LSOTBN->INTR_STATE)
        LSOTBN->INTR_STATE = OTBN_INTR_STATE_DONE_MASK;
    REG_FIELD_WR(LSOTBN->INTR_ENABLE, OTBN_INTR_ENABLE_EN, 0);
    LSOTBN->CMD = cmd;
    while (!LSOTBN->INTR_STATE) ;
    LSOTBN->INTR_STATE = OTBN_INTR_STATE_DONE_MASK;
}

void HAL_OTBN_CMD_Write_IT(enum OTBN_CMD cmd)
{
    if (LSOTBN->INTR_STATE)
        LSOTBN->INTR_STATE = OTBN_INTR_STATE_DONE_MASK;
    LSOTBN->INTR_ENABLE = OTBN_INTR_ENABLE_EN_MASK;
    LSOTBN->CMD = cmd;
}

__attribute__((weak)) void HAL_OTBN_CpltCallback(void){}
void HAL_OTBN_IRQHandler()
{
    if (LSOTBN->INTR_STATE)
    {
        LSOTBN->INTR_STATE = OTBN_INTR_STATE_DONE_MASK;
        HAL_OTBN_CpltCallback();
    }
}