#include "FlashOS.h"
#include "reg_base_addr.h"
#include "ls_hal_flash.h"
/**
 * structure to describe flash device
 */
struct FlashDevice const FlashDevices  INDEVSECTION =  {
    .Ver = 6,                      // Reserved version description, do not modify!!!
    .DevName = "TAURUS SPI NOR FLASH",              // Flash name
    .CPU = "e906",              // CPU name, must in low case
    .FlashID = 0x123456,               // Flash ID
    .FlashType = "NorFlash",             // type
    .TotalSize = 16*1024*1024,               // Reserved
    .IsAccDirect = 0,                      // Access directly
    .rangeNumbers = 1,                      // RangeNumbers
	// {start address, the flash size, sector size}
    .Devs = {{FLASH_BASE_ADDR, 16*1024*1024, FLASH_SECTOR_SIZE}},
    .VendorName = "LinkedSemi"
};
