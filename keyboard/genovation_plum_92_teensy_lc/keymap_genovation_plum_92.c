#include "keymap_common.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: qerty */
    KEYMAP(ESC,  F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10,  F11,  F12, PSCR, F14,    F15, \
           GRV,  1,   2,   3,   4,   5,   6,   7,   8,   9,   0,    MINS, EQL, BSPC, INS,    PGUP,  \
           TAB,  Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,    LBRC, RBRC,BSLS, DELETE, PGDN, \
           CAPS, A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN, QUOT, ENT, HOME, X,      VOLU, \
           LSFT, Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH, RSFT, UP,  END,  X,      VOLD, \
           LCTL, LALT,LGUI,     SPC,           BSPC,      RALT,RCTL,  LEFT, DOWN,RGHT, X,     MUTE),

    /* 1: FN 1 */
    KEYMAP(ESC,  Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,    X,    X, X, X, X, \
           ESC,  Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,    X,    X, X, X, X, \
           ESC,  Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,    X,    X, X, X, X, \
           FN0,  A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN, QUOT, X, X, X, X, \
           LSFT, Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH, FN20, X, X, X, X, \
           LCTL, LGUI,LALT,     TRNS,           TRNS,      RALT,APP,  RCTL, X, X, X, X),

    /* 2: FN 2 */
    /*KEYMAP(GRV,     1,   2,   3,   4,   5,   6,   7,  8,   9,   0,  DEL, \
           TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,MINS,EQL,LBRC,RBRC, BSLS, \
           TRNS, F11,  F12, F13, F14, F15, F16, F17, F18,PGUP,F20, TRNS, \
           TRNS, TRNS,  TRNS,      TRNS,    TRNS,      HOME, PGDN, END),*/		   
		   
    /* 3: TAB */
    /*KEYMAP(TRNS, CALC,WHOM,MAIL,TRNS,MYCM,TRNS,TRNS,TRNS,TRNS,PSCR, DEL, \
           TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
           TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,UP,  TRNS,TRNS, \
           TRNS, TRNS,  TRNS,      TRNS,    TRNS,      LEFT, DOWN, RGHT),*/
};

const action_t PROGMEM fn_actions[] = {
    ACTION_LAYER_TAP_KEY(2, KC_BSPC)
};