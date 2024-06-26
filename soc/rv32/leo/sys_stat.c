#include <string.h>
#include "sys_stat.h"
#include "platform.h"

#define UART1_STAT_BIT 0
#define UART2_STAT_BIT 1
#define UART3_STAT_BIT 2
#define DWUART1_STAT_BIT 3
#define DWUART2_STAT_BIT 4
#define SPI1_STAT_BIT 5
#define SPI2_STAT_BIT 6
#define SPI3_STAT_BIT 7
#define I2C1_STAT_BIT 8
#define I2C2_STAT_BIT 9
#define I2C3_STAT_BIT 10
#define ADTIM1_STAT_BIT 11
#define ADTIM2_STAT_BIT 12
#define ADTIM3_STAT_BIT 30
#define ADTIM4_STAT_BIT 31
#define BSTIM1_STAT_BIT 13
#define GPTIMA1_STAT_BIT 14
#define GPTIMA2_STAT_BIT 29
#define GPTIMB1_STAT_BIT 15
#define GPTIMC1_STAT_BIT 16
#define PDM_STAT_BIT 17
#define CRYPT_STAT_BIT 18
#define ADC1_STAT_BIT 19
#define ADC2_STAT_BIT 20
#define DAC_STAT_BIT 21
#define OP_STAT_BIT 22
#define COMP_STAT_BIT 23
#define TRNG_STAT_BIT 24
#define ECC_STAT_BIT 25
#define TK_STAT_BIT 26
#define SHA_STAT_BIT 27
#define BXCAN_STAT_BIT 28
#define I2C4_STAT_BIT 29
#define I2C5_STAT_BIT 30
#define I2C6_STAT_BIT 31
#define USB_STAT_BIT 0

#define SYS_STAT_WR(reg, bit, stat)  (reg) = (((reg) & (~(1 << (bit)))) | ((stat) << (bit)))

uint32_t peri_stat;
uint32_t peri_stat1;

bool dma1_busy;
bool dma2_busy;

void uart1_status_set(bool stat)
{
    SYS_STAT_WR(peri_stat, UART1_STAT_BIT, stat);
}

void uart2_status_set(bool stat)
{
    SYS_STAT_WR(peri_stat, UART2_STAT_BIT, stat);
}

void uart3_status_set(bool stat)
{
    SYS_STAT_WR(peri_stat, UART3_STAT_BIT, stat);
}

void dwuart1_status_set(bool stat)
{
    SYS_STAT_WR(peri_stat, DWUART1_STAT_BIT, stat);
}

void dwuart2_status_set(bool stat)
{
    SYS_STAT_WR(peri_stat, DWUART2_STAT_BIT, stat);
}

void spi1_status_set(bool stat)
{
    SYS_STAT_WR(peri_stat, SPI1_STAT_BIT, stat);
}

void spi2_status_set(bool stat)
{
    SYS_STAT_WR(peri_stat, SPI2_STAT_BIT, stat);
}

void spi3_status_set(bool stat)
{
    SYS_STAT_WR(peri_stat, SPI3_STAT_BIT, stat);
}

void i2c1_status_set(bool stat)
{
    SYS_STAT_WR(peri_stat, I2C1_STAT_BIT, stat);
}

void i2c2_status_set(bool stat)
{
    SYS_STAT_WR(peri_stat, I2C2_STAT_BIT, stat);
}

void i2c3_status_set(bool stat)
{
    SYS_STAT_WR(peri_stat, I2C3_STAT_BIT, stat);
}

void i2c4_status_set(bool stat)
{
    SYS_STAT_WR(peri_stat, I2C4_STAT_BIT, stat);
}

void i2c5_status_set(bool stat)
{
    SYS_STAT_WR(peri_stat, I2C5_STAT_BIT, stat);
}

void i2c6_status_set(bool stat)
{
    SYS_STAT_WR(peri_stat, I2C6_STAT_BIT, stat);
}

void adtimer1_status_set(bool stat)
{
    SYS_STAT_WR(peri_stat, ADTIM1_STAT_BIT, stat);
}

void adtimer2_status_set(bool stat)
{
    SYS_STAT_WR(peri_stat, ADTIM2_STAT_BIT, stat);
}

void adtimer3_status_set(bool stat)
{
    SYS_STAT_WR(peri_stat, ADTIM3_STAT_BIT, stat);
}

void adtimer4_status_set(bool stat)
{
    SYS_STAT_WR(peri_stat, ADTIM4_STAT_BIT, stat);
}

void bstimer1_status_set(bool stat)
{
    SYS_STAT_WR(peri_stat, BSTIM1_STAT_BIT, stat);
}

void gptimera1_status_set(bool stat)
{
    SYS_STAT_WR(peri_stat, GPTIMA1_STAT_BIT, stat);
}

void gptimera2_status_set(bool stat)
{
    SYS_STAT_WR(peri_stat, GPTIMA2_STAT_BIT, stat);
}

void gptimerb1_status_set(bool stat)
{
    SYS_STAT_WR(peri_stat, GPTIMB1_STAT_BIT, stat);
}

void gptimerc1_status_set(bool stat)
{
    SYS_STAT_WR(peri_stat, GPTIMC1_STAT_BIT, stat);
}

void pdm_status_set(bool stat)
{
    SYS_STAT_WR(peri_stat, PDM_STAT_BIT, stat);
}

void dma1_status_set(bool stat)
{
    dma1_busy = stat;
}

void dma2_status_set(bool stat)
{
    dma2_busy = stat;
}

void crypt_status_set(bool stat)
{
    SYS_STAT_WR(peri_stat, CRYPT_STAT_BIT, stat);
}

void adc1_status_set(bool stat)
{
    SYS_STAT_WR(peri_stat, ADC1_STAT_BIT, stat);
}

void adc2_status_set(bool stat)
{
    SYS_STAT_WR(peri_stat, ADC2_STAT_BIT, stat);
}

void ecc_status_set(bool stat)
{
    SYS_STAT_WR(peri_stat, ECC_STAT_BIT, stat);
}

void touchkey_status_set(bool stat)
{
    SYS_STAT_WR(peri_stat, TK_STAT_BIT, stat);
}

void sha_status_set(bool stat)
{
    SYS_STAT_WR(peri_stat, SHA_STAT_BIT, stat);
}

void comp_status_set(bool stat)
{
    SYS_STAT_WR(peri_stat, COMP_STAT_BIT, stat);
}

void bxcan_status_set(bool stat)
{
    SYS_STAT_WR(peri_stat, BXCAN_STAT_BIT, stat);
}

void usb_status_set(bool stat)
{
    SYS_STAT_WR(peri_stat1, USB_STAT_BIT, stat);
}

bool peri_status_busy()
{
    return (peri_stat | peri_stat1) ? true : false;
}

bool dma1_status_busy()
{
    return dma1_busy;
}

bool dma2_status_busy()
{
    return dma2_busy;
}
