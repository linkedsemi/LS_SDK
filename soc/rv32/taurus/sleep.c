#include "cpu.h"
#include "spi_flash.h"
#include "compile_flag.h"
#include "platform.h"
#include "reg_sysc_awo.h"
#include "reg_v33_rg.h"
#include "field_manipulate.h"
#include "sleep.h"
#include "io_config.h"
#include "common.h"
#include "csi_core.h"
#include "exception_isr.h"

static uint32_t sleep_msp;
void cpu_sleep_asm(void);
void cpu_recover_asm(void);
void xo16m(void);
extern uint32_t __StackTop;
extern uint32_t exception_entry;

void cpu_sleep_recover_init()
{
    V33_RG->SFT_CTRL03 = (uint32_t)cpu_recover_asm >> 1;
}

XIP_BANNED void xo16m()
{
    
}

XIP_BANNED void store_msp()   
{
    // sleep_msp = __get_MSP();
}

XIP_BANNED void restore_msp()
{
    // __set_MSP(sleep_msp);
}

XIP_BANNED void pwr_delay()
{
    REG_FIELD_WR(V33_RG->WKUP_TIM,V33_RG_STB_CLK_M1,0xf);
}

XIP_BANNED void before_wfi()
{

}

XIP_BANNED void after_wfi()
{
}

XIP_BANNED void power_down_config()
{
    REG_FIELD_WR(V33_RG->WKUP_CTRL,V33_RG_SWD_IO_WKUP_EN,0x01);
    while(SYSC_AWO->DBG_ACK)
    ;
    // io_set_pin(PA07);
    while(1);
    cpu_sleep_recover_init();
    V33_RG->PWR_CTRL = FIELD_BUILD(V33_RG_LPLDO_PD_EN,0)
                          |FIELD_BUILD(V33_RG_HPLDO_PD_EN,1)
                          |FIELD_BUILD(V33_RG_PWRSW_PD_EN,1)
                          |FIELD_BUILD(V33_RG_DCDC_PDPU_EN,0)
                          |FIELD_BUILD(V33_RG_DCDC_PDPU_MD,0)
                          |FIELD_BUILD(V33_RG_LSI_PD_EN,1)
                          |FIELD_BUILD(V33_RG_HSE_PD_EN,1)
                          |FIELD_BUILD(V33_RG_HSE_BUF_PD_EN,1)
                          |FIELD_BUILD(V33_RG_SRAM_DS_EN,1);
    V33_RG->MISC_CTRL1 = FIELD_BUILD(V33_RG_LATCH_GPIO,1)
                          |FIELD_BUILD(V33_RG_PD_GPIO,0)
                          |FIELD_BUILD(V33_RG_PD_ADC12,1)
                          |FIELD_BUILD(V33_RG_PD_AMIC,1)
                          |FIELD_BUILD(V33_RG_PD_TK,1)
                          |FIELD_BUILD(V33_RG_BOR_EN,0)
                          |FIELD_BUILD(V33_RG_BAT_DTCT_EN,0);
    V33_RG->MISC_CTRL1 = FIELD_BUILD(V33_RG_LATCH_GPIO,1)
                          |FIELD_BUILD(V33_RG_PD_GPIO,1)
                          |FIELD_BUILD(V33_RG_PD_ADC12,1)
                          |FIELD_BUILD(V33_RG_PD_AMIC,1)
                          |FIELD_BUILD(V33_RG_PD_TK,1)
                          |FIELD_BUILD(V33_RG_BOR_EN,0)
                          |FIELD_BUILD(V33_RG_BAT_DTCT_EN,0);
    V33_RG->TRIM0     = FIELD_BUILD(V33_RG_SPI_CODE,0)
                          |FIELD_BUILD(V33_RG_SPI_CODE_EN,1)
                          |FIELD_BUILD(V33_RG_RCO_I_ADJ,0)
                          |FIELD_BUILD(V33_RG_LPLDO_TRIM,0);
    REG_FIELD_WR(V33_RG->WKUP_CTRL,V33_RG_WKUP_MSK,0x08);
    // SCB->SCR = 0x01;
}

NOINLINE XIP_BANNED static void cpu_flash_deep_sleep_and_recover()
{
    spi_flash_xip_stop();
    spi_flash_deep_power_down();
    power_down_config();
    // io_set_pin(PA08);
    cpu_sleep_asm();
    REG_FIELD_WR(SYSC_AWO->PIN_SEL0,SYSC_AWO_QSPI_EN,0x3f);//QSPI_IO_INIT
    __set_MTVEC((uint32_t)&exception_entry);
    __set_MTVT((uint32_t)interrupt_vector);
    __set_SP((uint32_t)&__StackTop);
    __disable_irq();
    V33_RG->MISC_CTRL1 = FIELD_BUILD(V33_RG_LATCH_GPIO,0)
                          |FIELD_BUILD(V33_RG_PD_GPIO,1)
                          |FIELD_BUILD(V33_RG_PD_ADC12,1)
                          |FIELD_BUILD(V33_RG_PD_AMIC,1)
                          |FIELD_BUILD(V33_RG_PD_TK,1)
                          |FIELD_BUILD(V33_RG_BOR_EN,0)
                          |FIELD_BUILD(V33_RG_BAT_DTCT_EN,0);
    V33_RG->MISC_CTRL1 = FIELD_BUILD(V33_RG_LATCH_GPIO,0)
                          |FIELD_BUILD(V33_RG_PD_GPIO,0)
                          |FIELD_BUILD(V33_RG_PD_ADC12,1)
                          |FIELD_BUILD(V33_RG_PD_AMIC,1)
                          |FIELD_BUILD(V33_RG_PD_TK,1)
                          |FIELD_BUILD(V33_RG_BOR_EN,0)
                          |FIELD_BUILD(V33_RG_BAT_DTCT_EN,0);
    spi_flash_init();
    spi_flash_release_from_deep_power_down();
    DELAY_US(8);
    spi_flash_xip_start();
    __enable_irq();
}

XIP_BANNED void deep_sleep()
{   
    cpu_flash_deep_sleep_and_recover();
}

XIP_BANNED void lvl2_lvl3_mode_prepare()
{
    power_down_config();
    REG_FIELD_WR(V33_RG->WKUP_CTRL,V33_RG_WKUP_MSK,0x08);
    REG_FIELD_WR(V33_RG->PWR_CTRL,V33_RG_LPLDO_PD_EN,1);
}

XIP_BANNED void enter_deep_sleep_mode_lvl2_lvl3()
{
    spi_flash_xip_stop();
    spi_flash_deep_power_down();
    lvl2_lvl3_mode_prepare();
    __WFI();
    while(1);
}
