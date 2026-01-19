#ifndef REG_OTBN_TYPE_H_
#define REG_OTBN_TYPE_H_
#include <stdint.h>

#define OTBN_IMEM_SIZE (0x2000)
#define OTBN_DMEM_SIZE (0xC00)

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

enum OTBN_REG_STATUS_FIELD
{
    OTBN_STATUS_BUSY_EXECUTE_MASK = (int)0X2,
    OTBN_STATUS_BUSY_EXECUTE_POS = 1,
    OTBN_STATUS_IDLE_MASK = (int)0X1,
    OTBN_STATUS_IDLE_POS = 0,
    OTBN_STATUS_LOCK_MASK = (int)0xff,
    OTBN_STATUS_LOCK_POS = 0,
};


#endif