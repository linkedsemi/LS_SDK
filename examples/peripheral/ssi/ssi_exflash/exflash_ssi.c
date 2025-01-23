#include "exflash_ssi.h"
#include "log.h"
#include "cpu.h"
#include "platform.h"
#include "co_math.h"
#include <string.h>
#include "field_manipulate.h"
#include "ls_hal_ssi.h"
#include "by25qxx.h"

static SSI_HandleTypeDef SsiHandle;

#define FLASH_QSPI_NSS FLASH_SPI_CS // CS
// #define FLASH_QSPI_DQ0 PB08         // DI (MOSI)
// #define FLASH_QSPI_DQ1 PB09         // DO (MISO)
// #define FLASH_QSPI_DQ2 PA11         // WP
// #define FLASH_QSPI_DQ3 PA12         // HOLD
// #define FLASH_QSPI_CLK PB10         // CLK

#define FLASH_QSPI_DQ0 PA11         // DI (MOSI)
#define FLASH_QSPI_DQ1 PA12         // DO (MISO)
#define FLASH_QSPI_DQ2 PA11         // WP
#define FLASH_QSPI_DQ3 PA12         // HOLD
#define FLASH_QSPI_CLK PA09         // CLK

void exflash_ssi_init(void)
{
    pinmux_ssi_clk_init(FLASH_QSPI_CLK, Inactive_High); // The idle state of clock must correspond to the polarity
    pinmux_ssi_dq0_init(FLASH_QSPI_DQ0);
    pinmux_ssi_dq1_init(FLASH_QSPI_DQ1);
#if SSI_SPI_MODE != STD_SPI_MODE
    pinmux_ssi_dq2_init(FLASH_QSPI_DQ2);
    pinmux_ssi_dq3_init(FLASH_QSPI_DQ3);
#endif
    // pinmux_ssi_nss0_init(FLASH_QSPI_NSS);

    SsiHandle.REG = LSSSI;
    SsiHandle.Init.clk_div = 7;
    SsiHandle.Init.rxsample_dly = 0;
    SsiHandle.Init.ctrl.frame_format = Motorola_SPI;
    SsiHandle.Init.ctrl.cph = SCLK_Toggle_In_Middle;
    SsiHandle.Init.ctrl.cpol = Inactive_Low;
    SsiHandle.Init.ctrl.data_frame_size = DFS_32_8_bits;
    SsiHandle.Init.ctrl.reserved0 = 0;
    SsiHandle.Init.ctrl.reserved1 = 0;
    SsiHandle.Init.ctrl.control_frame_size = 0;
    if (HAL_SSI_Init(&SsiHandle) != HAL_OK)
    {
        /* Initialization Error */
        LOG_I("Error_Handler");
        while (1)
            ;
    }
    
    io_cfg_output(FLASH_QSPI_NSS);
    EX_FLASH_CS_HIGH();
}

void exflash_ssi_std_write_byte(uint8_t data)
{
    HAL_SSI_Transmit(&SsiHandle, &data, 1);
}

void exflash_ssi_std_write_data(uint8_t *data, uint16_t data_len)
{
    HAL_SSI_Transmit(&SsiHandle, data, data_len);
}

void exflash_ssi_quad_write_data(uint8_t *data, uint16_t data_len, uint32_t address)
{
    SSI_DualQuadConf conf;
    conf.trans_type = 0; //  00 - Instruction and Address will be sent in Standard SPI Mode.
    conf.addr_l = 0x6;   // 24 bit address Width
    conf.inst_l = 0x2;   // 8 bit  Instruction
    conf.wait_cycles = 8;

    HAL_SSI_Quad_Transmit(&SsiHandle, &conf, address, CMD_QUAD_PAGE_PROGRAM, data, data_len);
}

void exflash_ssi_std_read_data(uint8_t *data, uint16_t data_len)
{
    HAL_SSI_Receive(&SsiHandle, data, data_len);
}

void exflash_ssi_dual_read_data(uint8_t *data, uint16_t data_len, uint32_t address)
{
    SSI_DualQuadConf conf;
    conf.trans_type = 0; //  00 - Instruction and Address will be sent in Standard SPI Mode.
    conf.addr_l = 0x6;   // 24 bit address Width
    conf.inst_l = 0x2;   // 8 bit  Instruction
    conf.wait_cycles = 8;

    HAL_SSI_Dual_Receive(&SsiHandle, &conf, address, CMD_DUAL_READ_DATA, data, data_len);
}

void exflash_ssi_quad_read_data(uint8_t *data, uint16_t data_len, uint32_t address)
{
    SSI_DualQuadConf conf;
    conf.trans_type = 0; // 00 - Instruction and Address will be sent in Standard SPI Mode.
    conf.addr_l = 0x6;   // 24 bit address Width
    conf.inst_l = 0x2;   // 8 bit  Instruction
    conf.wait_cycles = 8;

    HAL_SSI_Quad_Receive(&SsiHandle, &conf, address, CMD_QUAD_READ_DATA, data, data_len);
}
