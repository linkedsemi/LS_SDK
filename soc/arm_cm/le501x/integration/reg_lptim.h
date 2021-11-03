#ifndef REG_LPTIM_H_
#define REG_LPTIM_H_
#include <stdint.h>
#include "reg_base_addr.h"
typedef struct
{
    volatile uint32_t CON0; //0x0
    volatile uint32_t CON1; //0x4
    volatile uint32_t ARR;  //0x8
    volatile uint32_t CNT;  //0xc
    volatile uint32_t CMP;  //0x10
    volatile uint32_t RESERVED0;
    volatile uint32_t IER;  //0x18
    volatile uint32_t ISR;  //0x1c
    volatile uint32_t IFC;  //0x20
    volatile uint32_t RESERVED1[3];
    volatile uint32_t UPDATE;   //0x30   
    volatile uint32_t SYNCSTAT; //0x34
}reg_lptim_t;

#define LPTIM ((reg_lptim_t *)0x40010000)
#endif
