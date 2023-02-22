#include <string.h>
#include <stdlib.h>
#include "ls_hal_crypt.h"
#include "platform.h"
#include "ls_soc_gpio.h"
#include "log.h"

enum lscrypt_mode
{
    LSCRYPT_ECB = 0,
    LSCRYPT_CBC,
};
enum lscrypt_encs
{
    LSCRYPT_DECRYPT = 0,
    LSCRYPT_ENCRYPT,
};
enum lscrypt_type
{
    LSCRYPT_ECB_ENCRYPT_128 = 0,
    LSCRYPT_ECB_DECRYPT_128,
    LSCRYPT_CBC_ENCRYPT_128,
    LSCRYPT_CBC_DECRYPT_128,

    LSCRYPT_ECB_ENCRYPT_192,
    LSCRYPT_ECB_DECRYPT_192,
    LSCRYPT_CBC_ENCRYPT_192,
    LSCRYPT_CBC_DECRYPT_192,

    LSCRYPT_ECB_ENCRYPT_256,
    LSCRYPT_ECB_DECRYPT_256,
    LSCRYPT_CBC_ENCRYPT_256,
    LSCRYPT_CBC_DECRYPT_256,
};
volatile enum lscrypt_type lscrypt_type_flag = LSCRYPT_ECB_ENCRYPT_128;

/**cbc-ecb-key-ciphertext-128**/
const uint32_t cbc_ecb_key_128[] = {
    0x09cf4f3c,
    0xabf71588,
    0x28aed2a6,
    0x2b7e1516};
/*ECB MODE ------- Plaintext is a multiple of 16*/
/****************************************************************************************************/
const uint8_t ecb_ciphertext_128_None_aligned[] = {
     //Block #1
    0x3A, 0xD7, 0x7B, 0xB4, 0x0D, 0x7A, 0x36, 0x60, 0xA8, 0x9E, 0xCA, 0xF3, 0x24, 0x66, 0xEF, 0x97,
    //Block #2
    0xF5, 0xD3, 0xD5, 0x85, 0x03, 0xB9, 0x69, 0x9D, 0xE7, 0x85, 0x89, 0x5A, 0x96, 0xFD, 0xBA, 0xAF,
    //Block #3
    0x7B, 0x0C, 0x78, 0x5E, 0x27, 0xE8, 0xAD, 0x3F, 0x82, 0x23, 0x20, 0x71, 0x04, 0x72, 0x5D, 0xD4,};
const uint8_t ecb_ciphertext_128_PKCS7_aligned[] = {
    //Block #1
    0x3A, 0xD7, 0x7B, 0xB4, 0x0D, 0x7A, 0x36, 0x60, 0xA8, 0x9E, 0xCA, 0xF3, 0x24, 0x66, 0xEF, 0x97,
    //Block #2
    0xF5, 0xD3, 0xD5, 0x85, 0x03, 0xB9, 0x69, 0x9D, 0xE7, 0x85, 0x89, 0x5A, 0x96, 0xFD, 0xBA, 0xAF,
    //Block #3
    0x7B, 0x0C, 0x78, 0x5E, 0x27, 0xE8, 0xAD, 0x3F, 0x82, 0x23, 0x20, 0x71, 0x04, 0x72, 0x5D, 0xD4,
    //Block #4
    0xA2, 0x54, 0xBE, 0x88, 0xE0, 0x37, 0xDD, 0xD9, 0xD7, 0x9F, 0xB6, 0x41, 0x1C, 0x3F, 0x9D, 0xF8};
const uint8_t ecb_ciphertext_128_ANSIX923_aligned[] = {
    0x3A, 0xD7, 0x7B, 0xB4, 0x0D, 0x7A, 0x36, 0x60, 0xA8, 0x9E, 0xCA, 0xF3, 0x24, 0x66, 0xEF, 0x97,

    0xF5, 0xD3, 0xD5, 0x85, 0x03, 0xB9, 0x69, 0x9D, 0xE7, 0x85, 0x89, 0x5A, 0x96, 0xFD, 0xBA, 0xAF,
    
    0x7B, 0x0C, 0x78, 0x5E, 0x27, 0xE8, 0xAD, 0x3F, 0x82, 0x23, 0x20, 0x71, 0x04, 0x72, 0x5D, 0xD4,

    0x7E, 0x79, 0x4A, 0x13, 0xC7, 0x49, 0x73, 0xB4, 0xBF, 0x55, 0xB1, 0x0F, 0x5A, 0x99, 0x04, 0xE8};
const uint8_t ecb_ciphertext_128_ISO7816_aligned[] = {
    0x3A, 0xD7, 0x7B, 0xB4, 0x0D, 0x7A, 0x36, 0x60, 0xA8, 0x9E, 0xCA, 0xF3, 0x24, 0x66, 0xEF, 0x97,

    0xF5, 0xD3, 0xD5, 0x85, 0x03, 0xB9, 0x69, 0x9D, 0xE7, 0x85, 0x89, 0x5A, 0x96, 0xFD, 0xBA, 0xAF,

    0x7B, 0x0C, 0x78, 0x5E, 0x27, 0xE8, 0xAD, 0x3F, 0x82, 0x23, 0x20, 0x71, 0x04, 0x72, 0x5D, 0xD4,

    0xF6, 0xC7, 0x1E, 0xED, 0xC3, 0xD9, 0x9B, 0xB1, 0x83, 0xCB, 0x5B, 0x8D, 0x15, 0x68, 0xE6, 0x06};
const uint8_t ecb_ciphertext_128_ISO10126_aligned[] = {
    0x3A, 0xD7, 0x7B, 0xB4, 0x0D, 0x7A, 0x36, 0x60, 0xA8, 0x9E, 0xCA, 0xF3, 0x24, 0x66, 0xEF, 0x97,

    0xF5, 0xD3, 0xD5, 0x85, 0x03, 0xB9, 0x69, 0x9D, 0xE7, 0x85, 0x89, 0x5A, 0x96, 0xFD, 0xBA, 0xAF,

    0x7B, 0x0C, 0x78, 0x5E, 0x27, 0xE8, 0xAD, 0x3F, 0x82, 0x23, 0x20, 0x71, 0x04, 0x72, 0x5D, 0xD4,

    0xCE, 0x6F, 0x2C, 0x18, 0x38, 0x06, 0x59, 0x28, 0xFC, 0x70, 0x23, 0xD0, 0xE1, 0x38, 0x3F, 0x91};
/****************************************************************************************************/

/*ECB MODE -------Plaintext is not a multiple of 16*/
/****************************************************************************************************/
const uint8_t ecb_ciphertext_128_PKCS7_unaligned[] = {
    0x3A, 0xD7, 0x7B, 0xB4, 0x0D, 0x7A, 0x36, 0x60, 0xA8, 0x9E, 0xCA, 0xF3, 0x24, 0x66, 0xEF, 0x97,

    0xF5, 0xD3, 0xD5, 0x85, 0x03, 0xB9, 0x69, 0x9D, 0xE7, 0x85, 0x89, 0x5A, 0x96, 0xFD, 0xBA, 0xAF,

    0x43, 0xB1, 0xCD, 0x7F, 0x59, 0x8E, 0xCE, 0x23, 0x88, 0x1B, 0x00, 0xE3, 0xED, 0x03, 0x06, 0x88,

    0x39, 0x1E, 0xC0, 0x32, 0xC0, 0x25, 0x5E, 0xE1, 0x6B, 0x02, 0x0A, 0x80, 0x10, 0xCD, 0x75, 0xAE};
const uint8_t ecb_ciphertext_128_ANSIX923_unaligned[] = {
    0x3A, 0xD7, 0x7B, 0xB4, 0x0D, 0x7A, 0x36, 0x60, 0xA8, 0x9E, 0xCA, 0xF3, 0x24, 0x66, 0xEF, 0x97,

    0xF5, 0xD3, 0xD5, 0x85, 0x03, 0xB9, 0x69, 0x9D, 0xE7, 0x85, 0x89, 0x5A, 0x96, 0xFD, 0xBA, 0xAF,

    0x43, 0xB1, 0xCD, 0x7F, 0x59, 0x8E, 0xCE, 0x23, 0x88, 0x1B, 0x00, 0xE3, 0xED, 0x03, 0x06, 0x88,

    0x8D, 0x84, 0xFF, 0x31, 0x5B, 0x5B, 0x11, 0x9C, 0xAA, 0x2B, 0xB3, 0x08, 0x65, 0x17, 0xF3, 0x9E};
const uint8_t ecb_ciphertext_128_ISO7816_unaligned[] = {
    0x3A, 0xD7, 0x7B, 0xB4, 0x0D, 0x7A, 0x36, 0x60, 0xA8, 0x9E, 0xCA, 0xF3, 0x24, 0x66, 0xEF, 0x97,

    0xF5, 0xD3, 0xD5, 0x85, 0x03, 0xB9, 0x69, 0x9D, 0xE7, 0x85, 0x89, 0x5A, 0x96, 0xFD, 0xBA, 0xAF,

    0x43, 0xB1, 0xCD, 0x7F, 0x59, 0x8E, 0xCE, 0x23, 0x88, 0x1B, 0x00, 0xE3, 0xED, 0x03, 0x06, 0x88,

    0x8C, 0xC9, 0x5A, 0xB7, 0x2A, 0x18, 0xE2, 0x71, 0x9A, 0x52, 0x3B, 0x49, 0x31, 0x38, 0x53, 0x64};
const uint8_t ecb_ciphertext_128_ISO10126_unaligned[] = {
    0x3A, 0xD7, 0x7B, 0xB4, 0x0D, 0x7A, 0x36, 0x60, 0xA8, 0x9E, 0xCA, 0xF3, 0x24, 0x66, 0xEF, 0x97,

    0xF5, 0xD3, 0xD5, 0x85, 0x03, 0xB9, 0x69, 0x9D, 0xE7, 0x85, 0x89, 0x5A, 0x96, 0xFD, 0xBA, 0xAF,

    0x43, 0xB1, 0xCD, 0x7F, 0x59, 0x8E, 0xCE, 0x23, 0x88, 0x1B, 0x00, 0xE3, 0xED, 0x03, 0x06, 0x88,

    0xC7, 0xC7, 0xC9, 0x24, 0x1D, 0xB0, 0x4A, 0x68, 0xFC, 0x31, 0x80, 0x9E, 0x0A, 0x4D, 0x1B, 0x12};
/****************************************************************************************************/

/**cbc-iv**/
const uint32_t cbc_iv[] = {
    0x0c0d0e0f,
    0x08090a0b,
    0x04050607,
    0x00010203,
};

/**ecb-plaintext**/
const uint8_t cbc_ecb_plaintext_aligned[] = {
    //Block #1   
    0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a,
    //Block #2
    0xae, 0x2d, 0x8a, 0x57, 0x1e, 0x03, 0xac, 0x9c, 0x9e, 0xb7, 0x6f, 0xac, 0x45, 0xaf, 0x8e, 0x51,
    //Block #3
    0xf6, 0x9f, 0x24, 0x45, 0xdf, 0x4f, 0x9b, 0x17, 0xad, 0x2b, 0x41, 0x7b, 0xe6, 0x6c, 0x37, 0x10};
const uint8_t cbc_ecb_plaintext_unaligned[] = {
    //Block #1
    0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a,
    //Block #2
    0xae, 0x2d, 0x8a, 0x57, 0x1e, 0x03, 0xac, 0x9c, 0x9e, 0xb7, 0x6f, 0xac, 0x45, 0xaf, 0x8e, 0x51,
    //Block #3
    0x30, 0xc8, 0x1c, 0x46, 0xa3, 0x5c, 0xe4, 0x11, 0xe5, 0xfb, 0xc1, 0x19, 0x1a, 0x0a, 0x52, 0xef,
    //Block #4
    0xf6, 0x9f, 0x24, 0x45, 0xdf, 0x4f, 0x9b, 0x17};

/**buff**/
uint8_t ciphertext_buff[64];
uint8_t plaintext_buff[64];
uint32_t encrypt_expected_length;
uint32_t decrypt_expected_length = sizeof(cbc_ecb_plaintext_aligned);
enum padding_mode mode;

void crypt_cbc_ecb_test_128_None(void)
{
    HAL_LSCRYPT_Block_Padding_Mode_Set(mode);
    HAL_LSCRYPT_AES_Key_Config(cbc_ecb_key_128, AES_KEY_128);

    HAL_LSCRYPT_AES_ECB_Encrypt_IT(cbc_ecb_plaintext_aligned, sizeof(cbc_ecb_plaintext_aligned), ciphertext_buff, sizeof(ciphertext_buff));
    while (lscrypt_type_flag == LSCRYPT_ECB_ENCRYPT_128);

    HAL_LSCRYPT_AES_ECB_Decrypt_IT(ecb_ciphertext_128_None_aligned, sizeof(ecb_ciphertext_128_None_aligned), plaintext_buff,sizeof(plaintext_buff));
    while (lscrypt_type_flag == LSCRYPT_ECB_DECRYPT_128);
}

void crypt_cbc_ecb_test_128_PKCS7(void)
{
    HAL_LSCRYPT_Block_Padding_Mode_Set(mode);
    HAL_LSCRYPT_AES_Key_Config(cbc_ecb_key_128, AES_KEY_128);
 
    HAL_LSCRYPT_AES_ECB_Encrypt_IT(cbc_ecb_plaintext_aligned, sizeof(cbc_ecb_plaintext_aligned), ciphertext_buff,sizeof(ciphertext_buff));
    while (lscrypt_type_flag == LSCRYPT_ECB_ENCRYPT_128);

    HAL_LSCRYPT_AES_ECB_Decrypt_IT(ecb_ciphertext_128_PKCS7_aligned, sizeof(ecb_ciphertext_128_PKCS7_aligned), plaintext_buff,sizeof(plaintext_buff));
    while (lscrypt_type_flag == LSCRYPT_ECB_DECRYPT_128);
}

void crypt_cbc_ecb_test_128_ANSIX923(void)
{
    HAL_LSCRYPT_Block_Padding_Mode_Set(mode);
    HAL_LSCRYPT_AES_Key_Config(cbc_ecb_key_128, AES_KEY_128);
 
    HAL_LSCRYPT_AES_ECB_Encrypt_IT(cbc_ecb_plaintext_aligned, sizeof(cbc_ecb_plaintext_aligned), ciphertext_buff,sizeof(ciphertext_buff));
    while (lscrypt_type_flag == LSCRYPT_ECB_ENCRYPT_128);

    HAL_LSCRYPT_AES_ECB_Decrypt_IT(ecb_ciphertext_128_ANSIX923_aligned, sizeof(ecb_ciphertext_128_ANSIX923_aligned), plaintext_buff,sizeof(plaintext_buff));
    while (lscrypt_type_flag == LSCRYPT_ECB_DECRYPT_128);
}

void crypt_cbc_ecb_test_128_ISO7816(void)
{
    HAL_LSCRYPT_Block_Padding_Mode_Set(mode);
    HAL_LSCRYPT_AES_Key_Config(cbc_ecb_key_128, AES_KEY_128);
 
    HAL_LSCRYPT_AES_ECB_Encrypt_IT(cbc_ecb_plaintext_aligned, sizeof(cbc_ecb_plaintext_aligned), ciphertext_buff,sizeof(ciphertext_buff));
    while (lscrypt_type_flag == LSCRYPT_ECB_ENCRYPT_128);

    HAL_LSCRYPT_AES_ECB_Decrypt_IT(ecb_ciphertext_128_ISO7816_aligned, sizeof(ecb_ciphertext_128_ISO7816_aligned), plaintext_buff,sizeof(plaintext_buff));
    while (lscrypt_type_flag == LSCRYPT_ECB_DECRYPT_128);
}

void crypt_cbc_ecb_test_128_ISO10126(void)
{
    HAL_LSCRYPT_Block_Padding_Mode_Set(mode);
    HAL_LSCRYPT_AES_Key_Config(cbc_ecb_key_128, AES_KEY_128);
 
    HAL_LSCRYPT_AES_ECB_Encrypt_IT(cbc_ecb_plaintext_aligned, sizeof(cbc_ecb_plaintext_aligned), ciphertext_buff,sizeof(ciphertext_buff));
    while (lscrypt_type_flag == LSCRYPT_ECB_ENCRYPT_128);

    HAL_LSCRYPT_AES_ECB_Decrypt_IT(ciphertext_buff, sizeof(ciphertext_buff), plaintext_buff,sizeof(plaintext_buff));
    while (lscrypt_type_flag == LSCRYPT_ECB_DECRYPT_128);
}

int main()
{
    sys_init_none();
    HAL_LSCRYPT_Init();
    mode = Padding_None;
    encrypt_expected_length = sizeof(cbc_ecb_plaintext_aligned);
    crypt_cbc_ecb_test_128_None();
    mode = Padding_PKCS7;
    encrypt_expected_length = sizeof(cbc_ecb_plaintext_aligned) + 16 - sizeof(cbc_ecb_plaintext_aligned) % 16;
    crypt_cbc_ecb_test_128_PKCS7();
    mode = Padding_ANSIX923;
    crypt_cbc_ecb_test_128_ANSIX923();
    mode = Padding_ISO7816;
    crypt_cbc_ecb_test_128_ISO7816();
    mode = Padding_ISO10126;
    crypt_cbc_ecb_test_128_ISO10126();
    while(1);
}

void HAL_LSCRYPT_AES_Complete_Callback(bool Encrypt, bool CBC , uint32_t length)
{
    switch (mode)
    {
    case Padding_None:
        switch (lscrypt_type_flag)
        {
        case LSCRYPT_ECB_ENCRYPT_128:
        {
            if (!(memcmp(ecb_ciphertext_128_None_aligned, ciphertext_buff, sizeof(ecb_ciphertext_128_None_aligned))) && (length == encrypt_expected_length))
            {
                LOG_I("CRYPT_AES_ECB_ENCRYPT_Padding_None_TEST_SUCCESS!------Length of encrypted data = %d",length);
            }
            else
            {
                LOG_I("CRYPT_AES_ECB_ENCRYPT_Padding_None_TEST_FAIL!");
            }
            lscrypt_type_flag = LSCRYPT_ECB_DECRYPT_128;
        }
        break;
        case LSCRYPT_ECB_DECRYPT_128:
        {
            if (!(memcmp(cbc_ecb_plaintext_aligned, plaintext_buff, sizeof(cbc_ecb_plaintext_aligned))) && (length == decrypt_expected_length))
            {
                LOG_I("CRYPT_AES_ECB_DECRYPT_Padding_None_TEST_SUCCESS!------Length of decrypted data = %d",length);
            }
            else
            {
                LOG_I("CRYPT_AES_ECB_DECRYPT_Padding_None_TEST_FAIL!");
            }
            lscrypt_type_flag = LSCRYPT_ECB_ENCRYPT_128;
        }
        break;
        default:
            break;
        }
        break;
    case Padding_PKCS7:
        switch (lscrypt_type_flag)
        {
        case LSCRYPT_ECB_ENCRYPT_128:
        {
            if (!(memcmp(ecb_ciphertext_128_PKCS7_aligned, ciphertext_buff, sizeof(ecb_ciphertext_128_PKCS7_aligned))) && (length == encrypt_expected_length))
            {
                LOG_I("CRYPT_AES_ECB_ENCRYPT_Padding_PKCS7_TEST_SUCCESS!------Length of encrypted data = %d",length);
            }
            else
            {
                LOG_I("CRYPT_AES_ECB_ENCRYPT_Padding_PKCS7_TEST_FAIL!");
            }
            lscrypt_type_flag = LSCRYPT_ECB_DECRYPT_128;
        }
        break;
        case LSCRYPT_ECB_DECRYPT_128:
        {
            if (!(memcmp(cbc_ecb_plaintext_aligned, plaintext_buff, sizeof(cbc_ecb_plaintext_aligned))) && (length == decrypt_expected_length))
            {
                LOG_I("CRYPT_AES_ECB_DECRYPT_Padding_PKCS7_TEST_SUCCESS!------Length of decrypted data = %d",length);
            }
            else
            {
                LOG_I("CRYPT_AES_ECB_DECRYPT_Padding_PKCS7_TEST_FAIL!");
            }
            lscrypt_type_flag = LSCRYPT_ECB_ENCRYPT_128;
        }
        break;
        default:
            break;
        }
        break;
    case Padding_ANSIX923:
        switch (lscrypt_type_flag)
        {
        case LSCRYPT_ECB_ENCRYPT_128:
        {
            if (!(memcmp(ecb_ciphertext_128_ANSIX923_aligned, ciphertext_buff, sizeof(ecb_ciphertext_128_ANSIX923_aligned))) && (length == encrypt_expected_length))
            {
                LOG_I("CRYPT_AES_ECB_ENCRYPT_Padding_ANSIX923_TEST_SUCCESS!------Length of encrypted data = %d",length);
            }
            else
            {
                LOG_I("CRYPT_AES_ECB_ENCRYPT_Padding_ANSIX923_TEST_FAIL!");
            }
            lscrypt_type_flag = LSCRYPT_ECB_DECRYPT_128;
        }
        break;
        case LSCRYPT_ECB_DECRYPT_128:
        {
            if (!(memcmp(cbc_ecb_plaintext_aligned, plaintext_buff, sizeof(cbc_ecb_plaintext_aligned))) && (length == decrypt_expected_length))
            {
                LOG_I("CRYPT_AES_ECB_DECRYPT_Padding_ANSIX923_TEST_SUCCESS!------Length of decrypted data = %d",length);
            }
            else
            {
                LOG_I("CRYPT_AES_ECB_DECRYPT_Padding_ANSIX923_TEST_FAIL!");
            }
            lscrypt_type_flag = LSCRYPT_ECB_ENCRYPT_128;
        }
        break;
        default:
            break;
        }
        break;
    case Padding_ISO7816:
        switch (lscrypt_type_flag)
        {
        case LSCRYPT_ECB_ENCRYPT_128:
        {
            if (!(memcmp(ecb_ciphertext_128_ISO7816_aligned, ciphertext_buff, sizeof(ecb_ciphertext_128_ISO7816_aligned))) && (length == encrypt_expected_length))
            {
                LOG_I("CRYPT_AES_ECB_ENCRYPT_Padding_ISO7816_TEST_SUCCESS!------Length of encrypted data = %d",length);
            }
            else
            {
                LOG_I("CRYPT_AES_ECB_ENCRYPT_Padding_ISO7816_TEST_FAIL!");
            }
            lscrypt_type_flag = LSCRYPT_ECB_DECRYPT_128;
        }
        break;
        case LSCRYPT_ECB_DECRYPT_128:
        {
            if (!(memcmp(cbc_ecb_plaintext_aligned, plaintext_buff, sizeof(cbc_ecb_plaintext_aligned))) && (length == decrypt_expected_length))
            {
                LOG_I("CRYPT_AES_ECB_DECRYPT_Padding_ISO7816_TEST_SUCCESS!------Length of decrypted data = %d",length);
            }
            else
            {
                LOG_I("CRYPT_AES_ECB_DECRYPT_Padding_ISO7816_TEST_FAIL!");
            }
            lscrypt_type_flag = LSCRYPT_ECB_ENCRYPT_128;
        }
        break;
        default:
            break;
        }
        break;
    case Padding_ISO10126:
        switch (lscrypt_type_flag)
        {
        case LSCRYPT_ECB_ENCRYPT_128:
        {
            if ((length == encrypt_expected_length))
            {
                LOG_I("CRYPT_AES_ECB_ENCRYPT_Padding_ISO10126_TEST!------Length of encrypted data = %d",length);
            }
            else
            {
                LOG_I("CRYPT_AES_ECB_ENCRYPT_Padding_ISO10126_TEST_FAIL!");
            }
            lscrypt_type_flag = LSCRYPT_ECB_DECRYPT_128;
        }
        break;
        case LSCRYPT_ECB_DECRYPT_128:
        {
            if (!(memcmp(cbc_ecb_plaintext_aligned, plaintext_buff, sizeof(cbc_ecb_plaintext_aligned))) && (length == decrypt_expected_length))
            {
                LOG_I("CRYPT_AES_ECB_DECRYPT_Padding_ISO10126_TEST_SUCCESS!------Length of decrypted data = %d",length);
                LOG_I("CRYPT_AES_ECB_ENCRYPT_Padding_ISO10126_TEST_SUCCESS!");
            }
            else
            {
                LOG_I("CRYPT_AES_ECB_DECRYPT_Padding_ISO10126_TEST_FAIL!");
            }
            lscrypt_type_flag = LSCRYPT_ECB_ENCRYPT_128;
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