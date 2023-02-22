#include <string.h>
#include <stdio.h>
#include "tmall_mesh_ctl.h"
#include "log.h"
#include "le501x.h"
#include "ls_soc_gpio.h"
#include "builtin_timer.h"

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
        onoff_status.present_onoff = onoff_set->onoff;
        onoff_status.target_onoff = onoff_set->onoff;
        onoff_status.remain = 0;
        dev_mesh_status_rsp(msg,GENERIC_ONOFF_STATUS,(uint8_t *)&onoff_status,sizeof(onoff_status));
    }
}

void tmall_mesh_recv_vendor_msg(struct model_rx_info *msg)
{
    struct mesh_vendor_model_set *vendor_set;
    if (msg->opcode == APP_MESH_VENDOR_SET)
    {
        vendor_set = (struct mesh_vendor_model_set *)msg->info;
        LOG_I("attr_type:%x",vendor_set->attr_type);
        
        dev_mesh_status_rsp(msg,APP_MESH_VENDOR_STATUES,(uint8_t *)vendor_set,msg->rx_info_len);
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
