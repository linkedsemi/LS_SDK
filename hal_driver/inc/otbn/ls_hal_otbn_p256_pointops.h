/* Auto-generated HAL for ecc_p256 */
#ifndef ECC_P256_HAL_H
#define ECC_P256_HAL_H

#include <stdint.h>
#include <stdbool.h>
#include "ls_hal_otbn.h"

/* Operation modes */
#define ECC_P256_MODE_SCALAR_MULT    (1)
#define ECC_P256_MODE_POINT_ADD      (2)
#define ECC_P256_MODE_DOUBLE_SCALAR  (3)
#define ECC_P256_MODE_CURVE_INIT     (4)
#define ECC_P256_MODE_BASE_MULT      (5)

/* DMEM layout offsets (from ELF symbol table) */
#define ECC_P256_MODE_OFFSET     (224)
#define ECC_P256_CURVE_ID_OFFSET (228)
#define ECC_P256_OK_OFFSET       (232)
#define ECC_P256_SCALAR_D_OFFSET (256)
#define ECC_P256_SCALAR_U_OFFSET (320)
#define ECC_P256_X_OFFSET        (384)
#define ECC_P256_Y_OFFSET        (416)
#define ECC_P256_QX_OFFSET       (448)
#define ECC_P256_QY_OFFSET       (480)

#define ECC_P256_FIELD_BYTES  (32)
#define ECC_P256_IMEM_SIZE    (g_ecc_p256_imem_size)
#define ECC_P256_DMEM_SIZE    (g_ecc_p256_dmem_size)
#define ECC_P256_DMEM_TOTAL   (1120)

/* External firmware data */
extern const uint8_t g_ecc_p256_imem[];
extern const uint32_t g_ecc_p256_imem_size;
extern const uint8_t g_ecc_p256_dmem[];
extern const uint32_t g_ecc_p256_dmem_size;


/* APIs */
HAL_StatusTypeDef HAL_OTBN_P256_ScalarMult_Polling(const uint8_t *scalar_d,
                                                     const uint8_t *px, const uint8_t *py,
                                                     uint8_t *rx, uint8_t *ry);
HAL_StatusTypeDef HAL_OTBN_P256_BaseMult_Polling(const uint8_t *scalar_d,
                                                   uint8_t *rx, uint8_t *ry);
HAL_StatusTypeDef HAL_OTBN_P256_PointAdd_Polling(const uint8_t *px, const uint8_t *py,
                                                   const uint8_t *qx, const uint8_t *qy,
                                                   uint8_t *rx, uint8_t *ry);

#endif /* ECC_P256_HAL_H */
