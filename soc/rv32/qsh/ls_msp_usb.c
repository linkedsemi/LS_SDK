#include "ls_msp_usb.h"
#include "field_manipulate.h"
#include "ls_soc_pinmux.h"
#include "qsh.h"
#include "HAL_def.h"
#include "platform.h"
#include <stddef.h>
#include "sys_stat.h"
#include "usbd.h"
#include "ls_soc_gpio.h"
#include "systick.h"
#include "musb_type.h"
#include "hcd.h"
#include "csi_core.h"
#include "exception_isr.h"

void HAL_USB_MSP_Init(void (*isr)())
{
    SYSC_APP_CPU->PD_CPU_CLKG0 = SYSC_APP_CPU_CLKG_CLR_USB1_MASK;
    SYSC_APP_CPU->PD_CPU_SRST = SYSC_APP_CPU_SRST_CLR_USB1_MASK;
    SYSC_APP_CPU->PD_CPU_SRST = SYSC_APP_CPU_SRST_SET_USB1_MASK;
    SYSC_APP_CPU->PD_CPU_CLKG0 = SYSC_APP_CPU_CLKG_SET_USB1_MASK;
    rv_set_int_isr(USB1_IRQN, isr);
    csi_vic_clear_pending_irq(USB1_IRQN);
    csi_vic_enable_irq(USB1_IRQN);
}

void HAL_USB_MSP_Deinit(void)
{
    SYSC_APP_CPU->PD_CPU_CLKG0 = SYSC_APP_CPU_CLKG_CLR_USB1_MASK;
    HAL_USB_MSP_DisableIRQ();
}

void HAL_USB_MSP_EnableIRQ()
{
    csi_vic_enable_irq(USB1_IRQN);
}

void HAL_USB_MSP_DisableIRQ()
{
    csi_vic_disable_irq(USB1_IRQN);
}

void HAL_USB_MSP_ClearPendingIRQ()
{
    csi_vic_clear_pending_irq(USB1_IRQN);
}

uint32_t HAL_USB_MSP_GetEnableIRQ()
{
    return csi_vic_get_enabled_irq(USB1_IRQN);
}

void HAL_USB_MSP_Host_Setup(void *param)
{
    // REG_FIELD_WR(SYSC_AWO->PIN_SEL0, SYSC_AWO_USB_PUPD, 0x1);
    // REG_FIELD_WR(SYSC_AWO->PIN_SEL0, SYSC_AWO_USB_CID, 0x1);
}

void HAL_USB_MSP_Host_Discon_Hook()
{

}

void HAL_USB_MSP_Busy_Set()
{

}

void HAL_USB_MSP_Idle_Set()
{
    
}