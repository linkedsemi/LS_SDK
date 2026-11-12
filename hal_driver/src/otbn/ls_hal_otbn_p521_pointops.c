/* Auto-generated HAL implementation for ecc_p521 atomic operations */
#include "ls_hal_otbn_p521_pointops.h"
#include "ls_hal_otbn.h"
#include "ls_hal_otbn.h"
#include <string.h>
#include "ls_hal_otbn.h"

/* ========================================================================== */
/* P-521 curve parameters                                                     */
/* ========================================================================== */

/* P-521 modulus: p = 2^521 - 1, stored as 66 bytes little-endian.
 * Bytes 0-64 are all 0xFF, byte 65 is 0x01. */
static const uint8_t p521_p[66] = {
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
    0xff,0x01
};

/* Base point G (66 bytes LE) */
static const uint8_t p521_gx[66] = {
    0x66,0xbd,0xe5,0xc2,0x31,0x7e,0x7e,0xf9, 0x9b,0x42,0x6a,0x85,0xc1,0xb3,0x48,0x33,
    0xde,0xa8,0xff,0xa2,0x27,0xc1,0x1d,0xfe, 0x28,0x59,0xe7,0xef,0x77,0x5e,0x4b,0xa1,
    0xba,0x3d,0x4d,0x6b,0x60,0xaf,0x28,0xf8, 0x21,0xb5,0x3f,0x05,0x39,0x81,0x64,0x9c,
    0x42,0xb4,0x95,0x23,0x66,0xcb,0x3e,0x9e, 0xcd,0xe9,0x04,0x04,0xb7,0x06,0x8e,0x85,
    0xc6,0x00
};

static const uint8_t p521_gy[66] = {
    0x50,0x66,0xd1,0x9f,0x76,0x94,0xbe,0x88, 0x40,0xc2,0x72,0xa2,0x86,0x70,0x3c,0x35,
    0x61,0x07,0xad,0x3f,0x01,0xb9,0x50,0xc5, 0x40,0x26,0xf4,0x5e,0x99,0x72,0xee,0x97,
    0x2c,0x66,0x3e,0x27,0x17,0xbd,0xaf,0x17, 0x68,0x44,0x9b,0x57,0x49,0x44,0xf5,0x98,
    0xd9,0x1b,0x7d,0x2c,0xb4,0x5f,0x8a,0x5c, 0x04,0xc0,0x3b,0x9a,0x78,0x6a,0x29,0x39,
    0x18,0x01
};

static const uint8_t p521_one[66] = {
    0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00
};

/* ========================================================================== */
/* P-521 field arithmetic in C (for Jacobian->affine conversion)              */
/* ========================================================================== */

/* result = (a + b) mod p, where a,b < p (66 bytes LE) */
static void p521_add_mod(uint8_t *result, const uint8_t *a, const uint8_t *b)
{
    uint16_t carry = 0;
    for (int i = 0; i < 66; i++) {
        uint16_t sum = (uint16_t)a[i] + b[i] + carry;
        result[i] = (uint8_t)sum;
        carry = sum >> 8;
    }
    if (carry) {
        /* result >= 2^521, need result -= p = result - (2^521-1) = result - 2^521 + 1 */
        uint16_t borrow = 1;
        for (int i = 0; i < 66; i++) {
            uint16_t diff = (uint16_t)result[i] - borrow;
            result[i] = (uint8_t)diff;
            borrow = (diff >> 8) & 1;
        }
    }
}

/* result = (a - b) mod p, where a,b < p (66 bytes LE) */
static void p521_sub_mod(uint8_t *result, const uint8_t *a, const uint8_t *b)
{
    uint16_t borrow = 0;
    for (int i = 0; i < 66; i++) {
        uint16_t diff = (uint16_t)a[i] - b[i] - borrow;
        result[i] = (uint8_t)diff;
        borrow = (diff >> 15) & 1;
    }
    if (borrow) {
        uint16_t carry = 0;
        for (int i = 0; i < 66; i++) {
            uint16_t sum = (uint16_t)result[i] + p521_p[i] + carry;
            result[i] = (uint8_t)sum;
            carry = sum >> 8;
        }
    }
}

/* result = (a * b) mod p, where a,b < p (66 bytes LE) */
static void p521_mul_mod(uint8_t *result, const uint8_t *a, const uint8_t *b)
{
    uint8_t prod[132];
    memset(prod, 0, sizeof(prod));

    for (int i = 0; i < 66; i++) {
        uint16_t carry = 0;
        for (int j = 0; j < 66; j++) {
            uint16_t p_val = (uint16_t)a[i] * b[j] + prod[i+j] + carry;
            prod[i+j] = (uint8_t)p_val;
            carry = p_val >> 8;
        }
        prod[i+66] = (uint8_t)carry;
    }

    for (int round = 0; round < 2; round++) {
        uint8_t high[66];
        memset(high, 0, 66);
        for (int i = 0; i < 65; i++) {
            high[i] = (prod[65 + i] >> 1) | (prod[66 + i] << 7);
        }
        high[65] = prod[130] >> 1;

        prod[65] &= 0x01;          /* keep only bit 520 */
        memset(prod + 66, 0, 66);  /* clear bytes 66..131 */

        uint16_t carry = 0;
        for (int i = 0; i < 66; i++) {
            uint16_t sum = (uint16_t)prod[i] + high[i] + carry;
            prod[i] = (uint8_t)sum;
            carry = sum >> 8;
        }
        if (carry) {
            prod[65] &= 0x01;        /* keep only bit 520 */
            uint16_t c = 1;
            for (int i = 0; i < 66 && c; i++) {
                uint16_t s = (uint16_t)prod[i] + c;
                prod[i] = (uint8_t)s;
                c = s >> 8;
            }
        }
    }
    memcpy(result, prod, 66);
}

/* result = a^(-1) mod p using Fermat's little theorem: a^(p-2) mod p */
static void p521_inv_mod(uint8_t *result, const uint8_t *a)
{
    uint8_t exp[66];
    memcpy(exp, p521_p, 66);
    uint16_t borrow = 2;
    for (int i = 0; i < 66; i++) {
        uint16_t diff = (uint16_t)exp[i] - borrow;
        exp[i] = (uint8_t)diff;
        borrow = (diff >> 8) & 1;
        if (!borrow) break;
    }

    uint8_t base[66];
    memcpy(base, a, 66);
    memset(result, 0, 66);
    result[0] = 1;

    for (int i = 520; i >= 0; i--) {
        uint8_t tmp[66];
        p521_mul_mod(tmp, result, result);
        memcpy(result, tmp, 66);

        int byte_idx = i / 8;
        int bit_idx = i % 8;
        if (exp[byte_idx] & (1 << bit_idx)) {
            p521_mul_mod(tmp, result, base);
            memcpy(result, tmp, 66);
        }
    }
}

/**
 * Convert Jacobian (X, Y, Z) to affine (x, y):
 *   z_inv = Z^(-1) mod p
 *   x = X * z_inv^2 mod p
 *   y = Y * z_inv^3 mod p
 */
static void p521_jacobian_to_affine(uint8_t *ax, uint8_t *ay,
                                     const uint8_t *jx, const uint8_t *jy, const uint8_t *jz)
{
    uint8_t z_inv[66], z_inv2[66], z_inv3[66];

    int z_zero = 1;
    for (int i = 0; i < 66; i++) {
        if (jz[i]) { z_zero = 0; break; }
    }
    if (z_zero) {
        memset(ax, 0, 66);
        memset(ay, 0, 66);
        return;
    }

    p521_inv_mod(z_inv, jz);
    p521_mul_mod(z_inv2, z_inv, z_inv);
    p521_mul_mod(z_inv3, z_inv2, z_inv);
    p521_mul_mod(ax, jx, z_inv2);
    p521_mul_mod(ay, jy, z_inv3);
}

/* ========================================================================== */
/* OTBN low-level helpers                                                     */
/* ========================================================================== */

static void otbn_load_firmware(void)
{
    HAL_OTBN_IMEM_Write(0, (const uint32_t *)g_ecc_p521_imem, g_ecc_p521_imem_size);
    HAL_OTBN_DMEM_Set(0, 0, ECC_P521_DMEM_TOTAL);
    HAL_OTBN_DMEM_Write(0, (const uint32_t *)g_ecc_p521_dmem, g_ecc_p521_dmem_size);
}

/* Copy 66 bytes from src to a zero-padded 96-byte buffer, then write to DMEM.
 * Buffer must be 4-byte aligned for HAL_OTBN_DMEM_Write.
 */
static void p521_write_coord(uint32_t offset, const uint8_t *src)
{
    uint32_t buf[24];
    memset(buf, 0, sizeof(buf));
    memcpy(buf, src, 66);
    HAL_OTBN_DMEM_Write(offset, buf, 96);
}

/* Read 96 bytes from DMEM, then copy only the first 66 bytes to dst.
 * Buffer must be 4-byte aligned for HAL_OTBN_DMEM_Read.
 */
static void p521_read_coord(uint32_t offset, uint8_t *dst)
{
    uint32_t buf[24];
    HAL_OTBN_DMEM_Read(offset, buf, 96);
    memcpy(dst, buf, 66);
}

/* Run a single OTBN atomic operation */
static HAL_StatusTypeDef otbn_run_mode(uint32_t mode)
{
    HAL_OTBN_DMEM_Write(ECC_P521_MODE_OFFSET, &mode, sizeof(uint32_t));
    if (HAL_OTBN_CMD_Write_Polling_Timeout(HAL_OTBN_CMD_EXECUTE, 20000) != HAL_OK)
        return HAL_TIMEOUT;
    return HAL_OK;
}

/* Field multiplication via OTBN */
static HAL_StatusTypeDef otbn_field_mul(const uint8_t *a, const uint8_t *b, uint8_t *c)
{
    p521_write_coord(ECC_P521_P_OFFSET, a);
    p521_write_coord(ECC_P521_Q_OFFSET, b);
    if (otbn_run_mode(ECC_P521_MODE_FIELD_MUL) != HAL_OK)
        return HAL_TIMEOUT;
    p521_read_coord(ECC_P521_R_OFFSET, c);
    return HAL_OK;
}

/* Check if a coordinate (66 bytes) is all zeros */
static int p521_is_zero(const uint8_t *a)
{
    for (int i = 0; i < 66; i++) {
        if (a[i]) return 0;
    }
    return 1;
}

/* Check if two coordinates (66 bytes each) are equal */
static int p521_coord_eq(const uint8_t *a, const uint8_t *b)
{
    for (int i = 0; i < 66; i++) {
        if (a[i] != b[i]) return 0;
    }
    return 1;
}

/* Point doubling via OTBN */
static HAL_StatusTypeDef otbn_point_dbl(const uint8_t *px, const uint8_t *py, const uint8_t *pz,
                           uint8_t *rx, uint8_t *ry, uint8_t *rz)
{
    /* Identity point: Z=0 -> double is identity */
    if (p521_is_zero(pz)) {
        memset(rx, 0, 66);
        memset(ry, 0, 66);
        ry[0] = 1;
        memset(rz, 0, 66);
        return HAL_OK;
    }

    p521_write_coord(ECC_P521_P_OFFSET, px);
    p521_write_coord(ECC_P521_P_OFFSET + 96, py);
    p521_write_coord(ECC_P521_P_OFFSET + 192, pz);
    if (otbn_run_mode(ECC_P521_MODE_POINT_DBL) != HAL_OK)
        return HAL_TIMEOUT;
    p521_read_coord(ECC_P521_R_OFFSET, rx);
    p521_read_coord(ECC_P521_R_OFFSET + 96, ry);
    p521_read_coord(ECC_P521_R_OFFSET + 192, rz);
    return HAL_OK;
}

/* Point addition via OTBN */
static HAL_StatusTypeDef otbn_point_add(const uint8_t *px, const uint8_t *py, const uint8_t *pz,
                           const uint8_t *qx, const uint8_t *qy, const uint8_t *qz,
                           uint8_t *rx, uint8_t *ry, uint8_t *rz)
{
    int p_is_zero = p521_is_zero(pz);
    int q_is_zero = p521_is_zero(qz);

    /* P + O = P */
    if (p_is_zero) {
        memcpy(rx, qx, 66);
        memcpy(ry, qy, 66);
        memcpy(rz, qz, 66);
        return HAL_OK;
    }

    /* O + Q = Q */
    if (q_is_zero) {
        memcpy(rx, px, 66);
        memcpy(ry, py, 66);
        memcpy(rz, pz, 66);
        return HAL_OK;
    }

    /* P == Q -> use point doubling */
    if (p521_coord_eq(px, qx) && p521_coord_eq(py, qy) && p521_coord_eq(pz, qz)) {
        return otbn_point_dbl(px, py, pz, rx, ry, rz);
    }

    p521_write_coord(ECC_P521_P_OFFSET, px);
    p521_write_coord(ECC_P521_P_OFFSET + 96, py);
    p521_write_coord(ECC_P521_P_OFFSET + 192, pz);
    p521_write_coord(ECC_P521_Q_OFFSET, qx);
    p521_write_coord(ECC_P521_Q_OFFSET + 96, qy);
    p521_write_coord(ECC_P521_Q_OFFSET + 192, qz);
    if (otbn_run_mode(ECC_P521_MODE_POINT_ADD) != HAL_OK)
        return HAL_TIMEOUT;
    p521_read_coord(ECC_P521_R_OFFSET, rx);
    p521_read_coord(ECC_P521_R_OFFSET + 96, ry);
    p521_read_coord(ECC_P521_R_OFFSET + 192, rz);
    return HAL_OK;
}

/* ========================================================================== */
/* Montgomery Ladder (scalar multiplication)                                  */
/* ========================================================================== */

static HAL_StatusTypeDef p521_scalar_mult(const uint8_t *k,
                             const uint8_t *px, const uint8_t *py,
                             uint8_t *rx, uint8_t *ry)
{
    /* Jacobian point buffers */
    uint8_t r0_x[66], r0_y[66], r0_z[66];
    uint8_t r1_x[66], r1_y[66], r1_z[66];

    /* R0 = identity (0, 1, 0) */
    memset(r0_x, 0, 66);
    memset(r0_y, 0, 66);
    r0_y[0] = 1;
    memset(r0_z, 0, 66);

    /* R1 = P (px, py, 1) */
    memcpy(r1_x, px, 66);
    memcpy(r1_y, py, 66);
    memset(r1_z, 0, 66);
    r1_z[0] = 1;

    /* Pointers for swap */
    uint8_t *p0x = r0_x, *p0y = r0_y, *p0z = r0_z;
    uint8_t *p1x = r1_x, *p1y = r1_y, *p1z = r1_z;

    /* Temporary result buffers */
    uint8_t t_x[66], t_y[66], t_z[66];

    /* Montgomery ladder: 521 iterations, MSB to LSB */
    for (int i = 520; i >= 0; i--) {
        int byte_idx = i >> 3;  /* i / 8 */
        int bit_idx = i & 7;   /* i % 8 */
        int bit = (k[byte_idx] >> bit_idx) & 1;

        if (bit == 0) {
            /* Swap R0 and R1 pointers */
            uint8_t *tx = p0x; p0x = p1x; p1x = tx;
            uint8_t *ty = p0y; p0y = p1y; p1y = ty;
            uint8_t *tz = p0z; p0z = p1z; p1z = tz;
        }

        /* R0 = R0 + R1 */
        if (otbn_point_add(p0x, p0y, p0z, p1x, p1y, p1z, t_x, t_y, t_z) != HAL_OK)
            return HAL_TIMEOUT;
        memcpy(p0x, t_x, 66);
        memcpy(p0y, t_y, 66);
        memcpy(p0z, t_z, 66);

        /* R1 = 2 * R1 */
        if (otbn_point_dbl(p1x, p1y, p1z, t_x, t_y, t_z) != HAL_OK)
            return HAL_TIMEOUT;
        memcpy(p1x, t_x, 66);
        memcpy(p1y, t_y, 66);
        memcpy(p1z, t_z, 66);

        if (bit == 0) {
            /* Swap back */
            uint8_t *tx = p0x; p0x = p1x; p1x = tx;
            uint8_t *ty = p0y; p0y = p1y; p1y = ty;
            uint8_t *tz = p0z; p0z = p1z; p1z = tz;
        }
    }

    /* Convert R0 to affine */
    p521_jacobian_to_affine(rx, ry, p0x, p0y, p0z);
    return HAL_OK;
}

/* ========================================================================== */
/* Public APIs                                                                */
/* ========================================================================== */

HAL_StatusTypeDef HAL_OTBN_P521_ScalarMult_Polling(const uint8_t *k,
                                      const uint8_t *px, const uint8_t *py,
                                      uint8_t *rx, uint8_t *ry)
{
    otbn_load_firmware();
    return p521_scalar_mult(k, px, py, rx, ry);
}

HAL_StatusTypeDef HAL_OTBN_P521_BaseMult_Polling(const uint8_t *k,
                                    uint8_t *rx, uint8_t *ry)
{
    otbn_load_firmware();
    return p521_scalar_mult(k, p521_gx, p521_gy, rx, ry);
}

HAL_StatusTypeDef HAL_OTBN_P521_PointAdd_Polling(const uint8_t *px, const uint8_t *py,
                                    const uint8_t *qx, const uint8_t *qy,
                                    uint8_t *rx, uint8_t *ry)
{
    uint8_t jx[66], jy[66], jz[66];

    otbn_load_firmware();

    /* P + Q (both affine Z=1) */
    if (otbn_point_add(px, py, p521_one, qx, qy, p521_one, jx, jy, jz) != HAL_OK)
        return HAL_TIMEOUT;
    p521_jacobian_to_affine(rx, ry, jx, jy, jz);
    return HAL_OK;
}
