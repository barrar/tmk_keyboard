#include "keymap_common.h"

const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: qerty */
    KEYMAP(ESC,  F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10,  F11,  F12, PSCR, F14,    F15, \
           GRV,  1,   2,   3,   4,   5,   6,   7,   8,   9,   0,    MINS, EQL, BSPC, INS,    PGUP,  \
           TAB,  Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,    LBRC, RBRC,BSLS, DELETE, PGDN, \
           CAPS, A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN, QUOT, ENT, HOME, X,      VOLU, \
           LSFT, Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH, RSFT, UP,  END,  X,      VOLD, \
           LCTL, LALT,LGUI,     SPC,           BSPC,     FN2, RCTL, LEFT, DOWN,RGHT, FN0,     MUTE),

    /* 1: FN 1 */
    KEYMAP(ESC,  F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10,  F11,  F12, PSCR, F14,    SLEP, \
           GRV,  1,   2,   3,   4,   5,   6,   7,   8,   9,   0,    MINS, EQL, BSPC, INS,    PGUP,  \
           TAB,  FN1, W,   E,   R,   T,   Y,   U,   I,   O,   P,    LBRC, RBRC,BSLS, DELETE, PGDN, \
           CAPS, A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN, QUOT, ENT, HOME, X,      VOLU, \
           LSFT, Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH, RSFT, MS_U,END,  X,      VOLD, \
           LCTL, LALT,LGUI,     SPC,           BSPC,     FN2, RCTL, MS_L, MS_D,MS_R, FN0,     MUTE),
};

enum macro_id {
    TRACK55,
    VOLUP,
    ALT_TAB,
};


const action_t fn_actions[] = {
    [0] = ACTION_LAYER_TOGGLE(1),
    [1] = ACTION_MACRO(TRACK55),
    [2] = ACTION_LAYER_MOMENTARY(1),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    (void)opt;
    switch (id) {
        case TRACK55:
            return (record->event.pressed ?
                    MACRO( I(10), T(5), T(5), END ) :
                    MACRO_NONE );
        case VOLUP:
            return (record->event.pressed ?
                    MACRO( D(VOLU), U(VOLU), END ) :
                    MACRO_NONE );
        case ALT_TAB:
            return (record->event.pressed ?
                    MACRO( D(LALT), D(TAB), END ) :
                    MACRO( U(TAB), END ));
    }
    return MACRO_NONE;
}