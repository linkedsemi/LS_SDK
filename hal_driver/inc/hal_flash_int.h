#ifndef HAL_FLASH_INT_H_
#define HAL_FLASH_INT_H_
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "sdk_config.h"
#include "ls_hal_flash.h"
#include "cpu.h"
#include "compile_flag.h"
#include "ls_dbg.h"
#include "platform.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(FLASH_PROG_ALGO) && __arm__
#define HAL_FLASH_C_MERGED
#endif

#define WRITE_STATUS_REGISTER_OPCODE 0x01
#define WRTIE_STATUS_REGISTER_0_OPCODE 0x01
#define WRITE_STATUS_REGISTER_1_OPCODE 0x31
#define READ_STATUS_REGISTER_0_OPCODE 0x05
#define READ_STATUS_REGISTER_1_OPCODE 0x35
#define WRITE_ENABLE_OPCODE 0x06
#define PAGE_ERASE_OPCODE 0x81
#define SECTOR_ERASE_OPCODE 0x20
#define CHIP_ERASE_OPCODE 0x60
#define BLOCK_32K_ERASE_OPCODE 0x52
#define BLOCK_64K_ERASE_OPCODE 0xd8
#define PAGE_PROGRAM_OPCODE 0x02
#define PAGE_PROGRAM4B_OPCODE 0x12
#define DUAL_PAGE_PROGRAM_OPCODE 0xa2
#define DUAL_PAGE_PROGRAM4B_OPCODE 0xa4
#define QUAD_PAGE_PROGRAM_OPCODE 0x32
#define QUAD_PAGE_PROGRAM4B_OPCODE 0x34
#define DUAL_IO_READ_OPCODE 0xbb
#define DUAL_IO_READ4B_OPCODE 0xbc
#define QUAD_IO_READ_OPCODE 0xeb
#define QUAD_IO_READ4B_OPCODE 0xec
#define FAST_READ_OPCODE 0x0b
#define FAST_READ4B_OPCODE 0x0c
#define READ_SFDP_OPCODE 0x5a
#define DEEP_POWER_DOWN_OPCODE 0xb9
#define RELEASE_FROM_DEEP_POWER_DOWN_OPCODE 0xab
#define READ_IDENTIFICATION_OPCODE 0x9f
#define READ_UNIQUE_ID_OPCODE 0x4b
#define ERASE_SECURITY_AREA_OPCODE 0x44
#define PROGRAM_SECURITY_AREA_OPCODE 0x42
#define READ_SECURITY_AREA_OPCODE 0x48
#define RESET_EN_OPCODE 0x66
#define RESET_OPCODE 0x99
#define PROG_ERASE_SUSPEND 0x75
#define PROG_ERASE_RESUME 0x7a
#define CONTINUOUS_READ_MODE_RESET 0xff

#define XIP_MODE_BITS 0xa0

#define DUMMY_BYTE_VAL 0x3c

enum mw_wid_type
{
    SINGLE_WIRE = 0,
    DUAL_WIRE,
    QUAD_WIRE,
};

struct flash_wr_rd_reg_param
{
    uint8_t *buf;
    uint8_t opcode;
    uint8_t length;
};

void hal_flashx_program_operation(struct hal_flash_env *env,void *param);

void hal_flashx_write_reg_operation(struct hal_flash_env *env,void *param);

void hal_flashx_read_operation(struct hal_flash_env *env,void *param);

void hal_flashx_read_reg_operation(struct hal_flash_env *env,void *param);

void hal_flashx_chip_erase_operation(struct hal_flash_env *env,void *param);

void do_hal_flashx_program_swint(struct hal_flash_env *env,void *param);

void do_hal_flashx_write_reg_swint(struct hal_flash_env *env,void *param);

void do_hal_flashx_read_swint(struct hal_flash_env *env,void *param);

void do_hal_flashx_read_reg_swint(struct hal_flash_env *env,void *param);

void do_hal_flashx_chip_erase_swint(struct hal_flash_env *env,void *param);

void hal_flashx_write_enable(struct hal_flash_env *env);

void do_hal_flashx_write_reg_func(struct hal_flash_env *env,void * param);

void do_hal_flashx_read_func(struct hal_flash_env *env,void *param);

void do_hal_flashx_read_reg_func(struct hal_flash_env *env,void *param);

void do_hal_flashx_prog_func(struct hal_flash_env *env,void *param);

void do_hal_flashx_chip_erase_func(struct hal_flash_env *env,void *param);

void flashx_reading_critical(void (*func)(struct hal_flash_env *,void *),struct hal_flash_env *env,void *param);

void flashx_writing_critical(void (*func)(struct hal_flash_env *,void *),struct hal_flash_env *env,void *param);

void do_hal_flashx_read(struct hal_flash_env *env,void *param);

void do_hal_flashx_program(struct hal_flash_env *env,void *param);

void do_hal_flashx_write_reg(struct hal_flash_env *env,void *param);

void do_hal_flashx_read_reg(struct hal_flash_env *env,void *param);

void do_hal_flashx_chip_erase(struct hal_flash_env *env,void *param);

void hal_flashx_read_addr_8bit_dummy(struct hal_flash_env *env,uint32_t offset, uint8_t * data, uint32_t length,uint8_t opcode,bool addr4b);

void sync_for_xip_stop(struct hal_flash_env *env);

#ifdef __cplusplus
}
#endif

#endif

