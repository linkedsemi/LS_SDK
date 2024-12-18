#include "ls_hal_sm4.h"
#include "ls_msp_sm4.h"
#include "field_manipulate.h"
#include <string.h>
#include "ls_dbg.h"

#define SM4_BLOCK_SIZE (0x10)

static const uint8_t *crypt_in;
static uint8_t *crypt_out;
static bool writeflag;

HAL_StatusTypeDef HAL_SM4_Init(void)
{
    HAL_LSSM4_MSP_Init();
    return HAL_OK;
}

HAL_StatusTypeDef HAL_SM4_DeInit(void)
{
    HAL_LSSM4_MSP_DeInit();
    return HAL_OK;
}

static uint32_t u8tou32(const uint8_t *in)
{
    return in[0] | in[1] << 8 | in[2] << 16 | in[3] << 24;
}

static void u32tou8(uint32_t in, uint8_t *out)
{
    *out++ = in;
    *out++ = in >> 8;
    *out++ = in >> 16;
    *out++ = in >> 24;
}

void sm4_key_start(const uint8_t *key)
{    
    LSSM4->SM4_KEY0 = u8tou32(key);
    LSSM4->SM4_KEY1 = u8tou32(key + 4);
    LSSM4->SM4_KEY2 = u8tou32(key + 8);
    LSSM4->SM4_KEY3 = u8tou32(key + 12);
    LSSM4->SM4_START = SM4_KEY_START_MASK;
}

HAL_StatusTypeDef HAL_SM4_KeyExpansion(const uint8_t *key)
{   
    sm4_key_start(key);
    while (REG_FIELD_RD(LSSM4->INTR_RAW, SM4_KEY_END) == 0)
        ;
    LSSM4->INTR_CLR = SM4_KEY_END_MASK;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_SM4_KeyExpansion_IT(const uint8_t *key)
{
    LSSM4->INTR_MSK |= SM4_KEY_END_MASK;
    sm4_key_start(key);
    return HAL_OK;
}

static void sm4_data_length_inout_config(const uint8_t *data, uint32_t length, uint8_t *result)
{
    LS_ASSERT(length % 16 == 0);
    writeflag = true;
    crypt_in = data;
    crypt_out = result;
    LSSM4->SM4_CTRL |= (uint8_t)(length / 16 - 1) << SM4_CALC_LEN_POS;
}

static void sm4_start()
{
    LSSM4->CALC_WRD = u8tou32(crypt_in);
    LSSM4->CALC_WRD = u8tou32(crypt_in + 4);
    LSSM4->CALC_WRD = u8tou32(crypt_in + 8);
    LSSM4->CALC_WRD = u8tou32(crypt_in + 12);
}

static void sm4_end()
{
    u32tou8(LSSM4->CALC_RSLT0, crypt_out);
    u32tou8(LSSM4->CALC_RSLT1, crypt_out + 4);
    u32tou8(LSSM4->CALC_RSLT2, crypt_out + 8);
    u32tou8(LSSM4->CALC_RSLT3, crypt_out + 12);
    crypt_in += 16;
    crypt_out += 16;
}

static void sm4_calculate()
{
    LSSM4->SM4_START = SM4_CALC_START_MASK;
    do
    {
        while (REG_FIELD_RD(LSSM4->INTR_RAW, SM4_INTR_DATA) == 1)
        {
            if (writeflag)
            {
                sm4_start();
            }
            else
            {
                sm4_end();
            }
            writeflag = !writeflag;
            LSSM4->INTR_CLR = SM4_INTR_DATA_MASK;
        }
    } while (REG_FIELD_RD(LSSM4->INTR_RAW, SM4_INTR_END) == 0);
    LSSM4->INTR_CLR = SM4_INTR_END_MASK;
    sm4_end();
}

HAL_StatusTypeDef HAL_SM4_Encrypt(const uint8_t *data, uint8_t *result, uint32_t length)
{
    sm4_data_length_inout_config(data, length, result);
    REG_FIELD_WR(LSSM4->SM4_CTRL,SM4_CALC_DEC,0);
    sm4_calculate();
    return HAL_OK;
}

HAL_StatusTypeDef HAL_SM4_Decrypt(const uint8_t *data, uint8_t *result, uint32_t length)
{
    sm4_data_length_inout_config(data, length, result);
    REG_FIELD_WR(LSSM4->SM4_CTRL,SM4_CALC_DEC,1);
    sm4_calculate();
    return HAL_OK;
}

void HAL_SM4_CTR_Crypt(uint8_t cnt[0x10], const uint8_t *in, uint32_t in_len, uint8_t *out)
{
    uint32_t i,length;
    uint8_t result[SM4_BLOCK_SIZE];
    uint8_t flag[SM4_BLOCK_SIZE];

    REG_FIELD_WR(LSSM4->SM4_CTRL, SM4_CALC_DEC, 0);
    do
    {
        memset(flag, 0, SM4_BLOCK_SIZE);
        sm4_data_length_inout_config(cnt, 0x10, result);
        sm4_calculate();
        length = (in_len > SM4_BLOCK_SIZE )? SM4_BLOCK_SIZE : in_len;
        for (i = 0; i < length; i++)
        {
            *out++ = result[i] ^ *in++;
        }
        in_len -= length;
        if (++cnt[SM4_BLOCK_SIZE - 1] == 0x00)
            flag[SM4_BLOCK_SIZE - 2] = true;
        for (i = SM4_BLOCK_SIZE - 1; i > 0; i--)
        {
            if (flag[i])
            {
                if (++cnt[i] == 0x00)
                    flag[i - 1] = true;
            }
        }
        if (flag[0])
            cnt[0]++;
    } while (in_len);
}

static void block_crypt(uint8_t *in, uint8_t *out)
{
    sm4_data_length_inout_config(in, 0x10, out);
    sm4_calculate();
}

#define SM4_MIN_AUTH_TAG_SIZE (0xc)

#define BSWAP_32(x) ((uint32_t) ((((x) >> 24) & 0xff) | \
				   (((x) >> 8) & 0xff00) | \
				   (((x) & 0xff00) << 8) | \
				   (((x) & 0xff) << 24)))
#define BSWAP_40(x) ((uint64_t) ((((x) >> 32) & 0xff) | \
				   (((x) >> 16) & 0xff00) | \
				   (((x)) & 0xff0000) | \
				   (((x) & 0xff00) << 16) | \
				   (((x) & 0xff) << 32)))
#define BSWAP_48(x) ((uint64_t) ((((x) >> 40) & 0xff) | \
				   (((x) >> 24) & 0xff00) | \
				   (((x) >> 8) & 0xff0000) | \
				   (((x) & 0xff0000) << 8) | \
				   (((x) & 0xff00) << 24) | \
				   (((x) & 0xff) << 40)))
#define BSWAP_64(x) ((uint64_t) ((((x) >> 56) & 0xff) | \
				   (((x) >> 40) & 0xff00) | \
				   (((x) >> 24) & 0xff0000) | \
				   (((x) >> 8) & 0xff000000) | \
				   (((x) & 0xff000000) << 8) | \
				   (((x) & 0xff0000) << 24) | \
				   (((x) & 0xff00) << 40) | \
				   (((x) & 0xff) << 56)))

#if !defined(KERNEL)
#define UNALIGNED_PUT(v, p)                                             \
do {   ;                                                                 \
	struct __attribute__((__packed__)) {                            \
		__typeof__(*p) __v;                                     \
	} *__p = (__typeof__(__p)) (p);                                 \
	__p->__v = (v);                                               \
} while (false)
#endif

static inline void mem_xor_n(uint8_t *dst, const uint8_t *src1, const uint8_t *src2, size_t len)
{
	while (len--) {
		*dst++ = *src1++ ^ *src2++;
	}
}

static void gmult(uint64_t *x, uint64_t *y)
{
    uint64_t z[2] = {0, 0};
    uint64_t v[2];
    int i, j;
    uint64_t v1;
    v[0] = x[0];
    v[1] = x[1];

    for (i = 0; i < 2; i++)
    {
        uint64_t y_tmp = y[i];
        for (j = 0; j < 64; j++)
        {
            uint64_t mask = 0 - (y_tmp >> 63);
            z[0] ^= v[0] & mask;
            z[1] ^= v[1] & mask;
            v1 = (0 - (v[1] & 1)) & 0xe100000000000000ull;
            v[1] >>= 1;
            v[1] |= v[0] << 63;
            v[0] >>= 1;
            v[0] ^= v1;
            y_tmp <<= 1;
        }
    }
    x[0] = z[0];
    x[1] = z[1];
}

static void ghash(uint8_t gcm_h[16],
                  const uint8_t *a, uint32_t a_size,
                  const uint8_t *c, uint32_t c_size,
                  uint8_t *s, uint32_t s_size)
{
    uint64_t x[2] = {0, 0};
    uint32_t blocks, partial;
    uint64_t big_h[2];

    memcpy(big_h, gcm_h, SM4_BLOCK_SIZE);
    big_h[0] = BSWAP_64(big_h[0]);
    big_h[1] = BSWAP_64(big_h[1]);

    /* Hash in A, the Additional Authentication Data */
    if (a_size != 0 && a != NULL)
    {
        uint64_t big_a[2];
        blocks = a_size / SM4_BLOCK_SIZE;
        partial = a_size % SM4_BLOCK_SIZE;
        while (blocks--)
        {
            memcpy(big_a, a, SM4_BLOCK_SIZE);
            big_a[0] = BSWAP_64(big_a[0]);
            big_a[1] = BSWAP_64(big_a[1]);
            x[0] ^= big_a[0];
            x[1] ^= big_a[1];
            gmult(x, big_h);
            a += SM4_BLOCK_SIZE;
        }
        if (partial != 0)
        {
            memset(big_a, 0, SM4_BLOCK_SIZE);
            memcpy(big_a, a, partial);
            big_a[0] = BSWAP_64(big_a[0]);
            big_a[1] = BSWAP_64(big_a[1]);
            x[0] ^= big_a[0];
            x[1] ^= big_a[1];
            gmult(x, big_h);
        }
    }

    /* Hash in C, the Ciphertext */
    if (c_size != 0 && c != NULL)
    {
        uint64_t big_c[2];
        blocks = c_size / SM4_BLOCK_SIZE;
        partial = c_size % SM4_BLOCK_SIZE;

        while (blocks--)
        {
            memcpy(big_c, c, SM4_BLOCK_SIZE);
            big_c[0] = BSWAP_64(big_c[0]);
            big_c[1] = BSWAP_64(big_c[1]);
            x[0] ^= big_c[0];
            x[1] ^= big_c[1];
            gmult(x, big_h);
            c += SM4_BLOCK_SIZE;
        }
        if (partial != 0)
        {
            memset(big_c, 0, SM4_BLOCK_SIZE);
            memcpy(big_c, c, partial);
            big_c[0] = BSWAP_64(big_c[0]);
            big_c[1] = BSWAP_64(big_c[1]);
            x[0] ^= big_c[0];
            x[1] ^= big_c[1];
            gmult(x, big_h);
        }
    }

    /* Hash in the lengths in bits of A and C */
    {
        uint64_t len[2];
        len[0] = a_size;
        len[1] = c_size;

        /* Lengths are in bytes. Convert to bits. */
        len[0] *= 8;
        len[1] *= 8;

        x[0] ^= len[0];
        x[1] ^= len[1];
        gmult(x, big_h);
    }
    x[0] = BSWAP_64(x[0]);
    x[1] = BSWAP_64(x[1]);
    memcpy(s, x, s_size);
}

static inline void inc_ctr(uint8_t *ctr, uint32_t ctr_size)
{
    for (uint32_t i = ctr_size - 1; i >= 0; i--)
    {
        if (++ctr[i])
            return;
    }
}

static inline void xorbufout16(uint8_t *out, const uint8_t *a, const uint8_t *b)
{
    uint64_t *out64 = (uint64_t *)out;
    uint64_t *a64 = (uint64_t *)a;
    uint64_t *b64 = (uint64_t *)b;

    out64[0] = a64[0] ^ b64[0];
    out64[1] = a64[1] ^ b64[1];
}

static inline void xor_array(const uint8_t *a, const uint8_t *b, uint8_t *out,uint32_t sz)
{
    for (uint32_t i = 0; i < sz; i++)
    {
        out[i] = a[i] ^ b[i];
    }
}

bool HAL_SM4_GCM_Decrypt(uint8_t *in, uint32_t in_size,
                         uint8_t *nonce, uint32_t nonce_size,
                         uint8_t *tag, uint32_t tag_size,
                         uint8_t *aad, uint32_t aad_size,
                         uint8_t *out)
{
    if ((nonce == NULL) || (tag == NULL) || (tag_size > SM4_BLOCK_SIZE) || (tag_size < SM4_MIN_AUTH_TAG_SIZE) ||
        ((aad == NULL) && (aad_size > 0)) || (nonce_size == 0) || (((in_size != 0) && ((in == NULL) || (out == NULL)))))
    {
        return HAL_INVALIAD_PARAM;
    }
    
    REG_FIELD_WR(LSSM4->SM4_CTRL,SM4_CALC_DEC,1);

    uint8_t gcm_h[SM4_BLOCK_SIZE] = {0};
    uint8_t c_j0[SM4_BLOCK_SIZE] = {0};
    uint8_t t_prime[SM4_BLOCK_SIZE] = {0};

    uint8_t counter[SM4_BLOCK_SIZE] = {0};
    uint8_t c[SM4_BLOCK_SIZE] = {0};
    uint32_t partial = in_size % SM4_BLOCK_SIZE;
    uint8_t *current_in = in;
    uint8_t *current_out = out;

    memcpy(counter, nonce, nonce_size);
    memset(counter + SM4_MIN_AUTH_TAG_SIZE, 0, SM4_BLOCK_SIZE - nonce_size);
    counter[SM4_BLOCK_SIZE - 1] = 1;

    for (uint32_t i = 0; i < in_size / SM4_BLOCK_SIZE; i++)
    {
        inc_ctr(counter + nonce_size, SM4_BLOCK_SIZE - nonce_size);
        block_crypt(counter, c);
        xorbufout16(current_out, c, current_in);
        current_out += SM4_BLOCK_SIZE;
        current_in += SM4_BLOCK_SIZE;
    }
    if (partial)
    {
        inc_ctr(counter + nonce_size, SM4_BLOCK_SIZE - nonce_size);
        block_crypt(counter, c);
        xor_array(c, current_in, current_out, partial);
    }

    block_crypt(gcm_h, gcm_h);

    UNALIGNED_PUT(BSWAP_32(1), (uint32_t *)&counter[12]);
    block_crypt(counter, c_j0);
    ghash(gcm_h, aad, aad_size, in, in_size, t_prime, sizeof(t_prime));

    mem_xor_n(t_prime, t_prime, c_j0, sizeof(t_prime));

    if (memcmp(t_prime, tag, tag_size) != 0)
    {
        return false;
    }
    return true;
}

void HAL_SM4_GCM_Decrypt_Init(sm4_gcm_env *gcm, uint8_t *nonce, uint32_t nonce_size)
{
    memset((uint8_t *)gcm, 0x0, sizeof(sm4_gcm_env));
    gcm->counter_size = nonce_size;

    if (nonce_size == SM4_MIN_AUTH_TAG_SIZE)
    {
        memcpy(gcm->counter, nonce, nonce_size);
        memset(gcm->counter + SM4_MIN_AUTH_TAG_SIZE, 0, SM4_BLOCK_SIZE - nonce_size);
        gcm->counter[SM4_BLOCK_SIZE - 1] = 1;
    }

    block_crypt(gcm->h, gcm->h);
    block_crypt(gcm->counter, gcm->j0);

    memcpy(gcm->big_h, gcm->h, SM4_BLOCK_SIZE);
    gcm->big_h[0] = BSWAP_64(gcm->big_h[0]);
    gcm->big_h[1] = BSWAP_64(gcm->big_h[1]);

}

void HAL_SM4_GCM_Decrypt_Update(sm4_gcm_env *gcm, uint8_t *out,
                                        uint8_t *in, uint32_t in_size,
                                        uint8_t *aad, uint32_t aad_size)
{
    uint8_t c[SM4_BLOCK_SIZE];
    uint32_t partial = in_size % SM4_BLOCK_SIZE;
    const uint8_t *_in = in;
    uint32_t blocks;
    gcm->data_size += in_size;
    gcm->aad_size += aad_size;

    /* GCTR */
    for (uint32_t i = 0; i < in_size / SM4_BLOCK_SIZE; i++)
    {
        inc_ctr(gcm->counter + gcm->counter_size, SM4_BLOCK_SIZE - gcm->counter_size);
        block_crypt(gcm->counter, c);
        xorbufout16(out, c, in);
        out += SM4_BLOCK_SIZE;
        in += SM4_BLOCK_SIZE;
    }
    if (partial)
    {
        inc_ctr(gcm->counter + gcm->counter_size, SM4_BLOCK_SIZE - gcm->counter_size);
        block_crypt(gcm->counter, c);
        xor_array(c, in, out, partial);
    }
    
    /* Hash in A, the Additional Authentication Data */
    if (aad_size != 0 && aad != NULL)
    {
        uint64_t big_a[2];
        blocks = aad_size / SM4_BLOCK_SIZE;
        partial = aad_size % SM4_BLOCK_SIZE;
        while (blocks--)
        {
            memcpy(big_a, aad, SM4_BLOCK_SIZE);
            big_a[0] = BSWAP_64(big_a[0]);
            big_a[1] = BSWAP_64(big_a[1]);
            gcm->x[0] ^= big_a[0];
            gcm->x[1] ^= big_a[1];
            gmult(gcm->x, gcm->big_h);
            aad += SM4_BLOCK_SIZE;
        }
        if (partial != 0)
        {
            memset(big_a, 0, SM4_BLOCK_SIZE);
            memcpy(big_a, aad, partial);
            big_a[0] = BSWAP_64(big_a[0]);
            big_a[1] = BSWAP_64(big_a[1]);
            gcm->x[0] ^= big_a[0];
            gcm->x[1] ^= big_a[1];
            gmult(gcm->x, gcm->big_h);
        }
    }

    /* Hash in C, the Ciphertext */
    if (in_size != 0 && _in != NULL)
    {
        uint64_t big_c[2];
        blocks = in_size / SM4_BLOCK_SIZE;
        partial = in_size % SM4_BLOCK_SIZE;
        while (blocks--)
        {
            memcpy(big_c, _in, SM4_BLOCK_SIZE);
            big_c[0] = BSWAP_64(big_c[0]);
            big_c[1] = BSWAP_64(big_c[1]);
            gcm->x[0] ^= big_c[0];
            gcm->x[1] ^= big_c[1];
            gmult(gcm->x, gcm->big_h);
            _in += SM4_BLOCK_SIZE;
        }
        if (partial != 0)
        {
            memset(big_c, 0, SM4_BLOCK_SIZE);
            memcpy(big_c, _in, partial);
            big_c[0] = BSWAP_64(big_c[0]);
            big_c[1] = BSWAP_64(big_c[1]);
            gcm->x[0] ^= big_c[0];
            gcm->x[1] ^= big_c[1];
            gmult(gcm->x, gcm->big_h);
        }
    }
}

bool HAL_SM4_GCM_Decrypt_Final(sm4_gcm_env *gcm, uint8_t *tag, uint32_t tag_size)
{
    /* Hash in the lengths in bits of A and C */
    {
        uint64_t len[2];
        len[0] = gcm->aad_size;
        len[1] = gcm->data_size;

        /* Lengths are in bytes. Convert to bits. */
        len[0] *= 8;
        len[1] *= 8;

        gcm->x[0] ^= len[0];
        gcm->x[1] ^= len[1];
        gmult(gcm->x, gcm->big_h);
    }

    gcm->x[0] = BSWAP_64(gcm->x[0]);
    gcm->x[1] = BSWAP_64(gcm->x[1]);
    memcpy(gcm->prime, gcm->x, SM4_BLOCK_SIZE);

    mem_xor_n(gcm->prime, gcm->prime, gcm->j0, SM4_BLOCK_SIZE);

    if (memcmp(gcm->prime, tag, tag_size) != 0)
    {
        return false;
    }
    return true;
}


HAL_StatusTypeDef HAL_SM4_Encrypt_IT(const uint8_t *data, uint8_t *result, uint32_t length)
{
    sm4_data_length_inout_config(data, length, result);
    REG_FIELD_WR(LSSM4->SM4_CTRL,SM4_CALC_DEC,0);
    MODIFY_REG(LSSM4->INTR_MSK, SM4_INTR_DATA_MASK | SM4_INTR_END_MASK, 1 << SM4_INTR_DATA_POS | 1 << SM4_INTR_END_POS);
    LSSM4->SM4_START = SM4_CALC_START_MASK;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_SM4_Decrypt_IT(const uint8_t *data, uint8_t *result, uint32_t length)
{
    sm4_data_length_inout_config(data, length, result);
    REG_FIELD_WR(LSSM4->SM4_CTRL,SM4_CALC_DEC,1);
    MODIFY_REG(LSSM4->INTR_MSK, SM4_INTR_DATA_MASK | SM4_INTR_END_MASK, 1 << SM4_INTR_DATA_POS | 1 << SM4_INTR_END_POS);
    LSSM4->SM4_START = SM4_CALC_START_MASK;
    return HAL_OK;
}

__attribute__((weak)) void HAL_SM4_Calculation_Complete_Callback(bool Encrypt){}
__attribute__((weak)) void HAL_SM4_KeyExpansion_Complete_Callback(){}

void HAL_SM4_IRQHandler()
{
    if (REG_FIELD_RD(LSSM4->INTR_STT, SM4_INTR_DATA))
    {
        if (writeflag)
        {
            writeflag = !writeflag;
            sm4_start();
        }
        else
        {
            writeflag = !writeflag;
            sm4_end();
        }
        LSSM4->INTR_CLR = SM4_INTR_DATA_MASK;
    }
    if (REG_FIELD_RD(LSSM4->INTR_STT, SM4_INTR_END))
    {
        sm4_end();
        LSSM4->INTR_CLR = SM4_INTR_END_MASK;
        HAL_SM4_Calculation_Complete_Callback(!REG_FIELD_RD(LSSM4->SM4_CTRL,SM4_CALC_DEC));
    }
    if(REG_FIELD_RD(LSSM4->INTR_STT, SM4_KEY_END))
    {
        LSSM4->INTR_CLR = SM4_KEY_END_MASK;
        HAL_SM4_KeyExpansion_Complete_Callback();
    }
}