#include "ls_hal_sha512.h"
#include "ls_msp_sha512.h"
#include "field_manipulate.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "common.h"
#include "log.h"

static uint32_t buffer[0x20];
static uint32_t total_cnt;
static uint32_t buffer_idx;
static bool isFirst;

HAL_StatusTypeDef HAL_SHA512_Init(void)
{
    HAL_SHA512_MSP_Init();
    SHA512->INTR_CLR = 0x1;
    SHA512->INTR_MSK = 0x0;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_SHA512_DeInit(void)
{
    HAL_SHA512_MSP_DeInit();
    return HAL_OK;
}
#include "ls_soc_gpio.h"

static void block_calculate(uint32_t addr, uint32_t block_number)
{
    LOG_HEX((uint8_t *)addr, block_number * 0x80);
    while ((SHA512->STATUS & 0x1) != 0x1) ;
    SHA512->CTRL = (block_number - 1) << 16;
    SHA512->ADDR = addr;

    if (isFirst)
    {
        SHA512->CTRL |= 0xF;
        isFirst = false;
    }
    else
    {
        SHA512->CTRL |= 0xE;
    }

    while ((SHA512->STATUS & 0x8) != 0x8);
}

void HAL_SHA512_SHA512_Init()
{
    isFirst = true;
}

void HAL_SHA512_SHA512_Update(uint32_t *addr, uint32_t length)
{   
    uint8_t *msg = (uint8_t *)addr;
    total_cnt += length;

    if (buffer_idx)
    {
        if ((length + buffer_idx) < SHA512_BLOCK_SIZE)
        {
            memcpy(&buffer[buffer_idx], addr, length);
            buffer_idx += length;
            return;
        }
        uint32_t wr_len = SHA512_BLOCK_SIZE - buffer_idx;
        memcpy(&buffer[buffer_idx], msg, wr_len);
        block_calculate((uint32_t)buffer, 1);
        buffer_idx = 0;
        length -= wr_len;
        msg += wr_len;
    }

    uint32_t block_number = length / SHA512_BLOCK_SIZE;
    if (block_number)
        block_calculate((uint32_t)msg, block_number);
    
    if (length % SHA512_BLOCK_SIZE)
    {
        memcpy(&buffer[buffer_idx], msg + (block_number * SHA512_BLOCK_SIZE), length % SHA512_BLOCK_SIZE);
        buffer_idx = length % SHA512_BLOCK_SIZE;
    }
}

void HAL_SHA512_SHA512_Final(uint8_t *digest)
{
    uint8_t *p_buffer=(uint8_t *)buffer;
    uint64_t bit_cnt = total_cnt * 8;

    p_buffer[buffer_idx++] = 0x80;
    if (buffer_idx == SHA512_BLOCK_SIZE)
    {
        block_calculate((uint32_t)buffer, 1);
        buffer_idx = 0;
    }

    while (buffer_idx != (SHA512_BLOCK_SIZE - 0x10))
    {
        p_buffer[buffer_idx++] = 0x0;
        if (buffer_idx == SHA512_BLOCK_SIZE)
        {
            block_calculate((uint32_t)buffer, 1);
            buffer_idx = 0;
        }
    }
    memset(&p_buffer[buffer_idx], 0x0, 8);
    buffer_idx += 8;

    for (uint8_t i = 0; i < 8; i++)
    {
        p_buffer[buffer_idx + (7 - i)] = (uint8_t)(bit_cnt >> (8 * i));
    }
    buffer_idx += 8;
    block_calculate((uint32_t)buffer, 1);

    for (uint8_t j = 0; j < 16; j++)
    {
        uint32_t in = SHA512->DIGEST[15 - j];
        *digest++ = in >> 24;
        *digest++ = in >> 16;
        *digest++ = in >> 8;
        *digest++ = in;
    }
}

void SHA512_IRQHandler()
{
    SHA512->INTR_CLR = 0x1;
}