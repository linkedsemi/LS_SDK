#ifndef MAIN_H_
#define MAIN_H_

#include "app_config.h"
#include "at_recv_cmd.h"
#include "at_cmd_parse.h"
#include "log.h"
#include "ls_ble.h"
#include <stdio.h>
#define DEV_NAME_MAX_LEN 0x20
extern uint8_t ble_device_name[DEV_NAME_MAX_LEN];

uint8_t search_conidx(uint8_t con_idx);
uint8_t search_client_conidx(uint8_t con_idx);

void start_init(uint8_t *peer_addr,uint8_t addr_type);
void create_adv_obj(uint32_t adv_intv);
void delete_adv_obj(void);
void at_stop_adv(void);
void gap_adv_report_ind(struct adv_report_evt *param);
void gap_scaning_cmp_ind(void);

uint8_t get_adv_status(void);
void at_start_adv(void);
void start_scan(uint16_t scan_duration);
uint8_t get_ble_con_num(void);
uint8_t get_ble_con_num(void);
void update_conn_param(uint8_t conidx,uint16_t latency);
void update_adv_intv(uint32_t new_adv_intv);

bool get_con_status(uint8_t con_idx);
void ble_slave_recv_data_ind(uint8_t con_idx,uint8_t const *value,uint16_t len);
void ble_master_recv_data_ind(uint8_t con_idx,uint8_t const *value,uint16_t len);
void ble_slave_send_data(uint8_t con_idx,uint8_t *value,uint16_t len);
void ble_master_send_data(uint8_t con_idx,uint8_t *value,uint16_t len);

#endif
