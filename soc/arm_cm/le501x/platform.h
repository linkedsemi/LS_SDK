#ifndef PLATFORM_H_
#define PLATFORM_H_
#include <stdint.h>
#include <stdbool.h>
#include "sdk_config.h"
#include "compile_flag.h"
#include "prf_fotas.h"
#define RESET_OTA_SUCCEED      0xDBDBDBDB
#define RESET_OTA_FAILED       0xBDBDBDBD
#define RESET_OTA_REQ          0xDDDDDDDD

#define LSI_CNT_CYCLES (100)

enum OTA_settings_type
{
    SINGLE_FOREGROUND = 0,
    DOUBLE_FOREGROUND = 1,
    DOUBLE_BACKGROUND = 2,
    OTA_SETTINGS_TYPE_MAX = DOUBLE_BACKGROUND + 1,
};

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

void rco_freq_counting_config(void);

void rco_freq_counting_start(void);

uint64_t lpcycles_to_hus(uint32_t lpcycles);

uint32_t us_to_lpcycles(uint32_t us);
#if SDK_LSI_USED
uint16_t get_lsi_cnt_val(void);
#endif
uint32_t lsi_freq_update_and_hs_to_lpcycles(int32_t hs_cnt);

uint64_t idiv_acc(uint32_t,uint32_t,bool);

void switch_to_hse(void);

void arm_cm_delay_asm(uint32_t);

void request_ota_reboot(void);

void power_up_hardware_modules(void);

void remove_hw_isolation(void);

uint32_t config_word_get(uint32_t offset);

void arm_cm_set_int_isr(uint8_t type,void (*isr)());


#define DELAY_US(a) arm_cm_delay_asm((a)*SDK_HCLK_MHZ/5)

void ota_settings_erase(void);

void ota_settings_write(uint32_t ota_settings_type);

uint32_t ota_settings_read(void);

bool ota_copy_info_get(struct fota_image_info *ptr);

void ota_copy_info_set(struct fota_image_info *ptr);

uint32_t get_app_image_base(void);

uint32_t get_fota_image_base(void);

#define OSTICK_HS_INC(Hz) (2000*1000/(Hz)/625)
#define OSTICK_HUS_INC(Hz) (2000*1000/(Hz) - 625*OSTICK_HS_INC(Hz))
#define OSTICK_HS_STEP_INC(Hz,step) (2000*1000/(Hz)*(step)/625)
#define OSTICK_HUS_STEP_INC(Hz,step) (2000*1000/(Hz)*(step) - 625*OSTICK_HS_STEP_INC(Hz,step))
#endif
