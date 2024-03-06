#include "platform.h"
#include "usb_packet_hid_data.h"
#include "upgrade_process.h"
#include "log.h"

IAP_Download_t gm_Download_Buffer;

void usb_packet_hid_data_init(void)
{
    gm_Download_Buffer.data_address = 0;
    gm_Download_Buffer.data_index = 0;
    gm_Download_Buffer.next_address = 0;
    gm_Download_Buffer.remain_data_len = 0;

    memset(gm_Download_Buffer.data_buffer, 0xFF, 256);
    memset(gm_Download_Buffer.remain_data, 0xFF, 64);
}

bool usb_packet_hid_data(uint32_t address, const uint8_t *data, uint32_t data_size)
{
    uint16_t len;
    uint16_t offset;

    /******************* 地址是否连续 ******************/
    if (gm_Download_Buffer.next_address > 0)
    {
        if (gm_Download_Buffer.next_address != address)
        {
            return false;
        }
    }

    /******* 首次进入 data_address 地址赋值 *******/
    if (gm_Download_Buffer.data_index == 0)
    {
        gm_Download_Buffer.data_address = address;
    }

    if (gm_Download_Buffer.remain_data_len > 0)
    {
        /************************************************************* 有备份数据 *****************************************************************/
        gm_Download_Buffer.data_address = gm_Download_Buffer.remain_address;
        memcpy(gm_Download_Buffer.data_buffer + gm_Download_Buffer.data_index, gm_Download_Buffer.remain_data, gm_Download_Buffer.remain_data_len);
        gm_Download_Buffer.data_index += gm_Download_Buffer.remain_data_len;

        /******************************* 清除备份数据 ***********************************/
        gm_Download_Buffer.remain_data_len = 0;
        memset(gm_Download_Buffer.remain_data, 0xFF, gm_Download_Buffer.remain_data_len);
    }

    len = gm_Download_Buffer.data_index + data_size;

    if (len < 256)
    {
        memcpy(gm_Download_Buffer.data_buffer + gm_Download_Buffer.data_index, data, data_size);
        gm_Download_Buffer.data_index = len;
    }
    else
    {
        offset = 256 - gm_Download_Buffer.data_index;
        memcpy(gm_Download_Buffer.data_buffer + gm_Download_Buffer.data_index, data, offset);
        gm_Download_Buffer.data_index = 256;

        /*********************************** 备份剩余数据 ****************************************/
        gm_Download_Buffer.remain_data_len = data_size - offset;
        memcpy(gm_Download_Buffer.remain_data, data + offset, gm_Download_Buffer.remain_data_len);
        gm_Download_Buffer.remain_address = address + offset;
    }

    /***************** 保留下次传输地址 *******************/
    gm_Download_Buffer.next_address = address + data_size;

    return true;
}

bool usb_packet_get_hid_data(bool check_last)
{
    LOG_I("usb_packet_get_hid_data");
    if (gm_Download_Buffer.data_index >= 256)
    {
        LOG_I("usb_packet_get_hid_data2");
__CONTINUE:        
        /************************************ write flash ************************************/
        write_app_code(gm_Download_Buffer.data_buffer,gm_Download_Buffer.data_address);
        
        gm_Download_Buffer.data_address = 0;
        gm_Download_Buffer.data_index = 0;

        return true;
    }

    if (check_last)
    {
        if (gm_Download_Buffer.remain_data_len > 0)
        {
            /************************************ 还有备份数据 ************************************/
            gm_Download_Buffer.data_address = gm_Download_Buffer.remain_address;
            memcpy(gm_Download_Buffer.data_buffer, gm_Download_Buffer.remain_data, gm_Download_Buffer.remain_data_len);
            gm_Download_Buffer.remain_data_len = 0;
            goto __CONTINUE;
        }
        else
        {
            /******* 没备份数据, 不足一帧数据的 *******/
            if (gm_Download_Buffer.data_index > 0)
            {
                goto __CONTINUE;
            }
        }
    }

    return false;
}
