
#ifndef __usb_packet_hid_data_H__
#define __usb_packet_hid_data_H__

#include <stddef.h>
#include <stdint.h>
#include <string.h>

// Data structure
typedef struct
{
    uint32_t data_address;
    uint32_t data_index;
    uint8_t data_buffer[256];
    uint32_t next_address;
    uint32_t remain_address;
    uint32_t remain_data_len;
    uint8_t remain_data[64];
} IAP_Download_t;

// Functions
extern void usb_packet_hid_data_init(void);
extern bool usb_packet_hid_data(uint32_t address, const uint8_t *data, uint32_t data_size);
extern bool usb_packet_get_hid_data(bool check_last);

#endif /* __usb_packet_hid_data_H__ */
