#ifndef LS_HAL_RTCV2_H_
#define LS_HAL_RTCV2_H_
#include <stdbool.h>
#include "ls_msp_rtc.h"
#include "HAL_def.h"
#include "field_manipulate.h"

/** \addtogroup PERIPHERAL
 *  @{
 */

/** \addtogroup LSRTC
 *  @{
 */


/**
 *  \brief structure definition of calendar date & month & year.
 */
typedef struct
{
  uint32_t week : 3, /**< week */
           mon  : 4, /**< month */
           year : 8; /**< year */
} calendar_cal_t;

/**
 *  \brief structure definition of calendar second & minute & hour & week.
 */
typedef struct
{
  uint32_t sec  : 6, /**< second */
           min  : 6, /**< minute */
           hour : 5, /**< hour */
           date : 5; /**< data */
} calendar_time_t;

/**
 ****************************************************************************************
 * \brief RTC initialization function
 *
 * \return status            0: success | others: error
 ****************************************************************************************
 */
HAL_StatusTypeDef HAL_RTC_Init(void);

/**
 ****************************************************************************************
 * \brief RTC de-initialization function
 *
 * \return status            0: success | others: error
 ****************************************************************************************
 */
HAL_StatusTypeDef HAL_RTC_DeInit(void);

/**
 ****************************************************************************************
 * \brief RTC param set 
 * 
 * \param[in]  cyc_1hz         Add one second for every [cyc_1hz] clock cycles
 * \param[in]  calib_cyc       60 seconds extra wait 1 minute for calib_cyc clock cycles
 * \param[in]  calib_en        Enable the sub-calibration function
 *
 * \return status            0: success | others: error
 ****************************************************************************************
 */
HAL_StatusTypeDef HAL_RTC_Cycle_Set(uint32_t cyc_1hz, uint32_t calib_cyc, bool calib_en);

/**
 ****************************************************************************************
 * \brief RTC calendar set function
 *
 * \param[in]  calendar_cal         parameter containing date/month/year infor to set
 * \param[in]  calendar_time        parameter containing second/minute/hour/week infor to set
 * 
 * \return status            0: success | others: error
 ****************************************************************************************
 */
HAL_StatusTypeDef HAL_RTC_CalendarSet(calendar_cal_t *calendar_cal, calendar_time_t *calendar_time);

/**
 ****************************************************************************************
 * \brief RTC calendar get function
 *
 * \param[out]  calendar_cal        returned date/month/year information
 * \param[out]  calendar_time       returned second/minute/hour/week information
 *
 * \return status            0: success | others: error
 ****************************************************************************************
 */
HAL_StatusTypeDef HAL_RTC_CalendarGet(calendar_cal_t *calendar_cal, calendar_time_t *calendar_time);

/**
 ****************************************************************************************
 * \brief RTC alarm set function
 *
 * \param[in]  calendar_cal         parameter containing date/month/year infor to set
 * \param[in]  calendar_time        parameter containing second/minute/hour/week infor to set
 *
 * \return status            0: success | others: error
 ****************************************************************************************
 */
HAL_StatusTypeDef HAL_RTC_AlarmSet(calendar_cal_t *calendar_cal, calendar_time_t *calendar_time);

/**
 ****************************************************************************************
 * \brief RTC alarm clear function
 *
 * \return status            0: success | others: error
 ****************************************************************************************
 */
HAL_StatusTypeDef HAL_RTC_AlarmClear(void);

/**
 ****************************************************************************************
 * \brief RTC alarm callback function
 *
 ****************************************************************************************
 */
void HAL_RTC_alarm_callback(void);

/**
 ****************************************************************************************
 * \brief RTC IRQ handler
 *
 ****************************************************************************************
 */
void HAL_RTC_IRQHandler(void);

/** @}*/

/** @}*/

#endif
