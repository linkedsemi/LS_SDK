#include "ls_hal_otpv2.h"
#include "ls_msp_otpv2.h"
#include "field_manipulate.h"

HAL_StatusTypeDef HAL_OTPV2_Init()
{
    HAL_LSOTPV2_MSP_Init();
    return HAL_OK;
}

HAL_StatusTypeDef HAL_OTPV2_DeInit()
{
    HAL_LSOTPV2_MSP_DeInit();
    return HAL_OK;
}

HAL_StatusTypeDef HAL_OTPV2_Read_Write(bool is_system_side, bool is_read, uint32_t offset, uint32_t *data, uint32_t length)
{
    uint32_t op_addr_bs;
    if(is_system_side)
    {
        while(READ_REG(SYS_SIDE_OTP->CFG_0x20) != 0xc);
        if (((offset + length) > OTP_MEM_TOTAL_BYTES) || (length == 0))
            return HAL_INVALIAD_PARAM;
        op_addr_bs = REG_OTP_BASE + offset;
    }else{
        while(READ_REG(CRP_SIDE_OTP->CFG_0x20) != 0xc);
        if (((offset + length) > OTP_MEM_TOTAL_BYTES*2) || (length == 0))
            return HAL_INVALIAD_PARAM;
        op_addr_bs = REG_OTP_CYP_BASE + offset;
    }

    for(uint32_t i = 0; i < length; i++){
        if(is_read)
            *data++ = *(volatile uint32_t *)(op_addr_bs + i*0x4);
        else
            *(volatile uint32_t *)(op_addr_bs + i*0x4) = *data++;
    }
    return HAL_OK;
}