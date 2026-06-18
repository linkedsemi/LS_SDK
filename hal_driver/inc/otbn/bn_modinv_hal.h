/* Auto-generated HAL for bn_modinv */
#ifndef BN_MODINV_HAL_H
#define BN_MODINV_HAL_H

#include <stdint.h>
#include <stdbool.h>

/* DMEM layout offsets (from ELF symbol table) */
#define BN_MODINV_MODE_OFFSET    (0)
#define BN_MODINV_NLIMBS_OFFSET  (4)
#define BN_MODINV_OP_A_OFFSET    (32)
#define BN_MODINV_RESULT_OFFSET  (1568)
#define BN_MODINV_MODULUS_OFFSET (544)
#define BN_MODINV_EXPONENT_OFFSET (1056)

#define BN_MODINV_IMEM_SIZE  (g_bn_modinv_imem_size)
#define BN_MODINV_DMEM_SIZE  (g_bn_modinv_dmem_size)
#define BN_MODINV_DMEM_TOTAL (2624)

/* External firmware data */
extern const uint8_t g_bn_modinv_imem[];
extern const uint32_t g_bn_modinv_imem_size;
extern const uint8_t g_bn_modinv_dmem[];
extern const uint32_t g_bn_modinv_dmem_size;


/* API */
bool HAL_OTBN_MODINV_Polling(const uint32_t *n, const uint32_t *modulus,
                              uint32_t nlimbs, uint32_t *result);

#endif /* BN_MODINV_HAL_H */
