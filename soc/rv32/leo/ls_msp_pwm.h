#ifndef LS_MSP_PWM_H_
#define LS_MSP_PWM_H_
#include "reg_base_addr.h"
#include "reg_pwm_type.h"
#ifdef __cplusplus
extern "C"{
#endif

#ifdef PWM_BASE_ADDR
#define PWM ((reg_pwm_t *) PWM_BASE_ADDR)
#endif

void HAL_PWM_MSP_Init(void);

void HAL_PWM_MSP_DeInit(void);

#ifdef __cplusplus
}
#endif
#endif