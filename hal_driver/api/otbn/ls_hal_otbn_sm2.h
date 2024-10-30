#ifndef LS_HAL_OTBN_SM2_H_
#define LS_HAL_OTBN_SM2_H_
#include "ls_hal_otbn.h"
#ifdef __cplusplus
extern "C" {
#endif

struct HAL_OTBN_SM2_Verify_Param
{
    uint32_t *msg;
    uint32_t *r;
    uint32_t *s;
    uint32_t *x;
    uint32_t *y;
};

struct HAL_OTBN_SM2_ScalarMult_Param
{
    uint32_t *scalar;
    uint32_t *point_x;
    uint32_t *point_y;
    uint32_t *result_x;
    uint32_t *result_y;
};

void HAL_OTBN_SM2_ScalarMult();

void HAL_OTBN_SM2_Verify_CallBack(bool result);
void HAL_OTBN_SM2_Verify_IT(struct HAL_OTBN_SM2_Verify_Param *param);
bool HAL_OTBN_SM2_Verify_Polling(struct HAL_OTBN_SM2_Verify_Param *param);

void HAL_OTBN_SM2_ValidPoint_CallBack(bool result);
void HAL_OTBN_SM2_ValidPoint_IT(uint32_t *x, uint32_t *y);
bool HAL_OTBN_SM2_ValidPoint_Polling(uint8_t *x, uint8_t *y);

void HAL_OTBN_SM2_ScalarMult_CallBack();
void HAL_OTBN_SM2_ScalarMult_IT(struct HAL_OTBN_SM2_ScalarMult_Param *param);


#ifdef __cplusplus
}
#endif
#endif