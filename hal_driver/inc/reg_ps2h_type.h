#ifndef REG_PS2H_TYPE_H_
#define REG_PS2H_TYPE_H_
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    volatile uint32_t INTR_MSK;
    volatile uint32_t INTR_CLR;
    volatile uint32_t INTR_STT;
    volatile uint32_t INTR_RAW;
    volatile uint32_t PS2H_CTRL0;
    volatile uint32_t PS2H_CTRL1;
    volatile uint32_t ERR_CLR;
    volatile uint32_t TX_REQ;
    volatile uint32_t TX_DAT;
    volatile uint32_t RX_DAT;
    volatile uint32_t RX_FLVL;
} reg_ps2h_t;

enum PS2H_REG_INTR_FIELD
{
    PS2H_INTR_ALL_MASK = (int)0xFF,
    PS2H_INTR_ALL_POS = 0,
    PS2H_INTR_RXERROR_MASK = (int)0x7,
    PS2H_INTR_RXERROR_POS = 0,
    PS2H_INTR_ERR_START_MASK = (int)0x1,
    PS2H_INTR_ERR_START_POS = 0,
    PS2H_INTR_ERR_PAR_MASK = (int)0x2,
    PS2H_INTR_ERR_PAR_POS = 1,
    PS2H_INTR_ERR_STOP_MASK = (int)0x4,
    PS2H_INTR_ERR_STOP_POS = 2,
    PS2H_INTR_ERR_ACK_MASK = (int)0x8,
    PS2H_INTR_ERR_ACK_POS = 3,
    PS2H_INTR_RX_END_MASK = (int)0x10,
    PS2H_INTR_RX_END_POS = 4,
    PS2H_INTR_TX_END_MASK = (int)0x20,
    PS2H_INTR_TX_END_POS = 5,
    PS2H_INTR_RX_FIFO_OVER_MASK = (int)0x40,
    PS2H_INTR_RX_FIFO_OVER_POS = 6,
    PS2H_INTR_RX_FIFO_MASK = (int)0x80,
    PS2H_INTR_RX_FIFO_POS = 7,
};

enum PS2H_REG_CTRL0_FIELD
{
    PS2H_CTRL0_FIL_NUM_MASK = (int)0x3F,
    PS2H_CTRL0_FIL_NUM_POS = 0,
    PS2H_CTRL0_CYC_1US_MASK = (int)0xFF00,
    PS2H_CTRL0_CYC_1US_POS = 8,
    PS2H_CTRL0_DRV_DLY_MASK = (int)0x1F0000,
    PS2H_CTRL0_DRV_DLY_POS = 16,
    PS2H_CTRL0_CAP_DLY_MASK = (int)0x1F000000,
    PS2H_CTRL0_CAP_DLY_POS = 24,
};

enum PS2H_REG_CTRL1_FIELD0xFF
{
    PS2H_CTRL1_ERR_MODE_MASK = (int)0x7,
    PS2H_CTRL1_ERR_MODE_POS = 0,
    PS2H_CTRL1_TX_MODE_MASK = (int)0x30,
    PS2H_CTRL1_TX_MODE_POS = 4,
    PS2H_CTRL1_RX_THR_MASK = (int)0xF00,
    PS2H_CTRL1_RX_THR_POS = 8,
};

enum PS2H_REG_ERR_CLR
{
    PS2H_ERR_CLR_MASK = 0x1,
    PS2H_ERR_CLR_POS = 0,
};

enum PS2H_REG_TX_REQ
{
    PS2H_TX_REQ_MASK = 0x1,
    PS2H_TX_REQ_POS = 0,
};

enum PS2H_REG_TX_DAT
{
    PS2H_TX_DAT_MASK = 0xFF,
    PS2H_TX_DAT_POS = 0,
};

enum PS2H_REG_RX_DAT
{
    PS2H_RX_DAT_MASK = 0xFF,
    PS2H_RX_DAT_POS = 0,
};

enum PS2H_REG_RX_FLVL
{
    PS2H_RX_FLVL_MASK = 0xF,
    PS2H_RX_FLVL_POS = 0,
};

#ifdef __cplusplus
}
#endif

#endif