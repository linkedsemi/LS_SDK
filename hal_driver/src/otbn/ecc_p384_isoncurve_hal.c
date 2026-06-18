/* Auto-generated HAL implementation for ecc_p384_isoncurve */
#include "ecc_p384_isoncurve_hal.h"
#include "ls_hal_otbn.h"
#include "ecc_p384_isoncurve_firmware.h"
#include "ls_hal_otbn.h"
#include <string.h>
#include "ls_hal_otbn.h"

bool HAL_OTBN_P384_ValidatePoint_Polling(const uint8_t *x,
                                                          const uint8_t *y)
{
    uint32_t mode = ECC_P384_ISONCURVE_MODE_VALIDATE;

    HAL_OTBN_IMEM_Write(0, (const uint32_t *)g_ecc_p384_isoncurve_imem, ECC_P384_ISONCURVE_IMEM_SIZE);
    HAL_OTBN_DMEM_Set(0, 0, ECC_P384_ISONCURVE_DMEM_TOTAL);
    HAL_OTBN_DMEM_Write(0, (const uint32_t *)g_ecc_p384_isoncurve_dmem, ECC_P384_ISONCURVE_DMEM_SIZE);

    HAL_OTBN_DMEM_Write(ECC_P384_ISONCURVE_MODE_OFFSET, &mode, sizeof(uint32_t));
    HAL_OTBN_DMEM_Write(ECC_P384_ISONCURVE_X_OFFSET, (const uint32_t *)x, ECC_P384_ISONCURVE_FIELD_BYTES);
    HAL_OTBN_DMEM_Write(ECC_P384_ISONCURVE_Y_OFFSET, (const uint32_t *)y, ECC_P384_ISONCURVE_FIELD_BYTES);

    HAL_OTBN_CMD_Write_Polling(1); /* HAL_OTBN_CMD_EXECUTE */

    uint32_t ok = 0;
    HAL_OTBN_DMEM_Read(ECC_P384_ISONCURVE_OK_OFFSET, &ok, sizeof(uint32_t));
    return (ok != 0);
}
