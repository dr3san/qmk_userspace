#include QMK_KEYBOARD_H
#include "swapper.h"
#include "oneshot.h"
#include "maccel.h"

// === BEGIN KEYMAP MACROS ===
#define MO_NAV TL_LOWR
#define MO_SYM TL_UPPR

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
// === END KEYMAP MACROS ===

enum layers {
    _ALPHA = 0,
    _NAV,
    _SYM,
    _NUM,
};

bool set_scrolling = false;

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state  = os_up_unqueued;
oneshot_state os_gui_state  = os_up_unqueued;

enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_GUI,
    SW_WIN,  // Switch to next window         (alt-tab)
    MO_SCRL, // Toggle drag scrolling
};

// === BEGIN UNICODE ===
#define EST_O_1 UP(EST_O_1_LOWER, EST_O_1_UPPER) // o with tilde (õ)
#define EST_A UP(EST_A_LOWER, EST_A_UPPER)       // a with diaeresis (ä)
#define EST_O_2 UP(EST_O_2_LOWER, EST_O_2_UPPER) // o with diaeresis (ö)
#define EST_U UP(EST_U_LOWER, EST_U_UPPER)       // u with diaeresis (ü)

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
    [EST_O_1_LOWER] = 0x00F5, [EST_O_1_UPPER] = 0x00D5, [EST_A_LOWER] = 0x00E4,
    [EST_A_UPPER] = 0x00C4,   [EST_O_2_LOWER] = 0x00F6, [EST_O_2_UPPER] = 0x00D6,
    [EST_U_LOWER] = 0x00FC,   [EST_U_UPPER] = 0x00DC,
};
// === END UNICODE ===

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_ALPHA] = LAYOUT_split_3x6_3(
        KC_TAB,     KC_Q,       KC_W,       KC_F,       KC_P,       KC_B,           KC_J,       KC_L,       KC_U,       KC_Y,       KC_QUOT,    KC_MINS,
	                KC_A,       KC_R,       KC_S,       KC_T,       KC_G,           KC_M,       KC_N,       KC_E,       KC_I,       KC_O,
        KC_ESC,     KC_Z,       KC_X,       KC_C,       KC_D,       KC_V,           KC_K,       KC_H,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_QUES,
                                                        TL_LOWR,     KC_LSFT,       TL_UPPR,     KC_SPC
    ),
    [_NAV] = LAYOUT_split_3x6_3(
        KC_TAB,     XXXXXXX,    PG_LEFT,    PG_RGHT,    BACK,       FWD,            KC_PGUP,    KC_HOME,    KC_UP,      KC_END,     XXXXXXX,    XXXXXXX,
                    OS_GUI,     OS_ALT,     OS_SHFT,    OS_CTRL,    KC_LGUI,        KC_PGDN,    KC_LEFT,    KC_DOWN,    KC_RGHT,    KC_BSPC,
        SAVE,       UNDO,       REDO,       CUT,        COPY,       PASTE,          SW_WIN,     MS_BTN1,    MS_BTN2,    MO_SCRL,    KC_DEL,     XXXXXXX,
                                                        _______,    XXXXXXX,        _______,    KC_ENT
    ),
    [_SYM] = LAYOUT_split_3x6_3(
        KC_TILD,    KC_CIRC,    KC_DLR,     KC_PERC,    KC_HASH,    KC_AMPR,        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
	                KC_LABK,    KC_LBRC,    KC_LCBR,    KC_LPRN,    KC_EQL,         KC_PIPE,    EST_A,      EST_O_2,    EST_U,      KC_BSPC,
        KC_PLUS,    KC_RABK,    KC_RBRC,    KC_RCBR,    KC_RPRN,    KC_ASTR,        KC_GRV,     EST_O_1,    KC_AT,      XXXXXXX,    XXXXXXX,    XXXXXXX,
                                                        _______,    KC_LSFT,        _______,    XXXXXXX
    ),
    [_NUM] = LAYOUT_split_3x6_3(
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    KC_7,       KC_8,        KC_9,       XXXXXXX,    KC_F11,
                    OS_GUI,     OS_ALT,     OS_SHFT,    OS_CTRL,    KC_EQL,         KC_0,       KC_4,       KC_5,        KC_6,       KC_BSPC,
        XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    KC_1,       KC_2,        KC_3,       XXXXXXX,    KC_F12,
                                                        _______,    XXXXXXX,        _______,    XXXXXXX
    ),
};
// clang-format on

// === BEGIN ONESHOT ===
bool sw_win_active = false;

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
        case OS_GUI:
        case OS_ALT:
        case OS_SHFT:
        case OS_CTRL:
        case MO_NAV:
        case MO_SYM:
            return true;
        default:
            return false;
    }
}
// === END ONESHOT ===

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_swapper(&sw_win_active, KC_LALT, KC_TAB, SW_WIN, keycode, record);

    update_oneshot(&os_shft_state, KC_LSFT, OS_SHFT, keycode, record);
    update_oneshot(&os_ctrl_state, KC_LCTL, OS_CTRL, keycode, record);
    update_oneshot(&os_alt_state, KC_LALT, OS_ALT, keycode, record);
    update_oneshot(&os_gui_state, KC_LGUI, OS_GUI, keycode, record);

    if (keycode == MO_SCRL) {
        set_scrolling = record->event.pressed;
    }

    return true;
}

// === BEGIN MOUSE ===
float scroll_accumulated = 0;

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (set_scrolling) {
        scroll_accumulated += (float)mouse_report.y / 24.0;
        mouse_report.v = (int8_t)scroll_accumulated;
        scroll_accumulated -= (int8_t)scroll_accumulated;

        mouse_report.h = 0;
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return pointing_device_task_maccel(mouse_report);
}
// === END MOUSE ===

// === BEGIN KEY OVERRIDES ===
const key_override_t comma_semicolon_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_SCLN);
const key_override_t dot_colon_override       = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_COLN);
const key_override_t slsh_bslsh_override      = ko_make_basic(MOD_MASK_SHIFT, KC_SLSH, KC_BSLS);
const key_override_t quest_exclm_override     = ko_make_basic(MOD_MASK_SHIFT, KC_QUES, KC_EXLM);
const key_override_t n1_f01_override          = ko_make_basic(MOD_MASK_SHIFT, KC_1, KC_F1);
const key_override_t n2_f02_override          = ko_make_basic(MOD_MASK_SHIFT, KC_2, KC_F2);
const key_override_t n3_f03_override          = ko_make_basic(MOD_MASK_SHIFT, KC_3, KC_F3);
const key_override_t n4_f04_override          = ko_make_basic(MOD_MASK_SHIFT, KC_4, KC_F4);
const key_override_t n5_f05_override          = ko_make_basic(MOD_MASK_SHIFT, KC_5, KC_F5);
const key_override_t n6_f06_override          = ko_make_basic(MOD_MASK_SHIFT, KC_6, KC_F6);
const key_override_t n7_f07_override          = ko_make_basic(MOD_MASK_SHIFT, KC_7, KC_F7);
const key_override_t n8_f08_override          = ko_make_basic(MOD_MASK_SHIFT, KC_8, KC_F8);
const key_override_t n9_f09_override          = ko_make_basic(MOD_MASK_SHIFT, KC_9, KC_F9);
const key_override_t n0_f10_override          = ko_make_basic(MOD_MASK_SHIFT, KC_0, KC_F10);

const key_override_t *key_overrides[] = {
    &comma_semicolon_override, &dot_colon_override, &slsh_bslsh_override, &quest_exclm_override,
    &n1_f01_override,          &n2_f02_override,    &n3_f03_override,     &n4_f04_override,
    &n5_f05_override,          &n6_f06_override,    &n7_f07_override,     &n8_f08_override,
    &n9_f09_override,          &n0_f10_override,
};
// === END KEY OVERRIDES ===

// === BEGIN COMBOS ===
const uint16_t PROGMEM mouse_combo[] = {MS_BTN1, MS_BTN2, COMBO_END};

combo_t key_combos[] = {
    COMBO(mouse_combo, MS_BTN3),
};
// === END COMBOS ===
