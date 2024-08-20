
#include "compile_flag.h"
#include "platform.h"
#include "cpu.h"
#include "log.h"
#include "swint_call_asm.h"
#include "systick.h"
#include "ls_hal_flash.h"
#include "exception_isr.h"
#include "ls_soc_gpio.h"
#include "field_manipulate.h"
#include "qsh.h"

#define PMU_CLK_VAL (SDK_HSE_USED << V33_RG_CLK_SET_HSE_POS | 1 << V33_RG_CLK_SET_HSI_POS | (!SDK_LSI_USED) << V33_RG_CLK_SET_LSE_POS)

__attribute__((aligned(64))) void (*interrupt_vector[IRQn_MAX])();

void rv_set_int_isr(uint8_t type,void (*isr)())
{
    interrupt_vector[type] = isr;
}

void SWINT_Handler_C(uint32_t *args)
{
    uint32_t (*func)(uint32_t,uint32_t,uint32_t,uint32_t) = (void *)args[11];
    args[15] = func(args[15],args[14],args[13],args[12]);
}

__attribute__((weak)) int _close (int fildes){  return -1;}

__attribute__((weak)) int _fstat (int fildes,void *st){  return -1;}

__attribute__((weak)) int _isatty (int file){  return 0;}

__attribute__((weak)) int _read (int file,char *ptr,int len){  return -1;}

__attribute__((weak)) int _lseek (int   file,int   ptr,int   dir){  return -1;}
