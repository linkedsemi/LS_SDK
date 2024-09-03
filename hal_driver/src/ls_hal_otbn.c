#include "ls_hal_otbn.h"
#include "ls_msp_otbn.h"
#include "field_manipulate.h"
#include "common.h"
#include <string.h>

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
    if (LSOTBN->STATUS != OTBN_STATUS_IDLE)
        return HAL_STATE_ERROR;

    if (((offset + size) > OTBN_IMEM_SIZE) || (offset & 0x3) || (size & 0x3))
        return HAL_INVALIAD_PARAM;

    memcpy32(OTBN_IMEM_OFFSET_PTR(offset), src, size / 4);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_OTBN_IMEM_Read(uint32_t offset, uint32_t *dst, uint32_t size)
{
    if (LSOTBN->STATUS != OTBN_STATUS_IDLE)
        return HAL_STATE_ERROR;

    if (((offset + size) > OTBN_IMEM_SIZE) || (offset & 0x3) || (size & 0x3))
        return HAL_INVALIAD_PARAM;

    memcpy32(dst, OTBN_IMEM_OFFSET_PTR(offset), size / 4);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_OTBN_DMEM_Write(uint32_t offset, uint32_t *src, uint32_t size)
{
    if (LSOTBN->STATUS != OTBN_STATUS_IDLE)
        return HAL_STATE_ERROR;

    if (((offset + size) > OTBN_IMEM_SIZE) || (offset & 0x3) || (size & 0x3))
        return HAL_INVALIAD_PARAM;

    memcpy32(OTBN_DMEM_OFFSET_PTR(offset), src, size / 4);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_OTBN_DMEM_Read(uint32_t offset, uint32_t *dst, uint32_t size)
{
    if (LSOTBN->STATUS != OTBN_STATUS_IDLE)
        return HAL_STATE_ERROR;

    if (((offset + size) > OTBN_IMEM_SIZE) || (offset & 0x3) || (size & 0x3))
        return HAL_INVALIAD_PARAM;

    memcpy32(dst, OTBN_DMEM_OFFSET_PTR(offset), size / 4);
    return HAL_OK;
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

#define OTBN_P256_Verify_X2_OFFSET (0x444)
#define OTBN_P256_Verify_X_R_OFFSET (0xA0)
extern const char _p256_verify_text[4040];
struct OTBN_P256_CURVE_PARAM {
    const uint32_t p256_b[8];
    const uint32_t p256_p[8];
    const uint32_t p256_r448[8];
    const uint32_t p256_n[8];
    const uint32_t p256_u_n[8];
    const uint32_t Gx[8];
    const uint32_t Gy[8];
} ;
static const struct OTBN_P256_CURVE_PARAM P_256 = {
    {0x27d2604b, 0x3bce3c3e, 0xcc53b0f6, 0x651d06b0, 0x769886bc, 0xb3ebbd55, 0xaa3a93e7, 0x5ac635d8},
    {0xffffffff, 0xffffffff, 0xffffffff, 0x00000000, 0x00000000, 0x00000000, 0x00000001, 0xffffffff},
    {0xffffffff, 0xfffffffe, 0xfffffffe, 0xffffffff, 0x00000000, 0x00000002, 0x00000003, 0x00000000},
    {0xfc632551, 0xf3b9cac2, 0xa7179e84, 0xbce6faad, 0xffffffff, 0xffffffff, 0x00000000, 0xffffffff},
    {0xeedf9bfe, 0x012ffd85, 0xdf1a6c21, 0x43190552, 0xffffffff, 0xfffffffe, 0xffffffff, 0x00000000},
    {0xd898c296, 0xf4a13945, 0x2deb33a0, 0x77037d81, 0x63a440f2, 0xf8bce6e5, 0xe12c4247, 0x6b17d1f2},
    {0x37bf51f5, 0xcbb64068, 0x6b315ece, 0x2bce3357, 0x7c0f9e16, 0x8ee7eb4a, 0xfe1a7f9b, 0x4fe342e2},
};
bool HAL_OTBN_P256_Verify(struct OTBN_P256_Verify_Param *verify_param)
{
    uint32_t verify_result = 0;
    bool result = false;
    HAL_OTBN_IMEM_Write(0, (uint32_t *)_p256_verify_text, sizeof(_p256_verify_text));
    HAL_OTBN_DMEM_Write(0x0, (uint32_t *)verify_param, sizeof(struct OTBN_P256_Verify_Param));
    HAL_OTBN_DMEM_Write(0xc0, (uint32_t *)&P_256, sizeof(P_256));

    HAL_OTBN_CMD_Write_Polling(OTBN_CMD_EXECUTE);

    HAL_OTBN_DMEM_Read(OTBN_P256_Verify_X2_OFFSET, &verify_result, 4);
    if (verify_result == HARDENED_BOOL_TRUE)
    {
        HAL_OTBN_DMEM_Read(OTBN_P256_Verify_X_R_OFFSET, verify_param->x_r, 0x20);
        if (!memcmp((uint8_t *)verify_param->x_r, (uint8_t *)verify_param->r, 0x20))
            result = true;
    }
    
    HAL_OTBN_CMD_Write_Polling(OTBN_CMD_SEC_WIPE_DMEM);
    return result;
}