#include "reg_v33_rg.h"
#include "leo.h"
#include "ls_hal_flash.h"
#include "compile_flag.h"
#include "platform.h"
#include "reg_sysc_awo.h"
#include "reg_sysc_cpu.h"
#include "field_manipulate.h"
#include "sleep.h"
#include "ls_soc_gpio.h"
#include "common.h"
#include "systick.h"
#include "sys_stat.h"
#include "cpu.h"
#include "ls_msp_qspiv2.h"
#include "csi_rv32_gcc.h"
#include "csi_core.h"
#include "ls_hal_cache.h"
#include "log.h"

static uint32_t CPU_SP;
// static uint32_t CPU_PSP;
// static uint8_t CPU_CONTROL;
extern uint32_t exception_entry;

#define ISR_VECTOR_ADDR ((uint32_t *)(0x20000000))
void cpu_sleep_asm(void);
void cpu_recover_asm(void);
void dpll_qspi_clk_config(void);
void cpu_sleep_recover_init()
{
    V33_RG->SFT_CTRL03 =(((uint32_t)cpu_recover_asm)>>1)<<24; 
}

void XIP_BANNED_FUNC(store_sp,)   
{
    CPU_SP = __get_SP();
}

void XIP_BANNED_FUNC(restore_sp,)
{
    __asm ( ".option push\n"
            ".option norelax\n"
            "la gp, __global_pointer$\n"
            ".option pop": : );
    __set_MTVEC((uint32_t)&exception_entry);
    __set_MTVT((uint32_t)interrupt_vector);
    __set_SP(CPU_SP);
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
                          |FIELD_BUILD(V33_RG_BAT_DET_CTRL,0);
    V33_RG->WKUP_CTRL = FIELD_BUILD(V33_RG_WKUP_MSK,0x79)
                        |FIELD_BUILD(V33_RG_SWD_IO_WKUP_EN,0)
                        |FIELD_BUILD(V33_RG_WKUP0_SYNC_SEL,0)
                        |FIELD_BUILD(V33_RG_WKUP1_SYNC_SEL,0);

    V33_RG->WKUP_TIM = FIELD_BUILD(V33_RG_STB_CLK_M1,0xb)
                        |FIELD_BUILD(V33_RG_STB_LDO_M1,0x1);
    V33_RG->WKUP_TIM1 = FIELD_BUILD(V33_RG_STB_BG_M1,0x0)
                        |FIELD_BUILD(V33_RG_STB_HSI_M1,0x02);
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
                          |FIELD_BUILD(V33_RG_BAT_DET_CTRL,0);
    V33_RG->MISC_CTRL1 = FIELD_BUILD(V33_RG_LATCH_GPIO,1)
                          |FIELD_BUILD(V33_RG_PD_GPIO,1)
                          |FIELD_BUILD(V33_RG_PD_ADC12,1)
                          |FIELD_BUILD(V33_RG_PD_AMIC,1)
                          |FIELD_BUILD(V33_RG_PD_TK,1)
                          |FIELD_BUILD(V33_RG_PD_DAC12,1)
                          |FIELD_BUILD(V33_RG_BAT_DET_CTRL,0);
}

static void XIP_BANNED_FUNC(gpio_pd_latch_state_exit,)
{
    V33_RG->MISC_CTRL1 = FIELD_BUILD(V33_RG_LATCH_GPIO,1)
                          |FIELD_BUILD(V33_RG_PD_GPIO,0)
                          |FIELD_BUILD(V33_RG_PD_ADC12,1)
                          |FIELD_BUILD(V33_RG_PD_AMIC,1)
                          |FIELD_BUILD(V33_RG_PD_TK,1)
                          |FIELD_BUILD(V33_RG_PD_DAC12,1)
                          |FIELD_BUILD(V33_RG_BAT_DET_CTRL,0);
    V33_RG->MISC_CTRL1 = FIELD_BUILD(V33_RG_LATCH_GPIO,0)
                          |FIELD_BUILD(V33_RG_PD_GPIO,0)
                          |FIELD_BUILD(V33_RG_PD_ADC12,1)
                          |FIELD_BUILD(V33_RG_PD_AMIC,1)
                          |FIELD_BUILD(V33_RG_PD_TK,1)
                          |FIELD_BUILD(V33_RG_PD_DAC12,1)
                          |FIELD_BUILD(V33_RG_BAT_DET_CTRL,0);
}

NOINLINE static void XIP_BANNED_FUNC(cpu_flash_deep_sleep_and_recover,)
{
    hal_flash_xip_stop();
    hal_flash_deep_power_down();
    uint8_t i;
    uint32_t GPIO_DOT[8];
    uint32_t GPIO_OE_FIR[8];
    uint32_t GPIO_IEN_OD[8];
    uint32_t GPIO_PUPD[8];
    uint32_t HSI_CAL = SYSC_AWO->PD_AWO_ANA1;
    for(i=0;i<8;++i)
    {
        GPIO_DOT[i] = SYSC_AWO->IO[i].DOT;
        GPIO_OE_FIR[i] = SYSC_AWO->IO[i].OE_FIR;
        GPIO_IEN_OD[i] = SYSC_AWO->IO[i].IEN_OD;
        GPIO_PUPD[i] = SYSC_AWO->IO[i].PUPD;
    }
    gpio_pd_latch_state_enter();
    cpu_sleep_asm();
    for(i=0;i<8;++i)
    {
        SYSC_AWO->IO[i].DOT = GPIO_DOT[i];
        SYSC_AWO->IO[i].OE_FIR = GPIO_OE_FIR[i];
        SYSC_AWO->IO[i].IEN_OD = GPIO_IEN_OD[i];
        SYSC_AWO->IO[i].PUPD = GPIO_PUPD[i];
    }
    SYSC_AWO->PD_AWO_ANA1 = HSI_CAL;
    if(hal_flash_dual_mode_get())
    {
        pinmux_hal_flash_init();
    }else
    {
        pinmux_hal_flash_quad_init();
    }
    gpio_pd_latch_state_exit();
    hal_flash_init();
    clk_flash_init();
    hal_flash_release_from_deep_power_down();
    DELAY_US(8);
    hal_flash_xip_start();
    lscache_cache_enable(1);
}

static void cpu_sleep_mode_config(uint8_t deep)
{
    uint32_t mextstaus = __get_MEXSTATUS();
    MODIFY_REG(mextstaus,MEXSTATUS_SLEEP_Msk,(!deep)<<MEXSTATUS_SLEEP_Pos);
    __set_MEXSTATUS(mextstaus);
}

static void deep_sleep_no_ble()
{
    uart_log_pause();
    cpu_sleep_mode_config(1);
    systick_stop();
    CLIC_INT_Control clicint[80];
    memcpy32((uint32_t*)clicint,(uint32_t*)&CLIC->CLICINT[0],ARRAY_LEN(clicint));
    cpu_flash_deep_sleep_and_recover();
    MODIFY_REG(CLIC->CLICCFG,CLIC_CLICCFG_NLBIT_Msk,0xf<<CLIC_CLICCFG_NLBIT_Pos);
    memcpy32((uint32_t*)&CLIC->CLICINT[0],(uint32_t*)clicint,ARRAY_LEN(clicint));
    systick_start();
    uart_log_resume();
}

static void XIP_BANNED_FUNC(light_sleep)
{
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_CLR_QSPI_MASK | SYSC_CPU_CLKG_CLR_CACHE_MASK;
    REG_FIELD_WR(SYSC_AWO->PD_AWO_CLK_CTRL,SYSC_AWO_CLK_SEL_QSPI,SDK_HSE_USED?1:2);
    __WFI();
    REG_FIELD_WR(SYSC_AWO->PD_AWO_CLK_CTRL,SYSC_AWO_CLK_SEL_QSPI,4);
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_SET_QSPI_MASK | SYSC_CPU_CLKG_SET_CACHE_MASK;
    __NOP();
    __NOP();
    __NOP();
    __NOP();
}

void low_power_mode_sched()
{
    uint32_t cpu_stat = enter_critical();
    cpu_sleep_mode_config(0);
    if((dma1_status_busy()==false) && (dma2_status_busy()==false))
    {
        if(peri_status_busy()==false)
        {
            deep_sleep_no_ble();
        }else
        {
            REG_FIELD_WR(SYSC_CPU->GATE_SYS,SYSC_CPU_GATE_SYS_EN,1);
            light_sleep();
        }
    }else
    {
        REG_FIELD_WR(SYSC_CPU->GATE_SYS,SYSC_CPU_GATE_SYS_EN,0);
        light_sleep();
    }
    exit_critical(cpu_stat);
}

static void lvl2_lvl3_mode_prepare(bool lp2_mode)
{
    V33_RG->SFT_CTRL03 &= 0x00ffffff;
    systick_stop();
    // SCB->SCR |= (1<<2);1<<2);
    V33_RG->PWR_CTRL = FIELD_BUILD(V33_RG_LPLDO_PD_EN,1)
                          |FIELD_BUILD(V33_RG_HPLDO_PD_EN,1)
                          |FIELD_BUILD(V33_RG_MSI_PD_EN,1)
                          |FIELD_BUILD(V33_RG_BG_PD_EN,0)
                          |FIELD_BUILD(V33_RG_BGIB_PD_EN,1)
                          |FIELD_BUILD(V33_RG_LSI_PD_EN,lp2_mode?(!SDK_LSI_USED):1)
                          |FIELD_BUILD(V33_RG_HSE_PD_EN,1)
                          |FIELD_BUILD(V33_RG_SRAM_DS_PD_EN,1)
                          |FIELD_BUILD(V33_RG_LSE_PD_EN,lp2_mode?SDK_LSI_USED:1)
                          |FIELD_BUILD(V33_RG_HSI_PD_EN,1)
                          |FIELD_BUILD(V33_RG_HSE_PU_EN,1)
                          |FIELD_BUILD(V33_RG_LSE_PU_EN,!SDK_LSI_USED)
                          |FIELD_BUILD(V33_RG_SRAM1_PD_EN,1)
                          |FIELD_BUILD(V33_RG_SRAM2_PD_EN,1)
                          |FIELD_BUILD(V33_RG_SRAM3_PD_EN,1)
                          |FIELD_BUILD(V33_RG_SRAM4_PD_EN,1)
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
        // V33_RG->EXTI_CTRL2 = 0x10;   //clear swd wakeup
        // V33_RG->EXTI_CTRL2 = 0x0;
        __WFI();
        hal_flash_release_from_deep_power_down();
        DELAY_US(8);
        hal_flash_xip_start();
        exit_critical(cpu_stat);
    }
}
