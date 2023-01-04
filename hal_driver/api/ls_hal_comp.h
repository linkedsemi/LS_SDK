#ifndef LS_HAL_COMP_H_
#define LS_HAL_COMP_H_
#include <stdint.h>
#include <stdbool.h>
#include "HAL_def.h"
#include "ls_msp_comp.h"

enum comp_speedmode
{
  LowSpeed                            = 0x1,
  MediumSpeed                         = 0x2,
  HighSpeed                           = 0x4,
};

enum comp_intr_edge
{
  COMP_EDGE_RISING                    = 0x1,
  COMP_EDGE_FALLING                   = 0x2,
  COMP_EDGE_BOTH                      = (COMP_EDGE_FALLING | COMP_EDGE_RISING),
};

enum comp_vrefsel
{
  VREFSEL_COMP1_PC01                  = 0x0,
  VREFSEL_COMP2_PC03                  = 0x0,
  VREFSEL_COMP3_PA03                  = 0x0,
  VREFSEL_COMP1_PC13                  = 0x1,
  VREFSEL_COMP2_PA02                  = 0x1,
  VREFSEL_COMP3_PA06                  = 0x1,
  VREFSEL_IOVIM2_RESERVED             = 0x2,
  VREFSEL_IOVIM3_RESERVED             = 0x3,
  VREFSEL_INTERNAL_REFERENCE_VOLTAGE  = 0x4,
  VREFSEL_DAC2                        = 0x5,
  VREFSEL_BANDGAP_1200mV              = 0x6,
  VREFSEL_GND                         = 0x7,
};

enum comp_vrefctl
{
  VREFCTL_300MV                       = 0x0,
  VREFCTL_600MV                       = 0x1,
  VREFCTL_900MV                       = 0x2,
  VREFCTL_1200MV                      = 0x3,
};

enum comp_input
{
  INPUT_COMP1_PC00                    = 0x0,
  INPUT_COMP2_PA00                    = 0x0,
  INPUT_COMP3_PA04                    = 0x0,
  INPUT_COMP1_PC02                    = 0x1,
  INPUT_COMP2_PA01                    = 0x1,
  INPUT_COMP3_PA05                    = 0x1,
  INPUT_COMP1_PC13                    = 0x2,
  INPUT_COMP2_PA02                    = 0x2,
  INPUT_COMP3_PA06                    = 0x2,
  INPUT_IOVIP3                        = 0x3,
};

enum comp_hysteresis
{
  HYS_HS_0MV                          = 0x0,
  HYS_MS_0MV                          = 0x0,
  HYS_LS_1P3MV                        = 0x0,
  HYS_HS_8P2MV                        = 0x1,
  HYS_MS_5P4MV                        = 0x1,
  HYS_LS_5P2MV                        = 0x1,
  HYS_HS_15P6MV                       = 0x2,
  HYS_MS_10P1MV                       = 0x2,
  HYS_LS_8P8MV                        = 0x2,
  HYS_HS_21P9MV                       = 0x3,
  HYS_MS_14P2MV                       = 0x3,
  HYS_LS_12MV                         = 0x3,
};

enum comp_flt_eanble
{
  COMP_FLT_ENABLE                     = 0x0,
  COMP_FLT_DISABLE_FLT                = 0x1,
};

typedef struct
{
  uint32_t
      comp_en : 1,        // COMP enable
      clk_mode : 3,       // COMP speed mode
      hysteresis : 2,     // COMP hysteresis select
                          // HS mode:0: 0mV     1: 8.2mV   2: 15.6mV   3: 21.9mV
                          // MS mode:0: 0mV     1: 5.4mV   2: 10.1mV   3: 14.2mV
                          // LS mode:0: 1.3mV   1: 5.2mV   2: 8.8mV    3: 12.0mV
      vrefctl : 2,        // COMP internal reference voltage select
                          // 0: 0.3V   1: 0.6V   2: 0.9V   3: 1.2V
      vrefsel : 3,        // COMP reference source select
                          // 0: IOVIM[0] COMP1: PC01 COMP2: PC03 COMP3: PA03
                          // 1: IOVIM[1] COMP1: PC13 COMP2: PA02 COMP3: PA06
                          // 2: IOVIM[2] ----
                          // 3: IOVIM[3] ----
                          // 4: internal reference defined by VREFCTL
                          // 5: DAC
                          // 6: bandgap 1.2V
                          // 7: GND
      input : 2,          // COMP input select
                          // 0: IOVIP[0] COMP1: PC00 COMP2: PA00 COMP3: PA04
                          // 1: IOVIP[1] COMP1: PC02 COMP2: PA01 COMP3: PA05
                          // 2: IOVIP[2] COMP1: PC13 COMP2: PA02 COMP3: PA06
                          // 3: IOVIP[3] ----
      reserved1 : 3,      // reserved 3 bit
      flt_prd : 2,        // the filter period in MSI clock
      flt_byp : 1,        // filter bypass
      risingintr_en : 1,  // interrupt enable for the rising edge interrupt
      fallingintr_en : 1, // interrupt enable for the falling edge interrupt
      reserved2 : 11;     // reserved 11 bit
} COMP_Param;

typedef struct __COMP_HandleTypeDef
{
  reg_comp_t *COMP;
} COMP_HandleTypeDef;

/**
 * @brief LSCOMP Initialize
 *
 * @param  hcomp Pointer to a COMP_HandleTypeDef structure that contains
 *               the configuration information for the specified COMP module.int_t
 * @return HAL_StatusTypeDef
 */
HAL_StatusTypeDef HAL_COMP_Init(COMP_HandleTypeDef *hcomp);

/**
 * @brief LSCOMP DeInitialize
 *
 * @return HAL_StatusTypeDef
 */
HAL_StatusTypeDef HAL_COMP_DeInit(void);

/**
 * @brief LSCOMP Config
 *
 * @param  hcomp Pointer to a COMP_HandleTypeDef structure that contains
 *               the configuration information for the specified COMP module.int_t
 * @param param[in] Pointer to a COMP_Param structure
 * @return HAL_StatusTypeDef
 */
HAL_StatusTypeDef HAL_COMP_Config(COMP_HandleTypeDef *hcomp, COMP_Param *param);

/**
 * @brief LSCOMP start
 *
 * @param  hcomp Pointer to a COMP_HandleTypeDef structure that contains
 *               the configuration information for the specified COMP module.int_t
 * @return HAL_StatusTypeDef
 */
HAL_StatusTypeDef HAL_COMP_Start(COMP_HandleTypeDef *hcomp);

/**
 * @brief LSCOMP stop
 *
 * @param  hcomp Pointer to a COMP_HandleTypeDef structure that contains
 *               the configuration information for the specified COMP module.int_t
 * @return HAL_StatusTypeDef
 */
HAL_StatusTypeDef HAL_COMP_Stop(COMP_HandleTypeDef *hcomp);

/**
 * @brief COMP Rising/falling edge interrupt callbacks.
 *
 * @note  This function needs to be implemented when the callback is needed,
          the HAL_UART_TxCpltCallback could be implemented in the user file
 * @param  hcomp Pointer to a COMP_HandleTypeDef structure that contains
 *               the configuration information for the specified COMP module.int_t
 * @param  edge enum comp_intr_edge, rising/falling/both
 * @param  output comparator output results
*/
void HAL_COMP_Callback(COMP_HandleTypeDef *hcomp, enum comp_intr_edge edge, bool output);

/**
 * @brief  This function handles COMP interrupt request.
 *
 * @param  hcomp Pointer to a COMP_HandleTypeDef structure that contains
 *               the configuration information for the specified COMP module.int_t
 * @param  edge enum comp_intr_edge, rising/falling/both
 * @param  output comparator output results
 */
void HAL_COMP_IRQHandler(COMP_HandleTypeDef *hcomp, enum comp_intr_edge edge, bool output);

#endif
