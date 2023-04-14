#include <stdbool.h>
#include "systick.h"
#include "platform.h"
#include "ls_soc_pinmux.h"
#include "ls_soc_gpio.h"
#include "tusb_config.h"
#if CFG_TUH_ENABLED
#define USB_HOST 1
#else
#define USB_HOST 0
#endif

#define LED_RED PB15
#define LED_GREEN PB14
#define LED_BLUE PB13

uint8_t g_board_led_rgb_idx = 0;

void board_init(void)
{
  sys_init_none();
  pinmux_usb_init(USB_HOST);

  // HIGH , LED OFF
  io_cfg_output(LED_RED);
  io_cfg_output(LED_GREEN);
  io_cfg_output(LED_BLUE);

  io_set_pin(LED_RED);
  io_set_pin(LED_GREEN);
  io_set_pin(LED_BLUE);
}

void board_led_write(bool state)
{
  uint8_t led_rgb;
  switch (g_board_led_rgb_idx)
  {
  case 0:
    led_rgb = LED_RED;
    break;
  case 1:
    led_rgb = LED_GREEN;
    break;
  case 2:
    led_rgb = LED_BLUE;
    break;
  default:
    return;
  }

  if (state)
  {
    io_clr_pin(led_rgb);
  }
  else
  {
    io_set_pin(led_rgb);
  }
}

uint32_t board_millis(void)
{
  return systick_get_value();
}

uint32_t board_button_read(void)
{
  static uint32_t button = 0;
  if (button > 4)
  {
    button = 0;
  }
  else
  {
    button++;
  }

  return button;
}

#if defined(__ICCARM__)
extern int _write(int fd, char *ptr, int len)
#define sys_write __write
#define sys_read __read
#elif defined(__GNUC__)
#define sys_write _write
#define sys_read _read
#elif defined(__CC_ARM)

#endif

#include "SEGGER_RTT.h"
    // int sys_write (int fhdl, const void *buf, size_t count)
    // {
    //   (void) fhdl;
    //   SEGGER_RTT_Write(0, (const char*) buf, (int) count);
    //   return count;
    // }

    int sys_read(int fhdl, char *buf, size_t count)
{
  (void)fhdl;
  int rd = (int)SEGGER_RTT_Read(0, buf, count);
  return (rd > 0) ? rd : -1;
}

int board_getchar(void)
{
  char c;
  return (sys_read(0, &c, 1) > 0) ? (int)c : (-1);
}
