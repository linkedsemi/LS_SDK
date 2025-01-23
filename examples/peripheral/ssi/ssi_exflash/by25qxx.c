
#include "platform.h"
#include "exflash_ssi.h"
#include "by25qxx.h"

static void write_enable(void)
{
    EX_FLASH_CS_LOW();
    exflash_ssi_std_write_byte(CMD_WRITE_ENABLE);
    EX_FLASH_CS_HIGH();
}

// 1 busy; 0 not busy
uint8_t nor_wait_busy(uint32_t wait_us)
{
    uint8_t data;
    uint8_t status;
    uint8_t waiting_forever;

    waiting_forever = (wait_us == WAITING_FOREVER) ? 1 : 0;
    EX_FLASH_CS_LOW();
    do
    {
        exflash_ssi_std_write_byte(CMD_READ_STATUS_R0);
        exflash_ssi_std_read_data(&data, 1);
        status = ((data & NOR_STATU_BUSY) == 0x00) ? 0 : 1;
        if (status == 0)
        {
            break;
        }
        if (!waiting_forever)
        {
            if (wait_us == 0)
            {
                break;
            }
            wait_us--;
            DELAY_US(wait_us);
        }
    } while (1);
    EX_FLASH_CS_HIGH();
    return status;
}

static void fill_address(uint8_t *cmd_buf, uint8_t flash_cmd, uint32_t address)
{
    cmd_buf[0] = flash_cmd;
    cmd_buf[1] = (uint8_t)(address >> 16);
    cmd_buf[2] = (uint8_t)(address >> 8);
    cmd_buf[3] = (uint8_t)(address);
    cmd_buf[4] = 0x00;
}

uint32_t nor_read_jedec_id(uint8_t *id)
{
    uint32_t read_id;
    uint8_t jedec_id[3] = {0, 0, 0};

    EX_FLASH_CS_LOW();
    exflash_ssi_std_write_byte(CMD_RDID);
    exflash_ssi_std_read_data(jedec_id, 3);
    EX_FLASH_CS_HIGH();

    if (id != NULL)
    {
        id[0] = jedec_id[0];
        id[1] = jedec_id[1];
        id[2] = jedec_id[2];
    }
    read_id = (jedec_id[0] << 16) | (jedec_id[1] << 8) | jedec_id[2];

    return read_id;
}

void nor_sector_erase(uint32_t Sector_addr)
{
    uint8_t sector_command[8];

    fill_address(sector_command, CMD_SECTOR_ERASE, Sector_addr);

    write_enable();
    // wait_busy();
    EX_FLASH_CS_LOW();
    exflash_ssi_std_write_data(sector_command, 4);
    EX_FLASH_CS_HIGH();
    // wait_busy();
}

void nor_chip_erase(void)
{
    write_enable();
    // wait_busy();
    EX_FLASH_CS_LOW();
    exflash_ssi_std_write_byte(CMD_CHIP_ERASE);
    EX_FLASH_CS_HIGH();
    // wait_busy();
}

void nor_write_page(uint32_t address, uint8_t *data, uint16_t data_len)
{
    // if ((address % 256) == 0 && (data_len <= 256))
    // {
    // return;
    // }
#if SSI_SPI_MODE == STD_SPI_MODE
    uint8_t write_command[8];

    fill_address(write_command, CMD_PAGE_PROGRAM, address);

    write_enable();
    EX_FLASH_CS_LOW();
    exflash_ssi_std_write_data(write_command, 4);
    exflash_ssi_std_write_data(data, data_len);
    EX_FLASH_CS_HIGH();
#else

    write_enable();
    EX_FLASH_CS_LOW();
    exflash_ssi_quad_write_data(data, data_len, address);
    EX_FLASH_CS_HIGH();
#endif
}

void nor_read_data(uint32_t address, uint8_t *data, uint32_t read_len)
{
#if SSI_SPI_MODE == STD_SPI_MODE
    uint8_t read_command[8];

    fill_address(read_command, CMD_READ_DATA, address);

    EX_FLASH_CS_LOW();
    exflash_ssi_std_write_data(read_command, 4);
    exflash_ssi_std_read_data(data, read_len);
    EX_FLASH_CS_HIGH();
#elif SSI_SPI_MODE == DUAL_SPI_MODE
    EX_FLASH_CS_LOW();
    exflash_ssi_dual_read_data(data, read_len, address);
    EX_FLASH_CS_HIGH();
#else
    EX_FLASH_CS_LOW();
    exflash_ssi_quad_read_data(data, read_len, address);
    EX_FLASH_CS_HIGH();
#endif
}
