/* Auto-generated HAL implementation for bn_modinv */
#include "bn_modinv_hal.h"
#include "ls_hal_otbn.h"
#include "bn_modinv_firmware.h"
#include "ls_hal_otbn.h"

#define BN_MODINV_MODE_VALUE  (0x1001)

bool HAL_OTBN_MODINV_Polling(const uint32_t *n, const uint32_t *modulus,
                              uint32_t nlimbs, uint32_t *result)
{
    uint32_t mode = BN_MODINV_MODE_VALUE;
    uint32_t nl   = nlimbs;

    HAL_OTBN_IMEM_Write(0, (const uint32_t *)g_bn_modinv_imem, BN_MODINV_IMEM_SIZE);
    HAL_OTBN_DMEM_Set(0, 0, BN_MODINV_DMEM_TOTAL);
    HAL_OTBN_DMEM_Write(0, (const uint32_t *)g_bn_modinv_dmem, BN_MODINV_DMEM_SIZE);

    HAL_OTBN_DMEM_Write(BN_MODINV_MODE_OFFSET,   &mode, sizeof(uint32_t));
    HAL_OTBN_DMEM_Write(BN_MODINV_NLIMBS_OFFSET, &nl,   sizeof(uint32_t));
    HAL_OTBN_DMEM_Write(BN_MODINV_OP_A_OFFSET,   n,       nlimbs * 32);
    HAL_OTBN_DMEM_Write(BN_MODINV_MODULUS_OFFSET, modulus, nlimbs * 32);

    HAL_OTBN_CMD_Write_Polling(1);

    HAL_OTBN_DMEM_Read(BN_MODINV_RESULT_OFFSET, result, nlimbs * 32);
    return true;
}
