#include "ls_hal_otbn_ecc.h"

#define ECC384_DMEM_MSG_OFFSET         (0x0)
#define ECC384_DMEM_MSG_SIZE               (0x40)
#define ECC384_DMEM_R_OFFSET           (0x40)
#define ECC384_DMEM_R_SIZE                 (0x40)
#define ECC384_DMEM_S_OFFSET           (0x80)
#define ECC384_DMEM_S_SIZE                 (0x40)
#define ECC384_DMEM_X_OFFSET           (0xC0)
#define ECC384_DMEM_X_SIZE                 (0x40)
#define ECC384_DMEM_Y_OFFSET           (0x100)
#define ECC384_DMEM_Y_SIZE                 (0x40)
#define ECC384_DMEM_X_R_OFFSET         (0x140)
#define ECC384_DMEM_X_R_SIZE               (0x40)
#define ECC384_DMEM_CURVE_P_OFFSET     (0x180)
#define ECC384_DMEM_CURVE_P_SIZE           (0x140)

extern const char ecc384_ecdsa_verify_text[3180];

struct OTBN_ECC384_CURVE {
    const uint32_t b[0x10];
    const uint32_t p[0x10];
    const uint32_t n[0x10];
    const uint32_t Gx[0x10];
    const uint32_t Gy[0x10];
};

/****************
 *  Curve SM2 
 * 
 * *****************/
static const struct OTBN_ECC384_CURVE P384 = {
    .b  = {0xd3ec2aef, 0x2a85c8ed, 0x8a2ed19d, 0xc656398d, 0x5013875a, 0x0314088f, 0xfe814112, 0x181d9c6e,
           0xe3f82d19, 0x988e056b, 0xe23ee7e4, 0xb3312fa7, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
    .p  = {0xffffffff, 0x00000000, 0x00000000, 0xffffffff, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff,
           0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
    .n  = {0xccc52973, 0xecec196a, 0x48b0a77a, 0x581a0db2, 0xf4372ddf, 0xc7634d81, 0xffffffff, 0xffffffff,
           0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
    .Gx = {0x72760ab7, 0x3a545e38, 0xbf55296c, 0x5502f25d, 0x82542a38, 0x59f741e0, 0x8ba79b98, 0x6e1d3b62,
           0xf320ad74, 0x8eb1c71e, 0xbe8b0537, 0xaa87ca22, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
    .Gy = {0x90ea0e5f, 0x7a431d7c, 0x1d7e819d, 0x0a60b1ce, 0xb5f0b8c0, 0xe9da3113, 0x289a147c, 0xf8f41dbd,
           0x9292dc29, 0x5d9e98bf, 0x96262c6f, 0x3617de4a, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
};

__attribute__((weak)) void HAL_OTBN_ECC384_ECDSA_Verify_CallBack(ls_otbn_status_t status) {}

static uint32_t *ecc384_curve_get(enum HAL_OTBN_ECC384_CURVES curve)
{
    switch (curve)
    {
    case HAL_OTBN_ECC384_CURVE_P384:
        return (uint32_t *)&P384;
        break;
    default:
        break;
    }
    return NULL;
}

ls_otbn_status_t HAL_OTBN_ECC384_ECDSA_Verify_Polling(enum HAL_OTBN_ECC384_CURVES curve, struct HAL_OTBN_ECC384_Verify_Param *verify_param)
{
    if (!verify_param || curve != HAL_OTBN_ECC384_CURVE_P384) return LS_OTBN_INVALID_PARAM;
    /* Reject out-of-range r/s (wc_ecc_check_r_s_range) and off-curve
     * public keys before programming OTBN */
    if (!ls_otbn_ecc_rs_in_range_u32(LS_OTBN_ECC_CURVE_P384, verify_param->r, verify_param->s))
        return LS_OTBN_RS_RANGE;
    if (!ls_otbn_ecc_point_on_curve_u32(LS_OTBN_ECC_CURVE_P384, verify_param->x, verify_param->y))
        return LS_OTBN_POINT_NOT_ON_CURVE;

    HAL_OTBN_IMEM_Write(0, (uint32_t *)ecc384_ecdsa_verify_text, sizeof(ecc384_ecdsa_verify_text));
    HAL_OTBN_DMEM_Set(0, 0x0, OTBN_DMEM_SIZE);
    HAL_OTBN_DMEM_Write(ECC384_DMEM_CURVE_P_OFFSET, ecc384_curve_get(curve), ECC384_DMEM_CURVE_P_SIZE);
    HAL_OTBN_DMEM_Write(ECC384_DMEM_MSG_OFFSET, verify_param->msg, 0x30);
    HAL_OTBN_DMEM_Write(ECC384_DMEM_R_OFFSET, verify_param->r, 0x30);
    HAL_OTBN_DMEM_Write(ECC384_DMEM_S_OFFSET, verify_param->s, 0x30);
    HAL_OTBN_DMEM_Write(ECC384_DMEM_X_OFFSET, verify_param->x, 0x30);
    HAL_OTBN_DMEM_Write(ECC384_DMEM_Y_OFFSET, verify_param->y, 0x30);
    HAL_StatusTypeDef st = HAL_OTBN_CMD_Write_Polling_Timeout(HAL_OTBN_CMD_EXECUTE, 20000);
    if (st != HAL_OK)
        return ls_otbn_status_from_hal(st);

    uint8_t x_r[ECC384_DMEM_X_R_SIZE];
    HAL_OTBN_DMEM_Read(ECC384_DMEM_X_R_OFFSET, (uint32_t *)x_r, ECC384_DMEM_X_R_SIZE);
    return !memcmp(verify_param->r, x_r, 0x30) ? LS_OTBN_OK : LS_OTBN_VERIFY_INVALID;
}

void ECC384_ecdsa_verify_cb(void *param)
{
    struct HAL_OTBN_ECC384_Verify_Param *verify_param = param;
    uint8_t x_r[ECC384_DMEM_X_R_SIZE];
    /* Engine flagged an error: the DMEM result is untrustworthy, report
     * ENGINE rather than a (meaningless) valid/invalid answer. */
    if (HAL_OTBN_Error_Bit_Get() != 0)
    {
        HAL_OTBN_ECC384_ECDSA_Verify_CallBack(LS_OTBN_ENGINE);
        return;
    }
    HAL_OTBN_DMEM_Read(ECC384_DMEM_X_R_OFFSET, (uint32_t *)x_r, ECC384_DMEM_X_R_SIZE);
    HAL_OTBN_ECC384_ECDSA_Verify_CallBack(!memcmp(verify_param->r, x_r, 0x30) ? LS_OTBN_OK : LS_OTBN_VERIFY_INVALID);
}

ls_otbn_status_t HAL_OTBN_ECC384_ECDSA_Verify_IT(enum HAL_OTBN_ECC384_CURVES curve, struct HAL_OTBN_ECC384_Verify_Param *verify_param)
{
    /* Rejections are reported via the return value; only an accepted
     * submit delivers its completion through the callback. */
    /* Only P-384 is supported; reject any other curve id (the curve
     * lookup below returns NULL for unknown ids). */
    if (!verify_param || curve != HAL_OTBN_ECC384_CURVE_P384)
        return LS_OTBN_INVALID_PARAM;
    if (!ls_otbn_ecc_rs_in_range_u32(LS_OTBN_ECC_CURVE_P384, verify_param->r, verify_param->s))
        return LS_OTBN_RS_RANGE;
    if (!ls_otbn_ecc_point_on_curve_u32(LS_OTBN_ECC_CURVE_P384, verify_param->x, verify_param->y))
        return LS_OTBN_POINT_NOT_ON_CURVE;
    /* OTBN is a single engine: refuse a second submit while a job is
     * running (no DMEM read -- the active job's result is not ours). */
    if (HAL_OTBN_Is_Busy() || !HAL_OTBN_In_Idle_State())
        return LS_OTBN_BUSY;

    HAL_OTBN_IMEM_Write(0, (uint32_t *)ecc384_ecdsa_verify_text, sizeof(ecc384_ecdsa_verify_text));
    HAL_OTBN_DMEM_Set(0, 0x0, OTBN_DMEM_SIZE);
    HAL_OTBN_DMEM_Write(ECC384_DMEM_CURVE_P_OFFSET, ecc384_curve_get(curve), ECC384_DMEM_CURVE_P_SIZE);
    HAL_OTBN_DMEM_Write(ECC384_DMEM_MSG_OFFSET, verify_param->msg, 0x30);
    HAL_OTBN_DMEM_Write(ECC384_DMEM_R_OFFSET, verify_param->r, 0x30);
    HAL_OTBN_DMEM_Write(ECC384_DMEM_S_OFFSET, verify_param->s, 0x30);
    HAL_OTBN_DMEM_Write(ECC384_DMEM_X_OFFSET, verify_param->x, 0x30);
    HAL_OTBN_DMEM_Write(ECC384_DMEM_Y_OFFSET, verify_param->y, 0x30);

    HAL_StatusTypeDef st = HAL_OTBN_CMD_Write_IT(HAL_OTBN_CMD_EXECUTE, ECC384_ecdsa_verify_cb, verify_param);
    if (st != HAL_OK)
        /* Engine went busy between the idle check and the submit. */
        return ls_otbn_status_from_hal(st);
    return LS_OTBN_OK;
}
