#ifndef REG_PECI_TYPE_H_
#define REG_PECI_TYPE_H_
#include <stdint.h>

typedef struct
{
    volatile uint32_t INTR_MSK;
    volatile uint32_t INTR_CLR;
    volatile uint32_t INTR_STT;
    volatile uint32_t INTR_RAW;
    volatile uint32_t PECI_CTRL;
    volatile uint32_t TXRX_REQ;
    volatile uint32_t PECI_CTRL2;
    volatile uint32_t RESERVED0;
    volatile uint32_t PECI_A_TIM0;
    volatile uint32_t PECI_A_TIM1;
    volatile uint32_t PECI_M_TIM0;
    volatile uint32_t PECI_M_TIM1;
    volatile uint32_t TX_DAT0;
    volatile uint32_t TX_DAT1;
    volatile uint32_t TX_DAT2;
    volatile uint32_t TX_DAT3;
    volatile uint32_t TX_DAT4;
    volatile uint32_t TX_DAT5;
    volatile uint32_t TX_DAT6;
    volatile uint32_t TX_DAT7;
    volatile uint32_t RX_DAT0;
    volatile uint32_t RX_DAT1;
    volatile uint32_t RX_DAT2;
    volatile uint32_t RX_DAT3;
    volatile uint32_t RX_DAT4;
    volatile uint32_t RX_DAT5;
    volatile uint32_t RX_DAT6;
    volatile uint32_t RX_DAT7;
    volatile uint32_t TX_H_DAT0;
    volatile uint32_t TX_H_DAT1;
    volatile uint32_t TX_H_DAT2;
    volatile uint32_t TX_H_DAT3;
    volatile uint32_t TX_H_DAT4;
    volatile uint32_t TX_H_DAT5;
    volatile uint32_t TX_H_DAT6;
    volatile uint32_t TX_H_DAT7;
    volatile uint32_t RX_H_DAT0;
    volatile uint32_t RX_H_DAT1;
    volatile uint32_t RX_H_DAT2;
    volatile uint32_t RX_H_DAT3;
    volatile uint32_t RX_H_DAT4;
    volatile uint32_t RX_H_DAT5;
    volatile uint32_t RX_H_DAT6;
    volatile uint32_t RX_H_DAT7;
} reg_peci_t;

enum PECI_REG_INTR_MSK_FIELD
{
    PECI_INTR_MSK_MASK = (int)0x1,
    PECI_INTR_MSK_POS = 0,
};

enum PECI_REG_INTR_CLR_FIELD
{
    PECI_INTR_CLR_MASK = (int)0x1,
    PECI_INTR_CLR_POS = 0,
};

enum PECI_REG_PECI_CTRL_FIELD
{
    PECI_PRE_DIV_MASK = (int)0xff,
    PECI_PRE_DIV_POS = 0,
    PECI_FLT_NUM_MASK = (int)0xf00,
    PECI_FLT_NUM_POS = 8,
    PECI_DAT_LEN_MASK = (int)0x3ff000,
    PECI_DAT_LEN_POS = 12,
    PECI_DAT_WLEN_MASK = (int)0x7fc00000,
    PECI_DAT_WLEN_POS = 22,
    PECI_WT_MODE_MASK = (int)0x1,
    PECI_WT_MODE_POS = 31,
};

enum PECI_REG_TXRX_REQ_FIELD
{
    PECI_TXRX_REQ_MASK = (int)0x1,
    PECI_TXRX_REQ_POS = 0,
};

enum PECI_REG_PECI_CTRL2_FIELD
{
    PECI_BIT_REVERSE_MASK = (int)0x1,
    PECI_BIT_REVERSE_POS = 0,
};

enum PECI_REG_PECI_A_TIM0_FIELD
{
    PECI_A_BIT_CYC_MASK = (int)0x3ff,
    PECI_A_BIT_CYC_POS = 0,
    PECI_A_SMP_IDX_MASK = (int)0x3ff0000,
    PECI_A_SMP_IDX_POS = 16,
};

enum PECI_REG_PECI_A_TIM1_FIELD
{
    PECI_A_TGT_IDX0_MASK = (int)0x3ff,
    PECI_A_TGT_IDX0_POS = 0,
    PECI_A_TGT_IDX1_MASK = (int)0x3ff0000,
    PECI_A_TGT_IDX1_POS = 16,
};

enum PECI_REG_PECI_M_TIM0_FIELD
{
    PECI_M_BIT_CYC_MASK = (int)0x3ff,
    PECI_M_BIT_CYC_POS = 0,
    PECI_M_SMP_IDX_MASK = (int)0x3ff0000,
    PECI_M_SMP_IDX_POS = 16,
};

enum PECI_REG_PECI_M_TIM1_FIELD
{
    PECI_M_TGT_IDX0_MASK = (int)0x3ff,
    PECI_M_TGT_IDX0_POS = 0,
    PECI_M_TGT_IDX1_MASK = (int)0x3ff0000,
    PECI_M_TGT_IDX1_POS = 16,
};

#endif