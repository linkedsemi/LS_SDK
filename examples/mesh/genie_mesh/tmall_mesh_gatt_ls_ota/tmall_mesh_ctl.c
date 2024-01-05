#include <string.h>
#include <stdio.h>
#include "tmall_mesh_ctl.h"
#include "log.h"
#include "le501x.h"
#include "tmall_light_cfg.h"
#include "ls_soc_gpio.h"
#include "builtin_timer.h"

extern struct mesh_model_info model_env;

static uint8_t tmall_hdw_rst_indicate_tid =NODE_INITI_REPORT_TID_MIN;
static uint8_t cnt_report_hardware_node_rst=0;
static bool genie_app_check_hdw_rst_flg=false;
static bool app_hdw_rst_node_status=false;

void dev_mesh_status_rsp(struct model_rx_info const *ind,uint32_t opcode,uint8_t *status,uint16_t cmd_len)
{
    struct model_send_info rsp;
    rsp.opcode = opcode;
    rsp.ModelHandle = ind->ModelHandle;
    rsp.app_key_lid = ind->app_key_lid;
    rsp.dest_addr = ind->source_addr;
    rsp.len = ind->rx_info_len;
    memcpy(rsp.info, status, cmd_len);
    LOG_I("status");
    model_send_info_handler(&rsp);  
}

void tmall_mesh_recv_onoff_msg(struct model_rx_info *msg)
{
    struct mesh_generic_onoff_set *onoff_set;
    struct mesh_generic_onoff_status onoff_status;
    if(msg->opcode == GENERIC_ONOFF_SET)
    {
        onoff_set = (struct mesh_generic_onoff_set *)msg->info;
        //LightControl( LED_0 | LED_1, onoff_set->onoff);
        tmall_light_set_onoff(onoff_set->onoff);
        onoff_status.present_onoff = onoff_set->onoff;
        onoff_status.target_onoff = onoff_set->onoff;
        onoff_status.remain = 0;
        dev_mesh_status_rsp(msg,GENERIC_ONOFF_STATUS,(uint8_t *)&onoff_status,sizeof(onoff_status));
    }
}

void tmall_mesh_recv_vendor_msg(struct model_rx_info *msg)
{
    struct mesh_vendor_model_set *vendor_set;
    vendor_set = (struct mesh_vendor_model_set *)msg->info;
    if (msg->opcode == APP_MESH_VENDOR_SET_ACK)
    {
        vendor_set = (struct mesh_vendor_model_set *)msg->info;
        LOG_I("attr_type:%x",vendor_set->attr_type);
        
        dev_mesh_status_rsp(msg,APP_MESH_VENDOR_STATUS,(uint8_t *)vendor_set,msg->rx_info_len);
    }
    else if(msg->opcode == APP_MESH_VENDOR_CONFIRMATION)
    {
       if ((vendor_set->tid >=NODE_INITI_REPORT_TID_MIN) && (vendor_set->tid <=NODE_INITI_REPORT_TID_MAX) && app_hdw_rst_node_status) 
       {
           genie_app_check_hdw_rst_flg = true;
       }
    }
}

void tmall_mesh_recv_lightness_msg(struct model_rx_info *msg)
{
    struct mesh_generic_level_set *lightness_set;
    struct mesh_generic_level_status lightness_status;
    if(msg->opcode == LIGHT_LIGHTNESS_SET)
    {
        lightness_set = (struct mesh_generic_level_set *)msg->info;

        LOG_I("lightness:%04x",lightness_set->level);
        tmall_light_set_lightness(lightness_set->level);
        lightness_status.current_level = lightness_set->level;
        lightness_status.target_level = lightness_set->level;
        lightness_status.remain = 0;

        dev_mesh_status_rsp(msg,LIGHT_LIGHTNESS_STATUS,(uint8_t *)&lightness_status,sizeof(lightness_status));
    }
}

void tmall_mesh_recv_light_ctl_msg(struct model_rx_info *msg)
{
    struct mesh_ctl_model_set *ctl_set;
    struct mesh_ctl_model_status ctl_status;
    if(msg->opcode == LIGHT_CTL_SET)
    {
        ctl_set = (struct mesh_ctl_model_set *)msg->info;
        LOG_I("temperature:%x",ctl_set->temperature);

        ctl_status.current_lightness = ctl_set->lightness;
        ctl_status.current_temperature = ctl_set->temperature;
        ctl_status.target_lightness = ctl_set->lightness;
        ctl_status.target_temperature = ctl_set->temperature;
        ctl_status.remain = 0;
        dev_mesh_status_rsp(msg,LIGHT_CTL_STATUS,(uint8_t *)&ctl_status,sizeof(ctl_status));
    }
    else if(msg->opcode == LIGHT_CTL_SET_UNACK)
    {

    }
}

void tmall_mesh_recv_light_hsl_msg(struct model_rx_info *msg)
{
    struct mesh_hsl_model_set *hsl_set;
    struct mesh_hsl_model_status hsl_status;
    if(msg->opcode == LIGHT_HSL_SET)
    {
        hsl_set = (struct mesh_hsl_model_set *)msg->info;

        hsl_status.hsl_lightness = hsl_set->lightness;
        hsl_status.hsl_hue = hsl_set->hue;
        hsl_status.hsl_saturation = hsl_set->hsl_saturation;
        hsl_status.remain = 0;
        dev_mesh_status_rsp(msg,LIGHT_HSL_STATUS,(uint8_t *)&hsl_status,sizeof(hsl_status));
    }
    else if(msg->opcode == LIGHT_HSL_SET_UNACK)
    {

    }
}

uint8_t tmall_mesh_hardware_node_reset_ind(uint8_t model_lid, uint8_t app_key_lid, uint16_t dst_addr)
{
    struct model_send_info hardware_node_rst;
     
     app_hdw_rst_node_status = true;
     if (((cnt_report_hardware_node_rst++) >6) || (genie_app_check_hdw_rst_flg == true))
     {
         ls_sig_mesh_disable();
         cnt_report_hardware_node_rst=0;
         genie_app_check_hdw_rst_flg = false;
         app_hdw_rst_node_status = false;
         return cnt_report_hardware_node_rst;        
     }

    tmall_hdw_rst_indicate_tid++;
    cnt_report_hardware_node_rst++;
    hardware_node_rst.ModelHandle = model_lid;
    hardware_node_rst.opcode =  APP_MESH_VENDOR_INDICATION;
    hardware_node_rst.app_key_lid = app_key_lid; 
    hardware_node_rst.dest_addr = dst_addr;
    hardware_node_rst.info[0] = ((tmall_hdw_rst_indicate_tid>NODE_INITI_REPORT_TID_MAX)?NODE_INITI_REPORT_TID_MIN:tmall_hdw_rst_indicate_tid);  //tid
    hardware_node_rst.info[1] = (uint8_t)(VENDOR_ATTR_TYPE_EVENT & 0x00ff);
    hardware_node_rst.info[2] = (uint8_t)((VENDOR_ATTR_TYPE_EVENT & 0xff00)>>8);
    hardware_node_rst.info[3] = NODE_HARDWARE_RST_EVENT;
    hardware_node_rst.len = 4; 
    model_send_info_handler(&hardware_node_rst);
   return cnt_report_hardware_node_rst;
}
