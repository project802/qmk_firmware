/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0xB101
#define DEVICE_VER 		0x0001
#define MANUFACTURER    Project 802
#define PRODUCT         Zesk Hommage Keyboard
#define DESCRIPTION     Project 802 Zesk Hommage Keyboard

/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 6

/* 9Key PCB default pin-out */
#define MATRIX_ROW_PINS { B4 }
#define MATRIX_COL_PINS { B3, B2, B6,F6, F7, B1 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define TAPPING_TERM 200

#define CATERINA_BOOTLOADER

#endif
