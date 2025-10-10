#include "ls_hal_crypt.h"
#include "ls_msp_crypt.h"
#include "field_manipulate.h"
#include "ls_dbg.h"
#include <string.h>
#define AES_BLOCK_SIZE 16
#define DES_BLOCK_SIZE 8
static uint8_t BLOCK_SIZE;
static const uint8_t *current_in;
static uint8_t *current_out;
static uint32_t length_in;
static uint32_t length_out;
static uint32_t length_residue;
static enum padding_mode crypt_padding_mode = Padding_None;
static int (* crypt_rand_func)(void);

void HAL_LSCRYPT_SetRandFunc(void *func)
{
    crypt_rand_func = func;
}

HAL_StatusTypeDef HAL_LSCRYPT_Init(void)
{
    HAL_LSCRYPT_MSP_Init();
    HAL_LSCRYPT_MSP_Busy_Set();
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSCRYPT_DeInit(void)
{
    HAL_LSCRYPT_MSP_Idle_Set();
    HAL_LSCRYPT_MSP_DeInit();
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSCRYPT_Block_Padding_Mode_Set(enum padding_mode mode)
{
    crypt_padding_mode = mode;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSCRYPT_AES_Key_Config(const uint32_t *key,enum aes_key_type key_size)
{
    REG_FIELD_WR(LSCRYPT->CR,CRYPT_AESKS,key_size);
    do{
        LSCRYPT->KEY0 = *key++;
        LSCRYPT->KEY1 = *key++;
        LSCRYPT->KEY2 = *key++;
        LSCRYPT->KEY3 = *key++;
        if(key_size == AES_KEY_128) break;
        LSCRYPT->KEY4 = *key++;
        LSCRYPT->KEY5 = *key++;
        if(key_size == AES_KEY_192) break;
        LSCRYPT->KEY6 = *key++;
        LSCRYPT->KEY7 = *key++;
        if(key_size == AES_KEY_256) break;
    }while(0);
    return HAL_OK;
}

static void aes_config(bool iv_en,bool cbc,bool enc,bool ie)
{
    MODIFY_REG(LSCRYPT->CR,CRYPT_CRYSEL_MASK|CRYPT_DMAEN_MASK|CRYPT_FIFOEN_MASK|CRYPT_IE_MASK|CRYPT_IVREN_MASK|CRYPT_MODE_MASK|CRYPT_ENCS_MASK,
        0<<CRYPT_CRYSEL_POS|0<<CRYPT_DMAEN_POS|0<<CRYPT_FIFOEN_POS|(ie?1:0)<<CRYPT_IE_POS|(iv_en?1:0)<<CRYPT_IVREN_POS|(cbc?1:0)<<CRYPT_MODE_POS|(enc?1:0)<<CRYPT_ENCS_POS);
}

static inline uint32_t get_uint32_t(const uint8_t *data)
{
    return __builtin_bswap32(*(const uint32_t *)data);
}

static inline void set_uint32_t(uint32_t src,uint8_t *dst)
{
    *(uint32_t *)dst = __builtin_bswap32(src);
}

static void block_data_in(const uint8_t *in)
{
    if(BLOCK_SIZE == AES_BLOCK_SIZE)
    {
        LSCRYPT->DATA3 = get_uint32_t(in);
        in += sizeof(uint32_t);
        LSCRYPT->DATA2 = get_uint32_t(in);
        in += sizeof(uint32_t);
        LSCRYPT->DATA1 = get_uint32_t(in);
        in += sizeof(uint32_t);
        LSCRYPT->DATA0 = get_uint32_t(in);
        in += sizeof(uint32_t);
    }
    else
    {
        LSCRYPT->DATA1 = get_uint32_t(in);
        in += sizeof(uint32_t);
        LSCRYPT->DATA0 = get_uint32_t(in);
        in += sizeof(uint32_t);        
    }
}

static void block_data_out(uint8_t *out)
{
    if(BLOCK_SIZE == AES_BLOCK_SIZE)
    {
        set_uint32_t(LSCRYPT->RES3,out);
        out += sizeof(uint32_t);
        set_uint32_t(LSCRYPT->RES2,out);
        out += sizeof(uint32_t);
        set_uint32_t(LSCRYPT->RES1,out);
        out += sizeof(uint32_t);
        set_uint32_t(LSCRYPT->RES0,out);
        out += sizeof(uint32_t);
    }
    else
    {
        set_uint32_t(LSCRYPT->RES1, out);
        out += sizeof(uint32_t);
        set_uint32_t(LSCRYPT->RES0, out);
        out += sizeof(uint32_t);
    }
}

static void crypt_data_in_Padding_PKCS7(const uint8_t *in_src, uint8_t *in_res,uint8_t read_length)
{
    for (int i = 0; i < BLOCK_SIZE; i++)
    { 
        if(i < read_length)
        {
            in_res[i] = in_src[i];
        }
        else
        {
            length_out += 1;
            in_res[i] = BLOCK_SIZE - read_length;
        }
    }
}

static void crypt_data_in_Padding_ANSIX923(const uint8_t *in_src, uint8_t *in_res,uint8_t read_length)
{
    for (int i = 0; i < BLOCK_SIZE; i++)
    {
        if (i < read_length)
        {
            in_res[i] = in_src[i];
        }
        else
        {
            length_out += 1;
            in_res[i] = i == BLOCK_SIZE - 1 ? BLOCK_SIZE - read_length : 0;
        }
    }
}

static void crypt_data_in_Padding_ISO7816(const uint8_t *in_src, uint8_t *in_res,uint8_t read_length)
{
    for (int i = 0; i < BLOCK_SIZE; i++)
    {
        if (i < read_length)
        {
            in_res[i] = in_src[i];
        }
        else
        {
            length_out += 1;
            in_res[i] = i == read_length ? 0x80 : 0;
        }
    }
}

static void crypt_data_in_Padding_ISO10126(const uint8_t *in_src, uint8_t *in_res,uint8_t read_length)
{
    for (int i = 0; i < BLOCK_SIZE; i++)
    {
        if (i < read_length)
        {
            in_res[i] = in_src[i];
        }
        else
        {
            length_out += 1;
            in_res[i] = i == BLOCK_SIZE - 1 ? BLOCK_SIZE - read_length : crypt_rand_func() % 256;
        }
    }
}

static void crypt_data_in()
{
    uint8_t read_length = length_residue >= BLOCK_SIZE ? BLOCK_SIZE : length_residue;
    if (read_length != BLOCK_SIZE)
    {
        uint8_t data_buffer[BLOCK_SIZE];
        switch (crypt_padding_mode)
        {
        case Padding_PKCS7:
            crypt_data_in_Padding_PKCS7(current_in, data_buffer, read_length);
            break;
        case Padding_ANSIX923:
            crypt_data_in_Padding_ANSIX923(current_in, data_buffer, read_length);
            break;
        case Padding_ISO7816:
            crypt_data_in_Padding_ISO7816(current_in, data_buffer, read_length);
            break;
        case Padding_ISO10126:
            crypt_data_in_Padding_ISO10126(current_in, data_buffer, read_length);
            break;
        default:
            break;
        }
        block_data_in(data_buffer);
    }
    else
    {
        block_data_in(current_in);
    }
}

static void crypt_data_out()
{
    if(REG_FIELD_RD(LSCRYPT->CR,CRYPT_ENCS) == 0 && length_residue == BLOCK_SIZE && crypt_padding_mode != Padding_None)
    {
        uint8_t res_buffer[BLOCK_SIZE];
        block_data_out(res_buffer);
        uint8_t padding_length = 0;
        int index = 0 ;
        switch (crypt_padding_mode)
        {
        case Padding_PKCS7:
            padding_length = res_buffer[BLOCK_SIZE - 1];
            for (int i = 0; i < BLOCK_SIZE; i++)
            {
                if (i < BLOCK_SIZE - padding_length)
                {
                    current_out[i] = res_buffer[i];
                }
                else
                {
                    if (res_buffer[i] != padding_length)
                    {
                        length_out = 0;
                        return;
                    }
                }
            }
            break;
        case Padding_ANSIX923:
            padding_length = res_buffer[BLOCK_SIZE - 1];
            for (int i = 0; i < BLOCK_SIZE; i++)
            {
                if (i < BLOCK_SIZE - padding_length)
                {
                    current_out[i] = res_buffer[i];
                }
                else if (i < BLOCK_SIZE - 1)
                {
                    if (res_buffer[i] != 0)
                    {
                        length_out = 0;
                        return;
                    }
                }
            }
            break;
        case Padding_ISO7816:
            index = BLOCK_SIZE - 1;
            while (res_buffer[index] == 0  && index != 0)
            {
                index--;
                padding_length++;
            }
            if(res_buffer[index] == 0x80)
            {
                padding_length++;
                for (int i = 0; i < index; i++)
                {
                   current_out[i] = res_buffer[i];
                }
            }
            else
            {
                length_out = 0;
                return;
            }
            break;
        case Padding_ISO10126:
            padding_length = res_buffer[BLOCK_SIZE - 1];
            while (index < BLOCK_SIZE - padding_length )
            {
                current_out[index] = res_buffer[index];
                index++;
            }
            break;
        default:
            break;
        }
        length_out = length_in - padding_length;
    }
    else
    {
        block_data_out(current_out);
    }
}

static void crypt_start()
{
    crypt_data_in();
    REG_FIELD_WR(LSCRYPT->CR,CRYPT_GO,1);
}

static void crypt_end()
{
    crypt_data_out();
    current_in += BLOCK_SIZE;
    current_out += BLOCK_SIZE;
    length_residue = length_residue < BLOCK_SIZE ? 0 : length_residue - BLOCK_SIZE;
}

static void crypt_in_out_length_set(const uint8_t *in,uint8_t *out,uint32_t length)
{
    current_in = in;
    current_out = out;
    length_in = length;
    length_out = length;
    length_residue = length;
}

static void aes_enc_dec(bool enc, bool cbc)
{
    bool iv_en = cbc;
    do
    {
        aes_config(iv_en, cbc, enc, false);
        BLOCK_SIZE = AES_BLOCK_SIZE;
        crypt_start();
        iv_en = false;
        while (REG_FIELD_RD(LSCRYPT->SR, CRYPT_AESRIF) == 0);
        LSCRYPT->ICFR = CRYPT_AESIF_MASK;
        crypt_end();
        if(length_residue == 0 && crypt_padding_mode == Padding_None)break;
    } while (length_out == length_in);
}

static void length_check(uint8_t crypt_mode, uint8_t crypt_type, uint32_t plaintextlength,uint32_t ciphertextlength)
{
    switch (crypt_mode)
    {
    case AES_MODE:
        BLOCK_SIZE = AES_BLOCK_SIZE;
        break;
    case DES_MODE:
        BLOCK_SIZE = DES_BLOCK_SIZE; 
    default:
        break;
    }
    switch (crypt_type)
    {
    case ENCRYPT: 
        if (crypt_padding_mode != Padding_None)
        {
            LS_ASSERT(ciphertextlength >= plaintextlength + BLOCK_SIZE - plaintextlength % BLOCK_SIZE);
        }
        else
        {
            LS_ASSERT(ciphertextlength >= plaintextlength);
            LS_ASSERT(plaintextlength % BLOCK_SIZE == 0);
        }
        break;
    case DECRYPT:
        LS_ASSERT(plaintextlength >= ciphertextlength);
    default:
        break;
    }
}
static void block_crypt(uint8_t *in, uint8_t *out)
{
    block_data_in(in);
    REG_FIELD_WR(LSCRYPT->CR, CRYPT_GO, 1);
    while (REG_FIELD_RD(LSCRYPT->SR, CRYPT_AESRIF) == 0)
        ;
    LSCRYPT->ICFR = CRYPT_AESIF_MASK;
    block_data_out(out);
}

HAL_StatusTypeDef HAL_LSCRYPT_AES_ECB_Encrypt(const uint8_t *plaintext,uint32_t plaintextlength,uint8_t *ciphertext,uint32_t *ciphertextlength)
{
    length_check(AES_MODE,ENCRYPT,plaintextlength,*ciphertextlength);
    crypt_in_out_length_set(plaintext,ciphertext,plaintextlength);
    aes_enc_dec(true,false);
    *ciphertextlength =  length_out;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSCRYPT_AES_ECB_Decrypt(const uint8_t *ciphertext,uint32_t ciphertextlength,uint8_t *plaintext,uint32_t *plaintextlength)
{
    length_check(AES_MODE,DECRYPT,*plaintextlength,ciphertextlength);
    crypt_in_out_length_set(ciphertext, plaintext, ciphertextlength);
    aes_enc_dec(false, false);
    *plaintextlength = length_out;
    return HAL_OK;
}

void HAL_LSCRYPT_SET_IV(const uint32_t iv[4])
{
    LSCRYPT->IVR0 = iv[0];
    LSCRYPT->IVR1 = iv[1];
    LSCRYPT->IVR2 = iv[2];
    LSCRYPT->IVR3 = iv[3];
}

HAL_StatusTypeDef HAL_LSCRYPT_AES_CBC_Encrypt(const uint8_t *plaintext,uint32_t plaintextlength,uint8_t *ciphertext,uint32_t *ciphertextlength)
{
    length_check(AES_MODE,ENCRYPT,plaintextlength,*ciphertextlength);
    crypt_in_out_length_set(plaintext, ciphertext, plaintextlength);
    aes_enc_dec(true, true);
    *ciphertextlength = length_out;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSCRYPT_AES_CBC_Decrypt(const uint8_t *ciphertext,uint32_t ciphertextlength,uint8_t *plaintext,uint32_t *plaintextlength)
{
    length_check(AES_MODE,DECRYPT,*plaintextlength,ciphertextlength);
    crypt_in_out_length_set(ciphertext,plaintext,ciphertextlength);
    aes_enc_dec(false,true);
    *plaintextlength = length_out;
    return HAL_OK;
}

static void aes_ctr_enc(uint8_t *cnt)
{
    uint32_t i,length;
    uint8_t result[AES_BLOCK_SIZE];
    uint8_t flag[AES_BLOCK_SIZE];
    uint8_t initial_cnt[AES_BLOCK_SIZE];
    memcpy(initial_cnt, cnt, AES_BLOCK_SIZE);
    BLOCK_SIZE = AES_BLOCK_SIZE;
    aes_config(false, false, true, false);
    do
    {
        memset(flag, 0, AES_BLOCK_SIZE);
        block_data_in(cnt);
        REG_FIELD_WR(LSCRYPT->CR,CRYPT_GO,1);
        while (REG_FIELD_RD(LSCRYPT->SR, CRYPT_AESRIF) == 0);
        LSCRYPT->ICFR = CRYPT_AESIF_MASK;
        block_data_out(result);
        length = (length_residue > AES_BLOCK_SIZE )? AES_BLOCK_SIZE : length_residue;
        for (i = 0; i < length; i++)
        {
            *current_out++ = result[i] ^ *current_in++;
        }
        length_residue -= length;
        i = AES_BLOCK_SIZE - 1;
        if(++cnt[i] == 0x0) // Check LSB overflow
        {
            while((cnt[i] == 0x0) && (i>0)) // Inner logic loop: keeps propagating carry IF the current byte is 0
            {
                ++cnt[--i];
            }
        }
    } while (length_residue);
    memcpy(cnt, initial_cnt, AES_BLOCK_SIZE);
}

HAL_StatusTypeDef HAL_LSCRYPT_AES_CTR_Crypt(uint8_t cnt[0x10], const uint8_t *in, uint32_t in_len, uint8_t *out)
{
    crypt_in_out_length_set(in, out, in_len);
    aes_ctr_enc((uint8_t *)cnt);
    return HAL_OK;
}

#define AES_MIN_AUTH_TAG_SIZE (0xc)

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
#else
#include <zephyr/toolchain.h>
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

    memcpy(big_h, gcm_h, AES_BLOCK_SIZE);
    big_h[0] = BSWAP_64(big_h[0]);
    big_h[1] = BSWAP_64(big_h[1]);

    /* Hash in A, the Additional Authentication Data */
    if (a_size != 0 && a != NULL)
    {
        uint64_t big_a[2];
        blocks = a_size / AES_BLOCK_SIZE;
        partial = a_size % AES_BLOCK_SIZE;
        while (blocks--)
        {
            memcpy(big_a, a, AES_BLOCK_SIZE);
            big_a[0] = BSWAP_64(big_a[0]);
            big_a[1] = BSWAP_64(big_a[1]);
            x[0] ^= big_a[0];
            x[1] ^= big_a[1];
            gmult(x, big_h);
            a += AES_BLOCK_SIZE;
        }
        if (partial != 0)
        {
            memset(big_a, 0, AES_BLOCK_SIZE);
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
        blocks = c_size / AES_BLOCK_SIZE;
        partial = c_size % AES_BLOCK_SIZE;

        while (blocks--)
        {
            memcpy(big_c, c, AES_BLOCK_SIZE);
            big_c[0] = BSWAP_64(big_c[0]);
            big_c[1] = BSWAP_64(big_c[1]);
            x[0] ^= big_c[0];
            x[1] ^= big_c[1];
            gmult(x, big_h);
            c += AES_BLOCK_SIZE;
        }
        if (partial != 0)
        {
            memset(big_c, 0, AES_BLOCK_SIZE);
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

static bool aes_gcm_dec(uint8_t *in, uint8_t *nonce, uint32_t nonce_size, uint8_t *tag, uint32_t tag_size, uint8_t *aad, uint32_t aad_size)
{
    uint8_t gcm_h[AES_BLOCK_SIZE] = {0};
    uint8_t c_j0[AES_BLOCK_SIZE] = {0};
    uint8_t t_prime[AES_BLOCK_SIZE] = {0};

    uint8_t counter[AES_BLOCK_SIZE] = {0};
    uint8_t c[AES_BLOCK_SIZE] = {0};
    uint32_t partial = length_in % AES_BLOCK_SIZE;

    memcpy(counter, nonce, nonce_size);
    memset(counter + AES_MIN_AUTH_TAG_SIZE, 0, AES_BLOCK_SIZE - nonce_size);
    counter[AES_BLOCK_SIZE - 1] = 1;

    for (uint32_t i = 0; i < length_in / AES_BLOCK_SIZE; i++)
    {
        inc_ctr(counter + nonce_size, AES_BLOCK_SIZE - nonce_size);
        block_crypt(counter, c);
        xorbufout16(current_out, c, current_in);
        current_out += AES_BLOCK_SIZE;
        current_in += AES_BLOCK_SIZE;
        length_out += AES_BLOCK_SIZE;
    }
    if (partial)
    {
        inc_ctr(counter + nonce_size, AES_BLOCK_SIZE - nonce_size);
        block_crypt(counter, c);
        xor_array(c, current_in, current_out, partial);
        length_out += partial;
    }

    block_crypt(gcm_h, gcm_h);

    UNALIGNED_PUT(BSWAP_32(1), (uint32_t *)&counter[12]);
    block_crypt(counter, c_j0);
    ghash(gcm_h, aad, aad_size, in, length_in, t_prime, sizeof(t_prime));

    mem_xor_n(t_prime, t_prime, c_j0, sizeof(t_prime));

    if (memcmp(t_prime, tag, tag_size) != 0)
    {
        return false;
    }
    return true;
}

bool HAL_LSCRYPT_AES_GCM_Decrypt(uint8_t *in, uint32_t in_size,
                                              uint8_t *nonce, uint32_t nonce_size,
                                              uint8_t *tag, uint32_t tag_size,
                                              uint8_t *aad, uint32_t aad_size,
                                              uint8_t *out)
{
    if ((nonce == NULL) || (tag == NULL) || (tag_size > AES_BLOCK_SIZE) || (tag_size < AES_MIN_AUTH_TAG_SIZE) ||
        ((aad == NULL) && (aad_size > 0)) || (nonce_size == 0) || (((in_size != 0) && ((in == NULL) || (out == NULL)))))
    {
        return HAL_INVALIAD_PARAM;
    }

    BLOCK_SIZE = AES_BLOCK_SIZE;
    aes_config(false, false, true, false);
    crypt_in_out_length_set(in, out, in_size);
    return aes_gcm_dec(in, nonce, nonce_size, tag, tag_size, aad, aad_size);
}

void HAL_LSCRYPT_AES_GCM_Decrypt_Init(aes_gcm_env *gcm, uint8_t *nonce, uint32_t nonce_size)
{
    BLOCK_SIZE = AES_BLOCK_SIZE;
    aes_config(false, false, true, false);

    memset((uint8_t *)gcm, 0x0, sizeof(aes_gcm_env));
    gcm->counter_size = nonce_size;

    memcpy(gcm->counter, nonce, nonce_size);
    memset(gcm->counter + AES_MIN_AUTH_TAG_SIZE, 0, AES_BLOCK_SIZE - nonce_size);
    gcm->counter[AES_BLOCK_SIZE - 1] = 1;

    block_crypt(gcm->h, gcm->h);
    block_crypt(gcm->counter, gcm->j0);

    memcpy(gcm->big_h, gcm->h, AES_BLOCK_SIZE);
    gcm->big_h[0] = BSWAP_64(gcm->big_h[0]);
    gcm->big_h[1] = BSWAP_64(gcm->big_h[1]);
}

void HAL_LSCRYPT_AES_GCM_Decrypt_Update(aes_gcm_env *gcm, uint8_t *out,
                                        uint8_t *in, uint32_t in_size,
                                        uint8_t *aad, uint32_t aad_size)
{
    uint8_t c[AES_BLOCK_SIZE];
    uint32_t partial = in_size % AES_BLOCK_SIZE;
    const uint8_t *_in = in;
    uint32_t blocks;
    gcm->data_size += in_size;
    gcm->aad_size += aad_size;

    /* GCTR */
    for (uint32_t i = 0; i < in_size / AES_BLOCK_SIZE; i++)
    {
        inc_ctr(gcm->counter + gcm->counter_size, AES_BLOCK_SIZE - gcm->counter_size);
        block_crypt(gcm->counter, c);
        xorbufout16(out, c, in);
        out += AES_BLOCK_SIZE;
        in += AES_BLOCK_SIZE;
        length_out += AES_BLOCK_SIZE;
    }
    if (partial)
    {
        inc_ctr(gcm->counter + gcm->counter_size, AES_BLOCK_SIZE - gcm->counter_size);
        block_crypt(gcm->counter, c);
        xor_array(c, in, out, partial);
        length_out += partial;
    }
    
    /* Hash in A, the Additional Authentication Data */
    if (aad_size != 0 && aad != NULL)
    {
        uint64_t big_a[2];
        blocks = aad_size / AES_BLOCK_SIZE;
        partial = aad_size % AES_BLOCK_SIZE;
        while (blocks--)
        {
            memcpy(big_a, aad, AES_BLOCK_SIZE);
            big_a[0] = BSWAP_64(big_a[0]);
            big_a[1] = BSWAP_64(big_a[1]);
            gcm->x[0] ^= big_a[0];
            gcm->x[1] ^= big_a[1];
            gmult(gcm->x, gcm->big_h);
            aad += AES_BLOCK_SIZE;
        }
        if (partial != 0)
        {
            memset(big_a, 0, AES_BLOCK_SIZE);
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
        blocks = in_size / AES_BLOCK_SIZE;
        partial = in_size % AES_BLOCK_SIZE;
        while (blocks--)
        {
            memcpy(big_c, _in, AES_BLOCK_SIZE);
            big_c[0] = BSWAP_64(big_c[0]);
            big_c[1] = BSWAP_64(big_c[1]);
            gcm->x[0] ^= big_c[0];
            gcm->x[1] ^= big_c[1];
            gmult(gcm->x, gcm->big_h);
            _in += AES_BLOCK_SIZE;
        }
        if (partial != 0)
        {
            memset(big_c, 0, AES_BLOCK_SIZE);
            memcpy(big_c, _in, partial);
            big_c[0] = BSWAP_64(big_c[0]);
            big_c[1] = BSWAP_64(big_c[1]);
            gcm->x[0] ^= big_c[0];
            gcm->x[1] ^= big_c[1];
            gmult(gcm->x, gcm->big_h);
        }
    }
}

bool HAL_LSCRYPT_AES_GCM_Decrypt_Final(aes_gcm_env *gcm, uint8_t *tag, uint32_t tag_size)
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
    memcpy(gcm->prime, gcm->x, AES_BLOCK_SIZE);

    mem_xor_n(gcm->prime, gcm->prime, gcm->j0, AES_BLOCK_SIZE);

    if (memcmp(gcm->prime, tag, tag_size) != 0)
    {
        return false;
    }
    return true;
}

HAL_StatusTypeDef HAL_LSCRYPT_AES_ECB_Encrypt_IT(const uint8_t *plaintext,uint32_t plaintextlength,uint8_t *ciphertext,uint32_t ciphertextlength)
{ 
    length_check(AES_MODE,ENCRYPT,plaintextlength,ciphertextlength);
    crypt_in_out_length_set(plaintext, ciphertext, plaintextlength);
    aes_config(false, false, true, true);
    crypt_start();
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSCRYPT_AES_ECB_Decrypt_IT(const uint8_t *ciphertext,uint32_t ciphertextlength,uint8_t *plaintext,uint32_t plaintextlength)
{
    length_check(AES_MODE,DECRYPT,plaintextlength,ciphertextlength);
    crypt_in_out_length_set(ciphertext,plaintext,ciphertextlength);
    aes_config(false,false,false,true);
    crypt_start();
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSCRYPT_AES_CBC_Encrypt_IT(const uint8_t *plaintext,uint32_t plaintextlength,uint8_t *ciphertext,uint32_t ciphertextlength)
{
    length_check(AES_MODE,ENCRYPT,plaintextlength,ciphertextlength);
    crypt_in_out_length_set(plaintext, ciphertext, plaintextlength);
    aes_config(true, true, true, true);
    crypt_start();
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSCRYPT_AES_CBC_Decrypt_IT(const uint8_t *ciphertext,uint32_t ciphertextlength,uint8_t *plaintext,uint32_t plaintextlength)
{
    length_check(AES_MODE,DECRYPT,plaintextlength,ciphertextlength);
    crypt_in_out_length_set(ciphertext,plaintext,ciphertextlength);
    aes_config(true,true,false,true);
    crypt_start();
    return HAL_OK;
}

// DES
HAL_StatusTypeDef HAL_LSCRYPT_DES_Key_Config(const uint32_t *key,enum tdes_key_type key_size)
{
    if(key_size != DES_KEY_64)
    {
        REG_FIELD_WR(LSCRYPT->CR, CRYPT_TDES, 1);
        REG_FIELD_WR(LSCRYPT->CR, CRYPT_DESKS, key_size);
    }
    else
    {
        REG_FIELD_WR(LSCRYPT->CR, CRYPT_TDES, 0); 
    }

    if(key_size == DES_KEY_64)
    {
        LSCRYPT->KEY0 = *key++;
        LSCRYPT->KEY1 = *key++;
    }
    else if(key_size == TDES_KEY_128)
    {
        LSCRYPT->KEY2 = *key++;
        LSCRYPT->KEY3 = *key++;
        LSCRYPT->KEY0 = *key++;
        LSCRYPT->KEY1 = *key++;
    }
    else
    {
        LSCRYPT->KEY4 = *key++;
        LSCRYPT->KEY5 = *key++;
        LSCRYPT->KEY2 = *key++;
        LSCRYPT->KEY3 = *key++;
        LSCRYPT->KEY0 = *key++;
        LSCRYPT->KEY1 = *key++;
    }
    return HAL_OK;
}

static void des_config(bool iv_en,bool cbc,bool enc,bool ie)
{
    MODIFY_REG(LSCRYPT->CR,CRYPT_CRYSEL_MASK|CRYPT_DMAEN_MASK|CRYPT_FIFOEN_MASK|CRYPT_IE_MASK|CRYPT_IVREN_MASK|CRYPT_MODE_MASK|CRYPT_ENCS_MASK,
        1<<CRYPT_CRYSEL_POS|0<<CRYPT_DMAEN_POS|0<<CRYPT_FIFOEN_POS|(ie?1:0)<<CRYPT_IE_POS|(iv_en?1:0)<<CRYPT_IVREN_POS|(cbc?1:0)<<CRYPT_MODE_POS|(enc?1:0)<<CRYPT_ENCS_POS);
}

static void des_enc_dec(bool enc, bool cbc)
{
    bool iv_en = cbc;
    do
    {
        des_config(iv_en,cbc,enc,false);    
        crypt_start();
        iv_en = false;
        while (REG_FIELD_RD(LSCRYPT->SR, CRYPT_DESRIF) == 0);
        LSCRYPT->ICFR = CRYPT_DESIF_MASK;
        crypt_end();
        if(length_residue == 0 && crypt_padding_mode == Padding_None)break;
    } while (length_out == length_in);
}

HAL_StatusTypeDef HAL_LSCRYPT_DES_ECB_Encrypt(const uint8_t *plaintext,uint32_t plaintextlength,uint8_t *ciphertext,uint32_t *ciphertextlength)
{
    length_check(DES_MODE,ENCRYPT,plaintextlength,*ciphertextlength);
    crypt_in_out_length_set(plaintext, ciphertext, plaintextlength);
    des_enc_dec(true, false);
    *ciphertextlength = length_out;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSCRYPT_DES_ECB_Decrypt(const uint8_t *ciphertext,uint32_t ciphertextlength,uint8_t *plaintext,uint32_t *plaintextlength)
{
    length_check(DES_MODE,DECRYPT,*plaintextlength,ciphertextlength);
    crypt_in_out_length_set(ciphertext, plaintext, ciphertextlength);
    des_enc_dec(false, false);
    *plaintextlength = length_out;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSCRYPT_DES_CBC_Encrypt(const uint8_t *plaintext,uint32_t plaintextlength,uint8_t *ciphertext,uint32_t *ciphertextlength)
{
    length_check(DES_MODE,ENCRYPT,plaintextlength,*ciphertextlength);
    crypt_in_out_length_set(plaintext, ciphertext, plaintextlength);
    des_enc_dec(true, true);
    *ciphertextlength = length_out;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSCRYPT_DES_CBC_Decrypt(const uint8_t *ciphertext,uint32_t ciphertextlength,uint8_t *plaintext,uint32_t *plaintextlength)
{
    length_check(DES_MODE,DECRYPT,*plaintextlength,ciphertextlength);
    crypt_in_out_length_set(ciphertext,plaintext,ciphertextlength);
    des_enc_dec(false,true);
    *plaintextlength = length_out;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSCRYPT_DES_ECB_Encrypt_IT(const uint8_t *plaintext,uint32_t plaintextlength,uint8_t *ciphertext,uint32_t ciphertextlength)
{
    length_check(DES_MODE,ENCRYPT,plaintextlength,ciphertextlength);
    crypt_in_out_length_set(plaintext, ciphertext, plaintextlength);
    des_config(false, false, true, true);
    crypt_start();
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSCRYPT_DES_ECB_Decrypt_IT(const uint8_t *ciphertext,uint32_t ciphertextlength,uint8_t *plaintext,uint32_t plaintextlength)
{
    length_check(DES_MODE,DECRYPT,plaintextlength,ciphertextlength);
    crypt_in_out_length_set(ciphertext,plaintext,ciphertextlength);
    des_config(false,false,false,true);
    crypt_start();
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSCRYPT_DES_CBC_Encrypt_IT(const uint8_t *plaintext,uint32_t plaintextlength,uint8_t *ciphertext,uint32_t ciphertextlength)
{
    length_check(DES_MODE,ENCRYPT,plaintextlength,ciphertextlength);
    crypt_in_out_length_set(plaintext, ciphertext, plaintextlength);
    des_config(true, true, true, true);
    crypt_start();
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSCRYPT_DES_CBC_Decrypt_IT(const uint8_t *ciphertext,uint32_t ciphertextlength,uint8_t *plaintext,uint32_t plaintextlength)
{
    length_check(DES_MODE,DECRYPT,plaintextlength,ciphertextlength);
    crypt_in_out_length_set(ciphertext,plaintext,ciphertextlength);
    des_config(true,true,false,true);
    crypt_start();
    return HAL_OK;
}

__attribute__((weak)) void HAL_LSCRYPT_DES_Complete_Callback(bool Encrypt,bool CBC,uint32_t length){}

__attribute__((weak)) void HAL_LSCRYPT_AES_Complete_Callback(bool Encrypt,bool CBC,uint32_t length){}

void HAL_LSCRYPT_IRQHandler()
{
    if (LSCRYPT->SR & CRYPT_AESRIF_MASK)
    {
        LSCRYPT->ICFR = CRYPT_AESIF_MASK;
        crypt_end();
        if (length_out == length_in)
        {
            if((length_residue == 0) && (crypt_padding_mode == Padding_None))
            {
                HAL_LSCRYPT_AES_Complete_Callback(REG_FIELD_RD(LSCRYPT->CR, CRYPT_ENCS), REG_FIELD_RD(LSCRYPT->CR, CRYPT_MODE), length_out);
            }
            else
            {
                crypt_start();
            }
        }
        else
        {
            HAL_LSCRYPT_AES_Complete_Callback(REG_FIELD_RD(LSCRYPT->CR, CRYPT_ENCS), REG_FIELD_RD(LSCRYPT->CR, CRYPT_MODE), length_out);
        }
    }
    else if (LSCRYPT->SR & CRYPT_DESRIF_MASK)
    {
        LSCRYPT->ICFR = CRYPT_DESIF_MASK;
        crypt_end();
        if (length_out == length_in)
        {
            if((length_residue == 0) && (crypt_padding_mode == Padding_None))
            {
                HAL_LSCRYPT_DES_Complete_Callback(REG_FIELD_RD(LSCRYPT->CR, CRYPT_ENCS), REG_FIELD_RD(LSCRYPT->CR, CRYPT_MODE), length_out);
            }
            else
            {
                crypt_start();
            }
        }
        else
        {
            HAL_LSCRYPT_DES_Complete_Callback(REG_FIELD_RD(LSCRYPT->CR, CRYPT_ENCS), REG_FIELD_RD(LSCRYPT->CR, CRYPT_MODE), length_out);
        }
    }
}