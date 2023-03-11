
#ifndef _LSSOFTIIC_H_
#define _LSSOFTIIC_H_
#include "platform.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
		Macro Definition
*******************************************************************************/

/*******************************************************************************
		Fcuction Declaration
*******************************************************************************/
void I2C_Release(void);
void HAL_TK_Reset(void);
bool TK_GetReg(uint8_t addr, uint8_t *pBuff, uint8_t len);
bool TK_SetReg(uint8_t addr, const uint8_t *pBuff, uint8_t len);

/*******************************************************************************
		End File
*******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif
