/* Auto-generated HAL implementation for ecc_p256 */
#include "ls_hal_otbn_p256_pointops.h"
#include "ls_hal_otbn.h"
#include "ls_hal_otbn.h"
#include <string.h>
#include "ls_hal_otbn.h"

static void ecc_p256_setup_dmem(void)
{
    HAL_OTBN_IMEM_Write(0, (const uint32_t *)g_ecc_p256_imem, ECC_P256_IMEM_SIZE);
    HAL_OTBN_DMEM_Set(0, 0, ECC_P256_DMEM_TOTAL);
    HAL_OTBN_DMEM_Write(0, (const uint32_t *)g_ecc_p256_dmem, ECC_P256_DMEM_SIZE);
}

HAL_StatusTypeDef HAL_OTBN_P256_ScalarMult_Polling(const uint8_t *scalar_d,
                                         const uint8_t *px, const uint8_t *py,
                                         uint8_t *rx, uint8_t *ry)
{
    uint32_t mode = ECC_P256_MODE_SCALAR_MULT;
    ecc_p256_setup_dmem();
    HAL_OTBN_DMEM_Write(ECC_P256_MODE_OFFSET, &mode, sizeof(uint32_t));
    HAL_OTBN_DMEM_Write(ECC_P256_SCALAR_D_OFFSET,
                        (const uint32_t *)scalar_d, ECC_P256_FIELD_BYTES);
    HAL_OTBN_DMEM_Write(ECC_P256_X_OFFSET, (const uint32_t *)px, ECC_P256_FIELD_BYTES);
    HAL_OTBN_DMEM_Write(ECC_P256_Y_OFFSET, (const uint32_t *)py, ECC_P256_FIELD_BYTES);
    if (HAL_OTBN_CMD_Write_Polling_Timeout(HAL_OTBN_CMD_EXECUTE, 20000) != HAL_OK)
        return HAL_TIMEOUT;
    HAL_OTBN_DMEM_Read(ECC_P256_X_OFFSET, (uint32_t *)rx, ECC_P256_FIELD_BYTES);
    HAL_OTBN_DMEM_Read(ECC_P256_Y_OFFSET, (uint32_t *)ry, ECC_P256_FIELD_BYTES);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_OTBN_P256_BaseMult_Polling(const uint8_t *scalar_d,
                                       uint8_t *rx, uint8_t *ry)
{
    uint32_t mode = ECC_P256_MODE_BASE_MULT;
    ecc_p256_setup_dmem();
    HAL_OTBN_DMEM_Write(ECC_P256_MODE_OFFSET, &mode, sizeof(uint32_t));
    HAL_OTBN_DMEM_Write(ECC_P256_SCALAR_D_OFFSET,
                        (const uint32_t *)scalar_d, ECC_P256_FIELD_BYTES);
    if (HAL_OTBN_CMD_Write_Polling_Timeout(HAL_OTBN_CMD_EXECUTE, 20000) != HAL_OK)
        return HAL_TIMEOUT;
    HAL_OTBN_DMEM_Read(ECC_P256_X_OFFSET, (uint32_t *)rx, ECC_P256_FIELD_BYTES);
    HAL_OTBN_DMEM_Read(ECC_P256_Y_OFFSET, (uint32_t *)ry, ECC_P256_FIELD_BYTES);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_OTBN_P256_PointAdd_Polling(const uint8_t *px, const uint8_t *py,
                                       const uint8_t *qx, const uint8_t *qy,
                                       uint8_t *rx, uint8_t *ry)
{
    uint32_t mode = ECC_P256_MODE_POINT_ADD;
    ecc_p256_setup_dmem();
    HAL_OTBN_DMEM_Write(ECC_P256_MODE_OFFSET, &mode, sizeof(uint32_t));
    HAL_OTBN_DMEM_Write(ECC_P256_X_OFFSET, (const uint32_t *)px, ECC_P256_FIELD_BYTES);
    HAL_OTBN_DMEM_Write(ECC_P256_Y_OFFSET, (const uint32_t *)py, ECC_P256_FIELD_BYTES);
    HAL_OTBN_DMEM_Write(ECC_P256_QX_OFFSET, (const uint32_t *)qx, ECC_P256_FIELD_BYTES);
    HAL_OTBN_DMEM_Write(ECC_P256_QY_OFFSET, (const uint32_t *)qy, ECC_P256_FIELD_BYTES);
    if (HAL_OTBN_CMD_Write_Polling_Timeout(HAL_OTBN_CMD_EXECUTE, 20000) != HAL_OK)
        return HAL_TIMEOUT;
    HAL_OTBN_DMEM_Read(ECC_P256_X_OFFSET, (uint32_t *)rx, ECC_P256_FIELD_BYTES);
    HAL_OTBN_DMEM_Read(ECC_P256_Y_OFFSET, (uint32_t *)ry, ECC_P256_FIELD_BYTES);
    return HAL_OK;
}
