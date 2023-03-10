#include <string.h>
#include "genie_crc16.h"
#include "platform.h"
#include "reg_base_addr.h"
#include "ls_hal_flash.h"
#include "tmall_genie_ota.h"
#include "log.h"
#include "prf_fotas.h"

#define SPIF_SECTOR_SIZE 0x1000
#define OTA_MAX_LENGTH  0x14000 //80K
static unsigned short image_crc16 = 0;
extern struct fota_copy_info ais_ota_ptr;
extern genie_ota_ctx_t genie_ota_ctx;
uint16_t num_current_page=0;

int32_t hal_flash_erase(uint32_t off_set, uint32_t size)
{
    while(size)
    {
        hal_flash_sector_erase(off_set);
        if(size > FLASH_SECTOR_SIZE)
        {
            size -= FLASH_SECTOR_SIZE;
            off_set += FLASH_SECTOR_SIZE;
        }else
        {
            break;
        }
    }


    return 0;
}

int32_t hal_flash_read(uint32_t *off_set, void *out_buf, uint32_t out_buf_size)
{
    uint32_t current = *off_set;
    hal_flash_quad_io_read(current - FLASH_BASE_ADDR,out_buf,out_buf_size);
    current += out_buf_size;
    *off_set = current;
    return 0;
}


int erase_dfu_flash(void)
{
    int ret;
    uint32_t offset = ais_ota_ptr.fw_copy_src_addr - FLASH_BASE_ADDR;
    uint32_t length = OTA_MAX_LENGTH;
    uint8_t cmp_buf[32] = {0xFF};
    uint8_t wr_buf[32] = {0};

    memset(cmp_buf, 0xFF, sizeof(cmp_buf));
    ret = hal_flash_read(&offset, (void *)wr_buf, sizeof(wr_buf));
    if (ret < 0)
    {
        return -1;
    }

    if (memcmp(wr_buf, cmp_buf, sizeof(wr_buf)) == 0)
    {
        return 0;
    }

    /* For bootloader upgrade, we will reserve two sectors, then save the image */
    ret = hal_flash_erase(offset, length);
    if (ret < 0)
    {
        return -1;
    }

    return 0;
}

int32_t hal_flash_write(uint32_t *off_set,const void *in_buf, uint32_t in_buf_size)
{
    uint32_t current = *off_set;
    uint16_t length;
    if(current % 256)
    {
        length = in_buf_size > 256 - current % 256 ? 256 - current % 256 : in_buf_size;
    }else
    {
        length = 0;
    }
    if(length)
    {
        hal_flash_quad_page_program(ais_ota_ptr.fw_copy_src_addr  + current - FLASH_BASE_ADDR,(void *)in_buf,length);
        in_buf_size -= length;
        current += length;
        in_buf = (uint8_t *)in_buf + length; 
    }
    while(in_buf_size)
    {
        length = in_buf_size > 256 ? 256 : in_buf_size;
        hal_flash_quad_page_program(ais_ota_ptr.fw_copy_src_addr  + current - FLASH_BASE_ADDR,(void *)in_buf,length);
        in_buf_size -= length;
        current += length;
        in_buf = (uint8_t *)in_buf + length; 
    }
    return in_buf_size;
}

int ali_dfu_image_update(short signature, int offset, int length, int *buf)
{
    int ret;
    uint8_t *wr_buf = (uint8_t *)buf;
    
    if (offset == 0)
    {
        image_crc16 = util_crc16_ccitt(wr_buf, length, NULL);
    }
    else
    {
        image_crc16 = util_crc16_ccitt(wr_buf, length, &image_crc16);
    }

    if (OTA_MAX_LENGTH < (offset + length))
    {
        return -1;
    }

     ret = hal_flash_write((uint32_t*)&offset, (void *)wr_buf, length);
    if (ret < 0)
    {
        return -1;
    }

	return 0;

}

uint32_t ali_dfu_get_ota_partition_max_size(void)
{

	return 4*1024*1024/2/8;
}

unsigned char dfu_check_checksum(short image_id, unsigned short *crc16_output)
{
    num_current_page=0;
    *crc16_output = image_crc16;
    return 1;
}


