#ifndef LS_HAL_OTBN_H_
#define LS_HAL_OTBN_H_
#include "reg_otbn_type.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "HAL_def.h"
#include "common.h"
#ifdef __cplusplus
extern "C" {
#endif

#define HARDENED_BOOL_TRUE 0x739
#define HARDENED_BOOL_FALSE 0x1d4

enum HAL_OTBN_StatusTypeDef
{  
    HAL_OTBN_STATUS_IDLE    = 0x0,
    HAL_TBN_STATUS_BUSY_EXECUTE,
    HAL_OTBN_STATUS_SEC_WIPE_DMEM,
    HAL_OTBN_STATUS_SEC_WIPE_IMEM,
    HAL_OTBN_STATUS_SEC_WIPE_INT,
    HAL_OTBN_STATUS_LOCKED  = 0xff,
};

enum HAL_OTBN_CMD
{
    HAL_OTBN_CMD_EXECUTE            = 0xd8,
    HAL_OTBN_CMD_SEC_WIPE_DMEM      = 0xc3,
    HAL_OTBN_CMD_SEC_WIPE_IMEM      = 0x1e,
};

/* The encryption algorithm library supported by otbn*/
typedef enum{
    OTBN_UNUSED = 0,
    OTBN_SHA256,
    OBTN_SHA384,
    OTBN_SHA512,
    OTBN_SM3,
    OTBN_ECDSA_P256,
    OTBN_ECDSA_P384,
    OTBN_SM2,
}ls_otbn_fireware_t;

void HAL_OTBN_Init(void);

void HAL_OTBN_CMD_Write_Polling(enum HAL_OTBN_CMD cmd);

void HAL_OTBN_CMD_Write_IT(enum HAL_OTBN_CMD cmd, void(* func)(void *), void *param);

void HAL_OTBN_INTR_Test(bool enable);

void HAL_OTBN_INTR_EN(bool enable);

bool HAL_OTBN_In_Idle_State(void);

uint32_t HAL_OTBN_Error_Bit_Get(void);

uint32_t HAL_OTBN_Checksum_Get(void);

void HAL_OTBN_Checksum_Clear(void);

HAL_StatusTypeDef HAL_OTBN_IMEM_Write(uint32_t offset, uint32_t *src, uint32_t size);

HAL_StatusTypeDef HAL_OTBN_IMEM_Read(uint32_t offset, uint32_t *dst, uint32_t size);

HAL_StatusTypeDef HAL_OTBN_DMEM_Write(uint32_t offset, uint32_t *src, uint32_t size);

HAL_StatusTypeDef HAL_OTBN_DMEM_Read(uint32_t offset, uint32_t *dst, uint32_t size);

HAL_StatusTypeDef HAL_OTBN_DMEM_Set(uint32_t offset, uint32_t data, uint32_t size);

void HAL_OTBN_IRQHandler();

#ifdef __cplusplus
}
#endif
#endif