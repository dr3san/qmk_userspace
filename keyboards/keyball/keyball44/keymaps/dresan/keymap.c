#include QMK_KEYBOARD_H
#include "quantum.h"

#include "lib/oledkit/oledkit.h"

#include "swapper.h"
#include "oneshot.h"

#include "keycodes.h"

#define MO_SYM MO(_SYM)
#define MO_NAV MO(_NAV)
#define TG_NAV TG(_NAV)
#define MO_NUM MO(_NUM)
#define MO_FN MO(_FN)
#define MO_EST MO(_EST)

#define BACK A(KC_LEFT)
#define FWD A(KC_RGHT)
#define PG_LEFT C(KC_PGUP)
#define PG_RGHT C(KC_PGDN)

#define UNDO C(KC_Z)
#define REDO C(KC_Y)
#define CUT C(KC_X)
#define COPY C(KC_C)
#define SAVE C(KC_S)
#define PASTE C(KC_V)

#define EST_O_1 UP(EST_O_1_LOWER, EST_O_1_UPPER) // o with tilde
#define EST_A UP(EST_A_LOWER, EST_A_UPPER)   // a with diaeresis
#define EST_O_2 UP(EST_O_2_LOWER, EST_O_2_UPPER) // o with diaeresis
#define EST_U UP(EST_U_LOWER, EST_U_UPPER)   // u with diaeresis

enum unicode_names {
  EST_O_1_LOWER,
  EST_O_1_UPPER,
  EST_A_LOWER,
  EST_A_UPPER,
  EST_O_2_LOWER,
  EST_O_2_UPPER,
  EST_U_LOWER,
  EST_U_UPPER,
};

const uint32_t unicode_map[] PROGMEM = {
  [EST_O_1_LOWER] = 0x00F5,
  [EST_O_1_UPPER] = 0x00D5,
  [EST_A_LOWER] = 0x00E4,
  [EST_A_UPPER] = 0x00C4,
  [EST_O_2_LOWER] = 0x00F6,
  [EST_O_2_UPPER] = 0x00D6,
  [EST_U_LOWER] = 0x00FC,
  [EST_U_UPPER] = 0x00DC,
};

enum layers {
    _ALPHA = 0,
    _NAV,
    _SYM,
    _NUM,
    _FN,
    _EST,
};

enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_GUI,

    SW_WIN,  // Switch to next window         (alt-tab)
    SW_LANG, // Switch to next input language (gui-spc)
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_ALPHA] = LAYOUT_right_ball(
        KC_ESC,     KC_Q,       KC_W,       KC_F,       KC_P,       KC_B,           KC_J,       KC_L,       KC_U,       KC_Y,       KC_QUOT,    CW_TOGG,
	    KC_TAB,     KC_A,       KC_R,       KC_S,       KC_T,       KC_G,           KC_M,       KC_N,       KC_E,       KC_I,       KC_O,       KC_MINS,
        MO_EST,     KC_Z,       KC_X,       KC_C,       KC_D,       KC_V,           KC_K,       KC_H,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_SCLN,
                    XXXXXXX,    MO_FN,      MO_NAV,     KC_LSFT,    MO_NUM,         MO_SYM,     KC_SPC,                             TG_NAV
    ),

    [_NAV] = LAYOUT_right_ball(
        _______,    XXXXXXX,    PG_LEFT,    PG_RGHT,    BACK,       FWD,            KC_PGUP,    KC_HOME,    KC_UP,      KC_END,     XXXXXXX,    XXXXXXX,
        _______,    OS_GUI,     OS_ALT,     OS_SHFT,    OS_CTRL,    KC_LGUI,        KC_PGDN,    KC_LEFT,    KC_DOWN,    KC_RGHT,    KC_BSPC,    XXXXXXX,
        SAVE,       UNDO,       REDO,       CUT,        COPY,       PASTE,          SW_WIN,     KC_MS_BTN1, KC_MS_BTN2, SCRL_MO,    KC_DEL,     XXXXXXX,
                    XXXXXXX,    _______,    _______,    _______,    _______,        _______,    KC_ENT,                             TG_NAV
    ),

    [_SYM] = LAYOUT_right_ball(
        _______,    XXXXXXX,    KC_CIRC,    KC_DLR,     KC_HASH,    KC_PERC,        KC_EQL,     XXXXXXX,    XXXXXXX,     XXXXXXX,    KC_PLUS,    XXXXXXX,
        _______,    KC_LABK,    KC_LBRC,    KC_LCBR,    KC_LPRN,    KC_PIPE,        XXXXXXX,    KC_GRV,     KC_BSLS,     KC_AT,      KC_BSPC,    KC_MINS,
        XXXXXXX,    KC_RABK,    KC_RBRC,    KC_RCBR,    KC_RPRN,    KC_TILD,        KC_ASTR,    KC_AMPR,    KC_EXLM,     KC_QUES,    KC_SLSH,    XXXXXXX,
                    XXXXXXX,    _______,    XXXXXXX,    _______,    _______,        _______,    XXXXXXX,                             XXXXXXX
    ),

    [_NUM] = LAYOUT_right_ball(
        _______,    KC_PSCR,    KC_MPRV,    KC_MNXT,    KC_MPLY,    KC_VOLU,        KC_EQL,     KC_7,       KC_8,        KC_9,       KC_PLUS,    XXXXXXX,
        _______,    OS_GUI,     OS_ALT,     OS_SHFT,    OS_CTRL,    KC_VOLD,        KC_0,       KC_4,       KC_5,        KC_6,       KC_BSPC,    KC_MINS,
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        KC_ASTR,    KC_1,       KC_2,        KC_3,       KC_SLSH,    XXXXXXX,
                    XXXXXXX,    _______,    XXXXXXX,    _______,    _______,        XXXXXXX,    XXXXXXX,                             XXXXXXX
    ),

    [_FN] = LAYOUT_right_ball(
        _______,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        KC_F10,     KC_F7,      KC_F8,      KC_F9,       XXXXXXX,     XXXXXXX,
        _______,    OS_GUI,     OS_ALT,     OS_SHFT,    OS_CTRL,    XXXXXXX,        KC_F11,     KC_F4,      KC_F5,      KC_F6,       XXXXXXX,     XXXXXXX,
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        KC_F12,     KC_F1,      KC_F2,      KC_F3,       XXXXXXX,     XXXXXXX,
                    XXXXXXX,    _______,    XXXXXXX,    _______,    XXXXXXX,        XXXXXXX,    XXXXXXX,                             XXXXXXX
    ),

    [_EST] = LAYOUT_right_ball(
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
	    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    EST_A,      EST_O_2,    EST_U,      KC_BSPC,    XXXXXXX,
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    EST_O_1,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
                    XXXXXXX,    XXXXXXX,    XXXXXXX,    _______,    XXXXXXX,        XXXXXXX,    XXXXXXX,                            XXXXXXX
    ),


};
// clang-format on

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
        case KC_ESC:
        case KC_LSFT:
            return true;
        default:
            return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
        case MO_SYM:
        case MO_NAV:
        case MO_NUM:
        case OS_GUI:
        case OS_ALT:
        case OS_SHFT:
        case OS_CTRL:
            return true;
        default:
            return false;
    }
}

bool sw_win_active  = false;
bool sw_lang_active = false;

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state  = os_up_unqueued;
oneshot_state os_gui_state  = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_swapper(&sw_win_active, KC_LALT, KC_TAB, SW_WIN, keycode, record);
    update_swapper(&sw_lang_active, KC_LGUI, KC_SPC, SW_LANG, keycode, record);

    update_oneshot(&os_shft_state, KC_LSFT, OS_SHFT, keycode, record);
    update_oneshot(&os_ctrl_state, KC_LCTL, OS_CTRL, keycode, record);
    update_oneshot(&os_alt_state, KC_LALT, OS_ALT, keycode, record);
    update_oneshot(&os_gui_state, KC_LGUI, OS_GUI, keycode, record);

    return true;
}
