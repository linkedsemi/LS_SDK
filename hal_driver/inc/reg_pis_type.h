#ifndef REG_PIS_TYPE_H_
#define REG_PIS_TYPE_H_
#include <stdint.h>
#include "pis_config.h"

typedef struct
{
    volatile uint32_t CH[PIC_CHANNEL_NUM];
    volatile uint32_t OER;
} reg_pis_t;

enum PIS_REG_CH_FIELD
{
    PIS_DST_MASK = (int)0x3f,
    PIS_DST_POS = 0,
    PIS_SRC_MASK = (int)0x3f00,
    PIS_SRC_POS = 8,
    PIS_EDGE_MASK = (int)0x30000,
    PIS_EDGE_POS = 16,
    PIS_SYNC_MASK = (int)0x3000000,
    PIS_SYNC_POS = 24,
};

#endif
