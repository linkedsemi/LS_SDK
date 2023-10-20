#ifndef LS_HAL_CRC_H_
#define LS_HAL_CRC_H_
#include "HAL_def.h"
#include "ls_msp_crc.h"

#ifdef __cplusplus
extern "C" {
#endif

struct crc_param
{
    uint32_t poly;
    uint32_t init;
    uint32_t xor_out;
    uint8_t bitwidth;
    uint8_t reverse_in:1,
            reverse_out:1;
};



extern const struct crc_param CRC4_TU_PARAM;
extern const struct crc_param CRC5_EPC_PARAM;
extern const struct crc_param CRC5_TU_PARAM;
extern const struct crc_param CRC5_USB_PARAM;
extern const struct crc_param CRC6_TU_PARAM;
extern const struct crc_param CRC7_MMC_PARAM;
extern const struct crc_param CRC8_PARAM;
extern const struct crc_param CRC8_ROHC_PARAM;
extern const struct crc_param CRC8_MAXIM_PARAM;
extern const struct crc_param CRC8_IBM_PARAM;
extern const struct crc_param CRC16_MAXIM_PARAM;
extern const struct crc_param CRC16_USB_PARAM;
extern const struct crc_param CRC16_MODBUS_PARAM;
extern const struct crc_param CRC16_CCIT_PARAM;
extern const struct crc_param CRC16_CCIT_FALSE_PARAM;
extern const struct crc_param CRC16_X25_PARAM;
extern const struct crc_param CRC16_XMODEM_PARAM;
extern const struct crc_param CRC16_DNP_PARAM;
extern const struct crc_param CRC32_PARAM;
extern const struct crc_param CRC32_MPEG_PARAM;


void HAL_LSCRC_Init(void);

void HAL_LSCRC_DeInit(void);

uint32_t HAL_LSCRC_CRC_CALC(const struct crc_param *cfg,const uint8_t *data,uint32_t length);

uint32_t HAL_LSCRC_Bit_Reverse(uint32_t in,uint8_t bitwidth);

#ifdef __cplusplus
}
#endif

#endif
