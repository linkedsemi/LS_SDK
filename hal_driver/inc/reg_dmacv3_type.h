#ifndef REG_DMAC_TYPE_H_
#define REG_DMAC_TYPE_H_
#include <stdint.h>

typedef struct 
{
    volatile uint32_t SAR; //0x0
    volatile uint32_t RESERVED0[1];
    volatile uint32_t DAR; //0x8
    volatile uint32_t RESERVED1[1];
    volatile uint32_t LLP; //0x10
    volatile uint32_t RESERVED2[1];
    volatile uint32_t CTL[2]; //0x18
    volatile uint32_t SSTAT; //0x20
    volatile uint32_t RESERVED3[1];
    volatile uint32_t DSTAT; //0x28
    volatile uint32_t RESERVED4[1];
    volatile uint32_t SSTATAR; //0x30
    volatile uint32_t RESERVED5[1];
    volatile uint32_t DSTATAR; //0x38
    volatile uint32_t RESERVED6[1];
    volatile uint32_t CFG[2]; //0x40
    volatile uint32_t SGR; //0x48
    volatile uint32_t RESERVED7[1];
    volatile uint32_t DSR; //0x50
    volatile uint32_t RESERVED8[1];
}dw_dmac_ch_reg_t;

typedef struct
{
    dw_dmac_ch_reg_t CH[8];
    volatile uint32_t RAWTFR; //0x2c0
    volatile uint32_t RESERVED54[1];
    volatile uint32_t RAWBLOCK; //0x2c8
    volatile uint32_t RESERVED55[1];
    volatile uint32_t RAWSRCTRAN; //0x2d0
    volatile uint32_t RESERVED56[1];
    volatile uint32_t RAWDSTTRAN; //0x2d8
    volatile uint32_t RESERVED57[1];
    volatile uint32_t RAWERR; //0x2e0
    volatile uint32_t RESERVED58[1];
    volatile uint32_t STATUSTFR; //0x2e8
    volatile uint32_t RESERVED59[1];
    volatile uint32_t STATUSBLOCK; //0x2f0
    volatile uint32_t RESERVED60[1];
    volatile uint32_t STATUSSRCTRAN; //0x2f8
    volatile uint32_t RESERVED61[1];
    volatile uint32_t STATUSDSTTRAN; //0x300
    volatile uint32_t RESERVED62[1];
    volatile uint32_t STATUSERR; //0x308
    volatile uint32_t RESERVED63[1];
    volatile uint32_t MASKTFR; //0x310
    volatile uint32_t RESERVED64[1];
    volatile uint32_t MASKBLOCK; //0x318
    volatile uint32_t RESERVED65[1];
    volatile uint32_t MASKSRCTRAN; //0x320
    volatile uint32_t RESERVED66[1];
    volatile uint32_t MASKDSTTRAN; //0x328
    volatile uint32_t RESERVED67[1];
    volatile uint32_t MASKERR; //0x330
    volatile uint32_t RESERVED68[1];
    volatile uint32_t CLEARTFR; //0x338
    volatile uint32_t RESERVED69[1];
    volatile uint32_t CLEARBLOCK; //0x340
    volatile uint32_t RESERVED70[1];
    volatile uint32_t CLEARSRCTRAN; //0x348
    volatile uint32_t RESERVED71[1];
    volatile uint32_t CLEARDSTTRAN; //0x350
    volatile uint32_t RESERVED72[1];
    volatile uint32_t CLEARERR; //0x358
    volatile uint32_t RESERVED73[1];
    volatile uint32_t STATUSINT; //0x360
    volatile uint32_t RESERVED74[1];
    volatile uint32_t REQSRCREG; //0x368
    volatile uint32_t RESERVED75[1];
    volatile uint32_t REQDSTREG; //0x370
    volatile uint32_t RESERVED76[1];
    volatile uint32_t SGLREQSRC; //0x378
    volatile uint32_t RESERVED77[1];
    volatile uint32_t SGLREQDST; //0x380
    volatile uint32_t RESERVED78[1];
    volatile uint32_t LSTSRCREG; //0x388
    volatile uint32_t RESERVED79[1];
    volatile uint32_t LSTDSTREG; //0x390
    volatile uint32_t RESERVED80[1];
    volatile uint32_t EN;        //0x398
    volatile uint32_t RESERVED81[1];
    volatile uint32_t CHEN;      //0x3a0
    volatile uint32_t RESERVED82[1];
    volatile uint32_t ID; //0x3a8
}reg_dmac_t;

enum DMAC_REG_LLP_FIELD
{
    DMAC_LMS_MASK = (int)0x3,
    DMAC_LMS_POS = 0,
    DMAC_LOC_MASK = (int)0xfffffffc,
    DMAC_LOC_POS = 2,
};

enum DMAC_REG_CTL0_FIELD
{
    DMAC_INT_EN_MASK = (int)0x1,
    DMAC_INT_EN_POS = 0,
    DMAC_DST_TR_WIDTH_MASK = (int)0xe,
    DMAC_DST_TR_WIDTH_POS = 1,
    DMAC_SRC_TR_WIDTH_MASK = (int)0x70,
    DMAC_SRC_TR_WIDTH_POS = 4,
    DMAC_DINC_MASK = (int)0x180,
    DMAC_DINC_POS = 7,
    DMAC_SINC_MASK = (int)0x600,
    DMAC_SINC_POS = 9,
    DMAC_DEST_MSIZE_MASK = (int)0x3800,
    DMAC_DEST_MSIZE_POS = 11,
    DMAC_SRC_MSIZE_MASK = (int)0x1c000,
    DMAC_SRC_MSIZE_POS = 14,
    DMAC_SRC_GATHER_EN_MASK = (int)0x20000,
    DMAC_SRC_GATHER_EN_POS = 17,
    DMAC_DST_SCATTER_EN_MASK = (int)0x40000,
    DMAC_DST_SCATTER_EN_POS = 18,
    DMAC_TT_FC_MASK = (int)0x700000,
    DMAC_TT_FC_POS = 20,
    DMAC_DMS_MASK = (int)0x1800000,
    DMAC_DMS_POS = 23,
    DMAC_SMS_MASK = (int)0x6000000,
    DMAC_SMS_POS = 25,
    DMAC_LLP_DST_EN_MASK = (int)0x8000000,
    DMAC_LLP_DST_EN_POS = 27,
    DMAC_LLP_SRC_EN_MASK = (int)0x10000000,
    DMAC_LLP_SRC_EN_POS = 28,
};

enum DMAC_REG_CTL1_FIELD
{
    DMAC_BLOCK_TS_MASK = (int)0xfff,
    DMAC_BLOCK_TS_POS = 0,
    DMAC_DONE_MASK = (int)0x1000,
    DMAC_DONE_POS = 12,
};

enum DMAC_REG_CFG0_FIELD
{
    DMAC_CH_PRIOR_MASK = (int)0xe0,
    DMAC_CH_PRIOR_POS = 5,
    DMAC_CH_SUSP_MASK = (int)0x100,
    DMAC_CH_SUSP_POS = 8,
    DMAC_FIFO_EMPTY_MASK = (int)0x200,
    DMAC_FIFO_EMPTY_POS = 9,
    DMAC_HS_SEL_DST_MASK = (int)0x400,
    DMAC_HS_SEL_DST_POS = 10,
    DMAC_HS_SEL_SRC_MASK = (int)0x800,
    DMAC_HS_SEL_SRC_POS = 11,
    DMAC_LOCK_CH_L_MASK = (int)0x3000,
    DMAC_LOCK_CH_L_POS = 12,
    DMAC_LOCK_B_L_MASK = (int)0xc000,
    DMAC_LOCK_B_L_POS = 14,
    DMAC_LOCK_H_MASK = (int)0x10000,
    DMAC_LOCK_H_POS = 16,
    DMAC_LOCK_B_MASK = (int)0x20000,
    DMAC_LOCK_B_POS = 17,
    DMAC_DST_HS_POL_MASK = (int)0x40000,
    DMAC_DST_HS_POL_POS = 18,
    DMAC_SRC_HS_POL_MASK = (int)0x80000,
    DMAC_SRC_HS_POL_POS = 19,
    DMAC_MAX_ABRST_MASK = (int)0x3ff00000,
    DMAC_MAX_ABRST_POS = 20,
    DMAC_RELOAD_SRC_MASK = (int)0x40000000,
    DMAC_RELOAD_SRC_POS = 30,
    DMAC_RELOAD_DST_MASK = (int)0x80000000,
    DMAC_RELOAD_DST_POS = 31,
};

enum DMAC_REG_CFG1_FIELD
{
    DMAC_FCMODE_MASK = (int)0x1,
    DMAC_FCMODE_POS = 0,
    DMAC_FIFO_MODE_MASK = (int)0x2,
    DMAC_FIFO_MODE_POS = 1,
    DMAC_PROTCTL_MASK = (int)0x1c,
    DMAC_PROTCTL_POS = 2,
    DMAC_DS_UPD_EN_MASK = (int)0x20,
    DMAC_DS_UPD_EN_POS = 5,
    DMAC_SS_UPD_EN_MASK = (int)0x40,
    DMAC_SS_UPD_EN_POS = 6,
    DMAC_SRC_PER_MASK = (int)0x780,
    DMAC_SRC_PER_POS = 7,
    DMAC_DEST_PER_MASK = (int)0xf800,
    DMAC_DEST_PER_POS = 11,
};

enum DMAC_REG_SGR_FIELD
{
    DMAC_SGI_MASK = (int)0xfffff,
    DMAC_SGI_POS = 0,
    DMAC_SGC_MASK = (int)0xfff00000,
    DMAC_SGC_POS = 20,
};

enum DMAC_REG_DSR_FIELD
{
    DMAC_DSI_MASK = (int)0xfffff,
    DMAC_DSI_POS = 0,
    DMAC_DSC_MASK = (int)0xfff00000,
    DMAC_DSC_POS = 20,
};


enum DMAC_REG_STATUSINT_FIELD
{
    DMAC_TFR_MASK = (int)0x1,
    DMAC_TFR_POS = 0,
    DMAC_BLOCK_MASK = (int)0x2,
    DMAC_BLOCK_POS = 1,
    DMAC_SRCT_MASK = (int)0x4,
    DMAC_SRCT_POS = 2,
    DMAC_DSTT_MASK = (int)0x8,
    DMAC_DSTT_POS = 3,
    DMAC_ERR_MASK = (int)0x10,
    DMAC_ERR_POS = 4,
};


#endif

