#include "ls_hal_sm4.h"
#include "ls_msp_sm4.h"
#include "field_manipulate.h"
#include "ls_dbg.h"
#include "log.h"
static const uint8_t *crypt_in;
static uint8_t *crypt_out;
static bool writeflag;

HAL_StatusTypeDef HAL_SM4_Init(void)
{
    HAL_LSSM4_MSP_Init();
    return HAL_OK;
}

HAL_StatusTypeDef HAL_SM4_DeInit(void)
{
    HAL_LSSM4_MSP_DeInit();
    return HAL_OK;
}

static uint32_t u8tou32(const uint8_t *in)
{
    return in[0] | in[1] << 8 | in[2] << 16 | in[3] << 24;
}

static void u32tou8(uint32_t in, uint8_t *out)
{
    *out++ = in;
    *out++ = in >> 8;
    *out++ = in >> 16;
    *out++ = in >> 24;
}

void sm4_key_start(const uint8_t *key)
{    
    LSSM4->SM4_KEY0 = u8tou32(key);
    LSSM4->SM4_KEY1 = u8tou32(key + 4);
    LSSM4->SM4_KEY2 = u8tou32(key + 8);
    LSSM4->SM4_KEY3 = u8tou32(key + 12);
    LSSM4->SM4_START = SM4_KEY_START_MASK;
}

HAL_StatusTypeDef HAL_SM4_KeyExpansion(const uint8_t *key)
{   
    sm4_key_start(key);
    while (REG_FIELD_RD(LSSM4->INTR_RAW, SM4_KEY_END) == 0)
        ;
    LSSM4->INTR_CLR = SM4_KEY_END_MASK;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_SM4_KeyExpansion_IT(const uint8_t *key)
{
    LSSM4->INTR_MSK |= SM4_KEY_END_MASK;
    sm4_key_start(key);
    return HAL_OK;
}

static void sm4_data_length_inout_config(const uint8_t *data, uint32_t length, uint8_t *result)
{
    LS_ASSERT(length % 16 == 0);
    writeflag = true;
    crypt_in = data;
    crypt_out = result;
    LSSM4->SM4_CTRL |= (uint8_t)(length / 16 - 1) << SM4_CALC_LEN_POS;
}

static void sm4_start()
{
    LSSM4->CALC_WRD = u8tou32(crypt_in);
    LSSM4->CALC_WRD = u8tou32(crypt_in + 4);
    LSSM4->CALC_WRD = u8tou32(crypt_in + 8);
    LSSM4->CALC_WRD = u8tou32(crypt_in + 12);
}

static void sm4_end()
{
    u32tou8(LSSM4->CALC_RSLT0, crypt_out);
    u32tou8(LSSM4->CALC_RSLT1, crypt_out + 4);
    u32tou8(LSSM4->CALC_RSLT2, crypt_out + 8);
    u32tou8(LSSM4->CALC_RSLT3, crypt_out + 12);
    crypt_in += 16;
    crypt_out += 16;
}

static void sm4_calculate()
{
    LSSM4->SM4_START = SM4_CALC_START_MASK;
    do
    {
        while (REG_FIELD_RD(LSSM4->INTR_RAW, SM4_INTR_DATA) == 1)
        {
            if (writeflag)
            {
                sm4_start();
            }
            else
            {
                sm4_end();
            }
            writeflag = !writeflag;
            LSSM4->INTR_CLR = SM4_INTR_DATA_MASK;
        }
    } while (REG_FIELD_RD(LSSM4->INTR_RAW, SM4_INTR_END) == 0);
    LSSM4->INTR_CLR = SM4_INTR_END_MASK;
    sm4_end();
}

HAL_StatusTypeDef HAL_SM4_Encrypt(const uint8_t *data, uint8_t *result, uint32_t length)
{
    sm4_data_length_inout_config(data, length, result);
    REG_FIELD_WR(LSSM4->SM4_CTRL,SM4_CALC_DEC,0);
    sm4_calculate();
    return HAL_OK;
}

HAL_StatusTypeDef HAL_SM4_Decrypt(const uint8_t *data, uint8_t *result, uint32_t length)
{
    sm4_data_length_inout_config(data, length, result);
    REG_FIELD_WR(LSSM4->SM4_CTRL,SM4_CALC_DEC,1);
    sm4_calculate();
    return HAL_OK;
}

HAL_StatusTypeDef HAL_SM4_Encrypt_IT(const uint8_t *data, uint8_t *result, uint32_t length)
{
    sm4_data_length_inout_config(data, length, result);
    REG_FIELD_WR(LSSM4->SM4_CTRL,SM4_CALC_DEC,0);
    MODIFY_REG(LSSM4->INTR_MSK, SM4_INTR_DATA_MASK | SM4_INTR_END_MASK, 1 << SM4_INTR_DATA_POS | 1 << SM4_INTR_END_POS);
    LSSM4->SM4_START = SM4_CALC_START_MASK;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_SM4_Decrypt_IT(const uint8_t *data, uint8_t *result, uint32_t length)
{
    sm4_data_length_inout_config(data, length, result);
    REG_FIELD_WR(LSSM4->SM4_CTRL,SM4_CALC_DEC,1);
    MODIFY_REG(LSSM4->INTR_MSK, SM4_INTR_DATA_MASK | SM4_INTR_END_MASK, 1 << SM4_INTR_DATA_POS | 1 << SM4_INTR_END_POS);
    LSSM4->SM4_START = SM4_CALC_START_MASK;
    return HAL_OK;
}

__attribute__((weak)) void HAL_SM4_Calculation_Complete_Callback(bool Encrypt){}
__attribute__((weak)) void HAL_SM4_KeyExpansion_Complete_Callback(){}

void HAL_SM4_IRQHandler()
{
    if (REG_FIELD_RD(LSSM4->INTR_STT, SM4_INTR_DATA))
    {
        if (writeflag)
        {
            writeflag = !writeflag;
            sm4_start();
        }
        else
        {
            writeflag = !writeflag;
            sm4_end();
        }
        LSSM4->INTR_CLR = SM4_INTR_DATA_MASK;
    }
    if (REG_FIELD_RD(LSSM4->INTR_STT, SM4_INTR_END))
    {
        sm4_end();
        LSSM4->INTR_CLR = SM4_INTR_END_MASK;
        HAL_SM4_Calculation_Complete_Callback(!REG_FIELD_RD(LSSM4->SM4_CTRL,SM4_CALC_DEC));
    }
    if(REG_FIELD_RD(LSSM4->INTR_STT, SM4_KEY_END))
    {
        LSSM4->INTR_CLR = SM4_KEY_END_MASK;
        HAL_SM4_KeyExpansion_Complete_Callback();
    }
}