#ifndef LS_MSP_USB_H_
#define LS_MSP_USB_H_
#include <stdbool.h>
#include "reg_base_addr.h"
#include "reg_usb_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef APP_USB1_ADDR
#define USB0 ((volatile reg_usb_t*)(APP_USB1_ADDR))
#endif

void HAL_USB_MSP_Init(void (*)());

void HAL_USB_MSP_Deinit(void);

void HAL_USB_MSP_EnableIRQ();

void HAL_USB_MSP_DisableIRQ();

void HAL_USB_MSP_ClearPendingIRQ();

uint32_t HAL_USB_MSP_GetEnableIRQ();

void HAL_USB_MSP_Host_Setup(void *);

void HAL_USB_MSP_Host_Discon_Hook();

void HAL_USB_MSP_Busy_Set();

void HAL_USB_MSP_Idle_Set();

#ifdef __cplusplus
}
#endif

#endif
