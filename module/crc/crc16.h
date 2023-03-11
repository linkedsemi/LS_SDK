#ifndef CRC16_H_
#define CRC16_H_
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint16_t crc16ccitt(uint16_t crc,const void *in_data,uint32_t len);

#ifdef __cplusplus
}
#endif

#endif

