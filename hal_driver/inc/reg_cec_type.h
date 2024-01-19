#ifndef REG_CEC_TYPE_H_
#define REG_CEC_TYPE_H_
#include <stdint.h>

typedef struct
{
    volatile uint32_t CEC_CTRL;     //0x00
    volatile uint32_t INTR_MSK;     //0x04
    volatile uint32_t INTR_STT;     //0x08
    volatile uint32_t CEC_LOG_ADDR; //0x0C
    volatile uint32_t TX_BUF_CNT;   //0x10
    volatile uint32_t RX_BUF_CNT;   //0x14
    volatile uint32_t RESERVED0[2]; //0x18 0x1c
    volatile uint32_t TX_DATA[16];  //0x20 0x24 0x28 0x2c 0x30 0x34 0x38 0x3c 0x40 0x44 0x48 0x4c 0x50 0x54 0x58 0x5c
    volatile uint32_t RX_DATA[16];  //0x60 0x64 0x68 0x6c 0x70 0x74 0x78 0x7c 0x80 0x84 0x88 0x8c 0x90 0x94 0x98 0x9c
    volatile uint32_t BUF_LOCK;     //0xA0
    volatile uint32_t WAKE_CTRL_STT;//0xA4
}reg_cec_t;

enum CEC_CTRL_FIELD
{
    CEC_SEND_MASK = (int)0x1,
    CEC_SEND_POS = 0,
    CEC_FRAME_TYPE_MASK = (int)0x6,
    CEC_FRAME_TYPE_POS = 1,
    BC_NACK_MASK = (int)0x8,
    BC_NACK_POS = 3,
    CEC_STANDY_MASK = (int)0x10,
    CEC_STANDY_POS = 4,
    CEC_EN_MASK = (int)0x20,
    CEC_EN_POS = 5,
    CEC_CLK_RATE_MASK = (int)0xfff0000,
    CEC_CLK_RATE_POS = 16,
};

enum CEC_REG_INTR_FIELD
{
    TX_DONE_MASK = (int)0x1,
    TX_DONE_POS = 0,
    RX_FINISH_MASK = (int)0x2,
    RX_FINISH_POS = 1,
    NACK_MASK = (int)0x4,
    NACK_POS = 2,
    ARB_LOST_MASK = (int)0x8,
    ARB_LOST_POS = 3,
    TX_ERR_MASK = (int)0x10,
    TX_ERR_POS = 4,
    LBIT_ERR_MASK = (int)0x20,
    LBIT_ERR_POS = 5,
    WAKE_INT_MASK = (int)0x40,
    WAKE_INT_POS = 6,
    TX_DONE_CLR_MASK = (int)0x10000,
    TX_DONE_CLR_POS = 16,
    RX_FINISH_CLR_MASK = (int)0x20000,
    RX_FINISH_CLR_POS = 17,
    NACK_CLR_MASK = (int)0x40000,
    NACK_CLR_POS = 18,
    ARB_LOST_CLR_MASK = (int)0x80000,
    ARB_LOST_CLR_POS = 19,
    TX_ERR_CLR_MASK = (int)0x100000,
    TX_ERR_CLR_POS = 20,
    LBIT_ERR_CLR_MASK = (int)0x200000,
    LBIT_ERR_CLR_POS = 21,
    WAKE_INT_CLR_MASK = (int)0x400000,
    WAKE_INT_CLR_POS = 22,
};

enum CEC_REG_INTR_STT_FIELD
{
    TX_DONE_RAW_MASK = (int)0x1,
    TX_DONE_RAW_POS = 0,
    RX_FINISH_RAW_MASK = (int)0x2,
    RX_FINISH_RAW_POS = 1,
    NACK_RAW_MASK = (int)0x4,
    NACK_RAW_POS = 2,
    ARB_LOST_RAW_MASK = (int)0x8,
    ARB_LOST_RAW_POS = 3,
    TX_ERR_RAW_MASK = (int)0x10,
    TX_ERR_RAW_POS = 4,
    LBIT_ERR_RAW_MASK = (int)0x20,
    LBIT_ERR_RAW_POS = 5,
    WAKE_INT_RAW_MASK = (int)0x40,
    WAKE_INT_RAW_POS = 6,
    TX_DONE_STT_MASK = (int)0x10000,
    TX_DONE_STT_POS = 16,
    RX_FINISH_STT_MASK = (int)0x20000,
    RX_FINISH_STT_POS = 17,
    NACK_STT_MASK = (int)0x40000,
    NACK_STT_POS = 18,
    ARB_LOST_STT_MASK = (int)0x80000,
    ARB_LOST_STT_POS = 19,
    TX_ERR_STT_MASK = (int)0x100000,
    TX_ERR_STT_POS = 20,
    LBIT_ERR_STT_MASK = (int)0x200000,
    LBIT_ERR_STT_POS = 21,
    WAKE_INT_STT_MASK = (int)0x400000,
    WAKE_INT_STT_POS = 22,
};

	
#endif /* REG_CEC_TYPE_H_ */

