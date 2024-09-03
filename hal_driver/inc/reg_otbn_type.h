#ifndef REG_OTBN_TYPE_H_
#define REG_OTBN_TYPE_H_
#include <stdint.h>

typedef struct
{
    volatile uint32_t INTR_STATE;
    volatile uint32_t INTR_ENABLE;
    volatile uint32_t INTR_TEST;
    volatile uint32_t ALERT_TEST;
    volatile uint32_t CMD;
    volatile uint32_t CTRL;
    volatile uint32_t STATUS;
    volatile uint32_t ERR_BITS;
    volatile uint32_t FATAL_ALERT_CAUSE;
    volatile uint32_t TNSN_CNT;
    volatile uint32_t LOAD_CHECKSUM;
    volatile uint32_t reserved_0[0xff5];
    volatile uint32_t IMEM[0x800];
    volatile uint32_t reserved_1[0x800];
    volatile uint32_t DMEM[0x300];
} reg_otbn_t;

enum OTBN_REG_INTR_STATE_FIELD
{
    OTBN_INTR_STATE_DONE_MASK = (int)0x1,
    OTBN_INTR_STATE_DONE_POS = 0,
};

enum OTBN_REG_INTR_ENABLE_FIELD
{
    OTBN_INTR_ENABLE_EN_MASK = (int)0x1,
    OTBN_INTR_ENABLE_EN_POS = 0,
};

enum OTBN_REG_INTR_TEST_FIELD
{
    OTBN_INTR_TEST_DONE_MASK = (int)0x1,
    OTBN_INTR_TEST_DONE_POS = 0,
};

enum OTBN_REG_CMD_FIELD
{
    OTBN_CMD_CMD_MASK = (int)0xff,
    OTBN_CMD_CMD_POS = 0,
};



#endif