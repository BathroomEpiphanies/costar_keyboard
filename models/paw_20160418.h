/* Filco Majestouch replacement controller board parameters. */

#ifndef paw_20160418_h__
#define paw_20160418_h__

#include "common.h"

#define STR_PRODUCT      L"Filco Majestouch"
#define PRODUCT_ID       0x047D

#define ROW_PORT  PORTB
#define ROW_MASK  0b01111111

#define ROW_BITS \
  {              \
    0b01100100,  \
    0b01101100,  \
    0b01100010,  \
    0b01111010,  \
    0b01100110,  \
    0b01110110,  \
    0b01101110,  \
    0b01111110,  \
    0b01000001,  \
    0b00100001,  \
    0b01101010,  \
    0b01110010,  \
    0b01111100,  \
    0b01110100,  \
    0b01111000,  \
    0b01110000,  \
    0b01100000,  \
    0b01101000   \
  }

#define COLUMN_PINS \
  {                 \
    {_PINC, _BIT7}, \
    {_PIND, _BIT5}, \
    {_PIND, _BIT3}, \
    {_PIND, _BIT1}, \
    {_PINC, _BIT2}, \
    {_PIND, _BIT2}, \
    {_PIND, _BIT4}, \
    {_PIND, _BIT6}  \
  }

#define INPUT_PINS               \
  {                              \
    {_DDRB, _PORTB, 0b00000000}, \
    {_DDRC, _PORTC, 0b10000100}, \
    {_DDRD, _PORTD, 0b01111110}  \
  }

#define OUTPUT_PINS              \
  {                              \
    {_DDRB, _PORTB, 0b11111111}, \
    {_DDRC, _PORTC, 0b01100000}, \
    {_DDRD, _PORTD, 0b00000000}  \
  }

#endif


/*


aq
bp
cr
do
ea
fn
gb
hm
ic
jl
kk
ld
me
nf
og
ph
qi
rj

0
1
2
3
4
5
6
7

abcd




































#define ROW_PORT  PORTB
#define ROW_MASK  0b01111111

#define ROW_BITS \
  {              \
    0b01100000,  \
    0b01110000,  \
    0b01101000,  \
    0b01111000,  \
    0b01100100,  \
    0b01110100,  \
    0b01101100,  \
    0b01111100,  \
    0b01100010,  \
    0b01110010,  \
    0b01101010,  \
    0b01111010,  \
    0b01100110,  \
    0b01110110,  \
    0b01101110,  \
    0b01111110,  \
    0b01000001,  \
    0b00100001   \
  }

#define COLUMN_PINS \
  {                 \
    {_PINC, _BIT2}, \
    {_PINC, _BIT4}, \
    {_PINC, _BIT7}, \
    {_PIND, _BIT0}, \
    {_PIND, _BIT1}, \
    {_PIND, _BIT2}, \
    {_PIND, _BIT3}, \
    {_PIND, _BIT4}, \
    {_PIND, _BIT5}, \
    {_PIND, _BIT6}  \
  }

*/
