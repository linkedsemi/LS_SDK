#include "platform.h"
#include "ls_hal_flash.h"
#include "usb_command.h"
#include "usb_packet_hid_data.h"

#include "log.h"
#include <string.h>
#include <stdint.h>
#include "usbd.h"
#include "ls_soc_gpio.h"
#include "ls_hal_iwdgv2.h"
#include "upgrade_process.h"
#include "ls_hal_crc.h"

/*********************************************************** 芯片型号和固件版本 ***********************************************************************/
static const uint8_t USB_IAP_FW_Ver[] = {'L', 'M', '3', '0', '5', '0', ' ', '1', '.', '0', '7', '(', '2', '0', '2', '3', '0', '9', '1', '2', ')'};

USB_Flash_Algo_t usb_flash_algo_param;

__attribute__((aligned(4))) uint8_t ga_buffer[64];
static uint8_t gn_buffer_size = 0;
volatile bool g_ubReset_System = 0;


/**************************************************************
 * @brief 初始化 Flash 烧录结构体变量
 * 
 *************************************************************/
void usb_command_var_init(void)
{
    usb_flash_algo_param.is_flash_process = false;
    usb_flash_algo_param.download_bin_start_address = 0;
    usb_flash_algo_param.download_bin_size = 0;
    usb_flash_algo_param.download_bin_offset = 0;
    usb_packet_hid_data_init();
}


/********************************************************************
 * @brief 计算命令数据和
 * 
 * @param data 命令数据
 * @param data_size 命令数据大小
 * @return uint8_t 
 *******************************************************************/
static uint8_t calc_checksum(const uint8_t *data, uint32_t data_size)
{
    uint32_t sum = 0;
    const uint8_t *p_data_end = data + data_size;
    while (data < p_data_end)
    {
        sum += *data++;
    }
    return (sum & 0xff);
}


/*******************************************************************
 * @brief 获取上位机下发数据大小
 * 
 * @param data   
 * @param bigendian 
 * @return uint32_t 
 *******************************************************************/
static uint32_t get_uint32_data(const uint8_t *data, bool bigendian)
{
    uint32_t val;
    if (bigendian)
    {
        val = (((uint32_t)data[0]) << 24) | (((uint32_t)data[1]) << 16) | (((uint32_t)data[2]) << 8) | ((uint32_t)data[3]);
    }
    else
    {
        val = (((uint32_t)data[3]) << 24) | (((uint32_t)data[2]) << 16) | (((uint32_t)data[1]) << 8) | ((uint32_t)data[0]);
    }
    return val;
}


/***********************************************************************************************
 * @brief  返回错误应答给上位机
 * 
 * @param cmd  ：对应上位机的命令
 * @param response2 ：要回复的错误信息
 * @param response  ：返回数据指针
 ***********************************************************************************************/
static void usb_packet_error_data(const uint8_t cmd, const uint8_t response2, uint8_t *response)
{
    response[0] = EC_CMD_FRAME_HEAD;
    response[1] = cmd;
    response[2] = 0x02;
    response[3] = RESPONSE1_ERROR;
    response[4] = response2;
    response[5] = calc_checksum(response, 5);
}

/**********************************************************************************************************
 * @brief 返回正确应答给上位机
 * 
 * 
 * @param cmd  ：对应上位机的命令
 * @param data ：返回数据
 * @param data_len  ：返回数据长度
 * @param response  ：返回数据指针
 *********************************************************************************************************/
static void usb_packet_respone_data(const uint8_t cmd, uint8_t *data, uint8_t data_len, uint8_t *response)
{
    uint8_t num;
    uint8_t i;

    response[0] = EC_CMD_FRAME_HEAD;
    response[1] = cmd;
    response[2] = data_len + 2;
    response[3] = RESPONSE1_OK;
    response[4] = RESPONSE2_OK;

    for (i = 0; i < data_len; i++)
    {
        response[5 + i] = data[i];
    }
    num = data_len + 5;

    response[num] = calc_checksum(response, num);
}

/*****************************************************************************
 * @brief 检查命令数据
 * 
 * 
 * @param request   ：上位机的命令数据
 * @param response  ：返回数据指针
 * @return true 
 * @return false 
 ****************************************************************************/
static bool usb_check_command_data(const uint8_t *request, uint8_t *response)
{
    // [0] = 0xff, [1] = cmd, [2] = length, [3...x] = data
    uint8_t cmd_length;
    uint8_t sum;

    cmd_length = request[2] + 3;
    sum = calc_checksum(request, (uint32_t)cmd_length);
    if (sum != request[cmd_length])
    {
        usb_packet_error_data(request[1], RESPONSE2_SUM_INVALID, response);

        return false;
    }

    return true;
}


/*************************************************************************************
 * 
 * @brief 上位机下发数据解析为握手命令，实现握手应答
 * 
 * 
 * @param request  ：FF 00/01 00 xor
 * @param response ：FF 00/01 xx 90 00 + "EC_Link 0.xxx" xor or  FF 00/01 02 68 xx xor
 * 
 *************************************************************************************/
static void usb_process_read_link_info(const uint8_t *request, uint8_t *response)
{
    /***************************** Command of Length ***************************/
    if (request[2] != 0x00)
    {
        // LOG_I("RESPONSE2_LENGTH_INVALID\n");
        usb_packet_error_data(request[1], RESPONSE2_LENGTH_INVALID, response);
        return;
    }

    /******************* 返回给上位机的芯片型号和固件版本 **********************/
    if (request[1] == ID_CMD_READ_LINK_INFO)
    {
        gn_buffer_size = sizeof(USB_IAP_FW_Ver);
        memcpy(ga_buffer, (uint8_t *)USB_IAP_FW_Ver, gn_buffer_size);
    }
    else
    {
        gn_buffer_size = sizeof(USB_IAP_FW_Ver);
        memcpy(ga_buffer, (uint8_t *)USB_IAP_FW_Ver, gn_buffer_size);
    }
    usb_packet_respone_data(request[1], ga_buffer, gn_buffer_size, response);
}

/*****************************************************************************
 * 
 * @brief 上位机下发数据解析为复位命令，实现复位
 * 
 * 
 * @param request  ：FF 03 00 xor
 * @param response ：FF 03 02 90 00 xor or  FF 03 00 02 68 xx xor
 * 
 *****************************************************************************/
static void ec_process_connect_reset(const uint8_t *request, uint8_t *response)
{
    if (request[2] != 0x00)
    {
        LOG_I("RESPONSE2_LENGTH_INVALID\n");
        usb_packet_error_data(request[1], RESPONSE2_LENGTH_INVALID, response);
        return;
    }
    /********************************** 复位 **********************************/
    if (request[1] == ID_CMD_RESET_EC)
    {
        // LOG_I(" reset!\n");
        g_ubReset_System = true;
        usb_packet_respone_data(request[1], NULL, 0, response);
    }
    else
    {
        usb_packet_error_data(request[1], RESPONSE2_CONNECT_ERROR, response);
    }
}


/***************************************************************************************************
 * 
 * @brief 上位机下发数据解析为擦除 Flash 命令，实现 Flash 擦除
 * 
 * 
 * @param request  ：FF 21 01 00 xor (chip_erase) / FF 21 09 01 addr sector_count xor (sector_erase)
 * @param response ：FF 21 00 00  xor / FF 21 00 02 68 xx xor
 * 
 **************************************************************************************************/
static void usb_process_flash_erase(const uint8_t *request, uint8_t *response)
{
    if (earse_app_code())
    {
        LOG_I(" flash erase completed!\n");
        usb_packet_respone_data(request[1], NULL, 0, response);
    }
    else
    {
        LOG_I(" flash erase  ERROR!\n");
        usb_packet_error_data(request[1], RESPONSE2_TIMEOUT, response);
    }
}


/**********************************************************************************************
 * 
 * @brief 上位机下发数据解析为设置数据参数命令，实现数据参数接收
 * 
 * 
 * @param request  ：FF 22 04 bin_size xor / FF 22 0c bin_start_address bin_size crc16 xor
 * @param response ：FF 22 02 90 00  xor / FF 22 00 02 68 xx xor
 * 
 **********************************************************************************************/
static void usb_process_flash_info(const uint8_t *request, uint8_t *response)
{
    /********************************* Flash 数据不需要校验的情况 **************************/
    if (request[2] == 0x04)
    {
        // LOG_I(" flash write no verfiy\n");
        usb_flash_algo_param.is_verfiy_download = false;
        usb_flash_algo_param.download_bin_size = get_uint32_data(&request[3], true);
    }
    /********************************* Flash 数据需要校验的情况 ****************************/
    else if (request[2] == 0x0c)
    {
        // LOG_I(" flash write verfiy\n");
        usb_flash_algo_param.is_verfiy_download = true;
        usb_flash_algo_param.download_bin_start_address = get_uint32_data(&request[3], true);
        usb_flash_algo_param.download_bin_size = get_uint32_data(&request[7], true);
        usb_flash_algo_param.download_bin_crc32 = get_uint32_data(&request[11], true);
    }
    else
    {
        usb_packet_error_data(request[1], RESPONSE2_LENGTH_INVALID, response);
        return;
    }

    usb_flash_algo_param.download_bin_offset = 0;

    usb_packet_respone_data(request[1], NULL, 0, response);
}

/*******************************************************************************************************
 * 
 * @brief 校验烧录到 Flash 的数据是否正确
 * 
 *******************************************************************************************************/
static bool lm3050_flash_verify(void)
{
    volatile uint32_t crc32_result = 0;
    uint32_t remain = 0;
    uint8_t temp_buf[1024] = {0};
    struct crc_param CRC32_PARAM_0 = {
        .poly = 0x04c11db7,
        .init = 0xffffffff,
        .xor_out = 0x0,
        .bitwidth = 32,
        .reverse_in = 1,
        .reverse_out = 0};
    struct crc_param CRC32_PARAM_1 = {
        .poly = 0x04c11db7,
        .init = 0xffffffff,
        .xor_out = 0xffffffff,
        .bitwidth = 32,
        .reverse_in = 1,
        .reverse_out = 1};
    HAL_LSCRC_Init();
    remain = usb_flash_algo_param.download_bin_size % sizeof(temp_buf);
    /******************************* 计算烧录到 Flash 数据的 CRC32值 *********************************/
    for (uint32_t i = 0; i < usb_flash_algo_param.download_bin_size / sizeof(temp_buf); ++i)
    {
        hal_flash_fast_read(usb_flash_algo_param.download_bin_start_address, temp_buf, sizeof(temp_buf));
        if (i+1 < usb_flash_algo_param.download_bin_size / sizeof(temp_buf))
        {
            crc32_result = HAL_LSCRC_CRC_CALC(&CRC32_PARAM_0, temp_buf, sizeof(temp_buf));
            usb_flash_algo_param.download_bin_start_address += sizeof(temp_buf);
            CRC32_PARAM_0.init = crc32_result;
        }
        else
        {
            if (remain)
            {
                crc32_result = HAL_LSCRC_CRC_CALC(&CRC32_PARAM_0, temp_buf, sizeof(temp_buf));
                usb_flash_algo_param.download_bin_start_address += sizeof(temp_buf);
                CRC32_PARAM_1.init = crc32_result;
                hal_flash_fast_read(usb_flash_algo_param.download_bin_start_address, temp_buf, remain);
                crc32_result = HAL_LSCRC_CRC_CALC(&CRC32_PARAM_1, temp_buf, remain);
            }
            else
            {
                CRC32_PARAM_1.init = crc32_result;
                crc32_result = HAL_LSCRC_CRC_CALC(&CRC32_PARAM_1, temp_buf, sizeof(temp_buf));
            }
        }
    }
    
    LOG_I("crc32_result:%#x\n", crc32_result);

    HAL_LSCRC_DeInit();

    /******************************* 比较上位机下发的 CRC32值 *********************************/
    if ((crc32_result != usb_flash_algo_param.download_bin_crc32))
    {
        return false;
    }
    return true;
}

static bool usb_flash_write(bool check_last)
{
    usb_packet_get_hid_data(check_last);
    return true;
}

/*******************************************************************************
 * 
 * @brief 上位机下发数据解析为烧录 Flash 命令，实现 Flash 烧录
 * 
 * 
 * @param request  ：FF 23 len addr data xor
 * @param response ：FF 23 02 90 00  xor / FF 23 02 68 xx xor
 * 
 ******************************************************************************/
static void usb_process_flash_write(const uint8_t *request, uint8_t *response)
{
    uint32_t address;
    uint8_t data_len;

    /******************************* 检验数据大小 *********************************/
    if (usb_flash_algo_param.download_bin_size <= 0)
    {
        usb_packet_error_data(request[1], RESPONSE2_LENGTH_INVALID, response);
        return;
    }
    
    if ((request[2] <= 0x3c) && (request[2] > 4))          // len = request[2]        
    {
        address = get_uint32_data(&request[3], true);
        data_len = request[2] - 4;                         // - len(addr)
        usb_flash_algo_param.download_bin_offset += data_len;

        /********************************** 拼包 **********************************/
        if (!usb_packet_hid_data(address, request + 7, data_len))
        {
            usb_command_var_init();
            usb_packet_error_data(request[1], RESPONSE2_ADDRESS_INVALID, response);
            return;
        }

        /***************************** 写flash ***************************/
        if (!usb_flash_write(false))
        {
            usb_command_var_init();
            usb_packet_error_data(request[1], RESPONSE2_TIMEOUT, response);
            return;
        }

        usb_flash_algo_param.is_flash_process = true;

        if (usb_flash_algo_param.download_bin_offset >= usb_flash_algo_param.download_bin_size)
        {
            if (!usb_flash_write(true))
            {
                usb_command_var_init();
                usb_packet_error_data(request[1], RESPONSE2_TIMEOUT, response);
                return;
            }
            /******************************** verify *********************************/
            if (usb_flash_algo_param.is_verfiy_download)
            {
                if (!lm3050_flash_verify())
                {
                    usb_command_var_init();
                    usb_packet_error_data(request[1], RESPONSE2_VERIFY_ERROR, response);
                    return;
                }
                sign_app_code();
            }
            /************************************ download end ************************************/
            usb_command_var_init();
        }
        sign_app_code();
        usb_packet_respone_data(request[1], NULL, 0, response);
    }
    else
    {
        usb_packet_error_data(request[1], RESPONSE2_LENGTH_INVALID, response);
    }
}

/************************************************************************
 * 
 * @brief 区分上位机命令，执行命令处理函数
 * 
 * 
 * @param request  接收到来自上位机的数据包内容
 * @param response 将要返回给上位机的数据包内容
 * 
 ***********************************************************************/
void usb_command_execute(const uint8_t *request, uint8_t *response)
{
    if (usb_check_command_data(request, response) == false)
    {
        return;
    }

    switch (request[1])
    {
    case ID_CMD_READ_LINK_INFO:
        usb_process_read_link_info(request, response);
        break;
    case ID_CMD_RESET_EC:
        ec_process_connect_reset(request, response);
        break;
    case ID_CMD_E_FLASH_ERASE:
        usb_process_flash_erase(request, response);
        break;
    case ID_CMD_E_FLASH_INFO:
        usb_process_flash_info(request, response);
        break;
    case ID_CMD_E_FLASH_WRITE:
        usb_process_flash_write(request, response);
        break;
    default:
        usb_packet_error_data(*request, RESPONSE2_COMMAND_INVALID, response);
    }
}
