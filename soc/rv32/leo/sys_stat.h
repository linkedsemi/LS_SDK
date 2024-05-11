#ifndef SYS_STAT_H_
#define SYS_STAT_H_
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

void uart1_status_set(bool);

void uart2_status_set(bool);

void uart3_status_set(bool);

void dwuart1_status_set(bool);

void dwuart2_status_set(bool);

void spi1_status_set(bool);

void spi2_status_set(bool);

void spi3_status_set(bool);

void i2c1_status_set(bool);

void i2c2_status_set(bool);

void i2c3_status_set(bool);

void i2c4_status_set(bool);

void i2c5_status_set(bool);

void i2c6_status_set(bool);

void adtimer1_status_set(bool);

void adtimer2_status_set(bool);

void adtimer3_status_set(bool);

void adtimer4_status_set(bool);

void bstimer1_status_set(bool);

void gptimera1_status_set(bool);

void gptimera2_status_set(bool);

void gptimerb1_status_set(bool);

void gptimerc1_status_set(bool);

void pdm_status_set(bool);

void dma1_status_set(bool);

void dma2_status_set(bool);

void crypt_status_set(bool);

void adc1_status_set(bool);

void adc2_status_set(bool);

void ecc_status_set(bool);

void trng_status_set(bool);

void comp_status_set(bool);

void touchkey_status_set(bool);

void sha_status_set(bool);

void bxcan_status_set(bool);

void app_status_set(bool);

void usb_status_set(bool);

bool peri_status_busy(void);

bool dma1_status_busy(void);

bool dma2_status_busy(void);

#ifdef __cplusplus
}
#endif

#endif
