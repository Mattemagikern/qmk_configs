#include QMK_KEYBOARD_H
#ifdef AUDIO_ENABLE
        #include "muse.h"
#endif
#include "eeprom.h" /* What does this do? */
#include "keymap_swedish.h"

enum planck_keycodes {
        RGB_SLD = EZ_SAFE_RANGE,
};

enum planck_layers {
        _BASE,
        _LOWER,
        _RAISE,
        _ADJUST,
};

#define ______ KC_TRANSPARENT
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        /* ~Svdvorak
          ,-------------------------------------------------------------------------------------.
          | Tab    |   Å  |   .  |   ,  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
          |------+------+------+------+------+------+------+------+------+------+------+--------|
          | Ctrl   |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  -   |
          |------+------+------+------+------+------+------+------+------+------+------+--------|
          | Shift/Ö|   Ä  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
          |------+------+------+------+------+------+------+------+------+------+------+--------|
          | Esc    |      |      | Alt  |Lower |    Space    |Raise |   '  | Down |  Up  |      |
          `-------------------------------------------------------------------------------------'
         */
        [_BASE] = LAYOUT_planck_grid(
                KC_TAB          , SE_AA  , KC_COMMA , KC_DOT  , KC_P  , KC_Y     , KC_F     , KC_G  , KC_C    , KC_R  , KC_L    , KC_BSPACE ,
                KC_LCTRL        , KC_A   , KC_O     , KC_E    , KC_U  , KC_I     , KC_D     , KC_H  , KC_T    , KC_N  , KC_S    , SE_MINS   ,
                LSFT_T(SE_OSLH) , SE_AE  , KC_Q     , KC_J    , KC_K  , KC_X     , KC_B     , KC_M  , KC_W    , KC_V  , KC_Z    , KC_ENTER  ,
                KC_ESCAPE       , ______ , ______   , KC_LALT , LOWER , KC_SPACE , KC_SPACE , RAISE , SE_APOS , KC_UP , KC_DOWN , ______
                ),

        [_LOWER] = LAYOUT_planck_grid(
                ______ , ______ , SE_SCLN , SE_COLN , ______  , ______ , ______  , ______     , ______ , ______  , ______  , ______  ,
                ______ , ______ , SE_QUO2 , KC_HASH , KC_PERC , SE_EQL , SE_PLUS , SE_DLR_MAC , SE_AT  , SE_APOS , SE_ACUT , SE_BSLS ,
                ______ , ______ , ______  , ______  , ______  , ______ , ______  , ______     , ______ , ______  , ______  , ______  ,
                ______ , ______ , ______  , ______  , ______  , ______ , ______  , ______     , ______ , ______  , ______  , ______) ,

        [_RAISE] = LAYOUT_planck_grid(
                ______  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_BSPACE ,
                SE_ASTR , KC_EXLM , SE_LCBR , SE_RCBR , SE_PIPE , SE_LPRN , SE_RPRN , SE_AMPR , SE_LBRC , SE_RBRC , SE_QUES , SE_SLSH   ,
                ______  , ______  , ______  , ______  , SE_CIRC , SE_LESS , SE_GRTR , SE_TILD , ______  , ______  , ______  , ______    ,
                ______  , ______  , ______  , ______  , ______  , ______  , _______ , ______  , ______  , ______  , ______  , ______
                ),

        [_ADJUST] = LAYOUT_planck_grid(
                ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ ,
                ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ ,
                ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ ,
                ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ ,
                ),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
        (void)keycode;
        (void)recrod;
        return true;
}

#ifdef AUDIO_ENABLE
bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise)
{
        if (muse_mode) {
                if (IS_LAYER_ON(_RAISE)) {
                        if (clockwise) {
                                muse_offset++;
                        } else {
                                muse_offset--;
                        }
                } else {
                        if (clockwise) {
                                muse_tempo += 1;
                        } else {
                                muse_tempo -= 1;
                        }
                }
        } else {
                if (clockwise) {
                        #ifdef MOUSEKEY_ENABLE
                        register_code(KC_MS_WH_DOWN);
                        unregister_code(KC_MS_WH_DOWN);
                        #else
                        register_code(KC_PGDN);
                        unregister_code(KC_PGDN);
                        #endif
                } else {
                        #ifdef MOUSEKEY_ENABLE
                        register_code(KC_MS_WH_UP);
                        unregister_code(KC_MS_WH_UP);
                        #else
                        register_code(KC_PGUP);
                        unregister_code(KC_PGUP);
                        #endif
                }
        }
}

void matrix_scan_user(void) {}

bool music_mask_user(uint16_t keycode)
{
        if (keycode == RAISE || keycode == LOWER) {
                return false;
        }
        return true;
}
#endif

uint32_t layer_state_set_user(uint32_t state)
{
        return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
