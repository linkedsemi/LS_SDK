#ifndef LS_MSP_TIMER_H_
#define LS_MSP_TIMER_H_
#include "reg_base_addr.h"
#include "reg_timer_type.h"

/// LSTIMER Macro for Register Access
#ifdef LSBSTIM_BASE_ADDR
#define LSBSTIM ((reg_timer_t *)LSBSTIM_BASE_ADDR)
#endif
#ifdef LSGPTIMA_BASE_ADDR
#define LSGPTIMA ((reg_timer_t *)LSGPTIMA_BASE_ADDR)
#endif
#ifdef LSGPTIMB_BASE_ADDR
#define LSGPTIMB ((reg_timer_t *)LSGPTIMB_BASE_ADDR)
#endif
#ifdef LSGPTIMC_BASE_ADDR
#define LSGPTIMC ((reg_timer_t *)LSGPTIMC_BASE_ADDR)
#endif
#ifdef LSADTIM1_BASE_ADDR
#define LSADTIM1 ((reg_timer_t *)LSADTIM1_BASE_ADDR)
#endif
#ifdef LSADTIM2_BASE_ADDR
#define LSADTIM2 ((reg_timer_t *)LSADTIM2_BASE_ADDR)
#endif


#define IS_TIM_ADVANCED_INSTANCE(INSTANCE) ((INSTANCE) == LSADTIM1)||((INSTANCE) == LSADTIM2)

#define IS_TIM_CC1_INSTANCE(INSTANCE) \
  (((INSTANCE) == LSADTIM1) ||        \
   ((INSTANCE) == LSADTIM2) ||        \
   ((INSTANCE) == LSGPTIMC) ||        \
   ((INSTANCE) == LSGPTIMA) ||        \
   ((INSTANCE) == LSGPTIMB))

#define IS_TIM_CC2_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM1) ||        \
   ((INSTANCE) == LSADTIM2) ||        \
   ((INSTANCE) == LSGPTIMC) ||        \
   ((INSTANCE) == LSGPTIMA) ||        \
   ((INSTANCE) == LSGPTIMB))

#define IS_TIM_CC3_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM1) ||        \
   ((INSTANCE) == LSADTIM2) ||        \
   ((INSTANCE) == LSGPTIMC) ||        \
   ((INSTANCE) == LSGPTIMA) ||        \
   ((INSTANCE) == LSGPTIMB))

#define IS_TIM_CC4_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM1) ||        \
   ((INSTANCE) == LSADTIM2) ||        \
   ((INSTANCE) == LSGPTIMC) ||        \
   ((INSTANCE) == LSGPTIMA) ||        \
   ((INSTANCE) == LSGPTIMB))

#define  IS_TIM_CLOCKSOURCE_ETRMODE1_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM1) ||        \
   ((INSTANCE) == LSADTIM2) ||        \
   ((INSTANCE) == LSGPTIMC) ||        \
   ((INSTANCE) == LSGPTIMA) ||        \
   ((INSTANCE) == LSGPTIMB))

#define IS_TIM_CLOCKSOURCE_ETRMODE2_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM1) ||        \
   ((INSTANCE) == LSADTIM2) ||        \
   ((INSTANCE) == LSGPTIMC) ||        \
   ((INSTANCE) == LSGPTIMA) ||        \
   ((INSTANCE) == LSGPTIMB))

#define IS_TIM_CLOCKSOURCE_TIX_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM1)    || \
   ((INSTANCE) == LSADTIM2)    || \
   ((INSTANCE) == LSGPTIMC)    || \
   ((INSTANCE) == LSGPTIMA)    || \
   ((INSTANCE) == LSGPTIMB))

#define IS_TIM_CLOCKSOURCE_ITRX_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM1)    || \
   ((INSTANCE) == LSADTIM2)    || \
   ((INSTANCE) == LSGPTIMC)    || \
   ((INSTANCE) == LSGPTIMA)    || \
   ((INSTANCE) == LSGPTIMB))

#define IS_TIM_OCXREF_CLEAR_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM1) ||        \
   ((INSTANCE) == LSADTIM2) ||        \
   ((INSTANCE) == LSGPTIMC) ||        \
   ((INSTANCE) == LSGPTIMA) ||        \
   ((INSTANCE) == LSGPTIMB))

#define IS_TIM_ENCODER_INTERFACE_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM1) ||        \
   ((INSTANCE) == LSADTIM2) ||        \
   ((INSTANCE) == LSGPTIMC) ||        \
   ((INSTANCE) == LSGPTIMA) ||        \
   ((INSTANCE) == LSGPTIMB))

#define IS_TIM_XOR_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM1) ||        \
   ((INSTANCE) == LSADTIM2) ||        \
   ((INSTANCE) == LSGPTIMC) ||        \
   ((INSTANCE) == LSGPTIMA) ||        \
   ((INSTANCE) == LSGPTIMB))

#define IS_TIM_SLAVE_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM1)    || \
   ((INSTANCE) == LSADTIM2)    || \
   ((INSTANCE) == LSGPTIMC)    || \
   ((INSTANCE) == LSGPTIMA)    || \
   ((INSTANCE) == LSGPTIMB))

#define IS_TIM_SYNCHRO_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM1)    || \
   ((INSTANCE) == LSADTIM2)    || \
   ((INSTANCE) == LSGPTIMC)    || \
   ((INSTANCE) == LSGPTIMA)    || \
   ((INSTANCE) == LSGPTIMB))

#define IS_TIM_BREAK_INSTANCE(INSTANCE) \
  (((INSTANCE) == LSADTIM1) ||          \
   ((INSTANCE) == LSADTIM2) ||          \
   ((INSTANCE) == LSGPTIMC))

#define IS_TIM_CCX_INSTANCE(INSTANCE, CHANNEL) \
   ((((INSTANCE) == LSADTIM1) &&                  \
     (((CHANNEL) == TIM_CHANNEL_1) ||          \
      ((CHANNEL) == TIM_CHANNEL_2) ||          \
      ((CHANNEL) == TIM_CHANNEL_3) ||          \
      ((CHANNEL) == TIM_CHANNEL_4)))           \
    ||                                         \
    (((INSTANCE) == LSADTIM2) &&                  \
     (((CHANNEL) == TIM_CHANNEL_1) ||          \
      ((CHANNEL) == TIM_CHANNEL_2) ||          \
      ((CHANNEL) == TIM_CHANNEL_3) ||          \
      ((CHANNEL) == TIM_CHANNEL_4)))           \
    ||                                         \
    (((INSTANCE) == LSGPTIMC) &&                   \
     (((CHANNEL) == TIM_CHANNEL_1) ||          \
      ((CHANNEL) == TIM_CHANNEL_2)))           \
    ||                                         \
    (((INSTANCE) == LSGPTIMA) &&                   \
     (((CHANNEL) == TIM_CHANNEL_1) ||          \
      ((CHANNEL) == TIM_CHANNEL_2) ||          \
      ((CHANNEL) == TIM_CHANNEL_3) ||          \
      ((CHANNEL) == TIM_CHANNEL_4)))           \
    ||                                         \
    (((INSTANCE) == LSGPTIMB) &&                   \
     (((CHANNEL) == TIM_CHANNEL_1) ||          \
      ((CHANNEL) == TIM_CHANNEL_2) ||          \
      ((CHANNEL) == TIM_CHANNEL_3) ||          \
      ((CHANNEL) == TIM_CHANNEL_4))))

#define IS_TIM_CCXN_INSTANCE(INSTANCE, CHANNEL) \
   ((((INSTANCE) == LSADTIM1) &&                    \
     (((CHANNEL) == TIM_CHANNEL_1) ||           \
      ((CHANNEL) == TIM_CHANNEL_2) ||           \
      ((CHANNEL) == TIM_CHANNEL_3)))            \
    ||                                          \
    (((INSTANCE) == LSADTIM2) &&                    \
     (((CHANNEL) == TIM_CHANNEL_1) ||           \
      ((CHANNEL) == TIM_CHANNEL_2) ||           \
      ((CHANNEL) == TIM_CHANNEL_3)))            \
    ||                                          \
    (((INSTANCE) == LSGPTIMC) &&                   \
      ((CHANNEL) == TIM_CHANNEL_1)))

#define IS_TIM_COUNTER_MODE_SELECT_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM1)    || \
   ((INSTANCE) == LSADTIM2)    || \
   ((INSTANCE) == LSGPTIMC)    || \
   ((INSTANCE) == LSGPTIMA)    || \
   ((INSTANCE) == LSGPTIMB))

#define IS_TIM_REPETITION_COUNTER_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM1)    || \
   ((INSTANCE) == LSADTIM2)    || \
   ((INSTANCE) == LSGPTIMC))

#define IS_TIM_CLOCK_DIVISION_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM1)    || \
   ((INSTANCE) == LSADTIM2)    || \
   ((INSTANCE) == LSGPTIMC)    || \
   ((INSTANCE) == LSGPTIMA)    || \
   ((INSTANCE) == LSGPTIMB))
    
#define IS_TIM_COMMUTATION_EVENT_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM1)    || \
   ((INSTANCE) == LSADTIM2)    || \
   ((INSTANCE) == LSGPTIMC))

#define IS_TIM_ETR_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM1)    || \
   ((INSTANCE) == LSADTIM2)    || \
   ((INSTANCE) == LSGPTIMC)    || \
   ((INSTANCE) == LSGPTIMA)    || \
   ((INSTANCE) == LSGPTIMB))

#define IS_TIM_HALL_SENSOR_INTERFACE_INSTANCE(INSTANCE)\
  (((INSTANCE) == LSADTIM1) ||        \
   ((INSTANCE) == LSADTIM2) ||        \
   ((INSTANCE) == LSGPTIMC) ||        \
   ((INSTANCE) == LSGPTIMA) ||        \
   ((INSTANCE) == LSGPTIMB))

#define IS_TIM_32B_COUNTER_INSTANCE(INSTANCE)    ((INSTANCE) == LSGPTIMA)

struct __TIM_HandleTypeDef;
void HAL_TIM_MSP_Init(struct __TIM_HandleTypeDef *inst);
void HAL_TIM_MSP_DeInit(struct __TIM_HandleTypeDef *inst);
void HAL_TIM_MSP_Busy_Set(struct __TIM_HandleTypeDef *inst);
void HAL_TIM_MSP_Idle_Set(struct __TIM_HandleTypeDef *inst);

#endif
