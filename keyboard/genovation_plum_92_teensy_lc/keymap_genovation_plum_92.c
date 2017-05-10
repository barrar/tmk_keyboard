#include "keymap_common.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: qerty */
    KEYMAP(ESC,  Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,    X,    X, X, X, X, \
           ESC,  Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,    X,    X, X, X, X, \
           ESC,  Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,    X,    X, X, X, X, \
           FN0,  A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN, QUOT, X, X, X, X, \
           LSFT, Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH, FN20, X, X, X, X, \
           LCTL, LGUI,LALT,     FN1,           FN2,      RALT,APP,  RCTL, X, X, X, X),

    /* 1: FN 1 */
    KEYMAP(ESC,  Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,    X,    X, X, X, X, \
           ESC,  Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,    X,    X, X, X, X, \
           ESC,  Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,    X,    X, X, X, X, \
           FN0,  A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN, QUOT, X, X, X, X, \
           LSFT, Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH, FN20, X, X, X, X, \
           LCTL, LGUI,LALT,     FN1,           FN2,      RALT,APP,  RCTL, X, X, X, X),

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
    [0]  = ACTION_LAYER_MOMENTARY(1),
};


