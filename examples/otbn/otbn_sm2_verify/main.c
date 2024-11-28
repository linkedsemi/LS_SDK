#include <string.h>
#include <stdint.h>
#include "ls_hal_otbn_sm2.h"
#include "platform.h"
#include "log.h"

static uint32_t msg[] = {
    0xC0D28640, 0xF4486FDF, 0x19CE7B31, 0x17E6AB5A,
    0x534382EB, 0xACE692ED, 0xBA45ACCA, 0xF0B43E94};
static uint32_t sign_r[] = {
    0xEEE720B3, 0x43AC7EAC,0x27D5B741, 0x5944DA38,
    0xE1BB81A1, 0x0EEAC513,0x48D2C463, 0xF5A03B06};
static uint32_t sign_s[] = {
    0x85BBC1AA, 0x840B69C4,0x1F7F42D4, 0xBB9038FD,
    0x0D421CA1, 0x763182BC,0xDF212FD8, 0xB1B6AA29};
static uint32_t pubk_x[] = {
    0x56F35020, 0x6BB08FF3,0x1833FC07, 0x72179FAD,
    0x1E4BC5C6, 0x50DD7D16,0x1E5421A1, 0x09F9DF31};
static uint32_t pubk_y[] = {
    0x2DA9AD13, 0x6632F607,0xF35E084A, 0x0AED05FB,
    0x8CC1AA60, 0x2DC6EA71,0xE26775A5, 0xCCEA490C};

struct HAL_OTBN_SM2_Verify_Param Param = {
    .msg = msg,
    .r = sign_r,
    .s = sign_s,
    .x = pubk_x,
    .y = pubk_y,
};

int main(void)
{
    sys_init_none();
    HAL_OTBN_Init();
    bool result = HAL_OTBN_SM2_Verify_Polling(&Param);
    LOG_I("OTBN SM2 Verify result : %d ", result);
    HAL_OTBN_SM2_Verify_IT(&Param);
    
    while (1) ;
}


void HAL_OTBN_SM2_Verify_CallBack(bool result)
{
    LOG_I("OTBN SM2 Verify result : %d ", result);
}
