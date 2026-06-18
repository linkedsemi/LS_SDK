/* Auto-generated HAL implementation for bn_mul */
#include "bn_mul_hal.h"
#include "ls_hal_otbn.h"
#include "bn_mul_firmware.h"
#include "ls_hal_otbn.h"

#define BN_MUL_MODE_VALUE  (0x1001)

bool HAL_OTBN_MUL_Polling(const uint32_t *op_a, const uint32_t *op_b,
                              uint32_t nlimbs, uint32_t *result)
{
    uint32_t mode = BN_MUL_MODE_VALUE;
    uint32_t n    = nlimbs;

    HAL_OTBN_IMEM_Write(0, (const uint32_t *)g_bn_mul_imem, BN_MUL_IMEM_SIZE);
    HAL_OTBN_DMEM_Set(0, 0, BN_MUL_DMEM_TOTAL);
    HAL_OTBN_DMEM_Write(0, (const uint32_t *)g_bn_mul_dmem, BN_MUL_DMEM_SIZE);

    HAL_OTBN_DMEM_Write(BN_MUL_MODE_OFFSET,   &mode, sizeof(uint32_t));
    HAL_OTBN_DMEM_Write(BN_MUL_NLIMBS_OFFSET, &n,    sizeof(uint32_t));
    HAL_OTBN_DMEM_Write(BN_MUL_OP_A_OFFSET,   op_a,  nlimbs * 32);
    HAL_OTBN_DMEM_Write(BN_MUL_OP_B_OFFSET,   op_b,  nlimbs * 32);

    HAL_OTBN_CMD_Write_Polling(1);

    HAL_OTBN_DMEM_Read(BN_MUL_RESULT_OFFSET, result, nlimbs * 64);
    return true;
}
