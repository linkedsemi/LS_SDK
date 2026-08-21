/**
 * @file ls_hal_otbn_crypto_sm2.c
 * @brief HAL interface for SM2 derive_pubkey / sign / shared_secret
 *        (verification: use HAL_OTBN_SM2_Verify_Polling/IT directly)
 *
 * Layer structure (no duplicated firmware driving here):
 *   - derive_pubkey  -> HAL_OTBN_SM2_BaseMult_Polling    (otbn_sm2_pointops.c)
 *   - shared_secret  -> HAL_OTBN_SM2_ScalarMult_Polling  (otbn_sm2_pointops.c)
 *   - sign           -> unified sm2_imem firmware, SIGN mode (no SDK equivalent)
 */
#include "ls_hal_otbn.h"
#include "ls_otbn_ecc.h"
#include "ls_hal_otbn_ecc.h"
#include "ls_hal_otbn_sm2_pointops.h"
#include <string.h>

/* ====================================================================
 * Helpers
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
 * SM2 derive_pubkey (pointops firmware g_ecc_sm2, BaseMult mode)
 * ==================================================================== */
uint32_t HAL_OTBN_SM2_DerivePubkey(const uint8_t priv_key[SM2_PRIVATE_KEY_SIZE],
                                uint8_t pub_key[SM2_PUBLIC_KEY_SIZE])
{
    if (!priv_key || !pub_key) return 1;
    /* Reject d outside [1, n-1] (mbedtls_ecp_check_privkey) */
    if (!ls_otbn_ecc_scalar_in_range(LS_OTBN_ECC_CURVE_SM2, priv_key)) return 1;

    /* g_ecc_sm2 DMEM uses little-endian words: reverse the scalar first */
    uint8_t priv_le[SM2_COMPONENT_LENGTH];
    memcpy(priv_le, priv_key, SM2_COMPONENT_LENGTH);
    reverse_bytes(priv_le, SM2_COMPONENT_LENGTH);

    HAL_OTBN_Checksum_Clear();
    if (HAL_OTBN_SM2_BaseMult_Polling(priv_le, pub_key,
                                      pub_key + SM2_COMPONENT_LENGTH) != HAL_OK)
        return 1;

    reverse_bytes(pub_key, SM2_COMPONENT_LENGTH);
    reverse_bytes(pub_key + SM2_COMPONENT_LENGTH, SM2_COMPONENT_LENGTH);
    return 0;
}

/* ====================================================================
 * SM2 sign (unified sm2 firmware, SIGN mode 0x15b)
 * ==================================================================== */
#define SM2_SIGN_MODE 0x0000015b

uint32_t HAL_OTBN_SM2_Sign(const uint8_t sm2_e[SM2_COMPONENT_LENGTH],
                       const uint8_t rand_k[SM2_COMPONENT_LENGTH],
                       const uint8_t priv_key[SM2_PRIVATE_KEY_SIZE],
                       uint8_t signature[SM2_SIGNATURE_SIZE])
{
    if (!sm2_e || !rand_k || !priv_key || !signature) return 1;
    /* Reject d / k outside [1, n-1]: an out-of-range ephemeral key
     * produces a degenerate signature (r or s == 0) */
    if (!ls_otbn_ecc_scalar_in_range(LS_OTBN_ECC_CURVE_SM2, priv_key)) return 1;
    if (!ls_otbn_ecc_scalar_in_range(LS_OTBN_ECC_CURVE_SM2, rand_k)) return 1;

    uint8_t e_buf[SM2_COMPONENT_LENGTH];
    uint8_t rand_buf[SM2_COMPONENT_LENGTH];
    uint8_t priv_buf[SM2_COMPONENT_LENGTH];
    memcpy(e_buf, sm2_e, SM2_COMPONENT_LENGTH);
    memcpy(rand_buf, rand_k, SM2_COMPONENT_LENGTH);
    memcpy(priv_buf, priv_key, SM2_COMPONENT_LENGTH);
    reverse_bytes(e_buf, SM2_COMPONENT_LENGTH);
    reverse_bytes(rand_buf, SM2_COMPONENT_LENGTH);
    reverse_bytes(priv_buf, SM2_COMPONENT_LENGTH);

    HAL_OTBN_Checksum_Clear();

    uint32_t mode = SM2_SIGN_MODE;
    HAL_OTBN_DMEM_Set(0, 0, LS_OTBN_SM2_DMEM_END);
    HAL_OTBN_IMEM_Write(0, (uint32_t *)sm2_imem, sm2_imem_size);
    HAL_OTBN_DMEM_Write(0, (uint32_t *)sm2_dmem, sm2_dmem_size);
    HAL_OTBN_DMEM_Write(LS_OTBN_SM2_RANDOM_SEED_OFFSET, (const uint32_t *)rand_buf, SM2_COMPONENT_LENGTH);
    HAL_OTBN_DMEM_Write(LS_OTBN_SM2_MODE_OFFSET, &mode, sizeof(uint32_t));
    HAL_OTBN_DMEM_Set(LS_OTBN_SM2_D1_OFFSET, 0, SM2_COMPONENT_LENGTH);
    HAL_OTBN_DMEM_Write(LS_OTBN_SM2_D0_OFFSET, (const uint32_t *)priv_buf, SM2_COMPONENT_LENGTH);
    HAL_OTBN_DMEM_Write(LS_OTBN_SM2_MSG_OFFSET, (const uint32_t *)e_buf, SM2_COMPONENT_LENGTH);
    if (HAL_OTBN_CMD_Write_Polling_Timeout(HAL_OTBN_CMD_EXECUTE, 20000) != HAL_OK)
        return 1;

    HAL_OTBN_DMEM_Read(LS_OTBN_SM2_R_OFFSET, (uint32_t *)signature, SM2_COMPONENT_LENGTH);
    HAL_OTBN_DMEM_Read(LS_OTBN_SM2_S_OFFSET, (uint32_t *)(signature + SM2_COMPONENT_LENGTH), SM2_COMPONENT_LENGTH);
    reverse_bytes(signature, SM2_COMPONENT_LENGTH);
    reverse_bytes(signature + SM2_COMPONENT_LENGTH, SM2_COMPONENT_LENGTH);
    return 0;
}

/* ====================================================================
 * SM2 shared_secret (pointops firmware g_ecc_sm2, ScalarMult mode)
 * ==================================================================== */
uint32_t HAL_OTBN_SM2_SharedSecret(const uint8_t priv_key[SM2_PRIVATE_KEY_SIZE],
                                const uint8_t pub_key[SM2_PUBLIC_KEY_SIZE],
                                uint8_t shared[SM2_PUBLIC_KEY_SIZE])
{
    if (!priv_key || !pub_key || !shared) return 1;
    if (!ls_otbn_ecc_scalar_in_range(LS_OTBN_ECC_CURVE_SM2, priv_key)) return 1;
    if (!ls_otbn_ecc_point_on_curve(LS_OTBN_ECC_CURVE_SM2,
                                    pub_key, pub_key + SM2_COMPONENT_LENGTH)) return 1;

    /* g_ecc_sm2 DMEM uses little-endian words: reverse inputs first */
    uint8_t scalar_le[SM2_COMPONENT_LENGTH];
    uint8_t px_le[SM2_COMPONENT_LENGTH];
    uint8_t py_le[SM2_COMPONENT_LENGTH];
    memcpy(scalar_le, priv_key, SM2_COMPONENT_LENGTH);
    memcpy(px_le, pub_key, SM2_COMPONENT_LENGTH);
    memcpy(py_le, pub_key + SM2_COMPONENT_LENGTH, SM2_COMPONENT_LENGTH);
    reverse_bytes(scalar_le, SM2_COMPONENT_LENGTH);
    reverse_bytes(px_le, SM2_COMPONENT_LENGTH);
    reverse_bytes(py_le, SM2_COMPONENT_LENGTH);

    /* Delegate to the pointops scalar-mult path
     * (HAL_OTBN_SM2_ScalarMult_Polling, g_ecc_sm2 firmware).
     * The pointops firmware (BaseMult and ScalarMult alike) outputs
     * LSW-first u32 words, so reverse back to big-endian.  (Verified
     * by k*G == DerivePubkey(k) checks in the otbn_ecdsa example.) */
    HAL_OTBN_Checksum_Clear();
    if (HAL_OTBN_SM2_ScalarMult_Polling(scalar_le, px_le, py_le,
                                        shared, shared + SM2_COMPONENT_LENGTH) != HAL_OK)
        return 1;
    reverse_bytes(shared, SM2_COMPONENT_LENGTH);
    reverse_bytes(shared + SM2_COMPONENT_LENGTH, SM2_COMPONENT_LENGTH);
    return 0;
}

/* ====================================================================
 * SM2 async (IT) interfaces
 *
 * Same contract as the P-384 IT interfaces: submit and return, the
 * completion callback converts the DMEM result to big-endian, writes
 * the caller's output array and invokes the matching weak CallBack.
 * NOTE: unlike P-384, the SM2 pointops firmware writes its result
 * back into the X/Y DMEM slots, so the callbacks read ECC_SM2_X/Y.
 * ==================================================================== */

__attribute__((weak)) void HAL_OTBN_SM2_DerivePubkey_CallBack(uint32_t status) {}
__attribute__((weak)) void HAL_OTBN_SM2_Sign_CallBack(uint32_t status) {}
__attribute__((weak)) void HAL_OTBN_SM2_SharedSecret_CallBack(uint32_t status) {}

static void sm2_derive_it_cb(void *param)
{
    uint8_t *pub = (uint8_t *)param;
    uint8_t x[SM2_COMPONENT_LENGTH];
    uint8_t y[SM2_COMPONENT_LENGTH];
    HAL_OTBN_DMEM_Read(ECC_SM2_X_OFFSET, (uint32_t *)x, SM2_COMPONENT_LENGTH);
    HAL_OTBN_DMEM_Read(ECC_SM2_Y_OFFSET, (uint32_t *)y, SM2_COMPONENT_LENGTH);
    reverse_bytes(x, SM2_COMPONENT_LENGTH);
    reverse_bytes(y, SM2_COMPONENT_LENGTH);
    memcpy(pub, x, SM2_COMPONENT_LENGTH);
    memcpy(pub + SM2_COMPONENT_LENGTH, y, SM2_COMPONENT_LENGTH);
    HAL_OTBN_SM2_DerivePubkey_CallBack(0);
}

uint32_t HAL_OTBN_SM2_DerivePubkey_IT(const uint8_t priv_key[SM2_PRIVATE_KEY_SIZE],
                                   uint8_t pub_key[SM2_PUBLIC_KEY_SIZE])
{
    if (!priv_key || !pub_key) return 1;
    if (!ls_otbn_ecc_scalar_in_range(LS_OTBN_ECC_CURVE_SM2, priv_key)) return 1;

    uint8_t priv_le[SM2_COMPONENT_LENGTH];
    memcpy(priv_le, priv_key, SM2_COMPONENT_LENGTH);
    reverse_bytes(priv_le, SM2_COMPONENT_LENGTH);

    /* OTBN is a single engine: refuse while a previous job is running */
    if (HAL_OTBN_Is_Busy() || !HAL_OTBN_In_Idle_State()) return 1;

    HAL_OTBN_Checksum_Clear();
    HAL_OTBN_IMEM_Write(0, (const uint32_t *)g_ecc_sm2_imem, g_ecc_sm2_imem_size);
    HAL_OTBN_DMEM_Set(0, 0, ECC_SM2_DMEM_TOTAL);
    HAL_OTBN_DMEM_Write(0, (const uint32_t *)g_ecc_sm2_dmem, ECC_SM2_DMEM_SIZE);

    uint32_t mode = ECC_SM2_MODE_BASE_MULT;
    HAL_OTBN_DMEM_Write(ECC_SM2_MODE_OFFSET, &mode, sizeof(uint32_t));
    HAL_OTBN_DMEM_Write(ECC_SM2_SCALAR_D_OFFSET, (const uint32_t *)priv_le, SM2_COMPONENT_LENGTH);

    if (HAL_OTBN_CMD_Write_IT(HAL_OTBN_CMD_EXECUTE, sm2_derive_it_cb, pub_key) != HAL_OK)
        return 1;
    return 0;
}

static void sm2_sign_it_cb(void *param)
{
    uint8_t *sig = (uint8_t *)param;
    uint8_t r[SM2_COMPONENT_LENGTH];
    uint8_t s[SM2_COMPONENT_LENGTH];
    HAL_OTBN_DMEM_Read(LS_OTBN_SM2_R_OFFSET, (uint32_t *)r, SM2_COMPONENT_LENGTH);
    HAL_OTBN_DMEM_Read(LS_OTBN_SM2_S_OFFSET, (uint32_t *)s, SM2_COMPONENT_LENGTH);
    reverse_bytes(r, SM2_COMPONENT_LENGTH);
    reverse_bytes(s, SM2_COMPONENT_LENGTH);
    memcpy(sig, r, SM2_COMPONENT_LENGTH);
    memcpy(sig + SM2_COMPONENT_LENGTH, s, SM2_COMPONENT_LENGTH);
    HAL_OTBN_SM2_Sign_CallBack(0);
}

uint32_t HAL_OTBN_SM2_Sign_IT(const uint8_t sm2_e[SM2_COMPONENT_LENGTH],
                          const uint8_t rand_k[SM2_COMPONENT_LENGTH],
                          const uint8_t priv_key[SM2_PRIVATE_KEY_SIZE],
                          uint8_t signature[SM2_SIGNATURE_SIZE])
{
    if (!sm2_e || !rand_k || !priv_key || !signature) return 1;
    if (!ls_otbn_ecc_scalar_in_range(LS_OTBN_ECC_CURVE_SM2, priv_key)) return 1;
    if (!ls_otbn_ecc_scalar_in_range(LS_OTBN_ECC_CURVE_SM2, rand_k)) return 1;

    uint8_t e_buf[SM2_COMPONENT_LENGTH];
    uint8_t rand_buf[SM2_COMPONENT_LENGTH];
    uint8_t priv_buf[SM2_COMPONENT_LENGTH];
    memcpy(e_buf, sm2_e, SM2_COMPONENT_LENGTH);
    memcpy(rand_buf, rand_k, SM2_COMPONENT_LENGTH);
    memcpy(priv_buf, priv_key, SM2_COMPONENT_LENGTH);
    reverse_bytes(e_buf, SM2_COMPONENT_LENGTH);
    reverse_bytes(rand_buf, SM2_COMPONENT_LENGTH);
    reverse_bytes(priv_buf, SM2_COMPONENT_LENGTH);

    /* OTBN is a single engine: refuse while a previous job is running */
    if (HAL_OTBN_Is_Busy() || !HAL_OTBN_In_Idle_State()) return 1;

    HAL_OTBN_Checksum_Clear();

    uint32_t mode = SM2_SIGN_MODE;
    HAL_OTBN_DMEM_Set(0, 0, LS_OTBN_SM2_DMEM_END);
    HAL_OTBN_IMEM_Write(0, (uint32_t *)sm2_imem, sm2_imem_size);
    HAL_OTBN_DMEM_Write(0, (uint32_t *)sm2_dmem, sm2_dmem_size);
    HAL_OTBN_DMEM_Write(LS_OTBN_SM2_RANDOM_SEED_OFFSET, (const uint32_t *)rand_buf, SM2_COMPONENT_LENGTH);
    HAL_OTBN_DMEM_Write(LS_OTBN_SM2_MODE_OFFSET, &mode, sizeof(uint32_t));
    HAL_OTBN_DMEM_Set(LS_OTBN_SM2_D1_OFFSET, 0, SM2_COMPONENT_LENGTH);
    HAL_OTBN_DMEM_Write(LS_OTBN_SM2_D0_OFFSET, (const uint32_t *)priv_buf, SM2_COMPONENT_LENGTH);
    HAL_OTBN_DMEM_Write(LS_OTBN_SM2_MSG_OFFSET, (const uint32_t *)e_buf, SM2_COMPONENT_LENGTH);

    if (HAL_OTBN_CMD_Write_IT(HAL_OTBN_CMD_EXECUTE, sm2_sign_it_cb, signature) != HAL_OK)
        return 1;
    return 0;
}

static void sm2_shared_it_cb(void *param)
{
    uint8_t *shared = (uint8_t *)param;
    uint8_t x[SM2_COMPONENT_LENGTH];
    uint8_t y[SM2_COMPONENT_LENGTH];
    HAL_OTBN_DMEM_Read(ECC_SM2_X_OFFSET, (uint32_t *)x, SM2_COMPONENT_LENGTH);
    HAL_OTBN_DMEM_Read(ECC_SM2_Y_OFFSET, (uint32_t *)y, SM2_COMPONENT_LENGTH);
    reverse_bytes(x, SM2_COMPONENT_LENGTH);
    reverse_bytes(y, SM2_COMPONENT_LENGTH);
    memcpy(shared, x, SM2_COMPONENT_LENGTH);
    memcpy(shared + SM2_COMPONENT_LENGTH, y, SM2_COMPONENT_LENGTH);
    HAL_OTBN_SM2_SharedSecret_CallBack(0);
}

uint32_t HAL_OTBN_SM2_SharedSecret_IT(const uint8_t priv_key[SM2_PRIVATE_KEY_SIZE],
                                   const uint8_t peer_pub_key[SM2_PUBLIC_KEY_SIZE],
                                   uint8_t shared_secret[SM2_PUBLIC_KEY_SIZE])
{
    if (!priv_key || !peer_pub_key || !shared_secret) return 1;
    if (!ls_otbn_ecc_scalar_in_range(LS_OTBN_ECC_CURVE_SM2, priv_key)) return 1;
    if (!ls_otbn_ecc_point_on_curve(LS_OTBN_ECC_CURVE_SM2,
                                    peer_pub_key, peer_pub_key + SM2_COMPONENT_LENGTH)) return 1;

    uint8_t scalar_le[SM2_COMPONENT_LENGTH];
    uint8_t px_le[SM2_COMPONENT_LENGTH];
    uint8_t py_le[SM2_COMPONENT_LENGTH];
    memcpy(scalar_le, priv_key, SM2_COMPONENT_LENGTH);
    memcpy(px_le, peer_pub_key, SM2_COMPONENT_LENGTH);
    memcpy(py_le, peer_pub_key + SM2_COMPONENT_LENGTH, SM2_COMPONENT_LENGTH);
    reverse_bytes(scalar_le, SM2_COMPONENT_LENGTH);
    reverse_bytes(px_le, SM2_COMPONENT_LENGTH);
    reverse_bytes(py_le, SM2_COMPONENT_LENGTH);

    /* OTBN is a single engine: refuse while a previous job is running */
    if (HAL_OTBN_Is_Busy() || !HAL_OTBN_In_Idle_State()) return 1;

    HAL_OTBN_Checksum_Clear();
    HAL_OTBN_IMEM_Write(0, (const uint32_t *)g_ecc_sm2_imem, g_ecc_sm2_imem_size);
    HAL_OTBN_DMEM_Set(0, 0, ECC_SM2_DMEM_TOTAL);
    HAL_OTBN_DMEM_Write(0, (const uint32_t *)g_ecc_sm2_dmem, ECC_SM2_DMEM_SIZE);

    uint32_t mode = ECC_SM2_MODE_SCALAR_MULT;
    HAL_OTBN_DMEM_Write(ECC_SM2_MODE_OFFSET, &mode, sizeof(uint32_t));
    HAL_OTBN_DMEM_Write(ECC_SM2_SCALAR_D_OFFSET, (const uint32_t *)scalar_le, SM2_COMPONENT_LENGTH);
    HAL_OTBN_DMEM_Write(ECC_SM2_X_OFFSET, (const uint32_t *)px_le, SM2_COMPONENT_LENGTH);
    HAL_OTBN_DMEM_Write(ECC_SM2_Y_OFFSET, (const uint32_t *)py_le, SM2_COMPONENT_LENGTH);

    if (HAL_OTBN_CMD_Write_IT(HAL_OTBN_CMD_EXECUTE, sm2_shared_it_cb, shared_secret) != HAL_OK)
        return 1;
    return 0;
}
