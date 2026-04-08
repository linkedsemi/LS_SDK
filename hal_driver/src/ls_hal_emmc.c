#include "ls_hal_emmc.h"
#include "ls_msp_emmc.h"
#include "field_manipulate.h"
#include "reg_base_addr.h"
#ifdef QSH
    #include "reg_sysc_sec_cpu.h"
#endif
#include "platform.h"
#include "log.h"

//qsh 0x40049000
//raptor 0x92000000

HAL_StatusTypeDef HAL_EMMC_Init(sdhci_host *host)
{
    HAL_LSEMMC_MSP_Init(host);
    sdhci_writeb(host, SDHCI_POWER_ON | SDHCI_POWER_330, SDHCI_POWER_CONTROL);
    sdhci_writew(host, 0x25, SDHCI_CLOCK_CONTROL);
    sdhci_writeb(host, 0x7, SDHCI_TIMEOUT_CONTROL);
    sdhci_writel(host, SDHCI_INT_DATA_MASK | SDHCI_INT_CMD_MASK, SDHCI_INT_ENABLE);
    sdhci_writeb(host, SDHCI_POWER_ON | SDHCI_POWER_330, SDHCI_POWER_CONTROL);
    sdhci_writel(host, SDHCI_INT_CARD_INT, SDHCI_SIGNAL_ENABLE);
#ifdef QSH
    if(READ_REG(SYSC_SEC_CPU->APP_CPU_SRST) > 0)
    {
        while(1);
    }
#endif
    return HAL_OK;
}

HAL_StatusTypeDef HAL_EMMC_DeInit(sdhci_host *host)
{
    HAL_LSEMMC_MSP_DeInit(host);
    return HAL_OK;
}

static uint32_t sdhci_get_present_status_flag(sdhci_host *sdhci_host)
{
    return sdhci_readl(sdhci_host, SDHCI_PRESENT_STATE);
}

static uint32_t sdhci_get_int_status_flag(sdhci_host *sdhci_host)
{
    return sdhci_readl(sdhci_host, SDHCI_INT_STATUS);
}

static void sdhci_clear_int_status_flag(sdhci_host *sdhci_host, uint32_t mask)
{
    sdhci_writel(sdhci_host, mask, SDHCI_INT_STATUS);
}

uint32_t sdhci_receive_command_response(sdhci_host *sdhci_host, struct sdhci_command *command)
{
    if (command->response_type == CARD_RESPONSE_TYPE_R2) {
        /* CRC is stripped so we need to do some shifting. */
        for (uint8_t i = 0; i < 4; i++) {
            command->response[3 - i] = sdhci_readl(sdhci_host, SDHCI_RESPONSE + (3 - i) * 4) << 8;
            if (i != 3) {
                command->response[3 - i] |= sdhci_readb(sdhci_host, SDHCI_RESPONSE + (3 - i) * 4 - 1);
            }
        }
    } else {
        command->response[0] = sdhci_readl(sdhci_host, SDHCI_RESPONSE);
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

static uint32_t linkedsemi_sdhci_wait_command_done(sdhci_host *host, struct sdhci_command *command, bool execute_tuning)
{
    /* tuning cmd do not need to wait command done */
    if (execute_tuning)
        return 0;
    /* Wait command complete or SDHC encounters error. */
    while(!host->transfer_sem);
    // host->transfer_sem = false;
    if (host->error_code & SDHCI_INT_ERROR) {
        if (!host->execute_tuning) {
            LOG_I("%s: Error detected in status(0x%X)!", __func__, host->error_code);
        }
        host->error_code = 0;
        return -1;
    }

    return sdhci_receive_command_response(host, command);
}

void sdhci_reset(sdhci_host *host, uint8_t mask)
{
    unsigned long timeout;
    /* Wait max 100 ms */
    timeout = 100;
    sdhci_writeb(host, mask, SDHCI_SOFTWARE_RESET);
    while (sdhci_readb(host, SDHCI_SOFTWARE_RESET) & mask) {
        if (timeout == 0) {
            LOG_I("%s: Reset 0x%x never completed.", __func__, (int)mask);
            return;
        }
        timeout--;
        DELAY_MS(1);
    }
}

uint32_t sdhci_set_transfer_config(sdhci_host *sdhci_host, struct sdhci_command *sdhci_command, struct sdhci_data *sdhci_data)
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

void sdhci_send_command(sdhci_host *sdhci_host, struct sdhci_command *command, bool use_dma)
{
    uint32_t cmd_r, xfer_mode;
    struct sdhci_data *sdhci_data = sdhci_host->sdhci_data;

    cmd_r = SDHCI_MAKE_CMD(command->index, command->flags);
    if (sdhci_data != NULL) {
        if (use_dma) {
            uint32_t start_addr;
            if (sdhci_data->rx_data) {
                start_addr = (uint32_t)((uint8_t *)sdhci_data->rx_data);
                csi_dcache_invalid_range((uint32_t *)start_addr, sdhci_data->block_size * sdhci_data->block_count);
            } else {
                start_addr = (uint32_t)((uint8_t *)sdhci_data->tx_data);
                csi_dcache_clean_range((void *)start_addr, sdhci_data->block_size * sdhci_data->block_count);
            }
            command->flags2 |= SDHCI_ENABLE_DMA_FLAG;
            sdhci_writel(sdhci_host, start_addr, SDHCI_DMA_ADDRESS);
        }
        sdhci_writew(sdhci_host, SDHCI_MAKE_BLKSZ(SDHCI_DEFAULT_BOUNDARY_ARG, sdhci_data->block_size), SDHCI_BLOCK_SIZE);
        sdhci_writew(sdhci_host, sdhci_data->block_count, SDHCI_BLOCK_COUNT);
    }
    xfer_mode = command->flags2 & 0x1ff;

    sdhci_writew(sdhci_host, xfer_mode, SDHCI_TRANSFER_MODE);
    sdhci_writel(sdhci_host, command->argument, SDHCI_ARGUMENT);
    sdhci_writew(sdhci_host, cmd_r, SDHCI_COMMAND);
}

static int32_t linkedsemi_sdhci_transfer_data_blocking(sdhci_host *host, struct sdhci_data *data, bool use_dma)
{
    if (use_dma) {
        uint32_t stat;

        while (1) {
    
            while(!host->transfer_sem);
            host->transfer_sem = false;
            stat = host->irq_status;
            if (stat & SDHCI_INT_ERROR) {
                if (!host->execute_tuning) {
                    LOG_I("%s: Error detected in status(0x%x)!", __func__, host->error_code);
                }
                return -1;
            }
            if (stat & SDHCI_INT_DMA_END) {
                sdhci_writel(host, SDHCI_INT_DMA_END, SDHCI_INT_STATUS);
                sdhci_writel(host, sdhci_readl(host, SDHCI_DMA_ADDRESS), SDHCI_DMA_ADDRESS);
            }
            if (stat & SDHCI_INT_DATA_END) {
                csi_dcache_invalid_range((void *)data->rx_data, data->block_size * data->block_count);
                return 0;
            }
        }
    } else {
        uint32_t stat, rdy, mask, block;

        block = 0;
        rdy = SDHCI_INT_SPACE_AVAIL | SDHCI_INT_DATA_AVAIL;
        mask = SDHCI_DATA_AVAILABLE | SDHCI_SPACE_AVAILABLE;

        while (1) {
            while(!host->transfer_sem);
            host->transfer_sem = false;
            stat = host->irq_status;
            if (stat & SDHCI_INT_ERROR) {
                if (!host->execute_tuning) {
                    LOG_I("%s: Error detected in status(0x%X)!", __func__, stat);
                }
                return -1;
            }
            if (stat & rdy) {
                if (!(sdhci_readl(host, SDHCI_PRESENT_STATE) & mask)) {
                    continue;
                }
                if (data->rx_data) {
                    uint16_t block_size = data->block_size >> 2;
                    for (uint32_t i = 0; i < block_size; i++) {
                        data->rx_data[i + block * block_size] = sdhci_readl(host, SDHCI_BUFFER);
                    }
                } else {
                    uint16_t block_size = data->block_size >> 2;
                    for (uint32_t i = 0; i < block_size; i++) {
                        sdhci_writel(host, data->tx_data[i + block * block_size], SDHCI_BUFFER);
                    }
                }
                block++;
                if (block >= data->block_count) {
                    return 0;
                }
            }
        }
    }
}

static uint32_t linkedsemi_sdhci_transfer_blocking(sdhci_host *host)
{
    struct sdhci_command *sdhci_command = host->sdhci_command;
    struct sdhci_data *sdhci_data = host->sdhci_data;

    bool use_dma = true;
    uint8_t ret = 0;

    /* Wait until command/data bus out of busy status. */
    while (sdhci_get_present_status_flag(host) & SDHCI_COMMAND_INHIBIT_FLAG) {
    }
    while (sdhci_data && (sdhci_get_present_status_flag(host) & SDHCI_DATA_INHIBIT_FLAG)) {
    }

    sdhci_writel(host, SDHCI_INT_ALL_MASK, SDHCI_INT_STATUS);

    ret = sdhci_set_transfer_config(host, sdhci_command, sdhci_data);
    if (ret != 0) {
        return ret;
    }
    sdhci_writel(host, sdhci_readl(host, SDHCI_SIGNAL_ENABLE) | SDHCI_INT_DATA_MASK | SDHCI_INT_CMD_MASK, SDHCI_SIGNAL_ENABLE);

    host->transfer_status = 0U;
    host->transfer_sem = false;
    sdhci_send_command(host, sdhci_command, use_dma);
    /* wait command done */
    ret = linkedsemi_sdhci_wait_command_done(host, sdhci_command, ((sdhci_data == NULL) ? false : sdhci_data->execute_tuning));
    /* transfer data */
    if ((sdhci_data != NULL) && (ret == 0) && (!(host->irq_status & SDHCI_INT_ERROR))) {
        ret = linkedsemi_sdhci_transfer_data_blocking(host, sdhci_data, use_dma);
    }
    while ((sdhci_get_present_status_flag(host) & SDHCI_COMMAND_INHIBIT_FLAG) && (!(host->irq_status & SDHCI_INT_ERROR)));
    while ((sdhci_data && (sdhci_get_present_status_flag(host) & SDHCI_DATA_INHIBIT_FLAG) && (!(host->irq_status & SDHCI_INT_ERROR))));
    sdhci_writel(host, sdhci_readl(host, SDHCI_SIGNAL_ENABLE) & ~(SDHCI_INT_DATA_MASK | SDHCI_INT_CMD_MASK), SDHCI_SIGNAL_ENABLE);
    sdhci_writel(host, SDHCI_INT_ALL_MASK, SDHCI_INT_STATUS);
    sdhci_reset(host, SDHCI_RESET_CMD);
    sdhci_reset(host, SDHCI_RESET_DATA);
    return ret;
}

uint32_t sdhci_card_busy(sdhci_host *sdhci_host)
{
    return (!(sdhci_get_present_status_flag(sdhci_host) & SDHCI_DATA0_LINE_LEVEL_FLAG));
}

uint32_t linkedsemi_sdhci_request(sdhci_host *host, struct sdhc_command *cmd, struct sdhc_data *data)
{
    uint32_t ret;
    uint32_t busy_timeout = LINKEDSEMI_SDHCI_DEFAULT_TIMEOUT;
    struct sdhci_data sdhci_data = { 0 };
    struct sdhci_command sdhci_command = { 0 };

    host->sdhci_command = &sdhci_command;

    host->irq_status = 0;
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

        host->sdhci_data = &sdhci_data;
        host->sdhci_data->timeout_ms = data->timeout_ms;
    } else {
        host->sdhci_data = NULL;
    }
    host->sdhci_command->timeout_ms = cmd->timeout_ms;

    do {
        // LOG_I("cmd->retries = %d \n", cmd->retries);
        ret = linkedsemi_sdhci_transfer_blocking(host);
        if (data && ret) {
            /* Send CMD12 to stop transmission after error */
            while (busy_timeout > 0) {
                if (!sdhci_card_busy(host)) {
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
            cmd->response[0] = host->sdhci_command->response[0];
            cmd->response[1] = host->sdhci_command->response[1];
            cmd->response[2] = host->sdhci_command->response[2];
            cmd->response[3] = host->sdhci_command->response[3];
        }
    } while (ret != 0 && (cmd->retries-- > 0));

    return 0;
}

void HAL_LSEMMC_IRQHandler(sdhci_host *host)
{
    volatile uint32_t status = sdhci_get_int_status_flag(host);
    sdhci_clear_int_status_flag(host, status);
    if (status & (SDHCI_INT_RESPONSE
                | SDHCI_INT_DATA_END
                | SDHCI_INT_DMA_END
                | SDHCI_INT_SPACE_AVAIL
                | SDHCI_INT_DATA_AVAIL
                | SDHCI_INT_ERROR)) {
        host->error_code = (status >> 16) & 0xffff;
        if (host->error_code) {
            if (!host->execute_tuning) {
                uint32_t cmd_r = sdhci_readw(host, SDHCI_COMMAND);
                LOG_I("error: %x  CMD_R: %x", host->error_code, cmd_r);
            }
        }
        host->irq_status |= status;
        if (status & SDHCI_INT_ERROR) {
            host->transfer_sem = true;
        }
        if (status & SDHCI_INT_RESPONSE) {
            host->transfer_sem = true;
        }
        if (status & (SDHCI_INT_DATA_END
                    | SDHCI_INT_DMA_END
                    | SDHCI_INT_SPACE_AVAIL
                    | SDHCI_INT_DATA_AVAIL)) {
            host->transfer_sem = true;
        }
    }
}