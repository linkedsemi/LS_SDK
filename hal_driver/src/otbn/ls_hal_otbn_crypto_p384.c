/**
 * @file ls_hal_otbn_crypto_p384.c
 * @brief HAL interface for ECDSA P-384 derive_pubkey / sign / shared_secret
 *        (verification: use HAL_OTBN_ECC384_ECDSA_Verify_Polling/IT directly)
 */
#include "ls_hal_otbn.h"
#include "ls_otbn_ecc.h"
#include "ls_hal_otbn_ecc.h"
#include "ls_hal_otbn_p384_pointops.h"
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
 * P-384 derive_pubkey (pointops firmware g_ecc_p384, BaseMult mode)
 * ==================================================================== */
ls_otbn_status_t HAL_OTBN_ECDSA_P384_DerivePubkey(const uint8_t priv_key[ECDSA_P384_PRIVATE_KEY_SIZE],
                                       uint8_t pub_key[ECDSA_P384_PUBLIC_KEY_SIZE])
{
    if (!priv_key || !pub_key) return LS_OTBN_INVALID_PARAM;
    /* Reject d outside [1, n-1] (mbedtls_ecp_check_privkey) */
    if (!ls_otbn_ecc_scalar_in_range(LS_OTBN_ECC_CURVE_P384, priv_key)) return LS_OTBN_SCALAR_RANGE;

    uint8_t priv_buf[ECDSA_P384_COMPONENT_LENGTH];
    memcpy(priv_buf, priv_key, ECDSA_P384_COMPONENT_LENGTH);
    reverse_bytes(priv_buf, ECDSA_P384_COMPONENT_LENGTH);

    HAL_OTBN_Checksum_Clear();
    HAL_OTBN_DMEM_Set(0, 0, ECC_P384_DMEM_TOTAL);
    HAL_OTBN_IMEM_Write(0, (const uint32_t *)g_ecc_p384_imem, g_ecc_p384_imem_size);
    HAL_OTBN_DMEM_Write(0, (const uint32_t *)g_ecc_p384_dmem, ECC_P384_DMEM_SIZE);

    uint32_t mode = ECC_P384_MODE_BASE_MULT;
    HAL_OTBN_DMEM_Write(ECC_P384_MODE_OFFSET, &mode, sizeof(uint32_t));
    HAL_OTBN_DMEM_Write(ECC_P384_SCALAR_D_OFFSET, (const uint32_t *)priv_buf, ECDSA_P384_COMPONENT_LENGTH);

    HAL_StatusTypeDef st = HAL_OTBN_CMD_Write_Polling_Timeout(HAL_OTBN_CMD_EXECUTE, 20000);
    if (st != HAL_OK)
        return ls_otbn_status_from_hal(st);

    HAL_OTBN_DMEM_Read(ECC_P384_RX_OFFSET, (uint32_t *)pub_key, ECDSA_P384_COMPONENT_LENGTH);
    HAL_OTBN_DMEM_Read(ECC_P384_RY_OFFSET, (uint32_t *)(pub_key + ECDSA_P384_COMPONENT_LENGTH), ECDSA_P384_COMPONENT_LENGTH);
    reverse_bytes(pub_key, ECDSA_P384_COMPONENT_LENGTH);
    reverse_bytes(pub_key + ECDSA_P384_COMPONENT_LENGTH, ECDSA_P384_COMPONENT_LENGTH);
    return LS_OTBN_OK;
}

/* ====================================================================
 * P-384 sign (unified p384 firmware, SIGN mode 0x15b)
 * ==================================================================== */
#define P384_SIGN_MODE 0x0000015b

ls_otbn_status_t HAL_OTBN_ECDSA_P384_Sign(const uint8_t digest[ECDSA_P384_COMPONENT_LENGTH],
                              const uint8_t rand_k[ECDSA_P384_COMPONENT_LENGTH],
                              const uint8_t priv_key[ECDSA_P384_PRIVATE_KEY_SIZE],
                              uint8_t signature[ECDSA_P384_SIGNATURE_SIZE])
{
    if (!digest || !rand_k || !priv_key || !signature) return LS_OTBN_INVALID_PARAM;
    /* Reject d / k outside [1, n-1]: an out-of-range ephemeral key
     * produces a degenerate signature (r or s == 0) */
    if (!ls_otbn_ecc_scalar_in_range(LS_OTBN_ECC_CURVE_P384, priv_key)) return LS_OTBN_SCALAR_RANGE;
    if (!ls_otbn_ecc_scalar_in_range(LS_OTBN_ECC_CURVE_P384, rand_k)) return LS_OTBN_SCALAR_RANGE;

    uint8_t digest_buf[ECDSA_P384_COMPONENT_LENGTH];
    uint8_t rand_buf[ECDSA_P384_COMPONENT_LENGTH];
    uint8_t priv_buf[ECDSA_P384_COMPONENT_LENGTH];
    memcpy(digest_buf, digest, ECDSA_P384_COMPONENT_LENGTH);
    memcpy(rand_buf, rand_k, ECDSA_P384_COMPONENT_LENGTH);
    memcpy(priv_buf, priv_key, ECDSA_P384_COMPONENT_LENGTH);
    reverse_bytes(digest_buf, ECDSA_P384_COMPONENT_LENGTH);
    reverse_bytes(rand_buf, ECDSA_P384_COMPONENT_LENGTH);
    reverse_bytes(priv_buf, ECDSA_P384_COMPONENT_LENGTH);

    HAL_OTBN_Checksum_Clear();
    HAL_OTBN_DMEM_Set(0, 0, LS_OTBN_ECDSA_P384_DMEM_END);
    HAL_OTBN_IMEM_Write(0, (const uint32_t *)p384_imem, p384_imem_size);
    HAL_OTBN_DMEM_Write(0, (const uint32_t *)p384_dmem, p384_dmem_size);

    uint32_t mode = P384_SIGN_MODE;
    HAL_OTBN_DMEM_Write(LS_OTBN_ECDSA_P384_RANDOM_SEED_OFFSET, (const uint32_t *)rand_buf, ECDSA_P384_COMPONENT_LENGTH);
    HAL_OTBN_DMEM_Write(LS_OTBN_ECDSA_P384_MODE_OFFSET, &mode, sizeof(uint32_t));
    HAL_OTBN_DMEM_Set(LS_OTBN_ECDSA_P384_D1_OFFSET, 0, ECDSA_P384_COMPONENT_LENGTH);
    HAL_OTBN_DMEM_Write(LS_OTBN_ECDSA_P384_D0_OFFSET, (const uint32_t *)priv_buf, ECDSA_P384_COMPONENT_LENGTH);
    HAL_OTBN_DMEM_Write(LS_OTBN_ECDSA_P384_MSG_OFFSET, (const uint32_t *)digest_buf, ECDSA_P384_COMPONENT_LENGTH);

    HAL_StatusTypeDef st = HAL_OTBN_CMD_Write_Polling_Timeout(HAL_OTBN_CMD_EXECUTE, 20000);
    if (st != HAL_OK)
        return ls_otbn_status_from_hal(st);

    HAL_OTBN_DMEM_Read(LS_OTBN_ECDSA_P384_R_OFFSET, (uint32_t *)signature, ECDSA_P384_COMPONENT_LENGTH);
    HAL_OTBN_DMEM_Read(LS_OTBN_ECDSA_P384_S_OFFSET, (uint32_t *)(signature + ECDSA_P384_COMPONENT_LENGTH), ECDSA_P384_COMPONENT_LENGTH);
    reverse_bytes(signature, ECDSA_P384_COMPONENT_LENGTH);
    reverse_bytes(signature + ECDSA_P384_COMPONENT_LENGTH, ECDSA_P384_COMPONENT_LENGTH);
    return LS_OTBN_OK;
}

/* ====================================================================
 * P-384 shared_secret (pointops firmware g_ecc_p384, ScalarMult mode)
 *
 * Same structure as the SM2 shared_secret: delegate to the pointops
 * scalar-mult path.  (P-256 shared_secret uses the SDK scalar-mult
 * firmware instead -- the unified p256 firmware's SHARED_KEY mode was
 * found to produce wrong points and hang on some scalars.)
 * ==================================================================== */
ls_otbn_status_t HAL_OTBN_ECDSA_P384_SharedSecret(const uint8_t priv_key[ECDSA_P384_PRIVATE_KEY_SIZE],
                                       const uint8_t pub_key[ECDSA_P384_PUBLIC_KEY_SIZE],
                                       uint8_t shared[ECDSA_P384_PUBLIC_KEY_SIZE])
{
    if (!priv_key || !pub_key || !shared) return LS_OTBN_INVALID_PARAM;
    if (!ls_otbn_ecc_scalar_in_range(LS_OTBN_ECC_CURVE_P384, priv_key)) return LS_OTBN_SCALAR_RANGE;
    if (!ls_otbn_ecc_point_on_curve(LS_OTBN_ECC_CURVE_P384,
                                    pub_key, pub_key + ECDSA_P384_COMPONENT_LENGTH)) return LS_OTBN_POINT_NOT_ON_CURVE;

    /* g_ecc_p384 DMEM uses little-endian words: reverse inputs first */
    uint8_t scalar_le[ECDSA_P384_COMPONENT_LENGTH];
    uint8_t px_le[ECDSA_P384_COMPONENT_LENGTH];
    uint8_t py_le[ECDSA_P384_COMPONENT_LENGTH];
    memcpy(scalar_le, priv_key, ECDSA_P384_COMPONENT_LENGTH);
    memcpy(px_le, pub_key, ECDSA_P384_COMPONENT_LENGTH);
    memcpy(py_le, pub_key + ECDSA_P384_COMPONENT_LENGTH, ECDSA_P384_COMPONENT_LENGTH);
    reverse_bytes(scalar_le, ECDSA_P384_COMPONENT_LENGTH);
    reverse_bytes(px_le, ECDSA_P384_COMPONENT_LENGTH);
    reverse_bytes(py_le, ECDSA_P384_COMPONENT_LENGTH);

    /* Delegate to the pointops scalar-mult path
     * (HAL_OTBN_P384_ScalarMult_Polling, g_ecc_p384 firmware).
     * The pointops firmware (BaseMult and ScalarMult alike) outputs
     * LSW-first u32 words, so reverse back to big-endian.  (The
     * otbn_ecdsa example cross-checks ScalarMult vs BaseMult; the SM2
     * twin of this path is verified by the same k*G checks.) */
    HAL_OTBN_Checksum_Clear();
    HAL_StatusTypeDef st = HAL_OTBN_P384_ScalarMult_Polling(scalar_le, px_le, py_le,
                                         shared, shared + ECDSA_P384_COMPONENT_LENGTH);
    if (st != HAL_OK)
        return ls_otbn_status_from_hal(st);
    reverse_bytes(shared, ECDSA_P384_COMPONENT_LENGTH);
    reverse_bytes(shared + ECDSA_P384_COMPONENT_LENGTH, ECDSA_P384_COMPONENT_LENGTH);
    return LS_OTBN_OK;
}

/* ====================================================================
 * P-384 async (IT) interfaces
 *
 * Submit the same operations as the Polling wrappers above without
 * waiting.  The completion callback reads the OTBN DMEM result,
 * converts it to big-endian and writes the caller's output array
 * (the pointer passed to HAL_OTBN_CMD_Write_IT), then invokes the
 * matching weak CallBack.  Output arrays must stay valid until the
 * callback fires; inputs are consumed at submit time.
 * ==================================================================== */

__attribute__((weak)) void HAL_OTBN_ECDSA_P384_DerivePubkey_CallBack(ls_otbn_status_t status) {}
__attribute__((weak)) void HAL_OTBN_ECDSA_P384_Sign_CallBack(ls_otbn_status_t status) {}
__attribute__((weak)) void HAL_OTBN_ECDSA_P384_SharedSecret_CallBack(ls_otbn_status_t status) {}

static void p384_derive_it_cb(void *param)
{
    uint8_t *pub = (uint8_t *)param;
    uint8_t x[ECDSA_P384_COMPONENT_LENGTH];
    uint8_t y[ECDSA_P384_COMPONENT_LENGTH];
    /* Engine flagged an error: the DMEM result is untrustworthy. */
    if (HAL_OTBN_Error_Bit_Get() != 0) {
        HAL_OTBN_ECDSA_P384_DerivePubkey_CallBack(LS_OTBN_ENGINE);
        return;
    }
    HAL_OTBN_DMEM_Read(ECC_P384_RX_OFFSET, (uint32_t *)x, ECDSA_P384_COMPONENT_LENGTH);
    HAL_OTBN_DMEM_Read(ECC_P384_RY_OFFSET, (uint32_t *)y, ECDSA_P384_COMPONENT_LENGTH);
    reverse_bytes(x, ECDSA_P384_COMPONENT_LENGTH);
    reverse_bytes(y, ECDSA_P384_COMPONENT_LENGTH);
    memcpy(pub, x, ECDSA_P384_COMPONENT_LENGTH);
    memcpy(pub + ECDSA_P384_COMPONENT_LENGTH, y, ECDSA_P384_COMPONENT_LENGTH);
    HAL_OTBN_ECDSA_P384_DerivePubkey_CallBack(LS_OTBN_OK);
}

ls_otbn_status_t HAL_OTBN_ECDSA_P384_DerivePubkey_IT(const uint8_t priv_key[ECDSA_P384_PRIVATE_KEY_SIZE],
                                          uint8_t pub_key[ECDSA_P384_PUBLIC_KEY_SIZE])
{
    if (!priv_key || !pub_key) return LS_OTBN_INVALID_PARAM;
    if (!ls_otbn_ecc_scalar_in_range(LS_OTBN_ECC_CURVE_P384, priv_key)) return LS_OTBN_SCALAR_RANGE;

    uint8_t priv_buf[ECDSA_P384_COMPONENT_LENGTH];
    memcpy(priv_buf, priv_key, ECDSA_P384_COMPONENT_LENGTH);
    reverse_bytes(priv_buf, ECDSA_P384_COMPONENT_LENGTH);

    /* OTBN is a single engine: refuse while a previous job is running
     * (would otherwise corrupt its IMEM/DMEM and never fire the callback). */
    if (HAL_OTBN_Is_Busy() || !HAL_OTBN_In_Idle_State()) return LS_OTBN_BUSY;

    HAL_OTBN_Checksum_Clear();
    HAL_OTBN_IMEM_Write(0, (const uint32_t *)g_ecc_p384_imem, g_ecc_p384_imem_size);
    HAL_OTBN_DMEM_Set(0, 0, ECC_P384_DMEM_TOTAL);
    HAL_OTBN_DMEM_Write(0, (const uint32_t *)g_ecc_p384_dmem, ECC_P384_DMEM_SIZE);

    uint32_t mode = ECC_P384_MODE_BASE_MULT;
    HAL_OTBN_DMEM_Write(ECC_P384_MODE_OFFSET, &mode, sizeof(uint32_t));
    HAL_OTBN_DMEM_Write(ECC_P384_SCALAR_D_OFFSET, (const uint32_t *)priv_buf, ECDSA_P384_COMPONENT_LENGTH);

    HAL_StatusTypeDef st = HAL_OTBN_CMD_Write_IT(HAL_OTBN_CMD_EXECUTE, p384_derive_it_cb, pub_key);
    if (st != HAL_OK)
        return ls_otbn_status_from_hal(st);
    return LS_OTBN_OK;
}

static void p384_sign_it_cb(void *param)
{
    uint8_t *sig = (uint8_t *)param;
    uint8_t r[ECDSA_P384_COMPONENT_LENGTH];
    uint8_t s[ECDSA_P384_COMPONENT_LENGTH];
    /* Engine flagged an error: the DMEM result is untrustworthy. */
    if (HAL_OTBN_Error_Bit_Get() != 0) {
        HAL_OTBN_ECDSA_P384_Sign_CallBack(LS_OTBN_ENGINE);
        return;
    }
    HAL_OTBN_DMEM_Read(LS_OTBN_ECDSA_P384_R_OFFSET, (uint32_t *)r, ECDSA_P384_COMPONENT_LENGTH);
    HAL_OTBN_DMEM_Read(LS_OTBN_ECDSA_P384_S_OFFSET, (uint32_t *)s, ECDSA_P384_COMPONENT_LENGTH);
    reverse_bytes(r, ECDSA_P384_COMPONENT_LENGTH);
    reverse_bytes(s, ECDSA_P384_COMPONENT_LENGTH);
    memcpy(sig, r, ECDSA_P384_COMPONENT_LENGTH);
    memcpy(sig + ECDSA_P384_COMPONENT_LENGTH, s, ECDSA_P384_COMPONENT_LENGTH);
    HAL_OTBN_ECDSA_P384_Sign_CallBack(LS_OTBN_OK);
}

ls_otbn_status_t HAL_OTBN_ECDSA_P384_Sign_IT(const uint8_t digest[ECDSA_P384_COMPONENT_LENGTH],
                                 const uint8_t rand_k[ECDSA_P384_COMPONENT_LENGTH],
                                 const uint8_t priv_key[ECDSA_P384_PRIVATE_KEY_SIZE],
                                 uint8_t signature[ECDSA_P384_SIGNATURE_SIZE])
{
    if (!digest || !rand_k || !priv_key || !signature) return LS_OTBN_INVALID_PARAM;
    if (!ls_otbn_ecc_scalar_in_range(LS_OTBN_ECC_CURVE_P384, priv_key)) return LS_OTBN_SCALAR_RANGE;
    if (!ls_otbn_ecc_scalar_in_range(LS_OTBN_ECC_CURVE_P384, rand_k)) return LS_OTBN_SCALAR_RANGE;

    uint8_t digest_buf[ECDSA_P384_COMPONENT_LENGTH];
    uint8_t rand_buf[ECDSA_P384_COMPONENT_LENGTH];
    uint8_t priv_buf[ECDSA_P384_COMPONENT_LENGTH];
    memcpy(digest_buf, digest, ECDSA_P384_COMPONENT_LENGTH);
    memcpy(rand_buf, rand_k, ECDSA_P384_COMPONENT_LENGTH);
    memcpy(priv_buf, priv_key, ECDSA_P384_COMPONENT_LENGTH);
    reverse_bytes(digest_buf, ECDSA_P384_COMPONENT_LENGTH);
    reverse_bytes(rand_buf, ECDSA_P384_COMPONENT_LENGTH);
    reverse_bytes(priv_buf, ECDSA_P384_COMPONENT_LENGTH);

    /* OTBN is a single engine: refuse while a previous job is running */
    if (HAL_OTBN_Is_Busy() || !HAL_OTBN_In_Idle_State()) return LS_OTBN_BUSY;

    HAL_OTBN_Checksum_Clear();
    HAL_OTBN_DMEM_Set(0, 0, LS_OTBN_ECDSA_P384_DMEM_END);
    HAL_OTBN_IMEM_Write(0, (const uint32_t *)p384_imem, p384_imem_size);
    HAL_OTBN_DMEM_Write(0, (const uint32_t *)p384_dmem, p384_dmem_size);

    uint32_t mode = P384_SIGN_MODE;
    HAL_OTBN_DMEM_Write(LS_OTBN_ECDSA_P384_RANDOM_SEED_OFFSET, (const uint32_t *)rand_buf, ECDSA_P384_COMPONENT_LENGTH);
    HAL_OTBN_DMEM_Write(LS_OTBN_ECDSA_P384_MODE_OFFSET, &mode, sizeof(uint32_t));
    HAL_OTBN_DMEM_Set(LS_OTBN_ECDSA_P384_D1_OFFSET, 0, ECDSA_P384_COMPONENT_LENGTH);
    HAL_OTBN_DMEM_Write(LS_OTBN_ECDSA_P384_D0_OFFSET, (const uint32_t *)priv_buf, ECDSA_P384_COMPONENT_LENGTH);
    HAL_OTBN_DMEM_Write(LS_OTBN_ECDSA_P384_MSG_OFFSET, (const uint32_t *)digest_buf, ECDSA_P384_COMPONENT_LENGTH);

    HAL_StatusTypeDef st = HAL_OTBN_CMD_Write_IT(HAL_OTBN_CMD_EXECUTE, p384_sign_it_cb, signature);
    if (st != HAL_OK)
        return ls_otbn_status_from_hal(st);
    return LS_OTBN_OK;
}

static void p384_shared_it_cb(void *param)
{
    uint8_t *shared = (uint8_t *)param;
    uint8_t x[ECDSA_P384_COMPONENT_LENGTH];
    uint8_t y[ECDSA_P384_COMPONENT_LENGTH];
    /* Engine flagged an error: the DMEM result is untrustworthy. */
    if (HAL_OTBN_Error_Bit_Get() != 0) {
        HAL_OTBN_ECDSA_P384_SharedSecret_CallBack(LS_OTBN_ENGINE);
        return;
    }
    HAL_OTBN_DMEM_Read(ECC_P384_RX_OFFSET, (uint32_t *)x, ECDSA_P384_COMPONENT_LENGTH);
    HAL_OTBN_DMEM_Read(ECC_P384_RY_OFFSET, (uint32_t *)y, ECDSA_P384_COMPONENT_LENGTH);
    reverse_bytes(x, ECDSA_P384_COMPONENT_LENGTH);
    reverse_bytes(y, ECDSA_P384_COMPONENT_LENGTH);
    memcpy(shared, x, ECDSA_P384_COMPONENT_LENGTH);
    memcpy(shared + ECDSA_P384_COMPONENT_LENGTH, y, ECDSA_P384_COMPONENT_LENGTH);
    HAL_OTBN_ECDSA_P384_SharedSecret_CallBack(LS_OTBN_OK);
}

ls_otbn_status_t HAL_OTBN_ECDSA_P384_SharedSecret_IT(const uint8_t priv_key[ECDSA_P384_PRIVATE_KEY_SIZE],
                                          const uint8_t peer_pub_key[ECDSA_P384_PUBLIC_KEY_SIZE],
                                          uint8_t shared_secret[ECDSA_P384_PUBLIC_KEY_SIZE])
{
    if (!priv_key || !peer_pub_key || !shared_secret) return LS_OTBN_INVALID_PARAM;
    if (!ls_otbn_ecc_scalar_in_range(LS_OTBN_ECC_CURVE_P384, priv_key)) return LS_OTBN_SCALAR_RANGE;
    if (!ls_otbn_ecc_point_on_curve(LS_OTBN_ECC_CURVE_P384,
                                    peer_pub_key, peer_pub_key + ECDSA_P384_COMPONENT_LENGTH)) return LS_OTBN_POINT_NOT_ON_CURVE;

    /* Same inputs as the Polling path: LSW-first words for the
     * pointops firmware (mode + scalar + point). */
    uint8_t scalar_le[ECDSA_P384_COMPONENT_LENGTH];
    uint8_t px_le[ECDSA_P384_COMPONENT_LENGTH];
    uint8_t py_le[ECDSA_P384_COMPONENT_LENGTH];
    memcpy(scalar_le, priv_key, ECDSA_P384_COMPONENT_LENGTH);
    memcpy(px_le, peer_pub_key, ECDSA_P384_COMPONENT_LENGTH);
    memcpy(py_le, peer_pub_key + ECDSA_P384_COMPONENT_LENGTH, ECDSA_P384_COMPONENT_LENGTH);
    reverse_bytes(scalar_le, ECDSA_P384_COMPONENT_LENGTH);
    reverse_bytes(px_le, ECDSA_P384_COMPONENT_LENGTH);
    reverse_bytes(py_le, ECDSA_P384_COMPONENT_LENGTH);

    /* OTBN is a single engine: refuse while a previous job is running */
    if (HAL_OTBN_Is_Busy() || !HAL_OTBN_In_Idle_State()) return LS_OTBN_BUSY;

    HAL_OTBN_Checksum_Clear();
    HAL_OTBN_IMEM_Write(0, (const uint32_t *)g_ecc_p384_imem, g_ecc_p384_imem_size);
    HAL_OTBN_DMEM_Set(0, 0, ECC_P384_DMEM_TOTAL);
    HAL_OTBN_DMEM_Write(0, (const uint32_t *)g_ecc_p384_dmem, ECC_P384_DMEM_SIZE);

    uint32_t mode = ECC_P384_MODE_SCALAR_MULT;
    HAL_OTBN_DMEM_Write(ECC_P384_MODE_OFFSET, &mode, sizeof(uint32_t));
    HAL_OTBN_DMEM_Write(ECC_P384_SCALAR_D_OFFSET, (const uint32_t *)scalar_le, ECDSA_P384_COMPONENT_LENGTH);
    HAL_OTBN_DMEM_Write(ECC_P384_X_OFFSET, (const uint32_t *)px_le, ECDSA_P384_COMPONENT_LENGTH);
    HAL_OTBN_DMEM_Write(ECC_P384_Y_OFFSET, (const uint32_t *)py_le, ECDSA_P384_COMPONENT_LENGTH);

    HAL_StatusTypeDef st = HAL_OTBN_CMD_Write_IT(HAL_OTBN_CMD_EXECUTE, p384_shared_it_cb, shared_secret);
    if (st != HAL_OK)
        return ls_otbn_status_from_hal(st);
    return LS_OTBN_OK;
}
