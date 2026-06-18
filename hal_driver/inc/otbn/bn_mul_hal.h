/* Auto-generated HAL for bn_mul */
#ifndef BN_MUL_HAL_H
#define BN_MUL_HAL_H

#include <stdint.h>
#include <stdbool.h>

/* DMEM layout offsets (from ELF symbol table) */
#define BN_MUL_MODE_OFFSET       (0)
#define BN_MUL_NLIMBS_OFFSET     (4)
#define BN_MUL_OP_A_OFFSET       (32)
#define BN_MUL_OP_B_OFFSET       (544)
#define BN_MUL_RESULT_OFFSET     (1056)

#define BN_MUL_IMEM_SIZE  (g_bn_mul_imem_size)
#define BN_MUL_DMEM_SIZE  (g_bn_mul_dmem_size)
#define BN_MUL_DMEM_TOTAL (2080)

/* External firmware data */
extern const uint8_t g_bn_mul_imem[];
extern const uint32_t g_bn_mul_imem_size;
extern const uint8_t g_bn_mul_dmem[];
extern const uint32_t g_bn_mul_dmem_size;


/* API */
bool HAL_OTBN_MUL_Polling(const uint32_t *op_a, const uint32_t *op_b,
                              uint32_t nlimbs, uint32_t *result);

#endif /* BN_MUL_HAL_H */
