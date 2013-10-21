/* Rosewill replacement controller board parameters. */

#ifndef petal_h__
#define petal_h__

#include "common.h"

#define STR_PRODUCT      L"Rosewill"
#define PRODUCT_ID       0x047D

#define ROW_PORT  PORTD
#define ROW_MASK  0b01110111
#define ROW_BITS                                                            \
  {                                                                         \
    0b01110000, 0b01100100, 0b01100000, 0b01000111, 0b01000011, 0b00110111, \
    0b00110011, 0b00100111, 0b00100011, 0b00010111, 0b00010011, 0b00000111, \
    0b00000011, 0b01100101, 0b01100001, 0b01110110, 0b01110010, 0b01100110  \
  }
#define COLUMN_PINS                                                 \
  {                                                                 \
    {_PINC, _BIT2}, {_PINB, _BIT3}, {_PINB, _BIT4}, {_PINB, _BIT2}, \
    {_PINB, _BIT1}, {_PINB, _BIT5}, {_PINB, _BIT6}, {_PINC, _BIT7}  \
  }
#define INPUT_PINS  {{_DDRB, _PORTB, 0b01111110}, {_DDRC, _PORTC, 0b10000100}, {_DDRD, _PORTD, 0b00000000}}
#define OUTPUT_PINS {{_DDRB, _PORTB, 0b10000000}, {_DDRC, _PORTC, 0b01100000}, {_DDRD, _PORTD, 0b01110111}}

#endif
