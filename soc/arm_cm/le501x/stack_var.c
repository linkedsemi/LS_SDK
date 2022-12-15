#include <stdint.h>
#include <stdlib.h>
#include "sdk_config.h"
#include "platform.h"
#include "cpu.h"
#include "log.h"
#include "modem_rf_le501x.h"
#define ENV_BUF_SIZE 2048
#if CONFIG_AOS
#define DB_BUF_SIZE 0
#define MSG_BUF_SIZE 1900
#define NON_RET_BUF_SIZE (12)
#else
#define DB_BUF_SIZE 8192
#define MSG_BUF_SIZE 8192
#define NON_RET_BUF_SIZE (380*2)

#endif

extern int (*rand_fn) (void);

__attribute((weak)) void (*stack_assert_asm_fn)(uint32_t,uint32_t,uint32_t);
__attribute((weak)) void (*app_init_fn)(void); 
__attribute((weak)) void (*platform_reset_fn)(uint32_t);
__attribute((weak)) uint64_t (*idiv_acc_fn)(uint32_t,uint32_t,bool);
__attribute((weak)) void (*ecc_calc_fn)(const uint8_t*,const uint8_t*,const uint8_t*,uint8_t*,uint8_t*,void (*)(void *),void *);
__attribute((weak)) void (*exit_critical_fn)(uint32_t);
__attribute((weak)) uint32_t (*enter_critical_fn)(void);
__attribute((weak)) void (*stack_reset_hook_fn)(void);
__attribute((weak)) uint64_t (*lpcycles_to_hus_fn)(uint32_t);
__attribute((weak)) uint32_t (*us_to_lpcycles_fn)(uint32_t);
__attribute((weak)) uint32_t (*lsi_freq_update_and_hs_to_lpcycles_fn)(int32_t);
__attribute((weak)) void (*rf_reg_config_fn)(uint8_t,uint8_t,uint16_t);
__attribute((weak)) bool lsi_used;

__attribute((weak)) uint8_t main_task;
__attribute((weak)) uint8_t max_activity_num;
__attribute((weak)) uint8_t max_profile_num;
__attribute((weak)) uint8_t max_ral_num;
__attribute((weak)) uint8_t max_user_task_num;
__attribute((weak)) bool slave_md_enable_default;

#if !defined(CONFIG_AOS)
struct {
    uint32_t env[5];
}prf_buf[SDK_MAX_PROFILE_NUM];

void* gapc_env_buf[SDK_MAX_CONN_NUM];

void* gattc_env_buf[SDK_MAX_CONN_NUM];

void *l2cc_env_buf[SDK_MAX_CONN_NUM];

void *gapm_env_actvs_buf[SDK_MAX_ACT_NUM];

uint8_t gapc_state_buf[SDK_MAX_CONN_NUM];

uint8_t gattc_state_buf[SDK_MAX_CONN_NUM];

uint8_t l2cc_state_buf[SDK_MAX_CONN_NUM];
#endif

uint32_t task_list_buf[10 + SDK_MAX_PROFILE_NUM + SDK_MAX_USER_TASK_NUM];

void* llc_env_buf[SDK_MAX_ACT_NUM];

void* adv_env_buf[SDK_MAX_ACT_NUM];

void* con_env_buf[SDK_MAX_ACT_NUM];

void* per_adv_env_buf[SDK_MAX_ACT_NUM];

void* sync_env_buf[SDK_MAX_ACT_NUM];

struct 
{
    uint32_t env[18];
}act_info_buf[SDK_MAX_ACT_NUM];

struct{
    uint32_t env[2];
}slice_buf[SDK_MAX_ACT_NUM];

struct
{
    uint32_t env[2];
}llcp_tx_buf[(2*SDK_MAX_ACT_NUM)];


struct{
    uint32_t env[2];
}acl_tx_buf[(SDK_MAX_ACT_NUM + 2)];

#if CONFIG_AOS
struct 
{
    uint32_t env[2];
}rx_buf[6]; 

struct{
    uint32_t env[2];
}adv_tx_buf[3];
#else
struct 
{
    uint32_t env[2];
}rx_buf[9];

struct{
    uint32_t env[2];
}adv_tx_buf[6];
#endif

struct 
{
    uint16_t env[5];
}dev_list_buf[(SDK_MAX_ACT_NUM + 2)];

uint16_t adv_sids_buf[(SDK_MAX_ACT_NUM + 2)];

bool ble_con_state_buf[SDK_MAX_ACT_NUM];

uint8_t per_adv_rep_chain_stat_buf[SDK_MAX_ACT_NUM];

uint8_t llc_state_buf[SDK_MAX_ACT_NUM];

struct
{
    uint8_t env[39];
}ral_buf[SDK_MAX_RAL_NUM];

uint32_t heap_buf[ENV_BUF_SIZE/sizeof(uint32_t)+DB_BUF_SIZE/sizeof(uint32_t)+MSG_BUF_SIZE/sizeof(uint32_t)+NON_RET_BUF_SIZE/sizeof(uint32_t)];

__attribute((weak)) void statck_buffer_init(uint32_t size0,uint32_t size1,uint32_t size2,uint32_t size3){}

__attribute((weak)) void prf_fn_init(void){}

__attribute((weak)) void ble_storage_max_num_init(uint8_t num){}

void stack_var_ptr_init()
{
    stack_assert_asm_fn = stack_assert_asm;
    platform_reset_fn = platform_reset;
    ecc_calc_fn = ecc_calc_start;
    rand_fn = rand;
    idiv_acc_fn = idiv_acc;
    enter_critical_fn = enter_critical;
    exit_critical_fn = exit_critical;
    stack_reset_hook_fn = NULL;
    lpcycles_to_hus_fn = lpcycles_to_hus;
    us_to_lpcycles_fn = us_to_lpcycles;
    lsi_freq_update_and_hs_to_lpcycles_fn = lsi_freq_update_and_hs_to_lpcycles;
    rf_reg_config_fn = rf_reg_config;
    #if SDK_LSI_USED
    lsi_used = true;
    #else
    lsi_used = false;
    #endif

    max_activity_num = SDK_MAX_ACT_NUM;
    max_profile_num = SDK_MAX_PROFILE_NUM;
    max_ral_num = SDK_MAX_RAL_NUM;
    max_user_task_num = SDK_MAX_USER_TASK_NUM;
    slave_md_enable_default = false;

    statck_buffer_init(ENV_BUF_SIZE,DB_BUF_SIZE,MSG_BUF_SIZE,NON_RET_BUF_SIZE);
    prf_fn_init();
    ble_storage_max_num_init(SDK_BLE_STORAGE_PEER_MAX);
}

static bool dummy()
{
    return true;
}

__attribute((weak)) void (*eif_read) (uint8_t *bufptr, uint32_t size, void (*callback)(void *,uint8_t), void* dummy);
__attribute((weak)) void (*eif_write)(uint8_t *bufptr, uint32_t size, void (*callback)(void *,uint8_t), void* dummy);
__attribute((weak)) void (*eif_flow_on)(void);
__attribute((weak)) bool (*eif_flow_off)(void);

__attribute__((weak)) void uart_eif_read(uint8_t *bufptr, uint32_t size, void (*callback)(void *,uint8_t), void* dummy){}
__attribute__((weak)) void uart_eif_write(uint8_t *bufptr, uint32_t size, void (*callback)(void *,uint8_t), void* dummy){}
__attribute__((weak)) void uart_eif_flow_on(void){}
__attribute__((weak)) bool uart_eif_flow_off(void){return false;}

__attribute((weak)) void app_init(void){}

void main_task_app_init()
{
    main_task = 3;
    app_init_fn = app_init;
    eif_read = (void (*)(uint8_t *, uint32_t, void (*)(void *, uint8_t), void *))dummy;
    eif_write = (void (*)(uint8_t *, uint32_t, void (*)(void *, uint8_t), void *))dummy;
    eif_flow_on = (void (*)(void))dummy;
    eif_flow_off = (bool (*)(void))dummy;
}


void main_task_itf_init()
{
    main_task = 9;
    app_init_fn = (void (*)(void))dummy;
    eif_read = uart_eif_read;
    eif_write = uart_eif_write;
    eif_flow_on = uart_eif_flow_on;
    eif_flow_off = uart_eif_flow_off;
}

uint8_t peer_id_buf[SDK_MAX_CONN_NUM];

uint8_t *get_peer_id_buf()
{
    return peer_id_buf;
}

void eif_init(void *read,void *write,void *flow_on,void *flow_off)
{
    eif_read = (void (*)(uint8_t *,uint32_t,void (*)(void *,uint8_t),void*))read;
    eif_write = (void (*)(uint8_t *,uint32_t,void (*)(void *,uint8_t),void*))write;
    eif_flow_on = (void (*)(void))flow_on;
    eif_flow_off = (_Bool (*)(void))flow_off;
}

__attribute__((weak)) void ll_stack_buffer_init(uint32_t env_size,uint32_t msg_size,uint32_t non_ret_size){};

__attribute__((weak)) void ll_stack_reset_hook(){};

__attribute__((weak)) void ll_get_mac_addr(uint8_t *buf){}

__attribute__((weak)) void (*ll_get_mac_addr_fn)(uint8_t *);

__attribute__((weak)) uint32_t (*hci_rand_fn)();

uint32_t get_trng_value(void);

void ll_stack_var_ptr_init()
{
    ll_get_mac_addr_fn = ll_get_mac_addr;
    stack_assert_asm_fn = stack_assert_asm;
    platform_reset_fn = platform_reset;
    ecc_calc_fn = ecc_calc_start;
    rand_fn = rand;
    hci_rand_fn = get_trng_value;
    idiv_acc_fn = idiv_acc;
    enter_critical_fn = enter_critical;
    exit_critical_fn = exit_critical;
    stack_reset_hook_fn = ll_stack_reset_hook;
    lpcycles_to_hus_fn = lpcycles_to_hus;
    us_to_lpcycles_fn = us_to_lpcycles;
    lsi_freq_update_and_hs_to_lpcycles_fn = lsi_freq_update_and_hs_to_lpcycles;
    rf_reg_config_fn = rf_reg_config;
    #if SDK_LSI_USED
    lsi_used = true;
    #else
    lsi_used = false;
    #endif

    max_activity_num = SDK_MAX_ACT_NUM;
    max_ral_num = SDK_MAX_RAL_NUM;
    max_user_task_num = SDK_MAX_USER_TASK_NUM;
    slave_md_enable_default = false;

    ll_stack_buffer_init(ENV_BUF_SIZE,MSG_BUF_SIZE,NON_RET_BUF_SIZE);
}
