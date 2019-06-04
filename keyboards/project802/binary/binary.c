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

#include "binary.h"

#define KEY_BUILDER_TIMEOUT_MS   350
#define DFU_TIMEOUT_MS           7000

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

bool process_record_kb( uint16_t keycode, keyrecord_t *record )
{
	bool retVal = false;
	
	dprintf( "key: %d pressed: %d\r\n", keycode, record->event.pressed );
	
	// Any action press or release should always reset the DFU timer
	dfuTimer = 0;
	
	switch( keycode )
	{
		case KC_0:
		case KC_1:
			if( !record->event.pressed || (bitsCollected >= 16) )
			{
				break;
			}
			
			keyBuilderTimer = timer_read();
			keyBuilder = keyBuilder << 1;
			
			if( keycode == KC_1 )
			{
				keyBuilder |= 1;
			}
			
			dprintf( "building: 0x%04x\r\n", keyBuilder );
			
			// Fast-forward the timeout for sending the code if max bits are collected
			if( ++bitsCollected >= 16 )
			{
				keyBuilderTimer -= KEY_BUILDER_TIMEOUT_MS;
			}
			break;

		default:
			if( record->event.pressed )
			{
				dfuTimer = timer_read();
			}

			retVal = process_record_user( keycode, record );
			break;
	}
	
	return retVal;
}

void matrix_scan_kb( void )
{
	if( (keyBuilderTimer > 0) && (timer_elapsed(keyBuilderTimer) > KEY_BUILDER_TIMEOUT_MS) )
	{
		dprintf( "Sending 0x%04x\r\n", keyBuilder );
		tap_code( keyBuilder );
		keyBuilder = 0;
		keyBuilderTimer = 0;
		bitsCollected = 0;
	}
	
	if( (dfuTimer > 0) && (timer_elapsed(dfuTimer) > DFU_TIMEOUT_MS) )
	{
		reset_keyboard();
	}
	
	matrix_scan_user();
}

void keyboard_post_init_user( void )
{
#if CONSOLE_ENABLE == yes
	debug_enable = true;
#endif
}
