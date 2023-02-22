#ifndef REG_LSIWDG_TYPE_H_
#define REG_LSIWDG_TYPE_H_
#include <stdint.h>

typedef struct
{
    volatile uint32_t IWDG_LOAD;
    volatile uint32_t IWDG_VALUE;
    volatile uint32_t IWDG_CON;
    volatile uint32_t IWDG_INTCLR;
    volatile uint32_t IWDG_RIS;
    volatile uint32_t IWDG_LOCK;
} reg_iwdg_t;

enum IWDG_REG_IWDG_LOAD_FIELD
{
    IWDG_LOAD_MASK = (int)0xffffffff,
    IWDG_LOAD_POS = 0,
};

enum IWDG_REG_IWDG_VALUE_FIELD
{
    IWDG_VALUE_MASK = (int)0xffffffff,
    IWDG_VALUE_POS = 0,
};

enum IWDG_REG_IWDG_CON_FIELD
{
    IWDG_EN_MASK = 0x1,
    IWDG_EN_POS = 0,
    IWDG_IE_MASK = 0x2,
    IWDG_IE_POS = 1,
    IWDG_RSTEN_MASK = 0x4,
    IWDG_RSTEN_POS = 2,
    IWDG_CLKS_MASK = 0x30,
    IWDG_CLKS_POS = 4,
};

enum IWDG_REG_IWDG_INTCLR_FIELD
{
    IWDG_INTCLR_MASK = (int)0xffffffff,
    IWDG_INTCLR_POS = 0,
};

enum IWDG_REG_IWDG_RIS_FIELD
{
    IWDG_WDTIF_MASK = 0x1,
    IWDG_WDTIF_POS = 0,
};

enum IWDG_REG_IWDG_LOCK_FIELD
{
    IWDG_LOCK_MASK = (int)0xffffffff,
    IWDG_LOCK_POS = 0,
};

#endif
