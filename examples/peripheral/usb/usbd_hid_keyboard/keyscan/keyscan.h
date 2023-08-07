/******************************************************************************
 * File: keyscan.c
 * Author: jyluo
 * Overview: matrix keyboard scan source file
 *
 * Date: Created on 2023-03-13, 10:20
 ******************************************************************************/
#ifndef _KEYSCAN_H_
#define _KEYSCAN_H_

#ifdef	__cplusplus
extern "C" {
#endif
/******************************************************************************
 Include
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "ls_hal_timer.h"
#include "ls_soc_gpio.h"
#include "platform.h"
/******************************************************************************
 External Macro Definition
 ******************************************************************************/
/***************timer configuration paramter**********************/
#define TIM_PRESCALER     (SDK_HCLK_MHZ-1)
#define TIM_PERIOD        (1000 - 1) /* Period Value 1ms */

/***************Keyboard configuration paramter**********************/
/*********************************
		C0  C1  C2	C4       	Matrix
	R0 {0,	0,	0,	0},       1  2  3  4
	R1 {0,	0,	0,	0},       5  6  7  8
	R2 {0,	0,	0,	0},       9  10 11 12
	R3 {0,	0,	0,	0},       13 14 15 16
*********************************/
//output ROW
#define KEY_ROW1_PIN 	(PB05)
#define KEY_ROW2_PIN 	(PB06)
#define KEY_ROW3_PIN 	(PB07)
#define KEY_ROW4_PIN 	(PB08)

//input COL
#define KEY_COL1_PIN 	(PB01)
#define KEY_COL2_PIN 	(PB12)
#define KEY_COL3_PIN 	(PA02)
#define KEY_COL4_PIN 	(PB09)

//Keyboard create paramter
#define KEYSCAN_ROW_NUM 		(4)		// ROW PIN NUM
#define KEYSCAN_COL_NUM 		(4)		// COL PIN NUM
#define BUTTON_KEEP_TIME_MAX    (60)  	// debounce time
#define KEYBORAD_SCAN_PERIOD 	(1)		//Keyboard scan cycle

//io array
#define KEYSCAN_ROW_TABLES {KEY_ROW1_PIN, KEY_ROW2_PIN, KEY_ROW3_PIN, KEY_ROW4_PIN}
#define KEYSCAN_COL_TABLES {KEY_COL1_PIN, KEY_COL2_PIN, KEY_COL3_PIN, KEY_COL4_PIN}
/******************************************************************************
 External Type Definition
 ******************************************************************************/
typedef void (*KS_KEY_CALLBACK)(uint16_t );
/******************************************************************************
 External Const Definition
 ******************************************************************************/

/******************************************************************************
 External Variable Definition
 ******************************************************************************/

/******************************************************************************
 External Function Definition
 ******************************************************************************/

bool keyscan_Start(bool scan);
void keyscan_Create_Keyboard( void (*keyscan_callback)(uint16_t));
void keyscan_Light_Sleep(void);

#ifdef	__cplusplus
}
#endif

#endif	
