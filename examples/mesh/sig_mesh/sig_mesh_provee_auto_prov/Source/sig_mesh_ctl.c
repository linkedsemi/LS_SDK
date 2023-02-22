#include <string.h>
#include <stdio.h>
#include "sig_mesh_ctl.h"
#include "cpu.h"
#include "log.h"
#include "le501x.h"

void dev_mesh_status_rsp(struct model_rx_info const *ind,uint32_t opcode,uint8_t *status,uint16_t cmd_len)
{
    struct model_send_info rsp;
    rsp.opcode = opcode;
    rsp.ModelHandle = ind->ModelHandle;
    rsp.app_key_lid = ind->app_key_lid;
    rsp.dest_addr = ind->source_addr;
    rsp.len = ind->rx_info_len;
    memcpy(rsp.info, status, cmd_len);
    model_send_info_handler(&rsp);
}
