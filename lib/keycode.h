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

#define NORMAL   0x00
#define MODIFIER 0x01

#define IS_MODIFIER(key) ((key).type == MODIFIER)

/* Short names */
#define KC_NO   {NORMAL, KEY_NO}

#define KC_LCTL {MODIFIER, 0x01}
#define KC_LSFT {MODIFIER, 0x02}
#define KC_LALT {MODIFIER, 0x04}
#define KC_LGUI {MODIFIER, 0x08}
#define KC_RCTL {MODIFIER, 0x10}
#define KC_RSFT {MODIFIER, 0x20}
#define KC_RALT {MODIFIER, 0x40}
#define KC_RGUI {MODIFIER, 0x80}

#define KC_A    {NORMAL, KEY_A}
#define KC_B    {NORMAL, KEY_B}
#define KC_C    {NORMAL, KEY_C}
#define KC_D    {NORMAL, KEY_D}
#define KC_E    {NORMAL, KEY_E}
#define KC_F    {NORMAL, KEY_F}
#define KC_G    {NORMAL, KEY_G}
#define KC_H    {NORMAL, KEY_H}
#define KC_I    {NORMAL, KEY_I}
#define KC_J    {NORMAL, KEY_J}
#define KC_K    {NORMAL, KEY_K}
#define KC_L    {NORMAL, KEY_L}
#define KC_M    {NORMAL, KEY_M}
#define KC_N    {NORMAL, KEY_N}
#define KC_O    {NORMAL, KEY_O}
#define KC_P    {NORMAL, KEY_P}
#define KC_Q    {NORMAL, KEY_Q}
#define KC_R    {NORMAL, KEY_R}
#define KC_S    {NORMAL, KEY_S}
#define KC_T    {NORMAL, KEY_T}
#define KC_U    {NORMAL, KEY_U}
#define KC_V    {NORMAL, KEY_V}
#define KC_W    {NORMAL, KEY_W}
#define KC_X    {NORMAL, KEY_X}
#define KC_Y    {NORMAL, KEY_Y}
#define KC_Z    {NORMAL, KEY_Z}
#define KC_1    {NORMAL, KEY_1}
#define KC_2    {NORMAL, KEY_2}
#define KC_3    {NORMAL, KEY_3}
#define KC_4    {NORMAL, KEY_4}
#define KC_5    {NORMAL, KEY_5}
#define KC_6    {NORMAL, KEY_6}
#define KC_7    {NORMAL, KEY_7}
#define KC_8    {NORMAL, KEY_8}
#define KC_9    {NORMAL, KEY_9}
#define KC_0    {NORMAL, KEY_0}
#define KC_ENT  {NORMAL, KEY_ENTER}
#define KC_ESC  {NORMAL, KEY_ESCAPE}
#define KC_BSPC {NORMAL, KEY_BSPACE}
#define KC_TAB  {NORMAL, KEY_TAB}
#define KC_SPC  {NORMAL, KEY_SPACE}
#define KC_MINS {NORMAL, KEY_MINUS}
#define KC_EQL  {NORMAL, KEY_EQUAL}
#define KC_LBRC {NORMAL, KEY_LBRACKET}
#define KC_RBRC {NORMAL, KEY_RBRACKET}
#define KC_BSLS {NORMAL, KEY_BSLASH}
#define KC_NUHS {NORMAL, KEY_NONUS_HASH}
#define KC_SCLN {NORMAL, KEY_SCOLON}
#define KC_QUOT {NORMAL, KEY_QUOTE}
#define KC_GRV  {NORMAL, KEY_GRAVE}
#define KC_COMM {NORMAL, KEY_COMMA}
#define KC_DOT  {NORMAL, KEY_DOT}
#define KC_SLSH {NORMAL, KEY_SLASH}
#define KC_CAPS {NORMAL, KEY_CAPSLOCK}
#define KC_F1   {NORMAL, KEY_F1}
#define KC_F2   {NORMAL, KEY_F2}
#define KC_F3   {NORMAL, KEY_F3}
#define KC_F4   {NORMAL, KEY_F4}
#define KC_F5   {NORMAL, KEY_F5}
#define KC_F6   {NORMAL, KEY_F6}
#define KC_F7   {NORMAL, KEY_F7}
#define KC_F8   {NORMAL, KEY_F8}
#define KC_F9   {NORMAL, KEY_F9}
#define KC_F10  {NORMAL, KEY_F10}
#define KC_F11  {NORMAL, KEY_F11}
#define KC_F12  {NORMAL, KEY_F12}
#define KC_PSCR {NORMAL, KEY_PSCREEN}
#define KC_SLCK {NORMAL, KEY_SCKLOCK}
#define KC_PAUS {NORMAL, KEY_PAUSE}
#define KC_INS  {NORMAL, KEY_INSERT}
#define KC_HOME {NORMAL, KEY_HOME}
#define KC_PGUP {NORMAL, KEY_PGUP}
#define KC_DEL  {NORMAL, KEY_DELETE}
#define KC_END  {NORMAL, KEY_END}
#define KC_PGDN {NORMAL, KEY_PGDOWN}
#define KC_RGHT {NORMAL, KEY_RIGHT}
#define KC_LEFT {NORMAL, KEY_LEFT}
#define KC_DOWN {NORMAL, KEY_DOWN}
#define KC_UP   {NORMAL, KEY_UP}
#define KC_NLCK {NORMAL, KEY_NUMLOCK}
#define KC_PSLS {NORMAL, KEY_KP_SLASH}
#define KC_PAST {NORMAL, KEY_KP_ASTERISK}
#define KC_PMNS {NORMAL, KEY_KP_MINUS}
#define KC_PPLS {NORMAL, KEY_KP_PLUS}
#define KC_PENT {NORMAL, KEY_KP_ENTER}
#define KC_P1   {NORMAL, KEY_KP_1}
#define KC_P2   {NORMAL, KEY_KP_2}
#define KC_P3   {NORMAL, KEY_KP_3}
#define KC_P4   {NORMAL, KEY_KP_4}
#define KC_P5   {NORMAL, KEY_KP_5}
#define KC_P6   {NORMAL, KEY_KP_6}
#define KC_P7   {NORMAL, KEY_KP_7}
#define KC_P8   {NORMAL, KEY_KP_8}
#define KC_P9   {NORMAL, KEY_KP_9}
#define KC_P0   {NORMAL, KEY_KP_0}
#define KC_PDOT {NORMAL, KEY_KP_DOT}
#define KC_NUBS {NORMAL, KEY_NONUS_BSLASH}
#define KC_APP  {NORMAL, KEY_APPLICATION}
#define KC_PEQL {NORMAL, KEY_KP_EQUAL}
#define KC_PCMM {NORMAL, KEY_KP_COMMA}
#define KC_BRK  {NORMAL, KEY_PAUSE}
#define KC_ERAS {NORMAL, KEY_ALT_ERASE}
#define KC_CLR  {NORMAL, KEY_CLEAR}
/* Japanese specific */
#define KC_ZKHK {NORMAL, KEY_GRAVE}
#define KC_RO   {NORMAL, KEY_INT1}
#define KC_KANA {NORMAL, KEY_INT2}
#define KC_JYEN {NORMAL, KEY_INT3}
#define KC_HENK {NORMAL, KEY_INT4}
#define KC_MHEN {NORMAL, KEY_INT5}


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
