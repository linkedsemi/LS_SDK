#include <string.h>
#include "sys_stat.h"

struct peri_stat_env
{
    bool uart1;
    bool uart2;
    bool uart3;
    bool uart4;
    bool uart5;
    bool spi1;
    bool spi2;
    bool spi3;
    bool i2c1;
    bool i2c2;
    bool i2c3;
    bool adtimer1;
    bool adtimer2;
    bool bstimer1;
    bool gptimera1;
    bool gptimerb1;
    bool gptimerc1;
    bool pdm;
    bool crypt;
    bool adc1;
    bool adc2;
    bool trng;
    bool ecc;
    bool touchkey;
    bool sha;
    bool dac;
}peri_stat;

bool dma_busy;

void uart1_status_set(bool stat)
{
    peri_stat.uart1 = stat;
}

void uart2_status_set(bool stat)
{
    peri_stat.uart2 = stat;
}

void uart3_status_set(bool stat)
{
    peri_stat.uart3 = stat;
}

void uart4_status_set(bool stat)
{
    peri_stat.uart4 = stat;
}

void uart5_status_set(bool stat)
{
    peri_stat.uart5 = stat;
}

void spi1_status_set(bool stat)
{
    peri_stat.spi1 = stat;
}

void spi2_status_set(bool stat)
{
    peri_stat.spi2 = stat;
}

void spi3_status_set(bool stat)
{
    peri_stat.spi3 = stat;
}

void i2c1_status_set(bool stat)
{
    peri_stat.i2c1 = stat;
}

void i2c2_status_set(bool stat)
{
    peri_stat.i2c2 = stat;
}

void i2c3_status_set(bool stat)
{
    peri_stat.i2c3 = stat;
}

void adtimer1_status_set(bool stat)
{
    peri_stat.adtimer1 = stat;
}

void adtimer2_status_set(bool stat)
{
    peri_stat.adtimer2 = stat;
}

void bstimer1_status_set(bool stat)
{
    peri_stat.bstimer1 = stat;
}

void gptimera1_status_set(bool stat)
{
    peri_stat.gptimera1 = stat;
}

void gptimerb1_status_set(bool stat)
{
    peri_stat.gptimerb1 = stat;
}

void gptimerc1_status_set(bool stat)
{
    peri_stat.gptimerc1 = stat;
}

void pdm_status_set(bool stat)
{
    peri_stat.pdm = stat;
}

void dma_status_set(bool stat)
{
    dma_busy = stat;
}

void crypt_status_set(bool stat)
{
    peri_stat.crypt = stat;
}

void adc1_status_set(bool stat)
{
    peri_stat.adc1 = stat;
}

void adc2_status_set(bool stat)
{
    peri_stat.adc2 = stat;
}

void ecc_status_set(bool stat)
{
    peri_stat.ecc = stat;
}

void trng_status_set(bool stat)
{
    peri_stat.trng = stat;
}

void touchkey_status_set(bool stat)
{
    peri_stat.touchkey = stat;
}

void sha_status_set(bool stat)
{
    peri_stat.sha = stat;
}

bool peri_status_busy()
{
    const struct peri_stat_env idle_stat = {0};
    if(memcmp(&peri_stat,&idle_stat,sizeof(struct peri_stat_env))==0)
    {
        return false;
    }else
    {
        return true;
    }
}

bool dma_status_busy()
{
    return dma_busy;
}
