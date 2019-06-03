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

#define BIT_COLLECTION_TIMEOUT 500

void matrix_init_kb(void) {
  // Turn status LED on
  setPinOutput(C13);
  writePinHigh(C13);

  matrix_init_user();
}

uint16_t timeLatch = 0;
uint16_t keyBuilder = 0;
unsigned bitsCollected = 0;

bool process_record_kb( uint16_t keycode, keyrecord_t *record )
{
	bool retVal = false;
	
	switch( keycode )
	{
		case KC_0:
		case KC_1:
			if( !record->event.pressed || (bitsCollected >= 16) )
			{
				break;
			}
			
			timeLatch = timer_read();
			keyBuilder = keyBuilder << 1;
			
			if( keycode == KC_1 )
			{
				keyBuilder |= 1;
			}
			
			// Fast-forward the timeout for sending the code if max bits are collected
			if( ++bitsCollected >= 16 )
			{
				timeLatch -= BIT_COLLECTION_TIMEOUT;
			}
			break;
		
		default:
			retVal = process_record_user( keycode, record );
			break;
	}
	
	return retVal;
}

void matrix_scan_kb( void )
{
	if( (timeLatch > 0) && (timer_elapsed(timeLatch) > 500) )
	{
		tap_code( keyBuilder );
		keyBuilder = 0;
		timeLatch = 0;
		bitsCollected = 0;
	}
	
	matrix_scan_user();
}

void keyboard_post_init_user( void )
{
	debug_enable = true;
}
