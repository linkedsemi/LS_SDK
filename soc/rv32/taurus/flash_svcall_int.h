#ifndef FLASH_SVCALL_INT_H_
#define FLASH_SVCALL_INT_H_
#include "core_rv32.h"
#if defined(FLASH_PROG_ALGO) || BOOT_RAM==1
#define GLOBAL_INT_MASK_STATUS() (!(__get_MSTATUS()&0x8))
#else
#define GLOBAL_INT_MASK_STATUS() (CLIC->MINTTHRESH)
#endif

void do_spi_flash_program_svcall(uint32_t offset,uint8_t *data,uint16_t length,uint8_t multi_type);
void do_spi_flash_erase_svcall(uint32_t offset,uint8_t opcode);
void do_spi_flash_read_svcall(void *param);
void do_spi_flash_read_reg_svcall(void *param);
void do_spi_flash_chip_erase_svcall(void);
void do_spi_flash_erase_security_area_svcall(uint8_t idx);
void do_spi_flash_program_security_area_svcall(uint8_t idx, uint16_t addr, uint8_t * data, uint16_t length);
void do_spi_flash_read_security_area_svcall(uint8_t idx, uint16_t addr, uint8_t * data, uint16_t length);

#endif
