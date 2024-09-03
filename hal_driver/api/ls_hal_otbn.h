#ifndef LS_HAL_OTBN_H_
#define LS_HAL_OTBN_H_
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

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

bool HAL_OTBN_WRITE_IMEM(uint32_t offset, uint32_t *src, uint32_t size);

bool HAL_OTBN_WRITE_DMEM(uint32_t offset, uint32_t *src, uint32_t size);

void HAL_OTBN_CpltCallback(void);

void HAL_OTBN_IRQHandler();

#ifdef __cplusplus
}
#endif
#endif