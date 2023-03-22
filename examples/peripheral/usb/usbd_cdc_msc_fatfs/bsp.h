#ifndef _BSP_H_
#define _BSP_H_
#include <stdbool.h>
#include <stdint.h>
//--------------------------------------------------------------------+
// Board Porting API
// For simplicity, only one LED and one Button are used
//--------------------------------------------------------------------+

// Initialize on-board peripherals : led, button, uart and USB
void bsp_init(void);

uint32_t bsp_millis(void);

// Turn BLUE LED on or off
void bsp_blue_led_write(bool state);

uint32_t bsp_download_button_read(void);

#endif /* _BSP_H_ */
