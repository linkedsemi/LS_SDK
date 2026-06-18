/* Auto-generated HAL implementation for bn_modexp */
#include "bn_modexp_hal.h"
#include "ls_hal_otbn.h"
#include "bn_modexp_firmware.h"
#include "ls_hal_otbn.h"

#define BN_MODEXP_MODE_VALUE  (0x1001)

bool HAL_OTBN_MODEXP_Polling(const uint32_t *base, const uint32_t *exp,
                              const uint32_t *modulus, uint32_t nlimbs, uint32_t *result)
{
    uint32_t mode = BN_MODEXP_MODE_VALUE;
    uint32_t n    = nlimbs;

    HAL_OTBN_IMEM_Write(0, (const uint32_t *)g_bn_modexp_imem, BN_MODEXP_IMEM_SIZE);
    HAL_OTBN_DMEM_Set(0, 0, BN_MODEXP_DMEM_TOTAL);
    HAL_OTBN_DMEM_Write(0, (const uint32_t *)g_bn_modexp_dmem, BN_MODEXP_DMEM_SIZE);

    HAL_OTBN_DMEM_Write(BN_MODEXP_MODE_OFFSET,   &mode, sizeof(uint32_t));
    HAL_OTBN_DMEM_Write(BN_MODEXP_NLIMBS_OFFSET, &n,    sizeof(uint32_t));
    HAL_OTBN_DMEM_Write(BN_MODEXP_OP_A_OFFSET,   base,    nlimbs * 32);
    HAL_OTBN_DMEM_Write(BN_MODEXP_OP_B_OFFSET,   exp,     nlimbs * 32);
    HAL_OTBN_DMEM_Write(BN_MODEXP_MODULUS_OFFSET, modulus, nlimbs * 32);

    HAL_OTBN_CMD_Write_Polling(1);

    HAL_OTBN_DMEM_Read(BN_MODEXP_RESULT_OFFSET, result, nlimbs * 32);
    return true;
}
