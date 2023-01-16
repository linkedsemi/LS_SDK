#include <string.h>
#include <stdlib.h>
#include "ls_hal_crypt.h"
#include "platform.h"
#include "ls_soc_gpio.h"
#include "log.h"

enum lscrypt_des_type
{
    LSCRYPT_DES_ECB_ENCRYPT_64 = 0,
    LSCRYPT_DES_ECB_DECRYPT_64,
    LSCRYPT_DES_CBC_ENCRYPT_64,
    LSCRYPT_DES_CBC_DECRYPT_64,

    LSCRYPT_TDES_ECB_ENCRYPT_64,
    LSCRYPT_TDES_ECB_DECRYPT_64,
    LSCRYPT_TDES_CBC_ENCRYPT_64,
    LSCRYPT_TDES_CBC_DECRYPT_64,

    LSCRYPT_TDES_ECB_ENCRYPT_128,
    LSCRYPT_TDES_ECB_DECRYPT_128,
    LSCRYPT_TDES_CBC_ENCRYPT_128,
    LSCRYPT_TDES_CBC_DECRYPT_128,

    LSCRYPT_TDES_ECB_ENCRYPT_192,
    LSCRYPT_TDES_ECB_DECRYPT_192,
    LSCRYPT_TDES_CBC_ENCRYPT_192,
    LSCRYPT_TDES_CBC_DECRYPT_192
};
volatile enum lscrypt_des_type lscrypt_des_type_flag = LSCRYPT_TDES_ECB_ENCRYPT_128;

/**des_cbc-ecb-key-ciphertext-64**/
const uint32_t des_tdes_cbc_ecb_key_64[] = {
    0x05060708,
    0x01020304};

/**tdes_cbc-ecb-key-ciphertext-128**/
const uint32_t tdes_cbc_ecb_key_128[] = {
    0xA5A6A7A8,
    0xA1A2A3A4,
    0x05060708,
    0x01020304};

/*ECB MODE ------ Plaintext is a multiple of 8*/
const uint8_t tdes_ecb_ciphertext_128_None_aligned[] = {
    0x53,0x40,0xB5,0xDF,0x02,0xF1,0x6A,0x66,0x53,0x40,0xB5,0xDF,0x02,0xF1,0x6A,0x66};

const uint8_t tdes_ecb_ciphertext_128_PKCS7_aligned[] = {
    0x53,0x40,0xB5,0xDF,0x02,0xF1,0x6A,0x66,0x53,0x40,0xB5,0xDF,0x02,0xF1,0x6A,0x66,
    0x7A,0x4C,0xA7,0x1C,0x7D,0xE9,0x2E,0x0B};

const uint8_t tdes_ecb_ciphertext_128_ANSIX923_aligned[] = {
    0x53,0x40,0xB5,0xDF,0x02,0xF1,0x6A,0x66,0x53,0x40,0xB5,0xDF,0x02,0xF1,0x6A,0x66,
    0x0C,0x0F,0xF7,0xFC,0x38,0x0A,0xD0,0x68};

const uint8_t tdes_ecb_ciphertext_128_ISO7816_aligned[] = {
    0x53,0x40,0xB5,0xDF,0x02,0xF1,0x6A,0x66,0x53,0x40,0xB5,0xDF,0x02,0xF1,0x6A,0x66,
    0xC4,0x58,0x23,0x1E,0x23,0x0D,0x1c,0xBC};

const uint8_t tdes_ecb_ciphertext_128_ISO10126_aligned[] = {
    0x53,0x40,0xB5,0xDF,0x02,0xF1,0x6A,0x66,0x53,0x40,0xB5,0xDF,0x02,0xF1,0x6A,0x66,
    0x26,0xad,0xb2,0x79,0x6c,0xd2,0x6f,0x6c};

/**cbc-iv**/
const uint32_t cbc_iv[] = {
    0x05060708,
    0x01020304};

/**cbc-ecb-plaintext**/
const uint8_t cbc_ecb_plaintext_aligned[] = {
    0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};

const uint8_t cbc_ecb_plaintext_unaligned[] = {
    0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x01,0x02,0x03};

/**buff**/
uint8_t ciphertext_buff[24];
uint8_t plaintext_buff[24];
uint32_t encrypt_expected_length;
uint32_t decrypt_expected_length = sizeof(cbc_ecb_plaintext_aligned);
enum padding_mode mode;

void des_init(void)
{
    HAL_LSCRYPT_Init();
}

void crypt_ecb_test_128_None(void)
{
    HAL_LSCRYPT_Block_Padding_Mode_Set(mode);
    HAL_LSCRYPT_DES_Key_Config(tdes_cbc_ecb_key_128,TDES_KEY_128);

    HAL_LSCRYPT_DES_ECB_Encrypt_IT(cbc_ecb_plaintext_aligned,sizeof(cbc_ecb_plaintext_aligned),ciphertext_buff,sizeof(ciphertext_buff));    
    while (lscrypt_des_type_flag == LSCRYPT_TDES_ECB_ENCRYPT_128);

    HAL_LSCRYPT_DES_ECB_Decrypt_IT(tdes_ecb_ciphertext_128_None_aligned,sizeof(tdes_ecb_ciphertext_128_None_aligned),plaintext_buff,sizeof(plaintext_buff));    
    while (lscrypt_des_type_flag == LSCRYPT_TDES_ECB_DECRYPT_128);
}

void crypt_ecb_test_128_PKCS7(void)
{
    HAL_LSCRYPT_Block_Padding_Mode_Set(mode);
    HAL_LSCRYPT_DES_Key_Config(tdes_cbc_ecb_key_128,TDES_KEY_128);

    HAL_LSCRYPT_DES_ECB_Encrypt_IT(cbc_ecb_plaintext_aligned,sizeof(cbc_ecb_plaintext_aligned),ciphertext_buff,sizeof(ciphertext_buff));    
    while (lscrypt_des_type_flag == LSCRYPT_TDES_ECB_ENCRYPT_128);

    HAL_LSCRYPT_DES_ECB_Decrypt_IT(tdes_ecb_ciphertext_128_PKCS7_aligned,sizeof(tdes_ecb_ciphertext_128_PKCS7_aligned),plaintext_buff,sizeof(plaintext_buff));    
    while (lscrypt_des_type_flag == LSCRYPT_TDES_ECB_DECRYPT_128);
}

void crypt_ecb_test_128_ANSIX923(void)
{
    HAL_LSCRYPT_Block_Padding_Mode_Set(mode);
    HAL_LSCRYPT_DES_Key_Config(tdes_cbc_ecb_key_128,TDES_KEY_128);

    HAL_LSCRYPT_DES_ECB_Encrypt_IT(cbc_ecb_plaintext_aligned,sizeof(cbc_ecb_plaintext_aligned),ciphertext_buff,sizeof(ciphertext_buff));    
    while (lscrypt_des_type_flag == LSCRYPT_TDES_ECB_ENCRYPT_128);

    HAL_LSCRYPT_DES_ECB_Decrypt_IT(tdes_ecb_ciphertext_128_ANSIX923_aligned,sizeof(tdes_ecb_ciphertext_128_ANSIX923_aligned),plaintext_buff,sizeof(plaintext_buff));    
    while (lscrypt_des_type_flag == LSCRYPT_TDES_ECB_DECRYPT_128);
}

void crypt_ecb_test_128_ISO7816(void)
{
    HAL_LSCRYPT_Block_Padding_Mode_Set(mode);
    HAL_LSCRYPT_DES_Key_Config(tdes_cbc_ecb_key_128,TDES_KEY_128);

    HAL_LSCRYPT_DES_ECB_Encrypt_IT(cbc_ecb_plaintext_aligned,sizeof(cbc_ecb_plaintext_aligned),ciphertext_buff,sizeof(ciphertext_buff));    
    while (lscrypt_des_type_flag == LSCRYPT_TDES_ECB_ENCRYPT_128);

    HAL_LSCRYPT_DES_ECB_Decrypt_IT(tdes_ecb_ciphertext_128_ISO7816_aligned,sizeof(tdes_ecb_ciphertext_128_ISO7816_aligned),plaintext_buff,sizeof(plaintext_buff));    
    while (lscrypt_des_type_flag == LSCRYPT_TDES_ECB_DECRYPT_128);
}

void crypt_ecb_test_128_ISO10126(void)
{
    HAL_LSCRYPT_Block_Padding_Mode_Set(mode);
    HAL_LSCRYPT_DES_Key_Config(tdes_cbc_ecb_key_128,TDES_KEY_128);

    HAL_LSCRYPT_DES_ECB_Encrypt_IT(cbc_ecb_plaintext_aligned,sizeof(cbc_ecb_plaintext_aligned),ciphertext_buff,sizeof(ciphertext_buff));    
    while (lscrypt_des_type_flag == LSCRYPT_TDES_ECB_ENCRYPT_128);

    HAL_LSCRYPT_DES_ECB_Decrypt_IT(ciphertext_buff,sizeof(ciphertext_buff),plaintext_buff,sizeof(plaintext_buff));    
    while (lscrypt_des_type_flag == LSCRYPT_TDES_ECB_DECRYPT_128);
}


int main()
{
    sys_init_none();
    des_init();
    mode = Padding_None;
    encrypt_expected_length = sizeof(cbc_ecb_plaintext_aligned);
    crypt_ecb_test_128_None();
    mode = Padding_PKCS7;
    encrypt_expected_length = sizeof(cbc_ecb_plaintext_aligned) + 8 - sizeof(cbc_ecb_plaintext_aligned) % 8;
    crypt_ecb_test_128_PKCS7();
    mode = Padding_ANSIX923;
    crypt_ecb_test_128_ANSIX923();
    mode = Padding_ISO7816;
    crypt_ecb_test_128_ISO7816();
    mode = Padding_ISO10126;
    crypt_ecb_test_128_ISO10126();
}

void HAL_LSCRYPT_DES_Complete_Callback(bool Encrypt, bool CBC , uint32_t length)
{
    switch (mode)
    {
    case Padding_None:
        switch (lscrypt_des_type_flag)
        {
        case LSCRYPT_TDES_ECB_ENCRYPT_128:
        {
            if (!(memcmp(tdes_ecb_ciphertext_128_None_aligned, ciphertext_buff, sizeof(tdes_ecb_ciphertext_128_None_aligned))) && (length == encrypt_expected_length))
            {
                LOG_I("CRYPT_TDES_ECB_ENCRYPT_Padding_None_TEST_SUCCESS!------Length of encrypted data = %d",length);
            }
            else
            {
                LOG_I("CRYPT_TDES_ECB_ENCRYPT_Padding_None_TEST_FAIL!");
            }
            lscrypt_des_type_flag = LSCRYPT_TDES_ECB_DECRYPT_128;
        }
        break;
        case LSCRYPT_TDES_ECB_DECRYPT_128:
        {
            if (!(memcmp(cbc_ecb_plaintext_aligned, plaintext_buff, sizeof(cbc_ecb_plaintext_aligned))) && (length == decrypt_expected_length))
            {
                LOG_I("CRYPT_TDES_ECB_DECRYPT_Padding_None_TEST_SUCCESS!------Length of encrypted data = %d",length);
            }
            else
            {
                LOG_I("CRYPT_TDES_ECB_DECRYPT_Padding_None_TEST_FAIL!");
            }
            lscrypt_des_type_flag = LSCRYPT_TDES_ECB_ENCRYPT_128;
        }
        break;
        default:
            break;
        }
        break;
    case Padding_PKCS7:
        switch (lscrypt_des_type_flag)
        {
        case LSCRYPT_TDES_ECB_ENCRYPT_128:
        {
            if (!(memcmp(tdes_ecb_ciphertext_128_PKCS7_aligned, ciphertext_buff, sizeof(tdes_ecb_ciphertext_128_PKCS7_aligned))) && (length == encrypt_expected_length))
            {
                LOG_I("CRYPT_TDES_ECB_ENCRYPT_Padding_PKCS7_TEST_SUCCESS!------Length of encrypted data = %d",length);
            }
            else
            {
                LOG_I("CRYPT_TDES_ECB_ENCRYPT_Padding_PKCS7_TEST_FAIL!");
            }
            lscrypt_des_type_flag = LSCRYPT_TDES_ECB_DECRYPT_128;
        }
        break;
        case LSCRYPT_TDES_ECB_DECRYPT_128:
        {
            if (!(memcmp(cbc_ecb_plaintext_aligned, plaintext_buff, sizeof(cbc_ecb_plaintext_aligned))) && (length == decrypt_expected_length))
            {
                LOG_I("CRYPT_TDES_ECB_DECRYPT_Padding_PKCS7_TEST_SUCCESS!------Length of encrypted data = %d",length);
            }
            else
            {
                LOG_I("CRYPT_TDES_ECB_DECRYPT_Padding_PKCS7_TEST_FAIL!");
            }
            lscrypt_des_type_flag = LSCRYPT_TDES_ECB_ENCRYPT_128;
        }
        break;
        default:
            break;
        }
        break;    
    case Padding_ANSIX923:
        switch (lscrypt_des_type_flag)
        {
        case LSCRYPT_TDES_ECB_ENCRYPT_128:
        {
            if (!(memcmp(tdes_ecb_ciphertext_128_ANSIX923_aligned, ciphertext_buff, sizeof(tdes_ecb_ciphertext_128_ANSIX923_aligned))) && (length == encrypt_expected_length))
            {
                LOG_I("CRYPT_TDES_ECB_ENCRYPT_Padding_ANSIX923_TEST_SUCCESS!------Length of encrypted data = %d",length);
            }
            else
            {
                LOG_I("CRYPT_TDES_ECB_ENCRYPT_Padding_ANSIX923_TEST_FAIL!");
            }
            lscrypt_des_type_flag = LSCRYPT_TDES_ECB_DECRYPT_128;
        }
        break;
        case LSCRYPT_TDES_ECB_DECRYPT_128:
        {
            if (!(memcmp(cbc_ecb_plaintext_aligned, plaintext_buff, sizeof(cbc_ecb_plaintext_aligned))) && (length == decrypt_expected_length))
            {
                LOG_I("CRYPT_TDES_ECB_DECRYPT_Padding_ANSIX923_TEST_SUCCESS!------Length of encrypted data = %d",length);
            }
            else
            {
                LOG_I("CRYPT_TDES_ECB_DECRYPT_Padding_ANSIX923_TEST_FAIL!");
            }
            lscrypt_des_type_flag = LSCRYPT_TDES_ECB_ENCRYPT_128;
        }
        break;
        default:
            break;
        }
        break;      
    case Padding_ISO7816:
        switch (lscrypt_des_type_flag)
        {
        case LSCRYPT_TDES_ECB_ENCRYPT_128:
        {
            if (!(memcmp(tdes_ecb_ciphertext_128_ISO7816_aligned, ciphertext_buff, sizeof(tdes_ecb_ciphertext_128_ISO7816_aligned))) && (length == encrypt_expected_length))
            {
                LOG_I("CRYPT_TDES_ECB_ENCRYPT_Padding_ISO7816_TEST_SUCCESS!------Length of encrypted data = %d",length);
            }
            else
            {
                LOG_I("CRYPT_TDES_ECB_ENCRYPT_Padding_ISO7816_TEST_FAIL!");
            }
            lscrypt_des_type_flag = LSCRYPT_TDES_ECB_DECRYPT_128;
        }
        break;
        case LSCRYPT_TDES_ECB_DECRYPT_128:
        {
            if (!(memcmp(cbc_ecb_plaintext_aligned, plaintext_buff, sizeof(cbc_ecb_plaintext_aligned))) && (length == decrypt_expected_length))
            {
                LOG_I("CRYPT_TDES_ECB_DECRYPT_Padding_ISO7816_TEST_SUCCESS!------Length of encrypted data = %d",length);
            }
            else
            {
                LOG_I("CRYPT_TDES_ECB_DECRYPT_Padding_ISO7816_TEST_FAIL!");
            }
            lscrypt_des_type_flag = LSCRYPT_TDES_ECB_ENCRYPT_128;
        }
        break;
        default:
            break;
        }
        break; 
    case Padding_ISO10126:
        switch (lscrypt_des_type_flag)
        {
        case LSCRYPT_TDES_ECB_ENCRYPT_128:
        {
            if (length == encrypt_expected_length)
            {
                LOG_I("CRYPT_TDES_ECB_ENCRYPT_Padding_ISO10126_TEST!------Length of encrypted data = %d",length);
            }
            else
            {
                LOG_I("CRYPT_TDES_ECB_ENCRYPT_Padding_ISO10126_TEST_FAIL!");
            }
            lscrypt_des_type_flag = LSCRYPT_TDES_ECB_DECRYPT_128;
        }
        break;
        case LSCRYPT_TDES_ECB_DECRYPT_128:
        {
            if (!(memcmp(cbc_ecb_plaintext_aligned, plaintext_buff, sizeof(cbc_ecb_plaintext_aligned))) && (length == decrypt_expected_length))
            {
                LOG_I("CRYPT_TDES_ECB_DECRYPT_Padding_ISO10126_TEST_SUCCESS!------Length of encrypted data = %d",length);
                LOG_I("CRYPT_TDES_ECB_ENCRYPT_Padding_ISO10126_TEST SUCCESS!");
            }
            else
            {
                LOG_I("CRYPT_TDES_ECB_DECRYPT_Padding_ISO10126_TEST_FAIL!");
            }
            lscrypt_des_type_flag = LSCRYPT_TDES_ECB_ENCRYPT_128;
        }
        break;
        default:
            break;
        }
        break; 
    default:
        break;
    }
}