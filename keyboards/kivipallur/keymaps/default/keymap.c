#include QMK_KEYBOARD_H
#include "quantum.h"

#include "swapper.h"
#include "oneshot.h"

#define MO_NAV MO(_NAV)
#define TG_NAV TG(_NAV)
#define MO_FN MO(_FN)
#define MO_EST MO(_EST)
#define MO_SYMNM MO(_SYMNUM)

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
    _SYMNUM,
    _EST,
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum {
    TD_LYR,
    TD_CAPS,
};

// Function associated with all tap dances
td_state_t cur_dance(tap_dance_state_t *state);

// Functions associated with individual tap dances
void ql_finished(tap_dance_state_t *state, void *user_data);
void ql_reset(tap_dance_state_t *state, void *user_data);


enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_GUI,

    SW_WIN,  // Switch to next window         (alt-tab)
    SW_LANG, // Switch to next input language (gui-spc)KC_SCLN

    MO_SCRL,
};

const key_override_t comma_semicolon_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_SCLN);
const key_override_t dot_colon_override = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_COLN);
const key_override_t slsh_bslsh_override = ko_make_basic(MOD_MASK_SHIFT, KC_SLSH, KC_BSLS);
const key_override_t quest_exclm_override = ko_make_basic(MOD_MASK_SHIFT, KC_QUES, KC_EXLM);
const key_override_t parenthesis_override = ko_make_basic(MOD_MASK_SHIFT, KC_LEFT_PAREN, KC_RIGHT_PAREN);
const key_override_t curly_brace_override = ko_make_basic(MOD_MASK_SHIFT, KC_LEFT_CURLY_BRACE, KC_RIGHT_CURLY_BRACE);
const key_override_t bracket_override = ko_make_basic(MOD_MASK_SHIFT, KC_LEFT_BRACKET, KC_RIGHT_BRACKET);
const key_override_t angle_bracket_override = ko_make_basic(MOD_MASK_SHIFT, KC_LEFT_ANGLE_BRACKET, KC_RIGHT_ANGLE_BRACKET);

const key_override_t n1_f01_override = ko_make_basic(MOD_MASK_SHIFT, KC_1, KC_F1);
const key_override_t n2_f02_override = ko_make_basic(MOD_MASK_SHIFT, KC_2, KC_F2);
const key_override_t n3_f03_override = ko_make_basic(MOD_MASK_SHIFT, KC_3, KC_F3);
const key_override_t n4_f04_override = ko_make_basic(MOD_MASK_SHIFT, KC_4, KC_F4);
const key_override_t n5_f05_override = ko_make_basic(MOD_MASK_SHIFT, KC_5, KC_F5);
const key_override_t n6_f06_override = ko_make_basic(MOD_MASK_SHIFT, KC_6, KC_F6);
const key_override_t n7_f07_override = ko_make_basic(MOD_MASK_SHIFT, KC_7, KC_F7);
const key_override_t n8_f08_override = ko_make_basic(MOD_MASK_SHIFT, KC_8, KC_F8);
const key_override_t n9_f09_override = ko_make_basic(MOD_MASK_SHIFT, KC_9, KC_F9);
const key_override_t n0_f10_override = ko_make_basic(MOD_MASK_SHIFT, KC_0, KC_F10);
const key_override_t ampr_f11_override = ko_make_basic(MOD_MASK_SHIFT, KC_AMPR, KC_F11);
const key_override_t astr_f12_override = ko_make_basic(MOD_MASK_SHIFT, KC_ASTR, KC_F12);

const key_override_t *key_overrides[] = {
	&comma_semicolon_override,
    &dot_colon_override,
    &slsh_bslsh_override,
    &quest_exclm_override,
    &parenthesis_override,
    &curly_brace_override,
    &bracket_override,
    &angle_bracket_override,
};

// TODO layer tap ESC to _EST
// TAP dance num layer?

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_ALPHA] = LAYOUT_split_3x6_3(
        KC_TAB,     KC_Q,       KC_W,       KC_F,       KC_P,       KC_B,           KC_J,       KC_L,       KC_U,       KC_Y,       KC_QUOT,    KC_MINS,
	                KC_A,       KC_R,       KC_S,       KC_T,       KC_G,           KC_M,       KC_N,       KC_E,       KC_I,       KC_O,
        KC_ESC,     KC_Z,       KC_X,       KC_C,       KC_D,       KC_V,           KC_K,       KC_H,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_QUES,
                                                        TD(TD_LYR), KC_LSFT,        XXXXXXX,    KC_SPC
    ),
    [_NAV] = LAYOUT_split_3x6_3(
        XXXXXXX,    SW_WIN,     PG_LEFT,    PG_RGHT,    BACK,       FWD,            KC_PGUP,    KC_HOME,    KC_UP,      KC_END,     XXXXXXX,    XXXXXXX,
                    OS_GUI,     OS_ALT,     OS_SHFT,    OS_CTRL,    KC_LGUI,        KC_DEL,     KC_LEFT,    KC_DOWN,    KC_RGHT,    KC_BSPC,
        MO_EST,     UNDO,       REDO,       CUT,        COPY,       PASTE,          KC_PGDN,    MS_BTN1,    MS_BTN2,    MO_SCRL,    KC_DEL,     SAVE,
                                                        _______,    XXXXXXX,        XXXXXXX,     KC_ENT
    ),
// tekita shift overrided sulgudele ja fn layeri jaoks nritele ka (f10,11,12 lahenda 2ra)
    [_SYMNUM] = LAYOUT_split_3x6_3(
        KC_TILD,    KC_LABK,    KC_LBRC,    KC_LCBR,    KC_LPRN,    KC_HASH,        KC_AMPR,    KC_7,       KC_8,        KC_9,       XXXXXXX,    KC_AT,
                    OS_GUI,     OS_ALT,     OS_SHFT,    OS_CTRL,    KC_EQL,         KC_0,       KC_4,       KC_5,        KC_6,       KC_BSPC,
        XXXXXXX,    KC_CIRC,    KC_PERC,    KC_PIPE,    KC_GRV,     KC_PLUS,        KC_ASTR,    KC_1,       KC_2,        KC_3,       KC_DLR,     XXXXXXX,
                                                        _______,    XXXXXXX,        XXXXXXX,    XXXXXXX
    ),
    [_EST] = LAYOUT_split_3x6_3(
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
	                XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    EST_A,      EST_O_2,    EST_U,      KC_BSPC,
        _______,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    EST_O_1,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
                                                        _______,    XXXXXXX,        XXXXXXX,    XXXXXXX
    ),
};
// clang-format on

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
        case MO_NAV:
        case OS_GUI:
        case OS_ALT:
        case OS_SHFT:
        case OS_CTRL:
            return true;
        default:
            return false;
    }
}

bool set_scrolling = false;
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

    if (keycode == MO_SCRL) {
        set_scrolling = !set_scrolling;
    }

    return true;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (set_scrolling) {
        mouse_report.h = 0;
        mouse_report.v = mouse_report.y;
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}

// Determine the current tap dance state
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        if (!state->pressed) return TD_DOUBLE_TAP;
        else return TD_DOUBLE_HOLD;
    }
    else return TD_UNKNOWN;
}

// Initialize tap structure associated with example tap dance key
static td_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void ql_finished(tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_HOLD:
            layer_on(_NAV);
            break;
        case TD_DOUBLE_HOLD:
            layer_on(_SYMNUM);
            break;
        default:
            break;
    }
}

void ql_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(_NAV);
    }
    if (ql_tap_state.state == TD_DOUBLE_HOLD) {
        layer_off(_SYMNUM);
    }
    ql_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
tap_dance_action_t tap_dance_actions[] = {
    [TD_LYR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ql_finished, ql_reset)
};

// Set a long-ish tapping term for tap-dance keys
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            return 275;
        default:
            return TAPPING_TERM;
    }
}
