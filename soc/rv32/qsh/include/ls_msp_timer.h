#ifndef LS_MSP_TIMER_H_
#define LS_MSP_TIMER_H_
#include "reg_base_addr.h"
#include "reg_timer_type.h"

#ifdef __cplusplus
extern "C" {
#endif

// LSTIMER Macro for Register Access
#ifdef APP_BSTIM1_ADDR
#define LSBSTIM ((reg_timer_t *)APP_BSTIM1_ADDR)
#endif
#ifdef APP_BSTIM2_ADDR
#define LSBSTIM2 ((reg_timer_t *)APP_BSTIM2_ADDR)
#endif

#ifdef APP_GPTIMA1_ADDR
#define LSGPTIMA ((reg_timer_t *)APP_GPTIMA1_ADDR)
#endif
#ifdef APP_GPTIMA2_ADDR
#define LSGPTIMA2 ((reg_timer_t *)APP_GPTIMA2_ADDR)
#endif
#ifdef APP_GPTIMB1_ADDR
#define LSGPTIMB ((reg_timer_t *)APP_GPTIMB1_ADDR)
#endif
#ifdef APP_GPTIMC1_ADDR
#define LSGPTIMC ((reg_timer_t *)APP_GPTIMC1_ADDR)
#endif

#define IS_TIM_ADVANCED_INSTANCE(INSTANCE) (1)

#define IS_TIM_CC1_INSTANCE(INSTANCE) (1)

#define IS_TIM_CC2_INSTANCE(INSTANCE) (1)

#define IS_TIM_CC3_INSTANCE(INSTANCE) (1)

#define IS_TIM_CC4_INSTANCE(INSTANCE) (1)

#define  IS_TIM_CLOCKSOURCE_ETRMODE1_INSTANCE(INSTANCE) (1)

#define IS_TIM_CLOCKSOURCE_ETRMODE2_INSTANCE(INSTANCE) (1)

#define IS_TIM_CLOCKSOURCE_TIX_INSTANCE(INSTANCE) (1)

#define IS_TIM_CLOCKSOURCE_ITRX_INSTANCE(INSTANCE) (1)

#define IS_TIM_OCXREF_CLEAR_INSTANCE(INSTANCE) (1)

#define IS_TIM_ENCODER_INTERFACE_INSTANCE(INSTANCE) (1)

#define IS_TIM_XOR_INSTANCE(INSTANCE) (1)

#define IS_TIM_SLAVE_INSTANCE(INSTANCE) (1)

#define IS_TIM_SYNCHRO_INSTANCE(INSTANCE) (1)

#define IS_TIM_BREAK_INSTANCE(INSTANCE) (1)

#define IS_TIM_CCX_INSTANCE(INSTANCE, CHANNEL)  (1)

#define IS_TIM_CCXN_INSTANCE(INSTANCE, CHANNEL)  (1)

#define IS_TIM_COUNTER_MODE_SELECT_INSTANCE(INSTANCE) (1)

#define IS_TIM_REPETITION_COUNTER_INSTANCE(INSTANCE) (1)

#define IS_TIM_CLOCK_DIVISION_INSTANCE(INSTANCE) (1)

#define IS_TIM_COMMUTATION_EVENT_INSTANCE(INSTANCE) (1)

#define IS_TIM_ETR_INSTANCE(INSTANCE) (1)

#define IS_TIM_HALL_SENSOR_INTERFACE_INSTANCE(INSTANCE) (1)

#define IS_TIM_32B_COUNTER_INSTANCE(INSTANCE) (1)

struct __TIM_HandleTypeDef;
void HAL_TIM_MSP_Init(struct __TIM_HandleTypeDef *inst);
void HAL_TIM_MSP_DeInit(struct __TIM_HandleTypeDef *inst);
void HAL_TIM_MSP_Busy_Set(struct __TIM_HandleTypeDef *inst);
void HAL_TIM_MSP_Idle_Set(struct __TIM_HandleTypeDef *inst);

#ifdef __cplusplus
}
#endif

#endif