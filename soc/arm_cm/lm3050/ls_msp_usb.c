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
// #include "tusb_config.h"
#include "systick.h"

static void USB_IRQHandler(void)
{
    tud_int_handler(0);
}

void HAL_USB_MSP_Init(void)
{
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_SET_USB_MASK;
    arm_cm_set_int_isr(USB_IRQn, USB_IRQHandler);
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