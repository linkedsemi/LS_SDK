#ifndef REG_TOUCHKEY_TYPE_H_
#define REG_TOUCHKEY_TYPE_H_
#include <stdint.h>

typedef struct
{
    volatile uint32_t TOUCHKEY_START;//0x000
    volatile uint32_t TOUCHKEY_CLK_CFG;
    volatile uint32_t TOUCHKEY_SCAN_MTIM;
    volatile uint32_t TOUCHKEY_SCAN_CFG;
    volatile uint32_t TOUCHKEY_ANA_CFG;//0x010
    volatile uint32_t RESERVED0;
    volatile uint32_t RESERVED1;
    volatile uint32_t RESERVED2;
    volatile uint32_t INTR_MSK;//0x020
    volatile uint32_t INTR_CLR;
    volatile uint32_t INTR_STT;
    volatile uint32_t INTR_RAW;
    volatile uint32_t CH0_CNT;//0x030
    volatile uint32_t CH1_CNT;
    volatile uint32_t CH2_CNT;
    volatile uint32_t CH3_CNT;
    volatile uint32_t CH4_CNT;//0x040
    volatile uint32_t CH5_CNT;
    volatile uint32_t CH6_CNT;
    volatile uint32_t CH7_CNT;
    volatile uint32_t CH8_CNT;//0x050
    volatile uint32_t CH9_CNT;
    volatile uint32_t CHA_CNT;
    volatile uint32_t CHB_CNT;
    volatile uint32_t CHC_CNT;//0x060
    volatile uint32_t CHD_CNT;
    volatile uint32_t CHE_CNT;
    volatile uint32_t CHF_CNT;
}reg_touchkey_t;

enum TOUCHKEY_REG_START_FIELD
{
    TOUCHKEY_START_MASK = 0x1,
    TOUCHKEY_START_POS = 0,
};

enum TOUCHKEY_REG_CLK_CFG_FIELD
{
    TOUCHKEY_LPRD_MASK = 0x3ff,
    TOUCHKEY_LPRD_POS = 0,
    TOUCHKEY_HPRD_MASK = 0x3ff0000,
    TOUCHKEY_HPRD_POS = 16,
};

enum TOUCHKEY_REG_SCAN_MTIM_FIELD
{
    TOUCHKEY_SCAN_MTIM_MASK = (int)0xffffffff,
    TOUCHKEY_SCAN_MTIM_POS = 0,
};

enum TOUCHKEY_REG_SCAN_CFG_FIELD
{
    TOUCHKEY_DISCH_PRD_MASK = 0x7,
    TOUCHKEY_DISCH_PRD_POS = 0,
    TOUCHKEY_SCAN_ITER_MASK = 0xf0,
    TOUCHKEY_SCAN_ITER_POS = 4,
    TOUCHKEY_FLT_PRD_MASK = 0x300,
    TOUCHKEY_FLT_PRD_POS = 8,
    TOUCHKEY_CH_EN_MASK = 0xffff000,
    TOUCHKEY_CH_EN_POS = 12,
};

enum TOUCHKEY_REG_ANA_CFG_FIELD
{
    TOUCHKEY_ANA_EN_MASK = 0x1,
    TOUCHKEY_ANA_EN_POS = 0,
    TOUCHKEY_CP_VCTL_MASK = 0x30,
    TOUCHKEY_CP_VCTL_POS = 4,
};

enum TOUCHKEY_REG_INTR_FIELD
{
    TOUCHKEY_INTR_END_MASK = 0x1,
    TOUCHKEY_INTR_END_POS = 0,
    TOUCHKEY_INTR_ERR_MASK = 0x2,
    TOUCHKEY_INTR_ERR_POS = 1,
};

#endif