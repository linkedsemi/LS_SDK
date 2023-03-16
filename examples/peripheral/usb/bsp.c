#include <stdbool.h>
#include "systick.h"
#include "platform.h"
#include "ls_soc_pinmux.h"
#include "tusb_config.h"
#if CFG_TUH_ENABLED
#define USB_HOST 1
#else
#define USB_HOST 0
#endif

void board_init(void)
{
    sys_init_none();
    pinmux_usb_init(USB_HOST);
}

void board_led_write(bool state)
{

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
  extern int _write (int fd, char *ptr, int len)
  #define sys_write   __write
  #define sys_read    __read
#elif defined(__GNUC__)
  #define sys_write   _write
  #define sys_read    _read
#elif defined(__CC_ARM)

#endif

#include "SEGGER_RTT.h"
// int sys_write (int fhdl, const void *buf, size_t count)
// {
//   (void) fhdl;
//   SEGGER_RTT_Write(0, (const char*) buf, (int) count);
//   return count;
// }

int sys_read (int fhdl, char *buf, size_t count)
{
  (void) fhdl;
  int rd = (int) SEGGER_RTT_Read(0, buf, count);
  return (rd > 0) ? rd : -1;
}

int board_getchar(void)
{
  char c;
  return ( sys_read(0, &c, 1) > 0 ) ? (int) c : (-1);
}
