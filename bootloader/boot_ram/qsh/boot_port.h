#ifndef BOOT_PORT_H_
#define BOOT_PORT_H_
#include "ls_soc_gpio.h"

#define TEMP_BUF_SIZE 0x800

#define BOOT_FLASH_SBL_ADDR         (0x0)
#define BOOT_FLASH_SBL_SIZE         (56 * 1024)
#define BOOT_FLASH_SBL_ENV_ADDR     (BOOT_FLASH_SBL_SIZE)
#define BOOT_FLASH_SBL_ENV_SIZE     (8 * 1024)

#define DICE_CDI_LENGTH             (0x40)

#define DICE_UDS_LENGTH             (0x40)

#define FLASH_CACHE_ADDR            (0x8000000)

#define COMMAND_RAM_BIST_SUPPORT    (0)

#define CHIP_ID_LENGTH              (0x8)

#define OTP_CODE_MAXLEN             (0xEB2)

#define OTP_LOG_WORD_LENGTH         (0x30)

#define LTPI_CODE_WAIT_TIME_US      (10 * 1000)

#define SM2_DECRYPT_MESSAGE_MAXLENGTH           (0x40)
#define SM2_DECRYPT_C1C3C2_STANDARD_MODE        (true)
#define SM2_DECRYPT_C1C2C3_NONSTANDARD_MODE     (false)

#define SFT_CTRL_REG_NUM_RESET_FLAG     (0x2)
#define SFT_CTRL_REG_NUM_WAKEUP_ADDR    (0x3)
#define SFT_CTRL_REG_LVDS_EXE_ADDR      (0x4)
#define SFT_CTRL_REG_NUM_BITMAP_ADDR    (0xB)
#define SFT_CTRL_REG_NUM_LIFE_TOKEN     (0xC)

#define STARTUP_PART_FLAG_MASK          (0xF)
#define FLASH_XIP_MODE_RESET_BIT        (4)
#define LIFE_CYCLE_UPDATE_REQ_BIT       (5)
#define LIFE_CYCLE_STATUS_OFFSET        (8)

#define MODE_PIN_LVDS       (0)
#define MODE_PIN_SECURE     (1)
#define MODE_PIN_UART       (2)
#define MODE_PIN_ALI        (3)

#define BOOT_UART_PIN_TX    (PN04)
#define BOOT_UART_PIN_RX    (PN03)

#endif
