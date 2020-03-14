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

#include "usb_vol.h"

void matrix_init_kb(void) {
  // Turn status LED on
  setPinOutput( C13 );
  writePinHigh( C13 );

  matrix_init_user();
}

uint16_t keyBuilderTimer = 0;
uint16_t keyBuilder = 0;
unsigned bitsCollected = 0;

uint16_t dfuTimer = 0;

void matrix_scan_kb( void )
{
	matrix_scan_user();
}

void encoder_update_kb( uint8_t index, bool clockwise )
{
	//dprintf( "encoder: index %d, clockwise %d\n", index, clockwise );
	
	uint16_t code = clockwise ? KC_VOLU : KC_VOLD;
	
	uint16_t held_keycode_timer = timer_read();
	
	register_code16( code );
	
	while( timer_elapsed(held_keycode_timer) < 10 );
	
	unregister_code16( code );
}

void keyboard_post_init_user( void )
{
#if CONSOLE_ENABLE
	debug_enable = true;
#endif
}
