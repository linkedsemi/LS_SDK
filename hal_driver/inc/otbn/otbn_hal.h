/* Copyright lowRISC contributors (OpenTitan project). */
/* Licensed under the Apache License, Version 2.0, see LICENSE for details. */
/* SPDX-License-Identifier: Apache-2.0 */

/**
 * @file otbn_hal.h
 * @brief Unified OTBN HAL interface for all ls_otbn modules.
 *
 * This header defines the common HAL functions that must be implemented
 * by the target platform to run any OTBN firmware module.
 */

#ifndef OTBN_HAL_H_
#define OTBN_HAL_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void HAL_OTBN_IMEM_Write(uint32_t offset, const uint32_t *data,
                                uint32_t len);
extern void HAL_OTBN_DMEM_Write(uint32_t offset, const uint32_t *data,
                                uint32_t len);
extern void HAL_OTBN_DMEM_Read(uint32_t offset, uint32_t *data, uint32_t len);
extern void HAL_OTBN_DMEM_Set(uint32_t offset, uint8_t val, uint32_t len);
extern void HAL_OTBN_CMD_Write_Polling(uint32_t cmd);

#ifdef __cplusplus
}
#endif

#endif /* OTBN_HAL_H_ */
