#ifndef REG_LSECC_TYPE_H_
#define REG_LSECC_TYPE_H_
#include <stdint.h>

typedef struct
{
    volatile uint32_t ARAM[64];
    volatile uint32_t BRAM[64];
    volatile uint32_t NRAM[64];
    volatile uint32_t CON;
    volatile uint32_t STAT;
    volatile uint32_t DMACTR;
    volatile uint32_t OMEGA;
}reg_ecc_t;

enum ECC_REG_CON_FIELD
{
    ECC_RUN_MASK = (int)0x80000000,
    ECC_RUN_POS = 31,
    ECC_COMB_MASK = (int)0x40000000,
    ECC_COMB_POS = 30,
    ECC_REMAP_MASK = (int)0x20000000,
    ECC_REMAP_POS = 29,
    ECC_COMMOD_MASK = (int)0x18000000,
    ECC_COMMOD_POS = 27,
    ECC_OPL_MASK = (int)0x1C00,
    ECC_OPL_POS = 10,
    ECC_OPR_MASK = (int)0x380,
    ECC_OPR_POS = 7,
    ECC_RES_MASK = (int)0x70,
    ECC_RES_POS = 4,
    ECC_MODE_MASK = (int)0xE,
    ECC_MODE_POS = 1,
    ECC_RST_MASK = (int)0x1,
    ECC_RST_POS = 0,
};

enum ECC_REG_STAT_FIELD
{
    ECC_RUNNING_MASK = 0x1,
    ECC_RUNNING_POS = 0,
    ECC_DONE_MASK = 0x2,
    ECC_DONE_POS = 1,
    ECC_STATBIT_MASK = (int)0xfffffffc,
    ECC_STATBIT_POS = 2,
};

enum ECC_REG_DMACTR_FIELD
{
    ECC_DMA_EN_MASK = 0x1,
    ECC_DMA_EN_POS = 0,
};

#endif
