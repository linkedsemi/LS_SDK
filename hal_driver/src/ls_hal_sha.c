#include <string.h>
#include "ls_hal_sha.h"
#include "ls_msp_sha.h"
#include "field_manipulate.h"
#include "ls_dbg.h"
#include "compile_flag.h"
#define SHA_BLOCK_SIZE 64
#define SHA_PADDING_MOD 56
#define SHA_DATA_LENGTH_SIZE 8
static uint64_t total_length;
static uint32_t current_word;
static uint8_t current_block_bytes;
static bool first_update;

HAL_StatusTypeDef HAL_LSSHA_Init(void)
{
    HAL_LSSHA_MSP_Init();
    HAL_LSSHA_MSP_Busy_Set();
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSSHA_DeInit(void)
{
    HAL_LSSHA_MSP_Idle_Set();
    HAL_LSSHA_MSP_DeInit();
    return HAL_OK;
}

static void sha_variable_init()
{
    total_length = 0;
    current_block_bytes = 0;
    current_word = 0;
}

HAL_StatusTypeDef HAL_LSSHA_SHA256_Init()
{
    LSSHA->SHA_CTRL = FIELD_BUILD(SHA_FST_DAT,1)|FIELD_BUILD(SHA_CALC_SHA224,0)|FIELD_BUILD(SHA_CALC_SM3,0);
    first_update = false;
    sha_variable_init();
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSSHA_SHA224_Init()
{
    LSSHA->SHA_CTRL = FIELD_BUILD(SHA_FST_DAT,1)|FIELD_BUILD(SHA_CALC_SHA224,1)|FIELD_BUILD(SHA_CALC_SM3,0);
    first_update = false;
    sha_variable_init();
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSSHA_SM3_Init()
{
    LSSHA->SHA_CTRL = FIELD_BUILD(SHA_FST_DAT,1)|FIELD_BUILD(SHA_CALC_SHA224,0)|FIELD_BUILD(SHA_CALC_SM3,1);
    first_update = false;
    sha_variable_init();
    return HAL_OK;
}

static void byte_update(const uint8_t val)
{
    switch(current_block_bytes%sizeof(uint32_t))
    {
    case 0:
        MODIFY_REG(current_word,0xff,val);
    break;
    case 1:
        MODIFY_REG(current_word,0xff00,val<<8);
    break;
    case 2:
        MODIFY_REG(current_word,0xff0000,val<<16);
    break;
    case 3:
        MODIFY_REG(current_word,0xff000000,val<<24);
    break;
    }
    current_block_bytes++;
    if(current_block_bytes%sizeof(uint32_t)==0)
    {
        LSSHA->FIFO_DAT = current_word;
    }
}

static void sha_start(bool end)
{
    if(current_block_bytes==SHA_BLOCK_SIZE)
    {
        current_block_bytes = 0;
        while((LSSHA->INTR_R&SHA_FSM_END_INTR_MASK)==0);
        LSSHA->INTR_C = SHA_FSM_END_INTR_MASK;
        if(!end)    LSSHA->SHA_START = 1;
    }
}

HAL_StatusTypeDef HAL_LSSHA_Update(const uint8_t *data,uint32_t length)
{
    if((!first_update))
    {
        LSSHA->SHA_START = 1;
        LSSHA->SHA_CTRL &= ~SHA_FST_DAT_MASK;
        first_update = true;
    }
    LSSHA->INTR_M = 0;
    total_length += length*8;
    while(length)
    {
        do{
            byte_update(*data);
            data++;
            length--;
        }while(current_block_bytes!=SHA_BLOCK_SIZE&&length);
        sha_start(false);
    }
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSSHA_Final(uint8_t *digest)
{
    byte_update(0x80);
    while(current_block_bytes!=SHA_PADDING_MOD)
    {
        sha_start(false);
        byte_update(0x00);
    }
    byte_update(total_length>>56);
    byte_update(total_length>>48);
    byte_update(total_length>>40);
    byte_update(total_length>>32);
    byte_update(total_length>>24);
    byte_update(total_length>>16);
    byte_update(total_length>>8);
    byte_update(total_length>>0);
    sha_start(true);
    uint8_t i;
    uint8_t count = REG_FIELD_RD(LSSHA->SHA_CTRL,SHA_CALC_SHA224) != 1 ? SHA256_WORDS_NUM : SHA224_WORDS_NUM;
    for (i = 0; i < count; ++i)
    {
        uint32_t val = LSSHA->SHA_RSLT[i];
        *digest++ = val>>24;
        *digest++ = val>>16;
        *digest++ = val>>8;
        *digest++ = val;
    }
    return HAL_OK;
}

#define B 64
#define I_PAD 0x36
#define O_PAD 0x5C

HAL_StatusTypeDef HAL_LSSHA_SHA256_HMAC(uint8_t out[SHA256_BYTES_NUM], uint8_t *data, uint32_t data_len, uint8_t *key, uint32_t key_len)
{
    uint8_t kh[SHA256_BYTES_NUM];
    HAL_LSSHA_SHA256_Init();

    /*
     * If the key length is bigger than the buffer size B, apply the hash
     * function to it first and use the result instead.
     */
    if (key_len > B)
    {
        HAL_LSSHA_Update(key, key_len);
        HAL_LSSHA_Final(kh);
        key_len = SHA256_BYTES_NUM;
        key = kh;
    }

    /*
     * (1) append zeros to the end of K to create a B byte string
     *     (e.g., if K is of length 20 bytes and B=64, then K will be
     *     appended with 44 zero bytes 0x00)
     * (2) XOR (bitwise exclusive-OR) the B byte string computed in step
     *     (1) with ipad
     */
    uint8_t kx[B];
    for (uint32_t i = 0; i < key_len; i++)
        kx[i] = I_PAD ^ key[i];
    for (uint32_t i = key_len; i < B; i++)
        kx[i] = I_PAD ^ 0;

    /*
     * (3) append the stream of data 'text' to the B byte string resulting
     *     from step (2)
     * (4) apply H to the stream generated in step (3)
     */
    HAL_LSSHA_Update(kx, B);
    HAL_LSSHA_Update(data, data_len);
    HAL_LSSHA_Final(out);
    HAL_LSSHA_SHA256_Init();

    /*
     * (5) XOR (bitwise exclusive-OR) the B byte string computed in
     *     step (1) with opad
     *
     * NOTE: The "kx" variable is reused.
     */
    for (uint8_t i = 0; i < key_len; i++)
        kx[i] = O_PAD ^ key[i];
    for (uint8_t i = key_len; i < B; i++)
        kx[i] = O_PAD ^ 0;

    /*
     * (6) append the H result from step (4) to the B byte string
     *     resulting from step (5)
     * (7) apply H to the stream generated in step (6) and output
     *     the result
     */
    HAL_LSSHA_Update(kx, B);
    HAL_LSSHA_Update(out, SHA256_BYTES_NUM);
    HAL_LSSHA_Final(out);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSSHA_SHA224_HMAC(uint8_t out[SHA224_BYTES_NUM], uint8_t *data, uint32_t data_len, uint8_t *key, uint32_t key_len)
{
    uint8_t kh[SHA224_BYTES_NUM];
    HAL_LSSHA_SHA224_Init();

    if (key_len > B)
    {
        HAL_LSSHA_Update(key, key_len);
        HAL_LSSHA_Final(kh);
        key_len = SHA224_BYTES_NUM;
        key = kh;
    }

    uint8_t kx[B];
    for (uint32_t i = 0; i < key_len; i++)
        kx[i] = I_PAD ^ key[i];
    for (uint32_t i = key_len; i < B; i++)
        kx[i] = I_PAD ^ 0;

    HAL_LSSHA_Update(kx, B);
    HAL_LSSHA_Update(data, data_len);
    HAL_LSSHA_Final((uint8_t *)out);
    HAL_LSSHA_SHA224_Init();

    for (uint8_t i = 0; i < key_len; i++)
        kx[i] = O_PAD ^ key[i];
    for (uint8_t i = key_len; i < B; i++)
        kx[i] = O_PAD ^ 0;

    HAL_LSSHA_Update(kx, B);
    HAL_LSSHA_Update(out, SHA224_BYTES_NUM);
    HAL_LSSHA_Final(out);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSSHA_SM3_HMAC(uint8_t out[SM3_BYTES_NUM], uint8_t *data, uint32_t data_len, uint8_t *key, uint32_t key_len)
{
    uint8_t kh[SM3_BYTES_NUM];
    uint8_t kx[B];
    uint8_t i;

    if (key_len > B)
    {
        HAL_LSSHA_SM3_Init();
        HAL_LSSHA_Update(key, key_len);
        HAL_LSSHA_Final(kh);
        key_len = SM3_BYTES_NUM;
        key = kh;
    }

    for (i = 0; i < key_len; i++)
        kx[i] = I_PAD ^ key[i];
    for (i = key_len; i < B; i++)
        kx[i] = I_PAD ^ 0;

    HAL_LSSHA_SM3_Init();
    HAL_LSSHA_Update(kx, B);
    HAL_LSSHA_Update(data, data_len);
    HAL_LSSHA_Final(out);

    for (i = 0; i < key_len; i++)
        kx[i] = O_PAD ^ key[i];
    for (i = key_len; i < B; i++)
        kx[i] = O_PAD ^ 0;

    HAL_LSSHA_SM3_Init();
    HAL_LSSHA_Update(kx, B);
    HAL_LSSHA_Update(out, SM3_BYTES_NUM);
    HAL_LSSHA_Final(out);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSSHA_SHA256(const uint8_t *data, uint32_t length, uint8_t hash_val[SHA256_BYTES_NUM])
{
    HAL_LSSHA_SHA256_Init();
    HAL_LSSHA_Update(data, length);
    HAL_LSSHA_Final(hash_val);
    return HAL_OK;
}

bool HAL_LSSHA_SM3_KDF(uint8_t *Z, uint32_t Zlen, uint8_t *out, uint32_t out_len)
{
    uint32_t ct = 0x1;
    uint8_t Data[4];
	uint32_t digest_len = 0x20;
	uint8_t digest[0x20];
	uint32_t index = (out_len + 0x1f) / 0x20;

    if (Z == NULL || out_len == 0 || Zlen == 0 || out == NULL)
        return false;

    for (uint32_t i = 0; i < index; i++)
    {
        Data[0] = (ct >> 24) & 0xFF;
        Data[1] = (ct >> 16) & 0xFF;
        Data[2] = (ct >> 8) & 0xFF;
        Data[3] = (ct >> 0) & 0xFF;
        HAL_LSSHA_SM3_Init();
        HAL_LSSHA_Update(Z, Zlen);
        HAL_LSSHA_Update(Data, 4);
        HAL_LSSHA_Final(digest);
        if ((i == index - 1) && (out_len % 0x20 != 0))
                digest_len = (out_len) % 0x20;
        memcpy(out + 0x20 * i, digest, digest_len);
        ct++;
    }
    return true;
}

void LSSHA_IRQHandler(void){}