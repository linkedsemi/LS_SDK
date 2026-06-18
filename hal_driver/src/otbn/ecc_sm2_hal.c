/* Auto-generated HAL implementation for ecc_sm2 */
#include "ecc_sm2_hal.h"
#include "ls_hal_otbn.h"
#include "ecc_sm2_firmware.h"
#include "ls_hal_otbn.h"
#include <string.h>
#include "ls_hal_otbn.h"

static void ecc_sm2_setup_dmem(void)
{
    HAL_OTBN_IMEM_Write(0, (const uint32_t *)g_ecc_sm2_imem, ECC_SM2_IMEM_SIZE);
    HAL_OTBN_DMEM_Set(0, 0, ECC_SM2_DMEM_TOTAL);
    HAL_OTBN_DMEM_Write(0, (const uint32_t *)g_ecc_sm2_dmem, ECC_SM2_DMEM_SIZE);
}

void HAL_OTBN_SM2_ScalarMult_Polling(const uint8_t *scalar_d,
                                         const uint8_t *px, const uint8_t *py,
                                         uint8_t *rx, uint8_t *ry)
{
    uint32_t mode = ECC_SM2_MODE_SCALAR_MULT;
    ecc_sm2_setup_dmem();
    HAL_OTBN_DMEM_Write(ECC_SM2_MODE_OFFSET, &mode, sizeof(uint32_t));
    HAL_OTBN_DMEM_Write(ECC_SM2_SCALAR_D_OFFSET,
                        (const uint32_t *)scalar_d, ECC_SM2_FIELD_BYTES);
    HAL_OTBN_DMEM_Write(ECC_SM2_X_OFFSET, (const uint32_t *)px, ECC_SM2_FIELD_BYTES);
    HAL_OTBN_DMEM_Write(ECC_SM2_Y_OFFSET, (const uint32_t *)py, ECC_SM2_FIELD_BYTES);
    HAL_OTBN_CMD_Write_Polling(1);
    HAL_OTBN_DMEM_Read(ECC_SM2_X_OFFSET, (uint32_t *)rx, ECC_SM2_FIELD_BYTES);
    HAL_OTBN_DMEM_Read(ECC_SM2_Y_OFFSET, (uint32_t *)ry, ECC_SM2_FIELD_BYTES);
}

void HAL_OTBN_SM2_BaseMult_Polling(const uint8_t *scalar_d,
                                       uint8_t *rx, uint8_t *ry)
{
    uint32_t mode = ECC_SM2_MODE_BASE_MULT;
    ecc_sm2_setup_dmem();
    HAL_OTBN_DMEM_Write(ECC_SM2_MODE_OFFSET, &mode, sizeof(uint32_t));
    HAL_OTBN_DMEM_Write(ECC_SM2_SCALAR_D_OFFSET,
                        (const uint32_t *)scalar_d, ECC_SM2_FIELD_BYTES);
    HAL_OTBN_CMD_Write_Polling(1);
    HAL_OTBN_DMEM_Read(ECC_SM2_X_OFFSET, (uint32_t *)rx, ECC_SM2_FIELD_BYTES);
    HAL_OTBN_DMEM_Read(ECC_SM2_Y_OFFSET, (uint32_t *)ry, ECC_SM2_FIELD_BYTES);
}

void HAL_OTBN_SM2_PointAdd_Polling(const uint8_t *px, const uint8_t *py,
                                       const uint8_t *qx, const uint8_t *qy,
                                       uint8_t *rx, uint8_t *ry)
{
    uint32_t mode = ECC_SM2_MODE_POINT_ADD;
    ecc_sm2_setup_dmem();
    HAL_OTBN_DMEM_Write(ECC_SM2_MODE_OFFSET, &mode, sizeof(uint32_t));
    HAL_OTBN_DMEM_Write(ECC_SM2_X_OFFSET, (const uint32_t *)px, ECC_SM2_FIELD_BYTES);
    HAL_OTBN_DMEM_Write(ECC_SM2_Y_OFFSET, (const uint32_t *)py, ECC_SM2_FIELD_BYTES);
    HAL_OTBN_DMEM_Write(ECC_SM2_QX_OFFSET, (const uint32_t *)qx, ECC_SM2_FIELD_BYTES);
    HAL_OTBN_DMEM_Write(ECC_SM2_QY_OFFSET, (const uint32_t *)qy, ECC_SM2_FIELD_BYTES);
    HAL_OTBN_CMD_Write_Polling(1);
    HAL_OTBN_DMEM_Read(ECC_SM2_X_OFFSET, (uint32_t *)rx, ECC_SM2_FIELD_BYTES);
    HAL_OTBN_DMEM_Read(ECC_SM2_Y_OFFSET, (uint32_t *)ry, ECC_SM2_FIELD_BYTES);
}
