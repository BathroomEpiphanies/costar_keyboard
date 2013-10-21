#ifndef hw_interface__
#define hw_interface__

#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lib/avr_extra.h"
#include KEYBOARD_MODEL

void pull_row(uint8_t row);
void release_rows(void);
bool probe_column(uint8_t col);
void update_leds(uint8_t keyboard_leds);
void keyboard_init(void);
void poll_timer_setup(void);
void poll_timer_enable(void);
void poll_timer_disable(void);

#endif
