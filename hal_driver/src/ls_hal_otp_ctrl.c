#include "ls_hal_otp_ctrl.h"
#include "ls_msp_otp_ctrl.h"
#include "field_manipulate.h"
#include "platform.h"

#define ONEBIT_BYTES (0x20)
#define FIFO_DEPTH_BYTES (0x20)

static uint32_t otp_buffer[0x10];

static void otp_check_power_ready()
{
    while (1)
    {
        if (REG_FIELD_RD(OTP_CTRL->READY, OTP_CTRL_READY_POWER_READY) == 0xF)
        {
            return;
        }
    }
}

void HAL_OTP_CTRL_Init()
{
    HAL_MSP_OTP_CTRL_Init();

    otp_check_power_ready();

    REG_FIELD_WR(OTP_CTRL->PIN, OTP_CTRL_PIN_PTRIM, 1);

#ifndef ROM_CODE
    DELAY_US(50);
#else
    DELAY_US(50);//TODO
#endif
}

void HAL_OTP_SET_WR_Addr(uint32_t addr[0x4])
{
    for (uint8_t i = 0; i < 0x4; i++)
    {
        OTP_CTRL->WR_FORBIDDEN_ADDR[i] = addr[i];
    }
}

void HAL_OTP_SET_RD_Addr(uint32_t addr[0x4])
{
    for (uint8_t i = 0; i < 0x4; i++)
    {
        OTP_CTRL->RD_FORBIDDEN_ADDR[i] = addr[i];
    }
}

HAL_StatusTypeDef HAL_OTP_Write_bit(uint32_t offset, uint8_t bit_field)
{
    uint8_t byte = 0;

    if (bit_field > 7)
        return HAL_INVALIAD_PARAM;
    
    otp_check_power_ready();

    HAL_StatusTypeDef result_val = HAL_OTP_Read(offset, &byte, 1);  
    if (result_val != HAL_OK)
        return result_val;
    
    if (((byte >> bit_field) & 0x1)== 0x0)
        return HAL_ERROR; 

    OTP_CTRL->SOFT_REQ = 0;
    OTP_CTRL->INTR_CLR = OTP_CTRL_INTR_CLR_FINISH_MASK;
    OTP_CTRL->INTR_MSK = 0;
    REG_FIELD_WR(OTP_CTRL->CTRL, OTP_CTRL_CTRL_1LEN_MODE, 1);
    OTP_CTRL->READY = OTP_CTRL_READY_WRITE_EN_MASK;
    OTP_CTRL->WR_FIFO_CTRL = OTP_CTRL_WR_FIFO_RCLR_MASK | OTP_CTRL_WR_FIFO_WCLR_MASK;
    OTP_CTRL->WR_FIFO_CTRL = 0x0;

    OTP_CTRL->PIN = FIELD_BUILD(OTP_CTRL_PIN_PTRIM, 1) | FIELD_BUILD(OTP_CTRL_PIN_PA, offset) |
                    FIELD_BUILD(OTP_CTRL_PIN_PCE, 1) | FIELD_BUILD(OTP_CTRL_PIN_PPROG, 1) |
                    FIELD_BUILD(OTP_CTRL_PIN_PAIO, bit_field) | FIELD_BUILD(OTP_CTRL_PIN_PAS, 0) |
                    FIELD_BUILD(OTP_CTRL_PIN_PTC, 0) | FIELD_BUILD(OTP_CTRL_PIN_PTR, 0) |
                    FIELD_BUILD(OTP_CTRL_PIN_PTM, 2);

    OTP_CTRL->WR_DATA = 0x0;
    OTP_CTRL->SOFT_REQ = OTP_CTRL_SOFT_REQ_MASK;

    while (OTP_CTRL->INTR_RAW == 0x0) ;

    return HAL_OK;
}

HAL_StatusTypeDef HAL_OTP_Write(uint32_t offset, uint8_t *data, uint32_t length)
{
    uint32_t i;
    uint8_t *p_buffer = (uint8_t *)otp_buffer;
    if ((length % sizeof(uint32_t)) || (length > 0x40))
        return HAL_INVALIAD_PARAM;

    otp_check_power_ready();

    HAL_StatusTypeDef result_val = HAL_OTP_Read(offset, p_buffer, length);
    if (result_val != HAL_OK)
        return result_val;

    for (i = 0; i < length; i++)
    {
        p_buffer[i] = data[i] | ~p_buffer[i];
    }

    OTP_CTRL->SOFT_REQ = 0;
    OTP_CTRL->INTR_CLR = OTP_CTRL_INTR_CLR_FINISH_MASK;
    OTP_CTRL->INTR_MSK = 0;
    REG_FIELD_WR(OTP_CTRL->CTRL, OTP_CTRL_CTRL_1LEN_MODE, 0);
    OTP_CTRL->WR_LEN = FIELD_BUILD(OTP_CTRL_WR_LEN, length - 1) |
                       FIELD_BUILD(OTP_CTRL_WFIFO_FULL_EN, 1);
    OTP_CTRL->READY = OTP_CTRL_READY_WRITE_EN_MASK;
    OTP_CTRL->WR_FIFO_CTRL = OTP_CTRL_WR_FIFO_RCLR_MASK | OTP_CTRL_WR_FIFO_WCLR_MASK;
    OTP_CTRL->WR_FIFO_CTRL = 0x0;

    OTP_CTRL->PIN = FIELD_BUILD(OTP_CTRL_PIN_PTRIM, 1) | FIELD_BUILD(OTP_CTRL_PIN_PA, offset) |
                    FIELD_BUILD(OTP_CTRL_PIN_PCE, 1) | FIELD_BUILD(OTP_CTRL_PIN_PPROG, 1) |
                    FIELD_BUILD(OTP_CTRL_PIN_PAIO, 0) | FIELD_BUILD(OTP_CTRL_PIN_PAS, 0) |
                    FIELD_BUILD(OTP_CTRL_PIN_PTC, 0) | FIELD_BUILD(OTP_CTRL_PIN_PTR, 0) |
                    FIELD_BUILD(OTP_CTRL_PIN_PTM, 2);
    OTP_CTRL->SOFT_REQ = OTP_CTRL_SOFT_REQ_MASK;

    i = 0;
    while (length)
    {
        if ((OTP_CTRL->WR_FIFO_CTRL & OTP_CTRL_WR_FIFO_FULL_MASK) == 0)
        {
            OTP_CTRL->WR_DATA = otp_buffer[i++];
            length -= 4;
        }
    }

    while (OTP_CTRL->INTR_RAW == 0x0) ; /* wait program done */

    return HAL_OK;
}

HAL_StatusTypeDef HAL_OTP_Read(uint32_t offset, uint8_t *data, uint32_t length)
{
    uint8_t remain_length = length & 0x3;
    uint32_t len = (length + 0x3) & ~0x3;

    otp_check_power_ready();

    OTP_CTRL->SOFT_REQ = 0;
    OTP_CTRL->INTR_MSK = 0;
    OTP_CTRL->INTR_CLR = OTP_CTRL_INTR_CLR_FINISH_MASK;
    REG_FIELD_WR(OTP_CTRL->CTRL, OTP_CTRL_CTRL_1LEN_MODE, 0);
    OTP_CTRL->RD_LEN = FIELD_BUILD(OTP_CTRL_RD_LEN, len - 1) |
                       FIELD_BUILD(OTP_CTRL_RFIFO_FULL_EN, 1);
    OTP_CTRL->READY = OTP_CTRL_READY_READ_EN_MASK;
    OTP_CTRL->RD_FIFO_CTRL = OTP_CTRL_RD_FIFO_RCLR_MASK | OTP_CTRL_RD_FIFO_WCLR_MASK;
    OTP_CTRL->RD_FIFO_CTRL = 0x0;

    OTP_CTRL->PIN = FIELD_BUILD(OTP_CTRL_PIN_PTRIM, 1) | FIELD_BUILD(OTP_CTRL_PIN_PA, offset) |
                    FIELD_BUILD(OTP_CTRL_PIN_PCE, 1) | FIELD_BUILD(OTP_CTRL_PIN_PPROG, 0) |
                    FIELD_BUILD(OTP_CTRL_PIN_PAIO, 0) | FIELD_BUILD(OTP_CTRL_PIN_PAS, 0) |
                    FIELD_BUILD(OTP_CTRL_PIN_PTC, 0) | FIELD_BUILD(OTP_CTRL_PIN_PTR, 0) |
                    FIELD_BUILD(OTP_CTRL_PIN_PTM, 0);
    OTP_CTRL->SOFT_REQ = OTP_CTRL_SOFT_REQ_MASK;

    while (length - remain_length)
    {
        if ((OTP_CTRL->RD_FIFO_CTRL & OTP_CTRL_RD_FIFO_EMPTY_MASK) == 0)
        {
            uint32_t temp_data = OTP_CTRL->RD_DATA;
            *data++ = temp_data & 0xff;
            *data++ = (temp_data >> 8) & 0xff;
            *data++ = (temp_data >> 16) & 0xff;
            *data++ = (temp_data >> 24) & 0xff;
            length -= 4;
        }
    }

    if (remain_length)
    {
        while (OTP_CTRL->RD_FIFO_CTRL & OTP_CTRL_RD_FIFO_EMPTY_MASK) ;
        uint32_t temp_data = OTP_CTRL->RD_DATA;

        for (uint8_t i = 0; i < remain_length; i++)
        {
            data[i] = (temp_data >> (8 * i)) & 0xff;
        }
    }

    return HAL_OK;
}