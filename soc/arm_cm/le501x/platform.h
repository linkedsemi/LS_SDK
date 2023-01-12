#ifndef PLATFORM_H_
#define PLATFORM_H_
#include <stdint.h>
#include <stdbool.h>
#include "sdk_config.h"
#include "compile_flag.h"
#include "le501x.h"
#define RESET_OTA_SUCCEED      0xDBDBDBDB
#define RESET_OTA_FAILED       0xBDBDBDBD
#define RESET_OTA_REQ          0xDDDDDDDD

#define LSI_CNT_CYCLES (1500)

struct reset_retain_struct
{
    uint32_t reset_reason;
};

void switch_to_rc32k(void);

void switch_to_xo16m(void);

bool clk_check(void);

void clk_switch(void);

uint8_t get_reset_source(void);

void set_wakeup_source(uint8_t wkup_src);

uint8_t get_wakeup_source(void);

void sys_init_app(void);

void sys_init_itf(void);

void sys_init_none(void);

void sys_init_24g(void);

void irq_reinit(void);

void uart_eif_read(uint8_t *bufptr, uint32_t size, void (*callback)(void *,uint8_t), void* dummy);

void uart_eif_write(uint8_t *bufptr, uint32_t size, void (*callback)(void *,uint8_t), void* dummy);

void uart_eif_flow_on(void);

bool uart_eif_flow_off(void);

void stack_assert_asm(uint32_t,uint32_t,uint32_t);

void platform_reset(uint32_t error);

void ecc_calc_start(const uint8_t* secret_key,const uint8_t* pub_x,const uint8_t* pub_y,uint8_t* result_x,uint8_t* result_y,void (*cb)(void *),void *param);

uint64_t lpcycles_to_hus(uint32_t lpcycles);

uint32_t us_to_lpcycles(uint32_t us);
#if SDK_LSI_USED
uint16_t get_lsi_cnt_val(void);
#endif
uint32_t lsi_freq_update_and_hs_to_lpcycles(int32_t hs_cnt);

uint64_t idiv_acc(uint32_t,uint32_t,bool);

void arm_cm_delay_asm(uint32_t);

void power_up_hardware_modules(void);

void remove_hw_isolation(void);

uint32_t config_word_get(uint32_t offset);

void arm_cm_set_int_isr(int8_t type,void (*isr)());


#define DELAY_US(a) arm_cm_delay_asm((a)*SDK_HCLK_MHZ/5)

uint32_t get_app_image_base(void);

void LVD33_Handler(void);

void lvd33_config(void);

void lvd33_enable(void);

void lvd33_disable(void);

void mesh_stack_data_bss_init(void);

#define OSTICK_HS_INC(Hz) (2000*1000/(Hz)/625)
#define OSTICK_HUS_INC(Hz) (2000*1000/(Hz) - 625*OSTICK_HS_INC(Hz))
#define OSTICK_HS_STEP_INC(Hz,step) (2000*1000/(Hz)*(step)/625)
#define OSTICK_HUS_STEP_INC(Hz,step) (2000*1000/(Hz)*(step) - 625*OSTICK_HS_STEP_INC(Hz,step))
#endif
