/* Auto-generated HAL for ecc_sm2 */
#ifndef ECC_SM2_HAL_H
#define ECC_SM2_HAL_H

#include <stdint.h>
#include <stdbool.h>
#include "ls_hal_otbn.h"

/* Operation modes */
#define ECC_SM2_MODE_SCALAR_MULT    (1)
#define ECC_SM2_MODE_POINT_ADD      (2)
#define ECC_SM2_MODE_DOUBLE_SCALAR  (3)
#define ECC_SM2_MODE_CURVE_INIT     (4)
#define ECC_SM2_MODE_BASE_MULT      (5)

/* DMEM layout offsets (from ELF symbol table) */
#define ECC_SM2_MODE_OFFSET      (224)
#define ECC_SM2_CURVE_ID_OFFSET  (228)
#define ECC_SM2_OK_OFFSET        (232)
#define ECC_SM2_SCALAR_D_OFFSET  (256)
#define ECC_SM2_SCALAR_U_OFFSET  (320)
#define ECC_SM2_X_OFFSET         (384)
#define ECC_SM2_Y_OFFSET         (416)
#define ECC_SM2_QX_OFFSET        (448)
#define ECC_SM2_QY_OFFSET        (480)

#define ECC_SM2_FIELD_BYTES  (32)
#define ECC_SM2_IMEM_SIZE    (g_ecc_sm2_imem_size)
#define ECC_SM2_DMEM_SIZE    (g_ecc_sm2_dmem_size)
#define ECC_SM2_DMEM_TOTAL   (1088)

/* External firmware data */
extern const uint8_t g_ecc_sm2_imem[];
extern const uint32_t g_ecc_sm2_imem_size;
extern const uint8_t g_ecc_sm2_dmem[];
extern const uint32_t g_ecc_sm2_dmem_size;


/* APIs */
HAL_StatusTypeDef HAL_OTBN_SM2_ScalarMult_Polling(const uint8_t *scalar_d,
                                                     const uint8_t *px, const uint8_t *py,
                                                     uint8_t *rx, uint8_t *ry);
HAL_StatusTypeDef HAL_OTBN_SM2_BaseMult_Polling(const uint8_t *scalar_d,
                                                   uint8_t *rx, uint8_t *ry);
HAL_StatusTypeDef HAL_OTBN_SM2_PointAdd_Polling(const uint8_t *px, const uint8_t *py,
                                                   const uint8_t *qx, const uint8_t *qy,
                                                   uint8_t *rx, uint8_t *ry);

#endif /* ECC_SM2_HAL_H */
