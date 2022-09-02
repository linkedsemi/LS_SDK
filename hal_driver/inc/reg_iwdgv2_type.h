#ifndef REG_IWDTV2_TYPE_H_
#define REG_IWDTV2_TYPE_H_
#include <stdint.h>

typedef struct
{
    volatile uint32_t IWDT_LOAD; //0x0
    volatile uint32_t IWDT_CTRL; //0x4
    volatile uint32_t IWDT_CNT; //0x8
    volatile uint32_t IWDT_INTR; //0xc
}reg_iwdg_t;

enum IWDT_REG_IWDT_LOAD_FIELD
{
    IWDT_LOAD_MASK = (int)0xffffffff,
    IWDT_LOAD_POS = 0,
};

enum IWDT_REG_IWDT_CTRL_FIELD
{
    IWDT_EN_MASK = (int)0x1,
    IWDT_EN_POS = 0,
    IWDT_RST_EN_MASK = (int)0x2,
    IWDT_RST_EN_POS = 1,
    IWDT_INTR_CLR_MASK = (int)0x4,
    IWDT_INTR_CLR_POS = 2,
    IWDT_CNT_CLR_MASK = (int)0x8,
    IWDT_CNT_CLR_POS = 3,
};

enum IWDT_REG_IWDT_CNT_FIELD
{
    IWDT_CNT_MASK = (int)0xffffffff,
    IWDT_CNT_POS = 0,
};

enum IWDT_REG_IWDT_INTR_FIELD
{
    IWDT_INTR_MASK = (int)0x1,
    IWDT_INTR_POS = 0,
};

#endif
