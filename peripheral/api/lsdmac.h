#ifndef LSDMAC_H_
#define LSDMAC_H_
#include <stdbool.h>
#include "reg_dmac_type.h"
#include "reg_base_addr.h"
#include "dmac_config.h"

#ifdef DMAC1_BASE_ADDR
#define DMAC1 (reg_dmac_t *)DMAC1_BASE_ADDR
#endif
#define DMA_RAM_ATTR __attribute__((section("DMARAM")))
typedef struct __DMA_Controller_HandleTypeDef
{
    reg_dmac_t *Instance;
    uint32_t *channel_param;
}DMA_Controller_HandleTypeDef;

struct ctrl_data_config
{
    uint32_t cycle_ctrl:3,
            next_useburst:1,
            n_minus_1:10,
            R_power:4,
            src_prot_ctrl:3,
            dst_prot_ctrl:3,
            src_size:2,
            src_inc:2,
            dst_size:2,
            dst_inc:2;
};

struct DMA_Channel_Config
{
    uint32_t src_data_end_ptr;
    uint32_t dst_data_end_ptr;
    struct ctrl_data_config ctrl_data;
    uint32_t dummy;
};

enum DMA_Cycle_Type {
    DMA_Cycle_Stop,
    DMA_Cycle_Basic,
    DMA_Cycle_Auto,
    DMA_Cycle_PingPong,
    DMA_Cycle_Mem_Scatter_Gather_Prim,
    DMA_Cycle_Mem_Scatter_Gather_Alt,
    DMA_Cycle_Periph_Scatter_Gather_Prim,
    DMA_Cycle_Periph_Scatter_Gather_Alt,
};

/**
 * @brief HAL DMA channel control structure address increment size definition
 *        The address increment size depends on data width
 *        source data width = byte:  all valid
 *        source data width = halfword: 2'b01/10/11
 *        source data width = word: 2'b10/11
 */
enum HAL_DMA_CTRL_ADDRINCR
{
    DMA_INC_BYTE = 0x0,     // address increment + 1
    DMA_INC_HALFWORD = 0x1, // address increment + 2
    DMA_INC_WORD = 0x2,     // address increment + 4
    DMA_INC_NONE = 0x3      // address no increment
};

/**
 * @brief HAL DMA channel control structure data size definition
 */
enum DMA_CTRL_DATASIZE
{
    DMA_SIZE_BYTE = 0x0,
    DMA_SIZE_HALFWORD = 0x1,
    DMA_SIZE_WORD = 0x2
};

/**
 * @brief HAL DMA control structure's R_power definition
 *        Controls how many DMA xfer can occur before the controller rearbitrates.
 */
enum HAL_DMA_CTRL_RPOWER
{
    DMA_RPOWER1 = 0x0,    // arbit after each DMA transfer
    DMA_RPOWER2 = 0x1,    // arbit after 2 DMA transfer
    DMA_RPOWER4 = 0x2,    // arbit after 4 DMA transfer
    DMA_RPOWER8 = 0x3,    // arbit after 8 DMA transfer
    DMA_RPOWER16 = 0x4,   // arbit after 16 DMA transfer
    DMA_RPOWER32 = 0x5,   // arbit after 32 DMA transfer
    DMA_RPOWER64 = 0x6,   // arbit after 64 DMA transfer
    DMA_RPOWER128 = 0x7,  // arbit after 128 DMA transfer
    DMA_RPOWER256 = 0x8,  // arbit after 256 DMA transfer
    DMA_RPOWER512 = 0x9,  // arbit after 512 DMA transfer
    DMA_RPOWER1024 = 0xf, // arbit after 1024 DMA transfer, also means no arbit
};

#define DEF_DMA_CONTROLLER(dmac_inst,dmac_reg) \
    __attribute__((section(#dmac_reg),aligned(dmac_reg##_MAX_CHANNEL_NUM * 32))) struct dmac_inst##_cs_env {\
        struct DMA_Channel_Config prim[dmac_reg##_MAX_CHANNEL_NUM];\
        struct DMA_Channel_Config alt[dmac_reg##_MAX_CHANNEL_NUM];\
    } dmac_inst##_cs;\
    static uint32_t dmac_inst##_ch_param[dmac_reg##_MAX_CHANNEL_NUM]; \
    DMA_Controller_HandleTypeDef dmac_inst = { \
        .Instance = dmac_reg,\
        .channel_param = dmac_inst##_ch_param, \
    };

#define DMA_CONTROLLER_INIT(dmac_inst) HAL_DMA_Controller_Init(&dmac_inst,&dmac_inst##_cs)
#define DMA_CONTROLLER_DEINIT(dmac_inst) HAL_DMA_Controller_DeInit(&dmac_inst)

void HAL_DMA_Controller_Init(DMA_Controller_HandleTypeDef *hdma,void *cs_ptr);

void HAL_DMA_Controller_DeInit(DMA_Controller_HandleTypeDef *hdma);

void HAL_DMA_Channel_Start_IT(DMA_Controller_HandleTypeDef *hdma,uint8_t ch_idx,uint8_t handshake,uint32_t param);

void HAL_DMA_Channel_Config_Set(DMA_Controller_HandleTypeDef *hdma,uint8_t ch_idx,bool alt,struct DMA_Channel_Config *cfg);

void HAL_DMA_Channel_Config_Get(DMA_Controller_HandleTypeDef *hdma,uint8_t ch_idx,bool alt,struct DMA_Channel_Config *cfg);

void HAL_DMA_Channel_Abort(DMA_Controller_HandleTypeDef *hdma,uint8_t ch_idx);

void HAL_DMA_Controller_IRQHandler(DMA_Controller_HandleTypeDef *hdma);


#endif
