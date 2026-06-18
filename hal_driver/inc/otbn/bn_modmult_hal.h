/* Auto-generated HAL for bn_modmult */
#ifndef BN_MODMULT_HAL_H
#define BN_MODMULT_HAL_H

#include <stdint.h>
#include <stdbool.h>

/* DMEM layout offsets (from ELF symbol table) */
#define BN_MODMULT_MODE_OFFSET   (0)
#define BN_MODMULT_NLIMBS_OFFSET (4)
#define BN_MODMULT_OP_A_OFFSET   (32)
#define BN_MODMULT_OP_B_OFFSET   (544)
#define BN_MODMULT_RESULT_OFFSET (1568)
#define BN_MODMULT_MODULUS_OFFSET (1056)

#define BN_MODMULT_IMEM_SIZE  (g_bn_modmult_imem_size)
#define BN_MODMULT_DMEM_SIZE  (g_bn_modmult_dmem_size)
#define BN_MODMULT_DMEM_TOTAL (2624)

/* External firmware data */
extern const uint8_t g_bn_modmult_imem[];
extern const uint32_t g_bn_modmult_imem_size;
extern const uint8_t g_bn_modmult_dmem[];
extern const uint32_t g_bn_modmult_dmem_size;


/* API */
bool HAL_OTBN_MODMULT_Polling(const uint32_t *op_a, const uint32_t *op_b,
                              const uint32_t *modulus, uint32_t nlimbs, uint32_t *result);

#endif /* BN_MODMULT_HAL_H */
