#ifndef REG_SPIS_TYPE_H_
#define REG_SPIS_TYPE_H_
#include <stdint.h>

typedef struct
{
    volatile uint32_t INTR_MSK; //0x0
    volatile uint32_t INTR_CLR; //0x4
    volatile uint32_t INTR_STT; //0x8
    volatile uint32_t INTR_RAW; //0xc
    volatile uint32_t RX_CTRL; //0x10
    volatile uint32_t TX_CTRL; //0x14
    volatile uint32_t RX_FIFO_THR; //0x18
    volatile uint32_t TX_FIFO_THR; //0x1c
    volatile uint32_t RX_FIFO_DAT; //0x20
    volatile uint32_t TX_FIFO_DAT; //0x24
    volatile uint32_t RX_FIFO_FLVL; //0x28
    volatile uint32_t TX_FIFO_FLVL; //0x2c
    volatile uint32_t FIFO_CLR; //0x30
}reg_spis_t;

enum SPIS_REG_INTR_STT_FIELD
{
    SPIS_INTR_END_MASK = (int)0x10,
    SPIS_INTR_END_POS = 4,  
    SPIS_INTR_TX_UDR_MASK = (int)0x8,
    SPIS_INTR_TX_UDR_POS = 3,  
    SPIS_INTR_RX_OVR_MASK = (int)0x4,
    SPIS_INTR_RX_OVR_POS = 2,
    SPIS_INTR_TX_FIFO_MASK = (int)0x2,
    SPIS_INTR_TX_FIFO_POS = 1,  
    SPIS_INTR_RX_FIFO_MASK = (int)0x1,
    SPIS_INTR_RX_FIFO_POS = 0,
};

enum SPIS_REG_INTR_RAW_FIELD
{
    SPIS_INTR_RAW_MASK = (int)0x1f,
    SPIS_INTR_RAW_POS = 0
};

enum SPIS_REG_RX_CTRL_FIELD
{
    SPIS_RX_POL_MASK = (int)0x1,
    SPIS_RX_POL_POS = 0,
    SPIS_RX_START_IDX_MASK = (int)0x2,
    SPIS_RX_START_IDX_POS = 1,
    SPIS_RX_MSB_MASK = (int)0x4,
    SPIS_RX_MSB_POS = 2,
    SPIS_RX_DMA_EN_MASK = (int)0x8,
    SPIS_RX_DMA_EN_POS = 3,
    SPIS_RX_SZ_MASK = (int)0x1f0,
    SPIS_RX_SZ_POS = 4,
    SPIS_CAP_DIS_MASK = (int)0x1000,
    SPIS_CAP_DIS_POS = 12,
    SPIS_CAP_IDX_MASK = (int)0x1f0000,
    SPIS_CAP_IDX_POS = 16,
    SPIS_CAP_INFNT_MASK = (int)0x1000000,
    SPIS_CAP_INFNT_POS = 24,
};

enum SPIS_REG_TX_CTRL_FIELD
{
    SPIS_TX_POL_MASK = (int)0x1,
    SPIS_TX_POL_POS = 0,
    SPIS_TX_START_IDX_MASK = (int)0x2,
    SPIS_TX_START_IDX_POS = 1,
    SPIS_TX_MSB_MASK = (int)0x4,
    SPIS_TX_MSB_POS = 2,
    SPIS_TX_DMA_EN_MASK = (int)0x8,
    SPIS_TX_DMA_EN_POS = 3,
    SPIS_TX_SZ_MASK = (int)0x1f0,
    SPIS_TX_SZ_POS = 4,
    SPIS_DRV_DIS_MASK = (int)0x1000,
    SPIS_DRV_DIS_POS = 12,
    SPIS_DRV_IDX_MASK = (int)0x1f0000,
    SPIS_DRV_IDX_POS = 16,
};

enum SPIS_REG_FIFO_CLR_FIELD
{
    SPIS_RX_FIFO_CLR_MASK = (int)0x1,
    SPIS_RX_FIFO_CLR_POS = 0,
    SPIS_TX_FIFO_CLR_MASK = (int)0x2,
    SPIS_TX_FIFO_CLR_POS = 1,
};

#endif