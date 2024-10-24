#include <string.h>
#include <stdint.h>
#include "ls_hal_otbn_sm2.h"
#include "platform.h"
#include "log.h"

static uint32_t msg[] = {
    0x00313131, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000};
static uint32_t sign_r[] = {
    0xb55b10cf, 0xa9ec6dd4,0x8f053307, 0xdd542b3a,
    0x4757a53f, 0x3bf8c110,0xaa201141, 0xc68a1bf0};
static uint32_t sign_s[] = {
    0xa7d3498e, 0xb5e64121,0x28c99741, 0xe69a57ff,
    0x3a059cd3, 0x2ba80623,0x35712c3d, 0x97dca223};
static uint32_t pubk_x[] = {
    0x331A8308, 0x7EB00BEF,0xBB2FF631, 0xEF5DDEB0,
    0x273747D7, 0xBA880429,0x4E9C91F7, 0xB9C9A6E0};
static uint32_t pubk_y[] = {
    0x24620207, 0x347B483E,0x4162F5AF, 0x87C018FB,
    0x1872266C, 0x6EADDDB8,0x993F3F5D, 0x1A6994B8};

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
    HAL_OTBN_SM2_Verify_IT(&Param);
    
    while (1) ;
}


void HAL_OTBN_SM2_Verify_CallBack(bool result)
{
    LOG_I("OTBN SM2 Verify result : %d ", result);
}
