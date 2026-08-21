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
#define OTBN_FIRMWARE_UNUSED         0
#define OTBN_FIRMWARE_SHA256         1
#define OTBN_FIRMWARE_SHA384         2
#define OTBN_FIRMWARE_SHA512         3
#define OTBN_FIRMWARE_SM3            4
#define OTBN_FIRMWARE_ECDSA_P256     5
#define OTBN_FIRMWARE_ECDSA_P384     6
#define OTBN_FIRMWARE_SM2            7


void HAL_OTBN_Init(void);

/**
 * @brief Execute OTBN command in polling mode with a default 20 s timeout.
 * @param cmd OTBN command to execute
 * @note  Use HAL_OTBN_CMD_Write_Polling_Timeout() for a custom timeout.
 */
void HAL_OTBN_CMD_Write_Polling(enum HAL_OTBN_CMD cmd);

/**
 * @brief Execute OTBN command with timeout in polling mode.
 * @param cmd       OTBN command to execute
 * @param timeout_ms Timeout in milliseconds, 0 means no timeout (wait forever)
 * @return HAL_OK on success, HAL_BUSY if the engine is already running
 *         a job (e.g. a previously submitted IT job), HAL_TIMEOUT if
 *         the execution did not finish within the timeout
 */
HAL_StatusTypeDef HAL_OTBN_CMD_Write_Polling_Timeout(enum HAL_OTBN_CMD cmd, uint32_t timeout_ms);

/**
 * @brief Execute OTBN command in interrupt mode.
 *
 * OTBN is a single engine: operations cannot be interleaved (each job
 * reprograms IMEM/DMEM), so a submit while the engine is still running
 * is rejected.  On success the completion interrupt invokes func(param)
 * after the engine has returned to IDLE, so func may safely DMEM_Read
 * the result and submit the next job.
 * @param cmd    OTBN command to execute
 * @param func   Completion callback (may be NULL for fire-and-forget)
 * @param param  Callback parameter
 * @return HAL_OK on success, HAL_BUSY if the engine is still running
 *         a previous job (nothing is submitted)
 *
 * @note  Data atomicity: OTBN has a single shared IMEM/DMEM and no
 *        per-request state storage.  The busy guard above guarantees
 *        that one job runs to completion before another can be
 *        submitted, so a job's inputs are never overwritten while it
 *        is executing.  However the HAL does NOT preserve DMEM/IMEM
 *        contents across calls: once a job completes the engine is
 *        idle and any later call (hash update/final, ECC, ...) freely
 *        overwrites the memory.  Multi-step flows (e.g. hash Update
 *        before Final) must not interleave other OTBN operations.
 */
HAL_StatusTypeDef HAL_OTBN_CMD_Write_IT(enum HAL_OTBN_CMD cmd, void(* func)(void *), void *param);

void HAL_OTBN_INTR_Test(bool enable);

void HAL_OTBN_INTR_EN(bool enable);

bool HAL_OTBN_In_Idle_State(void);

/* Whether an OTBN job is currently submitted/executing (software busy
 * flag).  OTBN is a single engine: callers must check this (together
 * with HAL_OTBN_In_Idle_State()) before programming IMEM/DMEM or
 * submitting a new command, because the STATUS register only reflects
 * the engine a few cycles after CMD is written, and a submit that
 * slips through that window would overwrite the active job's IMEM/DMEM. */
bool HAL_OTBN_Is_Busy(void);

/* Force-recover the OTBN engine after a stuck job or a polling timeout
 * (HAL_TIMEOUT clears the busy flag, but the engine itself may still be
 * running).  Pulse-resets the peripheral through the SoC reset
 * controller; any in-flight job is lost and DMEM/IMEM contents are
 * undefined afterwards -- reprogram the firmware before the next submit.
 * Clears the busy flag and the pending DONE state. */
void HAL_OTBN_Reset(void);

uint32_t HAL_OTBN_Error_Bit_Get(void);

uint32_t HAL_OTBN_Checksum_Get(void);

void HAL_OTBN_Checksum_Clear(void);

HAL_StatusTypeDef HAL_OTBN_IMEM_Write(uint32_t offset, const uint32_t *src, uint32_t size);

HAL_StatusTypeDef HAL_OTBN_IMEM_Read(uint32_t offset, uint32_t *dst, uint32_t size);

HAL_StatusTypeDef HAL_OTBN_DMEM_Write(uint32_t offset, const uint32_t *src, uint32_t size);

HAL_StatusTypeDef HAL_OTBN_DMEM_Read(uint32_t offset, uint32_t *dst, uint32_t size);

HAL_StatusTypeDef HAL_OTBN_DMEM_Set(uint32_t offset, uint32_t data, uint32_t size);

void HAL_OTBN_IRQHandler();

#ifdef __cplusplus
}
#endif
#endif