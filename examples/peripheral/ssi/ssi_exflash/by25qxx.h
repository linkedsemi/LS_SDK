#ifndef _BY25QXX_H
#define _BY25QXX_H

#include <stddef.h>
#include <stdint.h>

/*COMMAND */
#define CMD_RESET_ENABLE       	0x66
#define CMD_RESET_MEMORY       	0x99
#define CMD_WRITE_ENABLE 	    0x06   	// write enable instruction
#define CMD_READ_STATUS_R0 	    0x05 	// read status register instruction
#define CMD_READ_DATA 		    0x03   	// read from memory instruction
#define CMD_DUAL_READ_DATA 	    0x3B   	// The Fast Read Dual Output (3Bh) instruction
#define CMD_QUAD_READ_DATA 		0x6B   	// The Fast Read Quad Output (6Bh) instruction
#define CMD_PAGE_PROGRAM 	    0x02    //
#define CMD_QUAD_PAGE_PROGRAM   0x32    //
#define CMD_SECTOR_ERASE 	    0x20    // sector erase instruction
#define CMD_CHIP_ERASE 		    0x60 	//
#define CMD_READ_MANDEV_ID 	    0X90  	//
#define CMD_RDID 			    0X9F   	// read identification

#define NOR_STATU_BUSY		    0x01   	// write in progress(wip)flag
#define DUMMY_BYTE       	    0xA5

#define WAITING_FOREVER		    0x00
#define EXFLASH_PAGE_SIZE	    256

// uint16_t nor_read_device_id(void);
uint32_t nor_read_jedec_id(uint8_t *id);
void nor_sector_erase(uint32_t address);
void nor_chip_erase(void);
void nor_write_page(uint32_t address, uint8_t *data, uint16_t data_len);
void nor_read_data(uint32_t address, uint8_t *data, uint32_t read_len);
uint8_t nor_wait_busy(uint32_t wait_ms);

#endif
