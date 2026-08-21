#include "ls_hal_otbn.h"
#include "ls_msp_otbn.h"
#include "field_manipulate.h"
#include "core_rv32.h"
#include "reg_sysc_sec_cpu.h"
#include <stdio.h>
#define OTBN_IMEM_OFFSET_PTR(offset) (uint32_t *)(OTBN_IMEM_ADDR+offset)
#define OTBN_DMEM_OFFSET_PTR(offset) (uint32_t *)(OTBN_DMEM_ADDR+offset)

/* Software busy flag.  The hardware STATUS register only reflects
 * "running" a few cycles after CMD is written, so a submit that closely
 * follows another one could slip through a STATUS-only check and
 * corrupt the active job.  The flag is set at submit time (no delay
 * window) and cleared by the completion interrupt handler. */
static volatile bool s_engine_busy = false;

void HAL_OTBN_Init(void)
{
    s_engine_busy = false;
    HAL_LSOTBN_MSP_Init();
    /* MSP_Init pulse-resets the engine; clear any stale DONE state so a
     * leftover interrupt cannot fire the previous job's callback. */
    if (LSOTBN->INTR_STATE)
        LSOTBN->INTR_STATE = OTBN_INTR_STATE_DONE_MASK;
    LSOTBN->INTR_ENABLE = 0;
}

/* Force-recover the OTBN engine after a stuck job.  The CMD register
 * has no ABORT/RESET command (EXECUTE / SEC_WIPE_DMEM / SEC_WIPE_IMEM
 * only), so recovery is a pulse reset of the peripheral through the SoC
 * clock/reset controller -- the same sequence MSP_Init performs.  Any
 * in-flight job is lost and DMEM/IMEM contents are undefined afterwards;
 * re-program the firmware before the next submit.  Clears the software
 * busy flag and the pending DONE state, so the engine is ready for a
 * fresh HAL_OTBN_Init()/submit sequence. */
void HAL_OTBN_Reset(void)
{
    s_engine_busy = false;
    if (LSOTBN->INTR_STATE)
        LSOTBN->INTR_STATE = OTBN_INTR_STATE_DONE_MASK;
    LSOTBN->INTR_ENABLE = 0;
    SYSC_SEC_CPU->PD_CPU_SRST[1] = SYSC_SEC_CPU_SRST_CLR_OTBN_MASK;
    SYSC_SEC_CPU->PD_CPU_SRST[1] = SYSC_SEC_CPU_SRST_SET_OTBN_MASK;
}

void HAL_OTBN_DeInit(void)
{
    HAL_LSOTBN_MSP_DeInit();
}

void HAL_OTBN_INTR_EN(bool enable)
{
    LSOTBN->INTR_ENABLE = enable;
}

void HAL_OTBN_INTR_Test(bool enable)
{
    LSOTBN->INTR_TEST = enable;
}

HAL_StatusTypeDef HAL_OTBN_IMEM_Write(uint32_t offset, const uint32_t *src, uint32_t size)
{
    /* A job may be submitted (busy flag) but the engine not yet visible
     * as busy in STATUS; refuse the overwrite either way. */
    if (s_engine_busy || LSOTBN->STATUS != HAL_OTBN_STATUS_IDLE)
        return HAL_BUSY;

    if (((offset + size) > OTBN_IMEM_SIZE) || (offset & 0x3) || (size & 0x3))
        return HAL_INVALIAD_PARAM;

    memcpy32(OTBN_IMEM_OFFSET_PTR(offset), src, size / 4);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_OTBN_DMEM_Set(uint32_t offset, uint32_t data, uint32_t size)
{
    if (s_engine_busy || LSOTBN->STATUS != HAL_OTBN_STATUS_IDLE)
        return HAL_BUSY;

    if (((offset + size) > OTBN_DMEM_SIZE) || (offset & 0x3) || (size & 0x3))
        return HAL_INVALIAD_PARAM;

    memset32(OTBN_DMEM_OFFSET_PTR(offset), data, size / 4);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_OTBN_IMEM_Read(uint32_t offset, uint32_t *dst, uint32_t size)
{
    if (LSOTBN->STATUS != HAL_OTBN_STATUS_IDLE)
        return HAL_BUSY;

    if (((offset + size) > OTBN_IMEM_SIZE) || (offset & 0x3) || (size & 0x3))
        return HAL_INVALIAD_PARAM;

    memcpy32(dst, OTBN_IMEM_OFFSET_PTR(offset), size / 4);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_OTBN_DMEM_Write(uint32_t offset, const uint32_t *src, uint32_t size)
{
    if (s_engine_busy || LSOTBN->STATUS != HAL_OTBN_STATUS_IDLE)
    {
        // printf("otbn is busy\r\n");
        return HAL_BUSY;
    }

    if (((offset + size) > OTBN_DMEM_SIZE)){
        // printf("otbn: memory overflow,size = 0x%x\r\n",size);
        return HAL_INVALIAD_PARAM;
    }

    if((offset & 0x3) || (size & 0x3))
    {
        // printf("otbn: Input parameter alignment error,size = 0x%x\r\n",size);
        return HAL_INVALIAD_PARAM;
    }

    memcpy32(OTBN_DMEM_OFFSET_PTR(offset), src, size / 4);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_OTBN_DMEM_Read(uint32_t offset, uint32_t *dst, uint32_t size)
{
    if (LSOTBN->STATUS != HAL_OTBN_STATUS_IDLE)
        return HAL_BUSY;

    if (((offset + size) > OTBN_DMEM_SIZE) || (offset & 0x3) || (size & 0x3))
        return HAL_INVALIAD_PARAM;

    memcpy32(dst, OTBN_DMEM_OFFSET_PTR(offset), size / 4);
    return HAL_OK;
}

void HAL_OTBN_CMD_Write_Polling(enum HAL_OTBN_CMD cmd)
{
    /* Default timeout: 20 s */
    (void)HAL_OTBN_CMD_Write_Polling_Timeout(cmd, 20000);
}

HAL_StatusTypeDef HAL_OTBN_CMD_Write_Polling_Timeout(enum HAL_OTBN_CMD cmd, uint32_t timeout_ms)
{
    /* OTBN is a single engine: a polling job cannot be queued while the
     * engine is still executing (e.g. a previously submitted IT job).
     * Refuse instead of corrupting the running firmware. */
    if (s_engine_busy || LSOTBN->STATUS != HAL_OTBN_STATUS_IDLE)
        return HAL_BUSY;

    /* Guard the run: an interrupt handler that submits a new job after
     * this point must be refused until the engine finishes. */
    s_engine_busy = true;

    if (LSOTBN->INTR_STATE)
        LSOTBN->INTR_STATE = OTBN_INTR_STATE_DONE_MASK;
    REG_FIELD_WR(LSOTBN->INTR_ENABLE, OTBN_INTR_ENABLE_EN, 0);
    LSOTBN->CMD = cmd;

    /* CORET->MTIME is a free-running 64-bit counter ticking at HCLK
     * (600 MHz). Measure elapsed time directly so the timeout does not
     * depend on the SysTick interrupt firing. */
    uint64_t start = 0;
    uint64_t timeout_cycles = 0;
    if (timeout_ms != 0) {
        start = CORET->MTIME;
        timeout_cycles = (uint64_t)timeout_ms * 600000ULL;
    }

    /* The DONE interrupt may fire before the OTBN has committed its results
     * to DMEM and returned to IDLE, so wait for both. */
    while (!LSOTBN->INTR_STATE || (LSOTBN->STATUS != HAL_OTBN_STATUS_IDLE)) {
        if (timeout_ms != 0 && (CORET->MTIME - start) >= timeout_cycles) {
            /* Timeout: the engine did not finish in time.  Clear the
             * software busy flag instead of leaving it set forever --
             * polling disabled the DONE interrupt, so nothing would ever
             * clear it.  While the engine is still running every submit
             * is refused by the STATUS != IDLE check, so the engine
             * cannot be corrupted; HAL_OTBN_Reset() recovers a stuck
             * engine.  INTR_STATE is cleared so the late DONE interrupt
             * is treated as spurious by the IRQ handler (busy flag
             * gate). */
            LSOTBN->INTR_STATE = OTBN_INTR_STATE_DONE_MASK;
            s_engine_busy = false;
            return HAL_TIMEOUT;
        }
    }

    LSOTBN->INTR_STATE = OTBN_INTR_STATE_DONE_MASK;
    s_engine_busy = false;
    return HAL_OK;
}

bool HAL_OTBN_In_Idle_State(void)
{
    if(LSOTBN->STATUS != 0)
    {
        return false;
    }

    return true;
}

uint32_t HAL_OTBN_Error_Bit_Get(void)
{
    uint32_t err_bit = LSOTBN->ERR_BITS;
    LSOTBN->ERR_BITS = 0;
    return err_bit;
}

uint32_t HAL_OTBN_Checksum_Get(void)
{
    uint32_t check_sum = LSOTBN->LOAD_CHECKSUM;
    return check_sum;
}

void HAL_OTBN_Checksum_Clear(void)
{
    LSOTBN->LOAD_CHECKSUM = 0;
}

static void (*callback_func)(void *);
static void *callback_param;

/* Software busy flag state.  See ls_hal_otbn.h for usage. */
bool HAL_OTBN_Is_Busy(void) { return s_engine_busy; }

HAL_StatusTypeDef HAL_OTBN_CMD_Write_IT(enum HAL_OTBN_CMD cmd, void(* func)(void *), void *param)
{
    /* OTBN is a single engine and there is no way to interleave jobs
     * (unlike streaming engines such as hash): each operation must
     * reprogram IMEM/DMEM, so a second submit while the engine is
     * still running would corrupt the active job.  Refuse with HAL_BUSY
     * and leave the running job untouched; callers decide how to
     * surface the failure (return an error, or complete synchronously). */
    if (s_engine_busy || LSOTBN->STATUS != HAL_OTBN_STATUS_IDLE)
        return HAL_BUSY;

    if (LSOTBN->INTR_STATE)
        LSOTBN->INTR_STATE = OTBN_INTR_STATE_DONE_MASK;
    callback_func = func;
    callback_param = param;
    LSOTBN->INTR_ENABLE = OTBN_INTR_ENABLE_EN_MASK;
    s_engine_busy = true;
    LSOTBN->CMD = cmd;
    return HAL_OK;
}

void HAL_OTBN_IRQHandler()
{
    if (LSOTBN->INTR_STATE)
    {
        LSOTBN->INTR_STATE = OTBN_INTR_STATE_DONE_MASK;
        /* Only complete a job that was actually submitted (busy flag
         * set).  A spurious DONE -- e.g. the late interrupt after a
         * polling timeout already cleaned up, or one left over from a
         * HAL_OTBN_Reset() -- must not fire the previous job's callback
         * again with stale data. */
        if (!s_engine_busy)
            return;
        /* The DONE flag may assert before OTBN has committed its results
         * to DMEM and returned to IDLE (see the polling path).  Wait
         * (bounded) so callbacks can safely DMEM_Read the result. */
        uint32_t spins = 0;
        while (LSOTBN->STATUS != HAL_OTBN_STATUS_IDLE && spins < 100000)
            spins++;
        /* Clear the busy flag before the callback so a chained submit
         * from the callback is accepted. */
        s_engine_busy = false;
        if(callback_func)
            callback_func(callback_param);
    }
}
