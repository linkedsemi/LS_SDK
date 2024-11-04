#include "ls_hal_otbn_sha.h"

#define SHA512_TEXT_LENTH           (1588)
extern const char sha512_text[SHA512_TEXT_LENTH];

#define SHA384_DMEM_STATE_OFFSET        (0x0)
#define SHA384_DMEM_STATE_SIZE              (0x100)
#define SHA384_DMEM_MSG_OFFSET          (0x100)
#define SHA384_DMEM_MSG_SIZE                (0x800)
#define SHA384_DMEM_N_CHUNKS_OFFSET     (0x900)
#define SHA384_DMEM_PTR_STATE_OFFSET    (0x904)
#define SHA384_DMEM_PTR_MSG_OFFSET      (0x908)
#define SHA384_DMEM_K_OFFSET            (0x920)
#define SHA384_DMEM_K_SIZE                  (0x280)

#define SHA384_MSG_BLOCK_SIZE       (0x80)

static uint32_t index;
static uint32_t total_cnt;
static uint32_t remain_len;
static uint8_t remain_data[SHA384_MSG_BLOCK_SIZE];

static uint64_t state_init[] = {
    0xcbbb9d5dc1059ed8, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
    0x629a292a367cd507, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
    0x9159015a3070dd17, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
    0x152fecd8f70e5939, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
    0x67332667ffc00b31, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
    0x8eb44a8768581511, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
    0xdb0c2e0d64f98fa7, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
    0x47b5481dbefa4fa4, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,};

static uint64_t K[] = {
    0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
    0x3956c25bf348b538, 0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
    0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
    0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 0xc19bf174cf692694,
    0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
    0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
    0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4,
    0xc6e00bf33da88fc2, 0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70,
    0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
    0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
    0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30,
    0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
    0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
    0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
    0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
    0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b,
    0xca273eceea26619c, 0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
    0x06f067aa72176fba, 0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
    0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
    0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817};

static void SHA384_BlockNumber_Update(uint32_t number)
{
    uint32_t n_checks = number;
    HAL_OTBN_DMEM_Write(SHA384_DMEM_N_CHUNKS_OFFSET, &n_checks, sizeof(uint32_t));
}

void HAL_OTBN_SHA384_Init()
{
    total_cnt = 0;
    remain_len = 0;
    index = SHA384_DMEM_MSG_OFFSET;
    uint32_t state_ptr = SHA384_DMEM_STATE_OFFSET;
    uint32_t msg_ptr = SHA384_DMEM_MSG_OFFSET;
    HAL_OTBN_DMEM_Set(0x0, 0x0, OTBN_DMEM_SIZE);
    HAL_OTBN_IMEM_Write(0, (uint32_t *)sha512_text, SHA512_TEXT_LENTH);
    HAL_OTBN_DMEM_Write(SHA384_DMEM_STATE_OFFSET, (uint32_t *)state_init, SHA384_DMEM_STATE_SIZE);
    HAL_OTBN_DMEM_Write(SHA384_DMEM_K_OFFSET, (uint32_t *)K, SHA384_DMEM_K_SIZE);
    HAL_OTBN_DMEM_Write(SHA384_DMEM_PTR_STATE_OFFSET, &state_ptr, sizeof(uint32_t));
    HAL_OTBN_DMEM_Write(SHA384_DMEM_PTR_MSG_OFFSET, &msg_ptr, sizeof(uint32_t));
    SHA384_BlockNumber_Update(0x10);
}

static void SHA384_msg_write(uint8_t *msg)
{
    uint8_t dword[8];
    uint64_t sha384_buffer[0x10];
    for (uint8_t i = 0; i < 0x10; i++)
    {
        dword[7] = *msg++;
        dword[6] = *msg++;
        dword[5] = *msg++;
        dword[4] = *msg++;
        dword[3] = *msg++;
        dword[2] = *msg++;
        dword[1] = *msg++;
        dword[0] = *msg++;
        sha384_buffer[i] = *(uint64_t *)dword;
    }
    HAL_OTBN_DMEM_Write(index, (uint32_t *)sha384_buffer, SHA384_MSG_BLOCK_SIZE);
    index += SHA384_MSG_BLOCK_SIZE;
    if (index == (SHA384_DMEM_MSG_SIZE + SHA384_DMEM_MSG_OFFSET))
    {
        HAL_OTBN_CMD_Write_Polling(HAL_OTBN_CMD_EXECUTE);
        index = SHA384_DMEM_MSG_OFFSET;
    }
}

void HAL_OTBN_SHA384_Update(uint8_t *msg, uint32_t length)
{   
    total_cnt += length;
    if (remain_len)
    {
        if ((length + remain_len) < SHA384_MSG_BLOCK_SIZE)
        {
            memcpy(&remain_data[remain_len], msg, length);
            remain_len += length;
            return;
        }
        uint32_t wr_len = SHA384_MSG_BLOCK_SIZE - remain_len;
        memcpy(&remain_data[remain_len], msg, wr_len);
        SHA384_msg_write(remain_data);
        remain_len = 0;
        length -= wr_len;
        msg += wr_len;
    }

    for (uint32_t i = 0; i < (length / SHA384_MSG_BLOCK_SIZE); i++)
    {
        SHA384_msg_write(msg);
        msg += SHA384_MSG_BLOCK_SIZE;
    }
    
    if (length % SHA384_MSG_BLOCK_SIZE)
    {
        memcpy(&remain_data[remain_len], msg, length % SHA384_MSG_BLOCK_SIZE);
        remain_len = length % SHA384_MSG_BLOCK_SIZE;
    }
}

void HAL_OTBN_SHA384_Final(uint8_t result[SHA384_RESULT_SIZE])
{
    uint64_t bit_cnt = total_cnt * 8;

    remain_data[remain_len++] = 0x80;
    if (remain_len == SHA384_MSG_BLOCK_SIZE)
    {
        SHA384_msg_write(remain_data);
        remain_len = 0;
    }

    while (remain_len != (SHA384_MSG_BLOCK_SIZE - 16))
    {
        remain_data[remain_len++] = 0x0;
        if (remain_len == SHA384_MSG_BLOCK_SIZE)
        {
            SHA384_msg_write(remain_data);
            remain_len = 0;
        }
    }
    memset(&remain_data[remain_len], 0x0, 0x8);
    remain_len += 8;

    for (uint8_t i = 0; i < 8; i++)
    {
        remain_data[SHA384_MSG_BLOCK_SIZE - 1 - i] = (uint8_t)(bit_cnt >> (8 * i));
    }
    SHA384_msg_write((uint8_t *)remain_data);
    SHA384_BlockNumber_Update((index - SHA384_DMEM_MSG_OFFSET) / SHA384_MSG_BLOCK_SIZE);
    HAL_OTBN_CMD_Write_Polling(HAL_OTBN_CMD_EXECUTE);

    uint64_t rs;
    for (uint8_t i = 0; i < 6; i++)
    {
        HAL_OTBN_DMEM_Read(SHA384_DMEM_STATE_OFFSET + i * 0x20, (uint32_t *)&rs, sizeof(uint64_t));
        *result++ = (uint8_t)(rs >> 56);
        *result++ = (uint8_t)(rs >> 48);
        *result++ = (uint8_t)(rs >> 40);
        *result++ = (uint8_t)(rs >> 32);
        *result++ = (uint8_t)(rs >> 24);
        *result++ = (uint8_t)(rs >> 16);
        *result++ = (uint8_t)(rs >> 8);
        *result++ = (uint8_t)(rs >> 0);
    }
    HAL_OTBN_CMD_Write_Polling(HAL_OTBN_CMD_SEC_WIPE_DMEM);
}

#define HMAC_B 0x80
void HAL_OTBN_SHA384_HMAC(uint8_t out[SHA384_RESULT_SIZE], uint8_t *data, uint32_t data_len, uint8_t *key, uint32_t key_len)
{
    uint8_t kh[SHA384_RESULT_SIZE];
    uint8_t kx[HMAC_B];
    uint8_t i;

    if (key_len > HMAC_B)
    {
        HAL_OTBN_SHA384_Init();
        HAL_OTBN_SHA384_Update(key, key_len);
        HAL_OTBN_SHA384_Final(kh);
        key_len = SHA384_RESULT_SIZE;
        key = kh;
    }

    for (uint32_t i = 0; i < key_len; i++)
        kx[i] = HMAC_I_PAD ^ key[i];
    for (uint32_t i = key_len; i < HMAC_B; i++)
        kx[i] = HMAC_I_PAD ^ 0;

    HAL_OTBN_SHA384_Init();
    HAL_OTBN_SHA384_Update(kx, HMAC_B);
    HAL_OTBN_SHA384_Update(data, data_len);
    HAL_OTBN_SHA384_Final(out);
    for (i = 0; i < key_len; i++)
        kx[i] = HMAC_O_PAD ^ key[i];
    for (i = key_len; i < HMAC_B; i++)
        kx[i] = HMAC_O_PAD ^ 0;

    HAL_OTBN_SHA384_Init();
    HAL_OTBN_SHA384_Update(kx, HMAC_B);
    HAL_OTBN_SHA384_Update(out, SHA384_RESULT_SIZE);
    HAL_OTBN_SHA384_Final(out);
}
