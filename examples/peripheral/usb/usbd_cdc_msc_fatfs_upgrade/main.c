/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cpu.h"
#include "platform.h"

#include "bsp/board.h"
#include "tusb.h"
#include "ff.h"
#include "download.h"
//--------------------------------------------------------------------+
// MACRO CONSTANT TYPEDEF PROTYPES
//--------------------------------------------------------------------+

#define LED_RED_IDX 0
#define LED_GREEN_IDX 1
#define LED_BLUE_IDX 2

/* Blink pattern
 * - 250 ms  : device not mounted
 * - 1000 ms : device mounted
 * - 2500 ms : device is suspended
 */
enum
{
  BLINK_NOT_MOUNTED = 250,
  BLINK_MOUNTED = 1000,
  BLINK_SUSPENDED = 2500,
  BLINK_TIMEOUT_INTERVAL = 1000,
  BLINK_FLICKER_INTERVAL = 100,
  BLINK_DOWNLOAD_INTERVAL = 100,
};

FATFS FatFs;
FRESULT g_MountFr = FR_NOT_READY;

static uint32_t blink_interval_ms = BLINK_NOT_MOUNTED;
uint32_t report_check_ms = 0;
bool report_desc_complete = false;

void report_check_task(void);
void download_task(void);
void flicker_task(void);

void cdc_task(void);

/*------------- MAIN -------------*/
int main(void)
{
  sys_init_none();

  if (check_application())
  {
    // REG_FIELD_WR(SYSC_AWO->IO[0].DS,SYSC_AWO_GPIOA_DS1,0x800);
    jump_to_app();
    while (1)
      ;
  }
  else
  {
    board_init();
  }

  // init device stack on configured roothub port
  tud_init(BOARD_TUD_RHPORT);

  report_check_ms = 0;
  report_desc_complete = false;
  g_bin_filename_exist = false;

  download_info_init();

  while (1)
  {
    tud_task(); // tinyusb device task
    report_check_task();
    if (report_desc_complete)
    {
      download_task();
      flicker_task();
    }
    cdc_task();
  }

  return 0;
}

//--------------------------------------------------------------------+
// Device callbacks
//--------------------------------------------------------------------+

// Invoked when device is mounted
void tud_mount_cb(void)
{
  blink_interval_ms = BLINK_MOUNTED;

  g_MountFr = f_mount(&FatFs, "0:", 1);
  if (g_MountFr == FR_OK)
  {
    download_check_bin_file();
  }
}

// Invoked when device is unmounted
void tud_umount_cb(void)
{
  blink_interval_ms = BLINK_NOT_MOUNTED;
  if (g_MountFr == FR_OK)
  {
    f_mount(NULL, "0:", 1);
  }
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en)
{
  (void)remote_wakeup_en;
  blink_interval_ms = BLINK_SUSPENDED;
}

// Invoked when usb bus is resumed
void tud_resume_cb(void)
{
  blink_interval_ms = BLINK_MOUNTED;
}

//--------------------------------------------------------------------+
// USB CDC
//--------------------------------------------------------------------+
void cdc_task(void)
{
  // connected() check for DTR bit
  // Most but not all terminal client set this when making connection
  // if ( tud_cdc_connected() )
  {
    // connected and there are data available
    if (tud_cdc_available())
    {
      // read data
      char buf[64];
      uint32_t count = tud_cdc_read(buf, sizeof(buf));
      (void)count;

      // Echo back
      // Note: Skip echo by commenting out write() and write_flush()
      // for throughput test e.g
      //    $ dd if=/dev/zero of=/dev/ttyACM0 count=10000
      tud_cdc_write(buf, count);
      tud_cdc_write_flush();
    }
  }
}

// Invoked when cdc when line state changed e.g connected/disconnected
void tud_cdc_line_state_cb(uint8_t itf, bool dtr, bool rts)
{
  (void)itf;
  (void)rts;

  // TODO set some indicator
  if (dtr)
  {
    // Terminal connected
  }
  else
  {
    // Terminal disconnected
  }
}

// Invoked when CDC interface received data from host
void tud_cdc_rx_cb(uint8_t itf)
{
  (void)itf;
}
//--------------------------------------------------------------------+
// REPORT CHECK TASK
//--------------------------------------------------------------------+
void report_check_task(void)
{
  static uint32_t report_interval_count = 0;

  if (report_desc_complete)
  {
    return;
  }
  // MOUNTED after
  if (blink_interval_ms == BLINK_MOUNTED)
  {
    // Blink every interval ms
    if (board_millis() - report_check_ms < BLINK_MOUNTED)
    {
      return; // not enough time
    }
    report_check_ms += BLINK_MOUNTED;

    if (report_interval_count++ >= 2)
    {
      // LOG_I("report_desc_complete\n");
      report_desc_complete = true;
    }
  }
}

//--------------------------------------------------------------------+
// FLICKER TASK
//--------------------------------------------------------------------+
void flicker_task(void)
{
  extern uint8_t g_board_led_rgb_idx;

  static uint32_t flicker_ms = 0;
  static bool blue_led_state = false;
  static bool red_led_state = false;
  static uint8_t blue_led_interval_count = 0;

  // every interval 100 ms
  if (board_millis() - flicker_ms < BLINK_FLICKER_INTERVAL)
  {
    return; // not enough time
  }

  flicker_ms += BLINK_FLICKER_INTERVAL;

  switch (g_download_info.bin_download_step)
  {
  case DOWNLOAD_STEP_READY:
    // red off,1000ms blue on 
    if (blue_led_interval_count++ >= 10)
    {
      blue_led_interval_count = 0;
      g_board_led_rgb_idx = LED_RED_IDX;
      board_led_write(0);
      g_board_led_rgb_idx = LED_BLUE_IDX;
      board_led_write(blue_led_state);
      blue_led_state = 1 - blue_led_state; // toggle
    }
    break;
  case DOWNLOAD_STEP_TIMEOUT:
  case DOWNLOAD_STEP_ERROR:

    // blue off,100ms red on
    blue_led_interval_count = 0;
    g_board_led_rgb_idx = LED_BLUE_IDX;
    board_led_write(0);
    g_board_led_rgb_idx = LED_RED_IDX;
    board_led_write(red_led_state);
    red_led_state = 1 - red_led_state; // toggle
    break;
  case DOWNLOAD_STEP_COMPLETE:

    // red off,100ms blue on

      blue_led_interval_count = 0;
      g_board_led_rgb_idx = LED_RED_IDX;
      board_led_write(0);
      g_board_led_rgb_idx = LED_BLUE_IDX;
      board_led_write(blue_led_state);
      blue_led_state = 1 - blue_led_state; // toggle
    break;
  }
}

//--------------------------------------------------------------------+
// DOWNLOAD TASK
//--------------------------------------------------------------------+

void download_task(void)
{
  static uint32_t download_ms = 0;

  // every interval 50ms
  if ((board_millis() - download_ms) < BLINK_DOWNLOAD_INTERVAL)
  {
    return; // not enough time
  }

  download_ms += BLINK_DOWNLOAD_INTERVAL;

  __disable_irq();

  switch (g_download_info.bin_download_step)
  {
  case DOWNLOAD_STEP_READY:
    // Check download KEY
    // if (board_button_read())
    {
      if (g_bin_filename_exist)
      {
        g_download_info.bin_download_step = DOWNLOAD_STEP_CHIP_ERASE;
        // LOG_I("erase begin");
        earse_app_code(true);
      }
      else
      {
        g_download_info.bin_download_step = DOWNLOAD_STEP_ERROR;
      }
    }
    break;
  case DOWNLOAD_STEP_CHIP_ERASE:
    // LOG_I("erase int...");
    earse_app_code(false);
    break;
  case DOWNLOAD_STEP_FLASH_PROGRAM:
    write_app_code();
    break;
  default:
    break;
  }
  __enable_irq();

  // clear timeout
  // timeout_ms = 0;
}
