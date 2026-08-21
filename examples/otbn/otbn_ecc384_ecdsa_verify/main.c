#include <string.h>
#include <stdint.h>
#include "ls_hal_otbn_ecc.h"
#include "platform.h"
#include "log.h"

/* ECDSA P-384 test vector (u32 words, least-significant word first --
 * the SDK verify parameter format; each field is 48 bytes = 12 words) */
static uint32_t message[12] = {
    0x55555555, 0x55555555, 0x55555555, 0x55555555,
    0x55555555, 0x55555555, 0x55555555, 0x55555555,
    0x55555555, 0x55555555, 0x55555555, 0x55555555};
static uint32_t sign_r[12] = {
    0xb68c28d8, 0x2b23ce3a, 0x9a1a30fc, 0x56e186cf,
    0x12d35b38, 0xc16c09de, 0x0235d77e, 0x49d29eef,
    0xd3c43053, 0xb45990db, 0x7c0d8125, 0xb2fcf95c};
static uint32_t sign_s[12] = {
    0x24bc1bf9, 0x752042f5, 0x98144c27, 0x77e415a1,
    0xa78101eb, 0x0016f9c3, 0x3e7f6895, 0x80eb391d,
    0xf19a653d, 0xfa9554e0, 0xe34d88c1, 0x1a72ebdd};
static uint32_t pubkey_x[12] = {
    0x4877f3d1, 0x7b829460, 0xb1cac609, 0x5869de54,
    0xee0e2beb, 0x6c30f2d8, 0x47e80661, 0x394d8b70,
    0xcf60d89e, 0x1a9ea916, 0xb439d701, 0xca230836};
static uint32_t pubkey_y[12] = {
    0xc181f90f, 0xc31ef079, 0xbf3aff6e, 0xc7e55880,
    0xec18818c, 0xcea028a9, 0x928c3e92, 0x82b63bf3,
    0xd65e905d, 0x68eef2d1, 0x03afe2c2, 0xaaafcad2};

static struct HAL_OTBN_ECC384_Verify_Param p384_param = {
    .msg = message,
    .r = sign_r,
    .s = sign_s,
    .x = pubkey_x,
    .y = pubkey_y,
};

/* [0]=Polling result, [1]=IT callback result (GDB-readable) */
volatile uint32_t g_result[2] = {0, 0};

int main(void)
{
    sys_init_none();
    HAL_OTBN_Init();

    LOG_I(" OTBN P384_ECDSA_Verify_Test Start...");
    g_result[0] = HAL_OTBN_ECC384_ECDSA_Verify_Polling(HAL_OTBN_ECC384_CURVE_P384, &p384_param);
    if (g_result[0])
        LOG_I("HAL_OTBN_P384_Verify pass!");
    else
        LOG_I("HAL_OTBN_P384_Verify fail!");

    HAL_OTBN_ECC384_ECDSA_Verify_IT(HAL_OTBN_ECC384_CURVE_P384, &p384_param);

    while (1) ;
}

void HAL_OTBN_ECC384_ECDSA_Verify_CallBack(bool result)
{
    g_result[1] = result;
    LOG_I("ecdsa Verify IT: %s", result ? "PASS" : "FAIL");
}
