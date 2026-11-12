#ifndef REG_OTFAD_TYPE_H_
#define REG_OTFAD_TYPE_H_
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct
{
    uint32_t DMA_EN;
    uint32_t INTR_MSK;
    uint32_t INTR_CLR;
    uint32_t RESVERED0;
    uint32_t CTRL;
    uint32_t RESVERED1;
    uint32_t STAT; // 0x18
    uint32_t RESVERED2[9];
    uint32_t KEY0; // 0x40
    uint32_t KEY1;
    uint32_t KEY2;
    uint32_t KEY3;
    uint32_t KEY4;
    uint32_t KEY5;
    uint32_t KEY6;
    uint32_t KEY7; // 0x5c
    uint32_t RESVERED3[8];
    uint32_t COUNTER0; // 0x80
    uint32_t COUNTER1;
    uint32_t COUNTER2;
    uint32_t COUNTER3;
    uint32_t RESVERED4[4];
    uint32_t TEXT_RES0; // 0xa0
    uint32_t TEXT_RES1;
    uint32_t TEXT_RES2;
    uint32_t TEXT_RES3;
} aes_otfad_reg;

// #if defined(MBEDTLS_CIPHER_MODE_XTS)
// /**
//  * \brief The AES XTS context-type definition.
//  */
// typedef struct mbedtls_aes_xts_context {
//     mbedtls_aes_context MBEDTLS_PRIVATE(crypt); /*!< The AES context to use for AES block
//                                                    encryption or decryption. */
//     mbedtls_aes_context MBEDTLS_PRIVATE(tweak); /*!< The AES context used for tweak
//                                                    computation. */
// } mbedtls_aes_xts_context;
// #endif /* MBEDTLS_CIPHER_MODE_XTS */

#define STAT_AES_ERROR (1 << 3)
#define STAT_AES_EMPTY (1 << 2)
#define CTRL_INIT (1<<0)
#define CTRL_ENABLE (1<<1)
#define CTRL_MODE (1<<2)
#define CTRL_KEY_VALID (1<<6)
#define CTRL_IN_VALID (1<<7)
#define STAT_AES_READY (1 << 0)
#ifdef __cplusplus
}
#endif

#endif