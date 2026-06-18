/* Auto-generated HAL for ecc_p384_isoncurve */
#ifndef ECC_P384_ISONCURVE_HAL_H
#define ECC_P384_ISONCURVE_HAL_H

#include <stdint.h>
#include <stdbool.h>

/* Operation modes */
#define ECC_P384_ISONCURVE_MODE_VALIDATE       (4)

/* DMEM layout offsets (from ELF symbol table) */
#define ECC_P384_ISONCURVE_MODE_OFFSET (0)
#define ECC_P384_ISONCURVE_OK_OFFSET (4)
#define ECC_P384_ISONCURVE_X_OFFSET (32)
#define ECC_P384_ISONCURVE_Y_OFFSET (96)

#define ECC_P384_ISONCURVE_FIELD_BYTES  (48)
#define ECC_P384_ISONCURVE_IMEM_SIZE    (g_ecc_p384_isoncurve_imem_size)
#define ECC_P384_ISONCURVE_DMEM_SIZE    (g_ecc_p384_isoncurve_dmem_size)
#define ECC_P384_ISONCURVE_DMEM_TOTAL   (608)

/* External firmware data */
extern const uint8_t g_ecc_p384_isoncurve_imem[];
extern const uint32_t g_ecc_p384_isoncurve_imem_size;
extern const uint8_t g_ecc_p384_isoncurve_dmem[];
extern const uint32_t g_ecc_p384_isoncurve_dmem_size;


/* APIs */
bool HAL_OTBN_P384_ValidatePoint_Polling(const uint8_t *x,
                                                          const uint8_t *y);

#endif /* ECC_P384_ISONCURVE_HAL_H */
