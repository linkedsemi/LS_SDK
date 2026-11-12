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

/* ============================================================
 * Standard return code for the OTBN external interfaces.
 *
 * ls_otbn_status_t replaces the legacy bool verify/validpoint
 * predicates and the application-level uint32_t 0/1 results: every
 * failure path reports a specific code so the caller knows WHY the
 * function returned.  The high nibble encodes the category, so
 * ls_otbn_status_is_error() is a single bit test:
 *   0x0_  result   -- the operation completed with a definite answer.
 *        LS_OTBN_OK is success; LS_OTBN_VERIFY_INVALID /
 *        LS_OTBN_POINT_NOT_ON_CURVE are legitimate negative RESULTS
 *        (signature invalid / point off curve), not execution errors.
 *   0x1_  input validation error  -- bad pointer/curve, scalar or
 *        r/s outside [1, n-1].
 *   0x2_  execution error  -- engine busy, polling timeout, or a
 *        hardware error (ERR_BITS / IMEM/DMEM integrity).
 *
 * Distinct from enum HAL_OTBN_StatusTypeDef (HAL_OTBN_STATUS_IDLE/...),
 * which is the OTBN engine's hardware state, not a return code.
 * ============================================================ */
typedef enum
{
    /* Result (operation completed with a definite answer, not an error) */
    LS_OTBN_OK                 = 0x00U,  /* success: signature valid / point on curve / result written */
    LS_OTBN_VERIFY_INVALID     = 0x01U,  /* signature verification failed (firmware returned FALSE) */
    LS_OTBN_POINT_NOT_ON_CURVE = 0x02U,  /* point is not on the curve */

    /* Input validation errors */
    LS_OTBN_INVALID_PARAM      = 0x10U,  /* NULL pointer / invalid curve id */
    LS_OTBN_SCALAR_RANGE       = 0x11U,  /* private key / nonce d,k outside [1, n-1] */
    LS_OTBN_RS_RANGE           = 0x12U,  /* signature r,s outside [1, n-1] */

    /* Execution errors */
    LS_OTBN_BUSY               = 0x20U,  /* OTBN engine busy / reentrant submit */
    LS_OTBN_TIMEOUT            = 0x21U,  /* polling timeout */
    LS_OTBN_ENGINE             = 0x22U,  /* ERR_BITS / IMEM/DMEM integrity (single code, bits not expanded) */
} ls_otbn_status_t;

/* True for any error (input validation / execution), i.e. not a result code. */
static inline bool ls_otbn_status_is_error(ls_otbn_status_t s)
{
    return ((unsigned)s & 0xF0U) != 0U;
}

/* Map the transport-layer HAL_StatusTypeDef to ls_otbn_status_t
 * (used at the SDK / application-layer boundary). */
static inline ls_otbn_status_t ls_otbn_status_from_hal(HAL_StatusTypeDef s)
{
    switch (s) {
    case HAL_OK:      return LS_OTBN_OK;
    case HAL_BUSY:    return LS_OTBN_BUSY;
    case HAL_TIMEOUT: return LS_OTBN_TIMEOUT;
    default:          return LS_OTBN_ENGINE;
    }
}

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