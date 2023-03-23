#ifndef _MSC_DISK_H
#define _MSC_DISK_H

#define DEV_FLASH_ADDRESS           0x14000         //0x00800000 + 0x14000
#define DEV_FLASH_ADDRESS_END       0x7ffff         

#define DISK_BLOCK_NUM              800             // sector number    400K = 400 * 1024 / 512 = 800
#define DISK_BLOCK_SIZE             512             // sector size

#endif