#ifndef REG_SHA512_TYPE_H_
#define REG_SHA512_TYPE_H_
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    volatile uint32_t INTR_MSK;
    volatile uint32_t INTR_CLR;
    volatile uint32_t INTR_RAW;
    volatile uint32_t INTR_STT;
    volatile uint32_t CTRL; 
    volatile uint32_t RACTOR_NUM;
    volatile uint32_t ADDR;
    volatile uint32_t STATUS;
    volatile uint32_t RESERVED[40];//0x20
    volatile uint32_t DIGEST[16];
} reg_sha512_t;


#ifdef __cplusplus
}
#endif
#endif