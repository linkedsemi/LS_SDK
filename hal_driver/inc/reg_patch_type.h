#ifndef REG_PATCH_TYPE_H_
#define REG_PATCH_TYPE_H_
#include <stdint.h>
#include "patch_config.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct{
    volatile uint32_t ADDR[ROM_PATCH_NUM];
    volatile uint32_t DATA[ROM_PATCH_NUM];
    volatile uint32_t EN;
}reg_patch_t;


#ifdef __cplusplus
}
#endif

#endif
