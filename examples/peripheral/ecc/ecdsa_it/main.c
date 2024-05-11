#include "ls_hal_ecc.h"
#include "ls_msp_ecc.h"
#include <string.h>
#include <stdlib.h>
#include "field_manipulate.h"
#include "ls_hal_trng.h"
#include "ls_hal_sha.h"
#include "platform.h"
#include "common.h"
#include "log.h"


#define secp256r1   1
// #define secp256k1   1
// #define sm2         1

enum lsecdsa_type
{
    LSECC_SIGN,
    LSECC_VERIFY,
};
volatile enum lsecdsa_type lsecc_type_flag = LSECC_SIGN;

#if secp256r1
// Base Point : G
const static uint8_t Gx[32] = {
    0x96, 0xC2, 0x98, 0xD8, 0x45, 0x39, 0xA1, 0xF4,
    0xA0, 0x33, 0xEB, 0x2D, 0x81, 0x7D, 0x03, 0x77,
    0xF2, 0x40, 0xA4, 0x63, 0xE5, 0xE6, 0xBC, 0xF8,
    0x47, 0x42, 0x2C, 0xE1, 0xF2, 0xD1, 0x17, 0x6B};

const static uint8_t Gy[32] = {
    0xF5, 0x51, 0xBF, 0x37, 0x68, 0x40, 0xB6, 0xCB,
    0xCE, 0x5E, 0x31, 0x6B, 0x57, 0x33, 0xCE, 0x2B,
    0x16, 0x9E, 0x0F, 0x7C, 0x4A, 0xEB, 0xE7, 0x8E,
    0x9B, 0x7F, 0x1A, 0xFE, 0xE2, 0x42, 0xE3, 0x4F};


#elif secp256k1
const static uint8_t Gx[32] = {
    0x98, 0x17, 0xF8, 0x16, 0x5B, 0x81, 0xF2, 0x59,
    0xD9, 0x28, 0xCE, 0x2D, 0xDB, 0xFC, 0x9B, 0x02, 
    0x07, 0x0B, 0x87, 0xCE, 0x95, 0x62, 0xA0, 0x55,
    0xAC, 0xBB, 0xDC, 0xF9, 0x7E, 0x66, 0xBE, 0x79};

const static uint8_t Gy[32] = {
    
    0xB8, 0xD4, 0x10, 0xFB, 0x8F, 0xD0, 0x47, 0x9C,
    0x19, 0x54, 0x85, 0xA6, 0x48, 0xB4, 0x17, 0xFD,
    0xA8, 0x08, 0x11, 0x0E, 0xFC, 0xFB, 0xA4, 0x5D,
    0x65, 0xC4, 0xA3, 0x26, 0x77, 0xDA, 0x3A, 0x48};


#elif sm2
const static uint8_t Gx[32] = {
    0xC7, 0x74, 0x4C, 0x33, 0x89, 0x45, 0x5A, 0x71,
    0xE1, 0x0B, 0x66, 0xF2, 0xBF, 0x0B, 0xE3, 0x8F,
    0x94, 0xC9, 0x39, 0x6A, 0x46, 0x04, 0x99, 0x5F,
    0x19, 0x81, 0x19, 0x1F, 0x2C, 0xAE, 0xC4, 0x32};

const static uint8_t Gy[32] = {
    0xA0, 0xF0, 0x39, 0x21, 0xE5, 0x32, 0xDF, 0x02,
    0x40, 0x47, 0x2A, 0xC6, 0x7C, 0x87, 0xA9, 0xD0,
    0x53, 0x21, 0x69, 0x6B, 0xE3, 0xCE, 0xBD, 0x59,
    0x9C, 0x77, 0xF6, 0xF4, 0xA2, 0x36, 0x37, 0xBC};

#endif


const static uint8_t *BasePoint[2] = {Gx, Gy};

 static uint8_t pri_key1[32] = {
    0x17, 0xb2, 0xc2, 0x64, 0x85, 0x05, 0x41, 0x41,
    0x36, 0x15, 0xa5, 0xa4, 0x35, 0xe5, 0xe3, 0x9c,
    0x54, 0xf5, 0x11, 0x6e, 0x7a, 0xb0, 0x6a, 0xe4,
    0xed, 0xa7, 0x76, 0x3c, 0x15, 0x0f, 0x77, 0x77};

static const uint8_t plaintext[32] = {
    0xA7, 0xFC, 0xFC, 0x6B, 0x52, 0x69, 0xBD, 0xCC, 0xE5, 0x71, 0x79, 0x8D, 0x61, 0x8E, 0xA2, 0x19,
    0xA6, 0x8B, 0x96, 0xCB, 0x87, 0xA0, 0xE2, 0x10, 0x80, 0xC2, 0xE7, 0x58, 0xD2, 0x3E, 0x4C, 0xE9};

static uint8_t P1x[32] = {0};
static uint8_t P1y[32] = {0};
static uint8_t *pub_key1[2] = {P1x, P1y};

static uint8_t P2x[32] = {0};
static uint8_t P2y[32] = {0};
static uint8_t *pub_key2[2] = {P2x, P2y};

uint32_t random32bit = 0x11223344;
uint32_t cipherbuffer_sha256[8];
uint8_t sign[64]={0};

bool sign_element_judgment(uint8_t *arr)
{
    uint8_t j = 0;
    for(uint8_t i = 0; i<32; i++)
    {
        if(*arr == 0)
        {
            j++;
        }
        arr++;
    }
    if(j == 32)
        return false;
    else
        return true;
}
void sign_test()
{
    #if secp256r1
    HAL_LSECC_PointMult(&secp256r1_param, (uint8_t*)&random32bit, BasePoint, pub_key1);//k*G
    HAL_LSECC_PointMult(&secp256r1_param, pri_key1, BasePoint, pub_key2);//da*G
    HAL_LSSHA_SHA256(plaintext, sizeof(plaintext), cipherbuffer_sha256);
    HAL_LSECC_Sign_IT(&secp256r1_param, pri_key1, (uint8_t *)cipherbuffer_sha256, sizeof(cipherbuffer_sha256), (uint8_t*)&random32bit, sign);
    while (lsecc_type_flag == LSECC_SIGN);
    const static uint8_t *pubkey2[2] = {P2x, P2y};
    HAL_LSECC_Verify_IT(&secp256r1_param, pubkey2, (uint8_t *)cipherbuffer_sha256, sizeof(cipherbuffer_sha256), sign);
    while (lsecc_type_flag == LSECC_VERIFY);

    #elif secp256k1
    HAL_LSECC_PointMult(&secp256k1_param, (uint8_t*)&random32bit, BasePoint, pub_key1);//k*G
    HAL_LSECC_PointMult(&secp256k1_param, pri_key1, BasePoint, pub_key2);//da*G
    HAL_LSSHA_SHA256(plaintext, sizeof(plaintext), cipherbuffer_sha256);
    HAL_LSECC_Sign_IT(&secp256k1_param, pri_key1, (uint8_t *)cipherbuffer_sha256, sizeof(cipherbuffer_sha256), (uint8_t*)&random32bit, sign);
    while (lsecc_type_flag == LSECC_SIGN);
    const static uint8_t *pubkey2[2] = {P2x, P2y};
    HAL_LSECC_Verify_IT(&secp256k1_param, pubkey2, (uint8_t *)cipherbuffer_sha256, sizeof(cipherbuffer_sha256), sign);
    while (lsecc_type_flag == LSECC_VERIFY);

    #elif sm2
    HAL_LSECC_PointMult(&sm2_param, (uint8_t*)&random32bit, BasePoint, pub_key1);//k*G
    HAL_LSECC_PointMult(&sm2_param, pri_key1, BasePoint, pub_key2);//da*G
    HAL_LSSHA_SHA256(plaintext, sizeof(plaintext), cipherbuffer_sha256);
    HAL_LSECC_Sign_IT(&sm2_param, pri_key1, (uint8_t *)cipherbuffer_sha256, sizeof(cipherbuffer_sha256), (uint8_t*)&random32bit, sign);
    while (lsecc_type_flag == LSECC_SIGN);
    const static uint8_t *pubkey2[2] = {P2x, P2y};
    HAL_LSECC_Verify_IT(&sm2_param, pubkey2, (uint8_t *)cipherbuffer_sha256, sizeof(cipherbuffer_sha256), sign);
    while (lsecc_type_flag == LSECC_VERIFY);

    #endif
}

int main(void)
{
    sys_init_none();
    HAL_LSECC_Init();
    HAL_LSSHA_Init();
    sign_test();
    while (1)
    {
    }
}

void HAL_LSECC_Sign_Complete_Callback(void)
{
    if(sign_element_judgment(sign) == 1)
    {
        LOG_I("ecdsa signature success");
    }
    lsecc_type_flag = LSECC_VERIFY;
}

void HAL_LSECC_Verify_Complete_Callback(bool succeed)
{
    if(succeed)
    {
        LOG_I("ecdsa verify success");
    }
    else
    {
        LOG_I("ecdsa verify error");
    }
}
