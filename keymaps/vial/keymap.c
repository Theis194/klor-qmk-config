/*

                                        █         █    █            ▄▄▄▀▀▀▀▀▀▄▄▄        █▀▀▀▀▀▀▀▀▀▀█
                                        █        █     █          ▄▀            ▀▄      █          █
                                        █       █      █        ▄▀                ▀▄    █          █
                                        █      █       █        █                  █    █          █
                                        █     █        █       █                    █   █          █
                                        █    █         █       █                    █   █▄▄▄▄▄▄▄▄▄▄█
                                        █   █ █        █       █                    █   █      █
                                        █  █   █       █        █                  █    █       █
                                        █ █     █      █        ▀▄                ▄▀    █        █
                                        ██       █     █          ▀▄            ▄▀      █         █
                                        █         █    █▄▄▄▄▄▄▄▄    ▀▀▀▄▄▄▄▄▄▀▀▀        █          █

                                        ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
                                        D E F A U L T
*/
#include QMK_KEYBOARD_H
#include <stdio.h>
#include <string.h>
#include "nvm_dynamic_keymap.h"
#if HAPTIC_ENABLE
#    include "drivers/haptic/DRV2605L.h"
#endif // HAPTIC ENABLE

// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ K E Y C O D E S                                                                                                                            │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘

enum custom_keycodes {
    ACTION_KEY = QK_KB_0,
};

static uint8_t previous_layer = 0; // Tracks the layer we came from
static bool action_key_activated = false; // Tracks if we entered via ACTION_KEY

// Action layer functionality
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ACTION_KEY:
            if (record->event.pressed) {
                uint8_t current_layer = get_highest_layer(layer_state);

                if (current_layer == ACTION_LAYER) {
                    // Find and return to the highest non-normal layer
                    action_key_activated = false;
                    layer_move(previous_layer);
                } else {
                    previous_layer = current_layer;
                    action_key_activated = true;
                    layer_move(ACTION_LAYER);
                }
            }
            return false;

        case KC_ENT:
            if (record->event.pressed && layer_state_is(ACTION_LAYER) && action_key_activated) {
                if (action_key_activated) {
                    // Only exit if ACTION_KEY was used to enter
                    action_key_activated = false;
                    layer_move(previous_layer);
                    return true; // Block default Enter behavior
                }
                // If not action_key_activated, allow normal Enter
            }
            return true;
    }
    return true;
}

// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ K E Y M A P S                                                                                                                              │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /*
       ┌───────────────────────────────────────────────────────────┐
       │ q w e r t y                                               │
       └───────────────────────────────────────────────────────────┘
                 ┌─────────┬─────────┬─────────┬─────────┬─────────┐                    ┌─────────┬─────────┬─────────┬─────────┬─────────┐
                 │    Q    │    W    │    E    │    R    │    T    │ ╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮ │    Y    │    U    │    I    │    O    │    P    │
       ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤ │╰╯╰╯╰╯╰╯╰╯╰╯╰╯╰╯│ ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
       │   TAB   │    A    │    S    │    D    │    F    │    G    ├─╯                ╰─┤    H    │    J    │    K    │    L    │    ;    │    "    │
       ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤╭────────╮╭────────╮├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
       │   DEL   │    Z    │    X    │    C    │    V    │    B    ││  MUTE  ││PLY/PSE ││    N    │    M    │    ,    │    .    │    /    │  SHIFT  │
       └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┼╰────────╯╰────────╯┼─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                     │  CTRL   │  _____  │  SPACE  │   ALT   ││ CMD/WIN │  ENTER  │  _____  │ BSPACE  │
                                     └─────────┴─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┴─────────┘ */

    [0] = LAYOUT(
        // ╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
        KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_LBRC, KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_P, KC_QUOT, KC_LALT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_MUTE, KC_MPLY, KC_N, KC_M, KC_COMM, KC_DOT, KC_SCLN, KC_ENT, KC_LCTL, _______, KC_SPC, _______, _______, KC_RSFT, _______, KC_BSPC),

    [1] = LAYOUT(
        // ╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
        KC_CAPS, KC_NUM, KC_UP, LSFT(KC_0), RALT(KC_7), RALT(KC_0), KC_P7, KC_P8, KC_P9, KC_PPLS, KC_ESC, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, RALT(KC_8), RALT(KC_9), KC_P4, KC_P5, KC_P6, KC_SLSH, KC_COMM, KC_DEL, KC_END, KC_PGUP, KC_PSCR, KC_PGDN, LSFT(KC_8), KC_MUTE, KC_MPLY, LSFT(KC_9), KC_P1, KC_P2, KC_P3, KC_PAST, KC_PSLS, _______, _______, _______, _______, _______, _______, _______, KC_P0),

    [2] = LAYOUT(
        // ╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
        KC_EXLM, RALT(KC_2), KC_HASH, RALT(KC_EQL), KC_PERC, LSFT(KC_2), KC_CIRC, LSFT(KC_MINS), RALT(KC_3), KC_BSLS, XXXXXXX, KC_NUBS, RALT(KC_4), RALT(KC_NUBS), RALT(KC_RBRC), KC_MPRV, KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, KC_MPLY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, KC_LGUI, _______, _______, _______, _______, _______),

    [3] = LAYOUT(
        // ╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
        KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_MUTE, KC_MPLY, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_ESC, KC_TAB, KC_ENT, KC_LALT, KC_LGUI, KC_SPC, KC_BSPC, KC_DEL),

    /*
      ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸

      ┌───────────────────────────────────────────────────────────┐
      │ t e m p l a t e                                           │
      └───────────────────────────────────────────────────────────┘
                ┌─────────┬─────────┬─────────┬─────────┬─────────┐                    ┌─────────┬─────────┬─────────┬─────────┬─────────┐
                │         │         │         │         │         │ ╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮ │         │         │         │         │         │
      ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤ │╰╯╰╯╰╯╰╯╰╯╰╯╰╯╰╯│ ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
      │         │         │         │         │         │         ├─╯                ╰─┤         │         │         │         │         │         │
      ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤╭────────╮╭────────╮├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      │         │         │         │         │         │         ││        ││        ││         │         │         │         │         │         │
      └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┼╰────────╯╰────────╯┼─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                    │         │         │         │         ││         │         │         │         │
                                    └─────────┴─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┴─────────┘

      [_TEMPLATE] = LAYOUT(
    //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
                 _______,  _______,  _______,  _______,  _______,                       _______,  _______,  _______,  _______,  _______,
       _______,  _______,  _______,  _______,  _______,  _______,                       _______,  _______,  _______,  _______,  _______,  _______,
       _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,
                                     _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______
    )*/
};

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT(
    // ╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
    'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R');

#ifdef ENCODER_MAP_ENABLE

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = {ENCODER_CCW_CW(QK_MOUSE_WHEEL_UP, QK_MOUSE_WHEEL_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [1] = {ENCODER_CCW_CW(RGB_HUD, RGB_HUI), ENCODER_CCW_CW(RGB_SAD, RGB_SAI)},
    [2] = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI), ENCODER_CCW_CW(RGB_SPD, RGB_SPI)},
    [3] = {ENCODER_CCW_CW(RGB_RMOD, RGB_MOD), ENCODER_CCW_CW(KC_RIGHT, KC_LEFT)},
    //                  Encoder 1                                     Encoder 2
};

#endif

// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ O L E D                                                                                                                                    │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘

#ifdef OLED_ENABLE

char layer_state_str[24];
char o_text[24] = "";

// ┌───────────────────────────────────────────────────────────┐
// │ o l e d   g r a p h i c s                                 │
// └───────────────────────────────────────────────────────────┘

void render_os_lock_status(void) {
    static const char PROGMEM sep_v[]  = {0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0};
    static const char PROGMEM sep_h1[] = {0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0};
    static const char PROGMEM sep_h2[] = {0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0};
    static const char PROGMEM face_1[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0xE1, 0};
    static const char PROGMEM face_2[] = {0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xE1, 0};
    static const char PROGMEM os_m_1[] = {0x95, 0x96, 0};
    static const char PROGMEM os_m_2[] = {0xB5, 0xB6, 0};
    static const char PROGMEM os_w_1[] = {0x97, 0x98, 0};
    static const char PROGMEM os_w_2[] = {0xB7, 0xB8, 0};
    static const char PROGMEM s_lock[] = {0x8F, 0x90, 0};
    static const char PROGMEM n_lock[] = {0x91, 0x92, 0};
    static const char PROGMEM c_lock[] = {0x93, 0x94, 0};
    static const char PROGMEM b_lock[] = {0xE1, 0xE1, 0};
    static const char PROGMEM action_on[] = {0x41, 0x43, 0x54, 0};
#    ifdef AUDIO_ENABLE
    static const char PROGMEM aud_en[] = {0xAF, 0xB0, 0};
    static const char PROGMEM aud_di[] = {0xCF, 0xD0, 0};
#    endif
#    ifdef HAPTIC_ENABLE
    static const char PROGMEM hap_en[] = {0xB1, 0xB2, 0};
#    endif

    // os mode status ────────────────────────────────────────┐

    oled_write_ln_P(sep_v, false);

    if (keymap_config.swap_lctl_lgui) {
        oled_write_P(os_m_1, false); // ──── MAC
    } else {
        oled_write_P(os_w_1, false); // ──── WIN
    }

    oled_write_P(sep_h1, false);
    oled_write_P(face_1, false);

    if (keymap_config.swap_lctl_lgui) {
        oled_write_P(os_m_2, false); // ──── MAC
    } else {
        oled_write_P(os_w_2, false); // ──── WIN
    }

    oled_write_P(sep_h1, false);
    oled_write_P(face_2, false);
    oled_write_ln_P(sep_v, false);

    // lock key layer status ─────────────────────────────────┐

    led_t led_usb_state = host_keyboard_led_state();

    if (led_usb_state.num_lock) {
        oled_write_P(n_lock, false); // ──── NUMLOCK
    } else {
        oled_write_P(b_lock, false);
    }
    if (led_usb_state.caps_lock) {
        oled_write_P(c_lock, false); // ─── CAPSLOCK
    } else {
        oled_write_P(b_lock, false);
    }
    if (led_usb_state.scroll_lock) { // ─ SCROLLLOCK
        oled_write_P(s_lock, false);
    } else {
        oled_write_P(b_lock, false);
    }

    // ACTION

    if (action_key_activated) {
        oled_write_P(action_on, false); // ── ACTION LAYER ON
    } else {
        oled_write_P(b_lock, false);
    }

    // hardware feature status ──────────────────────────────┐

    oled_write_P(sep_h2, false);

#    ifndef AUDIO_ENABLE
    oled_write_P(b_lock, false);
#    endif
#    ifndef HAPTIC_ENABLE
    oled_write_P(b_lock, false);
#    endif

#    ifdef AUDIO_ENABLE // ────────────────── AUDIO
    if (is_audio_on()) {
        oled_write_P(aud_en, false);
    } else {
        oled_write_P(aud_di, false);
    }
#    endif // AUDIO ENABLE

#    ifdef HAPTIC_ENABLE // ─────────────── HAPTIC
    oled_write_P(hap_en, false);
#    endif // HAPTIC ENABLE
}

// layer status ──────────────────────────────────────────┐

int layerstate = 0;

layer_state_t layer_state_set_kb(layer_state_t state) {
    uint8_t layer = get_highest_layer(state);

    // Default placeholder in case fetching the layer name fails
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer %u", layer);

    uint8_t raw[16] = {0};
    char tmp[17] = {0};

    // Attempt to fetch the layer name from NVM. If it fails, we keep the default placeholder.
    if (nvm_dynamic_keymap_get_layer_name(layer, raw) != 0) {
        return state;
    }

    // Process the raw layer name, ensuring it's printable and properly null-terminated
    bool has_printable = false;
    int out = 0;
    for (int i = 0; i < 16; i++) {
        uint8_t b = raw[i];
        if (b == 0) {
            break;
        }

        if (b >= 0x20 && b <= 0x7E) {
            tmp[out++] = (char)b;
            has_printable = true;
        } else {
            tmp[out++] = ' ';
        }
    }

    tmp[out] = '\0';

    // Trim trailing spaces and null characters
    for (int i = out - 1; i >= 0; i--) {
        if (tmp[i] == ' ' || tmp[i] == '\0') {
            tmp[i] = '\0';
        } else {
            break;
        }
    }

    // If we didn't find any printable characters, keep the default placeholder
    if (!has_printable || tmp[0] == '\0') {
        return state;
    }

    // Copy the processed layer name into the global variable for OLED display
    strncpy(layer_state_str, tmp, sizeof(layer_state_str) - 1);
    layer_state_str[sizeof(layer_state_str) - 1] = '\0';
    return state;
}

// ┌───────────────────────────────────────────────────────────┐
// │ w r i t e   t o   o l e d                                 │
// └───────────────────────────────────────────────────────────┘

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    if (is_keyboard_master()) { // ────────────────────────── PRIMARY SIDE
        strcpy(o_text, layer_state_str);
        // layer status ──────────────────────────────────────────────────┐
        oled_write_ln(o_text, false);
        render_os_lock_status();

    } else { // ─────────────────────────────────────────── SECONDARY SIDE

        // KLOR face ─────────────────────────────────────────────────────┐

        static const char PROGMEM klor_face[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0xf0, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0xf0, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                 0xff, 0xff, 0x0f, 0x0f, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0f, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x0f, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0f, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0xf0, 0xf0, 0xff,
                                                 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0xf0, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0xff, 0xff, 0xff, 0xff,
                                                 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0f, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x0f, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0f, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x0f, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x0f, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0xf0, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0f, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        oled_write_raw_P(klor_face, sizeof(klor_face));
    }
    return false;
}
#endif // OLED_ENABLE
