/* Auto-generated HAL for bn_modexp */
#ifndef BN_MODEXP_HAL_H
#define BN_MODEXP_HAL_H

#include <stdint.h>
#include <stdbool.h>

/* DMEM layout offsets (from ELF symbol table) */
#define BN_MODEXP_MODE_OFFSET    (0)
#define BN_MODEXP_NLIMBS_OFFSET  (4)
#define BN_MODEXP_OP_A_OFFSET    (32)
#define BN_MODEXP_OP_B_OFFSET    (544)
#define BN_MODEXP_RESULT_OFFSET  (1568)
#define BN_MODEXP_MODULUS_OFFSET (1056)

#define BN_MODEXP_IMEM_SIZE  (g_bn_modexp_imem_size)
#define BN_MODEXP_DMEM_SIZE  (g_bn_modexp_dmem_size)
#define BN_MODEXP_DMEM_TOTAL (2624)

/* External firmware data */
extern const uint8_t g_bn_modexp_imem[];
extern const uint32_t g_bn_modexp_imem_size;
extern const uint8_t g_bn_modexp_dmem[];
extern const uint32_t g_bn_modexp_dmem_size;


/* API */
bool HAL_OTBN_MODEXP_Polling(const uint32_t *base, const uint32_t *exp,
                              const uint32_t *modulus, uint32_t nlimbs, uint32_t *result);

#endif /* BN_MODEXP_HAL_H */
