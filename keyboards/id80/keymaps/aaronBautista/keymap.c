/* Copyright 2020 Sergey Vlasov <sigprof@gmail.com>
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

struct RGB_MODE{
  bool rgbEnabled;
  uint8_t rgbMode;
  uint16_t rgbHue;
  uint8_t rgbSat;
  uint8_t rgbVal;
  uint8_t rgbSpeed;
};

typedef struct RGB_MODE RGBMode;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,    KC_F1,   KC_F2,   KC_F3,   KC_F4,     KC_F5,   KC_F6,   KC_F7,   KC_F8,     KC_F9,   KC_F10,  KC_F11,  KC_F12,     MO(1),     KC_INS,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,            KC_HOME,
        KC_TAB,      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,        KC_DEL,
        KC_CAPS,       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT,            KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,
        KC_LCTL,   KC_LGUI,   KC_LALT,                       KC_SPC,                              KC_RALT,     KC_RCTL,        KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT(
        RESET,     _______, _______, _______, _______,   _______, _______, _______, _______,   _______, _______, _______, _______,    _______,   KC_MUTE,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______,
        _______,     RGB_TOG, _______, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______, _______,        _______,
        _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,            _______, _______, BL_DEC,  BL_TOGG, BL_INC,  NK_TOGG, _______, _______, _______, _______, _______,          BL_INC,
        _______,   _______,   _______,                      _______,                              _______,     _______,        BL_TOGG, BL_DEC,  BL_STEP
    ),
    [2] = LAYOUT(
        _______,   _______, _______, _______, _______,   _______, _______, _______, _______,   _______, _______, _______, _______,    _______,   _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______,
        _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,        _______,
        _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,   _______,   _______,                      _______,                              _______,     _______,        _______, _______, _______
    ),
    [3] = LAYOUT(
        _______,   _______, _______, _______, _______,   _______, _______, _______, _______,   _______, _______, _______, _______,    _______,   _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______,
        _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,        _______,
        _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,   _______,   _______,                      _______,                              _______,     _______,        _______, _______, _______
    ),
};

static RGBMode capsOffRGB;
static RGBMode capsOnRGB;

RGBMode GetRGBMode(bool rgbEnabled, uint8_t rgbMode, uint16_t rgbHue, uint8_t rgbSat, uint8_t rgbVal, uint8_t rgbSpeed)
{
  RGBMode current;

  current.rgbEnabled = rgbEnabled;
  current.rgbMode = rgbMode;
  current.rgbHue = rgbHue;
  current.rgbSat = rgbSat;
  current.rgbVal = rgbVal;
  current.rgbSpeed = rgbSpeed;

  return current;
}

void SetRGBMode(RGBMode newMode)
{
  newMode.rgbEnabled ? rgblight_enable() : rgblight_disable();
  rgblight_mode(newMode.rgbMode);
  rgblight_sethsv(newMode.rgbHue, newMode.rgbSat, newMode.rgbVal);
  rgblight_set_speed(newMode.rgbSpeed);
}

static bool capsDefined = false;
static bool capsSaved = false;

// NOTE: USER SET CAPS LOCK RGB
bool led_update_user(led_t led_state) {
    static uint8_t caps_state = 0;
    if (caps_state != led_state.caps_lock) {
      caps_state = led_state.caps_lock;

      if(!capsDefined)
      {
        capsOnRGB = GetRGBMode(rgblight_is_enabled(), rgblight_get_mode(), rgblight_get_hue(), rgblight_get_sat(), rgblight_get_val(), rgblight_get_speed());
        capsDefined = true;
      }

      if(caps_state && !capsSaved)
      {
        //if caps turned on
        capsOffRGB = GetRGBMode(rgblight_is_enabled(), rgblight_get_mode(), rgblight_get_hue(), rgblight_get_sat(), rgblight_get_val(), rgblight_get_speed());
        SetRGBMode(capsOnRGB);
        capsSaved = true;
      }
      else if(!caps_state && capsSaved)
      {
        //if caps turned off
        capsOnRGB = GetRGBMode(rgblight_is_enabled(), rgblight_get_mode(), rgblight_get_hue(), rgblight_get_sat(), rgblight_get_val(), rgblight_get_speed());
        SetRGBMode(capsOffRGB);
        capsSaved = false;
      }
    }

    return true;
}