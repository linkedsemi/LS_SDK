#include "sdk_config.h"
#include "le501x.h"
#include "spi_flash.h"
#include "compile_flag.h"
#include "lscache.h"
#include "platform.h"
#include "modem_rf_le501x.h"
#include "reg_syscfg.h"
#include "field_manipulate.h"
#include "sleep.h"
#include "reg_rcc.h"
#include "reg_lsgpio.h"
#include "ls_dbg.h"
#include "cpu.h"
#include "io_config.h"
#include "lsrtc.h"
#include "systick.h"
#include "reg_lsgpio.h"
#include "sys_stat.h"

const uint16_t wkup_delay_us = 1500;
static uint32_t CPU_PSP;
static uint8_t CPU_CONTROL;
bool waiting_ble_wkup_irq;
static uint8_t wkup_stat;
void cpu_sleep_asm(void);

#if SDK_DCDC_BYPASS
void dcdc_off(){}
XIP_BANNED void dcdc_on(){}
#else
void dcdc_off()
{
    REG_FIELD_WR(SYSCFG->DCDC, SYSCFG_EN, 0);
}

XIP_BANNED void dcdc_on()
{
    REG_FIELD_WR(SYSCFG->DCDC, SYSCFG_EN, 1);
}

#endif

uint8_t get_deep_sleep_enable(void)
{
    return SDK_DEEP_SLEEP_ENABLE;
}

XIP_BANNED static void ble_hclk_clr()
{
    REG_FIELD_WR(RCC->BLECFG, RCC_BLE_AHBEN, 0);
}

XIP_BANNED static void normal_sleep_set()
{
    MODIFY_REG(SYSCFG->PMU_WKUP,SYSCFG_SLP_LVL_MASK,
        NORMAL_SLEEP<<SYSCFG_SLP_LVL_POS|
        (BLE_WKUP|WDT_WKUP|RTC_WKUP)<<SYSCFG_WKUP_EN_POS|
        (BLE_WKUP_EDGE_RISING|WDT_WKUP_EDGE_RISING|RTC_WKUP_EDGE_RISING)<<SYSCFG_WKUP_EDGE_POS);
}

#if DEBUG_MODE == 0
XIP_BANNED static void sleep_mode_set()
{
    SCB->SCR |= (1<<2);
    MODIFY_REG(SYSCFG->PMU_WKUP,SYSCFG_SLP_LVL_MASK,
        SLEEP_MODE0<<SYSCFG_SLP_LVL_POS|
        (BLE_WKUP|WDT_WKUP|RTC_WKUP)<<SYSCFG_WKUP_EN_POS|
        (BLE_WKUP_EDGE_RISING|WDT_WKUP_EDGE_RISING|RTC_WKUP_EDGE_RISING)<<SYSCFG_WKUP_EDGE_POS);
}
#else
XIP_BANNED static void sleep_mode_set()
{
    normal_sleep_set();
}
#endif

XIP_BANNED void before_wfi()
{
    sleep_mode_set();
    while(REG_FIELD_RD(SYSCFG->PMU_PWR, SYSCFG_BLE_PWR3_ST));
    ble_hclk_clr();
    switch_to_xo16m();
    SYSCFG->ANACFG0 &= ~(SYSCFG_EN_DPLL_MASK | SYSCFG_EN_DPLL_16M_RF_MASK | SYSCFG_EN_DPLL_128M_RF_MASK | SYSCFG_EN_DPLL_128M_EXT_MASK | SYSCFG_EN_QCLK_MASK);
}

XIP_BANNED static void wait_dpll_lock()
{
    uint32_t i = 0;
    while(1)
    {
        if(REG_FIELD_RD(SYSCFG->ANACFG0, SYSCFG_DPLL_LOCK))
        {

            break;
        }
        if(i>40)
        {
            break;
        }
        i += 1;
    }
}

static void wkup_ble()
{
    RCC->BLECFG |= RCC_BLE_WKUP_RST_MASK;
}

XIP_BANNED uint32_t __NVIC_GetPendingIRQ(IRQn_Type IRQn);

XIP_BANNED void after_wfi()
{
    LS_RAM_ASSERT(__NVIC_GetPendingIRQ(LPWKUP_IRQn)||__NVIC_GetPendingIRQ(EXTI_IRQn)||__NVIC_GetPendingIRQ(RTC_IRQn));
    wkup_stat = REG_FIELD_RD(SYSCFG->PMU_WKUP,SYSCFG_WKUP_STAT);
    REG_FIELD_WR(SYSCFG->PMU_WKUP, SYSCFG_LP_WKUP_CLR,1);
    normal_sleep_set();
    if(wkup_stat & WDT_WKUP)
    {
        while(1);
    }
    dcdc_on();
    SYSCFG->ANACFG0 |= (SYSCFG_EN_DPLL_MASK | SYSCFG_EN_DPLL_16M_RF_MASK | SYSCFG_EN_DPLL_128M_RF_MASK | SYSCFG_EN_DPLL_128M_EXT_MASK | SYSCFG_EN_QCLK_MASK);
    wait_dpll_lock();
    clk_switch();
}

void clr_ble_wkup_req()
{
    RCC->BLECFG &= ~RCC_BLE_WKUP_RST_MASK;
}

XIP_BANNED void power_up_hardware_modules()
{
    uint32_t pmu_pwr = SYSCFG->PMU_PWR;
    uint32_t clr_mask = 0;
    uint32_t set_mask = 0;
    if(pmu_pwr & ((uint32_t)SYSCFG_PERI_PWR2_ST_MASK))
    {
        clr_mask |= SYSCFG_PERI_PWR2_PD_MASK;
        set_mask |= SYSCFG_PERI_ISO2_EN_MASK;
    }
    if(pmu_pwr & ((uint32_t)SYSCFG_SEC_PWR4_ST_MASK))
    {
        clr_mask |= SYSCFG_SEC_PWR4_PD_MASK;
        set_mask |= SYSCFG_SEC_ISO4_EN_MASK;
    }
    MODIFY_REG(SYSCFG->PMU_PWR,clr_mask,set_mask);
    do{
        pmu_pwr = SYSCFG->PMU_PWR;
    }while((pmu_pwr & ((uint32_t)SYSCFG_PERI_PWR2_ST_MASK)) || (pmu_pwr & ((uint32_t)SYSCFG_SEC_PWR4_ST_MASK)));
    SYSCFG->PMU_PWR = 0;
}

XIP_BANNED static void power_down_hardware_modules()
{
    if(SYSCFG->PMU_WKUP & (PA00_IO_WKUP|PA07_IO_WKUP|PB11_IO_WKUP|PB15_IO_WKUP)<<WKUP_EN_POS)
    {
        SYSCFG->PMU_PWR = FIELD_BUILD(SYSCFG_SEC_PWR4_PD, 1)
                        | FIELD_BUILD(SYSCFG_SEC_ISO4_EN ,1);
    }else
    {
        SYSCFG->PMU_PWR = FIELD_BUILD(SYSCFG_PERI_PWR2_PD, 1)
                        | FIELD_BUILD(SYSCFG_PERI_ISO2_EN,1)
                        | FIELD_BUILD(SYSCFG_SEC_PWR4_PD, 1)
                        | FIELD_BUILD(SYSCFG_SEC_ISO4_EN ,1);
    }
}

NOINLINE XIP_BANNED static void cpu_flash_deep_sleep_and_recover()
{
    spi_flash_xip_stop();
    spi_flash_deep_power_down();
    power_down_hardware_modules();
    cpu_sleep_asm();
    power_up_hardware_modules();
    __disable_irq();
    spi_flash_init();
    spi_flash_release_from_deep_power_down();
    DELAY_US(8);
    spi_flash_xip_start();
}

XIP_BANNED uint32_t io_retention_pull(uint32_t idx,uint16_t oe,uint16_t ie,uint16_t dout,uint32_t pupd)
{
    if((1<<idx) & oe)
    {
        if((1<<idx) & dout)
        {
            return IO_PULL_UP<<(2*idx);
        }else
        {
            return IO_PULL_DOWN<<(2*idx);
        }
    }else if(((1<<idx) & ie)==0)
    {
        return IO_PULL_DOWN<<(2*idx);
    }else
    {
        return pupd&(0x3<<(2*idx));
    }
}

static void lvl2_lvl3_io_retention(reg_lsgpio_t *gpiox)
{
    uint16_t oe = gpiox->OE;
    uint16_t ie = gpiox->IE;
    uint16_t dout = gpiox->DOUT;
    uint32_t pupd = gpiox->PUPD;
    uint32_t pull = 0;
    uint8_t i;
    for(i=0;i<16;++i)
    {
        pull |= io_retention_pull(i,oe,ie,dout,pupd);
    }
    gpiox->PUPD = pull;
}

void ble_wkup_status_set(bool status)
{
    waiting_ble_wkup_irq = status;
}

void ble_hclk_set()
{
    REG_FIELD_WR(RCC->BLECFG, RCC_BLE_AHBEN, 1);
}

static void ble_radio_en_sync()
{
    LS_ASSERT(REG_FIELD_RD(SYSCFG->PMU_PWR,SYSCFG_BLE_PWR3_ST)==0);
    while(REG_FIELD_RD(SYSCFG->PMU_PWR,SYSCFG_BLE_PWR3_ST)==0);
//    io_cfg_output(PB00);
//    io_toggle_pin(PB00);
//    static uint8_t i=0;
//    if(i==1)     while(1);
//    i+=1;
//    LS_ASSERT(__NVIC_GetPendingIRQ(BLE_WKUP_IRQn)==0);
    __NVIC_ClearPendingIRQ(BLE_WKUP_IRQn);
    __NVIC_EnableIRQ(BLE_WKUP_IRQn);
}

static void lvl2_lvl3_mode_prepare(struct deep_sleep_wakeup *wakeup)
{
    NVIC->ICER[0] = 0xffffffff;
    lvl2_lvl3_io_retention(LSGPIOA);
    lvl2_lvl3_io_retention(LSGPIOB);
    uint8_t mode;
    if(wakeup->rtc || wakeup->wdt)
    {
        mode = SLEEP_MODE2;
    }else
    {
        mode = SLEEP_MODE3;
    }
    uint16_t edge_src = *(uint16_t *)wakeup;
    uint8_t edge = edge_src >> 8;
    edge |= RTC_WKUP | NRST_IO_WKUP | BLE_WKUP | WDT_WKUP;
    uint8_t src = edge_src & 0xff;
    src &= ~BLE_WKUP;
    SYSCFG->PMU_WKUP = FIELD_BUILD(SYSCFG_SLP_LVL, mode) 
                      | FIELD_BUILD(SYSCFG_WKUP_EDGE,edge)
                      | FIELD_BUILD(SYSCFG_WKUP_EN, src);
    SYSCFG->PMU_PWR = 0; 
    SCB->SCR |= (1<<2);
}

XIP_BANNED void enter_deep_sleep_mode_lvl2_lvl3(struct deep_sleep_wakeup *wakeup)
{
    lvl2_lvl3_mode_prepare(wakeup);
    spi_flash_xip_stop();
    spi_flash_deep_power_down();
    uint16_t c_oe = LSGPIOC->OE;
    uint16_t c_ie = LSGPIOC->IE;
    uint16_t c_dout = LSGPIOC->DOUT;
    uint32_t c_pupd = LSGPIOC->PUPD;
    uint32_t pull0 = io_retention_pull(0,c_oe, c_ie, c_dout, c_pupd);
    uint32_t pull1 = io_retention_pull(1,c_oe, c_ie, c_dout, c_pupd);
    LSGPIOC->PUPD = 0x5550|pull1|pull0;
    __WFI();
    while(1);
}

void deep_sleep()
{
    NVIC->ICER[0] = ~(1<<LPWKUP_IRQn|1<<EXTI_IRQn|1 << RTC_IRQn);
    SCB->ICSR = SCB_ICSR_PENDSVCLR_Msk;
    systick_stop();
    lvd33_disable();
    cpu_flash_deep_sleep_and_recover();
    rco_freq_counting_config();
    wkup_ble();
    lvd33_enable();
    irq_reinit();
    ble_wkup_status_set(true);
    ble_radio_en_sync();
    systick_start();
    rco_freq_counting_start();
}

void uart_log_pause(void);
void uart_log_resume(void);
__attribute__((weak)) bool mac_sleep_check(){return false;}

__attribute((weak)) void check_and_sleep()
{
    if(mac_sleep_check())
    {
        deep_sleep();
    }
}

void sleep_process()
{
    uint32_t cpu_stat = enter_critical();
    uart_log_pause();
    if((peri_status_busy() || app_event_status_busy())==false)
    {
        check_and_sleep();
    }
    uart_log_resume();
    exit_critical(cpu_stat);
}

bool timer_sleep(void);
void deep_sleep_no_ble()
{
    uint32_t cpu_stat = enter_critical();
    uart_log_pause();
    if(timer_sleep())
    {
        deep_sleep();
    }
    uart_log_resume();
    exit_critical(cpu_stat);
}

bool ble_wkup_status_get(void)
{
    return waiting_ble_wkup_irq;
}

static bool exti_int_pending(uint8_t pin)
{
    uint8_t idx = pin&0xf;
    uint8_t port = pin>>4;
    if(EXTI->EEIFM & 1<<idx)
    {
        if(idx<8)
        {
            if((EXTI->EICFG0 >> (4*idx) & 0xf)==port)
            {
                return true;
            }
        }else
        {
            if((EXTI->EICFG1 >> (4*(idx-8)) & 0xf)==port)
            {
                return true;
            }
        }
    }
    return false;
}

void LPWKUP_Handler(void)
{
    SYSCFG->PMU_WKUP &= ~(wkup_stat << WKUP_EN_POS);
    SYSCFG->PMU_WKUP |= wkup_stat << WKUP_EN_POS;
    if(wkup_stat&PB15_IO_WKUP)
    {
        if(exti_int_pending(PB15)==false)
        {
            io_exti_callback(PB15);
        }
    }
    if(wkup_stat&PA00_IO_WKUP)
    {
        if(exti_int_pending(PA00)==false)
        {
            io_exti_callback(PA00);
        }
    }
    if(wkup_stat&PA07_IO_WKUP)
    {
        if(exti_int_pending(PA07)==false)
        {
            io_exti_callback(PA07);
        }
    }
    if(wkup_stat&PB11_IO_WKUP)
    {
        if(exti_int_pending(PB11)==false)
        {
            io_exti_callback(PB11);
        }
    }
    if (wkup_stat & RTC_WKUP)
    {
        if (__NVIC_GetPendingIRQ(RTC_IRQn) == 0)
        {
            rtc_wkup_callback();
        }
    }
}

void BLE_WKUP_IRQ_DISABLE()
{
    __NVIC_DisableIRQ(BLE_WKUP_IRQn);
}

XIP_BANNED uint64_t store_psp_return_msp_and_addr()
{
    CPU_CONTROL = __get_CONTROL();
    CPU_PSP = __get_PSP();
    return __get_MSP();
}

XIP_BANNED void restore_psp()
{
    __set_PSP(CPU_PSP);
    __set_CONTROL(CPU_CONTROL);
}
