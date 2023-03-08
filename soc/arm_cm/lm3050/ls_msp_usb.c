#include "ls_msp_usb.h"
#include "field_manipulate.h"
#include "ls_soc_pinmux.h"
#include "lm3050.h"
#include "HAL_def.h"
#include "platform.h"
#include <stddef.h>
#include "sys_stat.h"
#include "reg_sysc_cpu_type.h"
#include "usbd.h"
#include "ls_soc_gpio.h"
#include "systick.h"
#include "musb_type.h"
#include "hcd.h"

void HAL_USB_MSP_Init(void (*isr)())
{
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_SET_USB_MASK;
    arm_cm_set_int_isr(USB_IRQn, isr);
    HAL_USB_MSP_ClearPendingIRQ();
}

void HAL_USB_MSP_Deinit(void)
{
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_CLR_USB_MASK;
}

void HAL_USB_MSP_EnableIRQ()
{
    __NVIC_EnableIRQ(USB_IRQn);
}

void HAL_USB_MSP_DisableIRQ()
{
    __NVIC_DisableIRQ(USB_IRQn);
}

void HAL_USB_MSP_ClearPendingIRQ()
{
    __NVIC_ClearPendingIRQ(USB_IRQn);
}

uint32_t HAL_USB_MSP_GetEnableIRQ()
{
    return __NVIC_GetEnableIRQ(USB_IRQn);
}

void HAL_USB_MSP_Host_Setup(void *param)
{
    io_pull_write(PA12,IO_PULL_UP);
    USB0->DEVCTL |= USB_DEVCTL_HOSTREQ | USB_DEVCTL_SESSION;
    while((USB0->DEVCTL&USB_DEVCTL_HOST)==0);
    io_pull_write(PA12,IO_PULL_DOWN);
}

void HAL_USB_MSP_Host_Discon_Hook()
{
    if((USB0->DEVCTL & USB_DEVCTL_HOST) == 0)
    {
        hcd_event_t event;
        event.rhport = 0;
        event.event_id = USBH_EVENT_FUNC_CALL;
        event.func_call.func = HAL_USB_MSP_Host_Setup;
        event.func_call.param = NULL;
        hcd_event_handler(&event,true);
    }
}