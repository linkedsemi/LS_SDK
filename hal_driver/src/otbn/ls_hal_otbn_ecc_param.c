/**
 * @file ls_hal_otbn_ecc_param.c
 * @brief ECC input parameter validation for the OTBN HAL layer.
 *
 * See ls_hal_otbn_ecc.h for the rationale: these are the checks
 * upstream wolfSSL / mbedTLS apply to ECC inputs, re-implemented inside
 * the HAL so out-of-range scalars and off-curve points never reach the
 * OTBN firmware (whose behaviour on invalid inputs is undefined and has
 * been observed to hang).
 *
 * Arithmetic is plain schoolbook big-number code over 32-bit words,
 * least-significant-word first (the OTBN DMEM representation).  The
 * modular reduction is a deliberately simple binary shift-and-subtract
 * loop: it is correct for any modulus and the validation path is not
 * performance critical (a handful of field ops per call).
 */

#include "ls_hal_otbn_ecc.h"
#include <string.h>

#define LS_OTBN_ECC_MAX_WORDS 12   /* P-384 is the largest curve */

/* ------------------------------------------------------------------
 * Curve parameters (same values as the OTBN firmware curve tables in
 * ls_hal_otbn_ecc256.c / ls_hal_otbn_ecc384.c / ls_hal_otbn_sm2.c),
 * stored least-significant-word first.
 * a == -3 for P-256, SM2 and P-384.
 * ------------------------------------------------------------------ */
static const uint32_t P256_P[8] = {
    0xffffffff, 0xffffffff, 0xffffffff, 0x00000000,
    0x00000000, 0x00000000, 0x00000001, 0xffffffff};
static const uint32_t P256_N[8] = {
    0xfc632551, 0xf3b9cac2, 0xa7179e84, 0xbce6faad,
    0xffffffff, 0xffffffff, 0x00000000, 0xffffffff};
static const uint32_t P256_B[8] = {
    0x27d2604b, 0x3bce3c3e, 0xcc53b0f6, 0x651d06b0,
    0x769886bc, 0xb3ebbd55, 0xaa3a93e7, 0x5ac635d8};

static const uint32_t SM2_P[8] = {
    0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFE};
static const uint32_t SM2_N[8] = {
    0x39D54123, 0x53BBF409, 0x21C6052B, 0x7203DF6B,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFE};
static const uint32_t SM2_B[8] = {
    0x4D940E93, 0xDDBCBD41, 0x15AB8F92, 0xF39789F5,
    0xCF6509A7, 0x4D5A9E4B, 0x9D9F5E34, 0x28E9FA9E};

static const uint32_t P384_P[12] = {
    0xffffffff, 0x00000000, 0x00000000, 0xffffffff,
    0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff,
    0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff};
static const uint32_t P384_N[12] = {
    0xccc52973, 0xecec196a, 0x48b0a77a, 0x581a0db2,
    0xf4372ddf, 0xc7634d81, 0xffffffff, 0xffffffff,
    0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff};
static const uint32_t P384_B[12] = {
    0xd3ec2aef, 0x2a85c8ed, 0x8a2ed19d, 0xc656398d,
    0x5013875a, 0x0314088f, 0xfe814112, 0x181d9c6e,
    0xe3f82d19, 0x988e056b, 0xe23ee7e4, 0xb3312fa7};

struct ls_otbn_ecc_curve_param {
    uint32_t nwords;            /* words per component */
    const uint32_t *p;          /* field modulus, LSW first */
    const uint32_t *n;          /* group order, LSW first */
    const uint32_t *b;          /* curve constant, LSW first */
};

static const struct ls_otbn_ecc_curve_param g_curves[3] = {
    [LS_OTBN_ECC_CURVE_P256] = { 8, P256_P, P256_N, P256_B },
    [LS_OTBN_ECC_CURVE_SM2]  = { 8, SM2_P, SM2_N, SM2_B },
    [LS_OTBN_ECC_CURVE_P384] = { 12, P384_P, P384_N, P384_B },
};

static const struct ls_otbn_ecc_curve_param *curve_get(int curve)
{
    if ((uint32_t)curve >= 3)
        return NULL;
    return &g_curves[curve];
}

/* ------------------------------------------------------------------
 * Word-level helpers.  All arrays are LSW-first unless noted.
 * ------------------------------------------------------------------ */

static bool bn_is_zero(const uint32_t *a, uint32_t nw)
{
    for (uint32_t i = 0; i < nw; i++)
        if (a[i])
            return false;
    return true;
}

/* -1 / 0 / 1 */
static int32_t bn_cmp(const uint32_t *a, const uint32_t *b, uint32_t nw)
{
    for (uint32_t i = nw; i > 0; i--) {
        if (a[i - 1] != b[i - 1])
            return a[i - 1] < b[i - 1] ? -1 : 1;
    }
    return 0;
}

/* a -= b; caller guarantees a >= b */
static void bn_sub(uint32_t *a, const uint32_t *b, uint32_t nw)
{
    uint64_t borrow = 0;
    for (uint32_t i = 0; i < nw; i++) {
        uint64_t bb = (uint64_t)b[i] + borrow;
        if (a[i] < bb) {
            a[i] = (uint32_t)((uint64_t)a[i] + (1ull << 32) - bb);
            borrow = 1;
        } else {
            a[i] = (uint32_t)(a[i] - bb);
            borrow = 0;
        }
    }
}

/* a += b; returns carry out (wraps mod 2^(32*nw)) */
static uint32_t bn_add(uint32_t *a, const uint32_t *b, uint32_t nw)
{
    uint64_t carry = 0;
    for (uint32_t i = 0; i < nw; i++) {
        uint64_t s = (uint64_t)a[i] + b[i] + carry;
        a[i] = (uint32_t)s;
        carry = s >> 32;
    }
    return (uint32_t)carry;
}

/* r[2*nw] = a * b (schoolbook).  r must not alias a or b. */
static void bn_mul(const uint32_t *a, const uint32_t *b, uint32_t *r, uint32_t nw)
{
    memset(r, 0, 2 * nw * sizeof(uint32_t));
    for (uint32_t i = 0; i < nw; i++) {
        uint64_t carry = 0;
        uint32_t *rp = &r[i];
        for (uint32_t j = 0; j < nw; j++) {
            uint64_t t = (uint64_t)a[i] * b[j] + rp[j] + carry;
            rp[j] = (uint32_t)t;
            carry = t >> 32;
        }
        for (uint32_t k = i + nw; carry; k++) {
            uint64_t t = (uint64_t)r[k] + carry;
            r[k] = (uint32_t)t;
            carry = t >> 32;
        }
    }
}

/* t (2*nw words, t < p^2) -> t mod p, result in the low nw words.
 * Binary shift-and-subtract long division: start with P = p << (32*nw),
 * so T < p^2 < p*2^(32*nw) = P.  Each step does "if R >= P: R -= P;
 * P >>= 1", which keeps R < 2P.  After 32*nw steps P == p and R < 2p;
 * one final conditional subtract finishes the reduction. */
static void bn_reduce(uint32_t *t, const uint32_t *p, uint32_t nw)
{
    const uint32_t tn = 2 * nw;
    uint32_t P[2 * LS_OTBN_ECC_MAX_WORDS];
    uint32_t R[2 * LS_OTBN_ECC_MAX_WORDS];

    memset(P, 0, sizeof(P));
    memset(R, 0, sizeof(R));
    memcpy(R, t, tn * sizeof(uint32_t));
    memcpy(&P[nw], p, nw * sizeof(uint32_t));

    for (uint32_t k = nw * 32; k > 0; k--) {
        if (bn_cmp(R, P, tn) >= 0)
            bn_sub(R, P, tn);
        /* P >>= 1 */
        uint32_t carry = 0;
        for (uint32_t i = tn; i > 0; i--) {
            uint32_t next = P[i - 1] & 1u;
            P[i - 1] = (P[i - 1] >> 1) | (carry << 31);
            carry = next;
        }
    }
    /* R < 2p here and (since 2p > 2^(32*nw) for these primes) may carry
     * into word nw; compare/subtract over the full 2*nw words with p
     * zero-extended */
    {
        uint32_t pe[2 * LS_OTBN_ECC_MAX_WORDS];
        memset(pe, 0, sizeof(pe));
        memcpy(pe, p, nw * sizeof(uint32_t));
        if (bn_cmp(R, pe, tn) >= 0)
            bn_sub(R, pe, tn);
    }

    memcpy(t, R, nw * sizeof(uint32_t));
}

/* r = (a + b) mod p; a,b < p */
static void bn_mod_add(uint32_t *r, const uint32_t *a, const uint32_t *b,
                       const uint32_t *p, uint32_t nw)
{
    memcpy(r, a, nw * sizeof(uint32_t));
    uint32_t carry = bn_add(r, b, nw);
    if (carry) {
        /* The true sum is r + 2^(32*nw); the wrap lost that bit, so add
         * it back mod p.  For all supported curves p < 2^(32*nw) < 2p,
         * hence 2^(32*nw) mod p == 2^(32*nw) - p == ~p + 1 (mod 2^32nw).
         * r + (2^(32*nw) - p) < 2^(32*nw), so no second carry out. */
        uint32_t c[LS_OTBN_ECC_MAX_WORDS];
        uint32_t cy = 1;
        for (uint32_t i = 0; i < nw; i++) {
            uint64_t s = (uint64_t)(~p[i]) + cy;
            c[i] = (uint32_t)s;
            cy = s >> 32;
        }
        (void)bn_add(r, c, nw);
        if (bn_cmp(r, p, nw) >= 0)
            bn_sub(r, p, nw);
    } else if (bn_cmp(r, p, nw) >= 0) {
        bn_sub(r, p, nw);
    }
}

/* r = (a - b) mod p; a,b < p */
static void bn_mod_sub(uint32_t *r, const uint32_t *a, const uint32_t *b,
                       const uint32_t *p, uint32_t nw)
{
    memcpy(r, a, nw * sizeof(uint32_t));
    if (bn_cmp(a, b, nw) >= 0) {
        bn_sub(r, b, nw);
    } else {
        /* a + p - b == p - (b - a) in [1, p-1]; the 2's-complement
         * wrap of bn_add/bn_sub computes it correctly mod 2^(32*nw),
         * and the true result fits in nw words. */
        (void)bn_add(r, p, nw);
        bn_sub(r, b, nw);
    }
}

/* Big-endian byte string -> LSW-first words. */
static void be_to_lsw(const uint8_t *be, uint32_t *lsw, uint32_t nw)
{
    for (uint32_t i = 0; i < nw; i++) {
        const uint8_t *b = be + (nw - 1 - i) * 4;
        lsw[i] = ((uint32_t)b[0] << 24) | ((uint32_t)b[1] << 16) |
                 ((uint32_t)b[2] << 8) | b[3];
    }
}

/* ------------------------------------------------------------------
 * Checks (upstream equivalents noted in the header).
 * ------------------------------------------------------------------ */

/* 1 <= scalar < n */
static bool scalar_in_range(const uint32_t *x, const struct ls_otbn_ecc_curve_param *c)
{
    if (bn_is_zero(x, c->nwords))
        return false;
    return bn_cmp(x, c->n, c->nwords) < 0;
}

/* x,y < p and y^2 == x^3 - 3x + b (mod p) */
static bool point_on_curve(const uint32_t *x, const uint32_t *y,
                           const struct ls_otbn_ecc_curve_param *c)
{
    const uint32_t nw = c->nwords;
    uint32_t t[2 * LS_OTBN_ECC_MAX_WORDS];
    uint32_t lhs[LS_OTBN_ECC_MAX_WORDS];
    uint32_t rhs[LS_OTBN_ECC_MAX_WORDS];
    uint32_t tmp[LS_OTBN_ECC_MAX_WORDS];

    if (bn_cmp(x, c->p, nw) >= 0 || bn_cmp(y, c->p, nw) >= 0)
        return false;

    /* lhs = y^2 mod p */
    bn_mul(y, y, t, nw);
    bn_reduce(t, c->p, nw);
    memcpy(lhs, t, nw * sizeof(uint32_t));

    /* rhs = x^3 mod p (bn_mul must not alias its output) */
    bn_mul(x, x, t, nw);
    bn_reduce(t, c->p, nw);
    memcpy(tmp, t, nw * sizeof(uint32_t));  /* tmp = x^2 mod p */
    bn_mul(tmp, x, t, nw);
    bn_reduce(t, c->p, nw);
    memcpy(rhs, t, nw * sizeof(uint32_t));

    /* rhs = x^3 - 3x + b mod p (a == -3 for all supported curves) */
    bn_mod_add(tmp, x, x, c->p, nw);      /* 2x */
    bn_mod_add(tmp, tmp, x, c->p, nw);    /* 3x */
    bn_mod_sub(rhs, rhs, tmp, c->p, nw);  /* x^3 - 3x */
    bn_mod_add(rhs, rhs, c->b, c->p, nw); /* + b */

    return memcmp(lhs, rhs, nw * sizeof(uint32_t)) == 0;
}

/* ------------------------------------------------------------------
 * Public API.
 * ------------------------------------------------------------------ */

bool ls_otbn_ecc_scalar_in_range(int curve, const uint8_t *scalar_be)
{
    const struct ls_otbn_ecc_curve_param *c = curve_get(curve);
    uint32_t x[LS_OTBN_ECC_MAX_WORDS];
    if (!c || !scalar_be)
        return false;
    be_to_lsw(scalar_be, x, c->nwords);
    return scalar_in_range(x, c);
}

bool ls_otbn_ecc_rs_in_range(int curve, const uint8_t *r_be, const uint8_t *s_be)
{
    const struct ls_otbn_ecc_curve_param *c = curve_get(curve);
    uint32_t x[LS_OTBN_ECC_MAX_WORDS];
    if (!c || !r_be || !s_be)
        return false;
    be_to_lsw(r_be, x, c->nwords);
    if (!scalar_in_range(x, c))
        return false;
    be_to_lsw(s_be, x, c->nwords);
    return scalar_in_range(x, c);
}

bool ls_otbn_ecc_point_on_curve(int curve, const uint8_t *x_be, const uint8_t *y_be)
{
    const struct ls_otbn_ecc_curve_param *c = curve_get(curve);
    uint32_t x[LS_OTBN_ECC_MAX_WORDS];
    uint32_t y[LS_OTBN_ECC_MAX_WORDS];
    if (!c || !x_be || !y_be)
        return false;
    be_to_lsw(x_be, x, c->nwords);
    be_to_lsw(y_be, y, c->nwords);
    return point_on_curve(x, y, c);
}

bool ls_otbn_ecc_scalar_in_range_u32(int curve, const uint32_t *scalar_lsw)
{
    const struct ls_otbn_ecc_curve_param *c = curve_get(curve);
    if (!c || !scalar_lsw)
        return false;
    return scalar_in_range(scalar_lsw, c);
}

bool ls_otbn_ecc_rs_in_range_u32(int curve, const uint32_t *r_lsw, const uint32_t *s_lsw)
{
    const struct ls_otbn_ecc_curve_param *c = curve_get(curve);
    if (!c || !r_lsw || !s_lsw)
        return false;
    if (!scalar_in_range(r_lsw, c))
        return false;
    return scalar_in_range(s_lsw, c);
}

bool ls_otbn_ecc_point_on_curve_u32(int curve, const uint32_t *x_lsw, const uint32_t *y_lsw)
{
    const struct ls_otbn_ecc_curve_param *c = curve_get(curve);
    if (!c || !x_lsw || !y_lsw)
        return false;
    return point_on_curve(x_lsw, y_lsw, c);
}
