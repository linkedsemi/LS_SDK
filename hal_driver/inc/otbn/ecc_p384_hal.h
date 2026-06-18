/* Auto-generated HAL for ecc_p384 */
#ifndef ECC_P384_HAL_H
#define ECC_P384_HAL_H

#include <stdint.h>
#include <stdbool.h>

/* Operation modes */
#define ECC_P384_MODE_SCALAR_MULT    (1)
#define ECC_P384_MODE_POINT_ADD      (2)
#define ECC_P384_MODE_DOUBLE_SCALAR  (3)
#define ECC_P384_MODE_CURVE_INIT     (4)
#define ECC_P384_MODE_BASE_MULT      (5)

/* DMEM layout offsets (from ELF symbol table) */
#define ECC_P384_MODE_OFFSET     (320)
#define ECC_P384_CURVE_ID_OFFSET (324)
#define ECC_P384_OK_OFFSET       (328)
#define ECC_P384_SCALAR_D_OFFSET (352)
#define ECC_P384_SCALAR_U_OFFSET (416)
#define ECC_P384_X_OFFSET        (480)
#define ECC_P384_Y_OFFSET        (544)
#define ECC_P384_QX_OFFSET       (608)
#define ECC_P384_QY_OFFSET       (672)
#define ECC_P384_RX_OFFSET       (736)
#define ECC_P384_RY_OFFSET       (800)

#define ECC_P384_FIELD_BYTES  (48)
#define ECC_P384_IMEM_SIZE    (g_ecc_p384_imem_size)
#define ECC_P384_DMEM_SIZE    (g_ecc_p384_dmem_size)
#define ECC_P384_DMEM_TOTAL   (1696)

/* External firmware data */
extern const uint8_t g_ecc_p384_imem[];
extern const uint32_t g_ecc_p384_imem_size;
extern const uint8_t g_ecc_p384_dmem[];
extern const uint32_t g_ecc_p384_dmem_size;


/* APIs */
void HAL_OTBN_P384_ScalarMult_Polling(const uint8_t *scalar_d,
                                                     const uint8_t *px, const uint8_t *py,
                                                     uint8_t *rx, uint8_t *ry);
void HAL_OTBN_P384_BaseMult_Polling(const uint8_t *scalar_d,
                                                   uint8_t *rx, uint8_t *ry);
void HAL_OTBN_P384_PointAdd_Polling(const uint8_t *px, const uint8_t *py,
                                                   const uint8_t *qx, const uint8_t *qy,
                                                   uint8_t *rx, uint8_t *ry);

#endif /* ECC_P384_HAL_H */
