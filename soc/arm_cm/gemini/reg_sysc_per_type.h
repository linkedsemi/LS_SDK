#ifndef REG_SYSC_PER_TYPE_H_
#define REG_SYSC_PER_TYPE_H_
#include <stdint.h>

#define SYSC_PER ((reg_sysc_per_t *)0x4008D000)

typedef struct
{
    volatile uint32_t PD_PER_CLKG0; //0x0
    volatile uint32_t PD_PER_CLKG1; //0x4
    volatile uint32_t PD_PER_CLKG2; //0x8
    volatile uint32_t PD_PER_CLKG3; //0xc
    volatile uint32_t PD_PER_SRST0; //0x10
    volatile uint32_t PD_PER_SRST1; //0x14
    volatile uint32_t PD_PER_SRST2; //0x18
    volatile uint32_t PD_PER_SRST3; //0x1c
    volatile uint32_t FUNC_SEL[15];//0x20-0x5c
    volatile uint32_t COMP_PIS; //0x60
}reg_sysc_per_t;

enum SYSC_PER_REG_PD_PER_CLKG0_FIELD
{
    SYSC_PER_CLKG_SET_BSTIM1_MASK = (int)0x1,
    SYSC_PER_CLKG_SET_BSTIM1_POS = 0,
    SYSC_PER_CLKG_CLR_BSTIM1_MASK = (int)0x2,
    SYSC_PER_CLKG_CLR_BSTIM1_POS = 1,
    SYSC_PER_CLKG_SET_GPTIMA1_MASK = (int)0x4,
    SYSC_PER_CLKG_SET_GPTIMA1_POS = 2,
    SYSC_PER_CLKG_CLR_GPTIMA1_MASK = (int)0x8,
    SYSC_PER_CLKG_CLR_GPTIMA1_POS = 3,
    SYSC_PER_CLKG_SET_GPTIMB1_MASK = (int)0x10,
    SYSC_PER_CLKG_SET_GPTIMB1_POS = 4,
    SYSC_PER_CLKG_CLR_GPTIMB1_MASK = (int)0x20,
    SYSC_PER_CLKG_CLR_GPTIMB1_POS = 5,
    SYSC_PER_CLKG_SET_GPTIMC1_MASK = (int)0x40,
    SYSC_PER_CLKG_SET_GPTIMC1_POS = 6,
    SYSC_PER_CLKG_CLR_GPTIMC1_MASK = (int)0x80,
    SYSC_PER_CLKG_CLR_GPTIMC1_POS = 7,
    SYSC_PER_CLKG_SET_ADTIM1_MASK = (int)0x100,
    SYSC_PER_CLKG_SET_ADTIM1_POS = 8,
    SYSC_PER_CLKG_CLR_ADTIM1_MASK = (int)0x200,
    SYSC_PER_CLKG_CLR_ADTIM1_POS = 9,
    SYSC_PER_CLKG_SET_ADTIM2_MASK = (int)0x400,
    SYSC_PER_CLKG_SET_ADTIM2_POS = 10,
    SYSC_PER_CLKG_CLR_ADTIM2_MASK = (int)0x800,
    SYSC_PER_CLKG_CLR_ADTIM2_POS = 11,
    SYSC_PER_CLKG_SET_I2C1_MASK = (int)0x1000000,
    SYSC_PER_CLKG_SET_I2C1_POS = 24,
    SYSC_PER_CLKG_CLR_I2C1_MASK = (int)0x2000000,
    SYSC_PER_CLKG_CLR_I2C1_POS = 25,
    SYSC_PER_CLKG_SET_I2C2_MASK = (int)0x4000000,
    SYSC_PER_CLKG_SET_I2C2_POS = 26,
    SYSC_PER_CLKG_CLR_I2C2_MASK = (int)0x8000000,
    SYSC_PER_CLKG_CLR_I2C2_POS = 27,
    SYSC_PER_CLKG_SET_I2C3_MASK = (int)0x10000000,
    SYSC_PER_CLKG_SET_I2C3_POS = 28,
    SYSC_PER_CLKG_CLR_I2C3_MASK = (int)0x20000000,
    SYSC_PER_CLKG_CLR_I2C3_POS = 29,
};

enum SYSC_PER_REG_PD_PER_CLKG1_FIELD
{
    SYSC_PER_CLKG_SET_UART1_MASK = (int)0x100,
    SYSC_PER_CLKG_SET_UART1_POS = 8,
    SYSC_PER_CLKG_CLR_UART1_MASK = (int)0x200,
    SYSC_PER_CLKG_CLR_UART1_POS = 9,
    SYSC_PER_CLKG_SET_UART2_MASK = (int)0x400,
    SYSC_PER_CLKG_SET_UART2_POS = 10,
    SYSC_PER_CLKG_CLR_UART2_MASK = (int)0x800,
    SYSC_PER_CLKG_CLR_UART2_POS = 11,
    SYSC_PER_CLKG_SET_UART3_MASK = (int)0x1000,
    SYSC_PER_CLKG_SET_UART3_POS = 12,
    SYSC_PER_CLKG_CLR_UART3_MASK = (int)0x2000,
    SYSC_PER_CLKG_CLR_UART3_POS = 13,
    SYSC_PER_CLKG_SET_UART4_MASK = (int)0x4000,
    SYSC_PER_CLKG_SET_UART4_POS = 14,
    SYSC_PER_CLKG_CLR_UART4_MASK = (int)0x8000,
    SYSC_PER_CLKG_CLR_UART4_POS = 15,
    SYSC_PER_CLKG_SET_UART5_MASK = (int)0x10000,
    SYSC_PER_CLKG_SET_UART5_POS = 16,
    SYSC_PER_CLKG_CLR_UART5_MASK = (int)0x20000,
    SYSC_PER_CLKG_CLR_UART5_POS = 17,
    SYSC_PER_CLKG_SET_SPI1_MASK = (int)0x1000000,
    SYSC_PER_CLKG_SET_SPI1_POS = 24,
    SYSC_PER_CLKG_CLR_SPI1_MASK = (int)0x2000000,
    SYSC_PER_CLKG_CLR_SPI1_POS = 25,
    SYSC_PER_CLKG_SET_SPI2_MASK = (int)0x4000000,
    SYSC_PER_CLKG_SET_SPI2_POS = 26,
    SYSC_PER_CLKG_CLR_SPI2_MASK = (int)0x8000000,
    SYSC_PER_CLKG_CLR_SPI2_POS = 27,
    SYSC_PER_CLKG_SET_SPI3_MASK = (int)0x10000000,
    SYSC_PER_CLKG_SET_SPI3_POS = 28,
    SYSC_PER_CLKG_CLR_SPI3_MASK = (int)0x20000000,
    SYSC_PER_CLKG_CLR_SPI3_POS = 29,
};

enum SYSC_PER_REG_PD_PER_CLKG2_FIELD
{
    SYSC_PER_CLKG_SET_ADC1_MASK = (int)0x100,
    SYSC_PER_CLKG_SET_ADC1_POS = 8,
    SYSC_PER_CLKG_CLR_ADC1_MASK = (int)0x200,
    SYSC_PER_CLKG_CLR_ADC1_POS = 9,
    SYSC_PER_CLKG_SET_ADC2_MASK = (int)0x400,
    SYSC_PER_CLKG_SET_ADC2_POS = 10,
    SYSC_PER_CLKG_CLR_ADC2_MASK = (int)0x800,
    SYSC_PER_CLKG_CLR_ADC2_POS = 11,
    SYSC_PER_CLKG_SET_PDM_MASK = (int)0x10000,
    SYSC_PER_CLKG_SET_PDM_POS = 16,
    SYSC_PER_CLKG_CLR_PDM_MASK = (int)0x20000,
    SYSC_PER_CLKG_CLR_PDM_POS = 17,
    SYSC_PER_CLKG_SET_EXTI_MASK = (int)0x1000000,
    SYSC_PER_CLKG_SET_EXTI_POS = 24,
    SYSC_PER_CLKG_CLR_EXTI_MASK = (int)0x2000000,
    SYSC_PER_CLKG_CLR_EXTI_POS = 25,
};

enum SYSC_PER_REG_PD_PER_CLKG3_FIELD
{
    SYSC_PER_CLKG_SET_WWDT_MASK = (int)0x1,
    SYSC_PER_CLKG_SET_WWDT_POS = 0,
    SYSC_PER_CLKG_CLR_WWDT_MASK = (int)0x2,
    SYSC_PER_CLKG_CLR_WWDT_POS = 1,
    SYSC_PER_CLKG_SET_PIS_MASK = (int)0x4,
    SYSC_PER_CLKG_SET_PIS_POS = 2,
    SYSC_PER_CLKG_CLR_PIS_MASK = (int)0x8,
    SYSC_PER_CLKG_CLR_PIS_POS = 3,
    SYSC_PER_CLKG_SET_TK_MASK = (int)0x10,
    SYSC_PER_CLKG_SET_TK_POS = 4,
    SYSC_PER_CLKG_CLR_TK_MASK = (int)0x20,
    SYSC_PER_CLKG_CLR_TK_POS = 5,
    SYSC_PER_CLKG_SET_TRNG_MASK = (int)0x40,
    SYSC_PER_CLKG_SET_TRNG_POS = 6,
    SYSC_PER_CLKG_CLR_TRNG_MASK = (int)0x80,
    SYSC_PER_CLKG_CLR_TRNG_POS = 7,
    SYSC_PER_CLKG_SET_DAC12_MASK = (int)0x100,
    SYSC_PER_CLKG_SET_DAC12_POS = 8,
    SYSC_PER_CLKG_CLR_DAC12_MASK = (int)0x200,
    SYSC_PER_CLKG_CLR_DAC12_POS = 9,
};

enum SYSC_PER_REG_PD_PER_SRST0_FIELD
{
    SYSC_PER_SRST_SET_BSTIM1_N_MASK = (int)0x1,
    SYSC_PER_SRST_SET_BSTIM1_N_POS = 0,
    SYSC_PER_SRST_CLR_BSTIM1_N_MASK = (int)0x2,
    SYSC_PER_SRST_CLR_BSTIM1_N_POS = 1,
    SYSC_PER_SRST_SET_GPTIMA1_N_MASK = (int)0x4,
    SYSC_PER_SRST_SET_GPTIMA1_N_POS = 2,
    SYSC_PER_SRST_CLR_GPTIMA1_N_MASK = (int)0x8,
    SYSC_PER_SRST_CLR_GPTIMA1_N_POS = 3,
    SYSC_PER_SRST_SET_GPTIMB1_N_MASK = (int)0x10,
    SYSC_PER_SRST_SET_GPTIMB1_N_POS = 4,
    SYSC_PER_SRST_CLR_GPTIMB1_N_MASK = (int)0x20,
    SYSC_PER_SRST_CLR_GPTIMB1_N_POS = 5,
    SYSC_PER_SRST_SET_GPTIMC1_N_MASK = (int)0x40,
    SYSC_PER_SRST_SET_GPTIMC1_N_POS = 6,
    SYSC_PER_SRST_CLR_GPTIMC1_N_MASK = (int)0x80,
    SYSC_PER_SRST_CLR_GPTIMC1_N_POS = 7,
    SYSC_PER_SRST_SET_ADTIM1_N_MASK = (int)0x100,
    SYSC_PER_SRST_SET_ADTIM1_N_POS = 8,
    SYSC_PER_SRST_CLR_ADTIM1_N_MASK = (int)0x200,
    SYSC_PER_SRST_CLR_ADTIM1_N_POS = 9,
    SYSC_PER_SRST_SET_ADTIM2_N_MASK = (int)0x400,
    SYSC_PER_SRST_SET_ADTIM2_N_POS = 10,
    SYSC_PER_SRST_CLR_ADTIM2_N_MASK = (int)0x800,
    SYSC_PER_SRST_CLR_ADTIM2_N_POS = 11,
    SYSC_PER_SRST_SET_I2C1_N_MASK = (int)0x1000000,
    SYSC_PER_SRST_SET_I2C1_N_POS = 24,
    SYSC_PER_SRST_CLR_I2C1_N_MASK = (int)0x2000000,
    SYSC_PER_SRST_CLR_I2C1_N_POS = 25,
    SYSC_PER_SRST_SET_I2C2_N_MASK = (int)0x4000000,
    SYSC_PER_SRST_SET_I2C2_N_POS = 26,
    SYSC_PER_SRST_CLR_I2C2_N_MASK = (int)0x8000000,
    SYSC_PER_SRST_CLR_I2C2_N_POS = 27,
    SYSC_PER_SRST_SET_I2C3_N_MASK = (int)0x10000000,
    SYSC_PER_SRST_SET_I2C3_N_POS = 28,
    SYSC_PER_SRST_CLR_I2C3_N_MASK = (int)0x20000000,
    SYSC_PER_SRST_CLR_I2C3_N_POS = 29,
};

enum SYSC_PER_REG_PD_PER_SRST1_FIELD
{
    SYSC_PER_SRST_SET_UART1_N_MASK = (int)0x100,
    SYSC_PER_SRST_SET_UART1_N_POS = 8,
    SYSC_PER_SRST_CLR_UART1_N_MASK = (int)0x200,
    SYSC_PER_SRST_CLR_UART1_N_POS = 9,
    SYSC_PER_SRST_SET_UART2_N_MASK = (int)0x400,
    SYSC_PER_SRST_SET_UART2_N_POS = 10,
    SYSC_PER_SRST_CLR_UART2_N_MASK = (int)0x800,
    SYSC_PER_SRST_CLR_UART2_N_POS = 11,
    SYSC_PER_SRST_SET_UART3_N_MASK = (int)0x1000,
    SYSC_PER_SRST_SET_UART3_N_POS = 12,
    SYSC_PER_SRST_CLR_UART3_N_MASK = (int)0x2000,
    SYSC_PER_SRST_CLR_UART3_N_POS = 13,
    SYSC_PER_SRST_SET_UART4_N_MASK = (int)0x4000,
    SYSC_PER_SRST_SET_UART4_N_POS = 14,
    SYSC_PER_SRST_CLR_UART4_N_MASK = (int)0x8000,
    SYSC_PER_SRST_CLR_UART4_N_POS = 15,
    SYSC_PER_SRST_SET_UART5_N_MASK = (int)0x10000,
    SYSC_PER_SRST_SET_UART5_N_POS = 16,
    SYSC_PER_SRST_CLR_UART5_N_MASK = (int)0x20000,
    SYSC_PER_SRST_CLR_UART5_N_POS = 17,
    SYSC_PER_SRST_SET_SPI1_N_MASK = (int)0x1000000,
    SYSC_PER_SRST_SET_SPI1_N_POS = 24,
    SYSC_PER_SRST_CLR_SPI1_N_MASK = (int)0x2000000,
    SYSC_PER_SRST_CLR_SPI1_N_POS = 25,
    SYSC_PER_SRST_SET_SPI2_N_MASK = (int)0x4000000,
    SYSC_PER_SRST_SET_SPI2_N_POS = 26,
    SYSC_PER_SRST_CLR_SPI2_N_MASK = (int)0x8000000,
    SYSC_PER_SRST_CLR_SPI2_N_POS = 27,
    SYSC_PER_SRST_SET_SPI3_N_MASK = (int)0x10000000,
    SYSC_PER_SRST_SET_SPI3_N_POS = 28,
    SYSC_PER_SRST_CLR_SPI3_N_MASK = (int)0x20000000,
    SYSC_PER_SRST_CLR_SPI3_N_POS = 29,
};

enum SYSC_PER_REG_PD_PER_SRST2_FIELD
{
    SYSC_PER_SRST_SET_ADC_N_MASK = (int)0x100,
    SYSC_PER_SRST_SET_ADC_N_POS = 8,
    SYSC_PER_SRST_CLR_ADC_N_MASK = (int)0x200,
    SYSC_PER_SRST_CLR_ADC_N_POS = 9,
    SYSC_PER_SRST_SET_PDM_N_MASK = (int)0x10000,
    SYSC_PER_SRST_SET_PDM_N_POS = 16,
    SYSC_PER_SRST_CLR_PDM_N_MASK = (int)0x20000,
    SYSC_PER_SRST_CLR_PDM_N_POS = 17,
    SYSC_PER_SRST_SET_EXTI_N_MASK = (int)0x1000000,
    SYSC_PER_SRST_SET_EXTI_N_POS = 24,
    SYSC_PER_SRST_CLR_EXTI_N_MASK = (int)0x2000000,
    SYSC_PER_SRST_CLR_EXTI_N_POS = 25,
};

enum SYSC_PER_REG_PD_PER_SRST3_FIELD
{
    SYSC_PER_SRST_SET_WWDT_N_MASK = (int)0x1,
    SYSC_PER_SRST_SET_WWDT_N_POS = 0,
    SYSC_PER_SRST_CLR_WWDT_N_MASK = (int)0x2,
    SYSC_PER_SRST_CLR_WWDT_N_POS = 1,
    SYSC_PER_SRST_SET_PIS_N_MASK = (int)0x4,
    SYSC_PER_SRST_SET_PIS_N_POS = 2,
    SYSC_PER_SRST_CLR_PIS_N_MASK = (int)0x8,
    SYSC_PER_SRST_CLR_PIS_N_POS = 3,
    SYSC_PER_SRST_SET_TK_N_MASK = (int)0x10,
    SYSC_PER_SRST_SET_TK_N_POS = 4,
    SYSC_PER_SRST_CLR_TK_N_MASK = (int)0x20,
    SYSC_PER_SRST_CLR_TK_N_POS = 5,
    SYSC_PER_SRST_SET_TRNG_N_MASK = (int)0x40,
    SYSC_PER_SRST_SET_TRNG_N_POS = 6,
    SYSC_PER_SRST_CLR_TRNG_N_MASK = (int)0x80,
    SYSC_PER_SRST_CLR_TRNG_N_POS = 7,
    SYSC_PER_SRST_SET_DAC12_N_MASK = (int)0x100,
    SYSC_PER_SRST_SET_DAC12_N_POS = 8,
    SYSC_PER_SRST_CLR_DAC12_N_MASK = (int)0x200,
    SYSC_PER_SRST_CLR_DAC12_N_POS = 9,
};

enum SYSC_PER_REG_FUNC_SEL0_FIELD
{
    SYSC_PER_FUNC_IO00_SEL_MASK = (int)0x7f,
    SYSC_PER_FUNC_IO00_SEL_POS = 0,
    SYSC_PER_FUNC_IO01_SEL_MASK = (int)0x7f00,
    SYSC_PER_FUNC_IO01_SEL_POS = 8,
    SYSC_PER_FUNC_IO02_SEL_MASK = (int)0x7f0000,
    SYSC_PER_FUNC_IO02_SEL_POS = 16,
    SYSC_PER_FUNC_IO03_SEL_MASK = (int)0x7f000000,
    SYSC_PER_FUNC_IO03_SEL_POS = 24,
};

enum SYSC_PER_REG_FUNC_SEL1_FIELD
{
    SYSC_PER_FUNC_IO04_SEL_MASK = (int)0x7f,
    SYSC_PER_FUNC_IO04_SEL_POS = 0,
    SYSC_PER_FUNC_IO05_SEL_MASK = (int)0x7f00,
    SYSC_PER_FUNC_IO05_SEL_POS = 8,
    SYSC_PER_FUNC_IO06_SEL_MASK = (int)0x7f0000,
    SYSC_PER_FUNC_IO06_SEL_POS = 16,
    SYSC_PER_FUNC_IO07_SEL_MASK = (int)0x7f000000,
    SYSC_PER_FUNC_IO07_SEL_POS = 24,
};

enum SYSC_PER_REG_FUNC_SEL2_FIELD
{
    SYSC_PER_FUNC_IO08_SEL_MASK = (int)0x7f,
    SYSC_PER_FUNC_IO08_SEL_POS = 0,
    SYSC_PER_FUNC_IO09_SEL_MASK = (int)0x7f00,
    SYSC_PER_FUNC_IO09_SEL_POS = 8,
    SYSC_PER_FUNC_IO10_SEL_MASK = (int)0x7f0000,
    SYSC_PER_FUNC_IO10_SEL_POS = 16,
    SYSC_PER_FUNC_IO11_SEL_MASK = (int)0x7f000000,
    SYSC_PER_FUNC_IO11_SEL_POS = 24,
};

enum SYSC_PER_REG_FUNC_SEL3_FIELD
{
    SYSC_PER_FUNC_IO12_SEL_MASK = (int)0x7f,
    SYSC_PER_FUNC_IO12_SEL_POS = 0,
    SYSC_PER_FUNC_IO13_SEL_MASK = (int)0x7f00,
    SYSC_PER_FUNC_IO13_SEL_POS = 8,
    SYSC_PER_FUNC_IO14_SEL_MASK = (int)0x7f0000,
    SYSC_PER_FUNC_IO14_SEL_POS = 16,
    SYSC_PER_FUNC_IO15_SEL_MASK = (int)0x7f000000,
    SYSC_PER_FUNC_IO15_SEL_POS = 24,
};

enum SYSC_PER_REG_FUNC_SEL4_FIELD
{
    SYSC_PER_FUNC_IO16_SEL_MASK = (int)0x7f,
    SYSC_PER_FUNC_IO16_SEL_POS = 0,
    SYSC_PER_FUNC_IO17_SEL_MASK = (int)0x7f00,
    SYSC_PER_FUNC_IO17_SEL_POS = 8,
    SYSC_PER_FUNC_IO18_SEL_MASK = (int)0x7f0000,
    SYSC_PER_FUNC_IO18_SEL_POS = 16,
    SYSC_PER_FUNC_IO19_SEL_MASK = (int)0x7f000000,
    SYSC_PER_FUNC_IO19_SEL_POS = 24,
};

enum SYSC_PER_REG_FUNC_SEL5_FIELD
{
    SYSC_PER_FUNC_IO20_SEL_MASK = (int)0x7f,
    SYSC_PER_FUNC_IO20_SEL_POS = 0,
    SYSC_PER_FUNC_IO21_SEL_MASK = (int)0x7f00,
    SYSC_PER_FUNC_IO21_SEL_POS = 8,
    SYSC_PER_FUNC_IO22_SEL_MASK = (int)0x7f0000,
    SYSC_PER_FUNC_IO22_SEL_POS = 16,
    SYSC_PER_FUNC_IO23_SEL_MASK = (int)0x7f000000,
    SYSC_PER_FUNC_IO23_SEL_POS = 24,
};

enum SYSC_PER_REG_FUNC_SEL6_FIELD
{
    SYSC_PER_FUNC_IO24_SEL_MASK = (int)0x7f,
    SYSC_PER_FUNC_IO24_SEL_POS = 0,
    SYSC_PER_FUNC_IO25_SEL_MASK = (int)0x7f00,
    SYSC_PER_FUNC_IO25_SEL_POS = 8,
    SYSC_PER_FUNC_IO26_SEL_MASK = (int)0x7f0000,
    SYSC_PER_FUNC_IO26_SEL_POS = 16,
    SYSC_PER_FUNC_IO27_SEL_MASK = (int)0x7f000000,
    SYSC_PER_FUNC_IO27_SEL_POS = 24,
};

enum SYSC_PER_REG_FUNC_SEL7_FIELD
{
    SYSC_PER_FUNC_IO28_SEL_MASK = (int)0x7f,
    SYSC_PER_FUNC_IO28_SEL_POS = 0,
    SYSC_PER_FUNC_IO29_SEL_MASK = (int)0x7f00,
    SYSC_PER_FUNC_IO29_SEL_POS = 8,
    SYSC_PER_FUNC_IO30_SEL_MASK = (int)0x7f0000,
    SYSC_PER_FUNC_IO30_SEL_POS = 16,
    SYSC_PER_FUNC_IO31_SEL_MASK = (int)0x7f000000,
    SYSC_PER_FUNC_IO31_SEL_POS = 24,
};

enum SYSC_PER_REG_FUNC_SEL8_FIELD
{
    SYSC_PER_FUNC_IO32_SEL_MASK = (int)0x7f,
    SYSC_PER_FUNC_IO32_SEL_POS = 0,
    SYSC_PER_FUNC_IO33_SEL_MASK = (int)0x7f00,
    SYSC_PER_FUNC_IO33_SEL_POS = 8,
    SYSC_PER_FUNC_IO34_SEL_MASK = (int)0x7f0000,
    SYSC_PER_FUNC_IO34_SEL_POS = 16,
    SYSC_PER_FUNC_IO35_SEL_MASK = (int)0x7f000000,
    SYSC_PER_FUNC_IO35_SEL_POS = 24,
};

enum SYSC_PER_REG_FUNC_SEL9_FIELD
{
    SYSC_PER_FUNC_IO36_SEL_MASK = (int)0x7f,
    SYSC_PER_FUNC_IO36_SEL_POS = 0,
    SYSC_PER_FUNC_IO37_SEL_MASK = (int)0x7f00,
    SYSC_PER_FUNC_IO37_SEL_POS = 8,
    SYSC_PER_FUNC_IO38_SEL_MASK = (int)0x7f0000,
    SYSC_PER_FUNC_IO38_SEL_POS = 16,
    SYSC_PER_FUNC_IO39_SEL_MASK = (int)0x7f000000,
    SYSC_PER_FUNC_IO39_SEL_POS = 24,
};

enum SYSC_PER_REG_FUNC_SEL10_FIELD
{
    SYSC_PER_FUNC_IO40_SEL_MASK = (int)0x7f,
    SYSC_PER_FUNC_IO40_SEL_POS = 0,
    SYSC_PER_FUNC_IO41_SEL_MASK = (int)0x7f00,
    SYSC_PER_FUNC_IO41_SEL_POS = 8,
    SYSC_PER_FUNC_IO42_SEL_MASK = (int)0x7f0000,
    SYSC_PER_FUNC_IO42_SEL_POS = 16,
    SYSC_PER_FUNC_IO43_SEL_MASK = (int)0x7f000000,
    SYSC_PER_FUNC_IO43_SEL_POS = 24,
};

enum SYSC_PER_REG_FUNC_SEL11_FIELD
{
    SYSC_PER_FUNC_IO44_SEL_MASK = (int)0x7f,
    SYSC_PER_FUNC_IO44_SEL_POS = 0,
    SYSC_PER_FUNC_IO45_SEL_MASK = (int)0x7f00,
    SYSC_PER_FUNC_IO45_SEL_POS = 8,
    SYSC_PER_FUNC_IO46_SEL_MASK = (int)0x7f0000,
    SYSC_PER_FUNC_IO46_SEL_POS = 16,
    SYSC_PER_FUNC_IO47_SEL_MASK = (int)0x7f000000,
    SYSC_PER_FUNC_IO47_SEL_POS = 24,
};

enum SYSC_PER_REG_FUNC_SEL12_FIELD
{
    SYSC_PER_FUNC_IO48_SEL_MASK = (int)0x7f,
    SYSC_PER_FUNC_IO48_SEL_POS = 0,
    SYSC_PER_FUNC_IO49_SEL_MASK = (int)0x7f00,
    SYSC_PER_FUNC_IO49_SEL_POS = 8,
    SYSC_PER_FUNC_IO50_SEL_MASK = (int)0x7f0000,
    SYSC_PER_FUNC_IO50_SEL_POS = 16,
    SYSC_PER_FUNC_IO51_SEL_MASK = (int)0x7f000000,
    SYSC_PER_FUNC_IO51_SEL_POS = 24,
};

enum SYSC_PER_REG_FUNC_SEL13_FIELD
{
    SYSC_PER_FUNC_IO52_SEL_MASK = (int)0x7f,
    SYSC_PER_FUNC_IO52_SEL_POS = 0,
    SYSC_PER_FUNC_IO53_SEL_MASK = (int)0x7f00,
    SYSC_PER_FUNC_IO53_SEL_POS = 8,
    SYSC_PER_FUNC_IO54_SEL_MASK = (int)0x7f0000,
    SYSC_PER_FUNC_IO54_SEL_POS = 16,
    SYSC_PER_FUNC_IO55_SEL_MASK = (int)0x7f000000,
    SYSC_PER_FUNC_IO55_SEL_POS = 24,
};

enum SYSC_PER_REG_FUNC_SEL14_FIELD
{
    SYSC_PER_FUNC_IO56_SEL_MASK = (int)0x7f,
    SYSC_PER_FUNC_IO56_SEL_POS = 0,
    SYSC_PER_FUNC_IO57_SEL_MASK = (int)0x7f00,
    SYSC_PER_FUNC_IO57_SEL_POS = 8,
    SYSC_PER_FUNC_IO58_SEL_MASK = (int)0x7f0000,
    SYSC_PER_FUNC_IO58_SEL_POS = 16,
    SYSC_PER_FUNC_IO59_SEL_MASK = (int)0x7f000000,
    SYSC_PER_FUNC_IO59_SEL_POS = 24,
};

enum SYSC_PER_REG_FUNC_SEL15_FIELD
{
    SYSC_PER_FUNC_IO60_SEL_MASK = (int)0x7f,
    SYSC_PER_FUNC_IO60_SEL_POS = 0,
    SYSC_PER_FUNC_IO61_SEL_MASK = (int)0x7f00,
    SYSC_PER_FUNC_IO61_SEL_POS = 8,
    SYSC_PER_FUNC_IO62_SEL_MASK = (int)0x7f0000,
    SYSC_PER_FUNC_IO62_SEL_POS = 16,
    SYSC_PER_FUNC_IO63_SEL_MASK = (int)0x7f000000,
    SYSC_PER_FUNC_IO63_SEL_POS = 24,
};

enum SYSC_PER_REG_COMP_PIS_FIELD
{
    SYSC_PER_COMP_SEL_MASK = (int)0x7,
    SYSC_PER_COMP_SEL_POS = 0,
};

#endif

