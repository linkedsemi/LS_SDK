#ifndef LS_HAL_DMACV3_H_
#define LS_HAL_DMACV3_H_
#include <stdbool.h>
#include "ls_msp_dmacv3.h"

#ifndef DMA_RAM_ATTR
#define DMA_RAM_ATTR 
#endif

enum DMA_TRANSFER_TYPE
{
    M2M,
    M2P,
    P2M,
    P2P
};

enum DMA_ADDR_CHNG
{
    ADDR_INC,
    ADDR_DEC,
    ADDR_NO_CHNG,
};

enum DMA_TRANSFER_WIDTH
{
    TRANSFER_WIDTH_8BITS,
    TRANSFER_WIDTH_16BITS,
    TRANSFER_WIDTH_32BITS,
    TRANSFER_WIDTH_64BITS,
    TRANSFER_WIDTH_128BITS,
    TRANSFER_WIDTH_256BITS,
};

enum DMA_BURST_TRANSACTION_LENGTH
{
    BUSRT_TRANSACTION_1_ITEM,
    BURST_TRANSACTION_4_ITEMS,
    BURST_TRANSACTION_8_ITEMS,
    BURST_TRANSACTION_16_ITEMS,
    BURST_TRANSACTION_32_ITEMS,
    BURST_TRANSACTION_64_ITEMS,
    BURST_TRANSACTION_128_ITEMS,
    BURST_TRANSACTION_256_ITEMS,
};

struct ch_ctl
{
    uint32_t int_en:1,
             dst_tr_width:3,
             src_tr_width:3,
             dinc:2,
             sinc:2,
             dest_msize:3,
             src_msize:3,
             src_gather_en:1,
             dst_scatter_en:1,
             reserved0:1,
             tt_fc:3,
             dms:2,
             sms:2,
             llp_dst_en:1,
             llp_src_en:1,
             reserved1:3;
    uint32_t block_ts:12,
             done:1,
             reserved2:19;
};

struct ch_cfg
{
    uint32_t reserved0:5,
             ch_prior:3,
             ch_susp:1,
             fifo_empty:1,
             hs_sel_dst:1,
             hs_sel_src:1,
             lock_ch_l:2,
             lock_b_l:2,
             lock_ch:1,
             lock_b:1,
             dst_hs_pol:1,
             src_hs_pol:1,
             max_abrst:10,
             reload_src:1,
             reload_dst:1;
    uint32_t fcmode:1,
             fifo_mode:1,
             protctl:3,
             ds_upd_en:1,
             ss_upd_en:1,
             src_per:4,
             dst_per:4,
             reserved1:17;
};

struct dma_lli
{
    uint32_t sar;
    uint32_t dar;
    uint32_t llp;
    struct ch_ctl ctl;
    uint32_t sstat;
    uint32_t dstat;
};

struct ch_gather_scatter
{
    uint32_t interval:20,
             count:12;
};

struct ch_reg
{
    uint32_t sar;
    uint32_t dar;
    uint32_t llp;
    struct ch_ctl ctl;
    struct ch_cfg cfg;
    struct ch_gather_scatter sgr;
    struct ch_gather_scatter dsr;
    uint8_t ch_idx;
    uint8_t handshake;
};

typedef struct __DMA_Controller_HandleTypeDef
{
    reg_dmac_t *Instance;
    void (*channel_callback[DMAC_CHANNEL_NUM])(struct __DMA_Controller_HandleTypeDef*,uint32_t,uint8_t,uint32_t *,bool,uint32_t);
    uint32_t param[DMAC_CHANNEL_NUM];
}DMA_Controller_HandleTypeDef;

#define DEF_DMA_CONTROLLER(dmac_inst,dmac_reg) \
    DMA_Controller_HandleTypeDef dmac_inst = { \
        .Instance = dmac_reg,\
    };

#define DMA_CONTROLLER_INIT(dmac_inst) HAL_DMA_Controller_Init(&dmac_inst)
#define DMA_CONTROLLER_DEINIT(dmac_inst) HAL_DMA_Controller_DeInit(&dmac_inst)

#define _DMA_SAR_DAR_LLP_CTL_SET(struct_var,idx,src,dst,data_width,src_burst_len,dst_burst_len,size,type,lli,scatter_count,gather_count) \
    do{\
        struct_var.sar = (uint32_t)src;\
        struct_var.dar = (uint32_t)dst;\
        struct_var.llp = (uint32_t)lli;\
        struct_var.ctl.int_en = 1;\
        struct_var.ctl.dst_tr_width = data_width;\
        struct_var.ctl.src_tr_width = data_width;\
        struct_var.ctl.dinc = type == M2P? ADDR_NO_CHNG : ADDR_INC;\
        struct_var.ctl.sinc = type == P2M? ADDR_NO_CHNG : ADDR_INC;\
        struct_var.ctl.dest_msize = dst_burst_len;\
        struct_var.ctl.src_msize = src_burst_len;\
        struct_var.ctl.src_gather_en = !!gather_count;\
        struct_var.ctl.dst_scatter_en = !!scatter_count;\
        struct_var.ctl.reserved0 = 0;\
        struct_var.ctl.tt_fc = type;\
        struct_var.ctl.dms = 0;\
        struct_var.ctl.sms = 0;\
        struct_var.ctl.llp_dst_en = type == P2M && lli;\
        struct_var.ctl.llp_src_en = type == M2P && lli;\
        struct_var.ctl.reserved1 = 0;\
        struct_var.ctl.block_ts = size;\
        struct_var.ctl.done = 0;\
        struct_var.ctl.reserved2 = 0;\
    }while(0)

#define DMA_CHANNEL_CFG(reg_struct,idx,src,dst,data_width,size,type,lli,hs,scatter_count,scatter_interval,gather_count,gather_interval) \
    do{\
        _DMA_SAR_DAR_LLP_CTL_SET(reg_struct,idx,src,dst,data_width,BUSRT_TRANSACTION_1_ITEM,BUSRT_TRANSACTION_1_ITEM,size,type,lli,scatter_count,gather_count);\
        reg_struct.cfg.reserved0 = 0;\
        reg_struct.cfg.ch_prior = idx;\
        reg_struct.cfg.ch_susp = 0;\
        reg_struct.cfg.fifo_empty = 0;\
        reg_struct.cfg.hs_sel_dst = 0;\
        reg_struct.cfg.hs_sel_src = 0;\
        reg_struct.cfg.lock_ch_l = 0;\
        reg_struct.cfg.lock_b_l = 0;\
        reg_struct.cfg.lock_ch = 0;\
        reg_struct.cfg.dst_hs_pol = 0;\
        reg_struct.cfg.src_hs_pol = 0;\
        reg_struct.cfg.max_abrst = 0;\
        reg_struct.cfg.reload_src = 0;\
        reg_struct.cfg.reload_dst = 0;\
        reg_struct.cfg.fcmode = 0;\
        reg_struct.cfg.fifo_mode = 1;\
        reg_struct.cfg.protctl = 1;\
        reg_struct.cfg.ds_upd_en = 0;\
        reg_struct.cfg.ss_upd_en = 0;\
        reg_struct.cfg.src_per = idx;\
        reg_struct.cfg.dst_per = idx;\
        reg_struct.cfg.reserved1 = 0;\
        reg_struct.sgr.interval = gather_interval;\
        reg_struct.sgr.count = gather_count;\
        reg_struct.dsr.interval = scatter_interval;\
        reg_struct.dsr.count = scatter_count;\
        reg_struct.ch_idx = idx;\
        reg_struct.handshake = hs;\
    }while(0)

#define DMA_LLI_CFG(lli_struct,idx,src,dst,data_width,size,type,lli) \
    do{\
        _DMA_SAR_DAR_LLP_CTL_SET(lli_struct,idx,src,dst,data_width,BUSRT_TRANSACTION_1_ITEM,BUSRT_TRANSACTION_1_ITEM,size,type,lli,0,0);\
        lli_struct.sstat = 0;\
        lli_struct.dstat = 0;\
    }while(0)

void HAL_DMA_Controller_Init(DMA_Controller_HandleTypeDef *hdma);

void HAL_DMA_Controller_DeInit(DMA_Controller_HandleTypeDef *hdma);

void HAL_DMA_Channel_Start_IT(DMA_Controller_HandleTypeDef *hdma,struct ch_reg *reg_cfg,void (*callback)(DMA_Controller_HandleTypeDef *,uint32_t,uint8_t,uint32_t *,bool,uint32_t),uint32_t param);

uint32_t HAL_DMA_Channel_Abort(DMA_Controller_HandleTypeDef *hdma,uint8_t ch_idx);

void HAL_DMA_Controller_IRQHandler(DMA_Controller_HandleTypeDef *hdma);

#endif
