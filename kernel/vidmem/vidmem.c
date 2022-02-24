// implementation of video memory functions

#include "vidmem.h"

#include "../port_io.h"
#include "../util/algorithm.h"

#define _VIDMEM_ROW_CNT 25
#define _VIDMEM_COL_CNT 80

#define _VIDMEM_ADDRESS ((uint_8*) 0xb8000)

#define _VIDMEM_REGISTER_SCREEN_CTRL 0x3d4
#define _VIDMEM_REGISTER_SCREEN_DATA 0x3d5

typedef uint_16 _vm_pos;

// begin utility (used only in vidmem.c)

// get _vm_pos of row and col
_vm_pos _vidmem_position_of(uint_8 row, uint_8 col) {
	return ((_vm_pos) row * _VIDMEM_COL_CNT + (_vm_pos) col) << 1;
}

// get row of _vm_pos
uint_8 _vidmem_row_of(_vm_pos position) {
	return (position >> 1) / _VIDMEM_COL_CNT;
}

// get col of _vm_pos
uint_8 _vidmem_col_of(_vm_pos position) {
	return (position >> 1) % _VIDMEM_COL_CNT;
}

// get cursor position (_vm_pos format)
_vm_pos vidmem_get_cursor() {
	port_byte_out(_VIDMEM_REGISTER_SCREEN_CTRL, 14);
	_vm_pos result = port_byte_in(_VIDMEM_REGISTER_SCREEN_DATA) << 8;
	port_byte_out(_VIDMEM_REGISTER_SCREEN_CTRL, 15);
	result += port_byte_in(_VIDMEM_REGISTER_SCREEN_DATA);
	return result;
}

// end utility (used only in vidmem.c)

// set cursor position
// caps row at _VIDMEM_ROW_CNT - 1
// caps col at _VIDMEM_COL_CNT - 1
void vidmem_set_cursor(uint_8 row, uint_8 col) {
	row = min(row, _VIDMEM_ROW_CNT - 1);
	col = min(col, _VIDMEM_COL_CNT - 1);
	_vm_pos position = _vidmem_position_of(row, col) >> 1;
	port_byte_out(_VIDMEM_REGISTER_SCREEN_CTRL, 0x0f);
	port_byte_out(_VIDMEM_REGISTER_SCREEN_DATA, (uint_8) position);
	port_byte_out(_VIDMEM_REGISTER_SCREEN_CTRL, 0x0e);
	port_byte_out(_VIDMEM_REGISTER_SCREEN_DATA, (uint_8) (position >> 8));
}

// get cursor position row
uint_8 vidmem_cursor_row() {
	return _vidmem_row_of(vidmem_get_cursor());
}

// get cursor position col
uint_8 vidmem_cursor_col() {
	return _vidmem_col_of(vidmem_get_cursor());
}

// clear the screen
void vidmem_clear_screen() {
	for (uint_8 row = 0; row < _VIDMEM_ROW_CNT; row++) {
		for (uint_8 col = 0; col < _VIDMEM_COL_CNT; col++) {
			_VIDMEM_ADDRESS[_vidmem_position_of(row, col)    ] = 0x00;
			_VIDMEM_ADDRESS[_vidmem_position_of(row, col) | 1] = 0x00;
		}
	}
}

// clear screen to a specific color
void vidmem_clear_screen_color(uint_8 color) {
	for (uint_8 row = 0; row < _VIDMEM_ROW_CNT; row++) {
		for (uint_8 col = 0; col < _VIDMEM_COL_CNT; col++) {
			_VIDMEM_ADDRESS[_vidmem_position_of(row, col)    ] =  0x00;
			_VIDMEM_ADDRESS[_vidmem_position_of(row, col) | 1] = color;
		}
	}
}
