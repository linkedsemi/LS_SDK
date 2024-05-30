#include <string.h>
#include <stdio.h>
#include "sig_mesh_ctl.h"
#include "cpu.h"
#include "log.h"
#include "le501x.h"
#include "sig_light_cfg.h"
extern UART_HandleTypeDef UART_SIG_MESH_Config;
extern struct mesh_model_info model_env;
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

void sig_mesh_mdl_state_upd_hdl(struct model_state_upd* msg)
{
    switch(msg->state_id)
    {
        case MESH_STATE_GEN_ONOFF:
        {
            if (msg->elmt_idx==model_env.info[MODEL0_GENERIC_ONOFF_SVC].element_id)
            {
               ls_mesh_light_set_onoff((uint8_t)msg->state, LIGHT_LED_2); 
            }
        }    
        break;
        case MESH_STATE_GEN_LVL:
        {
            if (msg->elmt_idx==model_env.info[MODEL1_GENERIC_LEVEL_SVC].element_id)
            {
               ls_mesh_light_set_lightness(((uint16_t)msg->state - GENERIC_LEVEL_MIN),LIGHT_LED_1); 
            }
        }
        break;
        default:
        break;
    }
}
