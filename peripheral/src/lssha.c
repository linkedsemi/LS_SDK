#include <stdbool.h>
#include "lssha.h"
#include "sha_msp.h"
#include "field_manipulate.h"
#include "ls_dbg.h"
#define SHA_BLOCK_SIZE 64
#define SHA_MAX_BLOCK_NUM 16384
#define SHA_PADDING_MOD 56
#define SHA_DATA_LENGTH_SIZE 8
static const uint8_t *sha_data_ptr;
static uint32_t sha_data_bits;
static uint32_t sha_remain_length;
static uint32_t *sha_rslt;
static uint16_t sha_padding_length;
static bool sha_padding_started;
HAL_StatusTypeDef HAL_LSSHA_Init(void)
{
    HAL_LSSHA_MSP_Init();
    HAL_LSSHA_MSP_Busy_Set();
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSSHA_DeInit(void)
{
    HAL_LSSHA_MSP_Idle_Set();
    HAL_LSSHA_MSP_DeInit();
    return HAL_OK;
}

static void sha256_start(const uint8_t *data,uint32_t length,uint32_t sha256[SHA256_WORDS_NUM])
{
    sha_data_ptr = data;
    sha_data_bits = length*8;
    sha_remain_length = length;
    sha_rslt = sha256;
    uint16_t block;
    if(length % SHA_BLOCK_SIZE > SHA_PADDING_MOD - 1)
    {
        block = length / SHA_BLOCK_SIZE + 2;
    }else
    {
        block = length / SHA_BLOCK_SIZE + 1;
    }
    sha_padding_length = block * SHA_BLOCK_SIZE - length - SHA_DATA_LENGTH_SIZE;
    sha_padding_started = false;
    LSSHA->SHA_CTRL = FIELD_BUILD(SHA_FST_DAT,1)|FIELD_BUILD(SHA_CALC_SHA224,0)|FIELD_BUILD(SHA_CALC_SM3,0)|FIELD_BUILD(SHA_SHA_LEN,block - 1);
    LSSHA->SHA_START = 1;
}

static uint32_t get_uint32_t(const uint8_t *data)
{
    return data[3]<<24|data[2]<<16|data[1]<<8|data[0];
}

static void sha_data_config()
{
    if(sha_remain_length>=SHA_BLOCK_SIZE)
    {
        uint8_t i;
        for(i=0;i<SHA_BLOCK_SIZE;i+=sizeof(uint32_t))
        {
            LSSHA->FIFO_DAT = get_uint32_t(sha_data_ptr);
            sha_data_ptr += sizeof(uint32_t);
        }
        sha_remain_length -= SHA_BLOCK_SIZE;
    }else
    {
        bool last = sha_padding_length<=SHA_PADDING_MOD;
        if(sha_padding_started==false)
        {
            while(sha_remain_length>=sizeof(uint32_t))
            {
                LSSHA->FIFO_DAT = get_uint32_t(sha_data_ptr);
                sha_data_ptr += sizeof(uint32_t);
                sha_remain_length -= sizeof(uint32_t);
            }
            switch(sha_remain_length)
            {
            case 3:
                LSSHA->FIFO_DAT = 0x80<<24|sha_data_ptr[2]<<16|sha_data_ptr[1]<<8|sha_data_ptr[0];
                sha_padding_length -= 1;
            break;
            case 2:
                LSSHA->FIFO_DAT = 0x80<<16|sha_data_ptr[1]<<8|sha_data_ptr[0];
                sha_padding_length -= 2;
            break;
            case 1:
                LSSHA->FIFO_DAT = 0x80<<8|sha_data_ptr[0];
                sha_padding_length -= 3;
            break;
            case 0:
                LSSHA->FIFO_DAT = 0x80;
                sha_padding_length -= 4;
            break;
            }
            sha_remain_length = 0;
            sha_padding_started = true;
        }
        LS_ASSERT(sha_padding_length%4==0);
        if(last)
        {
            while(sha_padding_length)
            {
                LSSHA->FIFO_DAT = 0;
                sha_padding_length -= sizeof(uint32_t);
            }
            if(sha_padding_length==0)
            {
                LSSHA->FIFO_DAT = 0;
                LSSHA->FIFO_DAT = (sha_data_bits&0xff)<<24|(sha_data_bits&0xff00)<<8
                    |(sha_data_bits&0xff0000)>>8|(sha_data_bits&0xff000000)>>24;
            }
        }else
        {
            LS_ASSERT(sha_padding_length%sizeof(uint32_t)==0);
            LS_ASSERT(sha_padding_length <= SHA_BLOCK_SIZE - sizeof(uint32_t));
            if(sha_padding_length == SHA_BLOCK_SIZE - sizeof(uint32_t))
            {
                LSSHA->FIFO_DAT = 0;
                sha_padding_length = SHA_PADDING_MOD;
            }
        }
    }
    LSSHA->INTR_C = SHA_FSM_EMPT_INTR_MASK;
}

static bool sha_continue()
{
    while(1)
    {
        uint8_t state = LSSHA->INTR_R;
        if(state&SHA_FSM_EMPT_INTR_MASK)
        {
            return true;
        }
        if(state&SHA_FSM_END_INTR_MASK)
        {
            return false;
        }
    }
}

static void sha_rslt_copy()
{
    uint8_t i;
    for(i=0;i<8;++i)
    {
        uint32_t val = LSSHA->SHA_RSLT[i];
        sha_rslt[i] = val<<24| (val<<8&0xff0000) | (val>>8&0xff00) | val>>24;
    }
    LSSHA->INTR_C = SHA_FSM_END_INTR_MASK;
}

HAL_StatusTypeDef HAL_LSSHA_SHA256(const uint8_t *data,uint32_t length,uint32_t sha256[SHA256_WORDS_NUM])
{
    LSSHA->INTR_M = 0;
    sha256_start(data,length,sha256);
    do{
        sha_data_config();
    }while(sha_continue());
    sha_rslt_copy();
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSSHA_SHA256_IT(const uint8_t *data,uint32_t length,uint32_t sha256[SHA256_WORDS_NUM])
{
    LSSHA->INTR_M = FIELD_BUILD(SHA_FSM_END_INTR,1) | FIELD_BUILD(SHA_FSM_END_INTR,1);
    sha256_start(data,length,sha256);
    return HAL_OK;
}

__attribute__((weak)) void HAL_LSSHA_SHA256_Complete_Callback(void){}

void LSSHA_IRQHandler(void)
{
    uint8_t irq = LSSHA->INTR_S;
    if(irq&SHA_FSM_EMPT_INTR_MASK)
    {
        sha_data_config();
    }
    if(irq&SHA_FSM_END_INTR_MASK)
    {
        sha_rslt_copy();
        HAL_LSSHA_SHA256_Complete_Callback();
    }
}