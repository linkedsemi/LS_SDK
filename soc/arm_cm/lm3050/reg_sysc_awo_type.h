#ifndef REG_SYSC_AWO_TYPE_H_
#define REG_SYSC_AWO_TYPE_H_
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SYSC_AWO ((reg_sysc_awo_t *)0x4000D000)

typedef struct
{
    volatile uint32_t LOCK;
    volatile uint32_t OE_DOT;
    volatile uint32_t PUPD;
    volatile uint32_t IEN_OD;
    volatile uint32_t DS;
    volatile uint32_t AE;
    volatile uint32_t FIR;
    volatile uint32_t DIN;
}reg_lsgpio_t;

typedef struct
{
    volatile uint32_t RESERVED0[2];
    volatile uint32_t CRYPT_WORD; //0x8
    volatile uint32_t AWO_CTRL; //0xc
    volatile uint32_t RESERVED1[6];
    volatile uint32_t PD_AWO_CLKG_SRST; //0x28
    volatile uint32_t PD_AWO_CLK_CTRL; //0x2c
    volatile uint32_t RESERVED2[1];
    volatile uint32_t PD_AWO_ANA0; //0x34
    volatile uint32_t PD_AWO_ANA1; //0x38
    volatile uint32_t RESERVED3[1];
    volatile uint32_t PIN_SEL0; //0x40
    volatile uint32_t PIN_SEL1; //0x44
    volatile uint32_t PIN_SEL2; //0x48
    volatile uint32_t RESERVED4[5];
    reg_lsgpio_t IO[4];      // 0x60
    volatile uint32_t RESERVED5[1];
    volatile uint32_t DBG_ACK; //0xe4
    volatile uint32_t ANA_STAT; //0xe8
}reg_sysc_awo_t;

enum SYSC_AWO_REG_AWO_CTRL_FIELD
{
    SYSC_AWO_CRYPT_EN_MASK = (int)0x80000000,
    SYSC_AWO_CRYPT_EN_POS = 31,
};

enum SYSC_AWO_REG_PD_AWO_CLKG_SRST_FIELD
{
    SYSC_AWO_CLKG_SET_DIV_HBUS_MASK = (int)0x1,
    SYSC_AWO_CLKG_SET_DIV_HBUS_POS = 0,
    SYSC_AWO_CLKG_CLR_DIV_HBUS_MASK = (int)0x2,
    SYSC_AWO_CLKG_CLR_DIV_HBUS_POS = 1,
};

enum SYSC_AWO_REG_PD_AWO_CLK_CTRL_FIELD
{
    SYSC_AWO_CLK_DIV_PARA_HBUS_M1_MASK = (int)0xf,
    SYSC_AWO_CLK_DIV_PARA_HBUS_M1_POS = 0,
    SYSC_AWO_CLK_SEL_HBUS_MASK = (int)0xf0,
    SYSC_AWO_CLK_SEL_HBUS_POS = 4,
    SYSC_AWO_CLK_SEL_HBUS_FLT_MASK = (int)0x300,
    SYSC_AWO_CLK_SEL_HBUS_FLT_POS = 8,
    SYSC_AWO_CLK_SEL_QSPI_FLT_MASK = (int)0xc00,
    SYSC_AWO_CLK_SEL_QSPI_FLT_POS = 10,
    SYSC_AWO_HBUS_FLT_CTRL_MASK = (int)0xf000,
    SYSC_AWO_HBUS_FLT_CTRL_POS = 12,
    SYSC_AWO_QSPI_FLT_CTRL_MASK = (int)0xf0000,
    SYSC_AWO_QSPI_FLT_CTRL_POS = 16,
    SYSC_AWO_CLK_SEL_PBUS0_MASK = (int)0x300000,
    SYSC_AWO_CLK_SEL_PBUS0_POS = 20,
    SYSC_AWO_CLK_PBUS1_DIV4_MASK = (int)0x800000,
    SYSC_AWO_CLK_PBUS1_DIV4_POS = 23,
    SYSC_AWO_CLK_SEL_QSPI_MASK = (int)0x7000000,
    SYSC_AWO_CLK_SEL_QSPI_POS = 24,
    SYSC_AWO_HSE_DCT_EN_MASK = (int)0x10000000,
    SYSC_AWO_HSE_DCT_EN_POS = 28,
};

enum SYSC_AWO_REG_PD_AWO_ANA0_FIELD
{
    SYSC_AWO_AWO_DPLL_EN_MASK = (int)0x01,
    SYSC_AWO_AWO_DPLL_EN_POS = 0,
    SYSC_AWO_AWO_DPLL_SEL_REF_24M_MASK = (int)0x02,
    SYSC_AWO_AWO_DPLL_SEL_REF_24M_POS = 1,
    SYSC_AWO_AWO_DPLL_SEL_144M_MASK = (int)0x04,
    SYSC_AWO_AWO_DPLL_SEL_144M_POS = 2,
    SYSC_AWO_AWO_DPLL_EN_48M_MASK = (int)0x08,
    SYSC_AWO_AWO_DPLL_EN_48M_POS = 3,
    SYSC_AWO_AWO_DPLL_EN_128M_MASK = (int)0x10,
    SYSC_AWO_AWO_DPLL_EN_128M_POS = 4,
    SYSC_AWO_AWO_DPLL_LOCK_BYPS_MASK = (int)0x20,
    SYSC_AWO_AWO_DPLL_LOCK_BYPS_POS = 5,
    SYSC_AWO_AWO_DPLL_DPLL_TESTEN_MASK = (int)0x40,
    SYSC_AWO_AWO_DPLL_DPLL_TESTEN_POS = 6,
    SYSC_AWO_AWO_DPLL_NDIV_MASK = (int)0xF80,
    SYSC_AWO_AWO_DPLL_NDIV_POS = 7,
};

enum SYSC_AWO_REG_PD_AWO_ANA1_FIELD
{
    SYSC_AWO_AWO_CFG_HSICAL_MASK = (int)0x3ff,
    SYSC_AWO_AWO_CFG_HSICAL_POS = 0,
    SYSC_AWO_AWO_CFG_HSICAP_MASK = (int)0xc00,
    SYSC_AWO_AWO_CFG_HSICAP_POS = 10,
    SYSC_AWO_AWO_CFG_HSI_IB_ISEL_MASK = (int)0x3000,
    SYSC_AWO_AWO_CFG_HSI_IB_ISEL_POS = 12,
    SYSC_AWO_AWO_CFG_HSI_SEL_2M_MASK = (int)0x4000,
    SYSC_AWO_AWO_CFG_HSI_SEL_2M_POS = 14,
    SYSC_AWO_AWO_CFG_HSE_MASK = (int)0xfff00000,
    SYSC_AWO_AWO_CFG_HSE_POS = 20,
};

enum SYSC_AWO_REG_PIN_SEL0_FIELD
{
    SYSC_AWO_SWD_EN_MASK = (int)0x1,
    SYSC_AWO_SWD_EN_POS = 0,
    SYSC_AWO_CLK_HBUS_OUT_EN_MASK = (int)0x8,
    SYSC_AWO_CLK_HBUS_OUT_EN_POS = 3,
    SYSC_AWO_HSE_OUT_EN_MASK = (int)0x20,
    SYSC_AWO_HSE_OUT_EN_POS = 5,
    SYSC_AWO_QSPI_EN_MASK = (int)0x3f00,
    SYSC_AWO_QSPI_EN_POS = 8,
    SYSC_AWO_CLK_OUT_SEL_MASK = (int)0x30000000,
    SYSC_AWO_CLK_OUT_SEL_POS = 28,
};

enum SYSC_AWO_REG_PIN_SEL1_FIELD
{
    SYSC_AWO_FUNC_IO_EN_MASK = (int)0xffffffff,
    SYSC_AWO_FUNC_IO_EN_POS = 0,
};

enum SYSC_AWO_REG_PIN_SEL2_FIELD
{
    SYSC_AWO_FUNC_IO_EN_H_MASK = (int)0xffffffff,
    SYSC_AWO_FUNC_IO_EN_H_POS = 0,
};

enum SYSC_AWO_REG_IOA_LOCK_FIELD
{
    SYSC_AWO_GPIOA_LOCK_MASK = (int)0xffff,
    SYSC_AWO_GPIOA_LOCK_POS = 0,
};

enum SYSC_AWO_REG_IOA_OE_DOT_FIELD
{
    SYSC_AWO_GPIOA_DOT_MASK = (int)0xffff,
    SYSC_AWO_GPIOA_DOT_POS = 0,
    SYSC_AWO_GPIOA_OE_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOA_OE_POS = 16,
};

enum SYSC_AWO_REG_IOA_PD_PU_FIELD
{
    SYSC_AWO_GPIOA_PU_MASK = (int)0xffff,
    SYSC_AWO_GPIOA_PU_POS = 0,
    SYSC_AWO_GPIOA_PD_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOA_PD_POS = 16,
};

enum SYSC_AWO_REG_IOA_IEN_OD_FIELD
{
    SYSC_AWO_GPIOA_OD_MASK = (int)0xffff,
    SYSC_AWO_GPIOA_OD_POS = 0,
    SYSC_AWO_GPIOA_IE_N_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOA_IE_N_POS = 16,
};

enum SYSC_AWO_REG_IOA_DS_FIELD
{
    SYSC_AWO_GPIOA_DS2_MASK = (int)0xffff,
    SYSC_AWO_GPIOA_DS2_POS = 0,
    SYSC_AWO_GPIOA_DS1_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOA_DS1_POS = 16,
};

enum SYSC_AWO_REG_IOA_AE_FIELD
{
    SYSC_AWO_GPIOA_AE2_MASK = (int)0xffff,
    SYSC_AWO_GPIOA_AE2_POS = 0,
    SYSC_AWO_GPIOA_AE1_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOA_AE1_POS = 16,
};

enum SYSC_AWO_REG_IOA_FIR_FIELD
{
    SYSC_AWO_GPIOA_FIR_MASK = (int)0xffff,
    SYSC_AWO_GPIOA_FIR_POS = 0,
};

enum SYSC_AWO_REG_IOA_DIN_FIELD
{
    SYSC_AWO_GPIOA_DIN_MASK = (int)0xffff,
    SYSC_AWO_GPIOA_DIN_POS = 0,
};

enum SYSC_AWO_REG_IOB_LOCK_FIELD
{
    SYSC_AWO_GPIOB_LOCK_MASK = (int)0xffff,
    SYSC_AWO_GPIOB_LOCK_POS = 0,
};

enum SYSC_AWO_REG_IOB_OE_DOT_FIELD
{
    SYSC_AWO_GPIOB_DOT_MASK = (int)0xffff,
    SYSC_AWO_GPIOB_DOT_POS = 0,
    SYSC_AWO_GPIOB_OE_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOB_OE_POS = 16,
};

enum SYSC_AWO_REG_IOB_PD_PU_FIELD
{
    SYSC_AWO_GPIOB_PU_MASK = (int)0xffff,
    SYSC_AWO_GPIOB_PU_POS = 0,
    SYSC_AWO_GPIOB_PD_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOB_PD_POS = 16,
};

enum SYSC_AWO_REG_IOB_IEN_OD_FIELD
{
    SYSC_AWO_GPIOB_OD_MASK = (int)0xffff,
    SYSC_AWO_GPIOB_OD_POS = 0,
    SYSC_AWO_GPIOB_IE_N_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOB_IE_N_POS = 16,
};

enum SYSC_AWO_REG_IOB_DS_FIELD
{
    SYSC_AWO_GPIOB_DS2_MASK = (int)0xffff,
    SYSC_AWO_GPIOB_DS2_POS = 0,
    SYSC_AWO_GPIOB_DS1_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOB_DS1_POS = 16,
};

enum SYSC_AWO_REG_IOB_AE_FIELD
{
    SYSC_AWO_GPIOB_AE2_MASK = (int)0xffff,
    SYSC_AWO_GPIOB_AE2_POS = 0,
    SYSC_AWO_GPIOB_AE1_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOB_AE1_POS = 16,
};

enum SYSC_AWO_REG_IOB_FIR_FIELD
{
    SYSC_AWO_GPIOB_FIR_MASK = (int)0xffff,
    SYSC_AWO_GPIOB_FIR_POS = 0,
};

enum SYSC_AWO_REG_IOB_DIN_FIELD
{
    SYSC_AWO_GPIOB_DIN_MASK = (int)0xffff,
    SYSC_AWO_GPIOB_DIN_POS = 0,
};

enum SYSC_AWO_REG_IOC_LOCK_FIELD
{
    SYSC_AWO_GPIOC_LOCK_MASK = (int)0xffff,
    SYSC_AWO_GPIOC_LOCK_POS = 0,
};

enum SYSC_AWO_REG_IOC_OE_DOT_FIELD
{
    SYSC_AWO_GPIOC_DOT_MASK = (int)0xffff,
    SYSC_AWO_GPIOC_DOT_POS = 0,
    SYSC_AWO_GPIOC_OE_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOC_OE_POS = 16,
};

enum SYSC_AWO_REG_IOC_PD_PU_FIELD
{
    SYSC_AWO_GPIOC_PU_MASK = (int)0xffff,
    SYSC_AWO_GPIOC_PU_POS = 0,
    SYSC_AWO_GPIOC_PD_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOC_PD_POS = 16,
};

enum SYSC_AWO_REG_IOC_IEN_OD_FIELD
{
    SYSC_AWO_GPIOC_OD_MASK = (int)0xffff,
    SYSC_AWO_GPIOC_OD_POS = 0,
    SYSC_AWO_GPIOC_IE_N_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOC_IE_N_POS = 16,
};

enum SYSC_AWO_REG_IOC_DS_FIELD
{
    SYSC_AWO_GPIOC_DS2_MASK = (int)0xffff,
    SYSC_AWO_GPIOC_DS2_POS = 0,
    SYSC_AWO_GPIOC_DS1_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOC_DS1_POS = 16,
};

enum SYSC_AWO_REG_IOC_AE_FIELD
{
    SYSC_AWO_GPIOC_AE2_MASK = (int)0xffff,
    SYSC_AWO_GPIOC_AE2_POS = 0,
    SYSC_AWO_GPIOC_AE1_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOC_AE1_POS = 16,
};

enum SYSC_AWO_REG_IOC_FIR_FIELD
{
    SYSC_AWO_GPIOC_FIR_MASK = (int)0xffff,
    SYSC_AWO_GPIOC_FIR_POS = 0,
};

enum SYSC_AWO_REG_IOC_DIN_FIELD
{
    SYSC_AWO_GPIOC_DIN_MASK = (int)0xffff,
    SYSC_AWO_GPIOC_DIN_POS = 0,
};

enum SYSC_AWO_REG_IOD_LOCK_FIELD
{
    SYSC_AWO_GPIOD_LOCK_MASK = (int)0xffff,
    SYSC_AWO_GPIOD_LOCK_POS = 0,
};

enum SYSC_AWO_REG_IOD_OE_DOT_FIELD
{
    SYSC_AWO_GPIOD_DOT_MASK = (int)0xffff,
    SYSC_AWO_GPIOD_DOT_POS = 0,
    SYSC_AWO_GPIOD_OE_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOD_OE_POS = 16,
};

enum SYSC_AWO_REG_IOD_PD_PU_FIELD
{
    SYSC_AWO_GPIOD_PU_MASK = (int)0xffff,
    SYSC_AWO_GPIOD_PU_POS = 0,
    SYSC_AWO_GPIOD_PD_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOD_PD_POS = 16,
};

enum SYSC_AWO_REG_IOD_IEN_OD_FIELD
{
    SYSC_AWO_GPIOD_OD_MASK = (int)0xffff,
    SYSC_AWO_GPIOD_OD_POS = 0,
    SYSC_AWO_GPIOD_IE_N_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOD_IE_N_POS = 16,
};

enum SYSC_AWO_REG_IOD_DS_FIELD
{
    SYSC_AWO_GPIOD_DS2_MASK = (int)0xffff,
    SYSC_AWO_GPIOD_DS2_POS = 0,
    SYSC_AWO_GPIOD_DS1_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOD_DS1_POS = 16,
};

enum SYSC_AWO_REG_IOD_AE_FIELD
{
    SYSC_AWO_GPIOD_AE2_MASK = (int)0xffff,
    SYSC_AWO_GPIOD_AE2_POS = 0,
    SYSC_AWO_GPIOD_AE1_MASK = (int)0xffff0000,
    SYSC_AWO_GPIOD_AE1_POS = 16,
};

enum SYSC_AWO_REG_IOD_FIR_FIELD
{
    SYSC_AWO_GPIOD_FIR_MASK = (int)0xffff,
    SYSC_AWO_GPIOD_FIR_POS = 0,
};

enum SYSC_AWO_REG_IOD_DIN_FIELD
{
    SYSC_AWO_GPIOD_DIN_MASK = (int)0xffff,
    SYSC_AWO_GPIOD_DIN_POS = 0,
};

enum SYSC_AWO_REG_DBG_ACK_FIELD
{
    SYSC_AWO_CPU_CDBGPWRUPACK_MASK = (int)0x1,
    SYSC_AWO_CPU_CDBGPWRUPACK_POS = 0,
};

enum SYSC_AWO_REG_ANA_STAT_FIELD
{
    SYSC_AWO_DPLL_LOCK_MASK = (int)0x2,
    SYSC_AWO_DPLL_LOCK_POS = 1,
};

#ifdef __cplusplus
}
#endif

#endif

