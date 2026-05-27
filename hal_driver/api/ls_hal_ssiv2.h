#ifndef LS_HAL_SSIV2_H_
#define LS_HAL_SSIV2_H_
#include "ls_msp_ssiv2.h"
#include "HAL_def.h"
#include <stdbool.h>

#define TX_RX_FIFO_LEVEL 32

enum slave_select{
    SLAVE1 = 0x1,
    SLAVE2 = 0x2,
    SLAVE3 = 0x4
};

enum transfer_mode{
    TX_AND_RX,
    TX_ONLY,
    RX_ONLY,
    EEPROM_READ
};

enum data_frame_size{
    DFS_4_BIT = 0x3,
    DFS_8_BIT = 0x7,
    DFS_16_BIT = 0xF,
    DFS_32_BIT = 0x1F
};

enum slave_select_toggle{
    TOGGLE_DISABLE,
    TOGGLE_ENABLE
};

enum ssic_enable{
    SSIC_DISABLE,
    SSIC_ENABLE
};

enum spi_frame_format{
    STANDARD_SPI_FORMAT,
    DUAL_SPI_FORMAT,
    QUAD_SPI_FORMAT,
    OCTAL_SPI_FORMAT
};

struct SSIV2_HandleTypeDef
{
    reg_axi_ssi_t *reg;
    enum slave_select slave_select;
};

extern struct SSIV2_HandleTypeDef flash;

HAL_StatusTypeDef HAL_SSIV2_Init(reg_axi_ssi_t *reg, uint32_t div_para, uint8_t clk_edg_sel);
HAL_StatusTypeDef HAL_SSIV2_DeInit(void);
void lsssiv2_stg_read_register(reg_axi_ssi_t *reg, uint8_t slave_select, uint8_t opcode, uint8_t *data, uint32_t length);
void lsssiv2_stg_write_register(reg_axi_ssi_t *reg, uint8_t slave_select, uint32_t addr, bool is_addr, uint8_t opcode, uint8_t *data, uint16_t length);
void lsssiv2_stg_send_command(reg_axi_ssi_t *reg, uint8_t slave_select, uint8_t opcode);
void hal_flashx_fast_read_v2(reg_axi_ssi_t *reg, uint8_t slave_select, uint32_t offset, uint16_t *data, uint32_t length);
void hal_flashx_page_program_v2(reg_axi_ssi_t *reg, uint8_t slave_select, uint32_t offset, uint8_t *data, uint16_t length);
void hal_flashx_read_status_register_0_v2(reg_axi_ssi_t *reg, uint8_t slave_select, uint8_t *status_reg_0);
void hal_flashx_read_status_register_1_v2(reg_axi_ssi_t *reg, uint8_t slave_select, uint8_t *status_reg_1);
void hal_flashx_write_status_register_0_v2(reg_axi_ssi_t *reg, uint8_t slave_select, uint8_t status_0);
void hal_flashx_write_status_register_1_v2(reg_axi_ssi_t *reg, uint8_t slave_select, uint8_t status_1);
void hal_flashx_sector_erase_v2(reg_axi_ssi_t *reg, uint8_t slave_select, uint32_t offset);
void hal_flashx_block_32K_erase_v2(reg_axi_ssi_t *reg, uint8_t slave_select, uint32_t offset);
void hal_flashx_block_64K_erase_v2(reg_axi_ssi_t *reg, uint8_t slave_select, uint32_t offset);
void hal_flashx_software_reset_v2(reg_axi_ssi_t *reg, uint8_t slave_select);
void HAL_SSIV2_IRQHandler(void);

#endif
