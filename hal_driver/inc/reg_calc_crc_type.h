#ifndef REG_CALC_CRC_TYPE_H_
#define REG_CALC_CRC_TYPE_H_
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    volatile uint32_t CRC_PARAM; //0x0
    volatile uint32_t CRC_INIT; //0x4
    volatile uint32_t CRC_CTRL; //0x8
    volatile uint32_t CRC_START; //0xc
    volatile uint32_t CRC_DAT; //0x10
    volatile uint32_t RESERVED0[3];
    volatile uint32_t CRC_RSLT; //0x20
}reg_calc_crc_t;

enum CALC_CRC_REG_CRC_CTRL_FIELD
{
    CALC_CRC_CRC_DAT_WID_MASK = (int)0x1f,
    CALC_CRC_CRC_DAT_WID_POS = 0,
    CALC_CRC_CRC_LSB_MASK = (int)0x100,
    CALC_CRC_CRC_LSB_POS = 8,
};

#ifdef __cplusplus
}
#endif

#endif