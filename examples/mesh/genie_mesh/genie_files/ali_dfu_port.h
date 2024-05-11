#ifndef _ALI_DFU_PORT_H
#define _ALI_DFU_PORT_H
#include <stdbool.h>
#include <stdio.h>

void ais_ota_flash_cleanup(void);
int erase_dfu_flash(void);
unsigned char dfu_check_checksum(short image_id, unsigned short *crc16_output);
int ali_dfu_image_update(short signature, int offset, int length, int *p_void);
uint32_t ali_dfu_get_ota_partition_max_size(void);



#endif

