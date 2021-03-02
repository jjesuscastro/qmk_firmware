/* Copyright 2018 'mechmerlin'
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

// Defines the keycodes used by our macros in process_record_user
#define _QWERTY 0
#define _FN1 1
#define CLSPD 500

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  FN1,
  CSPDD,
  CSPDI,
  SNIP
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap (Base Layer) Default Layer
   * ,---------------------------------------------------------------------------------------------------------------------------.
   * |  Esc  |  1    |  2    |  3    |  4    |  5    |  6    |  7    |  8    |  9    |  0    |  -    |  =    |  Backsp   |  DEL  |
   * |---------------------------------------------------------------------------------------------------------------------------|
   * |   Tab   |  Q    |  W    |  E    |  R    |  T    |  Y    |  U    |  I    |  O    |  P    |  [    |  ]    |  \      | PSCR  |
   * |---------------------------------------------------------------------------------------------------------------------------|
   * |    Cap    |  A    |  S    |  D    |  F    |  G    |  H    |  J    |  K    |  L    |  ;    |  '    |    Return     | HOME  |
   * |---------------------------------------------------------------------------------------------------------------------------|
   * |    Shift     |  Z    |  X    |  C    |  V    |  B    |  N    |  M    |  ,    |  .    |  /    |   Shift    |  Up   |  End  |
   * |---------------------------------------------------------------------------------------------------------------------------|
   * | Ctrl  |  Win  |  Alt  |                      Space                        |  Alt  |  FN   | Ctrl  | Left  | Down  | Right |
   * `---------------------------------------------------------------------------------------------------------------------------'
   */
[_QWERTY] = LAYOUT_65_ansi(
  KC_ESC,  KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL, \
  KC_TAB,  KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PSCR, \
  KC_CAPS, KC_A,    KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT, KC_HOME,  \
  KC_LSFT, KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,  \
  KC_LCTL, KC_LGUI, KC_LALT,                KC_SPC,                          KC_RALT, MO(_FN1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),

  /* Keymap FN1 Layer
   * ,---------------------------------------------------------------------------------------------------------------------------.
   * |  ~ `  |  F1   |  F2   |  F3   |  F4   |  F5   |  F6   | F7    | F8    | F9    | F10   | F11   | F12   |  Delete   | PrtSc |
   * |---------------------------------------------------------------------------------------------------------------------------|
   * |         |       |       |       |       |       |       |       |       |       |       |       |       |         |       |
   * |---------------------------------------------------------------------------------------------------------------------------|
   * |           |       |       |       |       |       |       |       |       |       |       |       |               |       |
   * |---------------------------------------------------------------------------------------------------------------------------|
   * |              |       |       |       |       |       |       |       |       |       |       |            | VolUp | VolM  |
   * |---------------------------------------------------------------------------------------------------------------------------|
   * | RESET |       |       |                                                   |       |       | Play  | Prev  | VolDo | Next  |
   * `---------------------------------------------------------------------------------------------------------------------------'
   */
[_FN1] = LAYOUT_65_ansi(
  KC_GRV, KC_F1,   KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,   KC_F9,  KC_F10,     KC_F11,  KC_F12, _______,   RESET, \
 _______,_______,_______,_______,_______,_______,_______,_______,_______, _______, _______,    _______, _______, _______,    SNIP, \
 _______,  CSPDD,  CSPDI,_______,_______,_______,_______,_______,_______, _______,    _______, _______,          _______, _______, \
 _______, RGB_TOG, RGB_RMOD, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI,  _______,     _______,KC_VOLU,KC_MUTE, \
 _______, _______,  _______,                       _______,                        _______,_______,KC_MPLY,KC_MPRV,KC_VOLD, KC_MNXT)
};

static uint32_t cpspd = CLSPD;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CSPDD:
      if (record->event.pressed) {
        cpspd -= 100;
        if (cpspd < 100)
          cpspd = 100;
      }
      return false;
      break;
    case CSPDI:
      if (record->event.pressed) {
        cpspd += 100;
      }
      return false;
      break;
    case SNIP:
      if (record->event.pressed) {
        SEND_STRING(SS_DOWN(X_LGUI) SS_DOWN(X_LSHIFT) SS_TAP(X_S) SS_UP(X_LGUI) SS_UP(X_LSHIFT));
      }
      return false;
      break;
  }
  return true;
}

static uint32_t key_timer = 0;
static bool caps_on = false;
static bool rgblight_on;

bool led_update_user(led_t led_state) {
    static uint8_t caps_state = 0;
    if (caps_state != led_state.caps_lock) {
      caps_state = led_state.caps_lock;

      if(!caps_on)
        rgblight_on = rgblight_is_enabled();
      else
        rgblight_on ? rgblight_enable() : rgblight_disable();

      caps_on = caps_state ? true : false;
    }

    return true;
}

void matrix_scan_user(void) { 
    if (timer_elapsed32(key_timer) > cpspd) { 
        key_timer = timer_read32();  // resets timer
        if(caps_on) rgblight_toggle();
    }
}