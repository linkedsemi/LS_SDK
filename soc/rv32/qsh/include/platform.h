#ifndef PLATFORM_H_
#define PLATFORM_H_
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include "field_manipulate.h"
#include "sdk_config.h"
#include "core_rv32.h"
#include "qsh.h"
#include "reg_sysc_sec_cpu.h"
#include "reg_sysc_app_cpu.h"
#include <ls_soc_clock.h>
#include <ls_soc_reset.h>

#ifndef __ASM
#define __ASM                   __asm     /*!< asm keyword for GNU Compiler */
#endif

#ifndef __INLINE
#define __INLINE                inline    /*!< inline keyword for GNU Compiler */
#endif

#ifndef __ALWAYS_STATIC_INLINE
#define __ALWAYS_STATIC_INLINE  __attribute__((always_inline)) __ALWAYS_STATIC_INLINE
#endif

#ifndef __STATIC_INLINE
#define __STATIC_INLINE         __ALWAYS_STATIC_INLINE
#endif

__ALWAYS_STATIC_INLINE void e906_init()
{
    uint32_t value = __get_MSTATUS();
    MODIFY_REG(value,0x6000,0x2000); 
    __set_MSTATUS(value);//enable fpu
    value = __get_MHCR();
    value |= (CACHE_MHCR_RS_Msk | CACHE_MHCR_BPE_Msk | CACHE_MHCR_L0BTB_Msk);
    __set_MHCR(value);
}

void sys_init_none(void);

void rv_set_int_isr(uint8_t type,void (*isr)());

void rv32_delay_asm(uint32_t,uint32_t);

void SWINT_Handler_ASM();

void flash_swint_init();

void clk_flash_init();

#ifdef FREERTOS
#define FLASH_SWINT_HANDLER OS_SWINT_Handler
#else
#define FLASH_SWINT_HANDLER SWINT_Handler_ASM
#endif

#ifdef BOOT_ROM
void rom_delay(uint32_t us);
#define DELAY_US(a) rom_delay(a)
#else
#define DELAY_US(a) rv32_delay_asm((a)*SDK_HCLK_MHZ/5,1)
#endif
#define DELAY_MS(a) DELAY_US((a)*1000)

#define FLASH_SWINT_NUM QSPI1_IRQN
#define GLOBAL_INT_MASK_STATUS() (!(__get_MSTATUS()&0x8))

__ALWAYS_STATIC_INLINE void cpu_intr_sec_unmask(void)
{
    SYSC_SEC_CPU->SEC_CPU_IMSK = 1;
}

__ALWAYS_STATIC_INLINE void cpu_intr_sec_mask(void)
{
    SYSC_SEC_CPU->SEC_CPU_IMSK = 0;
}

__ALWAYS_STATIC_INLINE void cpu_intr_sec_activate(void)
{
    SYSC_SEC_CPU->SEC_CPU_INTR = 1;
}

__ALWAYS_STATIC_INLINE void cpu_intr_sec_clr(void)
{
    SYSC_SEC_CPU->SEC_CPU_INTR = 0;
}

__ALWAYS_STATIC_INLINE void app_cpu_reset(void)
{
    SYSC_SEC_CPU->APP_CPU_SRST = 0x2; /* reset */
}

__ALWAYS_STATIC_INLINE void cpu_intr_app_unmask(void)
{
    SYSC_APP_CPU->APP_CPU_IMSK = 1;
}

__ALWAYS_STATIC_INLINE void cpu_intr_app_mask(void)
{
    SYSC_APP_CPU->APP_CPU_IMSK = 0;
}

__ALWAYS_STATIC_INLINE void cpu_intr_app_activate(void)
{
    SYSC_APP_CPU->APP_CPU_INTR = 1;
}

__ALWAYS_STATIC_INLINE void cpu_intr_app_clr(void)
{
    SYSC_APP_CPU->APP_CPU_INTR = 0;
}

#if defined(CONFIG_CPU2_BOOT_ADDR)
__ALWAYS_STATIC_INLINE void app_cpu_dereset(void)
{
    SYSC_SEC_CPU->APP_CPU_ADDR_CFG = CONFIG_CPU2_BOOT_ADDR; /* set cpu1 pc addr */
    SYSC_SEC_CPU->APP_CPU_SRST = 0x1; /* release reset */
}
#endif

__ALWAYS_STATIC_INLINE void app_cpu_dereset_by_addr(uint32_t pc_addr)
{
    SYSC_SEC_CPU->APP_CPU_ADDR_CFG = pc_addr; /* set cpu1 pc addr */
    SYSC_SEC_CPU->APP_CPU_SRST = 0x1; /* release reset */
}

__ALWAYS_STATIC_INLINE void app_cpu_reset_pc(uint32_t addr)
{
    SYSC_SEC_CPU->APP_CPU_ADDR_CFG = addr;
}

__ALWAYS_STATIC_INLINE void app_cpu_reset_hold_clr(void)
{
    SYSC_SEC_CPU->CPU_SYSC &= ~(1UL << 16);
}

__ALWAYS_STATIC_INLINE void app_cpu_reset_hold_set(void)
{
    SYSC_SEC_CPU->CPU_SYSC |= (1UL << 16);
}

__ALWAYS_STATIC_INLINE bool is_app_cpu_running(void)
{
    return (SYSC_SEC_CPU->APP_CPU_SRST > 0);
}

static inline int soc_eth_tx_delay_set(uint32_t addr, uint8_t delay)
{
    int ret = 0;

    switch (addr) {
    case APP_ETH1_ADDR:
        REG_FIELD_WR(SYSC_APP_CPU->ETH1_PHY_CTRL, SYSC_APP_CPU_ETH1_RGMII_TX_DELAY_SEL, delay);
        break;
    case APP_ETH2_ADDR:
        REG_FIELD_WR(SYSC_APP_CPU->ETH2_PHY_CTRL, SYSC_APP_CPU_ETH2_RGMII_TX_DELAY_SEL, delay);
        break;
    default:
        ret = -EINVAL;
        break;
    }

    return ret;
}

static inline int soc_eth_rx_delay_set(uint32_t addr, uint8_t delay)
{
    int ret = 0;

    switch (addr) {
    case APP_ETH1_ADDR:
        REG_FIELD_WR(SYSC_APP_CPU->ETH1_PHY_CTRL, SYSC_APP_CPU_ETH1_RGMII_RX_DELAY_SEL, delay);
        break;
    case APP_ETH2_ADDR:
        REG_FIELD_WR(SYSC_APP_CPU->ETH2_PHY_CTRL, SYSC_APP_CPU_ETH2_RGMII_RX_DELAY_SEL, delay);
        break;
    default:
        ret = -EINVAL;
        break;
    }

    return ret;
}

static inline int soc_eth_tx_delay_get(uint32_t addr, uint8_t *delay)
{
    int ret = 0;

    if (NULL == delay) {
        ret = -EINVAL;
        goto error;
    }

    switch (addr) {
    case APP_ETH1_ADDR:
        *delay = REG_FIELD_RD(SYSC_APP_CPU->ETH1_PHY_CTRL, SYSC_APP_CPU_ETH1_RGMII_TX_DELAY_SEL);
        break;
    case APP_ETH2_ADDR:
        *delay = REG_FIELD_RD(SYSC_APP_CPU->ETH2_PHY_CTRL, SYSC_APP_CPU_ETH2_RGMII_TX_DELAY_SEL);
        break;
    default:
        ret = -EINVAL;
        break;
    }

error:
    return ret;
}

static inline int soc_eth_rx_delay_get(uint32_t addr, uint8_t *delay)
{
    int ret = 0;

    if (NULL == delay) {
        ret = -EINVAL;
        goto error;
    }

    switch (addr) {
    case APP_ETH1_ADDR:
        *delay = REG_FIELD_RD(SYSC_APP_CPU->ETH1_PHY_CTRL, SYSC_APP_CPU_ETH1_RGMII_RX_DELAY_SEL);
        break;
    case APP_ETH2_ADDR:
        *delay = REG_FIELD_RD(SYSC_APP_CPU->ETH2_PHY_CTRL, SYSC_APP_CPU_ETH2_RGMII_RX_DELAY_SEL);
        break;
    default:
        ret = -EINVAL;
        break;
    }

error:
    return ret;
}

__ALWAYS_STATIC_INLINE void ls_clock_control_on(uint32_t base, uint32_t reg, uint8_t set_pos, uint8_t clr_pos)
{
    (void)clr_pos;
    *(volatile uint32_t *)(base + reg) = 1 << set_pos;
}

__ALWAYS_STATIC_INLINE void ls_clock_control_off(uint32_t base, uint32_t reg, uint8_t set_pos, uint8_t clr_pos)
{
    (void)set_pos;
    *(volatile uint32_t *)(base + reg) = 1 << clr_pos;
}

__ALWAYS_STATIC_INLINE void ls_reset_line_assert(uint32_t base, uint32_t reg, uint8_t set_pos, uint8_t clr_pos)
{
    (void)set_pos;
    *(volatile uint32_t *)(base + reg) = 1 << clr_pos;
}

__ALWAYS_STATIC_INLINE void ls_reset_line_deassert(uint32_t base, uint32_t reg, uint8_t set_pos, uint8_t clr_pos)
{
    (void)clr_pos;
    *(volatile uint32_t *)(base + reg) = 1 << set_pos;
}

__ALWAYS_STATIC_INLINE void ls_reset_line_toggle(uint32_t base, uint32_t reg, uint8_t set_pos, uint8_t clr_pos)
{
    ls_reset_line_assert(base, reg, set_pos, clr_pos);
    ls_reset_line_deassert(base, reg, set_pos, clr_pos);
}

#endif
