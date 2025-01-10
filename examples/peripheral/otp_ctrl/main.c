#include <string.h>
#include <stdint.h>
#include "ls_hal_otp_ctrl.h"
#include "ls_msp_otp_ctrl.h"
#include "platform.h"
#include "common.h"
#include "log.h"

#define TEST_ADDR   (0x30)
#define TEST_LENGTH (0x30)

static uint8_t buffer[0x80];
static uint8_t buffer1[0x80];
static uint8_t buffer2[0x80];

static uint32_t read_forbidden[] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 
};
static uint32_t write_forbidden[] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 
};

static void error()
{
    __BKPT();
    while (1)
    {

    }
}

static void otp_test_write()
{
    if (HAL_OTP_Write(TEST_ADDR, buffer, TEST_LENGTH) != HAL_OK)
    {
        LOG_I("OTP write_data fail...");
        error();
    }
    LOG_I("OTP write -addr:0x%x -length:0x%x", TEST_ADDR, TEST_LENGTH);
    LOG_HEX(buffer, TEST_LENGTH);
}

static void otp_test_read()
{
    uint32_t addr = TEST_ADDR & ~0x1f;
    uint32_t length = TEST_LENGTH + TEST_ADDR;
    HAL_OTP_Read(addr, buffer, length);
    LOG_I("OTP read -addr:0x%x -length:0x%x", addr, length);
    LOG_HEX(buffer, length);
}

static void otp_test_write_forbid()
{
    write_forbidden[TEST_ADDR >> 0x10] = 0x2;
    HAL_OTP_SET_WR_Addr(write_forbidden);
    LOG_I("Set OTP write forbid...");
    LOG_HEX(write_forbidden, 0x10);

    HAL_OTP_Read(0x0, buffer1, 0x60);
    LOG_I("otp read -addr:0x%x -length:0x%x", 0x0, 0x60);
    LOG_HEX(buffer1, 0x60);

    if (!memcmp(buffer, buffer1, TEST_LENGTH))
    {
        LOG_I("OTP read forbid fail...");
        error();
    }
    LOG_I("OTP read forbid ok...");
}

static void otp_test_read_forbid()
{
    read_forbidden[TEST_ADDR >> 0x10] = 0x4;
    HAL_OTP_SET_RD_Addr(read_forbidden);
    LOG_I("Set OTP read forbid...");
    LOG_HEX(read_forbidden, 0x10);

    HAL_OTP_Read(TEST_ADDR, buffer1, 0x50);
    LOG_I("otp read -addr:0x%x -length:0x%x", TEST_ADDR, 0x50);
    LOG_HEX(buffer1, 0x50);
    HAL_OTP_Read(0x20, buffer2, 0x60);
    LOG_I("otp read -addr:0x%x -length:0x%x", 0x20, 0x60);
    LOG_HEX(buffer2, 0x60);
    if (!memcmp(buffer, buffer1, TEST_LENGTH))
    {
        LOG_I("OTP read forbid fail...");
        error();
    }
    LOG_I("OTP read forbid ok...");
}

int main(void)
{
    sys_init_none();
    HAL_OTP_CTRL_Init();
    LOG_I("OTP Test Start...");
    for (uint32_t i = 0; i < TEST_LENGTH; i++)
    {
        buffer[i] = i;
    }

    otp_test_write();

    otp_test_read();

    otp_test_write_forbid();

    otp_test_read_forbid();

    __BKPT();
    while (1) ;
}
