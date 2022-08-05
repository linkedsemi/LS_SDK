#ifndef _MAIN_H_
#define _MAIN_H_
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

void hextostring(const uint8_t *source, char *dest, int len);
int genie_ais_gatt_indicate(void *data, uint16_t len);
int genie_ais_gatt_notify_message(void *data, uint16_t len);
void genie_ais_gap_disconnect(uint8_t reason);

uint32_t ls_genie_ais_fw_version_get(void);
#endif
