#include "cpu.h"
#include "ls_hal_flash.h"
#include "leo.h"
#include "ls_hal_cache.h"
#include "platform.h"
#include "ls_soc_gpio.h"
#include "common.h"
#include "reg_sysc_awo.h"
#include "core_rv32.h"
#include "reg_v33_rg.h"
#include "field_manipulate.h"
#include "ls_hal_sha.h"
#include "ls_msp_qspiv2.h"
#include "../../module/micro-ecc/uECC.h"
#include "ext_flash.h"
#include <string.h>

typedef uint32_t (*crc32_calc_func_t)(uint32_t crc,uint8_t *data,uint32_t length);
#define HAL_LSCRC_CRC32          ((crc32_calc_func_t)0x01000c80)
#define EC_BOOT_SUPPORT 1
#define FLASH_ADDR 0x8000000
#define APP_DESC_OFFSET 0x2000
#define APP_IMAGE_OFFSET 0x2020
#define APP_OFFSET 0x2070
#define APP_SIGN_OFFSET APP_OFFSET - 0x40
#define APP_SIZE_INFO APP_OFFSET - 0x44
#define EXT_SEARCH_START_ADDR 0x2030
#define TEMP_BUF_SIZE 1024
#define MAX_EXT_FLASH_SIZE_BITS 26
__attribute__((aligned(4))) static const uint8_t ec_app_magic[8] = {'L','S','E','C','_','A','P','P'};
__attribute__((aligned(4))) uint8_t temp_buf[TEMP_BUF_SIZE];

#define EC_MODE_PIN PB06
#define I2C0_SCL_PIN PA11
#define I2C1_SCL_PIN PC02
#define I2C2_SCL_PIN PC04
#define I2C2_SCL_ALT_PIN PE00
#define I2C3_SCL_PIN PB00
#define I2C4_SCL_PIN PE05
#define I2C5_SCL_PIN PE13
#define I2C6_SCL_PIN PB14
#define I2C7_SCL_PIN PH07

const uint8_t i2c_scl_list[] = {
    I2C0_SCL_PIN,
    I2C1_SCL_PIN,
    I2C2_SCL_PIN,
    I2C2_SCL_ALT_PIN,
    I2C3_SCL_PIN,
    I2C4_SCL_PIN,
    I2C5_SCL_PIN,
    I2C6_SCL_PIN,
    I2C7_SCL_PIN,
};

struct flash_app_image_desc  
{
    uint8_t magic[8];
    uint32_t image_offset;
    uint32_t size;
    uint32_t version;
    uint32_t image_crc32;
    uint32_t crc32;
};

void boot_app(uint32_t base)
{
    void (*reset_handler)(void) = (void *)(base);
    reset_handler();
    while(1);
}

static void trim_val_load()
{
    uint32_t trim_value[12] = {0};

    hal_flash_read_security_area(1,0,(uint8_t *)trim_value,sizeof(trim_value));
    if(trim_value[0] == ~trim_value[1])
    {
        V33_RG->SRAM_LOCK = trim_value[0];
    }
    if(trim_value[2] == ~trim_value[3])
    {
        V33_RG->ANA_PMU_CTRL = trim_value[2];
    }
    if(trim_value[4] == ~trim_value[5])
    {
        V33_RG->TRIM0 = trim_value[4];
    }
    if(trim_value[6] == ~trim_value[7])
    {
        MODIFY_REG(V33_RG->SFT_CTRL01,0x70000000,trim_value[6]);
    }
    if(trim_value[8] == ~trim_value[9])
    {
        SYSC_AWO->PD_AWO_ANA1 = trim_value[8];
    }
    if(trim_value[10] == ~trim_value[11])
    {
        V33_RG->OP_CTRL = trim_value[10];
    }
}

void io_vcore_exti_config(uint8_t pin,exti_edge_t edge);
static void i2c_dbg_detect_int_disable()
{
    uint8_t i;
    for(i=0;i<ARRAY_LEN(i2c_scl_list);++i)
    {
        io_vcore_exti_config(i2c_scl_list[i],INT_EDGE_NONE);

    }
    csi_vic_disable_irq(EXTI_ASYNC_IRQn);
}

static void ext_flash_io_deinit()
{
    //cs
    uint8_t pin = PB07;
	set_gpio_mode((gpio_port_pin_t *)&pin);
    io_cfg_disable(pin);
    //clk
    pin = PB10;
	set_gpio_mode((gpio_port_pin_t *)&pin);
    io_cfg_disable(pin);
    //mosi
    pin = PB08;
	set_gpio_mode((gpio_port_pin_t *)&pin);
    io_cfg_disable(pin);
    //miso
    pin = PB09;
	set_gpio_mode((gpio_port_pin_t *)&pin);
    io_cfg_disable(pin);
}

extern bool sec_boot;
extern bool secp256k1;
extern uint8_t pub_key[64];
bool sign_verification(uint8_t *signature)
{
    uint32_t app_len;
    uint32_t digest[SHA256_WORDS_NUM];
    hal_flash_quad_io_read(APP_SIZE_INFO, (uint8_t *)&app_len,sizeof(app_len));
    HAL_LSSHA_Init();
    HAL_LSSHA_SHA256((void *)(FLASH_ADDR+APP_OFFSET),app_len,digest);
    HAL_LSSHA_DeInit();
    uECC_Curve curve = secp256k1 ? uECC_secp256k1() : uECC_secp256r1();
    uint8_t result =  uECC_verify(pub_key,(uint8_t *)digest,32,signature,curve);
    return result;
}

void ecc_verify(void)
{
    bool passed = false;
    uint8_t signature[64];
    if(sec_boot)
    {
        hal_flash_quad_io_read(APP_SIGN_OFFSET,signature,sizeof(signature));
        passed = sign_verification(signature);
        while(passed == false);
    }
}

static void image_copy(uint32_t src,uint32_t size)
{
    uint32_t dst = APP_DESC_OFFSET;
    while(size>FLASH_PAGE_SIZE)
    {
        ext_flash_read(src,(uint32_t *)temp_buf,FLASH_PAGE_SIZE/sizeof(uint32_t));
        hal_flash_page_program(dst,temp_buf,FLASH_PAGE_SIZE);
        src += FLASH_PAGE_SIZE;
        dst += FLASH_PAGE_SIZE;
        size -= FLASH_PAGE_SIZE;
    }
    ext_flash_read(src,(uint32_t *)temp_buf,CEILING(size,sizeof(uint32_t)));
    hal_flash_page_program(dst,temp_buf,size);
}

static bool int_flash_image_check(uint32_t image_crc32,uint32_t image_size, uint32_t offset)
{
    uint32_t crc = 0;
    uint16_t i;
    for(i=0;i<image_size/TEMP_BUF_SIZE;++i)
    {
        hal_flash_fast_read(offset,temp_buf,TEMP_BUF_SIZE);
        crc = HAL_LSCRC_CRC32(crc,temp_buf,TEMP_BUF_SIZE);
        offset += TEMP_BUF_SIZE;
    }
    if(image_size%TEMP_BUF_SIZE)
    {
        hal_flash_fast_read(offset,temp_buf,image_size%TEMP_BUF_SIZE);
        crc = HAL_LSCRC_CRC32(crc,temp_buf,image_size%TEMP_BUF_SIZE);
    }
    return image_crc32 == crc;
}

static bool ext_flash_app_desc_ptr_read(uint32_t offset,struct flash_app_image_desc *ptr)
{
    ext_flash_read(offset,(uint32_t *)ptr,sizeof(ptr->magic)/sizeof(uint32_t));
    if(memcmp(ptr->magic, ec_app_magic, sizeof(ptr->magic)) == 0)
    {
        ext_flash_read(offset+sizeof(ptr->magic),&((uint32_t *)ptr)[sizeof(ptr->magic)/sizeof(uint32_t)],(sizeof(*ptr)- sizeof(ptr->magic))/sizeof(uint32_t));
        uint32_t crc = HAL_LSCRC_CRC32(0,(uint8_t *)ptr,sizeof(*ptr)-sizeof(ptr->crc32));
        if(crc==ptr->crc32)
        {
            return true;
        }
    }
    return false;
}

static bool ext_flash_search(void *param)
{
    struct flash_app_image_desc *p = param;
    if(ext_flash_app_desc_ptr_read(EXT_SEARCH_START_ADDR, p))
    {
        return true;
    }else
    {
        return false;
    }
}

bool check_firmware_integrity(void *param)
{
    struct flash_app_image_desc *buf = param;
    hal_flash_fast_read(APP_DESC_OFFSET,(void *)buf,sizeof(struct flash_app_image_desc));
    if(memcmp(buf->magic, ec_app_magic, sizeof(buf->magic)) == 0)
    {
        uint32_t crc32_result = HAL_LSCRC_CRC32(0,(uint8_t *)buf,sizeof(struct flash_app_image_desc)-sizeof(uint32_t));
        if(crc32_result == buf->crc32)
        {
            if(int_flash_image_check(buf->image_crc32,buf->size,APP_IMAGE_OFFSET))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    return false;
}

void ec_app_boot_flow()
{
    bool internal;
    bool external;
    struct flash_app_image_desc nvm_head; 
    struct flash_app_image_desc desc_ptr;
    ext_flash_driver_init();
    while(1)
    {
        if(check_firmware_integrity(&nvm_head))
        {
            internal = true;
            external = ext_flash_search(&desc_ptr);
            break;
        }
        if(ext_flash_search(&desc_ptr))
        {
            external = true;
            internal = check_firmware_integrity(&nvm_head);
            break;
        }
    }

    if(internal && nvm_head.version >= desc_ptr.version)
    {
        return;
    }
    if(external)
    {
        if(internal == false || nvm_head.version < desc_ptr.version)
        {
            do{
                uint32_t offset = APP_DESC_OFFSET;
                while(offset < (desc_ptr.size + sizeof(struct flash_app_image_desc) + 4))
                {
                    hal_flash_sector_erase(offset);
                    offset += FLASH_SECTOR_SIZE;
                }
                image_copy(EXT_SEARCH_START_ADDR, desc_ptr.size + sizeof(struct flash_app_image_desc) + 4);
            }while(int_flash_image_check(desc_ptr.crc32, sizeof(struct flash_app_image_desc) - 4, APP_DESC_OFFSET)==false || 
            int_flash_image_check(desc_ptr.image_crc32,desc_ptr.size, APP_IMAGE_OFFSET)==false);
        }
    }
}

void boot_ram_start()
{
    if(io_read_pin(EC_MODE_PIN))
    {
        DELAY_US(1100);
        i2c_dbg_detect_int_disable();
    }else
    {   //pull up ph02 ph03
        MODIFY_REG(SYSC_AWO->IO[7].PUPD,3<<16<<2,3<<2);
    }
    __disable_irq();
    flash1.continuous_mode_enable = true;
    flash1.continuous_mode_on = false;
    flash1.reg = LSQSPIV2;
    flash1.writing = false;
    flash1.dual_mode_only = false;
    flash1.suspend_count = 0;
    flash1.addr4b = false;
    hal_flash_init();
    hal_flash_continuous_mode_start();
    pinmux_hal_flash_quad_init();
    trim_val_load();
    lscache_cache_enable(1);
    #if EC_BOOT_SUPPORT
    if(io_read_pin(EC_MODE_PIN))
    {
        ec_app_boot_flow();
        ext_flash_io_deinit();
    }
    #endif
    ecc_verify();
    boot_app(FLASH_ADDR+APP_OFFSET);
}