#include <string.h>
#include "platform.h"
#include "ls_soc_gpio.h"
#include "ls_msp_emmc.h"
#include "log.h"

#define SECTOR_COUNT 32
#define SECTOR_SIZE  512 /* subsystem should set all cards to 512 byte blocks */
#define BUF_SIZE     (SECTOR_SIZE * SECTOR_COUNT)
static uint8_t buf[BUF_SIZE] __aligned(CONFIG_SDHC_BUFFER_ALIGNMENT);
static uint8_t buf1[BUF_SIZE] __aligned(CONFIG_SDHC_BUFFER_ALIGNMENT);

int block_addr = 0;

uint8_t card_buffer[MMC_EXT_CSD_BYTES];

static sdhci_host emmc;

void EMMC_INIT(void)
{
#ifdef QSH
    emmc.mapbase = LSEMMC1;
#elif defined(RAPTOR)
    emmc.mapbase = LSEMMC;
#endif
    HAL_EMMC_Init(&emmc);
}

#ifdef QSH
    #include "reg_sysc_app_awo.h"
    void pinmux_init()
    {
        SYSC_APP_AWO->IO_FUNC[3][5] = 0xfff00000; //emmc func
        *(volatile uint32_t *)0x4006f2e4 = 0xfff0; //Pull_Up
        io_cfg_input(PM04); //dat[0]
        io_cfg_input(PM05); 
        io_cfg_input(PM06); 
        io_cfg_input(PM07); 
        io_cfg_input(PM08); 
        io_cfg_input(PM09); 
        io_cfg_input(PM10); 
        io_cfg_input(PM11); 
        io_cfg_input(PM12); //clk
        io_cfg_input(PM13); //cmd
        io_cfg_input(PM14); //ds
        io_cfg_input(PM15); //rstn
    }
#elif defined(RAPTOR)
    void pinmux_init()
    {
        pinmux_emmc_init();
    }
#endif

static uint32_t mmc_send_op_cond(struct sdhci_host *host, uint32_t ocr)
{
    struct sdhc_command cmd = {0};
    uint32_t ret = 0;
    uint32_t retries;

    cmd.opcode = MMC_SEND_OP_COND;
    cmd.arg = ocr;
    cmd.response_type = SD_RSP_TYPE_R3;
    cmd.timeout_ms = CONFIG_SD_CMD_TIMEOUT;

    for (retries = 0;
         retries < CONFIG_SD_OCR_RETRY_COUNT && !(cmd.response[0] & SD_OCR_PWR_BUSY_FLAG);
         retries++) {
        ret = linkedsemi_sdhci_request(host, &cmd, NULL);
        if (ret) {
            /* OCR failed */
            return ret;
        }
        if (ocr == 0) {
            /* Just probing */
            return 0;
        }
        DELAY_MS(10);
    }
    if (retries >= CONFIG_SD_OCR_RETRY_COUNT) {
        /* OCR timed out */
        LOG_I("Card never left busy state");
        return -ETIMEDOUT;
    }
    // LOG_I("MMC responded to CMD1 after %d attempts", retries);
    return 0;
}

static inline uint32_t sd_idle(struct sdhci_host *host)
{
    struct sdhc_command cmd;

    /* Reset card with CMD0 */
    cmd.opcode = SD_GO_IDLE_STATE;
    cmd.arg = 0x0;
    cmd.response_type = (SD_RSP_TYPE_NONE | SD_SPI_RSP_TYPE_R1);
    cmd.retries = CONFIG_SD_CMD_RETRIES;
    cmd.timeout_ms = CONFIG_SD_CMD_TIMEOUT;
    return linkedsemi_sdhci_request(host, &cmd, NULL);
}

static uint32_t sdmmc_read_cxd(struct sdhci_host *host, uint32_t opcode, uint32_t rca, uint32_t *cxd)
{
    struct sdhc_command cmd;
    uint32_t ret;

    cmd.opcode = opcode;
    cmd.arg = (rca << 16);
    cmd.response_type = SD_RSP_TYPE_R2;
    cmd.retries = CONFIG_SD_CMD_RETRIES;
    cmd.timeout_ms = CONFIG_SD_CMD_TIMEOUT;

    ret = linkedsemi_sdhci_request(host, &cmd, NULL);
    if (ret) {
        LOG_I("CMD%d failed: %d", opcode, ret);
        return ret;
    }
    /* CSD/CID is 16 bytes */
    memcpy(cxd, cmd.response, 16);
    return 0;
}

/* Reads card identification register, and decodes it */
uint32_t card_read_cid(struct sdhci_host *host)
{
    uint32_t cid[4];
    uint32_t ret;
    ret = sdmmc_read_cxd(host, SD_ALL_SEND_CID, 0, cid);
    if (ret) {
        return ret;
    }

    return 0;
}

static inline uint32_t sd_check_response(struct sdhc_command *cmd)
{
    if (cmd->response_type == SD_RSP_TYPE_R1) {
        return (cmd->response[0U] & SD_R1_ERR_FLAGS);
    }
    return 0;
}

static uint32_t mmc_set_rca(struct sdhci_host *host)
{
    struct sdhc_command cmd = {0};
    uint32_t ret;

    cmd.opcode = MMC_SEND_RELATIVE_ADDR;
    cmd.arg = MMC_RCA_ARG;
    cmd.response_type = SD_RSP_TYPE_R1;
    cmd.timeout_ms = CONFIG_SD_CMD_TIMEOUT;

    ret = linkedsemi_sdhci_request(host, &cmd, NULL);
    if (ret) {
        return ret;
    }
    ret = sd_check_response(&cmd);
    if (ret) {
        return ret;
    }

    // card->relative_addr = CONFIG_MMC_RCA;

    return 0;
}

static uint32_t mmc_read_csd(struct sdhci_host *host)
{
    uint32_t ret;
    struct sdhc_command cmd = {0};

    cmd.opcode = SD_SEND_CSD;
    cmd.arg = MMC_REL_ADR_ARG;
    cmd.response_type = SD_RSP_TYPE_R2;
    cmd.timeout_ms = CONFIG_SD_CMD_TIMEOUT;

    ret = linkedsemi_sdhci_request(host, &cmd, NULL);
    if (ret) {
        LOG_I("CMD9 failed: %d", ret);
        return ret;
    }

    return 0;
}

uint32_t sdmmc_select_card(struct sdhci_host *host)
{
    struct sdhc_command cmd;
    uint32_t ret;

    cmd.opcode = SD_SELECT_CARD;
    cmd.arg = (CONFIG_MMC_RCA << 16U);
    cmd.response_type = SD_RSP_TYPE_R1;
    cmd.retries = CONFIG_SD_CMD_RETRIES;
    cmd.timeout_ms = CONFIG_SD_CMD_TIMEOUT;

    ret = linkedsemi_sdhci_request(host, &cmd, NULL);
    if (ret) {
        LOG_I("CMD7 failed");
        return ret;
    }
    ret = sd_check_response(&cmd);
    if (ret) {
        LOG_I("CMD7 reports error");
        return ret;
    }
    return 0;
}

static inline uint32_t sd_retry(uint32_t(*cmd)(sdhci_host *host),
    struct sdhci_host *host,
    uint32_t retries)
{
    uint32_t ret = -ETIMEDOUT;

    while (retries-- >= 0) {
        /* Try cmd */
        ret = cmd(host);
        /**
         * Functions have 3 possible responses:
         * 0: success
         * SD_RETRY: retry command
         * other: does not retry
         */
        if (ret != SD_RETRY) {
            break;
        }
    }
    return ret == SD_RETRY ? -ETIMEDOUT : ret;
}

uint32_t sdmmc_read_status(struct sdhci_host *host)
{
    struct sdhc_command cmd;
    uint32_t ret;

    cmd.opcode = SD_SEND_STATUS;
    cmd.arg = 0;
    cmd.arg = CONFIG_MMC_RCA << 16U;
    cmd.response_type = (SD_RSP_TYPE_R1 | SD_SPI_RSP_TYPE_R2);
    cmd.retries = CONFIG_SD_CMD_RETRIES;
    cmd.timeout_ms = CONFIG_SD_CMD_TIMEOUT;

    ret = linkedsemi_sdhci_request(host, &cmd, NULL);
    if (ret) {
        return SD_RETRY;
    }

    /* Otherwise, check native card response */
    if ((cmd.response[0U] & SD_R1_RDY_DATA) &&
        (SD_R1_CURRENT_STATE(cmd.response[0U]) == SDMMC_R1_TRANSFER)) {
        return 0;
    }
    /* Valid response, the card is busy */
    return -EBUSY;
}

uint32_t sdmmc_wait_ready(struct sdhci_host *host)
{
    uint32_t ret, timeout = CONFIG_SD_DATA_TIMEOUT * 1000;

    do {
        if (!sdhci_card_busy(host)) {
            /* Check card status */
            ret = sd_retry(sdmmc_read_status, host, CONFIG_SD_RETRY_COUNT);
            if (ret == 0) {
                return 0;
            }
            if (ret == -ETIMEDOUT) {
                /* If this check timed out, then the total
                 * time elapsed in microseconds is
                 * SD_CMD_TIMEOUT * SD_RETRY_COUNT * 1000
                 */
                timeout -= (CONFIG_SD_CMD_TIMEOUT *
                        CONFIG_SD_RETRY_COUNT) * 1000;
            }
        }
        /* Delay 125us before polling again */
        DELAY_US(125);
        timeout -= 125;
    } while (timeout > 0);
    return -EBUSY;
}

uint32_t mmc_card_init(struct sdhci_host *host)
{
    uint32_t ret = 0;
    uint32_t ocr_arg = 0U;

    /* Probe to see if card is an MMC card */
    ret = mmc_send_op_cond(host, ocr_arg);
    if (ret) {
        return ret;
    }

    /* Modern SDHC always at least supports 512 byte block sizes,
     * which is enough to support sectors
     */
    ocr_arg |= MMC_OCR_SECTOR_MODE | MMC_OCR_VDD27_36FLAG;

    /* CMD1 */
    ret = mmc_send_op_cond(host, ocr_arg);
    if (ret) {
        LOG_I("Failed to query card OCR");
        return ret;
    }

    /* CMD2 */
    ret = card_read_cid(host);
    if (ret) {
        return ret;
    }

    /* CMD3 */
    ret = mmc_set_rca(host);
    if (ret) {
        LOG_I("Failed on sending RCA to card");
        return ret;
    }

    /* CMD9 */
    ret = mmc_read_csd(host);
    if (ret) {
        return ret;
    }

    /* CMD7 */
    ret = sdmmc_select_card(host);
    if (ret) {
        return ret;
    }

    return 0;
}

static int mmc_read_blocks(struct sdhci_host *host, uint8_t *rbuf, uint32_t start_block, uint32_t num_blocks)
{
    int ret;
    struct sdhc_command cmd;
    struct sdhc_data data;

    /*
     * Note: The SD specification allows for CMD23 to be sent before a
     * transfer in order to set the block length (often preferable).
     * The specification also requires that CMD12 be sent to stop a transfer.
     * However, the host specification defines support for "Auto CMD23" and
     * "Auto CMD12", where the host sends CMD23 and CMD12 automatically to
     * remove the overhead of interrupts in software from sending these
     * commands. Therefore, we will not handle CMD12 or CMD23 at this layer.
     * The host SDHC driver is expected to recognize CMD17, CMD18, CMD24,
     * and CMD25 as special read/write commands and handle CMD23 and
     * CMD12 appropriately.
     */
    cmd.opcode = (num_blocks == 1U) ? SD_READ_SINGLE_BLOCK : SD_READ_MULTIPLE_BLOCK;

    cmd.arg = start_block;

    cmd.response_type = (SD_RSP_TYPE_R1 | SD_SPI_RSP_TYPE_R1);
    cmd.retries = CONFIG_SD_DATA_RETRIES;
    cmd.timeout_ms = CONFIG_SD_CMD_TIMEOUT;

    data.block_addr = start_block;
    data.block_size = 512;
    data.blocks = num_blocks;
    data.data = rbuf;
    data.timeout_ms = CONFIG_SD_DATA_TIMEOUT;

    // LOG_I("READ: Sector = %u, Count = %u", start_block, num_blocks);

    ret = linkedsemi_sdhci_request(host, &cmd, &data);
    if (ret) {
        LOG_I("Failed to read from SDMMC %d", ret);
        return ret;
    }

    /* Verify card is back in transfer state after read */
    ret = sdmmc_wait_ready(host);
    if (ret) {
        LOG_I("Card did not return to ready state");
        return -ETIMEDOUT;
    }
    return 0;
}

static inline uint32_t mmc_send_cmd0_0xf0f0f0f0(struct sdhci_host *host)
{
    struct sdhc_command cmd;

    /* Reset card with CMD0 */
    cmd.opcode = SD_GO_IDLE_STATE;
    cmd.arg = 0xF0F0F0F0;
    cmd.response_type = (SD_RSP_TYPE_NONE | SD_SPI_RSP_TYPE_R1);
    cmd.retries = CONFIG_SD_CMD_RETRIES;
    cmd.timeout_ms = CONFIG_SD_CMD_TIMEOUT;
    return linkedsemi_sdhci_request(host, &cmd, NULL);
}

static inline uint32_t mmc_send_cmd0_0xfffffffa(struct sdhci_host *host)
{
    struct sdhc_command cmd;

    /* Reset card with CMD0 */
    cmd.opcode = SD_GO_IDLE_STATE;
    cmd.arg = 0xFFFFFFFA;
    cmd.response_type = (SD_RSP_TYPE_NONE | SD_SPI_RSP_TYPE_R1);
    cmd.retries = CONFIG_SD_CMD_RETRIES;
    cmd.timeout_ms = CONFIG_SD_CMD_TIMEOUT;
    return linkedsemi_sdhci_request(host, &cmd, NULL);
}

static int mmc_read_ext_csd(struct sdhci_host *host, uint8_t *rbuf)
{
    int ret;
    struct sdhc_command cmd = {0};
    struct sdhc_data data = {0};

    cmd.opcode = MMC_SEND_EXT_CSD;
    cmd.arg = 0;
    cmd.response_type = SD_RSP_TYPE_R1;
    cmd.timeout_ms = CONFIG_SD_CMD_TIMEOUT;

    data.block_size = MMC_EXT_CSD_BYTES;
    data.blocks = 1;
    data.data = rbuf;
    data.timeout_ms = CONFIG_SD_DATA_TIMEOUT;

    ret = linkedsemi_sdhci_request(host, &cmd, &data);
    if (ret) {
        LOG_I("CMD8 (send_ext_csd) failed: %d", ret);
        return ret;
    }

    // LOG_I("Card block count is %d, block size is %d", card->block_count, card->block_size);

    return 0;
}

static uint32_t mmc_set_rst_n_function_enable(struct sdhci_host *host)
{
    uint32_t ret;
    struct sdhc_command cmd = {0};
    cmd.arg = 0x3a20100;

    /* Set Card Bus Width */
    cmd.opcode = SD_SWITCH;
    cmd.response_type = SD_RSP_TYPE_R1b;
    cmd.timeout_ms = CONFIG_SD_CMD_TIMEOUT;
    ret = linkedsemi_sdhci_request(host, &cmd, NULL);
    sdmmc_wait_ready(host);
    if (ret) {
        LOG_I("Setting card data bus width failed: %d", ret);
        return ret;
    }
    return ret;
}

static uint32_t mmc_set_bootpartition_enable_boot1(struct sdhci_host *host)
{
    uint32_t ret;
    struct sdhc_command cmd = {0};
    // cmd.arg = 0x3b34800; //bootpartition_en
    cmd.arg = 0x3b30800; //bootpartition_en

    // cmd.arg = 0x3b37800; //regular
    /* Set Card Bus Width */
    cmd.opcode = SD_SWITCH;
    cmd.response_type = SD_RSP_TYPE_R1b;
    cmd.timeout_ms = CONFIG_SD_CMD_TIMEOUT;
    ret = linkedsemi_sdhci_request(host, &cmd, NULL);
    sdmmc_wait_ready(host);
    if (ret) {
        LOG_I("Setting card data bus width failed: %d", ret);
        return ret;
    }
    return ret;
}

static uint32_t mmc_set_bootpartition_enable_boot2(struct sdhci_host *host)
{
    uint32_t ret;
    struct sdhc_command cmd = {0};
    cmd.arg = 0x3b35000; //bootpartition_en
    // cmd.arg = 0x3b37800; //regular

    /* Set Card Bus Width */
    cmd.opcode = SD_SWITCH;
    cmd.response_type = SD_RSP_TYPE_R1b;
    cmd.timeout_ms = CONFIG_SD_CMD_TIMEOUT;
    ret = linkedsemi_sdhci_request(host, &cmd, NULL);
    sdmmc_wait_ready(host);
    if (ret) {
        LOG_I("Setting card data bus width failed: %d", ret);
        return ret;
    }
    return ret;
}

static uint32_t mmc_set_partition_access_boot1(struct sdhci_host *host)
{
    uint32_t ret;
    struct sdhc_command cmd = {0};
    cmd.arg = 0x3b34100;

    /* Set Card Bus Width */
    cmd.opcode = SD_SWITCH;
    cmd.response_type = SD_RSP_TYPE_R1b;
    cmd.timeout_ms = CONFIG_SD_CMD_TIMEOUT;
    ret = linkedsemi_sdhci_request(host, &cmd, NULL);
    sdmmc_wait_ready(host);
    if (ret) {
        LOG_I("Setting card data bus width failed: %d", ret);
        return ret;
    }
    return ret;
}

static uint32_t mmc_set_partition_access_boot2(struct sdhci_host *host)
{
    uint32_t ret;
    struct sdhc_command cmd = {0};
    cmd.arg = 0x3b34200;

    /* Set Card Bus Width */
    cmd.opcode = SD_SWITCH;
    cmd.response_type = SD_RSP_TYPE_R1b;
    cmd.timeout_ms = CONFIG_SD_CMD_TIMEOUT;
    ret = linkedsemi_sdhci_request(host, &cmd, NULL);
    sdmmc_wait_ready(host);
    if (ret) {
        LOG_I("Setting card data bus width failed: %d", ret);
        return ret;
    }
    return ret;
}

void mmc_boot_partition_en(struct sdhci_host *host)
{
    mmc_send_cmd0_0xf0f0f0f0(host);
    mmc_send_cmd0_0xfffffffa(host);
}

int mmc_write_blocks(struct sdhci_host *host, const uint8_t *wbuf, uint32_t start_block,
              uint32_t num_blocks)
{
    uint32_t ret;
    struct sdhc_command cmd;
    struct sdhc_data data;

    /*
     * See the note in card_read() above. We will not issue CMD23
     * or CMD12, and expect the host to handle those details.
     */
    cmd.opcode = (num_blocks == 1) ? SD_WRITE_SINGLE_BLOCK : SD_WRITE_MULTIPLE_BLOCK;

    cmd.arg = start_block;

    cmd.response_type = (SD_RSP_TYPE_R1 | SD_SPI_RSP_TYPE_R1);
    cmd.retries = CONFIG_SD_DATA_RETRIES;
    cmd.timeout_ms = CONFIG_SD_CMD_TIMEOUT;

    data.block_addr = start_block;
    data.block_size = 512;
    data.blocks = num_blocks;
    data.data = (uint8_t *)wbuf;
    data.timeout_ms = CONFIG_SD_DATA_TIMEOUT;

    // LOG_I("WRITE: Sector = %u, Count = %u", start_block, num_blocks);

    ret = linkedsemi_sdhci_request(host, &cmd, &data);
    if (ret) {
        LOG_I("Write failed: %d", ret);
        return ret;
    }
    /* Verify card is back in transfer state after write */
    ret = sdmmc_wait_ready(host);
    if (ret) {
        LOG_I("Card did not return to ready state");
        return -ETIMEDOUT;
    }
    return 0;
}

int main()
{
    sys_init_none();
    pinmux_init();
    EMMC_INIT();
    LOG_I("init\n");
    uint32_t ret;
    memset(buf1, 1, sizeof(buf1));
    if(sd_idle(&emmc))
    {
        LOG_I("Card error on CMD0");
    }

    if(!mmc_card_init(&emmc))
    {
        LOG_I("mmc_card_init successful\n");
    }

    // mmc_set_rst_n_function_enable(&emmc);
    // mmc_set_bootpartition_enable_boot1(&emmc);
    // mmc_set_bootpartition_enable_boot2(&emmc);
    // mmc_set_partition_access_boot1(&emmc);
    // mmc_set_partition_access_boot2(&emmc);

    // mmc_read_ext_csd(&emmc, card_buffer);

    // mmc_boot_partition_en(&emmc);

    // 从用户区读
    // ret = mmc_read_blocks(&emmc, buf, 0, 2);
    // if(ret)
    // {
    //     LOG_I("Single block card read failed\n");
    // }

    // mmc_boot_partition_en(&emmc);


	// ret = mmc_write_blocks(&emmc, buf1, 0, 1);
    // if(ret)
    // {
    //     LOG_I("Single block card write failed\n");
    // }

    // ret = mmc_read_blocks(&emmc, buf, 0, 2);
    // if(ret)
    // {
    //     LOG_I("Single block card read failed\n");
    // }

    while (1);
}