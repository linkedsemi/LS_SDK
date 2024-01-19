#include "ls_msp_cap.h"
#include "field_manipulate.h"
#include "leo.h"
#include "ls_hal_cap.h"
#include "core_rv32.h"
#include "reg_sysc_per.h"
#include "exception_isr.h"

void HAL_LSCAP_MSP_Init(void)
{
    SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_CAP_MASK;
    SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_CLR_CAP_N_MASK;
    SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_SET_CAP_N_MASK;
    SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_SET_CAP_MASK;
    rv_set_int_isr(CAP_IRQn, HAL_LSCAP_IRQHandler);
    csi_vic_clear_pending_irq(CAP_IRQn);
    csi_vic_enable_irq(CAP_IRQn);
}

void HAL_LSCAP_MSP_DeInit(void)
{
    SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_CAP_MASK;
    csi_vic_disable_irq(CAP_IRQn);
}