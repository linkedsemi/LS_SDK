#include <string.h>
#include <stdlib.h>
#include "lscrypt.h"
#include "platform.h"
#include "io_config.h"
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
enum lscrypt_type lscrypt_type_flag = LSCRYPT_ECB_ENCRYPT_128;

/**cbc-ecb-key-ciphertext-128**/
const uint32_t cbc_ecb_key_128[] = {
    0x09cf4f3c,
    0xabf71588,
    0x28aed2a6,
    0x2b7e1516};
const uint8_t ecb_ciphertext_128[] = {
    //Block #1
    0x97, 0xef, 0x66, 0x24, 0xf3, 0xca, 0x9e, 0xa8, 0x60, 0x36, 0x7a, 0x0d, 0xb4, 0x7b, 0xd7, 0x3a,
    //Block #2
    0xaf, 0xba, 0xfd, 0x96, 0x5a, 0x89, 0x85, 0xe7, 0x9d, 0x69, 0xb9, 0x03, 0x85, 0xd5, 0xd3, 0xf5,
    //Block #3
    0x88, 0x06, 0x03, 0xed, 0xe3, 0x00, 0x1b, 0x88, 0x23, 0xce, 0x8e, 0x59, 0x7f, 0xcd, 0xb1, 0x43,
    //Block #4
    0xd4, 0x5d, 0x72, 0x04, 0x71, 0x20, 0x23, 0x82, 0x3f, 0xad, 0xe8, 0x27, 0x5e, 0x78, 0x0c, 0x7b};
const uint8_t cbc_ciphertext_128[] = {
    //Block #1
    0x7d, 0x19, 0xe9, 0x12, 0x9b, 0x8e, 0xe9, 0xce, 0x46, 0xb2, 0x19, 0x81, 0xac, 0xab, 0x49, 0x76,
    //Block #2
    0xb2, 0x78, 0x76, 0x91, 0x3a, 0x11, 0xdb, 0x95, 0xee, 0x19, 0x72, 0x50, 0x9b, 0xcb, 0x86, 0x50,
    //Block #3
    0x16, 0x95, 0x22, 0x22, 0x9e, 0xe6, 0x16, 0x71, 0x3b, 0x74, 0xc1, 0xe3, 0xb8, 0xd6, 0xbe, 0x73,
    //Block #4
    0xa7, 0xe1, 0x86, 0x75, 0x30, 0xca, 0x0e, 0x12, 0x09, 0xac, 0x1f, 0x68, 0xa1, 0xca, 0xf1, 0x3f};

/**cbc-ecb-key-ciphertext-192**/
const uint32_t cbc_ecb_key_192[] = {
    0x522c6b7b,
    0x62f8ead2,
    0x809079e5,
    0xc810f32b,
    0xda0e6452,
    0x8e73b0f7};
const uint8_t ecb_ciphertext_192[] = {
    //Block #1
    0xcc, 0xa5, 0x1f, 0x57, 0x14, 0xa2, 0x12, 0xf7, 0x5f, 0xf2, 0x45, 0x6e, 0x1d, 0x4f, 0x33, 0xbd,
    //Block #2
    0xef, 0x4e, 0xee, 0xec, 0xb3, 0xec, 0x34, 0x77, 0xad, 0xd3, 0x0a, 0x6d, 0x84, 0x04, 0x41, 0x97,
    //Block #3
    0x4e, 0x44, 0xe6, 0xac, 0x2f, 0xba, 0xe0, 0xdc, 0x0a, 0xe6, 0xe2, 0x70, 0x22, 0xfd, 0x7a, 0xef,
    //Block #4
    0x0e, 0x8e, 0xc1, 0x03, 0x16, 0x69, 0x16, 0xfb, 0x72, 0x6c, 0x8d, 0x73, 0xba, 0x41, 0x4b, 0x9a};
const uint8_t cbc_ciphertext_192[] = {
    //Block #1
    0xe8, 0x71, 0xa0, 0x9f, 0x3a, 0x18, 0x78, 0x71, 0x3d, 0x63, 0xbc, 0x43, 0xb2, 0x1d, 0x02, 0x4f,
    //Block #2
    0x5a, 0x14, 0x69, 0x3f, 0x76, 0x38, 0xe7, 0xe5, 0xf4, 0xed, 0x7d, 0xad, 0xa9, 0xad, 0xd9, 0xb4,
    //Block #3
    0xe0, 0x02, 0xf1, 0x3d, 0xac, 0xba, 0xa9, 0x7f, 0xe0, 0x7a, 0xfb, 0x12, 0x20, 0x24, 0x1b, 0x57,
    //Block #4
    0xcd, 0x15, 0x56, 0x4f, 0xe6, 0xa9, 0x20, 0xd9, 0x81, 0x88, 0x59, 0x88, 0x79, 0xe2, 0xb0, 0x08};

/**cbc-ecb-key-ciphertext-256**/
const uint32_t cbc_ecb_key_256[] = {
    0x0914dff4,
    0x2d9810a3,
    0x3b6108d7,
    0x1f352c07,
    0x857d7781,
    0x2b73aef0,
    0x15ca71be,
    0x603deb10};
const uint8_t ecb_ciphertext_256[] = {
    //Block #1
    0xf8, 0x81, 0xb1, 0x3d, 0x7e, 0x5a, 0x4b, 0x06, 0x3c, 0xa0, 0xd2, 0xb5, 0xbd, 0xd1, 0xee, 0xf3,
    //Block #2
    0x70, 0x28, 0x36, 0x31, 0x4a, 0xa7, 0x5b, 0xdc, 0x26, 0xed, 0x10, 0xd4, 0x10, 0xcb, 0x1c, 0x59,
    //Block #3
    0x1d, 0xed, 0xaf, 0xbe, 0xb1, 0xe7, 0x53, 0xf1, 0xf9, 0xf4, 0xa6, 0x9c, 0xb9, 0x21, 0xed, 0xb6,
    //Block #4
    0xc7, 0xec, 0x24, 0x9e, 0x8f, 0x8d, 0x7d, 0x06, 0xff, 0xf3, 0xf9, 0x39, 0x7a, 0x4b, 0x30, 0x23};
const uint8_t cbc_ciphertext_256[] = {
    //Block #1
    0xd6, 0xfb, 0x7b, 0x5f, 0xfb, 0xab, 0x9e, 0x77, 0xba, 0xf1, 0xe5, 0xd6, 0x04, 0x4c, 0x8c, 0xf5,
    //Block #2
    0x7d, 0x2c, 0x70, 0xc6, 0x7b, 0x77, 0x9f, 0x67, 0x8d, 0x80, 0xdb, 0x7e, 0x96, 0x4e, 0xfc, 0x9c,
    //Block #3
    0x61, 0x14, 0x23, 0x04, 0x63, 0xe2, 0x30, 0xa5, 0xcf, 0xba, 0xd9, 0xa9, 0x69, 0x33, 0xf2, 0x39,
    //Block #4
    0x1b, 0x9d, 0x6a, 0x8c, 0x07, 0x19, 0x6c, 0xda, 0xfc, 0xe9, 0x9b, 0xc3, 0xe2, 0x05, 0xeb, 0xb2};

/**cbc-iv**/
const uint32_t cbc_iv[] = {
    0x0c0d0e0f,
    0x08090a0b,
    0x04050607,
    0x00010203,
};

/**cbc-ecb-plaintext**/
const uint8_t cbc_ecb_plaintext[] = {
    //Block #1
    0x2a, 0x17, 0x93, 0x73, 0x11, 0x7e, 0x3d, 0xe9, 0x96, 0x9f, 0x40, 0x2e, 0xe2, 0xbe, 0xc1, 0x6b,
    //Block #2
    0x51, 0x8e, 0xaf, 0x45, 0xac, 0x6f, 0xb7, 0x9e, 0x9c, 0xac, 0x03, 0x1e, 0x57, 0x8a, 0x2d, 0xae,
    //Block #3
    0xef, 0x52, 0x0a, 0x1a, 0x19, 0xc1, 0xfb, 0xe5, 0x11, 0xe4, 0x5c, 0xa3, 0x46, 0x1c, 0xc8, 0x30,
    //Block #4
    0x10, 0x37, 0x6c, 0xe6, 0x7b, 0x41, 0x2b, 0xad, 0x17, 0x9b, 0x4f, 0xdf, 0x45, 0x24, 0x9f, 0xf6};

/**buff**/
uint8_t ciphertext_buff[64];
uint8_t plaintext_buff[64];

void crypt_cbc_ecb_test(void)
{
    HAL_LSCRYPT_AES_Key_Config(cbc_ecb_key_128, AES_KEY_128);
    HAL_LSCRYPT_AES_ECB_Encrypt_IT(cbc_ecb_plaintext, sizeof(cbc_ecb_plaintext), ciphertext_buff);
    while (lscrypt_type_flag == LSCRYPT_ECB_ENCRYPT_128);

    HAL_LSCRYPT_AES_ECB_Decrypt_IT(ecb_ciphertext_128, sizeof(ecb_ciphertext_128), plaintext_buff);

    while (lscrypt_type_flag == LSCRYPT_ECB_DECRYPT_128);

    HAL_LSCRYPT_AES_CBC_Encrypt_IT(cbc_iv, cbc_ecb_plaintext, sizeof(cbc_ecb_plaintext), ciphertext_buff);
    while (lscrypt_type_flag == LSCRYPT_CBC_ENCRYPT_128);

    HAL_LSCRYPT_AES_CBC_Decrypt_IT(cbc_iv, cbc_ciphertext_128, sizeof(cbc_ciphertext_128), plaintext_buff);
    while (lscrypt_type_flag == LSCRYPT_CBC_DECRYPT_128);


    HAL_LSCRYPT_AES_Key_Config(cbc_ecb_key_192, AES_KEY_192);
    HAL_LSCRYPT_AES_ECB_Encrypt_IT(cbc_ecb_plaintext, sizeof(cbc_ecb_plaintext), ciphertext_buff);
    while (lscrypt_type_flag == LSCRYPT_ECB_ENCRYPT_192);

    HAL_LSCRYPT_AES_ECB_Decrypt_IT(ecb_ciphertext_192, sizeof(ecb_ciphertext_192), plaintext_buff);
    while (lscrypt_type_flag == LSCRYPT_ECB_DECRYPT_192);

    HAL_LSCRYPT_AES_CBC_Encrypt_IT(cbc_iv, cbc_ecb_plaintext, sizeof(cbc_ecb_plaintext), ciphertext_buff);
    while (lscrypt_type_flag == LSCRYPT_CBC_ENCRYPT_192);

    HAL_LSCRYPT_AES_CBC_Decrypt_IT(cbc_iv, cbc_ciphertext_192, sizeof(cbc_ciphertext_192), plaintext_buff);
    while (lscrypt_type_flag == LSCRYPT_CBC_DECRYPT_192);


    HAL_LSCRYPT_AES_Key_Config(cbc_ecb_key_256, AES_KEY_256);
    HAL_LSCRYPT_AES_ECB_Encrypt_IT(cbc_ecb_plaintext, sizeof(cbc_ecb_plaintext), ciphertext_buff);
    while (lscrypt_type_flag == LSCRYPT_ECB_ENCRYPT_256);

    HAL_LSCRYPT_AES_ECB_Decrypt_IT(ecb_ciphertext_256, sizeof(ecb_ciphertext_256), plaintext_buff);
    while (lscrypt_type_flag == LSCRYPT_ECB_DECRYPT_256);

    HAL_LSCRYPT_AES_CBC_Encrypt_IT(cbc_iv, cbc_ecb_plaintext, sizeof(cbc_ecb_plaintext), ciphertext_buff);
    while (lscrypt_type_flag == LSCRYPT_CBC_ENCRYPT_256);

    HAL_LSCRYPT_AES_CBC_Decrypt_IT(cbc_iv, cbc_ciphertext_256, sizeof(cbc_ciphertext_256), plaintext_buff);
    while (lscrypt_type_flag == LSCRYPT_CBC_DECRYPT_256);
}

int main()
{
    sys_init_none();
    HAL_LSCRYPT_Init();
    crypt_cbc_ecb_test();
}

void HAL_LSCRYPT_AES_Complete_Callback(bool Encrypt, bool CBC)
{
    switch (lscrypt_type_flag)
    {
        case LSCRYPT_ECB_ENCRYPT_128:
        {
            if (!(memcmp(ecb_ciphertext_128, ciphertext_buff, sizeof(ecb_ciphertext_128))))
            {
                LOG_I("CRYPT_AES_ECB_ENCRYPT_128_TEST_SUCCESS!");
            }
            else
            {
                LOG_I("CRYPT_AES_ECB_ENCRYPT_128_TEST_FAIL!");
            }
            lscrypt_type_flag = LSCRYPT_ECB_DECRYPT_128;
        }
        break;
        case LSCRYPT_ECB_DECRYPT_128:
        {
            if (!(memcmp(cbc_ecb_plaintext, plaintext_buff, sizeof(cbc_ecb_plaintext))))
            {
                LOG_I("CRYPT_AES_ECB_DECRYPT_128_TEST_SUCCESS!");
            }
            else
            {
                LOG_I("CRYPT_AES_ECB_DECRYPT_128_TEST_FAIL!");
            }
            lscrypt_type_flag = LSCRYPT_CBC_ENCRYPT_128;
        }
        break;
        case LSCRYPT_CBC_ENCRYPT_128:
        {
            if (!(memcmp(cbc_ciphertext_128, ciphertext_buff, sizeof(ecb_ciphertext_128))))
            {
                LOG_I("CRYPT_AES_CBC_ENCRYPT_128_TEST_SUCCESS!");
            }
            else
            {
                LOG_I("CRYPT_AES_CBC_ENCRYPT_128_TEST_FAIL!");
            }
            lscrypt_type_flag = LSCRYPT_CBC_DECRYPT_128;
        }
        break;
        case LSCRYPT_CBC_DECRYPT_128:
        {
            if (!(memcmp(cbc_ecb_plaintext, plaintext_buff, sizeof(cbc_ecb_plaintext))))
            {
                LOG_I("CRYPT_AES_CBC_DECRYPT_128_TEST_SUCCESS!");
            }
            else
            {
                LOG_I("CRYPT_AES_CBC_DECRYPT_128_TEST_FAIL!");
            }
            lscrypt_type_flag = LSCRYPT_ECB_ENCRYPT_192;
        }
        break;
        case LSCRYPT_ECB_ENCRYPT_192:
        {
            if (!(memcmp(ecb_ciphertext_192, ciphertext_buff, sizeof(ecb_ciphertext_192))))
            {
                LOG_I("CRYPT_AES_ECB_ENCRYPT_192_TEST_SUCCESS!");
            }
            else
            {
                LOG_I("CRYPT_AES_ECB_ENCRYPT_192_TEST_FAIL!");
            }
            lscrypt_type_flag = LSCRYPT_ECB_DECRYPT_192;
        }
        break;
        case LSCRYPT_ECB_DECRYPT_192:
        {
            if (!(memcmp(cbc_ecb_plaintext, plaintext_buff, sizeof(cbc_ecb_plaintext))))
            {
                LOG_I("CRYPT_AES_ECB_DECRYPT_192_TEST_SUCCESS!");
            }
            else
            {
                LOG_I("CRYPT_AES_ECB_DECRYPT_192_TEST_FAIL!");
            }
            lscrypt_type_flag = LSCRYPT_CBC_ENCRYPT_192;
        }
        break;
        case LSCRYPT_CBC_ENCRYPT_192:
        {
            if (!(memcmp(cbc_ciphertext_192, ciphertext_buff, sizeof(cbc_ciphertext_192))))
            {
                LOG_I("CRYPT_AES_CBC_ENCRYPT_192_TEST_SUCCESS!");
            }
            else
            {
                LOG_I("CRYPT_AES_CBC_ENCRYPT_192_TEST_FAIL!");
            }
            lscrypt_type_flag = LSCRYPT_CBC_DECRYPT_192;
        }
        break;

        case LSCRYPT_CBC_DECRYPT_192:
        {
            if (!(memcmp(cbc_ecb_plaintext, plaintext_buff, sizeof(cbc_ecb_plaintext))))
            {
                LOG_I("CRYPT_AES_CBC_DECRYPT_192_TEST_SUCCESS!");
            }
            else
            {
                LOG_I("CRYPT_AES_CBC_DECRYPT_192_TEST_FAIL!");
            }
            lscrypt_type_flag = LSCRYPT_ECB_ENCRYPT_256;
        }
        break;
        case LSCRYPT_ECB_ENCRYPT_256:
        {
            if (!(memcmp(ecb_ciphertext_256, ciphertext_buff, sizeof(ecb_ciphertext_256))))
            {
                LOG_I("CRYPT_AES_ECB_ENCRYPT_256_TEST_SUCCESS!");
            }
            else
            {
                LOG_I("CRYPT_AES_ECB_ENCRYPT_256_TEST_FAIL!");
            }
            lscrypt_type_flag = LSCRYPT_ECB_DECRYPT_256;
        }
        break;
        case LSCRYPT_ECB_DECRYPT_256:
        {
            if (!(memcmp(cbc_ecb_plaintext, plaintext_buff, sizeof(cbc_ecb_plaintext))))
            {
                LOG_I("CRYPT_AES_ECB_DECRYPT_256_TEST_SUCCESS!");
            }
            else
            {
                LOG_I("CRYPT_AES_ECB_DECRYPT_256_TEST_FAIL!");
            }
            lscrypt_type_flag = LSCRYPT_CBC_ENCRYPT_256;
        }
        break;
        case LSCRYPT_CBC_ENCRYPT_256:
        {

            if (!(memcmp(cbc_ciphertext_256, ciphertext_buff, sizeof(cbc_ciphertext_256))))
            {
                LOG_I("CRYPT_AES_CBC_ENCRYPT_256_TEST_SUCCESS!");
            }
            else
            {
                LOG_I("CRYPT_AES_CBC_ENCRYPT_256_TEST_FAIL!");
            }
            lscrypt_type_flag = LSCRYPT_CBC_DECRYPT_256;
        }
        break;
        case LSCRYPT_CBC_DECRYPT_256:
        {
            if (!(memcmp(cbc_ecb_plaintext, plaintext_buff, sizeof(cbc_ecb_plaintext))))
            {
                LOG_I("CRYPT_AES_CBC_DECRYPT_256_TEST_SUCCESS!");
            }
            else
            {
                LOG_I("CRYPT_AES_CBC_DECRYPT_256_TEST_FAIL!");
            }
            lscrypt_type_flag = LSCRYPT_ECB_ENCRYPT_128;
        }
        break;
        default:
            break;
    }
}


