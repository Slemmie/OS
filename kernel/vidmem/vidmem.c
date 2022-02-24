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
	return position / _VIDMEM_COL_CNT;
}

// get col of _vm_pos
uint_8 _vidmem_col_of(_vm_pos position) {
	return position % _VIDMEM_COL_CNT;
}

// get cursor position (_vm_pos format)
// does not correct for color bytes
_vm_pos _vidmem_get_cursor() {
	port_byte_out(_VIDMEM_REGISTER_SCREEN_CTRL, 14);
	_vm_pos result = port_byte_in(_VIDMEM_REGISTER_SCREEN_DATA) << 8;
	port_byte_out(_VIDMEM_REGISTER_SCREEN_CTRL, 15);
	result += port_byte_in(_VIDMEM_REGISTER_SCREEN_DATA);
	return result;
}

// scroll down a given number of lines
// does not update cursor position
void _vidmem_scroll_down(uint_64 count) {
	if (!count) {
		return;
	}
	
	for (uint_8 row = 0; row < _VIDMEM_ROW_CNT - 1; row++) {
		for (uint_8 col = 0; col < _VIDMEM_COL_CNT; col++) {
			_VIDMEM_ADDRESS[_vidmem_position_of(row, col)    ] =
			_VIDMEM_ADDRESS[_vidmem_position_of(row + 1, col)];
			_VIDMEM_ADDRESS[_vidmem_position_of(row, col)     | 1] =
			_VIDMEM_ADDRESS[_vidmem_position_of(row + 1, col) | 1];
		}
	}
	
	for (uint_8 col = 0; col < _VIDMEM_COL_CNT; col++) {
		_VIDMEM_ADDRESS[_vidmem_position_of(_VIDMEM_ROW_CNT - 1, col)    ] = 0x00;
		_VIDMEM_ADDRESS[_vidmem_position_of(_VIDMEM_ROW_CNT - 1, col) | 1] = 0x0f;
	}
	
	if (--count) {
		_vidmem_scroll_down(count);
	}
}

// advance cursor by count
// handle end of line
// handle scrolling
// updates cursor position at the end
void _vidmem_advance_cursor(uint_64 count) {
	if (!count) {
		return;
	}
	
	uint_8 row = _vidmem_row_of(_vidmem_get_cursor());
	uint_8 col = _vidmem_col_of(_vidmem_get_cursor());
	
	col++;
	
	// end of line?
	if (col >= _VIDMEM_COL_CNT) {
		col = 0;
		row++;
	}
	
	// handle scrolling
	while (row >= _VIDMEM_ROW_CNT) {
		_vidmem_scroll_down(1);
		row--;
	}
	
	vidmem_set_cursor(row, col);
	
	if (--count) {
		_vidmem_advance_cursor(count);
	}
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
	return _vidmem_row_of(_vidmem_get_cursor());
}

// get cursor position col
uint_8 vidmem_cursor_col() {
	return _vidmem_col_of(_vidmem_get_cursor());
}

// clear the screen
void vidmem_clear_screen() {
	for (uint_8 row = 0; row < _VIDMEM_ROW_CNT; row++) {
		for (uint_8 col = 0; col < _VIDMEM_COL_CNT; col++) {
			_VIDMEM_ADDRESS[_vidmem_position_of(row, col)    ] = 0x00;
			_VIDMEM_ADDRESS[_vidmem_position_of(row, col) | 1] = 0x0f;
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

// put a char then advance cursor
void vidmem_putchar(uint_8 data) {
	if (data == '\n') {
		uint_8 col = 0;
		uint_8 row = vidmem_cursor_row() + 1;
		while (row >= _VIDMEM_ROW_CNT) {
			_vidmem_scroll_down(1);
			row--;
		}
		vidmem_set_cursor(row, col);
		return;
	}
	
	_VIDMEM_ADDRESS[_vidmem_get_cursor() << 1] = data;
	
	_vidmem_advance_cursor(1);
}

// put a char with color then advance cursor
void vidmem_putchar_color(uint_8 data, uint_8 color) {
	if (data == '\n') {
		uint_8 col = 0;
		uint_8 row = vidmem_cursor_row() + 1;
		while (row >= _VIDMEM_ROW_CNT) {
			_vidmem_scroll_down(1);
			row--;
		}
		vidmem_set_cursor(row, col);
		return;
	}
	
	_VIDMEM_ADDRESS[(_vidmem_get_cursor() << 1)    ] =  data;
	_VIDMEM_ADDRESS[(_vidmem_get_cursor() << 1) | 1] = color;
	
	_vidmem_advance_cursor(1);
}

// put chars and advance cursor
void vidmem_puts(uint_8* data) {
	for (uint_8* it = data; *it != '\0'; it++) {
		vidmem_putchar(*it);
	}
}

// put chars with color and advance cursor
void vidmem_puts_color(uint_8* data, uint_8 color) {
	for (uint_8* it = data; *it != '\0'; it++) {
		vidmem_putchar_color(*it, color);
	}
}
