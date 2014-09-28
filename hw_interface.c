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

#include "lib/avr_extra.h"
#include "hw_interface.h"
#include KEYBOARD_MODEL_FILE

struct {uint8_t *const pin; const uint8_t bit;} column_pins[NCOL] = COLUMN_PINS;
const   uint8_t                                 row_bits[NROW]    = ROW_BITS;

/* The `pin` struct describes a AVR pin.
 * See <http://maxembedded.com/2011/06/10/port-operations-in-avr/> for an
 * overview of how AVR i/o works. */
struct pin {uint8_t *const ddr; uint8_t *const port; const uint8_t bits;};

void pull_row(uint8_t r) {
  ROW_PORT = (ROW_PORT & ~ROW_MASK) | row_bits[r];
  _delay_us(SETTLE_TIME_US);
}

void release_rows(void) {
  PORTD |= ROW_MASK;
}

bool probe_column(uint8_t c) {
  return (*column_pins[c].pin & column_pins[c].bit) == 0;
}

// 2 = scroll lock, 1 = caps lock, 0 = num lock.
void update_leds(uint8_t keyboard_leds) {
  // TODO: Replace by some smart definitions in corresponding board.h-files.
#if defined hoof_20131001_h__
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
#elif defined paw_20130602_h__
  PORTB = (PORTB & 0b01111111) | ((~keyboard_leds << 5) & 0b10000000); // Scroll Lock
  PORTC = (PORTC & 0b11011111) | ((~keyboard_leds << 5) & 0b00100000); // Num Lock
  PORTC = (PORTC & 0b10111111) | ((~keyboard_leds << 5) & 0b01000000); // Caps Lock
#elif defined petal_20131001_h__
  PORTB = (PORTB & 0b01111111) | ((~keyboard_leds << 5) & 0b10000000); // Scroll Lock
  PORTC = (PORTC & 0b11011111) | ((~keyboard_leds << 5) & 0b00100000); // Num Lock
  PORTC = (PORTC & 0b10111111) | ((~keyboard_leds << 5) & 0b01000000); // Caps Lock
#else
  #error Do not know how to implement update_leds()
#endif
}

void keyboard_init() {
  CPU_PRESCALE(0);                // 16MHz operation
  MCUCR |= 0x80; MCUCR |= 0x80;   // Disable JTAG
  struct pin input_pins[3] = INPUT_PINS;
  struct pin output_pins[3] = OUTPUT_PINS;
  for(int i=0; i<3; i++) {
    *input_pins[i].ddr = *input_pins[i].ddr & ~input_pins[i].bits;
    *input_pins[i].port = *input_pins[i].port | input_pins[i].bits;
    *output_pins[i].ddr = *output_pins[i].ddr | output_pins[i].bits;
    *output_pins[i].port = *output_pins[i].port  & ~output_pins[i].bits;
  }
  poll_timer_setup();
}

/* ### poll_timer_setup
 *
 * Setup timer so to trigger an interrupt every 1.024 ms.
 *
 * The frequency of the timer is set to 1/1024th of the clock frequency.
 * Each step increments the counter, until the counter hits 16 and
 * triggers an interrupt. After the interrupt is triggered, the counter
 * goes back to zero.
 *
 * Each step takes (F_CPU / 1024)^-1 = 0.064 ms, an interrupt is triggered
 * every 16 * 0.064 ms = 1.024 ms.
 */
void poll_timer_setup(void) {
  TCCR0A |=      // Timer0 control register A: timer mode
    (1<<WGM01);  // Set CTC, clear timer on compare
  TCCR0B |=      // Timer0 control register B: step frequency
    (1<<CS00) |  // Prescaler 1024, frequency 15.6kHz (Combined with next line)
    (1<<CS02);   // Prescaler 256, frequency 62.5kHz (This line alone)
  OCR0A = 16;    // Set Timer0 comparison to 16 (the number of steps)
}

/* ### poll_timer_enable
 *
 * Enable the timer that will run the polling routing when it will go
 * off.
 *
 * The timer register must have been set up before `poll_timer_enable`
 * is called.
 */
void poll_timer_enable(void) {
  TIMSK0 |=      // Timer interrupt mask register 0
    (1<<OCIE0A); // Enable timer interrupt on compare match with OCR0A
}

/* ### poll_timer_disable
 *
 * Disable the polling timer. `poll_timer_enable` can be used to enable
 * the timer again.
 */
void poll_timer_disable(void) {
  TIMSK0 &=       // Timer interrupt mask register 0
    ~(1<<OCIE0A); // Disable timer interrupt on compare match with OCR0A
}
