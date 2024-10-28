#include <string.h>
#include <stdint.h>
#include "platform.h"
#include "ls_hal_otbn_ecc256.h"
#include "log.h"

static struct HAL_OTBN_ECC256_ScalarMult_Param param;
static uint32_t p256_k[8]  = {0xfe6d1071, 0x21d0a016, 0xb0b2c781, 0x9590ef5d, 0x3fdfa379, 0x1b76ebe8, 0x74210263, 0x1420fc41};
static uint32_t p256_Px[8] = {0xbfa8c334, 0x9773b7b3, 0xf36b0689, 0x6ec0c0b2, 0xdb6c8bf3, 0x1628ce58, 0xfacdc546, 0xb5511a6a};
static uint32_t p256_Py[8] = {0x9e008c2e, 0xa8707058, 0xab9c6924, 0x7f7a11d0, 0xb53a17fa, 0x43dd09ea, 0x1f31c143, 0x42a1c697};
static uint32_t sm2_k[8]   = {0x3431E41A, 0xBD9C4C3C, 0xC034F2BE, 0xD4B1EDFF, 0x834962CA, 0x98C8950E, 0x21DA8C17, 0x06CEDF89};
static uint32_t sm2_Gx[8]  = {0x334C74C7, 0x715A4589, 0xF2660BE1, 0x8FE30BBF, 0x6A39C994, 0x5F990446, 0x1F198119, 0x32C4AE2C};
static uint32_t sm2_Gy[8]  = {0x2139F0A0, 0x02DF32E5, 0xC62A4740, 0xD0A9877C, 0x6B692153, 0x59BDCEE3, 0xF4F6779C, 0xBC3736A2};
static uint32_t result_x[8] = {};
static uint32_t result_y[8] = {};

static volatile bool flag = true;

static void test()
{
    param.scalar = p256_k;
    param.point_x = p256_Px;
    param.point_y = p256_Py;
    param.result_x = result_x;
    param.result_y = result_y;
    LOG_I("Curve P256 ScalarMult :");
    HAL_OTBN_ECC256_ScalarMult_IT(HAL_OTBN_ECC256_CURVE_P256, &param);
    while (flag) ;
    HAL_OTBN_CMD_Write_Polling(HAL_OTBN_CMD_SEC_WIPE_DMEM);
    
    flag = true;
    param.scalar = sm2_k;
    param.point_x = sm2_Gx;
    param.point_y = sm2_Gy;
    param.result_x = result_x;
    param.result_y = result_y;
    LOG_I("Curve SM2 ScalarMult :");
    HAL_OTBN_ECC256_ScalarMult_IT(HAL_OTBN_ECC256_CURVE_SM2, &param);
    while (flag) ;
    HAL_OTBN_CMD_Write_Polling(HAL_OTBN_CMD_SEC_WIPE_DMEM);
}

int main(void)
{
    sys_init_none();
    HAL_OTBN_Init();
    LOG_I(" OTBN ECC256_Scalar_Mult_Test Start...");
    test();

    while (1) ;
}

// P256_Result_x    0x82EBC9181D274257E8B275E63D9F867203C115EC90949A730A6426A346D7335F
// P256_Result_y    0x2D466CB7EF3D404C9AF9C97A4FB36ACE3AE21FE462A8703D9E9CC94A1EBDEBB5
// SM2_Result_x     0xC005D5D993566CAEAD01B9DB4680481572B1423C87EDA7506586AAEAD3C03915
// SM2_Result_y     0x068511F3180BCCBFD75022E94B4F3AD1B12426D8206EF5AF859F5AA8C90358B7
void HAL_OTBN_ECC256_ScalarMult_Cb(void)
{
    LOG_HEX(result_x, 0x20);
    LOG_HEX(result_y, 0x20);
    flag = false;
}
