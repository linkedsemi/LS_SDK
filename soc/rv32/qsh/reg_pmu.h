#ifndef REG_PMU_RG_TYPE_H_
#define REG_PMU_RG_TYPE_H_
#include <stdint.h>
#include "reg_base_addr.h"

#define PMU ((reg_pmu_rg_t *)QSH_PMU_RG_ADDR)

typedef struct 
{
    volatile uint32_t LOCK;
    volatile uint32_t DOT;
    volatile uint32_t PUPD;
    volatile uint32_t IEN_OD;
    volatile uint32_t DS;
    volatile uint32_t AE;
    volatile uint32_t OE_FIR;
    volatile uint32_t DIN;
} pmu_io_reg_t;

typedef struct
{
    volatile uint32_t SFT_CTRL0[4]; //0x0
    volatile uint32_t MISC_CTRL0; //0x10
    volatile uint32_t TRIM0; //0x14
    volatile uint32_t ANA_PMU_CTRL; //0x18
    volatile uint32_t WKUP_CTRL; //0x1c
    volatile uint32_t WKUP_TIM0; //0x20
    volatile uint32_t WKUP_TIM1; //0x24
    volatile uint32_t RST_SFT; //0x28
    volatile uint32_t CLKG_SRST; //0x2c
    volatile uint32_t PMU_SET_VAL; //0x30
    volatile uint32_t PWR_CTRL; //0x34
    volatile uint32_t SRAM_LOCK; //0x38
    volatile uint32_t PMU_STATUS; //0x3c
    volatile uint32_t TEST_STATUS; //0x40
    volatile uint32_t CASEOPEN_CTRL; //0x44
    volatile uint32_t RESERVED0[14];

    volatile uint32_t GPIO_INTR_MSK[15]; //0x80
    volatile uint32_t RESERVED1[1];
    volatile uint32_t GPIO_INTR_CLR[15]; //0xc0
    volatile uint32_t RESERVED2[1];
    volatile uint32_t GPIO_INTR_STT[15]; //0x100
    volatile uint32_t RESERVED3[1];
    volatile uint32_t GPIO_INTR_RAW[15]; //0x140
    volatile uint32_t RESERVED4[1];

    pmu_io_reg_t IO[15];
} reg_pmu_rg_t;

#if 0
typedef struct
{
    volatile uint32_t SFT_CTRL00; //0x0
    volatile uint32_t SFT_CTRL01; //0x4
    volatile uint32_t SFT_CTRL02; //0x8
    volatile uint32_t SFT_CTRL03; //0xc
    volatile uint32_t MISC_CTRL0; //0x10
    volatile uint32_t TRIM0; //0x14
    volatile uint32_t ANA_PMU_CTRL; //0x18
    volatile uint32_t WKUP_CTRL; //0x1c
    volatile uint32_t WKUP_TIM0; //0x20
    volatile uint32_t WKUP_TIM1; //0x24
    volatile uint32_t RST_SFT; //0x28
    volatile uint32_t CLKG_SRST; //0x2c
    volatile uint32_t PMU_SET_VAL; //0x30
    volatile uint32_t PWR_CTRL; //0x34
    volatile uint32_t SRAM_LOCK; //0x38
    volatile uint32_t PMU_STATUS; //0x3c
    volatile uint32_t TEST_STATUS; //0x40
    volatile uint32_t CASEOPEN_CTRL; //0x44
    volatile uint32_t RESERVED0[14];
    volatile uint32_t GPIOA_INTR_MSK; //0x80
    volatile uint32_t GPIOB_INTR_MSK; //0x84
    volatile uint32_t GPIOC_INTR_MSK; //0x88
    volatile uint32_t GPIOD_INTR_MSK; //0x8c
    volatile uint32_t GPIOE_INTR_MSK; //0x90
    volatile uint32_t GPIOF_INTR_MSK; //0x94
    volatile uint32_t GPIOG_INTR_MSK; //0x98
    volatile uint32_t GPIOH_INTR_MSK; //0x9c
    volatile uint32_t GPIOI_INTR_MSK; //0xa0
    volatile uint32_t GPIOJ_INTR_MSK; //0xa4
    volatile uint32_t GPIOK_INTR_MSK; //0xa8
    volatile uint32_t GPIOM_INTR_MSK; //0xac
    volatile uint32_t GPION_INTR_MSK; //0xb0
    volatile uint32_t GPIOQ_INTR_MSK; //0xb4
    volatile uint32_t GPIOT_INTR_MSK; //0xb8
    volatile uint32_t RESERVED1[1];
    volatile uint32_t GPIOA_INTR_CLR; //0xc0
    volatile uint32_t GPIOB_INTR_CLR; //0xc4
    volatile uint32_t GPIOC_INTR_CLR; //0xc8
    volatile uint32_t GPIOD_INTR_CLR; //0xcc
    volatile uint32_t GPIOE_INTR_CLR; //0xd0
    volatile uint32_t GPIOF_INTR_CLR; //0xd4
    volatile uint32_t GPIOG_INTR_CLR; //0xd8
    volatile uint32_t GPIOH_INTR_CLR; //0xdc
    volatile uint32_t GPIOI_INTR_CLR; //0xe0
    volatile uint32_t GPIOJ_INTR_CLR; //0xe4
    volatile uint32_t GPIOK_INTR_CLR; //0xe8
    volatile uint32_t GPIOM_INTR_CLR; //0xec
    volatile uint32_t GPION_INTR_CLR; //0xf0
    volatile uint32_t GPIOQ_INTR_CLR; //0xf4
    volatile uint32_t GPIOT_INTR_CLR; //0xf8
    volatile uint32_t RESERVED2[1];
    volatile uint32_t GPIOA_INTR_STT; //0x100
    volatile uint32_t GPIOB_INTR_STT; //0x104
    volatile uint32_t GPIOC_INTR_STT; //0x108
    volatile uint32_t GPIOD_INTR_STT; //0x10c
    volatile uint32_t GPIOE_INTR_STT; //0x110
    volatile uint32_t GPIOF_INTR_STT; //0x114
    volatile uint32_t GPIOG_INTR_STT; //0x118
    volatile uint32_t GPIOH_INTR_STT; //0x11c
    volatile uint32_t GPIOI_INTR_STT; //0x120
    volatile uint32_t GPIOJ_INTR_STT; //0x124
    volatile uint32_t GPIOK_INTR_STT; //0x128
    volatile uint32_t GPIOM_INTR_STT; //0x12c
    volatile uint32_t GPION_INTR_STT; //0x130
    volatile uint32_t GPIOQ_INTR_STT; //0x134
    volatile uint32_t GPIOT_INTR_STT; //0x138
    volatile uint32_t RESERVED3[1];
    volatile uint32_t GPIOA_INTR_RAW; //0x140
    volatile uint32_t GPIOB_INTR_RAW; //0x144
    volatile uint32_t GPIOC_INTR_RAW; //0x148
    volatile uint32_t GPIOD_INTR_RAW; //0x14c
    volatile uint32_t GPIOE_INTR_RAW; //0x150
    volatile uint32_t GPIOF_INTR_RAW; //0x154
    volatile uint32_t GPIOG_INTR_RAW; //0x158
    volatile uint32_t GPIOH_INTR_RAW; //0x15c
    volatile uint32_t GPIOI_INTR_RAW; //0x160
    volatile uint32_t GPIOJ_INTR_RAW; //0x164
    volatile uint32_t GPIOK_INTR_RAW; //0x168
    volatile uint32_t GPIOM_INTR_RAW; //0x16c
    volatile uint32_t GPION_INTR_RAW; //0x170
    volatile uint32_t GPIOQ_INTR_RAW; //0x174
    volatile uint32_t GPIOT_INTR_RAW; //0x178
    volatile uint32_t RESERVED4[1];
    volatile uint32_t IOA_LVS_LOCK; //0x180
    volatile uint32_t IOA_DOT; //0x184
    volatile uint32_t IOA_PD_PU; //0x188
    volatile uint32_t IOA_REN_ODE; //0x18c
    volatile uint32_t IOA_DS1_DS2; //0x190
    volatile uint32_t IOA_AE1_AE2; //0x194
    volatile uint32_t IOA_OTE_FIR; //0x198
    volatile uint32_t IOA_HSS_DIN; //0x19c
    volatile uint32_t IOB_LVS_LOCK; //0x1a0
    volatile uint32_t IOB_DOT; //0x1a4
    volatile uint32_t IOB_PD_PU; //0x1a8
    volatile uint32_t IOB_REN_ODE; //0x1ac
    volatile uint32_t IOB_DS1_DS2; //0x1b0
    volatile uint32_t IOB_AE1_AE2; //0x1b4
    volatile uint32_t IOB_OTE_FIR; //0x1b8
    volatile uint32_t IOB_HSS_DIN; //0x1bc
    volatile uint32_t IOC_LVS_LOCK; //0x1c0
    volatile uint32_t IOC_DOT; //0x1c4
    volatile uint32_t IOC_PD_PU; //0x1c8
    volatile uint32_t IOC_REN_ODE; //0x1cc
    volatile uint32_t IOC_DS1_DS2; //0x1d0
    volatile uint32_t IOC_AE1_AE2; //0x1d4
    volatile uint32_t IOC_OTE_FIR; //0x1d8
    volatile uint32_t IOC_HSS_DIN; //0x1dc
    volatile uint32_t IOD_LVS_LOCK; //0x1e0
    volatile uint32_t IOD_DOT; //0x1e4
    volatile uint32_t IOD_PD_PU; //0x1e8
    volatile uint32_t IOD_REN_ODE; //0x1ec
    volatile uint32_t IOD_DS1_DS2; //0x1f0
    volatile uint32_t IOD_AE1_AE2; //0x1f4
    volatile uint32_t IOD_OTE_FIR; //0x1f8
    volatile uint32_t IOD_HSS_DIN; //0x1fc
    volatile uint32_t IOE_LVS_LOCK; //0x200
    volatile uint32_t IOE_DOT; //0x204
    volatile uint32_t IOE_PD_PU; //0x208
    volatile uint32_t IOE_REN_ODE; //0x20c
    volatile uint32_t IOE_DS1_DS2; //0x210
    volatile uint32_t IOE_AE1_AE2; //0x214
    volatile uint32_t IOE_OTE_FIR; //0x218
    volatile uint32_t IOE_HSS_DIN; //0x21c
    volatile uint32_t IOF_LVS_LOCK; //0x220
    volatile uint32_t IOF_DOT; //0x224
    volatile uint32_t IOF_PD_PU; //0x228
    volatile uint32_t IOF_REN_ODE; //0x22c
    volatile uint32_t IOF_DS1_DS2; //0x230
    volatile uint32_t IOF_AE1_AE2; //0x234
    volatile uint32_t IOF_OTE_FIR; //0x238
    volatile uint32_t IOF_HSS_DIN; //0x23c
    volatile uint32_t IOG_LVS_LOCK; //0x240
    volatile uint32_t IOG_DOT; //0x244
    volatile uint32_t IOG_PD_PU; //0x248
    volatile uint32_t IOG_REN_ODE; //0x24c
    volatile uint32_t IOG_DS1_DS2; //0x250
    volatile uint32_t IOG_AE1_AE2; //0x254
    volatile uint32_t IOG_OTE_FIR; //0x258
    volatile uint32_t IOG_HSS_DIN; //0x25c
    volatile uint32_t IOH_LVS_LOCK; //0x260
    volatile uint32_t IOH_DOT; //0x264
    volatile uint32_t IOH_PD_PU; //0x268
    volatile uint32_t IOH_REN_ODE; //0x26c
    volatile uint32_t IOH_DS1_DS2; //0x270
    volatile uint32_t IOH_AE1_AE2; //0x274
    volatile uint32_t IOH_OTE_FIR; //0x278
    volatile uint32_t IOH_HSS_DIN; //0x27c
    volatile uint32_t IOI_LVS_LOCK; //0x280
    volatile uint32_t IOI_DOT; //0x284
    volatile uint32_t IOI_PD_PU; //0x288
    volatile uint32_t IOI_REN_ODE; //0x28c
    volatile uint32_t IOI_DS1_DS2; //0x290
    volatile uint32_t IOI_AE1_AE2; //0x294
    volatile uint32_t IOI_OTE_FIR; //0x298
    volatile uint32_t IOI_HSS_DIN; //0x29c
    volatile uint32_t IOJ_LVS_LOCK; //0x2a0
    volatile uint32_t IOJ_DOT; //0x2a4
    volatile uint32_t IOJ_PD_PU; //0x2a8
    volatile uint32_t IOJ_REN_ODE; //0x2ac
    volatile uint32_t IOJ_DS1_DS2; //0x2b0
    volatile uint32_t IOJ_AE1_AE2; //0x2b4
    volatile uint32_t IOJ_OTE_FIR; //0x2b8
    volatile uint32_t IOJ_HSS_DIN; //0x2bc
    volatile uint32_t IOK_LVS_LOCK; //0x2c0
    volatile uint32_t IOK_DOT; //0x2c4
    volatile uint32_t IOK_PD_PU; //0x2c8
    volatile uint32_t IOK_REN_ODE; //0x2cc
    volatile uint32_t IOK_DS1_DS2; //0x2d0
    volatile uint32_t IOK_AE1_AE2; //0x2d4
    volatile uint32_t IOK_OTE_FIR; //0x2d8
    volatile uint32_t IOK_HSS_DIN; //0x2dc
    volatile uint32_t IOM_LVS_LOCK; //0x2e0
    volatile uint32_t IOM_DOT; //0x2e4
    volatile uint32_t IOM_PD_PU; //0x2e8
    volatile uint32_t IOM_REN_ODE; //0x2ec
    volatile uint32_t IOM_DS1_DS2; //0x2f0
    volatile uint32_t IOM_AE1_AE2; //0x2f4
    volatile uint32_t IOM_OTE_FIR; //0x2f8
    volatile uint32_t IOM_HSS_DIN; //0x2fc
    volatile uint32_t ION_LVS_LOCK; //0x300
    volatile uint32_t ION_DOT; //0x304
    volatile uint32_t ION_PD_PU; //0x308
    volatile uint32_t ION_REN_ODE; //0x30c
    volatile uint32_t ION_DS1_DS2; //0x310
    volatile uint32_t ION_AE1_AE2; //0x314
    volatile uint32_t ION_OTE_FIR; //0x318
    volatile uint32_t ION_HSS_DIN; //0x31c
    volatile uint32_t IOQ_LVS_LOCK; //0x320
    volatile uint32_t IOQ_DOT; //0x324
    volatile uint32_t IOQ_PD_PU; //0x328
    volatile uint32_t IOQ_REN_ODE; //0x32c
    volatile uint32_t IOQ_DS1_DS2; //0x330
    volatile uint32_t IOQ_AE1_AE2; //0x334
    volatile uint32_t IOQ_OTE_FIR; //0x338
    volatile uint32_t IOQ_HSS_DIN; //0x33c
    volatile uint32_t IOT_LVS_LOCK; //0x340
    volatile uint32_t IOT_DOT; //0x344
    volatile uint32_t IOT_PD_PU; //0x348
    volatile uint32_t IOT_REN_ODE; //0x34c
    volatile uint32_t IOT_DS1_DS2; //0x350
    volatile uint32_t IOT_AE1_AE2; //0x354
    volatile uint32_t IOT_OTE_FIR; //0x358
    volatile uint32_t IOT_HSS_DIN; //0x35c
}reg_pmu_rg_t;
#endif

enum PMU_RG_REG_SFT_CTRL00_FIELD
{
    PMU_RG_SFT_CTRL00_MASK = (int)0xffffffff,
    PMU_RG_SFT_CTRL00_POS = 0,
};

enum PMU_RG_REG_SFT_CTRL01_FIELD
{
    PMU_RG_SFT_CTRL01_MASK = (int)0xffffffff,
    PMU_RG_SFT_CTRL01_POS = 0,
};

enum PMU_RG_REG_SFT_CTRL02_FIELD
{
    PMU_RG_SFT_CTRL02_MASK = (int)0xffffffff,
    PMU_RG_SFT_CTRL02_POS = 0,
};

enum PMU_RG_REG_SFT_CTRL03_FIELD
{
    PMU_RG_SFT_CTRL03_MASK = (int)0xffffffff,
    PMU_RG_SFT_CTRL03_POS = 0,
};

enum PMU_RG_REG_MISC_CTRL0_FIELD
{
    PMU_RG_LVD33_INTR_EN_MASK = (int)0x1,
    PMU_RG_LVD33_INTR_EN_POS = 0,
    PMU_RG_LVD33_POL_MASK = (int)0x2,
    PMU_RG_LVD33_POL_POS = 1,
    PMU_RG_LVD33_INTR_CLR_MASK = (int)0x4,
    PMU_RG_LVD33_INTR_CLR_POS = 2,
    PMU_RG_PD_AMIC_MASK = (int)0x8,
    PMU_RG_PD_AMIC_POS = 3,
    PMU_RG_USB1_CID_MASK = (int)0x300,
    PMU_RG_USB1_CID_POS = 8,
    PMU_RG_USB1_PUPD_MASK = (int)0x400,
    PMU_RG_USB1_PUPD_POS = 10,
    PMU_RG_HSI_FC_EN_MASK = (int)0x800,
    PMU_RG_HSI_FC_EN_POS = 11,
    PMU_RG_LATCH_GPIO_MASK = (int)0x1000,
    PMU_RG_LATCH_GPIO_POS = 12,
    PMU_RG_PWRDN_GPIO_MASK = (int)0x2000,
    PMU_RG_PWRDN_GPIO_POS = 13,
    PMU_RG_PD_ADC12_MASK = (int)0x4000,
    PMU_RG_PD_ADC12_POS = 14,
    PMU_RG_PD_DAC12_MASK = (int)0x8000,
    PMU_RG_PD_DAC12_POS = 15,
    PMU_RG_LKRST_TIM_MASK = (int)0x3f0000,
    PMU_RG_LKRST_TIM_POS = 16,
    PMU_RG_LKRST_EN_MASK = (int)0x400000,
    PMU_RG_LKRST_EN_POS = 22,
    PMU_RG_LKRST_POL_MASK = (int)0x800000,
    PMU_RG_LKRST_POL_POS = 23,
    PMU_RG_LKRST_SEL_MASK = (int)0x1f000000,
    PMU_RG_LKRST_SEL_POS = 24,
    PMU_RG_USB2_CID_MASK = (int)0x60000000,
    PMU_RG_USB2_CID_POS = 29,
    PMU_RG_USB2_PUPD_MASK = (int)0x80000000,
    PMU_RG_USB2_PUPD_POS = 31,
};

enum PMU_RG_REG_TRIM0_FIELD
{
    PMU_RG_SPI_CODE_MASK = (int)0xfff,
    PMU_RG_SPI_CODE_POS = 0,
    PMU_RG_HSE_CTRL_MASK = (int)0x7000,
    PMU_RG_HSE_CTRL_POS = 12,
    PMU_RG_LDO_PECI_VSEL_MASK = (int)0x70000,
    PMU_RG_LDO_PECI_VSEL_POS = 16,
    PMU_RG_LDO_PECI_EN_MASK = (int)0x80000,
    PMU_RG_LDO_PECI_EN_POS = 19,
    PMU_RG_DPLL_LDO_VSEL_MASK = (int)0x700000,
    PMU_RG_DPLL_LDO_VSEL_POS = 20,
    PMU_RG_BG_TESTEN_MASK = (int)0x800000,
    PMU_RG_BG_TESTEN_POS = 23,
    PMU_RG_XO32K_CODE_MASK = (int)0x1000000,
    PMU_RG_XO32K_CODE_POS = 24,
    PMU_RG_XO32K_OE_BYP_MASK = (int)0x2000000,
    PMU_RG_XO32K_OE_BYP_POS = 25,
    PMU_RG_RCO_I_ADJ_MASK = (int)0x4000000,
    PMU_RG_RCO_I_ADJ_POS = 26,
    PMU_RG_MSI_CAL_MASK = (int)0xf0000000,
    PMU_RG_MSI_CAL_POS = 28,
};

enum PMU_RG_REG_ANA_PMU_CTRL_FIELD
{
    PMU_RG_LPLDO_TRIM_MASK = (int)0xf,
    PMU_RG_LPLDO_TRIM_POS = 0,
    PMU_RG_HPLDO_TRIM_MASK = (int)0xf0,
    PMU_RG_HPLDO_TRIM_POS = 4,
    PMU_RG_BG_CTRL_MASK = (int)0xfff00,
    PMU_RG_BG_CTRL_POS = 8,
    PMU_RG_BOR_CTRL_MASK = (int)0xf00000,
    PMU_RG_BOR_CTRL_POS = 20,
    PMU_RG_LVD33_CTRL_MASK = (int)0x1f000000,
    PMU_RG_LVD33_CTRL_POS = 24,
    PMU_RG_BATDET_CTRL_MASK = (int)0xe0000000,
    PMU_RG_BATDET_CTRL_POS = 29,
};

enum PMU_RG_REG_WKUP_CTRL_FIELD
{
    PMU_RG_WKUP_MSK_MASK = (int)0x7f,
    PMU_RG_WKUP_MSK_POS = 0,
    PMU_RG_SWD_IO_WKUP_EN_MASK = (int)0x10000,
    PMU_RG_SWD_IO_WKUP_EN_POS = 16,
    PMU_RG_WKUP0_SYNC_SEL_MASK = (int)0x100000,
    PMU_RG_WKUP0_SYNC_SEL_POS = 20,
    PMU_RG_WKUP1_SYNC_SEL_MASK = (int)0x200000,
    PMU_RG_WKUP1_SYNC_SEL_POS = 21,
};

enum PMU_RG_REG_WKUP_TIM0_FIELD
{
    PMU_RG_STB_BG_M1_MASK = (int)0xffff,
    PMU_RG_STB_BG_M1_POS = 0,
    PMU_RG_STB_PSW_M1_MASK = (int)0xff0000,
    PMU_RG_STB_PSW_M1_POS = 16,
    PMU_RG_STB_HSI_M1_MASK = (int)0xf0000000,
    PMU_RG_STB_HSI_M1_POS = 28,
};

enum PMU_RG_REG_WKUP_TIM1_FIELD
{
    PMU_RG_STB_CLK_M1_MASK = (int)0xfff,
    PMU_RG_STB_CLK_M1_POS = 0,
    PMU_RG_STB_LDO_M1_MASK = (int)0xfff000,
    PMU_RG_STB_LDO_M1_POS = 12,
};

enum PMU_RG_REG_RST_SFT_FIELD
{
    PMU_RG_RST_FROM_SFT_MASK = (int)0x1,
    PMU_RG_RST_FROM_SFT_POS = 0,
    PMU_RG_CLK_SEL_LSC_MASK = (int)0x30,
    PMU_RG_CLK_SEL_LSC_POS = 4,
    PMU_RG_RST_SRC_CLR_MASK = (int)0x100,
    PMU_RG_RST_SRC_CLR_POS = 8,
};

enum PMU_RG_REG_CLKG_SRST_FIELD
{
    PMU_RG_CLKG_SET_TIM_MASK = (int)0x1,
    PMU_RG_CLKG_SET_TIM_POS = 0,
    PMU_RG_CLKG_CLR_TIM_MASK = (int)0x2,
    PMU_RG_CLKG_CLR_TIM_POS = 1,
    PMU_RG_CLKG_SET_WDT_MASK = (int)0x4,
    PMU_RG_CLKG_SET_WDT_POS = 2,
    PMU_RG_CLKG_CLR_WDT_MASK = (int)0x8,
    PMU_RG_CLKG_CLR_WDT_POS = 3,
    PMU_RG_CLKG_SET_RTC_MASK = (int)0x10,
    PMU_RG_CLKG_SET_RTC_POS = 4,
    PMU_RG_CLKG_CLR_RTC_MASK = (int)0x20,
    PMU_RG_CLKG_CLR_RTC_POS = 5,
};

enum PMU_RG_REG_PMU_SET_VAL_FIELD
{
    PMU_RG_CLK_SET_LSE_MASK = (int)0x1,
    PMU_RG_CLK_SET_LSE_POS = 0,
    PMU_RG_CLK_SET_HSI_MASK = (int)0x2,
    PMU_RG_CLK_SET_HSI_POS = 1,
    PMU_RG_CLK_SET_HSE_MASK = (int)0x4,
    PMU_RG_CLK_SET_HSE_POS = 2,
    PMU_RG_SRAM_DS_SET_MASK = (int)0xfff00,
    PMU_RG_SRAM_DS_SET_POS = 8,
    PMU_RG_PMU_SET_TGGL_MASK = (int)0x80000000,
    PMU_RG_PMU_SET_TGGL_POS = 31,
};

enum PMU_RG_REG_PWR_CTRL_FIELD
{
    PMU_RG_HPLDO_PD_EN_MASK = (int)0x2,
    PMU_RG_HPLDO_PD_EN_POS = 1,
    PMU_RG_BG_PD_EN_MASK = (int)0x4,
    PMU_RG_BG_PD_EN_POS = 2,
    PMU_RG_BGIB_PD_EN_MASK = (int)0x8,
    PMU_RG_BGIB_PD_EN_POS = 3,
    PMU_RG_MSI_PD_EN_MASK = (int)0x10,
    PMU_RG_MSI_PD_EN_POS = 4,
    PMU_RG_LSI_PD_EN_MASK = (int)0x20,
    PMU_RG_LSI_PD_EN_POS = 5,
    PMU_RG_LSE_PD_EN_MASK = (int)0x40,
    PMU_RG_LSE_PD_EN_POS = 6,
    PMU_RG_HSE_PD_EN_MASK = (int)0x80,
    PMU_RG_HSE_PD_EN_POS = 7,
    PMU_RG_HSI_PD_EN_MASK = (int)0x100,
    PMU_RG_HSI_PD_EN_POS = 8,
    PMU_RG_SRAM_DS_PD_EN_MASK = (int)0x200,
    PMU_RG_SRAM_DS_PD_EN_POS = 9,
    PMU_RG_LSE_PU_EN_MASK = (int)0x400,
    PMU_RG_LSE_PU_EN_POS = 10,
    PMU_RG_HSE_PU_EN_MASK = (int)0x800,
    PMU_RG_HSE_PU_EN_POS = 11,
    PMU_RG_SRAM_DS_PU_EN_MASK = (int)0x1000,
    PMU_RG_SRAM_DS_PU_EN_POS = 12,
    PMU_RG_RCO_BIAS_FC_MASK = (int)0x2000,
    PMU_RG_RCO_BIAS_FC_POS = 13,
    PMU_RG_PD_GPIO_SEL_MASK = (int)0x4000,
    PMU_RG_PD_GPIO_SEL_POS = 14,
    PMU_RG_HPSW1_PD_EN_MASK = (int)0x10000,
    PMU_RG_HPSW1_PD_EN_POS = 16,
    PMU_RG_HPSW2_PD_EN_MASK = (int)0x20000,
    PMU_RG_HPSW2_PD_EN_POS = 17,
    PMU_RG_SRAM0_PD_EN_MASK = (int)0x40000,
    PMU_RG_SRAM0_PD_EN_POS = 18,
    PMU_RG_SRAM1_PD_EN_MASK = (int)0x80000,
    PMU_RG_SRAM1_PD_EN_POS = 19,
    PMU_RG_SRAM2_PD_EN_MASK = (int)0x100000,
    PMU_RG_SRAM2_PD_EN_POS = 20,
    PMU_RG_SRAM3_PD_EN_MASK = (int)0x200000,
    PMU_RG_SRAM3_PD_EN_POS = 21,
    PMU_RG_SRAM4_PD_EN_MASK = (int)0x400000,
    PMU_RG_SRAM4_PD_EN_POS = 22,
    PMU_RG_SRAM5_PD_EN_MASK = (int)0x800000,
    PMU_RG_SRAM5_PD_EN_POS = 23,
    PMU_RG_SRAM6_PD_EN_MASK = (int)0x1000000,
    PMU_RG_SRAM6_PD_EN_POS = 24,
    PMU_RG_SRAM7_PD_EN_MASK = (int)0x2000000,
    PMU_RG_SRAM7_PD_EN_POS = 25,
    PMU_RG_SRAM8_PD_EN_MASK = (int)0x4000000,
    PMU_RG_SRAM8_PD_EN_POS = 26,
    PMU_RG_SRAM9_PD_EN_MASK = (int)0x8000000,
    PMU_RG_SRAM9_PD_EN_POS = 27,
    PMU_RG_SRAM10_PD_EN_MASK = (int)0x10000000,
    PMU_RG_SRAM10_PD_EN_POS = 28,
    PMU_RG_SRAM11_PD_EN_MASK = (int)0x20000000,
    PMU_RG_SRAM11_PD_EN_POS = 29,
};

enum PMU_RG_REG_SRAM_LOCK_FIELD
{
    PMU_RG_ACC_LOCK_MASK = (int)0x1,
    PMU_RG_ACC_LOCK_POS = 0,
    PMU_RG_DPLL_DIS_MASK = (int)0x10000,
    PMU_RG_DPLL_DIS_POS = 16,
};

enum PMU_RG_REG_PMU_STATUS_FIELD
{
    PMU_RG_LSE_EN_MASK = (int)0x1,
    PMU_RG_LSE_EN_POS = 0,
    PMU_RG_HSI_EN_MASK = (int)0x2,
    PMU_RG_HSI_EN_POS = 1,
    PMU_RG_HSE_EN_MASK = (int)0x4,
    PMU_RG_HSE_EN_POS = 2,
    PMU_RG_VREF_OK_MASK = (int)0x8,
    PMU_RG_VREF_OK_POS = 3,
    PMU_RG_SRAM_DS_MASK = (int)0x7f00,
    PMU_RG_SRAM_DS_POS = 8,
    PMU_RG_EXTI_INTR_MASK = (int)0x10000,
    PMU_RG_EXTI_INTR_POS = 16,
    PMU_RG_LVD33_INTR_MASK = (int)0x20000,
    PMU_RG_LVD33_INTR_POS = 17,
    PMU_RG_LVD33_DTCT_MASK = (int)0x40000,
    PMU_RG_LVD33_DTCT_POS = 18,
    PMU_RG_RST_SRC_MASK = (int)0x7f000000,
    PMU_RG_RST_SRC_POS = 24,
};

enum PMU_RG_REG_TEST_STATUS_FIELD
{
    PMU_RG_TEST_DATA_MASK = (int)0xffff,
    PMU_RG_TEST_DATA_POS = 0,
    PMU_RG_TEST_DOTE_MASK = (int)0xffff0000,
    PMU_RG_TEST_DOTE_POS = 16,
};

enum PMU_RG_REG_CASEOPEN_CTRL_FIELD
{
    PMU_RG_CASEOPEN_POL_MASK = (int)0xf,
    PMU_RG_CASEOPEN_POL_POS = 0,
    PMU_RG_CASEOPEN_MASK_MASK = (int)0xf0,
    PMU_RG_CASEOPEN_MASK_POS = 4,
    PMU_RG_CASEOPEN_CLR_MASK = (int)0xf00,
    PMU_RG_CASEOPEN_CLR_POS = 8,
};

enum PMU_RG_REG_IOA_LVS_LOCK_FIELD
{
    PMU_RG_GPIOA_LOCK_MASK = (int)0xffff,
    PMU_RG_GPIOA_LOCK_POS = 0,
    PMU_RG_GPIOA_LVS_MASK = (int)0xffff0000,
    PMU_RG_GPIOA_LVS_POS = 16,
};

enum PMU_RG_REG_IOA_DOT_FIELD
{
    PMU_RG_GPIOA_DOT_MASK = (int)0xffff,
    PMU_RG_GPIOA_DOT_POS = 0,
};

enum PMU_RG_REG_IOA_PD_PU_FIELD
{
    PMU_RG_GPIOA_PU_MASK = (int)0xffff,
    PMU_RG_GPIOA_PU_POS = 0,
    PMU_RG_GPIOA_PD_MASK = (int)0xffff0000,
    PMU_RG_GPIOA_PD_POS = 16,
};

enum PMU_RG_REG_IOA_REN_ODE_FIELD
{
    PMU_RG_GPIOA_ODE_MASK = (int)0xffff,
    PMU_RG_GPIOA_ODE_POS = 0,
    PMU_RG_GPIOA_REN_MASK = (int)0xffff0000,
    PMU_RG_GPIOA_REN_POS = 16,
};

enum PMU_RG_REG_IOA_DS1_DS2_FIELD
{
    PMU_RG_GPIOA_DS2_MASK = (int)0xffff,
    PMU_RG_GPIOA_DS2_POS = 0,
    PMU_RG_GPIOA_DS1_MASK = (int)0xffff0000,
    PMU_RG_GPIOA_DS1_POS = 16,
};

enum PMU_RG_REG_IOA_AE1_AE2_FIELD
{
    PMU_RG_GPIOA_AE2_MASK = (int)0xffff,
    PMU_RG_GPIOA_AE2_POS = 0,
    PMU_RG_GPIOA_AE1_MASK = (int)0xffff0000,
    PMU_RG_GPIOA_AE1_POS = 16,
};

enum PMU_RG_REG_IOA_OTE_FIR_FIELD
{
    PMU_RG_GPIOA_FIR_MASK = (int)0xffff,
    PMU_RG_GPIOA_FIR_POS = 0,
    PMU_RG_GPIOA_OTE_MASK = (int)0xffff0000,
    PMU_RG_GPIOA_OTE_POS = 16,
};

enum PMU_RG_REG_IOA_HSS_DIN_FIELD
{
    PMU_RG_GPIOA_DIN_MASK = (int)0xffff,
    PMU_RG_GPIOA_DIN_POS = 0,
    PMU_RG_GPIOA_HSS_MASK = (int)0xffff0000,
    PMU_RG_GPIOA_HSS_POS = 16,
};

enum PMU_RG_REG_IOB_LVS_LOCK_FIELD
{
    PMU_RG_GPIOB_LOCK_MASK = (int)0xffff,
    PMU_RG_GPIOB_LOCK_POS = 0,
    PMU_RG_GPIOB_LVS_MASK = (int)0xffff0000,
    PMU_RG_GPIOB_LVS_POS = 16,
};

enum PMU_RG_REG_IOB_DOT_FIELD
{
    PMU_RG_GPIOB_DOT_MASK = (int)0xffff,
    PMU_RG_GPIOB_DOT_POS = 0,
};

enum PMU_RG_REG_IOB_PD_PU_FIELD
{
    PMU_RG_GPIOB_PU_MASK = (int)0xffff,
    PMU_RG_GPIOB_PU_POS = 0,
    PMU_RG_GPIOB_PD_MASK = (int)0xffff0000,
    PMU_RG_GPIOB_PD_POS = 16,
};

enum PMU_RG_REG_IOB_REN_ODE_FIELD
{
    PMU_RG_GPIOB_ODE_MASK = (int)0xffff,
    PMU_RG_GPIOB_ODE_POS = 0,
    PMU_RG_GPIOB_REN_MASK = (int)0xffff0000,
    PMU_RG_GPIOB_REN_POS = 16,
};

enum PMU_RG_REG_IOB_DS1_DS2_FIELD
{
    PMU_RG_GPIOB_DS2_MASK = (int)0xffff,
    PMU_RG_GPIOB_DS2_POS = 0,
    PMU_RG_GPIOB_DS1_MASK = (int)0xffff0000,
    PMU_RG_GPIOB_DS1_POS = 16,
};

enum PMU_RG_REG_IOB_AE1_AE2_FIELD
{
    PMU_RG_GPIOB_AE2_MASK = (int)0xffff,
    PMU_RG_GPIOB_AE2_POS = 0,
    PMU_RG_GPIOB_AE1_MASK = (int)0xffff0000,
    PMU_RG_GPIOB_AE1_POS = 16,
};

enum PMU_RG_REG_IOB_OTE_FIR_FIELD
{
    PMU_RG_GPIOB_FIR_MASK = (int)0xffff,
    PMU_RG_GPIOB_FIR_POS = 0,
    PMU_RG_GPIOB_OTE_MASK = (int)0xffff0000,
    PMU_RG_GPIOB_OTE_POS = 16,
};

enum PMU_RG_REG_IOB_HSS_DIN_FIELD
{
    PMU_RG_GPIOB_DIN_MASK = (int)0xffff,
    PMU_RG_GPIOB_DIN_POS = 0,
    PMU_RG_GPIOB_HSS_MASK = (int)0xffff0000,
    PMU_RG_GPIOB_HSS_POS = 16,
};

enum PMU_RG_REG_IOC_LVS_LOCK_FIELD
{
    PMU_RG_GPIOC_LOCK_MASK = (int)0xffff,
    PMU_RG_GPIOC_LOCK_POS = 0,
    PMU_RG_GPIOC_LVS_MASK = (int)0xffff0000,
    PMU_RG_GPIOC_LVS_POS = 16,
};

enum PMU_RG_REG_IOC_DOT_FIELD
{
    PMU_RG_GPIOC_DOT_MASK = (int)0xffff,
    PMU_RG_GPIOC_DOT_POS = 0,
};

enum PMU_RG_REG_IOC_PD_PU_FIELD
{
    PMU_RG_GPIOC_PU_MASK = (int)0xffff,
    PMU_RG_GPIOC_PU_POS = 0,
    PMU_RG_GPIOC_PD_MASK = (int)0xffff0000,
    PMU_RG_GPIOC_PD_POS = 16,
};

enum PMU_RG_REG_IOC_REN_ODE_FIELD
{
    PMU_RG_GPIOC_ODE_MASK = (int)0xffff,
    PMU_RG_GPIOC_ODE_POS = 0,
    PMU_RG_GPIOC_REN_MASK = (int)0xffff0000,
    PMU_RG_GPIOC_REN_POS = 16,
};

enum PMU_RG_REG_IOC_DS1_DS2_FIELD
{
    PMU_RG_GPIOC_DS2_MASK = (int)0xffff,
    PMU_RG_GPIOC_DS2_POS = 0,
    PMU_RG_GPIOC_DS1_MASK = (int)0xffff0000,
    PMU_RG_GPIOC_DS1_POS = 16,
};

enum PMU_RG_REG_IOC_AE1_AE2_FIELD
{
    PMU_RG_GPIOC_AE2_MASK = (int)0xffff,
    PMU_RG_GPIOC_AE2_POS = 0,
    PMU_RG_GPIOC_AE1_MASK = (int)0xffff0000,
    PMU_RG_GPIOC_AE1_POS = 16,
};

enum PMU_RG_REG_IOC_OTE_FIR_FIELD
{
    PMU_RG_GPIOC_FIR_MASK = (int)0xffff,
    PMU_RG_GPIOC_FIR_POS = 0,
    PMU_RG_GPIOC_OTE_MASK = (int)0xffff0000,
    PMU_RG_GPIOC_OTE_POS = 16,
};

enum PMU_RG_REG_IOC_HSS_DIN_FIELD
{
    PMU_RG_GPIOC_DIN_MASK = (int)0xffff,
    PMU_RG_GPIOC_DIN_POS = 0,
    PMU_RG_GPIOC_HSS_MASK = (int)0xffff0000,
    PMU_RG_GPIOC_HSS_POS = 16,
};

enum PMU_RG_REG_IOD_LVS_LOCK_FIELD
{
    PMU_RG_GPIOD_LOCK_MASK = (int)0xffff,
    PMU_RG_GPIOD_LOCK_POS = 0,
    PMU_RG_GPIOD_LVS_MASK = (int)0xffff0000,
    PMU_RG_GPIOD_LVS_POS = 16,
};

enum PMU_RG_REG_IOD_DOT_FIELD
{
    PMU_RG_GPIOD_DOT_MASK = (int)0xffff,
    PMU_RG_GPIOD_DOT_POS = 0,
};

enum PMU_RG_REG_IOD_PD_PU_FIELD
{
    PMU_RG_GPIOD_PU_MASK = (int)0xffff,
    PMU_RG_GPIOD_PU_POS = 0,
    PMU_RG_GPIOD_PD_MASK = (int)0xffff0000,
    PMU_RG_GPIOD_PD_POS = 16,
};

enum PMU_RG_REG_IOD_REN_ODE_FIELD
{
    PMU_RG_GPIOD_ODE_MASK = (int)0xffff,
    PMU_RG_GPIOD_ODE_POS = 0,
    PMU_RG_GPIOD_REN_MASK = (int)0xffff0000,
    PMU_RG_GPIOD_REN_POS = 16,
};

enum PMU_RG_REG_IOD_DS1_DS2_FIELD
{
    PMU_RG_GPIOD_DS2_MASK = (int)0xffff,
    PMU_RG_GPIOD_DS2_POS = 0,
    PMU_RG_GPIOD_DS1_MASK = (int)0xffff0000,
    PMU_RG_GPIOD_DS1_POS = 16,
};

enum PMU_RG_REG_IOD_AE1_AE2_FIELD
{
    PMU_RG_GPIOD_AE2_MASK = (int)0xffff,
    PMU_RG_GPIOD_AE2_POS = 0,
    PMU_RG_GPIOD_AE1_MASK = (int)0xffff0000,
    PMU_RG_GPIOD_AE1_POS = 16,
};

enum PMU_RG_REG_IOD_OTE_FIR_FIELD
{
    PMU_RG_GPIOD_FIR_MASK = (int)0xffff,
    PMU_RG_GPIOD_FIR_POS = 0,
    PMU_RG_GPIOD_OTE_MASK = (int)0xffff0000,
    PMU_RG_GPIOD_OTE_POS = 16,
};

enum PMU_RG_REG_IOD_HSS_DIN_FIELD
{
    PMU_RG_GPIOD_DIN_MASK = (int)0xffff,
    PMU_RG_GPIOD_DIN_POS = 0,
    PMU_RG_GPIOD_HSS_MASK = (int)0xffff0000,
    PMU_RG_GPIOD_HSS_POS = 16,
};

enum PMU_RG_REG_IOE_LVS_LOCK_FIELD
{
    PMU_RG_GPIOE_LOCK_MASK = (int)0xffff,
    PMU_RG_GPIOE_LOCK_POS = 0,
    PMU_RG_GPIOE_LVS_MASK = (int)0xffff0000,
    PMU_RG_GPIOE_LVS_POS = 16,
};

enum PMU_RG_REG_IOE_DOT_FIELD
{
    PMU_RG_GPIOE_DOT_MASK = (int)0xffff,
    PMU_RG_GPIOE_DOT_POS = 0,
};

enum PMU_RG_REG_IOE_PD_PU_FIELD
{
    PMU_RG_GPIOE_PU_MASK = (int)0xffff,
    PMU_RG_GPIOE_PU_POS = 0,
    PMU_RG_GPIOE_PD_MASK = (int)0xffff0000,
    PMU_RG_GPIOE_PD_POS = 16,
};

enum PMU_RG_REG_IOE_REN_ODE_FIELD
{
    PMU_RG_GPIOE_ODE_MASK = (int)0xffff,
    PMU_RG_GPIOE_ODE_POS = 0,
    PMU_RG_GPIOE_REN_MASK = (int)0xffff0000,
    PMU_RG_GPIOE_REN_POS = 16,
};

enum PMU_RG_REG_IOE_DS1_DS2_FIELD
{
    PMU_RG_GPIOE_DS2_MASK = (int)0xffff,
    PMU_RG_GPIOE_DS2_POS = 0,
    PMU_RG_GPIOE_DS1_MASK = (int)0xffff0000,
    PMU_RG_GPIOE_DS1_POS = 16,
};

enum PMU_RG_REG_IOE_AE1_AE2_FIELD
{
    PMU_RG_GPIOE_AE2_MASK = (int)0xffff,
    PMU_RG_GPIOE_AE2_POS = 0,
    PMU_RG_GPIOE_AE1_MASK = (int)0xffff0000,
    PMU_RG_GPIOE_AE1_POS = 16,
};

enum PMU_RG_REG_IOE_OTE_FIR_FIELD
{
    PMU_RG_GPIOE_FIR_MASK = (int)0xffff,
    PMU_RG_GPIOE_FIR_POS = 0,
    PMU_RG_GPIOE_OTE_MASK = (int)0xffff0000,
    PMU_RG_GPIOE_OTE_POS = 16,
};

enum PMU_RG_REG_IOE_HSS_DIN_FIELD
{
    PMU_RG_GPIOE_DIN_MASK = (int)0xffff,
    PMU_RG_GPIOE_DIN_POS = 0,
    PMU_RG_GPIOE_HSS_MASK = (int)0xffff0000,
    PMU_RG_GPIOE_HSS_POS = 16,
};

enum PMU_RG_REG_IOF_LVS_LOCK_FIELD
{
    PMU_RG_GPIOF_LOCK_MASK = (int)0xffff,
    PMU_RG_GPIOF_LOCK_POS = 0,
    PMU_RG_GPIOF_LVS_MASK = (int)0xffff0000,
    PMU_RG_GPIOF_LVS_POS = 16,
};

enum PMU_RG_REG_IOF_DOT_FIELD
{
    PMU_RG_GPIOF_DOT_MASK = (int)0xffff,
    PMU_RG_GPIOF_DOT_POS = 0,
};

enum PMU_RG_REG_IOF_PD_PU_FIELD
{
    PMU_RG_GPIOF_PU_MASK = (int)0xffff,
    PMU_RG_GPIOF_PU_POS = 0,
    PMU_RG_GPIOF_PD_MASK = (int)0xffff0000,
    PMU_RG_GPIOF_PD_POS = 16,
};

enum PMU_RG_REG_IOF_REN_ODE_FIELD
{
    PMU_RG_GPIOF_ODE_MASK = (int)0xffff,
    PMU_RG_GPIOF_ODE_POS = 0,
    PMU_RG_GPIOF_REN_MASK = (int)0xffff0000,
    PMU_RG_GPIOF_REN_POS = 16,
};

enum PMU_RG_REG_IOF_DS1_DS2_FIELD
{
    PMU_RG_GPIOF_DS2_MASK = (int)0xffff,
    PMU_RG_GPIOF_DS2_POS = 0,
    PMU_RG_GPIOF_DS1_MASK = (int)0xffff0000,
    PMU_RG_GPIOF_DS1_POS = 16,
};

enum PMU_RG_REG_IOF_AE1_AE2_FIELD
{
    PMU_RG_GPIOF_AE2_MASK = (int)0xffff,
    PMU_RG_GPIOF_AE2_POS = 0,
    PMU_RG_GPIOF_AE1_MASK = (int)0xffff0000,
    PMU_RG_GPIOF_AE1_POS = 16,
};

enum PMU_RG_REG_IOF_OTE_FIR_FIELD
{
    PMU_RG_GPIOF_FIR_MASK = (int)0xffff,
    PMU_RG_GPIOF_FIR_POS = 0,
    PMU_RG_GPIOF_OTE_MASK = (int)0xffff0000,
    PMU_RG_GPIOF_OTE_POS = 16,
};

enum PMU_RG_REG_IOF_HSS_DIN_FIELD
{
    PMU_RG_GPIOF_DIN_MASK = (int)0xffff,
    PMU_RG_GPIOF_DIN_POS = 0,
    PMU_RG_GPIOF_HSS_MASK = (int)0xffff0000,
    PMU_RG_GPIOF_HSS_POS = 16,
};

enum PMU_RG_REG_IOG_LVS_LOCK_FIELD
{
    PMU_RG_GPIOG_LOCK_MASK = (int)0xffff,
    PMU_RG_GPIOG_LOCK_POS = 0,
    PMU_RG_GPIOG_LVS_MASK = (int)0xffff0000,
    PMU_RG_GPIOG_LVS_POS = 16,
};

enum PMU_RG_REG_IOG_DOT_FIELD
{
    PMU_RG_GPIOG_DOT_MASK = (int)0xffff,
    PMU_RG_GPIOG_DOT_POS = 0,
};

enum PMU_RG_REG_IOG_PD_PU_FIELD
{
    PMU_RG_GPIOG_PU_MASK = (int)0xffff,
    PMU_RG_GPIOG_PU_POS = 0,
    PMU_RG_GPIOG_PD_MASK = (int)0xffff0000,
    PMU_RG_GPIOG_PD_POS = 16,
};

enum PMU_RG_REG_IOG_REN_ODE_FIELD
{
    PMU_RG_GPIOG_ODE_MASK = (int)0xffff,
    PMU_RG_GPIOG_ODE_POS = 0,
    PMU_RG_GPIOG_REN_MASK = (int)0xffff0000,
    PMU_RG_GPIOG_REN_POS = 16,
};

enum PMU_RG_REG_IOG_DS1_DS2_FIELD
{
    PMU_RG_GPIOG_DS2_MASK = (int)0xffff,
    PMU_RG_GPIOG_DS2_POS = 0,
    PMU_RG_GPIOG_DS1_MASK = (int)0xffff0000,
    PMU_RG_GPIOG_DS1_POS = 16,
};

enum PMU_RG_REG_IOG_AE1_AE2_FIELD
{
    PMU_RG_GPIOG_AE2_MASK = (int)0xffff,
    PMU_RG_GPIOG_AE2_POS = 0,
    PMU_RG_GPIOG_AE1_MASK = (int)0xffff0000,
    PMU_RG_GPIOG_AE1_POS = 16,
};

enum PMU_RG_REG_IOG_OTE_FIR_FIELD
{
    PMU_RG_GPIOG_FIR_MASK = (int)0xffff,
    PMU_RG_GPIOG_FIR_POS = 0,
    PMU_RG_GPIOG_OTE_MASK = (int)0xffff0000,
    PMU_RG_GPIOG_OTE_POS = 16,
};

enum PMU_RG_REG_IOG_HSS_DIN_FIELD
{
    PMU_RG_GPIOG_DIN_MASK = (int)0xffff,
    PMU_RG_GPIOG_DIN_POS = 0,
    PMU_RG_GPIOG_HSS_MASK = (int)0xffff0000,
    PMU_RG_GPIOG_HSS_POS = 16,
};

enum PMU_RG_REG_IOH_LVS_LOCK_FIELD
{
    PMU_RG_GPIOH_LOCK_MASK = (int)0xffff,
    PMU_RG_GPIOH_LOCK_POS = 0,
    PMU_RG_GPIOH_LVS_MASK = (int)0xffff0000,
    PMU_RG_GPIOH_LVS_POS = 16,
};

enum PMU_RG_REG_IOH_DOT_FIELD
{
    PMU_RG_GPIOH_DOT_MASK = (int)0xffff,
    PMU_RG_GPIOH_DOT_POS = 0,
};

enum PMU_RG_REG_IOH_PD_PU_FIELD
{
    PMU_RG_GPIOH_PU_MASK = (int)0xffff,
    PMU_RG_GPIOH_PU_POS = 0,
    PMU_RG_GPIOH_PD_MASK = (int)0xffff0000,
    PMU_RG_GPIOH_PD_POS = 16,
};

enum PMU_RG_REG_IOH_REN_ODE_FIELD
{
    PMU_RG_GPIOH_ODE_MASK = (int)0xffff,
    PMU_RG_GPIOH_ODE_POS = 0,
    PMU_RG_GPIOH_REN_MASK = (int)0xffff0000,
    PMU_RG_GPIOH_REN_POS = 16,
};

enum PMU_RG_REG_IOH_DS1_DS2_FIELD
{
    PMU_RG_GPIOH_DS2_MASK = (int)0xffff,
    PMU_RG_GPIOH_DS2_POS = 0,
    PMU_RG_GPIOH_DS1_MASK = (int)0xffff0000,
    PMU_RG_GPIOH_DS1_POS = 16,
};

enum PMU_RG_REG_IOH_AE1_AE2_FIELD
{
    PMU_RG_GPIOH_AE2_MASK = (int)0xffff,
    PMU_RG_GPIOH_AE2_POS = 0,
    PMU_RG_GPIOH_AE1_MASK = (int)0xffff0000,
    PMU_RG_GPIOH_AE1_POS = 16,
};

enum PMU_RG_REG_IOH_OTE_FIR_FIELD
{
    PMU_RG_GPIOH_FIR_MASK = (int)0xffff,
    PMU_RG_GPIOH_FIR_POS = 0,
    PMU_RG_GPIOH_OTE_MASK = (int)0xffff0000,
    PMU_RG_GPIOH_OTE_POS = 16,
};

enum PMU_RG_REG_IOH_HSS_DIN_FIELD
{
    PMU_RG_GPIOH_DIN_MASK = (int)0xffff,
    PMU_RG_GPIOH_DIN_POS = 0,
    PMU_RG_GPIOH_HSS_MASK = (int)0xffff0000,
    PMU_RG_GPIOH_HSS_POS = 16,
};

enum PMU_RG_REG_IOI_LVS_LOCK_FIELD
{
    PMU_RG_GPIOI_LOCK_MASK = (int)0xffff,
    PMU_RG_GPIOI_LOCK_POS = 0,
    PMU_RG_GPIOI_LVS_MASK = (int)0xffff0000,
    PMU_RG_GPIOI_LVS_POS = 16,
};

enum PMU_RG_REG_IOI_DOT_FIELD
{
    PMU_RG_GPIOI_DOT_MASK = (int)0xffff,
    PMU_RG_GPIOI_DOT_POS = 0,
};

enum PMU_RG_REG_IOI_PD_PU_FIELD
{
    PMU_RG_GPIOI_PU_MASK = (int)0xffff,
    PMU_RG_GPIOI_PU_POS = 0,
    PMU_RG_GPIOI_PD_MASK = (int)0xffff0000,
    PMU_RG_GPIOI_PD_POS = 16,
};

enum PMU_RG_REG_IOI_REN_ODE_FIELD
{
    PMU_RG_GPIOI_ODE_MASK = (int)0xffff,
    PMU_RG_GPIOI_ODE_POS = 0,
    PMU_RG_GPIOI_REN_MASK = (int)0xffff0000,
    PMU_RG_GPIOI_REN_POS = 16,
};

enum PMU_RG_REG_IOI_DS1_DS2_FIELD
{
    PMU_RG_GPIOI_DS2_MASK = (int)0xffff,
    PMU_RG_GPIOI_DS2_POS = 0,
    PMU_RG_GPIOI_DS1_MASK = (int)0xffff0000,
    PMU_RG_GPIOI_DS1_POS = 16,
};

enum PMU_RG_REG_IOI_AE1_AE2_FIELD
{
    PMU_RG_GPIOI_AE2_MASK = (int)0xffff,
    PMU_RG_GPIOI_AE2_POS = 0,
    PMU_RG_GPIOI_AE1_MASK = (int)0xffff0000,
    PMU_RG_GPIOI_AE1_POS = 16,
};

enum PMU_RG_REG_IOI_OTE_FIR_FIELD
{
    PMU_RG_GPIOI_FIR_MASK = (int)0xffff,
    PMU_RG_GPIOI_FIR_POS = 0,
    PMU_RG_GPIOI_OTE_MASK = (int)0xffff0000,
    PMU_RG_GPIOI_OTE_POS = 16,
};

enum PMU_RG_REG_IOI_HSS_DIN_FIELD
{
    PMU_RG_GPIOI_DIN_MASK = (int)0xffff,
    PMU_RG_GPIOI_DIN_POS = 0,
    PMU_RG_GPIOI_HSS_MASK = (int)0xffff0000,
    PMU_RG_GPIOI_HSS_POS = 16,
};

enum PMU_RG_REG_IOJ_LVS_LOCK_FIELD
{
    PMU_RG_GPIOJ_LOCK_MASK = (int)0xffff,
    PMU_RG_GPIOJ_LOCK_POS = 0,
    PMU_RG_GPIOJ_LVS_MASK = (int)0xffff0000,
    PMU_RG_GPIOJ_LVS_POS = 16,
};

enum PMU_RG_REG_IOJ_DOT_FIELD
{
    PMU_RG_GPIOJ_DOT_MASK = (int)0xffff,
    PMU_RG_GPIOJ_DOT_POS = 0,
};

enum PMU_RG_REG_IOJ_PD_PU_FIELD
{
    PMU_RG_GPIOJ_PU_MASK = (int)0xffff,
    PMU_RG_GPIOJ_PU_POS = 0,
    PMU_RG_GPIOJ_PD_MASK = (int)0xffff0000,
    PMU_RG_GPIOJ_PD_POS = 16,
};

enum PMU_RG_REG_IOJ_REN_ODE_FIELD
{
    PMU_RG_GPIOJ_ODE_MASK = (int)0xffff,
    PMU_RG_GPIOJ_ODE_POS = 0,
    PMU_RG_GPIOJ_REN_MASK = (int)0xffff0000,
    PMU_RG_GPIOJ_REN_POS = 16,
};

enum PMU_RG_REG_IOJ_DS1_DS2_FIELD
{
    PMU_RG_GPIOJ_DS2_MASK = (int)0xffff,
    PMU_RG_GPIOJ_DS2_POS = 0,
    PMU_RG_GPIOJ_DS1_MASK = (int)0xffff0000,
    PMU_RG_GPIOJ_DS1_POS = 16,
};

enum PMU_RG_REG_IOJ_AE1_AE2_FIELD
{
    PMU_RG_GPIOJ_AE2_MASK = (int)0xffff,
    PMU_RG_GPIOJ_AE2_POS = 0,
    PMU_RG_GPIOJ_AE1_MASK = (int)0xffff0000,
    PMU_RG_GPIOJ_AE1_POS = 16,
};

enum PMU_RG_REG_IOJ_OTE_FIR_FIELD
{
    PMU_RG_GPIOJ_FIR_MASK = (int)0xffff,
    PMU_RG_GPIOJ_FIR_POS = 0,
    PMU_RG_GPIOJ_OTE_MASK = (int)0xffff0000,
    PMU_RG_GPIOJ_OTE_POS = 16,
};

enum PMU_RG_REG_IOJ_HSS_DIN_FIELD
{
    PMU_RG_GPIOJ_DIN_MASK = (int)0xffff,
    PMU_RG_GPIOJ_DIN_POS = 0,
    PMU_RG_GPIOJ_HSS_MASK = (int)0xffff0000,
    PMU_RG_GPIOJ_HSS_POS = 16,
};

enum PMU_RG_REG_IOK_LVS_LOCK_FIELD
{
    PMU_RG_GPIOK_LOCK_MASK = (int)0xffff,
    PMU_RG_GPIOK_LOCK_POS = 0,
    PMU_RG_GPIOK_LVS_MASK = (int)0xffff0000,
    PMU_RG_GPIOK_LVS_POS = 16,
};

enum PMU_RG_REG_IOK_DOT_FIELD
{
    PMU_RG_GPIOK_DOT_MASK = (int)0xffff,
    PMU_RG_GPIOK_DOT_POS = 0,
};

enum PMU_RG_REG_IOK_PD_PU_FIELD
{
    PMU_RG_GPIOK_PU_MASK = (int)0xffff,
    PMU_RG_GPIOK_PU_POS = 0,
    PMU_RG_GPIOK_PD_MASK = (int)0xffff0000,
    PMU_RG_GPIOK_PD_POS = 16,
};

enum PMU_RG_REG_IOK_REN_ODE_FIELD
{
    PMU_RG_GPIOK_ODE_MASK = (int)0xffff,
    PMU_RG_GPIOK_ODE_POS = 0,
    PMU_RG_GPIOK_REN_MASK = (int)0xffff0000,
    PMU_RG_GPIOK_REN_POS = 16,
};

enum PMU_RG_REG_IOK_DS1_DS2_FIELD
{
    PMU_RG_GPIOK_DS2_MASK = (int)0xffff,
    PMU_RG_GPIOK_DS2_POS = 0,
    PMU_RG_GPIOK_DS1_MASK = (int)0xffff0000,
    PMU_RG_GPIOK_DS1_POS = 16,
};

enum PMU_RG_REG_IOK_AE1_AE2_FIELD
{
    PMU_RG_GPIOK_AE2_MASK = (int)0xffff,
    PMU_RG_GPIOK_AE2_POS = 0,
    PMU_RG_GPIOK_AE1_MASK = (int)0xffff0000,
    PMU_RG_GPIOK_AE1_POS = 16,
};

enum PMU_RG_REG_IOK_OTE_FIR_FIELD
{
    PMU_RG_GPIOK_FIR_MASK = (int)0xffff,
    PMU_RG_GPIOK_FIR_POS = 0,
    PMU_RG_GPIOK_OTE_MASK = (int)0xffff0000,
    PMU_RG_GPIOK_OTE_POS = 16,
};

enum PMU_RG_REG_IOK_HSS_DIN_FIELD
{
    PMU_RG_GPIOK_DIN_MASK = (int)0xffff,
    PMU_RG_GPIOK_DIN_POS = 0,
    PMU_RG_GPIOK_HSS_MASK = (int)0xffff0000,
    PMU_RG_GPIOK_HSS_POS = 16,
};

enum PMU_RG_REG_IOM_LVS_LOCK_FIELD
{
    PMU_RG_GPIOM_LOCK_MASK = (int)0xffff,
    PMU_RG_GPIOM_LOCK_POS = 0,
    PMU_RG_GPIOM_LVS_MASK = (int)0xffff0000,
    PMU_RG_GPIOM_LVS_POS = 16,
};

enum PMU_RG_REG_IOM_DOT_FIELD
{
    PMU_RG_GPIOM_DOT_MASK = (int)0xffff,
    PMU_RG_GPIOM_DOT_POS = 0,
};

enum PMU_RG_REG_IOM_PD_PU_FIELD
{
    PMU_RG_GPIOM_PU_MASK = (int)0xffff,
    PMU_RG_GPIOM_PU_POS = 0,
    PMU_RG_GPIOM_PD_MASK = (int)0xffff0000,
    PMU_RG_GPIOM_PD_POS = 16,
};

enum PMU_RG_REG_IOM_REN_ODE_FIELD
{
    PMU_RG_GPIOM_ODE_MASK = (int)0xffff,
    PMU_RG_GPIOM_ODE_POS = 0,
    PMU_RG_GPIOM_REN_MASK = (int)0xffff0000,
    PMU_RG_GPIOM_REN_POS = 16,
};

enum PMU_RG_REG_IOM_DS1_DS2_FIELD
{
    PMU_RG_GPIOM_DS2_MASK = (int)0xffff,
    PMU_RG_GPIOM_DS2_POS = 0,
    PMU_RG_GPIOM_DS1_MASK = (int)0xffff0000,
    PMU_RG_GPIOM_DS1_POS = 16,
};

enum PMU_RG_REG_IOM_AE1_AE2_FIELD
{
    PMU_RG_GPIOM_AE2_MASK = (int)0xffff,
    PMU_RG_GPIOM_AE2_POS = 0,
    PMU_RG_GPIOM_AE1_MASK = (int)0xffff0000,
    PMU_RG_GPIOM_AE1_POS = 16,
};

enum PMU_RG_REG_IOM_OTE_FIR_FIELD
{
    PMU_RG_GPIOM_FIR_MASK = (int)0xffff,
    PMU_RG_GPIOM_FIR_POS = 0,
    PMU_RG_GPIOM_OTE_MASK = (int)0xffff0000,
    PMU_RG_GPIOM_OTE_POS = 16,
};

enum PMU_RG_REG_IOM_HSS_DIN_FIELD
{
    PMU_RG_GPIOM_DIN_MASK = (int)0xffff,
    PMU_RG_GPIOM_DIN_POS = 0,
    PMU_RG_GPIOM_HSS_MASK = (int)0xffff0000,
    PMU_RG_GPIOM_HSS_POS = 16,
};

enum PMU_RG_REG_ION_LVS_LOCK_FIELD
{
    PMU_RG_GPION_LOCK_MASK = (int)0xffff,
    PMU_RG_GPION_LOCK_POS = 0,
    PMU_RG_GPION_LVS_MASK = (int)0xffff0000,
    PMU_RG_GPION_LVS_POS = 16,
};

enum PMU_RG_REG_ION_DOT_FIELD
{
    PMU_RG_GPION_DOT_MASK = (int)0xffff,
    PMU_RG_GPION_DOT_POS = 0,
};

enum PMU_RG_REG_ION_PD_PU_FIELD
{
    PMU_RG_GPION_PU_MASK = (int)0xffff,
    PMU_RG_GPION_PU_POS = 0,
    PMU_RG_GPION_PD_MASK = (int)0xffff0000,
    PMU_RG_GPION_PD_POS = 16,
};

enum PMU_RG_REG_ION_REN_ODE_FIELD
{
    PMU_RG_GPION_ODE_MASK = (int)0xffff,
    PMU_RG_GPION_ODE_POS = 0,
    PMU_RG_GPION_REN_MASK = (int)0xffff0000,
    PMU_RG_GPION_REN_POS = 16,
};

enum PMU_RG_REG_ION_DS1_DS2_FIELD
{
    PMU_RG_GPION_DS2_MASK = (int)0xffff,
    PMU_RG_GPION_DS2_POS = 0,
    PMU_RG_GPION_DS1_MASK = (int)0xffff0000,
    PMU_RG_GPION_DS1_POS = 16,
};

enum PMU_RG_REG_ION_AE1_AE2_FIELD
{
    PMU_RG_GPION_AE2_MASK = (int)0xffff,
    PMU_RG_GPION_AE2_POS = 0,
    PMU_RG_GPION_AE1_MASK = (int)0xffff0000,
    PMU_RG_GPION_AE1_POS = 16,
};

enum PMU_RG_REG_ION_OTE_FIR_FIELD
{
    PMU_RG_GPION_FIR_MASK = (int)0xffff,
    PMU_RG_GPION_FIR_POS = 0,
    PMU_RG_GPION_OTE_MASK = (int)0xffff0000,
    PMU_RG_GPION_OTE_POS = 16,
};

enum PMU_RG_REG_ION_HSS_DIN_FIELD
{
    PMU_RG_GPION_DIN_MASK = (int)0xffff,
    PMU_RG_GPION_DIN_POS = 0,
    PMU_RG_GPION_HSS_MASK = (int)0xffff0000,
    PMU_RG_GPION_HSS_POS = 16,
};

enum PMU_RG_REG_IOQ_LVS_LOCK_FIELD
{
    PMU_RG_GPIOQ_LOCK_MASK = (int)0xffff,
    PMU_RG_GPIOQ_LOCK_POS = 0,
    PMU_RG_GPIOQ_LVS_MASK = (int)0xffff0000,
    PMU_RG_GPIOQ_LVS_POS = 16,
};

enum PMU_RG_REG_IOQ_DOT_FIELD
{
    PMU_RG_GPIOQ_DOT_MASK = (int)0xffff,
    PMU_RG_GPIOQ_DOT_POS = 0,
};

enum PMU_RG_REG_IOQ_PD_PU_FIELD
{
    PMU_RG_GPIOQ_PU_MASK = (int)0xffff,
    PMU_RG_GPIOQ_PU_POS = 0,
    PMU_RG_GPIOQ_PD_MASK = (int)0xffff0000,
    PMU_RG_GPIOQ_PD_POS = 16,
};

enum PMU_RG_REG_IOQ_REN_ODE_FIELD
{
    PMU_RG_GPIOQ_ODE_MASK = (int)0xffff,
    PMU_RG_GPIOQ_ODE_POS = 0,
    PMU_RG_GPIOQ_REN_MASK = (int)0xffff0000,
    PMU_RG_GPIOQ_REN_POS = 16,
};

enum PMU_RG_REG_IOQ_DS1_DS2_FIELD
{
    PMU_RG_GPIOQ_DS2_MASK = (int)0xffff,
    PMU_RG_GPIOQ_DS2_POS = 0,
    PMU_RG_GPIOQ_DS1_MASK = (int)0xffff0000,
    PMU_RG_GPIOQ_DS1_POS = 16,
};

enum PMU_RG_REG_IOQ_AE1_AE2_FIELD
{
    PMU_RG_GPIOQ_AE2_MASK = (int)0xffff,
    PMU_RG_GPIOQ_AE2_POS = 0,
    PMU_RG_GPIOQ_AE1_MASK = (int)0xffff0000,
    PMU_RG_GPIOQ_AE1_POS = 16,
};

enum PMU_RG_REG_IOQ_OTE_FIR_FIELD
{
    PMU_RG_GPIOQ_FIR_MASK = (int)0xffff,
    PMU_RG_GPIOQ_FIR_POS = 0,
    PMU_RG_GPIOQ_OTE_MASK = (int)0xffff0000,
    PMU_RG_GPIOQ_OTE_POS = 16,
};

enum PMU_RG_REG_IOQ_HSS_DIN_FIELD
{
    PMU_RG_GPIOQ_DIN_MASK = (int)0xffff,
    PMU_RG_GPIOQ_DIN_POS = 0,
    PMU_RG_GPIOQ_HSS_MASK = (int)0xffff0000,
    PMU_RG_GPIOQ_HSS_POS = 16,
};

enum PMU_RG_REG_IOT_LVS_LOCK_FIELD
{
    PMU_RG_GPIOT_LOCK_MASK = (int)0xffff,
    PMU_RG_GPIOT_LOCK_POS = 0,
    PMU_RG_GPIOT_LVS_MASK = (int)0xffff0000,
    PMU_RG_GPIOT_LVS_POS = 16,
};

enum PMU_RG_REG_IOT_DOT_FIELD
{
    PMU_RG_GPIOT_DOT_MASK = (int)0xffff,
    PMU_RG_GPIOT_DOT_POS = 0,
};

enum PMU_RG_REG_IOT_PD_PU_FIELD
{
    PMU_RG_GPIOT_PU_MASK = (int)0xffff,
    PMU_RG_GPIOT_PU_POS = 0,
    PMU_RG_GPIOT_PD_MASK = (int)0xffff0000,
    PMU_RG_GPIOT_PD_POS = 16,
};

enum PMU_RG_REG_IOT_REN_ODE_FIELD
{
    PMU_RG_GPIOT_ODE_MASK = (int)0xffff,
    PMU_RG_GPIOT_ODE_POS = 0,
    PMU_RG_GPIOT_REN_MASK = (int)0xffff0000,
    PMU_RG_GPIOT_REN_POS = 16,
};

enum PMU_RG_REG_IOT_DS1_DS2_FIELD
{
    PMU_RG_GPIOT_DS2_MASK = (int)0xffff,
    PMU_RG_GPIOT_DS2_POS = 0,
    PMU_RG_GPIOT_DS1_MASK = (int)0xffff0000,
    PMU_RG_GPIOT_DS1_POS = 16,
};

enum PMU_RG_REG_IOT_AE1_AE2_FIELD
{
    PMU_RG_GPIOT_AE2_MASK = (int)0xffff,
    PMU_RG_GPIOT_AE2_POS = 0,
    PMU_RG_GPIOT_AE1_MASK = (int)0xffff0000,
    PMU_RG_GPIOT_AE1_POS = 16,
};

enum PMU_RG_REG_IOT_OTE_FIR_FIELD
{
    PMU_RG_GPIOT_FIR_MASK = (int)0xffff,
    PMU_RG_GPIOT_FIR_POS = 0,
    PMU_RG_GPIOT_OTE_MASK = (int)0xffff0000,
    PMU_RG_GPIOT_OTE_POS = 16,
};

enum PMU_RG_REG_IOT_HSS_DIN_FIELD
{
    PMU_RG_GPIOT_DIN_MASK = (int)0xffff,
    PMU_RG_GPIOT_DIN_POS = 0,
    PMU_RG_GPIOT_HSS_MASK = (int)0xffff0000,
    PMU_RG_GPIOT_HSS_POS = 16,
};

#endif

