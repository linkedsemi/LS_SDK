#include "reg_base_addr.h"
#include "ls_hal_flash.h"
#include "ls_hal_cache.h"
#include "ls_soc_gpio.h"
#include "platform.h"
#include "cpu.h"

#if defined(LE501X)
#define DUAL_MODE false
#define FLASH_CTRL_REG LSQSPI_BASE_ADDR
static void io_pull_up_cfg() {}
static void clk_flash_init() {}
#elif defined(LM3050) 
#define FLASH_CTRL_REG LSQSPIV2_BASE_ADDR
#define DUAL_MODE true
static void io_pull_up_cfg()
{
    io_pull_write(PD14, IO_PULL_UP);
    io_pull_write(PD15, IO_PULL_UP);
}
__attribute__((long_call)) void pinmux_hal_flash_quad_init(void);
#elif defined(LEO)
#define FLASH_CTRL_REG LSQSPIV2_BASE_ADDR
#define DUAL_MODE false
static void io_pull_up_cfg()
{
    io_pull_write(PD04, IO_PULL_UP);
    io_pull_write(PC13, IO_PULL_UP);
}
#endif

static void flash_init(void)
{
    disable_global_irq();
    io_pull_up_cfg();
    lscache_cache_disable();
    pinmux_hal_flash_quad_init();
    flash1.reg = (void *)FLASH_CTRL_REG;
    flash1.dual_mode_only = DUAL_MODE;
    flash1.continuous_mode_enable = false;
    flash1.writing = false;
    flash1.suspend_count = 0;
    flash1.continuous_mode_on = false;
    flash1.addr4b = false;
    hal_flash_init();
    clk_flash_init();
    hal_flash_continuous_mode_reset();
    hal_flash_software_reset();
    DELAY_US(500);
    hal_flash_release_from_deep_power_down();
    DELAY_US(100);
    hal_flash_qe_status_read_and_set();
}

void FlashInit(void)
{
    flash_init();
    __BKPT();
}

void XipStart(void)
{
    flash_init();
    __BKPT();
}

void XipStop(void)
{
    disable_global_irq();
    __BKPT();
}

void EraseChip(void)
{ 
    flash_init();

    hal_flash_chip_erase();
    __BKPT();
}

void EraseSector(uint32_t first, uint32_t last, uint32_t sector_size)
{
    flash_init();

    for (uint8_t i = first; i <= last; i++)
    {
        hal_flash_sector_erase(i * sector_size);
    }

    __BKPT();
}

void ProgramSyn(uint32_t offset, uint32_t count, uint8_t *buffer)
{
    uint16_t length = 0x100;
    while (count)
    {
        if (count < length)
            length = count;
        hal_flash_page_program(offset, buffer, length);

        offset += length;
        buffer += length;
        count -= length;
    }

    __BKPT();
}

void ProgramAsyn(uint32_t offset, uint32_t count, uint8_t *buffer, uint32_t buffer_size)
{
    flash_init();

    volatile uint32_t *wp   = (uint32_t *)buffer;
    uint32_t *rp            = (uint32_t *)(buffer + 4);
    uint32_t buffer_start   = (uint32_t)(buffer + 8);
    uint32_t buffer_end     = buffer_start + buffer_size;

    uint32_t remain;
    uint32_t page_size = 256;
    uint16_t length = count >= page_size ? page_size : count;

    while (count > 0)
    {
        remain = *wp - *rp + (*wp >= *rp ? 0 : buffer_size);
        if (remain >= length)
        {
            hal_flash_page_program(offset, (uint8_t *)*rp, length);
            
            count -= length;
            offset += length;
            *rp += length;
            if (*rp >= buffer_end)
                *rp = buffer_start;

            length = count >= page_size ? page_size : count;
        }
    }

    __BKPT();
}

void ReadStatusReg(uint32_t *data)
{
    flash_init();

    hal_flash_read_status_register_0_ram((uint8_t *)data);
    hal_flash_read_status_register_1_ram((uint8_t *)data + 1);
    __BKPT();
}

void WriteStatusReg(uint16_t data)
{
    flash_init();

    hal_flash_write_status_register(data);
    __BKPT();
}
