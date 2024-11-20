#ifndef REG_DWTRNG_TYPE_H_
#define REG_DWTRNG_TYPE_H_
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    volatile uint32_t   CTRL;//0x00
    volatile uint32_t   MODE;//0x04
    volatile uint32_t   SMODE;//0x08
    volatile uint32_t   STAT;//0x0c
    volatile uint32_t   IE;//0x10
    volatile uint32_t   ISTAT;//0x14
    volatile uint32_t   ALARMS;//0x18
    volatile uint32_t   COREKIT_REL;//0x1c
    volatile uint32_t   FEATURES;//0x20
    volatile uint32_t   RAND[0x4];//0x24
    volatile uint32_t   NPA_DATA[0x10];//0x34
    volatile uint32_t   SEED[0xC];//0x74
    volatile uint32_t   IA_RDATA;//0xa4
    volatile uint32_t   IA_WDATA;//0xa8
    volatile uint32_t   IA_ADDR;//0xac
    volatile uint32_t   IA_CMD;//0xb0
} reg_dwtrng_t;

#ifdef __cplusplus
}
#endif
#endif