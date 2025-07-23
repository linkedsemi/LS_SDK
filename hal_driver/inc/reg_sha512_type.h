#ifndef REG_SHA512_TYPE_H_
#define REG_SHA512_TYPE_H_
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    volatile uint32_t INTR_MSK; //0
    volatile uint32_t INTR_CLR; //4
    volatile uint32_t INTR_RAW; //8
    volatile uint32_t INTR_STT; //c
    volatile uint32_t CTRL; //10
    volatile uint32_t FACTOR_NUM; //14
    volatile uint32_t ADDR; //18
    volatile uint32_t STATUS; //1c
    volatile uint32_t RESERVED[40]; //0x20
    volatile uint32_t DIGEST[16];
} reg_sha512_t;

enum SHA512_REG_INTR_FIELD
{
    SHA512_INTR_DMA_END_MASK = (int)0x1,
    SHA512_INTR_DMA_END_POS = 0,
    SHA512_INTR_CALC_END_MASK = (int)0x2,
    SHA512_INTR_CALC_END_POS = 1,
};

enum SHA512_REG_CTRL_FIELD
{
    SHA512_CTRL_INIT_CALC_MASK = (int)0x1,
    SHA512_CTRL_INIT_CALC_POS = 0,
    SHA512_CTRL_START_MASK = (int)0x2,
    SHA512_CTRL_START_POS = 1,
    SHA512_CTRL_MODE_MASK = (int)0xc,
    SHA512_CTRL_MODE_POS = 2,
    SHA512_CTRL_FACTOR_MASK = (int)0x80,
    SHA512_CTRL_FACTOR_POS = 7,
    SHA512_CTRL_BLOCK_NUM_MASK = (int)0xffff0000,
    SHA512_CTRL_BLOCK_NUM_POS = 16,
};

enum SHA512_REG_FACTOR_NUM_FIELD
{
    SHA512_FACTOR_NUM_MASK = (int)0xffffffff,
    SHA512_FACTOR_NUM_POS = 0,
};

enum SHA512_REG_ADDR_FIELD
{
    SHA512_ADDR_MASK = (int)0xffffffff,
    SHA512_ADDR_POS = 0,
};



#ifdef __cplusplus
}
#endif
#endif