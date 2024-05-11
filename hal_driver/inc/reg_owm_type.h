#ifndef REG_OWM_TYPE_H_
#define REG_OWM_TYPE_H_
#include <stdint.h>

typedef struct 
{
    volatile uint32_t INTR_MSK;                 //0x00
    volatile uint32_t INTR_CLR;                 //0x04
    volatile uint32_t INTR_STT;                 //0x08
    volatile uint32_t INTR_RAW;                 //0x01
    volatile uint32_t OWM_CTRL0;                 //0x10
    volatile uint32_t OWM_CTRL1;                 //0x14
    volatile uint32_t OWM_TGL;                 //0x18
    volatile uint32_t TX_DAT;                 //0x1C
    volatile uint32_t TXRX_REQ;                 //0x20
    volatile uint32_t RX_DAT;                 //0x24
}reg_owm_t;  

enum OWM_REG_INTR_MSK_FIELD
{
    OWM_INTR_MSK_MASK = (int)0x1,
    OWM_INTR_MSK_POS = 0
};

enum OWM_REG_INTR_CLR_FIELD
{
    OWM_INTR_CLR_MASK = (int)0x1,
    OWM_INTR_CLR_POS = 0
};

enum OWM_REG_INTR_STT_FIELD
{
    OWM_INTR_FSM_END_MASK = (int)0x1,
    OWM_INTR_FSM_END_POS = 0
};

enum OWM_REG_INTR_RAW_FIELD
{
    OWM_INTR_RAW_MASK = (int)0x7ffffff,
    OWM_INTR_RAW_POS = 0
};

enum OWM_REG_OWM_CTRL0_FIELD
{
    OWM_DAT_LEN_MASK = (int)0x1f000,
    OWM_DAT_LEN_POS = 12,
    OWM_FLT_NUM_MASK = (int)0xf00,
    OWM_FLT_NUM_POS = 8,
    OWM_PRE_DIV_MASK = (int)0xff,
    OWM_PRE_DIV_POS = 0
};

enum OWM_REG_OWM_CTRL1_FIELD
{
    OWM_SMP_IDX_MASK = (int)0x3ff0000,
    OWM_SMP_IDX_POS = 16,
    OWM_BIT_CYC_MASK = (int)0x3ff,
    OWM_BIT_CYC_POS = 0
};

enum OWM_REG_OWM_TGL_FIELD
{
    OWM_TGL1_IDX_MASK = (int)0x3ff0000,
    OWM_TGL1_IDX_POS = 16,
    OWM_TGL0_IDX_MASK = (int)0x3ff,
    OWM_TGL0_IDX_POS = 0
};

enum OWM_REG_TX_DAT_FIELD
{
    OWM_TX_DAT_MASK = (int)0xffffffff,
    OWM_TX_DAT_POS = 0
};

enum OWM_REG_TXRX_REQ_FIELD
{
    OWM_TXRX_REQ_MASK = (int)0x1,
    OWM_TXRX_REQ_POS = 0
};

enum OWM_REG_RX_DAT_FIELD
{
    OWM_RX_DAT_MASK = (int)0xffffffff,
    OWM_RX_DAT_POS = 0
};

#endif