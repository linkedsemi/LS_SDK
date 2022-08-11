#include "ls_hal_crc.h"
#include "ls_msp_crc.h"
#include "field_manipulate.h"
#include "compile_flag.h"
#define CRC32_POLY 0x04c11db7
#define CRC32_XOR_IN 0xffffffff
#define CRC32_XOR_OUT 0xffffffff
ROM_SYMBOL void HAL_LSCRC_Init(void)
{
    HAL_LSCRC_MSP_Init();
}

void HAL_LSCRC_DeInit(void)
{
    HAL_LSCRC_MSP_DeInit();
}

ROM_SYMBOL uint32_t HAL_LSCRC_32bit_Reverse(uint32_t in)
{
    LSCRC->CRC_PARAM = 0x1;
    LSCRC->CRC_INIT = 0;
    LSCRC->CRC_CTRL = FIELD_BUILD(CALC_CRC_CRC_DAT_WID,31)|FIELD_BUILD(CALC_CRC_CRC_LSB,1);
    LSCRC->CRC_START = 1;
    LSCRC->CRC_DAT = in;
    LSCRC->CRC_RSLT;
    return LSCRC->CRC_RSLT;
}

ROM_SYMBOL uint32_t HAL_LSCRC_CRC32(uint32_t crc,const uint8_t *data,uint32_t length)
{
    crc = HAL_LSCRC_32bit_Reverse(crc);
    LSCRC->CRC_PARAM = CRC32_POLY;
    LSCRC->CRC_INIT = CRC32_XOR_IN^crc;
    LSCRC->CRC_START = 1;
    if(length>=4)
    {
        LSCRC->CRC_CTRL = FIELD_BUILD(CALC_CRC_CRC_DAT_WID,31)|FIELD_BUILD(CALC_CRC_CRC_LSB,1);
        while(length>=4)
        {
            LSCRC->CRC_DAT = data[3]<<24|data[2]<<16|data[1]<<8|data[0];
            length -= 4;
            data += 4;
        }
    }
    LSCRC->CRC_RSLT;
    if(length)
    {
        LSCRC->CRC_CTRL = FIELD_BUILD(CALC_CRC_CRC_DAT_WID,length*8-1)|FIELD_BUILD(CALC_CRC_CRC_LSB,1);
        switch(length)
        {
        case 3:
            LSCRC->CRC_DAT = data[2]<<16|data[1]<<8|data[0];
        break;
        case 2:
            LSCRC->CRC_DAT = data[1]<<8|data[0];
        break;
        case 1:
            LSCRC->CRC_DAT = data[0];
        break;
        }
        LSCRC->CRC_RSLT;
    }
    return HAL_LSCRC_32bit_Reverse(LSCRC->CRC_RSLT) ^ CRC32_XOR_OUT;
}