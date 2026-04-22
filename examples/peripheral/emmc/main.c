#include <stdint.h>
#include <string.h>
#include "platform.h"
#include "ls_soc_gpio.h"
#include "ls_hal_emmc.h"
#include "ls_msp_emmc.h"
#include "log.h"
#include "common.h"

#define emmc_buf_addr ((uint8_t *)0xB0000000)
#define SECTOR_COUNT 32
#define SECTOR_SIZE  512 /* subsystem should set all cards to 512 byte blocks */
#define BUF_SIZE     (SECTOR_SIZE * SECTOR_COUNT)
static uint8_t buf[BUF_SIZE] __aligned(CONFIG_SDHC_BUFFER_ALIGNMENT);
static uint8_t buf1[BUF_SIZE] __aligned(CONFIG_SDHC_BUFFER_ALIGNMENT);

int block_addr = 0;

uint8_t card_buffer[MMC_EXT_CSD_BYTES];

uint32_t mapbase;

void EMMC_INIT(void)
{
#ifdef QSH
    mapbase = LSEMMC1;
#elif defined(RAPTOR)
    mapbase = LSEMMC;
#endif
    HAL_EMMC_Init(mapbase);
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

int main()
{
    sys_init_none();
    pinmux_init();
    EMMC_INIT();
    LOG_I("init\n");
    uint32_t ret;
#ifdef QSH
    memset(buf1, 1, sizeof(buf1));
#endif
    if(sd_idle(mapbase))
    {
        LOG_I("Card error on CMD0");
    }

    if(!mmc_card_init(mapbase))
    {
        LOG_I("mmc_card_init successful\n");
    }

    // mmc_set_rst_n_function_enable(mapbase);
    // mmc_set_bootpartition_enable_boot1(mapbase);
    // mmc_set_bootpartition_enable_boot2(mapbase);
    // mmc_set_partition_access_boot1(mapbase);
    // mmc_set_partition_access_boot2(mapbase);

    // mmc_read_ext_csd(mapbase, card_buffer);

    // mmc_boot_partition_en(mapbase);

    // 从用户区读
#ifdef QSH
    ret = mmc_read_blocks(mapbase, buf, 0, 2);
    if(ret)
    {
        LOG_I("Single block card read failed\n");
    }

    // mmc_boot_partition_en(mapbase);


	// ret = mmc_write_blocks(mapbase, buf1, 0, 1);
    // if(ret)
    // {
    //     LOG_I("Single block card write failed\n");
    // }

    // ret = mmc_read_blocks(mapbase, buf, 0, 2);
    // if(ret)
    // {
    //     LOG_I("Single block card read failed\n");
    // }
#elif defined(RAPTOR)
    ret = mmc_read_blocks(mapbase, emmc_buf_addr, 0, 2);
    if(ret)
    {
        LOG_I("Single block card read failed\n");
    }
    memcpy32((uint32_t *)buf, (uint32_t *)emmc_buf_addr, (2*512)/4);

    memset(emmc_buf_addr, 1, sizeof(buf1));

	ret = mmc_write_blocks(mapbase, emmc_buf_addr, 0, 1);
    if(ret)
    {
        LOG_I("Single block card write failed\n");
    }
    memset(emmc_buf_addr, 0, sizeof(buf1));

    ret = mmc_read_blocks(mapbase, emmc_buf_addr, 0, 2);
    if(ret)
    {
        LOG_I("Single block card read failed\n");
    }
    memcpy32((uint32_t *)buf, (uint32_t *)emmc_buf_addr, (2*512)/4);

#endif
    while (1);
}