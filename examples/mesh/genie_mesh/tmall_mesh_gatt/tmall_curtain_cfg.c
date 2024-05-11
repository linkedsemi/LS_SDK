#include "tmall_curtain_cfg.h"
#include "ls_soc_gpio.h"
#include "ls_ble.h"
#include "platform.h"
#include "ls_sig_mesh.h"
#include "tmall_mesh_ctl.h"
#include "log.h"
//#include "user_event.h"

extern struct mesh_model_info model_env;
extern uint16_t provisioner_unicast_addr;
extern uint16_t gatt_mesh_src_addr;
uint32_t   hall1_cnt = 0;
uint32_t   hall2_cnt = 0;
uint32_t   hall1_trip_cnt = 0;
uint32_t   hall2_trip_cnt = 0;
uint8_t    tmall_cuatain_percentage_flag=0;

struct curtain_state tmall_cuatain_state;
struct curtain_study_group tmall_cuatain_study;

uint8_t   current_tid = 0x80;

void curtain_control_forward(void)
{
   hall1_cnt = 0;
   hall2_cnt = 0;
   io_write_pin(M1H,0);
   io_write_pin(M1L,0); 
   io_write_pin(M2H,1); 
   io_write_pin(M2L,1); 
   tmall_cuatain_state.motor_state = 1;
   if(tmall_cuatain_state.direction == 1 )
   {
      tmall_cuatain_state.onoff_state = 1;  
   }
   else if(tmall_cuatain_state.direction == 0 )
   {
      tmall_cuatain_state.onoff_state = 0;
   }
}

void curtain_control_backward(void)
{
   hall1_cnt = 0;
   hall2_cnt = 0;
   io_write_pin(M1H,1);
   io_write_pin(M1L,1); 
   io_write_pin(M2H,0); 
   io_write_pin(M2L,0); 
   tmall_cuatain_state.motor_state = 1;
   if(tmall_cuatain_state.direction == 1 )
   {
      tmall_cuatain_state.onoff_state = 0;  
   }
   else if(tmall_cuatain_state.direction == 0 )
   {
      tmall_cuatain_state.onoff_state = 1;
   }
}


void curtain_control_on(void)
{
    tmall_cuatain_state.onoff_state = 1;
    tmall_cuatain_state.motor_state = 1;
    hall1_cnt = 0;
    hall2_cnt = 0;
    if(tmall_cuatain_state.direction == 0)//正向
    {
      io_write_pin(M1H,1);
      io_write_pin(M1L,1); 
      io_write_pin(M2H,0); 
      io_write_pin(M2L,0); 
    }
   else if(tmall_cuatain_state.direction == 1 ) //反向
   {
      io_write_pin(M1H,0);
      io_write_pin(M1L,0); 
      io_write_pin(M2H,1); 
      io_write_pin(M2L,1); 
   }
}

void curtain_control_stop(void)
{
   hall1_cnt = 0;
   hall2_cnt = 0;
   io_write_pin(M1H,1);
   io_write_pin(M1L,0); 
   io_write_pin(M2H,1); 
   io_write_pin(M2L,0);  
   tmall_cuatain_state.motor_state = 0;
}

void curtain_control_off(void)
{
   tmall_cuatain_state.onoff_state = 0;
   tmall_cuatain_state.motor_state = 1;
   hall1_cnt = 0;
   hall2_cnt = 0;
    if(tmall_cuatain_state.direction == 1)//反向
    {
      io_write_pin(M1H,1);
      io_write_pin(M1L,1); 
      io_write_pin(M2H,0); 
      io_write_pin(M2L,0); 
    }
   else if(tmall_cuatain_state.direction == 0 ) //正向
   {
      io_write_pin(M1H,0);
      io_write_pin(M1L,0); 
      io_write_pin(M2H,1); 
      io_write_pin(M2L,1); 
   }
}


void tmall_curtain_set_onoff(uint8_t on_off)
{
    LOG_I("tmall_curtain_set_onoff:%x",on_off);  
   if(on_off == 0x00)
   {
      curtain_control_off();
      LOG_I("tmall_curtain_set_off");
   }
   else if(on_off == 0x01)
   {
      curtain_control_on();
      LOG_I("tmall_curtain_set_on");
   }
   else if(on_off == 0x02)
   {
      tmall_cuatain_state.onoff_state = 2;  
      curtain_control_stop();
      LOG_I("tmall_curtain_set_stop");
   }
}

uint8_t tmall_curtain_get_onoff(void)
{
    return tmall_cuatain_state.onoff_state;
}



//PA13---M1
//PB06 ---M2

//PA14--M3
//PB05 --M4
//M1,M2    M3,M4
//关机--M1=H,M2=L   M3=H,M4=L
//正向--M1=H,M2=H  M3=L,M4=L
//反向--M1=M2=L,M3=M4=H;
//PA00  --HELL1
//PB15 ---HELL2
//PB11---KEY
//PA01----LED   H--ON
void tmall_curtain_init(void)
{
    //增加窗帘部分IO的初始化
     io_cfg_output(M1H);
     io_write_pin(M1H,1);
     io_cfg_output(M1L);
     io_write_pin(M1L,0); 
     io_cfg_output(M2H);
     io_write_pin(M2H,1); 
     io_cfg_output(M2L);
     io_write_pin(M2L,0); 

     io_cfg_input(KEY);
     io_pull_write(KEY,IO_PULL_UP);
     
     io_cfg_input(HALL1);
     io_pull_write(HALL1,IO_PULL_UP);
     io_exti_config(HALL1,INT_EDGE_FALLING);

     io_cfg_input(HALL2);
     io_pull_write(HALL2,IO_PULL_UP);
     io_exti_config(HALL2,INT_EDGE_FALLING);

     io_cfg_output(LED);
     io_write_pin(LED,0);
}



void io_exti_callback(uint8_t pin,exti_edge_t edge) 
{
    switch (pin)
    {
      case HALL1:
         hall1_cnt++;
         hall1_trip_cnt++;
         break;
      case HALL2:
         hall2_cnt++;
         hall2_trip_cnt++;
         break;    
      default:
         break;
    }
}

//窗帘属性上报接口
//report_type :   上报的attr——type   
//report_value ： 上报属性值
void  app_generic_percent_status_report(uint16_t report_type,uint8_t report_value)
{
      struct  model_send_info   percent_rsp;
      
      percent_rsp.ModelHandle = model_env.info[1].model_lid;
      percent_rsp.app_key_lid = model_env.app_key_lid;
      percent_rsp.opcode = APP_MESH_VENDOR_INDICATION;
      percent_rsp.dest_addr = ((gatt_mesh_src_addr!=0xffff)?gatt_mesh_src_addr:provisioner_unicast_addr);

      percent_rsp.len = 4;
      if(current_tid >= 0xbf)  current_tid = 0x80;
      percent_rsp.info[0] = current_tid++;
      
      percent_rsp.info[1] = (uint8_t)(report_type & 0x00ff);
      percent_rsp.info[2] =  0;//((report_type & 0xff00) << 8 );
      percent_rsp.info[3] =  report_value;
      
      model_send_info_handler(&percent_rsp);
}

