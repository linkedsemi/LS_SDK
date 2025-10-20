#include "ls_hal_otbn_sha.h"

#define SM3_TEXT_LENTH           (1000)
#define SM3_DMEM_LENTH           (320)
extern const char sm3_text[SM3_TEXT_LENTH];
extern const char sm3_dmem[SM3_DMEM_LENTH];
#define SM3_DMEM_BLOCKNUM_OFFSET (0x00000bc0)
#define SM3_DMEM_BLOCKNUM_SIZE   (0x4)

#define SM3_OTBN_MAX_CHUNKS    (33)  // 33*64 = 2112 btye， otbn sm3 once process
#define SM3_DMEM_MSG_SIZE        (2112)
#define SM3_DMEM_MSG_OFFSET      (0x00000380)

#define SM3_DMEM_STATE_IV_OFFSET    (0x00000120)
#define SM3_DMEM_STATE_IV_SIZE      (0x20)

/* can be changed */
static const uint32_t state_init[8] = {
    0x7380166f, 0x4914b2b9, 0x172442d7, 0xda8a0600,
    0xa96f30bc, 0x163138aa, 0xe38dee4d, 0xb0fb0e4e
};
static uint32_t currnt_state[8];

static uint32_t totash_sm3_msg_total_len;
static uint32_t remain_len;
static uint8_t remain_data[SM3_BLOCK_SIZE];
void HAL_OTBN_SM3_Init()
{
    totash_sm3_msg_total_len = 0;
    remain_len = 0;
    // sha_idx = SM3_DMEM_MSG_OFFSET;
    HAL_OTBN_DMEM_Set(0, 0x0, OTBN_DMEM_SIZE);
    HAL_OTBN_IMEM_Write(0, (uint32_t *)sm3_text, SM3_TEXT_LENTH);
    HAL_OTBN_DMEM_Write(0, (uint32_t *)sm3_dmem, SM3_DMEM_LENTH);
    memcpy32(currnt_state,state_init,8);
}

static void sm3_msg_write(uint8_t *msg,uint32_t chunks_num)
{
    HAL_OTBN_DMEM_Write(SM3_DMEM_STATE_IV_OFFSET,currnt_state,SM3_DMEM_STATE_IV_SIZE);
    HAL_OTBN_DMEM_Write(SM3_DMEM_BLOCKNUM_OFFSET,&chunks_num,SM3_DMEM_BLOCKNUM_SIZE);
    HAL_OTBN_DMEM_Write(SM3_DMEM_MSG_OFFSET, (uint32_t *)msg, SM3_BLOCK_SIZE*chunks_num);
    HAL_OTBN_CMD_Write_Polling(HAL_OTBN_CMD_EXECUTE);
    HAL_OTBN_DMEM_Read(SM3_DMEM_STATE_IV_OFFSET,currnt_state,SM3_DMEM_STATE_IV_SIZE);
    (void)chunks_num;
}

void HAL_OTBN_SM3_Update(uint8_t *msg, uint32_t length)
{   
    uint32_t chunks_num = (remain_len+length)/SM3_BLOCK_SIZE;
    uint32_t remain = (remain_len+length)%SM3_BLOCK_SIZE;
    totash_sm3_msg_total_len += length;
    if (remain_len)
    {
        uint16_t copy_len = SM3_BLOCK_SIZE - remain_len;
        if ((length + remain_len) < SM3_BLOCK_SIZE)
        {
            memcpy(&remain_data[remain_len], msg, length);
            remain_len += length;
            return;
        }
        else
        {
            memcpy(&remain_data[remain_len], msg, copy_len);
            remain_len = 0;
            msg += copy_len;
            sm3_msg_write(remain_data,1);
            chunks_num -= 1;
        }
    }
    
    while(chunks_num)
    {
        if(chunks_num >= SM3_OTBN_MAX_CHUNKS)
        {
            sm3_msg_write(msg,SM3_OTBN_MAX_CHUNKS);
            chunks_num -= SM3_OTBN_MAX_CHUNKS;
            msg += SM3_BLOCK_SIZE*SM3_OTBN_MAX_CHUNKS;
        }else
        {
            sm3_msg_write(msg,chunks_num);
            msg += SM3_BLOCK_SIZE*chunks_num;
            chunks_num = 0;
        }
    }

    if(remain)
    {
        memcpy(remain_data,msg,remain);
        remain_len = remain;
    }
}

void HAL_OTBN_SM3_Final(uint8_t result[0x20])
{
    uint64_t bit_cnt = totash_sm3_msg_total_len * 8;

    remain_data[remain_len++] = 0x80;
    if (remain_len == SM3_BLOCK_SIZE)
    {
        sm3_msg_write(remain_data,1);
        remain_len = 0;
    }

    while (remain_len != 0x38)
    {
        remain_data[remain_len++] = 0x0;
        if (remain_len == SM3_BLOCK_SIZE)
        {
            sm3_msg_write(remain_data,1);
            remain_len = 0;
        }
    }

    for (uint8_t i = 0; i < 8; i++)
    {
        remain_data[0x3f - i] = (uint8_t)(bit_cnt >> (8 * i));
    }
    sm3_msg_write(remain_data,1);

    for (uint8_t i = 0; i < 8; i++)
    {
        *result++ = (uint8_t)(currnt_state[7 - i] >> 24);
        *result++ = (uint8_t)(currnt_state[7 - i] >> 16);
        *result++ = (uint8_t)(currnt_state[7 - i] >> 8);
        *result++ = (uint8_t)(currnt_state[7 - i] >> 0);
    }
    totash_sm3_msg_total_len = 0;
    remain_len = 0;
    // memcpy32(currnt_state,state_init,32);
    // HAL_OTBN_CMD_Write_Polling(HAL_OTBN_CMD_SEC_WIPE_DMEM);
}
