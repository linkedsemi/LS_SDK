#ifndef LS_MSP_COMP_H_
#define LS_MSP_COMP_H_
#include "reg_comp_type.h"
#include "reg_v33_rg_type.h"

#define LSCOMP1 ((reg_comp_t *)&V33_RG->COMP1_CTRL)
#define LSCOMP2 ((reg_comp_t *)&V33_RG->COMP2_CTRL)
#define LSCOMP3 ((reg_comp_t *)&V33_RG->COMP3_CTRL)

struct __COMP_HandleTypeDef;
void HAL_COMP_MSP_Init(struct __COMP_HandleTypeDef *inst);

void HAL_COMP_MSP_DeInit(void);

#endif