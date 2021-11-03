#ifndef LL_EXTERNAL_H_
#define LL_EXTERNAL_H_
#include <stdint.h>
#include <stddef.h>

extern uint32_t (*enter_critical_fn)(void);

extern void (*exit_critical_fn)(uint32_t);

extern void *(*ll_malloc_fn)(size_t);

extern void (*ll_free_fn)(void *);

extern uint32_t (*ble_hclk2lpclk_fn)(uint32_t);

extern uint32_t (*ble_lpclk2hclk_fn)(uint32_t);

extern void (*io_set_pin_fn)(uint8_t);

extern void (*io_clr_pin_fn)(uint8_t);
#endif
