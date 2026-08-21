/**
 * @file ls_hal_otbn_crypto_p256.c
 * @brief HAL interface for ECDSA P-256 derive_pubkey / sign / shared_secret
 *        (verification: use HAL_OTBN_ECC256_ECDSA_Verify_Polling/IT directly)
 */
#include "ls_hal_otbn.h"
#include "ls_otbn_ecc.h"
#include "ls_hal_otbn_ecc.h"
#include <string.h>

/* ====================================================================
 * Helper: reverse byte order (little-endian <-> big-endian)
 * ==================================================================== */
static void reverse_bytes(uint8_t *buf, uint32_t len)
{
    for (uint32_t i = 0; i < len / 2; i++) {
        uint8_t tmp = buf[i];
        buf[i] = buf[len - 1 - i];
        buf[len - 1 - i] = tmp;
    }
}

/* ====================================================================
 * P-256 derive_pubkey (old firmware g_ecc_p256, BaseMult mode)
 * ==================================================================== */
#include "ls_hal_otbn_p256_pointops.h"

uint32_t HAL_OTBN_ECDSA_P256_DerivePubkey(const uint8_t priv_key[ECDSA_P256_PRIVATE_KEY_SIZE],
                                       uint8_t pub_key[ECDSA_P256_PUBLIC_KEY_SIZE])
{
    if (!priv_key || !pub_key) return 1;
    /* Reject d outside [1, n-1] (mbedtls_ecp_check_privkey) */
    if (!ls_otbn_ecc_scalar_in_range(LS_OTBN_ECC_CURVE_P256, priv_key)) return 1;

    uint8_t priv_buf[ECDSA_P256_COMPONENT_LENGTH];
    memcpy(priv_buf, priv_key, ECDSA_P256_COMPONENT_LENGTH);
    reverse_bytes(priv_buf, ECDSA_P256_COMPONENT_LENGTH);

    HAL_OTBN_Checksum_Clear();
    HAL_OTBN_DMEM_Set(0, 0, ECC_P256_DMEM_TOTAL);
    HAL_OTBN_IMEM_Write(0, (const uint32_t *)g_ecc_p256_imem, g_ecc_p256_imem_size);
    HAL_OTBN_DMEM_Write(0, (const uint32_t *)g_ecc_p256_dmem, ECC_P256_DMEM_SIZE);

    uint32_t mode = ECC_P256_MODE_BASE_MULT;
    HAL_OTBN_DMEM_Write(ECC_P256_MODE_OFFSET, &mode, sizeof(uint32_t));
    HAL_OTBN_DMEM_Write(ECC_P256_SCALAR_D_OFFSET, (const uint32_t *)priv_buf, ECDSA_P256_COMPONENT_LENGTH);

    if (HAL_OTBN_CMD_Write_Polling_Timeout(HAL_OTBN_CMD_EXECUTE, 20000) != HAL_OK)
        return 1;

    HAL_OTBN_DMEM_Read(ECC_P256_X_OFFSET, (uint32_t *)pub_key, ECDSA_P256_COMPONENT_LENGTH);
    HAL_OTBN_DMEM_Read(ECC_P256_Y_OFFSET, (uint32_t *)(pub_key + ECDSA_P256_COMPONENT_LENGTH), ECDSA_P256_COMPONENT_LENGTH);
    reverse_bytes(pub_key, ECDSA_P256_COMPONENT_LENGTH);
    reverse_bytes(pub_key + ECDSA_P256_COMPONENT_LENGTH, ECDSA_P256_COMPONENT_LENGTH);
    return 0;
}

/* ====================================================================
 * P-256 sign (unified p256 firmware, SIGN mode 0x15b)
 * ==================================================================== */
#define P256_SIGN_MODE 0x0000015b

uint32_t HAL_OTBN_ECDSA_P256_Sign(const uint8_t digest[ECDSA_P256_COMPONENT_LENGTH],
                              const uint8_t rand_k[ECDSA_P256_COMPONENT_LENGTH],
                              const uint8_t priv_key[ECDSA_P256_PRIVATE_KEY_SIZE],
                              uint8_t signature[ECDSA_P256_SIGNATURE_SIZE])
{
    if (!digest || !rand_k || !priv_key || !signature) return 1;
    /* Reject d / k outside [1, n-1]: an out-of-range ephemeral key
     * produces a degenerate signature (r or s == 0) */
    if (!ls_otbn_ecc_scalar_in_range(LS_OTBN_ECC_CURVE_P256, priv_key)) return 1;
    if (!ls_otbn_ecc_scalar_in_range(LS_OTBN_ECC_CURVE_P256, rand_k)) return 1;

    uint8_t digest_buf[ECDSA_P256_COMPONENT_LENGTH];
    uint8_t rand_buf[ECDSA_P256_COMPONENT_LENGTH];
    uint8_t priv_buf[ECDSA_P256_COMPONENT_LENGTH];
    memcpy(digest_buf, digest, ECDSA_P256_COMPONENT_LENGTH);
    memcpy(rand_buf, rand_k, ECDSA_P256_COMPONENT_LENGTH);
    memcpy(priv_buf, priv_key, ECDSA_P256_COMPONENT_LENGTH);
    reverse_bytes(digest_buf, ECDSA_P256_COMPONENT_LENGTH);
    reverse_bytes(rand_buf, ECDSA_P256_COMPONENT_LENGTH);
    reverse_bytes(priv_buf, ECDSA_P256_COMPONENT_LENGTH);

    HAL_OTBN_Checksum_Clear();
    HAL_OTBN_DMEM_Set(0, 0, LS_OTBN_ECDSA_P256_DMEM_END);
    HAL_OTBN_IMEM_Write(0, (const uint32_t *)p256_imem, p256_imem_size);
    HAL_OTBN_DMEM_Write(0, (const uint32_t *)p256_dmem, p256_dmem_size);

    uint32_t mode = P256_SIGN_MODE;
    HAL_OTBN_DMEM_Write(LS_OTBN_ECDSA_P256_RANDOM_SEED_OFFSET, (const uint32_t *)rand_buf, ECDSA_P256_COMPONENT_LENGTH);
    HAL_OTBN_DMEM_Write(LS_OTBN_ECDSA_P256_MODE_OFFSET, &mode, sizeof(uint32_t));
    HAL_OTBN_DMEM_Set(LS_OTBN_ECDSA_P256_D1_OFFSET, 0, ECDSA_P256_COMPONENT_LENGTH);
    HAL_OTBN_DMEM_Write(LS_OTBN_ECDSA_P256_D0_OFFSET, (const uint32_t *)priv_buf, ECDSA_P256_COMPONENT_LENGTH);
    HAL_OTBN_DMEM_Write(LS_OTBN_ECDSA_P256_MSG_OFFSET, (const uint32_t *)digest_buf, ECDSA_P256_COMPONENT_LENGTH);

    if (HAL_OTBN_CMD_Write_Polling_Timeout(HAL_OTBN_CMD_EXECUTE, 20000) != HAL_OK)
        return 1;

    HAL_OTBN_DMEM_Read(LS_OTBN_ECDSA_P256_R_OFFSET, (uint32_t *)signature, ECDSA_P256_COMPONENT_LENGTH);
    HAL_OTBN_DMEM_Read(LS_OTBN_ECDSA_P256_S_OFFSET, (uint32_t *)(signature + ECDSA_P256_COMPONENT_LENGTH), ECDSA_P256_COMPONENT_LENGTH);
    reverse_bytes(signature, ECDSA_P256_COMPONENT_LENGTH);
    reverse_bytes(signature + ECDSA_P256_COMPONENT_LENGTH, ECDSA_P256_COMPONENT_LENGTH);
    return 0;
}

/* ====================================================================
 * P-256 shared_secret
 * P256 统一固件 (p256_imem) 的 SHARED_KEY 模式经验证输出错误（输出点不在曲线上，
 * 部分标量下固件挂死），改用 SDK 专用的标量乘固件
 * (otbn_p256_scalarmult.c 中的 ecc256_scalar_mult_text)：
 * shared = priv x pub
 * ==================================================================== */

static void be_to_u32_le(const uint8_t be[ECDSA_P256_COMPONENT_LENGTH], uint32_t le[8])
{
    uint8_t tmp[ECDSA_P256_COMPONENT_LENGTH];
    memcpy(tmp, be, ECDSA_P256_COMPONENT_LENGTH);
    reverse_bytes(tmp, ECDSA_P256_COMPONENT_LENGTH);
    memcpy(le, tmp, ECDSA_P256_COMPONENT_LENGTH);
}

static void u32_le_to_be(const uint32_t le[8], uint8_t be[ECDSA_P256_COMPONENT_LENGTH])
{
    memcpy(be, le, ECDSA_P256_COMPONENT_LENGTH);
    reverse_bytes(be, ECDSA_P256_COMPONENT_LENGTH);
}

uint32_t HAL_OTBN_ECDSA_P256_SharedSecret(const uint8_t priv_key[ECDSA_P256_PRIVATE_KEY_SIZE],
                                       const uint8_t pub_key[ECDSA_P256_PUBLIC_KEY_SIZE],
                                       uint8_t shared[ECDSA_P256_PUBLIC_KEY_SIZE])
{
    if (!priv_key || !pub_key || !shared) return 1;
    if (!ls_otbn_ecc_scalar_in_range(LS_OTBN_ECC_CURVE_P256, priv_key)) return 1;
    if (!ls_otbn_ecc_point_on_curve(LS_OTBN_ECC_CURVE_P256,
                                    pub_key, pub_key + ECDSA_P256_COMPONENT_LENGTH)) return 1;

    uint32_t scalar[8], point_x[8], point_y[8];
    uint32_t result_x[8], result_y[8];
    be_to_u32_le(priv_key, scalar);
    be_to_u32_le(pub_key, point_x);
    be_to_u32_le(pub_key + ECDSA_P256_COMPONENT_LENGTH, point_y);

    struct HAL_OTBN_ECC256_ScalarMult_Param param = {
        .scalar = scalar,
        .point_x = point_x,
        .point_y = point_y,
        .result_x = result_x,
        .result_y = result_y,
    };
    if (HAL_OTBN_ECC256_ScalarMult_Polling(HAL_OTBN_ECC256_CURVE_P256, &param) != HAL_OK)
        return 1;

    u32_le_to_be(result_x, shared);
    u32_le_to_be(result_y, shared + ECDSA_P256_COMPONENT_LENGTH);
    return 0;
}

/* ====================================================================
 * P-256 async (IT) interfaces
 *
 * Same contract as the P-384 / SM2 IT interfaces: submit and return,
 * the completion callback converts the DMEM result to big-endian,
 * writes the caller's output array and invokes the matching weak
 * CallBack.  SharedSecret_IT runs the SDK scalar-mult firmware
 * (ecc256_scalar_mult_text) directly because the app-level wrapper
 * must not reach into ls_hal_otbn_ecc256.c's static curve tables.
 * ==================================================================== */

__attribute__((weak)) void HAL_OTBN_ECDSA_P256_DerivePubkey_CallBack(uint32_t status) {}
__attribute__((weak)) void HAL_OTBN_ECDSA_P256_Sign_CallBack(uint32_t status) {}
__attribute__((weak)) void HAL_OTBN_ECDSA_P256_SharedSecret_CallBack(uint32_t status) {}

static void p256_derive_it_cb(void *param)
{
    uint8_t *pub = (uint8_t *)param;
    uint8_t x[ECDSA_P256_COMPONENT_LENGTH];
    uint8_t y[ECDSA_P256_COMPONENT_LENGTH];
    HAL_OTBN_DMEM_Read(ECC_P256_X_OFFSET, (uint32_t *)x, ECDSA_P256_COMPONENT_LENGTH);
    HAL_OTBN_DMEM_Read(ECC_P256_Y_OFFSET, (uint32_t *)y, ECDSA_P256_COMPONENT_LENGTH);
    reverse_bytes(x, ECDSA_P256_COMPONENT_LENGTH);
    reverse_bytes(y, ECDSA_P256_COMPONENT_LENGTH);
    memcpy(pub, x, ECDSA_P256_COMPONENT_LENGTH);
    memcpy(pub + ECDSA_P256_COMPONENT_LENGTH, y, ECDSA_P256_COMPONENT_LENGTH);
    HAL_OTBN_ECDSA_P256_DerivePubkey_CallBack(0);
}

uint32_t HAL_OTBN_ECDSA_P256_DerivePubkey_IT(const uint8_t priv_key[ECDSA_P256_PRIVATE_KEY_SIZE],
                                          uint8_t pub_key[ECDSA_P256_PUBLIC_KEY_SIZE])
{
    if (!priv_key || !pub_key) return 1;
    if (!ls_otbn_ecc_scalar_in_range(LS_OTBN_ECC_CURVE_P256, priv_key)) return 1;

    uint8_t priv_buf[ECDSA_P256_COMPONENT_LENGTH];
    memcpy(priv_buf, priv_key, ECDSA_P256_COMPONENT_LENGTH);
    reverse_bytes(priv_buf, ECDSA_P256_COMPONENT_LENGTH);

    /* OTBN is a single engine: refuse while a previous job is running */
    if (HAL_OTBN_Is_Busy() || !HAL_OTBN_In_Idle_State()) return 1;

    HAL_OTBN_Checksum_Clear();
    HAL_OTBN_DMEM_Set(0, 0, ECC_P256_DMEM_TOTAL);
    HAL_OTBN_IMEM_Write(0, (const uint32_t *)g_ecc_p256_imem, g_ecc_p256_imem_size);
    HAL_OTBN_DMEM_Write(0, (const uint32_t *)g_ecc_p256_dmem, ECC_P256_DMEM_SIZE);

    uint32_t mode = ECC_P256_MODE_BASE_MULT;
    HAL_OTBN_DMEM_Write(ECC_P256_MODE_OFFSET, &mode, sizeof(uint32_t));
    HAL_OTBN_DMEM_Write(ECC_P256_SCALAR_D_OFFSET, (const uint32_t *)priv_buf, ECDSA_P256_COMPONENT_LENGTH);

    if (HAL_OTBN_CMD_Write_IT(HAL_OTBN_CMD_EXECUTE, p256_derive_it_cb, pub_key) != HAL_OK)
        return 1;
    return 0;
}

static void p256_sign_it_cb(void *param)
{
    uint8_t *sig = (uint8_t *)param;
    uint8_t r[ECDSA_P256_COMPONENT_LENGTH];
    uint8_t s[ECDSA_P256_COMPONENT_LENGTH];
    HAL_OTBN_DMEM_Read(LS_OTBN_ECDSA_P256_R_OFFSET, (uint32_t *)r, ECDSA_P256_COMPONENT_LENGTH);
    HAL_OTBN_DMEM_Read(LS_OTBN_ECDSA_P256_S_OFFSET, (uint32_t *)s, ECDSA_P256_COMPONENT_LENGTH);
    reverse_bytes(r, ECDSA_P256_COMPONENT_LENGTH);
    reverse_bytes(s, ECDSA_P256_COMPONENT_LENGTH);
    memcpy(sig, r, ECDSA_P256_COMPONENT_LENGTH);
    memcpy(sig + ECDSA_P256_COMPONENT_LENGTH, s, ECDSA_P256_COMPONENT_LENGTH);
    HAL_OTBN_ECDSA_P256_Sign_CallBack(0);
}

uint32_t HAL_OTBN_ECDSA_P256_Sign_IT(const uint8_t digest[ECDSA_P256_COMPONENT_LENGTH],
                                 const uint8_t rand_k[ECDSA_P256_COMPONENT_LENGTH],
                                 const uint8_t priv_key[ECDSA_P256_PRIVATE_KEY_SIZE],
                                 uint8_t signature[ECDSA_P256_SIGNATURE_SIZE])
{
    if (!digest || !rand_k || !priv_key || !signature) return 1;
    if (!ls_otbn_ecc_scalar_in_range(LS_OTBN_ECC_CURVE_P256, priv_key)) return 1;
    if (!ls_otbn_ecc_scalar_in_range(LS_OTBN_ECC_CURVE_P256, rand_k)) return 1;

    uint8_t digest_buf[ECDSA_P256_COMPONENT_LENGTH];
    uint8_t rand_buf[ECDSA_P256_COMPONENT_LENGTH];
    uint8_t priv_buf[ECDSA_P256_COMPONENT_LENGTH];
    memcpy(digest_buf, digest, ECDSA_P256_COMPONENT_LENGTH);
    memcpy(rand_buf, rand_k, ECDSA_P256_COMPONENT_LENGTH);
    memcpy(priv_buf, priv_key, ECDSA_P256_COMPONENT_LENGTH);
    reverse_bytes(digest_buf, ECDSA_P256_COMPONENT_LENGTH);
    reverse_bytes(rand_buf, ECDSA_P256_COMPONENT_LENGTH);
    reverse_bytes(priv_buf, ECDSA_P256_COMPONENT_LENGTH);

    /* OTBN is a single engine: refuse while a previous job is running */
    if (HAL_OTBN_Is_Busy() || !HAL_OTBN_In_Idle_State()) return 1;

    HAL_OTBN_Checksum_Clear();
    HAL_OTBN_DMEM_Set(0, 0, LS_OTBN_ECDSA_P256_DMEM_END);
    HAL_OTBN_IMEM_Write(0, (const uint32_t *)p256_imem, p256_imem_size);
    HAL_OTBN_DMEM_Write(0, (const uint32_t *)p256_dmem, p256_dmem_size);

    uint32_t mode = P256_SIGN_MODE;
    HAL_OTBN_DMEM_Write(LS_OTBN_ECDSA_P256_RANDOM_SEED_OFFSET, (const uint32_t *)rand_buf, ECDSA_P256_COMPONENT_LENGTH);
    HAL_OTBN_DMEM_Write(LS_OTBN_ECDSA_P256_MODE_OFFSET, &mode, sizeof(uint32_t));
    HAL_OTBN_DMEM_Set(LS_OTBN_ECDSA_P256_D1_OFFSET, 0, ECDSA_P256_COMPONENT_LENGTH);
    HAL_OTBN_DMEM_Write(LS_OTBN_ECDSA_P256_D0_OFFSET, (const uint32_t *)priv_buf, ECDSA_P256_COMPONENT_LENGTH);
    HAL_OTBN_DMEM_Write(LS_OTBN_ECDSA_P256_MSG_OFFSET, (const uint32_t *)digest_buf, ECDSA_P256_COMPONENT_LENGTH);

    if (HAL_OTBN_CMD_Write_IT(HAL_OTBN_CMD_EXECUTE, p256_sign_it_cb, signature) != HAL_OK)
        return 1;
    return 0;
}

/* Local copy of the P-256 curve table the SDK scalar-mult firmware
 * consumes (same bytes as the static P256 table in ls_hal_otbn_ecc256.c;
 * written to DMEM at ECC256_DMEM_SCALARMULT_CURVE_P_OFFSET, LSW-first). */
extern const char ecc256_scalar_mult_text[1880];

struct otbn_ecc256_curve_param {
    const uint32_t b[8];
    const uint32_t p[8];
    const uint32_t u_p[8];
    const uint32_t n[8];
    const uint32_t u_n[8];
    const uint32_t Gx[8];
    const uint32_t Gy[8];
};

static const struct otbn_ecc256_curve_param p256_curve_param = {
    .b =    {0x27d2604b, 0x3bce3c3e, 0xcc53b0f6, 0x651d06b0, 0x769886bc, 0xb3ebbd55, 0xaa3a93e7, 0x5ac635d8},
    .p =    {0xffffffff, 0xffffffff, 0xffffffff, 0x00000000, 0x00000000, 0x00000000, 0x00000001, 0xffffffff},
    .u_p =  {0x00000003, 0x00000000, 0xffffffff, 0xfffffffe, 0xfffffffe, 0xfffffffe, 0xffffffff, 0x00000000},
    .n =    {0xfc632551, 0xf3b9cac2, 0xa7179e84, 0xbce6faad, 0xffffffff, 0xffffffff, 0x00000000, 0xffffffff},
    .u_n =  {0xeedf9bfe, 0x012ffd85, 0xdf1a6c21, 0x43190552, 0xffffffff, 0xfffffffe, 0xffffffff, 0x00000000},
    .Gx =   {0xd898c296, 0xf4a13945, 0x2deb33a0, 0x77037d81, 0x63a440f2, 0xf8bce6e5, 0xe12c4247, 0x6b17d1f2},
    .Gy =   {0x37bf51f5, 0xcbb64068, 0x6b315ece, 0x2bce3357, 0x7c0f9e16, 0x8ee7eb4a, 0xfe1a7f9b, 0x4fe342e2},
};

#define ECC256_SM_SCALAR_OFFSET   (0x0)
#define ECC256_SM_POINT_X_OFFSET  (0x80)
#define ECC256_SM_POINT_Y_OFFSET  (0xA0)
#define ECC256_SM_RESULT_X_OFFSET (0xC0)
#define ECC256_SM_RESULT_Y_OFFSET (0xE0)
#define ECC256_SM_CURVE_P_OFFSET  (0x100)
#define ECC256_SM_BSS_START       (0x1E0)
#define ECC256_SM_BSS_SIZE        (0x1C0)

static void p256_shared_it_cb(void *param)
{
    uint8_t *shared = (uint8_t *)param;
    uint32_t rx[8], ry[8];
    HAL_OTBN_DMEM_Read(ECC256_SM_RESULT_X_OFFSET, rx, sizeof(rx));
    HAL_OTBN_DMEM_Read(ECC256_SM_RESULT_Y_OFFSET, ry, sizeof(ry));
    u32_le_to_be(rx, shared);
    u32_le_to_be(ry, shared + ECDSA_P256_COMPONENT_LENGTH);
    HAL_OTBN_ECDSA_P256_SharedSecret_CallBack(0);
}

uint32_t HAL_OTBN_ECDSA_P256_SharedSecret_IT(const uint8_t priv_key[ECDSA_P256_PRIVATE_KEY_SIZE],
                                          const uint8_t peer_pub_key[ECDSA_P256_PUBLIC_KEY_SIZE],
                                          uint8_t shared_secret[ECDSA_P256_PUBLIC_KEY_SIZE])
{
    if (!priv_key || !peer_pub_key || !shared_secret) return 1;
    if (!ls_otbn_ecc_scalar_in_range(LS_OTBN_ECC_CURVE_P256, priv_key)) return 1;
    if (!ls_otbn_ecc_point_on_curve(LS_OTBN_ECC_CURVE_P256,
                                    peer_pub_key, peer_pub_key + ECDSA_P256_COMPONENT_LENGTH)) return 1;

    uint32_t scalar[8], point_x[8], point_y[8];
    be_to_u32_le(priv_key, scalar);
    be_to_u32_le(peer_pub_key, point_x);
    be_to_u32_le(peer_pub_key + ECDSA_P256_COMPONENT_LENGTH, point_y);

    /* OTBN is a single engine: refuse while a previous job is running */
    if (HAL_OTBN_Is_Busy() || !HAL_OTBN_In_Idle_State()) return 1;

    /* Program the SDK scalar-mult firmware exactly as
     * HAL_OTBN_ECC256_ScalarMult_Polling/IT does (same DMEM layout,
     * same setup order) but with the local P-256 curve table. */
    HAL_OTBN_IMEM_Write(0, (const uint32_t *)ecc256_scalar_mult_text, sizeof(ecc256_scalar_mult_text));
    HAL_OTBN_DMEM_Write(ECC256_SM_SCALAR_OFFSET, scalar, 0x20);
    HAL_OTBN_DMEM_Set(0x20, 0x0, 0x60);
    HAL_OTBN_DMEM_Write(ECC256_SM_POINT_X_OFFSET, point_x, 0x20);
    HAL_OTBN_DMEM_Write(ECC256_SM_POINT_Y_OFFSET, point_y, 0x20);
    HAL_OTBN_DMEM_Set(ECC256_SM_RESULT_X_OFFSET, 0x0, 0x20);
    HAL_OTBN_DMEM_Set(ECC256_SM_RESULT_Y_OFFSET, 0x0, 0x20);
    HAL_OTBN_DMEM_Write(ECC256_SM_CURVE_P_OFFSET, (const uint32_t *)&p256_curve_param,
                        sizeof(struct otbn_ecc256_curve_param));
    HAL_OTBN_DMEM_Set(ECC256_SM_BSS_START, 0x0, ECC256_SM_BSS_SIZE);

    if (HAL_OTBN_CMD_Write_IT(HAL_OTBN_CMD_EXECUTE, p256_shared_it_cb, shared_secret) != HAL_OK)
        return 1;
    return 0;
}
