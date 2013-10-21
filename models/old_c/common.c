#include "common.h"
#include "../lib/print.h"
#include KEYBOARD_MODEL

struct {uint8_t *const pin; const uint8_t bit;} column_pins[NCOL] = COLUMN_PINS;
const   uint8_t                                 row_bits[NROW]    = ROW_BITS;

inline void pull_row(uint8_t r) {
  ROW_PORT = (ROW_PORT & ~ROW_MASK) | row_bits[r];
  _delay_us(SETTLE_TIME_US);
}

inline void release_rows(void) {
  PORTD |= ROW_MASK;
}

inline uint8_t probe_column(uint8_t c) {
  return ( *column_pins[c].pin & column_pins[c].bit ) == 0;
}

// 2 = scroll lock, 1 = caps lock, 0 = num lock.
inline void update_leds(uint8_t keyboard_leds) {
#ifdef FLAKE
  PORTB = (PORTB & 0b01111111) | ((~keyboard_leds << 6) & 0b10000000); // Caps Lock
  PORTC = (PORTC & 0b11011111) | ((~keyboard_leds << 5) & 0b00100000); // Win Lock (used as Scroll Lock)
  PORTC = (PORTC & 0b10111111) | ((~keyboard_leds << 4) & 0b01000000); // Scroll Lock
#endif
#ifdef HOOF
  PORTC = (PORTC & 0b11011111) | ((~keyboard_leds << 4) & 0b00100000); // Caps Lock
  PORTC = (PORTC & 0b10111111) | ((~keyboard_leds << 4) & 0b01000000); // Scroll Lock
#endif
#ifdef PAW
  PORTB = (PORTB & 0b01111111) | ((~keyboard_leds << 5) & 0b10000000); // Scroll Lock
  PORTC = (PORTC & 0b11011111) | ((~keyboard_leds << 5) & 0b00100000); // Num Lock
  PORTC = (PORTC & 0b10111111) | ((~keyboard_leds << 5) & 0b01000000); // Caps Lock
#endif
#ifdef PETAL
  PORTB = (PORTB & 0b01111111) | ((~keyboard_leds << 5) & 0b10000000); // Scroll Lock
  PORTC = (PORTC & 0b11011111) | ((~keyboard_leds << 5) & 0b00100000); // Num Lock
  PORTC = (PORTC & 0b10111111) | ((~keyboard_leds << 5) & 0b01000000); // Caps Lock
#endif
}

void keyboard_init() {
  CPU_PRESCALE(0);                // 16MHz operation
  MCUCR |= 0x80; MCUCR |= 0x80;   // Disable JTAG
  struct {uint8_t *const ddr; uint8_t *const port; const uint8_t bits;} input_pins[3] = INPUT_PINS;
  struct {uint8_t *const ddr; uint8_t *const port; const uint8_t bits;} output_pins[3] = OUTPUT_PINS;
  for(int i=0; i<3; i++) {
    *input_pins[i].ddr = *input_pins[i].ddr & ~input_pins[i].bits;
    *input_pins[i].port = *input_pins[i].port | input_pins[i].bits;
    *output_pins[i].ddr = *output_pins[i].ddr | output_pins[i].bits;
    *output_pins[i].port = *output_pins[i].port  & ~output_pins[i].bits;
  }
  poll_timer_setup();
}

void poll_timer_setup(void) {
  TCCR0A |=      // Timer control register 0A
    (1<<WGM01);  // Set CTC, clear timer on compare
  TCCR0B |=      // Timer control register 0A
    (1<<CS00) |  // Prescaler 1024, frequency 15.6kHz (Combined with next line)
    (1<<CS02);   // Prescaler 256, frequency 62.5kHz (This line alone)
  OCR0A = 16;    // Output compare register 0A
}

inline void poll_timer_enable(void) {
  TIMSK0 |=      // Timer interrupt mask register 0
    (1<<OCIE0A); // Enable timer interrupt on compare match with OCR0A
}

inline void poll_timer_disable(void) {
  TIMSK0 &=       // Timer interrupt mask register 0
    ~(1<<OCIE0A); // Disable timer interrupt on compare match with OCR0A
}

void toggle_leds(void) {
}
