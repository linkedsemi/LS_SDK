#include "platform.h"
#include "ls_hal_flash.h"
#include "usb_command.h"

#include "log.h"
#include <string.h>
#include <stdint.h>
#include "usbd.h"
#include "ls_soc_gpio.h"
#include "ls_hal_iwdgv2.h"

/*********************************************************** 芯片型号和固件版本 ***********************************************************************/
static const uint8_t USB_IAP_FW_Ver[] = {'L', 'M', '3', '0', '5', '0', ' ', '1', '.', '0', '8', '(', '2', '0', '2', '3', '0', '9', '1', '2', ')'};

USB_Flash_Algo_t usb_flash_algo_param;

__attribute__((aligned(4))) uint8_t ga_buffer[64];
static uint8_t gn_buffer_size = 0;
volatile bool g_ubReset_System = 0;


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
        LOG_I(" reset!\n");
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
    hal_flash_page_erase(APP_CONFIG_ADDR_BASE);
    // LOG_I("\t flash erase completed!");
    usb_packet_respone_data(request[1], NULL, 0, response);
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
    default:
        usb_packet_error_data(*request, RESPONSE2_COMMAND_INVALID, response);
    }
}
