#ifndef EXT_FLASH_H_
#define EXT_FLASH_H_
#include <stdint.h>

void ext_flash_driver_init(void);

void ext_flash_read_id(uint8_t jedec_id[3]);

void ext_flash_read(uint32_t offset,uint32_t *data,uint16_t length_by_word);

void ext_flash_addressing_mode_set(uint32_t flash_size);

#endif
