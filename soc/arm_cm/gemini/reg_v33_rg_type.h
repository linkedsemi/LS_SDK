#ifndef REG_V33_RG_TYPE_H_
#define REG_V33_RG_TYPE_H_
#include <stdint.h>

#define V33_RG ((reg_v33_rg_t *)0x4000F000)

typedef struct
{
    volatile uint32_t SFT_CTRL00; //0x0
    volatile uint32_t SFT_CTRL01; //0x4
    volatile uint32_t SFT_CTRL02; //0x8
    volatile uint32_t SFT_CTRL03; //0xc
    volatile uint32_t MISC_CTRL0; //0x10
    volatile uint32_t TRIM0; //0x14
    volatile uint32_t SRAM_LOCK; //0x18
    volatile uint32_t ANA_PMU_CTRL; //0x1c
    volatile uint32_t MISC_CTRL1; //0x20
    volatile uint32_t WKUP_CTRL; //0x24
    volatile uint32_t RST_SFT; //0x28
    volatile uint32_t CLKG_SRST; //0x2c
    volatile uint32_t RST_SRC_CLR; //0x30
    volatile uint32_t WKUP_TIM; //0x34
    volatile uint32_t PMU_SET_VAL; //0x38
    volatile uint32_t PWR_CTRL; //0x3c
    volatile uint32_t EXTI_CTRL0; //0x40
    volatile uint32_t WKUP_TIM1; //0x44
    volatile uint32_t RESERVED0[2];
    volatile uint32_t EXTI_CTRL2; //0x50
    volatile uint32_t GPIO_SEL; //0x54
    volatile uint32_t GPIO_FIR; //0x58
    volatile uint32_t RESERVED1[1];
    volatile uint32_t GPIO_INTR; //0x60
    volatile uint32_t RESERVED2[1];
    volatile uint32_t GPIO_INTR_RAW; //0x68
    volatile uint32_t RESERVED3[2];
    volatile uint32_t RST_SRC; //0x74
    volatile uint32_t EXT_INTR; //0x78
    volatile uint32_t CLK_STAT; //0x7c
    volatile uint32_t VREF_OK; //0x80
    volatile uint32_t COMP_STAT; //0x84
    volatile uint32_t RESERVED4[2];
    volatile uint32_t OP_CTRL; //0x90
    volatile uint32_t COMP1_CTRL; //0x94
    volatile uint32_t COMP2_CTRL; //0x98
    volatile uint32_t COMP3_CTRL; //0x9c
}reg_v33_rg_t;

enum V33_RG_REG_SFT_CTRL00_FIELD
{
    V33_RG_SFT_CTRL00_MASK = (int)0xffffffff,
    V33_RG_SFT_CTRL00_POS = 0,
};

enum V33_RG_REG_SFT_CTRL01_FIELD
{
    V33_RG_SFT_CTRL01_MASK = (int)0xffffffff,
    V33_RG_SFT_CTRL01_POS = 0,
};

enum V33_RG_REG_SFT_CTRL02_FIELD
{
    V33_RG_SFT_CTRL02_MASK = (int)0xffffffff,
    V33_RG_SFT_CTRL02_POS = 0,
};

enum V33_RG_REG_SFT_CTRL03_FIELD
{
    V33_RG_SFT_CTRL03_MASK = (int)0xffffffff,
    V33_RG_SFT_CTRL03_POS = 0,
};

enum V33_RG_REG_MISC_CTRL0_FIELD
{
    V33_RG_LVD33_INTR_EN_MASK = (int)0x1,
    V33_RG_LVD33_INTR_EN_POS = 0,
    V33_RG_LVD33_POL_MASK = (int)0x2,
    V33_RG_LVD33_POL_POS = 1,
    V33_RG_LVD33_INTR_CLR_MASK = (int)0x4,
    V33_RG_LVD33_INTR_CLR_POS = 2,
    V33_RG_LVD33_INTR_MASK = (int)0x40,
    V33_RG_LVD33_INTR_POS = 6,
    V33_RG_LVD33_DTCT_MASK = (int)0x80,
    V33_RG_LVD33_DTCT_POS = 7,
    V33_RG_LKRST_TIM_MASK = (int)0x3f0000,
    V33_RG_LKRST_TIM_POS = 16,
    V33_RG_LKRST_EN_MASK = (int)0x400000,
    V33_RG_LKRST_EN_POS = 22,
    V33_RG_LKRST_POL_MASK = (int)0x800000,
    V33_RG_LKRST_POL_POS = 23,
};

enum V33_RG_REG_TRIM0_FIELD
{
    V33_RG_SPI_CODE_MASK = (int)0xfff,
    V33_RG_SPI_CODE_POS = 0,
    V33_RG_HSE_BIAS_ADJ_MASK = (int)0x3000,
    V33_RG_HSE_BIAS_ADJ_POS = 12,
    V33_RG_HSE_LP_MASK = (int)0x4000,
    V33_RG_HSE_LP_POS = 14,
    V33_RG_RCO_I_ADJ_MASK = (int)0x10000,
    V33_RG_RCO_I_ADJ_POS = 16,
    V33_RG_XO32K_CODE_MASK = (int)0x1000000,
    V33_RG_XO32K_CODE_POS = 24,
    V33_RG_XO32K_OE_BYP_MASK = (int)0x2000000,
    V33_RG_XO32K_OE_BYP_POS = 25,
    V33_RG_MSI_CAL_MASK = (int)0xf0000000,
    V33_RG_MSI_CAL_POS = 28,
};

enum V33_RG_REG_SRAM_LOCK_FIELD
{
    V33_RG_SRAM_ACC_LOCK_MASK = (int)0x1,
    V33_RG_SRAM_ACC_LOCK_POS = 0,
    V33_RG_SRAM_ACC_MASK = (int)0xf00,
    V33_RG_SRAM_ACC_POS = 8,
    V33_RG_DPLL_DIS_MASK = (int)0x10000,
    V33_RG_DPLL_DIS_POS = 16,
};

enum V33_RG_REG_ANA_PMU_CTRL_FIELD
{
    V33_RG_LPLDO_TRIM_MASK = (int)0xf,
    V33_RG_LPLDO_TRIM_POS = 0,
    V33_RG_HPLDO_TRIM_MASK = (int)0x30,
    V33_RG_HPLDO_TRIM_POS = 4,
    V33_RG_BG_CTRL_MASK = (int)0xfff00,
    V33_RG_BG_CTRL_POS = 8,
    V33_RG_BOR_EN_MASK = (int)0x100000,
    V33_RG_BOR_EN_POS = 20,
    V33_RG_BOR_CTRL_MASK = (int)0xe00000,
    V33_RG_BOR_CTRL_POS = 21,
    V33_RG_LVD_CTRL_MASK = (int)0xf000000,
    V33_RG_LVD_CTRL_POS = 24,
    V33_RG_LVD_EN_MASK = (int)0x10000000,
    V33_RG_LVD_EN_POS = 28,
    V33_RG_BAT_DET_EN_MASK=(int)0x20000000,
    V33_RG_BAT_DET_EN_POS=29,
    V33_RG_BAT_DET_ADJ_MASK=(int)0xC0000000,
    V33_RG_BAT_DET_ADJ_POS=30,
};

enum V33_RG_REG_MISC_CTRL1_FIELD
{
    V33_RG_LATCH_GPIO_MASK = (int)0x1,
    V33_RG_LATCH_GPIO_POS = 0,
    V33_RG_PD_GPIO_MASK = (int)0x2,
    V33_RG_PD_GPIO_POS = 1,
    V33_RG_PD_ADC12_MASK = (int)0x4,
    V33_RG_PD_ADC12_POS = 2,
    V33_RG_PD_AMIC_MASK = (int)0x8,
    V33_RG_PD_AMIC_POS = 3,
    V33_RG_PD_TK_MASK = (int)0x10,
    V33_RG_PD_TK_POS = 4,
    V33_RG_PD_DAC12_MASK = (int)0x20,
    V33_RG_PD_DAC12_POS = 5,
    V33_RG_BAT_DTCT_EN_MASK = (int)0x40,
    V33_RG_BAT_DTCT_EN_POS = 6,
};

enum V33_RG_REG_WKUP_CTRL_FIELD
{
    V33_RG_WKUP_MSK_MASK = (int)0x3f,
    V33_RG_WKUP_MSK_POS = 0,
    V33_RG_SWD_IO_WKUP_EN_MASK = (int)0x10000,
    V33_RG_SWD_IO_WKUP_EN_POS = 16,
    V33_RG_WKUP0_SYNC_SEL_MASK = (int)0x100000,
    V33_RG_WKUP0_SYNC_SEL_POS = 20,
    V33_RG_WKUP1_SYNC_SEL_MASK = (int)0x200000,
    V33_RG_WKUP1_SYNC_SEL_POS = 21,
};

enum V33_RG_REG_RST_SFT_FIELD
{
    V33_RG_RST_FROM_SFT_MASK = (int)0x1,
    V33_RG_RST_FROM_SFT_POS = 0,
    V33_RG_CLK_SEL_LS_MASK = (int)0x30,
    V33_RG_CLK_SEL_LS_POS = 4,
};

enum V33_RG_REG_CLKG_SRST_FIELD
{
    V33_RG_CLKG_SET_TIM_MASK = (int)0x1,
    V33_RG_CLKG_SET_TIM_POS = 0,
    V33_RG_CLKG_CLR_TIM_MASK = (int)0x2,
    V33_RG_CLKG_CLR_TIM_POS = 1,
    V33_RG_CLKG_SET_WDT_MASK = (int)0x4,
    V33_RG_CLKG_SET_WDT_POS = 2,
    V33_RG_CLKG_CLR_WDT_MASK = (int)0x8,
    V33_RG_CLKG_CLR_WDT_POS = 3,
    V33_RG_CLKG_SET_RTC_MASK = (int)0x10,
    V33_RG_CLKG_SET_RTC_POS = 4,
    V33_RG_CLKG_CLR_RTC_MASK = (int)0x20,
    V33_RG_CLKG_CLR_RTC_POS = 5,
    V33_RG_CLKG_SET_CMP_MASK = (int)0x40,
    V33_RG_CLKG_SET_CMP_POS = 6,
    V33_RG_CLKG_CLR_CMP_MASK = (int)0x80,
    V33_RG_CLKG_CLR_CMP_POS = 7,
};

enum V33_RG_REG_RST_SRC_CLR_FIELD
{
    V33_RG_RST_SRC_CLR_MASK = (int)0x1,
    V33_RG_RST_SRC_CLR_POS = 0,
};

enum V33_RG_REG_WKUP_TIM_FIELD
{
    V33_RG_STB_CLK_M1_MASK = (int)0xfff,
    V33_RG_STB_CLK_M1_POS = 0,
    V33_RG_STB_LDO_M1_MASK = (int)0x3ff000,
    V33_RG_STB_LDO_M1_POS = 12,
};

enum V33_RG_REG_PMU_SET_VAL_FIELD
{
    V33_RG_CLK_SET_LSE_MASK = (int)0x1,
    V33_RG_CLK_SET_LSE_POS = 0,
    V33_RG_CLK_SET_HSI_MASK = (int)0x2,
    V33_RG_CLK_SET_HSI_POS = 1,
    V33_RG_CLK_SET_HSE_MASK = (int)0x4,
    V33_RG_CLK_SET_HSE_POS = 2,
    V33_RG_SRAM_DS_SET_MASK = (int)0x1fff00,
    V33_RG_SRAM_DS_SET_POS = 8,
    V33_RG_PMU_SET_TGGL_MASK = (int)0x80000000,
    V33_RG_PMU_SET_TGGL_POS = 31,
};

enum V33_RG_REG_PWR_CTRL_FIELD
{
    V33_RG_LPLDO_PD_EN_MASK = (int)0x1,
    V33_RG_LPLDO_PD_EN_POS = 0,
    V33_RG_HPLDO_PD_EN_MASK = (int)0x2,
    V33_RG_HPLDO_PD_EN_POS = 1,
    V33_RG_MSI_PD_EN_MASK = (int)0x4,
    V33_RG_MSI_PD_EN_POS = 2,
    V33_RG_BG_PD_EN_MASK = (int)0x8,
    V33_RG_BG_PD_EN_POS = 3,
    V33_RG_BGIB_PD_EN_MASK = (int)0x10,
    V33_RG_BGIB_PD_EN_POS = 4,
    V33_RG_LSI_PD_EN_MASK = (int)0x20,
    V33_RG_LSI_PD_EN_POS = 5,
    V33_RG_HSE_PD_EN_MASK = (int)0x40,
    V33_RG_HSE_PD_EN_POS = 6,
    V33_RG_SRAM_DS_PD_EN_MASK = (int)0x100,
    V33_RG_SRAM_DS_PD_EN_POS = 8,
    V33_RG_LSE_PD_EN_MASK = (int)0x200,
    V33_RG_LSE_PD_EN_POS = 9,
    V33_RG_HSI_PD_EN_MASK = (int)0x400,
    V33_RG_HSI_PD_EN_POS = 10,
    V33_RG_HSE_PU_EN_MASK = (int)0x800,
    V33_RG_HSE_PU_EN_POS = 11,
    V33_RG_LSE_PU_EN_MASK = (int)0x2000,
    V33_RG_LSE_PU_EN_POS = 13,
    V33_RG_SRAM1_PD_EN_MASK = (int)0x4000,
    V33_RG_SRAM1_PD_EN_POS = 14,
    V33_RG_SRAM2_PD_EN_MASK = (int)0x8000,
    V33_RG_SRAM2_PD_EN_POS = 15,
    V33_RG_SRAM3_PD_EN_MASK = (int)0x10000,
    V33_RG_SRAM3_PD_EN_POS = 16,
    V33_RG_SRAM4_PD_EN_MASK = (int)0x20000,
    V33_RG_SRAM4_PD_EN_POS = 17,
    V33_RG_SRAM_DS_PU_EN_MASK = (int)0x40000,
    V33_RG_SRAM_DS_PU_EN_POS = 18,
    V33_RG_RCO_BIAS_FC_MASK = (int)0x80000,
    V33_RG_RCO_BIAS_FC_POS = 19,
    V33_RG_HPSW_PU_LATE_MASK = (int)0x100000,
    V33_RG_HPSW_PU_LATE_POS = 20,
    V33_RG_PD_GPIO_SEL_MASK = (int)0x200000,
    V33_RG_PD_GPIO_SEL_POS = 21,
};

enum V33_RG_REG_EXTI_CTRL0_FIELD
{
    V33_RG_GPIO_INTR_MSK_MASK = (int)0xffff,
    V33_RG_GPIO_INTR_MSK_POS = 0,
};

enum V33_RG_REG_WKUP_TIM1_FIELD
{
    V33_RG_STB_BG_M1_MASK = (int)0x3fff,
    V33_RG_STB_BG_M1_POS = 0,
};

enum V33_RG_REG_EXTI_CTRL2_FIELD
{
    V33_RG_GPIO_INTR_CLR_MASK = (int)0xffffffff,
    V33_RG_GPIO_INTR_CLR_POS = 0,
};

enum V33_RG_REG_GPIO_SEL_FIELD
{
    V33_RG_GPIO_SEL00_MASK = (int)0x3,
    V33_RG_GPIO_SEL00_POS = 0,
    V33_RG_GPIO_SEL01_MASK = (int)0xc,
    V33_RG_GPIO_SEL01_POS = 2,
    V33_RG_GPIO_SEL02_MASK = (int)0x30,
    V33_RG_GPIO_SEL02_POS = 4,
    V33_RG_GPIO_SEL03_MASK = (int)0xc0,
    V33_RG_GPIO_SEL03_POS = 6,
    V33_RG_GPIO_SEL04_MASK = (int)0x300,
    V33_RG_GPIO_SEL04_POS = 8,
    V33_RG_GPIO_SEL05_MASK = (int)0xc00,
    V33_RG_GPIO_SEL05_POS = 10,
    V33_RG_GPIO_SEL06_MASK = (int)0x3000,
    V33_RG_GPIO_SEL06_POS = 12,
    V33_RG_GPIO_SEL07_MASK = (int)0xc000,
    V33_RG_GPIO_SEL07_POS = 14,
    V33_RG_GPIO_SEL08_MASK = (int)0x30000,
    V33_RG_GPIO_SEL08_POS = 16,
    V33_RG_GPIO_SEL09_MASK = (int)0xc0000,
    V33_RG_GPIO_SEL09_POS = 18,
    V33_RG_GPIO_SEL10_MASK = (int)0x300000,
    V33_RG_GPIO_SEL10_POS = 20,
    V33_RG_GPIO_SEL11_MASK = (int)0xc00000,
    V33_RG_GPIO_SEL11_POS = 22,
    V33_RG_GPIO_SEL12_MASK = (int)0x3000000,
    V33_RG_GPIO_SEL12_POS = 24,
    V33_RG_GPIO_SEL13_MASK = (int)0xc000000,
    V33_RG_GPIO_SEL13_POS = 26,
    V33_RG_GPIO_SEL14_MASK = (int)0x30000000,
    V33_RG_GPIO_SEL14_POS = 28,
    V33_RG_GPIO_SEL15_MASK = (int)0xc0000000,
    V33_RG_GPIO_SEL15_POS = 30,
};

enum V33_RG_REG_GPIO_FIR_FIELD
{
    V33_RG_GPIO_FIR_MASK = (int)0xffff,
    V33_RG_GPIO_FIR_POS = 0,
};

enum V33_RG_REG_GPIO_INTR_FIELD
{
    V33_RG_GPIO_R_INTR_MASK = (int)0xffff,
    V33_RG_GPIO_R_INTR_POS = 0,
    V33_RG_GPIO_F_INTR_MASK = (int)0xffff0000,
    V33_RG_GPIO_F_INTR_POS = 16,
};

enum V33_RG_REG_GPIO_INTR_RAW_FIELD
{
    V33_RG_GPIO_R_INTR_RAW_MASK = (int)0xffff,
    V33_RG_GPIO_R_INTR_RAW_POS = 0,
    V33_RG_GPIO_F_INTR_RAW_MASK = (int)0xffff0000,
    V33_RG_GPIO_F_INTR_RAW_POS = 16,
};

enum V33_RG_REG_RST_SRC_FIELD
{
    V33_RG_RST_SRC_MASK = (int)0x7f,
    V33_RG_RST_SRC_POS = 0,
};

enum V33_RG_REG_EXT_INTR_FIELD
{
    V33_RG_EXT_INTR_MASK = (int)0x1,
    V33_RG_EXT_INTR_POS = 0,
};

enum V33_RG_REG_COMP_STAT_FIELD
{
    V33_RG_COMP1_RINTR_MASK = 0x1,
    V33_RG_COMP1_RINTR_POS = 0,
    V33_RG_COMP1_FINTR_MASK = 0x2,
    V33_RG_COMP1_FINTR_POS = 1,
    V33_RG_COMP2_RINTR_MASK = 0x4,
    V33_RG_COMP2_RINTR_POS = 2,
    V33_RG_COMP2_FINTR_MASK = 0x8,
    V33_RG_COMP2_FINTR_POS = 3,
    V33_RG_COMP3_RINTR_MASK = 0x10,
    V33_RG_COMP3_RINTR_POS = 4,
    V33_RG_COMP3_FINTR_MASK = 0x20,
    V33_RG_COMP3_FINTR_POS = 5,
    V33_RG_COMP1_OUT_MASK = 0x100,
    V33_RG_COMP1_OUT_POS = 8,
    V33_RG_COMP2_OUT_MASK = 0x200,
    V33_RG_COMP2_OUT_POS = 9,
    V33_RG_COMP3_OUT_MASK = 0x400,
    V33_RG_COMP3_OUT_POS = 10,
};

enum V33_RG_REG_OP_CTRL_FIELD
{
    V33_RG_OP1_EN_MASK = (int)0x1,
    V33_RG_OP1_EN_POS = 0,
    V33_RG_OP2_EN_MASK = (int)0x2,
    V33_RG_OP2_EN_POS = 1,
    V33_RG_OP3_EN_MASK = (int)0x4,
    V33_RG_OP3_EN_POS = 2,
    V33_RG_OP1_CTRL_MASK = (int)0xff00,
    V33_RG_OP1_CTRL_POS = 8,
    V33_RG_OP2_CTRL_MASK = (int)0xff0000,
    V33_RG_OP2_CTRL_POS = 16,
    V33_RG_OP3_CTRL_MASK = (int)0xff000000,
    V33_RG_OP3_CTRL_POS = 24,
};

enum V33_RG_REG_COMP_CTRL_FIELD
{
    V33_RG_COMP_CTRL_EN_MASK = 0x1,
    V33_RG_COMP_CTRL_EN_POS = 0,
    V33_RG_COMP_CTRL_MODE_MASK = 0xe,
    V33_RG_COMP_CTRL_MODE_POS = 1,
    V33_RG_COMP_CTRL_HYS_MASK = 0x30,
    V33_RG_COMP_CTRL_HYS_POS = 4,
    V33_RG_COMP_CTRL_VREFCTL_MASK = 0xc0,
    V33_RG_COMP_CTRL_VREFCTL_POS = 6,
    V33_RG_COMP_CTRL_VREFSEL_MASK = 0x700,
    V33_RG_COMP_CTRL_VREFSEL_POS = 8,
    V33_RG_COMP_CTRL_IOVIPSEL_MASK = 0x1800,
    V33_RG_COMP_CTRL_IOVIPSEL_POS = 11,
    V33_RG_COMP_FLT_PRD_MASK = (int)0x30000,
    V33_RG_COMP_FLT_PRD_POS = 16,
    V33_RG_COMP_FLT_BYP_MASK = (int)0x40000,
    V33_RG_COMP_FLT_BYP_POS = 18,
    V33_RG_COMP_INTR_REN_MASK = (int)0x80000,
    V33_RG_COMP_INTR_REN_POS = 19,
    V33_RG_COMP_INTR_FEN_MASK = (int)0x100000,
    V33_RG_COMP_INTR_FEN_POS = 20,
    V33_RG_COMP_INTR_RCLR_MASK = (int)0x200000,
    V33_RG_COMP_INTR_RCLR_POS = 21,
    V33_RG_COMP_INTR_FCLR_MASK = (int)0x400000,
    V33_RG_COMP_INTR_FCLR_POS = 22,
};

#endif

