#ifndef LS_HAL_EMMC_H_
#define LS_HAL_EMMC_H_
#include "HAL_def.h"
#include <stdbool.h>
#include <stdint.h>
#include "reg_emmc_type.h"
#include "ls_msp_emmc.h"

#define BIT(n)  (1UL << (n))
#define CONFIG_SDHC_BUFFER_ALIGNMENT 32
#define CONFIG_SD_DATA_RETRIES 3
#define CONFIG_MMC_RCA 0x2
#define MMC_RCA_ARG (CONFIG_MMC_RCA << 16U)
#define MMC_REL_ADR_ARG (CONFIG_MMC_RCA << 16U)
#define CONFIG_SD_DATA_TIMEOUT 10000
#define ETIMEDOUT 116
#define CONFIG_SD_RETRY_COUNT 10
#define SDMMC_R1_TRANSFER 4
#define CONFIG_SD_CMD_TIMEOUT 200
#define SD_R1_CURRENT_STATE(x) (((x) & SD_R1_CUR_STATE) >> 9U)
#define SDHC_NATIVE_RESPONSE_MASK 0xF
#define LINKEDSEMI_SDHCI_DEFAULT_TIMEOUT (5000U)
#define CONFIG_SD_CMD_RETRIES 0
#define CONFIG_SD_OCR_RETRY_COUNT 1000
#define SDHCI_DEFAULT_BOUNDARY_ARG    (7)
#define MMC_EXT_CSD_BYTES 512

enum mmc_ocr_flag {
    MMC_OCR_VDD170_195FLAG = BIT(7),
    MMC_OCR_VDD20_26FLAG = 0x7F << 8,
    MMC_OCR_VDD27_36FLAG = 0x1FF << 15,
    MMC_OCR_SECTOR_MODE = BIT(30),
    MMC_OCR_PWR_BUSY_FLAG = BIT(31)
};

enum sd_opcode {
    SD_GO_IDLE_STATE = 0,
    MMC_SEND_OP_COND = 1,
    SD_ALL_SEND_CID = 2,
    SD_SEND_RELATIVE_ADDR = 3,
    MMC_SEND_RELATIVE_ADDR = 3,
    SDIO_SEND_OP_COND = 5, /* SDIO cards only */
    SD_SWITCH = 6,
    SD_SELECT_CARD = 7,
    SD_SEND_IF_COND = 8,
    MMC_SEND_EXT_CSD = 8,
    SD_SEND_CSD = 9,
    SD_SEND_CID = 10,
    SD_VOL_SWITCH = 11,
    SD_STOP_TRANSMISSION = 12,
    SD_SEND_STATUS = 13,
    MMC_CHECK_BUS_TEST = 14,
    SD_GO_INACTIVE_STATE = 15,
    SD_SET_BLOCK_SIZE = 16,
    SD_READ_SINGLE_BLOCK = 17,
    SD_READ_MULTIPLE_BLOCK = 18,
    SD_SEND_TUNING_BLOCK = 19,
    MMC_SEND_BUS_TEST = 19,
    MMC_SEND_TUNING_BLOCK = 21,
    SD_SET_BLOCK_COUNT = 23,
    SD_WRITE_SINGLE_BLOCK = 24,
    SD_WRITE_MULTIPLE_BLOCK = 25,
    SD_ERASE_BLOCK_START = 32,
    SD_ERASE_BLOCK_END = 33,
    SD_ERASE_BLOCK_OPERATION = 38,
    SDIO_RW_DIRECT = 52,
    SDIO_RW_EXTENDED = 53,
    SD_APP_CMD = 55,
    SD_SPI_READ_OCR = 58, /* SPI mode only */
    SD_SPI_CRC_ON_OFF = 59, /* SPI mode only */
};

enum sdhci_card_response_type {
    CARD_RESPONSE_TYPE_NONE = 0U, /*!< Response type: none */
    CARD_RESPONSE_TYPE_R1 = 1U, /*!< Response type: R1 */
    CARD_RESPONSE_TYPE_R1B = 2U, /*!< Response type: R1b */
    CARD_RESPONSE_TYPE_R2 = 3U, /*!< Response type: R2 */
    CARD_RESPONSE_TYPE_R3 = 4U, /*!< Response type: R3 */
    CARD_RESPONSE_TYPE_R4 = 5U, /*!< Response type: R4 */
    CARD_RESPONSE_TYPE_R5 = 6U, /*!< Response type: R5 */
    CARD_RESPONSE_TYPE_R5B = 7U, /*!< Response type: R5b */
    CARD_RESPONSE_TYPE_R6 = 8U, /*!< Response type: R6 */
    CARD_RESPONSE_TYPE_R7 = 9U, /*!< Response type: R7 */
};

enum sdhci_card_command_type {
    CARD_COMMAND_TYPE_NORMAL = 0U, /*!< Normal command */
    CARD_COMMAND_TYPE_SUSPEND = 1U, /*!< Suspend command */
    CARD_COMMAND_TYPE_RESUME = 2U, /*!< Resume command */
    CARD_COMMAND_TYPE_ABORT = 3U, /*!< Abort command */
};

enum sd_return_codes {
    SD_RETRY = 1,
    SD_NOT_SDIO = 2,
    SD_RESTART = 3,
};

enum sd_app_cmd {
    SD_APP_SEND_NUM_WRITTEN_BLK = 22,
    SD_APP_SEND_SCR = 51,
};

enum sdhci_present_status_flag {
    SDHCI_COMMAND_INHIBIT_FLAG = 0x1, /*!< Command inhibit */
    SDHCI_DATA_INHIBIT_FLAG = 0x2, /*!< Data inhibit */
    SDHCI_DATA0_LINE_LEVEL_FLAG = (1U << 20), /*!< Data0 line signal level */
};

enum sd_rsp_type {
    SD_RSP_TYPE_NONE = 0U,
    SD_RSP_TYPE_R1 = 1U,
    SD_RSP_TYPE_R1b = 2U,
    SD_RSP_TYPE_R2 = 3U,
    SD_RSP_TYPE_R3 = 4U,
    SD_SPI_RSP_TYPE_R1 = (1U << 4),
    SD_SPI_RSP_TYPE_R2 = (3U << 4),
};

enum sd_ocr_flag {
    /** Power up busy status */
    SD_OCR_PWR_BUSY_FLAG = BIT(31),
};

enum sdhci_command_flag {
    SDHCI_CMD_RESP_LONG = 0x1,
    SDHCI_CMD_RESP_SHORT = 0x2,
    SDHCI_CMD_RESP_SHORT_BUSY = 0x3,
    SDHCI_ENABLE_CMD_CRC_FLAG = SDHCI_CMD_CRC,
    SDHCI_ENABLE_CMD_INDEX_CHK_FLAG = SDHCI_CMD_INDEX,
    SDHCI_ENABLE_CMD_DATA_PRESENT_FLAG = SDHCI_CMD_DATA,
    SDHCI_ENABLE_COMMAND_TYPE_NORMAL = 0x00,
    SDHCI_ENABLE_COMMAND_TYPE_SUSPEND = 0x40,
    SDHCI_ENABLE_COMMAND_TYPE_RESUME = 0x80,
    SDHCI_ENABLE_COMMAND_TYPE_ABORT = 0xC0,
};

enum sdhci_transfer_mode {
    SDHCI_ENABLE_DMA_FLAG = SDHCI_TRNS_DMA, /*!< ENABLE DMA */
    SDHCI_ENABLE_BLOCK_COUNT_FLAG = SDHCI_TRNS_BLK_CNT_EN, /*!< ENABLE BLOCK COUNT */
    SDHCI_ENABLE_AUTO_COMMAND12_FLAG = SDHCI_TRNS_AUTO_CMD12, /*!< ENABLE AUTO CMD12 */
    SDHCI_DATA_READ_FLAG = SDHCI_TRNS_READ, /*!< ENABLE DATA READ */
    SDHCI_MULTIPLE_BLOCK_FLAG = SDHCI_TRNS_MULTI, /*!< MULTIPLE BLOCK DATA READ/WRITE */
    SDHCI_ENABLE_AUTO_COMMAND23_FLAG = SDHCI_TRNS_AUTO_CMD23, /*!< ENABLE AUTO CMD23 */
};

enum sd_r1_status {
    /* Bits 0-2 reserved */
    SD_R1_AUTH_ERR = BIT(3),
    /* Bit 7 reserved */
    SD_R1_RDY_DATA = BIT(8),
    SD_R1_CUR_STATE = (0xFU << 9),
    SD_R1_ERASE_SKIP = BIT(15),
    SD_R1_CSD_OVERWRITE = BIT(16),
    /* Bits 17-18 reserved */
    SD_R1_ERR = BIT(19),
    SD_R1_CC_ERR = BIT(20),
    SD_R1_ECC_FAIL = BIT(21),
    SD_R1_ILLEGAL_CMD = BIT(22),
    SD_R1_CRC_ERR = BIT(23),
    SD_R1_UNLOCK_FAIL = BIT(24),
    SD_R1_WP_VIOLATION = BIT(26),
    SD_R1_ERASE_PARAM = BIT(27),
    SD_R1_ERASE_SEQ_ERR = BIT(28),
    SD_R1_BLOCK_LEN_ERR = BIT(29),
    SD_R1_ADDR_ERR = BIT(30),
    SD_R1_OUT_OF_RANGE = BIT(31),
    SD_R1_ERR_FLAGS = (SD_R1_AUTH_ERR |
            SD_R1_ERASE_SKIP |
            SD_R1_CSD_OVERWRITE |
            SD_R1_ERR |
            SD_R1_CC_ERR |
            SD_R1_ECC_FAIL |
            SD_R1_ILLEGAL_CMD |
            SD_R1_CRC_ERR |
            SD_R1_UNLOCK_FAIL |
            SD_R1_WP_VIOLATION |
            SD_R1_ERASE_PARAM |
            SD_R1_ERASE_SEQ_ERR |
            SD_R1_BLOCK_LEN_ERR |
            SD_R1_ADDR_ERR |
            SD_R1_OUT_OF_RANGE),
};

struct sdhci_data {
    bool enable_auto_command12; /*!< Enable auto CMD12 */
    bool enable_auto_command23; /*!< Enable auto CMD23 */
    bool enableIgnoreError; /*!< Enable to ignore error event to read/write all the data */
    bool execute_tuning; /*!< execute tuning flag */
    uint32_t block_size; /*!< Block size */
    uint32_t block_count; /*!< Block count */
    uint32_t *rx_data; /*!< Buffer to save data read */
    const uint32_t *tx_data; /*!< Data buffer to write */
    uint32_t timeout_ms; /*!< data timeout in milliseconds */
};

struct sdhc_command {
    uint32_t opcode; /*!< SD Host specification CMD index */
    uint32_t arg; /*!< SD host specification argument */
    uint32_t response[4]; /*!< SD card response field */
    uint32_t response_type; /*!< Expected SD response type */
    unsigned int retries; /*!< Max number of retries */
    int timeout_ms; /*!< Command timeout in milliseconds */
};

struct sdhci_command {
    uint32_t index; /*!< Command index */
    uint32_t argument; /*!< Command argument */
    enum sdhci_card_command_type type; /*!< Command type */
    enum sdhci_card_response_type response_type; /*!< Command response type */
    uint32_t response[4U]; /*!< Response for this command */
    uint32_t response_error_flags; /*!< response error flag, the flag which need to check
                                                 the command reponse*/
    uint16_t flags; /*!< Cmd flags */
    uint16_t flags2; /*xfer mode*/
    uint32_t timeout_ms; /*!< data timeout in milliseconds */
};

// struct sdhc_data {
//     unsigned int block_addr; /*!< Block to start read from */
//     unsigned int block_size; /*!< Block size */
//     unsigned int blocks; /*!< Number of blocks */
//     unsigned int bytes_xfered; /*!< populated with number of bytes sent by SDHC */
//     void *data; /*!< Data to transfer or receive */
//     int timeout_ms; /*!< data timeout in milliseconds */
// };

// typedef struct sdhci_host {
//     uint32_t  mapbase;
//     struct sdhci_data *sdhci_data;
//     struct sdhci_command *sdhci_command;
//     void *usdhc_adma2_table;
//     volatile bool transfer_sem;
//     uint16_t error_code;
//     uint32_t irq_status;
//     uint32_t max_clk;
//     uint8_t index;
//     uint8_t is_emmc_card;
//     uint8_t io_fixed_1v8;
//     uint8_t power_mode;
//     uint8_t have_phy;
//     uint8_t mshc_ctrl_r;
//     uint32_t rx_delay_line;
//     uint32_t tx_delay_line;
//     uint32_t transfer_status;
//     uint8_t bus_width;
//     uint32_t current_speed;
//     bool execute_tuning;
// }sdhci_host;

static void sys_write32(uint32_t data, uint32_t addr)
{
    *(volatile uint32_t *)addr = data;
}

static void sys_write16(uint16_t data, uint32_t addr)
{
    *(volatile uint16_t *)addr = data;
}

static void sys_write8(uint8_t data, uint32_t addr)
{
    *(volatile uint8_t *)addr = data;
}

static uint32_t sys_read32(uint32_t addr)
{
    uint32_t value;
    value = *(volatile uint32_t *)addr;
    return value;
}

static uint16_t sys_read16(uint32_t addr)
{
    uint16_t value;
    value = *(volatile uint16_t *)addr;
    return value;
}

static uint8_t sys_read8(uint32_t addr)
{
    uint8_t value;
    value = *(volatile uint8_t *)addr;
    return value;
}

static inline void sdhci_writeb(sdhci_host *host, uint8_t val, uint32_t reg)
{
    sys_write8(val, host->mapbase + reg);
}

static inline void sdhci_writew(sdhci_host *host, uint16_t val, uint32_t reg)
{
    sys_write16(val, host->mapbase + reg);
}

static inline void sdhci_writel(sdhci_host *host, uint32_t val, uint32_t reg)
{
    sys_write32(val, host->mapbase + reg);
}

static inline uint8_t sdhci_readb(sdhci_host *host, uint32_t reg)
{
    return sys_read8(host->mapbase + reg);
}

static inline uint16_t sdhci_readw(sdhci_host *host, int reg)
{
    return sys_read16(host->mapbase + reg);
}

static inline uint32_t sdhci_readl(sdhci_host *host, uint32_t reg)
{
    return sys_read32(host->mapbase + reg);
}

HAL_StatusTypeDef HAL_EMMC_Init(sdhci_host *hemmc);
HAL_StatusTypeDef HAL_EMMC_DeInit(sdhci_host *host);
uint32_t linkedsemi_sdhci_request(sdhci_host *host, struct sdhc_command *cmd, struct sdhc_data *data);
uint32_t sdhci_card_busy(sdhci_host *sdhci_host);
void HAL_LSEMMC_IRQHandler(sdhci_host *host);

#endif /* LS_HAL_EMMC_H_ */