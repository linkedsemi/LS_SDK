#include "ls_hal_otbn_ecc.h"
#include "ls_otbn_ecc.h"
#include "ls_hal_otbn.h"

#define SM2_FUNC_VALIDPOINT     (0x10)
#define SM2_FUNC_SCALARMULT     (0x20)
#define SM2_FUNC_VERIFY         (0x30)

#define SM2_DMEM_CURVE_P_OFFSET     (0x0)
#define SM2_DMEM_CURVE_P_SIZE           (0xe0)
#define SM2_DMEM_K0_OFFSET          (0xe0)
#define SM2_DMEM_K0_SIZE                (0x40)
#define SM2_DMEM_K1_OFFSET          (0x120)
#define SM2_DMEM_K2_SIZE                (0x40)
#define SM2_DMEM_MSG_OFFSET         (0x160)
#define SM2_DMEM_MSG_SIZE               (0x20)
#define SM2_DMEM_R_OFFSET           (0x180)
#define SM2_DMEM_R_SIZE                 (0x20)
#define SM2_DMEM_S_OFFSET           (0x1a0)
#define SM2_DMEM_S_SIZE                 (0x20)
#define SM2_DMEM_X_OFFSET           (0x1c0)
#define SM2_DMEM_X_SIZE                 (0x20)
#define SM2_DMEM_Y_OFFSET           (0x1e0)
#define SM2_DMEM_Y_SIZE                 (0x20)
#define SM2_DMEM_X_R_OFFSET         (0x200)
#define SM2_DMEM_X_R_SIZE               (0x20)
#define SM2_DMEM_RESULT_X_OFFSET    (0x220)
#define SM2_DMEM_RESULT_X_SIZE          (0x40)
#define SM2_DMEM_RESULT_Y_OFFSET    (0x260)
#define SM2_DMEM_RESULT_Y_SIZE          (0x40)
#define SM2_DMEM_FUNC_OFFSET        (0x2a0)
#define SM2_DMEM_FUNC_SIZE              (0x20)
#define SM2_DMEM_DZERO_OFFSET       (0x2c0)
#define SM2_DMEM_DZERO_SIZE             (0x20)
#define SM2_DMEM_PROJ_SG_OFFSET     (0x2e0)
#define SM2_DMEM_PROJ_SG_SIZE           (0x60)
#define SM2_DMEM_BSS_START          (0x2e0)
#define SM2_DMEM_BSS_END            (0x340)
#define SM2_DMEM_BSS_SIZE               (0x60)

extern const char sm2_text[1924];
extern const char ecc256_scalar_mult_text[1880];

/* DMEM layout of the shared ECC-256 scalar-mult firmware
 * (ecc256_scalar_mult_text); same offsets as ls_hal_otbn_ecc256.c */
#define SM2_SCALARMULT_DMEM_SCALAR_OFFSET    (0x0)
#define SM2_SCALARMULT_DMEM_POINT_X_OFFSET   (0x80)
#define SM2_SCALARMULT_DMEM_POINT_Y_OFFSET   (0xA0)
#define SM2_SCALARMULT_DMEM_RESULT_X_OFFSET  (0xC0)
#define SM2_SCALARMULT_DMEM_RESULT_Y_OFFSET  (0xE0)
#define SM2_SCALARMULT_DMEM_CURVE_OFFSET     (0x100)
#define SM2_SCALARMULT_DMEM_BSS_START        (0x1E0)
#define SM2_SCALARMULT_DMEM_BSS_SIZE         (0x1C0)

struct OTBN_SM2_CURVE {
    const uint32_t b[8];
    const uint32_t p[8];
    const uint32_t u_p[8];
    const uint32_t n[8];
    const uint32_t u_n[8];
    const uint32_t Gx[8];
    const uint32_t Gy[8];
};

/****************
 *  Curve SM2 
 * 
 * *****************/
static const struct OTBN_SM2_CURVE SM2 = {
    .b =    {0x4D940E93, 0xDDBCBD41, 0x15AB8F92, 0xF39789F5, 0xCF6509A7, 0x4D5A9E4B, 0x9D9F5E34, 0x28E9FA9E},
    .p =    {0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFE},
    .u_p =  {0x00000003, 0x00000002, 0x00000002, 0x00000002, 0x00000001, 0x00000001, 0x00000001, 0x00000001},
    .n =    {0x39D54123, 0x53BBF409, 0x21C6052B, 0x7203DF6B, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFE},
    .u_n =  {0xf15149a0, 0x12ac6361, 0xfa323c01, 0x8dfc2096, 0x00000001, 0x00000001, 0x00000001, 0x00000001},
    .Gx =   {0x334C74C7, 0x715A4589, 0xF2660BE1, 0x8FE30BBF, 0x6A39C994, 0x5F990446, 0x1F198119, 0x32C4AE2C},
    .Gy =   {0x2139F0A0, 0x02DF32E5, 0xC62A4740, 0xD0A9877C, 0x6B692153, 0x59BDCEE3, 0xF4F6779C, 0xBC3736A2},
};

bool HAL_OTBN_SM2_Verify_Polling(struct HAL_OTBN_SM2_Verify_Param *param)
{
    if (!param) return false;
    /* Reject out-of-range r/s (wc_ecc_check_r_s_range) and off-curve
     * public keys before programming OTBN */
    if (!ls_otbn_ecc_rs_in_range_u32(LS_OTBN_ECC_CURVE_SM2, param->r, param->s))
        return false;
    if (!ls_otbn_ecc_point_on_curve_u32(LS_OTBN_ECC_CURVE_SM2, param->x, param->y))
        return false;

    uint32_t func = SM2_FUNC_VERIFY;
    HAL_OTBN_IMEM_Write(0, (uint32_t *)sm2_text, sizeof(sm2_text));
    HAL_OTBN_DMEM_Set(0, 0, SM2_DMEM_BSS_END);
    HAL_OTBN_DMEM_Write(SM2_DMEM_CURVE_P_OFFSET, (uint32_t *)&SM2, SM2_DMEM_CURVE_P_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_MSG_OFFSET, param->msg, SM2_DMEM_MSG_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_R_OFFSET, param->r, SM2_DMEM_R_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_S_OFFSET, param->s, SM2_DMEM_S_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_X_OFFSET, param->x, SM2_DMEM_X_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_Y_OFFSET, param->y, SM2_DMEM_Y_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_FUNC_OFFSET, &func, sizeof(uint32_t));
    
    if (HAL_OTBN_CMD_Write_Polling_Timeout(HAL_OTBN_CMD_EXECUTE, 20000) != HAL_OK)
        return false;

    uint8_t x_r[SM2_DMEM_X_R_SIZE];
    HAL_OTBN_DMEM_Read(SM2_DMEM_X_R_OFFSET, (uint32_t *)x_r, SM2_DMEM_X_R_SIZE);
    return !memcmp(param->r, x_r, SM2_DMEM_X_R_SIZE);
}

__attribute__((weak)) void HAL_OTBN_SM2_ScalarMult_CallBack() {}
__attribute__((weak)) void HAL_OTBN_SM2_Verify_CallBack(bool result) {}
__attribute__((weak)) void HAL_OTBN_SM2_ValidPoint_CallBack(bool result) {}

void SM2_Verify_Cb(void *param)
{
    uint8_t x_r[SM2_DMEM_X_R_SIZE];
    struct HAL_OTBN_SM2_Verify_Param *p = param;
   
    HAL_OTBN_DMEM_Read(SM2_DMEM_X_R_OFFSET, (uint32_t *)x_r, SM2_DMEM_X_R_SIZE);
    HAL_OTBN_SM2_Verify_CallBack(!memcmp(p->r, x_r, SM2_DMEM_X_R_SIZE));
}

void HAL_OTBN_SM2_Verify_IT(struct HAL_OTBN_SM2_Verify_Param *param)
{
    if (!param) return;
    if (!ls_otbn_ecc_rs_in_range_u32(LS_OTBN_ECC_CURVE_SM2, param->r, param->s) ||
        !ls_otbn_ecc_point_on_curve_u32(LS_OTBN_ECC_CURVE_SM2, param->x, param->y))
    {
        /* Reject before starting OTBN; complete synchronously */
        HAL_OTBN_SM2_Verify_CallBack(false);
        return;
    }
    /* OTBN is a single engine: refuse a second submit while a job is
     * running; complete synchronously with "invalid" (no DMEM read --
     * the engine's result belongs to the other job). */
    if (HAL_OTBN_Is_Busy() || !HAL_OTBN_In_Idle_State())
    {
        HAL_OTBN_SM2_Verify_CallBack(false);
        return;
    }

    uint32_t func = SM2_FUNC_VERIFY;
    HAL_OTBN_IMEM_Write(0, (uint32_t *)sm2_text, sizeof(sm2_text));
    HAL_OTBN_DMEM_Set(0, 0, SM2_DMEM_BSS_END);
    HAL_OTBN_DMEM_Write(SM2_DMEM_CURVE_P_OFFSET, (uint32_t *)&SM2, SM2_DMEM_CURVE_P_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_MSG_OFFSET, param->msg, SM2_DMEM_MSG_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_R_OFFSET, param->r, SM2_DMEM_R_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_S_OFFSET, param->s, SM2_DMEM_S_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_X_OFFSET, param->x, SM2_DMEM_X_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_Y_OFFSET, param->y, SM2_DMEM_Y_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_FUNC_OFFSET, &func, sizeof(uint32_t));

    if (HAL_OTBN_CMD_Write_IT(HAL_OTBN_CMD_EXECUTE, SM2_Verify_Cb, param) != HAL_OK)
    {
        /* Engine went busy between the idle check and the submit;
         * complete synchronously. */
        HAL_OTBN_SM2_Verify_CallBack(false);
        return;
    }
}

void SM2_ValidPoint_Cb(void *param)
{
    uint32_t data = 0;
    HAL_OTBN_DMEM_Read(SM2_DMEM_X_R_OFFSET, &data, sizeof(uint32_t));
    HAL_OTBN_SM2_ValidPoint_CallBack(data);
}

bool HAL_OTBN_SM2_ValidPoint_Polling(uint32_t *x, uint32_t *y)
{
    if (!x || !y) return false;

    uint32_t func = SM2_FUNC_VALIDPOINT;
    HAL_OTBN_IMEM_Write(0, (uint32_t *)sm2_text, sizeof(sm2_text));
    HAL_OTBN_DMEM_Set(0, 0, SM2_DMEM_BSS_END);
    HAL_OTBN_DMEM_Write(SM2_DMEM_CURVE_P_OFFSET, (uint32_t *)&SM2, SM2_DMEM_CURVE_P_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_X_OFFSET, x, SM2_DMEM_X_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_Y_OFFSET, y, SM2_DMEM_Y_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_FUNC_OFFSET, &func, sizeof(uint32_t));

    if (HAL_OTBN_CMD_Write_Polling_Timeout(HAL_OTBN_CMD_EXECUTE, 20000) != HAL_OK)
        return false;

    uint32_t data = 0;
    HAL_OTBN_DMEM_Read(SM2_DMEM_X_R_OFFSET, &data, sizeof(uint32_t));
    return (data != 0);
}

void HAL_OTBN_SM2_ValidPoint_IT(uint32_t *x, uint32_t *y)
{
    if (!x || !y) return;
    /* OTBN is a single engine: refuse a second submit while a job is
     * running; complete synchronously with "not on curve". */
    if (HAL_OTBN_Is_Busy() || !HAL_OTBN_In_Idle_State())
    {
        HAL_OTBN_SM2_ValidPoint_CallBack(false);
        return;
    }

    uint32_t func = SM2_FUNC_VALIDPOINT;
    HAL_OTBN_IMEM_Write(0, (uint32_t *)sm2_text, sizeof(sm2_text));
    HAL_OTBN_DMEM_Set(0, 0, SM2_DMEM_BSS_END);
    HAL_OTBN_DMEM_Write(SM2_DMEM_CURVE_P_OFFSET, (uint32_t *)&SM2, SM2_DMEM_CURVE_P_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_X_OFFSET, x, SM2_DMEM_X_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_Y_OFFSET, y, SM2_DMEM_Y_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_FUNC_OFFSET, &func, sizeof(uint32_t));

    if (HAL_OTBN_CMD_Write_IT(HAL_OTBN_CMD_EXECUTE, SM2_ValidPoint_Cb, NULL) != HAL_OK)
    {
        /* Engine went busy between the idle check and the submit;
         * complete synchronously. */
        HAL_OTBN_SM2_ValidPoint_CallBack(false);
        return;
    }
}

/* Completion routine of the shared ECC-256 scalar-mult firmware:
 * copy the result out and notify the SM2-layer callback. */
void SM2_ScalarMult_Cb(void *param)
{
    struct HAL_OTBN_SM2_ScalarMult_Param *p = param;
    HAL_OTBN_DMEM_Read(SM2_SCALARMULT_DMEM_RESULT_X_OFFSET, p->result_x, 0x20);
    HAL_OTBN_DMEM_Read(SM2_SCALARMULT_DMEM_RESULT_Y_OFFSET, p->result_y, 0x20);
    HAL_OTBN_SM2_ScalarMult_CallBack();
}

/* SM2 scalar multiplication runs on the shared ECC-256 engine with
 * the SM2 curve parameters -- the same path P-256 uses, so SM2 needs
 * no dedicated scalar-mult firmware.  Named *_Engine_* to avoid
 * clashing with the pointops primitive of the same stem
 * (HAL_OTBN_SM2_ScalarMult_Polling in ls_hal_otbn_sm2_pointops.h,
 * byte-array parameters, g_ecc_sm2 firmware). */
HAL_StatusTypeDef HAL_OTBN_SM2_ScalarMult_Engine_Polling(struct HAL_OTBN_SM2_ScalarMult_Param *param)
{
    if (!param) return HAL_ERROR;
    /* Layout-identical param structs; forward to the shared engine */
    struct HAL_OTBN_ECC256_ScalarMult_Param p256 = {
        .scalar = param->scalar,
        .point_x = param->point_x,
        .point_y = param->point_y,
        .result_x = param->result_x,
        .result_y = param->result_y,
    };
    return HAL_OTBN_ECC256_ScalarMult_Polling(HAL_OTBN_ECC256_CURVE_SM2, &p256);
}

void HAL_OTBN_SM2_ScalarMult_IT(struct HAL_OTBN_SM2_ScalarMult_Param *param)
{
    if (!param) return;
    if (!ls_otbn_ecc_scalar_in_range_u32(LS_OTBN_ECC_CURVE_SM2, param->scalar) ||
        !ls_otbn_ecc_point_on_curve_u32(LS_OTBN_ECC_CURVE_SM2, param->point_x, param->point_y))
    {
        /* Reject before starting OTBN; result stays zeroed, complete
         * synchronously so the caller is always notified exactly once. */
        memset(param->result_x, 0, 0x20);
        memset(param->result_y, 0, 0x20);
        HAL_OTBN_SM2_ScalarMult_CallBack();
        return;
    }
    /* OTBN is a single engine: refuse a second submit while a job is
     * running; result stays zeroed, complete synchronously. */
    if (HAL_OTBN_Is_Busy() || !HAL_OTBN_In_Idle_State())
    {
        memset(param->result_x, 0, 0x20);
        memset(param->result_y, 0, 0x20);
        HAL_OTBN_SM2_ScalarMult_CallBack();
        return;
    }

    /* Program the shared ECC-256 scalar-mult firmware with the SM2
     * curve parameters (same DMEM layout as ls_hal_otbn_ecc256.c). */
    HAL_OTBN_IMEM_Write(0, (uint32_t *)ecc256_scalar_mult_text, sizeof(ecc256_scalar_mult_text));
    HAL_OTBN_DMEM_Write(SM2_SCALARMULT_DMEM_SCALAR_OFFSET, param->scalar, 0x20);
    HAL_OTBN_DMEM_Set(0x20, 0x0, 0x60);
    HAL_OTBN_DMEM_Write(SM2_SCALARMULT_DMEM_POINT_X_OFFSET, param->point_x, 0x20);
    HAL_OTBN_DMEM_Write(SM2_SCALARMULT_DMEM_POINT_Y_OFFSET, param->point_y, 0x20);
    HAL_OTBN_DMEM_Set(SM2_SCALARMULT_DMEM_RESULT_X_OFFSET, 0x0, 0x20);
    HAL_OTBN_DMEM_Set(SM2_SCALARMULT_DMEM_RESULT_Y_OFFSET, 0x0, 0x20);
    HAL_OTBN_DMEM_Write(SM2_SCALARMULT_DMEM_CURVE_OFFSET, (uint32_t *)&SM2, sizeof(SM2));
    HAL_OTBN_DMEM_Set(SM2_SCALARMULT_DMEM_BSS_START, 0x0, SM2_SCALARMULT_DMEM_BSS_SIZE);

    if (HAL_OTBN_CMD_Write_IT(HAL_OTBN_CMD_EXECUTE, SM2_ScalarMult_Cb, param) != HAL_OK)
    {
        /* Engine went busy between the idle check and the submit;
         * result stays zeroed. */
        memset(param->result_x, 0, 0x20);
        memset(param->result_y, 0, 0x20);
        return;
    }
}


