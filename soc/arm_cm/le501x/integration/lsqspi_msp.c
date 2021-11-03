#include "lsqspi_msp.h"
#include "reg_rcc.h"
#include "field_manipulate.h"
#include "compile_flag.h"

XIP_BANNED void lsqspi_msp_init()
{
    REG_FIELD_WR(RCC->APB2RST, RCC_QSPI, 1);
    REG_FIELD_WR(RCC->APB2RST, RCC_QSPI, 0);
    REG_FIELD_WR(RCC->APB2EN, RCC_QSPI, 1);
}

XIP_BANNED uint8_t lsqspi_rd_cap_dly_get()
{
    return 2;
}

XIP_BANNED uint8_t lsqspi_baudrate_get()
{
    return 0;
}

XIP_BANNED uint32_t lsqspi_dly_get()
{
    return FIELD_BUILD(LSQSPI_DLY_NSS,4) | FIELD_BUILD(LSQSPI_DLY_AFTER,2) | FIELD_BUILD(LSQSPI_DLY_INIT, 2);
}
