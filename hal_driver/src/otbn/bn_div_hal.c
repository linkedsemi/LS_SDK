/* Auto-generated HAL implementation for bn_div */
#include "bn_div_hal.h"
#include "ls_hal_otbn.h"
#include "bn_div_firmware.h"
#include "ls_hal_otbn.h"

#define BN_DIV_MODE_VALUE  (0x1001)

bool HAL_OTBN_DIV_Polling(const uint32_t *dividend, const uint32_t *divisor,
                              uint32_t nlimbs, uint32_t *quotient, uint32_t *remainder)
{
    uint32_t mode = BN_DIV_MODE_VALUE;
    uint32_t n    = nlimbs;

    HAL_OTBN_IMEM_Write(0, (const uint32_t *)g_bn_div_imem, BN_DIV_IMEM_SIZE);
    HAL_OTBN_DMEM_Set(0, 0, BN_DIV_DMEM_TOTAL);
    HAL_OTBN_DMEM_Write(0, (const uint32_t *)g_bn_div_dmem, BN_DIV_DMEM_SIZE);

    HAL_OTBN_DMEM_Write(BN_DIV_MODE_OFFSET,   &mode, sizeof(uint32_t));
    HAL_OTBN_DMEM_Write(BN_DIV_NLIMBS_OFFSET, &n,    sizeof(uint32_t));
    HAL_OTBN_DMEM_Write(BN_DIV_OP_A_OFFSET,   dividend, nlimbs * 32);
    HAL_OTBN_DMEM_Write(BN_DIV_OP_B_OFFSET,   divisor,  nlimbs * 32);

    HAL_OTBN_CMD_Write_Polling(1);

    HAL_OTBN_DMEM_Read(BN_DIV_RESULT_OFFSET, quotient,  nlimbs * 32);
    HAL_OTBN_DMEM_Read(BN_DIV_OP_A_OFFSET,   remainder, nlimbs * 32);
    return true;
}
