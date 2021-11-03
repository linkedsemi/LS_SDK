#ifndef LSQSPI_MSP_H_
#define LSQSPI_MSP_H_
#include "lsqspi.h"

void lsqspi_msp_init(void);

uint8_t lsqspi_rd_cap_dly_get(void);

uint8_t lsqspi_baudrate_get(void);

uint32_t lsqspi_dly_get(void);

#endif
