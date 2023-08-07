/******************************************************************************
 * File: main.c
 * Author: jyluo
 * Overview:  keyboard hid source file
 *
 * Date: Created on 2023-03-13, 10:20
 ******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bsp/board.h"
#include "keyscan.h"
#include "tusb.h"

#include "usb_descriptors.h"

/******************************************************************************
 External Const Definition
 ******************************************************************************/

/******************************************************************************
 External Variable Declaration
 ******************************************************************************/

/******************************************************************************
 Local Const Definition
 ******************************************************************************/
//key value array
const uint8_t c_aucKeyBoardPin[] = KEYBOARD_KEYVALUE;
/******************************************************************************
Local Macro Definition
******************************************************************************/
/******************************************************************************
 Local Type Definition
 ******************************************************************************/
/******************************************************************************
 Local function Declaration
 **********************************************************************a********/
void led_blinking_task(void);
void hid_task(uint16_t ShortKey_Press);
/******************************************************************************
 Local Variable Definition
 ******************************************************************************/
/* Blink pattern
 * - 250 ms  : device not mounted
 * - 1000 ms : device mounted
 * - 2500 ms : device is suspended
 */
enum  {
  BLINK_NOT_MOUNTED = 250,
  BLINK_MOUNTED = 1000,
  BLINK_SUSPENDED = 2500,
};

static uint32_t blink_interval_ms = BLINK_NOT_MOUNTED;

volatile bool g_light_sleep_flag = false;

/*------------- MAIN -------------*/
int main(void)
{
  board_init();

  // init device stack on configured roothub port
  tud_init(BOARD_TUD_RHPORT);
  keyscan_Create_Keyboard(hid_task);//The hid_task function is called when a press is detected
  keyscan_Start(true);
  while (1)
  {
    tud_task(); // tinyusb device task
    if(g_light_sleep_flag)
    {
      g_light_sleep_flag = false;
      keyscan_Light_Sleep();
    }
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
}

// Invoked when device is unmounted
void tud_umount_cb(void)
{
  blink_interval_ms = BLINK_NOT_MOUNTED;
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en)
{
  (void)remote_wakeup_en;
  blink_interval_ms = BLINK_SUSPENDED;
  g_light_sleep_flag = true;
}

// Invoked when usb bus is resumed
void tud_resume_cb(void)
{
  blink_interval_ms = BLINK_MOUNTED;
}

//--------------------------------------------------------------------+
// USB HID
//--------------------------------------------------------------------+

static void send_hid_report(uint8_t report_id, uint32_t btn)
{
  // skip if hid is not ready yet
  if (!tud_hid_ready())
    return;
  // use to avoid send multiple consecutive zero report for keyboard
  static bool has_keyboard_key = false;
  uint16_t usKeyValue = 0;

  //Resolve the key value
  if (btn)
  {
    for (uint8_t i = 0; i < (KEYSCAN_COL_NUM * KEYSCAN_ROW_NUM); i++)
    {
      if ((btn >> i) & 0x01)
        usKeyValue = i;
    }
  }

  if (usKeyValue||btn)
  {
    // io_toggle_pin(c_aucLedPin[btn - 1]);
    uint8_t keycode[6] = {0};
    keycode[0] = c_aucKeyBoardPin[usKeyValue];
    tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
    has_keyboard_key = true;
  }
  else
  {
    // send empty key report if previously has key pressed
    if (has_keyboard_key)
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
    has_keyboard_key = false;
  }
}

// key scan success, we will sent 1 report for each HID profile (keyboard, mouse etc ..)
// tud_hid_report_complete_cb() is used to send the next report after previous one is complete
void hid_task(uint16_t ShortKey_Press)
{
  // Remote wakeup
  if ( tud_suspended() && ShortKey_Press )
  {
    // Wake up host if we are in suspend mode
    // and REMOTE_WAKEUP feature is enabled by host
    tud_remote_wakeup();
  }else
  {
    // Send the 1st of report chain, the rest will be sent by tud_hid_report_complete_cb()
    send_hid_report(REPORT_ID_KEYBOARD, ShortKey_Press);
  }
}

// Invoked when sent REPORT successfully to host
// Application can use this to send the next report
// Note: For composite reports, report[0] is report ID
void tud_hid_report_complete_cb(uint8_t instance, uint8_t const* report, uint16_t len)
{
  (void) instance;
  (void) len;
  (void) report;
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen)
{
  // TODO not Implemented
  (void) instance;
  (void) report_id;
  (void) report_type;
  (void) buffer;
  (void) reqlen;

  return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize)
{
  (void) instance;

  if (report_type == HID_REPORT_TYPE_OUTPUT)
  {
    // Set keyboard LED e.g Capslock, Numlock etc...
    if (report_id == REPORT_ID_KEYBOARD)
    {
      // bufsize should be (at least) 1
      if ( bufsize < 1 ) return;

      uint8_t const kbd_leds = buffer[0];

      if (kbd_leds & KEYBOARD_LED_CAPSLOCK)
      {
        // Capslock On: disable blink, turn led on
        blink_interval_ms = 0;
        // board_led_write(true);
      }else
      {
        // Caplocks Off: back to normal blink
        // board_led_write(false);
        blink_interval_ms = BLINK_MOUNTED;
      }
    }
  }
}

//--------------------------------------------------------------------+
// BLINKING TASK
//--------------------------------------------------------------------+
void led_blinking_task(void)
{
  static uint32_t start_ms = 0;
  static bool led_state = false;

  // blink is disabled
  if (!blink_interval_ms) return;

  // Blink every interval ms
  if ( board_millis() - start_ms < blink_interval_ms) return; // not enough time
  start_ms += blink_interval_ms;

  // board_led_write(led_state);
  led_state = 1 - led_state; // toggle
}
