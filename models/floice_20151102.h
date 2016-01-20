/* CM Storm Quick Fire Rapid replacement controller board parameters. */

#ifndef floice_20151102_h__
#define floice_20151102_h__

#include "common.h"

#define STR_PRODUCT      L"CM Storm Quick Fire Rapid"
#define PRODUCT_ID       0x047D

#define ROW_PORT  PORTB
#define ROW_MASK  0b00101111

#define ROW_BITS \
  {              \
    0b00001101,  \
    0b00000000,  \
    0b00100000,  \
    0b00001000,  \
    0b00001100,  \
    0b00100010,  \
    0b00100110,  \
    0b00101010,  \
    0b00101110,  \
    0b00101100,  \
    0b00000001,  \
    0b00001110,  \
    0b00001001,  \
    0b00101000,  \
    0b00000011,  \
    0b00100100,  \
    0b00001111,  \
    0b00000100,  \
    0b00001011,  \
    0b00001010,  \
    0b00000110,  \
    0b00000010,  \
    0b00000101,  \
    0b00000111   \
  }

#define COLUMN_PINS \
  {                 \
    {_PINC, _BIT7}, \
    {_PINC, _BIT4}, \
    {_PINB, _BIT4}, \
    {_PINB, _BIT6}, \
    {_PIND, _BIT0}, \
    {_PIND, _BIT4}, \
    {_PINC, _BIT2}, \
    {_PIND, _BIT1}  \
  }

#define INPUT_PINS               \
  {                              \
    {_DDRB, _PORTB, 0b01010000}, \
    {_DDRC, _PORTC, 0b10010100}, \
    {_DDRD, _PORTD, 0b00010011}  \
  }

#define OUTPUT_PINS              \
  {                              \
    {_DDRB, _PORTB, 0b10101111}, \
    {_DDRC, _PORTC, 0b01100000}, \
    {_DDRD, _PORTD, 0b00000000}  \
  }

#endif
