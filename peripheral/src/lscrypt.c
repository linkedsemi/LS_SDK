#include "lscrypt.h"
#include "lscrypt_msp.h"
#include "field_manipulate.h"
#include "ls_dbg.h"
#define AES_BLOCK_SIZE 16
static const uint8_t *crypt_in;
static uint8_t *crypt_out;
static uint32_t crypt_length;
static uint8_t current_length;
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

static uint32_t get_uint32_t(const uint8_t *data)
{
    return data[3]<<24|data[2]<<16|data[1]<<8|data[0];
}

static void set_uint32_t(uint32_t src,uint8_t *dst)
{
    *dst++ = src;
    *dst++ = src>>8;
    *dst++ = src>>16;
    *dst++ = src>>24;
}

static uint32_t last_word_data_pack(uint8_t length,const uint8_t *in)
{
    LS_ASSERT(length<4);
    uint32_t data = 0;
    switch(length)
    {
    case 3:
        data = in[2]<<16|in[1]<<8|in[0];
    break;
    case 2:
        data = in[1]<<8|in[0];
    break;
    case 1:
        data = in[0];
    break;
    }
    return data;
}

static void last_word_data_unpack(uint8_t length,uint8_t *data,uint32_t word)
{
    LS_ASSERT(length<4);
    switch(length)
    {
    case 3:
        *data++ = word;
        *data++ = word>>8;
        *data++ = word>>16;
    break;
    case 2:
        *data++ = word;
        *data++ = word>>8;
    break;
    case 1:
        *data++ = word;
    break;
    }
}

static void crypt_data_in()
{
    const uint8_t *in = crypt_in;
    switch(current_length)
    {
    case AES_BLOCK_SIZE:
        LSCRYPT->DATA0 = get_uint32_t(in);
        in += sizeof(uint32_t);
        LSCRYPT->DATA1 = get_uint32_t(in);
        in += sizeof(uint32_t);
        LSCRYPT->DATA2 = get_uint32_t(in);
        in += sizeof(uint32_t);
        LSCRYPT->DATA3 = get_uint32_t(in);
        in += sizeof(uint32_t);
    break;
    case 15: case 14: case 13: case 12:
        LSCRYPT->DATA0 = get_uint32_t(in);
        in += sizeof(uint32_t);
        LSCRYPT->DATA1 = get_uint32_t(in);
        in += sizeof(uint32_t);
        LSCRYPT->DATA2 = get_uint32_t(in);
        in += sizeof(uint32_t);
        LSCRYPT->DATA3 = last_word_data_pack(current_length - 12,in);
    break;
    case 11: case 10: case 9: case 8:
        LSCRYPT->DATA0 = get_uint32_t(in);
        in += sizeof(uint32_t);
        LSCRYPT->DATA1 = get_uint32_t(in);
        in += sizeof(uint32_t);
        LSCRYPT->DATA2 = last_word_data_pack(current_length - 8,in);
        LSCRYPT->DATA3 = 0;
    break;
    case 7: case 6: case 5: case 4:
        LSCRYPT->DATA0 = get_uint32_t(in);
        in += sizeof(uint32_t);
        LSCRYPT->DATA1 = last_word_data_pack(current_length - 4,in);
        LSCRYPT->DATA2 = 0;
        LSCRYPT->DATA3 = 0;
    break;
    case 3: case 2: case 1: case 0:
        LSCRYPT->DATA0 = last_word_data_pack(current_length,in);
        LSCRYPT->DATA1 = 0;
        LSCRYPT->DATA2 = 0;
        LSCRYPT->DATA3 = 0;
    break;
    }
}

static void crypt_data_out()
{
    uint8_t *out = crypt_out;
    switch(current_length)
    {
    case AES_BLOCK_SIZE:
        set_uint32_t(LSCRYPT->RES0,out);
        out += sizeof(uint32_t);
        set_uint32_t(LSCRYPT->RES1,out);
        out += sizeof(uint32_t);
        set_uint32_t(LSCRYPT->RES2,out);
        out += sizeof(uint32_t);
        set_uint32_t(LSCRYPT->RES3,out);
        out += sizeof(uint32_t);
    break;
    case 15: case 14: case 13: case 12:
        set_uint32_t(LSCRYPT->RES0,out);
        out += sizeof(uint32_t);
        set_uint32_t(LSCRYPT->RES1,out);
        out += sizeof(uint32_t);
        set_uint32_t(LSCRYPT->RES2,out);
        out += sizeof(uint32_t);
        last_word_data_unpack(current_length - 12,out,LSCRYPT->RES3);
    break;
    case 11: case 10: case 9: case 8:
        set_uint32_t(LSCRYPT->RES0,out);
        out += sizeof(uint32_t);
        set_uint32_t(LSCRYPT->RES1,out);
        out += sizeof(uint32_t);
        last_word_data_unpack(current_length - 8,out,LSCRYPT->RES2);
    break;
    case 7: case 6: case 5: case 4:
        set_uint32_t(LSCRYPT->RES0,out);
        out += sizeof(uint32_t);
        last_word_data_unpack(current_length - 4,out,LSCRYPT->RES1);
    break;
    case 3: case 2: case 1: case 0:
        last_word_data_unpack(current_length,out,LSCRYPT->RES0);
    break;
    }
}

static void aes_config(bool iv_en,bool cbc,bool enc,bool ie)
{
    MODIFY_REG(LSCRYPT->CR,CRYPT_CRYSEL_MASK|CRYPT_DMAEN_MASK|CRYPT_FIFOEN_MASK|CRYPT_IE_MASK|CRYPT_IVREN_MASK|CRYPT_MODE_MASK|CRYPT_ENCS_MASK,
        0<<CRYPT_CRYSEL_POS|0<<CRYPT_DMAEN_POS|0<<CRYPT_FIFOEN_POS|(ie?1:0)<<CRYPT_IE_POS|(iv_en?1:0)<<CRYPT_IVREN_POS|(cbc?1:0)<<CRYPT_MODE_POS|(enc?1:0)<<CRYPT_ENCS_POS);
}

static void aes_start()
{
    current_length = crypt_length>=AES_BLOCK_SIZE ? AES_BLOCK_SIZE : crypt_length;
    crypt_data_in();
    REG_FIELD_WR(LSCRYPT->CR,CRYPT_GO,1);
}

static void crypt_in_out_length_set(const uint8_t *in,uint8_t *out,uint32_t length)
{
    crypt_in = in;
    crypt_out = out;
    crypt_length = length;
}

static void aes_end()
{
    crypt_data_out();
    crypt_in += current_length;
    crypt_out += current_length;
    crypt_length -= current_length;
}

static void aes_enc_dec(bool enc,bool cbc)
{
    bool iv_en = cbc;
    do
    {
        aes_config(iv_en,cbc,enc,false);
        aes_start();
        iv_en = false;
        while(REG_FIELD_RD(LSCRYPT->SR,CRYPT_AESRIF)==0);
        LSCRYPT->ICFR = CRYPT_AESIF_MASK;
        aes_end();
    }while(crypt_length);
}

HAL_StatusTypeDef HAL_LSCRYPT_AES_ECB_Encrypt(const uint8_t *plaintext,uint32_t length,uint8_t *ciphertext)
{
    crypt_in_out_length_set(plaintext,ciphertext,length);
    aes_enc_dec(true,false);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSCRYPT_AES_ECB_Decrypt(const uint8_t *ciphertext,uint32_t length,uint8_t *plaintext)
{
    crypt_in_out_length_set(ciphertext,plaintext,length);
    aes_enc_dec(false,false);
    return HAL_OK;
}

static void iv_set(const uint32_t iv[4])
{
    LSCRYPT->IVR0 = iv[0];
    LSCRYPT->IVR1 = iv[1];
    LSCRYPT->IVR2 = iv[2];
    LSCRYPT->IVR3 = iv[3];
}

HAL_StatusTypeDef HAL_LSCRYPT_AES_CBC_Encrypt(const uint32_t iv[4],const uint8_t *plaintext,uint32_t length,uint8_t *ciphertext)
{
    crypt_in_out_length_set(plaintext,ciphertext,length);
    iv_set(iv);
    aes_enc_dec(true,true);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSCRYPT_AES_CBC_Decrypt(const uint32_t iv[4],const uint8_t *ciphertext,uint32_t length,uint8_t *plaintext)
{
    crypt_in_out_length_set(ciphertext,plaintext,length);
    iv_set(iv);
    aes_enc_dec(false,true);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSCRYPT_AES_ECB_Encrypt_IT(const uint8_t *plaintext,uint32_t length,uint8_t *ciphertext)
{
    crypt_in_out_length_set(plaintext,ciphertext,length);
    aes_config(false,false,true,true);
    aes_start();
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSCRYPT_AES_ECB_Decrypt_IT(const uint8_t *ciphertext,uint32_t length,uint8_t *plaintext)
{
    crypt_in_out_length_set(ciphertext,plaintext,length);
    aes_config(false,false,false,true);
    aes_start();
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSCRYPT_AES_CBC_Encrypt_IT(const uint32_t iv[4],const uint8_t *plaintext,uint32_t length,uint8_t *ciphertext)
{
    crypt_in_out_length_set(plaintext,ciphertext,length);
    iv_set(iv);
    aes_config(true,true,true,true);
    aes_start();
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSCRYPT_AES_CBC_Decrypt_IT(const uint32_t iv[4],const uint8_t *ciphertext,uint32_t length,uint8_t *plaintext)
{
    crypt_in_out_length_set(ciphertext,plaintext,length);
    iv_set(iv);
    aes_config(true,true,false,true);
    aes_start();
    return HAL_OK;
}

__attribute__((weak)) void HAL_LSCRYPT_AES_Complete_Callback(bool Encrypt,bool CBC){}

void HAL_LSCRYPT_IRQHandler()
{
    if(LSCRYPT->SR&CRYPT_AESRIF_MASK)
    {
        LSCRYPT->ICFR = CRYPT_AESIF_MASK;
        aes_end();
        if(crypt_length)
        {
            aes_start();
        }else{
            HAL_LSCRYPT_AES_Complete_Callback(REG_FIELD_RD(LSCRYPT->CR,CRYPT_ENCS),REG_FIELD_RD(LSCRYPT->CR,CRYPT_MODE));
        }
    }
    if(LSCRYPT->SR&CRYPT_DESRIF_MASK)
    {

    }
}
