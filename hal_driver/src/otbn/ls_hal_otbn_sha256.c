#include "ls_hal_otbn_sha.h"

#define SHA256_IMEM_BLOCKNUM_OFFSET (0x0)
#define SHA256_IMEM_BLOCKNUM_DATA   (0x00000f13)

#define SHA256_DMEM_STATE_OFFSET    (0x0)
#define SHA256_DMEM_STATE_SIZE          (0x20)
#define SHA256_DMEM_MASK_OFFSET     (0x20)
#define SHA256_DMEM_MASK_SIZE           (0x20)
#define SHA256_DMEM_K_OFFSET        (0x40)
#define SHA256_DMEM_K_SIZE              (0x100)
#define SHA256_DMEM_MSG_OFFSET      (0x140)
#define SHA256_DMEM_MSG_SIZE            (0x800)

#define SHA256_MSG_BLOCK_SIZE       (0x40)
#define SHA256_TEXT_LENTH (540)
extern const char sha256_text[SHA256_TEXT_LENTH];

static uint32_t state_init[8] = {
    0x5be0cd19, 0x1f83d9ab, 0x9b05688c, 0x510e527f,
    0xa54ff53a, 0x3c6ef372, 0xbb67ae85, 0x6a09e667};

static uint32_t bswap32_mask[8] = {
    0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff,
    0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff};

static const uint32_t K[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};


static void Sha256_BlockNumber_Update(uint16_t number)
{
    uint32_t insruct = SHA256_IMEM_BLOCKNUM_DATA | ((number << 20)&0xfff00000);
    HAL_OTBN_IMEM_Write(SHA256_IMEM_BLOCKNUM_OFFSET, &insruct, sizeof(uint32_t));
}

static uint32_t index;
static uint32_t total_cnt;
static uint32_t remain_len;
static uint8_t remain_data[SHA256_MSG_BLOCK_SIZE];
void HAL_OTBN_SHA256_Init()
{
    total_cnt = 0;
    remain_len = 0;
    index = SHA256_DMEM_MSG_OFFSET;
    HAL_OTBN_IMEM_Write(0, (uint32_t *)sha256_text, SHA256_TEXT_LENTH);
    HAL_OTBN_DMEM_Write(SHA256_DMEM_STATE_OFFSET, state_init, SHA256_DMEM_STATE_SIZE);
    HAL_OTBN_DMEM_Write(SHA256_DMEM_MASK_OFFSET, bswap32_mask, SHA256_DMEM_MASK_SIZE);
    HAL_OTBN_DMEM_Write(SHA256_DMEM_K_OFFSET, (uint32_t *)K, SHA256_DMEM_K_SIZE);
}

static void sha256_msg_write(uint8_t *msg)
{
    HAL_OTBN_DMEM_Write(index, (uint32_t *)msg, SHA256_MSG_BLOCK_SIZE);
    index += SHA256_MSG_BLOCK_SIZE;
    if (index == (SHA256_DMEM_MSG_SIZE + SHA256_DMEM_MSG_OFFSET))
    {
        HAL_OTBN_CMD_Write_Polling(HAL_OTBN_CMD_EXECUTE);
        index = SHA256_DMEM_MSG_OFFSET;
    }
}

void HAL_OTBN_SHA256_Update(uint8_t *msg, uint32_t length)
{   
    total_cnt += length;
    if (remain_len)
    {
        if ((length + remain_len) < SHA256_MSG_BLOCK_SIZE)
        {
            memcpy(&remain_data[remain_len], msg, length);
            remain_len += length;
            return;
        }
        uint32_t wr_len = SHA256_MSG_BLOCK_SIZE - remain_len;
        memcpy(&remain_data[remain_len], msg, wr_len);
        sha256_msg_write(remain_data);
        remain_len = 0;
        length -= wr_len;
        msg += wr_len;
    }

    for (uint32_t i = 0; i < (length / SHA256_MSG_BLOCK_SIZE); i++)
    {
        sha256_msg_write(msg);
        msg += SHA256_MSG_BLOCK_SIZE;
    }
    
    if (length % SHA256_MSG_BLOCK_SIZE)
    {
        memcpy(&remain_data[remain_len], msg, length % SHA256_MSG_BLOCK_SIZE);
        remain_len = length % SHA256_MSG_BLOCK_SIZE;
    }
}

void HAL_OTBN_SHA256_Final(uint8_t result[0x20])
{
    uint64_t bit_cnt = total_cnt * 8;

    remain_data[remain_len++] = 0x80;
    if (remain_len == SHA256_MSG_BLOCK_SIZE)
    {
        sha256_msg_write(remain_data);
        remain_len = 0;
    }

    while (remain_len != 0x38)
    {
        remain_data[remain_len++] = 0x0;
        if (remain_len == SHA256_MSG_BLOCK_SIZE)
        {
            sha256_msg_write(remain_data);
            remain_len = 0;
        }
    }

    for (uint8_t i = 0; i < 8; i++)
    {
        remain_data[0x3f - i] = (uint8_t)(bit_cnt >> (8 * i));
    }
    HAL_OTBN_DMEM_Write(index, (uint32_t *)remain_data, SHA256_MSG_BLOCK_SIZE);
    index += SHA256_MSG_BLOCK_SIZE;
    Sha256_BlockNumber_Update((index - SHA256_DMEM_MSG_OFFSET) / SHA256_MSG_BLOCK_SIZE);
    HAL_OTBN_CMD_Write_Polling(HAL_OTBN_CMD_EXECUTE);

    uint32_t rs[8];
    HAL_OTBN_DMEM_Read(SHA256_DMEM_STATE_OFFSET, rs, SHA256_DMEM_STATE_SIZE);
    for (uint8_t i = 0; i < 8; i++)
    {
        *result++ = (uint8_t)(rs[7 - i] >> 24);
        *result++ = (uint8_t)(rs[7 - i] >> 16);
        *result++ = (uint8_t)(rs[7 - i] >> 8);
        *result++ = (uint8_t)(rs[7 - i] >> 0);
    }
    HAL_OTBN_CMD_Write_Polling(HAL_OTBN_CMD_SEC_WIPE_DMEM);
}

