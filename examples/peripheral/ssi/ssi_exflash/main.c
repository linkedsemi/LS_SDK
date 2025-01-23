
#define LOG_TAG "MAIN"
#include "platform.h"
#include "log.h"
#include "ls_dbg.h"
#include "cpu.h"
#include <string.h>
#include "exflash_ssi.h"
#include "by25qxx.h"

static void wait(uint32_t ms)
{
    while (1)
    {
        if (nor_wait_busy(ms) == 0)
            break;
    }
}

void write_read(void)
{
#define TEST_WRITE_READ_LENGTH 128

    uint8_t write_buffer[TEST_WRITE_READ_LENGTH];
    uint8_t read_buffer[TEST_WRITE_READ_LENGTH];

    // nor_chip_erase();
    // wait(50000);

    nor_sector_erase(0);
    wait(500);

    for (uint32_t i = 0; i < TEST_WRITE_READ_LENGTH; i++)
    {
        // write_buffer[i] = 0xd0 + i;
        write_buffer[i] = i;
        read_buffer[i] = 0;
    }

    nor_write_page(0, write_buffer, TEST_WRITE_READ_LENGTH);
    wait(10);
    nor_read_data(0, read_buffer, TEST_WRITE_READ_LENGTH);

    if (memcmp(write_buffer, read_buffer, TEST_WRITE_READ_LENGTH))
    {
        LOG_HEX(read_buffer, TEST_WRITE_READ_LENGTH);
        LOG_I("The write and read data do not match.");
    }
    else
    {
        LOG_I("Write and read data match.");
    }
}

int main(void)
{
    uint32_t jedec_id = 0;
    sys_init_none();

    LOG_I("SSI EXFLASH start....");

    exflash_ssi_init();

    jedec_id = nor_read_jedec_id(NULL);

    LOG_I("jedec_id = 0x%08x", jedec_id);

#if 0
    uint8_t buffer[TEST_WRITE_READ_LENGTH];
    memset(buffer, 0, TEST_WRITE_READ_LENGTH);
    nor_read_data(0, buffer, TEST_WRITE_READ_LENGTH);
    LOG_HEX(buffer, TEST_WRITE_READ_LENGTH);
#else
    // test: read and write data
     write_read();
#endif

    while (1)
        ;
    return 0;
}
