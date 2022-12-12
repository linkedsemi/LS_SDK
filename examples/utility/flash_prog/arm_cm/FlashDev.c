/**************************************************************************//**
 * @file     FlashDev.c
 * @brief    Flash Device Description for New Device Flash
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
 
#include "FlashOS.h"        // FlashOS Structures
#include "reg_base_addr.h"
#if defined(LE501X) 
#define LS_FLASH_DEV_NAME "LE501X SPI NOR FLASH"
#elif defined(SAGI)
#define LS_FLASH_DEV_NAME "SAGI SPI NOR FLASH"
#elif defined(LM3050)
#define LS_FLASH_DEV_NAME "LM3050 SPI NOR FLASH"
#endif

struct FlashDevice const FlashDevice  __attribute__ ((section ("DevDscr")))  =  {
   .Vers = FLASH_DRV_VERS,             // Driver Version, do not modify!
   .DevName = LS_FLASH_DEV_NAME,   // Device Name 
   .DevType = EXTSPI,                     // Device Type
   .DevAdr = LSQSPI_MEM_MAP_BASE_ADDR,                 // Device Start Address
   .szDev = 0x00100000,                 // Device Size in Bytes (1MB)
   .szPage = 256,                       // Programming Page Size
   .Res = 0,                          // Reserved, must be 0
   .valEmpty = 0xFF,                       // Initial Content of Erased Memory
   .toProg = 500,                        // Program Page Timeout 500 mSec
   .toErase = 3000,                       // Erase Sector Timeout 3000 mSec
// Specify Size and Address of Sectors
    .sectors = {
        {0x001000, 0},                // sectors are 4 KB
        {SECTOR_END}
    }
};
