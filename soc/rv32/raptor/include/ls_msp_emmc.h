#ifndef LS_MSP_EMMC_H_
#define LS_MSP_EMMC_H_
#include "reg_base_addr.h"
#include "reg_emmc_type.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef REG_EMMC0_BASE
#define LSEMMC REG_EMMC0_BASE
#endif

struct sdhc_data {
    unsigned int block_addr; /*!< Block to start read from */
    unsigned int block_size; /*!< Block size */
    unsigned int blocks; /*!< Number of blocks */
    unsigned int bytes_xfered; /*!< populated with number of bytes sent by SDHC */
    void *data; /*!< Data to transfer or receive */
    int timeout_ms; /*!< data timeout in milliseconds */
};

typedef struct sdhci_host {
    uint32_t  mapbase;
    struct sdhci_data *sdhci_data;
    struct sdhci_command *sdhci_command;
    void *usdhc_adma2_table;
    volatile bool transfer_sem;
    uint16_t error_code;
    uint32_t irq_status;
    uint32_t max_clk;
    uint8_t index;
    uint8_t is_emmc_card;
    uint8_t io_fixed_1v8;
    uint8_t power_mode;
    uint8_t have_phy;
    uint8_t mshc_ctrl_r;
    uint32_t rx_delay_line;
    uint32_t tx_delay_line;
    uint32_t transfer_status;
    uint8_t bus_width;
    uint32_t current_speed;
    bool execute_tuning;
}sdhci_host;

void HAL_LSEMMC_MSP_Init(sdhci_host *host);
void HAL_LSEMMC_MSP_DeInit(sdhci_host *host);

#ifdef __cplusplus
}
#endif

#endif