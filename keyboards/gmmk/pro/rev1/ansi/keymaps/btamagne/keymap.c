/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>
   Copyright 2022 Ben Tamagne <bentamagne@gmail.com>

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

#include QMK_KEYBOARD_H
#include "features/custom_shift_keys.h"

enum layers {
   LAYER_BASE,       //WIN_BASE = 0,
   LAYER_FN,         //WIN_FN,
   LAYER_CODE,       //MAC_BASE,
   LAYER_MOUSE,      //MAC_FN
   LAYER_WORKMAN,    // BDT
   LAYER_WORKMAN_FN, // BDT
   LAYER_WORKMAN_MOUSE
};

enum custom_keycodes {
    KC_MACRO_1 = SAFE_RANGE,
    KC_MACRO_2,
    KC_MACRO_3,
    KC_MACRO_4
    //KC_MISSION_CONTROL = SAFE_RANGE,
    //KC_LAUNCHPAD
};

// Home row mods: GACS --- SCAG
#define HM_A LGUI_T(KC_A)
#define HM_S LALT_T(KC_S)
#define HM_H LCTL_T(KC_H)
#define HM_T LSFT_T(KC_T)

#define HM_N RSFT_T(KC_N)
#define HM_E RCTL_T(KC_E)
#define HM_O RALT_T(KC_O)
#define HM_I RGUI_T(KC_I)

// Custom shifts
const custom_shift_key_t custom_shift_keys[] = {
  {KC_EXLM, KC_1},    // Shift ! is 1
  {KC_AT,   KC_2},    // Shift @ is 2
  {KC_HASH, KC_3},    // Shift # is 3
  {KC_DLR,  KC_4},    // Shift $ is 4
  {KC_PERC, KC_5},    // Shift % is 5
  {KC_CIRC, KC_6},    // Shift ^ is 6
  {KC_AMPR, KC_7},    // Shift & is 7
  {KC_ASTR, KC_8},    // Shift * is 8
  {KC_LPRN, KC_9},    // Shift ( is 9
  {KC_RPRN, KC_0},    // Shift ) is 0
  {KC_LCBR, KC_LBRC}, // Shift { is [
  {KC_LCBR, KC_RBRC}, // Shift } is ]
};

uint8_t NUM_CUSTOM_SHIFT_KEYS = sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

//#define KC_MCTL KC_MISSION_CONTROL // Mac-specific
//#define KC_LPAD KC_LAUNCHPAD       // Mac-specific
//#define TO_WINB TO(WIN_BASE)
//#define TO_MACB TO(MAC_BASE)
//#define MO_WINF MO(WIN_FN)
//#define MO_MACF MO(MAC_FN)

// Momentary layer aliases
#define MO_FN   MO(LAYER_FN)
#define MO_CODE MO(LAYER_CODE)
#define MO_MOUS MO(LAYER_MOUSE)
#define MO_W_FN MO(LAYER_WORKMAN_FN)
#define MO_W_MS MO(LAYER_WORKMAN_MOUSE)


// Toggle layer aliases
#define TO_BASE TO(LAYER_BASE)
#define TG_WRKM TG(LAYER_WORKMAN)

// Windows shortcuts
#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)

// VSCode Shortcuts (used on LAYER_CODE)
#define TRNS_UP LCA(KC_EQL)  // Window transparency up
#define TRNS_DN LCA(KC_MINS)  // Window transparency down
#define GEN_DOC LCTL(KC_DOT) // Generate documentation (Mintlify extension)
#define TG_SCRN RALT(KC_GRV) // Toggle screencast mode
#define TG_TERM LCTL(KC_GRV) // Toggle terminal

// Macro keycode aliases
#define KC_MAC1 KC_MACRO_1
#define KC_MAC2 KC_MACRO_2
#define KC_MAC3 KC_MACRO_3
#define KC_MAC4 KC_MACRO_4

// Encoder masks
#define MODS_ALT_MASK (MOD_BIT(KC_LALT)) // Make ALT layer for encoder use
#define MODS_CTRL_MASK (MOD_BIT(KC_LCTL)) // Make CTRL layer for encoder use

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   // There are two keys used to access the 3 additional layers in this keymap.
   //    The "Function" layer is accessed momentarily by holding down the FN key.
   //    The "Code" layer is accessed momentarily by holding down the CODE key (conventionally RSFT).
   //    The "Mouse" layer is accessed momentarily by holding down the FN key then also hold down the CODE key.
   //
   // The Function layer contains the RESET key, Windows function row controls, RGB controls, and media controls.
   // The Code layer contains commands for various shortcuts I frequently use in VSCode.
   //    I plan to expand upon the code layer in the future.
   // The Mouse layer contains commands for controlling the mouse.
   //
   // The FN key by default maps to a momentary toggle to layer 1 to provide access to the RESET key (to put the board into bootloader mode). Without
   // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
   // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
   // if that's your preference.
   //
   // To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
   // it'll be back to normal when you plug it back in.
   //
   // This keyboard defaults to 6KRO instead of NKRO for compatibility reasons (some KVMs and BIOSes are incompatible with NKRO).
   // Since this is, among other things, a "gaming" keyboard, a key combination to enable NKRO on the fly is provided for convenience.
   // Press Fn+N to toggle between 6KRO and NKRO. This setting is persisted to the EEPROM and thus persists between restarts.

   /* Base Layout
      *
      * ,-------------------------------------------------------------------------------------------------------------.
      * | Esc  ||  F1  |  F2  |  F3  |  F4  ||  F5  |  F6  |  F7  |  F8  ||  F9  | F10  | F11  | F12  || Del  || Mute |
      * |=============================================================================================================|
      * |  ` ~ |  1 ! |  2 @ |  3 # |  4 $ |  5 % |  6 ^ |  7 & |  8 * |  9 ( |  0 ) |  - _ |  = + |  Backspc || Home |
      * |------+------+------+------+------+------+------+------+------+------+------+------+------+----------++------|
      * |   Tab   |  Q   |  W   |  E   |  R   |  T   |  Y   |  U   |  I   |  O   |  P   | [ }  | ] }  |  \ |  || End  |
      * |---------+------+------+------+------+------+------+------+------+------+------+------+------+-------++------|
      * |  Capslock  |  A   |  S   |  D   |  F  |  G   |  H   |  J   |  K   |  L   | ; :  | ' "  |    Enter   || PgUp |
      * |------------+------+------+------+-----+------+------+------+------+------+------+------|----+========+------|
      * |    LShift    |  Z   |  X   |  C   |  V   |  B   |  N   |  M   | , <  | . >  | / ?  | RShift ||  Up  || PgDn |
      * |--------------+------+------+------+------+------+------+------+------+------+------+--+=====++------++======|
      * |  Ctrl  |   Win  |  LAlt  |               Space                  | RAlt |  Fn  | Ctrl || Left | Down | Rght |
      * `------------------------------------------------------------------------------------------------------------'
      */

   [LAYER_BASE] = LAYOUT(
      /*fn*/  KC_ESC,  KC_F1,   KC_F2,   KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,           KC_MUTE,
      /*num*/ KC_GRV,  KC_1,    KC_2,    KC_3,     KC_4,     KC_5,     KC_6,     KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_HOME,
      /*Q*/   KC_TAB,  KC_Q,    KC_W,    KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_END,
      /*A*/   KC_CAPS, KC_A,    KC_S,    KC_D,     KC_F,     KC_G,     KC_H,     KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGUP,
      /*Z*/   KC_LSFT,          KC_Z,    KC_X,     KC_C,     KC_V,     KC_B,     KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          MO_CODE, KC_UP,   KC_PGDN,
      /*sp*/  KC_LCTL, KC_LGUI, KC_LALT,                               KC_SPC,                              KC_RALT, MO_FN,   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
   ),

   [LAYER_FN] = LAYOUT(
      /*fn*/  RESET,   KC_BRID, KC_BRIU, KC_TASK,  KC_FLXP,  KC_MPRV,  KC_MNXT,  KC_MPLY, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, _______, KC_INS,           _______,
      /*num*/ _______, _______, _______, _______,  _______,  _______,  _______,  _______, _______, _______, _______, _______, _______, _______,          KC_MAC1,
      /*Q*/   RGB_TOG, RGB_MOD, RGB_VAI, RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______, _______, _______, _______, _______, _______, RESET,            KC_MAC2,
      /*A*/   _______, RGB_M_P, RGB_M_B, RGB_M_R,  RGB_M_SW, RGB_M_SN, RGB_M_K,  RGB_M_X, RGB_M_G, RGB_M_T, _______, _______,          _______,          KC_MAC3,
      /*Z*/   _______,          _______, _______,  _______,  _______,  _______,  NK_TOGG, _______, _______, _______, _______,          MO_MOUS, KC_VOLU, KC_MAC4,
      /*sp*/  _______, KC_TASK, _______,                               KC_MPLY,                             _______, _______, TG_WRKM, KC_MPRV, KC_VOLD, KC_MNXT
   ),

   [LAYER_CODE] = LAYOUT(
      /*fn*/  _______, _______, _______, _______, _______,  _______,  _______,  _______, _______, _______, _______, _______, _______, _______,          _______,
      /*num*/ TG_SCRN, _______, _______, _______, _______,  _______,  _______,  _______, _______, _______, _______, TRNS_DN, TRNS_UP, _______,          _______,
      /*Q*/   _______, _______, _______, _______, _______,  _______,  _______,  _______, _______, _______, _______, _______, _______, _______,          _______,
      /*A*/   _______, _______, _______, _______, _______,  _______,  _______,  _______, _______, _______, _______, _______,          _______,          _______,
      /*Z*/   _______,          _______, _______, _______,  _______,  _______,  _______, _______, _______, GEN_DOC, _______,          _______, _______, _______,
      /*sp*/  _______, _______, _______,                              TG_TERM,                             _______, _______, _______, _______, _______, _______
   ),

   [LAYER_MOUSE] = LAYOUT(
      /*fn*/  _______, _______, _______, _______, _______,  _______,  _______,  _______, _______, _______, _______, _______, _______, _______,          _______,
      /*num*/ _______, _______, _______, _______, _______,  _______,  _______,  _______, _______, _______, _______, _______, _______, _______,          _______,
      /*Q*/   _______, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U,  _______,  _______,  _______, _______, _______, _______, _______, _______, _______,          DT_PRNT,
      /*A*/   _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,  _______,  _______,  _______, _______, _______, _______, _______,          _______,          DT_UP,
      /*Z*/   _______,          KC_BTN4, KC_BTN3, KC_BTN5,  _______,  _______,  _______, _______, _______, _______, _______,          _______, _______, DT_DOWN,
      /*sp*/  _______, _______, _______,                              _______,                             _______, _______, _______, _______, _______, _______
   ),

   /* Workman-P Layout
      * Custom shift keys (are supposed to) invert the number row and brackets
      * Home row mods (GACS)
      * ,-------------------------------------------------------------------------------------------------------------.
      * | Esc  ||  F1  |  F2  |  F3  |  F4  ||  F5  |  F6  |  F7  |  F8  ||  F9  | F10  | F11  | F12  || Del  || Mute |
      * |=============================================================================================================|
      * |  ` ~ | ! 1  | @ 2  | # 3  | $ 4  | % 5  | ^ 6  | & 7  | * 8  | ( 9  | ) 0  | - _ | = +    | Backspc || Home |
      * |------+------+------+------+------+------+------+------+------+------+------+-----+--------+---------++------|
      * |   Tab   |  Q   |  D   |  R   |  W   |  B   |  J   |  F   |  U   |  P   | ; :  | { [  | } ]  |  \ |  || End  |
      * |---------+------+------+------+------+------+------+------+------+------+------+------+------+-------++------|
      * |  Capslock  |  A   |  S   |  H   |  T  |  G   |  Y   |  N   |  E   |  O   |  I   | ' "  |    Enter   || PgUp |
      * |------------+------+------+------+-----+------+------+------+------+------+------+------|----+========+------|
      * |    LShift    |  Z   |  X   |  M   |  C   |  V   |  K   |  L   | , <  | . >  | / ?  |  Fn2   ||  Up  || PgDn |
      * |--------------+------+------+------+------+------+------+------+------+------+------+--+=====++------++======|
      * |  Ctrl  |   Win  |  LAlt  |               Space                  | RAlt |  Fn  | Ctrl || Left | Down | Rght  |
      * `-------------------------------------------------------------------------------------------------------------'
      */

   [LAYER_WORKMAN] = LAYOUT(
      /*fn*/  KC_ESC,  KC_F1,   KC_F2,   KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,           KC_MUTE,
      /*num*/ KC_GRV,  KC_1,    KC_2,    KC_3,     KC_4,     KC_5,     KC_6,     KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_HOME,
      /*Q*/   KC_TAB,  KC_Q,    KC_D,    KC_R,     KC_W,     KC_B,     KC_J,     KC_F,    KC_U,    KC_P,    KC_SCLN, KC_LBRC, KC_RBRC, KC_BSLS,          KC_END,
      /*A*/   KC_CAPS, HM_A,    HM_S,    HM_H,     HM_T,     KC_G,     KC_Y,     HM_N,    HM_E,    HM_O,    HM_I,    KC_QUOT,          KC_ENT,           KC_PGUP,
      /*Z*/   KC_LSFT,          KC_Z,    KC_X,     KC_M,     KC_C,     KC_V,     KC_K,    KC_L,    KC_COMM, KC_DOT,  KC_SLSH,          MO_CODE, KC_UP,   KC_PGDN,
      /*sp*/  KC_LCTL, KC_LGUI, KC_LALT,                               KC_SPC,                              KC_RALT, MO_W_FN, TO_BASE, KC_LEFT, KC_DOWN, KC_RGHT
   ),
   [LAYER_WORKMAN_FN] = LAYOUT(
      /*fn*/  RESET,   KC_BRID, KC_BRIU, KC_TASK,  KC_FLXP,  KC_MPRV,  KC_MNXT,  KC_MPLY, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, _______, KC_INS,           _______,
      /*num*/ _______, _______, _______, _______,  _______,  _______,  _______,  _______, _______, _______, _______, _______, _______, _______,          KC_MAC1,
      /*Q*/   RGB_TOG, RGB_MOD, RGB_VAI, RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______, _______, _______, _______, _______, _______, RESET,            KC_MAC2,
      /*A*/   _______, RGB_M_P, RGB_M_B, RGB_M_R,  RGB_M_SW, RGB_M_SN, RGB_M_K,  RGB_M_X, RGB_M_G, RGB_M_T, _______, _______,          _______,          KC_MAC3,
      /*Z*/   _______,          _______, _______,  _______,  _______,  _______,  NK_TOGG, _______, _______, _______, _______,          MO_W_MS, KC_VOLU, KC_MAC4,
      /*sp*/  _______, KC_TASK, _______,                               KC_MPLY,                             _______, _______, _______, KC_MPRV, KC_VOLD, KC_MNXT
   ),
   [LAYER_WORKMAN_MOUSE] = LAYOUT(
      /*fn*/  _______, _______, _______, _______, _______,  _______,  _______,  _______, _______, _______, _______, _______, _______, _______,          _______,
      /*num*/ _______, _______, _______, _______, _______,  _______,  _______,  _______, _______, _______, _______, _______, _______, _______,          _______,
      /*Q*/   _______, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U,  _______,  _______,  _______, _______, _______, _______, _______, _______, _______,          DT_PRNT,
      /*A*/   _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,  _______,  _______,  _______, _______, _______, _______, _______,          _______,          DT_UP,
      /*Z*/   _______,          KC_BTN4, KC_BTN3, KC_BTN5,  _______,  _______,  _______, _______, _______, _______, _______,          _______, _______, DT_DOWN,
      /*sp*/  _______, _______, _______,                              _______,                             _______, _______, _______, _______, _______, _______
   ),

};
// clang-format on

#ifdef ENCODER_ENABLE 
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (get_mods() & MODS_ALT_MASK) {
        if (clockwise) {
            tap_code(KC_TAB);
        } else {
            tap_code16(S(KC_TAB));
        }
    } else if (get_mods() & MODS_CTRL_MASK) {
        if (clockwise) {
            tap_code(KC_TAB);
        } else {
            tap_code16(S(KC_TAB));
        }
    } else if(IS_LAYER_ON(LAYER_FN)) {
        if (clockwise) {
            tap_code(KC_MEDIA_NEXT_TRACK);
        } else {
            tap_code(KC_MEDIA_PREV_TRACK);
        }
    } else {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return true;
}
#endif // ENCODER_ENABLE

#ifdef RGB_MATRIX_ENABLE

#define RGB_CONFIRMATION_BLINKING_TIME 2000 // 2 seconds

/* Renaming those to make the purpose on this keymap clearer */
#define LED_FLAG_CAPS LED_FLAG_NONE
#define LED_FLAG_EFFECTS LED_FLAG_INDICATOR

static void set_rgb_caps_leds(void);

static uint16_t effect_started_time = 0;
static uint8_t r_effect = 0x0, g_effect = 0x0, b_effect = 0x0;
static void start_effects(void);

/* The higher this is, the slower the blinking will be */
#ifndef TIME_SELECTED_BIT
   #define TIME_SELECTED_BIT 8
#endif
#if TIME_SELECTED_BIT < 0 || TIME_SELECTED_BIT >= 16
   #error "TIME_SELECTED_BIT must be a positive integer smaller than 16"
#endif
#define effect_red() r_effect = 0xFF, g_effect = 0x0, b_effect = 0x0
#define effect_green() r_effect = 0x0, g_effect = 0xFF, b_effect = 0x0
#define effect_blue() r_effect = 0x0, g_effect = 0x0, b_effect = 0xFF
#define effect_white() r_effect = 0xFF, g_effect = 0xFF, b_effect = 0xFF

static uint8_t previous_effect_layer = 255;

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t current_layer = get_highest_layer(state);
    switch (current_layer) {
        case LAYER_BASE:
            if (previous_effect_layer != current_layer) {
                previous_effect_layer = current_layer;
                effect_blue();
                start_effects();
            }
            break;
        case LAYER_WORKMAN:
            if (previous_effect_layer != current_layer) {
                previous_effect_layer = current_layer;
                effect_white();
                start_effects();
            }
            break;
    }
    return state;
}

bool led_update_user(led_t led_state) {
    if (led_state.caps_lock) {
        if (!rgb_matrix_is_enabled()) {
            /* Turn ON the RGB Matrix for CAPS LOCK */
            rgb_matrix_set_flags(LED_FLAG_CAPS);
            rgb_matrix_enable();
        }
    } else if (rgb_matrix_get_flags() == LED_FLAG_CAPS) {
        /* RGB Matrix was only ON because of CAPS LOCK. Turn it OFF. */
        rgb_matrix_set_flags(LED_FLAG_ALL);
        rgb_matrix_disable();
    }
    return true;
}

#endif // RGB_MATRIX_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Just testing these out on the workman layer for now
    if (layer_state_is(LAYER_WORKMAN) && !process_custom_shift_keys(keycode, record)) { return false; }

    switch (keycode) {
        case KC_MACRO_1:
            register_code(KC_LCTL);
            tap_code(KC_A);
            tap_code(KC_C);
            unregister_code(KC_LCTL);
            //host_consumer_send(some_keycode);
            //return false;  // Skip all further processing of this key
            break;
        case KC_MACRO_2:
            // TODO
            break;
        case KC_MACRO_3:
            // TODO
            break;
        case KC_MACRO_4:
            // TODO
            break;
    #ifdef RGB_MATRIX_ENABLE
      #ifdef NKRO_ENABLE
      case NK_TOGG:
            if (record->event.pressed) {
               if (keymap_config.nkro) {
                  /* Turning NKRO OFF */
                  effect_red();
               } else {
                  /* Turning NKRO ON */
                  effect_green();
               }
               start_effects();
            }
            break;
      #endif // NKRO_ENABLE
        case RGB_MOD:
        case RGB_RMOD:
        case RGB_HUI:
        case RGB_HUD:
        case RGB_SAI:
        case RGB_SAD:
        case RGB_VAI:
        case RGB_VAD:
        case RGB_SPI:
        case RGB_SPD:
            if (record->event.pressed) {
                if (rgb_matrix_get_flags() != LED_FLAG_ALL) {
                    /* Ignore changes to RGB settings while only it's supposed to be OFF */
                    return false;  // Skip all further processing of this key
                }
            }
            break;
        case RGB_TOG:
            if (record->event.pressed) {
                if (rgb_matrix_is_enabled()) {
                    switch (rgb_matrix_get_flags()) {
                        case LED_FLAG_EFFECTS:
                        case LED_FLAG_CAPS:
                            /* Turned ON because of EFFECTS or CAPS, is actually OFF */
                            /* Change to LED_FLAG_ALL to signal it's really ON */
                            rgb_matrix_set_flags(LED_FLAG_ALL);
                            /* Will be re-enabled by the processing of the toggle */
                            rgb_matrix_disable_noeeprom();
                            break;
                        case LED_FLAG_ALL:
                            /* Is actually ON */
                            if (effect_started_time > 0) {
                                /* Signal EFFECTS */
                                rgb_matrix_set_flags(LED_FLAG_EFFECTS);
                                /* Will be re-enabled by the processing of the toggle */
                                rgb_matrix_disable_noeeprom();
                            } else
                            if (host_keyboard_led_state().caps_lock) {
                                /* Signal CAPS */
                                rgb_matrix_set_flags(LED_FLAG_CAPS);
                                /* Will be re-enabled by the processing of the toggle */
                                rgb_matrix_disable_noeeprom();
                            }
                            break;
                    }
                }
            }
            break;
    #endif // RGB_MATRIX_ENABLE
    }
    return true;
}

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_user(void) {
    if (effect_started_time > 0) {
        /* Render blinking EFFECTS */
        const uint16_t deltaTime = sync_timer_elapsed(effect_started_time);
        if (deltaTime <= RGB_CONFIRMATION_BLINKING_TIME) {
            const uint8_t led_state = ((~deltaTime) >> TIME_SELECTED_BIT) & 0x01;
            const uint8_t val_r = led_state * r_effect;
            const uint8_t val_g = led_state * g_effect;
            const uint8_t val_b = led_state * b_effect;
            rgb_matrix_set_color_all(val_r, val_g, val_b);
            if (host_keyboard_led_state().caps_lock) {
                set_rgb_caps_leds();
            }
            return false;
        } else {
            /* EFFECTS duration is finished */
            effect_started_time = 0;
            if (rgb_matrix_get_flags() == LED_FLAG_EFFECTS) {
                /* It was turned ON because of EFFECTS */
                if (host_keyboard_led_state().caps_lock) {
                    /* CAPS is still ON. Demote to CAPS */
                    rgb_matrix_set_flags(LED_FLAG_CAPS);
                } else {
                    /* There is nothing else keeping RGB enabled. Reset flags and turn if off. */
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_disable_noeeprom();
                }
            }
        }
    }
    if (rgb_matrix_get_flags() == LED_FLAG_CAPS) {
        rgb_matrix_set_color_all(0x0, 0x0, 0x0);
    }
    if (host_keyboard_led_state().caps_lock) {
        set_rgb_caps_leds();
    }

    return false;
}

static void start_effects(void) {
    effect_started_time = sync_timer_read();
    if (!rgb_matrix_is_enabled()) {
        /* Turn it ON, signal the cause (EFFECTS) */
        rgb_matrix_set_flags(LED_FLAG_EFFECTS);
        rgb_matrix_enable_noeeprom();
    } else if (rgb_matrix_get_flags() == LED_FLAG_CAPS) {
        /* It's already ON, promote the cause from CAPS to EFFECTS */
        rgb_matrix_set_flags(LED_FLAG_EFFECTS);
    }
}

// RGB led number layout, function of the key

//  67, led 01   0, ESC    6, F1      12, F2      18, F3   23, F4   28, F5      34, F6   39, F7   44, F8      50, F9   56, F10   61, F11    66, F12    69, Prt       Rotary(Mute)   68, led 12
//  70, led 02   1, ~      7, 1       13, 2       19, 3    24, 4    29, 5       35, 6    40, 7    45, 8       51, 9    57, 0     62, -_     78, (=+)   85, BackSpc   72, Home       71, led 13
//  73, led 03   2, Tab    8, Q       14, W       20. E    25, R    30, T       36, Y    41, U    46, I       52, O    58, P     63, [{     89, ]}     93, \|        75, PgUp       74, led 14
//  76, led 04   3, Caps   9, A       15, S       21, D    26, F    31, G       37, H    42, J    47, K       53, L    59, ;:    64, '"                96, Enter     86, PgDn       77, led 15
//  80, led 05   4, Sh_L   10, Z      16, X       22, C    27, V    32, B       38, N    43, M    48, ,<      54, .<   60, /?               90, Sh_R   94, Up        82, End        81, led 16
//  83, led 06   5, Ct_L   11,Win_L   17, Alt_L                     33, SPACE                     49, Alt_R   55, FN             65, Ct_R   95, Left   97, Down      79, Right      84, led 17
//  87, led 07                                                                                                                                                                      88, led 18
//  91, led 08                                                                                                                                                                      92, led 19

static void set_rgb_caps_leds() {
    rgb_matrix_set_color(67, 0xFF, 0x0, 0x0); // Left side LED 1
    rgb_matrix_set_color(68, 0xFF, 0x0, 0x0); // Right side LED 1
    rgb_matrix_set_color(70, 0xFF, 0x0, 0x0); // Left side LED 2
    rgb_matrix_set_color(71, 0xFF, 0x0, 0x0); // Right side LED 2
    rgb_matrix_set_color(73, 0xFF, 0x0, 0x0); // Left side LED 3
    rgb_matrix_set_color(74, 0xFF, 0x0, 0x0); // Right side LED 3
    rgb_matrix_set_color(76, 0xFF, 0x0, 0x0); // Left side LED 4
    rgb_matrix_set_color(77, 0xFF, 0x0, 0x0); // Right side LED 4
    rgb_matrix_set_color(80, 0xFF, 0x0, 0x0); // Left side LED 5
    rgb_matrix_set_color(81, 0xFF, 0x0, 0x0); // Right side LED 5
    rgb_matrix_set_color(83, 0xFF, 0x0, 0x0); // Left side LED 6
    rgb_matrix_set_color(84, 0xFF, 0x0, 0x0); // Right side LED 6
    rgb_matrix_set_color(87, 0xFF, 0x0, 0x0); // Left side LED 7
    rgb_matrix_set_color(88, 0xFF, 0x0, 0x0); // Right side LED 7
    rgb_matrix_set_color(91, 0xFF, 0x0, 0x0); // Left side LED 8
    rgb_matrix_set_color(92, 0xFF, 0x0, 0x0); // Right side LED 8
    rgb_matrix_set_color(3, 0xFF, 0x0, 0x0); // CAPS LED
}

#endif // RGB_MATRIX_ENABLE
