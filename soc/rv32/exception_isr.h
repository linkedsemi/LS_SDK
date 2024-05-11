#ifndef EXCEPTION_ISR_H_
#define EXCEPTION_ISR_H_

#ifdef __cplusplus
extern "C" {
#endif

extern void (*interrupt_vector[])();

void rv_set_int_isr(uint8_t type,void (*isr)());

#ifdef __cplusplus
}
#endif

#endif
