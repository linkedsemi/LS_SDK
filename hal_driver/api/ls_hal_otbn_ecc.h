#ifndef LS_HAL_OTBN_ECC_H_
#define LS_HAL_OTBN_ECC_H_
#include "ls_hal_otbn.h"
#include <stdint.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================
 * Return-value conventions for this header
 *
 *   - Verify / ValidPoint predicates return bool: true = signature
 *     valid / point on curve (the "positive result"); a failed OTBN
 *     execution also yields false, so on false callers can read
 *     HAL_OTBN_Error_Bit_Get() to tell "verify rejected" (no error
 *     bits) from "execution failed" (error bits set).
 *   - Everything else returns HAL_StatusTypeDef: 0 == HAL_OK on
 *     success, non-zero = execution error.
 *   - The application-level crypto API returns uint32_t: 0 on
 *     success, non-zero on error (mbedTLS style).
 *
 * Byte-order conventions:
 *   - SDK interfaces (below) take u32 word arrays, least-significant
 *     word first (the same representation OTBN DMEM uses); every
 *     field is `component_length / 4` words (8 for P-256/SM2, 12 for
 *     P-384).
 *   - Application-level interfaces take big-endian byte strings
 *     (the representation mbedTLS / wolfSSL and network formats use).
 * ============================================================ */

/* ============================================================
 * Input validation (mirrors wolfSSL / mbedTLS upstream checks)
 *
 * Upstream TLS stacks validate EC inputs before touching the EC engine:
 *   - wolfSSL: wc_ecc_check_r_s_range() / ecc_point_is_pubkey_valid()
 *     (wolfssl/wolfcrypt/src/ecc.c)
 *   - mbedTLS: mbedtls_ecdsa_verify_restartable() r/s range check,
 *     mbedtls_ecp_check_privkey(), mbedtls_ecp_check_pubkey()
 * When those stacks are bypassed (bare HAL use) or their checks are
 * compiled out, out-of-range scalars / off-curve points reach the OTBN
 * firmware directly, which has no defined behaviour for them.  The
 * helpers below provide the same checks inside the HAL so every entry
 * point can validate before programming OTBN.
 * ============================================================ */

/* Curves known to the validation module. */
enum {
    LS_OTBN_ECC_CURVE_P256 = 0,
    LS_OTBN_ECC_CURVE_SM2,
    LS_OTBN_ECC_CURVE_P384,
};

/* 1 <= scalar < n (mirrors mbedtls_ecp_check_privkey).
 * scalar_be: big-endian byte string of the curve's component length. */
bool ls_otbn_ecc_scalar_in_range(int curve, const uint8_t *scalar_be);

/* r,s in [1, n-1] (mirrors wc_ecc_check_r_s_range /
 * mbedtls_ecdsa_verify_restartable).
 * r_be / s_be: big-endian byte strings of the curve's component length. */
bool ls_otbn_ecc_rs_in_range(int curve, const uint8_t *r_be, const uint8_t *s_be);

/* Public key point on curve: x,y < p and y^2 == x^3 - 3x + b (mod p)
 * (mirrors wolfSSL ecc_point_is_pubkey_valid /
 * mbedtls_ecp_check_pubkey).  All supported curves (P-256, SM2, P-384)
 * have a == -3.
 * x_be / y_be: big-endian byte strings of the curve's component length. */
bool ls_otbn_ecc_point_on_curve(int curve, const uint8_t *x_be, const uint8_t *y_be);

/* u32 variants for the SDK-style HALs whose parameters are word arrays
 * stored least-significant-word first (same representation OTBN DMEM
 * uses). */
bool ls_otbn_ecc_scalar_in_range_u32(int curve, const uint32_t *scalar_lsw);
bool ls_otbn_ecc_rs_in_range_u32(int curve, const uint32_t *r_lsw, const uint32_t *s_lsw);
bool ls_otbn_ecc_point_on_curve_u32(int curve, const uint32_t *x_lsw, const uint32_t *y_lsw);

/* ============================================================
 * Shared parameter types: ECC-256 engine
 *
 * "ECC-256" is the 256-bit point-arithmetic engine: it serves both
 * P-256 and SM2 (32-byte components).  The struct types below are
 * shared by the P-256 section and the SM2 section; multi-field
 * operations take a struct (five distinct arrays), two-field
 * operations (valid point) take the arrays directly.
 * ============================================================ */

/* Curve selector for the shared 256-bit engine. */
enum HAL_OTBN_ECC256_CURVES
{
    HAL_OTBN_ECC256_CURVE_P256 = 0,
    HAL_OTBN_ECC256_CURVE_SM2 = 1,
};

/* All fields: 8 u32 words, least-significant word first. */
struct HAL_OTBN_ECC256_Verify_Param
{
    uint32_t *msg;  /* message digest */
    uint32_t *r;    /* signature R */
    uint32_t *s;    /* signature S */
    uint32_t *x;    /* public key x-coordinate */
    uint32_t *y;    /* public key y-coordinate */
};

/* All fields: 8 u32 words, least-significant word first. */
struct HAL_OTBN_ECC256_ScalarMult_Param
{
    uint32_t *scalar;
    uint32_t *point_x;
    uint32_t *point_y;
    uint32_t *result_x;
    uint32_t *result_y;
};

/* ============================================================
 * P-256 (secp256r1)
 * ============================================================ */

/* ---------------- SDK: ECC-256 engine ----------------
 * Verify firmware is P-256 specific.  ScalarMult takes a curve
 * selector, so it also serves SM2 (see the SM2 section note). */

bool HAL_OTBN_ECC256_ECDSA_Verify_Polling(struct HAL_OTBN_ECC256_Verify_Param *verify_param);
void HAL_OTBN_ECC256_ECDSA_Verify_IT(struct HAL_OTBN_ECC256_Verify_Param *verify_param);
void HAL_OTBN_ECC256_ECDSA_Verify_CallBack(bool result);

void HAL_OTBN_ECC256_ScalarMult_Cb(void);
void HAL_OTBN_ECC256_ScalarMult_IT(enum HAL_OTBN_ECC256_CURVES Curve, struct HAL_OTBN_ECC256_ScalarMult_Param *param);
HAL_StatusTypeDef HAL_OTBN_ECC256_ScalarMult_Polling(enum HAL_OTBN_ECC256_CURVES Curve, struct HAL_OTBN_ECC256_ScalarMult_Param *param);

/* ---------------- Application level ---------------- */

#define ECDSA_P256_PRIVATE_KEY_SIZE  32U
#define ECDSA_P256_PUBLIC_KEY_SIZE   64U
#define ECDSA_P256_SIGNATURE_SIZE    64U
#define ECDSA_P256_COMPONENT_LENGTH  32U

/**
 * @brief Derive P-256 public key from private key.
 * @param priv_key  32-byte private key (big-endian)
 * @param pub_key   64-byte output: X (32 bytes) || Y (32 bytes)
 * @return 0 on success, non-zero on error
 */
uint32_t HAL_OTBN_ECDSA_P256_DerivePubkey(const uint8_t priv_key[ECDSA_P256_PRIVATE_KEY_SIZE],
                                       uint8_t pub_key[ECDSA_P256_PUBLIC_KEY_SIZE]);
uint32_t HAL_OTBN_ECDSA_P256_DerivePubkey_IT(const uint8_t priv_key[ECDSA_P256_PRIVATE_KEY_SIZE],
                                          uint8_t pub_key[ECDSA_P256_PUBLIC_KEY_SIZE]);
void HAL_OTBN_ECDSA_P256_DerivePubkey_CallBack(uint32_t status);

/**
 * @brief ECDSA P-256 signature.
 * @param digest    32-byte message hash
 * @param rand_k    32-byte random nonce (k)
 * @param priv_key  32-byte private key
 * @param signature 64-byte output: r (32 bytes) || s (32 bytes)
 * @return 0 on success, non-zero on error
 */
uint32_t HAL_OTBN_ECDSA_P256_Sign(const uint8_t digest[ECDSA_P256_COMPONENT_LENGTH],
                              const uint8_t rand_k[ECDSA_P256_COMPONENT_LENGTH],
                              const uint8_t priv_key[ECDSA_P256_PRIVATE_KEY_SIZE],
                              uint8_t signature[ECDSA_P256_SIGNATURE_SIZE]);
uint32_t HAL_OTBN_ECDSA_P256_Sign_IT(const uint8_t digest[ECDSA_P256_COMPONENT_LENGTH],
                                 const uint8_t rand_k[ECDSA_P256_COMPONENT_LENGTH],
                                 const uint8_t priv_key[ECDSA_P256_PRIVATE_KEY_SIZE],
                                 uint8_t signature[ECDSA_P256_SIGNATURE_SIZE]);
void HAL_OTBN_ECDSA_P256_Sign_CallBack(uint32_t status);

/**
 * @brief Compute P-256 ECDH shared secret.
 * @param priv_key      32-byte private key
 * @param peer_pub_key  64-byte peer public key: X (32 bytes) || Y (32 bytes)
 * @param shared_secret 64-byte output: X (32 bytes) || Y (32 bytes)
 * @return 0 on success, non-zero on error
 */
uint32_t HAL_OTBN_ECDSA_P256_SharedSecret(const uint8_t priv_key[ECDSA_P256_PRIVATE_KEY_SIZE],
                                       const uint8_t peer_pub_key[ECDSA_P256_PUBLIC_KEY_SIZE],
                                       uint8_t shared_secret[ECDSA_P256_PUBLIC_KEY_SIZE]);
uint32_t HAL_OTBN_ECDSA_P256_SharedSecret_IT(const uint8_t priv_key[ECDSA_P256_PRIVATE_KEY_SIZE],
                                          const uint8_t peer_pub_key[ECDSA_P256_PUBLIC_KEY_SIZE],
                                          uint8_t shared_secret[ECDSA_P256_PUBLIC_KEY_SIZE]);
void HAL_OTBN_ECDSA_P256_SharedSecret_CallBack(uint32_t status);

/* ============================================================
 * SM2 (sm2p256v1)
 * ============================================================ */

/* ---------------- SDK: SM2 ----------------
 * Verify and valid-point run the SM2 dedicated firmware (sm2_text),
 * a single image with verify / valid-point / scalar-mult modes.
 * Scalar multiplication, however, runs on the shared ECC-256 engine
 * with the SM2 curve parameters -- SM2 point arithmetic is the same
 * 256-bit engine that serves P-256, so SM2 has no dedicated
 * scalar-mult firmware path.  All SM2 interfaces below are the
 * SM2-curve counterparts of the ECC-256 ones above.
 *
 * Parameter structs are layout-identical to the ECC-256 ones but kept
 * as distinct types (SM2 is a distinct curve). */

/* All fields: 8 u32 words, least-significant word first. */
struct HAL_OTBN_SM2_Verify_Param
{
    uint32_t *msg;
    uint32_t *r;
    uint32_t *s;
    uint32_t *x;
    uint32_t *y;
};

/* All fields: 8 u32 words, least-significant word first. */
struct HAL_OTBN_SM2_ScalarMult_Param
{
    uint32_t *scalar;
    uint32_t *point_x;
    uint32_t *point_y;
    uint32_t *result_x;
    uint32_t *result_y;
};

void HAL_OTBN_SM2_Verify_CallBack(bool result);
void HAL_OTBN_SM2_Verify_IT(struct HAL_OTBN_SM2_Verify_Param *param);
bool HAL_OTBN_SM2_Verify_Polling(struct HAL_OTBN_SM2_Verify_Param *param);

void HAL_OTBN_SM2_ValidPoint_CallBack(bool result);
void HAL_OTBN_SM2_ValidPoint_IT(uint32_t *x, uint32_t *y);
bool HAL_OTBN_SM2_ValidPoint_Polling(uint32_t *x, uint32_t *y);

void HAL_OTBN_SM2_ScalarMult_CallBack();
void HAL_OTBN_SM2_ScalarMult_IT(struct HAL_OTBN_SM2_ScalarMult_Param *param);
HAL_StatusTypeDef HAL_OTBN_SM2_ScalarMult_Engine_Polling(struct HAL_OTBN_SM2_ScalarMult_Param *param);

/* ---------------- Application level ---------------- */

#define SM2_PRIVATE_KEY_SIZE   32U
#define SM2_PUBLIC_KEY_SIZE    64U   /* X || Y, each 32 bytes */
#define SM2_SIGNATURE_SIZE     64U   /* r || s, each 32 bytes */
#define SM2_COMPONENT_LENGTH   32U   /* digest / scalar size */

/**
 * @brief SM2 public key derivation.
 *        Computes pub_key = priv_key * G  (SM2 generator point).
 * @param priv_key  32-byte private key (big-endian)
 * @param pub_key   64-byte output: X (32 bytes) || Y (32 bytes)
 * @return 0 on success, non-zero on error
 */
uint32_t HAL_OTBN_SM2_DerivePubkey(const uint8_t priv_key[SM2_PRIVATE_KEY_SIZE],
                                uint8_t pub_key[SM2_PUBLIC_KEY_SIZE]);
uint32_t HAL_OTBN_SM2_DerivePubkey_IT(const uint8_t priv_key[SM2_PRIVATE_KEY_SIZE],
                                   uint8_t pub_key[SM2_PUBLIC_KEY_SIZE]);
void HAL_OTBN_SM2_DerivePubkey_CallBack(uint32_t status);

/**
 * @brief SM2 signature.
 * @param sm2_e     32-byte SM2 message digest (Z || M hash)
 * @param rand_k    32-byte random nonce (k)
 * @param priv_key  32-byte private key
 * @param signature 64-byte output: r (32 bytes) || s (32 bytes)
 * @return 0 on success, non-zero on error
 */
uint32_t HAL_OTBN_SM2_Sign(const uint8_t sm2_e[SM2_COMPONENT_LENGTH],
                       const uint8_t rand_k[SM2_COMPONENT_LENGTH],
                       const uint8_t priv_key[SM2_PRIVATE_KEY_SIZE],
                       uint8_t signature[SM2_SIGNATURE_SIZE]);
uint32_t HAL_OTBN_SM2_Sign_IT(const uint8_t sm2_e[SM2_COMPONENT_LENGTH],
                          const uint8_t rand_k[SM2_COMPONENT_LENGTH],
                          const uint8_t priv_key[SM2_PRIVATE_KEY_SIZE],
                          uint8_t signature[SM2_SIGNATURE_SIZE]);
void HAL_OTBN_SM2_Sign_CallBack(uint32_t status);

/**
 * @brief Compute SM2 ECDH shared secret.
 * @param priv_key      32-byte private key
 * @param peer_pub_key  64-byte peer public key: X (32 bytes) || Y (32 bytes)
 * @param shared_secret 64-byte output: X (32 bytes) || Y (32 bytes)
 * @return 0 on success, non-zero on error
 */
uint32_t HAL_OTBN_SM2_SharedSecret(const uint8_t priv_key[SM2_PRIVATE_KEY_SIZE],
                                const uint8_t peer_pub_key[SM2_PUBLIC_KEY_SIZE],
                                uint8_t shared_secret[SM2_PUBLIC_KEY_SIZE]);
uint32_t HAL_OTBN_SM2_SharedSecret_IT(const uint8_t priv_key[SM2_PRIVATE_KEY_SIZE],
                                   const uint8_t peer_pub_key[SM2_PUBLIC_KEY_SIZE],
                                   uint8_t shared_secret[SM2_PUBLIC_KEY_SIZE]);
void HAL_OTBN_SM2_SharedSecret_CallBack(uint32_t status);

/* ============================================================
 * P-384 (secp384r1)
 * ============================================================ */

/* ---------------- SDK: ECC-384 engine ---------------- */

enum HAL_OTBN_ECC384_CURVES
{
    HAL_OTBN_ECC384_CURVE_P384 = 0,
};

/* All fields: 12 u32 words, least-significant word first. */
struct HAL_OTBN_ECC384_Verify_Param
{
    uint32_t *msg;  /* message digest */
    uint32_t *r;    /* signature R */
    uint32_t *s;    /* signature S */
    uint32_t *x;    /* public key x-coordinate */
    uint32_t *y;    /* public key y-coordinate */
};

void HAL_OTBN_ECC384_ECDSA_Verify_CallBack(bool result);
bool HAL_OTBN_ECC384_ECDSA_Verify_Polling(enum HAL_OTBN_ECC384_CURVES curve, struct HAL_OTBN_ECC384_Verify_Param *verify_param);
void HAL_OTBN_ECC384_ECDSA_Verify_IT(enum HAL_OTBN_ECC384_CURVES curve, struct HAL_OTBN_ECC384_Verify_Param *verify_param);

/* ---------------- Application level ---------------- */

#define ECDSA_P384_PRIVATE_KEY_SIZE  48U
#define ECDSA_P384_PUBLIC_KEY_SIZE   96U   /* X || Y, each 48 bytes */
#define ECDSA_P384_SIGNATURE_SIZE    96U   /* r || s, each 48 bytes */
#define ECDSA_P384_COMPONENT_LENGTH  48U   /* digest / scalar size */

/**
 * @brief Derive P-384 public key from private key.
 *        Computes pub_key = priv_key * G  (generator point).
 * @param priv_key  48-byte private key (big-endian)
 * @param pub_key   96-byte output: X (48 bytes) || Y (48 bytes)
 * @return 0 on success, non-zero on error
 */
uint32_t HAL_OTBN_ECDSA_P384_DerivePubkey(const uint8_t priv_key[ECDSA_P384_PRIVATE_KEY_SIZE],
                                       uint8_t pub_key[ECDSA_P384_PUBLIC_KEY_SIZE]);
uint32_t HAL_OTBN_ECDSA_P384_DerivePubkey_IT(const uint8_t priv_key[ECDSA_P384_PRIVATE_KEY_SIZE],
                                          uint8_t pub_key[ECDSA_P384_PUBLIC_KEY_SIZE]);
void HAL_OTBN_ECDSA_P384_DerivePubkey_CallBack(uint32_t status);

/**
 * @brief ECDSA P-384 signature.
 * @param digest    48-byte message hash
 * @param rand_k    48-byte random nonce (k)
 * @param priv_key  48-byte private key
 * @param signature 96-byte output: r (48 bytes) || s (48 bytes)
 * @return 0 on success, non-zero on error
 */
uint32_t HAL_OTBN_ECDSA_P384_Sign(const uint8_t digest[ECDSA_P384_COMPONENT_LENGTH],
                              const uint8_t rand_k[ECDSA_P384_COMPONENT_LENGTH],
                              const uint8_t priv_key[ECDSA_P384_PRIVATE_KEY_SIZE],
                              uint8_t signature[ECDSA_P384_SIGNATURE_SIZE]);
uint32_t HAL_OTBN_ECDSA_P384_Sign_IT(const uint8_t digest[ECDSA_P384_COMPONENT_LENGTH],
                                 const uint8_t rand_k[ECDSA_P384_COMPONENT_LENGTH],
                                 const uint8_t priv_key[ECDSA_P384_PRIVATE_KEY_SIZE],
                                 uint8_t signature[ECDSA_P384_SIGNATURE_SIZE]);
void HAL_OTBN_ECDSA_P384_Sign_CallBack(uint32_t status);

/**
 * @brief Compute P-384 ECDH shared secret.
 *        Computes shared_secret = priv_key * peer_pub_key
 * @param priv_key      48-byte private key
 * @param peer_pub_key  96-byte peer public key: X (48 bytes) || Y (48 bytes)
 * @param shared_secret 96-byte output: X (48 bytes) || Y (48 bytes)
 * @return 0 on success, non-zero on error
 */
uint32_t HAL_OTBN_ECDSA_P384_SharedSecret(const uint8_t priv_key[ECDSA_P384_PRIVATE_KEY_SIZE],
                                       const uint8_t peer_pub_key[ECDSA_P384_PUBLIC_KEY_SIZE],
                                       uint8_t shared_secret[ECDSA_P384_PUBLIC_KEY_SIZE]);
uint32_t HAL_OTBN_ECDSA_P384_SharedSecret_IT(const uint8_t priv_key[ECDSA_P384_PRIVATE_KEY_SIZE],
                                          const uint8_t peer_pub_key[ECDSA_P384_PUBLIC_KEY_SIZE],
                                          uint8_t shared_secret[ECDSA_P384_PUBLIC_KEY_SIZE]);
void HAL_OTBN_ECDSA_P384_SharedSecret_CallBack(uint32_t status);

/* ============================================================
 * Application-level IT flavour notes
 *
 * Every application operation above comes in two flavours:
 *   - Polling:  blocks until OTBN finishes; the result is written
 *     into the caller's output array before returning.
 *   - IT:       submits the operation and returns 0 immediately;
 *     the OTBN completion interrupt writes the result into the
 *     caller's output array and then invokes the matching weak
 *     CallBack(status) with status == 0 on success.  The output
 *     array must stay valid until the callback fires (inputs are
 *     consumed at submit time).  OTBN is a single engine, so IT
 *     operations must not overlap each other.
 *
 * Signature verification has no application-level wrapper: callers
 * use the SDK Verify interfaces directly (HAL_OTBN_ECC256/ECC384/
 * SM2_Verify_Polling or _IT), whose parameters are u32 arrays,
 * least-significant word first.
 * ============================================================ */

#ifdef __cplusplus
}
#endif
#endif
