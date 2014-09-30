/*
Copyright 2011,2012 Jun Wako <wakojun@gmail.com>
Aggressively modified by Fredrik Atmer 2013

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/* 
 * Keycodes based on HID Usage Keyboard/Keypad Page(0x07) plus special codes
 * http://www.usb.org/developers/devclass_docs/Hut1_12.pdf
 */
#ifndef KEYCODE_H
#define KEYCODE_H

/* Definitions of keys. 

   There are two types of keys on a keyboard. Normal keys and modifier
   keys. They are handled differently from eachother. 

   The currently pressed modifier keys are indicated by setting bits
   in the 'mod_keys' variable. Each modifer has its own bit.

   Normal keys are added to a queue when pressed. The queue has a
   fixed length of 'QUEUE_LENGTH'. If the queue becomes full the earliest
   pressed key is pushed out at the end of the queue. The keycode
   value for normal keys are stored in the queue.

   All keys are defined by a struct {is_modifier, value} where the
   'is_modifier'-field is set to true for modifier keys, and false for
   normal keys.

   For modifier keys the 'value'-field is a bit pattern where the
   single bit representing that specific modifier is set.

   For normal keys the 'value'-field is the keycode for that key. */

/* Short names */
#define KC_NO   {false, KEY_NO}

#define KC_LCTL {true, 0x01}
#define KC_LSFT {true, 0x02}
#define KC_LALT {true, 0x04}
#define KC_LGUI {true, 0x08}
#define KC_RCTL {true, 0x10}
#define KC_RSFT {true, 0x20}
#define KC_RALT {true, 0x40}
#define KC_RGUI {true, 0x80}

#define KC_A    {false, KEY_A}
#define KC_B    {false, KEY_B}
#define KC_C    {false, KEY_C}
#define KC_D    {false, KEY_D}
#define KC_E    {false, KEY_E}
#define KC_F    {false, KEY_F}
#define KC_G    {false, KEY_G}
#define KC_H    {false, KEY_H}
#define KC_I    {false, KEY_I}
#define KC_J    {false, KEY_J}
#define KC_K    {false, KEY_K}
#define KC_L    {false, KEY_L}
#define KC_M    {false, KEY_M}
#define KC_N    {false, KEY_N}
#define KC_O    {false, KEY_O}
#define KC_P    {false, KEY_P}
#define KC_Q    {false, KEY_Q}
#define KC_R    {false, KEY_R}
#define KC_S    {false, KEY_S}
#define KC_T    {false, KEY_T}
#define KC_U    {false, KEY_U}
#define KC_V    {false, KEY_V}
#define KC_W    {false, KEY_W}
#define KC_X    {false, KEY_X}
#define KC_Y    {false, KEY_Y}
#define KC_Z    {false, KEY_Z}
#define KC_1    {false, KEY_1}
#define KC_2    {false, KEY_2}
#define KC_3    {false, KEY_3}
#define KC_4    {false, KEY_4}
#define KC_5    {false, KEY_5}
#define KC_6    {false, KEY_6}
#define KC_7    {false, KEY_7}
#define KC_8    {false, KEY_8}
#define KC_9    {false, KEY_9}
#define KC_0    {false, KEY_0}
#define KC_ENT  {false, KEY_ENTER}
#define KC_ESC  {false, KEY_ESCAPE}
#define KC_BSPC {false, KEY_BSPACE}
#define KC_TAB  {false, KEY_TAB}
#define KC_SPC  {false, KEY_SPACE}
#define KC_MINS {false, KEY_MINUS}
#define KC_EQL  {false, KEY_EQUAL}
#define KC_LBRC {false, KEY_LBRACKET}
#define KC_RBRC {false, KEY_RBRACKET}
#define KC_BSLS {false, KEY_BSLASH}
#define KC_NUHS {false, KEY_NONUS_HASH}
#define KC_SCLN {false, KEY_SCOLON}
#define KC_QUOT {false, KEY_QUOTE}
#define KC_GRV  {false, KEY_GRAVE}
#define KC_COMM {false, KEY_COMMA}
#define KC_DOT  {false, KEY_DOT}
#define KC_SLSH {false, KEY_SLASH}
#define KC_CAPS {false, KEY_CAPSLOCK}
#define KC_F1   {false, KEY_F1}
#define KC_F2   {false, KEY_F2}
#define KC_F3   {false, KEY_F3}
#define KC_F4   {false, KEY_F4}
#define KC_F5   {false, KEY_F5}
#define KC_F6   {false, KEY_F6}
#define KC_F7   {false, KEY_F7}
#define KC_F8   {false, KEY_F8}
#define KC_F9   {false, KEY_F9}
#define KC_F10  {false, KEY_F10}
#define KC_F11  {false, KEY_F11}
#define KC_F12  {false, KEY_F12}
#define KC_PSCR {false, KEY_PSCREEN}
#define KC_SLCK {false, KEY_SCKLOCK}
#define KC_PAUS {false, KEY_PAUSE}
#define KC_INS  {false, KEY_INSERT}
#define KC_HOME {false, KEY_HOME}
#define KC_PGUP {false, KEY_PGUP}
#define KC_DEL  {false, KEY_DELETE}
#define KC_END  {false, KEY_END}
#define KC_PGDN {false, KEY_PGDOWN}
#define KC_RGHT {false, KEY_RIGHT}
#define KC_LEFT {false, KEY_LEFT}
#define KC_DOWN {false, KEY_DOWN}
#define KC_UP   {false, KEY_UP}
#define KC_NLCK {false, KEY_NUMLOCK}
#define KC_PSLS {false, KEY_KP_SLASH}
#define KC_PAST {false, KEY_KP_ASTERISK}
#define KC_PMNS {false, KEY_KP_MINUS}
#define KC_PPLS {false, KEY_KP_PLUS}
#define KC_PENT {false, KEY_KP_ENTER}
#define KC_P1   {false, KEY_KP_1}
#define KC_P2   {false, KEY_KP_2}
#define KC_P3   {false, KEY_KP_3}
#define KC_P4   {false, KEY_KP_4}
#define KC_P5   {false, KEY_KP_5}
#define KC_P6   {false, KEY_KP_6}
#define KC_P7   {false, KEY_KP_7}
#define KC_P8   {false, KEY_KP_8}
#define KC_P9   {false, KEY_KP_9}
#define KC_P0   {false, KEY_KP_0}
#define KC_PDOT {false, KEY_KP_DOT}
#define KC_NUBS {false, KEY_NONUS_BSLASH}
#define KC_APP  {false, KEY_APPLICATION}
#define KC_PEQL {false, KEY_KP_EQUAL}
#define KC_PCMM {false, KEY_KP_COMMA}
#define KC_BRK  {false, KEY_PAUSE}
#define KC_ERAS {false, KEY_ALT_ERASE}
#define KC_CLR  {false, KEY_CLEAR}
/* Japanese specific */
#define KC_ZKHK {false, KEY_GRAVE}
#define KC_RO   {false, KEY_INT1}
#define KC_KANA {false, KEY_INT2}
#define KC_JYEN {false, KEY_INT3}
#define KC_HENK {false, KEY_INT4}
#define KC_MHEN {false, KEY_INT5}


/* Long names */
/* USB HID Keyboard/Keypad Usage(0x07) */
enum hid_keyboard_keypad_usage {
    KEY_NO               = 0x00,
    KEY_ROLL_OVER,
    KEY_POST_FAIL,
    KEY_UNDEFINED,
    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,               /* 0x10 */
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,
    KEY_1,
    KEY_2,
    KEY_3,               /* 0x20 */
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_0,
    KEY_ENTER,
    KEY_ESCAPE,
    KEY_BSPACE,
    KEY_TAB,
    KEY_SPACE,
    KEY_MINUS,
    KEY_EQUAL,
    KEY_LBRACKET,
    KEY_RBRACKET,        /* 0x30 */
    KEY_BSLASH,          /* \ (and |) */
    KEY_NONUS_HASH,      /* Non-US # and ~ */
    KEY_SCOLON,          /* ; (and :) */
    KEY_QUOTE,           /* ' and " */
    KEY_GRAVE,           /* Grave accent and tilde */
    KEY_COMMA,           /* , and < */
    KEY_DOT,             /* . and > */
    KEY_SLASH,           /* / and ? */
    KEY_CAPSLOCK,
    KEY_F1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,              /* 0x40 */
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_F11,
    KEY_F12,
    KEY_PSCREEN,
    KEY_SCKLOCK,
    KEY_PAUSE,
    KEY_INSERT,
    KEY_HOME,
    KEY_PGUP,
    KEY_DELETE,
    KEY_END,
    KEY_PGDOWN,
    KEY_RIGHT,
    KEY_LEFT,            /* 0x50 */
    KEY_DOWN,
    KEY_UP,
    KEY_NUMLOCK,
    KEY_KP_SLASH,
    KEY_KP_ASTERISK,
    KEY_KP_MINUS,
    KEY_KP_PLUS,
    KEY_KP_ENTER,
    KEY_KP_1,
    KEY_KP_2,
    KEY_KP_3,
    KEY_KP_4,
    KEY_KP_5,
    KEY_KP_6,
    KEY_KP_7,
    KEY_KP_8,            /* 0x60 */
    KEY_KP_9,
    KEY_KP_0,
    KEY_KP_DOT,
    KEY_NONUS_BSLASH,    /* Non-US \ and | */
    KEY_APPLICATION,
    KEY_POWER,
    KEY_KP_EQUAL,
    KEY_F13,
    KEY_F14,
    KEY_F15,
    KEY_F16,
    KEY_F17,
    KEY_F18,
    KEY_F19,
    KEY_F20,
    KEY_F21,             /* 0x70 */
    KEY_F22,
    KEY_F23,
    KEY_F24,
    KEY_EXECUTE,
    KEY_HELP,
    KEY_MENU,
    KEY_SELECT,
    KEY_STOP,
    KEY_AGAIN,
    KEY_UNDO,
    KEY_CUT,
    KEY_COPY,
    KEY_PASTE,
    KEY_FIND,
    KEY__MUTE,
    KEY__VOLUP,          /* 0x80 */
    KEY__VOLDOWN,
    KEY_LOCKING_CAPS,    /* locking Caps Lock */
    KEY_LOCKING_NUM,     /* locking Num Lock */
    KEY_LOCKING_SCROLL,  /* locking Scroll Lock */
    KEY_KP_COMMA,
    KEY_KP_EQUAL_AS400,  /* equal sign on AS/400 */
    KEY_INT1,
    KEY_INT2,
    KEY_INT3,
    KEY_INT4,
    KEY_INT5,
    KEY_INT6,
    KEY_INT7,
    KEY_INT8,
    KEY_INT9,
    KEY_LANG1,           /* 0x90 */
    KEY_LANG2,
    KEY_LANG3,
    KEY_LANG4,
    KEY_LANG5,
    KEY_LANG6,
    KEY_LANG7,
    KEY_LANG8,
    KEY_LANG9,
    KEY_ALT_ERASE,
    KEY_SYSREQ,
    KEY_CANCEL,
    KEY_CLEAR,
    KEY_PRIOR,
    KEY_RETURN,
    KEY_SEPARATOR,
    KEY_OUT,             /* 0xA0 */
    KEY_OPER,
    KEY_CLEAR_AGAIN,
    KEY_CRSEL,
    KEY_EXSEL,           /* 0xA4 */

    /* Modifiers */
    KEY_LCTRL            = 0xE0,
    KEY_LSHIFT,
    KEY_LALT,
    KEY_LGUI,
    KEY_RCTRL,
    KEY_RSHIFT,
    KEY_RALT,
    KEY_RGUI,
};

#endif
