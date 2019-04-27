#include "zesk_hommage.h"

// Macro Declarations
enum {
  MK_READ = 0
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* LAYER 0
 * ,-----------------------.
 * | Macro |   Up  | LT/Ent|
 * |-------+-------+-------|
 * |  Left |  Down |  Up   |
 * `-----------------------'
 */
[0] = KEYMAP( \
  KC_AUDIO_MUTE,  		KC_AUDIO_VOL_UP,    LT(1, KC_MEDIA_PLAY_PAUSE),
  KC_MEDIA_PREV_TRACK,	KC_AUDIO_VOL_DOWN,  KC_MEDIA_NEXT_TRACK  \
),
/*
[0] = KEYMAP( \
  M(MK_READ),  KC_UP,    LT(1, KC_ENTER),
  KC_LEFT,     KC_DOWN,  KC_RIGHT  \
),
*/
/* LAYER 1
 * ,-----------------------.
 * | RESET |   2   |   3   |
 * |-------+-------+-------|
 * |   4   |   5   |   6   |
 * `-----------------------'
 */
[1] = KEYMAP( \
  RESET,  			KC_2,  KC_3,  
  KC_SYSTEM_SLEEP,  KC_5,  KC_SYSTEM_WAKE  \
),

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  if (record->event.pressed) {
      switch(id) {
          case MK_READ:
              SEND_STRING(SS_TAP(X_APPLICATION)"k");
              return false;
      }
  }
  return MACRO_NONE;
};

void matrix_init_user(void) {
}


