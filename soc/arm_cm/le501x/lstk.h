/******************************************************************************
 * File: lsTK.h
 * Author: 
 * Overview: ls TK process when ls TK wake up
 * 
 * Date: Created on 2021-12-30, 19:45
 ******************************************************************************/

#ifndef LSTK_H
#define LSTK_H

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 Include
 ******************************************************************************/
#include <stdbool.h>
#include <stdint.h>
#include "HAL_def.h"
#include "tk_misc.h"
#include "ls_dbg.h"
  /******************************************************************************
 External Macro Definition
 ******************************************************************************/
/**
 *  @defgroup TK_noise_protect_mode TK noise protect mode.
 */
#define TK_DNPR_DISABLE 0x08U /*!< Disable TK noise protect mode.   */
#define TK_DNPR_ENABLE 0x00U  /*!< Enable TK noise protect mode.   */
/**
 *  @defgroup TK_channel_mode TK channel mode.
 */
#define TK_MULTION_DISABLE 0x00U /*!< Disable TK channel mode.   */
#define TK_MULTION_ENABLE 0x10U   /*!< Enable TK channel mode.   */
/**
 *  @defgroup TK_ScanEN_mode TK ScanEN mode.
 */
#define TK_SCANEN_DISABLE 0x00U /*!< Disable TK ScanEN mode.   */
#define TK_SCANEN_ENABLE 0x01U   /*!< Enable TK ScanEN mode.   */
/**
 *  @defgroup TK_Low_power_scan_mode TK cLow power scan mode. 
 */
#define TK_LP_DISABLE 0x00U /*!< Disable TK cLow power scan mode.   */
#define TK_LP_ENABLE 0x40U   /*!< Enable TK cLow power scan mode.   */
/**
 *  @defgroup TK_sleep_mode TK sleep mode.
 */
#define TK_PD_DISABLE 0x00U /*!< Disable TK sleep mode.   */
#define TK_PD_ENABLE 0x80U   /*!< Enable TK sleep mode.   */
/**
 *  @defgroup TK_Low_power_scan_preiod  TK Low power scan preiod.
 */
#define TK_LPSP_500 0x00U /*!< TK Low power scan preiod to 500ms.   */
#define TK_LPSP_250 0x01U /*!< TK Low power scan preiod to 250ms.   */
#define TK_LPSP_100 0x02U /*!< TK Low power scan preiod to 100ms.   */

  /*******************************************************************************
*External Type Definition
*******************************************************************************/
  typedef struct
  {
    volatile uint8_t NPRR; /* !<Specifies the noise threshold proportional multiple.
                        This parameter could be 0 - 7 (0：x4   1:：x6 .... 7：x18,default:0)*/

    volatile uint8_t DNPR; /* !< Specifies if noise protect mode is selected.
                            This parameter can be a value of @ref TK_noise_protect_mode */

    volatile uint8_t MultiOn; /* !< Specifies if channel mode is selected.
                            This parameter can be a value of @ref TK_channel_mode */

    volatile uint8_t Debounce; /* !< Specifies the Anti-jitter parameters.
                            This parameter can be set to 0-255 (default:3 ) */

    volatile uint16_t ChannelEN; /* !< Specifies if the channel is enabled.
                            This parameter can be set to 0x0000-0x3fff (default:0x3fff ) */

    volatile uint8_t GbSen; /* !< Specifies the global sensitivity parameters.
                            This parameter can be set to 0-255 (default:0) */

    volatile uint8_t LP; /* !< Specifies if Low-power scan mode is selected.
                            This parameter can be a value of @ref TK_Low_power_scan_mode */

    volatile uint8_t IComGS; /* !< Specified compensation current.
                            This parameter can be set to 0-127 (default:40) */

    volatile uint8_t CdcFswDiv; /* !< Specifies CDC module scanning frequency.
                            This parameter can be set to 0-255 (default:0x07) */

    volatile uint8_t LowPowerScanPeriod; /* !< Specifies the scan period in low power consumption.
                            This parameter can be a value of @ref TK_Low_power_scan_preiod */

    volatile uint8_t KeyDebounceCount; /* !< Specifies the scan period in low power consumption.
                            This parameter can be set to 1-3 (default:1) */

    volatile uint8_t LpDelay; /* !< auto enter low power if button donnot TK in delay time.
                            This parameter can be set to 0-255  (default:4,4*1 ms) */

    volatile uint8_t ScanPeriod; /* !< Specify scan period.
                            This parameter can be set to 1-3 (LpDelay*1 ms,1*16ms)  */

    volatile uint16_t GsMask; /* !< Specifies whether channel 7- channel 0 participates in low-power scanning.
                            This parameter can be set to 0x0000-0x03fff (default:0) */

    volatile uint8_t LSenseGS; /* !< Specifies group scan sensitivity.
                            This parameter can be set to 0-255 (default:0) */

  } TK_InitTypeDef;
  /**
  * @brief  TK handle Structure definition
  */
  typedef struct __TK_HandleTypeDef
  {
    TK_InitTypeDef Init; /*!< TK required parameters */

    HAL_LockTypeDef Lock; /*!< TK locking object */

    volatile uint32_t ErrorCode; /*!< TK Error code */

  } TK_HandleTypeDef;
/******************************************************************************
 External Const Definition
 ******************************************************************************/
/*Register list*/
#define SSR0 0x00
#define SSR1 0x01
#define SSR2 0x02
#define SSR3 0x03
#define SSR4 0x04
#define SSR5 0x05
#define SSR6 0x06
#define SSR7 0x07
#define SSR8 0x08
#define SSR9 0x09
#define SSR10  0x0A
#define SSR11  0x0B
#define SLR    0x10
#define STR    0x11
#define SCFR   0x12
#define DBR    0x13
#define CHELR  0x14
#define CHEHR  0x15
#define GSR    0x1E
#define SCCR    0x1F
#define SPR    0x21
#define CNTLR  0x22
#define CNTHR  0x23
#define CSR    0x25
#define ICGSR  0x29
#define CFDR   0x2A
#define LPSPR  0x2B
#define KDCR   0x2C
#define LDR    0x30
#define SCTR   0x31
#define WTR    0x32
#define SIGLR0 0x40
#define SIGHR0 0x41
#define SIGLR1 0x42
#define SIGHR1 0x43
#define SIGLR2 0x44
#define SIGHR2 0x45
#define SIGLR3 0x46
#define SIGHR3 0x47
#define SIGLR4 0x48
#define SIGHR4 0x49
#define SIGLR5 0x4A
#define SIGHR5 0x4B
#define SIGLR6 0x4C
#define SIGHR6 0x4D
#define SIGLR7 0x4E
#define SIGHR7 0x4F
#define SIGLR8 0X50
#define SIGHR8 0X51
#define SIGLR9 0X52
#define SIGHR9 0X53
#define SIGLR10 0X54
#define SIGHR10 0X55
#define SIGLR11 0X56
#define SIGHR11 0X57
#define SIGLR12 0X58
#define SIGHR12 0X59
#define SIGLR13 0X5A
#define SIGHR13 0X5B
#define SIGSLR0 0X5C
#define SIGSHR0 0X5D
#define SIGSLR1 0X5E
#define SIGSHR1 0X5F
#define SIGSLR2 0X60
#define SIGSHR2 0X61
#define SIGSLR3 0X62
#define SIGSHR3 0X63
#define SIGSLR4 0X64
#define SIGSHR4 0X65
#define SIGSLR5 0X66
#define SIGSHR5 0X67
#define SIGSLR6 0X68
#define SIGSHR6 0X69
#define SIGSLR7 0X6A
#define SIGSHR7 0X6B
#define SIGSLR8 0X6C
#define SIGSHR8 0X6D
#define SIGSLR9 0X6E
#define SIGSHR9 0X6F
#define SIGSLR10 0X70
#define SIGSHR10 0X71
#define SIGSLR11 0X72
#define SIGSHR11 0X73
#define SIGSLR12 0X74
#define SIGSHR12 0X75
#define SIGSLR13 0X76
#define SIGSHR13 0X77
#define WPR  0xAF
#define GMR0 0XB0
#define GMR1 0XB1
#define LSR0 0XE0
#define LSR1 0XE1
#define LSR2 0XE2
#define LSR3 0XE3
#define LSR4 0XE4
#define LSR5 0XE5
#define LSR6 0XE6
#define LSR7 0XE7
#define LSR8 0XE8
#define LSR9 0XE9
#define LSR10 0XEA
#define LSR11 0XEB
#define LSR12 0XEC
#define LSR13 0XED
#define LSGR  0XEE
#define TK_WKUP  PA00
  /******************************************************************************
 External Variable Definition
 ******************************************************************************/

  /******************************************************************************
 External Function Definition
 ******************************************************************************/
  /**
  * @brief  Initializes the TK according to the specified parameters
  *         in the TK_InitTypeDef and initialize the associated handle.
  * @param  htk: TK handle
  * @retval HAL status
  */
  HAL_StatusTypeDef HAL_TK_Init(TK_HandleTypeDef *htk);
  /**
  * @brief  DeInitialize the TK peripheral.
  * @note   
  * @param  htk Pointer to a TK_InitTypeDef structure that contains
  *         the configuration information for the specified TK.
  * @retval HAL status
  */
  HAL_StatusTypeDef HAL_TK_DeInit(TK_HandleTypeDef *htk);
  /**
  * @brief  Set TK Register.
  * @note   
  * @param  regAddr TK register
  * @param  param register parameter, fill NULL if need not param 
  * @param  size parameter size, fill 0 if not param
  * @retval HAL status
  */
  HAL_StatusTypeDef HAL_TK_Set_Reg(uint8_t regAddr, uint8_t *param, uint8_t size);
  /**
  * @brief  Get TK Register.
  * @note   
  * @param  regAddr TK register
  * @param  data store the data from register 
  * @param  size the data size if you want to read
  * @retval HAL status
  */
  HAL_StatusTypeDef HAL_TK_Get_Reg(uint8_t regAddr, uint8_t *data, uint8_t size);

  /**
  * @brief  HAL TK Scan Enable.
  * @note   
  * @param  htk Pointer to a TK_InitTypeDef structure that contains
  *         the configuration information for the specified TK.
  * @retval HAL status
  */
  HAL_StatusTypeDef HAL_TK_ScanEnable(TK_HandleTypeDef *htk);
  /**
  * @brief  HAL TK Scan Disable.
  * @note   
  * @param  htk Pointer to a TK_InitTypeDef structure that contains
  *         the configuration information for the specified TK.
  * @retval HAL status
  */
  HAL_StatusTypeDef HAL_TK_ScanDisable(TK_HandleTypeDef *htk);
  /**
  * @brief  HAL TK WriteProtection Disable.
  * @note   
  * @param  htk Pointer to a TK_InitTypeDef structure that contains
  *         the configuration information for the specified TK.
  * @retval HAL status
  */
  HAL_StatusTypeDef HAL_TK_Disable_WriteProtection(TK_HandleTypeDef *htk);
  /**
  * @brief  HAL TK Set single channel sensitivity.
  * @note   
  * @param  htk Pointer to a TK_InitTypeDef structure that contains
  *         the configuration information for the specified TK.
  * @param  ChannelNum  Capacitor key channel number
  * @param  Lsense  Key sensitivity
  * @retval HAL status
  */
  HAL_StatusTypeDef HAL_TK_Set_Lsense(TK_HandleTypeDef *htk, uint8_t ChannelNum, uint8_t Lsense);
  /**
  * @brief  HAL TK Enable sleep mode.
  * @note   
  * @param  htk Pointer to a TK_InitTypeDef structure that contains
  *         the configuration information for the specified TK.
  * @param  WTR Wake up the threshold
  * @retval HAL status
  */
  HAL_StatusTypeDef HAL_TK_Enable_DP(TK_HandleTypeDef *htk, uint8_t _WTR, uint8_t _IComGS);
  /**
  * @brief  HAL TK Wake up from sleep mode.
  * @note   
  * @param 
  * @retval HAL status
  */
  HAL_StatusTypeDef HAL_TK_Wake_DP(void);
  /**
  * @brief  HAL TK ENABLE the interrupt.
  * @note   
  * @param  htk Pointer to a TK_InitTypeDef structure that contains
  *         the configuration information for the specified TK.
  * @retval HAL status
  */
  HAL_StatusTypeDef HAL_TK_Enable_IT(TK_HandleTypeDef *htk);
  /**
  * @brief  HAL TK DISENABLE the interrupt.
  * @note   
  * @param  htk Pointer to a TK_InitTypeDef structure that contains
  *         the configuration information for the specified TK.
  * @retval HAL status
  */
  HAL_StatusTypeDef HAL_TK_DisEnable_IT(TK_HandleTypeDef *htk);

  /*******************************************************************************
 End of File
 ******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* LSTK_H */
