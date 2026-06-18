#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "platform.h"
#include "ls_hal_otbn_unified.h"
#include "ls_hal_otbn.h"
#include "log.h"

/* ======================================================================== */
/* Test result tracking                                                     */
/* ======================================================================== */

typedef struct {
    uint32_t passed;
    uint32_t failed;
    uint32_t skipped;
} test_result_t;

static void result_reset(test_result_t *r) {
    r->passed = 0;
    r->failed = 0;
    r->skipped = 0;
}

static void result_print(const test_result_t *r, const char *name) {
    LOG_I("  %s: %u passed, %u failed, %u skipped",
          name, (unsigned)r->passed, (unsigned)r->failed, (unsigned)r->skipped);
}

/* ======================================================================== */
/* Generic check helpers                                                    */
/* ======================================================================== */

static bool check_u32_eq(const uint32_t *a, const uint32_t *b, uint32_t nwords,
                         const char *name, test_result_t *r) {
    for (uint32_t i = 0; i < nwords; ++i) {
        if (a[i] != b[i]) {
            LOG_I("    [FAIL] %s: word %u mismatch: got 0x%08X, expected 0x%08X",
                  name, (unsigned)i, (unsigned)a[i], (unsigned)b[i]);
            r->failed++;
            return false;
        }
    }
    LOG_I("    [PASS] %s", name);
    r->passed++;
    return true;
}

static bool check_u8_eq(const uint8_t *a, const uint8_t *b, uint32_t nbytes,
                        const char *name, test_result_t *r) {
    for (uint32_t i = 0; i < nbytes; ++i) {
        if (a[i] != b[i]) {
            LOG_I("    [FAIL] %s: byte %u mismatch: got 0x%02X, expected 0x%02X",
                  name, (unsigned)i, (unsigned)a[i], (unsigned)b[i]);
            r->failed++;
            return false;
        }
    }
    LOG_I("    [PASS] %s", name);
    r->passed++;
    return true;
}

static bool check_bool(bool actual, bool expected, const char *name,
                       test_result_t *r) {
    if (actual != expected) {
        LOG_I("    [FAIL] %s: got %s, expected %s",
              name, actual ? "true" : "false", expected ? "true" : "false");
        r->failed++;
        return false;
    }
    LOG_I("    [PASS] %s", name);
    r->passed++;
    return true;
}

/* ======================================================================== */
/* 01. bn_mul tests                                                         */
/* ======================================================================== */

static void test_bn_mul(test_result_t *r) {
    LOG_I("--- 01. bn_mul ---");

    static const uint32_t a_3[] = {0x00000003U, 0, 0, 0, 0, 0, 0, 0};
    static const uint32_t b_5[] = {0x00000005U, 0, 0, 0, 0, 0, 0, 0};
    static const uint32_t exp_15[] = {0x0000000fU, 0, 0, 0, 0, 0, 0, 0,
                                      0, 0, 0, 0, 0, 0, 0, 0};
    uint32_t result[16] = {0};
    HAL_OTBN_MUL_Polling(a_3, b_5, 1, result);
    check_u32_eq(result, exp_15, 16, "3 * 5 = 15", r);
}

/* ======================================================================== */
/* 02. bn_div tests                                                         */
/* ======================================================================== */

static void test_bn_div(test_result_t *r) {
    LOG_I("--- 02. bn_div ---");

    static const uint32_t dividend[] = {15, 0, 0, 0, 0, 0, 0, 0};
    static const uint32_t divisor[]  = {3, 0, 0, 0, 0, 0, 0, 0};
    static const uint32_t exp_q[]    = {5, 0, 0, 0, 0, 0, 0, 0};
    static const uint32_t exp_r[]    = {0, 0, 0, 0, 0, 0, 0, 0};
    uint32_t quotient[8]  = {0};
    uint32_t remainder[8] = {0};
    HAL_OTBN_DIV_Polling(dividend, divisor, 1, quotient, remainder);
    check_u32_eq(quotient, exp_q, 8, "15 / 3 = 5", r);
    check_u32_eq(remainder, exp_r, 8, "15 % 3 = 0", r);
}

/* ======================================================================== */
/* 03. bn_modmult tests                                                     */
/* ======================================================================== */

static void test_bn_modmult(test_result_t *r) {
    LOG_I("--- 03. bn_modmult ---");

    /* Test 1: 1-limb mod mult with large odd modulus (Montgomery-friendly) */
    static const uint32_t a1[]   = {0x00000003U, 0, 0, 0, 0, 0, 0, 0};
    static const uint32_t b1[]   = {0x00000005U, 0, 0, 0, 0, 0, 0, 0};
    static const uint32_t m1[]   = {0x0000000bU, 0, 0, 0, 0, 0, 0, 0x80000000U};
    static const uint32_t exp1[] = {0x0000000fU, 0, 0, 0, 0, 0, 0, 0};
    uint32_t result1[8] = {0};
    HAL_OTBN_MODMULT_Polling(a1, b1, m1, 1, result1);
    check_u32_eq(result1, exp1, 8, "3 * 5 mod (2^255+11) = 15", r);

    /* Test 2: 1-limb mod mult */
    static const uint32_t a2[]   = {0x00000007U, 0, 0, 0, 0, 0, 0, 0};
    static const uint32_t b2[]   = {0x00000009U, 0, 0, 0, 0, 0, 0, 0};
    static const uint32_t m2[]   = {0x0000000dU, 0, 0, 0, 0, 0, 0, 0x80000000U};
    static const uint32_t exp2[] = {0x0000003fU, 0, 0, 0, 0, 0, 0, 0};
    uint32_t result2[8] = {0};
    HAL_OTBN_MODMULT_Polling(a2, b2, m2, 1, result2);
    check_u32_eq(result2, exp2, 8, "7 * 9 mod (2^255+13) = 63", r);

    /* Test 3: 2-limb mod mult */
    static const uint32_t a3[]   = {0x0000007bU, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0};
    static const uint32_t b3[]   = {0x000001c8U, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0};
    static const uint32_t m3[]   = {0x000003f1U, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0x80000000U};
    static const uint32_t exp3[] = {0x0000db18U, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0};
    uint32_t result3[16] = {0};
    HAL_OTBN_MODMULT_Polling(a3, b3, m3, 2, result3);
    check_u32_eq(result3, exp3, 16, "2-limb mod mult", r);
}

/* ======================================================================== */
/* 04. bn_gcd tests                                                         */
/* ======================================================================== */

static void test_bn_gcd(test_result_t *r) {
    LOG_I("--- 04. bn_gcd ---");

    static const uint32_t a[]   = {48, 0, 0, 0, 0, 0, 0, 0};
    static const uint32_t b[]   = {18, 0, 0, 0, 0, 0, 0, 0};
    static const uint32_t exp[] = {6, 0, 0, 0, 0, 0, 0, 0};
    uint32_t result[8] = {0};
    HAL_OTBN_GCD_Polling(a, b, 1, result);
    check_u32_eq(result, exp, 8, "gcd(48, 18) = 6", r);
}

/* ======================================================================== */
/* 05. bn_modexp tests                                                      */
/* ======================================================================== */

static void test_bn_modexp(test_result_t *r) {
    LOG_I("--- 05. bn_modexp ---");

    /* Test 1: 1-limb mod exp with large odd modulus */
    static const uint32_t base1[] = {0x00000002U, 0, 0, 0, 0, 0, 0, 0};
    static const uint32_t exp1[]  = {0x00000003U, 0, 0, 0, 0, 0, 0, 0};
    static const uint32_t mod1[]  = {0x00000007U, 0, 0, 0, 0, 0, 0, 0x80000000U};
    static const uint32_t exp_result1[] = {0x00000008U, 0, 0, 0, 0, 0, 0, 0};
    uint32_t result1[8] = {0};
    HAL_OTBN_MODEXP_Polling(base1, exp1, mod1, 1, result1);
    check_u32_eq(result1, exp_result1, 8, "2^3 mod (2^255+7) = 8", r);

    /* Test 2: 1-limb mod exp */
    static const uint32_t base2[] = {0x00000003U, 0, 0, 0, 0, 0, 0, 0};
    static const uint32_t exp2[]  = {0x00000005U, 0, 0, 0, 0, 0, 0, 0};
    static const uint32_t mod2[]  = {0x0000000bU, 0, 0, 0, 0, 0, 0, 0x80000000U};
    static const uint32_t exp_result2[] = {0x000000f3U, 0, 0, 0, 0, 0, 0, 0};
    uint32_t result2[8] = {0};
    HAL_OTBN_MODEXP_Polling(base2, exp2, mod2, 1, result2);
    check_u32_eq(result2, exp_result2, 8, "3^5 mod (2^255+11) = 243", r);

    /* Test 3: 2-limb mod exp */
    static const uint32_t base3[] = {0x0000007bU, 0, 0, 0, 0, 0, 0, 0,
                                     0, 0, 0, 0, 0, 0, 0, 0};
    static const uint32_t exp3[]  = {0x000001c8U, 0, 0, 0, 0, 0, 0, 0,
                                     0, 0, 0, 0, 0, 0, 0, 0};
    static const uint32_t mod3[]  = {0x000003f1U, 0, 0, 0, 0, 0, 0, 0,
                                     0, 0, 0, 0, 0, 0, 0, 0x80000000U};
    static const uint32_t exp_result3[] = {
        0x284bc68bU, 0x70f9aabdU, 0xee7e1207U, 0x1126bd17U,
        0xafe51b27U, 0xf6a16f78U, 0x3f618d2aU, 0xb4c6c81bU,
        0xc566bce5U, 0x6e694351U, 0xb3a9dc48U, 0x5bc24ed8U,
        0xd85c178fU, 0x488a1919U, 0xb3cccbedU, 0x6941e48fU};
    uint32_t result3[16] = {0};
    HAL_OTBN_MODEXP_Polling(base3, exp3, mod3, 2, result3);
    check_u32_eq(result3, exp_result3, 16, "2-limb mod exp", r);
}

/* ======================================================================== */
/* 06. bn_modinv tests                                                      */
/* ======================================================================== */

static void test_bn_modinv(test_result_t *r) {
    LOG_I("--- 06. bn_modinv ---");

    /* Test 1: 1-limb mod inverse with P-256 prime */
    static const uint32_t n1[]   = {0x00000003U, 0, 0, 0, 0, 0, 0, 0};
    static const uint32_t m1[]   = {
        0xffffffffU, 0xffffffffU, 0xffffffffU, 0x00000000U,
        0x00000000U, 0x00000000U, 0x00000001U, 0xffffffffU};
    static const uint32_t exp1[] = {
        0x55555555U, 0x55555555U, 0x55555555U, 0xaaaaaaabU,
        0xaaaaaaaaU, 0xaaaaaaaaU, 0x00000000U, 0xaaaaaaaaU};
    uint32_t result1[8] = {0};
    HAL_OTBN_MODINV_Polling(n1, m1, 1, result1);
    check_u32_eq(result1, exp1, 8, "3^-1 mod P-256", r);

    /* Test 2: 1-limb mod inverse (5^-1 mod P-256) */
    static const uint32_t n2[]   = {0x00000005U, 0, 0, 0, 0, 0, 0, 0};
    static const uint32_t m2[]   = {
        0xffffffffU, 0xffffffffU, 0xffffffffU, 0x00000000U,
        0x00000000U, 0x00000000U, 0x00000001U, 0xffffffffU};
    static const uint32_t exp2[] = {
        0x99999999U, 0x99999999U, 0x99999999U, 0xcccccccdU,
        0xccccccccU, 0xccccccccU, 0x00000000U, 0xccccccccU};
    uint32_t result2[8] = {0};
    HAL_OTBN_MODINV_Polling(n2, m2, 1, result2);
    check_u32_eq(result2, exp2, 8, "5^-1 mod P-256", r);

    /* Test 3: 2-limb mod inverse */
    static const uint32_t n3[]   = {0x0000007bU, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0};
    static const uint32_t m3[]   = {
        0x3c35381bU, 0x11c17e14U, 0x4a758e41U, 0xe1e492a1U,
        0x2a2548d4U, 0x531b5ca6U, 0xe469f597U, 0x351e6687U,
        0x20bdaa06U, 0x7750aad4U, 0xeafded1cU, 0x44064b1fU,
        0xd3b3677eU, 0x7382e4d1U, 0x3492675cU, 0xb93258acU};
    static const uint32_t exp3[] = {
        0x5129c495U, 0xdd5d07cbU, 0x5943e08eU, 0x810b2673U,
        0x2f083998U, 0x36313081U, 0x6ad89b4dU, 0x55728cbbU,
        0xd7195edeU, 0x1054bcbfU, 0xc1ff6d40U, 0x3c6df7a0U,
        0xb33bff78U, 0x8a138818U, 0x2dc0677fU, 0x33314c8bU};
    uint32_t result3[16] = {0};
    HAL_OTBN_MODINV_Polling(n3, m3, 2, result3);
    check_u32_eq(result3, exp3, 16, "2-limb mod inverse", r);
}

/* ======================================================================== */
/* 07. ecc_p256 tests                                                       */
/* ======================================================================== */

static void test_ecc_p256(test_result_t *r) {
    LOG_I("--- 07. ecc_p256 ---");

    static const uint8_t gx[32] = {
        0x96, 0xc2, 0x98, 0xd8, 0x45, 0x39, 0xa1, 0xf4,
        0xa0, 0x33, 0xeb, 0x2d, 0x81, 0x7d, 0x03, 0x77,
        0xf2, 0x40, 0xa4, 0x63, 0xe5, 0xe6, 0xbc, 0xf8,
        0x47, 0x42, 0x2c, 0xe1, 0xf2, 0xd1, 0x17, 0x6b};
    static const uint8_t gy[32] = {
        0xf5, 0x51, 0xbf, 0x37, 0x68, 0x40, 0xb6, 0xcb,
        0xce, 0x5e, 0x31, 0x6b, 0x57, 0x33, 0xce, 0x2b,
        0x16, 0x9e, 0x0f, 0x7c, 0x4a, 0xeb, 0xe7, 0x8e,
        0x9b, 0x7f, 0x1a, 0xfe, 0xe2, 0x42, 0xe3, 0x4f};
    static const uint8_t g2x[32] = {
        0x78, 0x99, 0x66, 0x47, 0xfc, 0x48, 0x0b, 0xa6,
        0x35, 0x1b, 0xf2, 0x77, 0xe2, 0x69, 0x89, 0xc0,
        0xc3, 0x1a, 0xb5, 0x04, 0x03, 0x38, 0x52, 0x8a,
        0x7e, 0x4f, 0x03, 0x8d, 0x18, 0x7b, 0xf2, 0x7c};
    static const uint8_t g2y[32] = {
        0xd1, 0x73, 0x78, 0x22, 0x9d, 0xb7, 0x04, 0x9e,
        0x29, 0x82, 0xe9, 0x3c, 0xe6, 0xad, 0x7d, 0xba,
        0xdb, 0x30, 0x74, 0x9f, 0xc6, 0x9a, 0x3d, 0x29,
        0x40, 0xd0, 0x8e, 0xdb, 0x10, 0x55, 0x77, 0x07};
    static const uint8_t d1[32] = {
        0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    static const uint8_t d2[32] = {
        0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    uint8_t rx[32], ry[32];

    /* Test 1: BaseMult d=1 -> G */
    HAL_OTBN_P256_BaseMult_Polling(d1, rx, ry);
    check_u8_eq(rx, gx, 32, "base_mult d=1 -> Gx", r);
    check_u8_eq(ry, gy, 32, "base_mult d=1 -> Gy", r);

    /* Test 2: BaseMult d=2 -> 2G */
    HAL_OTBN_P256_BaseMult_Polling(d2, rx, ry);
    check_u8_eq(rx, g2x, 32, "base_mult d=2 -> 2Gx", r);
    check_u8_eq(ry, g2y, 32, "base_mult d=2 -> 2Gy", r);

    /* Test 3: ScalarMult d=1, P=G -> G */
    HAL_OTBN_P256_ScalarMult_Polling(d1, gx, gy, rx, ry);
    check_u8_eq(rx, gx, 32, "scalar_mult d=1, P=G -> Gx", r);
    check_u8_eq(ry, gy, 32, "scalar_mult d=1, P=G -> Gy", r);

    /* Test 4: PointAdd G + G -> 2G */
    HAL_OTBN_P256_PointAdd_Polling(gx, gy, gx, gy, rx, ry);
    check_u8_eq(rx, g2x, 32, "point_add G+G -> 2Gx", r);
    check_u8_eq(ry, g2y, 32, "point_add G+G -> 2Gy", r);
}

/* ======================================================================== */
/* 08. ecc_p384 tests                                                       */
/* ======================================================================== */

static void test_ecc_p384(test_result_t *r) {
    LOG_I("--- 08. ecc_p384 ---");

    static const uint8_t gx[48] = {
        0xb7, 0x0a, 0x76, 0x72, 0x38, 0x5e, 0x54, 0x3a,
        0x6c, 0x29, 0x55, 0xbf, 0x5d, 0xf2, 0x02, 0x55,
        0x38, 0x2a, 0x54, 0x82, 0xe0, 0x41, 0xf7, 0x59,
        0x98, 0x9b, 0xa7, 0x8b, 0x62, 0x3b, 0x1d, 0x6e,
        0x74, 0xad, 0x20, 0xf3, 0x1e, 0xc7, 0xb1, 0x8e,
        0x37, 0x05, 0x8b, 0xbe, 0x22, 0xca, 0x87, 0xaa};
    static const uint8_t gy[48] = {
        0x5f, 0x0e, 0xea, 0x90, 0x7c, 0x1d, 0x43, 0x7a,
        0x9d, 0x81, 0x7e, 0x1d, 0xce, 0xb1, 0x60, 0x0a,
        0xc0, 0xb8, 0xf0, 0xb5, 0x13, 0x31, 0xda, 0xe9,
        0x7c, 0x14, 0x9a, 0x28, 0xbd, 0x1d, 0xf4, 0xf8,
        0x29, 0xdc, 0x92, 0x92, 0xbf, 0x98, 0x9e, 0x5d,
        0x6f, 0x2c, 0x26, 0x96, 0x4a, 0xde, 0x17, 0x36};
    static const uint8_t g2x[48] = {
        0x61, 0xdf, 0x95, 0x52, 0xc7, 0xa9, 0x96, 0x5b,
        0xf8, 0x64, 0x0e, 0xbe, 0x6e, 0xe8, 0xe0, 0x4f,
        0x9e, 0x6e, 0xb9, 0x9f, 0xd1, 0x07, 0xd2, 0x51,
        0xd6, 0x34, 0xf4, 0xa6, 0x59, 0x59, 0x02, 0x89,
        0xf0, 0x97, 0x5b, 0xc5, 0x45, 0x00, 0x26, 0x69,
        0xd9, 0xd2, 0xa3, 0x7b, 0x05, 0x99, 0xd9, 0x08};
    static const uint8_t g2y[48] = {
        0x80, 0x0e, 0x94, 0x0a, 0x70, 0x1e, 0x50, 0x61,
        0x2d, 0xe2, 0x39, 0x4d, 0xe9, 0x43, 0xfd, 0x5f,
        0x25, 0xb4, 0x6a, 0x25, 0x5f, 0x50, 0x4e, 0x90,
        0x3e, 0xc4, 0x6c, 0xbc, 0x75, 0xd8, 0x75, 0xb2,
        0x74, 0xba, 0x6d, 0xfd, 0xdf, 0xe8, 0xbf, 0xb7,
        0xed, 0x3c, 0x1b, 0x5b, 0xfa, 0xf1, 0x80, 0x8e};
    static const uint8_t d1[48] = {
        0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    static const uint8_t d2[48] = {
        0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    uint8_t rx[48], ry[48];

    /* Test 1: BaseMult d=1 -> G */
    HAL_OTBN_P384_BaseMult_Polling(d1, rx, ry);
    check_u8_eq(rx, gx, 48, "base_mult d=1 -> Gx", r);
    check_u8_eq(ry, gy, 48, "base_mult d=1 -> Gy", r);

    /* Test 2: BaseMult d=2 -> 2G */
    HAL_OTBN_P384_BaseMult_Polling(d2, rx, ry);
    check_u8_eq(rx, g2x, 48, "base_mult d=2 -> 2Gx", r);
    check_u8_eq(ry, g2y, 48, "base_mult d=2 -> 2Gy", r);

    /* Test 3: ScalarMult d=1, P=G -> G */
    HAL_OTBN_P384_ScalarMult_Polling(d1, gx, gy, rx, ry);
    check_u8_eq(rx, gx, 48, "scalar_mult d=1, P=G -> Gx", r);
    check_u8_eq(ry, gy, 48, "scalar_mult d=1, P=G -> Gy", r);

    /* Test 4: PointAdd G + G -> 2G */
    HAL_OTBN_P384_PointAdd_Polling(gx, gy, gx, gy, rx, ry);
    check_u8_eq(rx, g2x, 48, "point_add G+G -> 2Gx", r);
    check_u8_eq(ry, g2y, 48, "point_add G+G -> 2Gy", r);
}

/* ======================================================================== */
/* 09. ecc_p521 tests                                                       */
/* ======================================================================== */
extern const uint8_t g_ecc_p521_imem[];
extern const uint32_t g_ecc_p521_imem_size;
static void test_ecc_p521(test_result_t *r) {
  LOG_I("--- 09. ecc_p521 ---");
  /* P-521 G (little-endian, 66 bytes) */
  static const uint8_t gx[66] = {
    0x66, 0xbd, 0xe5, 0xc2, 0x31, 0x7e, 0x7e, 0xf9,
    0x9b, 0x42, 0x6a, 0x85, 0xc1, 0xb3, 0x48, 0x33,
    0xde, 0xa8, 0xff, 0xa2, 0x27, 0xc1, 0x1d, 0xfe,
    0x28, 0x59, 0xe7, 0xef, 0x77, 0x5e, 0x4b, 0xa1,
    0xba, 0x3d, 0x4d, 0x6b, 0x60, 0xaf, 0x28, 0xf8,
    0x21, 0xb5, 0x3f, 0x05, 0x39, 0x81, 0x64, 0x9c,
    0x42, 0xb4, 0x95, 0x23, 0x66, 0xcb, 0x3e, 0x9e,
    0xcd, 0xe9, 0x04, 0x04, 0xb7, 0x06, 0x8e, 0x85,
    0xc6, 0x00};
  static const uint8_t gy[66] = {
    0x50, 0x66, 0xd1, 0x9f, 0x76, 0x94, 0xbe, 0x88,
    0x40, 0xc2, 0x72, 0xa2, 0x86, 0x70, 0x3c, 0x35,
    0x61, 0x07, 0xad, 0x3f, 0x01, 0xb9, 0x50, 0xc5,
    0x40, 0x26, 0xf4, 0x5e, 0x99, 0x72, 0xee, 0x97,
    0x2c, 0x66, 0x3e, 0x27, 0x17, 0xbd, 0xaf, 0x17,
    0x68, 0x44, 0x9b, 0x57, 0x49, 0x44, 0xf5, 0x98,
    0xd9, 0x1b, 0x7d, 0x2c, 0xb4, 0x5f, 0x8a, 0x5c,
    0x04, 0xc0, 0x3b, 0x9a, 0x78, 0x6a, 0x29, 0x39,
    0x18, 0x01};
  static const uint8_t g2x[66] = {
    0x3d, 0x78, 0x6d, 0xba, 0x33, 0x39, 0x3e, 0xf4,
    0x67, 0xd9, 0x0f, 0xd6, 0x64, 0xa3, 0x2f, 0xcf,
    0x41, 0xaf, 0xc5, 0x35, 0x3a, 0x4a, 0x10, 0xaa,
    0x07, 0x55, 0xf5, 0x6e, 0xda, 0x04, 0xb2, 0xb3,
    0x97, 0xbe, 0x69, 0xd7, 0x05, 0x55, 0x6e, 0x2c,
    0x35, 0x06, 0xcc, 0x1c, 0x9b, 0x27, 0x03, 0x74,
    0x74, 0x82, 0xc2, 0x48, 0x81, 0x28, 0xcb, 0x2f,
    0x68, 0x7e, 0x7e, 0x27, 0x24, 0x90, 0x21, 0x3c,
    0x43, 0x00};
  static const uint8_t g2y[66] = {
    0x02, 0x1b, 0xf4, 0x61, 0xd6, 0x56, 0xe3, 0x1b,
    0xf7, 0xf4, 0xc0, 0xed, 0x95, 0xbe, 0xfc, 0xea,
    0xf4, 0x48, 0x32, 0x9a, 0xa9, 0x7f, 0x93, 0x93,
    0x6b, 0x1f, 0x25, 0x9f, 0xde, 0x77, 0xe3, 0xb3,
    0xbb, 0x2d, 0xc4, 0x06, 0x99, 0xa2, 0x21, 0xab,
    0x40, 0x77, 0xa9, 0x4d, 0x7c, 0x10, 0xb5, 0xc6,
    0xb5, 0xf0, 0xd3, 0xee, 0xee, 0xec, 0xf3, 0xa7,
    0x00, 0x67, 0xb2, 0x6d, 0xf8, 0xc7, 0x8c, 0xbb,
    0xf4, 0x00};
  static const uint8_t d1[66] = {
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00};
  static const uint8_t d2[66] = {
    0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00};

  uint8_t rx[66], ry[66];

  /* Test 1: BaseMult d=1 -> G */
  HAL_OTBN_P521_BaseMult_Polling(d1, rx, ry);
  check_u8_eq(rx, gx, 66, "base_mult d=1 -> Gx", r);
  check_u8_eq(ry, gy, 66, "base_mult d=1 -> Gy", r);

  /* Test 2: BaseMult d=2 -> 2G */
  HAL_OTBN_P521_BaseMult_Polling(d2, rx, ry);
  check_u8_eq(rx, g2x, 66, "base_mult d=2 -> 2Gx", r);
  check_u8_eq(ry, g2y, 66, "base_mult d=2 -> 2Gy", r);

  /* Test 3: ScalarMult d=1, P=G -> G */
  HAL_OTBN_P521_ScalarMult_Polling(d1, gx, gy, rx, ry);
  check_u8_eq(rx, gx, 66, "scalar_mult d=1, P=G -> Gx", r);
  check_u8_eq(ry, gy, 66, "scalar_mult d=1, P=G -> Gy", r);

  /* Test 4: PointAdd G + G -> 2G */
  HAL_OTBN_P521_PointAdd_Polling(gx, gy, gx, gy, rx, ry);
  check_u8_eq(rx, g2x, 66, "point_add G+G -> 2Gx", r);
  check_u8_eq(ry, g2y, 66, "point_add G+G -> 2Gy", r);
}
/* ======================================================================== */
/* 10. ecc_sm2 tests                                                        */
/* ======================================================================== */

static void test_ecc_sm2(test_result_t *r) {
    LOG_I("--- 10. ecc_sm2 ---");

    static const uint8_t gx[32] = {
        0xc7, 0x74, 0x4c, 0x33, 0x89, 0x45, 0x5a, 0x71,
        0xe1, 0x0b, 0x66, 0xf2, 0xbf, 0x0b, 0xe3, 0x8f,
        0x94, 0xc9, 0x39, 0x6a, 0x46, 0x04, 0x99, 0x5f,
        0x19, 0x81, 0x19, 0x1f, 0x2c, 0xae, 0xc4, 0x32};
    static const uint8_t gy[32] = {
        0xa0, 0xf0, 0x39, 0x21, 0xe5, 0x32, 0xdf, 0x02,
        0x40, 0x47, 0x2a, 0xc6, 0x7c, 0x87, 0xa9, 0xd0,
        0x53, 0x21, 0x69, 0x6b, 0xe3, 0xce, 0xbd, 0x59,
        0x9c, 0x77, 0xf6, 0xf4, 0xa2, 0x36, 0x37, 0xbc};
    static const uint8_t g2x[32] = {
        0x52, 0xbd, 0xf2, 0xa3, 0x1d, 0x2e, 0x5c, 0x49,
        0x31, 0x73, 0x8a, 0xc0, 0x08, 0xfa, 0x0d, 0x9c,
        0x4d, 0xba, 0x73, 0xfa, 0x57, 0xef, 0x58, 0x0d,
        0x00, 0x7c, 0xc8, 0xd7, 0x60, 0xfd, 0xce, 0x56};
    static const uint8_t g2y[32] = {
        0xc3, 0x23, 0x0a, 0x97, 0x3a, 0x0d, 0x78, 0x6f,
        0x71, 0x8e, 0x6c, 0x2f, 0x18, 0x4c, 0xe8, 0x6d,
        0xbd, 0xf1, 0xea, 0xf8, 0xe0, 0x5c, 0x53, 0x68,
        0xf6, 0x89, 0x81, 0xcc, 0xe6, 0xe7, 0xb7, 0x31};
    static const uint8_t d1[32] = {
        0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    static const uint8_t d2[32] = {
        0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    uint8_t rx[32], ry[32];

    /* Test 1: BaseMult d=1 -> G */
    HAL_OTBN_SM2_BaseMult_Polling(d1, rx, ry);
    check_u8_eq(rx, gx, 32, "base_mult d=1 -> Gx", r);
    check_u8_eq(ry, gy, 32, "base_mult d=1 -> Gy", r);

    /* Test 2: BaseMult d=2 -> 2G */
    HAL_OTBN_SM2_BaseMult_Polling(d2, rx, ry);
    check_u8_eq(rx, g2x, 32, "base_mult d=2 -> 2Gx", r);
    check_u8_eq(ry, g2y, 32, "base_mult d=2 -> 2Gy", r);

    /* Test 3: ScalarMult d=1, P=G -> G */
    HAL_OTBN_SM2_ScalarMult_Polling(d1, gx, gy, rx, ry);
    check_u8_eq(rx, gx, 32, "scalar_mult d=1, P=G -> Gx", r);
    check_u8_eq(ry, gy, 32, "scalar_mult d=1, P=G -> Gy", r);

    /* Test 4: PointAdd G + G -> 2G */
    HAL_OTBN_SM2_PointAdd_Polling(gx, gy, gx, gy, rx, ry);
    check_u8_eq(rx, g2x, 32, "point_add G+G -> 2Gx", r);
    check_u8_eq(ry, g2y, 32, "point_add G+G -> 2Gy", r);
}

/* ======================================================================== */
/* 11. ecc_p256_isoncurve tests                                             */
/* ======================================================================== */

static void test_ecc_p256_isoncurve(test_result_t *r) {
    LOG_I("--- 11. ecc_p256_isoncurve ---");

    static const uint8_t gx[32] = {
        0x96, 0xc2, 0x98, 0xd8, 0x45, 0x39, 0xa1, 0xf4,
        0xa0, 0x33, 0xeb, 0x2d, 0x81, 0x7d, 0x03, 0x77,
        0xf2, 0x40, 0xa4, 0x63, 0xe5, 0xe6, 0xbc, 0xf8,
        0x47, 0x42, 0x2c, 0xe1, 0xf2, 0xd1, 0x17, 0x6b};
    static const uint8_t gy[32] = {
        0xf5, 0x51, 0xbf, 0x37, 0x68, 0x40, 0xb6, 0xcb,
        0xce, 0x5e, 0x31, 0x6b, 0x57, 0x33, 0xce, 0x2b,
        0x16, 0x9e, 0x0f, 0x7c, 0x4a, 0xeb, 0xe7, 0x8e,
        0x9b, 0x7f, 0x1a, 0xfe, 0xe2, 0x42, 0xe3, 0x4f};
    static const uint8_t bad_y[32] = {
        0xf6, 0x51, 0xbf, 0x37, 0x68, 0x40, 0xb6, 0xcb,
        0xce, 0x5e, 0x31, 0x6b, 0x57, 0x33, 0xce, 0x2b,
        0x16, 0x9e, 0x0f, 0x7c, 0x4a, 0xeb, 0xe7, 0x8e,
        0x9b, 0x7f, 0x1a, 0xfe, 0xe2, 0x42, 0xe3, 0x4f};

    bool ok = HAL_OTBN_P256_ValidatePoint_Polling(gx, gy);
    check_bool(ok, true, "G is on curve", r);

    ok = HAL_OTBN_P256_ValidatePoint_Polling(gx, bad_y);
    check_bool(ok, false, "bad Y is not on curve", r);
}

/* ======================================================================== */
/* 12. ecc_p384_isoncurve tests                                             */
/* ======================================================================== */

static void test_ecc_p384_isoncurve(test_result_t *r) {
    LOG_I("--- 12. ecc_p384_isoncurve ---");

    static const uint8_t gx[48] = {
        0xb7, 0x0a, 0x76, 0x72, 0x38, 0x5e, 0x54, 0x3a,
        0x6c, 0x29, 0x55, 0xbf, 0x5d, 0xf2, 0x02, 0x55,
        0x38, 0x2a, 0x54, 0x82, 0xe0, 0x41, 0xf7, 0x59,
        0x98, 0x9b, 0xa7, 0x8b, 0x62, 0x3b, 0x1d, 0x6e,
        0x74, 0xad, 0x20, 0xf3, 0x1e, 0xc7, 0xb1, 0x8e,
        0x37, 0x05, 0x8b, 0xbe, 0x22, 0xca, 0x87, 0xaa};
    static const uint8_t gy[48] = {
        0x5f, 0x0e, 0xea, 0x90, 0x7c, 0x1d, 0x43, 0x7a,
        0x9d, 0x81, 0x7e, 0x1d, 0xce, 0xb1, 0x60, 0x0a,
        0xc0, 0xb8, 0xf0, 0xb5, 0x13, 0x31, 0xda, 0xe9,
        0x7c, 0x14, 0x9a, 0x28, 0xbd, 0x1d, 0xf4, 0xf8,
        0x29, 0xdc, 0x92, 0x92, 0xbf, 0x98, 0x9e, 0x5d,
        0x6f, 0x2c, 0x26, 0x96, 0x4a, 0xde, 0x17, 0x36};
    static const uint8_t bad_y[48] = {
        0x60, 0x0e, 0xea, 0x90, 0x7c, 0x1d, 0x43, 0x7a,
        0x9d, 0x81, 0x7e, 0x1d, 0xce, 0xb1, 0x60, 0x0a,
        0xc0, 0xb8, 0xf0, 0xb5, 0x13, 0x31, 0xda, 0xe9,
        0x7c, 0x14, 0x9a, 0x28, 0xbd, 0x1d, 0xf4, 0xf8,
        0x29, 0xdc, 0x92, 0x92, 0xbf, 0x98, 0x9e, 0x5d,
        0x6f, 0x2c, 0x26, 0x96, 0x4a, 0xde, 0x17, 0x36};

    bool ok = HAL_OTBN_P384_ValidatePoint_Polling(gx, gy);
    check_bool(ok, true, "G is on curve", r);

    ok = HAL_OTBN_P384_ValidatePoint_Polling(gx, bad_y);
    check_bool(ok, false, "bad Y is not on curve", r);
}

/* ======================================================================== */
/* 13. ecc_sm2_isoncurve tests                                              */
/* ======================================================================== */

static void test_ecc_sm2_isoncurve(test_result_t *r) {
    LOG_I("--- 13. ecc_sm2_isoncurve ---");

    static const uint8_t gx[32] = {
        0xc7, 0x74, 0x4c, 0x33, 0x89, 0x45, 0x5a, 0x71,
        0xe1, 0x0b, 0x66, 0xf2, 0xbf, 0x0b, 0xe3, 0x8f,
        0x94, 0xc9, 0x39, 0x6a, 0x46, 0x04, 0x99, 0x5f,
        0x19, 0x81, 0x19, 0x1f, 0x2c, 0xae, 0xc4, 0x32};
    static const uint8_t gy[32] = {
        0xa0, 0xf0, 0x39, 0x21, 0xe5, 0x32, 0xdf, 0x02,
        0x40, 0x47, 0x2a, 0xc6, 0x7c, 0x87, 0xa9, 0xd0,
        0x53, 0x21, 0x69, 0x6b, 0xe3, 0xce, 0xbd, 0x59,
        0x9c, 0x77, 0xf6, 0xf4, 0xa2, 0x36, 0x37, 0xbc};
    static const uint8_t bad_y[32] = {
        0xa1, 0xf0, 0x39, 0x21, 0xe5, 0x32, 0xdf, 0x02,
        0x40, 0x47, 0x2a, 0xc6, 0x7c, 0x87, 0xa9, 0xd0,
        0x53, 0x21, 0x69, 0x6b, 0xe3, 0xce, 0xbd, 0x59,
        0x9c, 0x77, 0xf6, 0xf4, 0xa2, 0x36, 0x37, 0xbc};

    bool ok = HAL_OTBN_SM2_ValidatePoint_Polling(gx, gy);
    check_bool(ok, true, "G is on curve", r);

    ok = HAL_OTBN_SM2_ValidatePoint_Polling(gx, bad_y);
    check_bool(ok, false, "bad Y is not on curve", r);
}

/* ======================================================================== */
/* Main                                                                     */
/* ======================================================================== */

int main(void) {
    test_result_t total = {0, 0, 0};
    test_result_t r;

    sys_init_none();
    HAL_OTBN_Init();

    LOG_I("========================================");
    LOG_I("ls_otbn Unified Test Suite");
    LOG_I("========================================");

    /* 01. bn_mul */
    result_reset(&r);
    test_bn_mul(&r);
    result_print(&r, "bn_mul");
    total.passed += r.passed; total.failed += r.failed; total.skipped += r.skipped;

    /* 02. bn_div */
    result_reset(&r);
    test_bn_div(&r);
    result_print(&r, "bn_div");
    total.passed += r.passed; total.failed += r.failed; total.skipped += r.skipped;

    /* 03. bn_modmult */
    result_reset(&r);
    test_bn_modmult(&r);
    result_print(&r, "bn_modmult");
    total.passed += r.passed; total.failed += r.failed; total.skipped += r.skipped;

    /* 04. bn_gcd */
    result_reset(&r);
    test_bn_gcd(&r);
    result_print(&r, "bn_gcd");
    total.passed += r.passed; total.failed += r.failed; total.skipped += r.skipped;

    /* 05. bn_modexp */
    result_reset(&r);
    test_bn_modexp(&r);
    result_print(&r, "bn_modexp");
    total.passed += r.passed; total.failed += r.failed; total.skipped += r.skipped;

    /* 06. bn_modinv */
    result_reset(&r);
    test_bn_modinv(&r);
    result_print(&r, "bn_modinv");
    total.passed += r.passed; total.failed += r.failed; total.skipped += r.skipped;

    /* 07. ecc_p256 */
    result_reset(&r);
    test_ecc_p256(&r);
    result_print(&r, "ecc_p256");
    total.passed += r.passed; total.failed += r.failed; total.skipped += r.skipped;

    /* 08. ecc_p384 */
    result_reset(&r);
    test_ecc_p384(&r);
    result_print(&r, "ecc_p384");
    total.passed += r.passed; total.failed += r.failed; total.skipped += r.skipped;

    /* 09. ecc_p521 */
    result_reset(&r);
    test_ecc_p521(&r);
    result_print(&r, "ecc_p521");
    total.passed += r.passed; total.failed += r.failed; total.skipped += r.skipped;

    /* 10. ecc_sm2 */
    result_reset(&r);
    test_ecc_sm2(&r);
    result_print(&r, "ecc_sm2");
    total.passed += r.passed; total.failed += r.failed; total.skipped += r.skipped;

    /* 11. ecc_p256_isoncurve */
    result_reset(&r);
    test_ecc_p256_isoncurve(&r);
    result_print(&r, "ecc_p256_isoncurve");
    total.passed += r.passed; total.failed += r.failed; total.skipped += r.skipped;

    /* 12. ecc_p384_isoncurve */
    result_reset(&r);
    test_ecc_p384_isoncurve(&r);
    result_print(&r, "ecc_p384_isoncurve");
    total.passed += r.passed; total.failed += r.failed; total.skipped += r.skipped;

    /* 13. ecc_sm2_isoncurve */
    result_reset(&r);
    test_ecc_sm2_isoncurve(&r);
    result_print(&r, "ecc_sm2_isoncurve");
    total.passed += r.passed; total.failed += r.failed; total.skipped += r.skipped;

    LOG_I("========================================");
    LOG_I("TOTAL: %u passed, %u failed, %u skipped",
          (unsigned)total.passed, (unsigned)total.failed, (unsigned)total.skipped);
    LOG_I("========================================");

    while (1) {
    }

    return (total.failed > 0) ? 1 : 0;
}
