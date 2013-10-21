/* Tenkeyless replacement controller board specifics. */

#include "paw.h"

struct { uint8_t *const pin; const uint8_t bit; } cols[NCOL] = 
  {
    {_PINC, _BIT2}, {_PINB, _BIT1}, {_PINB, _BIT2}, {_PINB, _BIT3},
    {_PINC, _BIT7}, {_PINB, _BIT4}, {_PINB, _BIT5}, {_PINB, _BIT6} 
  };

/* Specifies the bit patterns to activate the columns. The columns are
   driven through two 4-10 decoders via pins D012456. The two lower bits
   are common among the decoders. The two higher bits are connected to
   separate pins on the controller. Setting both of a decoders high
   bits to one deactivates it. */
const uint8_t row_bits[NROW] =  
  {
    0b01100100, 0b01010100, 0b01000100, 0b00010111, 0b00000111, 0b01110011,
    0b01100011, 0b01010011, 0b01000011, 0b00110011, 0b00100011, 0b00010011,
    0b00000011, 0b01010110, 0b01000110, 0b01110101, 0b01000101, 0b01110100 
  };

/* Activate one of the columns in the matrix. And wait for the
   electrical state to settle. */
inline void pull_row(uint8_t r) {
  PORTD = (PORTD & 0b10001000) | row_bits[r];
  _delay_us(SETTLE_TIME_US);
}

/* De-activate columns. */
inline void release_rows(void) {
  PORTD = (PORTD & 0b10001000) | 0b01110111;
}

/* Probe one of the rows to look for pressed keys. Returns 0b00000001
   if there is a key pressed in the row (while the corresponding
   column is activated) and 0b00000000 otherwise. */
inline uint8_t probe_column(uint8_t c) {
  return ( *cols[c].pin & cols[c].bit ) == 0;
}

/* Update keyboard LEDs. Which LEDs to turn on is indicated by bits in
   keyboard_leds.
   bit 2 = scroll lock, bit 1 = caps lock, bit 0 = num lock.
   LEDs are active low. The contents of keyboard_leds is shifted into
   the correct position and masked out. */
inline void update_leds(uint8_t keyboard_leds) {
  /* Scroll Lock on pin B7. */
  PORTB = (PORTB & 0b01111111) | ((~keyboard_leds << 5) & 0b10000000);
  /* Num Lock on pin C5. */
  PORTC = (PORTC & 0b11011111) | ((~keyboard_leds << 5) & 0b00100000);
  /* Caps Lock on pin C6. */
  PORTC = (PORTC & 0b10111111) | ((~keyboard_leds << 5) & 0b01000000);
}

void keyboard_init() {
  /* 16MHz operation */
  CPU_PRESCALE(0);
  /* Disable JTAG */
  MCUCR |= 0x80; MCUCR |= 0x80;
  /* Column pins are set as outputs. */
  DDRD |= 0b01110111; PORTD &= 0b10001000;
  /* Row pins are set as inputs (internal pull-up). */
  DDRC &= 0b01111011; PORTC |= 0b10000100;
  DDRB &= 0b10000001; PORTB |= 0b01111110;
  /* LEDs pins set as outputs. */
  DDRB |= 0b10000000;
  DDRC |= 0b01100000;
  poll_timer_setup();
}

/* Polling of the keyboard matrix is done on regular intervals. This
   is acheived by an interrupt on timer 0. The timer is scaled down to
   15600Hz and the match is done when it reaches 16. This gives a
   polling frequency of 975Hz. If bouncing still occurs the value of
   OCR0A can be increased to decrease the polling frequency. */
void poll_timer_setup(void) {
  TCCR0A |=      // Timer control register 0A
    (1<<WGM01);  // Set CTC, clear timer on compare
  TCCR0B |=      // Timer control register 0A
    (1<<CS00) |  // Prescaler 1024, frequency 15.6kHz (Combined with next line)
    (1<<CS02);   // Prescaler 256, frequency 62.5kHz (This line alone)
  OCR0A = 16;    // Output compare register 0A
}

/* Turn on polling. */
inline void poll_timer_enable(void) {
  TIMSK0 |=      // Timer interrupt mask register 0
    (1<<OCIE0A); // Enable timer interrupt on compare match with OCR0A
}

/* Turn off polling. */
inline void poll_timer_disable(void) {
  TIMSK0 &=       // Timer interrupt mask register 0
    ~(1<<OCIE0A); // Disable timer interrupt on compare match with OCR0A
}

/* Blink the LEDs, mostly for debugging purposes. */
void toggle_leds(void) {
}
