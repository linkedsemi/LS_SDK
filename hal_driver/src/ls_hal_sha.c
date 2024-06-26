#include <stdbool.h>
#include <string.h>
#include <stddef.h>
#include "ls_hal_sha.h"
#include "ls_msp_sha.h"
#include "field_manipulate.h"
#include "ls_dbg.h"
#include "compile_flag.h"
#define SHA_BLOCK_SIZE 64
#define SHA_MAX_BLOCK_NUM 16384
#define SHA_PADDING_MOD 56
#define SHA_DATA_LENGTH_SIZE 8
#define B 64
#define I_PAD 0x36
#define O_PAD 0x5C
#define SHA256_DIGEST_SIZE 32
#define SHA224_DIGEST_SIZE 28

struct SHA_CryptSector
{
    uint8_t     *index;
    uint8_t     *addr_head;
    uint8_t     *addr_tail;
} ;

static struct SHA_CryptSector Sector[SHA_SECTOR_NUM_MAX];
static uint32_t update_index;
static uint32_t rd_index;
static uint32_t sha_total_length;

static uint32_t sha_data_bits;
static uint32_t sha_remain_length;
static uint32_t *sha_rslt;
static uint16_t sha_padding_length;
static bool sha_padding_started;
HAL_StatusTypeDef HAL_LSSHA_Init(void)
{
    update_index = 0;
    rd_index = 0;
    sha_total_length = 0;
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

ROM_SYMBOL void calc_start(const uint8_t *data,uint32_t length)
{
    if (length != 0)
        HAL_LSSHA_SHA_Update((uint8_t *)data, length);

    sha_data_bits = sha_total_length * 8;     
    sha_remain_length = sha_total_length; 
    uint16_t block;
    if(sha_total_length % SHA_BLOCK_SIZE > SHA_PADDING_MOD - 1)
    {
        block = sha_total_length / SHA_BLOCK_SIZE + 2;
    }else
    {
        block = sha_total_length / SHA_BLOCK_SIZE + 1;
    }
    sha_padding_length = block * SHA_BLOCK_SIZE - sha_total_length - SHA_DATA_LENGTH_SIZE;
    sha_padding_started = false;
    LSSHA->SHA_CTRL |= FIELD_BUILD(SHA_SHA_LEN,block - 1);
    LSSHA->SHA_START = 1;
}

static uint8_t get_nextbyte()
{
    uint8_t data = *Sector[rd_index].index++; 
    
    if (Sector[rd_index].index == Sector[rd_index].addr_tail)
        rd_index++;

    return data;
}

static uint32_t get_uint32_t()
{
    uint8_t data[4];
    data[0] = get_nextbyte();
    data[1] = get_nextbyte();
    data[2] = get_nextbyte();
    data[3] = get_nextbyte();
    return data[3]<<24|data[2]<<16|data[1]<<8|data[0];
}

ROM_SYMBOL void sha_data_config()
{
    if(sha_remain_length>=SHA_BLOCK_SIZE)
    {
        uint8_t i;
        for(i=0;i<SHA_BLOCK_SIZE;i+=sizeof(uint32_t)) 
        {
            LSSHA->FIFO_DAT = get_uint32_t();
        }
        sha_remain_length -= SHA_BLOCK_SIZE;
    }else   
    {
        bool last = sha_padding_length<=SHA_PADDING_MOD;
        if(sha_padding_started==false)
        {
            while(sha_remain_length>=sizeof(uint32_t))
            {
                LSSHA->FIFO_DAT = get_uint32_t();
                sha_remain_length -= sizeof(uint32_t);
            }
            uint8_t byte[3];
            switch(sha_remain_length)
            {
            case 3:
                byte[0] = get_nextbyte();
                byte[1] = get_nextbyte();
                byte[2] = get_nextbyte();
                LSSHA->FIFO_DAT = 0x80<<24|byte[2]<<16|byte[1]<<8|byte[0];
                sha_padding_length -= 1;
            break;
            case 2:
                byte[0] = get_nextbyte();
                byte[1] = get_nextbyte();
                LSSHA->FIFO_DAT = 0x80<<16|byte[1]<<8|byte[0];
                sha_padding_length -= 2;
            break;
            case 1:
                byte[0] = get_nextbyte();
                LSSHA->FIFO_DAT = 0x80<<8|byte[0];
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

ROM_SYMBOL void rslt_copy()
{
    uint8_t i;
    uint8_t count = REG_FIELD_RD(LSSHA->SHA_CTRL,SHA_CALC_SHA224) != 1 ? SHA256_WORDS_NUM : SHA224_WORDS_NUM;
    for (i = 0; i < count; ++i)
    {
        uint32_t val = LSSHA->SHA_RSLT[i];
        sha_rslt[i] = val << 24 | (val << 8 & 0xff0000) | (val >> 8 & 0xff00) | val >> 24;
    }
    LSSHA->INTR_C = SHA_FSM_END_INTR_MASK;
    update_index = 0;
    rd_index = 0;
    sha_total_length = 0;
}

ROM_SYMBOL void sha256_config(const uint8_t *data,uint32_t length,uint32_t sha256[SHA256_WORDS_NUM])
{
    sha_rslt = sha256;
    LSSHA->SHA_CTRL = FIELD_BUILD(SHA_FST_DAT,1)|FIELD_BUILD(SHA_CALC_SHA224,0)|FIELD_BUILD(SHA_CALC_SM3,0);
    calc_start(data,length);
}

ROM_SYMBOL void sha224_config(const uint8_t *data,uint32_t length,uint32_t sha224[SHA224_WORDS_NUM])
{
    sha_rslt = sha224;
    LSSHA->SHA_CTRL = FIELD_BUILD(SHA_FST_DAT,1)|FIELD_BUILD(SHA_CALC_SHA224,1)|FIELD_BUILD(SHA_CALC_SM3,0);
    calc_start(data,length);
}

ROM_SYMBOL void sm3_config(const uint8_t *data,uint32_t length,uint32_t sm3[SM3_WORDS_NUM])
{
     sha_rslt = sm3;
    LSSHA->SHA_CTRL = FIELD_BUILD(SHA_FST_DAT,1)|FIELD_BUILD(SHA_CALC_SHA224,0)|FIELD_BUILD(SHA_CALC_SM3,1);
    calc_start(data,length);
}

ROM_SYMBOL HAL_StatusTypeDef HAL_LSSHA_SHA256(const uint8_t *data,uint32_t length,uint32_t sha256[SHA256_WORDS_NUM])
{
    LSSHA->INTR_M = 0;  
    sha256_config(data,length,sha256);
    do{
        sha_data_config();
    }while(sha_continue());
    rslt_copy();
    return HAL_OK;
}

ROM_SYMBOL HAL_StatusTypeDef HAL_LSSHA_SHA224(const uint8_t *data,uint32_t length,uint32_t sha224[SHA224_WORDS_NUM])
{
    LSSHA->INTR_M = 0;  
    sha224_config(data,length,sha224);
    do{
        sha_data_config();
    }while(sha_continue());
    rslt_copy();
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSSHA_SM3(const uint8_t *data,uint32_t length,uint32_t sm3[SM3_WORDS_NUM])
{
    LSSHA->INTR_M = 0;  
    sm3_config(data,length,sm3);
    do{
        sha_data_config();
    }while(sha_continue());
    rslt_copy();
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSSHA_SHA256_IT(const uint8_t *data,uint32_t length,uint32_t sha256[SHA256_WORDS_NUM])
{
    LSSHA->INTR_M = FIELD_BUILD(SHA_FSM_END_INTR,1) | FIELD_BUILD(SHA_FSM_EMPT_INTR,1);
    sha256_config(data,length,sha256);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSSHA_SHA224_IT(const uint8_t *data,uint32_t length,uint32_t sha224[SHA224_WORDS_NUM])
{
    LSSHA->INTR_M = FIELD_BUILD(SHA_FSM_END_INTR,1) | FIELD_BUILD(SHA_FSM_EMPT_INTR,1);
    sha224_config(data,length,sha224);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSSHA_SM3_IT(const uint8_t *data,uint32_t length,uint32_t sm3[SM3_WORDS_NUM])
{
    LSSHA->INTR_M = FIELD_BUILD(SHA_FSM_END_INTR,1) | FIELD_BUILD(SHA_FSM_EMPT_INTR,1);
    sm3_config(data,length,sm3);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSSHA_SHA_Update(uint8_t *data,uint32_t length)
{
    if (update_index == SHA_SECTOR_NUM_MAX)
        return HAL_ERROR;
    
    struct SHA_CryptSector *node = &Sector[update_index++];
    node->addr_head = data;
    node->addr_tail = data + length;
    node->index = data;
    sha_total_length += length;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSSHA_SHA256_Final(uint32_t sha256[SHA256_WORDS_NUM])
{
    LSSHA->INTR_M = 0;
    sha256_config(NULL, 0, sha256);
    do
    {
        sha_data_config();
    } while (sha_continue());
    rslt_copy();
    return HAL_OK;
}

HAL_StatusTypeDef HAL_LSSHA_SHA224_Final(uint32_t sha224[SHA224_WORDS_NUM])
{
    LSSHA->INTR_M = 0;
    sha224_config(NULL, 0, sha224);
    do
    {
        sha_data_config();
    } while (sha_continue());
    rslt_copy();
    return HAL_OK;
}

HAL_StatusTypeDef HAL_HMAC_SHA256(uint32_t out[SHA256_WORDS_NUM], uint8_t *data, uint32_t data_len, uint8_t *key, uint32_t key_len)
{
    uint32_t kh[SHA256_WORDS_NUM];

    /*
     * If the key length is bigger than the buffer size B, apply the hash
     * function to it first and use the result instead.
     */
    if (key_len > B)
    {
        HAL_LSSHA_SHA256(key, key_len, kh);
        key_len = SHA256_DIGEST_SIZE;
        key = (uint8_t *)kh;
    }

    /*
     * (1) append zeros to the end of K to create a B byte string
     *     (e.g., if K is of length 20 bytes and B=64, then K will be
     *     appended with 44 zero bytes 0x00)
     * (2) XOR (bitwise exclusive-OR) the B byte string computed in step
     *     (1) with ipad
     */
    uint8_t kx[B];
    for (uint32_t i = 0; i < key_len; i++)
        kx[i] = I_PAD ^ key[i];
    for (uint32_t i = key_len; i < B; i++)
        kx[i] = I_PAD ^ 0;

    /*
     * (3) append the stream of data 'text' to the B byte string resulting
     *     from step (2)
     * (4) apply H to the stream generated in step (3)
     */
    HAL_LSSHA_SHA_Update(kx, B);
    HAL_LSSHA_SHA_Update(data, data_len);
    HAL_LSSHA_SHA256_Final(out);

    /*
     * (5) XOR (bitwise exclusive-OR) the B byte string computed in
     *     step (1) with opad
     *
     * NOTE: The "kx" variable is reused.
     */
    for (size_t i = 0; i < key_len; i++)
        kx[i] = O_PAD ^ key[i];
    for (size_t i = key_len; i < B; i++)
        kx[i] = O_PAD ^ 0;

    /*
     * (6) append the H result from step (4) to the B byte string
     *     resulting from step (5)
     * (7) apply H to the stream generated in step (6) and output
     *     the result
     */
    HAL_LSSHA_SHA_Update(kx, B);
    HAL_LSSHA_SHA_Update((uint8_t *)out, SHA256_DIGEST_SIZE);
    HAL_LSSHA_SHA256_Final(out);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_HMAC_SHA224(uint32_t out[SHA224_WORDS_NUM], uint8_t *data, uint32_t data_len, uint8_t *key, uint32_t key_len)
{
    uint32_t kh[SHA224_WORDS_NUM];

    if (key_len > B)
    {
        HAL_LSSHA_SHA224(key, key_len, kh);
        key_len = SHA224_DIGEST_SIZE;
        key = (uint8_t *)kh;
    }

    uint8_t kx[B];
    for (uint32_t i = 0; i < key_len; i++)
        kx[i] = I_PAD ^ key[i];
    for (uint32_t i = key_len; i < B; i++)
        kx[i] = I_PAD ^ 0;

    HAL_LSSHA_SHA_Update(kx, B);
    HAL_LSSHA_SHA_Update(data, data_len);
    HAL_LSSHA_SHA224_Final(out);

    for (size_t i = 0; i < key_len; i++)
        kx[i] = O_PAD ^ key[i];
    for (size_t i = key_len; i < B; i++)
        kx[i] = O_PAD ^ 0;

    HAL_LSSHA_SHA_Update(kx, B);
    HAL_LSSHA_SHA_Update((uint8_t *)out, SHA224_DIGEST_SIZE);
    HAL_LSSHA_SHA224_Final(out);
    return HAL_OK;
}

__attribute__((weak)) void HAL_LSSHA_SHA256_Complete_Callback(void){}
__attribute__((weak)) void HAL_LSSHA_SHA224_Complete_Callback(void){}
__attribute__((weak)) void HAL_LSSHA_SM3_Complete_Callback(void){}

void LSSHA_IRQHandler(void)
{
    uint8_t irq = LSSHA->INTR_S;
    if(irq&SHA_FSM_EMPT_INTR_MASK) 
    {
        sha_data_config();
    }
    if(irq&SHA_FSM_END_INTR_MASK) 
    {
        rslt_copy();
        if(REG_FIELD_RD(LSSHA->SHA_CTRL,SHA_CALC_SHA224) == 1)
        {
            HAL_LSSHA_SHA224_Complete_Callback();
        }    
        else if(REG_FIELD_RD(LSSHA->SHA_CTRL, SHA_CALC_SM3) == 1) 
        {
            HAL_LSSHA_SM3_Complete_Callback();
        }
        else 
        {
            HAL_LSSHA_SHA256_Complete_Callback();
        }
    }
}