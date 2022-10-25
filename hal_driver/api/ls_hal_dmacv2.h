#ifndef LS_HAL_DMACV2_H_
#define LS_HAL_DMACV2_H_
#include "ls_msp_dmacv2.h"

#define DMA_RAM_ATTR 

typedef struct __DMA_Controller_HandleTypeDef
{
    reg_dmac_t *Instance;
    void (*channel_callback[DMAC_CHANNEL_NUM])(struct __DMA_Controller_HandleTypeDef*,uint32_t,uint8_t);
    uint32_t param[DMAC_CHANNEL_NUM];
}DMA_Controller_HandleTypeDef;

enum DMA_MODE_SEL
{
    Mem2Mem = 0,
    Peri2Mem,
    Mem2Peri,
};

enum DMA_DATA_WIDTH
{
    DMA_SIZE_BYTE = 0x0,
    DMA_SIZE_HALFWORD = 0x1,
    DMA_SIZE_WORD = 0x2
};

struct ctrl_data_config
{
    uint32_t channel_en:1,
             circular_mode_en:1,
             peripheral_flow_ctrl:1,
             direct_mode_en:1,
             dma_mode_sel:2,
             channel_priority:3,
             peripheral_handshake:7,
             src_inc:1,
             src_width:2,
             src_burst:3,
             src_inc_offset:1,
             rsvd0:1,
             dst_inc:1,
             dst_witdh:2,
             dst_burst:3,
             dst_inc_offset:1,
             rsvd1:1;
};

struct DMA_Channel_Config
{
    struct ctrl_data_config ctrl;
    uint32_t src_addr;
    uint32_t dst_addr;
    uint32_t byte_count:16,
             dummy:16; 
};

#define DEF_DMA_CONTROLLER(dmac_inst,dmac_reg) \
    DMA_Controller_HandleTypeDef dmac_inst = { \
        .Instance = dmac_reg,\
    };

#define DMA_CONTROLLER_INIT(dmac_inst) HAL_DMA_Controller_Init(&dmac_inst)
#define DMA_CONTROLLER_DEINIT(dmac_inst) HAL_DMA_Controller_DeInit(&dmac_inst)

void HAL_DMA_Controller_Init(DMA_Controller_HandleTypeDef *hdma);

void HAL_DMA_Controller_DeInit(DMA_Controller_HandleTypeDef *hdma);

void HAL_DMA_Channel_Start_IT(DMA_Controller_HandleTypeDef *hdma,uint8_t ch_idx,struct DMA_Channel_Config *cfg,void (*callback)(DMA_Controller_HandleTypeDef *,uint32_t,uint8_t),uint32_t param);

void HAL_DMA_Controller_IRQHandler(DMA_Controller_HandleTypeDef *hdma);
#endif

