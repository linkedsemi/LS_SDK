#ifndef REG_WWDG_TYPE_H_
#define REG_WWDG_TYPE_H_
#include <stdint.h>

typedef struct
{
    volatile uint32_t WWDG_LOAD; //0x0
    volatile uint32_t WWDG_CNT; //0x4
    volatile uint32_t WWDG_CON; //0x8
    volatile uint32_t WWDG_INTCLR; //0xc
    volatile uint32_t WWDG_RIS; //0x10
    volatile uint32_t RESERVED0[59];
    volatile uint32_t WWDG_LOCK; //0x100
}reg_wwdg_t;

enum REG_WWDG_LOAD_FIELD
{
    REG_WWDG_LOAD_MASK = (int)0xffffffff,
    REG_WWDG_LOAD_POS = 0,
};

enum REG_WWDG_CNT_FIELD
{
    REG_WWDG_CNT_MASK = (int)0xffffffff,
    REG_WWDG_CNT_POS = 0,
};

enum REG_WWDG_CON_FIELD
{
    REG_WWDG_EN_MASK = (int)0x1,
    REG_WWDG_EN_POS = 0,
    REG_WWDG_IE_MASK = (int)0x2,
    REG_WWDG_IE_POS = 1,
    REG_WWDG_RSTEN_MASK = (int)0x4,
    REG_WWDG_RSTEN_POS = 2,
    REG_WWDG_CLKS_MASK = (int)0x8,
    REG_WWDG_CLKS_POS = 3,
    REG_WWDG_WIN_MASK = (int)0x30,
    REG_WWDG_WIN_POS = 4,
};

enum REG_WWDG_INTCLR_FIELD
{
    REG_WWDG_ICR_MASK = (int)0x1,
    REG_WWDG_ICR_POS = 0,
};

enum REG_WWDG_RIS_FIELD
{
    REG_WWDG_RIF_MASK = (int)0x1,
    REG_WWDG_RIF_POS = 0,
};


#endif