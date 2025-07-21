#include "ls_msp_iwdg.h"
#include "reg_sysc_cpu.h"
#include "field_manipulate.h"
#include "reg_v33_rg.h"
void HAL_IWDG_MSP_Init()
{
    V33_RG->CLKG_SRST = V33_RG_CLKG_SET_WDT_MASK;
}

void HAL_IWDG_MSP_DeInit()
{
    V33_RG->CLKG_SRST = V33_RG_CLKG_CLR_WDT_MASK;
}

void HAL_IWDG_MSP_DEBUG(reg_iwdg_t *addr, uint8_t debug_en)
{
  if (debug_en)
  {
    SYSC_CPU->CPU_SYSC |= SYSC_CPU_WDT_DBG_MASK;
  }
  else
  {
    SYSC_CPU->CPU_SYSC &= ~SYSC_CPU_WDT_DBG_MASK;
  }
}