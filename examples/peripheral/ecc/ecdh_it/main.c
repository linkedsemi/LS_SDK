#include "ls_hal_ecc.h"
#include "ls_msp_ecc.h"
#include <string.h>
#include <stdlib.h>
#include "field_manipulate.h"
#include "platform.h"
#include "common.h"
#include "log.h"

#define secp256r1   1
// #define sm2         1

enum lsecc_type
{
    LSECC_POINTMULT_Alicepubkey,
    LSECC_POINTMULT_Bobpubkey,
    LSECC_POINTMULT_sharekey1,
    LSECC_POINTMULT_sharekey2,
};
volatile enum lsecc_type lsecc_type_flag = LSECC_POINTMULT_Alicepubkey;

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

const static uint8_t pri_key1[32] = {
    0x17, 0xb2, 0xc2, 0x64, 0x85, 0x05, 0x41, 0x41,
    0x36, 0x15, 0xa5, 0xa4, 0x35, 0xe5, 0xe3, 0x9c,
    0x54, 0xf5, 0x11, 0x6e, 0x7a, 0xb0, 0x6a, 0xe4,
    0xed, 0xa7, 0x76, 0x3c, 0x15, 0x0f, 0x77, 0x77};

const static uint8_t pri_key2[32] = {
    0x12, 0x25, 0x03, 0xd6, 0x47, 0x27, 0xcb, 0x08,
    0x79, 0xe3, 0x41, 0x70, 0x1e, 0x22, 0xce, 0x50,
    0x59, 0xa0, 0xdd, 0xdc, 0x9a, 0x4a, 0x35, 0x1e,
    0xcf, 0x0e, 0x7c, 0x6c, 0xa9, 0x7a, 0x0a, 0x4b};

static uint8_t P1x[32] = {0};
static uint8_t P1y[32] = {0};
static uint8_t *pub_key1[2] = {P1x, P1y};
static uint8_t P2x[32] = {0};
static uint8_t P2y[32] = {0};
static uint8_t *pub_key2[2] = {P2x, P2y};

static uint8_t s1x[32] = {0};
static uint8_t s1y[32] = {0};
static uint8_t *share_key1[2] = {s1x, s1y};
static uint8_t s2x[32] = {0};
static uint8_t s2y[32] = {0};
static uint8_t *share_key2[2] = {s2x, s2y};

const static uint8_t *pubkey1[2] = {P1x, P1y};
const static uint8_t *pubkey2[2] = {P2x, P2y};
void lsecc_test(void)
{
    #if secp256r1
    //Generate public key
    HAL_LSECC_PointMult_IT(&secp256r1_param, pri_key1, BasePoint, pub_key1);
    while (lsecc_type_flag == LSECC_POINTMULT_Alicepubkey);

    HAL_LSECC_PointMult_IT(&secp256r1_param, pri_key2, BasePoint, pub_key2);  //bG
    while (lsecc_type_flag == LSECC_POINTMULT_Bobpubkey);

    //Generating shared key
    HAL_LSECC_PointMult_IT(&secp256r1_param, pri_key1, pubkey2, share_key1);  //a * bG
    while (lsecc_type_flag == LSECC_POINTMULT_sharekey1);

    HAL_LSECC_PointMult_IT(&secp256r1_param, pri_key2, pubkey1, share_key2);  //b * aG
    while (lsecc_type_flag == LSECC_POINTMULT_sharekey2);

    #elif sm2
    //Generate public key
    HAL_LSECC_PointMult_IT(&sm2_param, pri_key1, BasePoint, pub_key1);
    while (lsecc_type_flag == LSECC_POINTMULT_Alicepubkey);

    HAL_LSECC_PointMult_IT(&sm2_param, pri_key2, BasePoint, pub_key2);  //bG
    while (lsecc_type_flag == LSECC_POINTMULT_Bobpubkey);

    //Generating shared key
    HAL_LSECC_PointMult_IT(&sm2_param, pri_key1, pubkey2, share_key1);  //a * bG
    while (lsecc_type_flag == LSECC_POINTMULT_sharekey1);

    HAL_LSECC_PointMult_IT(&sm2_param, pri_key2, pubkey1, share_key2);  //b * aG
    while (lsecc_type_flag == LSECC_POINTMULT_sharekey2);

    #endif
}

bool Array_element_judgment(uint8_t* arr1, uint8_t* arr2)
{
    uint8_t j=0,k=0;
    for(uint8_t i=0;i<32;i++)
    {
        if(*arr1 == 0)
        {
            j++;
        }
        if(*arr2 == 0)
        {
            k++;
        }
        arr1++;
        arr2++;
    }
    if(j == 32 || k == 32)
    {
        return false;
    }
    else
    {
        return true;
    }
}

int main(void)
{
    sys_init_none();
    HAL_LSECC_Init();
    lsecc_test();
    while (1)
    {
    }
}

void HAL_LSECC_PointMult_Complete_Callback(void)
{
    switch (lsecc_type_flag)
    {
    case LSECC_POINTMULT_Alicepubkey:
        if(Array_element_judgment(P1x, P1y) == 1)
        {
            lsecc_type_flag = LSECC_POINTMULT_Bobpubkey;
        }
        break;
    case LSECC_POINTMULT_Bobpubkey:
        if(Array_element_judgment(P2x, P2y) == 1)
        {
            lsecc_type_flag = LSECC_POINTMULT_sharekey1;
        }
    case LSECC_POINTMULT_sharekey1:
        if(Array_element_judgment(s1x, s1y) == 1)
        {
            lsecc_type_flag = LSECC_POINTMULT_sharekey2;
        }
    case LSECC_POINTMULT_sharekey2:
    {
        if(Array_element_judgment(s2x, s2y) == 1)
        {
            if ((!memcmp(s1x, s2x, 32)) && (!memcmp(s1y, s2y, 32)))
            {
                LOG_I("ECDH TEST SUCCESS");
            }
        }
    }
    default:
        break;
    }
}