#include "ls_hal_otbn_ecc256.h"

#define OTBN_P256_Verify_X2_OFFSET (0x444)
#define OTBN_P256_Verify_X_R_OFFSET (0xA0)

extern const char ecc256_verify_text[4040];

struct OTBN_ECC_256_CURVE_PARAM {
    const uint32_t b[8];
    const uint32_t p[8];
    const uint32_t r448[8];
    const uint32_t n[8];
    const uint32_t u_n[8];
    const uint32_t Gx[8];
    const uint32_t Gy[8];
};

/****************
 *  Curve P-256
 * *****************/
static const struct OTBN_ECC_256_CURVE_PARAM P_256 = {
    {0x27d2604b, 0x3bce3c3e, 0xcc53b0f6, 0x651d06b0, 0x769886bc, 0xb3ebbd55, 0xaa3a93e7, 0x5ac635d8},
    {0xffffffff, 0xffffffff, 0xffffffff, 0x00000000, 0x00000000, 0x00000000, 0x00000001, 0xffffffff},
    {0xffffffff, 0xfffffffe, 0xfffffffe, 0xffffffff, 0x00000000, 0x00000002, 0x00000003, 0x00000000},
    {0xfc632551, 0xf3b9cac2, 0xa7179e84, 0xbce6faad, 0xffffffff, 0xffffffff, 0x00000000, 0xffffffff},
    {0xeedf9bfe, 0x012ffd85, 0xdf1a6c21, 0x43190552, 0xffffffff, 0xfffffffe, 0xffffffff, 0x00000000},
    {0xd898c296, 0xf4a13945, 0x2deb33a0, 0x77037d81, 0x63a440f2, 0xf8bce6e5, 0xe12c4247, 0x6b17d1f2},
    {0x37bf51f5, 0xcbb64068, 0x6b315ece, 0x2bce3357, 0x7c0f9e16, 0x8ee7eb4a, 0xfe1a7f9b, 0x4fe342e2},
};

bool HAL_OTBN_P256_Verify_Polling(struct HAL_OTBN_P256_Verify_Param *verify_param)
{
    uint32_t verify_result = 0;
    bool result = false;
    HAL_OTBN_IMEM_Write(0, (uint32_t *)ecc256_verify_text, sizeof(ecc256_verify_text));
    HAL_OTBN_DMEM_Write(0x0, (uint32_t *)verify_param, sizeof(struct HAL_OTBN_P256_Verify_Param));
    HAL_OTBN_DMEM_Write(0xc0, (uint32_t *)&P_256, sizeof(P_256));

    HAL_OTBN_CMD_Write_Polling(HAL_OTBN_CMD_EXECUTE);

    HAL_OTBN_DMEM_Read(OTBN_P256_Verify_X2_OFFSET, &verify_result, 4);
    if (verify_result == HARDENED_BOOL_TRUE)
    {
        HAL_OTBN_DMEM_Read(OTBN_P256_Verify_X_R_OFFSET, verify_param->x_r, 0x20);
        if (!memcmp((uint8_t *)verify_param->x_r, (uint8_t *)verify_param->r, 0x20))
            result = true;
    }
    
    HAL_OTBN_CMD_Write_Polling(HAL_OTBN_CMD_SEC_WIPE_DMEM);
    return result;
}

static bool flag;

__attribute__((weak)) void HAL_OTBN_ECC256_ECDSA_Verify_CallBack(bool result);
void ECC256_Verify_Cb(void *param)
{
    if (flag)
        return;

    struct HAL_OTBN_P256_Verify_Param *verify_param = param;
    flag = true;
    uint32_t verify_result = 0;
    bool result = false;
    HAL_OTBN_DMEM_Read(OTBN_P256_Verify_X2_OFFSET, &verify_result, 4);
    if (verify_result == HARDENED_BOOL_TRUE)
    {
        HAL_OTBN_DMEM_Read(OTBN_P256_Verify_X_R_OFFSET, verify_param->x_r, 0x20);
        if (!memcmp((uint8_t *)verify_param->x_r, (uint8_t *)verify_param->r, 0x20))
            result = true;
    }
    HAL_OTBN_ECC256_ECDSA_Verify_CallBack(result);
    HAL_OTBN_CMD_Write_Polling(HAL_OTBN_CMD_SEC_WIPE_DMEM);
}

void HAL_OTBN_ECC256_ECDSA_Verify_IT(struct HAL_OTBN_P256_Verify_Param *verify_param)
{
    HAL_OTBN_IMEM_Write(0, (uint32_t *)ecc256_verify_text, sizeof(ecc256_verify_text));
    HAL_OTBN_DMEM_Write(0x0, (uint32_t *)verify_param, sizeof(struct HAL_OTBN_P256_Verify_Param));
    HAL_OTBN_DMEM_Write(0xc0, (uint32_t *)&P_256, sizeof(P_256));

    flag = false;
    HAL_OTBN_CMD_Write_IT(HAL_OTBN_CMD_EXECUTE, ECC256_Verify_Cb, verify_param);
}