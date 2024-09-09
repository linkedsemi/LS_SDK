#include "ls_hal_otbn.h"
#include "ls_msp_otbn.h"
#include "field_manipulate.h"

#define OTBN_IMEM_OFFSET_PTR(offset) (uint32_t *)(OTBN_IMEM_ADDR+offset)
#define OTBN_DMEM_OFFSET_PTR(offset) (uint32_t *)(OTBN_DMEM_ADDR+offset)

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

HAL_StatusTypeDef HAL_OTBN_IMEM_Write(uint32_t offset, uint32_t *src, uint32_t size)
{
    if (LSOTBN->STATUS != HAL_OTBN_STATUS_IDLE)
        return HAL_BUSY;

    if (((offset + size) > OTBN_IMEM_SIZE) || (offset & 0x3) || (size & 0x3))
        return HAL_INVALIAD_PARAM;

    memcpy32(OTBN_IMEM_OFFSET_PTR(offset), src, size / 4);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_OTBN_IMEM_Read(uint32_t offset, uint32_t *dst, uint32_t size)
{
    if (LSOTBN->STATUS != HAL_OTBN_STATUS_IDLE)
        return HAL_BUSY;

    if (((offset + size) > OTBN_IMEM_SIZE) || (offset & 0x3) || (size & 0x3))
        return HAL_INVALIAD_PARAM;

    memcpy32(dst, OTBN_IMEM_OFFSET_PTR(offset), size / 4);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_OTBN_DMEM_Write(uint32_t offset, uint32_t *src, uint32_t size)
{
    if (LSOTBN->STATUS != HAL_OTBN_STATUS_IDLE)
        return HAL_BUSY;

    if (((offset + size) > OTBN_IMEM_SIZE) || (offset & 0x3) || (size & 0x3))
        return HAL_INVALIAD_PARAM;

    memcpy32(OTBN_DMEM_OFFSET_PTR(offset), src, size / 4);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_OTBN_DMEM_Read(uint32_t offset, uint32_t *dst, uint32_t size)
{
    if (LSOTBN->STATUS != HAL_OTBN_STATUS_IDLE)
        return HAL_BUSY;

    if (((offset + size) > OTBN_IMEM_SIZE) || (offset & 0x3) || (size & 0x3))
        return HAL_INVALIAD_PARAM;

    memcpy32(dst, OTBN_DMEM_OFFSET_PTR(offset), size / 4);
    return HAL_OK;
}

void HAL_OTBN_CMD_Write_Polling(enum HAL_OTBN_CMD cmd)
{
    if (LSOTBN->INTR_STATE)
        LSOTBN->INTR_STATE = OTBN_INTR_STATE_DONE_MASK;
    REG_FIELD_WR(LSOTBN->INTR_ENABLE, OTBN_INTR_ENABLE_EN, 0);
    LSOTBN->CMD = cmd;
    while (!LSOTBN->INTR_STATE) ;
    LSOTBN->INTR_STATE = OTBN_INTR_STATE_DONE_MASK;
}

static void (*callback_func)(void *);
static void *callback_param;
void HAL_OTBN_CMD_Write_IT(enum HAL_OTBN_CMD cmd, void(* func)(void *), void *param)
{
    if (LSOTBN->INTR_STATE)
        LSOTBN->INTR_STATE = OTBN_INTR_STATE_DONE_MASK;
    callback_func = func;
    callback_param = param;
    LSOTBN->INTR_ENABLE = OTBN_INTR_ENABLE_EN_MASK;
    LSOTBN->CMD = cmd;
}

void HAL_OTBN_IRQHandler()
{
    if (LSOTBN->INTR_STATE)
    {
        LSOTBN->INTR_STATE = OTBN_INTR_STATE_DONE_MASK;
        callback_func(callback_param);
    }
}
