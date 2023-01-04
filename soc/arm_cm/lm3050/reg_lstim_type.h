#ifndef REG_LSTIM_TYPE_H_
#define REG_LSTIM_TYPE_H_
#include <stdint.h>

#define LSTIM ((reg_tim_t *)0x4000f100)

typedef struct
{
    volatile uint32_t TIM_CTRL; //0x0
    volatile uint32_t TIM_TGT; //0x4
    volatile uint32_t RESERVED0[2];
    volatile uint32_t TIM_CNT; //0x10
    volatile uint32_t TIM_INTR; //0x14
}reg_tim_t;

enum TIM_REG_TIM_CTRL_FIELD
{
    TIM_TIM_EN_MASK = (int)0x1,
    TIM_TIM_EN_POS = 0,
    TIM_TIM_INTR_EN_MASK = (int)0x2,
    TIM_TIM_INTR_EN_POS = 1,
    TIM_TIM_INTR_CLR_MASK = (int)0x4,
    TIM_TIM_INTR_CLR_POS = 2,
};

enum TIM_REG_TIM_TGT_FIELD
{
    TIM_TIM_TGT_MASK = (int)0xffffffff,
    TIM_TIM_TGT_POS = 0,
};

enum TIM_REG_TIM_CNT_FIELD
{
    TIM_TIM_CNT_MASK = (int)0xffffffff,
    TIM_TIM_CNT_POS = 0,
};

enum TIM_REG_TIM_INTR_FIELD
{
    TIM_TIM_INTR_MASK = (int)0x1,
    TIM_TIM_INTR_POS = 0,
};

#endif

