#define LOG_TAG "PLF"
#include <string.h>
#include <stdlib.h>
#include "platform.h"
#include "calc_div.h"
#include "cpu.h"
#include "tinyfs_config.h"
#include "tinyfs.h"
#include "sleep.h"
#include "le501x.h"
#include "log.h"
#include "ls_msp_qspi.h"
#include "ls_hal_flash.h"
#include "compile_flag.h"
#include "ls_hal_cache.h"
#include "reg_rcc.h"
#include "modem_rf_le501x.h"
#include "modem_rf_le501x_24g.h"
#include "calc_acc.h"
#include "builtin_timer.h"
#include "reg_syscfg.h"
#include "ls_hal_ecc.h"
#include "ls_hal_trng.h"
#include "field_manipulate.h"
#include "ls_soc_gpio.h"
#include "ls_dbg.h"
#include "systick.h"
#include "ls_hal_pis.h"
#include "ls_hal_timer.h"
#include "reg_lptim.h"
#include "sw_timer.h"
#include "ls_sys.h"
#include "sys_stat.h"
#define XTAL_STB_VAL 20
#define ISR_VECTOR_ADDR ((uint32_t *)(0x0))
#define APP_IMAGE_BASE_OFFSET (0x24)
#define FOTA_IMAGE_BASE_OFFSET (0x28)
#define DATA_STORAGE_BASE_OFFSET (0x2c)
#define BASEBAND_MEMORY_ADDR   (0x50004000)
#define IRQ_NVIC_PRIO(IRQn,priority) (((priority << (8U - __NVIC_PRIO_BITS)) & (uint32_t)0xFFUL) << _BIT_SHIFT(IRQn))

DEF_BUILTIN_TIMER_ENV(SDK_BUILTIN_TIMER_MAX);

void stack_var_ptr_init(void);

void main_task_app_init(void);

void main_task_itf_init(void);

__attribute__((weak)) void builtin_timer_env_register(linked_buffer_t *env){}    

static void bb_mem_clr(void)
{
    //memset((void *)BASEBAND_MEMORY_ADDR,0,16384);
}

static void irq_priority()
{
    __NVIC_SetPriority(SVCall_IRQn,2);
    __NVIC_SetPriority(SysTick_IRQn, 1);
    __NVIC_SetPriority(PendSV_IRQn,3);
    NVIC->IP[0] = IRQ_NVIC_PRIO(EXTI_IRQn,3) | IRQ_NVIC_PRIO(WWDT_IRQn,3) | IRQ_NVIC_PRIO(LPWKUP_IRQn,2) | IRQ_NVIC_PRIO(BLE_IRQn,1);
    NVIC->IP[1] = IRQ_NVIC_PRIO(RTC_IRQn,3) | IRQ_NVIC_PRIO(DMA_IRQn,3) | IRQ_NVIC_PRIO(QSPI_IRQn,3) | IRQ_NVIC_PRIO(ECC_IRQn,3);
    NVIC->IP[2] = IRQ_NVIC_PRIO(CACHE_IRQn,3) | IRQ_NVIC_PRIO(TRNG_IRQn,3) | IRQ_NVIC_PRIO(IWDT_IRQn,3) | IRQ_NVIC_PRIO(CRYPT_IRQn,3);
    NVIC->IP[3] = IRQ_NVIC_PRIO(PDM_IRQn,3) | IRQ_NVIC_PRIO(BLE_WKUP_IRQn,1) | IRQ_NVIC_PRIO(ADC_IRQn,3) | IRQ_NVIC_PRIO(ADTIM1_IRQn,3);
    NVIC->IP[4] = IRQ_NVIC_PRIO(BSTIM1_IRQn,3) | IRQ_NVIC_PRIO(GPTIMA1_IRQn,3) | IRQ_NVIC_PRIO(GPTIMB1_IRQn,3) | IRQ_NVIC_PRIO(BLE_ERR_IRQn,1);
    NVIC->IP[5] = IRQ_NVIC_PRIO(LVD33_IRQn,0) | IRQ_NVIC_PRIO(GPTIMC1_IRQn,3) | IRQ_NVIC_PRIO(LPTIM_IRQn,3) | IRQ_NVIC_PRIO(I2C1_IRQn,3);
    NVIC->IP[6] = IRQ_NVIC_PRIO(I2C2_IRQn,3) | IRQ_NVIC_PRIO(SPI1_IRQn,3) | IRQ_NVIC_PRIO(SPI2_IRQn,3) | IRQ_NVIC_PRIO(UART1_IRQn,3);
    NVIC->IP[7] = IRQ_NVIC_PRIO(UART2_IRQn,3) | IRQ_NVIC_PRIO(UART3_IRQn,3) | IRQ_NVIC_PRIO(BLE_FIFO_IRQn,1) | IRQ_NVIC_PRIO(BLE_CRYPT_IRQn,1);
}

#if defined(__CC_ARM)
__attribute__((weak)) uint32_t __stack_bss_start__;
__attribute__((weak)) uint32_t __stack_bss_size__;
__attribute__((weak)) uint32_t __stack_data_lma__;
__attribute__((weak)) uint32_t __stack_data_size__;
__attribute__((weak)) uint32_t __stack_data_start__;
__attribute__((weak)) uint32_t __mesh_stack_bss_start__;
__attribute__((weak)) uint32_t __mesh_stack_bss_size__;
__attribute__((weak)) uint32_t __mesh_stack_data_lma__;
__attribute__((weak)) uint32_t __mesh_stack_data_start__;
__attribute__((weak)) uint32_t __mesh_stack_data_size__;
#else
extern uint32_t __stack_bss_start__;
extern uint32_t __stack_bss_size__;
extern uint32_t __stack_data_lma__;
extern uint32_t __stack_data_size__;
extern uint32_t __stack_data_start__;
extern uint32_t __mesh_stack_bss_start__;
extern uint32_t __mesh_stack_bss_size__;
extern uint32_t __mesh_stack_data_lma__;
extern uint32_t __mesh_stack_data_start__;
extern uint32_t __mesh_stack_data_size__;
#endif
static void stack_data_bss_init()
{
    memset(&__stack_bss_start__,0,(uint32_t)&__stack_bss_size__);
    memcpy(&__stack_data_start__,&__stack_data_lma__,(uint32_t)&__stack_data_size__);
}

void mesh_stack_data_bss_init(void)
{
    memset(&__mesh_stack_bss_start__,0,(uint32_t)&__mesh_stack_bss_size__);
    memcpy(&__mesh_stack_data_start__,&__mesh_stack_data_lma__,(uint32_t)&__mesh_stack_data_size__);
}

static void ble_irq_clr()
{
    //clear ble irq
    NVIC->ICPR[0] = 1<<BLE_IRQn | 1<<BLE_ERR_IRQn | 1<<BLE_FIFO_IRQn | (unsigned int)1<<BLE_CRYPT_IRQn;
}

static void ble_irq_enable()
{
    //enable ble irq
    NVIC->ISER[0] = 1<<BLE_IRQn | 1<<BLE_ERR_IRQn | 1<<BLE_FIFO_IRQn | (unsigned int)1<<BLE_CRYPT_IRQn;
}

void ble_irq_clr_and_enable()
{
    ble_irq_clr();
    ble_irq_enable();
}

uint32_t config_word_get(uint32_t offset)
{
    uint32_t data;
    hal_flash_quad_io_read(offset,(uint8_t *)&data,sizeof(data));
    return data;
}

static uint32_t flash_data_storage_base_offset()
{
    return config_word_get(DATA_STORAGE_BASE_OFFSET);
}

static void lvd33_irq_enable()
{
    __NVIC_ClearPendingIRQ(LVD33_IRQn);
    __NVIC_EnableIRQ(LVD33_IRQn);
}

void irq_reinit()
{
    irq_priority();
    NVIC->ISER[0] = 1<<CACHE_IRQn|1<<LPWKUP_IRQn|1<<EXTI_IRQn|1<<RTC_IRQn;
    lvd33_irq_enable();
}

static void irq_init()
{
    irq_reinit();
    ble_irq_clr_and_enable();
}

static void mac_init()
{
    uint8_t mac_clk;
    uint32_t clk_cfg = RCC->CFG;
    if(REG_FIELD_RD(clk_cfg, RCC_SYSCLK_SW) == 0x4)
    {
        if(REG_FIELD_RD(clk_cfg, RCC_HCLK_SCAL) == 0x8 )
        {
            mac_clk = 1; //AHB 32M
        }else
        {
            mac_clk = 2; //AHB 64M
        }
    }else
    {
        mac_clk = 0; //AHB 16M
    }
    RCC->BLECFG = mac_clk<<RCC_BLE_CK_SEL_POS| 1<<RCC_BLE_MRST_POS | 1<<RCC_BLE_CRYPT_RST_POS | 1<<RCC_BLE_LCK_RST_POS | 1<<RCC_BLE_AHB_RST_POS | 1<<RCC_BLE_WKUP_RST_POS
        | 1<<RCC_BLE_LPWR_CKEN_POS | 1<<RCC_BLE_AHBEN_POS | 1<<RCC_BLE_MDM_REFCLK_CKEN_POS | !SDK_LSI_USED<<RCC_BLE_LCK_SEL_POS;
    RCC->BLECFG &= ~(1<<RCC_BLE_MRST_POS | 1<<RCC_BLE_CRYPT_RST_POS | 1<<RCC_BLE_LCK_RST_POS | 1<<RCC_BLE_AHB_RST_POS | 1<<RCC_BLE_WKUP_RST_POS);
}

#if SDK_LSI_USED
static void *lsi_counting_timer;
static volatile uint16_t lsi_cnt_val;
static bool lsi_counting_valid;

__attribute__((weak)) void builtin_timer_start(void *timer,uint32_t timeout,void *param){}
__attribute__((weak)) void *builtin_timer_create(void (*cb)(void *)){return NULL;}
__attribute__((weak)) void func_post(void (*func)(void *),void *param){}

void rco_freq_counting_start()
{
    HAL_PIS_Config(7,LPTIM_TRGO,GPTIMB1_ITR0,PIS_SYNC_SRC_LEVEL,PIS_EDGE_NONE);
//GPTIMC Config
    LSGPTIMB->PSC      = SDK_PCLK_MHZ - 1;         // Set precaler N+1
    LSGPTIMB->ARR      = 0xFFFFFFFF;  // Set reload N+1 (16 bit)
    REG_FIELD_WR(LSGPTIMB->CR1,TIMER_CR1_DIR,0);         // Set upcounting
    LSGPTIMB->ICR = TIMER_ICR_UIE_MASK;         // Clear interrupt
    LSGPTIMB->IER = TIMER_IER_UIE_MASK;
    REG_FIELD_WR(LSGPTIMB->CCMR1,TIMER_CCMR1_CC1S,0x3);
    REG_FIELD_WR(LSGPTIMB->SMCR,TIMER_SMCR_TS,0);
    REG_FIELD_WR(LSGPTIMB->SMCR,TIMER_SMCR_SMS,4);
    REG_FIELD_WR(LSGPTIMB->CR1,TIMER_CR1_CEN,1);  // Enable counter

//LPTIM Config
    LPTIM->ARR   = LSI_CNT_CYCLES-1;
    LPTIM->CON1  = 1;
    LPTIM->CON0 |= 1<<22;
    while(LPTIM->SYNCSTAT&2);
    LPTIM->CON1 |= 4;

    gptimerb1_status_set(true);
    lsi_counting_valid = false;
    __NVIC_ClearPendingIRQ(GPTIMB1_IRQn);
    __NVIC_EnableIRQ(GPTIMB1_IRQn);
}

static void lsi_counting_timer_callback(void *param)
{
    rco_freq_counting_start();
}

void lsi_counting_timer_create()
{
    lsi_counting_timer = builtin_timer_create(lsi_counting_timer_callback);
}

static void lsi_counting_timer_start(void *param)
{
    builtin_timer_start(lsi_counting_timer,LSI_RECOUNT_PERIOD_MS,lsi_counting_timer);
}

static void GPTIM_IRQ_Handler_For_LSI_Counting()
{
    LSGPTIMB->ICR = TIMER_ICR_UIE_MASK;         // Clear interrupt
    if(lsi_counting_valid)
    {
        lsi_cnt_val = LSGPTIMB->CCR1;
        __NVIC_DisableIRQ(GPTIMB1_IRQn);
        gptimerb1_status_set(false);
        REG_FIELD_WR(RCC->APB2RST,RCC_LPTIM,1);
        REG_FIELD_WR(RCC->APB2RST,RCC_LPTIM,0);
        REG_FIELD_WR(RCC->APB1RST,RCC_GPTIMB1,1);
        REG_FIELD_WR(RCC->APB1RST,RCC_GPTIMB1,0);
        if(lsi_counting_timer)
        {
            func_post(lsi_counting_timer_start,NULL);
        }
    }else
    {
        lsi_counting_valid = true;
    }
}

void rco_freq_counting_init()
{
    REG_FIELD_WR(RCC->CFG,RCC_LPTIM_CLKS,0);
    REG_FIELD_WR(RCC->APB2EN,RCC_LPTIM,1);
    REG_FIELD_WR(RCC->APB1EN,RCC_GPTIMB1,1);
    arm_cm_set_int_isr(GPTIMB1_IRQn,GPTIM_IRQ_Handler_For_LSI_Counting);
    DELAY_US(200);
}

uint64_t lpcycles_to_hus(uint32_t lpcycles)
{
    uint64_t hus = 2*lsi_cnt_val*(uint64_t)lpcycles;
    __div64_32(&hus,LSI_CNT_CYCLES);
    //LOG_I("%d,%d",lpcycles,hus);
    return hus;
}

uint32_t us_to_lpcycles(uint32_t us)
{
    return us*LSI_CNT_CYCLES/lsi_cnt_val;
}

uint16_t get_lsi_cnt_val(void)
{
    return lsi_cnt_val;
}

uint32_t lsi_freq_update_and_hs_to_lpcycles(int32_t hs_cnt)
{
    LS_ASSERT(hs_cnt);
    LS_ASSERT(lsi_cnt_val);
    uint64_t lpcycles = LSI_CNT_CYCLES*625*(uint64_t)hs_cnt;
    __div64_32(&lpcycles,2*lsi_cnt_val);
    //LOG_I("%d,%d,%d",lsi_cnt_val,lpcycles,hs_cnt);
    return lpcycles;
}

void lse_init(){}
#else
void rco_freq_counting_init(){}
void rco_freq_counting_start(){}
uint64_t lpcycles_to_hus(uint32_t lpcycles){return 0;}
uint32_t us_to_lpcycles(uint32_t us){return 0;}
uint32_t lsi_freq_update_and_hs_to_lpcycles(int32_t hs_cnt){return 0;}
void lse_init()
{
    REG_FIELD_WR(SYSCFG->PMU_TRIM,SYSCFG_LDO_LP_TRIM,7);
    RCC->CK |= RCC_LSE_EN_MASK;
    DELAY_US(100000);
}
void lsi_counting_timer_create(){}
#endif

uint8_t get_reset_source()
{
    uint8_t rst_stat = SYSCFG->RSTST;
    SYSCFG->RSTST = 0xff;
    return rst_stat;
}

void set_wakeup_source(uint8_t wkup_src)
{
    SYSCFG->BKD[6] = wkup_src;
}

uint8_t get_wakeup_source()
{
    return SYSCFG->BKD[6];
}

void arm_cm_set_int_isr(int8_t type,void (*isr)())
{
    ISR_VECTOR_ADDR[type + 16] = (uint32_t)isr;
}

void cpu_recover_asm(void);

void cpu_sleep_recover_init()
{
    ISR_VECTOR_ADDR[1] = (uint32_t)cpu_recover_asm;
    arm_cm_set_int_isr(LPWKUP_IRQn,LPWKUP_Handler);
}

uint32_t get_trng_value()
{
    uint32_t random32bit;
    HAL_TRNG_Init();
    HAL_TRNG_GenerateRandomNumber(&random32bit);
    HAL_TRNG_DeInit();
    return random32bit;
}

static void module_init()
{
    io_init();
    LOG_INIT();
    LOG_I("sys init");
    INIT_BUILTIN_TIMER_ENV();
    rco_freq_counting_init();
    lsi_counting_timer_create();
    HAL_PIS_Init();

    srand(get_trng_value());
    calc_acc_init();
    cpu_sleep_recover_init();
    mac_init();
    modem_rf_init();
    irq_init();
    systick_start();
    rco_freq_counting_start();
    uint32_t base_offset = flash_data_storage_base_offset();
    tinyfs_init(base_offset);
    tinyfs_print_dir_tree();
}

void XIP_BANNED_FUNC(LVD33_Handler,)
{
    while(REG_FIELD_RD(SYSCFG->RSTST,SYSCFG_LVD33_FLAG))
    {
        REG_FIELD_WR(SYSCFG->RSTST,SYSCFG_LVD33_FLAG,1);
    }
}

void lvd33_config()
{
    REG_FIELD_WR(SYSCFG->ANACFG0,SYSCFG_LVD_CTL,1);
    REG_FIELD_WR(SYSCFG->CFG,SYSCFG_LVD33_INTE,1);
}

void lvd33_enable()
{
    REG_FIELD_WR(SYSCFG->ANACFG0,SYSCFG_LVD_EN,1);
}

void lvd33_disable()
{
    REG_FIELD_WR(SYSCFG->ANACFG0,SYSCFG_LVD_EN,0);
}

static void lsi_calib()
{
    MODIFY_REG(SYSCFG->ANACFG1,SYSCFG_RCO_MODE_SEL_MASK|SYSCFG_RCO_CAL_START_MASK|SYSCFG_EN_RCO_DIG_PWR_MASK,
        0<<SYSCFG_RCO_MODE_SEL_POS|1<<SYSCFG_RCO_CAL_START_POS|1<<SYSCFG_EN_RCO_DIG_PWR_POS);
    while(REG_FIELD_RD(SYSCFG->ANACFG1, SYSCFG_RCO_CAL_DONE)==0)
    {
        uint16_t cal_code = REG_FIELD_RD(SYSCFG->ANACFG1, SYSCFG_RCO_CAL_CODE);
        SYSCFG->PMU_ANALOG = cal_code;
    }
    MODIFY_REG(SYSCFG->ANACFG1,SYSCFG_RCO_CAL_START_MASK|SYSCFG_EN_RCO_DIG_PWR_MASK,0);
}

static void analog_init()
{
    dcdc_on();
    if(clk_check()==false)
    {
        clk_switch();
    }
    lse_init();
    lsi_calib();
    REG_FIELD_WR(SYSCFG->PMU_TRIM, SYSCFG_XTAL_STBTIME, XTAL_STB_VAL);
    arm_cm_set_int_isr(LVD33_IRQn,LVD33_Handler);
}

static void var_init()
{
    stack_data_bss_init();
    bb_mem_clr();
    stack_var_ptr_init();
    hal_flash_drv_var_init(true,false);
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

void sys_init_none()
{
    analog_init();
    HAL_PIS_Init();
    hal_flash_drv_var_init(true,false);
    cpu_sleep_recover_init();
    calc_acc_init();
    mac_init();
    io_init();
    irq_init();
    systick_start();
    LOG_INIT();
    rco_freq_counting_init();
    rco_freq_counting_start();
    while (get_lsi_cnt_val() == 0);
    sw_timer_module_init();
}

void sys_init_24g(void)
{
    sys_init_none();
    modem_rf_init_24g();
}

void ll_stack_var_ptr_init(void);

static void ll_var_init()
{
    stack_data_bss_init();
    bb_mem_clr();
    ll_stack_var_ptr_init();
    hal_flash_drv_var_init(true,false);
}

void sys_init_ll()
{
    analog_init();
    ll_var_init();
    io_init();
    LOG_INIT();
    HAL_PIS_Init();
    calc_acc_init();
    cpu_sleep_recover_init();
    mac_init();
    modem_rf_init();
    irq_init();
    systick_start();
}

void platform_reset(uint32_t error)
{
    __disable_irq();
    struct reset_retain_struct *reset_retain_ptr = (struct reset_retain_struct*)RESET_RETAIN_BASE;
    reset_retain_ptr->reset_reason = error;
    switch_to_xo16m();
    __NVIC_SystemReset();
}

uint64_t idiv_acc(uint32_t dividend,uint32_t divisor,bool signed_int)
{
    uint32_t cpu_stat = enter_critical();
    uint64_t retval = calc_div(dividend, divisor, signed_int);
    exit_critical(cpu_stat);
    return retval;
}

__attribute__((weak)) void SystemInit(){}

uint32_t plf_get_reset_error()
{
    struct reset_retain_struct *reset_retain_ptr = (struct reset_retain_struct*)RESET_RETAIN_BASE;
    return reset_retain_ptr->reset_reason;
}

__attribute__((weak)) void ble_sched(){}

void ble_loop()
{
    while(1)
    {
        if(!ble_wkup_status_get())
        {
            ble_sched();
            sleep_process();
        }
    }
}

__attribute__((weak)) uint32_t ble_isr(){return 0;}

__attribute__((weak)) void ble_stack_isr(){ble_isr();}

void XIP_BANNED_FUNC(BLE_Handler,)
{
    bool flash_writing_status = hal_flash_writing_busy();
    bool xip = hal_flash_xip_status_get();
    if(flash_writing_status)
    {
        LS_RAM_ASSERT(xip == false);
        hal_flash_prog_erase_suspend();
        uint8_t status_reg1;
        do{
            hal_flash_read_status_register_1(&status_reg1);
        }while(hal_flash_write_in_process()&&(status_reg1&(STATUS_REG1_SUS1_MASK|STATUS_REG1_SUS2_MASK))==0);
    }
    if(xip == false)
    {
        hal_flash_xip_start();
    }
    ble_stack_isr();
    if(xip == false)
    {
        hal_flash_xip_stop();
    }
    if(flash_writing_status)
    {
        hal_flash_prog_erase_resume();
        DELAY_US(8);
    }
}

void XIP_BANNED_FUNC(switch_to_rc32k,)
{
    MODIFY_REG(RCC->CFG, RCC_SYSCLK_SW_MASK| RCC_HCLK_SCAL_MASK| RCC_CKCFG_MASK, (uint32_t)2<<RCC_SYSCLK_SW_POS | (uint32_t)1<<RCC_CKCFG_POS);
}

void XIP_BANNED_FUNC(switch_to_xo16m,)
{
    MODIFY_REG(RCC->CFG, RCC_HCLK_SCAL_MASK | RCC_CKCFG_MASK | RCC_SYSCLK_SW_MASK, (uint32_t)1<<RCC_CKCFG_POS | (uint32_t)1<<RCC_SYSCLK_SW_POS);
}

#if (SDK_HCLK_MHZ==16)
bool XIP_BANNED_FUNC(clk_check,)
{
    uint32_t rcc_cfg = RCC->CFG;
    return REG_FIELD_RD(rcc_cfg, RCC_SYSCLK_SW) == 1 && REG_FIELD_RD(rcc_cfg, RCC_HCLK_SCAL) == 0;
}

void XIP_BANNED_FUNC(clk_switch,)
{
    switch_to_xo16m();
}

#else
static void XIP_BANNED_FUNC(switch_to_pll,uint8_t hclk_scal)
{
    MODIFY_REG(RCC->CFG, RCC_SYSCLK_SW_MASK| RCC_HCLK_SCAL_MASK| RCC_CKCFG_MASK, (uint32_t)4 <<RCC_SYSCLK_SW_POS | (uint32_t)1<<RCC_CKCFG_POS | (uint32_t)hclk_scal << RCC_HCLK_SCAL_POS);
}

#if (SDK_HCLK_MHZ==32)

bool XIP_BANNED_FUNC(clk_check,)
{
    uint32_t rcc_cfg = RCC->CFG;
    return REG_FIELD_RD(rcc_cfg, RCC_SYSCLK_SW) == 4 && REG_FIELD_RD(rcc_cfg, RCC_HCLK_SCAL) == 0x8;
}

void XIP_BANNED_FUNC(clk_switch,)
{
    switch_to_pll(0x8);
}
#elif(SDK_HCLK_MHZ==64)

bool XIP_BANNED_FUNC(clk_check,)
{
    uint32_t rcc_cfg = RCC->CFG;
    return REG_FIELD_RD(rcc_cfg, RCC_SYSCLK_SW) == 4 && REG_FIELD_RD(rcc_cfg, RCC_HCLK_SCAL) == 0;
}

void XIP_BANNED_FUNC(clk_switch,)
{
    switch_to_pll(0);
}
#else
#error HCLK not supported
#endif

#endif

uint32_t get_ota_settings_offset()
{
    return hal_flash_total_size_get() - FLASH_PAGE_SIZE;
}

uint32_t get_app_image_base()
{
    return config_word_get(APP_IMAGE_BASE_OFFSET);
}

__attribute__((weak)) uint32_t __aeabi_uidiv(uint32_t r0,uint32_t r1)
{
    return (uint32_t)idiv_acc(r0,r1,false);
}

__attribute__((weak)) int32_t __aeabi_idiv(int32_t r0,int32_t r1)
{
    return (int32_t)(0xffffffff&idiv_acc(r0,r1,true));
}

__attribute__((weak)) uint64_t __aeabi_uidivmod(uint32_t r0,uint32_t r1)
{
    return idiv_acc(r0,r1,false);    
}


#if __ICCARM__
__attribute__((weak)) __value_in_regs div_t __aeabi_idivmod(int32_t r0,int32_t r1)
{
    int64_t val = idiv_acc(r0,r1,true);
    div_t res = {
        .quot = val,
        .rem = val>>32,
    };
    return res;
}
#else
__attribute__((weak)) int64_t __aeabi_idivmod(int32_t r0,int32_t r1)
{
    return (int64_t)idiv_acc(r0,r1,true);
}
#endif

void aos_swint_init(void (*isr)())
{
    arm_cm_set_int_isr(CACHE_IRQn,isr);
}

void aos_swint_set()
{
    __NVIC_SetPendingIRQ(CACHE_IRQn);
}

void ecc_calc_start(const uint8_t* secret_key,const uint8_t* pub_x,const uint8_t* pub_y,uint8_t* result_x,uint8_t* result_y,void (*cb)(void *),void *param)
{
    uint8_t *rslt[2];
    rslt[0] = result_x;
    rslt[1] = result_y;
    HAL_LSECC_Init();
    const uint8_t *pk[2] = {pub_x,pub_y};
    HAL_LSECC_PointMult(&secp256r1_param,secret_key,pk,rslt);
    HAL_LSECC_DeInit();
    cb(param);
}
