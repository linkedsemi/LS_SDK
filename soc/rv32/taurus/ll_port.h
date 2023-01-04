#ifndef LL_PORT_H_
#define LL_PORT_H_
#include "reg_mac_type.h"
#include "reg_base_addr.h"
#include "taurus.h"
#include "csi_core.h"
#include "swint_call_asm.h"
#include "compile_flag.h"
#include "reg_v33_rg.h"

#define MAC ((reg_mac_t *)MAC_BASE_ADDR)
#define MAC_CLK_MHZ (16)
#define BLE_EVT_INT_NUM 9
#define MAC_FIFO_DEPTH 64

__attribute__((always_inline)) static inline void ble_pkt_irq_mask()
{
    csi_vic_disable_irq(MAC1_IRQn);
}

__attribute__((always_inline)) static inline void ble_pkt_irq_unmask()
{
    csi_vic_enable_irq(MAC1_IRQn);
}

__attribute__((always_inline)) static inline void ble_pkt_irq_clr()
{
    csi_vic_clear_pending_irq(MAC1_IRQn);
}

__attribute__((always_inline)) static inline void ble_util_irq_clr()
{
    csi_vic_clear_pending_irq(MAC2_IRQn);
}

__attribute__((always_inline)) static inline void sleep_expected_time_set(uint32_t time)
{
    V33_RG->MAC_SLEEP_EXPECTED = time;
}

__attribute__((always_inline)) static inline uint32_t sleep_duration_get()
{
    return V33_RG->MAC_SLEEP_DURATION;
}

__attribute__((always_inline)) static inline void mac_reg_sync()
{
    __NOP();__NOP();__NOP();__NOP();__NOP();
}

#endif
