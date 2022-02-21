// implementation of vid_mem functions

#include "vid_mem.h"

void vidmem_putchar(int row, int col, char value, char color) {
	if (color == 0) {
		color = 0x0f;
	}
	((char*)0x000b8002)[(row * 80 + col) * 2] = value;
	((char*)0x000b8002)[(row * 80 + col) * 2 + 1] = color;
}
