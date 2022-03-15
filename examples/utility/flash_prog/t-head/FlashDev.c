#include "FlashOS.h"
#include "reg_base_addr.h"
#include "spi_flash.h"
/**
 * structure to describe flash device
 */
struct FlashDevice const FlashDevices  INDEVSECTION =  {
    6,                      // Reserved version description, do not modify!!!
    "TAURUS SPI NOR FLASH",              // Flash name
    "e902",              // CPU name, must in low case
    0x123456,               // Flash ID
    "NorFlash",             // type
    512*1024,               // Reserved
    0,                      // Access directly
    1,                      // RangeNumbers
	// {start address, the flash size, sector size}
    {{FLASH_BASE_ADDR, 0x80000, FLASH_SECTOR_SIZE}},
    "LinkedSemi"
};
