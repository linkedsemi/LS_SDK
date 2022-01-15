#include <string.h>
#include <stdio.h>
#include "sig_mesh_ctl.h"
#include "cpu.h"
#include "log.h"
#include "le501x.h"
#include "sig_light_cfg.h"
extern UART_HandleTypeDef UART_SIG_MESH_Config;
extern struct mesh_model_info model_env;
extern void app_generic_onoff_status_report(uint8_t onoff);
extern void app_light_lightness_status_report(void);
extern void app_light_ctl_temp_status_report(void);
extern void app_light_hsl_hue_status_report(void);
extern void app_light_hsl_sat_status_report(void);
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
    LOG_I("element_idx=%d,element_state_id=%d,element_state=%d,element_trans_time_ms=%d",msg->elmt_idx,msg->state_id,msg->state,msg->trans_time_ms);
    switch(msg->state_id)
    {
        case MESH_STATE_GEN_ONOFF:
        {
            LOG_I("MESH_STATE_GEN_ONOFF");
            if (msg->elmt_idx==model_env.info[MODEL0_GENERIC_ONOFF_SVC].element_id)
            {
                ls_mesh_light_set_onoff((uint8_t)msg->state, LIGHT_LED_2); 
                app_generic_onoff_status_report((uint8_t)msg->state);
            }
        }    
        break;
        case MESH_STATE_GEN_LVL:
        {
             LOG_I("MESH_STATE_GEN_LVL");
             
            if (msg->elmt_idx==model_env.info[MODEL1_GENERIC_LEVEL_SVC].element_id)
            {
               ls_mesh_light_set_lightness(((uint16_t)msg->state - GENERIC_LEVEL_MIN),LIGHT_LED_1); 
            }
        }
        break; 
        case MESH_STATE_LIGHT_LN:
        {
             LOG_I("MESH_STATE_LIGHT_LN");
            if (msg->elmt_idx==model_env.info[MODEL3_LIGHT_LIGHTNESS_SVC].element_id)
            {
                app_light_lightness_status_report();
            }
        }
        break;
        case MESH_STATE_LIGHT_CTL_TEMP:
        {
            LOG_I("MESH_STATE_LIGHT_CTL_TEMP");
            if (msg->elmt_idx==model_env.info[MODEL4_LIGHT_CTL_SVC].element_id)
            {
                app_light_ctl_temp_status_report();
            }
        }
        break;
        case MESH_STATE_LIGHT_HSL_HUE:
        {
             LOG_I("MESH_STATE_LIGHT_HSL_HUE");
            if (msg->elmt_idx==model_env.info[MODEL5_LIGHT_HSL_SVC].element_id)
            {
                app_light_hsl_hue_status_report();
            }
        }
        break;
        case MESH_STATE_LIGHT_HSL_SAT:
        {
             LOG_I("MESH_STATE_LIGHT_HSL_SAT");
            if (msg->elmt_idx==model_env.info[MODEL5_LIGHT_HSL_SVC].element_id)
            {
                app_light_hsl_sat_status_report();
            }
        }
        break;
        default:
        break;
    }
}
