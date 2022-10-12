#ifndef REG_SM4_TYPE_H_
#define REG_SM4_TYPE_H_
#include <stdint.h>

typedef struct
{
    volatile uint32_t SM4_START;
    volatile uint32_t SM4_CTRL;
    volatile uint32_t SM4_KEY_IDX;
    volatile uint32_t RESERVED0;
    volatile uint32_t SM4_KEY0;
    volatile uint32_t SM4_KEY1;
    volatile uint32_t SM4_KEY2;
    volatile uint32_t SM4_KEY3;
    volatile uint32_t INTR_MSK;
    volatile uint32_t INTR_CLR;
    volatile uint32_t INTR_STT;
    volatile uint32_t INTR_RAW;
    volatile uint32_t CALC_WRD;
    volatile uint32_t RESERVED1;
    volatile uint32_t RESERVED2;
    volatile uint32_t CUR_KEY;
    volatile uint32_t CALC_RSLT0;
    volatile uint32_t CALC_RSLT1;
    volatile uint32_t CALC_RSLT2;
    volatile uint32_t CALC_RSLT3;
}reg_sm4_t;

enum SM4_REG_SM4_START_FIELD
{
    SM4_CALC_START_MASK = 0x1,
    SM4_CALC_START_POS = 0,
    SM4_KEY_START_MASK = 0x2,
    SM4_KEY_START_POS = 1,
};
enum SM4_REG_SM4_CTRL_FIELD
{
    SM4_CALC_DEC_MASK = 0x1,
    SM4_CALC_DEC_POS = 0,
    SM4_CALC_LEN_MASK = 0x100,
    SM4_CALC_LEN_POS = 8,
};
enum SM4_REG_SM4_KEY_IDX_FIELD
{
    SM4_KEY_IDX_MASK = 0x1,
    SM4_KEY_IDX_POS = 0,
};
enum SM4_REG_SM4_KEY0_FIELD
{
    SM4_KEY0_MASK = (int)0xffffffff,
    SM4_KEY0_POS = 0,
};
enum SM4_REG_SM4_KEY1_FIELD
{
    SM4_KEY1_MASK = (int)0xffffffff,
    SM4_KEY1_POS = 0,
};
enum SM4_REG_SM4_KEY2_FIELD
{
    SM4_KEY2_MASK = (int)0xffffffff,
    SM4_KEY2_POS = 0,
};
enum SM4_REG_SM4_KEY3_FIELD
{
    SM4_KEY3_MASK = (int)0xffffffff,
    SM4_KEY3_POS = 0,
};
enum SM4_REG_INTR_MSK_FIELD
{
    SM4_INTR_END_MASK = 0x1,
    SM4_INTR_END_POS = 0,
    SM4_INTR_DATA_MASK = 0x2,
    SM4_INTR_DATA_POS = 1,
    SM4_KEY_END_MASK = 0x4,
    SM4_KEY_END_POS = 2,
};
enum SM4_REG_CALC_WRD_FIELD
{
    SM4_CALC_WRD_MASK = (int)0xffffffff,
    SM4_CALC_WRD_POS = 0,
};
enum SM4_REG_CUR_KEY_FIELD
{
    SM4_CUR_KEY_MASK = (int)0xffffffff,
    SM4_CUR_KEY_POS = 0,
};
enum SM4_REG_CALC_RSLT0_FIELD
{
    SM4_CALC_RSLT0_MASK = (int)0xffffffff,
    SM4_CALC_RSLT0_POS = 0,
};
enum SM4_REG_CALC_RSLT1_FIELD
{
    SM4_CALC_RSLT1_MASK = (int)0xffffffff,
    SM4_CALC_RSLT1_POS = 0,
};
enum SM4_REG_CALC_RSLT2_FIELD
{
    SM4_CALC_RSLT2_MASK = (int)0xffffffff,
    SM4_CALC_RSLT2_POS = 0,
};
enum SM4_REG_CALC_RSLT3_FIELD
{
    SM4_CALC_RSLT3_MASK = (int)0xffffffff,
    SM4_CALC_RSLT3_POS = 0,
};

#endif