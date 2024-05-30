#ifndef _AT_SIG_MESH_PROVER_CMD_PARSE_H_
#define _AT_SIG_MESH_PROVER_CMD_PARSE_H_

#include "platform.h"
#include "modem_rf_le501x.h"
#include "ls_ble.h"

#define RECV_MAX_LEN 128

typedef struct _at_recv_cmd
{
    uint8_t recv_data[RECV_MAX_LEN];
    uint16_t recv_len;
}at_recv_cmd_t;

extern struct at_buff_env ls_at_buff_env;

/**
 * @brief 
 * 
 * @param recv_buf 
 */
void at_recv_cmd_handler(at_recv_cmd_t *recv_buf);

#endif //_AT_SIG_MESH_PROVER_CMD_PARSE_H_
