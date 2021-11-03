#include "lspatch.h"

void lspatch_enable(uint8_t idx,uint32_t addr,uint32_t data)
{
    LSPATCH->ADDR[idx] = addr;
    LSPATCH->DATA[idx] = data;
    LSPATCH->EN |= 1<<idx;
}