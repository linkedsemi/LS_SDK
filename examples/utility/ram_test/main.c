#include "ls_ble.h"
#include "platform.h"
#include "ls_hal_uart.h"
#include "ls_soc_gpio.h"
#include <string.h>
UART_HandleTypeDef UART_Config2;

static uint8_t recv_cmd;

enum cmd_type
{
    MEM32_WRITE = 0x0,
    MEM32_READ = 0x1,
    MEM_BULK_WRITE = 0x2,
    MEM_BULK_READ = 0x3,
    PROGRAM_GO = 0x4,
    FLASH_CHIP_ERASE = 0x5,
    FLASH_READ_STATUS_REG_0 = 0x6,
    FLASH_READ_STATUS_REG_1 = 0x7,
    FLASH_WRITE_STATUS_REG = 0x8,
    FLASH_QUAD_PAGE_PROGRAM = 0x9,
    FLASH_PAGE_PROGRAM = 0xa,
    FLASH_SECTOR_ERASE = 0xb,
    FLASH_QUAD_IO_READ = 0xc,
    FLASH_FAST_READ = 0xd,
    FLASH_DEEP_POWER_DOWN = 0xe,
    FLASH_RELEASE_FROM_DEEP_POWER_DOWN = 0xf,
    FLASH_READ_JEDEC_ID = 0x10,
    FLASH_READ_UNIQUE_ID = 0x11,
    FLASH_ERASE_SECURITY_AREA = 0x12,
    FLASH_PROGRAM_SECURITY_AREA = 0x13,
    FLASH_READ_SECURITY_AREA = 0x14,
    FLASH_SOFTWARE_RESET = 0x15,
    INVALID_COMMAND = 0xff,
};
enum response_status
{
    RESPONSE_STATUS_NO_ERROR = 0x0,
    RESPONSE_STATUS_ERROR = 0x1,
    RESPONSE_STATUS_FEATURE_DISABLED = 0x2,
    
};
uint8_t timerout_buff[8] = {'t','i','m','e','r','o','u','t'};
void uart_read(uint8_t *buf,uint16_t length)
{
   uint8_t sta = HAL_UART_Receive(&UART_Config2, buf, 4, 10000);
   if (sta == HAL_TIMEOUT)
   {
       HAL_UART_Transmit(&UART_Config2, timerout_buff, 8, 1000);
   }
}

void uart_write(uint8_t *buf,uint16_t length)
{
    HAL_UART_Transmit(&UART_Config2, buf, length, 1000);
}

static void uart_write_word(uint32_t word)
{
    uart_write((void *)&word,sizeof(word));
}

static uint32_t uart_read_word()
{
    uint32_t read_data;
    uart_read((void *)&read_data,sizeof(read_data));
    return read_data;
}

static void uart_write_byte(uint8_t byte)
{
    uart_write(&byte,sizeof(byte));
}

uint32_t addr;
uint32_t data ;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart == &UART_Config2)
    {
        switch (recv_cmd)
        {
        case MEM32_WRITE:
            addr = uart_read_word();
            data = uart_read_word();
            *(uint32_t *)addr = data;
            uart_write_byte(MEM32_WRITE);
            uart_write_byte(RESPONSE_STATUS_NO_ERROR);
            break;
        case MEM32_READ:
            addr = uart_read_word();
            data = *(uint32_t *)addr;
            uart_write_byte(MEM32_READ);
            uart_write_byte(RESPONSE_STATUS_NO_ERROR);
            uart_write_word(data);
        break;
        default:
            break;
        }
        HAL_UART_Receive_IT(&UART_Config2, &recv_cmd, 1);
    }
}

static void uart_test_init(void)
{
    pinmux_uart1_init(PA10,PA11);
    io_pull_write(PA11, IO_PULL_UP);
    UART_Config2.UARTX = UART1;
    UART_Config2.Init.BaudRate = UART_BAUDRATE_115200;
    UART_Config2.Init.MSBEN = 0;
    UART_Config2.Init.Parity = UART_NOPARITY;
    UART_Config2.Init.StopBits = UART_STOPBITS1;
    UART_Config2.Init.WordLength = UART_BYTESIZE8;
    HAL_UART_Init(&UART_Config2);
    HAL_UART_Receive_IT(&UART_Config2, &recv_cmd, 1);
}

int main()
{
    sys_init_none();
    uart_test_init();
    while(1);
    return 0;
}
