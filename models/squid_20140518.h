/* Rosewill replacement controller board parameters. */

#ifndef squid_20140518_h__
#define squid_20140518_h__

#include "common.h"

#define STR_PRODUCT      L"CM Storm Quick Fire XT"
#define PRODUCT_ID       0x047D

#define NUM_LOCK(x)    ((x) == ON ? (PORTC &= ~0b00100000) : (PORTC |= 0b00100000))
#define CAPS_LOCK(x)   ((x) == ON ? (PORTC &= ~0b01000000) : (PORTC |= 0b01000000))
#define SCROLL_LOCK(x) ((x) == ON ? (PORTB &= ~0b10000000) : (PORTB |= 0b10000000))

#define ROW_PORT  PORTD
#define ROW_MASK  0b01111110

#define ROW_BITS \
  {              \
    0b01100010,  \
    0b01101000,  \
    0b01101100,  \
    0b01110000,  \
    0b01111000,  \
    0b01100000,  \
    0b01110100,  \
    0b01100100,  \
    0b01111100,  \
    0b01101010,  \
    0b00110110,  \
    0b00010110,  \
    0b01001110,  \
    0b00111110,  \
    0b00011110,  \
    0b01000110,  \
    0b00100110,  \
    0b00101110,  \
    ROW_MASK     \
  }

#define COLUMN_PINS \
  {                 \
    {_PINB, _BIT1}, \
    {_PINC, _BIT2}, \
    {_PINB, _BIT6}, \
    {_PINB, _BIT4}, \
    {_PINB, _BIT3}, \
    {_PINB, _BIT2}, \
    {_PINB, _BIT0}, \
    {_PINB, _BIT5}  \
  }

#define INPUT_PINS               \
  {                              \
    {_DDRB, _PORTB, 0b01111111}, \
    {_DDRC, _PORTC, 0b00000100}, \
    {_DDRD, _PORTD, 0b00000000}  \
  }

#define OUTPUT_PINS              \
  {                              \
    {_DDRB, _PORTB, 0b10000000}, \
    {_DDRC, _PORTC, 0b01100000}, \
    {_DDRD, _PORTD, 0b01111111}  \
  }

#endif
