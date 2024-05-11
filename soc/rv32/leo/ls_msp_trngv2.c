#include "ls_hal_trng.h"
#include "ls_msp_trngv2.h"
#include "exception_isr.h"
#include "reg_sysc_per.h"
#include "core_rv32.h"
#include "sys_stat.h"
#include "leo.h"

void HAL_TRNG_MSP_Init(void)
{
    SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_CLR_TRNG_MASK;
    SYSC_PER->PD_PER_SRST3 = SYSC_PER_SRST_CLR_TRNG_N_MASK;
    SYSC_PER->PD_PER_SRST3 = SYSC_PER_SRST_SET_TRNG_N_MASK;
    SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_SET_TRNG_MASK;
    rv_set_int_isr(TRNG_IRQn, HAL_TRNG_IRQHandler);
    csi_vic_clear_pending_irq(TRNG_IRQn);
    csi_vic_enable_irq(TRNG_IRQn);
}

void HAL_TRNG_MSP_DeInit(void)
{
    SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_CLR_TRNG_MASK;
    csi_vic_disable_irq(TRNG_IRQn);
}

void HAL_TRNG_MSP_Busy_Set(void)
{
    trng_status_set(true);
}

void HAL_TRNG_MSP_Idle_Set(void)
{
    trng_status_set(false);
}
