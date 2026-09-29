// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "lib/pmw3610/pmw3610.h"
#include "pointing_device.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
                 KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
                 KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                          KC_H,    KC_J,    KC_K,    KC_L,    KC_SLSH, KC_ENT,
                 KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                          KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_TRNS,
                 KC_LCTL, KC_LGUI, KC_LALT, KC_TRNS, KC_DEL,  KC_SPC,                                        KC_TRNS, KC_MINS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [1] = LAYOUT(
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [2] = LAYOUT(
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [3] = LAYOUT(
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

};

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    // X/Y を入れ替える
    int8_t tmp = mouse_report.x;
    mouse_report.x = mouse_report.y;
    mouse_report.y = tmp;

    static int16_t h_accum = 0;
    static int16_t v_accum = 0;

    // レイヤー1,2,3 → スクロール
    if (layer_state_is(1) || layer_state_is(2) || layer_state_is(3)) {

        // 入れ替え後の軸をそのまま蓄積
        h_accum += mouse_report.x;
        v_accum += mouse_report.y;

        mouse_report.h = h_accum / 10;
        mouse_report.v = -v_accum / 10;

        h_accum %= 10;
        v_accum %= 10;

        mouse_report.x = 0;
        mouse_report.y = 0;
    } else {
        // レイヤー0 → カーソル速度 1.25 倍
        // mouse_report.x = mouse_report.x * 5 / 4;
        // mouse_report.y = mouse_report.y * 5 / 4;
        
        // 通常カーソル時は蓄積をリセット
        h_accum = 0;
        v_accum = 0;
    }

    return mouse_report;
}