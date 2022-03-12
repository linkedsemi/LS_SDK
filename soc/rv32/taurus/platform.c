#include <string.h>
#include "taurus.h"
#include "core_rv32.h"
#include "swint_call_asm.h"
#include "field_manipulate.h"
#include "systick.h"
#include "cpu.h"
#include "log.h"
#include "compile_flag.h"
#include "reg_sysc_awo.h"
#include "platform.h"
#include "spi_flash.h"
#include "lscache.h"
#include "io_config.h"
#include "reg_sysc_ble.h"
#include "tinyfs.h"
#include "exception_isr.h"
#include "reg_v33_rg.h"
#include "evt_ctrl.h"
void ble_pkt_isr(void);
void ble_util_isr(void);
void SWINT_Handler_ASM(void);
void swint2_process(void);
void main_task_app_init(void);
void main_task_itf_init(void);
void stack_var_ptr_init(void);
void modem_rf_init(void);

static bool lock_check()
{
    if(REG_FIELD_RD(SYSC_AWO->ANA_STAT,SYSC_AWO_DPLL_LOCK)==0)
    {
        return false;
    }
    DELAY_US(1000);
    return REG_FIELD_RD(SYSC_AWO->ANA_STAT,SYSC_AWO_DPLL_LOCK);
}

void pll_enable()
{
    while(lock_check()==false)
    {
        REG_FIELD_WR(SYSC_AWO->PD_AWO_ANA0,SYSC_AWO_AWO_EN_DPLL,0);
        SYSC_AWO->PD_AWO_ANA0 |= SYSC_AWO_AWO_DPLL_SEL_REF_24M_MASK | SYSC_AWO_AWO_EN_QCLK_MASK | SYSC_AWO_AWO_EN_DPLL_16M_RF_MASK | SYSC_AWO_AWO_EN_DPLL_128M_RF_MASK | SYSC_AWO_AWO_EN_DPLL_128M_EXT_MASK | SYSC_AWO_AWO_EN_DPLL_48M_EXT_MASK;
        REG_FIELD_WR(SYSC_AWO->PD_AWO_ANA0,SYSC_AWO_AWO_EN_DPLL,1);
        REG_FIELD_WR(SYSC_AWO->PD_AWO_ANA0,SYSC_AWO_AWO_EN_DPLL,0);
        REG_FIELD_WR(SYSC_AWO->PD_AWO_ANA0,SYSC_AWO_AWO_DPLL_SEL_REF_24M,0);
        REG_FIELD_WR(SYSC_AWO->PD_AWO_ANA0,SYSC_AWO_AWO_EN_DPLL,1);
        DELAY_US(10000);
    }
    MODIFY_REG(SYSC_AWO->PD_AWO_CLK_CTRL,SYSC_AWO_CLK_SEL_QSPI_MASK,4<<SYSC_AWO_CLK_SEL_QSPI_POS);
}

__attribute__((weak)) void SystemInit(){
    clk_switch();
    disable_global_irq();
    qspi_flash_io_init();
    spi_flash_drv_var_init(false,false);
    spi_flash_init();
    spi_flash_software_reset();
    DELAY_US(500);
    spi_flash_xip_start();
    lscache_cache_enable(0);
    enable_global_irq();
}

bool mac_lp_irq_status_get()
{
    return csi_vic_get_pending_irq(MAC_LP_IRQn);
}

void mac_lp_irq_clr_reset()
{
    REG_FIELD_WR(V33_RG->MISC_CTRL0,V33_RG_MAC_SLP_INTR_CLR,0);
}

void mac_wakeup_prepare_time_set(uint16_t time)
{
    V33_RG->MAC_WAKEUP_PREPARE_TIME = time;
}

void mac_clk_clr()
{
    SYSC_BLE->PD_BLE_CLKG = SYSC_BLE_CLKG_CLR_MAC_MASK;
}

void mac_clk_set()
{
    SYSC_BLE->PD_BLE_CLKG = SYSC_BLE_CLKG_SET_MAC_MASK;
}

void mac_srst()
{
    SYSC_BLE->PD_BLE_SRST = SYSC_BLE_SRST_CLR_MAC_N_MASK;
    SYSC_BLE->PD_BLE_SRST = SYSC_BLE_SRST_SET_MAC_N_MASK;
}

void idle_process()
{
    uint32_t cpu_stat = enter_critical();
    uint32_t sleep_dur = mac_sleep();
    if(sleep_dur)
    {
        mac_wakeup_prepare_time_set(30);
        mac_lp_irq_clr_reset();
        mac_sleep_status_sync();
        mac_clk_clr();
        while(mac_lp_irq_status_get()==false);
        mac_srst();
        mac_clk_set();
        mac_hw_init();
    }else
    {

    }
    exit_critical(cpu_stat);
}

void irq_priority()
{
    MODIFY_REG(CLIC->CLICCFG,CLIC_CLICCFG_NLBIT_Msk,0xf<<CLIC_CLICCFG_NLBIT_Pos);
    csi_vic_set_prio(RV_SOFT_IRQn,4);
    csi_vic_set_prio(RV_TIME_IRQn,5);
    csi_vic_set_prio(RTC1_IRQn,0);
    csi_vic_set_prio(IWDT_IRQn,0);
    csi_vic_set_prio(RTC2_IRQn,0);
    csi_vic_set_prio(EXT_IRQn,0);
    csi_vic_set_prio(LVD33_IRQn,0);
    csi_vic_set_prio(MAC_LP_IRQn,5);
    csi_vic_set_prio(MAC1_IRQn,7);
    csi_vic_set_prio(MAC2_IRQn,5);
    csi_vic_set_prio(SWINT1_IRQn,5);
    csi_vic_set_prio(USB_IRQn,0);
    csi_vic_set_prio(QSPI_IRQn,0);
    csi_vic_set_prio(CACHE_IRQn,0);
    csi_vic_set_prio(GPTIMA1_IRQn,0);
    csi_vic_set_prio(GPTIMB1_IRQn,0);
    csi_vic_set_prio(GPTIMC1_IRQn,0);
    csi_vic_set_prio(ADTIM1_IRQn,0);
    csi_vic_set_prio(I2C1_IRQn,0);
    csi_vic_set_prio(I2C2_IRQn,0);
    csi_vic_set_prio(I2C3_IRQn,0);
    csi_vic_set_prio(UART1_IRQn,0);
    csi_vic_set_prio(UART2_IRQn,0);
    csi_vic_set_prio(UART3_IRQn,0);
    csi_vic_set_prio(SPI2_IRQn,0);
    csi_vic_set_prio(GPIO_IRQn,0);
    csi_vic_set_prio(WWDT_IRQn,0);
    csi_vic_set_prio(ADC_IRQn,0);
    csi_vic_set_prio(TK_IRQn,0);
    csi_vic_set_prio(SWINT2_IRQn,5);
    csi_vic_set_prio(SWINT3_IRQn,0);
}

static void MAC_LP_Handler()
{
    REG_FIELD_WR(V33_RG->MISC_CTRL0,V33_RG_MAC_SLP_INTR_CLR,1);
}

static void ble_irq_handler_set()
{
    rv_set_int_isr(MAC_LP_IRQn,MAC_LP_Handler);
    rv_set_int_isr(MAC1_IRQn,ble_pkt_isr);
    rv_set_int_isr(MAC2_IRQn,ble_util_isr);
    rv_set_int_isr(SWINT1_IRQn,SWINT_Handler_ASM);
    rv_set_int_isr(SWINT2_IRQn,swint2_process);
}

static void ble_irq_config()
{
    csi_vic_enable_irq(MAC_LP_IRQn);
    csi_vic_enable_irq(MAC1_IRQn);
    csi_vic_enable_irq(MAC2_IRQn);
    CLIC->CLICINT[SWINT1_IRQn].ATTR = 1 << CLIC_INTATTR_TRIG_Pos;
    csi_vic_enable_irq(SWINT1_IRQn);
    CLIC->CLICINT[SWINT2_IRQn].ATTR = 1 << CLIC_INTATTR_TRIG_Pos;
    csi_vic_enable_irq(SWINT2_IRQn);
}

static void flash_swint_handler_set()
{
    rv_set_int_isr(RV_SOFT_IRQn,SWINT_Handler_ASM);
}

static void flash_swint_enable()
{
    CLIC->CLICINT[RV_SOFT_IRQn].ATTR = 1 << CLIC_INTATTR_TRIG_Pos;
    csi_vic_enable_irq(RV_SOFT_IRQn);
}

static void module_init()
{
    V33_RG->CLKG_SRST = V33_RG_CLKG_SET_MAC_SLP_MASK | V33_RG_SRST_SET_MAC_SLP_N_MASK;
    REG_FIELD_WR(V33_RG->MISC_CTRL0,V33_RG_MAC_SLP_INTR_EN,1);
    LOG_INIT();
    irq_priority();
    flash_swint_handler_set();
    ble_irq_handler_set();
    flash_swint_enable();
    ble_irq_config();
    mac_clk_set();
    tinyfs_init(0x855000);
    modem_rf_init();
    systick_start();
}

#if defined(__CC_ARM)
__attribute__((weak)) uint32_t __stack_bss_start__;
__attribute__((weak)) uint32_t __stack_bss_end__;
__attribute__((weak)) uint32_t __stack_data_lma__;
__attribute__((weak)) uint32_t __stack_data_end__;
__attribute__((weak)) uint32_t __stack_data_start__;
#elif defined(__GNUC__)
extern uint32_t __stack_bss_start__;
extern uint32_t __stack_bss_end__;
extern uint32_t __stack_data_lma__;
extern uint32_t __stack_data_end__;
extern uint32_t __stack_data_start__;
#endif
static void stack_data_bss_init()
{
    memset(&__stack_bss_start__,0,(uint32_t)&__stack_bss_end__-(uint32_t)&__stack_bss_start__);
    memcpy(&__stack_data_start__,&__stack_data_lma__,(uint32_t)&__stack_data_end__-(uint32_t)&__stack_data_start__);
}

static void var_init()
{
    stack_data_bss_init();
    stack_var_ptr_init();
    //spi_flash_drv_var_init(true,false);
}

static void analog_init()
{
    clk_switch();
}

void sys_init_itf()
{
    analog_init();
    var_init();
    main_task_itf_init();
    module_init();
}

void sys_init_app()
{
    analog_init();
    var_init();
    main_task_app_init();
    module_init();
}

XIP_BANNED void flash_swint_set()
{
    SWINT_SET_INLINE_ASM(RV_SOFT_IRQn);
}

void clk_switch(void)
{
    pll_enable();
}

void sys_init_none()
{
    analog_init();
    LOG_INIT();
    systick_start();
}

void platform_reset(uint32_t error)
{
    while(1);
}

int _close (int fildes){  return -1;}

int _fstat (int fildes,void *st){  return -1;}

int _isatty (int file){  return 0;}

int _read (int file,char *ptr,int len){  return -1;}

int _lseek (int   file,int   ptr,int   dir){  return -1;}
