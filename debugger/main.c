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

/* This is a simple firmware that prints a debug report of which keys
 * are detected as pressed. It also flashes all the LEDs. Load this
 * firmware onto the keyboard to be tested, put the cursor in a text
 * editor, and start pressing keys.
 * 
 * The row and column indices of the pressed keys will be typed into
 * the text field. The update interval should be between 0.5 and 1
 * second.
 * 
 * 
 */

#include <avr/pgmspace.h>
#include "../libraries/usb_keyboard_debug.h"
#include "../libraries/print.h"
#include "../libraries/hw_interface.h"

#include KEYBOARD_MODEL_FILE

struct pin {uint8_t *const ddr; uint8_t *const port; const uint8_t bits;};
//struct {uint8_t *const pin; const uint8_t bit;} column_pins[NUMBER_OF_COLUMNS] = COLUMN_PINS;
//const   uint8_t                                 row_bits[NUMBER_OF_ROWS]       = ROW_BITS;
uint8_t leds = 0b00000111, mask = 0b00000111;

uint8_t alp_index[] = {KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J,
                       KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T,
                       KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z};

uint8_t num_index[] = {KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9};

void update_leds(uint8_t keyboard_leds);
  
int main(void) {
  usb_init();
  while(!usb_configured());
  CPU_PRESCALE(0);
  MCUCR |= 0x80; MCUCR |= 0x80;

  // Init keyboard
  struct pin input_pins[3] = INPUT_PINS;
  struct pin output_pins[3] = OUTPUT_PINS;

  for(int i=0; i<3; i++) {
    *input_pins[i].ddr = *input_pins[i].ddr & ~input_pins[i].bits;
    *input_pins[i].port = *input_pins[i].port | input_pins[i].bits;
    *output_pins[i].ddr = *output_pins[i].ddr | output_pins[i].bits;
    *output_pins[i].port = *output_pins[i].port  & ~output_pins[i].bits;
  }

  sei();

  // Start looping
  for(;;) {

    // usb_keyboard_press(KEY_A+name[i], 0);

    bool test = false;
    
    for(uint8_t r = 0, k = 0; r < NUMBER_OF_ROWS; r++) {
      ROW_PORT = (ROW_PORT & ~ROW_MASK) | row_bits[r]; _delay_us(1);  //  pull row r;
      for(uint8_t c = 0; c < NUMBER_OF_COLUMNS; c++, k++) {
        if( (*column_pins[c].pin & column_pins[c].bit) == 0 ) { // probe column c;
          
          usb_keyboard_press(alp_index[r], 0);
          usb_keyboard_press(num_index[c], 0);
          usb_keyboard_press(KEY_SPACE, 0);

          test = true;
          
        }
      }
    }

    if(test)
      usb_keyboard_press(KEY_ENTER, 0);

    leds = mask - leds;
    update_leds(leds);

    _delay_ms(500);
    
  }
}




// 2 = scroll lock, 1 = caps lock, 0 = num lock.
void update_leds(uint8_t keyboard_leds) {
  // TODO: Replace by some smart definitions in corresponding board.h-files.
#if defined hoof_20131001_h__
  PORTC = (PORTC & 0b11011111) | ((~keyboard_leds << 3) & 0b00100000); // Caps Lock
  PORTC = (PORTC & 0b10111111) | ((~keyboard_leds << 5) & 0b01000000); // Scroll Lock
#elif defined hoof_20150108_h__
  PORTC = (PORTC & 0b11011111) | ((~keyboard_leds << 3) & 0b00100000); // Caps Lock
  PORTC = (PORTC & 0b10111111) | ((~keyboard_leds << 5) & 0b01000000); // Scroll Lock
#elif defined flake_20130602_h__
  PORTB = (PORTB & 0b01111111) | ((~keyboard_leds << 6) & 0b10000000); // Caps Lock
  PORTC = (PORTC & 0b11011111) | ((~keyboard_leds << 5) & 0b00100000); // Win Lock (used as Num Lock)
  PORTC = (PORTC & 0b10111111) | ((~keyboard_leds << 4) & 0b01000000); // Scroll Lock
#elif defined flake_20140521_h__
  PORTB = (PORTB & 0b01111111) | ((~keyboard_leds << 7) & 0b10000000); // Caps Lock
  PORTC = (PORTC & 0b11011111) | ((~keyboard_leds << 4) & 0b00100000); // Win Lock (used as Num Lock)
  PORTC = (PORTC & 0b10111111) | ((~keyboard_leds << 4) & 0b01000000); // Scroll Lock
#elif defined floice_20151102_h__
  PORTB = (PORTB & 0b01111111) | ((~keyboard_leds << 6) & 0b10000000); // Caps Lock
  PORTC = (PORTC & 0b11011111) | ((~keyboard_leds << 5) & 0b00100000); // Win Lock (used as Num Lock)
  PORTC = (PORTC & 0b10111111) | ((~keyboard_leds << 4) & 0b01000000); // Scroll Lock
#elif defined paw_20130602_h__
  PORTB = (PORTB & 0b01111111) | ((~keyboard_leds << 5) & 0b10000000); // Scroll Lock
  PORTC = (PORTC & 0b11011111) | ((~keyboard_leds << 5) & 0b00100000); // Num Lock
  PORTC = (PORTC & 0b10111111) | ((~keyboard_leds << 5) & 0b01000000); // Caps Lock
#elif defined petal_20131001_h__
  PORTB = (PORTB & 0b01111111) | ((~keyboard_leds << 5) & 0b10000000); // Scroll Lock
  PORTC = (PORTC & 0b11011111) | ((~keyboard_leds << 5) & 0b00100000); // Num Lock
  PORTC = (PORTC & 0b10111111) | ((~keyboard_leds << 5) & 0b01000000); // Caps Lock
#elif defined squid_20140518_h__
  PORTB = (PORTB & 0b01111111) | ((~keyboard_leds << 5) & 0b10000000); // Scroll Lock
  PORTC = (PORTC & 0b11011111) | ((~keyboard_leds << 5) & 0b00100000); // Num Lock
  PORTC = (PORTC & 0b10111111) | ((~keyboard_leds << 5) & 0b01000000); // Caps Lock
#else
  #error Do not know how to implement update_leds()
#endif
}
