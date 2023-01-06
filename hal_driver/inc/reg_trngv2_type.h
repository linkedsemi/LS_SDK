#ifndef REG_TRNG_TYPE_H_
#define REG_TRNG_TYPE_H_
#include <stdint.h>

typedef struct
{
    volatile uint32_t TRNG_CTRL; //0x0
    volatile uint32_t CS_CNT_TH_L; //0x4
    volatile uint32_t CS_CNT_TH_H; //0x8
    volatile uint32_t GOOD_TH; //0xc
    volatile uint32_t NB_SMPL_LOCK_CYC; //0x10
    volatile uint32_t RO_SEL_OPT; //0x14
    volatile uint32_t RO0_DLY_SEL; //0x18
    volatile uint32_t RO1_DLY_SEL; //0x1c
    volatile uint32_t INTR_MSK; //0x20
    volatile uint32_t INTR_CLR; //0x24
    volatile uint32_t INTR_STAT; //0x28
    volatile uint32_t INTR_RAW; //0x2c
    volatile uint32_t TRNG_OUT; //0x30
    volatile uint32_t CUR_RO_SLE; //0x34
}reg_trng_t;

enum TRNG_REG_TRNG_CTRL_FIELD
{
    TRNG_FSM_RST_MASK = (int)0x1,
    TRNG_FSM_RST_POS = 0,
};

enum TRNG_REG_CS_CNT_TH_L_FIELD
{
    TRNG_CS_CNT_TH_L_MASK = (int)0xfffff,
    TRNG_CS_CNT_TH_L_POS = 0,
};

enum TRNG_REG_CS_CNT_TH_H_FIELD
{
    TRNG_CS_CNT_TH_H_MASK = (int)0xfffff,
    TRNG_CS_CNT_TH_H_POS = 0,
};

enum TRNG_REG_GOOD_TH_FIELD
{
    TRNG_GOOD_TH_H_MASK = (int)0xfff0000,
    TRNG_GOOD_TH_H_POS = 16,
    TRNG_GOOD_TH_L_MASK = (int)0xfff,
    TRNG_GOOD_TH_L_POS = 0,
};

enum TRNG_REG_NB_SMPL_LOCK_CYC_FIELD
{
    TRNG_MAX_LOCK_CYC_MASK = (int)0xfff0000,
    TRNG_MAX_LOCK_CYC_POS = 16,
    TRNG_NB_SMPL_MASK = (int)0xfff,
    TRNG_NB_SMPL_POS = 0,
};

enum TRNG_REG_RO_SEL_OPT_FIELD
{
    TRNG_RO_SEL_INIT_MASK = (int)0xfff0,
    TRNG_RO_SEL_INIT_POS = 4,
    TRNG_RO_SEL_CTRL_MASK = (int)0x1,
    TRNG_RO_SEL_CTRL_POS = 0,
};

enum TRNG_REG_RO0_DLY_SEL_FIELD
{
    TRNG_RO0_DLY_SEL_MASK = (int)0xffffffff,
    TRNG_RO0_DLY_SEL_POS = 0,
};

enum TRNG_REG_RO1_DLY_SEL_FIELD
{
    TRNG_RO1_DLY_SEL_MASK = (int)0xffffffff,
    TRNG_RO1_DLY_SEL_POS = 0,
};

enum TRNG_REG_INTR_MSK_FIELD
{
    TRNG_INTR_ALL_MASK = (int)0xf,
    TRNG_INTR_ALL_POS = 0,
    TRNG_INTR_RISI_MASK = (int)0x1,
    TRNG_INTR_RISI_POS = 0,
    TRNG_INTR_FALLING_MASK = (int)0x2,
    TRNG_INTR_FALLING_POS = 1,
    TRNG_INTR_LOCK_MASK = (int)0x4,
    TRNG_INTR_LOCK_POS = 2,
    TRNG_INTR_NOFND_MASK = (int)0x8,
    TRNG_INTR_NOFND_POS = 3,
};

enum TRNG_REG_TRNG_OUT_FIELD
{
    TRNG_MATCHED_MASK = (int)0x1,
    TRNG_MATCHED_POS = 0,
    TRNG_LOCKED_MASK = (int)0x2,
    TRNG_LOCKED_POS = 1,
    TRNG_NO_FND_MASK = (int)0x4,
    TRNG_NO_FND_POS = 2,
    TRNG_RAND_DAT_MASK = (int)0xffff0000,
    TRNG_RAND_DAT_POS = 16,
};

enum TRNG_REG_CUR_RO_SLE_FIELD
{
    TRNG_CUR_RO_SEL_MASK = (int)0xfff,
    TRNG_CUR_RO_SEL_POS = 0,
};

#endif

