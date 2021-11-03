#ifndef LSPATCH_H_
#define LSPATCH_H_
#include "reg_patch_type.h"
#include "reg_base_addr.h"

#define LSPATCH ((reg_patch_t *)LSPATCH_BASE_ADDR)

void lspatch_enable(uint8_t idx,uint32_t addr,uint32_t data);

#endif
