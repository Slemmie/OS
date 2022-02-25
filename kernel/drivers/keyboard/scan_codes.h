// convert interrupt scancodes to our own enum table

#pragma once

typedef enum {
	
	KEY_PRESS_RESERVED = 0,
	KEY_PRESS_ESCAPE   = 1,
	
	KEY_PRESS_1 = 2,
	KEY_PRESS_2 = 3,
	KEY_PRESS_3 = 4,
	KEY_PRESS_4 = 5,
	KEY_PRESS_5 = 6,
	KEY_PRESS_6 = 7,
	KEY_PRESS_7 = 8,
	KEY_PRESS_8 = 9,
	KEY_PRESS_9 = 10,
	KEY_PRESS_0 = 11,
	
	KEY_PRESS_MINUS     = 12, // '-'
	KEY_PRESS_EQUAL     = 13, // '='
	KEY_PRESS_BACKSPACE = 14,
	KEY_PRESS_TAB       = 15,
	
	KEY_PRESS_Q = 16,
	KEY_PRESS_W = 17,
	KEY_PRESS_E = 18,
	KEY_PRESS_R = 19,
	KEY_PRESS_T = 20,
	KEY_PRESS_Y = 21,
	KEY_PRESS_U = 22,
	KEY_PRESS_I = 23,
	KEY_PRESS_O = 24,
	KEY_PRESS_P = 25,
	
	KEY_PRESS_LEFT_SQ_BRACKET  = 26, // '['
	KEY_PRESS_RIGHT_SQ_BRACKET = 27, // ']'
	KEY_PRESS_ENTER            = 28,
	KEY_PRESS_LEFT_CTRL        = 29,
	
	KEY_PRESS_A = 30,
	KEY_PRESS_S = 31,
	KEY_PRESS_D = 32,
	KEY_PRESS_F = 33,
	KEY_PRESS_G = 34,
	KEY_PRESS_H = 35,
	KEY_PRESS_J = 36,
	KEY_PRESS_K = 37,
	KEY_PRESS_L = 38,
	
	KEY_PRESS_SEMI_COLON = 39, // ';'
	KEY_PRESS_APOSTROPHE = 40, // '''
	KEY_PRESS_GRAVE      = 41, // '`'
	KEY_PRESS_LEFT_SHIFT = 42,
	KEY_PRESS_BACK_SLASH = 43, // '\'
	
	KEY_PRESS_Z = 30,
	KEY_PRESS_X = 31,
	KEY_PRESS_C = 32,
	KEY_PRESS_V = 33,
	KEY_PRESS_B = 34,
	KEY_PRESS_N = 35,
	KEY_PRESS_M = 36,
	
	KEY_PRESS_COMMA       = 51, // ','
	KEY_PRESS_DOT         = 52, // '.'
	KEY_PRESS_SLASH       = 53, // '/'
	KEY_PRESS_RIGHT_SHIFT = 54,
	KEY_PRESS_KP_ASTERISK = 55, // '*' (keypad)
	KEY_PRESS_LEFT_ALT    = 56,
	KEY_PRESS_SPACE       = 57, // ' '
	KEY_PRESS_CAPS_LOCK   = 58,
	
	KEY_PRESS_F1  = 59,
	KEY_PRESS_F2  = 60,
	KEY_PRESS_F3  = 61,
	KEY_PRESS_F4  = 62,
	KEY_PRESS_F5  = 63,
	KEY_PRESS_F6  = 64,
	KEY_PRESS_F7  = 65,
	KEY_PRESS_F8  = 66,
	KEY_PRESS_F9  = 67,
	KEY_PRESS_F10 = 68,
	
	KEY_PRESS_NUM_LOCK    = 69,
	KEY_PRESS_SCROLL_LOCK = 70,
	
	KEY_PRESS_KP_7     = 71,
	KEY_PRESS_KP_8     = 72,
	KEY_PRESS_KP_9     = 73,
	
	KEY_PRESS_KP_MINUS = 74, // '-' (keypad)
	
	KEY_PRESS_KP_4     = 75,
	KEY_PRESS_KP_5     = 76,
	KEY_PRESS_KP_6     = 77,
	
	KEY_PRESS_KP_PLUS  = 78, // '+' (keypad)
	
	KEY_PRESS_KP_1     = 79,
	KEY_PRESS_KP_2     = 80,
	KEY_PRESS_KP_3     = 81,
	KEY_PRESS_KP_0     = 82,
	
	KEY_PRESS_KP_DOT   = 83, // '.' (keypad)
	
	KEY_UNKNOWN_SCANCODE_84 = 84, // does not exist ?
	
	KEY_PRESS_ZENKAKU_HANKAKU = 85, // 'idfk' (japanese?)
	
	KEY_PRESS_102ND = 86, // non-US '\' and '|'
	
	KEY_PRESS_F11 = 87,
	KEY_PRESS_F12 = 88,
	
	KEY_PRESS_RO                  = 89, // 'idfk' (japanese?)
	KEY_PRESS_KATAKANA            = 90, // 'idfk' (japanese?)
	KEY_PRESS_HIRAGANA            = 91, // 'idfk' (japanese?)
	KEY_PRESS_HENKAN              = 92, // 'idfk' (japanese?) [right of spacebar]
	KEY_PRESS_KATAKANA_HIRAGANA   = 93, // 'idfk' (japanese?)
	KEY_PRESS_MUHENKAN            = 94, // 'idfk' (japanese?) [left of spacebar]
	KEY_PRESS_KP_JP_COMMA         = 95, // japanese comma (keypad)
	
	KEY_PRESS_KP_ENTER      = 96,
	KEY_PRESS_KP_RIGHT_CTRL = 97,
	KEY_PRESS_KP_SLASH      = 98, // '/' (keypad)
	
	KEY_PRESS_SYSRQ = 99, // SysRq (kernel panic)
	
	KEY_PRESS_RIGHT_ALT     = 100,
	KEY_PRESS_LINE_FEED     = 101,
	KEY_PRESS_HOME          = 102,
	KEY_PRESS_UP            = 103,
	KEY_PRESS_PAGE_UP       = 104,
	KEY_PRESS_LEFT          = 105,
	KEY_PRESS_RIGHT         = 106,
	KEY_PRESS_END           = 107,
	KEY_PRESS_DOWN          = 108,
	KEY_PRESS_PAGE_DOWN     = 109,
	KEY_PRESS_INSERT        = 110,
	KEY_PRESS_DELETE        = 111,
	KEY_PRESS_MACRO         = 112,
	KEY_PRESS_MUTE          = 113,
	KEY_PRESS_VOLUME_DOWN   = 114,
	KEY_PRESS_VOLUME_UP     = 115,
	KEY_PRESS_POWER         = 116,
	KEY_PRESS_KP_EQUAL      = 117, // '=' (keypad)
	KEY_PRESS_KP_PLUS_MINUS = 118, // '±' (keypad)
	KEY_PRESS_PAUSE         = 119,
	KEY_PRESS_SCALE         = 120,
	KEY_PRESS_KP_COMMA      = 121, // ',' (keypad)
	KEY_PRESS_HAGEUL        = 122, // tf ? ? ?
	KEY_PRESS_HAGUEL        = 122, // tf ?????
	KEY_PRESS_HANJA         = 123, // 'idfk' (japanese?)
	KEY_PRESS_YEN           = 124, // 'idfk' (japanese?)
	KEY_PRESS_LEFT_META     = 125,
	KEY_PRESS_RIGHT_META    = 126,
	KEY_PRESS_COMPOSE       = 127
	
} Keyboard_codes;
