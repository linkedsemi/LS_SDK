#include "ls_hal_emmc.h"
#include "ls_msp_emmc.h"
#include "field_manipulate.h"
#include "reg_base_addr.h"
#include <stdint.h>
#ifdef QSH
    #include "reg_sysc_sec_cpu.h"
#endif
#ifdef RAPTOR
    #include "reg_pipe_sys.h"
#endif

#include "platform.h"
#include "log.h"
#include <string.h>

HAL_StatusTypeDef HAL_EMMC_Init(uint32_t mapbase)
{
    HAL_LSEMMC_MSP_Init(mapbase);
    sdhci_writeb(mapbase, SDHCI_POWER_ON | SDHCI_POWER_330, SDHCI_POWER_CONTROL);
    sdhci_writew(mapbase, 0x25, SDHCI_CLOCK_CONTROL);
    sdhci_writeb(mapbase, 0x7, SDHCI_TIMEOUT_CONTROL);
    sdhci_writel(mapbase, SDHCI_INT_DATA_MASK | SDHCI_INT_CMD_MASK, SDHCI_INT_ENABLE);
    sdhci_writeb(mapbase, SDHCI_POWER_ON | SDHCI_POWER_330, SDHCI_POWER_CONTROL);
    sdhci_writel(mapbase, SDHCI_INT_CARD_INT, SDHCI_SIGNAL_ENABLE);
#ifdef QSH
    if(READ_REG(SYSC_SEC_CPU->APP_CPU_SRST) > 0)
    {
        while(1);
    }
#endif
    return HAL_OK;
}

HAL_StatusTypeDef HAL_EMMC_DeInit(uint32_t mapbase)
{
    HAL_LSEMMC_MSP_DeInit(mapbase);
    return HAL_OK;
}

static uint32_t sdhci_get_present_status_flag(uint32_t mapbase)
{
    return sdhci_readl(mapbase, SDHCI_PRESENT_STATE);
}

static uint32_t sdhci_get_int_status_flag(uint32_t mapbase)
{
    return sdhci_readl(mapbase, SDHCI_INT_STATUS);
}

static void sdhci_clear_int_status_flag(uint32_t mapbase, uint32_t mask)
{
    sdhci_writel(mapbase, mask, SDHCI_INT_STATUS);
}

uint32_t sdhci_receive_command_response(uint32_t mapbase, struct sdhci_command *command)
{
    if (command->response_type == CARD_RESPONSE_TYPE_R2) {
        /* CRC is stripped so we need to do some shifting. */
        for (uint8_t i = 0; i < 4; i++) {
            command->response[3 - i] = sdhci_readl(mapbase, SDHCI_RESPONSE + (3 - i) * 4) << 8;
            if (i != 3) {
                command->response[3 - i] |= sdhci_readb(mapbase, SDHCI_RESPONSE + (3 - i) * 4 - 1);
            }
        }
    } else {
        command->response[0] = sdhci_readl(mapbase, SDHCI_RESPONSE);
    }
    /* check response error flag */
    if ((command->response_error_flags != 0U)
        && ((command->response_type == CARD_RESPONSE_TYPE_R1)
        || (command->response_type == CARD_RESPONSE_TYPE_R1B)
        || (command->response_type == CARD_RESPONSE_TYPE_R6)
        || (command->response_type == CARD_RESPONSE_TYPE_R5))) {
        if (((command->response_error_flags) & (command->response[0U])) != 0U) {
            return -1;
        }
    }
    return 0;
}

static uint32_t linkedsemi_sdhci_wait_command_done(uint32_t mapbase, struct sdhci_command *command)
{
    while(!(sdhci_get_int_status_flag(mapbase) & SDHCI_INT_RESPONSE));
    sdhci_clear_int_status_flag(mapbase, SDHCI_INT_RESPONSE);
    return sdhci_receive_command_response(mapbase, command);
}

void sdhci_reset(uint32_t mapbase, uint8_t mask)
{
    unsigned long timeout;
    /* Wait max 100 ms */
    timeout = 100;
    sdhci_writeb(mapbase, mask, SDHCI_SOFTWARE_RESET);
    while (sdhci_readb(mapbase, SDHCI_SOFTWARE_RESET) & mask) {
        if (timeout == 0) {
            LOG_I("%s: Reset 0x%x never completed.", __func__, (uint32_t)mask);
            return;
        }
        timeout--;
        DELAY_MS(1);
    }
}

uint32_t sdhci_set_transfer_config(struct sdhci_command *sdhci_command, struct sdhci_data *sdhci_data)
{
    /* Define the flag corresponding to each response type. */
    switch (sdhci_command->response_type) {
    case CARD_RESPONSE_TYPE_NONE:
        break;
    case CARD_RESPONSE_TYPE_R1: /* Response 1 */
    case CARD_RESPONSE_TYPE_R5: /* Response 5 */
    case CARD_RESPONSE_TYPE_R6: /* Response 6 */
    case CARD_RESPONSE_TYPE_R7: /* Response 7 */
        sdhci_command->flags |= (SDHCI_CMD_RESP_SHORT | SDHCI_ENABLE_CMD_CRC_FLAG | SDHCI_ENABLE_CMD_INDEX_CHK_FLAG);
        break;

    case CARD_RESPONSE_TYPE_R1B: /* Response 1 with busy */
    case CARD_RESPONSE_TYPE_R5B: /* Response 5 with busy */
        sdhci_command->flags |= (SDHCI_CMD_RESP_SHORT_BUSY | SDHCI_ENABLE_CMD_CRC_FLAG | SDHCI_ENABLE_CMD_INDEX_CHK_FLAG);
        break;

    case CARD_RESPONSE_TYPE_R2: /* Response 2 */
        sdhci_command->flags |= (SDHCI_CMD_RESP_LONG | SDHCI_ENABLE_CMD_CRC_FLAG);
        break;

    case CARD_RESPONSE_TYPE_R3: /* Response 3 */
    case CARD_RESPONSE_TYPE_R4: /* Response 4 */
        sdhci_command->flags |= (SDHCI_CMD_RESP_SHORT);
        break;

    default:
        break;
    }

    if (sdhci_command->type == CARD_COMMAND_TYPE_ABORT) {
        sdhci_command->flags |= SDHCI_ENABLE_COMMAND_TYPE_ABORT;
    } else if (sdhci_command->type == CARD_COMMAND_TYPE_RESUME) {
        sdhci_command->flags |= SDHCI_ENABLE_COMMAND_TYPE_RESUME;
    } else if (sdhci_command->type == CARD_COMMAND_TYPE_SUSPEND) {
        sdhci_command->flags |= SDHCI_ENABLE_COMMAND_TYPE_SUSPEND;
    } else if (sdhci_command->type == CARD_COMMAND_TYPE_NORMAL) {
        sdhci_command->flags |= SDHCI_ENABLE_COMMAND_TYPE_NORMAL;
    }

    if (sdhci_data) {
        sdhci_command->flags |= SDHCI_ENABLE_CMD_DATA_PRESENT_FLAG;
        sdhci_command->flags2 |= SDHCI_ENABLE_BLOCK_COUNT_FLAG;

        if (sdhci_data->rx_data) {
            sdhci_command->flags2 |= SDHCI_DATA_READ_FLAG;
        }
        if (sdhci_data->block_count > 1U) {
            sdhci_command->flags2 |= (SDHCI_MULTIPLE_BLOCK_FLAG);
            /* auto command 12 */
            if (sdhci_data->enable_auto_command12) {
                /* Enable Auto command 12. */
                sdhci_command->flags2 |= SDHCI_ENABLE_AUTO_COMMAND12_FLAG;
            }
            /* auto command 23 */
            if (sdhci_data->enable_auto_command23) {
                sdhci_command->flags2 |= SDHCI_ENABLE_AUTO_COMMAND23_FLAG;
            }
        }
    }
    return 0;
}

void sdhci_send_command(uint32_t mapbase, struct sdhci_command *command, struct sdhci_data *data)
{
    uint32_t cmd_r, xfer_mode;
    cmd_r = SDHCI_MAKE_CMD(command->index, command->flags);
    if (data != NULL) {
        uint32_t start_addr;
        if (data->rx_data) {
            start_addr = (uint32_t)((uint8_t *)data->rx_data);
            csi_dcache_invalid_range((uint32_t *)start_addr, data->block_size * data->block_count);
        } else {
            start_addr = (uint32_t)((uint8_t *)data->tx_data);
            csi_dcache_clean_range((void *)start_addr, data->block_size * data->block_count);
        }
        command->flags2 |= SDHCI_ENABLE_DMA_FLAG;
        sdhci_writel(mapbase, start_addr, SDHCI_DMA_ADDRESS);

        sdhci_writew(mapbase, SDHCI_MAKE_BLKSZ(SDHCI_DEFAULT_BOUNDARY_ARG, data->block_size), SDHCI_BLOCK_SIZE);
        sdhci_writew(mapbase, data->block_count, SDHCI_BLOCK_COUNT);
    }
    xfer_mode = command->flags2 & 0x1ff;

    sdhci_writew(mapbase, xfer_mode, SDHCI_TRANSFER_MODE);
    sdhci_writel(mapbase, command->argument, SDHCI_ARGUMENT);
    sdhci_writew(mapbase, cmd_r, SDHCI_COMMAND);
}

static int32_t linkedsemi_sdhci_transfer_data_blocking(uint32_t mapbase, struct sdhci_data *data)
{
    while (1) {
        if (sdhci_get_int_status_flag(mapbase) & SDHCI_INT_ERROR) {
            sdhci_clear_int_status_flag(mapbase, SDHCI_INT_ERROR);
            LOG_I("Error detected in status!");
            return -1;
        }
        if (sdhci_get_int_status_flag(mapbase) & SDHCI_INT_DMA_END) {
            sdhci_clear_int_status_flag(mapbase, SDHCI_INT_DMA_END);
            sdhci_writel(mapbase, SDHCI_INT_DMA_END, SDHCI_INT_STATUS);
            sdhci_writel(mapbase, sdhci_readl(mapbase, SDHCI_DMA_ADDRESS), SDHCI_DMA_ADDRESS);
        }
        if (sdhci_get_int_status_flag(mapbase) & SDHCI_INT_DATA_END) {
            sdhci_clear_int_status_flag(mapbase, SDHCI_INT_DATA_END);
            csi_dcache_invalid_range((void *)data->rx_data, data->block_size * data->block_count);
            return 0;
        }
    }
}

static uint32_t linkedsemi_sdhci_transfer_blocking(uint32_t mapbase, struct sdhci_command *command, struct sdhci_data *data)
{
    uint8_t ret = 0;
    /* Wait until command/data bus out of busy status. */
    while (sdhci_get_present_status_flag(mapbase) & SDHCI_COMMAND_INHIBIT_FLAG) {
    }
    while (data && (sdhci_get_present_status_flag(mapbase) & SDHCI_DATA_INHIBIT_FLAG)) {
    }

    sdhci_writel(mapbase, SDHCI_INT_ALL_MASK, SDHCI_INT_STATUS);

    ret = sdhci_set_transfer_config(command, data);
    if (ret != 0) {
        return ret;
    }
    sdhci_writel(mapbase, sdhci_readl(mapbase, SDHCI_SIGNAL_ENABLE) | SDHCI_INT_DATA_MASK | SDHCI_INT_CMD_MASK, SDHCI_SIGNAL_ENABLE);

    sdhci_send_command(mapbase, command, data);
    /* wait command done */
    ret = linkedsemi_sdhci_wait_command_done(mapbase, command);
    /* transfer data */
    if ((data != NULL) && (ret == 0) && (!(sdhci_get_int_status_flag(mapbase) & SDHCI_INT_ERROR))) {
        LOG_I("ret=%d, flag2 = %x\n",ret, sdhci_get_int_status_flag(mapbase));
        ret = linkedsemi_sdhci_transfer_data_blocking(mapbase, data);
    }
    while ((sdhci_get_present_status_flag(mapbase) & SDHCI_COMMAND_INHIBIT_FLAG) && (!(sdhci_get_int_status_flag(mapbase) & SDHCI_INT_ERROR)));
    while ((data && (sdhci_get_present_status_flag(mapbase) & SDHCI_DATA_INHIBIT_FLAG) && (!(sdhci_get_int_status_flag(mapbase) & SDHCI_INT_ERROR))));
    sdhci_writel(mapbase, sdhci_readl(mapbase, SDHCI_SIGNAL_ENABLE) & ~(SDHCI_INT_DATA_MASK | SDHCI_INT_CMD_MASK), SDHCI_SIGNAL_ENABLE);
    sdhci_writel(mapbase, SDHCI_INT_ALL_MASK, SDHCI_INT_STATUS);
    sdhci_reset(mapbase, SDHCI_RESET_CMD);
    sdhci_reset(mapbase, SDHCI_RESET_DATA);
    return ret;
}

uint32_t sdhci_card_busy(uint32_t mapbase)
{
    return (!(sdhci_get_present_status_flag(mapbase) & SDHCI_DATA0_LINE_LEVEL_FLAG));
}

uint32_t linkedsemi_sdhci_request(uint32_t mapbase, struct sdhc_command *cmd, struct sdhc_data *data)
{
    uint32_t ret;
    uint32_t busy_timeout = LINKEDSEMI_SDHCI_DEFAULT_TIMEOUT;
    struct sdhci_data sdhci_data = { 0 };
    struct sdhci_command sdhci_command = { 0 };
    struct sdhci_data *sdhci_data_ptr = &sdhci_data;

    sdhci_command.index = cmd->opcode;
    sdhci_command.argument = cmd->arg;

    /* Mask out part of response type field used for SPI commands */
    sdhci_command.response_type = (cmd->response_type & SDHC_NATIVE_RESPONSE_MASK);
    if (cmd->opcode == SD_STOP_TRANSMISSION) {
        sdhci_command.type = CARD_COMMAND_TYPE_ABORT;
    } else {
        sdhci_command.type = CARD_COMMAND_TYPE_NORMAL;
    }

    if (data) {
        sdhci_data.block_size = data->block_size;
        sdhci_data.block_count = data->blocks;

        switch (cmd->opcode) {
        case SD_WRITE_SINGLE_BLOCK:
        case SD_WRITE_MULTIPLE_BLOCK:
            sdhci_data.enable_auto_command12 = true;
            sdhci_data.tx_data = data->data;
            break;
        case MMC_SEND_BUS_TEST:
            sdhci_data.tx_data = data->data;
            break;
        case SD_READ_SINGLE_BLOCK:
        case SD_READ_MULTIPLE_BLOCK:
            sdhci_data.enable_auto_command12 = true;
            sdhci_data.rx_data = data->data;
            break;
        case SD_APP_SEND_SCR:
        case SD_SWITCH:
        case SD_APP_SEND_NUM_WRITTEN_BLK:
        case MMC_CHECK_BUS_TEST:
        case MMC_SEND_EXT_CSD:
        case MMC_SEND_TUNING_BLOCK:
            sdhci_data.rx_data = data->data;
            break;
        default:
            LOG_I("invalid opcode: %#x", cmd->opcode);
            return -ENOTSUP;
        }
        sdhci_data.timeout_ms = data->timeout_ms;
        sdhci_data_ptr = &sdhci_data;
    } else {
        sdhci_data_ptr = NULL;
    }
    sdhci_command.timeout_ms = cmd->timeout_ms;

    do {
        LOG_I("cmd->retries = %d \n", cmd->retries);
        ret = linkedsemi_sdhci_transfer_blocking(mapbase, &sdhci_command, sdhci_data_ptr);

        if (data && ret) {
            /* Send CMD12 to stop transmission after error */
            while (busy_timeout > 0) {
                if (!sdhci_card_busy(mapbase)) {
                    break;
                }
                /* Wait 125us before polling again */
                DELAY_US(125);
                busy_timeout -= 125;
            }
            if (busy_timeout <= 0) {
                LOG_I("Card did not idle after CMD12");
                return -ETIMEDOUT;
            }
        } else {
            cmd->response[0] = sdhci_command.response[0];
            cmd->response[1] = sdhci_command.response[1];
            cmd->response[2] = sdhci_command.response[2];
            cmd->response[3] = sdhci_command.response[3];
        }
    } while (ret != 0 && (cmd->retries-- > 0));

    return 0;
}

static uint32_t mmc_send_op_cond(uint32_t mapbase, uint32_t ocr)
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
        ret = linkedsemi_sdhci_request(mapbase, &cmd, NULL);
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

uint32_t sd_idle(uint32_t mapbase)
{
    struct sdhc_command cmd;

    /* Reset card with CMD0 */
    cmd.opcode = SD_GO_IDLE_STATE;
    cmd.arg = 0x0;
    cmd.response_type = (SD_RSP_TYPE_NONE | SD_SPI_RSP_TYPE_R1);
    cmd.retries = CONFIG_SD_CMD_RETRIES;
    cmd.timeout_ms = CONFIG_SD_CMD_TIMEOUT;
    return linkedsemi_sdhci_request(mapbase, &cmd, NULL);
}

static uint32_t sdmmc_read_cxd(uint32_t mapbase, uint32_t opcode, uint32_t rca, uint32_t *cxd)
{
    struct sdhc_command cmd;
    uint32_t ret;

    cmd.opcode = opcode;
    cmd.arg = (rca << 16);
    cmd.response_type = SD_RSP_TYPE_R2;
    cmd.retries = CONFIG_SD_CMD_RETRIES;
    cmd.timeout_ms = CONFIG_SD_CMD_TIMEOUT;

    ret = linkedsemi_sdhci_request(mapbase, &cmd, NULL);
    if (ret) {
        LOG_I("CMD%d failed: %d", opcode, ret);
        return ret;
    }
    /* CSD/CID is 16 bytes */
    memcpy(cxd, cmd.response, 16);
    return 0;
}

/* Reads card identification register, and decodes it */
uint32_t card_read_cid(uint32_t mapbase)
{
    uint32_t cid[4];
    uint32_t ret;
    ret = sdmmc_read_cxd(mapbase, SD_ALL_SEND_CID, 0, cid);
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

static uint32_t mmc_set_rca(uint32_t mapbase)
{
    struct sdhc_command cmd = {0};
    uint32_t ret;

    cmd.opcode = MMC_SEND_RELATIVE_ADDR;
    cmd.arg = MMC_RCA_ARG;
    cmd.response_type = SD_RSP_TYPE_R1;
    cmd.timeout_ms = CONFIG_SD_CMD_TIMEOUT;

    ret = linkedsemi_sdhci_request(mapbase, &cmd, NULL);
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

static uint32_t mmc_read_csd(uint32_t mapbase)
{
    uint32_t ret;
    struct sdhc_command cmd = {0};

    cmd.opcode = SD_SEND_CSD;
    cmd.arg = MMC_REL_ADR_ARG;
    cmd.response_type = SD_RSP_TYPE_R2;
    cmd.timeout_ms = CONFIG_SD_CMD_TIMEOUT;

    ret = linkedsemi_sdhci_request(mapbase, &cmd, NULL);
    if (ret) {
        LOG_I("CMD9 failed: %d", ret);
        return ret;
    }

    return 0;
}

uint32_t sdmmc_select_card(uint32_t mapbase)
{
    struct sdhc_command cmd;
    uint32_t ret;

    cmd.opcode = SD_SELECT_CARD;
    cmd.arg = (CONFIG_MMC_RCA << 16U);
    cmd.response_type = SD_RSP_TYPE_R1;
    cmd.retries = CONFIG_SD_CMD_RETRIES;
    cmd.timeout_ms = CONFIG_SD_CMD_TIMEOUT;

    ret = linkedsemi_sdhci_request(mapbase, &cmd, NULL);
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

static inline uint32_t sd_retry(uint32_t(*cmd)(uint32_t mapbase),
    uint32_t mapbase,
    uint32_t retries)
{
    uint32_t ret = -ETIMEDOUT;

    while (retries-- >= 0) {
        /* Try cmd */
        ret = cmd(mapbase);
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

uint32_t sdmmc_read_status(uint32_t mapbase)
{
    struct sdhc_command cmd;
    uint32_t ret;

    cmd.opcode = SD_SEND_STATUS;
    cmd.arg = 0;
    cmd.arg = CONFIG_MMC_RCA << 16U;
    cmd.response_type = (SD_RSP_TYPE_R1 | SD_SPI_RSP_TYPE_R2);
    cmd.retries = CONFIG_SD_CMD_RETRIES;
    cmd.timeout_ms = CONFIG_SD_CMD_TIMEOUT;

    ret = linkedsemi_sdhci_request(mapbase, &cmd, NULL);
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

uint32_t sdmmc_wait_ready(uint32_t mapbase)
{
    uint32_t ret, timeout = CONFIG_SD_DATA_TIMEOUT * 1000;

    do {
        if (!sdhci_card_busy(mapbase)) {
            /* Check card status */
            ret = sd_retry(sdmmc_read_status, mapbase, CONFIG_SD_RETRY_COUNT);
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

uint32_t mmc_card_init(uint32_t mapbase)
{
    uint32_t ret = 0;
    uint32_t ocr_arg = 0U;

    /* Probe to see if card is an MMC card */
    ret = mmc_send_op_cond(mapbase, ocr_arg);
    if (ret) {
        return ret;
    }

    /* Modern SDHC always at least supports 512 byte block sizes,
     * which is enough to support sectors
     */
    ocr_arg |= MMC_OCR_SECTOR_MODE | MMC_OCR_PWR_BUSY_FLAG | MMC_OCR_VDD27_36FLAG;

    /* CMD1 */
    ret = mmc_send_op_cond(mapbase, ocr_arg);
    if (ret) {
        LOG_I("Failed to query card OCR");
        return ret;
    }

    /* CMD2 */
    ret = card_read_cid(mapbase);
    if (ret) {
        return ret;
    }

    /* CMD3 */
    ret = mmc_set_rca(mapbase);
    if (ret) {
        LOG_I("Failed on sending RCA to card");
        return ret;
    }
#ifdef RAPTOR
    PIPE_SYS_CFG -> EMMC_CCLK_TX_CLK_CLK_DIV0_DIV10_REG = 0x0; //切到25M
#endif
    /* CMD9 */
    ret = mmc_read_csd(mapbase);
    if (ret) {
        return ret;
    }

    /* CMD7 */
    ret = sdmmc_select_card(mapbase);
    if (ret) {
        return ret;
    }

    return 0;
}

uint32_t mmc_read_blocks(uint32_t mapbase, uint8_t *rbuf, uint32_t start_block, uint32_t num_blocks)
{
    uint32_t ret;
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

    ret = linkedsemi_sdhci_request(mapbase, &cmd, &data);
    if (ret) {
        LOG_I("Failed to read from SDMMC %d", ret);
        return ret;
    }

    /* Verify card is back in transfer state after read */
    ret = sdmmc_wait_ready(mapbase);
    if (ret) {
        LOG_I("Card did not return to ready state");
        return -ETIMEDOUT;
    }
    return 0;
}

static inline uint32_t mmc_send_cmd0_0xf0f0f0f0(uint32_t mapbase)
{
    struct sdhc_command cmd;

    /* Reset card with CMD0 */
    cmd.opcode = SD_GO_IDLE_STATE;
    cmd.arg = 0xF0F0F0F0;
    cmd.response_type = (SD_RSP_TYPE_NONE | SD_SPI_RSP_TYPE_R1);
    cmd.retries = CONFIG_SD_CMD_RETRIES;
    cmd.timeout_ms = CONFIG_SD_CMD_TIMEOUT;
    return linkedsemi_sdhci_request(mapbase, &cmd, NULL);
}

static inline uint32_t mmc_send_cmd0_0xfffffffa(uint32_t mapbase)
{
    struct sdhc_command cmd;

    /* Reset card with CMD0 */
    cmd.opcode = SD_GO_IDLE_STATE;
    cmd.arg = 0xFFFFFFFA;
    cmd.response_type = (SD_RSP_TYPE_NONE | SD_SPI_RSP_TYPE_R1);
    cmd.retries = CONFIG_SD_CMD_RETRIES;
    cmd.timeout_ms = CONFIG_SD_CMD_TIMEOUT;
    return linkedsemi_sdhci_request(mapbase, &cmd, NULL);
}

uint32_t mmc_read_ext_csd(uint32_t mapbase, uint8_t *rbuf)
{
    uint32_t ret;
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

    ret = linkedsemi_sdhci_request(mapbase, &cmd, &data);
    if (ret) {
        LOG_I("CMD8 (send_ext_csd) failed: %d", ret);
        return ret;
    }

    // LOG_I("Card block count is %d, block size is %d", card->block_count, card->block_size);

    return 0;
}

uint32_t mmc_set_rst_n_function_enable(uint32_t mapbase)
{
    uint32_t ret;
    struct sdhc_command cmd = {0};
    cmd.arg = 0x3a20100; //0x1: RST_n signal is permanently enabled

    /* Set Card Bus Width */
    cmd.opcode = SD_SWITCH;
    cmd.response_type = SD_RSP_TYPE_R1b;
    cmd.timeout_ms = CONFIG_SD_CMD_TIMEOUT;
    ret = linkedsemi_sdhci_request(mapbase, &cmd, NULL);
    sdmmc_wait_ready(mapbase);
    if (ret) {
        LOG_I("Setting card data bus width failed: %d", ret);
        return ret;
    }
    return ret;
}

uint32_t mmc_set_bootpartition_enable_boot1(uint32_t mapbase)
{
    uint32_t ret;
    struct sdhc_command cmd = {0};
    cmd.arg = 0x3b30800; //bootpartition_en

    // cmd.arg = 0x3b37800; //regular
    /* Set Card Bus Width */
    cmd.opcode = SD_SWITCH;
    cmd.response_type = SD_RSP_TYPE_R1b;
    cmd.timeout_ms = CONFIG_SD_CMD_TIMEOUT;
    ret = linkedsemi_sdhci_request(mapbase, &cmd, NULL);
    sdmmc_wait_ready(mapbase);
    if (ret) {
        LOG_I("Setting card data bus width failed: %d", ret);
        return ret;
    }
    return ret;
}

uint32_t mmc_set_bootpartition_enable_boot2(uint32_t mapbase)
{
    uint32_t ret;
    struct sdhc_command cmd = {0};
    cmd.arg = 0x3b35000; //bootpartition_en
    // cmd.arg = 0x3b37800; //regular

    /* Set Card Bus Width */
    cmd.opcode = SD_SWITCH;
    cmd.response_type = SD_RSP_TYPE_R1b;
    cmd.timeout_ms = CONFIG_SD_CMD_TIMEOUT;
    ret = linkedsemi_sdhci_request(mapbase, &cmd, NULL);
    sdmmc_wait_ready(mapbase);
    if (ret) {
        LOG_I("Setting card data bus width failed: %d", ret);
        return ret;
    }
    return ret;
}

uint32_t mmc_set_partition_access_boot1(uint32_t mapbase)
{
    uint32_t ret;
    struct sdhc_command cmd = {0};
    cmd.arg = 0x3b34100;

    /* Set Card Bus Width */
    cmd.opcode = SD_SWITCH;
    cmd.response_type = SD_RSP_TYPE_R1b;
    cmd.timeout_ms = CONFIG_SD_CMD_TIMEOUT;
    ret = linkedsemi_sdhci_request(mapbase, &cmd, NULL);
    sdmmc_wait_ready(mapbase);
    if (ret) {
        LOG_I("Setting card data bus width failed: %d", ret);
        return ret;
    }
    return ret;
}

uint32_t mmc_set_partition_access_boot2(uint32_t mapbase)
{
    uint32_t ret;
    struct sdhc_command cmd = {0};
    cmd.arg = 0x3b34200;

    /* Set Card Bus Width */
    cmd.opcode = SD_SWITCH;
    cmd.response_type = SD_RSP_TYPE_R1b;
    cmd.timeout_ms = CONFIG_SD_CMD_TIMEOUT;
    ret = linkedsemi_sdhci_request(mapbase, &cmd, NULL);
    sdmmc_wait_ready(mapbase);
    if (ret) {
        LOG_I("Setting card data bus width failed: %d", ret);
        return ret;
    }
    return ret;
}

void mmc_boot_partition_en(uint32_t mapbase)
{
    mmc_send_cmd0_0xf0f0f0f0(mapbase);
    mmc_send_cmd0_0xfffffffa(mapbase);
}

uint32_t mmc_write_blocks(uint32_t mapbase, const uint8_t *wbuf, uint32_t start_block,
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

    ret = linkedsemi_sdhci_request(mapbase, &cmd, &data);
    if (ret) {
        LOG_I("Write failed: %d", ret);
        return ret;
    }
    /* Verify card is back in transfer state after write */
    ret = sdmmc_wait_ready(mapbase);
    if (ret) {
        LOG_I("Card did not return to ready state");
        return -ETIMEDOUT;
    }
    return 0;
}