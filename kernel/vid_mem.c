// implementation of vid_mem functions

#include "vid_mem.h"

void vidmem_putchar(int row, int col, char value, char color) {
	if (color == 0) {
		color = 0x0f;
	}
	((char*)0x000b8000)[(row * 80 + col) * 2] = value;
	((char*)0x000b8000)[(row * 80 + col) * 2 + 1] = color;
}

void vidmem_puts(int row, int col, const char* string, char color) {
	for (int i = 0; string[i] != '\0'; i++) {
		vidmem_putchar(row, col++, string[i], color);
	}
}
