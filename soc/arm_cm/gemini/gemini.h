/**************************************************************************//**
 * @file     ARMCM4_FP.h
 * @brief    CMSIS Core Peripheral Access Layer Header File for
 *           ARMCM4 Device (configured for CM4 with FPU)
 * @version  V5.3.1
 * @date     09. July 2018
 ******************************************************************************/
/*
 * Copyright (c) 2009-2018 Arm Limited. All rights reserved.
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

#ifndef GEMINI_H
#define GEMINI_H

#ifdef __cplusplus
extern "C" {
#endif


/* -------------------------  Interrupt Number Definition  ------------------------ */

typedef enum IRQn
{
/* -------------------  Processor Exceptions Numbers  ----------------------------- */
  NonMaskableInt_IRQn           = -14,     /*  2 Non Maskable Interrupt */
  HardFault_IRQn                = -13,     /*  3 HardFault Interrupt */
  MemoryManagement_IRQn         = -12,     /*  4 Memory Management Interrupt */
  BusFault_IRQn                 = -11,     /*  5 Bus Fault Interrupt */
  UsageFault_IRQn               = -10,     /*  6 Usage Fault Interrupt */
  SVCall_IRQn                   =  -5,     /* 11 SV Call Interrupt */
  DebugMonitor_IRQn             =  -4,     /* 12 Debug Monitor Interrupt */
  PendSV_IRQn                   =  -2,     /* 14 Pend SV Interrupt */
  SysTick_IRQn                  =  -1,     /* 15 System Tick Interrupt */

/* -------------------  Processor Interrupt Numbers  ------------------------------ */
  RTC_IRQn               =   0,
  IWDG_IRQn               =   1,
  LSTIM_IRQn               =   2,
  EXT_IRQn               =   3,
  LVD33_IRQn               =   4,
  COMP_IRQn               =   5,
  FPU_IRQn               =   6,
  USB_IRQn               =   7,
  QSPI_IRQn               =   8,
  CACHE_IRQn               =   9,
  DMAC_IRQn                =   10,
  CAN_IRQn                 =   11,
  CRYPT_IRQn               =   12,
  ECC_IRQn                 =   13,
  SHA_IRQn                 =   14,
  SM4_IRQn                 =   15,
  BSTIM_IRQn               =   16,
  GPTIMA1_IRQn             =   17,
  GPTIMB1_IRQn             =   18,
  GPTIMC1_IRQn             =   19,
  ADTIM1_IRQn              =   20,
  ADTIM2_IRQn              =   21,
  I2C1_IRQn                =   22,
  I2C2_IRQn                =   23,
  I2C3_IRQn                =   24,
  UART1_IRQn               =   25,
  UART2_IRQn               =   26,
  UART3_IRQn               =   27,
  UART4_IRQn               =   28,
  UART5_IRQn               =   29,
  SPI1_IRQn                =   30,
  SPI2_IRQn                =   31,
  SPI3_IRQn                =   32,
  ADC0_IRQn                =   33,
  PDM_IRQn                 =   34,
  GPIO_IRQn                =   35,
  WWDG_IRQn                =   36,
  TK_IRQn                  =   37,
  TRNG_IRQn                =   38,
  ADC1_IRQn                =   39,
  HSE_IRQn                 =   40,
  SFT0_IRQn                =   41,
  SFT1_IRQn                =   42,
  IRQn_Max,
} IRQn_Type;


/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */

/* -------  Start of section using anonymous unions and disabling warnings  ------- */
#if   defined (__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined (__ICCARM__)
  #pragma language=extended
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wc11-extensions"
  #pragma clang diagnostic ignored "-Wreserved-id-macro"
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning 586
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif


/* --------  Configuration of Core Peripherals  ----------------------------------- */
#define __CM4_REV                 0x0001U   /* Core revision r0p1 */
#define __MPU_PRESENT             1U        /* MPU present */
#define __VTOR_PRESENT            1U        /* VTOR present */
#define __NVIC_PRIO_BITS          3U        /* Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig    0U        /* Set to 1 if different SysTick Config is used */
#define __FPU_PRESENT             1U        /* FPU present */

#include "core_cm4.h"                       /* Processor and core peripherals */
//#include "system_ARMCM4.h"                  /* System Header */


/* --------  End of section using anonymous unions and disabling warnings  -------- */
#if   defined (__CC_ARM)
  #pragma pop
#elif defined (__ICCARM__)
  /* leave anonymous unions enabled */
#elif (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
  #pragma clang diagnostic pop
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning restore
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif


#ifdef __cplusplus
}
#endif

#endif  /* ARMCM4_FP_H */
