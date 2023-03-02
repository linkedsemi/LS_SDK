#ifndef LS_MSP_USB_H_
#define LS_MSP_USB_H_
#include <stdbool.h>
#include "reg_base_addr.h"
#include "reg_usb_type.h"

#ifdef LSUSB_BASE_ADDR
#define USB0 ((volatile reg_usb_t*)(LSUSB_BASE_ADDR))
#endif

void HAL_USB_MSP_Init(void);

void HAL_USB_MSP_Deinit(void);

void HAL_USB_MSP_EnableIRQ();

void HAL_USB_MSP_DisableIRQ();

void HAL_USB_MSP_ClearPendingIRQ();

uint32_t HAL_USB_MSP_GetEnableIRQ();
#endif
