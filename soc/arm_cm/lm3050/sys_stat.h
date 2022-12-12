#ifndef SYS_STAT_H_
#define SYS_STAT_H_
#include <stdbool.h>
void uart1_status_set(bool);

void uart2_status_set(bool);

void uart3_status_set(bool);

void uart4_status_set(bool);

void uart5_status_set(bool);

void spi1_status_set(bool);

void spi2_status_set(bool);

void spi3_status_set(bool);

void i2c1_status_set(bool);

void i2c2_status_set(bool);

void i2c3_status_set(bool);

void adtimer1_status_set(bool);

void adtimer2_status_set(bool);

void bstimer1_status_set(bool);

void gptimera1_status_set(bool);

void gptimerb1_status_set(bool);

void gptimerc1_status_set(bool);

void pdm_status_set(bool);

void dma_status_set(bool);

void crypt_status_set(bool);

void adc1_status_set(bool);

void adc2_status_set(bool);

void ecc_status_set(bool);

void trng_status_set(bool);

void touchkey_status_set(bool);

void sha_status_set(bool);

void bxcan_status_set(bool);

void app_status_set(bool);

bool peri_status_busy(void);

bool dma_status_busy(void);

#endif
