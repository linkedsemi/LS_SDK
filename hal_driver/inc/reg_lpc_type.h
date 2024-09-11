#ifndef REG_LPC_TYPE_H_
#define REG_LPC_TYPE_H_
#include <stdint.h>

typedef struct
{
    volatile uint32_t LPC_CTRL0;   // 0x0
    volatile uint32_t LPC_CTRL1;   // 0x4
    volatile uint32_t LPC_CTRL2;   // 0x8
    volatile uint32_t LPC_CTRL3;   // 0xc
    volatile uint32_t INTR_MSK;    // 0x10
    volatile uint32_t INTR_CLR;    // 0x14
    volatile uint32_t INTR_STT;    // 0x18
    volatile uint32_t INTR_RAW;    // 0x1c
    volatile uint32_t INTR_SEND;   // 0x20
    volatile uint32_t SERIRQ_MODE; // 0x24
    volatile uint32_t LPC_ADDR;    // 0x28
    volatile uint32_t LPC_RX;      // 0x2c
    volatile uint32_t LPC_FSM;     // 0x30
} reg_lpc_t;

enum LPC_REG_LPC_CTRL0_FIELD
{
    LPC_LPC_ICAP_MODE_MASK = (int)0x1,
    LPC_LPC_ICAP_MODE_POS = 0,
    LPC_LPC_SYNC_TO_MASK = (int)0xffff0,
    LPC_LPC_SYNC_TO_POS = 4,
    LPC_SERIRQ_STOP_TO_MASK = (int)0xff00000,
    LPC_SERIRQ_STOP_TO_POS = 20,
};

enum LPC_REG_LPC_CTRL1_FIELD
{
    LPC_LPC_DATA_UP_MASK = (int)0xff,
    LPC_LPC_DATA_UP_POS = 0,
    LPC_LPC_SYNC_MASK = (int)0xf00,
    LPC_LPC_SYNC_POS = 8,
};

enum LPC_REG_LPC_CTRL2_FIELD
{
    LPC_SERIRQ_SRC_MASK = (int)0xffff,
    LPC_SERIRQ_SRC_POS = 0,
};

enum LPC_REG_LPC_CTRL3_FIELD
{
    LPC_LPC_SYNC_VLD_T_MASK = (int)0x1,
    LPC_LPC_SYNC_VLD_T_POS = 0,
    LPC_SERIRQ_SEND_T_MASK = (int)0x2,
    LPC_SERIRQ_SEND_T_POS = 1,
    LPC_INTR_SEND_CLR_T_MASK = (int)0x4,
    LPC_INTR_SEND_CLR_T_POS = 2,
};

enum LPC_REG_LPC_INTR_STT_FIELD
{
    LPC_INTR_STT_CMD_VLD_MASK = (int)0x1,
    LPC_INTR_STT_CMD_VLD_POS = 0,
    LPC_INTR_STT_SYNC_TO_MASK = (int)0x2,
    LPC_INTR_STT_SYNC_TO_POS = 1,
    LPC_INTR_STT_SERIRQ_STOP_MASK = (int)0x4,
    LPC_INTR_STT_SERIRQ_STOP_POS = 2,
    LPC_INTR_STT_SERIRQ_STOP_TO_MASK = (int)0x8,
    LPC_INTR_STT_SERIRQ_STOP_TO_POS = 3,
    LPC_INTR_STT_SERIRQ_STOP_IVLD_MASK = (int)0x10,
    LPC_INTR_STT_SERIRQ_STOP_IVLD_POS = 4,
};

enum LPC_REG_LPC_RX_FIELD
{
    LPC_LPC_START_MASK = (int)0xf,
    LPC_LPC_START_POS = 0,
    LPC_LPC_IDCYC_MASK = (int)0xf0,
    LPC_LPC_IDCYC_POS = 4,
    LPC_LPC_DATA_DN_MASK = (int)0xff00,
    LPC_LPC_DATA_DN_POS = 8,
};

enum LPC_REG_LPC_FSM_FIELD
{
    LPC_LPC_TXRX_FSM_MASK = (int)0xf,
    LPC_LPC_TXRX_FSM_POS = 0,
    LPC_LPC_SERIRQ_FSM_MASK = (int)0x70,
    LPC_LPC_SERIRQ_FSM_POS = 4,
};

#endif
