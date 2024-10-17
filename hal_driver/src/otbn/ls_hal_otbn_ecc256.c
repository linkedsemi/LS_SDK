#include "ls_hal_otbn_ecc256.h"

#define ECC256_ECDSA_Verify_X2_OFFSET (0x444)
#define ECC256_ECDSA_Verify_X_R_OFFSET (0xA0)

extern const char ecc256_ecdsa_verify_text[4040];
extern const char ecc256_scalar_mult_text[1880];

struct OTBN_ECC256_CURVE_PARAM {
    const uint32_t b[8];
    const uint32_t p[8];
    const uint32_t u_p[8];
    const uint32_t n[8];
    const uint32_t u_n[8];
    const uint32_t Gx[8];
    const uint32_t Gy[8];
};

/****************
 *  Curve P-256
 * *****************/
static const struct OTBN_ECC256_CURVE_PARAM P_256 = {
    {0x27d2604b, 0x3bce3c3e, 0xcc53b0f6, 0x651d06b0, 0x769886bc, 0xb3ebbd55, 0xaa3a93e7, 0x5ac635d8},
    {0xffffffff, 0xffffffff, 0xffffffff, 0x00000000, 0x00000000, 0x00000000, 0x00000001, 0xffffffff},
    {0xffffffff, 0xfffffffe, 0xfffffffe, 0xffffffff, 0x00000000, 0x00000002, 0x00000003, 0x00000000},
    {0xfc632551, 0xf3b9cac2, 0xa7179e84, 0xbce6faad, 0xffffffff, 0xffffffff, 0x00000000, 0xffffffff},
    {0xeedf9bfe, 0x012ffd85, 0xdf1a6c21, 0x43190552, 0xffffffff, 0xfffffffe, 0xffffffff, 0x00000000},
    {0xd898c296, 0xf4a13945, 0x2deb33a0, 0x77037d81, 0x63a440f2, 0xf8bce6e5, 0xe12c4247, 0x6b17d1f2},
    {0x37bf51f5, 0xcbb64068, 0x6b315ece, 0x2bce3357, 0x7c0f9e16, 0x8ee7eb4a, 0xfe1a7f9b, 0x4fe342e2},
};

static const struct OTBN_ECC256_CURVE_PARAM P256 = {
    .b =    {0x27d2604b, 0x3bce3c3e, 0xcc53b0f6, 0x651d06b0, 0x769886bc, 0xb3ebbd55, 0xaa3a93e7, 0x5ac635d8},
    .p =    {0xffffffff, 0xffffffff, 0xffffffff, 0x00000000, 0x00000000, 0x00000000, 0x00000001, 0xffffffff},
    .u_p =  {0x00000003, 0x00000000, 0xffffffff, 0xfffffffe, 0xfffffffe, 0xfffffffe, 0xffffffff, 0x00000000},
    .n =    {0xfc632551, 0xf3b9cac2, 0xa7179e84, 0xbce6faad, 0xffffffff, 0xffffffff, 0x00000000, 0xffffffff},
    .u_n =  {0xeedf9bfe, 0x012ffd85, 0xdf1a6c21, 0x43190552, 0xffffffff, 0xfffffffe, 0xffffffff, 0x00000000},
    .Gx =   {0xd898c296, 0xf4a13945, 0x2deb33a0, 0x77037d81, 0x63a440f2, 0xf8bce6e5, 0xe12c4247, 0x6b17d1f2},
    .Gy =   {0x37bf51f5, 0xcbb64068, 0x6b315ece, 0x2bce3357, 0x7c0f9e16, 0x8ee7eb4a, 0xfe1a7f9b, 0x4fe342e2},
};

/****************
 *  Curve SM2 
 * 
 * *****************/
const static struct OTBN_ECC256_CURVE_PARAM SM2 = {
    .b =    {0x4D940E93, 0xDDBCBD41, 0x15AB8F92, 0xF39789F5, 0xCF6509A7, 0x4D5A9E4B, 0x9D9F5E34, 0x28E9FA9E},
    .p =    {0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFE},
    .u_p =  {0x00000003, 0x00000002, 0x00000002, 0x00000002, 0x00000001, 0x00000001, 0x00000001, 0x00000001},
    .n =    {0x39D54123, 0x53BBF409, 0x21C6052B, 0x7203DF6B, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFE},
    .u_n =  {0xf15149a0, 0x12ac6361, 0xfa323c01, 0x8dfc2096, 0x00000001, 0x00000001, 0x00000001, 0x00000001},
    .Gx =   {0x334C74C7, 0x715A4589, 0xF2660BE1, 0x8FE30BBF, 0x6A39C994, 0x5F990446, 0x1F198119, 0x32C4AE2C},
    .Gy =   {0x2139F0A0, 0x02DF32E5, 0xC62A4740, 0xD0A9877C, 0x6B692153, 0x59BDCEE3, 0xF4F6779C, 0xBC3736A2},
};

static bool flag;

static uint32_t *ECC256_getCurve(enum HAL_OTBN_ECC256_CURVES curve)
{
    switch (curve)
    {
    case HAL_OTBN_ECC256_CURVE_P256:
        return (uint32_t *)&P256;
    case HAL_OTBN_ECC256_CURVE_SM2:
        return (uint32_t *)&SM2;
    default:
        return NULL;
    }
}

bool HAL_OTBN_ECC256_ECDSA_Verify_Polling(struct HAL_OTBN_ECC256_Verify_Param *verify_param)
{
    uint32_t verify_result = 0;
    bool result = false;
    HAL_OTBN_IMEM_Write(0, (uint32_t *)ecc256_ecdsa_verify_text, sizeof(ecc256_ecdsa_verify_text));
    HAL_OTBN_DMEM_Write(0x0, (uint32_t *)verify_param, sizeof(struct HAL_OTBN_ECC256_Verify_Param));
    HAL_OTBN_DMEM_Write(0xc0, (uint32_t *)&P_256, sizeof(P_256));

    HAL_OTBN_CMD_Write_Polling(HAL_OTBN_CMD_EXECUTE);

    HAL_OTBN_DMEM_Read(ECC256_ECDSA_Verify_X2_OFFSET, &verify_result, 4);
    if (verify_result == HARDENED_BOOL_TRUE)
    {
        HAL_OTBN_DMEM_Read(ECC256_ECDSA_Verify_X_R_OFFSET, verify_param->x_r, 0x20);
        if (!memcmp((uint8_t *)verify_param->x_r, (uint8_t *)verify_param->r, 0x20))
            result = true;
    }
    
    HAL_OTBN_CMD_Write_Polling(HAL_OTBN_CMD_SEC_WIPE_DMEM);
    return result;
}

// #define ECC256_DMEM_VERIFY_PARAM_OFFSET            (0x0)
// #define ECC256_DMEM_VERIFY_CURVE_P_OFFSET          (0xC0)
// #define ECC256_DMEM_VERIFY_BSS_SECTION_START       (0x1A0)
// #define ECC256_DMEM_VERIFY_BSS_SECTION_SIZE        (0x280)

__attribute__((weak)) void HAL_OTBN_ECC256_ECDSA_Verify_CallBack(bool result);
void ECC256_Verify_Cb(void *p)
{
    if (flag)
        return;

    struct HAL_OTBN_ECC256_Verify_Param *verify_param = p;
    flag = true;
    uint32_t verify_result = 0;
    bool result = false;
    HAL_OTBN_DMEM_Read(ECC256_ECDSA_Verify_X2_OFFSET, &verify_result, 4);
    if (verify_result == HARDENED_BOOL_TRUE)
    {
        HAL_OTBN_DMEM_Read(ECC256_ECDSA_Verify_X_R_OFFSET, verify_param->x_r, 0x20);
        if (!memcmp((uint8_t *)verify_param->x_r, (uint8_t *)verify_param->r, 0x20))
            result = true;
    }
    HAL_OTBN_ECC256_ECDSA_Verify_CallBack(result);
    HAL_OTBN_CMD_Write_Polling(HAL_OTBN_CMD_SEC_WIPE_DMEM);
}

void HAL_OTBN_ECC256_ECDSA_Verify_IT(struct HAL_OTBN_ECC256_Verify_Param *verify_param)
{
    HAL_OTBN_IMEM_Write(0, (uint32_t *)ecc256_ecdsa_verify_text, sizeof(ecc256_ecdsa_verify_text));
    HAL_OTBN_DMEM_Write(0x0, (uint32_t *)verify_param, sizeof(struct HAL_OTBN_ECC256_Verify_Param));
    HAL_OTBN_DMEM_Write(0xc0, (uint32_t *)&P_256, sizeof(P_256));//TODO : Other Curves

    flag = false;
    HAL_OTBN_CMD_Write_IT(HAL_OTBN_CMD_EXECUTE, ECC256_Verify_Cb, verify_param);
}

#define ECC256_DMEM_SCALARMULT_SCALAR_OFFSET           (0x0)
#define ECC256_DMEM_SCALARMULT_POINT_X_OFFSET          (0x80)
#define ECC256_DMEM_SCALARMULT_POINT_Y_OFFSET          (0xA0)
#define ECC256_DMEM_SCALARMULT_RESULT_X_OFFSET         (0xC0)
#define ECC256_DMEM_SCALARMULT_RESULT_Y_OFFSET         (0xE0)
#define ECC256_DMEM_SCALARMULT_CURVE_P_OFFSET          (0x100)
#define ECC256_DMEM_SCALARMULT_BSS_SECTION_START       (0x1E0)
#define ECC256_DMEM_SCALARMULT_BSS_SECTION_SIZE        (0x1C0)

__attribute__((weak)) void HAL_OTBN_ECC256_ScalarMult_Cb(void) {}
static void ECC256_ScalarMult_Callback(void *param)
{
    struct HAL_OTBN_ECC256_ScalarMult_Param *p = param;
    HAL_OTBN_DMEM_Read(ECC256_DMEM_SCALARMULT_RESULT_X_OFFSET, p->result_x, 0x20);
    HAL_OTBN_DMEM_Read(ECC256_DMEM_SCALARMULT_RESULT_Y_OFFSET, p->result_y, 0x20);
    HAL_OTBN_ECC256_ScalarMult_Cb();
}

void HAL_OTBN_ECC256_ScalarMult_IT(enum HAL_OTBN_ECC256_CURVES Curve, struct HAL_OTBN_ECC256_ScalarMult_Param *param)
{
    HAL_OTBN_IMEM_Write(0, (uint32_t *)ecc256_scalar_mult_text, sizeof(ecc256_scalar_mult_text));
    HAL_OTBN_DMEM_Write(ECC256_DMEM_SCALARMULT_SCALAR_OFFSET, param->scalar, 0x20);
    HAL_OTBN_DMEM_Set(0x20, 0x0, 0x60);
    HAL_OTBN_DMEM_Write(ECC256_DMEM_SCALARMULT_POINT_X_OFFSET, param->point_x, 0x20);
    HAL_OTBN_DMEM_Write(ECC256_DMEM_SCALARMULT_POINT_Y_OFFSET, param->point_y, 0x20);
    HAL_OTBN_DMEM_Set(ECC256_DMEM_SCALARMULT_RESULT_X_OFFSET, 0x0, 0x20);
    HAL_OTBN_DMEM_Set(ECC256_DMEM_SCALARMULT_RESULT_Y_OFFSET, 0x0, 0x20);
    HAL_OTBN_DMEM_Write(ECC256_DMEM_SCALARMULT_CURVE_P_OFFSET, ECC256_getCurve(Curve), sizeof(struct OTBN_ECC256_CURVE_PARAM));
    HAL_OTBN_DMEM_Set(ECC256_DMEM_SCALARMULT_BSS_SECTION_START, 0x0, ECC256_DMEM_SCALARMULT_BSS_SECTION_SIZE);

    flag = false;
    HAL_OTBN_CMD_Write_IT(HAL_OTBN_CMD_EXECUTE, ECC256_ScalarMult_Callback, param);
}