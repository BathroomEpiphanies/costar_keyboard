/* USB Keyboard Firmware code for generic Teensy Keyboards
 * Copyright (c) 2012 Fredrik Atmer, Bathroom Epiphanies Inc
 * http://www.bathroomepiphanies.com
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
/* Include keycode definitions. */
#include "lib/keycode.h"
/* Extra definitions for AVR stuff. */
#include "lib/avr_extra.h"
/* Include the correct keyboard model. Defined in Makefile. */
#include KEYBOARD_MODEL

#include "lib/usb_keyboard_debug.h"
#include "lib/print.h"

/* A key can be either a normal character or a modifier key. A struct
   is used to keep track of the keycode and type of key. Layouts are
   defined in "KEYBOARD_MODEL".h. */
struct {uint8_t type; uint8_t value;} layout[] = KEYBOARD_LAYOUT;

/* Each keys bounce status is represented by an 8-bit integer. The
   lowest bit is set to 1 by the polling routine if the key is seen as
   pressed, 0 otherwise.

   The remaining seven bits is used as a debouncing register. The
   lowest bit is shifted left at each poll. When the seven register
   bits transits to all ones the key is considered de-bounced and
   added to the send queue. 

   If all register bits transits to zeros the key is considered
   debounced in its released state and removed from the send queue. 
   
   We also need to keep track of which keys that are pressed and
   not. */
struct {uint8_t pressed; uint8_t bounce;} key[NKEY];

/* queue     contains the keys that are to be sent in the HID packet 
   mod_keys  is the bit pattern corresponding to pressed modifier keys */
uint8_t queue[7] = {255,255,255,255,255,255,255};
uint8_t mod_keys = 0;

void init(void);
void send(void);
void key_press(uint8_t k);
void key_release(uint8_t k);
void debug_print(void);


ISR(SCAN_INTERRUPT_FUNCTION) {
  /* We want to be able to scan often enough to fill the debounce
     register within the specified debounce time of the switches (5ms
     for Cherry MX). We do NOT want to enter a call to another scan
     before the previous one finishes. Some care needs to be taken
     when choosing the parameters in poll_timer_setup() located in
     "KEYBOARD_MODEL".c. Scans may take different amount of time to
     finish due to other interrupt based routines. The simple solution
     is to disable the scan interrupts. */
  poll_timer_disable();

  /* Poll the matrix. 

     pull_column and probe_row are defined in
     "KEYBOARD_MODEL".c. probe_row returns 0b00000001 for matrix
     positions where the key is pressed, 0b00000001 for the rest. This
     value is written to the lowest bit in bounce_register.

     If all but the highest bit are ones, the key may be transiting
     from a released to a pressed state, and we have registered the
     key as pressed for seven consecutive polls. If the key is not
     already marked as pressed in key_pressed we consider this a true
     press and not only interference. The key is then added to the
     send queue.

     If all but the highest bit are zeros, the key may be transiting
     from a pressed to a released state, and we have registered the
     key as released for seven consecutive polls. If the key is marked
     as pressed in key_pressed we consider this a true release. The
     key is then removed from the send queue.

     We don't want to release a key on a random glitch in the matrix
     poll. A false release would trigger an extra key press when the
     glitch has been shifted out of the bounce register.

     If noise is not present, and we want faster reaction to a key
     press event, it is possible to trigger the key_press on the first
     positive read of the poll. The release event on the other hand
     should always be debounced. Otherwise there would be several key
     presses on both the press and release event due to bounce. */
  for(uint8_t c = 0, k = 0; c < NCOL; c++) {
    pull_column(c);
    for(uint8_t r = 0; r < NROW; r++, k++) {
      key[k].bounce |= probe_row(r);
      
      if(key[k].bounce == 0b01111111 && !key[k].pressed)
        key_press(k);
      if(key[k].bounce == 0b10000000 &&  key[k].pressed)
        key_release(k);

      key[k].bounce <<= 1;
    }
  }
  release_columns();

  /* Check if the trigger to jump to the bootloader has been
     activated. In this case when both shift keys are pressed at the
     same time.
     jump_bootloader is defined in usb_keyboard.c */
  // if(mod_keys == (uint8_t)(KC_LSFT | KC_RSFT))
  //   jump_bootloader();

  /* Update the keyboard keyboard LEDs. 
     update_leds is defined in "KEYBOARD_MODEL".c */
  update_leds(keyboard_leds);

#ifdef DEBUG
  debug_print();
#endif  

  /* Turn polling back on again. */
  poll_timer_enable();
}


/* Call initialization functions and start polling. */
int main(void) {
  init();
  poll_timer_enable(); //Turn interrupt polling on
  for(ever);
}


/* Translate internal key numers to keycodes, build a HID packet and
   send it. */
void send(void) {
  uint8_t i;
  for(i = 0; i < 6; i++)
    keyboard_keys[i] = queue[i]<255? layout[queue[i]].value: 0;
  keyboard_modifier_keys = mod_keys;
  usb_keyboard_send();
}


/* Add key to the send queue. If it is a modifier its bit pattern is
   added to the modifier byte. */
void key_press(uint8_t k) {
  uint8_t i;
  key[k].pressed = true;
  if(IS_MODIFIER(layout[k]))
    mod_keys |= layout[k].value;
  else {
    for(i = 5; i > 0; i--) 
      queue[i] = queue[i-1];
    queue[0] = k;
  }
  send();
}


/* Remove key from the send queue. If it is a modifier key its bit
   pattern is removed from the modifier byte. */
void key_release(uint8_t k) {
  uint8_t i;
  key[k].pressed = false;
  if(IS_MODIFIER(layout[k]))
    mod_keys &= ~layout[k].value;
  else {
    for(i = 0; i < 6; i++) 
      if(queue[i]==k)
        break;
    for(i = i; i < 6; i++)
      queue[i] = queue[i+1];
  }
  send();
}


/* Call initialization functions. */
void init(void) {
  usb_init();
  while(!usb_configured());
  keyboard_init();
  mod_keys = 0;
  for(uint8_t k = 0; k < NKEY; k++)
    key[k].bounce = key[k].pressed = 0x00;
  sei();  // Enable interrupts
}


/* Prints debug information. */
uint8_t debug_counter = 0;
void debug_print(void) {
  debug_counter++;
  if(debug_counter > 100) {
    debug_counter = 0;
    for(uint8_t i = 0; i < 7; i++)
      phex(queue[i]);
    print("\n");
    for(uint8_t k = 0; k < NKEY; k++)
      phex(key[k].bounce);
    print("\n");
  }
}
