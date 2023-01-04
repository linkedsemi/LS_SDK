#include <string.h>
#include <stdio.h>
#include "tmall_mesh_ctl.h"
#include "log.h"
#include "le501x.h"
#include "tmall_light_cfg.h"
#include "ls_soc_gpio.h"
#include "builtin_timer.h"

extern struct mesh_model_info model_env;
extern tinyfs_dir_t mesh_dir;
struct scene_store_message  Config_scence_msg[24];
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
void  tmall_mesh_recv_scene_msg (struct model_rx_info *msg)
{
    struct scene_register_staus_message  rsp_msg;
    int16_t t_index = 0;
    uint16_t t_len = 0;
    uint8_t t_status_code = 0;
    uint8_t scene_register_status_len=0;
    switch(msg->opcode)
    {
        case SCENE_RECALL:
        case SCENE_RECALL_UNAK:
        {
            struct scene_recall_messge  *recall_msg = (struct scene_recall_messge *)msg->info;
            t_index = recall_msg->scene_number - RECORD_PRESET_SCENCE_BASE - 1;
            LOG_I("RECALL_SCENE_NUM , scene_num=0x%x",recall_msg->scene_number);
            if(t_index>=0 && t_index<9)
            {
                switch(t_index)
                {
                case 0:
                     LOG_I("==================open curatin");
                break;
                case 1:
                     LOG_I("==================close curatin"); 
                break;
                case 2:
                     LOG_I("==================stop curatin"); 
                break;
                case 3: case 4: case 5: case 6: case 7: case 8:
                break;
              }
            }
            else if(t_index>=0x64 && t_index<(0x64+24))
            {
               t_index -=0x64;
               t_len = sizeof(struct scene_store_message);
               tinyfs_read(mesh_dir, recall_msg->scene_number, (uint8_t *)&Config_scence_msg[t_index], &t_len);
               LOG_I("t_index= %d,type_curtainctrl=0X%X",t_index,Config_scence_msg[t_index].type_curtainctrl);
            }        
        }          
        break;
        case SCENE_STORE:
        case SCENE_STORE_UNAK:
        {
            struct scene_store_message  *store_msg = (struct scene_store_message *)msg->info;
            t_index = store_msg->scene_number - RECORD_CONFIG_SCENCE_BASE - 1;
            if((t_index>=0) && t_index <RECORD_CONFIG_SCENCE_NUM)
            {
                memcpy(&Config_scence_msg[t_index],store_msg,sizeof(struct scene_store_message));
                tinyfs_write(mesh_dir, store_msg->scene_number, (uint8_t *)&Config_scence_msg[t_index], sizeof(struct scene_store_message));
                t_status_code = SCENE_STATUS_CODE_SUCCESS;
            }
            else
            {    
                t_status_code = SCENE_STATUS_CODE_NOT_FOUND;
            }
            rsp_msg.status_code = t_status_code;
            rsp_msg.current_scene = store_msg->scene_number;
            scene_register_status_len =3;
            dev_mesh_status_rsp(msg,SCENE_REGISTER_STATUS,(uint8_t *)&rsp_msg,scene_register_status_len);
        }
        break;
        case SCENE_DELETE:
        case SCENE_DELETE_UNAK:
        {
             struct scene_delete_message  *delete_msg = (struct scene_delete_message *)msg->info;
             t_index = delete_msg->scene_number - RECORD_CONFIG_SCENCE_BASE - 1;
             LOG_I("DELETE_SCENE_NUM , scene_num=0x%x",delete_msg->scene_number);
             if((t_index>=0) && t_index <RECORD_CONFIG_SCENCE_NUM)
             {
                  memset(&Config_scence_msg[t_index],0,sizeof(struct scene_store_message));
                  tinyfs_write(mesh_dir, delete_msg->scene_number, (uint8_t *)&Config_scence_msg[t_index], sizeof(struct scene_store_message));
                  t_status_code = SCENE_STATUS_CODE_SUCCESS;
             }
             else
             {
               t_status_code = SCENE_STATUS_CODE_NOT_FOUND;     
             } 
            rsp_msg.status_code = t_status_code;
            rsp_msg.current_scene = delete_msg->scene_number;
            scene_register_status_len = 3;
            dev_mesh_status_rsp(msg,SCENE_REGISTER_STATUS,(uint8_t *)&rsp_msg,scene_register_status_len);
        }
        break;
        case SCENE_GET:
        {
            struct scene_staus_message  rsp_msg;
            rsp_msg.status_code = SCENE_STATUS_CODE_SUCCESS;
            rsp_msg.current_scene = 0x0001;
            rsp_msg.target_scene = 0x0002;
            rsp_msg.remaining_time =0;
            LOG_I("SCENE_GET_STATUS");
            dev_mesh_status_rsp(msg,SCENE_STATUS,(uint8_t *)&rsp_msg,sizeof(struct scene_staus_message));
        }
        break;
        case SCENE_REGISTER_GET:
        {
            rsp_msg.status_code = SCENE_STATUS_CODE_SUCCESS;
            rsp_msg.current_scene = 0x0001;//Current scene
            scene_register_status_len =3;
            LOG_I("SCENE_REGISTER_GET_STATUS");
            dev_mesh_status_rsp(msg,SCENE_REGISTER_STATUS,(uint8_t *)&rsp_msg,scene_register_status_len);
        }
        break;
        default:
        break;
    }
}
