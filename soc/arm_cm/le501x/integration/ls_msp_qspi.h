#ifndef LS_MSP_QSPI_H_
#define LS_MSP_QSPI_H_
#include "reg_qspi_type.h"
#include "reg_base_addr.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LSQSPI ((reg_lsqspi_t *)LSQSPI_BASE_ADDR)

void lsqspi_msp_init(void);

uint8_t lsqspi_rd_cap_dly_get(void);

uint8_t lsqspi_baudrate_get(void);

uint32_t lsqspi_dly_get(void);

#ifdef __cplusplus
}
#endif

#endif
