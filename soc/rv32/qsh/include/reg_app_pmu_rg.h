#ifndef REG_APP_PMU_RG_TYPE_H_
#define REG_APP_PMU_RG_TYPE_H_
#include <stdint.h>
#include "reg_base_addr.h"

#define APP_PMU ((reg_app_pmu_rg_t *)APP_PMU_RG_APP_ADDR)

typedef struct {
    volatile uint32_t RESERVED0;
    volatile uint32_t PU1_PU0;
    volatile uint32_t PD_PU2;
    volatile uint32_t IEN1_IEN0;
    volatile uint32_t DS1_DS0;
    volatile uint32_t AE_DS2;
    volatile uint32_t OD_FIR;
    volatile uint32_t SL_ST;
} reg_io_cfg_t;

typedef struct {
    volatile uint32_t OE_DIN;
    volatile uint32_t DOC_DOS;
} reg_io_val_t;

typedef struct {
    volatile uint32_t RESERVED0;
    volatile uint32_t PD_PU;
    volatile uint32_t DS_IEN;
    volatile uint32_t FIR_DS1;
} reg_peci_io_cfg_t;

typedef struct
{
    volatile uint32_t RESERVED0[11];
    volatile uint32_t CLKG_SRST; //0x2c
    volatile uint32_t RESERVED1[5];
    volatile uint32_t CASEOPEN_CTRL; //0x44
    volatile uint32_t VBATMEM_CTRL; //0x48
    volatile uint32_t RESERVED2[1];
    volatile uint32_t PASSTHROUGH_INTR_MSK_CLR; //0x50
    volatile uint32_t PASSTHROUGH_INTR_RAW_STT; //0x54
    volatile uint32_t RESERVED3[2];
    reg_io_cfg_t QSPI1_PAD_CFG;//0x60
    volatile uint32_t GPIO_INTR_MSK[16]; //0x80
    volatile uint32_t GPIO_INTR_CLR[16]; //0xc0
    volatile uint32_t GPIO_INTR_STT[16]; //0x100
    volatile uint32_t GPIO_INTR_RAW[16]; //0x140
    reg_io_cfg_t IO_CFG[15];//0x180
    reg_io_val_t IO_VAL[16];//0x360
    reg_peci_io_cfg_t PECI_PAD_CFG;//0x3e0
#if 0
    volatile uint32_t IOA_PU0_PU1; //0x184
    volatile uint32_t IOA_PU2_PD; //0x188
    volatile uint32_t IOA_REN; //0x18c
    volatile uint32_t IOA_DS0_DS1; //0x190
    volatile uint32_t IOA_DS2_AE; //0x194
    volatile uint32_t IOA_FIR_ODE; //0x198
    volatile uint32_t IOA_ST_SL; //0x19c
    volatile uint32_t IOB_PU0_PU1; //0x1a4
    volatile uint32_t IOB_PU2_PD; //0x1a8
    volatile uint32_t IOB_REN; //0x1ac
    volatile uint32_t IOB_DS0_DS1; //0x1b0
    volatile uint32_t IOB_DS2_AE; //0x1b4
    volatile uint32_t IOB_FIR_ODE; //0x1b8
    volatile uint32_t IOB_ST_SL; //0x1bc
    volatile uint32_t IOC_PU0_PU1; //0x1c4
    volatile uint32_t IOC_PU2_PD; //0x1c8
    volatile uint32_t IOC_REN; //0x1cc
    volatile uint32_t IOC_DS0_DS1; //0x1d0
    volatile uint32_t IOC_DS2_AE; //0x1d4
    volatile uint32_t IOC_FIR_ODE; //0x1d8
    volatile uint32_t IOC_ST_SL; //0x1dc
    volatile uint32_t IOD_PU0_PU1; //0x1e4
    volatile uint32_t IOD_PU2_PD; //0x1e8
    volatile uint32_t IOD_REN; //0x1ec
    volatile uint32_t IOD_DS0_DS1; //0x1f0
    volatile uint32_t IOD_DS2_AE; //0x1f4
    volatile uint32_t IOD_FIR_ODE; //0x1f8
    volatile uint32_t IOD_ST_SL; //0x1fc
    volatile uint32_t IOE_PU0_PU1; //0x204
    volatile uint32_t IOE_PU2_PD; //0x208
    volatile uint32_t IOE_REN; //0x20c
    volatile uint32_t IOE_DS0_DS1; //0x210
    volatile uint32_t IOE_DS2_AE; //0x214
    volatile uint32_t IOE_FIR_ODE; //0x218
    volatile uint32_t IOE_ST_SL; //0x21c
    volatile uint32_t IOF_PU0_PU1; //0x224
    volatile uint32_t IOF_PU2_PD; //0x228
    volatile uint32_t IOF_REN; //0x22c
    volatile uint32_t IOF_DS0_DS1; //0x230
    volatile uint32_t IOF_DS2_AE; //0x234
    volatile uint32_t IOF_FIR_ODE; //0x238
    volatile uint32_t IOF_ST_SL; //0x23c
    volatile uint32_t IOG_PU0_PU1; //0x244
    volatile uint32_t IOG_PU2_PD; //0x248
    volatile uint32_t IOG_REN; //0x24c
    volatile uint32_t IOG_DS0_DS1; //0x250
    volatile uint32_t IOG_DS2_AE; //0x254
    volatile uint32_t IOG_FIR_ODE; //0x258
    volatile uint32_t IOG_ST_SL; //0x25c
    volatile uint32_t IOH_PU0_PU1; //0x264
    volatile uint32_t IOH_PU2_PD; //0x268
    volatile uint32_t IOH_REN; //0x26c
    volatile uint32_t IOH_DS0_DS1; //0x270
    volatile uint32_t IOH_DS2_AE; //0x274
    volatile uint32_t IOH_FIR_ODE; //0x278
    volatile uint32_t IOH_ST_SL; //0x27c
    volatile uint32_t IOI_PU0_PU1; //0x284
    volatile uint32_t IOI_PU2_PD; //0x288
    volatile uint32_t IOI_REN; //0x28c
    volatile uint32_t IOI_DS0_DS1; //0x290
    volatile uint32_t IOI_DS2_AE; //0x294
    volatile uint32_t IOI_FIR_ODE; //0x298
    volatile uint32_t IOI_ST_SL; //0x29c
    volatile uint32_t IOJ_PU0_PU1; //0x2a4
    volatile uint32_t IOJ_PU2_PD; //0x2a8
    volatile uint32_t IOJ_REN; //0x2ac
    volatile uint32_t IOJ_DS0_DS1; //0x2b0
    volatile uint32_t IOJ_DS2_AE; //0x2b4
    volatile uint32_t IOJ_FIR_ODE; //0x2b8
    volatile uint32_t IOJ_ST_SL; //0x2bc
    volatile uint32_t IOK_PU0_PU1; //0x2c4
    volatile uint32_t IOK_PU2_PD; //0x2c8
    volatile uint32_t IOK_REN; //0x2cc
    volatile uint32_t IOK_DS0_DS1; //0x2d0
    volatile uint32_t IOK_DS2_AE; //0x2d4
    volatile uint32_t IOK_FIR_ODE; //0x2d8
    volatile uint32_t IOK_ST_SL; //0x2dc
    volatile uint32_t IOM_PU0_PU1; //0x2e4
    volatile uint32_t IOM_PU2_PD; //0x2e8
    volatile uint32_t IOM_REN; //0x2ec
    volatile uint32_t IOM_DS0_DS1; //0x2f0
    volatile uint32_t IOM_DS2_AE; //0x2f4
    volatile uint32_t IOM_FIR_ODE; //0x2f8
    volatile uint32_t IOM_ST_SL; //0x2fc
    volatile uint32_t ION_PU0_PU1; //0x304
    volatile uint32_t ION_PU2_PD; //0x308
    volatile uint32_t ION_REN; //0x30c
    volatile uint32_t ION_DS0_DS1; //0x310
    volatile uint32_t ION_DS2_AE; //0x314
    volatile uint32_t ION_FIR_ODE; //0x318
    volatile uint32_t ION_ST_SL; //0x31c
    volatile uint32_t IOQ_PU0_PU1; //0x324
    volatile uint32_t IOQ_PU2_PD; //0x328
    volatile uint32_t IOQ_REN; //0x32c
    volatile uint32_t IOQ_DS0_DS1; //0x330
    volatile uint32_t IOQ_DS2_AE; //0x334
    volatile uint32_t IOQ_FIR_ODE; //0x338
    volatile uint32_t IOQ_ST_SL; //0x33c
    volatile uint32_t IOT_PU0_PU1; //0x344
    volatile uint32_t IOT_PU2_PD; //0x348
    volatile uint32_t IOT_REN; //0x34c
    volatile uint32_t IOT_DS0_DS1; //0x350
    volatile uint32_t IOT_DS2_AE; //0x354
    volatile uint32_t IOT_FIR_ODE; //0x358
    volatile uint32_t IOT_ST_SL; //0x35c
    volatile uint32_t IOA_DIN_OE; //0x360
    volatile uint32_t IOA_DOT; //0x364
    volatile uint32_t IOB_DIN_OE; //0x368
    volatile uint32_t IOB_DOT; //0x36c
    volatile uint32_t IOC_DIN_OE; //0x370
    volatile uint32_t IOC_DOT; //0x374
    volatile uint32_t IOD_DIN_OE; //0x378
    volatile uint32_t IOD_DOT; //0x37c
    volatile uint32_t IOE_DIN_OE; //0x380
    volatile uint32_t IOE_DOT; //0x384
    volatile uint32_t IOF_DIN_OE; //0x388
    volatile uint32_t IOF_DOT; //0x38c
    volatile uint32_t IOG_DIN_OE; //0x390
    volatile uint32_t IOG_DOT; //0x394
    volatile uint32_t IOH_DIN_OE; //0x398
    volatile uint32_t IOH_DOT; //0x39c
    volatile uint32_t IOI_DIN_OE; //0x3a0
    volatile uint32_t IOI_DOT; //0x3a4
    volatile uint32_t IOJ_DIN_OE; //0x3a8
    volatile uint32_t IOJ_DOT; //0x3ac
    volatile uint32_t IOK_DIN_OE; //0x3b0
    volatile uint32_t IOK_DOT; //0x3b4
    volatile uint32_t IOM_DIN_OE; //0x3b8
    volatile uint32_t IOM_DOT; //0x3bc
    volatile uint32_t ION_DIN_OE; //0x3c0
    volatile uint32_t ION_DOT; //0x3c4
    volatile uint32_t IOQ_DIN_OE; //0x3c8
    volatile uint32_t IOQ_DOT; //0x3cc
    volatile uint32_t IOT_DIN_OE; //0x3d0
    volatile uint32_t IOT_DOT; //0x3d4
    volatile uint32_t QSPI_PAD_DIN_OE; //0x3d8
    volatile uint32_t QSPI_PAD_DOT; //0x3dc
    volatile uint32_t PECI_PAD_PU_PD; //0x3e4
    volatile uint32_t PECI_PAD_REN; //0x3e8
    volatile uint32_t PECI_PAD_DS_FIR; //0x3ec
#endif
} reg_app_pmu_rg_t;
_Static_assert(sizeof(reg_app_pmu_rg_t) == 0x3f0, "reg_app_pmu_rg_t size error.");

enum APP_PMU_RG_REG_CLKG_SRST_FIELD {
    APP_PMU_RG_CLKG_SET_TIM_MASK = (int)0x1,
    APP_PMU_RG_CLKG_SET_TIM_POS = 0,
    APP_PMU_RG_CLKG_CLR_TIM_MASK = (int)0x2,
    APP_PMU_RG_CLKG_CLR_TIM_POS = 1,
    APP_PMU_RG_CLKG_SET_RTC_MASK = (int)0x10,
    APP_PMU_RG_CLKG_SET_RTC_POS = 4,
    APP_PMU_RG_CLKG_CLR_RTC_MASK = (int)0x20,
    APP_PMU_RG_CLKG_CLR_RTC_POS = 5,
};

enum APP_PMU_RG_REG_CASEOPEN_CTRL_FIELD {
    APP_PMU_RG_CASEOPEN_MASK_MASK = (int)0x3,
    APP_PMU_RG_CASEOPEN_MASK_POS = 0,
    APP_PMU_RG_CASEOPEN_CLR_MASK = (int)0xc,
    APP_PMU_RG_CASEOPEN_CLR_POS = 2,
    APP_PMU_RG_CASEOPEN_INT_MASK = (int)0x30,
    APP_PMU_RG_CASEOPEN_INT_POS = 4,
    APP_PMU_RG_CASEOPEN_STT_MASK = (int)0xc0,
    APP_PMU_RG_CASEOPEN_STT_POS = 6,
};

enum APP_PMU_RG_REG_VBATMEM_CTRL_FIELD {
    APP_PMU_RG_VBATMEM_CLK_MASK = (int)0x1,
    APP_PMU_RG_VBATMEM_CLK_POS = 0,
    APP_PMU_RG_VBATMEM_RDEN_MASK = (int)0x2,
    APP_PMU_RG_VBATMEM_RDEN_POS = 1,
    APP_PMU_RG_VBATMEM_WDEN_MASK = (int)0x4,
    APP_PMU_RG_VBATMEM_WDEN_POS = 2,
    APP_PMU_RG_VBATMEM_ADDR_MASK = (int)0xff00,
    APP_PMU_RG_VBATMEM_ADDR_POS = 8,
    APP_PMU_RG_VBATMEM_WDAT_MASK = (int)0xff0000,
    APP_PMU_RG_VBATMEM_WDAT_POS = 16,
    APP_PMU_RG_VBATMEM_RDAT_MASK = (int)0xff000000,
    APP_PMU_RG_VBATMEM_RDAT_POS = 24,
};

enum APP_PMU_RG_REG_PASSTHROUGH_INTR_MSK_CLR_FIELD {
    APP_PMU_RG_PASSTHROUGH_INTR_MSK_MASK = (int)0xffff,
    APP_PMU_RG_PASSTHROUGH_INTR_MSK_POS = 0,
    APP_PMU_RG_PASSTHROUGH_INTR_CLR_MASK = (int)0xffff0000,
    APP_PMU_RG_PASSTHROUGH_INTR_CLR_POS = 16,
};

enum APP_PMU_RG_REG_PASSTHROUGH_INTR_RAW_STT_FIELD {
    APP_PMU_RG_PASSTHROUGH_INTR_RAW_MASK = (int)0xffff,
    APP_PMU_RG_PASSTHROUGH_INTR_RAW_POS = 0,
    APP_PMU_RG_PASSTHROUGH_INTR_STT_MASK = (int)0xffff0000,
    APP_PMU_RG_PASSTHROUGH_INTR_STT_POS = 16,
};

enum APP_PMU_RG_REG_IOA_LOCK_FIELD {
    APP_PMU_RG_GPIOA_LOCK_MASK = (int)0xffff,
    APP_PMU_RG_GPIOA_LOCK_POS = 0,
};

enum APP_PMU_RG_REG_IOA_PU0_PU1_FIELD {
    APP_PMU_RG_GPIOA_PU0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOA_PU0_POS = 0,
    APP_PMU_RG_GPIOA_PU1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOA_PU1_POS = 16,
};

enum APP_PMU_RG_REG_IOA_PU2_PD_FIELD {
    APP_PMU_RG_GPIOA_PU2_MASK = (int)0xffff,
    APP_PMU_RG_GPIOA_PU2_POS = 0,
    APP_PMU_RG_GPIOA_PD_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOA_PD_POS = 16,
};

enum APP_PMU_RG_REG_IOA_REN_FIELD {
    APP_PMU_RG_GPIOA_REN0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOA_REN0_POS = 0,
    APP_PMU_RG_GPIOA_REN1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOA_REN1_POS = 16,
};

enum APP_PMU_RG_REG_IOA_DS0_DS1_FIELD {
    APP_PMU_RG_GPIOA_DS0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOA_DS0_POS = 0,
    APP_PMU_RG_GPIOA_DS1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOA_DS1_POS = 16,
};

enum APP_PMU_RG_REG_IOA_DS2_AE_FIELD {
    APP_PMU_RG_GPIOA_DS2_MASK = (int)0xffff,
    APP_PMU_RG_GPIOA_DS2_POS = 0,
    APP_PMU_RG_GPIOA_AE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOA_AE_POS = 16,
};

enum APP_PMU_RG_REG_IOA_FIR_ODE_FIELD {
    APP_PMU_RG_GPIOA_FIR_MASK = (int)0xffff,
    APP_PMU_RG_GPIOA_FIR_POS = 0,
    APP_PMU_RG_GPIOA_ODE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOA_ODE_POS = 16,
};

enum APP_PMU_RG_REG_IOA_ST_SL_FIELD {
    APP_PMU_RG_GPIOA_ST_MASK = (int)0xffff,
    APP_PMU_RG_GPIOA_ST_POS = 0,
    APP_PMU_RG_GPIOA_SL_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOA_SL_POS = 16,
};

enum APP_PMU_RG_REG_IOB_LOCK_FIELD {
    APP_PMU_RG_GPIOB_LOCK_MASK = (int)0xffff,
    APP_PMU_RG_GPIOB_LOCK_POS = 0,
};

enum APP_PMU_RG_REG_IOB_PU0_PU1_FIELD {
    APP_PMU_RG_GPIOB_PU0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOB_PU0_POS = 0,
    APP_PMU_RG_GPIOB_PU1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOB_PU1_POS = 16,
};

enum APP_PMU_RG_REG_IOB_PU2_PD_FIELD {
    APP_PMU_RG_GPIOB_PU2_MASK = (int)0xffff,
    APP_PMU_RG_GPIOB_PU2_POS = 0,
    APP_PMU_RG_GPIOB_PD_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOB_PD_POS = 16,
};

enum APP_PMU_RG_REG_IOB_REN_FIELD {
    APP_PMU_RG_GPIOB_REN0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOB_REN0_POS = 0,
    APP_PMU_RG_GPIOB_REN1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOB_REN1_POS = 16,
};

enum APP_PMU_RG_REG_IOB_DS0_DS1_FIELD {
    APP_PMU_RG_GPIOB_DS0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOB_DS0_POS = 0,
    APP_PMU_RG_GPIOB_DS1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOB_DS1_POS = 16,
};

enum APP_PMU_RG_REG_IOB_DS2_AE_FIELD {
    APP_PMU_RG_GPIOB_DS2_MASK = (int)0xffff,
    APP_PMU_RG_GPIOB_DS2_POS = 0,
    APP_PMU_RG_GPIOB_AE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOB_AE_POS = 16,
};

enum APP_PMU_RG_REG_IOB_FIR_ODE_FIELD {
    APP_PMU_RG_GPIOB_FIR_MASK = (int)0xffff,
    APP_PMU_RG_GPIOB_FIR_POS = 0,
    APP_PMU_RG_GPIOB_ODE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOB_ODE_POS = 16,
};

enum APP_PMU_RG_REG_IOB_ST_SL_FIELD {
    APP_PMU_RG_GPIOB_ST_MASK = (int)0xffff,
    APP_PMU_RG_GPIOB_ST_POS = 0,
    APP_PMU_RG_GPIOB_SL_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOB_SL_POS = 16,
};

enum APP_PMU_RG_REG_IOC_LOCK_FIELD {
    APP_PMU_RG_GPIOC_LOCK_MASK = (int)0xffff,
    APP_PMU_RG_GPIOC_LOCK_POS = 0,
};

enum APP_PMU_RG_REG_IOC_PU0_PU1_FIELD {
    APP_PMU_RG_GPIOC_PU0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOC_PU0_POS = 0,
    APP_PMU_RG_GPIOC_PU1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOC_PU1_POS = 16,
};

enum APP_PMU_RG_REG_IOC_PU2_PD_FIELD {
    APP_PMU_RG_GPIOC_PU2_MASK = (int)0xffff,
    APP_PMU_RG_GPIOC_PU2_POS = 0,
    APP_PMU_RG_GPIOC_PD_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOC_PD_POS = 16,
};

enum APP_PMU_RG_REG_IOC_REN_FIELD {
    APP_PMU_RG_GPIOC_REN0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOC_REN0_POS = 0,
    APP_PMU_RG_GPIOC_REN1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOC_REN1_POS = 16,
};

enum APP_PMU_RG_REG_IOC_DS0_DS1_FIELD {
    APP_PMU_RG_GPIOC_DS0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOC_DS0_POS = 0,
    APP_PMU_RG_GPIOC_DS1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOC_DS1_POS = 16,
};

enum APP_PMU_RG_REG_IOC_DS2_AE_FIELD {
    APP_PMU_RG_GPIOC_DS2_MASK = (int)0xffff,
    APP_PMU_RG_GPIOC_DS2_POS = 0,
    APP_PMU_RG_GPIOC_AE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOC_AE_POS = 16,
};

enum APP_PMU_RG_REG_IOC_FIR_ODE_FIELD {
    APP_PMU_RG_GPIOC_FIR_MASK = (int)0xffff,
    APP_PMU_RG_GPIOC_FIR_POS = 0,
    APP_PMU_RG_GPIOC_ODE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOC_ODE_POS = 16,
};

enum APP_PMU_RG_REG_IOC_ST_SL_FIELD {
    APP_PMU_RG_GPIOC_ST_MASK = (int)0xffff,
    APP_PMU_RG_GPIOC_ST_POS = 0,
    APP_PMU_RG_GPIOC_SL_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOC_SL_POS = 16,
};

enum APP_PMU_RG_REG_IOD_LOCK_FIELD {
    APP_PMU_RG_GPIOD_LOCK_MASK = (int)0xffff,
    APP_PMU_RG_GPIOD_LOCK_POS = 0,
};

enum APP_PMU_RG_REG_IOD_PU0_PU1_FIELD {
    APP_PMU_RG_GPIOD_PU0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOD_PU0_POS = 0,
    APP_PMU_RG_GPIOD_PU1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOD_PU1_POS = 16,
};

enum APP_PMU_RG_REG_IOD_PU2_PD_FIELD {
    APP_PMU_RG_GPIOD_PU2_MASK = (int)0xffff,
    APP_PMU_RG_GPIOD_PU2_POS = 0,
    APP_PMU_RG_GPIOD_PD_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOD_PD_POS = 16,
};

enum APP_PMU_RG_REG_IOD_REN_FIELD {
    APP_PMU_RG_GPIOD_REN0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOD_REN0_POS = 0,
    APP_PMU_RG_GPIOD_REN1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOD_REN1_POS = 16,
};

enum APP_PMU_RG_REG_IOD_DS0_DS1_FIELD {
    APP_PMU_RG_GPIOD_DS0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOD_DS0_POS = 0,
    APP_PMU_RG_GPIOD_DS1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOD_DS1_POS = 16,
};

enum APP_PMU_RG_REG_IOD_DS2_AE_FIELD {
    APP_PMU_RG_GPIOD_DS2_MASK = (int)0xffff,
    APP_PMU_RG_GPIOD_DS2_POS = 0,
    APP_PMU_RG_GPIOD_AE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOD_AE_POS = 16,
};

enum APP_PMU_RG_REG_IOD_FIR_ODE_FIELD {
    APP_PMU_RG_GPIOD_FIR_MASK = (int)0xffff,
    APP_PMU_RG_GPIOD_FIR_POS = 0,
    APP_PMU_RG_GPIOD_ODE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOD_ODE_POS = 16,
};

enum APP_PMU_RG_REG_IOD_ST_SL_FIELD {
    APP_PMU_RG_GPIOD_ST_MASK = (int)0xffff,
    APP_PMU_RG_GPIOD_ST_POS = 0,
    APP_PMU_RG_GPIOD_SL_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOD_SL_POS = 16,
};

enum APP_PMU_RG_REG_IOE_LOCK_FIELD {
    APP_PMU_RG_GPIOE_LOCK_MASK = (int)0xffff,
    APP_PMU_RG_GPIOE_LOCK_POS = 0,
};

enum APP_PMU_RG_REG_IOE_PU0_PU1_FIELD {
    APP_PMU_RG_GPIOE_PU0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOE_PU0_POS = 0,
    APP_PMU_RG_GPIOE_PU1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOE_PU1_POS = 16,
};

enum APP_PMU_RG_REG_IOE_PU2_PD_FIELD {
    APP_PMU_RG_GPIOE_PU2_MASK = (int)0xffff,
    APP_PMU_RG_GPIOE_PU2_POS = 0,
    APP_PMU_RG_GPIOE_PD_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOE_PD_POS = 16,
};

enum APP_PMU_RG_REG_IOE_REN_FIELD {
    APP_PMU_RG_GPIOE_REN0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOE_REN0_POS = 0,
    APP_PMU_RG_GPIOE_REN1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOE_REN1_POS = 16,
};

enum APP_PMU_RG_REG_IOE_DS0_DS1_FIELD {
    APP_PMU_RG_GPIOE_DS0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOE_DS0_POS = 0,
    APP_PMU_RG_GPIOE_DS1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOE_DS1_POS = 16,
};

enum APP_PMU_RG_REG_IOE_DS2_AE_FIELD {
    APP_PMU_RG_GPIOE_DS2_MASK = (int)0xffff,
    APP_PMU_RG_GPIOE_DS2_POS = 0,
    APP_PMU_RG_GPIOE_AE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOE_AE_POS = 16,
};

enum APP_PMU_RG_REG_IOE_FIR_ODE_FIELD {
    APP_PMU_RG_GPIOE_FIR_MASK = (int)0xffff,
    APP_PMU_RG_GPIOE_FIR_POS = 0,
    APP_PMU_RG_GPIOE_ODE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOE_ODE_POS = 16,
};

enum APP_PMU_RG_REG_IOE_ST_SL_FIELD {
    APP_PMU_RG_GPIOE_ST_MASK = (int)0xffff,
    APP_PMU_RG_GPIOE_ST_POS = 0,
    APP_PMU_RG_GPIOE_SL_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOE_SL_POS = 16,
};

enum APP_PMU_RG_REG_IOF_LOCK_FIELD {
    APP_PMU_RG_GPIOF_LOCK_MASK = (int)0xffff,
    APP_PMU_RG_GPIOF_LOCK_POS = 0,
};

enum APP_PMU_RG_REG_IOF_PU0_PU1_FIELD {
    APP_PMU_RG_GPIOF_PU0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOF_PU0_POS = 0,
    APP_PMU_RG_GPIOF_PU1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOF_PU1_POS = 16,
};

enum APP_PMU_RG_REG_IOF_PU2_PD_FIELD {
    APP_PMU_RG_GPIOF_PU2_MASK = (int)0xffff,
    APP_PMU_RG_GPIOF_PU2_POS = 0,
    APP_PMU_RG_GPIOF_PD_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOF_PD_POS = 16,
};

enum APP_PMU_RG_REG_IOF_REN_FIELD {
    APP_PMU_RG_GPIOF_REN0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOF_REN0_POS = 0,
    APP_PMU_RG_GPIOF_REN1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOF_REN1_POS = 16,
};

enum APP_PMU_RG_REG_IOF_DS0_DS1_FIELD {
    APP_PMU_RG_GPIOF_DS0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOF_DS0_POS = 0,
    APP_PMU_RG_GPIOF_DS1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOF_DS1_POS = 16,
};

enum APP_PMU_RG_REG_IOF_DS2_AE_FIELD {
    APP_PMU_RG_GPIOF_DS2_MASK = (int)0xffff,
    APP_PMU_RG_GPIOF_DS2_POS = 0,
    APP_PMU_RG_GPIOF_AE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOF_AE_POS = 16,
};

enum APP_PMU_RG_REG_IOF_FIR_ODE_FIELD {
    APP_PMU_RG_GPIOF_FIR_MASK = (int)0xffff,
    APP_PMU_RG_GPIOF_FIR_POS = 0,
    APP_PMU_RG_GPIOF_ODE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOF_ODE_POS = 16,
};

enum APP_PMU_RG_REG_IOF_ST_SL_FIELD {
    APP_PMU_RG_GPIOF_ST_MASK = (int)0xffff,
    APP_PMU_RG_GPIOF_ST_POS = 0,
    APP_PMU_RG_GPIOF_SL_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOF_SL_POS = 16,
};

enum APP_PMU_RG_REG_IOG_LOCK_FIELD {
    APP_PMU_RG_GPIOG_LOCK_MASK = (int)0xffff,
    APP_PMU_RG_GPIOG_LOCK_POS = 0,
};

enum APP_PMU_RG_REG_IOG_PU0_PU1_FIELD {
    APP_PMU_RG_GPIOG_PU0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOG_PU0_POS = 0,
    APP_PMU_RG_GPIOG_PU1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOG_PU1_POS = 16,
};

enum APP_PMU_RG_REG_IOG_PU2_PD_FIELD {
    APP_PMU_RG_GPIOG_PU2_MASK = (int)0xffff,
    APP_PMU_RG_GPIOG_PU2_POS = 0,
    APP_PMU_RG_GPIOG_PD_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOG_PD_POS = 16,
};

enum APP_PMU_RG_REG_IOG_REN_FIELD {
    APP_PMU_RG_GPIOG_REN0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOG_REN0_POS = 0,
    APP_PMU_RG_GPIOG_REN1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOG_REN1_POS = 16,
};

enum APP_PMU_RG_REG_IOG_DS0_DS1_FIELD {
    APP_PMU_RG_GPIOG_DS0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOG_DS0_POS = 0,
    APP_PMU_RG_GPIOG_DS1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOG_DS1_POS = 16,
};

enum APP_PMU_RG_REG_IOG_DS2_AE_FIELD {
    APP_PMU_RG_GPIOG_DS2_MASK = (int)0xffff,
    APP_PMU_RG_GPIOG_DS2_POS = 0,
    APP_PMU_RG_GPIOG_AE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOG_AE_POS = 16,
};

enum APP_PMU_RG_REG_IOG_FIR_ODE_FIELD {
    APP_PMU_RG_GPIOG_FIR_MASK = (int)0xffff,
    APP_PMU_RG_GPIOG_FIR_POS = 0,
    APP_PMU_RG_GPIOG_ODE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOG_ODE_POS = 16,
};

enum APP_PMU_RG_REG_IOG_ST_SL_FIELD {
    APP_PMU_RG_GPIOG_ST_MASK = (int)0xffff,
    APP_PMU_RG_GPIOG_ST_POS = 0,
    APP_PMU_RG_GPIOG_SL_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOG_SL_POS = 16,
};

enum APP_PMU_RG_REG_IOH_LOCK_FIELD {
    APP_PMU_RG_GPIOH_LOCK_MASK = (int)0xffff,
    APP_PMU_RG_GPIOH_LOCK_POS = 0,
};

enum APP_PMU_RG_REG_IOH_PU0_PU1_FIELD {
    APP_PMU_RG_GPIOH_PU0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOH_PU0_POS = 0,
    APP_PMU_RG_GPIOH_PU1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOH_PU1_POS = 16,
};

enum APP_PMU_RG_REG_IOH_PU2_PD_FIELD {
    APP_PMU_RG_GPIOH_PU2_MASK = (int)0xffff,
    APP_PMU_RG_GPIOH_PU2_POS = 0,
    APP_PMU_RG_GPIOH_PD_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOH_PD_POS = 16,
};

enum APP_PMU_RG_REG_IOH_REN_FIELD {
    APP_PMU_RG_GPIOH_REN0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOH_REN0_POS = 0,
    APP_PMU_RG_GPIOH_REN1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOH_REN1_POS = 16,
};

enum APP_PMU_RG_REG_IOH_DS0_DS1_FIELD {
    APP_PMU_RG_GPIOH_DS0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOH_DS0_POS = 0,
    APP_PMU_RG_GPIOH_DS1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOH_DS1_POS = 16,
};

enum APP_PMU_RG_REG_IOH_DS2_AE_FIELD {
    APP_PMU_RG_GPIOH_DS2_MASK = (int)0xffff,
    APP_PMU_RG_GPIOH_DS2_POS = 0,
    APP_PMU_RG_GPIOH_AE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOH_AE_POS = 16,
};

enum APP_PMU_RG_REG_IOH_FIR_ODE_FIELD {
    APP_PMU_RG_GPIOH_FIR_MASK = (int)0xffff,
    APP_PMU_RG_GPIOH_FIR_POS = 0,
    APP_PMU_RG_GPIOH_ODE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOH_ODE_POS = 16,
};

enum APP_PMU_RG_REG_IOH_ST_SL_FIELD {
    APP_PMU_RG_GPIOH_ST_MASK = (int)0xffff,
    APP_PMU_RG_GPIOH_ST_POS = 0,
    APP_PMU_RG_GPIOH_SL_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOH_SL_POS = 16,
};

enum APP_PMU_RG_REG_IOI_LOCK_FIELD {
    APP_PMU_RG_GPIOI_LOCK_MASK = (int)0xffff,
    APP_PMU_RG_GPIOI_LOCK_POS = 0,
};

enum APP_PMU_RG_REG_IOI_PU0_PU1_FIELD {
    APP_PMU_RG_GPIOI_PU0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOI_PU0_POS = 0,
    APP_PMU_RG_GPIOI_PU1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOI_PU1_POS = 16,
};

enum APP_PMU_RG_REG_IOI_PU2_PD_FIELD {
    APP_PMU_RG_GPIOI_PU2_MASK = (int)0xffff,
    APP_PMU_RG_GPIOI_PU2_POS = 0,
    APP_PMU_RG_GPIOI_PD_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOI_PD_POS = 16,
};

enum APP_PMU_RG_REG_IOI_REN_FIELD {
    APP_PMU_RG_GPIOI_REN0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOI_REN0_POS = 0,
    APP_PMU_RG_GPIOI_REN1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOI_REN1_POS = 16,
};

enum APP_PMU_RG_REG_IOI_DS0_DS1_FIELD {
    APP_PMU_RG_GPIOI_DS0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOI_DS0_POS = 0,
    APP_PMU_RG_GPIOI_DS1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOI_DS1_POS = 16,
};

enum APP_PMU_RG_REG_IOI_DS2_AE_FIELD {
    APP_PMU_RG_GPIOI_DS2_MASK = (int)0xffff,
    APP_PMU_RG_GPIOI_DS2_POS = 0,
    APP_PMU_RG_GPIOI_AE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOI_AE_POS = 16,
};

enum APP_PMU_RG_REG_IOI_FIR_ODE_FIELD {
    APP_PMU_RG_GPIOI_FIR_MASK = (int)0xffff,
    APP_PMU_RG_GPIOI_FIR_POS = 0,
    APP_PMU_RG_GPIOI_ODE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOI_ODE_POS = 16,
};

enum APP_PMU_RG_REG_IOI_ST_SL_FIELD {
    APP_PMU_RG_GPIOI_ST_MASK = (int)0xffff,
    APP_PMU_RG_GPIOI_ST_POS = 0,
    APP_PMU_RG_GPIOI_SL_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOI_SL_POS = 16,
};

enum APP_PMU_RG_REG_IOJ_LOCK_FIELD {
    APP_PMU_RG_GPIOJ_LOCK_MASK = (int)0xffff,
    APP_PMU_RG_GPIOJ_LOCK_POS = 0,
};

enum APP_PMU_RG_REG_IOJ_PU0_PU1_FIELD {
    APP_PMU_RG_GPIOJ_PU0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOJ_PU0_POS = 0,
    APP_PMU_RG_GPIOJ_PU1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOJ_PU1_POS = 16,
};

enum APP_PMU_RG_REG_IOJ_PU2_PD_FIELD {
    APP_PMU_RG_GPIOJ_PU2_MASK = (int)0xffff,
    APP_PMU_RG_GPIOJ_PU2_POS = 0,
    APP_PMU_RG_GPIOJ_PD_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOJ_PD_POS = 16,
};

enum APP_PMU_RG_REG_IOJ_REN_FIELD {
    APP_PMU_RG_GPIOJ_REN0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOJ_REN0_POS = 0,
    APP_PMU_RG_GPIOJ_REN1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOJ_REN1_POS = 16,
};

enum APP_PMU_RG_REG_IOJ_DS0_DS1_FIELD {
    APP_PMU_RG_GPIOJ_DS0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOJ_DS0_POS = 0,
    APP_PMU_RG_GPIOJ_DS1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOJ_DS1_POS = 16,
};

enum APP_PMU_RG_REG_IOJ_DS2_AE_FIELD {
    APP_PMU_RG_GPIOJ_DS2_MASK = (int)0xffff,
    APP_PMU_RG_GPIOJ_DS2_POS = 0,
    APP_PMU_RG_GPIOJ_AE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOJ_AE_POS = 16,
};

enum APP_PMU_RG_REG_IOJ_FIR_ODE_FIELD {
    APP_PMU_RG_GPIOJ_FIR_MASK = (int)0xffff,
    APP_PMU_RG_GPIOJ_FIR_POS = 0,
    APP_PMU_RG_GPIOJ_ODE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOJ_ODE_POS = 16,
};

enum APP_PMU_RG_REG_IOJ_ST_SL_FIELD {
    APP_PMU_RG_GPIOJ_ST_MASK = (int)0xffff,
    APP_PMU_RG_GPIOJ_ST_POS = 0,
    APP_PMU_RG_GPIOJ_SL_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOJ_SL_POS = 16,
};

enum APP_PMU_RG_REG_IOK_LOCK_FIELD {
    APP_PMU_RG_GPIOK_LOCK_MASK = (int)0xffff,
    APP_PMU_RG_GPIOK_LOCK_POS = 0,
};

enum APP_PMU_RG_REG_IOK_PU0_PU1_FIELD {
    APP_PMU_RG_GPIOK_PU0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOK_PU0_POS = 0,
    APP_PMU_RG_GPIOK_PU1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOK_PU1_POS = 16,
};

enum APP_PMU_RG_REG_IOK_PU2_PD_FIELD {
    APP_PMU_RG_GPIOK_PU2_MASK = (int)0xffff,
    APP_PMU_RG_GPIOK_PU2_POS = 0,
    APP_PMU_RG_GPIOK_PD_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOK_PD_POS = 16,
};

enum APP_PMU_RG_REG_IOK_REN_FIELD {
    APP_PMU_RG_GPIOK_REN0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOK_REN0_POS = 0,
    APP_PMU_RG_GPIOK_REN1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOK_REN1_POS = 16,
};

enum APP_PMU_RG_REG_IOK_DS0_DS1_FIELD {
    APP_PMU_RG_GPIOK_DS0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOK_DS0_POS = 0,
    APP_PMU_RG_GPIOK_DS1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOK_DS1_POS = 16,
};

enum APP_PMU_RG_REG_IOK_DS2_AE_FIELD {
    APP_PMU_RG_GPIOK_DS2_MASK = (int)0xffff,
    APP_PMU_RG_GPIOK_DS2_POS = 0,
    APP_PMU_RG_GPIOK_AE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOK_AE_POS = 16,
};

enum APP_PMU_RG_REG_IOK_FIR_ODE_FIELD {
    APP_PMU_RG_GPIOK_FIR_MASK = (int)0xffff,
    APP_PMU_RG_GPIOK_FIR_POS = 0,
    APP_PMU_RG_GPIOK_ODE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOK_ODE_POS = 16,
};

enum APP_PMU_RG_REG_IOK_ST_SL_FIELD {
    APP_PMU_RG_GPIOK_ST_MASK = (int)0xffff,
    APP_PMU_RG_GPIOK_ST_POS = 0,
    APP_PMU_RG_GPIOK_SL_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOK_SL_POS = 16,
};

enum APP_PMU_RG_REG_IOM_LOCK_FIELD {
    APP_PMU_RG_GPIOM_LOCK_MASK = (int)0xffff,
    APP_PMU_RG_GPIOM_LOCK_POS = 0,
};

enum APP_PMU_RG_REG_IOM_PU0_PU1_FIELD {
    APP_PMU_RG_GPIOM_PU0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOM_PU0_POS = 0,
    APP_PMU_RG_GPIOM_PU1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOM_PU1_POS = 16,
};

enum APP_PMU_RG_REG_IOM_PU2_PD_FIELD {
    APP_PMU_RG_GPIOM_PU2_MASK = (int)0xffff,
    APP_PMU_RG_GPIOM_PU2_POS = 0,
    APP_PMU_RG_GPIOM_PD_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOM_PD_POS = 16,
};

enum APP_PMU_RG_REG_IOM_REN_FIELD {
    APP_PMU_RG_GPIOM_REN0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOM_REN0_POS = 0,
    APP_PMU_RG_GPIOM_REN1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOM_REN1_POS = 16,
};

enum APP_PMU_RG_REG_IOM_DS0_DS1_FIELD {
    APP_PMU_RG_GPIOM_DS0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOM_DS0_POS = 0,
    APP_PMU_RG_GPIOM_DS1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOM_DS1_POS = 16,
};

enum APP_PMU_RG_REG_IOM_DS2_AE_FIELD {
    APP_PMU_RG_GPIOM_DS2_MASK = (int)0xffff,
    APP_PMU_RG_GPIOM_DS2_POS = 0,
    APP_PMU_RG_GPIOM_AE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOM_AE_POS = 16,
};

enum APP_PMU_RG_REG_IOM_FIR_ODE_FIELD {
    APP_PMU_RG_GPIOM_FIR_MASK = (int)0xffff,
    APP_PMU_RG_GPIOM_FIR_POS = 0,
    APP_PMU_RG_GPIOM_ODE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOM_ODE_POS = 16,
};

enum APP_PMU_RG_REG_IOM_ST_SL_FIELD {
    APP_PMU_RG_GPIOM_ST_MASK = (int)0xffff,
    APP_PMU_RG_GPIOM_ST_POS = 0,
    APP_PMU_RG_GPIOM_SL_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOM_SL_POS = 16,
};

enum APP_PMU_RG_REG_ION_LOCK_FIELD {
    APP_PMU_RG_GPION_LOCK_MASK = (int)0xffff,
    APP_PMU_RG_GPION_LOCK_POS = 0,
};

enum APP_PMU_RG_REG_ION_PU0_PU1_FIELD {
    APP_PMU_RG_GPION_PU0_MASK = (int)0xffff,
    APP_PMU_RG_GPION_PU0_POS = 0,
    APP_PMU_RG_GPION_PU1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPION_PU1_POS = 16,
};

enum APP_PMU_RG_REG_ION_PU2_PD_FIELD {
    APP_PMU_RG_GPION_PU2_MASK = (int)0xffff,
    APP_PMU_RG_GPION_PU2_POS = 0,
    APP_PMU_RG_GPION_PD_MASK = (int)0xffff0000,
    APP_PMU_RG_GPION_PD_POS = 16,
};

enum APP_PMU_RG_REG_ION_REN_FIELD {
    APP_PMU_RG_GPION_REN0_MASK = (int)0xffff,
    APP_PMU_RG_GPION_REN0_POS = 0,
    APP_PMU_RG_GPION_REN1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPION_REN1_POS = 16,
};

enum APP_PMU_RG_REG_ION_DS0_DS1_FIELD {
    APP_PMU_RG_GPION_DS0_MASK = (int)0xffff,
    APP_PMU_RG_GPION_DS0_POS = 0,
    APP_PMU_RG_GPION_DS1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPION_DS1_POS = 16,
};

enum APP_PMU_RG_REG_ION_DS2_AE_FIELD {
    APP_PMU_RG_GPION_DS2_MASK = (int)0xffff,
    APP_PMU_RG_GPION_DS2_POS = 0,
    APP_PMU_RG_GPION_AE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPION_AE_POS = 16,
};

enum APP_PMU_RG_REG_ION_FIR_ODE_FIELD {
    APP_PMU_RG_GPION_FIR_MASK = (int)0xffff,
    APP_PMU_RG_GPION_FIR_POS = 0,
    APP_PMU_RG_GPION_ODE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPION_ODE_POS = 16,
};

enum APP_PMU_RG_REG_ION_ST_SL_FIELD {
    APP_PMU_RG_GPION_ST_MASK = (int)0xffff,
    APP_PMU_RG_GPION_ST_POS = 0,
    APP_PMU_RG_GPION_SL_MASK = (int)0xffff0000,
    APP_PMU_RG_GPION_SL_POS = 16,
};

enum APP_PMU_RG_REG_IOQ_LOCK_FIELD {
    APP_PMU_RG_GPIOQ_LOCK_MASK = (int)0xffff,
    APP_PMU_RG_GPIOQ_LOCK_POS = 0,
};

enum APP_PMU_RG_REG_IOQ_PU0_PU1_FIELD {
    APP_PMU_RG_GPIOQ_PU0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOQ_PU0_POS = 0,
    APP_PMU_RG_GPIOQ_PU1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOQ_PU1_POS = 16,
};

enum APP_PMU_RG_REG_IOQ_PU2_PD_FIELD {
    APP_PMU_RG_GPIOQ_PU2_MASK = (int)0xffff,
    APP_PMU_RG_GPIOQ_PU2_POS = 0,
    APP_PMU_RG_GPIOQ_PD_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOQ_PD_POS = 16,
};

enum APP_PMU_RG_REG_IOQ_REN_FIELD {
    APP_PMU_RG_GPIOQ_REN0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOQ_REN0_POS = 0,
    APP_PMU_RG_GPIOQ_REN1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOQ_REN1_POS = 16,
};

enum APP_PMU_RG_REG_IOQ_DS0_DS1_FIELD {
    APP_PMU_RG_GPIOQ_DS0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOQ_DS0_POS = 0,
    APP_PMU_RG_GPIOQ_DS1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOQ_DS1_POS = 16,
};

enum APP_PMU_RG_REG_IOQ_DS2_AE_FIELD {
    APP_PMU_RG_GPIOQ_DS2_MASK = (int)0xffff,
    APP_PMU_RG_GPIOQ_DS2_POS = 0,
    APP_PMU_RG_GPIOQ_AE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOQ_AE_POS = 16,
};

enum APP_PMU_RG_REG_IOQ_FIR_ODE_FIELD {
    APP_PMU_RG_GPIOQ_FIR_MASK = (int)0xffff,
    APP_PMU_RG_GPIOQ_FIR_POS = 0,
    APP_PMU_RG_GPIOQ_ODE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOQ_ODE_POS = 16,
};

enum APP_PMU_RG_REG_IOQ_ST_SL_FIELD {
    APP_PMU_RG_GPIOQ_ST_MASK = (int)0xffff,
    APP_PMU_RG_GPIOQ_ST_POS = 0,
    APP_PMU_RG_GPIOQ_SL_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOQ_SL_POS = 16,
};

enum APP_PMU_RG_REG_IOT_LOCK_FIELD {
    APP_PMU_RG_GPIOT_LOCK_MASK = (int)0xffff,
    APP_PMU_RG_GPIOT_LOCK_POS = 0,
};

enum APP_PMU_RG_REG_IOT_PU0_PU1_FIELD {
    APP_PMU_RG_GPIOT_PU0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOT_PU0_POS = 0,
    APP_PMU_RG_GPIOT_PU1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOT_PU1_POS = 16,
};

enum APP_PMU_RG_REG_IOT_PU2_PD_FIELD {
    APP_PMU_RG_GPIOT_PU2_MASK = (int)0xffff,
    APP_PMU_RG_GPIOT_PU2_POS = 0,
    APP_PMU_RG_GPIOT_PD_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOT_PD_POS = 16,
};

enum APP_PMU_RG_REG_IOT_REN_FIELD {
    APP_PMU_RG_GPIOT_REN0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOT_REN0_POS = 0,
    APP_PMU_RG_GPIOT_REN1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOT_REN1_POS = 16,
};

enum APP_PMU_RG_REG_IOT_DS0_DS1_FIELD {
    APP_PMU_RG_GPIOT_DS0_MASK = (int)0xffff,
    APP_PMU_RG_GPIOT_DS0_POS = 0,
    APP_PMU_RG_GPIOT_DS1_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOT_DS1_POS = 16,
};

enum APP_PMU_RG_REG_IOT_DS2_AE_FIELD {
    APP_PMU_RG_GPIOT_DS2_MASK = (int)0xffff,
    APP_PMU_RG_GPIOT_DS2_POS = 0,
    APP_PMU_RG_GPIOT_AE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOT_AE_POS = 16,
};

enum APP_PMU_RG_REG_IOT_FIR_ODE_FIELD {
    APP_PMU_RG_GPIOT_FIR_MASK = (int)0xffff,
    APP_PMU_RG_GPIOT_FIR_POS = 0,
    APP_PMU_RG_GPIOT_ODE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOT_ODE_POS = 16,
};

enum APP_PMU_RG_REG_IOT_ST_SL_FIELD {
    APP_PMU_RG_GPIOT_ST_MASK = (int)0xffff,
    APP_PMU_RG_GPIOT_ST_POS = 0,
    APP_PMU_RG_GPIOT_SL_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOT_SL_POS = 16,
};

enum APP_PMU_RG_REG_IOA_DIN_OE_FIELD {
    APP_PMU_RG_GPIOA_DIN_MASK = (int)0xffff,
    APP_PMU_RG_GPIOA_DIN_POS = 0,
    APP_PMU_RG_GPIOA_OE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOA_OE_POS = 16,
};

enum APP_PMU_RG_REG_IOA_DOT_FIELD {
    APP_PMU_RG_GPIOA_DOT_MASK = (int)0xffff,
    APP_PMU_RG_GPIOA_DOT_POS = 0,
};

enum APP_PMU_RG_REG_IOB_DIN_OE_FIELD {
    APP_PMU_RG_GPIOB_DIN_MASK = (int)0xffff,
    APP_PMU_RG_GPIOB_DIN_POS = 0,
    APP_PMU_RG_GPIOB_OE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOB_OE_POS = 16,
};

enum APP_PMU_RG_REG_IOB_DOT_FIELD {
    APP_PMU_RG_GPIOB_DOT_MASK = (int)0xffff,
    APP_PMU_RG_GPIOB_DOT_POS = 0,
};

enum APP_PMU_RG_REG_IOC_DIN_OE_FIELD {
    APP_PMU_RG_GPIOC_DIN_MASK = (int)0xffff,
    APP_PMU_RG_GPIOC_DIN_POS = 0,
    APP_PMU_RG_GPIOC_OE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOC_OE_POS = 16,
};

enum APP_PMU_RG_REG_IOC_DOT_FIELD {
    APP_PMU_RG_GPIOC_DOT_MASK = (int)0xffff,
    APP_PMU_RG_GPIOC_DOT_POS = 0,
};

enum APP_PMU_RG_REG_IOD_DIN_OE_FIELD {
    APP_PMU_RG_GPIOD_DIN_MASK = (int)0xffff,
    APP_PMU_RG_GPIOD_DIN_POS = 0,
    APP_PMU_RG_GPIOD_OE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOD_OE_POS = 16,
};

enum APP_PMU_RG_REG_IOD_DOT_FIELD {
    APP_PMU_RG_GPIOD_DOT_MASK = (int)0xffff,
    APP_PMU_RG_GPIOD_DOT_POS = 0,
};

enum APP_PMU_RG_REG_IOE_DIN_OE_FIELD {
    APP_PMU_RG_GPIOE_DIN_MASK = (int)0xffff,
    APP_PMU_RG_GPIOE_DIN_POS = 0,
    APP_PMU_RG_GPIOE_OE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOE_OE_POS = 16,
};

enum APP_PMU_RG_REG_IOE_DOT_FIELD {
    APP_PMU_RG_GPIOE_DOT_MASK = (int)0xffff,
    APP_PMU_RG_GPIOE_DOT_POS = 0,
};

enum APP_PMU_RG_REG_IOF_DIN_OE_FIELD {
    APP_PMU_RG_GPIOF_DIN_MASK = (int)0xffff,
    APP_PMU_RG_GPIOF_DIN_POS = 0,
    APP_PMU_RG_GPIOF_OE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOF_OE_POS = 16,
};

enum APP_PMU_RG_REG_IOF_DOT_FIELD {
    APP_PMU_RG_GPIOF_DOT_MASK = (int)0xffff,
    APP_PMU_RG_GPIOF_DOT_POS = 0,
};

enum APP_PMU_RG_REG_IOG_DIN_OE_FIELD {
    APP_PMU_RG_GPIOG_DIN_MASK = (int)0xffff,
    APP_PMU_RG_GPIOG_DIN_POS = 0,
    APP_PMU_RG_GPIOG_OE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOG_OE_POS = 16,
};

enum APP_PMU_RG_REG_IOG_DOT_FIELD {
    APP_PMU_RG_GPIOG_DOT_MASK = (int)0xffff,
    APP_PMU_RG_GPIOG_DOT_POS = 0,
};

enum APP_PMU_RG_REG_IOH_DIN_OE_FIELD {
    APP_PMU_RG_GPIOH_DIN_MASK = (int)0xffff,
    APP_PMU_RG_GPIOH_DIN_POS = 0,
    APP_PMU_RG_GPIOH_OE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOH_OE_POS = 16,
};

enum APP_PMU_RG_REG_IOH_DOT_FIELD {
    APP_PMU_RG_GPIOH_DOT_MASK = (int)0xffff,
    APP_PMU_RG_GPIOH_DOT_POS = 0,
};

enum APP_PMU_RG_REG_IOI_DIN_OE_FIELD {
    APP_PMU_RG_GPIOI_DIN_MASK = (int)0xffff,
    APP_PMU_RG_GPIOI_DIN_POS = 0,
    APP_PMU_RG_GPIOI_OE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOI_OE_POS = 16,
};

enum APP_PMU_RG_REG_IOI_DOT_FIELD {
    APP_PMU_RG_GPIOI_DOT_MASK = (int)0xffff,
    APP_PMU_RG_GPIOI_DOT_POS = 0,
};

enum APP_PMU_RG_REG_IOJ_DIN_OE_FIELD {
    APP_PMU_RG_GPIOJ_DIN_MASK = (int)0xffff,
    APP_PMU_RG_GPIOJ_DIN_POS = 0,
    APP_PMU_RG_GPIOJ_OE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOJ_OE_POS = 16,
};

enum APP_PMU_RG_REG_IOJ_DOT_FIELD {
    APP_PMU_RG_GPIOJ_DOT_MASK = (int)0xffff,
    APP_PMU_RG_GPIOJ_DOT_POS = 0,
};

enum APP_PMU_RG_REG_IOK_DIN_OE_FIELD {
    APP_PMU_RG_GPIOK_DIN_MASK = (int)0xffff,
    APP_PMU_RG_GPIOK_DIN_POS = 0,
    APP_PMU_RG_GPIOK_OE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOK_OE_POS = 16,
};

enum APP_PMU_RG_REG_IOK_DOT_FIELD {
    APP_PMU_RG_GPIOK_DOT_MASK = (int)0xffff,
    APP_PMU_RG_GPIOK_DOT_POS = 0,
};

enum APP_PMU_RG_REG_IOM_DIN_OE_FIELD {
    APP_PMU_RG_GPIOM_DIN_MASK = (int)0xffff,
    APP_PMU_RG_GPIOM_DIN_POS = 0,
    APP_PMU_RG_GPIOM_OE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOM_OE_POS = 16,
};

enum APP_PMU_RG_REG_IOM_DOT_FIELD {
    APP_PMU_RG_GPIOM_DOT_MASK = (int)0xffff,
    APP_PMU_RG_GPIOM_DOT_POS = 0,
};

enum APP_PMU_RG_REG_ION_DIN_OE_FIELD {
    APP_PMU_RG_GPION_DIN_MASK = (int)0xffff,
    APP_PMU_RG_GPION_DIN_POS = 0,
    APP_PMU_RG_GPION_OE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPION_OE_POS = 16,
};

enum APP_PMU_RG_REG_ION_DOT_FIELD {
    APP_PMU_RG_GPION_DOT_MASK = (int)0xffff,
    APP_PMU_RG_GPION_DOT_POS = 0,
};

enum APP_PMU_RG_REG_IOQ_DIN_OE_FIELD {
    APP_PMU_RG_GPIOQ_DIN_MASK = (int)0xffff,
    APP_PMU_RG_GPIOQ_DIN_POS = 0,
    APP_PMU_RG_GPIOQ_OE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOQ_OE_POS = 16,
};

enum APP_PMU_RG_REG_IOQ_DOT_FIELD {
    APP_PMU_RG_GPIOQ_DOT_MASK = (int)0xffff,
    APP_PMU_RG_GPIOQ_DOT_POS = 0,
};

enum APP_PMU_RG_REG_IOT_DIN_OE_FIELD {
    APP_PMU_RG_GPIOT_DIN_MASK = (int)0xffff,
    APP_PMU_RG_GPIOT_DIN_POS = 0,
    APP_PMU_RG_GPIOT_OE_MASK = (int)0xffff0000,
    APP_PMU_RG_GPIOT_OE_POS = 16,
};

enum APP_PMU_RG_REG_IOT_DOT_FIELD {
    APP_PMU_RG_GPIOT_DOT_MASK = (int)0xffff,
    APP_PMU_RG_GPIOT_DOT_POS = 0,
};

enum APP_PMU_RG_REG_MODE_PAD_LOCK_ST_FIELD {
    APP_PMU_RG_MODE_PAD_LOCK_MASK = (int)0xffff,
    APP_PMU_RG_MODE_PAD_LOCK_POS = 0,
    APP_PMU_RG_MODE_PAD_ST_MASK = (int)0xffff0000,
    APP_PMU_RG_MODE_PAD_ST_POS = 16,
};

enum APP_PMU_RG_REG_MODE_PAD_PU_PD_FIELD {
    APP_PMU_RG_MODE_PAD_PU_MASK = (int)0xffff,
    APP_PMU_RG_MODE_PAD_PU_POS = 0,
    APP_PMU_RG_MODE_PAD_PD_MASK = (int)0xffff0000,
    APP_PMU_RG_MODE_PAD_PD_POS = 16,
};

enum APP_PMU_RG_REG_MODE_PAD_REN_DS0_FIELD {
    APP_PMU_RG_MODE_PAD_REN_MASK = (int)0xffff,
    APP_PMU_RG_MODE_PAD_REN_POS = 0,
    APP_PMU_RG_MODE_PAD_DS0_MASK = (int)0xffff0000,
    APP_PMU_RG_MODE_PAD_DS0_POS = 16,
};

enum APP_PMU_RG_REG_MODE_PAD_DS1_FIR_FIELD {
    APP_PMU_RG_MODE_PAD_DS1_MASK = (int)0xffff,
    APP_PMU_RG_MODE_PAD_DS1_POS = 0,
    APP_PMU_RG_MODE_PAD_FIR_MASK = (int)0xffff0000,
    APP_PMU_RG_MODE_PAD_FIR_POS = 16,
};

#endif
