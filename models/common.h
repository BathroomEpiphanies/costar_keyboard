/* Common stuff. */

#ifndef common_h__
#define common_h__

#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/* Extra definitions for AVR stuff. */
#include "../lib/avr_extra.h"
/* include keycode definitions. */
#include "../lib/keycode.h"

#define STR_MANUFACTURER L"Bathroom Epiphanies, Costar Keyboard -"
#define VENDOR_ID        0x16C0

#define SCAN_INTERRUPT_FUNCTION TIMER0_COMPA_vect
#define SETTLE_TIME_US 1

#define NROW  18
#define NCOL   8
#define NKEY 144

/* Convert physical keyboard layout to matrix array. This is a macro
   to define keymap easily in keyboard layout form. All ANSI ISO JIS
   Layouts are on the same PCB */
#define KEYMAP( \
    KJ6,      KI4, KH4, KH2, KH6, KA7, KE6, KD2, KD4, KB4, KB7, KB6, KB0,   KC7, KC5, KA5,                       \
    KJ4, KJ7, KI7, KH7, KG7, KG4, KF4, KF7, KE7, KD7, KR7, KR4, KE4, KB2,   KL4, KO4, KQ4,   KK1, KL1, KQ1, KQ0, \
    KJ2, KJ5, KI5, KH5, KG5, KG2, KF2, KF5, KE5, KD5, KR5, KR2, KE2, KB3,   KK4, KO7, KQ7,   KK5, KL5, KQ5, KO5, \
    KI2, KJ3, KI3, KH3, KG3, KG6, KF6, KF3, KE3, KD3, KR3, KR6,      KB1,                    KK2, KL2, KQ2,      \
    KN2, KI6, KJ1, KI1, KH1, KG1, KG0, KF0, KF1, KE1, KD1, KR0,      KN3,        KO6,        KK3, KL3, KQ3, KO3, \
    KA4, KP2, KC6,                KK6,                KC0, KM3, KD0, KA1,   KO0, KK0, KL0,   KL6,      KQ6,      \
\
    KA0, KA2, KA3, KA6, KB5, KC1, KC2, KC3, KC4, KD6, KE0, KH0, KI0, KJ0, KK7, KL7, \
    KM0, KM1, KM2, KM4, KM5, KM6, KM7, KN0, KN1, KN4, KN5, KN6, KN7, KO1, KO2, KP0, \
    KP1, KP3, KP4, KP5, KP6, KP7, KR1) \
{                                                                                       \
/*      0         1         2         3         4         5         6         7   */    \
/* A */ KC_##KA0, KC_##KA1, KC_##KA2, KC_##KA3, KC_##KA4, KC_##KA5, KC_##KA6, KC_##KA7, \
/* B */ KC_##KB0, KC_##KB1, KC_##KB2, KC_##KB3, KC_##KB4, KC_##KB5, KC_##KB6, KC_##KB7, \
/* C */ KC_##KC0, KC_##KC1, KC_##KC2, KC_##KC3, KC_##KC4, KC_##KC5, KC_##KC6, KC_##KC7, \
/* D */ KC_##KD0, KC_##KD1, KC_##KD2, KC_##KD3, KC_##KD4, KC_##KD5, KC_##KD6, KC_##KD7, \
/* E */ KC_##KE0, KC_##KE1, KC_##KE2, KC_##KE3, KC_##KE4, KC_##KE5, KC_##KE6, KC_##KE7, \
/* F */ KC_##KF0, KC_##KF1, KC_##KF2, KC_##KF3, KC_##KF4, KC_##KF5, KC_##KF6, KC_##KF7, \
/* G */ KC_##KG0, KC_##KG1, KC_##KG2, KC_##KG3, KC_##KG4, KC_##KG5, KC_##KG6, KC_##KG7, \
/* H */ KC_##KH0, KC_##KH1, KC_##KH2, KC_##KH3, KC_##KH4, KC_##KH5, KC_##KH6, KC_##KH7, \
/* I */ KC_##KI0, KC_##KI1, KC_##KI2, KC_##KI3, KC_##KI4, KC_##KI5, KC_##KI6, KC_##KI7, \
/* J */ KC_##KJ0, KC_##KJ1, KC_##KJ2, KC_##KJ3, KC_##KJ4, KC_##KJ5, KC_##KJ6, KC_##KJ7, \
/* K */ KC_##KK0, KC_##KK1, KC_##KK2, KC_##KK3, KC_##KK4, KC_##KK5, KC_##KK6, KC_##KK7, \
/* L */ KC_##KL0, KC_##KL1, KC_##KL2, KC_##KL3, KC_##KL4, KC_##KL5, KC_##KL6, KC_##KL7, \
/* M */ KC_##KM0, KC_##KM1, KC_##KM2, KC_##KM3, KC_##KM4, KC_##KM5, KC_##KM6, KC_##KM7, \
/* N */ KC_##KN0, KC_##KN1, KC_##KN2, KC_##KN3, KC_##KN4, KC_##KN5, KC_##KN6, KC_##KN7, \
/* O */ KC_##KO0, KC_##KO1, KC_##KO2, KC_##KO3, KC_##KO4, KC_##KO5, KC_##KO6, KC_##KO7, \
/* P */ KC_##KP0, KC_##KP1, KC_##KP2, KC_##KP3, KC_##KP4, KC_##KP5, KC_##KP6, KC_##KP7, \
/* Q */ KC_##KQ0, KC_##KQ1, KC_##KQ2, KC_##KQ3, KC_##KQ4, KC_##KQ5, KC_##KQ6, KC_##KQ7, \
/* R */ KC_##KR0, KC_##KR1, KC_##KR2, KC_##KR3, KC_##KR4, KC_##KR5, KC_##KR6, KC_##KR7  \
}

/* ,---.   ,---------------. ,---------------. ,---------------. ,-----------. ,---------------.
   |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|ScL|Pau| |PrS|ScL|ScL|Pau|
   `---'   `---------------' `---------------' `---------------' `-----------' `---------------'
   ,-----------------------------------------------------------. ,-----------. ,---------------.
   | ~ | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = | Backsp| |Ins|Hom|PgU| |NuL| / | * | - |
   |-----------------------------------------------------------| |-----------| |---------------|
   | Tab | Q | W | E | R | T | Y | U | I | O | P | [ | ] |  \  | |Del|End|PgD| | 7 | 8 | 9 | + |
   |-----------------------------------------------------------| `-----------' |-----------|   |
   |CapsL | A | S | D | F | G | H | J | K | L | ; | ' | Return |               | 5 | 6 | 6 |   |
   |-----------------------------------------------------------|     ,---.     |---------------|
   |Shft|ISO| Z | X | C | V | B | N | M | , | . | / |    Shift |     |Up |     | 1 | 2 | 3 | E |
   |-----------------------------------------------------------| ,-----------. |-----------| n |
   |Ctl|Gui|Alt|          Space                |Alt|Gui|App|Ctl| |Lef|Dow|Rig| | 0     | . | t |
   `-----------------------------------------------------------' `-----------' `---------------'  */
#define ANSI_ISO_JIS \
  KEYMAP(ESC,        F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9, F10, F11, F12,  PSCR,SLCK,PAUS,                       \
         GRV,    1,   2,   3,   4,   5,   6,   7,   8,   9,   0,MINS, EQL,BSPC,   INS,HOME,PGUP,  NLCK,PSLS,PAST,PMNS, \
         TAB,    Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,LBRC,RBRC,BSLS,   DEL, END,PGDN,    P7,  P8,  P9,PPLS, \
         CAPS,   A,   S,   D,   F,   G,   H,   J,   K,   L,SCLN,QUOT,      ENT,                     P4,  P5,  P6,      \
         LSFT,NUBS,   Z,   X,   C,   V,   B,   N,   M,COMM, DOT,SLSH,     RSFT,          UP,        P1,  P2,  P3,PENT, \
         LCTL,LGUI,LALT,                SPC,               RALT,RGUI, APP,RCTL,   LEFT,DOWN,RGHT,   P0,     PDOT,      \
         \
         NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, \
         NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, \
         NO, NO, NO, NO, NO, NO, NO)

#define DVORAK \
  KEYMAP(ESC,        F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9, F10, F11, F12,  PSCR,SLCK,PAUS,                       \
         GRV,    1,   2,   3,   4,   5,   6,   7,   8,   9,   0,LBRC,RBRC,BSPC,   INS,HOME,PGUP,  NLCK,PSLS,PAST,PMNS, \
         TAB, QUOT,COMM, DOT,   P,   Y,   F,   G,   C,   R,   L,SLSH, EQL,BSLS,   DEL, END,PGDN,    P7,  P8,  P9,PPLS, \
         CAPS,   A,   O,   E,   U,   I,   D,   H,   T,   N,   S,MINS,      ENT,                     P4,  P5,  P6,      \
         LSFT,NUBS,SCLN,   Q,   J,   K,   X,   B,   M,   W,   V,   Z,     RSFT,         UP,         P1,  P2,  P3,PENT, \
         LCTL,LGUI,LALT,                SPC,               RALT,RGUI, APP,RCTL,  LEFT,DOWN,RGHT,    P0,     PDOT,      \
         \
         NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, \
         NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, \
         NO, NO, NO, NO, NO, NO, NO)

#define TEST_FLAKE \
  KEYMAP(ESC,        F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9, F10, F11, F12,  PSCR,SLCK,PAUS,                       \
         GRV,    1,   2,   3,   4,   5,   6,   7,   8,   9,   0,MINS, EQL,BSPC,   INS,HOME,PGUP,  NLCK,PSLS,PAST,PMNS, \
         TAB,    Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,LBRC,RBRC,BSLS,   DEL, END,PGDN,    P7,  P8,  P9,PPLS, \
         CAPS,   A,   S,   D,   F,   G,   H,   J,   K,   L,SCLN,QUOT,      ENT,                     P4,  P5,  P6,      \
         LSFT,NUBS,   Z,   X,   C,   V,   B,   N,   M,COMM, DOT,SLSH,     RSFT,          UP,        P1,  P2,  P3,PENT, \
         LCTL,LGUI,LALT,                SPC,               RALT,RGUI,NLCK,RCTL,   LEFT,DOWN,RGHT,   P0,     PDOT,      \
         \
         NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, \
         NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, NO, \
         NO, NO, NO, NO, NO, NO, NO)


/* Test layouts to easily find the position of keys in the underlying
   matrix. */
#define TEST_COLS \
/*  COL 0   COL 1   COL 2   COL 3   COL 4   COL 5   COL 6   COL 7 */ \
  { \
    KC_0,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   /* ROW A */ \
    KC_0,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   /* ROW B */ \
    KC_0,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   /* ROW C */ \
    KC_0,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   /* ROW D */ \
    KC_0,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   /* ROW E */ \
    KC_0,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   /* ROW F */ \
    KC_0,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   /* ROW G */ \
    KC_0,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   /* ROW H */ \
    KC_0,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   /* ROW I */ \
    KC_0,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   /* ROW J */ \
    KC_0,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   /* ROW K */ \
    KC_0,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   /* ROW L */ \
    KC_0,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   /* ROW M */ \
    KC_0,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   /* ROW N */ \
    KC_0,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   /* ROW O */ \
    KC_0,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   /* ROW P */ \
    KC_0,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   /* ROW Q */ \
    KC_0,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7    /* ROW R */ \
  };
#define TEST_ROWS \
/*  COL 0   COL 1   COL 2   COL 3   COL 4   COL 5   COL 6   COL 7 */ \
  { \
    KC_A,   KC_A,   KC_A,   KC_A,   KC_A,   KC_A,   KC_A,   KC_A,   /* ROW A */ \
    KC_B,   KC_B,   KC_B,   KC_B,   KC_B,   KC_B,   KC_B,   KC_B,   /* ROW B */ \
    KC_C,   KC_C,   KC_C,   KC_C,   KC_C,   KC_C,   KC_C,   KC_C,   /* ROW C */ \
    KC_D,   KC_D,   KC_D,   KC_D,   KC_D,   KC_D,   KC_D,   KC_D,   /* ROW D */ \
    KC_E,   KC_E,   KC_E,   KC_E,   KC_E,   KC_E,   KC_E,   KC_E,   /* ROW E */ \
    KC_F,   KC_F,   KC_F,   KC_F,   KC_F,   KC_F,   KC_F,   KC_F,   /* ROW F */ \
    KC_G,   KC_G,   KC_G,   KC_G,   KC_G,   KC_G,   KC_G,   KC_G,   /* ROW G */ \
    KC_H,   KC_H,   KC_H,   KC_H,   KC_H,   KC_H,   KC_H,   KC_H,   /* ROW H */ \
    KC_I,   KC_I,   KC_I,   KC_I,   KC_I,   KC_I,   KC_I,   KC_I,   /* ROW I */ \
    KC_J,   KC_J,   KC_J,   KC_J,   KC_J,   KC_J,   KC_J,   KC_J,   /* ROW J */ \
    KC_K,   KC_K,   KC_K,   KC_K,   KC_K,   KC_K,   KC_K,   KC_K,   /* ROW K */ \
    KC_L,   KC_L,   KC_L,   KC_L,   KC_L,   KC_L,   KC_L,   KC_L,   /* ROW L */ \
    KC_M,   KC_M,   KC_M,   KC_M,   KC_M,   KC_M,   KC_M,   KC_M,   /* ROW M */ \
    KC_N,   KC_N,   KC_N,   KC_N,   KC_N,   KC_N,   KC_N,   KC_N,   /* ROW N */ \
    KC_O,   KC_O,   KC_O,   KC_O,   KC_O,   KC_O,   KC_O,   KC_O,   /* ROW O */ \
    KC_P,   KC_P,   KC_P,   KC_P,   KC_P,   KC_P,   KC_P,   KC_P,   /* ROW P */ \
    KC_Q,   KC_Q,   KC_Q,   KC_Q,   KC_Q,   KC_Q,   KC_Q,   KC_Q,   /* ROW Q */ \
    KC_R,   KC_R,   KC_R,   KC_R,   KC_R,   KC_R,   KC_R,   KC_R    /* ROW R */ \
  };

#endif
