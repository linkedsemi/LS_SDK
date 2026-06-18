/* Auto-generated HAL implementation for ecc_p384 */
#include "ecc_p384_hal.h"
#include "ls_hal_otbn.h"
#include "ecc_p384_firmware.h"
#include "ls_hal_otbn.h"
#include <string.h>
#include "ls_hal_otbn.h"

static void ecc_p384_setup_dmem(void)
{
    HAL_OTBN_IMEM_Write(0, (const uint32_t *)g_ecc_p384_imem, ECC_P384_IMEM_SIZE);
    HAL_OTBN_DMEM_Set(0, 0, ECC_P384_DMEM_TOTAL);
    HAL_OTBN_DMEM_Write(0, (const uint32_t *)g_ecc_p384_dmem, ECC_P384_DMEM_SIZE);
}

void HAL_OTBN_P384_ScalarMult_Polling(const uint8_t *scalar_d,
                                         const uint8_t *px, const uint8_t *py,
                                         uint8_t *rx, uint8_t *ry)
{
    uint32_t mode = ECC_P384_MODE_SCALAR_MULT;
    ecc_p384_setup_dmem();
    HAL_OTBN_DMEM_Write(ECC_P384_MODE_OFFSET, &mode, sizeof(uint32_t));
    HAL_OTBN_DMEM_Write(ECC_P384_SCALAR_D_OFFSET,
                        (const uint32_t *)scalar_d, ECC_P384_FIELD_BYTES);
    HAL_OTBN_DMEM_Write(ECC_P384_X_OFFSET, (const uint32_t *)px, ECC_P384_FIELD_BYTES);
    HAL_OTBN_DMEM_Write(ECC_P384_Y_OFFSET, (const uint32_t *)py, ECC_P384_FIELD_BYTES);
    HAL_OTBN_CMD_Write_Polling(1);
    HAL_OTBN_DMEM_Read(ECC_P384_RX_OFFSET, (uint32_t *)rx, ECC_P384_FIELD_BYTES);
    HAL_OTBN_DMEM_Read(ECC_P384_RY_OFFSET, (uint32_t *)ry, ECC_P384_FIELD_BYTES);
}

void HAL_OTBN_P384_BaseMult_Polling(const uint8_t *scalar_d,
                                       uint8_t *rx, uint8_t *ry)
{
    uint32_t mode = ECC_P384_MODE_BASE_MULT;
    ecc_p384_setup_dmem();
    HAL_OTBN_DMEM_Write(ECC_P384_MODE_OFFSET, &mode, sizeof(uint32_t));
    HAL_OTBN_DMEM_Write(ECC_P384_SCALAR_D_OFFSET,
                        (const uint32_t *)scalar_d, ECC_P384_FIELD_BYTES);
    HAL_OTBN_CMD_Write_Polling(1);
    HAL_OTBN_DMEM_Read(ECC_P384_RX_OFFSET, (uint32_t *)rx, ECC_P384_FIELD_BYTES);
    HAL_OTBN_DMEM_Read(ECC_P384_RY_OFFSET, (uint32_t *)ry, ECC_P384_FIELD_BYTES);
}

void HAL_OTBN_P384_PointAdd_Polling(const uint8_t *px, const uint8_t *py,
                                       const uint8_t *qx, const uint8_t *qy,
                                       uint8_t *rx, uint8_t *ry)
{
    uint32_t mode = ECC_P384_MODE_POINT_ADD;
    ecc_p384_setup_dmem();
    HAL_OTBN_DMEM_Write(ECC_P384_MODE_OFFSET, &mode, sizeof(uint32_t));
    HAL_OTBN_DMEM_Write(ECC_P384_X_OFFSET, (const uint32_t *)px, ECC_P384_FIELD_BYTES);
    HAL_OTBN_DMEM_Write(ECC_P384_Y_OFFSET, (const uint32_t *)py, ECC_P384_FIELD_BYTES);
    HAL_OTBN_DMEM_Write(ECC_P384_QX_OFFSET, (const uint32_t *)qx, ECC_P384_FIELD_BYTES);
    HAL_OTBN_DMEM_Write(ECC_P384_QY_OFFSET, (const uint32_t *)qy, ECC_P384_FIELD_BYTES);
    HAL_OTBN_CMD_Write_Polling(1);
    HAL_OTBN_DMEM_Read(ECC_P384_RX_OFFSET, (uint32_t *)rx, ECC_P384_FIELD_BYTES);
    HAL_OTBN_DMEM_Read(ECC_P384_RY_OFFSET, (uint32_t *)ry, ECC_P384_FIELD_BYTES);
}
