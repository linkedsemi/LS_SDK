#include "ls_hal_crypt.h"
#include "ls_msp_crypt.h"
#include "field_manipulate.h"
#include "ls_dbg.h"
 #include <stdlib.h>
#include <string.h>
#define AES_BLOCK_SIZE 16
static const uint8_t *current_in;
static uint8_t *current_out;
static uint32_t length_in;
static uint32_t length_out;
static uint32_t length_residue;
static enum padding_mode crypt_padding_mode = Padding_None;

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
    return data[0]<<24|data[1]<<16|data[2]<<8|data[3];
}

static inline void set_uint32_t(uint32_t src,uint8_t *dst)
{
    *dst++ = src>>24;
    *dst++ = src>>16;
    *dst++ = src>>8;
    *dst++ = src;
}

static void block_data_in(const uint8_t *in)
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

static void block_data_out(uint8_t *out)
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

static void crypt_data_in_Padding_PKCS7(const uint8_t *in_src, uint8_t *in_res,uint8_t read_length)
{
    for (int i = 0; i < AES_BLOCK_SIZE; i++)
    { 
        if(i < read_length)
        {
            in_res[i] = in_src[i];
        }
        else
        {
            length_out += 1;
             in_res[i] = AES_BLOCK_SIZE - read_length;
        }
    }
}

static void crypt_data_in_Padding_ANSIX923(const uint8_t *in_src, uint8_t *in_res,uint8_t read_length)
{
    for (int i = 0; i < AES_BLOCK_SIZE; i++)
    {
        if (i < read_length)
        {
            in_res[i] = in_src[i];
        }
        else
        {
            length_out += 1;
            in_res[i] = i == AES_BLOCK_SIZE - 1 ? AES_BLOCK_SIZE - read_length : 0;
        }
    }
}

static void crypt_data_in_Padding_ISO7816(const uint8_t *in_src, uint8_t *in_res,uint8_t read_length)
{
    for (int i = 0; i < AES_BLOCK_SIZE; i++)
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
    for (int i = 0; i < AES_BLOCK_SIZE; i++)
    {
        if (i < read_length)
        {
            in_res[i] = in_src[i];
        }
        else
        {
            length_out += 1;
            in_res[i] = i == AES_BLOCK_SIZE - 1 ? AES_BLOCK_SIZE - read_length : rand() % 256;
        }
    }
}

static void crypt_data_in()
{
    uint8_t read_length = length_residue >= AES_BLOCK_SIZE ? AES_BLOCK_SIZE : length_residue;
    if (read_length != AES_BLOCK_SIZE)
    {
        uint8_t data_buffer[AES_BLOCK_SIZE];
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
    if(REG_FIELD_RD(LSCRYPT->CR,CRYPT_ENCS) == 0 && length_residue == AES_BLOCK_SIZE && crypt_padding_mode != Padding_None)
    {
        uint8_t res_buffer[AES_BLOCK_SIZE];
        block_data_out(res_buffer);
        uint8_t padding_length = 0;
        int index = 0 ;
        switch (crypt_padding_mode)
        {
        case Padding_PKCS7:
            padding_length = res_buffer[AES_BLOCK_SIZE - 1];
            for (int i = 0; i < AES_BLOCK_SIZE; i++)
            {
                if (i < AES_BLOCK_SIZE - padding_length)
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
            padding_length = res_buffer[AES_BLOCK_SIZE - 1];
            for (int i = 0; i < AES_BLOCK_SIZE; i++)
            {
                if (i < AES_BLOCK_SIZE - padding_length)
                {
                    current_out[i] = res_buffer[i];
                }
                else if (i < AES_BLOCK_SIZE - 1)
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
            index = AES_BLOCK_SIZE - 1;
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
            padding_length = res_buffer[AES_BLOCK_SIZE - 1];
            while (index < AES_BLOCK_SIZE - padding_length )
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

static void aes_start()
{
    crypt_data_in();
    REG_FIELD_WR(LSCRYPT->CR,CRYPT_GO,1);
}

static void aes_end()
{
    crypt_data_out();
    current_in += AES_BLOCK_SIZE;
    current_out += AES_BLOCK_SIZE;
    length_residue = length_residue < AES_BLOCK_SIZE ? 0 : length_residue - AES_BLOCK_SIZE;
}

static void crypt_in_out_length_set(const uint8_t *in,uint8_t *out,uint32_t length)
{
    LS_ASSERT(crypt_padding_mode != Padding_None || length % 16 == 0);
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
        aes_start();
        iv_en = false;
        while (REG_FIELD_RD(LSCRYPT->SR, CRYPT_AESRIF) == 0);
        LSCRYPT->ICFR = CRYPT_AESIF_MASK;
        aes_end();
        if(length_residue == 0 && crypt_padding_mode == Padding_None)break;
    } while (length_out == length_in);
}

HAL_StatusTypeDef HAL_LSCRYPT_AES_ECB_Encrypt(const uint8_t *plaintext,uint32_t *length,uint8_t *ciphertext)
{
    crypt_in_out_length_set(plaintext,ciphertext,*length);
    aes_enc_dec(true,false);
    *length = length_out;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSCRYPT_AES_ECB_Decrypt(const uint8_t *ciphertext,uint32_t *length,uint8_t *plaintext)
{
    crypt_in_out_length_set(ciphertext,plaintext,*length);
    aes_enc_dec(false,false);
    *length = length_out;
    return HAL_OK;
}

static void iv_set(const uint32_t iv[4])
{
    LSCRYPT->IVR0 = iv[0];
    LSCRYPT->IVR1 = iv[1];
    LSCRYPT->IVR2 = iv[2];
    LSCRYPT->IVR3 = iv[3];
}

HAL_StatusTypeDef HAL_LSCRYPT_AES_CBC_Encrypt(const uint32_t iv[4],const uint8_t *plaintext,uint32_t *length,uint8_t *ciphertext)
{
    crypt_in_out_length_set(plaintext,ciphertext,*length);
    iv_set(iv);
    aes_enc_dec(true,true);
    *length = length_out;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSCRYPT_AES_CBC_Decrypt(const uint32_t iv[4],const uint8_t *ciphertext,uint32_t *length,uint8_t *plaintext)
{
    crypt_in_out_length_set(ciphertext,plaintext,*length);
    iv_set(iv);
    aes_enc_dec(false,true);
    *length = length_out;
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

__attribute__((weak)) void HAL_LSCRYPT_AES_Complete_Callback(bool Encrypt,bool CBC,uint32_t length){}

void HAL_LSCRYPT_IRQHandler()
{
    if (LSCRYPT->SR & CRYPT_AESRIF_MASK)
    {
        LSCRYPT->ICFR = CRYPT_AESIF_MASK;
        aes_end();
        if (length_out == length_in && !((length_residue == 0) & (crypt_padding_mode == Padding_None)))
        {
            aes_start();
        }
        else
        {
            HAL_LSCRYPT_AES_Complete_Callback(REG_FIELD_RD(LSCRYPT->CR, CRYPT_ENCS), REG_FIELD_RD(LSCRYPT->CR, CRYPT_MODE), length_out);
        }
    }
    if (LSCRYPT->SR & CRYPT_DESRIF_MASK)
    {
        LSCRYPT->ICFR = CRYPT_DESIF_MASK;
    }
}
