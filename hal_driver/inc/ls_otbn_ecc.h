#ifndef _LS_OTBN_ECC_H_
#define _LS_OTBN_ECC_H_

typedef enum 
{
    LS_OTBN_CURVE_ECC_P256 = 0xf0,
    LS_OTBN_CURVE_ECC_P384,
    LS_OTBN_CURVE_SM2,
    LS_OTBN_CURVE_MAX,
}ls_otbn_curve_id;

typedef struct ls_otbn_current_remote_addr
{
    uint8_t curve_size;
    uint32_t mode;
    uint32_t remote_random_addr;
    uint32_t remote_mode_addr;
    uint32_t remote_addr_d0;
    uint32_t remote_addr_d1;
    uint32_t remote_addr_r;
    uint32_t remote_addr_s;
    uint32_t remote_addr_msg; // digest
    uint32_t remote_addr_qx;
    uint32_t remote_addr_qy;
    uint32_t remote_addr_r_x;
}ecc_remote_addr;

#define LS_OTBN_TRUE  0x00000739
#define LS_OTBN_FALSE 0x000001d4

extern const uint8_t p256_imem[4304];
extern const uint8_t p256_dmem[224];
#define LS_OTBN_ECDSA_P256_IMEM_SIZE    4304
#define LS_OTBN_ECDSA_P256_DMEM_SIZE    224
#define LS_OTBN_ECDSA_P256_DMEM_END     0x260
#define LS_OTBN_ECDSA_P256_OK                 0x00000104
/* random */
#define LS_OTBN_ECDSA_P256_RANDOM_SEED_OFFSET 0x000000e0
/* digest */
#define LS_OTBN_ECDSA_P256_MSG_OFFSET         0X00000120
/* sign */
#define LS_OTBN_ECDSA_P256_R_OFFSET           0X00000140
#define LS_OTBN_ECDSA_P256_S_OFFSET           0X00000160
/* private key */
#define LS_OTBN_ECDSA_P256_D0_OFFSET          0x000001c0
#define LS_OTBN_ECDSA_P256_D1_OFFSET          0x00000200
/* public key */
#define LS_OTBN_ECDSA_P256_X_OFFSET           0X00000180
#define LS_OTBN_ECDSA_P256_Y_OFFSET           0X000001a0
/* verify */
#define LS_OTBN_ECDSA_P256_X_R_OFFSET         0X00000240
/* mode */
#define LS_OTBN_ECDSA_P256_MODE_OFFSET        0x00000100
#define LS_OTBN_ECDSA_P256_MODE_SIGN          0x0000015b
#define LS_OTBN_ECDSA_P256_MODE_VERIFY        0x00000727
#define LS_OTBN_ECDSA_P256_MODE_KEYGEN        0x000003d4
#define LS_OTBN_ECDSA_P256_MODE_SHARED_KEY    0x000005ec

extern const uint8_t p384_imem[5572];
extern const uint8_t p384_dmem[1152];
#define LS_OTBN_ECDSA_P384_IMEM_SIZE    5572
#define LS_OTBN_ECDSA_P384_DMEM_SIZE    1152
#define LS_OTBN_ECDSA_P384_DMEM_END     0x00000c00
/* random */
#define LS_OTBN_ECDSA_P384_RANDOM_SEED_OFFSET 0x00000140
/* digest */
#define LS_OTBN_ECDSA_P384_MSG_OFFSET         0x00000300
/* sign */
#define LS_OTBN_ECDSA_P384_R_OFFSET           0x00000340
#define LS_OTBN_ECDSA_P384_S_OFFSET           0x00000380
/* private key */
#define LS_OTBN_ECDSA_P384_D0_OFFSET          0x000001c0
#define LS_OTBN_ECDSA_P384_D1_OFFSET          0x00000200
/* public key */
#define LS_OTBN_ECDSA_P384_X_OFFSET           0x000003c0
#define LS_OTBN_ECDSA_P384_Y_OFFSET           0x00000400
/* verify */
#define LS_OTBN_ECDSA_P384_X_R_OFFSET         0x00000440
/* mode */
#define LS_OTBN_ECDSA_P384_MODE_OFFSET        0x00000180
#define LS_OTBN_ECDSA_P384_MODE_SIGN          0x0000015b
#define LS_OTBN_ECDSA_P384_MODE_VERIFY        0x00000727
#define LS_OTBN_ECDSA_P384_MODE_KEYGEN        0x000003d4
#define LS_OTBN_ECDSA_P384_MODE_SHARED_KEY    0x000005ec

/* SM2 */
extern const uint8_t sm2_imem[2716];
extern const uint8_t sm2_dmem[320];
#define LS_OTBN_SM2_IMEM_SIZE    2716
#define LS_OTBN_SM2_DMEM_SIZE    320
#define LS_OTBN_SM2_DMEM_END     0x464
#define LS_OTBN_SM2_OK         0x00000460
/* random */
#define LS_OTBN_SM2_RANDOM_SEED_OFFSET 0x000000e0
/* digest */
#define LS_OTBN_SM2_MSG_OFFSET         0x00000320
/* sign */
#define LS_OTBN_SM2_R_OFFSET         0x00000340
#define LS_OTBN_SM2_S_OFFSET         0x00000360
/* private key */
#define LS_OTBN_SM2_D0_OFFSET         0x000002a0
#define LS_OTBN_SM2_D1_OFFSET         0x000002e0
/* public key */
#define LS_OTBN_SM2_X_OFFSET            0x00000380
#define LS_OTBN_SM2_Y_OFFSET            0x000003a0
/* verify */
#define LS_OTBN_SM2_X_R_OFFSET         0x000003c0
/* mode */
#define LS_OTBN_SM2_MODE_OFFSET           0x00000280
#define LS_OTBN_SM2_MODE_SIGN             0x0000015b
#define LS_OTBN_SM2_MODE_VERIFY           0x00000727
#define LS_OTBN_SM2_MODE_KEYGEN           0x000003d4
#define LS_OTBN_SM2_MODE_SHARED_KEY       0x000005ec


#define LS_OTBN_MODE_SIGN             0x0000015b
#define LS_OTBN_MODE_VERIFY           0x00000727
#define LS_OTBN_MODE_KEYGEN           0x000003d4
#define LS_OTBN_MODE_SHARED_KEY       0x000005ec



#endif





























// void wc_LS_Otbn_Module_Init(void);
// void wc_LS_Otbn_Module_DeInit(void);
// int ls_otbn_ecc_creat_key(struct ecc_key* key, int curve_id, int keySize);
// int ls_otbn_ecc_sign_hash_ex(const byte* in, word32 inLen, MATH_INT_T* r, MATH_INT_T* s,
//                             byte* out, word32 *outLen, struct ecc_key* key);
// int ls_otbn_ecc_shared_secret(ecc_key* private_key, ecc_key* public_key,
//                             byte* out, word32* outlen);
// int ls_otbn_ecc_verify_hash_ex(mp_int *r, mp_int *s, const byte* hash,
//                     word32 hashlen, int* res, ecc_key* key);
// #endif