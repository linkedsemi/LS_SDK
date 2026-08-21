#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "ls_hal_otbn.h"
#include "ls_hal_otbn_ecc.h"
#include "ls_hal_otbn_p384_pointops.h"
#include "ls_hal_otbn_sm2_pointops.h"
#include "ls_otbn_ecc.h"
#include "ls_msp_otbn.h"
#include "platform.h"
#include "log.h"
#include "core_rv32.h"

#define P384_BYTES ECDSA_P384_COMPONENT_LENGTH

/* Fixed 48-byte random seed for deterministic test (replace with TRNG in production) */
static const uint8_t random_seed_sign[P384_BYTES] = {
    0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
    0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70,
    0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
    0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f, 0x80,
    0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88,
    0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90,
};

static const uint8_t message_hash[P384_BYTES] = {
    0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00, 0x11,
    0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99,
    0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00, 0x11,
    0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99,
    0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00, 0x11,
    0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99,
};

static uint8_t priv_key_a[P384_BYTES];

static uint8_t priv_key_b[P384_BYTES];

/* ===== SM2 test data ===== */
#define SM2_BYTES  32
static const uint8_t sm2_random_seed[SM2_BYTES] = {
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
    0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10,
    0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
    0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20,
};
static const uint8_t sm2_sign_rand[SM2_BYTES] = {
    0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
    0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70,
    0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
    0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f, 0x80,
};
static const uint8_t sm2_msg_hash[SM2_BYTES] = {
    0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00, 0x11,
    0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99,
    0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00, 0x11,
    0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99,
};
static uint8_t sm2_priv_key[SM2_BYTES];

/* ===== P-256 test data ===== */
#define P256_BYTES  32
static const uint8_t p256_random_seed[P256_BYTES] = {
    0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8,
    0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0,
    0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8,
    0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf, 0xc0,
};
static const uint8_t p256_sign_rand[P256_BYTES] = {
    0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8,
    0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0,
    0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8,
    0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf, 0xe0,
};
static const uint8_t p256_msg_hash[P256_BYTES] = {
    0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88,
    0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00,
    0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88,
    0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00,
};
static uint8_t p256_priv_key[P256_BYTES];

static volatile bool s_it_done = false;
static bool s_it_result = false;

/* Strict serialization: each IT test must wait for its own completion
 * callback (and the result it produced) before the next test starts.
 * A short spin budget previously let a test give up while its job was
 * still running; the late callback then polluted the following tests'
 * state (stale s_it_done, s_engine_busy still set) and every later
 * submit was refused.  OTBN firmware finishes every operation in
 * bounded time, so the MTIME-based ceiling below only guards against a
 * hung engine.  Returns true if the callback fired. */
static bool it_wait(void)
{
    uint64_t start = CORET->MTIME;
    while (!s_it_done)
    {
        /* 30 s ceiling @ 600 MHz: OTBN firmware finishes every operation
         * in bounded time, so this only guards against a hung engine. */
        if ((CORET->MTIME - start) >= 30ULL * 600000000ULL)
            return false;   /* hung engine: give up, do not block forever */
    }
    return true;
}

/* Global test results (readable from GDB, not optimized out) */
volatile uint32_t g_test_result[120] = {0};
volatile uint8_t g_sm2_shared_a[SM2_BYTES * 2];
volatile uint8_t g_sm2_shared_b[SM2_BYTES * 2];
volatile uint8_t g_p256_shared_a[P256_BYTES * 2];
volatile uint8_t g_p256_shared_b[P256_BYTES * 2];
volatile uint8_t g_p384_shared_a[P384_BYTES * 2];
volatile uint8_t g_p384_shared_b[P384_BYTES * 2];
volatile uint8_t g_p384_derived[P384_BYTES * 2];
volatile uint8_t g_p384_sig[P384_BYTES * 2];
volatile uint8_t g_sm2_derived[SM2_BYTES * 2];
volatile uint8_t g_sm2_sig[SM2_BYTES * 2];
volatile uint8_t g_p256_derived[P256_BYTES * 2];
volatile uint8_t g_p256_sig[P256_BYTES * 2];

/* Output buffers for the app-level crypto IT tests (async writes) */
volatile uint8_t g_p384_derived_it[P384_BYTES * 2];
volatile uint8_t g_p384_sig_it[P384_BYTES * 2];
volatile uint8_t g_p384_shared_it[P384_BYTES * 2];
volatile uint8_t g_sm2_derived_it[SM2_BYTES * 2];
volatile uint8_t g_sm2_sig_it[SM2_BYTES * 2];
volatile uint8_t g_sm2_shared_it[SM2_BYTES * 2];
volatile uint8_t g_p256_derived_it[P256_BYTES * 2];
volatile uint8_t g_p256_sig_it[P256_BYTES * 2];
volatile uint8_t g_p256_shared_it[P256_BYTES * 2];
volatile uint32_t s_it_status = 0xFFFFFFFF;

/* Record test result: g_test_result[idx*2]=ret, g_test_result[idx*2+1]=pass */
#define REC(idx, r, p) do { g_test_result[(idx) * 2] = (uint32_t)(r); \
                            g_test_result[(idx) * 2 + 1] = (uint32_t)(p); } while (0)

static bool buffer_is_zero(const uint8_t *buf, uint32_t len)
{
    uint8_t acc = 0;
    for (uint32_t i = 0; i < len; i++) {
        acc |= buf[i];
    }
    return acc == 0;
}

static void print_result(const char *name, HAL_StatusTypeDef status, bool pass)
{
    if (pass) {
        LOG_I("%s: PASS", name);
    } else {
        LOG_I("%s: FAIL (status=%d)", name, status);
    }
}

static bool bufs_eq(const uint8_t *a, const uint8_t *b, uint32_t len)
{
    return memcmp(a, b, len) == 0;
}

/* Big-endian byte string -> u32 words, least-significant word first
 * (the SDK verify parameter format). */
static void be_to_words(const uint8_t *be, uint32_t *out, uint32_t nbytes)
{
    uint8_t le[48];
    memcpy(le, be, nbytes);
    for (uint32_t i = 0; i < nbytes / 2; i++) {
        uint8_t t = le[i];
        le[i] = le[nbytes - 1 - i];
        le[nbytes - 1 - i] = t;
    }
    memcpy(out, le, nbytes);
}

/* Signature verification via the SDK Verify interfaces (big-endian
 * byte inputs, app-style return: 0 = valid, 1 = invalid/error). */
static uint32_t p256_verify_be(const uint8_t *digest, const uint8_t *sig, const uint8_t *pub)
{
    uint32_t msg[8], r[8], s[8], x[8], y[8];
    struct HAL_OTBN_ECC256_Verify_Param vp = { msg, r, s, x, y };
    be_to_words(digest, msg, P256_BYTES);
    be_to_words(sig, r, P256_BYTES);
    be_to_words(sig + P256_BYTES, s, P256_BYTES);
    be_to_words(pub, x, P256_BYTES);
    be_to_words(pub + P256_BYTES, y, P256_BYTES);
    return HAL_OTBN_ECC256_ECDSA_Verify_Polling(&vp) ? 0 : 1;
}

static uint32_t p384_verify_be(const uint8_t *digest, const uint8_t *sig, const uint8_t *pub)
{
    uint32_t msg[12], r[12], s[12], x[12], y[12];
    struct HAL_OTBN_ECC384_Verify_Param vp = { msg, r, s, x, y };
    be_to_words(digest, msg, P384_BYTES);
    be_to_words(sig, r, P384_BYTES);
    be_to_words(sig + P384_BYTES, s, P384_BYTES);
    be_to_words(pub, x, P384_BYTES);
    be_to_words(pub + P384_BYTES, y, P384_BYTES);
    return HAL_OTBN_ECC384_ECDSA_Verify_Polling(HAL_OTBN_ECC384_CURVE_P384, &vp) ? 0 : 1;
}

static uint32_t sm2_verify_be(const uint8_t *e, const uint8_t *sig, const uint8_t *pub)
{
    uint32_t msg[8], r[8], s[8], x[8], y[8];
    struct HAL_OTBN_SM2_Verify_Param vp = { msg, r, s, x, y };
    be_to_words(e, msg, SM2_BYTES);
    be_to_words(sig, r, SM2_BYTES);
    be_to_words(sig + SM2_BYTES, s, SM2_BYTES);
    be_to_words(pub, x, SM2_BYTES);
    be_to_words(pub + SM2_BYTES, y, SM2_BYTES);
    return HAL_OTBN_SM2_Verify_Polling(&vp) ? 0 : 1;
}

int main(void)
{
    bool pass;

    sys_init_none();
    HAL_OTBN_Init();

    LOG_I("OTBN P-384 ECC v2 test start");
    /* ================================================================
     *  New HAL interface tests
     * ================================================================ */

    /* --- P384 derive_pubkey --- */
    LOG_I("--- P384 HAL interface tests ---");
    /* Use a fixed private key for all P384 tests */
    memcpy(priv_key_a, random_seed_sign, P384_BYTES);
    uint8_t derived_pub[P384_BYTES * 2];
    uint32_t ret;
    ret = HAL_OTBN_ECDSA_P384_DerivePubkey(priv_key_a, derived_pub);
    pass = (ret == 0) && !buffer_is_zero(derived_pub, P384_BYTES);
    memcpy((void *)g_p384_derived, derived_pub, P384_BYTES * 2);
    REC(0, ret, pass);
    print_result("P384 derive_pubkey", ret, pass);

    /* --- P384 sign --- */
    uint8_t hal_sig[ECDSA_P384_SIGNATURE_SIZE];
    ret = HAL_OTBN_ECDSA_P384_Sign(message_hash, random_seed_sign, priv_key_a, hal_sig);
    pass = (ret == 0) &&
           !buffer_is_zero(hal_sig, ECDSA_P384_COMPONENT_LENGTH) &&
           !buffer_is_zero(hal_sig + ECDSA_P384_COMPONENT_LENGTH, ECDSA_P384_COMPONENT_LENGTH);
    memcpy((void *)g_p384_sig, hal_sig, P384_BYTES * 2);
    REC(1, ret, pass);
    print_result("P384 sign", ret, pass);

    /* --- P384 verify --- */
    uint8_t p384_verify_sig[ECDSA_P384_SIGNATURE_SIZE];
    ret = HAL_OTBN_ECDSA_P384_Sign(message_hash, random_seed_sign, priv_key_a, p384_verify_sig);
    if (ret == 0) {
        ret = p384_verify_be(message_hash, p384_verify_sig, derived_pub);
        REC(2, ret, ret == 0);
        print_result("P384 verify (valid)", ret, ret == 0);
        p384_verify_sig[0] ^= 0xFF;
        ret = p384_verify_be(message_hash, p384_verify_sig, derived_pub);
        REC(3, ret, ret == 1);
        print_result("P384 verify (bad sig)", ret, ret == 1);
    } else {
        REC(2, ret, false);
        REC(3, ret, false);
        print_result("P384 verify (sign fail)", ret, false);
    }

    /* --- P384 shared_secret ECDH --- */
    memcpy(priv_key_b, random_seed_sign, P384_BYTES);
    uint8_t p384_shared_a[P384_BYTES * 2], p384_shared_b[P384_BYTES * 2];
    uint8_t p384_pub_b[P384_BYTES * 2];
    ret = HAL_OTBN_ECDSA_P384_DerivePubkey(priv_key_b, p384_pub_b);
    if (ret == 0) {
        ret = HAL_OTBN_ECDSA_P384_SharedSecret(priv_key_a, p384_pub_b, p384_shared_a);
        if (ret == 0)
            ret = HAL_OTBN_ECDSA_P384_SharedSecret(priv_key_b, derived_pub, p384_shared_b);
    }
    bool p384_ecdh_match = (ret == 0) && !buffer_is_zero(p384_shared_a, P384_BYTES) && bufs_eq(p384_shared_a, p384_shared_b, P384_BYTES * 2);
    memcpy((void *)g_p384_shared_a, p384_shared_a, P384_BYTES * 2);
    memcpy((void *)g_p384_shared_b, p384_shared_b, P384_BYTES * 2);
    REC(4, ret, p384_ecdh_match);
    print_result("P384 ECDH", ret, p384_ecdh_match);

    /* ================================================================
     *  SM2 HAL interface tests
     * ================================================================ */
    LOG_I("--- SM2 HAL interface tests ---");

    /* Step 1: Generate keypair using HAL_OTBN_SM2_DerivePubkey */
    memcpy(sm2_priv_key, sm2_random_seed, SM2_BYTES);
    uint8_t sm2_derived_pub[SM2_PUBLIC_KEY_SIZE];
    ret = HAL_OTBN_SM2_DerivePubkey(sm2_priv_key, sm2_derived_pub);
    pass = (ret == 0) && !buffer_is_zero(sm2_derived_pub, SM2_BYTES);
    memcpy((void *)g_sm2_derived, sm2_derived_pub, SM2_BYTES * 2);
    REC(5, ret, pass);
    print_result("SM2 derive_pubkey (1st call)", ret, pass);

    /* Step 2: Second derive_pubkey call - must be deterministic */
    uint8_t sm2_derived_pub2[SM2_PUBLIC_KEY_SIZE];
    ret = HAL_OTBN_SM2_DerivePubkey(sm2_priv_key, sm2_derived_pub2);
    bool sm2_key_match = bufs_eq(sm2_derived_pub, sm2_derived_pub2, SM2_PUBLIC_KEY_SIZE);
    pass = (ret == 0) && sm2_key_match;
    REC(6, ret, pass);
    print_result("SM2 derive_pubkey (2nd call, deterministic)", ret, pass);

    /* Step 3: Sign (1st call) */
    uint8_t sm2_hal_sig1[SM2_SIGNATURE_SIZE];
    ret = HAL_OTBN_SM2_Sign(sm2_msg_hash, sm2_sign_rand, sm2_priv_key, sm2_hal_sig1);
    pass = (ret == 0) &&
           !buffer_is_zero(sm2_hal_sig1, SM2_COMPONENT_LENGTH) &&
           !buffer_is_zero(sm2_hal_sig1 + SM2_COMPONENT_LENGTH, SM2_COMPONENT_LENGTH);
    memcpy((void *)g_sm2_sig, sm2_hal_sig1, SM2_BYTES * 2);
    REC(7, ret, pass);
    print_result("SM2 sign (1st call)", ret, pass);

    /* Step 4: Second sign call - deterministic */
    uint8_t sm2_hal_sig2[SM2_SIGNATURE_SIZE];
    ret = HAL_OTBN_SM2_Sign(sm2_msg_hash, sm2_sign_rand, sm2_priv_key, sm2_hal_sig2);
    bool sm2_sig_match = bufs_eq(sm2_hal_sig1, sm2_hal_sig2, SM2_SIGNATURE_SIZE);
    pass = (ret == 0) && sm2_sig_match;
    REC(8, ret, pass);
    print_result("SM2 sign (2nd call, deterministic)", ret, pass);

    /* --- SM2 verify --- */
    uint8_t sm2_verify_sig[SM2_SIGNATURE_SIZE];
    ret = HAL_OTBN_SM2_Sign(sm2_msg_hash, sm2_sign_rand, sm2_priv_key, sm2_verify_sig);
    if (ret == 0) {
        ret = sm2_verify_be(sm2_msg_hash, sm2_verify_sig, sm2_derived_pub);
        REC(9, ret, ret == 0);
        print_result("SM2 verify (valid)", ret, ret == 0);
        sm2_verify_sig[0] ^= 0xFF;
        ret = sm2_verify_be(sm2_msg_hash, sm2_verify_sig, sm2_derived_pub);
        REC(10, ret, ret == 1);
        print_result("SM2 verify (bad sig)", ret, ret == 1);
    } else {
        REC(9, ret, false);
        REC(10, ret, false);
        print_result("SM2 verify (sign fail)", ret, false);
    }

    /* --- SM2 shared_secret ECDH --- */
    uint8_t sm2_shared_a[SM2_BYTES * 2], sm2_shared_b[SM2_BYTES * 2];
    uint8_t sm2_priv_b[SM2_BYTES], sm2_pub_b[SM2_BYTES * 2];
    static const uint8_t sm2_priv_b_seed[SM2_BYTES] = {
        0xab, 0xcd, 0xef, 0x01, 0x23, 0x45, 0x67, 0x89,
        0xab, 0xcd, 0xef, 0x01, 0x23, 0x45, 0x67, 0x89,
        0xab, 0xcd, 0xef, 0x01, 0x23, 0x45, 0x67, 0x89,
        0xab, 0xcd, 0xef, 0x01, 0x23, 0x45, 0x67, 0x89,
    };
    memcpy(sm2_priv_b, sm2_priv_b_seed, SM2_BYTES);
    ret = HAL_OTBN_SM2_DerivePubkey(sm2_priv_b, sm2_pub_b);
    if (ret == 0) {
        ret = HAL_OTBN_SM2_SharedSecret(sm2_priv_key, sm2_pub_b, sm2_shared_a);
        if (ret == 0)
            ret = HAL_OTBN_SM2_SharedSecret(sm2_priv_b, sm2_derived_pub, sm2_shared_b);
    }
    bool sm2_ecdh_match = (ret == 0) && !buffer_is_zero(sm2_shared_a, SM2_BYTES) && bufs_eq(sm2_shared_a, sm2_shared_b, SM2_BYTES * 2);
    memcpy((void *)g_sm2_shared_a, sm2_shared_a, SM2_BYTES * 2);
    memcpy((void *)g_sm2_shared_b, sm2_shared_b, SM2_BYTES * 2);
    REC(11, ret, sm2_ecdh_match);
    print_result("SM2 ECDH", ret, sm2_ecdh_match);

    /* ================================================================
     *  P-256 HAL interface tests
     * ================================================================ */
    LOG_I("--- P-256 HAL interface tests ---");

    /* Step 1: Generate keypair using HAL_OTBN_ECDSA_P256_DerivePubkey */
    memcpy(p256_priv_key, p256_random_seed, P256_BYTES);
    uint8_t p256_derived_pub[P256_BYTES * 2];
    ret = HAL_OTBN_ECDSA_P256_DerivePubkey(p256_priv_key, p256_derived_pub);
    pass = (ret == 0) && !buffer_is_zero(p256_derived_pub, P256_BYTES);
    memcpy((void *)g_p256_derived, p256_derived_pub, P256_BYTES * 2);
    REC(12, ret, pass);
    print_result("P256 derive_pubkey (1st call)", ret, pass);

    /* Step 2: Second derive_pubkey call - must be deterministic */
    uint8_t p256_derived_pub2[P256_BYTES * 2];
    ret = HAL_OTBN_ECDSA_P256_DerivePubkey(p256_priv_key, p256_derived_pub2);
    bool p256_key_match = bufs_eq(p256_derived_pub, p256_derived_pub2, P256_BYTES * 2);
    pass = (ret == 0) && p256_key_match;
    REC(13, ret, pass);
    print_result("P256 derive_pubkey (2nd call, deterministic)", ret, pass);

    /* Step 3: Sign (1st call) */
    uint8_t p256_hal_sig1[P256_BYTES * 2];
    ret = HAL_OTBN_ECDSA_P256_Sign(p256_msg_hash, p256_sign_rand, p256_priv_key, p256_hal_sig1);
    pass = (ret == 0) &&
           !buffer_is_zero(p256_hal_sig1, P256_BYTES) &&
           !buffer_is_zero(p256_hal_sig1 + P256_BYTES, P256_BYTES);
    memcpy((void *)g_p256_sig, p256_hal_sig1, P256_BYTES * 2);
    REC(14, ret, pass);
    print_result("P256 sign (1st call)", ret, pass);

    /* Step 4: Second sign call - deterministic */
    uint8_t p256_hal_sig2[P256_BYTES * 2];
    ret = HAL_OTBN_ECDSA_P256_Sign(p256_msg_hash, p256_sign_rand, p256_priv_key, p256_hal_sig2);
    bool p256_sig_match = bufs_eq(p256_hal_sig1, p256_hal_sig2, P256_BYTES * 2);
    pass = (ret == 0) && p256_sig_match;
    REC(15, ret, pass);
    print_result("P256 sign (2nd call, deterministic)", ret, pass);

    /* --- P256 verify --- */
    uint8_t p256_verify_sig[P256_BYTES * 2];
    ret = HAL_OTBN_ECDSA_P256_Sign(p256_msg_hash, p256_sign_rand, p256_priv_key, p256_verify_sig);
    if (ret == 0) {
        ret = p256_verify_be(p256_msg_hash, p256_verify_sig, p256_derived_pub);
        REC(16, ret, ret == 0);
        print_result("P256 verify (valid)", ret, ret == 0);
        p256_verify_sig[0] ^= 0xFF;
        ret = p256_verify_be(p256_msg_hash, p256_verify_sig, p256_derived_pub);
        REC(17, ret, ret == 1);
        print_result("P256 verify (bad sig)", ret, ret == 1);
    } else {
        REC(16, ret, false);
        REC(17, ret, false);
        print_result("P256 verify (sign fail)", ret, false);
    }

    /* --- P256 shared_secret ECDH --- */
    uint8_t p256_shared_a[P256_BYTES * 2], p256_shared_b[P256_BYTES * 2];
    uint8_t p256_priv_b[P256_BYTES], p256_pub_b[P256_BYTES * 2];
    static const uint8_t p256_priv_b_seed[P256_BYTES] = {
        0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10,
        0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10,
        0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10,
        0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10,
    };
    memcpy(p256_priv_b, p256_priv_b_seed, P256_BYTES);
    ret = HAL_OTBN_ECDSA_P256_DerivePubkey(p256_priv_b, p256_pub_b);
    if (ret == 0) {
        ret = HAL_OTBN_ECDSA_P256_SharedSecret(p256_priv_key, p256_pub_b, p256_shared_a);
        if (ret == 0)
            ret = HAL_OTBN_ECDSA_P256_SharedSecret(p256_priv_b, p256_derived_pub, p256_shared_b);
    }
    bool p256_ecdh_match = (ret == 0) && !buffer_is_zero(p256_shared_a, P256_BYTES) && bufs_eq(p256_shared_a, p256_shared_b, P256_BYTES * 2);
    memcpy((void *)g_p256_shared_a, p256_shared_a, P256_BYTES * 2);
    memcpy((void *)g_p256_shared_b, p256_shared_b, P256_BYTES * 2);
    REC(18, ret, p256_ecdh_match);
    print_result("P256 ECDH", ret, p256_ecdh_match);

    /* ================================================================
     *  Negative tests: the HAL must reject invalid inputs (upstream
     *  wolfSSL / mbedTLS checks mirrored in the validation module).
     * ================================================================ */
    LOG_I("--- negative validation tests ---");

    /* P-256 n (big-endian): r/d == n is out of range, == 0 is out of range */
    static const uint8_t p256_n_be[P256_BYTES] = {
        0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xbc, 0xe6, 0xfa, 0xad, 0xa7, 0x17, 0x9e, 0x84,
        0xf3, 0xb9, 0xca, 0xc2, 0xfc, 0x63, 0x25, 0x51,
    };
    uint8_t neg_pub[P256_BYTES * 2];
    uint8_t neg_sig[P256_BYTES * 2];
    uint8_t zero_buf[P256_BYTES] = {0};

    /* t19: derive with d = 0 */
    ret = HAL_OTBN_ECDSA_P256_DerivePubkey(zero_buf, neg_pub);
    pass = (ret != 0);
    REC(19, ret, pass);
    print_result("P256 derive d=0 rejected", ret, pass);

    /* t20: derive with d = n */
    ret = HAL_OTBN_ECDSA_P256_DerivePubkey(p256_n_be, neg_pub);
    pass = (ret != 0);
    REC(20, ret, pass);
    print_result("P256 derive d=n rejected", ret, pass);

    /* t21: sign with k = 0 */
    ret = HAL_OTBN_ECDSA_P256_Sign(p256_msg_hash, zero_buf, p256_priv_key, neg_sig);
    pass = (ret != 0);
    REC(21, ret, pass);
    print_result("P256 sign k=0 rejected", ret, pass);

    /* t22: verify with r = 0 (s kept from a valid signature) */
    memcpy(neg_sig, (void *)g_p256_sig, P256_BYTES * 2);
    memset(neg_sig, 0, P256_BYTES);
    ret = p256_verify_be(p256_msg_hash, neg_sig, (void *)g_p256_derived);
    pass = (ret != 0);
    REC(22, ret, pass);
    print_result("P256 verify r=0 rejected", ret, pass);

    /* t23: verify with r = n */
    memcpy(neg_sig, (void *)g_p256_sig, P256_BYTES * 2);
    memcpy(neg_sig, p256_n_be, P256_BYTES);
    ret = p256_verify_be(p256_msg_hash, neg_sig, (void *)g_p256_derived);
    pass = (ret != 0);
    REC(23, ret, pass);
    print_result("P256 verify r=n rejected", ret, pass);

    /* t24: verify with an off-curve public key (y incremented by 1) */
    memcpy(neg_pub, (void *)g_p256_derived, P256_BYTES * 2);
    for (int i = P256_BYTES - 1; i >= 0 && ++neg_pub[P256_BYTES + i] == 0; i--) {
    }
    ret = p256_verify_be(p256_msg_hash, (void *)g_p256_sig, neg_pub);
    pass = (ret != 0);
    REC(24, ret, pass);
    print_result("P256 verify off-curve pub rejected", ret, pass);

    /* t25: SM2 verify with an off-curve public key */
    uint8_t sm2_neg_pub[SM2_BYTES * 2];
    memcpy(sm2_neg_pub, (void *)g_sm2_derived, SM2_BYTES * 2);
    for (int i = SM2_BYTES - 1; i >= 0 && ++sm2_neg_pub[SM2_BYTES + i] == 0; i--) {
    }
    ret = sm2_verify_be(sm2_msg_hash, (void *)g_sm2_sig, sm2_neg_pub);
    pass = (ret != 0);
    REC(25, ret, pass);
    print_result("SM2 verify off-curve pub rejected", ret, pass);

    /* t26: P384 verify with an off-curve public key */
    uint8_t p384_neg_pub[P384_BYTES * 2];
    memcpy(p384_neg_pub, (void *)g_p384_derived, P384_BYTES * 2);
    for (int i = P384_BYTES - 1; i >= 0 && ++p384_neg_pub[P384_BYTES + i] == 0; i--) {
    }
    ret = p384_verify_be(message_hash, (void *)g_p384_sig, p384_neg_pub);
    pass = (ret != 0);
    REC(26, ret, pass);
    print_result("P384 verify off-curve pub rejected", ret, pass);

    /* ================================================================
     *  Boundary tests (t27-t36): extreme-but-legal inputs must be
     *  accepted (d=1, d=n-1, k=1, k=n-1), extreme-illegal ones must
     *  be rejected (infinity pub, r>=n at crypto layer, r=0/k=0 at
     *  SDK layer).  Reference values (G, -G, n-1) independently
     *  verified with Python big-int math.
     * ================================================================ */
    LOG_I("--- boundary tests ---");

    static const uint8_t p256_gx_be[P256_BYTES] = {
        0x6b, 0x17, 0xd1, 0xf2, 0xe1, 0x2c, 0x42, 0x47,
        0xf8, 0xbc, 0xe6, 0xe5, 0x63, 0xa4, 0x40, 0xf2,
        0x77, 0x03, 0x7d, 0x81, 0x2d, 0xeb, 0x33, 0xa0,
        0xf4, 0xa1, 0x39, 0x45, 0xd8, 0x98, 0xc2, 0x96,
    };
    static const uint8_t p256_gy_be[P256_BYTES] = {
        0x4f, 0xe3, 0x42, 0xe2, 0xfe, 0x1a, 0x7f, 0x9b,
        0x8e, 0xe7, 0xeb, 0x4a, 0x7c, 0x0f, 0x9e, 0x16,
        0x2b, 0xce, 0x33, 0x57, 0x6b, 0x31, 0x5e, 0xce,
        0xcb, 0xb6, 0x40, 0x68, 0x37, 0xbf, 0x51, 0xf5,
    };
    static const uint8_t p256_neggy_be[P256_BYTES] = {
        0xb0, 0x1c, 0xbd, 0x1c, 0x01, 0xe5, 0x80, 0x65,
        0x71, 0x18, 0x14, 0xb5, 0x83, 0xf0, 0x61, 0xe9,
        0xd4, 0x31, 0xcc, 0xa9, 0x94, 0xce, 0xa1, 0x31,
        0x34, 0x49, 0xbf, 0x97, 0xc8, 0x40, 0xae, 0x0a,
    };
    static const uint8_t p256_nm1_be[P256_BYTES] = {
        0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xbc, 0xe6, 0xfa, 0xad, 0xa7, 0x17, 0x9e, 0x84,
        0xf3, 0xb9, 0xca, 0xc2, 0xfc, 0x63, 0x25, 0x50,
    };
    static const uint8_t sm2_gx_be[SM2_BYTES] = {
        0x32, 0xc4, 0xae, 0x2c, 0x1f, 0x19, 0x81, 0x19,
        0x5f, 0x99, 0x04, 0x46, 0x6a, 0x39, 0xc9, 0x94,
        0x8f, 0xe3, 0x0b, 0xbf, 0xf2, 0x66, 0x0b, 0xe1,
        0x71, 0x5a, 0x45, 0x89, 0x33, 0x4c, 0x74, 0xc7,
    };
    static const uint8_t sm2_gy_be[SM2_BYTES] = {
        0xbc, 0x37, 0x36, 0xa2, 0xf4, 0xf6, 0x77, 0x9c,
        0x59, 0xbd, 0xce, 0xe3, 0x6b, 0x69, 0x21, 0x53,
        0xd0, 0xa9, 0x87, 0x7c, 0xc6, 0x2a, 0x47, 0x40,
        0x02, 0xdf, 0x32, 0xe5, 0x21, 0x39, 0xf0, 0xa0,
    };
    static const uint8_t p384_gx_be[P384_BYTES] = {
        0xaa, 0x87, 0xca, 0x22, 0xbe, 0x8b, 0x05, 0x37,
        0x8e, 0xb1, 0xc7, 0x1e, 0xf3, 0x20, 0xad, 0x74,
        0x6e, 0x1d, 0x3b, 0x62, 0x8b, 0xa7, 0x9b, 0x98,
        0x59, 0xf7, 0x41, 0xe0, 0x82, 0x54, 0x2a, 0x38,
        0x55, 0x02, 0xf2, 0x5d, 0xbf, 0x55, 0x29, 0x6c,
        0x3a, 0x54, 0x5e, 0x38, 0x72, 0x76, 0x0a, 0xb7,
    };
    static const uint8_t p384_gy_be[P384_BYTES] = {
        0x36, 0x17, 0xde, 0x4a, 0x96, 0x26, 0x2c, 0x6f,
        0x5d, 0x9e, 0x98, 0xbf, 0x92, 0x92, 0xdc, 0x29,
        0xf8, 0xf4, 0x1d, 0xbd, 0x28, 0x9a, 0x14, 0x7c,
        0xe9, 0xda, 0x31, 0x13, 0xb5, 0xf0, 0xb8, 0xc0,
        0x0a, 0x60, 0xb1, 0xce, 0x1d, 0x7e, 0x81, 0x9d,
        0x7a, 0x43, 0x1d, 0x7c, 0x90, 0xea, 0x0e, 0x5f,
    };
    /* P256 G as LSW-first u32 (SDK HAL input format) */
    static const uint32_t p256_gx_lsw[8] = {
        0xd898c296U, 0xf4a13945U, 0x2deb33a0U, 0x77037d81U,
        0x63a440f2U, 0xf8bce6e5U, 0xe12c4247U, 0x6b17d1f2U,
    };
    static const uint32_t p256_gy_lsw[8] = {
        0x37bf51f5U, 0xcbb64068U, 0x6b315eceU, 0x2bce3357U,
        0x7c0f9e16U, 0x8ee7eb4aU, 0xfe1a7f9bU, 0x4fe342e2U,
    };

    uint8_t edge_priv[P384_BYTES];
    uint8_t edge_pub[P384_BYTES * 2];

    /* t27: derive d=1 → pub == G */
    memset(edge_priv, 0, P384_BYTES);
    edge_priv[P256_BYTES - 1] = 1;
    ret = HAL_OTBN_ECDSA_P256_DerivePubkey(edge_priv, edge_pub);
    pass = (ret == 0) && bufs_eq(edge_pub, p256_gx_be, P256_BYTES) &&
           bufs_eq(edge_pub + P256_BYTES, p256_gy_be, P256_BYTES);
    REC(27, ret, pass);
    print_result("P256 derive d=1 == G", ret, pass);

    /* t28: derive d=n-1 → pub == -G == (Gx, p-Gy) */
    ret = HAL_OTBN_ECDSA_P256_DerivePubkey(p256_nm1_be, edge_pub);
    pass = (ret == 0) && bufs_eq(edge_pub, p256_gx_be, P256_BYTES) &&
           bufs_eq(edge_pub + P256_BYTES, p256_neggy_be, P256_BYTES);
    REC(28, ret, pass);
    print_result("P256 derive d=n-1 == -G", ret, pass);

    /* t29: sign k=1 → round-trip verify */
    memset(edge_priv, 0, P384_BYTES);
    edge_priv[P256_BYTES - 1] = 1;
    ret = HAL_OTBN_ECDSA_P256_Sign(p256_msg_hash, edge_priv, p256_priv_key, neg_sig);
    if (ret == 0)
        ret = p256_verify_be(p256_msg_hash, neg_sig, (void *)g_p256_derived);
    pass = (ret == 0);
    REC(29, ret, pass);
    print_result("P256 sign k=1 round-trip", ret, pass);

    /* t30: sign k=n-1 → round-trip verify */
    ret = HAL_OTBN_ECDSA_P256_Sign(p256_msg_hash, p256_nm1_be, p256_priv_key, neg_sig);
    if (ret == 0)
        ret = p256_verify_be(p256_msg_hash, neg_sig, (void *)g_p256_derived);
    pass = (ret == 0);
    REC(30, ret, pass);
    print_result("P256 sign k=n-1 round-trip", ret, pass);

    /* t31: verify with infinity public key (0,0) */
    memset(neg_pub, 0, P256_BYTES * 2);
    ret = p256_verify_be(p256_msg_hash, (void *)g_p256_sig, neg_pub);
    pass = (ret != 0);
    REC(31, ret, pass);
    print_result("P256 verify infinity pub rejected", ret, pass);

    /* t32: verify with r = 0xFF..FF (>= n) */
    memcpy(neg_sig, (void *)g_p256_sig, P256_BYTES * 2);
    memset(neg_sig, 0xFF, P256_BYTES);
    ret = p256_verify_be(p256_msg_hash, neg_sig, (void *)g_p256_derived);
    pass = (ret != 0);
    REC(32, ret, pass);
    print_result("P256 verify r=0xFF..FF rejected", ret, pass);

    /* t33: SDK layer verify with r=0 → rejected without touching OTBN */
    {
        struct HAL_OTBN_ECC256_Verify_Param vp;
        uint32_t m0[8] = {0}, r0[8] = {0}, s0[8] = {0};
        uint32_t gx[8], gy[8];
        memcpy(gx, p256_gx_lsw, sizeof(gx));
        memcpy(gy, p256_gy_lsw, sizeof(gy));
        vp.msg = m0; vp.r = r0; vp.s = s0; vp.x = gx; vp.y = gy;
        bool vres = HAL_OTBN_ECC256_ECDSA_Verify_Polling(&vp);
        REC(33, vres, !vres);
        print_result("SDK ECC256 verify r=0 rejected", vres, !vres);
    }

    /* t34: SDK layer scalar mult with k=0 → HAL_ERROR */
    {
        struct HAL_OTBN_ECC256_ScalarMult_Param sp;
        uint32_t k0[8] = {0};
        uint32_t gx[8], gy[8], sx[8], sy[8];
        memcpy(gx, p256_gx_lsw, sizeof(gx));
        memcpy(gy, p256_gy_lsw, sizeof(gy));
        sp.scalar = k0;
        sp.point_x = gx;
        sp.point_y = gy;
        sp.result_x = sx;
        sp.result_y = sy;
        HAL_StatusTypeDef sres =
            HAL_OTBN_ECC256_ScalarMult_Polling(HAL_OTBN_ECC256_CURVE_P256, &sp);
        REC(34, sres, sres != HAL_OK);
        print_result("SDK ECC256 scalarmult k=0 rejected", sres, sres != HAL_OK);
    }

    /* t35: SM2 derive d=1 → pub == SM2 G */
    memset(edge_priv, 0, P384_BYTES);
    edge_priv[SM2_BYTES - 1] = 1;
    ret = HAL_OTBN_SM2_DerivePubkey(edge_priv, edge_pub);
    pass = (ret == 0) && bufs_eq(edge_pub, sm2_gx_be, SM2_BYTES) &&
           bufs_eq(edge_pub + SM2_BYTES, sm2_gy_be, SM2_BYTES);
    REC(35, ret, pass);
    print_result("SM2 derive d=1 == G", ret, pass);

    /* t36: P384 derive d=1 → pub == P384 G */
    memset(edge_priv, 0, P384_BYTES);
    edge_priv[P384_BYTES - 1] = 1;
    ret = HAL_OTBN_ECDSA_P384_DerivePubkey(edge_priv, edge_pub);
    pass = (ret == 0) && bufs_eq(edge_pub, p384_gx_be, P384_BYTES) &&
           bufs_eq(edge_pub + P384_BYTES, p384_gy_be, P384_BYTES);
    REC(36, ret, pass);
    print_result("P384 derive d=1 == G", ret, pass);

    /* t40: P384 pointops ScalarMult k*G == DerivePubkey(k) (BaseMult).
     * Cross-validates the g_ecc_p384 ScalarMult path behind P384
     * SharedSecret against the already-verified BaseMult path. */
    {
        uint8_t scalar_le[P384_BYTES];
        uint32_t gx_le[12], gy_le[12], out32[24];
        uint8_t sm_out[P384_BYTES * 2];
        uint8_t ref_pub[P384_BYTES * 2];
        /* ScalarMult expects LSW-first (LE) words: same byte order
         * DerivePubkey feeds the BaseMult firmware after reversing */
        be_to_words(random_seed_sign, (uint32_t *)scalar_le, P384_BYTES);
        be_to_words(p384_gx_be, gx_le, P384_BYTES);
        be_to_words(p384_gy_be, gy_le, P384_BYTES);
        memset(sm_out, 0, sizeof(sm_out));
        HAL_StatusTypeDef sres = HAL_OTBN_P384_ScalarMult_Polling(scalar_le, (const uint8_t *)gx_le,
                                                                  (const uint8_t *)gy_le,
                                                                  sm_out, sm_out + P384_BYTES);
        /* Reference: same scalar through BaseMult (DerivePubkey) */
        uint32_t rref = HAL_OTBN_ECDSA_P384_DerivePubkey(random_seed_sign, ref_pub);
        /* Pointops firmware outputs LSW-first words (like BaseMult):
         * convert back to big-endian before comparing with the ref */
        be_to_words(sm_out, out32, P384_BYTES);
        be_to_words(sm_out + P384_BYTES, out32 + 12, P384_BYTES);
        pass = (sres == HAL_OK) && (rref == 0) &&
               bufs_eq((uint8_t *)out32, ref_pub, P384_BYTES * 2);
        REC(40, sres, pass);
        print_result("P384 Scalarmult k*G == BaseMult", sres, pass);
    }

    /* t41: SM2 pointops ScalarMult k*G == DerivePubkey(k) (BaseMult).
     * Cross-validates the g_ecc_sm2 ScalarMult path behind SM2
     * SharedSecret against the already-verified BaseMult path (the SM2
     * ECDH test alone only checks shared_a == shared_b). */
    {
        uint8_t scalar_le[SM2_BYTES];
        uint32_t gx_le[8], gy_le[8], out32[16];
        uint8_t sm_out[SM2_BYTES * 2];
        uint8_t ref_pub[SM2_BYTES * 2];
        /* ScalarMult expects LSW-first (LE) words: same byte order
         * DerivePubkey feeds the BaseMult firmware after reversing */
        be_to_words(sm2_random_seed, (uint32_t *)scalar_le, SM2_BYTES);
        be_to_words(sm2_gx_be, gx_le, SM2_BYTES);
        be_to_words(sm2_gy_be, gy_le, SM2_BYTES);
        memset(sm_out, 0, sizeof(sm_out));
        HAL_StatusTypeDef sres = HAL_OTBN_SM2_ScalarMult_Polling(scalar_le, (const uint8_t *)gx_le,
                                                                 (const uint8_t *)gy_le,
                                                                 sm_out, sm_out + SM2_BYTES);
        uint32_t rref = HAL_OTBN_SM2_DerivePubkey(sm2_random_seed, ref_pub);
        /* Pointops firmware outputs LSW-first words (like BaseMult):
         * convert back to big-endian before comparing with the ref */
        be_to_words(sm_out, out32, SM2_BYTES);
        be_to_words(sm_out + SM2_BYTES, out32 + 8, SM2_BYTES);
        pass = (sres == HAL_OK) && (rref == 0) &&
               bufs_eq((uint8_t *)out32, ref_pub, SM2_BYTES * 2);
        REC(41, sres, pass);
        print_result("SM2 Scalarmult k*G == BaseMult", sres, pass);
    }

    /* ================================================================
     *  SDK Verify IT tests (async path, bounded wait via it_wait)
     * ================================================================ */
    LOG_I("--- SDK Verify IT tests ---");

    /* t37: P256 verify IT (valid signature) */
    {
        uint32_t msg[8], r[8], s[8], x[8], y[8];
        struct HAL_OTBN_ECC256_Verify_Param vp = { msg, r, s, x, y };
        be_to_words(p256_msg_hash, msg, P256_BYTES);
        be_to_words((const uint8_t *)(void *)g_p256_sig, r, P256_BYTES);
        be_to_words((const uint8_t *)(void *)g_p256_sig + P256_BYTES, s, P256_BYTES);
        be_to_words((const uint8_t *)(void *)g_p256_derived, x, P256_BYTES);
        be_to_words((const uint8_t *)(void *)g_p256_derived + P256_BYTES, y, P256_BYTES);
        s_it_done = false;
        HAL_OTBN_ECC256_ECDSA_Verify_IT(&vp);
        pass = it_wait() && s_it_result;
        REC(37, pass, pass);
        print_result("P256 verify IT (valid)", 0, pass);
    }

    /* t38: P384 verify IT (valid signature) */
    {
        uint32_t msg[12], r[12], s[12], x[12], y[12];
        struct HAL_OTBN_ECC384_Verify_Param vp = { msg, r, s, x, y };
        be_to_words(message_hash, msg, P384_BYTES);
        be_to_words((const uint8_t *)(void *)g_p384_sig, r, P384_BYTES);
        be_to_words((const uint8_t *)(void *)g_p384_sig + P384_BYTES, s, P384_BYTES);
        be_to_words((const uint8_t *)(void *)g_p384_derived, x, P384_BYTES);
        be_to_words((const uint8_t *)(void *)g_p384_derived + P384_BYTES, y, P384_BYTES);
        s_it_done = false;
        HAL_OTBN_ECC384_ECDSA_Verify_IT(HAL_OTBN_ECC384_CURVE_P384, &vp);
        pass = it_wait() && s_it_result;
        REC(38, pass, pass);
        print_result("P384 verify IT (valid)", 0, pass);
    }

    /* t39: SM2 verify IT (valid signature) */
    {
        uint32_t msg[8], r[8], s[8], x[8], y[8];
        struct HAL_OTBN_SM2_Verify_Param vp = { msg, r, s, x, y };
        be_to_words(sm2_msg_hash, msg, SM2_BYTES);
        be_to_words((const uint8_t *)(void *)g_sm2_sig, r, SM2_BYTES);
        be_to_words((const uint8_t *)(void *)g_sm2_sig + SM2_BYTES, s, SM2_BYTES);
        be_to_words((const uint8_t *)(void *)g_sm2_derived, x, SM2_BYTES);
        be_to_words((const uint8_t *)(void *)g_sm2_derived + SM2_BYTES, y, SM2_BYTES);
        s_it_done = false;
        HAL_OTBN_SM2_Verify_IT(&vp);
        pass = it_wait() && s_it_result;
        REC(39, pass, pass);
        print_result("SM2 verify IT (valid)", 0, pass);
    }

    /* ================================================================
     *  App-level crypto IT consistency tests (t42-t50): each async
     *  interface must produce exactly the polling result for the same
     *  inputs, written through its callback, with status 0.
     * ================================================================ */
    LOG_I("--- App-level crypto IT consistency tests ---");

    /* t42: P384 DerivePubkey_IT == DerivePubkey (polling) */
    {
        s_it_done = false;
        s_it_status = 0xFFFFFFFF;
        uint32_t r_it = HAL_OTBN_ECDSA_P384_DerivePubkey_IT(priv_key_a, (uint8_t *)(void *)g_p384_derived_it);
        pass = (r_it == 0) && it_wait() && (s_it_status == 0) &&
               bufs_eq((const uint8_t *)(void *)g_p384_derived,
                       (const uint8_t *)(void *)g_p384_derived_it, P384_BYTES * 2);
        REC(42, r_it, pass);
        print_result("P384 DerivePubkey IT == polling", r_it, pass);
    }

    /* t43: P384 Sign_IT == Sign (polling, same k and d) */
    {
        s_it_done = false;
        s_it_status = 0xFFFFFFFF;
        uint32_t r_it = HAL_OTBN_ECDSA_P384_Sign_IT(message_hash, random_seed_sign,
                                                    priv_key_a, (uint8_t *)(void *)g_p384_sig_it);
        pass = (r_it == 0) && it_wait() && (s_it_status == 0) &&
               bufs_eq((const uint8_t *)(void *)g_p384_sig,
                       (const uint8_t *)(void *)g_p384_sig_it, P384_BYTES * 2);
        REC(43, r_it, pass);
        print_result("P384 Sign IT == polling", r_it, pass);
    }

    /* t44: P384 SharedSecret_IT == SharedSecret (polling) */
    {
        s_it_done = false;
        s_it_status = 0xFFFFFFFF;
        uint32_t r_it = HAL_OTBN_ECDSA_P384_SharedSecret_IT(priv_key_a, p384_pub_b,
                                                            (uint8_t *)(void *)g_p384_shared_it);
        pass = (r_it == 0) && it_wait() && (s_it_status == 0) &&
               bufs_eq((const uint8_t *)(void *)g_p384_shared_a,
                       (const uint8_t *)(void *)g_p384_shared_it, P384_BYTES * 2);
        REC(44, r_it, pass);
        print_result("P384 SharedSecret IT == polling", r_it, pass);
    }

    /* t45: SM2 DerivePubkey_IT == DerivePubkey (polling) */
    {
        s_it_done = false;
        s_it_status = 0xFFFFFFFF;
        uint32_t r_it = HAL_OTBN_SM2_DerivePubkey_IT(sm2_priv_key, (uint8_t *)(void *)g_sm2_derived_it);
        pass = (r_it == 0) && it_wait() && (s_it_status == 0) &&
               bufs_eq((const uint8_t *)(void *)g_sm2_derived,
                       (const uint8_t *)(void *)g_sm2_derived_it, SM2_BYTES * 2);
        REC(45, r_it, pass);
        print_result("SM2 DerivePubkey IT == polling", r_it, pass);
    }

    /* t46: SM2 Sign_IT == Sign (polling, same k and d) */
    {
        s_it_done = false;
        s_it_status = 0xFFFFFFFF;
        uint32_t r_it = HAL_OTBN_SM2_Sign_IT(sm2_msg_hash, sm2_sign_rand,
                                             sm2_priv_key, (uint8_t *)(void *)g_sm2_sig_it);
        pass = (r_it == 0) && it_wait() && (s_it_status == 0) &&
               bufs_eq((const uint8_t *)(void *)g_sm2_sig,
                       (const uint8_t *)(void *)g_sm2_sig_it, SM2_BYTES * 2);
        REC(46, r_it, pass);
        print_result("SM2 Sign IT == polling", r_it, pass);
    }

    /* t47: SM2 SharedSecret_IT == SharedSecret (polling) */
    {
        s_it_done = false;
        s_it_status = 0xFFFFFFFF;
        uint32_t r_it = HAL_OTBN_SM2_SharedSecret_IT(sm2_priv_key, sm2_pub_b,
                                                     (uint8_t *)(void *)g_sm2_shared_it);
        pass = (r_it == 0) && it_wait() && (s_it_status == 0) &&
               bufs_eq((const uint8_t *)(void *)g_sm2_shared_a,
                       (const uint8_t *)(void *)g_sm2_shared_it, SM2_BYTES * 2);
        REC(47, r_it, pass);
        print_result("SM2 SharedSecret IT == polling", r_it, pass);
    }

    /* t48: P256 DerivePubkey_IT == DerivePubkey (polling) */
    {
        s_it_done = false;
        s_it_status = 0xFFFFFFFF;
        uint32_t r_it = HAL_OTBN_ECDSA_P256_DerivePubkey_IT(p256_priv_key, (uint8_t *)(void *)g_p256_derived_it);
        pass = (r_it == 0) && it_wait() && (s_it_status == 0) &&
               bufs_eq((const uint8_t *)(void *)g_p256_derived,
                       (const uint8_t *)(void *)g_p256_derived_it, P256_BYTES * 2);
        REC(48, r_it, pass);
        print_result("P256 DerivePubkey IT == polling", r_it, pass);
    }

    /* t49: P256 Sign_IT == Sign (polling, same k and d) */
    {
        s_it_done = false;
        s_it_status = 0xFFFFFFFF;
        uint32_t r_it = HAL_OTBN_ECDSA_P256_Sign_IT(p256_msg_hash, p256_sign_rand,
                                                    p256_priv_key, (uint8_t *)(void *)g_p256_sig_it);
        pass = (r_it == 0) && it_wait() && (s_it_status == 0) &&
               bufs_eq((const uint8_t *)(void *)g_p256_sig,
                       (const uint8_t *)(void *)g_p256_sig_it, P256_BYTES * 2);
        REC(49, r_it, pass);
        print_result("P256 Sign IT == polling", r_it, pass);
    }

    /* t50: P256 SharedSecret_IT == SharedSecret (polling) */
    {
        s_it_done = false;
        s_it_status = 0xFFFFFFFF;
        uint32_t r_it = HAL_OTBN_ECDSA_P256_SharedSecret_IT(p256_priv_key, p256_pub_b,
                                                            (uint8_t *)(void *)g_p256_shared_it);
        pass = (r_it == 0) && it_wait() && (s_it_status == 0) &&
               bufs_eq((const uint8_t *)(void *)g_p256_shared_a,
                       (const uint8_t *)(void *)g_p256_shared_it, P256_BYTES * 2);
        REC(50, r_it, pass);
        print_result("P256 SharedSecret IT == polling", r_it, pass);
    }

    /* t51: OTBN busy rejection.  A second submit while the first job is
     * still running must be refused (OTBN is a single engine, no
     * interleaving), and the first job's callback must still fire. */
    {
        /* Poison the second job's output buffer so a "refused" submit
         * can be distinguished from a stale write from test t42. */
        uint8_t poison[P384_BYTES * 2];
        memset(poison, 0xAA, sizeof(poison));
        memcpy((void *)g_p384_derived_it, poison, sizeof(poison));
        s_it_done = false;
        s_it_status = 0xFFFFFFFF;
        uint32_t r1 = HAL_OTBN_ECDSA_P384_Sign_IT(message_hash, random_seed_sign,
                                                  priv_key_a, (uint8_t *)(void *)g_p384_sig_it);
        /* Second submit must be rejected while the engine is running */
        uint32_t r2 = HAL_OTBN_ECDSA_P384_DerivePubkey_IT(priv_key_a, (uint8_t *)(void *)g_p384_derived_it);
        bool first_fired = it_wait();
        /* Refused job must not have touched its output buffer */
        bool second_no_result = bufs_eq((const uint8_t *)(void *)g_p384_derived_it,
                                        poison, sizeof(poison));
        bool sig_match = bufs_eq((const uint8_t *)(void *)g_p384_sig,
                                 (const uint8_t *)(void *)g_p384_sig_it, P384_BYTES * 2);
        pass = (r1 == 0) && (r2 == 1) && first_fired && (s_it_status == 0) &&
               sig_match && second_no_result;
        REC(51, r2, pass);
        print_result("OTBN busy: 2nd submit rejected", r2, pass);
    }

    /* t52: SM2 ValidPoint_Polling (SM2 unified firmware VALIDPOINT
     * mode, polling companion of the existing IT).  The generator
     * point must pass; y+1 (still < p) must be rejected. */
    {
        uint32_t xw[8], yw[8], yw_bad[8];
        be_to_words(sm2_gx_be, xw, SM2_BYTES);
        be_to_words(sm2_gy_be, yw, SM2_BYTES);
        memcpy(yw_bad, yw, sizeof(yw_bad));
        yw_bad[0]++;   /* y+1: off the curve */
        bool ok = HAL_OTBN_SM2_ValidPoint_Polling(xw, yw);
        bool rej = !HAL_OTBN_SM2_ValidPoint_Polling(xw, yw_bad);
        pass = ok && rej;
        REC(52, ok, pass);
        print_result("SM2 ValidPoint polling: on-curve pass, off-curve reject", ok, pass);
    }

    /* t53: SM2 ScalarMult_Engine_Polling (SM2 unified firmware
     * SCALARMULT mode -- this firmware mode previously had no caller).
     * Validate 1*G == G and k*G == DerivePubkey(k) (BaseMult). */
    {
        uint32_t scalar1[16], scalark[16];
        uint32_t gx[8], gy[8];
        uint32_t rx[16], ry[16];
        uint32_t out32[16];
        uint8_t ref_pub[SM2_BYTES * 2];
        struct HAL_OTBN_SM2_ScalarMult_Param p;
        memset(scalar1, 0, sizeof(scalar1));
        scalar1[0] = 1;                      /* d = 1 */
        be_to_words(sm2_random_seed, scalark, SM2_BYTES);
        be_to_words(sm2_gx_be, gx, SM2_BYTES);
        be_to_words(sm2_gy_be, gy, SM2_BYTES);
        p.point_x = gx;
        p.point_y = gy;
        /* Scalar slot is 0x40 bytes in the SM2 firmware layout */
        p.scalar = scalar1;
        p.result_x = rx;
        p.result_y = ry;
        HAL_StatusTypeDef s1 = HAL_OTBN_SM2_ScalarMult_Engine_Polling(&p);
        /* d=1 -> G: firmware outputs LSW-first words, convert to BE */
        be_to_words((uint8_t *)rx, out32, SM2_BYTES);
        be_to_words((uint8_t *)ry, out32 + 8, SM2_BYTES);
        bool one_g = (s1 == HAL_OK) &&
                     bufs_eq((uint8_t *)out32, sm2_gx_be, SM2_BYTES) &&
                     bufs_eq((uint8_t *)out32 + SM2_BYTES, sm2_gy_be, SM2_BYTES);
        /* k*G == DerivePubkey(k) */
        p.scalar = scalark;
        HAL_StatusTypeDef s2 = HAL_OTBN_SM2_ScalarMult_Engine_Polling(&p);
        uint32_t rref = HAL_OTBN_SM2_DerivePubkey(sm2_random_seed, ref_pub);
        be_to_words((uint8_t *)rx, out32, SM2_BYTES);
        be_to_words((uint8_t *)ry, out32 + 8, SM2_BYTES);
        bool k_g = (s2 == HAL_OK) && (rref == 0) &&
                   bufs_eq((uint8_t *)out32, ref_pub, SM2_BYTES * 2);
        pass = one_g && k_g;
        REC(53, s2, pass);
        print_result("SM2 ScalarMult engine polling: 1*G==G, k*G==BaseMult", s2, pass);
    }

    /* t54: HAL_OTBN_Reset() recovers the engine -- after a forced
     * reset (pulse reset through the SoC reset controller), the engine
     * must accept a fresh program + submit and produce a correct result
     * (1*G == G on P-256). */
    {
        struct HAL_OTBN_ECC256_ScalarMult_Param sp;
        uint32_t k1[8] = {0}, gx[8], gy[8], rx[8], ry[8], out32[16];
        static const uint8_t gx_be[P256_BYTES] = {
            0x6b, 0x17, 0xd1, 0xf2, 0xe1, 0x2c, 0x42, 0x47,
            0xf8, 0xbc, 0xe6, 0xe5, 0x63, 0xa4, 0x40, 0xf2,
            0x77, 0x03, 0x7d, 0x81, 0x2d, 0xeb, 0x33, 0xa0,
            0xf4, 0xa1, 0x39, 0x45, 0xd8, 0x98, 0xc2, 0x96};
        static const uint8_t gy_be[P256_BYTES] = {
            0x4f, 0xe3, 0x42, 0xe2, 0xfe, 0x1a, 0x7f, 0x9b,
            0x8e, 0xe7, 0xeb, 0x4a, 0x7c, 0x0f, 0x9e, 0x16,
            0x2b, 0xce, 0x33, 0x57, 0x6b, 0x31, 0x5e, 0xce,
            0xcb, 0xb6, 0x40, 0x68, 0x37, 0xbf, 0x51, 0xf5};
        k1[0] = 1;
        be_to_words(gx_be, gx, P256_BYTES);
        be_to_words(gy_be, gy, P256_BYTES);
        HAL_OTBN_Reset();
        sp.scalar = k1;
        sp.point_x = gx;
        sp.point_y = gy;
        sp.result_x = rx;
        sp.result_y = ry;
        HAL_StatusTypeDef s = HAL_OTBN_ECC256_ScalarMult_Polling(HAL_OTBN_ECC256_CURVE_P256, &sp);
        be_to_words((uint8_t *)rx, out32, P256_BYTES);
        be_to_words((uint8_t *)ry, out32 + 8, P256_BYTES);
        bool ok = (s == HAL_OK) &&
                  bufs_eq((uint8_t *)out32, gx_be, P256_BYTES) &&
                  bufs_eq((uint8_t *)out32 + P256_BYTES, gy_be, P256_BYTES);
        REC(54, s, ok);
        print_result("OTBN Reset: engine recovers, 1*G==G after reset", s, ok);
    }

    LOG_I("OTBN P-384 ECC v2 test done");
    while (1);
}

void HAL_OTBN_ECC256_ECDSA_Verify_CallBack(bool result)
{
    s_it_done = true;
    s_it_result = result;
}

void HAL_OTBN_ECC384_ECDSA_Verify_CallBack(bool result)
{
    s_it_done = true;
    s_it_result = result;
}

void HAL_OTBN_SM2_Verify_CallBack(bool result)
{
    s_it_done = true;
    s_it_result = result;
}

/* App-level crypto IT callbacks (override the weak defaults) */
void HAL_OTBN_ECDSA_P384_DerivePubkey_CallBack(uint32_t status)
{
    s_it_done = true;
    s_it_status = status;
}

void HAL_OTBN_ECDSA_P384_Sign_CallBack(uint32_t status)
{
    s_it_done = true;
    s_it_status = status;
}

void HAL_OTBN_ECDSA_P384_SharedSecret_CallBack(uint32_t status)
{
    s_it_done = true;
    s_it_status = status;
}

void HAL_OTBN_SM2_DerivePubkey_CallBack(uint32_t status)
{
    s_it_done = true;
    s_it_status = status;
}

void HAL_OTBN_SM2_Sign_CallBack(uint32_t status)
{
    s_it_done = true;
    s_it_status = status;
}

void HAL_OTBN_SM2_SharedSecret_CallBack(uint32_t status)
{
    s_it_done = true;
    s_it_status = status;
}

void HAL_OTBN_ECDSA_P256_DerivePubkey_CallBack(uint32_t status)
{
    s_it_done = true;
    s_it_status = status;
}

void HAL_OTBN_ECDSA_P256_Sign_CallBack(uint32_t status)
{
    s_it_done = true;
    s_it_status = status;
}

void HAL_OTBN_ECDSA_P256_SharedSecret_CallBack(uint32_t status)
{
    s_it_done = true;
    s_it_status = status;
}
