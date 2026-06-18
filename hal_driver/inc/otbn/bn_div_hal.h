/* Auto-generated HAL for bn_div */
#ifndef BN_DIV_HAL_H
#define BN_DIV_HAL_H

#include <stdint.h>
#include <stdbool.h>

/* DMEM layout offsets (from ELF symbol table) */
#define BN_DIV_MODE_OFFSET       (0)
#define BN_DIV_NLIMBS_OFFSET     (4)
#define BN_DIV_OP_A_OFFSET       (32)
#define BN_DIV_OP_B_OFFSET       (544)
#define BN_DIV_RESULT_OFFSET     (1056)

#define BN_DIV_IMEM_SIZE  (g_bn_div_imem_size)
#define BN_DIV_DMEM_SIZE  (g_bn_div_dmem_size)
#define BN_DIV_DMEM_TOTAL (1568)

/* External firmware data */
extern const uint8_t g_bn_div_imem[];
extern const uint32_t g_bn_div_imem_size;
extern const uint8_t g_bn_div_dmem[];
extern const uint32_t g_bn_div_dmem_size;


/* API */
bool HAL_OTBN_DIV_Polling(const uint32_t *dividend, const uint32_t *divisor,
                              uint32_t nlimbs, uint32_t *quotient, uint32_t *remainder);

#endif /* BN_DIV_HAL_H */
