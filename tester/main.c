#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "../libraries/usb_keyboard_debug.h"
#include "../libraries/print.h"
#include "../libraries/hw_interface.h"
#include KEYBOARD_MODEL_FILE

char tmp_str[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

uint8_t leds = 0b00000000, mask = 0b00000111;


int main(void) {
  CPU_PRESCALE(0);
  MCUCR |= 0x80; MCUCR |= 0x80;
  usb_init();
  while(!usb_configured());
  keyboard_init();

  for(uint8_t t=0; t<6; t++) {
    for(uint8_t r = 0; r < NUMBER_OF_ROWS; r++) {
      pull_row(r);
      _delay_us(16);
      sprintf(tmp_str, "row %02d: ", r);
      print_S(tmp_str);
      _delay_ms(5);
      for(uint8_t c = 0; c < NUMBER_OF_COLUMNS; c++) {
        bool b = probe_column(c);
        if(!b) {
          sprintf(tmp_str, "%02d %02d\n\n", r, c);
          print_S("\n\nSomething went wrong here: ");
          print_S(tmp_str);
          _delay_ms(1000);
        }
        else
          print_S("1");
      }
      release_rows();
      print_S(" ");
      for(uint8_t c = 0; c < NUMBER_OF_COLUMNS; c++) {
        bool b = probe_column(c);
        if(b) {
          sprintf(tmp_str, "%02d %02d\n\n", r, c);
          print_S("\n\nSomething went wrong here: ");
          print_S(tmp_str);
          _delay_ms(1000);
        }
        else
          print_S("0");
      }
      print_S("\n");
      leds = mask-leds;
      update_leds(leds);
      _delay_ms(200);
    }
  }
  
  EIMSK = 0; PCICR = 0; SPCR = 0; ACSR = 0; EECR = 0;
  TIMSK0 = 0; TIMSK1 = 0; UCSR1B = 0;
  DDRB = 0; DDRC = 0; DDRD = 0;
  PORTB = 0; PORTC = 0; PORTD = 0;
  asm volatile("jmp 0x7000");

}
