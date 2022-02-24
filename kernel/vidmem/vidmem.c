// implementation of video memory functions

#include "vidmem.h"

#include "../port_io.h"
#include "../util/algorithm.h"

#define _VIDMEM_ROW_CNT 25
#define _VIDMEM_COL_CNT 80

#define _VIDMEM_ADDRESS ((uint_8*) 0xb8000)

typedef uint_16 _vm_pos;

// begin utility (used only in vidmem.c)

// get _vm_pos of row and col
_vm_pos _vidmem_position_of(uint_8 row, uint_8 col) {
	return (_vm_pos) row * _VIDMEM_COL_CNT + (_vm_pos) col;
}

// get row of _vm_pos
uint_8 _vidmem_row_of(_vm_pos position) {
	return position / _VIDMEM_COL_CNT;
}

// get col of _vm_pos
uint_8 _vidmem_col_of(_vm_pos position) {
	return position % _VIDMEM_COL_CNT;
}

// end utility (used only in vidmem.c)

// set cursor position
// caps row at _VIDMEM_ROW_CNT - 1
// caps col at _VIDMEM_COL_CNT - 1
void vidmem_set_cursor(uint_8 row, uint_8 col) {
	row = min(row, _VIDMEM_ROW_CNT - 1);
	col = min(col, _VIDMEM_COL_CNT - 1);
	_vm_pos position = _vidmem_position_of(row, col);
	port_byte_out(0x3d4, 0x0f);
	port_byte_out(0x3d5, (uint_8) position);
	port_byte_out(0x3d4, 0x0e);
	port_byte_out(0x3d5, (uint_8) (position >> 8));
}
