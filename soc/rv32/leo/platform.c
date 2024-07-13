
#include "compile_flag.h"
#include "platform.h"
#include "cpu.h"
#include "log.h"
#include "swint_call_asm.h"
#include "systick.h"
#include "reg_sysc_awo.h"
#include "ls_hal_flash.h"
#include "exception_isr.h"
#include "reg_v33_rg.h"
#include "ls_soc_gpio.h"
#include "field_manipulate.h"
#include "sleep.h"
#include "ls_msp_qspiv2.h"
#include "sw_timer.h"
#include "reg_sysc_per.h"
#include "ls_msp_timer.h"
#include "ls_hal_pis.h"

#define PMU_CLK_VAL (SDK_HSE_USED << V33_RG_CLK_SET_HSE_POS | 1 << V33_RG_CLK_SET_HSI_POS | (!SDK_LSI_USED) << V33_RG_CLK_SET_LSE_POS)

__attribute__((aligned(64))) void (*interrupt_vector[IRQn_MAX])();

void rv_set_int_isr(uint8_t type,void (*isr)())
{
    interrupt_vector[type] = isr;
}

__attribute__((weak)) void SystemInit(){
    e906_init();
    MODIFY_REG(V33_RG->TRIM0,V33_RG_HSE_CTRL_MASK,7<<V33_RG_HSE_CTRL_POS);
    REG_FIELD_WR(V33_RG->RST_SFT, V33_RG_CLK_SEL_LS, SDK_LSI_USED ? 1 : 2);
    V33_RG->PMU_SET_VAL = PMU_CLK_VAL;
    V33_RG->PMU_SET_VAL = V33_RG_PMU_SET_TGGL_MASK | PMU_CLK_VAL;
    V33_RG->PMU_SET_VAL = PMU_CLK_VAL;
    if(SDK_HSE_USED)
    {//delay for hse stabilization
        rv32_delay_asm(14400,1);
    }
    enable_global_irq();
}

static inline void shut_down_hsi()
{
    V33_RG->PMU_SET_VAL = 1 << V33_RG_CLK_SET_HSE_POS | (!SDK_LSI_USED) << V33_RG_CLK_SET_LSE_POS;
    V33_RG->PMU_SET_VAL = V33_RG_PMU_SET_TGGL_MASK | 1 << V33_RG_CLK_SET_HSE_POS | (!SDK_LSI_USED) << V33_RG_CLK_SET_LSE_POS;
    V33_RG->PMU_SET_VAL = 1 << V33_RG_CLK_SET_HSE_POS | (!SDK_LSI_USED) << V33_RG_CLK_SET_LSE_POS;
}

static void XIP_BANNED_FUNC(clk_switch,)
{
    hclk_set(SDK_HCLK_MHZ);
    if(SDK_HSE_USED)
    {
        shut_down_hsi();
    }
}

void XIP_BANNED_FUNC(dpll_qspi_clk_config,)
{
    if(SYSC_AWO->ANA_STAT & SYSC_AWO_DPLL_LOCK_MASK)
    {
        return;
    }
    uint8_t ndiv;
    if(SDK_HSE_USED)
    {
        switch (SDK_HSE_MHZ)
        {
        case 16:
            ndiv = 8;
            break;
        case 24:
        default:
            ndiv = 5;
            break;
        }
    }
    else
    {
        ndiv = 5;
    }
    SYSC_AWO->PD_AWO_ANA0 = FIELD_BUILD(SYSC_AWO_AWO_DPLL_EN,1) |
                            FIELD_BUILD(SYSC_AWO_AWO_DPLL_SEL_REF_24M,!SDK_HSE_USED) |
                            FIELD_BUILD(SYSC_AWO_AWO_DPLL_SEL_144M,1) |
                            FIELD_BUILD(SYSC_AWO_AWO_DPLL_EN_48M,1) |
                            FIELD_BUILD(SYSC_AWO_AWO_DPLL_EN_128M,1) |
                            FIELD_BUILD(SYSC_AWO_AWO_DPLL_LOCK_BYPS,0) |
                            FIELD_BUILD(SYSC_AWO_AWO_DPLL_DPLL_TESTEN,0) |
                            FIELD_BUILD(SYSC_AWO_AWO_DPLL_NDIV, ndiv);
    rv32_delay_asm(50,1);
    REG_FIELD_WR(SYSC_AWO->PD_AWO_CLK_CTRL,SYSC_AWO_CLK_SEL_QSPI,4);
}

NOINLINE void XIP_BANNED_FUNC(clk_flash_init,)
{
    dpll_qspi_clk_config();
    MODIFY_REG(LSQSPIV2->QSPI_CTRL1,LSQSPIV2_MODE_DAC_MASK|LSQSPIV2_CAP_DLY_MASK|LSQSPIV2_CAP_NEG_MASK,
                1<<LSQSPIV2_MODE_DAC_POS|QSPI_CAPTURE_DELAY<<LSQSPIV2_CAP_DLY_POS|QSPI_CAPTURE_NEG<<LSQSPIV2_CAP_NEG_POS);
    clk_switch();
}

static void set_all_irq_priority_to_lowest_level()
{
    uint8_t i;
    for(i=0;i<IRQn_MAX;++i)
    {
        csi_vic_set_prio(i,0);
    }
}

static void flash_swint_init()
{
    rv_set_int_isr(FLASH_SWINT_NUM,FLASH_SWINT_HANDLER);
    CLIC->CLICINT[FLASH_SWINT_NUM].ATTR = 1 << CLIC_INTATTR_TRIG_Pos;
    csi_vic_set_prio(FLASH_SWINT_NUM,0xf);
    csi_vic_clear_pending_irq(FLASH_SWINT_NUM);
    csi_vic_enable_irq(FLASH_SWINT_NUM);
}
void sys_init_none()
{
    clk_flash_init();
    set_all_irq_priority_to_lowest_level();
    flash_swint_init();
    hal_flash_xip_func_ptr_init();
    io_init();
    LOG_INIT();
    low_power_init();
    systick_start();
    sw_timer_module_init();
    HAL_PIS_Init();
}

void platform_reset(uint32_t error)
{
    REG_FIELD_WR(V33_RG->RST_SFT, V33_RG_RST_FROM_SFT, 1);
}

void key_reset(uint32_t seconds, uint8_t pin, bool voltage_level)
{
    gpio_port_pin_t *x = (gpio_port_pin_t *)&pin;
    if (x->port > 1)
        return;
    io_cfg_input(pin);
    io_pull_write(pin, voltage_level ? IO_PULL_DOWN : IO_PULL_UP);

    uint16_t sel = ((x->port == 0) ? 0x0 : 0x10) | (x->num & 0xf);
    REG_FIELD_WR(V33_RG->MISC_CTRL0, V33_RG_LKRST_SEL, sel);
    REG_FIELD_WR(V33_RG->MISC_CTRL0, V33_RG_LKRST_TIM, seconds);
    REG_FIELD_WR(V33_RG->MISC_CTRL0, V33_RG_LKRST_POL, voltage_level);
    REG_FIELD_WR(V33_RG->MISC_CTRL0, V33_RG_LKRST_EN, 1);
}

void XIP_BANNED_FUNC(sync_for_xip_stop,)
{
    while((SYSC_AWO->IO[3].DIN&1<<8)==0);
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

uint32_t get_hclk_mhz()
{
    return SDK_HCLK_MHZ;
}

void rng_init()
{
    /* TIMER */
    SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_GPTIMB1_MASK;
    SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_CLR_GPTIMB1_N_MASK;
    SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_SET_GPTIMB1_N_MASK;
    SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_SET_GPTIMB1_MASK;

    LSGPTIMB->PSC = 0;
    LSGPTIMB->ARR = 0xFFFFFFFF;
    REG_FIELD_WR(LSGPTIMB->CR1, TIMER_CR1_DIR, 0);
    REG_FIELD_WR(LSGPTIMB->CCMR1, TIMER_CCMR1_CC1S, 0x3);
    REG_FIELD_WR(LSGPTIMB->SMCR, TIMER_SMCR_TS, 0);
    REG_FIELD_WR(LSGPTIMB->SMCR, TIMER_SMCR_SMS, 6);

    /* PIS */
    HAL_PIS_Config(0, CLK_LS, GPTIMB1_ITR0, PIS_SYNC_SRC_LEVEL, PIS_EDGE_NONE);
}

uint32_t GenerateRandom32Bit()
{
    REG_FIELD_WR(LSGPTIMB->CR1, TIMER_CR1_CEN, 1);
    uint32_t result=0, random32bit = 0;
    static uint16_t data, predata = 0;
    uint8_t clk_cnt=0, i = 0;
    while ((LSGPTIMB->RIF & 0x40) == 0) ;
    LSGPTIMB->ICR = TIMER_ICR_TIE_MASK;
    predata = LSGPTIMB->CCR1;
    while (1)
    {
        while ((LSGPTIMB->RIF & 0x40) == 0) ;
        LSGPTIMB->ICR = TIMER_ICR_TIE_MASK;
        data = LSGPTIMB->CCR1;
        int16_t diff = data - predata;
        LS_ASSERT(diff > 0);
        result += diff;
        predata = data;
        if (++clk_cnt < RNG_32K_NUMBER)
        {
            continue;
        }
        random32bit |= (result & 0x1) << i;
        if (i++ >= 32)
        {
        REG_FIELD_WR(LSGPTIMB->CR1, TIMER_CR1_CEN, 0);
            return random32bit;
        }
        result = 0;
        clk_cnt = 0;
    }
}