/* Copyright 2023 @ Keychron (https://www.keychron.com)
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

#include QMK_KEYBOARD_H
#include "quantum/process_keycode/process_combo.h"

enum combo_events {
    CAPS_COMBO, // Our single combo index
};

const uint16_t PROGMEM caps_combo_keys[] = {KC_LSFT, KC_RSFT, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [CAPS_COMBO] = COMBO_ACTION(caps_combo_keys),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case CAPS_COMBO:
            if (pressed) {
                // When both LShift + RShift are pressed, send a Caps Lock press
                tap_code(KC_CAPS);
            }
            break;
    }
}

// clang-format off
enum layers{
  MAC_BASE,
  MAC_FN,
  MAC_CAPS,
  DEFAULT_MAC_BASE,
};

enum custom_keycodes {
    BRACES = SAFE_RANGE,
    PARENS,
    SEND_TEXT,
    LW_EMAIL,
    GOV_EMAIL,
    SEND_PIN,
    LEFT_RESIZE,
    RIGHT_RESIZE,
    FULLSCREEN,
    MINIMIZE,
    KC_JIGGLE = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    const uint8_t mods = get_mods();
    const uint8_t oneshot_mods = get_oneshot_mods();

    switch (keycode) {
        case BRACES:
            if (record->event.pressed) {
                clear_oneshot_mods();
                unregister_mods(MOD_MASK_CSAG);
                if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {
                    SEND_STRING("{}");
                } else {
                    SEND_STRING("[]");
                }
                tap_code(KC_LEFT);
                register_mods(mods);
                return false;
            }

        case PARENS:
            if (record->event.pressed) {
                clear_oneshot_mods();
                unregister_mods(MOD_MASK_CSAG);
                if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {
                    SEND_STRING("()");
                    tap_code(KC_LEFT);
                    register_mods(mods);
                    return false;
                } else {
                    SEND_STRING("9");
                }
                register_mods(mods);
                return true;
            }
        case SEND_TEXT:
            if (record->event.pressed) {
                clear_oneshot_mods();
                unregister_mods(MOD_MASK_CSAG);
                SEND_STRING("hello world\n");
                register_mods(mods);
                return false;
            }
        case LW_EMAIL:
            if (record->event.pressed) {
                clear_oneshot_mods();
                unregister_mods(MOD_MASK_CSAG);
                SEND_STRING(LASTWALL_EMAIL);
                register_mods(mods);
                return false;
            }
        case GOV_EMAIL:
            if (record->event.pressed) {
                clear_oneshot_mods();
                unregister_mods(MOD_MASK_CSAG);
                SEND_STRING(LASTWALL_GOV_EMAIL);
                register_mods(mods);
                return false;
            }
        case SEND_PIN:
            if (record->event.pressed) {
                clear_oneshot_mods();
                unregister_mods(MOD_MASK_CSAG);
                SEND_STRING(YUBIKEY_PIN);
                register_mods(mods);
                return false;
            }
        case LEFT_RESIZE:
            if (record->event.pressed) {
                clear_oneshot_mods();
                unregister_mods(MOD_MASK_CSAG);

                register_code(KC_LGUI);
                register_code(KC_LALT);
                register_code(KC_LCTL);
                register_code(KC_LSFT);

                tap_code(KC_L);

                unregister_code(KC_LGUI);
                unregister_code(KC_LALT);
                unregister_code(KC_LCTL);
                unregister_code(KC_LSFT);

                register_mods(mods);
                return false;
            }
        case RIGHT_RESIZE:
            if (record->event.pressed) {
                clear_oneshot_mods();
                unregister_mods(MOD_MASK_CSAG);

                register_code(KC_LGUI);
                register_code(KC_LALT);
                register_code(KC_LCTL);
                register_code(KC_LSFT);

                tap_code(KC_RBRC);

                unregister_code(KC_LGUI);
                unregister_code(KC_LALT);
                unregister_code(KC_LCTL);
                unregister_code(KC_LSFT);

                register_mods(mods);
                return false;
            }
        case FULLSCREEN:
            if (record->event.pressed) {
                clear_oneshot_mods();
                unregister_mods(MOD_MASK_CSAG);

                register_code(KC_LGUI);
                register_code(KC_LALT);
                register_code(KC_LCTL);
                register_code(KC_LSFT);

                tap_code(KC_Z);

                unregister_code(KC_LGUI);
                unregister_code(KC_LALT);
                unregister_code(KC_LCTL);
                unregister_code(KC_LSFT);

                register_mods(mods);
                return false;
            }
        case MINIMIZE:
            if (record->event.pressed) {
                clear_oneshot_mods();
                unregister_mods(MOD_MASK_CSAG);

                register_code(KC_LGUI);
                register_code(KC_LALT);
                register_code(KC_LCTL);
                register_code(KC_LSFT);

                tap_code(KC_M);

                unregister_code(KC_LGUI);
                unregister_code(KC_LALT);
                unregister_code(KC_LCTL);
                unregister_code(KC_LSFT);

                register_mods(mods);
                return false;
            }

    }

    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[MAC_BASE] = LAYOUT_ansi_84(
     KC_ESC,        KC_BRID,  KC_BRIU,  KC_MCTL,  KC_LPAD,  BL_DOWN,  BL_UP,    KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_SNAP,  KC_DEL,   RGB_TOG,
     KC_GRV,        KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
     KC_TAB,        KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
     MO(MAC_CAPS),  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_HOME,
     KC_LSFT,                 KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,    KC_END,
     KC_LCTL,       KC_LOPTN, KC_LCMMD,                               KC_SPC,                                 KC_RCMMD,MO(MAC_FN),KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

[MAC_FN] = LAYOUT_ansi_84(
     KC_TRNS,       KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_TRNS,  KC_TRNS,  RGB_TOG,
     KC_TRNS,       BT_HST1,  BT_HST2,  BT_HST3,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     RGB_TOG,       RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     KC_TRNS,       RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,            KC_TRNS,
     KC_TRNS,                 KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  BAT_LVL,  NK_TOGG,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,       KC_TRNS,  KC_TRNS,                                KC_TRNS,                                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),


[MAC_CAPS] = LAYOUT_ansi_84(
     KC_TRNS,       KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,       KC_TRNS,    KC_TRNS,  QK_BOOT,
     KC_TRNS,       BT_HST1,  BT_HST2,  BT_HST3,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  PARENS,   KC_TRNS,  KC_TRNS,  KC_TRNS,      KC_TRNS,            KC_TRNS,
     RGB_TOG,       RGB_MOD,  RGB_VAI,  LW_EMAIL, GOV_EMAIL,RGB_SPI,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  BRACES,   KC_TRNS,      KC_TRNS,            KC_TRNS,
     KC_TRNS,       RGB_RMOD, RGB_VAD,  RGB_HUD,  SEND_PIN, SEND_TEXT,KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,      KC_TRNS,
     KC_TRNS,                 KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  BAT_LVL,  NK_TOGG,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,      FULLSCREEN,  KC_TRNS,
     KC_TRNS,       KC_TRNS,  KC_TRNS,                      KC_TRNS,                                KC_TRNS,  KC_TRNS,  KC_TRNS,  LEFT_RESIZE,  MINIMIZE,   RIGHT_RESIZE),

[DEFAULT_MAC_BASE] = LAYOUT_ansi_84(
     KC_ESC,        KC_BRID,  KC_BRIU,  KC_MCTL,  KC_LPAD,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_SNAP,  KC_DEL,   RGB_MOD,
     KC_GRV,        KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
     KC_TAB,        KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
     KC_CAPS,       KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_HOME,
     KC_LSFT,                 KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,    KC_END,
     KC_LCTL,       KC_LOPTN, KC_LCMMD,                               KC_SPC,                                 KC_RCMMD,MO(MAC_FN),KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),
};
