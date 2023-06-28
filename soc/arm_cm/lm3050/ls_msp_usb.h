#ifndef LS_MSP_USB_H_
#define LS_MSP_USB_H_
#include <stdbool.h>
#include "reg_base_addr.h"
#include "reg_usb_type.h"
#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef LSUSB_BASE_ADDR
#define USB0 ((volatile reg_usb_t*)(LSUSB_BASE_ADDR))
#endif

#if defined(__ICCARM__)
#define __builtin_ctz count_trailing_zeros
#endif

void HAL_USB_MSP_Init(void (*)());

void HAL_USB_MSP_Deinit(void);

void HAL_USB_MSP_EnableIRQ();

void HAL_USB_MSP_DisableIRQ();

void HAL_USB_MSP_ClearPendingIRQ();

uint32_t HAL_USB_MSP_GetEnableIRQ();

void HAL_USB_MSP_Host_Setup(void *);

void HAL_USB_MSP_Host_Discon_Hook();

#ifdef __cplusplus
}
#endif

#endif
