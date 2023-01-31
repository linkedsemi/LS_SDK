#ifndef HAL_FLASH_SWINT_H_
#define HAL_FLASH_SWINT_H_
#include <stdint.h>
#include <stdbool.h>

void hal_flash_program_operation(void *param);

void hal_flash_erase_operation(void *param);

void hal_flash_read_operation(void *param);

void hal_flash_chip_erase_operation(void);

void hal_flash_erase_security_area_operation(uint8_t idx);

void hal_flash_program_security_area_operation(void *param);

void hal_flash_read_security_area_operation(void *param);

void hal_flash_read_reg_operation(void *param);

#endif

