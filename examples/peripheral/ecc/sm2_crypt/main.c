
#include <string.h>
#include <stdlib.h>
#include "ls_hal_sha.h"
#include "ls_hal_ecc.h"
#include "platform.h"
#include "log.h"

#define SM2_DECRYPT_MESSAGE_MAXLENGTH           (0x200)

static const uint8_t msg[0x20]=
{
    0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
    0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
    0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
    0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
};
static const uint8_t pubkey_x[]=
{
    0x3C, 0xD9, 0x2F, 0x5B, 0xD9, 0x29, 0x36, 0x50, 
    0x73, 0x8D, 0x70, 0x6B, 0xA0, 0xE8, 0x42, 0xAD, 
    0xED, 0x1B, 0x50, 0x5B, 0xCA, 0x57, 0xCB, 0xA4, 
    0x68, 0x1E, 0x7E, 0x9D, 0xD2, 0xE5, 0x72, 0xF8,
};
static const uint8_t pubkey_y[]=
{
    0xC6, 0x7C, 0xCB, 0xC5, 0x50, 0x8F, 0x0B, 0x2F, 
    0x0D, 0x27, 0xAB, 0x42, 0x01, 0x96, 0xB0, 0xEA, 
    0xA9, 0xC6, 0x70, 0xF8, 0xB7, 0x3E, 0xE2, 0x56, 
    0xA1, 0x6C, 0xCA, 0x8F, 0x0E, 0x14, 0x86, 0xD1,
};
static const uint8_t random_data[]=
{
    0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
    0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
    0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
    0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
};

static uint8_t buffer[0x100];

static uint8_t* sm2_random_generate()
{
    return (uint8_t *)random_data;    // Only for Test 
}


static bool sm2_check_zero(uint8_t *p, uint32_t len)
{
    for (uint32_t i = 0; i < len; i++)
    {
        if (p[i] != 0)
            return true;
    }
    return false;
}

static void copy_reverse(uint8_t *dest, uint8_t *src, uint32_t length)
{
    for (uint32_t i = 0; i < length; i++)
    {
        dest[i] = src[length - i - 1];
    }
}

static void arr_reverse(uint8_t *idx, uint32_t length)
{
    uint8_t temp;
    for (uint32_t i = 0; i < length / 2; i++)
    {
        temp = idx[i];
        idx[i] = idx[length - 1 - i];
        idx[length - 1 - i] = temp;
    }
}

static bool sm2_encrypt(const uint8_t *msg, uint32_t len, uint8_t *Px, uint8_t *Py, uint8_t *out)
{
    uint8_t S[0x40];
    uint8_t Z[0x40];
    uint8_t pubkey_x[0x20];
    uint8_t pubkey_y[0x20];
    uint8_t t[SM2_DECRYPT_MESSAGE_MAXLENGTH];
    uint8_t *C1 = out;
    uint8_t *C3 = C1 + 0x40;
    uint8_t *C2 = C3 + 0x20;
    const uint8_t *public_key[2] = {pubkey_x, pubkey_y};
    copy_reverse(pubkey_x, Px, 0x20);
    copy_reverse(pubkey_y, Py, 0x20);

    // step 1
    uint8_t *k = sm2_random_generate();
    
    // step 2
    uint8_t *pC1[2] = {C1, C1 + 0x20};
    const uint8_t *G[2] = {(uint8_t *)sm2_param.G, (uint8_t *)(sm2_param.G + 8)};
    HAL_LSECC_PointMult(&sm2_param, k, G, pC1);
    arr_reverse(pC1[0], 0x20);
    arr_reverse(pC1[1], 0x20);

    // step 3
    uint8_t *pS[2] = {S, S + 0x20};
    HAL_LSECC_PointMult(&sm2_param, (uint8_t *)sm2_param.n.h, public_key, pS);
    if (!sm2_check_zero(S, 0x40))
        return false;
    
    // step 4
    uint8_t *pZ[2] = {Z, Z + 0x20};
    HAL_LSECC_PointMult(&sm2_param, k, public_key, pZ);
    arr_reverse(pZ[0], 0x20);
    arr_reverse(pZ[1], 0x20);

    // step 5
    HAL_KDF_SM3(Z, 0x40, t, len);
    if (!sm2_check_zero(t, len))
        return false;

    // step 6
    for (uint32_t i = 0; i < len; i++)
        C2[i] = msg[i] ^ t[i];
    
    // step 7
    HAL_LSSHA_SM3_Init();
    HAL_LSSHA_Update(pZ[0], 0x20);
    HAL_LSSHA_Update(msg, len);
    HAL_LSSHA_Update(pZ[1], 0x20);
    HAL_LSSHA_Final(C3);

    return true;
}

int main(void)
{
    sys_init_none();
    HAL_LSECC_Init();
    HAL_LSSHA_Init();

    // output : C1C3C2(GMT 0003.4)StandardFormat 
    if(sm2_encrypt((uint8_t *)msg, sizeof(msg), (uint8_t *)pubkey_x, (uint8_t *)pubkey_y, buffer))
    {
        LOG_I("sm2 encrypt msg ciphertext:");
        LOG_HEX(buffer, 0x100);
    }
    else
    {
        LOG_I("sm2 encrypt msg fail...");
    }

    while (1)
    {

    }
}

// ciphertext : 0xEED74B66F14CBAD8AD479295474C921F6642F34CE92A82381C473365DF1D367187C13F9D0545607228BDA49E322C7445DE21BC60346451B6509E32B0EC2355874811468C9C67C6422A9CAFE40C610E9709CBBC94BFBA65995284C9533E91CEFCBA10A8E1B2B5FF872DC65842D3E784F64C740EE95DFDB2167983FB5E2E4F4268