#pragma once
#define VIAL_KEYBOARD_UID {0x7C, 0x18, 0xF1, 0xD7, 0x4E, 0x1B, 0xA2, 0xE2}

#define DYNAMIC_KEYMAP_LAYER_COUNT 5

#define VIAL_UNLOCK_COMBO_ROWS {0, 0}
#define VIAL_UNLOCK_COMBO_COLS {0, 1}

//rp2040ボードで起動時にコールドスタックする事象に対する対応
#define SPLIT_USB_TIMEOUT 5000 // default 2000
#define SPLIT_USB_TIMEOUT_POLL 25 // default 10
#define USB_SUSPEND_WAKEUP_DELAY 2000 // default 0