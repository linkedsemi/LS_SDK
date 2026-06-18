/* Auto-generated HAL for ecc_p521 atomic operations */
#ifndef ECC_P521_HAL_H
#define ECC_P521_HAL_H

#include <stdint.h>
#include <stdbool.h>

/* Operation modes */
#define ECC_P521_MODE_FIELD_ADD    (0x100)
#define ECC_P521_MODE_FIELD_SUB    (0x101)
#define ECC_P521_MODE_FIELD_MUL    (0x102)
#define ECC_P521_MODE_POINT_DBL    (0x200)
#define ECC_P521_MODE_POINT_ADD    (0x201)

/* DMEM layout offsets (must match main.s) */
#define ECC_P521_MODE_OFFSET     (0)
#define ECC_P521_P_OFFSET        (0x20)
#define ECC_P521_Q_OFFSET        (0x140)
#define ECC_P521_R_OFFSET        (0x260)

#define ECC_P521_FIELD_BYTES  (66)
#define ECC_P521_COORD_BYTES  (96)  /* 3 WDRs = 96 bytes, 4-byte aligned for HAL */
#define ECC_P521_IMEM_SIZE    (g_ecc_p521_imem_size)
#define ECC_P521_DMEM_SIZE    (g_ecc_p521_dmem_size)
#define ECC_P521_DMEM_TOTAL   (4096)

/* External firmware data */
extern const uint8_t g_ecc_p521_imem[];
extern const uint32_t g_ecc_p521_imem_size;
extern const uint8_t g_ecc_p521_dmem[];
extern const uint32_t g_ecc_p521_dmem_size;


/* APIs */
void HAL_OTBN_P521_ScalarMult_Polling(const uint8_t *k,
                                      const uint8_t *px, const uint8_t *py,
                                      uint8_t *rx, uint8_t *ry);
void HAL_OTBN_P521_BaseMult_Polling(const uint8_t *k,
                                    uint8_t *rx, uint8_t *ry);
void HAL_OTBN_P521_PointAdd_Polling(const uint8_t *px, const uint8_t *py,
                                    const uint8_t *qx, const uint8_t *qy,
                                    uint8_t *rx, uint8_t *ry);

#endif /* ECC_P521_HAL_H */
