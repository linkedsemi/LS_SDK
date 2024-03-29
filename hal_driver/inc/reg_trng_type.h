#ifndef REG_LSTRNG_TYPE_H_
#define REG_LSTRNG_TYPE_H_
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    volatile uint32_t CR;
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t SEED;
    volatile uint32_t CFGR;
    volatile uint32_t IER;
    volatile uint32_t IFR;
    volatile uint32_t IFCR;
    volatile uint32_t ISR;
}reg_trng_t;

enum TRNG_REG_CR_FIELD
{
    TRNG_TRNGEN_MASK = 0x1,
    TRNG_TRNGEN_POS = 0,
    TRNG_ADJM_MASK = 0x2,
    TRNG_ADJM_POS = 1,
    TRNG_TRNGSEL_MASK = 0x4,
    TRNG_TRNGSEL_POS = 2,
    TRNG_POSTEN_MASK = 0x8,
    TRNG_POSTEN_POS = 3,
    TRNG_DSEL_MASK = 0x300,
    TRNG_DSEL_POS = 8,
    TRNG_SDSEL_MASK = 0xc00,
    TRNG_SDSEL_POS = 10,
    TRNG_ADJC_MASK = 0x30000,
    TRNG_ADJC_POS = 16,
};

enum TRNG_REG_SR_FIELD
{
    TRNG_START_MASK = 0x1,
    TRNG_START_POS = 0,
    TRNG_DAVLD_MASK = 0x2,
    TRNG_DAVLD_POS = 1,
    TRNG_SERR_MASK = 0x4,
    TRNG_SERR_POS = 2,
    TRNG_OVER_MASK = 0x8,
    TRNG_OVER_POS = 3,
    TRNG_TRNG0_SO_MASK = 0x1ff0000,
    TRNG_TRNG0_SO_POS = 16,
    TRNG_TRNG0_CLK_MASK = 0x2000000,
    TRNG_TRNG0_CLK_POS = 25,
    TRNG_TRNG1_SO_MASK = 0x4000000,
    TRNG_TRNG1_SO_POS = 26,
    TRNG_TRNG1_CLK_MASK = 0x8000000,
    TRNG_TRNG1_CLK_POS = 27,
    TRNG_TRNG1_SEED_MASK = 0x10000000,
    TRNG_TRNG1_SEED_POS = 28,
};

enum TRNG_REG_DR_FIELD
{
    TRNG_DATA_MASK = (int)0xffffffff,
    TRNG_DATA_POS = 0,
};

enum TRNG_REG_SEED_FIELD
{
    TRNG_SEED_MASK = (int)0xffffffff,
    TRNG_SEED_POS = 0,
};

enum TRNG_REG_CFGR_FIELD
{
    TRNG_TSTART_MASK = 0x7,
    TRNG_TSTART_POS = 0,
    TRNG_CKDIV_MASK = 0xf00,
    TRNG_CKDIV_POS = 8,
    TRNG_TOPLMT_MASK = 0x1ff0000,
    TRNG_TOPLMT_POS = 16,
};

enum TRNG_REG_IER_FIELD
{
    TRNG_IE_START_MASK = 0x1,
    TRNG_IE_START_POS = 0,
    TRNG_IE_DAVLD_MASK = 0x2,
    TRNG_IE_DAVLD_POS = 1,
    TRNG_IE_SERR_MASK = 0x4,
    TRNG_IE_SERR_POS = 2,
};

enum TRNG_REG_IFR_FIELD
{
    TRNG_FI_START_MASK = 0x1,
    TRNG_FI_START_POS = 0,
    TRNG_FI__DAVLD_MASK = 0x2,
    TRNG_FI__DAVLD_POS = 1,
    TRNG_FI__SERR_MASK = 0x4,
    TRNG_FI__SERR_POS = 2,
};

enum TRNG_REG_IFCR_FIELD
{
    TRNG_IFC_START_MASK = 0x1,
    TRNG_IFC_START_POS = 0,
    TRNG_IFC_DAVLD_MASK = 0x2,
    TRNG_IFC_DAVLD_POS = 1,
    TRNG_IFC_SERR_MASK = 0x4,
    TRNG_IFC_SERR_POS = 2,
};

enum TRNG_REG_ISR_FIELD
{
    TRNG_IS_START_MASK = 0x1,
    TRNG_IS_START_POS = 0,
    TRNG_IS_DAVLD_MASK = 0x2,
    TRNG_IS_DAVLD_POS = 1,
    TRNG_IS_SERR_MASK = 0x4,
    TRNG_IS_SERR_POS = 2,
};

#ifdef __cplusplus
}
#endif

#endif
