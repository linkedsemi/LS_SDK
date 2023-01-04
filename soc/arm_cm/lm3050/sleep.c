#include "reg_v33_rg_type.h"
#include "lm3050.h"
#include "ls_hal_flash.h"
#include "compile_flag.h"
#include "platform.h"
#include "reg_sysc_awo_type.h"
#include "reg_v33_rg_type.h"
#include "reg_sysc_cpu_type.h"
#include "field_manipulate.h"
#include "sleep.h"
#include "ls_soc_gpio.h"
#include "common.h"
#include "systick.h"
#include "sys_stat.h"
#include "cpu.h"
#include "ls_msp_qspiv2.h"
static uint32_t CPU_MSP;
static uint32_t CPU_PSP;
static uint8_t CPU_CONTROL;
#define ISR_VECTOR_ADDR ((uint32_t *)(0x20000000))
void cpu_sleep_asm(void);
void cpu_recover_asm(void);
void dpll_qspi_clk_config(void);
void cpu_sleep_recover_init()
{
    V33_RG->SFT_CTRL03 =(((uint32_t)cpu_recover_asm)>>1)<<24; 
}

void XIP_BANNED_FUNC(store_msp_psp_control,)   
{
    CPU_CONTROL = __get_CONTROL();
    CPU_PSP = __get_PSP();
    CPU_MSP = __get_MSP();
}

void XIP_BANNED_FUNC(restore_msp_psp_control,)
{
    __set_MSP(CPU_MSP);
    __set_PSP(CPU_PSP);
    __set_CONTROL(CPU_CONTROL);
}

void XIP_BANNED_FUNC(before_wfi,)
{

}

void XIP_BANNED_FUNC(after_wfi,)
{

}

void sleep_wakeup_config()
{
    V33_RG->PWR_CTRL = FIELD_BUILD(V33_RG_LPLDO_PD_EN,0)
                          |FIELD_BUILD(V33_RG_HPLDO_PD_EN,1)
                          |FIELD_BUILD(V33_RG_MSI_PD_EN,1)
                          |FIELD_BUILD(V33_RG_BG_PD_EN,0)
                          |FIELD_BUILD(V33_RG_BGIB_PD_EN,1)
                          |FIELD_BUILD(V33_RG_LSI_PD_EN,!SDK_LSI_USED)
                          |FIELD_BUILD(V33_RG_HSE_PD_EN,1)
                          |FIELD_BUILD(V33_RG_SRAM_DS_PD_EN,1)
                          |FIELD_BUILD(V33_RG_LSE_PD_EN,SDK_LSI_USED)
                          |FIELD_BUILD(V33_RG_HSI_PD_EN,1)
                          |FIELD_BUILD(V33_RG_HSE_PU_EN,SDK_HSE_USED)
                          |FIELD_BUILD(V33_RG_LSE_PU_EN,!SDK_LSI_USED)
                          |FIELD_BUILD(V33_RG_SRAM1_PD_EN,SDK_SRAM1_PWR_DOWN)
                          |FIELD_BUILD(V33_RG_SRAM2_PD_EN,SDK_SRAM2_PWR_DOWN)
                          |FIELD_BUILD(V33_RG_SRAM3_PD_EN,SDK_SRAM3_PWR_DOWN)
                          |FIELD_BUILD(V33_RG_SRAM4_PD_EN,SDK_SRAM4_PWR_DOWN)
                          |FIELD_BUILD(V33_RG_SRAM_DS_PU_EN,1)
                          |FIELD_BUILD(V33_RG_RCO_BIAS_FC,0)
                          |FIELD_BUILD(V33_RG_HPSW_PU_LATE,1)
                          |FIELD_BUILD(V33_RG_PD_GPIO_SEL,SYSC_AWO->DBG_ACK);
    V33_RG->MISC_CTRL1 = FIELD_BUILD(V33_RG_LATCH_GPIO,0)
                          |FIELD_BUILD(V33_RG_PD_GPIO,0)
                          |FIELD_BUILD(V33_RG_PD_ADC12,1)
                          |FIELD_BUILD(V33_RG_PD_AMIC,1)
                          |FIELD_BUILD(V33_RG_PD_TK,1)
                          |FIELD_BUILD(V33_RG_PD_DAC12,1)
                          |FIELD_BUILD(V33_RG_BAT_DTCT_EN,0);
    V33_RG->WKUP_CTRL = FIELD_BUILD(V33_RG_WKUP_MSK,0x3d)
                        |FIELD_BUILD(V33_RG_SWD_IO_WKUP_EN,0)
                        |FIELD_BUILD(V33_RG_WKUP0_SYNC_SEL,0)
                        |FIELD_BUILD(V33_RG_WKUP1_SYNC_SEL,0);

    V33_RG->WKUP_TIM = FIELD_BUILD(V33_RG_STB_CLK_M1,0xfff)
                        |FIELD_BUILD(V33_RG_STB_LDO_M1,0x3ff);
    V33_RG->WKUP_TIM1 = FIELD_BUILD(V33_RG_STB_BG_M1,0x3fff);
}

void low_power_init()
{
    cpu_sleep_recover_init();
    sleep_wakeup_config();
}

static void XIP_BANNED_FUNC(gpio_pd_latch_state_enter,)
{
    V33_RG->MISC_CTRL1 = FIELD_BUILD(V33_RG_LATCH_GPIO,1)
                          |FIELD_BUILD(V33_RG_PD_GPIO,0)
                          |FIELD_BUILD(V33_RG_PD_ADC12,1)
                          |FIELD_BUILD(V33_RG_PD_AMIC,1)
                          |FIELD_BUILD(V33_RG_PD_TK,1)
                          |FIELD_BUILD(V33_RG_PD_DAC12,1)
                          |FIELD_BUILD(V33_RG_BAT_DTCT_EN,0);
    V33_RG->MISC_CTRL1 = FIELD_BUILD(V33_RG_LATCH_GPIO,1)
                          |FIELD_BUILD(V33_RG_PD_GPIO,1)
                          |FIELD_BUILD(V33_RG_PD_ADC12,1)
                          |FIELD_BUILD(V33_RG_PD_AMIC,1)
                          |FIELD_BUILD(V33_RG_PD_TK,1)
                          |FIELD_BUILD(V33_RG_PD_DAC12,1)
                          |FIELD_BUILD(V33_RG_BAT_DTCT_EN,0);
}

static void XIP_BANNED_FUNC(gpio_pd_latch_state_exit,)
{
    V33_RG->MISC_CTRL1 = FIELD_BUILD(V33_RG_LATCH_GPIO,1)
                          |FIELD_BUILD(V33_RG_PD_GPIO,0)
                          |FIELD_BUILD(V33_RG_PD_ADC12,1)
                          |FIELD_BUILD(V33_RG_PD_AMIC,1)
                          |FIELD_BUILD(V33_RG_PD_TK,1)
                          |FIELD_BUILD(V33_RG_PD_DAC12,1)
                          |FIELD_BUILD(V33_RG_BAT_DTCT_EN,0);
    V33_RG->MISC_CTRL1 = FIELD_BUILD(V33_RG_LATCH_GPIO,0)
                          |FIELD_BUILD(V33_RG_PD_GPIO,0)
                          |FIELD_BUILD(V33_RG_PD_ADC12,1)
                          |FIELD_BUILD(V33_RG_PD_AMIC,1)
                          |FIELD_BUILD(V33_RG_PD_TK,1)
                          |FIELD_BUILD(V33_RG_PD_DAC12,1)
                          |FIELD_BUILD(V33_RG_BAT_DTCT_EN,0);
}

NOINLINE static void XIP_BANNED_FUNC(cpu_flash_deep_sleep_and_recover,)
{
    hal_flash_xip_stop();
    hal_flash_deep_power_down();
    uint8_t i;
    uint32_t GPIO_OE_DOT[4];
    uint32_t GPIO_IEN_OD[4];
    uint32_t GPIO_PUPD[4];
    for(i=0;i<4;++i)
    {
        GPIO_OE_DOT[i] = SYSC_AWO->IO[i].OE_DOT;
        GPIO_IEN_OD[i] = SYSC_AWO->IO[i].IEN_OD;
        GPIO_PUPD[i] = SYSC_AWO->IO[i].PUPD;
    }
    gpio_pd_latch_state_enter();
    cpu_sleep_asm();
    __disable_irq();
    for(i=0;i<4;++i)
    {
        SYSC_AWO->IO[i].OE_DOT = GPIO_OE_DOT[i];
        SYSC_AWO->IO[i].IEN_OD = GPIO_IEN_OD[i];
        SYSC_AWO->IO[i].PUPD = GPIO_PUPD[i];
    }
    gpio_pd_latch_state_exit();
    hal_flash_init();
    clk_flash_init();
    hal_flash_release_from_deep_power_down();
    DELAY_US(8);
    hal_flash_xip_start();
}

void io_irq_enable(void);

static void deep_sleep_no_ble()
{
    uint32_t cpu_stat = enter_critical();
    SCB->SCR |= (1<<2);
    systick_stop();
    uint32_t NVIC_EN[CEILING(IRQn_Max,32)];
    memcpy32(NVIC_EN,(uint32_t *)NVIC->ISER,ARRAY_LEN(NVIC_EN));
    uint32_t NVIC_IP[CEILING(IRQn_Max,4)];
    memcpy32(NVIC_IP,(uint32_t *)NVIC->IP,ARRAY_LEN(NVIC_IP));
    cpu_flash_deep_sleep_and_recover();
    SCB->VTOR = (uint32_t)ISR_VECTOR_ADDR;
    memcpy32((uint32_t *)NVIC->IP,NVIC_IP,ARRAY_LEN(NVIC_IP));
    memcpy32((uint32_t *)NVIC->ISER,NVIC_EN,ARRAY_LEN(NVIC_EN));
    io_irq_enable();
    systick_start();
    SCB->SCR &= ~(1<<2);
    exit_critical(cpu_stat);
}

void low_power_mode_sched()
{
    if(dma_status_busy()==false)
    {
        if(peri_status_busy()==false)
        {
            deep_sleep_no_ble();
        }else
        {
            REG_FIELD_WR(SYSC_CPU->GATE_SYS,SYSC_CPU_GATE_SYS_EN,1);
            __WFI();
        }
    }else
    {
        REG_FIELD_WR(SYSC_CPU->GATE_SYS,SYSC_CPU_GATE_SYS_EN,0);
        __WFI();
    }
}

static void lvl2_lvl3_mode_prepare(bool lp2_mode)
{
    V33_RG->SFT_CTRL03 &= 0x00ffffff;
    systick_stop();
    SCB->SCR |= (1<<2);
    V33_RG->PWR_CTRL = FIELD_BUILD(V33_RG_LPLDO_PD_EN,1)
                          |FIELD_BUILD(V33_RG_HPLDO_PD_EN,1)
                          |FIELD_BUILD(V33_RG_MSI_PD_EN,1)
                          |FIELD_BUILD(V33_RG_BG_PD_EN,0)
                          |FIELD_BUILD(V33_RG_BGIB_PD_EN,1)
                          |FIELD_BUILD(V33_RG_LSI_PD_EN,lp2_mode?(!SDK_LSI_USED):0)
                          |FIELD_BUILD(V33_RG_HSE_PD_EN,1)
                          |FIELD_BUILD(V33_RG_SRAM_DS_PD_EN,1)
                          |FIELD_BUILD(V33_RG_LSE_PD_EN,lp2_mode?SDK_LSI_USED:0)
                          |FIELD_BUILD(V33_RG_HSI_PD_EN,1)
                          |FIELD_BUILD(V33_RG_HSE_PU_EN,SDK_HSE_USED)
                          |FIELD_BUILD(V33_RG_LSE_PU_EN,!SDK_LSI_USED)
                          |FIELD_BUILD(V33_RG_SRAM1_PD_EN,SDK_SRAM1_PWR_DOWN)
                          |FIELD_BUILD(V33_RG_SRAM2_PD_EN,SDK_SRAM2_PWR_DOWN)
                          |FIELD_BUILD(V33_RG_SRAM3_PD_EN,SDK_SRAM3_PWR_DOWN)
                          |FIELD_BUILD(V33_RG_SRAM4_PD_EN,SDK_SRAM4_PWR_DOWN)
                          |FIELD_BUILD(V33_RG_SRAM_DS_PU_EN,1)
                          |FIELD_BUILD(V33_RG_RCO_BIAS_FC,0)
                          |FIELD_BUILD(V33_RG_HPSW_PU_LATE,1)
                          |FIELD_BUILD(V33_RG_PD_GPIO_SEL,1);
    
}

void XIP_BANNED_FUNC(enter_deep_sleep_mode_lvl2_lvl3,bool lp2_mode)
{
    lvl2_lvl3_mode_prepare(lp2_mode);
    while(1)
    {
        uint32_t cpu_stat = enter_critical();
        hal_flash_xip_stop();
        hal_flash_deep_power_down();
        V33_RG->EXTI_CTRL2 = 0x10;   //clear swd wakeup
        V33_RG->EXTI_CTRL2 = 0x0;
        __WFI();
        hal_flash_release_from_deep_power_down();
        DELAY_US(8);
        hal_flash_xip_start();
        exit_critical(cpu_stat);
    }
}
