#ifndef _AT_CMD_PARSE_H_
#define _AT_CMD_PARSE_H_

#include "platform.h"
#include "modem_rf_le501x.h"
#include "ls_ble.h"

#define RECV_MAX_LEN 30
#define ADV_REPORT_NUM 10

struct at_ctrl
{
    uint32_t one_slot_send_len;
    uint16_t scan_duration; //uint: 10ms
    uint8_t transparent_start;
    uint8_t transparent_conidx;
    uint8_t one_slot_send_start;
};

typedef struct at_adv_report
{
    uint8_t data[0x1F];
    struct adv_report_info evt_type;
    struct dev_addr adv_addr;
    uint8_t adv_addr_type;
    uint8_t data_len;
    int8_t  rssi;
}adv_report_t;

typedef struct _at_recv_cmd
{
    uint8_t recv_data[RECV_MAX_LEN];
    uint16_t recv_len;
}at_recv_cmd_t;

typedef struct at_defualt_info
{
    uint8_t auto_trans;
    int8_t rfpower;
    uint8_t advint;
    uint8_t auto_sleep;
} default_info_t;

struct at_buff_env
{
    default_info_t default_info;
    adv_report_t adv_rpt[ADV_REPORT_NUM];
};
extern struct at_ctrl ls_at_ctl_env;
extern struct at_buff_env ls_at_buff_env;
extern const uint16_t adv_int_arr[6];

void at_recv_cmd_handler(at_recv_cmd_t *recv_buf);
void trans_mode_enter(void);
void trans_mode_exit(void);

#endif
