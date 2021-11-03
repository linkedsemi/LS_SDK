#ifndef LSQSPI_H_
#define LSQSPI_H_
#include <stdbool.h>
#include "reg_lsqspi_type.h"
#include "reg_base_addr.h"

#define LSQSPI ((reg_lsqspi_t *)LSQSPI_BASE_ADDR)

struct lsqspi_direct_read_config_param
{
    uint8_t opcode;
    uint8_t mode_bits;
    uint8_t dummy_bytes:2,
            quad_addr:1,
            quad_data:1,
            mode_bits_en:1;
};

struct stig_start_param
{
    uint8_t *data;
    uint32_t opcode:8,
             addr:24;
    uint8_t dummy_bytes:2,
            dummy_bytes_en:1,
            addr_en:1,
            quad_addr:1,
            mode_bits_en:1,
            opcode_en:1;
};

struct lsqspi_stig_rd_wr_param
{
    struct stig_start_param start;
    uint16_t size;
    uint8_t mode_bits;
    bool quad_data;
};

void lsqspi_init(void);

void lsqspi_direct_read_config(struct lsqspi_direct_read_config_param *param);

void lsqspi_stig_write_data(struct lsqspi_stig_rd_wr_param *param);

void lsqspi_stig_read_data(struct lsqspi_stig_rd_wr_param *param);

void lsqspi_stig_write_register(uint8_t opcode,uint8_t *data,uint8_t length);

void lsqspi_stig_send_command(uint8_t opcode);

void lsqspi_stig_read_register(uint8_t opcode,uint8_t *data,uint8_t length);

#endif

