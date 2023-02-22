#ifndef REG_PATCH_TYPE_H_
#define REG_PATCH_TYPE_H_
#include <stdint.h>
#include "patch_config.h"

typedef struct{
    volatile uint32_t ADDR[ROM_PATCH_NUM];
    volatile uint32_t DATA[ROM_PATCH_NUM];
    volatile uint32_t EN;
}reg_patch_t;


#endif
