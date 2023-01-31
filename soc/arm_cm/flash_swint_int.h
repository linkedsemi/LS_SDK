#ifndef FLASH_SWINT_INT_H_
#define FLASH_SWINT_INT_H_
#include <stdbool.h>
#include "platform.h"

#define GLOBAL_INT_MASK_STATUS() __get_PRIMASK()

void do_hal_flash_program_swint(void *param);
void do_hal_flash_erase_swint(void *param);
void do_hal_flash_read_swint(void *param);
void do_hal_flash_read_reg_swint(void *param);
void do_hal_flash_chip_erase_swint(void);
void do_hal_flash_erase_security_area_swint(uint8_t idx);
void do_hal_flash_program_security_area_swint(void *param);
void do_hal_flash_read_security_area_swint(void *param);

#endif
