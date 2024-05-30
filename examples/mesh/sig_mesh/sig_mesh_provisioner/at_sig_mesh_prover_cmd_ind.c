#include <stdlib.h>
#include <string.h>
#include "at_sig_mesh_prover_recv_cmd.h"
#include "ls_sig_mesh_provisioner.h"
#include "log.h"

extern void hex_arr_to_str(uint8_t *str, const uint8_t hex_arr[], uint8_t arr_len);
extern void dec_arr_to_str(uint8_t *str, const uint8_t hex_arr[], uint8_t arr_len);

void at_prover_ready_ind(void)
{
    uint8_t ind_len={0};
    char ind_msg[100]={0};
    char ready_info[18] = "Prover Start Scan?";

    ind_len = sprintf((char *)ind_msg,"\r\n%s Y or N\r\n",ready_info);
    uart_write((uint8_t *)ind_msg,ind_len);
}

void at_prover_report_dev_uuid(uint8_t *param,int8_t rssi)
{
    uint8_t ind_len=0;
    char ind_msg[100]={0};
    uint8_t dev_uuid_str[UUID_MESH_DEV_LEN*2+1]={0};
    uint8_t at_dev_rssi[sizeof(uint8_t)*2+1]={0};
    uint8_t tmp_dev_rssi=0;

    hex_arr_to_str(dev_uuid_str,param,UUID_MESH_DEV_LEN);
    ind_len = sprintf(ind_msg,"\r\n+DEV_UUID:%s\r\n",dev_uuid_str);
    uart_write((uint8_t *)ind_msg,ind_len);
    
    tmp_dev_rssi = abs(rssi);
    dec_arr_to_str(at_dev_rssi,(uint8_t *)&tmp_dev_rssi,sizeof(uint8_t));
    if (rssi>=0)
    {
       ind_len = sprintf(ind_msg,"\r\n+DEV_RSSI:%s\r\n",at_dev_rssi);
    }
    else
    {
       ind_len = sprintf(ind_msg,"\r\n+DEV_RSSI:-%s\r\n",at_dev_rssi);
    }
    uart_write((uint8_t *)ind_msg,ind_len);
}

void at_prover_report_provisiong_status(uint8_t state, uint16_t status,uint16_t node_unicast_address)
{
    uint8_t ind_len=0;
    char ind_msg[100]={0};
    uint8_t at_node_address[sizeof(uint16_t)*2+1]={0};
    uint8_t at_status[sizeof(uint16_t)*2+1]={0};


     hex_arr_to_str(at_node_address,(uint8_t *)&node_unicast_address,sizeof(uint16_t));
    if(state == PROVISIONING_SUCCEED)
    {
       ind_len = sprintf(ind_msg,"\r\n+Provisioning_Succeed-Unicast_addr:%s\r\n",at_node_address);
    }
    else
    {
       ind_len = sprintf(ind_msg,"\r\n+DEV_Provisioning_Fail-Unicast_addr:%s\r\n",at_node_address);
    }
    uart_write((uint8_t *)ind_msg,ind_len);

    hex_arr_to_str(at_status,(uint8_t *)&status,sizeof(uint16_t));
    ind_len = sprintf(ind_msg,"\r\n+DEV_Provisioning_status:%s\r\n",at_status);
    uart_write((uint8_t *)ind_msg,ind_len);
}

void at_prover_report_dev_composition_data0(uint16_t unicast_addr,uint16_t company_id, uint16_t product_id,uint16_t version_id, uint16_t support_feature, uint8_t dev_nb_elements)
{
    uint8_t ind_len=0;
    char ind_msg[100]={0};
    uint8_t at_unicast_addr[sizeof(uint16_t)*2+1]={0};
    uint8_t at_company_id[sizeof(uint16_t)*2+1]={0};
    uint8_t at_product_id[sizeof(uint16_t)*2+1]={0};
    uint8_t at_version_id[sizeof(uint16_t)*2+1]={0};
    uint8_t at_support_feature[sizeof(uint16_t)*2+1]={0};
    uint8_t at_dev_nb_elements[sizeof(uint8_t)*2+1]={0};


     hex_arr_to_str(at_unicast_addr,(uint8_t *)&unicast_addr,sizeof(uint16_t));
     ind_len = sprintf(ind_msg,"\r\n+Unicast_address:%s\r\n",at_unicast_addr);
     uart_write((uint8_t *)ind_msg,ind_len);
     
     hex_arr_to_str(at_company_id,(uint8_t *)&company_id,sizeof(uint16_t));
     ind_len = sprintf(ind_msg,"+Company_ID:%s\r\n",at_company_id);
     uart_write((uint8_t *)ind_msg,ind_len);
     
     hex_arr_to_str(at_product_id,(uint8_t *)&product_id,sizeof(uint16_t));
     ind_len = sprintf(ind_msg,"+Product_ID:%s\r\n",at_product_id);
     uart_write((uint8_t *)ind_msg,ind_len);
     
     hex_arr_to_str(at_version_id,(uint8_t *)&version_id,sizeof(uint16_t));
     ind_len = sprintf(ind_msg,"+Version_ID:%s\r\n",at_version_id);
     uart_write((uint8_t *)ind_msg,ind_len);
     
     hex_arr_to_str(at_support_feature,(uint8_t *)&support_feature,sizeof(uint16_t));
     ind_len = sprintf(ind_msg,"+Support_Feature:%s\r\n",at_support_feature);
     uart_write((uint8_t *)ind_msg,ind_len);
    
     hex_arr_to_str(at_dev_nb_elements,(uint8_t *)&dev_nb_elements,sizeof(uint8_t));
     ind_len = sprintf(ind_msg,"+Dev_Nb_Elements:%s\r\n",at_dev_nb_elements);
     uart_write((uint8_t *)ind_msg,ind_len);
}

void at_prover_report_dev_composition_data0_element(uint16_t element_addr,uint8_t number_sig_models, uint8_t number_vendor_models,uint8_t *model_info)
{
    uint8_t ind_len=0;
    char ind_msg[100]={0};
    uint8_t rx_model_info[80]={0}; //4*max number_model 4*20 
    uint8_t at_element_addr[sizeof(uint16_t)*2+1]={0};
    uint8_t at_num_model[sizeof(uint8_t)*2+1]={0};
    uint8_t at_sig_model[sizeof(uint16_t)*2+1]={0};
    uint8_t at_vendor_model[sizeof(uint32_t)*2+1]={0};
    uint32_t offset=0;
    uint8_t num_models=0; 

     hex_arr_to_str(at_element_addr,(uint8_t *)&element_addr,sizeof(uint16_t));
     ind_len = sprintf(ind_msg,"\r\n+Element:%s\r\n",at_element_addr);
     uart_write((uint8_t *)ind_msg,ind_len);

     num_models=number_sig_models+number_vendor_models; 
     hex_arr_to_str(at_num_model,(uint8_t *)&num_models,sizeof(uint16_t));
     ind_len = sprintf(ind_msg,"+Models_Num:%s\r\n",at_num_model);
     uart_write((uint8_t *)ind_msg,ind_len);
     
     memcpy(rx_model_info,model_info,(number_sig_models+number_vendor_models)*4*sizeof(uint8_t));
     for(uint8_t i=0; i<number_sig_models;i++)
     {
         hex_arr_to_str(at_sig_model,(rx_model_info+i*sizeof(uint32_t)),sizeof(uint16_t));
         ind_len = sprintf(ind_msg,"+sig_model:%s\r\n",at_sig_model);
         uart_write((uint8_t *)ind_msg,ind_len);
     }
     
    offset = number_sig_models*sizeof(uint32_t);

     for(uint8_t i=0; i<number_vendor_models;i++)
     {
         hex_arr_to_str(at_vendor_model,(rx_model_info+offset+i*sizeof(uint32_t)),sizeof(uint32_t));
         ind_len = sprintf(ind_msg,"+vendor_model:%s\r\n",at_vendor_model);
         uart_write((uint8_t *)ind_msg,ind_len);
     }

}

void at_prover_report_dev_default_ttl(uint16_t unicast_addr,uint8_t default_ttl)
{
    uint8_t ind_len=0;
    char ind_msg[100]={0};
    uint8_t at_unicast_addr[sizeof(uint16_t)*2+1]={0};
    uint8_t at_default_ttl[sizeof(uint8_t)*2+1]={0};

     hex_arr_to_str(at_unicast_addr,(uint8_t *)&unicast_addr,sizeof(uint16_t));
     ind_len = sprintf(ind_msg,"\r\n+Unicast_address:%s\r\n",at_unicast_addr);
     uart_write((uint8_t *)ind_msg,ind_len);
     
     hex_arr_to_str(at_default_ttl,(uint8_t *)&default_ttl,sizeof(uint8_t));
     ind_len = sprintf(ind_msg,"+Default_ttl:%s\r\n",at_default_ttl);
     uart_write((uint8_t *)ind_msg,ind_len);
}

void at_prover_report_node_app_key_status(uint16_t unicast_addr,uint8_t active_status,uint16_t net_key_id,uint8_t app_key_id)
{
    uint8_t ind_len=0;
    char ind_msg[100]={0};
    uint8_t at_unicast_addr[sizeof(uint16_t)*2+1]={0};
    uint8_t at_active_status[sizeof(uint8_t)*2+1]={0};
    uint8_t at_net_key_id[sizeof(uint16_t)*2+1]={0};
    uint8_t at_app_key_id[sizeof(uint16_t)*2+1]={0};
   

     hex_arr_to_str(at_unicast_addr,(uint8_t *)&unicast_addr,sizeof(uint16_t));
     ind_len = sprintf(ind_msg,"\r\n+Unicast_address:%s\r\n",at_unicast_addr);
     uart_write((uint8_t *)ind_msg,ind_len);
     
     hex_arr_to_str(at_active_status,(uint8_t *)&active_status,sizeof(uint8_t));
     ind_len = sprintf(ind_msg,"+App_key_active_status:%s\r\n",at_active_status);
     uart_write((uint8_t *)ind_msg,ind_len);

     hex_arr_to_str(at_net_key_id,(uint8_t *)&net_key_id,sizeof(uint16_t));
     ind_len = sprintf(ind_msg,"+Net_key_id:%s\r\n",at_net_key_id);
     uart_write((uint8_t *)ind_msg,ind_len);

     hex_arr_to_str(at_app_key_id,(uint8_t *)&app_key_id,sizeof(uint16_t));
     ind_len = sprintf(ind_msg,"+App_key_id:%s\r\n",at_app_key_id);
     uart_write((uint8_t *)ind_msg,ind_len);
}

void at_prover_report_dev_key(uint16_t unicast_addr,uint8_t *devkey)
{
    uint8_t ind_len=0;
    char ind_msg[100]={0};
    uint8_t at_unicast_addr[sizeof(uint16_t)*2+1]={0};
    uint8_t at_dev_key[BLE_KEY_LEN*2+1]={0};
    char ready_info[33] = "+Mesh Node Configuration Complete";
     hex_arr_to_str(at_unicast_addr,(uint8_t *)&unicast_addr,sizeof(uint16_t));
     ind_len = sprintf(ind_msg,"\r\n+Unicast_address:%s\r\n",at_unicast_addr);
     uart_write((uint8_t *)ind_msg,ind_len);
     
    hex_arr_to_str(at_dev_key,devkey,BLE_KEY_LEN);
    ind_len = sprintf(ind_msg,"\r\n+DEV KEY:%s\r\n",at_dev_key);
    uart_write((uint8_t *)ind_msg,ind_len);

    memset((uint8_t *)ind_msg,0,100*sizeof(char));
    ind_len = sprintf((char *)ind_msg,"\r\n%s\r\n",ready_info);
    uart_write((uint8_t *)ind_msg,ind_len);
}

void at_prover_report_model_subs_status(uint16_t unicast_addr,uint8_t subs_status,uint16_t element_addr,uint32_t model_id,uint16_t subs_value)
{
    uint8_t ind_len=0;
    char ind_msg[100]={0};
    uint8_t at_unicast_addr[sizeof(uint16_t)*2+1]={0};
    uint8_t at_subs_status[sizeof(uint8_t)*2+1]={0};
    uint8_t at_element_addr[sizeof(uint16_t)*2+1]={0};
    uint8_t at_model_id[sizeof(uint32_t)*2+1]={0};
    uint8_t at_subs_value[sizeof(uint16_t)*2+1]={0};

     hex_arr_to_str(at_unicast_addr,(uint8_t *)&unicast_addr,sizeof(uint16_t));
     ind_len = sprintf(ind_msg,"\r\n+Unicast_address:%s\r\n",at_unicast_addr);
     uart_write((uint8_t *)ind_msg,ind_len);
     
     hex_arr_to_str(at_subs_status,(uint8_t *)&subs_status,sizeof(uint8_t));
     ind_len = sprintf(ind_msg,"+Subs_status:%s\r\n",at_subs_status);
     uart_write((uint8_t *)ind_msg,ind_len);

     hex_arr_to_str(at_element_addr,(uint8_t *)&element_addr,sizeof(uint16_t));
     ind_len = sprintf(ind_msg,"+Element_Addr:%s\r\n",at_element_addr);
     uart_write((uint8_t *)ind_msg,ind_len);

     hex_arr_to_str(at_model_id,(uint8_t *)&model_id,sizeof(uint32_t));
     ind_len = sprintf(ind_msg,"+Model_id:%s\r\n",at_model_id);
     uart_write((uint8_t *)ind_msg,ind_len);

     hex_arr_to_str(at_subs_value,(uint8_t *)&subs_value,sizeof(uint16_t));
     ind_len = sprintf(ind_msg,"+Subs_Value:%s\r\n",at_subs_value);
     uart_write((uint8_t *)ind_msg,ind_len);
}

void at_prover_report_model_app_status(uint16_t unicast_addr,uint8_t model_app_status,uint16_t element_addr,uint32_t model_id,uint16_t model_app_value)
{
    uint8_t ind_len=0;
    char ind_msg[100]={0};
    uint8_t at_unicast_addr[sizeof(uint16_t)*2+1]={0};
    uint8_t at_model_app_status[sizeof(uint8_t)*2+1]={0};
    uint8_t at_element_addr[sizeof(uint16_t)*2+1]={0};
    uint8_t at_model_id[sizeof(uint32_t)*2+1]={0};
    uint8_t at_model_app_value[sizeof(uint16_t)*2+1]={0};

     hex_arr_to_str(at_unicast_addr,(uint8_t *)&unicast_addr,sizeof(uint16_t));
     ind_len = sprintf(ind_msg,"\r\n+Unicast_address:%s\r\n",at_unicast_addr);
     uart_write((uint8_t *)ind_msg,ind_len);
     
     hex_arr_to_str(at_model_app_status,(uint8_t *)&model_app_status,sizeof(uint8_t));
     ind_len = sprintf(ind_msg,"+Model_App_status:%s\r\n",at_model_app_status);
     uart_write((uint8_t *)ind_msg,ind_len);

     hex_arr_to_str(at_element_addr,(uint8_t *)&element_addr,sizeof(uint16_t));
     ind_len = sprintf(ind_msg,"+Element_Addr:%s\r\n",at_element_addr);
     uart_write((uint8_t *)ind_msg,ind_len);

     hex_arr_to_str(at_model_id,(uint8_t *)&model_id,sizeof(uint32_t));
     ind_len = sprintf(ind_msg,"+Model_id:%s\r\n",at_model_id);
     uart_write((uint8_t *)ind_msg,ind_len);

     hex_arr_to_str(at_model_app_value,(uint8_t *)&model_app_value,sizeof(uint16_t));
     ind_len = sprintf(ind_msg,"+Model_App_Value:%s\r\n",at_model_app_value);
     uart_write((uint8_t *)ind_msg,ind_len);
}

void at_prover_report_model_pub_status(uint16_t unicast_addr,uint8_t model_app_status,int16_t element_addr,int16_t publish_addr,uint16_t app_key_id,bool cred_flag,uint8_t publish_ttl,uint32_t publish_period_ms,uint8_t publish_retx_cont,uint8_t publish_retx_intv_step_solution,uint32_t model_id)
{ 
    uint8_t ind_len=0;
    char ind_msg[100]={0};
    uint8_t at_unicast_addr[sizeof(uint16_t)*2+1]={0};
    uint8_t at_model_app_status[sizeof(uint8_t)*2+1]={0};
    uint8_t at_element_addr[sizeof(uint16_t)*2+1]={0};
    uint8_t at_publish_addr[sizeof(uint16_t)*2+1]={0};
    uint8_t at_app_key_id[sizeof(uint16_t)*2+1]={0};
    uint8_t at_cred_flag[sizeof(uint8_t)*2+1]={0};
    uint8_t at_publish_ttl[sizeof(uint8_t)*2+1]={0};
    uint8_t at_publish_period_ms[sizeof(uint32_t)*2+1]={0};
    uint8_t at_publish_retx_cont[sizeof(uint8_t)*2+1]={0};
    uint8_t at_publish_retx_intv_step_solution[sizeof(uint8_t)*2+1]={0};
    uint8_t at_model_id[sizeof(uint32_t)*2+1]={0};

    hex_arr_to_str(at_unicast_addr,(uint8_t *)&unicast_addr,sizeof(uint16_t));
     ind_len = sprintf(ind_msg,"\r\n+Unicast_address:%s\r\n",at_unicast_addr);
     uart_write((uint8_t *)ind_msg,ind_len);
     
     hex_arr_to_str(at_model_app_status,(uint8_t *)&model_app_status,sizeof(uint8_t));
     ind_len = sprintf(ind_msg,"+Model_App_status:%s\r\n",at_model_app_status);
     uart_write((uint8_t *)ind_msg,ind_len);

     hex_arr_to_str(at_element_addr,(uint8_t *)&element_addr,sizeof(uint16_t));
     ind_len = sprintf(ind_msg,"+Element_Addr:%s\r\n",at_element_addr);
     uart_write((uint8_t *)ind_msg,ind_len);

     hex_arr_to_str(at_publish_addr,(uint8_t *)&publish_addr,sizeof(uint16_t));
     ind_len = sprintf(ind_msg,"+Publish_Addr:%s\r\n",at_publish_addr);
     uart_write((uint8_t *)ind_msg,ind_len);

     hex_arr_to_str(at_model_id,(uint8_t *)&model_id,sizeof(uint32_t));
     ind_len = sprintf(ind_msg,"+Model_id:%s\r\n",at_model_id);
     uart_write((uint8_t *)ind_msg,ind_len);

     hex_arr_to_str(at_app_key_id,(uint8_t *)&app_key_id,sizeof(uint16_t));
     ind_len = sprintf(ind_msg,"+App_Key_ID:%s\r\n",at_app_key_id);
     uart_write((uint8_t *)ind_msg,ind_len);
     
     hex_arr_to_str(at_cred_flag,(uint8_t *)&cred_flag,sizeof(uint8_t));
     ind_len = sprintf(ind_msg,"+Cred_Flag:%s\r\n",at_cred_flag);
     uart_write((uint8_t *)ind_msg,ind_len);

     hex_arr_to_str(at_publish_ttl,(uint8_t *)&publish_ttl,sizeof(uint8_t));
     ind_len = sprintf(ind_msg,"+Publish_TTL:%s\r\n",at_publish_ttl);
     uart_write((uint8_t *)ind_msg,ind_len);

     hex_arr_to_str(at_publish_period_ms,(uint8_t *)&publish_period_ms,sizeof(uint32_t));
     ind_len = sprintf(ind_msg,"+Publish_Period_ms:%s\r\n",at_publish_period_ms);
     uart_write((uint8_t *)ind_msg,ind_len);

     hex_arr_to_str(at_publish_retx_cont,(uint8_t *)&publish_retx_cont,sizeof(uint8_t));
     ind_len = sprintf(ind_msg,"+Publish_Retx_Cont:%s\r\n",at_publish_retx_cont);
     uart_write((uint8_t *)ind_msg,ind_len);

     hex_arr_to_str(at_publish_retx_intv_step_solution,(uint8_t *)&publish_retx_intv_step_solution,sizeof(uint8_t));
     ind_len = sprintf(ind_msg,"+Publish_Retx_Intv_Step_Solution:%s\r\n",at_publish_retx_intv_step_solution);
     uart_write((uint8_t *)ind_msg,ind_len);

}

void at_prover_report_node_info(uint16_t unicast_addr,uint16_t net_key_lid,uint16_t dev_key_lid)
{
    uint8_t ind_len=0;
    char ind_msg[100]={0};
    uint8_t at_unicast_addr[sizeof(uint16_t)*2+1]={0};
    uint8_t at_net_key_lid[sizeof(uint16_t)*2+1]={0};
    uint8_t at_dev_key_lid[sizeof(uint16_t)*2+1]={0};

    hex_arr_to_str(at_unicast_addr,(uint8_t *)&unicast_addr,sizeof(uint16_t));
    ind_len = sprintf(ind_msg,"\r\n+Unicast_address:%s\r\n",at_unicast_addr);
    uart_write((uint8_t *)ind_msg,ind_len);

    hex_arr_to_str(at_net_key_lid,(uint8_t *)&net_key_lid,sizeof(uint16_t));
    ind_len = sprintf(ind_msg,"\r\n+net_key_lid:%s\r\n",at_net_key_lid);
    uart_write((uint8_t *)ind_msg,ind_len);

    hex_arr_to_str(at_dev_key_lid,(uint8_t *)&dev_key_lid,sizeof(uint16_t));
    ind_len = sprintf(ind_msg,"\r\n+dev_key_lid:%s\r\n",at_dev_key_lid);
    uart_write((uint8_t *)ind_msg,ind_len);
}


void at_prover_report_iv_seq_info(uint32_t prover_iv,uint32_t prover_seq)
{
    uint8_t ind_len=0;
    char ind_msg[100]={0};
    uint8_t at_prover_prim_iv[sizeof(uint32_t)*2+1]={0};
    uint8_t at_prover_prim_seq[sizeof(uint32_t)*2+1]={0};

    hex_arr_to_str(at_prover_prim_iv,(uint8_t *)&prover_iv,sizeof(uint32_t));
    ind_len = sprintf(ind_msg,"\r\n+Prover_iv:%s\r\n",at_prover_prim_iv);
    uart_write((uint8_t *)ind_msg,ind_len);

    hex_arr_to_str(at_prover_prim_seq,(uint8_t *)&prover_seq,sizeof(uint32_t));
    ind_len = sprintf(ind_msg,"\r\n+Prover_seq:%s\r\n",at_prover_prim_seq);
    uart_write((uint8_t *)ind_msg,ind_len);
}
