#ifndef REG_SHA_TYPE_H_
#define REG_SHA_TYPE_H_
#include <stdint.h>

typedef struct
{
    volatile uint32_t SHA_START; //0x0
    volatile uint32_t SHA_CTRL; //0x4
    volatile uint32_t RESERVED0[6];
    volatile uint32_t INTR_M; //0x20
    volatile uint32_t INTR_C; //0x24
    volatile uint32_t INTR_S; //0x28
    volatile uint32_t INTR_R; //0x2c
    volatile uint32_t FIFO_DAT; //0x30
    volatile uint32_t FIFO_STAT; //0x34
    volatile uint32_t FSM_STAT; //0x38
    volatile uint32_t RESERVED1[1];
    volatile uint32_t SHA_RSLT[8]; //0x40
}reg_sha_t;

enum SHA_REG_SHA_START_FIELD
{
    SHA_FSM_START_MASK = (int)0x1,
    SHA_FSM_START_POS = 0,
};

enum SHA_REG_SHA_CTRL_FIELD
{
    SHA_FST_DAT_MASK = (int)0x1,
    SHA_FST_DAT_POS = 0,
    SHA_CALC_SHA224_MASK = (int)0x10,
    SHA_CALC_SHA224_POS = 4,
    SHA_CALC_SM3_MASK = (int)0x20,
    SHA_CALC_SM3_POS = 5,
    SHA_SHA_LEN_MASK = (int)0x3fff00,
    SHA_SHA_LEN_POS = 8,
};

enum SHA_REG_INTR_FIELD
{
    SHA_FSM_END_INTR_MASK = (int)0x1,
    SHA_FSM_END_INTR_POS = 0,
    SHA_FSM_EMPT_INTR_MASK = (int)0x2,
    SHA_FSM_EMPT_INTR_POS = 1,
};


enum SHA_REG_FIFO_STAT_FIELD
{
    SHA_FIFO_FLVL_MASK = (int)0xf,
    SHA_FIFO_FLVL_POS = 0,
};

enum SHA_REG_FSM_STAT_FIELD
{
    SHA_FSM_IDLE_MASK = (int)0x1,
    SHA_FSM_IDLE_POS = 0,
};

#endif

