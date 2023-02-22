#ifndef HAL_FLASH_INT_H_
#define HAL_FLASH_INT_H_
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "sdk_config.h"
#include "ls_hal_flash.h"
#include "hal_flash_svcall.h"
#include "cpu.h"
#include "compile_flag.h"
#include "ls_dbg.h"
#include "platform.h"
#if defined(FLASH_PROG_ALGO) && __arm__
#define HAL_FLASH_C_MERGED
#endif
#define PUYA_FLASH_WORKAROUND 1
#define TSINGTENG_FLASH_WORKAROUND 2
#if (defined(FLASH_PROG_ALGO) || BOOT_RAM==1)
#define SUSPEND_WORKAROUND 0
#else
#ifndef SUSPEND_WORKAROUND 
#define SUSPEND_WORKAROUND PUYA_FLASH_WORKAROUND
#endif
#endif
#if defined(LM3050)
#define DUAL_CONTINUOUS_MODE_OFF 1
#else
#define DUAL_CONTINUOUS_MODE_OFF 0
#endif

#define WRITE_STATUS_REGISTER_OPCODE 0x01
#define READ_STATUS_REGISTER_0_OPCODE 0x05
#define READ_STATUS_REGISTER_1_OPCODE 0x35
#define WRITE_ENABLE_OPCODE 0x06
#define PAGE_ERASE_OPCODE 0x81
#define SECTOR_ERASE_OPCODE 0x20
#define CHIP_ERASE_OPCODE 0x60
#define PAGE_PROGRAM_OPCODE 0x02
#define DUAL_PAGE_PROGRAM_OPCODE 0xa2
#define QUAD_PAGE_PROGRAM_OPCODE 0x32
#define DUAL_IO_READ_OPCODE 0xbb
#define QUAD_IO_READ_OPCODE 0xeb
#define FAST_READ_OPCODE 0x0b
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

#define XIP_MODE_BITS 0x20

#define DUMMY_BYTE_VAL 0x3c

enum mw_wid_type
{
    SINGLE_WIRE = 0,
    DUAL_WIRE,
    QUAD_WIRE,
};

struct flash_erase_param
{
    uint8_t addr[3];
    uint8_t opcode;
};

struct flash_read_reg_param
{
    uint8_t *buf;
    uint8_t opcode;
    uint8_t length;    
};

void hal_flash_write_enable(void);

void do_hal_flash_write_status_reg_func(void * param);

void do_hal_flash_erase_func(void *param);

void do_hal_flash_chip_erase_func(void *param);

void do_hal_flash_read_func(void *param);

void do_hal_flash_read_reg_func(void *param);

void do_hal_flash_erase_security_area_func(void *param);

void do_hal_flash_program_security_area_func(void *param);

void do_hal_flash_read_security_area_func(void *param);

void do_hal_flash_prog_func(void *param);

void flash_reading_critical(void (*func)(void *),void *param);

void flash_writing_critical(void (*func)(void *),void *param);

void do_hal_flash_read(void *param);

void do_hal_flash_erase(uint32_t offset,uint8_t opcode);

void do_hal_flash_program(uint32_t offset,uint8_t *data,uint16_t length,uint8_t multi_type);

void do_hal_flash_chip_erase(void);

void do_hal_flash_write_status_reg(uint16_t status);

void do_hal_flash_erase_security_area(uint8_t idx);

void do_hal_flash_program_security_area(uint8_t idx, uint16_t addr, uint8_t * data, uint16_t length);

void do_hal_flash_read_security_area(uint8_t idx,uint16_t addr,uint8_t *data,uint16_t length);

void do_hal_flash_read_reg(void *param);

void hal_flash_read_24bit_addr_8bit_dummy(uint32_t offset, uint8_t * data, uint16_t length,uint8_t opcode);

void sync_for_xip_stop(void);
#endif

