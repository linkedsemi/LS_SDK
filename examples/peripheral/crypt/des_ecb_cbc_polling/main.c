#include <string.h>
#include <stdlib.h>
#include "ls_hal_crypt.h"
#include "platform.h"
#include "log.h"

/**des_cbc-ecb-key-ciphertext-64**/
const uint32_t des_tdes_cbc_ecb_key_64[] = {
    0x05060708,
    0x01020304};

const uint8_t des_ecb_ciphertext_64[] = {
    0x77,0xA7,0xD6,0xBC,0xF5,0x79,0x62,0xB9,0x77,0xA7,0xD6,0xBC,0xF5,0x79,0x62,0xB9};

const uint8_t des_cbc_ciphertext_64[] = {
    0xB0,0x73,0xDC,0x3F,0xB2,0x09,0x53,0x6D,0x24,0x3C,0x6B,0x6A,0x39,0x60,0xF2,0x8E};


/**tdes_cbc-ecb-key-ciphertext-128**/
const uint32_t tdes_cbc_ecb_key_128[] = {
    0xA5A6A7A8,
    0xA1A2A3A4,
    0x05060708,
    0x01020304};

const uint8_t tdes_ecb_ciphertext_128[] = {
    0x53,0x40,0xB5,0xDF,0x02,0xF1,0x6A,0x66,0x53,0x40,0xB5,0xDF,0x02,0xF1,0x6A,0x66};

const uint8_t tdes_cbc_ciphertext_128[] = {
    0xCA,0xB9,0x2D,0x0C,0x58,0x08,0xF0,0xA7,0xA6,0xE7,0xC7,0xE2,0x9F,0x2C,0x14,0xA2};


/**tdes_cbc-ecb-key-ciphertext-192**/
const uint32_t tdes_cbc_ecb_key_192[] = {
    0xB5B6B7B8,
    0xB1B2B3B4,
    0xA5A6A7A8,
    0xA1A2A3A4,
    0x05060708,
    0x01020304};

const uint8_t tdes_ecb_ciphertext_192[] = {
   0x52,0xB7,0xDC,0x6B,0x26,0xCC,0xA0,0x77,0x52,0xB7,0xDC,0x6B,0x26,0xCC,0xA0,0x77};

const uint8_t tdes_cbc_ciphertext_192[] = {
   0xC8,0xFD,0x1B,0xA5,0x34,0xE3,0x0A,0xCA,0x71,0x9A,0xFF,0x16,0x95,0xA5,0x94,0xAD};


/**cbc-iv**/
const uint32_t cbc_iv[] = {
    0x05060708,
    0x01020304};

/**cbc-ecb-plaintext**/
const uint8_t cbc_ecb_plaintext[] = {
    0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};

/**buff**/
uint8_t ciphertext_buff[16];
uint8_t plaintext_buff[16];
uint32_t expected_length = sizeof(cbc_ecb_plaintext);
uint32_t length;

void des_init(void)
{
    HAL_LSCRYPT_Init();
}

// des
void des_ecb_cbc_test_64(void)
{ 
    HAL_LSCRYPT_DES_Key_Config(des_tdes_cbc_ecb_key_64,DES_KEY_64);
    // ecb    
    length = sizeof(ciphertext_buff);
    HAL_LSCRYPT_DES_ECB_Encrypt(cbc_ecb_plaintext,sizeof(cbc_ecb_plaintext),ciphertext_buff,&length);    
    if (!(memcmp(des_ecb_ciphertext_64, ciphertext_buff, sizeof(des_ecb_ciphertext_64))) && (length == expected_length))
    {
        LOG_I("CRYPT_DES_ECB_ENCRYPT_64_TEST_SUCCESS!");
    }
    else
    {
        LOG_I("CRYPT_DES_ECB_ENCRYPT_64_TEST_FAIL!");
    }

    length = sizeof(plaintext_buff);
    HAL_LSCRYPT_DES_ECB_Decrypt(des_ecb_ciphertext_64,sizeof(des_ecb_ciphertext_64),plaintext_buff,&length);    
    if (!(memcmp(cbc_ecb_plaintext, plaintext_buff, sizeof(cbc_ecb_plaintext))))
    {
        LOG_I("CRYPT_DES_ECB_DECRYPT_64_TEST_SUCCESS!");
    }
    else
    {
        LOG_I("CRYPT_DES_ECB_DECRYPT_64_TEST_FAIL!");
    }

    // cbc
    length = sizeof(ciphertext_buff);
    HAL_LSCRYPT_DES_CBC_Encrypt(cbc_iv,cbc_ecb_plaintext,sizeof(cbc_ecb_plaintext),ciphertext_buff,&length);    
    if (!(memcmp(des_cbc_ciphertext_64, ciphertext_buff, sizeof(des_cbc_ciphertext_64))))
    {
        LOG_I("CRYPT_DES_CBC_ENCRYPT_64_TEST_SUCCESS!");
    }
    else
    {
        LOG_I("CRYPT_DES_CBC_ENCRYPT_64_TEST_FAIL!");
    }

    length = sizeof(plaintext_buff);
    HAL_LSCRYPT_DES_CBC_Decrypt(cbc_iv,des_cbc_ciphertext_64,sizeof(des_cbc_ciphertext_64),plaintext_buff,&length);    
    if (!(memcmp(cbc_ecb_plaintext, plaintext_buff, sizeof(cbc_ecb_plaintext))))
    {
        LOG_I("CRYPT_DES_CBC_DECRYPT_64_TEST_SUCCESS!");
    }
    else
    {
        LOG_I("CRYPT_DES_CBC_DECRYPT_64_TEST_FAIL!");
    }
}

// tdes
void tdes_ecb_cbc_test_128(void)
{        
    HAL_LSCRYPT_DES_Key_Config(tdes_cbc_ecb_key_128,TDES_KEY_128);
    // ecb
    length = sizeof(ciphertext_buff);
    HAL_LSCRYPT_DES_ECB_Encrypt(cbc_ecb_plaintext,sizeof(cbc_ecb_plaintext),ciphertext_buff,&length);    
    if (!(memcmp(tdes_ecb_ciphertext_128, ciphertext_buff, sizeof(tdes_ecb_ciphertext_128))))
    {
        LOG_I("CRYPT_TDES_ECB_ENCRYPT_128_TEST_SUCCESS!");
    }
    else
    {
        LOG_I("CRYPT_TDES_ECB_ENCRYPT_128_TEST_FAIL!");
    }

    length = sizeof(plaintext_buff);
    HAL_LSCRYPT_DES_ECB_Decrypt(tdes_ecb_ciphertext_128,sizeof(tdes_ecb_ciphertext_128),plaintext_buff,&length);    
    if (!(memcmp(cbc_ecb_plaintext, plaintext_buff, sizeof(cbc_ecb_plaintext))))
    {
        LOG_I("CRYPT_TDES_ECB_DECRYPT_128_TEST_SUCCESS!");
    }
    else
    {
        LOG_I("CRYPT_TDES_ECB_DECRYPT_128_TEST_FAIL!");
    }  

    // cbc
    length = sizeof(ciphertext_buff);    
    HAL_LSCRYPT_DES_CBC_Encrypt(cbc_iv,cbc_ecb_plaintext,sizeof(cbc_ecb_plaintext),ciphertext_buff,&length);    
    if (!(memcmp(tdes_cbc_ciphertext_128, ciphertext_buff, sizeof(tdes_cbc_ciphertext_128))))
    {
        LOG_I("CRYPT_TDES_CBC_ENCRYPT_128_TEST_SUCCESS!");
    }
    else
    {
        LOG_I("CRYPT_TDES_CBC_ENCRYPT_128_TEST_FAIL!");
    }

    length = sizeof(plaintext_buff);
    HAL_LSCRYPT_DES_CBC_Decrypt(cbc_iv,ciphertext_buff,sizeof(ciphertext_buff),plaintext_buff,&length);    
    if (!(memcmp(cbc_ecb_plaintext, plaintext_buff, sizeof(cbc_ecb_plaintext))))
    {
        LOG_I("CRYPT_TDES_CBC_DECRYPT_128_TEST_SUCCESS!");
    }
    else
    {
        LOG_I("CRYPT_TDES_CBC_DECRYPT_128_TEST_FAIL!");
    }
}

void tdes_ecb_cbc_test_192(void)
{  
    HAL_LSCRYPT_DES_Key_Config(tdes_cbc_ecb_key_192,TDES_KEY_192);
    // ecb
    length = sizeof(ciphertext_buff);

    HAL_LSCRYPT_DES_ECB_Encrypt(cbc_ecb_plaintext,sizeof(cbc_ecb_plaintext),ciphertext_buff,&length);    
    if (!(memcmp(tdes_ecb_ciphertext_192, ciphertext_buff, sizeof(tdes_ecb_ciphertext_192))))
    {
        LOG_I("CRYPT_TDES_ECB_ENCRYPT_192_TEST_SUCCESS!");
    }
    else
    {
        LOG_I("CRYPT_TDES_ECB_ENCRYPT_192_TEST_FAIL!");
    }

    length = sizeof(plaintext_buff);
    HAL_LSCRYPT_DES_ECB_Decrypt(tdes_ecb_ciphertext_192,sizeof(tdes_ecb_ciphertext_192),plaintext_buff,&length);    
    if (!(memcmp(cbc_ecb_plaintext, plaintext_buff, sizeof(cbc_ecb_plaintext))))
    {
        LOG_I("CRYPT_TDES_ECB_DECRYPT_192_TEST_SUCCESS!");
    }
    else
    {
        LOG_I("CRYPT_TDES_ECB_DECRYPT_192_TEST_FAIL!");
    }

    // cbc
    length = sizeof(ciphertext_buff);
    HAL_LSCRYPT_DES_CBC_Encrypt(cbc_iv,cbc_ecb_plaintext,sizeof(cbc_ecb_plaintext),ciphertext_buff,&length);    
    if (!(memcmp(tdes_cbc_ciphertext_192, ciphertext_buff, sizeof(tdes_cbc_ciphertext_192))))
    {
        LOG_I("CRYPT_TDES_CBC_ENCRYPT_192_TEST_SUCCESS!");
    }
    else
    {
        LOG_I("CRYPT_TDES_CBC_ENCRYPT_192_TEST_FAIL!");
    }

    length = sizeof(plaintext_buff);
    HAL_LSCRYPT_DES_CBC_Decrypt(cbc_iv,tdes_cbc_ciphertext_192,sizeof(tdes_cbc_ciphertext_192),plaintext_buff,&length);    
    if (!(memcmp(cbc_ecb_plaintext, plaintext_buff, sizeof(cbc_ecb_plaintext))))
    {
        LOG_I("CRYPT_TDES_CBC_DECRYPT_192_TEST_SUCCESS!");
    }
    else
    {
        LOG_I("CRYPT_TDES_CBC_DECRYPT_192_TEST_FAIL!");
    }
}
void des_cbc_ecb_test(void)
{
    des_ecb_cbc_test_64();
    tdes_ecb_cbc_test_128();
    tdes_ecb_cbc_test_192();
    
}

int main()
{
    sys_init_none();
    des_init();
    des_cbc_ecb_test();
    while (1)
    {
    }
}


