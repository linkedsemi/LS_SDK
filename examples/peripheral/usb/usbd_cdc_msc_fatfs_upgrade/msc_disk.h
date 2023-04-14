#ifndef _MSC_DISK_H
#define _MSC_DISK_H
/* +------------------+ 0x0087FFFF
 * |    252 Kbytes    |
 * | User flash space |
 * |------------------| 0x00841000
 * |    220 Kbytes    |
 * | USB flash disk   |
 * |------------------| 0x0080A000
 * |    40 Kbytes     |
 * | usb_fatfs_code   | 0x00800000
 * |------------------|*/

/***
 * const unsigned char __user_info_config[256] = {0X44, 0x33, 0x22, 0x11,0xdd, 0xcc, 0xbb, 0xaa};
 *
 * User Application .ld configuration
 *
 * signature information : __user_info_config
 *
 * .ld
 * MEMORY
 * {
 * RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 0x2000
 * FLASH (rx) : ORIGIN = 0x841000, LENGTH = 0x3F000
 * }
 *
 * SECTIONS
 * {
 * 	.user_info_config :
 *    {
 *       KEEP(*(.rodata.__user_info_config))
 *       . = ALIGN(0x100);
 *     } >FLASH
 *  ........
 */

#define DEV_FLASH_ADDRESS 0xA000 // 0x00800000 + 0xA000
#define DEV_FLASH_ADDRESS_END 0x40fff

#define DISK_BLOCK_NUM 440  // sector number    220KB = 220 * 1024 / 512 = 440
#define DISK_BLOCK_SIZE 512 // sector size

#endif
