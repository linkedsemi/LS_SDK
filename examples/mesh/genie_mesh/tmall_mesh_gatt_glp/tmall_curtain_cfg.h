#ifndef TMALL_CURTAIN_CFG_H_
#define TMALL_CURTAIN_CFG_H_

#include "ls_hal_timer.h"
#include "le501x.h"
#include "platform.h"
#include "reg_rcc.h"
#include "field_manipulate.h"

#include <string.h>

//PA13---M1
//PB06 ---M2

//PA14--M3
//PB05 --M4
//M1,M2    M3,M4
//关机--M1=H,M2=L   M3=H,M4=L
//正向--M1=H,M2=H  M3=L,M4=L
//反向--M1=M2=L,M3=M4=H;
//PA00  --HALL1
//PB15 ---HALL2
//PB11---KEY
//PA01----LED   H--ON

#define   LED     PA01
#define   KEY     PB11
#define   HALL1   PA00
#define   HALL2   PB15
#define   M1H     PA13 //M1
#define   M1L     PB06 //M2
#define   M2H     PA14 //M3
#define   M2L     PB05 //M4





extern uint32_t   hall1_cnt;
extern uint32_t   hall2_cnt;
extern uint32_t   hall1_trip_cnt;
extern uint32_t   hall2_trip_cnt;



struct curtain_state
{
    uint8_t onoff_state;   //0，关机状态；1，开机状态，2，暂停状态
    uint8_t  motor_state;  //电机状态，0，停止，1：运行
    uint16_t level;
    uint8_t  direction;
};

struct curtain_study_group
{
    uint8_t study_state_flag;
    uint32_t hall1_study_value;
    uint32_t hall1_set_value;
    uint32_t hall1_before_value;
    uint32_t hall2_study_value;
    uint32_t hall2_set_value;
    uint32_t hall2_before_value;
};

extern uint8_t    tmall_cuatain_percentage_flag;
extern struct curtain_state tmall_cuatain_state;
extern struct curtain_study_group tmall_cuatain_study;

extern void tmall_curtain_init(void);
extern void tmall_curtain_set_onoff(uint8_t on_off);
extern uint8_t tmall_curtain_get_onoff(void);
extern void  app_generic_percent_status_report(uint16_t report_type,uint8_t report_value);
extern void curtain_control_off(void);
extern void curtain_control_on(void);
extern void curtain_control_stop(void);
extern void curtain_control_forward(void);
extern void curtain_control_backward(void);
#endif
