#include "ls_msp_usb.h"
#include "field_manipulate.h"
#include "ls_soc_pinmux.h"
#include "leo.h"
#include "HAL_def.h"
#include "platform.h"
#include <stddef.h>
#include "sys_stat.h"
#include "reg_sysc_cpu.h"
#include "usbd.h"
#include "ls_soc_gpio.h"
#include "systick.h"
#include "musb_type.h"
#include "hcd.h"
#include "csi_core.h"
#include "exception_isr.h"

void HAL_USB_MSP_Init(void (*isr)())
{
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_CLR_USB_MASK;
    SYSC_CPU->PD_CPU_SRST = SYSC_CPU_SRST_CLR_USB_N_MASK;
    SYSC_CPU->PD_CPU_SRST = SYSC_CPU_SRST_SET_USB_N_MASK;
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_SET_USB_MASK;
    rv_set_int_isr(USB_IRQn, isr);
    csi_vic_clear_pending_irq(USB_IRQn);
    csi_vic_enable_irq(USB_IRQn);
}

void HAL_USB_MSP_Deinit(void)
{
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_CLR_USB_MASK;
    HAL_USB_MSP_DisableIRQ();
}

void HAL_USB_MSP_EnableIRQ()
{
    csi_vic_enable_irq(USB_IRQn);
}

void HAL_USB_MSP_DisableIRQ()
{
    csi_vic_disable_irq(USB_IRQn);
}

void HAL_USB_MSP_ClearPendingIRQ()
{
    csi_vic_clear_pending_irq(USB_IRQn);
}

uint32_t HAL_USB_MSP_GetEnableIRQ()
{
    return csi_vic_get_enabled_irq(USB_IRQn);
}

void HAL_USB_MSP_Host_Setup(void *param)
{

}

void HAL_USB_MSP_Host_Discon_Hook()
{

}

void HAL_USB_MSP_Busy_Set()
{
    usb_status_set(true);
}

void HAL_USB_MSP_Idle_Set()
{
    usb_status_set(false);
}