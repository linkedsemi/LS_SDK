#include "tinyfs_nvm.h"
#include "ls_hal_flash.h"

void (* const nvm_program)(uint32_t,uint8_t *,uint16_t) = hal_flash_quad_page_program;
void (* const nvm_read)(uint32_t, uint8_t *, uint16_t) = hal_flash_quad_io_read;
void (* const nvm_sector_ease)(uint32_t) = hal_flash_sector_erase;
