#ifndef LS_HAL_OTBN_H_
#define LS_HAL_OTBN_H_
#include <stdbool.h>
#include <stdint.h>
#include "HAL_def.h"
#ifdef __cplusplus
extern "C" {
#endif

#define HARDENED_BOOL_TRUE 0x739
#define HARDENED_BOOL_FALSE 0x1d4

extern const char _p256_verify_text[4040];

enum OTBN_STATUS
{  
    OTBN_STATUS_IDLE    = 0x0,
    OTBN_STATUS_BUSY_EXECUTE,
    OTBN_STATUS_SEC_WIPE_DMEM,
    OTBN_STATUS_SEC_WIPE_IMEM,
    OTBN_STATUS_SEC_WIPE_INT,
    OTBN_STATUS_LOCKED  = 0xff,
};

enum OTBN_CMD
{
    OTBN_CMD_EXECUTE            = 0xd8,
    OTBN_CMD_SEC_WIPE_DMEM      = 0xc3,
    OTBN_CMD_SEC_WIPE_IMEM      = 0x1e,
};

void HAL_OTBN_Init(void);

void HAL_OTBN_CMD_Write_Polling(enum OTBN_CMD cmd);

void HAL_OTBN_INTR_Test(bool enable);

void HAL_OTBN_INTR_EN(bool enable);

HAL_StatusTypeDef HAL_OTBN_IMEM_Write(uint32_t offset, uint32_t *src, uint32_t size);

HAL_StatusTypeDef HAL_OTBN_IMEM_Read(uint32_t offset, uint32_t *dst, uint32_t size);

HAL_StatusTypeDef HAL_OTBN_DMEM_Write(uint32_t offset, uint32_t *src, uint32_t size);

HAL_StatusTypeDef HAL_OTBN_DMEM_Read(uint32_t offset, uint32_t *dst, uint32_t size);

void HAL_OTBN_CpltCallback(void);

void HAL_OTBN_IRQHandler();

struct OTBN_P256_Verify_Param
{
    uint32_t msg[8];
    uint32_t r[8];  /* signature R */
    uint32_t s[8];  /* signature S */
    uint32_t x[8];  /* public key x-coordinate */
    uint32_t y[8];  /* public key y-coordinate */
    uint32_t x_r[8];/* signature verification result x_r */
};

bool HAL_OTBN_P256_Verify(struct OTBN_P256_Verify_Param *verify_param);
#ifdef __cplusplus
}
#endif
#endif