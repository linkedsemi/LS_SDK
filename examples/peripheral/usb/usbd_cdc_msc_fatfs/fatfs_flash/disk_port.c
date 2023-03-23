#include "disk_port.h"
#include "ls_hal_flash.h"
#include "msc_disk.h"
// #include "log.h"

DSTATUS RAM_disk_status(void)
{
    return 0;
}

DSTATUS RAM_disk_initialize(void)
{
    return 0;
}

DRESULT RAM_disk_read(BYTE *buff, DWORD sector, UINT count)
{
    uint32_t dev_flash_address;
    uint32_t dev_flash_address_end;
    int i;

    // LOG_I("disk_read sector:%d,count:%d\n", sector, count);
    dev_flash_address_end = DEV_FLASH_ADDRESS_END - DISK_BLOCK_SIZE;

    for (i = 0; i < count; i++)
    {
        dev_flash_address = DEV_FLASH_ADDRESS + sector * DISK_BLOCK_SIZE;

        if (dev_flash_address > dev_flash_address_end)
            break;

        hal_flash_fast_read(dev_flash_address, buff, DISK_BLOCK_SIZE);

        sector++;
        buff += DISK_BLOCK_SIZE;
    }

    return RES_OK;
}

DRESULT RAM_disk_write(const BYTE *buff, DWORD sector, UINT count)
{
    uint32_t dev_flash_address;
    uint32_t dev_flash_address_end;
    BYTE *buf;
    int i;

    // LOG_I("disk_write sector:%d,count:%d\n", sector, count);
    dev_flash_address_end = DEV_FLASH_ADDRESS_END - DISK_BLOCK_SIZE;
    buf = (BYTE *)buff;
    for (i = 0; i < count; i++)
    {
        dev_flash_address = DEV_FLASH_ADDRESS + sector * DISK_BLOCK_SIZE;

        if (dev_flash_address > dev_flash_address_end)
            break;

        // Write 256 bytes twice
        hal_flash_page_erase(dev_flash_address);
        hal_flash_quad_page_program(dev_flash_address, buf, FLASH_PAGE_SIZE);

        dev_flash_address += FLASH_PAGE_SIZE;
        buf += FLASH_PAGE_SIZE;

        hal_flash_page_erase(dev_flash_address);
        hal_flash_quad_page_program(dev_flash_address, buf, FLASH_PAGE_SIZE);

        sector++;
    }

    return RES_OK;
}

DRESULT RAM_disk_ioctl(BYTE cmd, void *buff)
{
    //#define CTRL_SYNC			0	/* Complete pending write process (needed at FF_FS_READONLY == 0) */
    //#define GET_SECTOR_COUNT	1	/* Get media size (needed at FF_USE_MKFS == 1) */
    //#define GET_SECTOR_SIZE	2	/* Get sector size (needed at FF_MAX_SS != FF_MIN_SS) */
    //#define GET_BLOCK_SIZE	3	/* Get erase block size (needed at FF_USE_MKFS == 1) */
    //#define CTRL_TRIM			4	/* Inform device that the data on the block of sectors is no longer used (needed at FF_USE_TRIM == 1) */
    DRESULT res = RES_OK;

    switch (cmd)
    {
    case CTRL_SYNC:
        break;
    case GET_SECTOR_COUNT:
        *(DWORD *)buff = DISK_BLOCK_NUM;
        break;
    case GET_SECTOR_SIZE:
        *(DWORD *)buff = DISK_BLOCK_SIZE;
        break;
    case GET_BLOCK_SIZE:
        *(DWORD *)buff = 1;
        break;
    case CTRL_TRIM:
        res = RES_PARERR;
        break;
    default:
        res = RES_PARERR;
        break;
    }
    return res;
}
