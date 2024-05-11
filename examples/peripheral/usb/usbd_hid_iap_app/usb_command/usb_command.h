
#ifndef __usb_command_H__
#define __usb_command_H__

#define EC_CMD_FRAME_HEAD 0xFF

// EC Commandc IDs
#define ID_CMD_READ_LINK_INFO 0x00U
#define ID_CMD_READ_EC_INFO 0x01U

#define ID_CMD_CONNECT_EC 0x02U
#define ID_CMD_RESET_EC 0x03U
#define ID_CMD_CONNECT_STATE 0x04U

#define ID_CMD_MEM_READ 0x10U
#define ID_CMD_MEM_WRITE 0x11U

#define ID_CMD_E_FLASH_LOAD 0x20U
#define ID_CMD_E_FLASH_ERASE 0x21U
#define ID_CMD_E_FLASH_INFO 0x22U
#define ID_CMD_E_FLASH_WRITE 0x23U
#define ID_CMD_E_FLASH_READ 0x24U
#define ID_CMD_E_FLASH_FETCH_EC 0x25U
#define ID_CMD_E_FLASH_READ_LINK 0x26U

#define ID_CMD_BIOS_FLASH_LOAD 0x30U
#define ID_CMD_BIOS_FLASH_ERASE 0x31U
#define ID_CMD_BIOS_FLASH_INFO 0x32U
#define ID_CMD_BIOS_FLASH_WRITE 0x33U
#define ID_CMD_BIOS_FLASH_READ 0x34U

#define ID_CMD_INVALID 0xFFU

// EC Status Code
#define RESPONSE1_OK 0x90
#define RESPONSE1_ERROR 0x68

#define RESPONSE2_OK 0x00
#define RESPONSE2_SUM_INVALID 0x01
#define RESPONSE2_COMMAND_INVALID 0x02
#define RESPONSE2_LENGTH_INVALID 0x03
#define RESPONSE2_TIMEOUT 0x04
#define RESPONSE2_ADDRESS_INVALID 0x09
#define RESPONSE2_CONNECT_ERROR 0x0a
#define RESPONSE2_FLASH_ALGO_EXEC_ERROR 0x0b
#define RESPONSE2_VERIFY_ERROR 0x0c

// EC Other
#define ID_PACKET_MIN_DATA_LENGTH 4
#define ID_PACKET_MAX_DATA_LENGTH 60
#define ID_PACKET_MAX_DATA_LENGTH2 56

#define EC_FLASH_ALGO_EXEC_WAITTING_MS 5000 // Running wait time

// NOR FLASH
// PUYA P25Q40SU
#define PUYA_FLASH_CHIP_ERASE_TIME_MS 3000   // typical 16ms,max 30ms
#define PUYA_FLASH_SECTOR_ERASE_TIME_MS 2000  // typical 16ms 4K-byte sector erase time,max 30ms
#define PUYA_FLASH_PROGRAM_TIME_MS 2000       // typical 2ms Single/Dual/Quad Page(s) program time,max 3ms

#define PUYA_FLASH_VERIFY_TIME_MS 3000 // xx ms

// BOYA BY25Q16BS
#define NOR_FLASH_CHIP_ERASE_TIME_MS 3000   // typical 10s,max 35S
#define NOR_FLASH_SECTOR_ERASE_TIME_MS 2000 // typical 50ms,max 400ms
#define NOR_FLASH_PROGRAM_TIME_MS 3000       // typical 0.6ms,max 2.4ms

#define NOR_FLASH_VERIFY_TIME_MS 3000 // xx ms

// READ 56 BYTES
#define NOR_FLASH_READ_TIME_MS 1000 // xx ms

#include <stddef.h>
#include <stdint.h>
#include <string.h>

typedef struct
{
    uint32_t address_base;
    uint32_t address_end;

} EC_Address_t;

typedef void (*PTR_FUN_NULL)(void);

typedef struct
{
    uint32_t flash_algo_var_address; // e-flash/bios-flash Variable address
    bool is_verfiy_download;
    bool is_flash_process;         // wait processing
    uint32_t download_bin_size;
    uint32_t download_bin_offset;
    uint32_t download_bin_start_address;
    uint32_t download_bin_crc32;
    // PTR_FUN_NULL flash_write_timeout_func;
} USB_Flash_Algo_t;
extern volatile bool g_ubReset_System;
extern USB_Flash_Algo_t usb_flash_algo_param;

extern void usb_command_execute(const uint8_t *request, uint8_t *response);

#endif /* __usb_command_H__ */
