#ifndef LS_HAL_SHA512_H_
#define LS_HAL_SHA512_H_
#include "ls_msp_sha512.h"
#include "HAL_def.h"
#include <stdbool.h>

#define LS_SHA512_BLOCK_SIZE           (0x80)

void HAL_SHA512_SHA512_Init();
void HAL_SHA384_SHA384_Init();
void HAL_SHA512_SHA512_Update(uint32_t *addr, uint32_t length);
void HAL_SHA512_SHA512_Final(uint8_t *digest);

HAL_StatusTypeDef HAL_SHA512_Init(void);

HAL_StatusTypeDef HAL_SHA512_DeInit(void);

void SHA512_IRQHandler();

#endif