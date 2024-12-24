#include "ls_hal_crc.h"
#include "ls_msp_crc.h"
#include "field_manipulate.h"
#include "compile_flag.h"

const struct crc_param CRC4_TU_PARAM = {
    .poly = 0x03,
    .init = 0,
    .xor_out = 0,
    .bitwidth = 4,
    .reverse_in = 1,
    .reverse_out = 1
};

const struct crc_param CRC5_EPC_PARAM = {
    .poly = 0x09,
    .init = 0x09,
    .xor_out = 0,
    .bitwidth = 5,
    .reverse_in = 1,
    .reverse_out = 1
};

const struct crc_param CRC5_TU_PARAM = {
    .poly = 0x15,
    .init = 0,
    .xor_out = 0,
    .bitwidth = 5,
    .reverse_in = 1,
    .reverse_out = 1
};

const struct crc_param CRC5_USB_PARAM = {
    .poly = 0x5,
    .init = 0x1f,
    .xor_out = 0x1f,
    .bitwidth = 5,
    .reverse_in = 1,
    .reverse_out = 1
};

const struct crc_param CRC6_TU_PARAM = {
    .poly = 0x3,
    .init = 0,
    .xor_out = 0,
    .bitwidth = 6,
    .reverse_in = 1,
    .reverse_out = 1
};

const struct crc_param CRC7_MMC_PARAM = {
    .poly = 0x9,
    .init = 0,
    .xor_out = 0,
    .bitwidth = 7,
    .reverse_in = 0,
    .reverse_out = 0
};

const struct crc_param CRC8_PARAM = {
    .poly = 0x7,
    .init = 0,
    .xor_out = 0,
    .bitwidth = 8,
    .reverse_in = 0,
    .reverse_out = 0
};

const struct crc_param CRC8_ROHC_PARAM = {
    .poly = 0x7,
    .init = 0XFF,
    .xor_out = 0,
    .bitwidth = 8,
    .reverse_in = 1,
    .reverse_out = 1
};

const struct crc_param CRC8_MAXIM_PARAM = {
    .poly = 0x31,
    .init = 0,
    .xor_out = 0,
    .bitwidth = 8,
    .reverse_in = 1,
    .reverse_out = 1
};

const struct crc_param CRC8_IBM_PARAM = {
    .poly = 0x8005,
    .init = 0,
    .xor_out = 0,
    .bitwidth = 16,
    .reverse_in = 1,
    .reverse_out = 1
};

const struct crc_param CRC16_MAXIM_PARAM = {
    .poly = 0x8005,
    .init = 0,
    .xor_out = 0XFFFF,
    .bitwidth = 16,
    .reverse_in = 1,
    .reverse_out = 1
};

const struct crc_param CRC16_USB_PARAM = {
    .poly = 0x8005,
    .init = 0XFFFF,
    .xor_out = 0XFFFF,
    .bitwidth = 16,
    .reverse_in = 1,
    .reverse_out = 1
};

const struct crc_param CRC16_MODBUS_PARAM = {
    .poly = 0x8005,
    .init = 0XFFFF,
    .xor_out = 0,
    .bitwidth = 16,
    .reverse_in = 1,
    .reverse_out = 1
};

const struct crc_param CRC16_CCIT_PARAM = {
    .poly = 0x1021,
    .init = 0,
    .xor_out = 0,
    .bitwidth = 16,
    .reverse_in = 1,
    .reverse_out = 1
};

const struct crc_param CRC16_CCIT_FALSE_PARAM = {
    .poly = 0x1021,
    .init = 0XFFFF,
    .xor_out = 0,
    .bitwidth = 16,
    .reverse_in = 0,
    .reverse_out = 0
};

const struct crc_param CRC16_X25_PARAM = {
    .poly = 0x1021,
    .init = 0XFFFF,
    .xor_out = 0XFFFF,
    .bitwidth = 16,
    .reverse_in = 1,
    .reverse_out = 1
};

const struct crc_param CRC16_XMODEM_PARAM = {
    .poly = 0x1021,
    .init = 0,
    .xor_out = 0,
    .bitwidth = 16,
    .reverse_in = 0,
    .reverse_out = 0
};

const struct crc_param CRC16_DNP_PARAM = {
    .poly = 0x3D65,
    .init = 0,
    .xor_out = 0XFFFF,
    .bitwidth = 16,
    .reverse_in = 1,
    .reverse_out = 1
};

const struct crc_param CRC32_PARAM = {
    .poly = 0x04c11db7,
    .init = 0xffffffff,
    .xor_out = 0xffffffff,
    .bitwidth = 32,
    .reverse_in = 1,
    .reverse_out = 1
};

const struct crc_param CRC32_MPEG_PARAM = {
    .poly = 0x04C11DB7,
    .init = 0xFFFFFFFF,
    .xor_out = 0,
    .bitwidth = 32,
    .reverse_in = 0,
    .reverse_out = 0
};

ROM_SYMBOL void HAL_LSCRC_Init(void)
{
    HAL_LSCRC_MSP_Init();
}

void HAL_LSCRC_DeInit(void)
{
    HAL_LSCRC_MSP_DeInit();
}

ROM_SYMBOL uint32_t HAL_LSCRC_Bit_Reverse(uint32_t in,uint8_t bitwidth)
{
    LSCRC->CRC_PARAM = 0x1;
    LSCRC->CRC_INIT = 0;
    LSCRC->CRC_CTRL = FIELD_BUILD(CALC_CRC_CRC_DAT_WID,bitwidth - 1)|FIELD_BUILD(CALC_CRC_CRC_LSB,1);
    LSCRC->CRC_START = 1;
    LSCRC->CRC_DAT = in;
    LSCRC->CRC_RSLT;
    return LSCRC->CRC_RSLT;
}

#include "log.h"
ROM_SYMBOL uint32_t HAL_LSCRC_CRC_CALC(const struct crc_param *cfg,const uint8_t *data,uint32_t length)
{
    LOG_HEX(data, length);
    LSCRC->CRC_PARAM = cfg->poly<<(32-cfg->bitwidth);
    LSCRC->CRC_INIT = cfg->init<<(32-cfg->bitwidth);
    LSCRC->CRC_START = 1;
    if(length>=4)
    {
        LSCRC->CRC_CTRL = FIELD_BUILD(CALC_CRC_CRC_DAT_WID,31)|FIELD_BUILD(CALC_CRC_CRC_LSB,cfg->reverse_in);
        do{
            if(cfg->reverse_in){
                LSCRC->CRC_DAT = data[3]<<24|data[2]<<16|data[1]<<8|data[0];
            }else
            {
                LSCRC->CRC_DAT = data[0]<<24|data[1]<<16|data[2]<<8|data[3];
            }
            length -= 4;
            data += 4;
        }while(length>=4);
    }
    LSCRC->CRC_RSLT;
    if(length)
    {
        LSCRC->CRC_CTRL = FIELD_BUILD(CALC_CRC_CRC_DAT_WID,length*8-1)|FIELD_BUILD(CALC_CRC_CRC_LSB,cfg->reverse_in);
        switch(length)
        {
        case 3:
            LSCRC->CRC_DAT = cfg->reverse_in ? (data[2]<<16|data[1]<<8|data[0]): (data[0]<<16|data[1]<<8|data[2]);
        break;
        case 2:
            LSCRC->CRC_DAT = cfg->reverse_in ? (data[1]<<8|data[0]): (data[0]<<8|data[1]);
        break;
        case 1:
            LSCRC->CRC_DAT = data[0];
        break;
        }
        LSCRC->CRC_RSLT;
    }
    if(cfg->reverse_out)
    {
        return HAL_LSCRC_Bit_Reverse(LSCRC->CRC_RSLT>>(32-cfg->bitwidth),cfg->bitwidth)^cfg->xor_out;
    }else
    {
        return (LSCRC->CRC_RSLT>>(32-cfg->bitwidth))^cfg->xor_out;
    }
}