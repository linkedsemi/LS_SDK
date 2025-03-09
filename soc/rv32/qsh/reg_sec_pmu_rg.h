#ifndef REG_SEC_PMU_RG_TYPE_H_
#define REG_SEC_PMU_RG_TYPE_H_
#include <stdint.h>
#include "reg_base_addr.h"

#define SEC_PMU ((reg_sec_pmu_rg_t *)SEC_PMU_RG_SEC_ADDR)

typedef struct {
    volatile uint32_t LOCK;
    volatile uint32_t RESERVED[7];
} reg_sec_io_cfg_t;

typedef struct {
    volatile uint32_t DIN;       //0x0
    volatile uint32_t RESERVED0; //0x4
} reg_sec_io_val_t;

typedef struct
{
    volatile uint32_t RESERVED0[4]; //0x0
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
    volatile uint32_t HSE_CAP; //0x38
    volatile uint32_t PMU_STATUS; //0x3c
    volatile uint32_t SFT_CTRL[16]; //0x40
    volatile uint32_t GPIO_INTR_MSK[16]; //0x80
    volatile uint32_t GPIO_INTR_LOCK[16]; //0xc0
    volatile uint32_t GPIO_INTR_STT[16]; //0x100
    volatile uint32_t GPIO_INTR_RAW[16]; //0x140
    union {
        reg_sec_io_cfg_t IO_CFG[15];//0x180 GPIO[A-T]
        struct {
            volatile uint32_t RESERVED1[113];
            volatile uint32_t QSPI_PAD_LOCK; //0x344
            volatile uint32_t PECI_PAD_LOCK; //0x348
            volatile uint32_t RESERVED2[5];
        };
    };
    reg_sec_io_val_t IO_VAL[16];//0x360
    volatile uint32_t MODE_PAD_LOCK_ST; //0x3e0
    volatile uint32_t MODE_PAD_PU_PD; //0x3e4
    volatile uint32_t MODE_PAD_REN_DS0; //0x3e8
    volatile uint32_t MODE_PAD_DS1_FIR; //0x3ec
    volatile uint32_t MODE_PAD_OE_DIN; //0x3f0
    volatile uint32_t MODE_PAD_DOT; //0x3f4
#if 0
    volatile uint32_t GPIOA_INTR_MSK; //0x80
    volatile uint32_t GPIOB_INTR_MSK; //0x80
    volatile uint32_t GPIOC_INTR_MSK; //0x88
    volatile uint32_t GPIOD_INTR_MSK; //0x8C
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
    volatile uint32_t GPIOV_INTR_MSK; //0xbc
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
    volatile uint32_t GPIOV_INTR_CLR; //0xfc
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
    volatile uint32_t GPIOV_INTR_STT; //0x13c
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
    volatile uint32_t GPIOV_INTR_RAW; //0x17c
    volatile uint32_t IOA_LOCK; //0x180
    volatile uint32_t IOB_LOCK; //0x1a0
    volatile uint32_t IOC_LOCK; //0x1c0
    volatile uint32_t IOD_LOCK; //0x1e0
    volatile uint32_t IOE_LOCK; //0x200
    volatile uint32_t IOF_LOCK; //0x220
    volatile uint32_t IOG_LOCK; //0x240
    volatile uint32_t IOH_LOCK; //0x260
    volatile uint32_t IOI_LOCK; //0x280
    volatile uint32_t IOJ_LOCK; //0x2a0
    volatile uint32_t IOK_LOCK; //0x2c0
    volatile uint32_t IOM_LOCK; //0x2e0
    volatile uint32_t ION_LOCK; //0x300
    volatile uint32_t IOQ_LOCK; //0x320
    volatile uint32_t IOT_LOCK; //0x340
    volatile uint32_t QSPI1_PAD_LOCK; //0x344
    volatile uint32_t PECI_LOCK; //0x348
    volatile uint32_t GPIO_A_DIN; //0x360
    volatile uint32_t GPIO_B_DIN; //0x368
    volatile uint32_t GPIO_C_DIN; //0x370
    volatile uint32_t GPIO_D_DIN; //0x378
    volatile uint32_t GPIO_E_DIN; //0x380
    volatile uint32_t GPIO_F_DIN; //0x388
    volatile uint32_t GPIO_G_DIN; //0x390
    volatile uint32_t GPIO_H_DIN; //0x398
    volatile uint32_t GPIO_I_DIN; //0x3a0
    volatile uint32_t GPIO_J_DIN; //0x3a8
    volatile uint32_t GPIO_K_DIN; //0x3b0
    volatile uint32_t GPIO_M_DIN; //0x3b8
    volatile uint32_t GPIO_N_DIN; //0x3c0
    volatile uint32_t GPIO_Q_DIN; //0x3c8
    volatile uint32_t GPIO_T_DIN; //0x3d0
    volatile uint32_t GPIO_V_DIN; //0x3d8
    volatile uint32_t MODE_PAD_LOCK_ST; //0x3e0
    volatile uint32_t MODE_PAD_PU_PD; //0x3e4
    volatile uint32_t MODE_PAD_REN_DS0; //0x3e8
    volatile uint32_t MODE_PAD_DS1_FIR; //0x3ec
    volatile uint32_t MODE_PAD_OE_DIN; //0x3f0
    volatile uint32_t MODE_PAD_DOT; //0x3f4
#endif
}reg_sec_pmu_rg_t;
_Static_assert(sizeof(reg_sec_pmu_rg_t) == 0x3f8, "reg_sec_pmu_rg_t size error.");
_Static_assert((uint32_t)(&((reg_sec_pmu_rg_t *)0)->QSPI_PAD_LOCK) == 0x344, "reg_sec_pmu_rg_t QSPI_PAD_LOCK offset error.");
_Static_assert((uint32_t)(((reg_sec_pmu_rg_t *)0)->IO_VAL) == 0x360, "reg_sec_pmu_rg_t IO_VAL offset error.");

enum SEC_PMU_RG_REG_SFT_CTRL00_FIELD
{
    SEC_PMU_RG_SFT_CTRL00_MASK = (int)0xffffffff,
    SEC_PMU_RG_SFT_CTRL00_POS = 0,
};

enum SEC_PMU_RG_REG_SFT_CTRL01_FIELD
{
    SEC_PMU_RG_SFT_CTRL01_MASK = (int)0xffffffff,
    SEC_PMU_RG_SFT_CTRL01_POS = 0,
};

enum SEC_PMU_RG_REG_SFT_CTRL02_FIELD
{
    SEC_PMU_RG_SFT_CTRL02_MASK = (int)0xffffffff,
    SEC_PMU_RG_SFT_CTRL02_POS = 0,
};

enum SEC_PMU_RG_REG_SFT_CTRL03_FIELD
{
    SEC_PMU_RG_SFT_CTRL03_MASK = (int)0xffffffff,
    SEC_PMU_RG_SFT_CTRL03_POS = 0,
};

enum SEC_PMU_RG_REG_MISC_CTRL0_FIELD
{
    SEC_PMU_RG_LVD33_INTR_EN_MASK = (int)0x1,
    SEC_PMU_RG_LVD33_INTR_EN_POS = 0,
    SEC_PMU_RG_LVD33_POL_MASK = (int)0x2,
    SEC_PMU_RG_LVD33_POL_POS = 1,
    SEC_PMU_RG_LVD33_INTR_CLR_MASK = (int)0x4,
    SEC_PMU_RG_LVD33_INTR_CLR_POS = 2,
    SEC_PMU_RG_CLK_LDO1_VSEL_MASK = (int)0x70,
    SEC_PMU_RG_CLK_LDO1_VSEL_POS = 4,
    SEC_PMU_RG_CLK_LDO2_VSEL_MASK = (int)0x700,
    SEC_PMU_RG_CLK_LDO2_VSEL_POS = 8,
    SEC_PMU_RG_HSI_FC_EN_MASK = (int)0x800,
    SEC_PMU_RG_HSI_FC_EN_POS = 11,
    SEC_PMU_RG_USB1_CID_MASK = (int)0x3000,
    SEC_PMU_RG_USB1_CID_POS = 12,
    SEC_PMU_RG_PD_ADC12_MASK = (int)0x4000,
    SEC_PMU_RG_PD_ADC12_POS = 14,
    SEC_PMU_RG_LKRST_TIM_MASK = (int)0x3f0000,
    SEC_PMU_RG_LKRST_TIM_POS = 16,
    SEC_PMU_RG_LKRST_EN_MASK = (int)0x400000,
    SEC_PMU_RG_LKRST_EN_POS = 22,
    SEC_PMU_RG_LKRST_POL_MASK = (int)0x800000,
    SEC_PMU_RG_LKRST_POL_POS = 23,
    SEC_PMU_RG_LKRST_SEL_MASK = (int)0x1f000000,
    SEC_PMU_RG_LKRST_SEL_POS = 24,
    SEC_PMU_RG_BOR09_CTRL_MASK = (int)0xe0000000,
    SEC_PMU_RG_BOR09_CTRL_POS = 29,
};

enum SEC_PMU_RG_REG_TRIM0_FIELD
{
    SEC_PMU_RG_SPI_CODE_MASK = (int)0xfff,
    SEC_PMU_RG_SPI_CODE_POS = 0,
    SEC_PMU_RG_HSE_CTRL_MASK = (int)0x7000,
    SEC_PMU_RG_HSE_CTRL_POS = 12,
    SEC_PMU_RG_LDO_PECI_VSEL_MASK = (int)0xf0000,
    SEC_PMU_RG_LDO_PECI_VSEL_POS = 16,
    SEC_PMU_RG_LDO_PECI_EN_MASK = (int)0x80000,
    SEC_PMU_RG_LDO_PECI_EN_POS = 19,
    SEC_PMU_RG_BG_TESTEN_MASK = (int)0x800000,
    SEC_PMU_RG_BG_TESTEN_POS = 23,
    SEC_PMU_RG_XO32K_CODE_MASK = (int)0x1000000,
    SEC_PMU_RG_XO32K_CODE_POS = 24,
    SEC_PMU_RG_XO32K_OE_BYP_MASK = (int)0x2000000,
    SEC_PMU_RG_XO32K_OE_BYP_POS = 25,
    SEC_PMU_RG_RCO_I_ADJ_MASK = (int)0x4000000,
    SEC_PMU_RG_RCO_I_ADJ_POS = 26,
    SEC_PMU_RG_MSI_CAL_MASK = (int)0xf0000000,
    SEC_PMU_RG_MSI_CAL_POS = 28,
};

enum SEC_PMU_RG_REG_ANA_PMU_CTRL_FIELD
{
    SEC_PMU_RG_LPLDO_TRIM_MASK = (int)0xf,
    SEC_PMU_RG_LPLDO_TRIM_POS = 0,
    SEC_PMU_RG_HPLDO_TRIM_MASK = (int)0xf0,
    SEC_PMU_RG_HPLDO_TRIM_POS = 4,
    SEC_PMU_RG_BG_VREF_TRIM_MASK = (int)0x3f00,
    SEC_PMU_RG_BG_VREF_TRIM_POS = 8,
    SEC_PMU_RG_BG_VREF_FINE_MASK = (int)0xc000,
    SEC_PMU_RG_BG_VREF_FINE_POS = 14,
    SEC_PMU_RG_BG_IBG_TRIM_MASK = (int)0xf0000,
    SEC_PMU_RG_BG_IBG_TRIM_POS = 16,
    SEC_PMU_RG_BOR33_CTRL_MASK = (int)0xf00000,
    SEC_PMU_RG_BOR33_CTRL_POS = 20,
    SEC_PMU_RG_LVD33_CTRL_MASK = (int)0x1f000000,
    SEC_PMU_RG_LVD33_CTRL_POS = 24,
    SEC_PMU_RG_BATDET_CTRL_MASK = (int)0xe0000000,
    SEC_PMU_RG_BATDET_CTRL_POS = 29,
};

enum SEC_PMU_RG_REG_WKUP_CTRL_FIELD
{
    SEC_PMU_RG_WKUP_MSK_MASK = (int)0x7f,
    SEC_PMU_RG_WKUP_MSK_POS = 0,
    SEC_PMU_RG_SWD_IO_WKUP_EN_MASK = (int)0x10000,
    SEC_PMU_RG_SWD_IO_WKUP_EN_POS = 16,
    SEC_PMU_RG_WKUP0_SYNC_SEL_MASK = (int)0x100000,
    SEC_PMU_RG_WKUP0_SYNC_SEL_POS = 20,
    SEC_PMU_RG_WKUP1_SYNC_SEL_MASK = (int)0x200000,
    SEC_PMU_RG_WKUP1_SYNC_SEL_POS = 21,
};

enum SEC_PMU_RG_REG_WKUP_TIM0_FIELD
{
    SEC_PMU_RG_STB_BG_M1_MASK = (int)0xffff,
    SEC_PMU_RG_STB_BG_M1_POS = 0,
    SEC_PMU_RG_STB_PSW_M1_MASK = (int)0xff0000,
    SEC_PMU_RG_STB_PSW_M1_POS = 16,
    SEC_PMU_RG_STB_HSI_M1_MASK = (int)0xf0000000,
    SEC_PMU_RG_STB_HSI_M1_POS = 28,
};

enum SEC_PMU_RG_REG_WKUP_TIM1_FIELD
{
    SEC_PMU_RG_STB_CLK_M1_MASK = (int)0xfff,
    SEC_PMU_RG_STB_CLK_M1_POS = 0,
    SEC_PMU_RG_STB_LDO_M1_MASK = (int)0xfff000,
    SEC_PMU_RG_STB_LDO_M1_POS = 12,
};

enum SEC_PMU_RG_REG_RST_SFT_FIELD
{
    SEC_PMU_RG_RST_FROM_SFT_MASK = (int)0x1,
    SEC_PMU_RG_RST_FROM_SFT_POS = 0,
    SEC_PMU_RG_CLK_SEL_LSC_MASK = (int)0x30,
    SEC_PMU_RG_CLK_SEL_LSC_POS = 4,
    SEC_PMU_RG_RST_SRC_CLR_MASK = (int)0x100,
    SEC_PMU_RG_RST_SRC_CLR_POS = 8,
};

enum SEC_PMU_RG_REG_CLKG_SRST_FIELD
{
    SEC_PMU_RG_CLKG_SET_WDT_MASK = (int)0x4,
    SEC_PMU_RG_CLKG_SET_WDT_POS = 2,
    SEC_PMU_RG_CLKG_CLR_WDT_MASK = (int)0x8,
    SEC_PMU_RG_CLKG_CLR_WDT_POS = 3,
};

enum SEC_PMU_RG_REG_PMU_SET_VAL_FIELD
{
    SEC_PMU_RG_CLK_SET_LSE_MASK = (int)0x1,
    SEC_PMU_RG_CLK_SET_LSE_POS = 0,
    SEC_PMU_RG_CLK_SET_HSI_MASK = (int)0x2,
    SEC_PMU_RG_CLK_SET_HSI_POS = 1,
    SEC_PMU_RG_CLK_SET_HSE_MASK = (int)0x4,
    SEC_PMU_RG_CLK_SET_HSE_POS = 2,
    SEC_PMU_RG_SRAM_DS_SET_MASK = (int)0xfff00,
    SEC_PMU_RG_SRAM_DS_SET_POS = 8,
    SEC_PMU_RG_PMU_SET_TGGL_MASK = (int)0x80000000,
    SEC_PMU_RG_PMU_SET_TGGL_POS = 31,
};

enum SEC_PMU_RG_REG_PWR_CTRL_FIELD
{
    SEC_PMU_RG_HPLDO_PD_EN_MASK = (int)0x2,
    SEC_PMU_RG_HPLDO_PD_EN_POS = 1,
    SEC_PMU_RG_BG_PD_EN_MASK = (int)0x4,
    SEC_PMU_RG_BG_PD_EN_POS = 2,
    SEC_PMU_RG_BGIB_PD_EN_MASK = (int)0x8,
    SEC_PMU_RG_BGIB_PD_EN_POS = 3,
    SEC_PMU_RG_MSI_PD_EN_MASK = (int)0x10,
    SEC_PMU_RG_MSI_PD_EN_POS = 4,
    SEC_PMU_RG_LSI_PD_EN_MASK = (int)0x20,
    SEC_PMU_RG_LSI_PD_EN_POS = 5,
    SEC_PMU_RG_LSE_PD_EN_MASK = (int)0x40,
    SEC_PMU_RG_LSE_PD_EN_POS = 6,
    SEC_PMU_RG_HSE_PD_EN_MASK = (int)0x80,
    SEC_PMU_RG_HSE_PD_EN_POS = 7,
    SEC_PMU_RG_HSI_PD_EN_MASK = (int)0x100,
    SEC_PMU_RG_HSI_PD_EN_POS = 8,
    SEC_PMU_RG_SRAM_DS_PD_EN_MASK = (int)0x200,
    SEC_PMU_RG_SRAM_DS_PD_EN_POS = 9,
    SEC_PMU_RG_LSE_PU_EN_MASK = (int)0x400,
    SEC_PMU_RG_LSE_PU_EN_POS = 10,
    SEC_PMU_RG_HSE_PU_EN_MASK = (int)0x800,
    SEC_PMU_RG_HSE_PU_EN_POS = 11,
    SEC_PMU_RG_SRAM_DS_PU_EN_MASK = (int)0x1000,
    SEC_PMU_RG_SRAM_DS_PU_EN_POS = 12,
    SEC_PMU_RG_RCO_BIAS_FC_MASK = (int)0x2000,
    SEC_PMU_RG_RCO_BIAS_FC_POS = 13,
    SEC_PMU_RG_PD_GPIO_SEL_MASK = (int)0x4000,
    SEC_PMU_RG_PD_GPIO_SEL_POS = 14,
    SEC_PMU_RG_HPSW1_PD_EN_MASK = (int)0x10000,
    SEC_PMU_RG_HPSW1_PD_EN_POS = 16,
    SEC_PMU_RG_HPSW2_PD_EN_MASK = (int)0x20000,
    SEC_PMU_RG_HPSW2_PD_EN_POS = 17,
    SEC_PMU_RG_SRAM0_PD_EN_MASK = (int)0x40000,
    SEC_PMU_RG_SRAM0_PD_EN_POS = 18,
    SEC_PMU_RG_SRAM1_PD_EN_MASK = (int)0x80000,
    SEC_PMU_RG_SRAM1_PD_EN_POS = 19,
    SEC_PMU_RG_SRAM2_PD_EN_MASK = (int)0x100000,
    SEC_PMU_RG_SRAM2_PD_EN_POS = 20,
    SEC_PMU_RG_SRAM3_PD_EN_MASK = (int)0x200000,
    SEC_PMU_RG_SRAM3_PD_EN_POS = 21,
    SEC_PMU_RG_SRAM4_PD_EN_MASK = (int)0x400000,
    SEC_PMU_RG_SRAM4_PD_EN_POS = 22,
    SEC_PMU_RG_SRAM5_PD_EN_MASK = (int)0x800000,
    SEC_PMU_RG_SRAM5_PD_EN_POS = 23,
    SEC_PMU_RG_SRAM6_PD_EN_MASK = (int)0x1000000,
    SEC_PMU_RG_SRAM6_PD_EN_POS = 24,
    SEC_PMU_RG_SRAM7_PD_EN_MASK = (int)0x2000000,
    SEC_PMU_RG_SRAM7_PD_EN_POS = 25,
    SEC_PMU_RG_SRAM8_PD_EN_MASK = (int)0x4000000,
    SEC_PMU_RG_SRAM8_PD_EN_POS = 26,
    SEC_PMU_RG_SRAM9_PD_EN_MASK = (int)0x8000000,
    SEC_PMU_RG_SRAM9_PD_EN_POS = 27,
    SEC_PMU_RG_SRAM10_PD_EN_MASK = (int)0x10000000,
    SEC_PMU_RG_SRAM10_PD_EN_POS = 28,
    SEC_PMU_RG_SRAM11_PD_EN_MASK = (int)0x20000000,
    SEC_PMU_RG_SRAM11_PD_EN_POS = 29,
};

enum SEC_PMU_RG_REG_HSE_CAP_FIELD
{
    SEC_PMU_RG_HSE_CAP_MASK = (int)0x3f,
    SEC_PMU_RG_HSE_CAP_POS = 0,
};

enum SEC_PMU_RG_REG_PMU_STATUS_FIELD
{
    SEC_PMU_RG_LSE_EN_MASK = (int)0x1,
    SEC_PMU_RG_LSE_EN_POS = 0,
    SEC_PMU_RG_HSI_EN_MASK = (int)0x2,
    SEC_PMU_RG_HSI_EN_POS = 1,
    SEC_PMU_RG_HSE_EN_MASK = (int)0x4,
    SEC_PMU_RG_HSE_EN_POS = 2,
    SEC_PMU_RG_VREF_OK_MASK = (int)0x8,
    SEC_PMU_RG_VREF_OK_POS = 3,
    SEC_PMU_RG_SRAM_DS_MASK = (int)0x7f00,
    SEC_PMU_RG_SRAM_DS_POS = 8,
    SEC_PMU_RG_EXTI_INTR_MASK = (int)0x10000,
    SEC_PMU_RG_EXTI_INTR_POS = 16,
    SEC_PMU_RG_LVD33_INTR_MASK = (int)0x20000,
    SEC_PMU_RG_LVD33_INTR_POS = 17,
    SEC_PMU_RG_LVD33_DTCT_MASK = (int)0x40000,
    SEC_PMU_RG_LVD33_DTCT_POS = 18,
    SEC_PMU_RG_RST_SRC_MASK = (int)0x7f000000,
    SEC_PMU_RG_RST_SRC_POS = 24,
};

enum SEC_PMU_RG_REG_IO_LOCK_FIELD
{
    SEC_PMU_RG_GPIO_LOCK_MASK = (int)0xffff,
    SEC_PMU_RG_GPIO_LOCK_POS = 0,
    SEC_PMU_RG_GPIO_DIN_LOCK_MASK = (int)0xffff0000,
    SEC_PMU_RG_GPIO_DIN_LOCK_POS = 16,
};

enum SEC_PMU_RG_REG_IO_DIN_OE_FIELD
{
    SEC_PMU_RG_GPIO_DIN_MASK = (int)0xffff,
    SEC_PMU_RG_GPIO_DIN_POS = 0,
};

enum SEC_PMU_RG_REG_MODE_PAD_LOCK_ST_FIELD
{
    SEC_PMU_RG_MODE_PAD_LOCK_MASK = (int)0xf,
    SEC_PMU_RG_MODE_PAD_LOCK_POS = 0,
    SEC_PMU_RG_MODE_PAD_ST_MASK = (int)0xf0000,
    SEC_PMU_RG_MODE_PAD_ST_POS = 16,
};

enum SEC_PMU_RG_REG_MODE_PAD_PU_PD_FIELD
{
    SEC_PMU_RG_MODE_PAD_PU_MASK = (int)0xf,
    SEC_PMU_RG_MODE_PAD_PU_POS = 0,
    SEC_PMU_RG_MODE_PAD_PD_MASK = (int)0xf0000,
    SEC_PMU_RG_MODE_PAD_PD_POS = 16,
};

enum SEC_PMU_RG_REG_MODE_PAD_REN_DS0_FIELD
{
    SEC_PMU_RG_MODE_PAD_REN_MASK = (int)0xf,
    SEC_PMU_RG_MODE_PAD_REN_POS = 0,
    SEC_PMU_RG_MODE_PAD_DS0_MASK = (int)0xf0000,
    SEC_PMU_RG_MODE_PAD_DS0_POS = 16,
};

enum SEC_PMU_RG_REG_MODE_PAD_DS1_FIR_FIELD
{
    SEC_PMU_RG_MODE_PAD_DS1_MASK = (int)0xf,
    SEC_PMU_RG_MODE_PAD_DS1_POS = 0,
    SEC_PMU_RG_MODE_PAD_FIR_MASK = (int)0xf0000,
    SEC_PMU_RG_MODE_PAD_FIR_POS = 16,
};

enum SEC_PMU_RG_REG_MODE_PAD_OE_DIN_FIELD
{
    SEC_PMU_RG_MODE_PAD_DIN_MASK = (int)0xf,
    SEC_PMU_RG_MODE_PAD_DIN_POS = 0,
    SEC_PMU_RG_MODE_PAD_OE_MASK = (int)0xf0000,
    SEC_PMU_RG_MODE_PAD_OE_POS = 16,
};

enum SEC_PMU_RG_REG_MODE_PAD_DOT_FIELD
{
    SEC_PMU_RG_MODE_PAD_DOT_MASK = (int)0xf,
    SEC_PMU_RG_MODE_PAD_DOT_POS = 0,
};
#endif

