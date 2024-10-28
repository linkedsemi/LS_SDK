#include <string.h>
#include <stdint.h>
#include "ls_hal_otbn_sm2.h"
#include "platform.h"
#include "log.h"

uint32_t x[] = {
    0x331A8308, 0x7EB00BEF, 0xBB2FF631, 0xEF5DDEB0,
    0x273747D7, 0xBA880429, 0x4E9C91F7, 0xB9C9A6E0};
uint32_t y[] = {
    0x24620207, 0x347B483E, 0x4162F5AF, 0x87C018FB,
    0x1872266C, 0x6EADDDB8, 0x993F3F5D, 0x1A6994B8};

int main(void)
{
    sys_init_none();
    HAL_OTBN_Init();
    HAL_OTBN_SM2_ValidPoint_IT(x, y);
    
    while (1) ;
}


void HAL_OTBN_SM2_ValidPoint_CallBack(bool result)
{
    LOG_I("OTBN SM2 ValidPoint result : %d ", result);
}
