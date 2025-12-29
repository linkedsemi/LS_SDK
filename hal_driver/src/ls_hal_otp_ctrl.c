#include "ls_hal_otp_ctrl.h"
#include "ls_msp_otp_ctrl.h"
#include "field_manipulate.h"
#include "platform.h"
#include <string.h>

#define ONEBIT_BYTES            (0x20)
#define OTP_BYTE_DEFAULT_VALUE  (0xFF)
#define SINGLE_WRITE_MAX_LENGTH (0x20)

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

    DELAY_US(50);
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

static void otp_single_wirte(uint32_t *buffer, uint32_t offset, uint32_t length, bool pas)
{
    uint32_t idx = 0;

    OTP_CTRL->SOFT_REQ = 0;
    OTP_CTRL->INTR_MSK = 0;
    OTP_CTRL->INTR_CLR = OTP_CTRL_INTR_FINISH_MASK;
    REG_FIELD_WR(OTP_CTRL->CTRL, OTP_CTRL_CTRL_1LEN_MODE, 0);
    OTP_CTRL->WR_LEN = FIELD_BUILD(OTP_CTRL_WR_LEN, length - 1) |
                       FIELD_BUILD(OTP_CTRL_WFIFO_FULL_EN, 1);
    OTP_CTRL->READY = OTP_CTRL_READY_WRITE_EN_MASK;
    OTP_CTRL->WR_FIFO_CTRL = OTP_CTRL_WR_FIFO_RCLR_MASK | OTP_CTRL_WR_FIFO_WCLR_MASK;
    DELAY_US(1);
    OTP_CTRL->WR_FIFO_CTRL = 0x0;
    DELAY_US(1);

    OTP_CTRL->PIN = FIELD_BUILD(OTP_CTRL_PIN_PTRIM, 1) | FIELD_BUILD(OTP_CTRL_PIN_PA, offset) |
                    FIELD_BUILD(OTP_CTRL_PIN_PCE, 1) | FIELD_BUILD(OTP_CTRL_PIN_PPROG, 1) |
                    FIELD_BUILD(OTP_CTRL_PIN_PAIO, 0) | FIELD_BUILD(OTP_CTRL_PIN_PAS, pas) |
                    FIELD_BUILD(OTP_CTRL_PIN_PTC, 0) | FIELD_BUILD(OTP_CTRL_PIN_PTR, 0) |
                    FIELD_BUILD(OTP_CTRL_PIN_PTM, 2);
    OTP_CTRL->SOFT_REQ = OTP_CTRL_SOFT_REQ_MASK;

    while (length)
    {
        if ((OTP_CTRL->WR_FIFO_CTRL & OTP_CTRL_WR_FIFO_FULL_MASK) == 0)
        {
            OTP_CTRL->WR_DATA = buffer[idx++];
            length -= (length < 4) ? length : 4;
        }
    }

    while (REG_FIELD_RD(OTP_CTRL->INTR_RAW, OTP_CTRL_INTR_FINISH) == 0x0) ; /* wait program done */
}

static bool otp_block_write(uint32_t offset, uint8_t *data, uint32_t length)
{
    uint32_t buffer[SINGLE_WRITE_MAX_LENGTH];
    uint8_t *p_buffer = (uint8_t *)buffer;

    if (((offset + length) > OTP_MEM_TOTAL_BYTES) || (length > SINGLE_WRITE_MAX_LENGTH))
        return false;

    if (HAL_OTP_Read(offset, p_buffer, length) != HAL_OK)
        return false;

    for (uint8_t i = 0; i < length; i++)
    {
        p_buffer[i] = data[i] | ~p_buffer[i];
    }

    otp_single_wirte(buffer, offset, length, 0);// pas low
    otp_single_wirte(buffer, offset, length, 1);// pas high

    return true;
}

HAL_StatusTypeDef HAL_OTP_Write(uint32_t offset, uint8_t *data, uint32_t length)
{
    otp_check_power_ready();

    for (uint32_t i = 0; i < length / SINGLE_WRITE_MAX_LENGTH; i++)
    {
        if (!otp_block_write(offset, data, SINGLE_WRITE_MAX_LENGTH))
            return HAL_ERROR;
        offset += SINGLE_WRITE_MAX_LENGTH;
        data += SINGLE_WRITE_MAX_LENGTH;
    }

    if (length % SINGLE_WRITE_MAX_LENGTH)
    {
        if (!otp_block_write(offset, data, length % SINGLE_WRITE_MAX_LENGTH))
            return HAL_ERROR;
    }

    return HAL_OK;
}

static void otp_read_en_check(uint32_t offset, uint8_t *data, uint32_t length)
{
    uint32_t bit_start = offset / ONEBIT_BYTES;
    uint32_t bit_end = (offset + length - 1) / ONEBIT_BYTES;

    for (uint32_t i = bit_start; i <= bit_end; i++)
    {
        if ((OTP_CTRL->RD_FORBIDDEN_ADDR[i / 0x20] >> (i % 0x20)) & 0x1)
        {
             //Calculate the address range of the current protection block
            uint32_t block_start = i * ONEBIT_BYTES;
            uint32_t block_end = block_start + ONEBIT_BYTES - 1;

            //Calculate the intersection of the query and the request scope
            uint32_t request_end = offset + length - 1;
            uint32_t fill_start = (block_start > offset) ? block_start : offset;
            uint32_t fill_end = (block_end < request_end) ? block_end : request_end;

            if (fill_end >= fill_start) {
                //The actual length that needs to be filled
                uint32_t fill_length = fill_end - fill_start + 1;
                uint32_t data_offset = fill_start - offset;

                //Fill only within the valid range
                memset(data + data_offset, OTP_BYTE_DEFAULT_VALUE, fill_length);
            }

        }
    }
}

HAL_StatusTypeDef HAL_OTP_Read(uint32_t offset, uint8_t *data, uint32_t length)
{
    if (((offset + length) > OTP_MEM_TOTAL_BYTES) || (length == 0))
        return HAL_INVALIAD_PARAM;

    uint32_t remain_length = length & 0x3;
    uint32_t len = (length + 0x3) & ~0x3;
    uint32_t count = length;
    uint8_t *out = data;

    otp_check_power_ready();

    OTP_CTRL->SOFT_REQ = 0;
    OTP_CTRL->INTR_MSK = 0;
    OTP_CTRL->INTR_CLR = OTP_CTRL_INTR_FINISH_MASK;
    REG_FIELD_WR(OTP_CTRL->CTRL, OTP_CTRL_CTRL_1LEN_MODE, 0);
    OTP_CTRL->RD_LEN = FIELD_BUILD(OTP_CTRL_RD_LEN, len - 1) |
                       FIELD_BUILD(OTP_CTRL_RFIFO_FULL_EN, 1);
    OTP_CTRL->READY = OTP_CTRL_READY_READ_EN_MASK;
    OTP_CTRL->RD_FIFO_CTRL = OTP_CTRL_RD_FIFO_RCLR_MASK | OTP_CTRL_RD_FIFO_WCLR_MASK;
    DELAY_US(1);
    OTP_CTRL->RD_FIFO_CTRL = 0x0;
    DELAY_US(1);

    OTP_CTRL->PIN = FIELD_BUILD(OTP_CTRL_PIN_PTRIM, 1) | FIELD_BUILD(OTP_CTRL_PIN_PA, offset) |
                    FIELD_BUILD(OTP_CTRL_PIN_PCE, 1) | FIELD_BUILD(OTP_CTRL_PIN_PPROG, 0) |
                    FIELD_BUILD(OTP_CTRL_PIN_PAIO, 0) | FIELD_BUILD(OTP_CTRL_PIN_PAS, 0) |
                    FIELD_BUILD(OTP_CTRL_PIN_PTC, 0) | FIELD_BUILD(OTP_CTRL_PIN_PTR, 0) |
                    FIELD_BUILD(OTP_CTRL_PIN_PTM, 0);
    OTP_CTRL->SOFT_REQ = OTP_CTRL_SOFT_REQ_MASK;

    while (count - remain_length)
    {
        if ((OTP_CTRL->RD_FIFO_CTRL & OTP_CTRL_RD_FIFO_EMPTY_MASK) == 0)
        {
            uint32_t temp_data = OTP_CTRL->RD_DATA;
            *out++ = temp_data & 0xff;
            *out++ = (temp_data >> 8) & 0xff;
            *out++ = (temp_data >> 16) & 0xff;
            *out++ = (temp_data >> 24) & 0xff;
            count -= 4;
        }
    }

    if (remain_length)
    {
        while (OTP_CTRL->RD_FIFO_CTRL & OTP_CTRL_RD_FIFO_EMPTY_MASK) ;
        uint32_t temp_data = OTP_CTRL->RD_DATA;

        for (uint8_t i = 0; i < remain_length; i++)
        {
            out[i] = (temp_data >> (8 * i)) & 0xff;
        }
    }

    otp_read_en_check(offset, data, length);

    return HAL_OK;
}