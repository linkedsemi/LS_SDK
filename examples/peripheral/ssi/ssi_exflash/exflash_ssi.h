#ifndef _EXFLASH_SSI_H
#define _EXFLASH_SSI_H

#include "platform.h"
#include "ls_soc_gpio.h"

//////////////////////////////////////////

#define STD_SPI_MODE 0  // STD_SPI_MODE
#define DUAL_SPI_MODE 1 // DUAL_SPI_MODE
#define QUAD_SPI_MODE 2 // QUAD_SPI_MODE

#define SSI_SPI_MODE QUAD_SPI_MODE

//////////////////////////////////////////

#define FLASH_SPI_CS PA13
// #define FLASH_SPI_CS PB07 // CS

#define EX_FLASH_CS_LOW() io_clr_pin(FLASH_SPI_CS)
#define EX_FLASH_CS_HIGH() io_set_pin(FLASH_SPI_CS)

void exflash_ssi_init(void);

void exflash_ssi_std_write_byte(uint8_t data);
void exflash_ssi_std_write_data(uint8_t *data, uint16_t data_len);
// void exflash_ssi_dual_write_data(uint8_t *data, uint16_t data_len, uint32_t address);
void exflash_ssi_quad_write_data(uint8_t *data, uint16_t data_len, uint32_t address);

void exflash_ssi_std_read_data(uint8_t *data, uint16_t data_len);
void exflash_ssi_dual_read_data(uint8_t *data, uint16_t data_len, uint32_t address);
void exflash_ssi_quad_read_data(uint8_t *data, uint16_t data_len, uint32_t address);

#endif /* _EXFLASH_SSI_H */
