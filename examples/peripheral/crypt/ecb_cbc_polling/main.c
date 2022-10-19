#include <string.h>
#include <stdlib.h>
#include "ls_hal_crypt.h"
#include "platform.h"
#include "ls_soc_gpio.h"
#include "log.h"
/**cbc-ecb-key-ciphertext-128**/
uint32_t cbc_ecb_key_128[] = {
    0x09cf4f3c,
    0xabf71588,
    0x28aed2a6,
    0x2b7e1516};
uint8_t ecb_ciphertext_128[] = {
    //Block #1
    0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60, 0xa8, 0x9e, 0xca, 0xf3, 0x24, 0x66, 0xef, 0x97,
    //Block #2
    0xf5, 0xd3, 0xd5, 0x85, 0x03, 0xb9, 0x69, 0x9d, 0xe7, 0x85, 0x89, 0x5a, 0x96, 0xfd, 0xba, 0xaf,
    //Block #3
    0x43, 0xb1, 0xcd, 0x7f, 0x59, 0x8e, 0xce, 0x23, 0x88, 0x1b, 0x00, 0xe3, 0xed, 0x03, 0x06, 0x88,
    //Block #4
    0x7b, 0x0c, 0x78, 0x5e, 0x27, 0xe8, 0xad, 0x3f, 0x82, 0x23, 0x20, 0x71, 0x04, 0x72, 0x5d, 0xd4};
uint8_t cbc_ciphertext_128[] = {
    //Block #1
    0x76, 0x49, 0xab, 0xac, 0x81, 0x19, 0xb2, 0x46, 0xce, 0xe9, 0x8e, 0x9b, 0x12, 0xe9, 0x19, 0x7d,
    //Block #2
    0x50, 0x86, 0xcb, 0x9b, 0x50, 0x72, 0x19, 0xee, 0x95, 0xdb, 0x11, 0x3a, 0x91, 0x76, 0x78, 0xb2,
    //Block #3
    0x73, 0xbe, 0xd6, 0xb8, 0xe3, 0xc1, 0x74, 0x3b, 0x71, 0x16, 0xe6, 0x9e, 0x22, 0x22, 0x95, 0x16,
    //Block #4
    0x3f, 0xf1, 0xca, 0xa1, 0x68, 0x1f, 0xac, 0x09, 0x12, 0x0e, 0xca, 0x30, 0x75, 0x86, 0xe1, 0xa7};

/**cbc-ecb-key-ciphertext-192**/
uint32_t cbc_ecb_key_192[] = {
    0x522c6b7b,
    0x62f8ead2,
    0x809079e5,
    0xc810f32b,
    0xda0e6452,
    0x8e73b0f7};
uint8_t ecb_ciphertext_192[] = {
    //Block #1
    0xbd, 0x33, 0x4f, 0x1d, 0x6e, 0x45, 0xf2, 0x5f, 0xf7, 0x12, 0xa2, 0x14, 0x57, 0x1f, 0xa5, 0xcc,
    //Block #2
    0x97, 0x41, 0x04, 0x84, 0x6d, 0x0a, 0xd3, 0xad, 0x77, 0x34, 0xec, 0xb3, 0xec, 0xee, 0x4e, 0xef,
    //Block #3
    0xef, 0x7a, 0xfd, 0x22, 0x70, 0xe2, 0xe6, 0x0a, 0xdc, 0xe0, 0xba, 0x2f, 0xac, 0xe6, 0x44, 0x4e,
    //Block #4
    0x9a, 0x4b, 0x41, 0xba, 0x73, 0x8d, 0x6c, 0x72, 0xfb, 0x16, 0x69, 0x16, 0x03, 0xc1, 0x8e, 0x0e};
uint8_t cbc_ciphertext_192[] = {
    //Block #1
    0x4f, 0x02, 0x1d, 0xb2, 0x43, 0xbc, 0x63, 0x3d, 0x71, 0x78, 0x18, 0x3a, 0x9f, 0xa0, 0x71, 0xe8,
    //Block #2
    0xb4, 0xd9, 0xad, 0xa9, 0xad, 0x7d, 0xed, 0xf4, 0xe5, 0xe7, 0x38, 0x76, 0x3f, 0x69, 0x14, 0x5a,
    //Block #3
    0x57, 0x1b, 0x24, 0x20, 0x12, 0xfb, 0x7a, 0xe0, 0x7f, 0xa9, 0xba, 0xac, 0x3d, 0xf1, 0x02, 0xe0,
    //Block #4
    0x08, 0xb0, 0xe2, 0x79, 0x88, 0x59, 0x88, 0x81, 0xd9, 0x20, 0xa9, 0xe6, 0x4f, 0x56, 0x15, 0xcd};

/**cbc-ecb-key-ciphertext-256**/
uint32_t cbc_ecb_key_256[] = {
    0x0914dff4,
    0x2d9810a3,
    0x3b6108d7,
    0x1f352c07,
    0x857d7781,
    0x2b73aef0,
    0x15ca71be,
    0x603deb10};
uint8_t ecb_ciphertext_256[] = {
    //Block #1
    0xf3, 0xee, 0xd1, 0xbd, 0xb5, 0xd2, 0xa0, 0x3c, 0x06, 0x4b, 0x5a, 0x7e, 0x3d, 0xb1, 0x81, 0xf8,
    //Block #2
    0x59, 0x1c, 0xcb, 0x10, 0xd4, 0x10, 0xed, 0x26, 0xdc, 0x5b, 0xa7, 0x4a, 0x31, 0x36, 0x28, 0x70,
    //Block #3
    0xb6, 0xed, 0x21, 0xb9, 0x9c, 0xa6, 0xf4, 0xf9, 0xf1, 0x53, 0xe7, 0xb1, 0xbe, 0xaf, 0xed, 0x1d,
    //Block #4
    0x23, 0x30, 0x4b, 0x7a, 0x39, 0xf9, 0xf3, 0xff, 0x06, 0x7d, 0x8d, 0x8f, 0x9e, 0x24, 0xec, 0xc7};
uint8_t cbc_ciphertext_256[] = {
    //Block #1
    0xf5, 0x8c, 0x4c, 0x04, 0xd6, 0xe5, 0xf1, 0xba, 0x77, 0x9e, 0xab, 0xfb, 0x5f, 0x7b, 0xfb, 0xd6,
    //Block #2
    0x9c, 0xfc, 0x4e, 0x96, 0x7e, 0xdb, 0x80, 0x8d, 0x67, 0x9f, 0x77, 0x7b, 0xc6, 0x70, 0x2c, 0x7d,
    //Block #3
    0x39, 0xf2, 0x33, 0x69, 0xa9, 0xd9, 0xba, 0xcf, 0xa5, 0x30, 0xe2, 0x63, 0x04, 0x23, 0x14, 0x61,
    //Block #4
    0xb2, 0xeb, 0x05, 0xe2, 0xc3, 0x9b, 0xe9, 0xfc, 0xda, 0x6c, 0x19, 0x07, 0x8c, 0x6a, 0x9d, 0x1b};

/**cbc-iv**/
uint32_t cbc_iv[] = {
    0x0c0d0e0f,
    0x08090a0b,
    0x04050607,
    0x00010203,
};

/**cbc-ecb-plaintext**/
uint8_t cbc_ecb_plaintext[] = {
    //Block #1
    0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a,
    //Block #2
    0xae, 0x2d, 0x8a, 0x57, 0x1e, 0x03, 0xac, 0x9c, 0x9e, 0xb7, 0x6f, 0xac, 0x45, 0xaf, 0x8e, 0x51,
    //Block #3
    0x30, 0xc8, 0x1c, 0x46, 0xa3, 0x5c, 0xe4, 0x11, 0xe5, 0xfb, 0xc1, 0x19, 0x1a, 0x0a, 0x52, 0xef,
    //Block #4
    0xf6, 0x9f, 0x24, 0x45, 0xdf, 0x4f, 0x9b, 0x17, 0xad, 0x2b, 0x41, 0x7b, 0xe6, 0x6c, 0x37, 0x10};

/**buff**/
uint8_t ciphertext_buff[64];
uint8_t plaintext_buff[64];
uint32_t expected_length = sizeof(cbc_ecb_plaintext);
uint32_t length;

void crypt_init(void)
{
    HAL_LSCRYPT_Init();
}

void crypt_cbc_ecb_test_128(void)
{
    HAL_LSCRYPT_AES_Key_Config(cbc_ecb_key_128, AES_KEY_128);
    /*CRYPT_AES_ECB_TEST*/
    length = sizeof(ciphertext_buff);
    HAL_LSCRYPT_AES_ECB_Encrypt(cbc_ecb_plaintext, sizeof(cbc_ecb_plaintext), ciphertext_buff, &length);
    if (!(memcmp(ecb_ciphertext_128, ciphertext_buff, sizeof(ecb_ciphertext_128))) && (length == expected_length))
    {
        LOG_I("CRYPT_AES_ECB_ENCRYPT_128_TEST_SUCCESS!------Length of encrypted data = %d",length);
    }
    else
    {
        LOG_I("CRYPT_AES_ECB_ENCRYPT_128_TEST_FAIL!");
    }
    length = sizeof(plaintext_buff);
    HAL_LSCRYPT_AES_ECB_Decrypt(ecb_ciphertext_128, sizeof(ecb_ciphertext_128), plaintext_buff, &length);
    if (!(memcmp(cbc_ecb_plaintext, plaintext_buff, sizeof(cbc_ecb_plaintext))) && (length == expected_length))
    {
        LOG_I("CRYPT_AES_ECB_DECRYPT_128_TEST_SUCCESS!------Length of decrypted data = %d",length);
    }
    else
    {
        LOG_I("CRYPT_AES_ECB_DECRYPT_128_TEST_FAIL!");
    }
    /*CRYPT_AES_CBC_TEST*/
    length = sizeof(ciphertext_buff);
    HAL_LSCRYPT_AES_CBC_Encrypt(cbc_iv, cbc_ecb_plaintext, sizeof(cbc_ecb_plaintext), ciphertext_buff, &length);
    if (!(memcmp(cbc_ciphertext_128, ciphertext_buff, sizeof(ecb_ciphertext_128))) && (length == expected_length))
    {
        LOG_I("CRYPT_AES_CBC_ENCRYPT_128_TEST_SUCCESS!------Length of encrypted data = %d",length);
    }
    else
    {
        LOG_I("CRYPT_AES_CBC_ENCRYPT_128_TEST_FAIL!");
    }
    length = sizeof(plaintext_buff);
    HAL_LSCRYPT_AES_CBC_Decrypt(cbc_iv, cbc_ciphertext_128, sizeof(cbc_ciphertext_128), plaintext_buff, &length);
    if (!(memcmp(cbc_ecb_plaintext, plaintext_buff, sizeof(cbc_ecb_plaintext))) && (length == expected_length))
    {
        LOG_I("CRYPT_AES_CBC_DECRYPT_128_TEST_SUCCESS!------Length of decrypted data = %d",length);
    }
    else
    {
        LOG_I("CRYPT_AES_CBC_DECRYPT_128_TEST_FAIL!");
    }
}

void crypt_cbc_ecb_test_192(void)
{
    HAL_LSCRYPT_AES_Key_Config(cbc_ecb_key_192, AES_KEY_192);
    /*CRYPT_AES_ECB_TEST*/
    length = sizeof(ciphertext_buff);
    HAL_LSCRYPT_AES_ECB_Encrypt(cbc_ecb_plaintext, sizeof(cbc_ecb_plaintext), ciphertext_buff, &length);
    if (!(memcmp(ecb_ciphertext_192, ciphertext_buff, sizeof(ecb_ciphertext_192))) && (length == expected_length))
    {
        LOG_I("CRYPT_AES_ECB_ENCRYPT_192_TEST_SUCCESS!------Length of encrypted data = %d",length);
    }
    else
    {
        LOG_I("CRYPT_AES_ECB_ENCRYPT_192_TEST_FAIL!");
    }
    length = sizeof(plaintext_buff);
    HAL_LSCRYPT_AES_ECB_Decrypt(ecb_ciphertext_192, sizeof(ecb_ciphertext_192), plaintext_buff, &length);
    if (!(memcmp(cbc_ecb_plaintext, plaintext_buff, sizeof(cbc_ecb_plaintext))) && (length == expected_length))
    {
        LOG_I("CRYPT_AES_ECB_DECRYPT_192_TEST_SUCCESS!------Length of decrypted data = %d",length);
    }
    else
    {
        LOG_I("CRYPT_AES_ECB_DECRYPT_192_TEST_FAIL!");
    }
    /*CRYPT_AES_CBC_TEST*/
    length = sizeof(ciphertext_buff);
    HAL_LSCRYPT_AES_CBC_Encrypt(cbc_iv, cbc_ecb_plaintext, sizeof(cbc_ecb_plaintext), ciphertext_buff, &length);
    if (!(memcmp(cbc_ciphertext_192, ciphertext_buff, sizeof(cbc_ciphertext_192))) && (length == expected_length))
    {
        LOG_I("CRYPT_AES_CBC_ENCRYPT_192_TEST_SUCCESS!------Length of encrypted data = %d",length);
    }
    else
    {
        LOG_I("CRYPT_AES_CBC_ENCRYPT_192_TEST_FAIL!");
    }
    length = sizeof(plaintext_buff);
    HAL_LSCRYPT_AES_CBC_Decrypt(cbc_iv, cbc_ciphertext_192, sizeof(cbc_ciphertext_192), plaintext_buff, &length);
    if (!(memcmp(cbc_ecb_plaintext, plaintext_buff, sizeof(cbc_ecb_plaintext))) && (length == expected_length))
    {
        LOG_I("CRYPT_AES_CBC_DECRYPT_192_TEST_SUCCESS!------Length of decrypted data = %d",length);
    }
    else
    {
        LOG_I("CRYPT_AES_CBC_DECRYPT_192_TEST_FAIL!");
    }
}

void crypt_cbc_ecb_test_256(void)
{
    HAL_LSCRYPT_AES_Key_Config(cbc_ecb_key_256, AES_KEY_256);
    /*CRYPT_AES_ECB_TEST*/
    length = sizeof(ciphertext_buff);
    HAL_LSCRYPT_AES_ECB_Encrypt(cbc_ecb_plaintext, sizeof(cbc_ecb_plaintext), ciphertext_buff, &length);
    if (!(memcmp(ecb_ciphertext_256, ciphertext_buff, sizeof(ecb_ciphertext_256))) && (length == expected_length))
    {
        LOG_I("CRYPT_AES_ECB_ENCRYPT_256_TEST_SUCCESS!------Length of encrypted data = %d",length);
    }
    else
    {
        LOG_I("CRYPT_AES_ECB_ENCRYPT_256_TEST_FAIL!");
    }
    length = sizeof(plaintext_buff);
    HAL_LSCRYPT_AES_ECB_Decrypt(ecb_ciphertext_256, sizeof(ecb_ciphertext_256), plaintext_buff, &length);
    if (!(memcmp(cbc_ecb_plaintext, plaintext_buff, sizeof(cbc_ecb_plaintext))) && (length == expected_length))
    {
        LOG_I("CRYPT_AES_ECB_DECRYPT_256_TEST_SUCCESS!------Length of decrypted data = %d",length);
    }
    else
    {
        LOG_I("CRYPT_AES_ECB_DECRYPT_256_TEST_FAIL!");
    }
    /*CRYPT_AES_CBC_TEST*/
    length = sizeof(ciphertext_buff);
    HAL_LSCRYPT_AES_CBC_Encrypt(cbc_iv, cbc_ecb_plaintext, sizeof(cbc_ecb_plaintext), ciphertext_buff, &length);
    if (!(memcmp(cbc_ciphertext_256, ciphertext_buff, sizeof(cbc_ciphertext_256))) && (length == expected_length))
    {
        LOG_I("CRYPT_AES_CBC_ENCRYPT_256_TEST_SUCCESS!------Length of encrypted data = %d",length);
    }
    else
    {
        LOG_I("CRYPT_AES_CBC_ENCRYPT_256_TEST_FAIL!");
    }
    length = sizeof(plaintext_buff);
    HAL_LSCRYPT_AES_CBC_Decrypt(cbc_iv, cbc_ciphertext_256, sizeof(cbc_ciphertext_256), plaintext_buff, &length);
    if (!(memcmp(cbc_ecb_plaintext, plaintext_buff, sizeof(cbc_ecb_plaintext))) && (length == expected_length))
    {
        LOG_I("CRYPT_AES_CBC_DECRYPT_256_TEST_SUCCESS!------Length of decrypted data = %d",length);
    }
    else
    {
        LOG_I("CRYPT_AES_CBC_DECRYPT_256_TEST_FAIL!");
    }
}

void crypt_cbc_ecb_test(void)
{
    HAL_LSCRYPT_Block_Padding_Mode_Set(Padding_None);
    crypt_cbc_ecb_test_128();
    crypt_cbc_ecb_test_192();
    crypt_cbc_ecb_test_256();
}

int main()
{
    sys_init_none();
    crypt_init();
    crypt_cbc_ecb_test();
    while (1)
    {
    }
}
