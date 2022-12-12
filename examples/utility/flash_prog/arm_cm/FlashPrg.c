/**************************************************************************//**
 * @file     FlashPrg.c
 * @brief    Flash Programming Functions adapted for New Device Flash
 * @version  V1.0.0
 * @date     10. January 2018
 ******************************************************************************/
/*
 * Copyright (c) 2010-2018 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <stdbool.h> 
#include "FlashOS.h"        // FlashOS Structures
#include "ls_hal_flash.h"
#include "reg_base_addr.h"
#include "cpu.h"
#include "platform.h"
#include "ls_soc_gpio.h"

/* 
   Mandatory Flash Programming Functions (Called by FlashOS):
                int Init        (unsigned long adr,   // Initialize Flash
                                 unsigned long clk,
                                 unsigned long fnc);
                int UnInit      (unsigned long fnc);  // De-initialize Flash
                int EraseSector (unsigned long adr);  // Erase Sector Function
                int ProgramPage (unsigned long adr,   // Program Page Function
                                 unsigned long sz,
                                 unsigned char *buf);

   Optional  Flash Programming Functions (Called by FlashOS):
                int BlankCheck  (unsigned long adr,   // Blank Check
                                 unsigned long sz,
                                 unsigned char pat);
                int EraseChip   (void);               // Erase complete Device
      unsigned long Verify      (unsigned long adr,   // Verify Function
                                 unsigned long sz,
                                 unsigned char *buf);

       - BlanckCheck  is necessary if Flash space is not mapped into CPU memory space
       - Verify       is necessary if Flash space is not mapped into CPU memory space
       - if EraseChip is not provided than EraseSector for all sectors is called
*/

uint32_t PRGDATA_StartMarker;
/*
 *  Initialize Flash Programming Functions
 *    Parameter:      adr:  Device Base Address
 *                    clk:  Clock Frequency (Hz)
 *                    fnc:  Function Code (1 - Erase, 2 - Program, 3 - Verify)
 *    Return Value:   0 - OK,  1 - Failed
 */
#ifdef LM3050
static void io_pull_up_cfg()
{
    io_pull_write(PD14,IO_PULL_UP);
    io_pull_write(PD15,IO_PULL_UP);
}
__attribute__((long_call)) void pinmux_hal_flash_quad_init(void);
#else
static void io_pull_up_cfg(){}
#endif

int Init (unsigned long adr, unsigned long clk, unsigned long fnc) {
    disable_global_irq();
    //clk_switch();
    io_pull_up_cfg();
    pinmux_hal_flash_quad_init();
    hal_flash_drv_var_init(false,false);
    hal_flash_dual_mode_set(false);
    hal_flash_init();
    hal_flash_xip_mode_reset();
    hal_flash_software_reset();
    DELAY_US(500);
    hal_flash_release_from_deep_power_down();
    DELAY_US(100);
    hal_flash_qe_status_read_and_set();
    hal_flash_xip_start();
    return (0);                                  // Finished without Errors
}


/*
 *  De-Initialize Flash Programming Functions
 *    Parameter:      fnc:  Function Code (1 - Erase, 2 - Program, 3 - Verify)
 *    Return Value:   0 - OK,  1 - Failed
 */

int UnInit (unsigned long fnc) {
    disable_global_irq();
    hal_flash_xip_stop();
    return (0);                                  // Finished without Errors
}


/*
 *  Erase complete Flash Memory
 *    Return Value:   0 - OK,  1 - Failed
 */

int EraseChip (void) {
    disable_global_irq();
    hal_flash_chip_erase();
    return (0);                                  // Finished without Errors
}


/*
 *  Erase Sector in Flash Memory
 *    Parameter:      adr:  Sector Address
 *    Return Value:   0 - OK,  1 - Failed
 */

int EraseSector (unsigned long adr) {
    disable_global_irq();
    hal_flash_sector_erase(adr - LSQSPI_MEM_MAP_BASE_ADDR);
    return (0);                                  // Finished without Errors
}


/*
 *  Program Page in Flash Memory
 *    Parameter:      adr:  Page Start Address
 *                    sz:   Page Size
 *                    buf:  Page Data
 *    Return Value:   0 - OK,  1 - Failed
 */

int ProgramPage (unsigned long adr, unsigned long sz, unsigned char *buf) {
    disable_global_irq();
    hal_flash_page_program(adr - LSQSPI_MEM_MAP_BASE_ADDR, buf, sz);
    return (0);                                  // Finished without Errors
}
