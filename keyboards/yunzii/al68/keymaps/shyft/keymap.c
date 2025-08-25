/* Copyright 2022 Jacky
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "action.h"
#include "action_layer.h"
#include "color.h"
#include "keycodes.h"

#include "debug.h"
#include "modifiers.h"
#include "quantum_keycodes.h"
#include "rgb_matrix.h"
#include QMK_KEYBOARD_H

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =  { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [1] =  { ENCODER_CCW_CW(KC_MRWD, KC_MFFD)  },
    [2] =  { ENCODER_CCW_CW(_______, _______)  }
};
#endif

enum shyft_layers {
    L_HOME,
    L_FN,
    L_EXTRA,

    L_MC,
    L_MC_UTIL,
    L_MC_TEXT
};

enum mc_keycodes {
    MC_OPEN_CHAT = KC_U,
    MC_TEXT = SAFE_RANGE,
    MC_COMMAND,
    MC_CANCEL,
    MC_SEND,
};

enum mc_f3keys {
    F3_CHUNK_RELOAD = KC_A,
    F3_HITBOX = KC_B,
    F3_POS = KC_C,
    F3_CLEARCHAT = KC_D,
    F3_RENDERDIST = KC_F,
    F3_RELOADRES = KC_T,
};

enum mc_binds {
    MC_FORWARD = KC_E,
    MC_BACKWARD,
    MC_LEFT,
    MC_RIGHT,
};
const HSV HSV_DEFAULT = {20, 200, 255};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // BASE
    [L_HOME] = LAYOUT_65_ansi_blocker(
    KC_ESC,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINS,    KC_EQL,     KC_BSPC,    KC_MUTE,
    KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_LBRC,    KC_RBRC,    KC_BSLS,    KC_DELETE,
    KC_F24,     KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,                KC_ENT,     KC_INSERT,
    KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSFT,                KC_UP,      KC_PAGE_DOWN,
    KC_LCTL,    KC_LGUI,    KC_LALT,                            KC_SPC,                             MO(1),      KC_RCTL,                            KC_LEFT,    KC_DOWN,    KC_RIGHT
    ),
    // FUNCTION
    [L_FN] = LAYOUT_65_ansi_blocker(
    KC_GRV,     KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,     _______,    _______,
    _______,    KC_BLE1,    KC_BLE2,    KC_BLE3,    KC_24G,     _______,    _______,    _______,    _______,    _______,    _______,    KC_HOME,    KC_PGUP,    RGB_MOD,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_MPRV,    _______,    KC_MNXT,    KC_END,     KC_PGDN,                RGB_HUI,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    MO(2),                  RGB_VAI,    _______,
    _______,    _______,    _______,                           KC_MPLY,                             _______,    _______,                            RGB_SPD,    RGB_VAD,    RGB_SPI
    ),
    // FUNCTION + RSHIFT (UTILITY)
    [L_EXTRA] = LAYOUT_65_ansi_blocker(
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    QK_MAKE,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    QK_MAKE,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______,    TO(L_MC),
    _______,    _______,    _______,                            _______,                            _______,    _______,                            _______,    _______,    _______
    ),
    // MINECRAFT
    // [MINECRAFT_LAYER] = LAYOUT_65_ansi_blocker(
    // _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    // _______,    _______,    _______,    _______,    _______,    KC_F,       _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    // _______,    KC_LBRC,    _______,    KC_RBRC,    KC_K,       _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______,    _______,
    // _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______,    _______,
    // _______,    KC_RSFT,    LT(MINECRAFT_UTIL_LAYER, ),                            _______,                            _______,    KC_LGUI,                            _______,    _______,    _______
    // ),
    [L_MC] = LAYOUT_65_ansi_blocker(
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    _______,    _______,    _______,    _______,    KC_O   ,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    KC_M   ,    _______,    KC_LBRC,    KC_RBRC,    KC_J   ,    KC_0   ,    KC_G   ,    _______,    _______,    _______,    _______,                _______,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_A,       _______,    _______,    MC_COMMAND, _______,                _______,    TO(L_HOME),
    _______,    KC_DOT ,    LM(L_MC_UTIL, MOD_LALT),            _______,                            _______,    _______,                            _______,    _______,    _______
    ),
    [L_MC_UTIL] = LAYOUT_65_ansi_blocker(
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    KC_LGUI,    _______,    MC_TEXT,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______,    _______,
    _______,    _______,    _______,                            _______,                            _______,    _______,                            _______,    _______,    _______
    ),
    [L_MC_TEXT] = LAYOUT_65_ansi_blocker(
    MC_CANCEL,  _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                MC_SEND,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______,    _______,
    _______,    _______,    _______,                            _______,                            _______,    _______,                            _______,    _______,    _______
    ),


    // EMPTY
    // [____] = LAYOUT_65_ansi_blocker(
    // _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    // _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    // _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______,    _______,
    // _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                _______,    _______,
    // _______,    _______,    _______,                            _______,                            _______,    _______,                            _______,    _______,    _______
    // )
};


void keyboard_post_init_user(void) {
    rgb_matrix_set_flags(LED_FLAG_KEYLIGHT);
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv(HSV_DEFAULT.h, HSV_DEFAULT.s, rgb_matrix_config.hsv.v);

    debug_enable=true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {


    switch (keycode) {
        case MC_TEXT:
            if (record->event.pressed) {
                tap_code(MC_OPEN_CHAT);
                layer_move(L_MC_TEXT);
                // layer_debug();
            }
            return false;
        case MC_COMMAND:
            if (record->event.pressed) {
                tap_code(KC_SLSH);
                layer_move(L_MC_TEXT);
                // layer_debug();
            }
            return false;
        case MC_SEND:
            if (record->event.pressed) {
                tap_code(KC_ENTER);
                layer_move(L_MC);
            }
            return false;
        case MC_CANCEL:
            if (record->event.pressed) {
                tap_code(KC_ESCAPE);
                layer_move(L_MC);
            }
            return false;
    }
    return true;

}

bool rgb_matrix_indicators_user(void) {
    int indicator_led = 3;
    switch(get_highest_layer(layer_state|default_layer_state)) {
        case L_MC:
            rgb_matrix_set_color(indicator_led, 0, 50, 0);
            break;
        case L_MC_TEXT:
            rgb_matrix_set_color(indicator_led, 20, 50, 0);
            break;
        default:
            // HSV base = {HSV_DEFAULT.h, HSV_DEFAULT.s, rgb_matrix_config.hsv.v};
            // RGB rgb = hsv_to_rgb(base);
            // rgb_matrix_set_color(indicator_led, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(indicator_led, 0, 0, 0);
            break;
    }

    return false;
}
