
#include "platform.h"
#include "log.h"
#include "ls_hal_otpv2.h"
#include "common.h"

uint32_t wdata[10];
uint32_t rdata[10];

int main()
{
    sys_init_none();
    memset32(wdata, 0x12345678, sizeof(wdata)/sizeof(uint32_t));
    memset32(rdata, 0, sizeof(rdata)/sizeof(uint32_t));
    HAL_OTPV2_Init();

    //写 system_side 的OTP2偏移0x100 10个u32
    HAL_OTPV2_Read_Write(true, false, 0x100, wdata, sizeof(wdata)/sizeof(uint32_t));
    //读 system_side 的OTP2偏移0x100 10个u32
    HAL_OTPV2_Read_Write(true, true, 0x100, rdata, sizeof(rdata)/sizeof(uint32_t));
    memset32(rdata, 0, sizeof(rdata)/sizeof(uint32_t));
    //读 crypto_side 的OTP2偏移0x100 10个u32
    HAL_OTPV2_Read_Write(false, true, OTP_MEM_TOTAL_BYTES + 0x100, rdata, sizeof(rdata)/sizeof(uint32_t));

    memset32(rdata, 0, sizeof(rdata)/sizeof(uint32_t));
    //写 crypto_side 的OTP2开头10个u32
    HAL_OTPV2_Read_Write(false, false, 0x800, wdata, sizeof(wdata)/sizeof(uint32_t));
    //读 crypto_side 的OTP2开头10个u32
    HAL_OTPV2_Read_Write(false, true, 0x800, rdata, sizeof(rdata)/sizeof(uint32_t));

    memset32(rdata, 0, sizeof(rdata)/sizeof(uint32_t));
    //写crypto_side 的OTP3开头10个u32
    HAL_OTPV2_Read_Write(false, false, 0x0, wdata, sizeof(wdata)/sizeof(uint32_t));
    //读crypto_side 的OTP3开头10个u32
    HAL_OTPV2_Read_Write(false, true, 0x0, rdata, sizeof(rdata)/sizeof(uint32_t));

    while (1);
}

