/* Auto-generated HAL implementation for bn_modmult */
#include "bn_modmult_hal.h"
#include "ls_hal_otbn.h"
#include "bn_modmult_firmware.h"
#include "ls_hal_otbn.h"

#define BN_MODMULT_MODE_VALUE  (0x1001)

bool HAL_OTBN_MODMULT_Polling(const uint32_t *op_a, const uint32_t *op_b,
                              const uint32_t *modulus, uint32_t nlimbs, uint32_t *result)
{
    uint32_t mode = BN_MODMULT_MODE_VALUE;
    uint32_t n    = nlimbs;

    HAL_OTBN_IMEM_Write(0, (const uint32_t *)g_bn_modmult_imem, BN_MODMULT_IMEM_SIZE);
    HAL_OTBN_DMEM_Set(0, 0, BN_MODMULT_DMEM_TOTAL);
    HAL_OTBN_DMEM_Write(0, (const uint32_t *)g_bn_modmult_dmem, BN_MODMULT_DMEM_SIZE);

    HAL_OTBN_DMEM_Write(BN_MODMULT_MODE_OFFSET,   &mode, sizeof(uint32_t));
    HAL_OTBN_DMEM_Write(BN_MODMULT_NLIMBS_OFFSET, &n,    sizeof(uint32_t));
    HAL_OTBN_DMEM_Write(BN_MODMULT_OP_A_OFFSET,   op_a,    nlimbs * 32);
    HAL_OTBN_DMEM_Write(BN_MODMULT_OP_B_OFFSET,   op_b,    nlimbs * 32);
    HAL_OTBN_DMEM_Write(BN_MODMULT_MODULUS_OFFSET, modulus, nlimbs * 32);

    HAL_OTBN_CMD_Write_Polling(1);

    HAL_OTBN_DMEM_Read(BN_MODMULT_RESULT_OFFSET, result, nlimbs * 32);
    return true;
}
