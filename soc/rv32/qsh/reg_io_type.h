#ifndef REG_IO_TYPE_H_
#define REG_IO_TYPE_H_
#include <stdint.h>

typedef struct {
    volatile uint32_t LOCK; // in sec
    volatile uint32_t PU1_PU0;
    volatile uint32_t PD_PU2;
    volatile uint32_t IEN1_IEN0;
    volatile uint32_t DS1_DS0;
    volatile uint32_t AE_DS2;
    volatile uint32_t OD_FIR;
    volatile uint32_t SL_ST;
} reg_io_cfg_t;

typedef struct {
    volatile uint32_t OE_DIN;
    volatile uint32_t DOC_DOS; // in app
} reg_io_val_t;

#endif
