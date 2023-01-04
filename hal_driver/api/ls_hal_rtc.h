#ifndef LS_HAL_RTC_H_
#define LS_HAL_RTC_H_
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
    uint32_t  date:5,   /**< date */
              mon:4,    /**< month */
              year:7;   /**< year */
}calendar_cal_t;	

/**
 *  \brief structure definition of calendar second & minute & hour & week.
 */
typedef struct 
{
    uint32_t  sec:6,   /**< second */
              min:6,   /**< minute */
              hour:5,  /**< hour */
              week:3;  /**< week */
}calendar_time_t;

/**
  * \brief  RTC clock source enumeration definition
  */
enum RTC_CLK_SEL
{
    // RTC_CKSEL_HSI,
    RTC_CKSEL_LSE = 1,
    RTC_CKSEL_LSI,
    // RTC_CKSEL_PLL,
};
/**
 ****************************************************************************************
 * \brief RTC IRQ handler
 *
 ****************************************************************************************
 */
void HAL_RTC_IRQHandler(void);

/**
 ****************************************************************************************
 * \brief RTC initialization function
 *
 * \param[in]  cksel         clock source selection
 *
 ****************************************************************************************
 */
void HAL_RTC_Init(uint8_t cksel);
/**
 ****************************************************************************************
 * \brief RTC de-initialization function
 *
 ****************************************************************************************
 */
void HAL_RTC_DeInit(void);
/**
 ****************************************************************************************
 * \brief RTC calendar set function
 *
 * \param[in]  calendar_cal         parameter containing date/month/year infor to set
 * \param[in]  calendar_time        parameter containing second/minute/hour/week infor to set
 *
 ****************************************************************************************
 */
void RTC_CalendarSet(calendar_cal_t *calendar_cal, calendar_time_t *calendar_time);
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
HAL_StatusTypeDef RTC_CalendarGet(calendar_cal_t *calendar_cal, calendar_time_t *calendar_time);

/**
 ****************************************************************************************
 * \brief RTC wakeup time set function
 *
 * \param[in]  t_ms         wakeup time(the unit is millisecond). The accuracy depends on 
 * the real RC clock.
 *
 ****************************************************************************************
 */
void RTC_wkuptime_set(uint32_t t_ms);

/**
 ****************************************************************************************
 * \brief Clear RTC wakeuptime configuration
 *
 ****************************************************************************************
 */
void RTC_wkuptime_clr(void);

/**
 ****************************************************************************************
 * \brief RTC wakeup callback function(in LP0 mode)
 *
 ****************************************************************************************
 */
void rtc_wkup_callback(void);

/** @}*/


/** @}*/

#endif 
