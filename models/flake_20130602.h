/* CM Storm Quick Fire Rapid replacement controller board parameters. */

#ifndef flake_20130602_h__
#define flake_20130602_h__

#include "common.h"

#define STR_PRODUCT      L"CM Storm Quick Fire Rapid"
#define PRODUCT_ID       0x047D

#define ROW_PORT  PORTB
#define ROW_MASK  0b01111110
#define ROW_BITS \ 
  {              \
    0b00111010,  \
    0b01011000,  \
    0b01110000,  \
    0b01101110,  \
    0b01101100,  \
    0b01101010,  \
    0b01101000,  \
    0b01100100,  \
    0b01100000,  \
    0b01100010,  \
    0b00011010,  \
    0b00011000,  \
    0b00111100,  \
    0b01100110,  \
    0b00111000,  \
    0b01110010,  \
    0b00011110,  \
    0b00111110   \
  }

#define COLUMN_PINS \
  {                 \
    {_PINC, _BIT2}, \
    {_PIND, _BIT0}, \
    {_PIND, _BIT1}, \
    {_PINC, _BIT7}, \
    {_PIND, _BIT5}, \
    {_PIND, _BIT4}, \
    {_PIND, _BIT2}, \
    {_PIND, _BIT6}  \
  }

#define INPUT_PINS               \
  {                              \
    {_DDRB, _PORTB, 0b00000000}, \
    {_DDRC, _PORTC, 0b10000100}, \
    {_DDRD, _PORTD, 0b01110111}  \
  }

#define OUTPUT_PINS              \
  {                              \
    {_DDRB, _PORTB, 0b11111110}, \
    {_DDRC, _PORTC, 0b01100000}, \
    {_DDRD, _PORTD, 0b00000000}  \
  }

#endif
