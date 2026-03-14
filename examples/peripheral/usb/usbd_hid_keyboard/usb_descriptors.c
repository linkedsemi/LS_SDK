/* 
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "tusb.h"
#include "usb_descriptors.h"

/* A combination of interfaces must have a unique product id, since PC will save device driver after the first plug.
 * Same VID/PID with different interface e.g MSC (first), then CDC (later) will possibly cause system error on PC.
 *
 * Auto ProductID layout's Bitmap:
 *   [MSB]         HID | MSC | CDC          [LSB]
 */
#define _PID_MAP(itf, n)  ( (CFG_TUD_##itf) << (n) )
// #define USB_PID           (0x4000 | _PID_MAP(CDC, 0) | _PID_MAP(MSC, 1) | _PID_MAP(HID, 2) |
//                            _PID_MAP(MIDI, 3) | _PID_MAP(VENDOR, 4) )
#define USB_PID   0x0001
#define USB_VID   0xCafe
#define USB_BCD   0x0200

//--------------------------------------------------------------------+
// Device Descriptors
//--------------------------------------------------------------------+
tusb_desc_device_t const desc_device =
{
    .bLength            = sizeof(tusb_desc_device_t),
    .bDescriptorType    = TUSB_DESC_DEVICE,
    .bcdUSB             = USB_BCD,
    .bDeviceClass       = 0x00,
    .bDeviceSubClass    = 0x00,
    .bDeviceProtocol    = 0x00,
    .bMaxPacketSize0    = CFG_TUD_ENDPOINT0_SIZE,

    .idVendor           = USB_VID,
    .idProduct          = USB_PID,
    .bcdDevice          = 0x0100,

    .iManufacturer      = 0x01,
    .iProduct           = 0x02,
    .iSerialNumber      = 0x03,

    .bNumConfigurations = 0x01
};

// Invoked when received GET DEVICE DESCRIPTOR
// Application return pointer to descriptor
uint8_t const * tud_descriptor_device_cb(void)
{
  return (uint8_t const *) &desc_device;
}

//--------------------------------------------------------------------+
// HID Report Descriptor
//--------------------------------------------------------------------+

uint8_t const desc_hid_report[] =
{
  TUD_HID_REPORT_DESC_KEYBOARD( HID_REPORT_ID(REPORT_ID_KEYBOARD         )),
};

// Invoked when received GET HID REPORT DESCRIPTOR
// Application return pointer to descriptor
// Descriptor contents must exist long enough for transfer to complete
uint8_t const * tud_hid_descriptor_report_cb(uint8_t instance)
{
  (void) instance;
  return desc_hid_report;
}

//--------------------------------------------------------------------+
// Configuration Descriptor
//--------------------------------------------------------------------+

enum
{
  ITF_NUM_HID,
  ITF_NUM_TOTAL
};

#define  CONFIG_TOTAL_LEN  (TUD_CONFIG_DESC_LEN + TUD_HID_DESC_LEN)

#define EPNUM_HID   0x81

uint8_t const desc_configuration[] =
{
  // Config number, interface count, string index, total length, attribute, power in mA
  TUD_CONFIG_DESCRIPTOR(1, ITF_NUM_TOTAL, 0, CONFIG_TOTAL_LEN, TUSB_DESC_CONFIG_ATT_REMOTE_WAKEUP, 100),

  // Interface number, string index, protocol, report descriptor len, EP In address, size & polling interval
  TUD_HID_DESCRIPTOR(ITF_NUM_HID, 0, HID_ITF_PROTOCOL_KEYBOARD, sizeof(desc_hid_report), EPNUM_HID, CFG_TUD_HID_EP_BUFSIZE, 5)
};

#if TUD_OPT_HIGH_SPEED
// Per USB specs: high speed capable device must report device_qualifier and other_speed_configuration

// other speed configuration
uint8_t desc_other_speed_config[CONFIG_TOTAL_LEN];

// device qualifier is mostly similar to device descriptor since we don't change configuration based on speed
tusb_desc_device_qualifier_t const desc_device_qualifier =
{
  .bLength            = sizeof(tusb_desc_device_qualifier_t),
  .bDescriptorType    = TUSB_DESC_DEVICE_QUALIFIER,
  .bcdUSB             = USB_BCD,

  .bDeviceClass       = 0x00,
  .bDeviceSubClass    = 0x00,
  .bDeviceProtocol    = 0x00,

  .bMaxPacketSize0    = CFG_TUD_ENDPOINT0_SIZE,
  .bNumConfigurations = 0x01,
  .bReserved          = 0x00
};

// Invoked when received GET DEVICE QUALIFIER DESCRIPTOR request
// Application return pointer to descriptor, whose contents must exist long enough for transfer to complete.
// device_qualifier descriptor describes information about a high-speed capable device that would
// change if the device were operating at the other speed. If not highspeed capable stall this request.
uint8_t const* tud_descriptor_device_qualifier_cb(void)
{
  return (uint8_t const*) &desc_device_qualifier;
}

// Invoked when received GET OTHER SEED CONFIGURATION DESCRIPTOR request
// Application return pointer to descriptor, whose contents must exist long enough for transfer to complete
// Configuration descriptor in the other speed e.g if high speed then this is for full speed and vice versa
uint8_t const* tud_descriptor_other_speed_configuration_cb(uint8_t index)
{
  (void) index; // for multiple configurations

  // other speed config is basically configuration with type = OHER_SPEED_CONFIG
  memcpy(desc_other_speed_config, desc_configuration, CONFIG_TOTAL_LEN);
  desc_other_speed_config[1] = TUSB_DESC_OTHER_SPEED_CONFIG;

  // this example use the same configuration for both high and full speed mode
  return desc_other_speed_config;
}

#endif // highspeed

// Invoked when received GET CONFIGURATION DESCRIPTOR
// Application return pointer to descriptor
// Descriptor contents must exist long enough for transfer to complete
uint8_t const * tud_descriptor_configuration_cb(uint8_t index)
{
  (void) index; // for multiple configurations

  // This example use the same configuration for both high and full speed mode
  return desc_configuration;
}

//--------------------------------------------------------------------+
// String Descriptors
//--------------------------------------------------------------------+

// array of pointer to string descriptors
char const* string_desc_arr [] =
{
  (const char[]) { 0x09, 0x04 }, // 0: is supported language is English (0x0409)
  "Linkedsemi",                     // 1: Manufacturer
  "Linkedsemi Keyboard",              // 2: Product
  "v1.0",                      // 3: Serials, should use chip ID
  (const char[]){'M', 0, 'S', 0, 'F', 0, 'T', 0, '1', 0, '0', 0, '0', 0, 0x01, 0}, // 0xEE: Windows OS String Descriptor ("MSFT100")      
};


// Microsoft OS 1.0 Extended Compat ID Descriptor
uint8_t const desc_ms_os_compat_id[] = 
{
    0x28, 0x00, 0x00, 0x00, // length--Size of this struct = 16 + bCount*24
    0x00, 0x01,             // bcdVersion--1.00 -> 0x0100
    0x04, 0x00,             // index--Command index - 0x0004 for extended compatibility id
    0x01,                   // count--Number of interfaces for which an extended compatibility feature descriptor is defined
    0, 0, 0, 0, 0, 0, 0,    // reserved[7]

    0x00,                   // firstInterfaceNumber--Interface number for which an extended compatibility feature descriptor is defined
    0x01,                   // reserved
    0, 0, 0, 0, 0, 0, 0, 0, // compatibleID[8]--String describing the compatible id
    0, 0, 0, 0, 0, 0, 0, 0, // subCompatibleID[8]--String describing the sub compatible id
    0, 0, 0, 0, 0, 0        // reserved[6]
};

// Microsoft OS 1.0 Extended Property Descriptor
uint8_t const desc_ms_os_property[] = 
{
    U32_TO_U8S_LE(0x0000004C),  // dwLength--Size of this struct:0x0000004c=76
    0x00, 0x01,                 // bcdVersion--1.00 -> 0x0100
    0x05, 0x00,                 // wIndex--Command index - Extended property OS descriptor: 0x0005 
    0x01, 0x00,                 // wCount--One custom property
    U32_TO_U8S_LE(0x00000042),  // dwSize--0x00000042 (66 bytes for this property)
    U32_TO_U8S_LE(0x00000004),  // wPropertyDataType (REG_DWORD)
    U16_TO_U8S_LE(0x0030),      // wPropertyNameLength (48 bytes)
    // bPropertyName: "SelectiveSuspendEnabled" (Unicode)
    // 48 Bytes EnableDshowRedirection (Unicode string end with NULL)
    'S', 0x00, 'e', 0x00, 'l', 0x00, 'e', 0x00, 'c', 0x00, 't', 0x00, 'i', 0x00, 'v', 0x00,
    'e', 0x00, 'S', 0x00, 'u', 0x00, 's', 0x00, 'p', 0x00, 'e', 0x00, 'n', 0x00, 'd', 0x00,
    'E', 0x00, 'n', 0x00, 'a', 0x00, 'b', 0x00, 'l', 0x00, 'e', 0x00, 'd', 0x00, 0x00, 0x00,
    U32_TO_U8S_LE(0x00000004),    // dwPropertyDataLength--0x00000004 (Sizeof(DWORD))
    0x01, 0x00, 0x00, 0x00,   // bPropertyData--0x00000001 (DWORD data)
};

// Invoked when received GET STRING DESCRIPTOR request
// Application return pointer to descriptor, whose contents must exist long enough for transfer to complete
uint16_t const *tud_descriptor_string_cb(uint8_t index, uint16_t langid)
{
    (void)langid;
    
    static uint16_t _desc_str[32];
    uint8_t chr_count;

    if (index == 0)
    {
        memcpy(&_desc_str[1], string_desc_arr[0], 2);
        chr_count = 1;
    }
    else
    {
        // Note: the 0xEE index string is a Microsoft OS 1.0 Descriptors.
        // https://docs.microsoft.com/en-us/windows-hardware/drivers/usbcon/microsoft-defined-usb-descriptors
        if (index == 0xEE)
        {
            const char *str = string_desc_arr[4];
            uint8_t len = 8; // "MSFT100" + 0x01 (共8字符)
            for (uint8_t i = 0; i < len; i++)
            {
                _desc_str[1 + i] = ((uint16_t *)str)[i]; // 直接复制UTF-16数据
            }
            _desc_str[0] = (TUSB_DESC_STRING << 8) | (2 * len + 2);
            return _desc_str;
        }

        if (index > 4)
        {
            return NULL;
        }
        const char *str = string_desc_arr[index];
        // Cap at max char
        chr_count = (uint8_t)strlen(str);
        if (chr_count > 31)
        {
            chr_count = 31;
        }
        // Convert ASCII string into UTF-16
        for (uint8_t i = 0; i < chr_count; i++)
        {
            _desc_str[1 + i] = str[i];
        }
    }

    // first byte is length (including header), second byte is string type
    _desc_str[0] = (uint16_t)((TUSB_DESC_STRING << 8) | (2 * chr_count + 2));
    
    return _desc_str;
}

bool tud_vendor_control_xfer_cb(uint8_t rhport, uint8_t stage, tusb_control_request_t const *request)
{
    // nothing to with DATA & ACK stage
    if (stage != CONTROL_STAGE_SETUP)
        return true;

    // 处理OS描述符请求（0xC0）
    if (request->bmRequestType == 0xC0)
    {
        // Get Microsoft OS 1.0 compatible descriptor 
        return tud_control_xfer(rhport, request, (void *)desc_ms_os_compat_id, sizeof(desc_ms_os_compat_id));
    }

    // 处理扩展属性请求 (0xC1)
    if (request->bmRequestType == 0xC1)
    {
        // Get Microsoft OS 1.0 property descriptor
        tud_control_xfer(rhport, request, (void *)desc_ms_os_property, sizeof(desc_ms_os_property));
        return true;
    }

    return false; // 其他厂商请求
}
