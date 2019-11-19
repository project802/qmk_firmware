/* Copyright 2018 Jack Humbert
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = {
			{ KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_O },
			{ KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_M },
			{ KC_CAPS,  KC_A,    KC_S,    KC_D,    KC_F,    KC_F1 },
			{ KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    XXXXXXX },
			{ KC_LCTRL, XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC,  LT(1, KC_R) }
		},
  [1] = {
			{ RESET,    KC_1,    KC_2,    KC_3,    KC_4,    KC_O },
			{ KC_TAB,   KC_Q,    KC_UP,   KC_E,    KC_R,    KC_M },
			{ KC_CAPS,  KC_LEFT, KC_DOWN, KC_RGHT, KC_G,    KC_F1 },
			{ KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    XXXXXXX },
			{ KC_LCTRL, XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC,  XXXXXXX }
		}
};
