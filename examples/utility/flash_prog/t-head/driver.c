/**
 * Driver for flash program.
 */
#include "common.h"
#include "ls_hal_flash.h"
#include "ls_hal_cache.h"
#include "reg_base_addr.h"
#include "platform.h"
#include "ls_soc_gpio.h"
#include "cpu.h"
#include "ls_hal_cache.h"
#include "FlashOS.h"
#if !defined(NDEBUG)
#include "log.h"
#endif
#if defined(QSH)
#include "ls_msp_qspiv2.h"
#include "reg_sysc_sec_awo.h"
#endif
/**
 * ERROR TYPE. MUST NOT BE MODIFIED
 */
#define ERROR_INIT      -200
#define ERROR_READID    -201
#define ERROR_PROGRAM   -202
#define ERROR_READ      -203
#define ERROR_ERASE     -204
#define ERROR_CHIPERASE -205
#define ERROR_UNINIT	-206
#define ERROR_CHECKSUM  -207

extern int g_rwBuffer[G_RWBUFFER_SIZE];

#if defined(LEO)
static void io_pull_up_cfg()
{
    io_pull_write(PD04, IO_PULL_UP);
    io_pull_write(PC13, IO_PULL_UP);
}
#endif

/**
 * Customize this method to perform any initialization
 * needed to access your flash device.
 *
 * @return: if this method returns an error,MUST RUTURN ERROR_INIT,
 * Otherwise return 0.
 */
int  flashInit(){
    disable_global_irq();
#if defined(QSH)
    app_cpu_reset();
#endif

#if !defined(NDEBUG)
    log_en = true;
    LOG_INIT();
#endif

    lscache_cache_disable();
#if defined(LEO)
    io_pull_up_cfg();
#endif

    struct hal_flash_env *flash[] = {
        &flash1,
#if defined(LSQSPIV2_2_ENABLED)
        &flash2,
#endif
    };

    flash1.reg = (void *)LSQSPIV2;
#if defined(LSQSPIV2_2_ENABLED)
    flash2.reg = (void *)LSQSPIV2_2;
#endif

    for (int i = 0; i < sizeof(flash) / sizeof(flash[0]); i++) {
        flash[i]->dual_mode_only = false;
        flash[i]->continuous_mode_enable = false;
        flash[i]->writing = false;
        flash[i]->suspend_count = 0;
        flash[i]->continuous_mode_on = false;
        flash[i]->addr4b = false;

#if defined(LEO)
        pinmux_hal_flash_init();
#else
        pinmux_hal_flashx_quad_init(flash[i]->reg);
#endif
        hal_flashx_init(flash[i]);
        clk_flashx_init(flash[i]->reg);

        hal_flashx_software_reset(flash[i]);
        DELAY_US(500);
        hal_flashx_release_from_deep_power_down(flash[i]);
        DELAY_US(100);

        hal_flashx_qe_status_read_and_set(flash[i]);

        uint8_t jedec_id[3] = {};
        uint32_t size;
        hal_flashx_read_id(flash[i], jedec_id);
        if ((jedec_id[0] != 0) && (jedec_id[1] != 0) && (jedec_id[2] != 0)) {
            size = (2 << (jedec_id[2] - 1));
            if (size > (16 << 20)) {
                flash1.addr4b = true;
            }
        } else {
            return ERROR_INIT;
        }
#if !defined(NDEBUG)
        LOG_RAW("0x%x: jedec-id=[%02x %02x %02x]: size=%d\r\n", (uint32_t)flash[i]->reg, jedec_id[0], jedec_id[1], jedec_id[2], size);
#endif

        uint8_t status_reg_0;
        uint8_t status_reg_1;
        hal_flashx_read_status_register_0(flash[i], &status_reg_0);
        hal_flashx_read_status_register_1(flash[i], &status_reg_1);
#if !defined(NDEBUG)
        LOG_RAW("status_reg_1: %02x, status_reg_0: %02x\r\n", status_reg_1, status_reg_0);
#endif
        if ((status_reg_1 & (~0xbf)) || (status_reg_0 & (~0x83))) {
            LOG_RAW("unlock flash\r\n");
            hal_flashx_write_status_register(flash[i], ((status_reg_1 & 0xbf) << 8) | (status_reg_0 & 0x83));
            hal_flashx_read_status_register_0(flash[i], &status_reg_0);
            hal_flashx_read_status_register_1(flash[i], &status_reg_1);
            LOG_RAW("status_reg_1: %02x, status_reg_0: %02x\r\n", status_reg_1, status_reg_0);
        }
    }

    return 0;
}

/**
 * Customize this method to perform any un-initialization
 * needed to access your flash device.
 *
 * @return: if this method returns an error,MUST RUTURN ERROR_UNINIT,
 * Otherwise return 0.
 */
int  flashUnInit(){
#if !defined(NDEBUG)
    LOG_RAW("%s\r\n", __func__);
#endif
    return 0;
}

/**
 * Customize this method to read flash ID
 *
 * @param flashID: returns for flash ID
 *
 * @return: if this method returns an error,MUST RUTURN ERROR_READID,
 * Otherwise return 0.
 */
int  flashID(unsigned int* flashID){
#if !defined(NDEBUG)
    LOG_RAW("%s\r\n", __func__);
#endif
    hal_flashx_read_id(&flash1, (uint8_t *)flashID);
    return 0;
}

/**
 * This method takes the data pointed to by the src parameter
 * and writes it to the flash blocks indicated by the
 * dst parameter.
 *
 * @param dst : destination address where flash program
 * @param src : address of data
 * @param length : data length
 *
 * @return : if this method returns an error,MUST RUTURN ERROR_PROGRAM,
 * Otherwise return 0.
 */
int flashProgram(char* dst, char *src, int size){
    uint32_t flash_base_addr;
    struct hal_flash_env *flash;
#if defined(LSQSPIV2_2_ENABLED)
    if ((uintptr_t)dst >= CACHE2_ADDR) {
        flash_base_addr = CACHE2_ADDR;
        flash = &flash2;
    } else {
        flash_base_addr = FLASH_BASE_ADDR;
        flash = &flash1;
    }
#else
    flash_base_addr = FLASH_BASE_ADDR;
    flash = &flash1;
#endif

    uint32_t current = (uint32_t)dst;
    uint8_t *data = (uint8_t *)src;
    uint16_t length;
#if !defined(NDEBUG)
    LOG_RAW("%s: dst:0x%x src:0x%x size:0x%x\r\n", __func__, dst, src, size);
#endif

    if(current % 256)
    {
        length = size > 256 - current % 256 ? 256 - current % 256 : size;
    }else
    {
        length = 0;
    }
    if(length)
    {
#if 0
#if !defined(NDEBUG)
        LOG_RAW("%s: dst:0x%x size:0x%x\r\n", __func__, current - flash_base_addr, length);
#endif
#endif
        hal_flashx_multi_io_page_program(flash, current - flash_base_addr,(void *)data,length);
        size -= length;
        current += length;
        data = (uint8_t *)data + length; 
    }
    while(size)
    {
        length = size > 256 ? 256 : size;
#if 0
#if !defined(NDEBUG)
        LOG_RAW("%s: dst:0x%x size:0x%x\r\n", __func__, current - flash_base_addr, length);
#endif
#endif
        hal_flashx_multi_io_page_program(flash, current - flash_base_addr,(void *)data,length);
        size -= length;
        current += length;
        data = (uint8_t *)data + length; 
    }
    return 0;
}

/**
 * Customize this method to read data from a group of flash blocks into a buffer
 *
 * @param dst : reads the contents of those flash blocks into the address pointed to by
 * the dst parameter.
 * @param src : a pointer to a single flash.
 * @param length : data length
 *
 *  @return: if this method returns an error,MUST RUTURN ERROR_READ,
 * Otherwise return 0.
 */
int flashRead(char* dst, char *src, int length){
    uint32_t flash_base_addr;
    struct hal_flash_env *flash;
#if defined(LSQSPIV2_2_ENABLED)
    if ((uintptr_t)src >= CACHE2_ADDR) {
        flash_base_addr = CACHE2_ADDR;
        flash = &flash2;
    } else {
        flash_base_addr = FLASH_BASE_ADDR;
        flash = &flash1;
    }
#else
    flash_base_addr = FLASH_BASE_ADDR;
    flash = &flash1;
#endif

#if !defined(NDEBUG)
    LOG_RAW("%s: dst:0x%x src:0x%x size:0x%x\r\n", __func__, dst, src, length);
#endif
    hal_flashx_multi_io_read(flash, (uint32_t)src - flash_base_addr,(uint8_t *)dst,length);
    return 0;
}

/**
 * Customize this method to erase a group of flash blocks.
 *
 * @param dst : a pointer to the base of the flash device.
 * NOTE: dst will always be sector aligned, the sector size is stored in FlashDev.c#FlashDevices#Devs#PageSize
 * @param length : erase length
 * NOTE: length will always be sector aligned, the sector size is stored in FlashDev.c#FlashDevices#Devs#PageSize
 *
 * @return : if this method returns an error,MUST RUTURN ERROR_ERASE,
 * Otherwise return 0
 */
int flashErase(char *dst, int size){
    uint32_t flash_base_addr;
    struct hal_flash_env *flash;
#if defined(LSQSPIV2_2_ENABLED)
    if ((uintptr_t)dst >= CACHE2_ADDR) {
        flash_base_addr = CACHE2_ADDR;
        flash = &flash2;
    } else {
        flash_base_addr = FLASH_BASE_ADDR;
        flash = &flash1;
    }
#else
    flash_base_addr = FLASH_BASE_ADDR;
    flash = &flash1;
#endif

#if !defined(NDEBUG)
    LOG_RAW("%s: data:0x%x size:0x%x\r\n", __func__, dst, size);
#endif
    uint32_t offset = (uint32_t)dst - flash_base_addr;
    for (uint32_t addr = offset; addr < (offset + size);) {
#if 0
#if !defined(NDEBUG)
        LOG_RAW("%s: offset:0x%x\r\n", __func__, offset);
#endif
#endif
        if (((addr % KB(64)) == 0) && ((offset + size - addr) >= KB(64))) {
            hal_flashx_block_64K_erase(flash, addr);
            addr += KB(64);
        } else if (((addr % KB(32)) == 0) && ((offset + size - addr) >= KB(32))) {
            hal_flashx_block_32K_erase(flash, addr);
            addr += KB(32);
        } else if ((offset + size - addr) >= KB(4)) {
            hal_flashx_sector_erase(flash, addr);
            addr += KB(4);
        }
    }

    return 0;
}

/**
 * Customize this method to erase the whole flash.
 *
 * @return : if this method returns an error,MUST RUTURN ERROR_CHIPERASE,
 * Otherwise return 0.
 */
int flashChipErase( ){
#if !defined(NDEBUG)
    LOG_RAW("%s\r\n", __func__);
#endif
    hal_flashx_chip_erase(&flash1);
    hal_flashx_chip_erase(&flash2);
    return 0;
}

/**
 * Customize this method to make the veryfiy process more quickly.
 * 
 * @param dst : a pointer to the base of the flash device.
 * NOTE: dst will always be 4 aligned.
 * @param length : the lenght of the data which will be used for checksum
 * NOTE: the length will always be 4 aligned.
 * @param checksum : the expected checksum value in the programmed file(ihex,bin,elf format)
 * 
 * @return : if the specified data's checksum from dst and lenght is checksum, return 0, else return ERROR_CHECKSUM
 * @example if the flash can be read directly, you can copy following code to replace current "return 0;"
 *
  int i, sum = 0;
  for (i = 0; i < length; i++) {
   sum += dst[i];
  }
  return sum == checksum ? 0 : ERROR_CHECKSUM;
 * 
 */
int flashChecksum(char*dst, int length, int checksum) {
    int sum = 0;
    int remain = length % sizeof(g_rwBuffer);
    int current = 0;
    char *p_buf = (char *)g_rwBuffer;

    for(int i = 0; i < length / sizeof(g_rwBuffer); i++) {
#if !defined(NDEBUG)
        LOG_RAW("%s pos:0x%x size:0x%x\r\n", __func__, dst + current, sizeof(g_rwBuffer));
#endif
        flashRead(p_buf, dst + current, sizeof(g_rwBuffer));
        for (int i = 0; i < sizeof(g_rwBuffer); i++) {
            sum += p_buf[i];
        }
        current += sizeof(g_rwBuffer);
    }
    if (remain) {
#if !defined(NDEBUG)
        LOG_RAW("%s pos:0x%x size:0x%x\r\n", __func__, dst + current, remain);
#endif
        flashRead(p_buf, dst + current, remain);
        for (int i = 0; i < remain; i++) {
            sum += p_buf[i];
        }
    }

#if !defined(NDEBUG)
    LOG_RAW("%s sum:0x%x " "%s" " checksum:0x%x\r\n", __func__, sum, sum == checksum ? "==" : "!=", checksum);
#endif
    return sum == checksum ? 0 : ERROR_CHECKSUM;
}

void SystemInit(){}

// NOTING: when debug the driver, this macro defined as 1, and then
// it must be set as 0, for release to flash programmer library
#define DEBUG_DRIVER	0

/**
 * Debug entry for driver.
 *
 * @return : if this method returns an error,MUST RUTURN ERROR_CHIPERASE,
 * Otherwise return 0.
 */
#if DEBUG_DRIVER
#include <string.h>
#include <stdlib.h>
uint32_t rand_buf[64];
uint32_t result[64];
int sum2,sum;
int flashTest(){
    char *dst = (char *)0x858000;
    int length = 0x225fc;
    int i;
    sum = 0;
    spi_flash_xip_start();
    for (i = 0; i < length; i++) {
        sum += dst[i];
    }
    spi_flash_xip_stop();
    char data;
    sum2 = 0;
    for (i = 0; i < length; i++){
        spi_flash_quad_io_read(i+0x58000,&data,1);
        sum2 += data;
    }
    return sum;
/*
    while(1)
    {
        spi_flash_chip_erase();
        uint32_t offset;
        for(offset = 0;offset<0x80000;offset += 0x100)
        {
            uint8_t i;
            for(i = 0;i<64;++i)
            {
                rand_buf[i] = rand();
            }
            spi_flash_page_program(offset,(void *)rand_buf,sizeof(rand_buf));
            spi_flash_xip_start();
            for(i=0;i<64;++i)
            {
                uint32_t *val = (uint32_t *)(0x800000 + offset + 4*i);
                if(*val!=rand_buf[i])
                {
                    io_set_pin(PA00);
                    spi_flash_quad_io_read(offset,(void *)result,sizeof(result));
                    __asm("ebreak"::);
                    while(1);
                }
            }
            spi_flash_xip_stop();
        }
    }
    return 0;
*/
}
#else
int flashTest(){
	return 0;
}
#endif

void __bkpt_label()
{
    __asm("ebreak"::);
}

void __continue_label(){}
