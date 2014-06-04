/* CM Storm Quick Fire Rapid replacement controller board parameters. */

#ifndef flake_20140521_h__
#define flake_20140521_h__

#include "common.h"

#define STR_PRODUCT      L"CM Storm Quick Fire Rapid"
#define PRODUCT_ID       0x047D

#define ROW_PORT  PORTD
#define ROW_MASK  0b01111011

#define ROW_BITS \
  {              \
    0b00011011,  \
    0b01000011,  \
    0b01101010,  \
    0b01111001,  \
    0b01100010,  \
    0b01110001,  \
    0b01100001,  \
    0b01110000,  \
    0b01100000,  \
    0b01101000,  \
    0b00101011,  \
    0b00110011,  \
    0b00100011,  \
    0b01111000,  \
    0b00010011,  \
    0b01101001,  \
    0b00001011,  \
    0b00111011,  \
  }

#define COLUMN_PINS \
  {                 \
    {_PINC, _BIT7}, \
    {_PINB, _BIT5}, \
    {_PINB, _BIT4}, \
    {_PINB, _BIT6}, \
    {_PINB, _BIT1}, \
    {_PINB, _BIT2}, \
    {_PINB, _BIT3}, \
    {_PINB, _BIT0}  \
  }

#define INPUT_PINS               \
  {                              \
    {_DDRB, _PORTB, 0b01111111}, \
    {_DDRC, _PORTC, 0b10000000}, \
    {_DDRD, _PORTD, 0b00000000}  \
}

#define OUTPUT_PINS              \
  {                              \
    {_DDRB, _PORTB, 0b10000000}, \
    {_DDRC, _PORTC, 0b01100000}, \
    {_DDRD, _PORTD, 0b01111011}  \
}


#endif
