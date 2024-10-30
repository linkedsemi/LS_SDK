#include "ls_hal_otbn_sm2.h"

#define SM2_FUNC_VALIDPOINT     (0x10)
#define SM2_FUNC_SCALARMULT     (0x20)
#define SM2_FUNC_VERIFY         (0x30)

#define SM2_DMEM_CURVE_P_OFFSET     (0x0)
#define SM2_DMEM_CURVE_P_SIZE           (0xe0)
#define SM2_DMEM_K0_OFFSET          (0xe0)
#define SM2_DMEM_K0_SIZE                (0x40)
#define SM2_DMEM_K1_OFFSET          (0x120)
#define SM2_DMEM_K2_SIZE                (0x40)
#define SM2_DMEM_MSG_OFFSET         (0x160)
#define SM2_DMEM_MSG_SIZE               (0x20)
#define SM2_DMEM_R_OFFSET           (0x180)
#define SM2_DMEM_R_SIZE                 (0x20)
#define SM2_DMEM_S_OFFSET           (0x1a0)
#define SM2_DMEM_S_SIZE                 (0x20)
#define SM2_DMEM_X_OFFSET           (0x1c0)
#define SM2_DMEM_X_SIZE                 (0x20)
#define SM2_DMEM_Y_OFFSET           (0x1e0)
#define SM2_DMEM_Y_SIZE                 (0x20)
#define SM2_DMEM_X_R_OFFSET         (0x200)
#define SM2_DMEM_X_R_SIZE               (0x20)
#define SM2_DMEM_RESULT_X_OFFSET    (0x220)
#define SM2_DMEM_RESULT_X_SIZE          (0x40)
#define SM2_DMEM_RESULT_Y_OFFSET    (0x260)
#define SM2_DMEM_RESULT_Y_SIZE          (0x40)
#define SM2_DMEM_FUNC_OFFSET        (0x2a0)
#define SM2_DMEM_FUNC_SIZE              (0x20)
#define SM2_DMEM_DZERO_OFFSET       (0x2c0)
#define SM2_DMEM_DZERO_SIZE             (0x20)
#define SM2_DMEM_PROJ_SG_OFFSET     (0x2e0)
#define SM2_DMEM_PROJ_SG_SIZE           (0x60)
#define SM2_DMEM_BSS_START          (0x2e0)
#define SM2_DMEM_BSS_END            (0x340)
#define SM2_DMEM_BSS_SIZE               (0x60)

extern const char sm2_text[1924];

struct OTBN_SM2_CURVE {
    const uint32_t b[8];
    const uint32_t p[8];
    const uint32_t u_p[8];
    const uint32_t n[8];
    const uint32_t u_n[8];
    const uint32_t Gx[8];
    const uint32_t Gy[8];
};

/****************
 *  Curve SM2 
 * 
 * *****************/
const static struct OTBN_SM2_CURVE SM2 = {
    .b =    {0x4D940E93, 0xDDBCBD41, 0x15AB8F92, 0xF39789F5, 0xCF6509A7, 0x4D5A9E4B, 0x9D9F5E34, 0x28E9FA9E},
    .p =    {0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFE},
    .u_p =  {0x00000003, 0x00000002, 0x00000002, 0x00000002, 0x00000001, 0x00000001, 0x00000001, 0x00000001},
    .n =    {0x39D54123, 0x53BBF409, 0x21C6052B, 0x7203DF6B, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFE},
    .u_n =  {0xf15149a0, 0x12ac6361, 0xfa323c01, 0x8dfc2096, 0x00000001, 0x00000001, 0x00000001, 0x00000001},
    .Gx =   {0x334C74C7, 0x715A4589, 0xF2660BE1, 0x8FE30BBF, 0x6A39C994, 0x5F990446, 0x1F198119, 0x32C4AE2C},
    .Gy =   {0x2139F0A0, 0x02DF32E5, 0xC62A4740, 0xD0A9877C, 0x6B692153, 0x59BDCEE3, 0xF4F6779C, 0xBC3736A2},
};

bool HAL_OTBN_SM2_Verify_Polling(struct HAL_OTBN_SM2_Verify_Param *param)
{
    uint32_t func = SM2_FUNC_VERIFY;
    HAL_OTBN_IMEM_Write(0, (uint32_t *)sm2_text, sizeof(sm2_text));
    HAL_OTBN_DMEM_Set(0, 0, SM2_DMEM_BSS_END);
    HAL_OTBN_DMEM_Write(SM2_DMEM_CURVE_P_OFFSET, (uint32_t *)&SM2, SM2_DMEM_CURVE_P_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_MSG_OFFSET, param->msg, SM2_DMEM_MSG_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_R_OFFSET, param->r, SM2_DMEM_R_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_S_OFFSET, param->s, SM2_DMEM_S_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_X_OFFSET, param->x, SM2_DMEM_X_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_Y_OFFSET, param->y, SM2_DMEM_Y_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_FUNC_OFFSET, &func, sizeof(uint32_t));
    
    HAL_OTBN_CMD_Write_Polling(HAL_OTBN_CMD_EXECUTE);
    
    uint8_t x_r[SM2_DMEM_X_R_SIZE];
    HAL_OTBN_DMEM_Read(SM2_DMEM_X_R_OFFSET, (uint32_t *)x_r, SM2_DMEM_X_R_SIZE);
    return !memcmp(param->r, x_r, SM2_DMEM_X_R_SIZE);
}

bool HAL_OTBN_SM2_ValidPoint_Polling(uint8_t *x, uint8_t *y)
{
    uint32_t data = SM2_FUNC_VALIDPOINT;
    HAL_OTBN_IMEM_Write(0, (uint32_t *)sm2_text, sizeof(sm2_text));
    HAL_OTBN_DMEM_Set(0, 0, SM2_DMEM_BSS_END);
    HAL_OTBN_DMEM_Write(SM2_DMEM_CURVE_P_OFFSET, (uint32_t *)&SM2, SM2_DMEM_CURVE_P_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_X_OFFSET, (uint32_t *)x, SM2_DMEM_X_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_Y_OFFSET, (uint32_t *)y, SM2_DMEM_Y_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_FUNC_OFFSET, &data, sizeof(uint32_t));
    
    HAL_OTBN_CMD_Write_Polling(HAL_OTBN_CMD_EXECUTE);
    
    HAL_OTBN_DMEM_Read(SM2_DMEM_X_R_OFFSET, &data, sizeof(uint32_t));
    return data;
}

__attribute__((weak)) void HAL_OTBN_SM2_ScalarMult_CallBack() {}
__attribute__((weak)) void HAL_OTBN_SM2_Verify_CallBack(bool result) {}
__attribute__((weak)) void HAL_OTBN_SM2_ValidPoint_CallBack(bool result) {}

void SM2_Verify_Cb(void *param)
{
    uint8_t x_r[SM2_DMEM_X_R_SIZE];
    struct HAL_OTBN_SM2_Verify_Param *p = param;
   
    HAL_OTBN_DMEM_Read(SM2_DMEM_X_R_OFFSET, (uint32_t *)x_r, SM2_DMEM_X_R_SIZE);
    HAL_OTBN_SM2_Verify_CallBack(!memcmp(p->r, x_r, SM2_DMEM_X_R_SIZE));
}

void HAL_OTBN_SM2_Verify_IT(struct HAL_OTBN_SM2_Verify_Param *param)
{
    uint32_t func = SM2_FUNC_VERIFY;
    HAL_OTBN_IMEM_Write(0, (uint32_t *)sm2_text, sizeof(sm2_text));
    HAL_OTBN_DMEM_Set(0, 0, SM2_DMEM_BSS_END);
    HAL_OTBN_DMEM_Write(SM2_DMEM_CURVE_P_OFFSET, (uint32_t *)&SM2, SM2_DMEM_CURVE_P_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_MSG_OFFSET, param->msg, SM2_DMEM_MSG_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_R_OFFSET, param->r, SM2_DMEM_R_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_S_OFFSET, param->s, SM2_DMEM_S_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_X_OFFSET, param->x, SM2_DMEM_X_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_Y_OFFSET, param->y, SM2_DMEM_Y_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_FUNC_OFFSET, &func, sizeof(uint32_t));
    
    HAL_OTBN_CMD_Write_IT(HAL_OTBN_CMD_EXECUTE, SM2_Verify_Cb, param);
}

void SM2_ValidPoint_Cb(void *param)
{
    uint32_t data = 0;
    HAL_OTBN_DMEM_Read(SM2_DMEM_X_R_OFFSET, &data, sizeof(uint32_t));
    HAL_OTBN_SM2_ValidPoint_CallBack(data);
}

void HAL_OTBN_SM2_ValidPoint_IT(uint32_t *x, uint32_t *y)
{
    uint32_t func = SM2_FUNC_VALIDPOINT;
    HAL_OTBN_IMEM_Write(0, (uint32_t *)sm2_text, sizeof(sm2_text));
    HAL_OTBN_DMEM_Set(0, 0, SM2_DMEM_BSS_END);
    HAL_OTBN_DMEM_Write(SM2_DMEM_CURVE_P_OFFSET, (uint32_t *)&SM2, SM2_DMEM_CURVE_P_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_X_OFFSET, x, SM2_DMEM_X_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_Y_OFFSET, y, SM2_DMEM_Y_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_FUNC_OFFSET, &func, sizeof(uint32_t));
    
    HAL_OTBN_CMD_Write_IT(HAL_OTBN_CMD_EXECUTE, SM2_ValidPoint_Cb, NULL);
}

void SM2_ScalarMult_Cb(void *param)
{
    struct HAL_OTBN_SM2_ScalarMult_Param *p = param;
    HAL_OTBN_DMEM_Read(SM2_DMEM_RESULT_X_OFFSET, p->result_x, SM2_DMEM_RESULT_X_SIZE);
    HAL_OTBN_DMEM_Read(SM2_DMEM_RESULT_Y_OFFSET, p->result_y, SM2_DMEM_RESULT_Y_SIZE);
}

void HAL_OTBN_SM2_ScalarMult_IT(struct HAL_OTBN_SM2_ScalarMult_Param *param)
{
    uint32_t func = SM2_FUNC_SCALARMULT;
    HAL_OTBN_IMEM_Write(0, (uint32_t *)sm2_text, sizeof(sm2_text));
    HAL_OTBN_DMEM_Set(0, 0, SM2_DMEM_BSS_END);
    HAL_OTBN_DMEM_Write(SM2_DMEM_CURVE_P_OFFSET, (uint32_t *)&SM2, SM2_DMEM_CURVE_P_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_K0_OFFSET, param->scalar, SM2_DMEM_K0_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_X_OFFSET, param->point_x, SM2_DMEM_X_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_Y_OFFSET, param->point_y, SM2_DMEM_Y_SIZE);
    HAL_OTBN_DMEM_Write(SM2_DMEM_FUNC_OFFSET, &func, sizeof(uint32_t));
    
    HAL_OTBN_CMD_Write_IT(HAL_OTBN_CMD_EXECUTE, SM2_ScalarMult_Cb, param);

}