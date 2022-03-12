#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include "sdk_config.h"
#include "platform.h"
#include "cpu.h"
#include "log.h"
#include "io_config.h"

uint8_t peer_id_buf[SDK_MAX_CONN_NUM];

uint8_t *get_peer_id_buf()
{
    return peer_id_buf;
}

extern uint8_t main_task;
extern uint8_t max_activity_num;
extern uint8_t max_profile_num;
extern uint8_t max_ral_num;
extern uint8_t max_user_task_num;
extern void (*stack_assert_asm_fn)(uint32_t,uint32_t,uint32_t);
extern void (*platform_reset_fn)(uint32_t);
extern int (*rand_fn) (void);
extern void (*exit_critical_fn)(uint32_t);
extern uint32_t (*enter_critical_fn)(void);
extern void (*app_init_fn)(void); 
extern void (*eif_read) (uint8_t *bufptr, uint32_t size, void (*callback)(void *,uint8_t), void* dummy);
extern void (*eif_write)(uint8_t *bufptr, uint32_t size, void (*callback)(void *,uint8_t), void* dummy);
extern void (*eif_flow_on)(void);
extern bool (*eif_flow_off)(void);
extern void *(*ll_malloc_fn)(size_t);
extern void (*ll_free_fn)(void *);
extern uint32_t (*ble_hclk2lpclk_fn)(uint32_t);
extern uint32_t (*ble_lpclk2hclk_fn)(uint32_t);
extern void (*io_set_pin_fn)(uint8_t);
extern void (*io_clr_pin_fn)(uint8_t);
extern void *hci_write;
extern void *hci_read;
static bool dummy()
{
    return true;
}

__attribute__((weak)) void uart_eif_read(uint8_t *bufptr, uint32_t size, void (*callback)(void *,uint8_t), void* dummy){}
__attribute__((weak)) void uart_eif_write(uint8_t *bufptr, uint32_t size, void (*callback)(void *,uint8_t), void* dummy){}
void controller_read(uint8_t *buf,uint16_t length,void (*cb)());
void controller_write(uint8_t *buf,uint16_t length,void (*cb)());

static void eif0_set()
{
    eif_read = (void (*)(uint8_t *, uint32_t, void (*)(void *, uint8_t), void *))dummy;
    eif_write = (void (*)(uint8_t *, uint32_t, void (*)(void *, uint8_t), void *))dummy;
    eif_flow_on = (void (*)(void))dummy;
    eif_flow_off = (bool (*)(void))dummy;
}

void app_init(void);

void main_task_app_init()
{
    main_task = 0;
    app_init_fn = app_init;
    hci_read = controller_read;
    hci_write = controller_write;
    eif0_set();
}


void main_task_itf_init()
{
    main_task = 6;
    app_init_fn = (void (*)(void))dummy;
    hci_read = uart_eif_read;
    hci_write = uart_eif_write;
    eif0_set();
}

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

uint32_t task_list_buf[10 + SDK_MAX_PROFILE_NUM + SDK_MAX_USER_TASK_NUM];

uint8_t per_adv_rep_chain_stat_buf[SDK_MAX_ACT_NUM];

void ke_mem_func_init();
void host_buffer_init();
void prf_fn_init(void);
void ble_storage_max_num_init(uint8_t num);
uint32_t ble_hclk2lpclk(uint32_t cycles);
uint32_t ble_lpclk2hclk(uint32_t cycles);
void ll_buf_init(void);

void stack_var_ptr_init()
{
    stack_assert_asm_fn = stack_assert_asm;
    platform_reset_fn = platform_reset;
    rand_fn = rand;
    enter_critical_fn = enter_critical;
    exit_critical_fn = exit_critical;
    ll_malloc_fn = malloc;
    ll_free_fn = free;
    io_set_pin_fn = io_set_pin;
    io_clr_pin_fn = io_clr_pin;
    ble_hclk2lpclk_fn = ble_hclk2lpclk;
    ble_lpclk2hclk_fn = ble_lpclk2hclk;

    
    max_activity_num = SDK_MAX_ACT_NUM;
    max_profile_num = SDK_MAX_PROFILE_NUM;
    max_ral_num = SDK_MAX_RAL_NUM;
    max_user_task_num = SDK_MAX_USER_TASK_NUM;
    
    host_buffer_init();
    ke_mem_func_init();
    prf_fn_init();
    ble_storage_max_num_init(SDK_BLE_STORAGE_PEER_MAX);
    ll_buf_init();

}
