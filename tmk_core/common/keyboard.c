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
/*
static void printbin(uint16_t data)
{
    for (int col = 0; col < MATRIX_COLS; col++) {
        if (data & (1<<col))
            print("1");
        else
            print("0");
    }
}
*/
static bool countones(uint16_t data)
{
    int count = 0;
    for (int col = 0; col < MATRIX_COLS; col++) {
        if (data & (1<<col))
            count++;
    }
    if (count > 1){
        return true;
    }else{
        return false;
    }
}

// bit map of true keys and empty spots in matrix, each row is reversed
static matrix_row_t matrix_ghost_check[MATRIX_ROWS] = {
    (matrix_row_t) 0b001101111110111,
    (matrix_row_t) 0b101111111101110,
    (matrix_row_t) 0b010010111111111,
    (matrix_row_t) 0b111111001111001,
    (matrix_row_t) 0b111011101111111,
    (matrix_row_t) 0b111111111111001,
    (matrix_row_t) 0b110110110110111,
    (matrix_row_t) 0b111101010011110
};
static bool has_ghost_in_row(uint8_t row)
{
    matrix_row_t matrix_row = (matrix_get_row(row));
    // No ghost exists when less than 2 keys are down on the row
    if (((matrix_row - 1) & matrix_row) == 0){
        return false;

    }

    // Ghost occurs when the row shares column line with other row
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        if (i != row && countones((matrix_get_row(i) & matrix_ghost_check[i]) & (matrix_row & matrix_ghost_check[row]))){
          /*
            print("\nmatrix_ghost_check: ");
            printbin(matrix_ghost_check[i]);
            chThdSleepMilliseconds(50);
            print("\nmatrix_get_row:     ");
            printbin(matrix_get_row(i));
            chThdSleepMilliseconds(50);
            print("\nmatrix_row:         ");
            printbin(matrix_row);
            chThdSleepMilliseconds(50);
            print("\nmore than one 1:    ");
            printbin((matrix_get_row(i) & matrix_ghost_check[i]) & (matrix_row & matrix_ghost_check[row]));
            chThdSleepMilliseconds(50);
            */
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
            if (has_ghost_in_row(r)) {
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
