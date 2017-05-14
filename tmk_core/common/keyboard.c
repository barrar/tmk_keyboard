#include <stdint.h>
#include "keyboard.h"
#include "matrix.h"
#include "keymap.h"
#include "host.h"
#include "led.h"
#include "keycode.h"
#include "timer.h"
#include "print.h"
#include "debug.h"
#include "command.h"
#include "util.h"
#include "sendchar.h"
#include "bootmagic.h"
#include "eeconfig.h"
#include "backlight.h"
#include "hook.h"
#ifdef MOUSEKEY_ENABLE
#   include "mousekey.h"
#endif
#ifdef PS2_MOUSE_ENABLE
#   include "ps2_mouse.h"
#endif
#ifdef SERIAL_MOUSE_ENABLE
#include "serial_mouse.h"
#endif
#ifdef ADB_MOUSE_ENABLE
#include "adb.h"
#endif


#ifdef MATRIX_HAS_GHOST
extern const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS];
static matrix_row_t get_real_keys(uint8_t row, matrix_row_t rowdata){
    matrix_row_t out = 0;
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        //read each key in the row data and check if the keymap defines it as a real key
        if (pgm_read_byte(&keymaps[0][row][col]) && (rowdata & (1<<col))){
            //this creates new row data, if a key is defined in the keymap, it will be set here
            out |= 1<<col;
        }
    }
    return out;
}

static inline bool popcount_more_than_one(matrix_row_t rowdata)
{
    rowdata &= rowdata-1; //if there are less than two bits (keys) set, rowdata will become zero
    return rowdata;
}

static inline bool has_ghost_in_row(uint8_t row, matrix_row_t rowdata)
{
    /* No ghost exists when less than 2 keys are down on the row.
    If there are "active" blanks in the matrix, the key can't be pressed by the user,
    there is no doubt as to which keys are really being pressed.
    The ghosts will be ignored, they are KC_NO.   */
    rowdata = get_real_keys(row, rowdata);
    if ((popcount_more_than_one(rowdata)) == 0){
        return false;
    }
    /* Ghost occurs when the row shares a column line with other row,
    and two columns are read on each row. Blanks in the matrix don't matter,
    so they are filtered out.
    If there are two or more real keys pressed and they match columns with
    at least two of another row's real keys, the row will be ignored. Keep in mind,
    we are checking one row at a time, not all of them at once.
    */
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        if (i != row && popcount_more_than_one(get_real_keys(i, matrix_get_row(i)) & rowdata)){
            return true;
        }
    }
    return false;
}
#endif

void keyboard_setup(void)
{
    matrix_setup();
}

void keyboard_init(void)
{
    timer_init();
    matrix_init();
#ifdef PS2_MOUSE_ENABLE
    ps2_mouse_init();
#endif
#ifdef SERIAL_MOUSE_ENABLE
    serial_mouse_init();
#endif
#ifdef ADB_MOUSE_ENABLE
    adb_mouse_init();
#endif
#ifdef BOOTMAGIC_ENABLE
    bootmagic();
#endif
#ifdef BACKLIGHT_ENABLE
    backlight_init();
#endif
}

/*
 * Do keyboard routine jobs: scan mantrix, light LEDs, ...
 * This is repeatedly called as fast as possible.
 */
void keyboard_task(void)
{
    static matrix_row_t matrix_prev[MATRIX_ROWS];
    static uint8_t led_status = 0;
    matrix_row_t matrix_row = 0;
    matrix_row_t matrix_change = 0;

    matrix_scan();
    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        matrix_row = matrix_get_row(r);
        matrix_change = matrix_row ^ matrix_prev[r];
        if (matrix_change) {
#ifdef MATRIX_HAS_GHOST
            if (has_ghost_in_row(r, matrix_row)) {
                continue;
            }
#endif
            for (uint8_t c = 0; c < MATRIX_COLS; c++) {
                if (matrix_change & ((matrix_row_t)1<<c)) {
                    keyevent_t e = (keyevent_t){
                        .key = (keypos_t){ .row = r, .col = c },
                        .pressed = (matrix_row & ((matrix_row_t)1<<c)),
                        .time = (timer_read() | 1) /* time should not be 0 */
                    };
                    action_exec(e);
                    hook_matrix_change(e);
                    // record a processed key
                    matrix_prev[r] ^= ((matrix_row_t)1<<c);

                    // This can miss stroke when scan matrix takes long like Topre
                    // process a key per task call
                }
            }
        }
    }
    // call with pseudo tick event when no real key event.
    action_exec(TICK);

    hook_keyboard_loop();

#ifdef MOUSEKEY_ENABLE
    // mousekey repeat & acceleration
    mousekey_task();
#endif

#ifdef PS2_MOUSE_ENABLE
    ps2_mouse_task();
#endif

#ifdef SERIAL_MOUSE_ENABLE
        serial_mouse_task();
#endif

#ifdef ADB_MOUSE_ENABLE
        adb_mouse_task();
#endif

    // update LED
    if (led_status != host_keyboard_leds()) {
        led_status = host_keyboard_leds();
        if (debug_keyboard) dprintf("LED: %02X\n", led_status);
        hook_keyboard_leds_change(led_status);
    }
}

void keyboard_set_leds(uint8_t leds)
{
    led_set(leds);
}
