#include <string.h>
#include <stdint.h>
#include "platform.h"
#include "ls_hal_otbn_ecc256.h"
#include "log.h"

static struct HAL_OTBN_ECC256_ScalarMult_Param param;
static uint32_t scalar[8] = {0xfe6d1071,0x21d0a016,0xb0b2c781,0x9590ef5d,0x3fdfa379,0x1b76ebe8,0x74210263,0x1420fc41};
static uint32_t Px[8] = {0xbfa8c334,0x9773b7b3,0xf36b0689,0x6ec0c0b2,0xdb6c8bf3,0x1628ce58,0xfacdc546,0xb5511a6a};
static uint32_t Py[8] = {0x9e008c2e,0xa8707058,0xab9c6924,0x7f7a11d0,0xb53a17fa,0x43dd09ea,0x1f31c143,0x42a1c697};
static uint32_t result_x[8] = {};
static uint32_t result_y[8] = {};

static void init()
{
    LOG_I(" OTBN P256_Scalar_Mult_Test Start...");
    HAL_OTBN_Init();
    param.p_x = Px;
    param.p_y = Py;
    param.scalar = scalar;
    param.result_x = result_x;
    param.result_y = result_y;
}

int main(void)
{
    sys_init_none();
    init();
    HAL_OTBN_ECC256_Scalar_Mult_IT(&param);

    while (1) ;
}

// Result_X = 82EBC9181D274257E8B275E63D9F867203C115EC90949A730A6426A346D7335F
// Result_Y = 2D466CB7EF3D404C9AF9C97A4FB36ACE3AE21FE462A8703D9E9CC94A1EBDEBB5
void HAL_OTBN_ECC256_ScalarMult_Cb(void)
{
    LOG_I("scarlar_mult result : ");
    LOG_HEX(result_x, 32);
    LOG_HEX(result_y, 32);
}
