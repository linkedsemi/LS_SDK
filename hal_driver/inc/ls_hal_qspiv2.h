#ifndef LS_HAL_QSPIV2_H_
#define LS_HAL_QSPIV2_H_
#include "ls_msp_qspiv2.h"

enum data_dir_type
{
    WRITE_TO_FLASH = 0,
    READ_FROM_FLASH,
};

struct stg_ctrl
{
    uint32_t sw_en:1,
             reserved0:3,
             sw_cyc:6,
             reserved1:2,
             mw_en:1,
             reserved2:3,
             mw_cyc:6,
             reserved3:2,
             mw_wid:2,
             reserved4:2,
             hz_cyc:4;
};

struct stg_dat_ctrl
{
    uint32_t dat_en:1,
            reserved0:3,
            dat_bytes:12,
            dat_dir:1,
            reserved1:3,
            dat_offset:2,
            reserved2:10;
};

struct lsqspiv2_stg_cfg
{
    struct stg_ctrl ctrl;
    uint32_t ca_high;
    uint32_t ca_low;
    struct stg_dat_ctrl dat_ctrl;
    uint8_t *data;
};

void lsqspiv2_init(void);

void lsqspiv2_direct_quad_read_config(void);

void lsqspiv2_direct_dual_read_config(void);

void lsqspiv2_stg_read_write(struct lsqspiv2_stg_cfg *cfg);

void lsqspiv2_stg_send_command(uint8_t opcode);

void lsqspiv2_stg_read_register(uint8_t opcode,uint8_t *data,uint8_t length);

void lsqspiv2_stg_write_register(uint8_t opcode,uint8_t *data,uint8_t length);

#if defined(LM3050) && defined(FLASH_PROG_ALGO)
__attribute__((long_call)) void lsqspiv2_stg_read_write(struct lsqspiv2_stg_cfg *);
__attribute__((long_call)) void lsqspiv2_stg_write_register(uint8_t opcode,uint8_t *data,uint8_t length);
#endif

#endif

