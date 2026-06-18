/* Auto-generated HAL for bn_gcd */
#ifndef BN_GCD_HAL_H
#define BN_GCD_HAL_H

#include <stdint.h>
#include <stdbool.h>

/* DMEM layout offsets (from ELF symbol table) */
#define BN_GCD_MODE_OFFSET       (0)
#define BN_GCD_NLIMBS_OFFSET     (4)
#define BN_GCD_OP_A_OFFSET       (32)
#define BN_GCD_OP_B_OFFSET       (544)

#define BN_GCD_IMEM_SIZE  (g_bn_gcd_imem_size)
#define BN_GCD_DMEM_SIZE  (g_bn_gcd_dmem_size)
#define BN_GCD_DMEM_TOTAL (1056)

/* External firmware data */
extern const uint8_t g_bn_gcd_imem[];
extern const uint32_t g_bn_gcd_imem_size;
extern const uint8_t g_bn_gcd_dmem[];
extern const uint32_t g_bn_gcd_dmem_size;


/* API */
bool HAL_OTBN_GCD_Polling(const uint32_t *op_a, const uint32_t *op_b,
                              uint32_t nlimbs, uint32_t *result);

#endif /* BN_GCD_HAL_H */
