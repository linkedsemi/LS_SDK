#ifndef LS_HAL_TRNG_H_
#define LS_HAL_TRNG_H_
#include <stdint.h>
#include "HAL_def.h"

/** \addtogroup PERIPHERAL
 *  @{
 */

/** \addtogroup LSTRNG
 *  @{
 */


/** \brief LSTRNG Initialize.
 */
HAL_StatusTypeDef HAL_TRNG_Init(void);

/** \brief LSTRNG De-initialization.
 *  \return status 
 */
HAL_StatusTypeDef HAL_TRNG_DeInit(void);

/** \brief Gets the true random number (Block Mode).
 *  \param[in] random32bit The value of a truly random number.
 *  \return status 
 */
HAL_StatusTypeDef HAL_TRNG_GenerateRandomNumber(uint32_t *random32bit);

/** \brief Gets the true random number (Interrupt Mode).
 *  \return status 
 */
HAL_StatusTypeDef HAL_TRNG_GenerateRandomNumber_IT(void);

void HAL_TRNG_IRQHandler(void);

/** Callback function that will be invoked in the interrupt context when true random number operation is complete.
 *  Overwrite this function to get notification of completion of true random number operation.
 *  \param random32bit The value of a truly random number.
 */
void HAL_TRNG_ReadyDataCallback(uint32_t random32bit);

/** @}*/


/** @}*/

#endif
