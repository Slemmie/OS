// implementation of vid_mem functions

#include "vid_mem.h"

#include "port_io.h"

// Screen device I/O ports
#define REGISTER_SCREEN_CTRL 0x3D4
#define REGISTER_SCREEN_DATA 0x3D5

// address of beginning of vid_mem
#define VIDEO_MEM_ADDRESS 0xb8000

// dimensions
#define ROW_CNT 25
#define COL_CNT 80

int vidmem_get_offset(int row, int col) {
	return (row * COL_CNT + col) * 2;
}

int vidmem_get_cursor() {
	port_byte_out(REGISTER_SCREEN_CTRL, 14);
	int result = port_byte_in(REGISTER_SCREEN_DATA) << 8;
	port_byte_out(REGISTER_SCREEN_CTRL, 15);
	result += port_byte_in(REGISTER_SCREEN_DATA);
	return result;
}

int vidmem_get_cursor_row() {
	return vidmem_get_cursor() / COL_CNT;
}

int vidmem_get_cursor_col() {
	return vidmem_get_cursor() % COL_CNT;
}

void vidmem_set_cursor(int row, int col) {
	int offset = vidmem_get_offset(row, col);
	offset /= 2;
    port_byte_out(REGISTER_SCREEN_CTRL, 14);
    port_byte_out(REGISTER_SCREEN_DATA, (unsigned char)(offset >> 8));
    port_byte_out(REGISTER_SCREEN_CTRL, 15);
    port_byte_out(REGISTER_SCREEN_DATA, offset);
}

void vidmem_advance_cursor(int* row, int* col) {
	(*col)++;
	if (*col >= COL_CNT) {
		*col = 0;
		(*row)++;
	}
	if (*row >= ROW_CNT) {
		(*row)--;
		// scroll once
		for (int i = 1; i < ROW_CNT; i++) {
			for (int j = 0; j < COL_CNT; j++) {
				((char*)VIDEO_MEM_ADDRESS)[vidmem_get_offset(i - 1, j)] =
				((char*)VIDEO_MEM_ADDRESS)[vidmem_get_offset(i, j)];
				((char*)VIDEO_MEM_ADDRESS)[vidmem_get_offset(i - 1, j) + 1] =
				((char*)VIDEO_MEM_ADDRESS)[vidmem_get_offset(i, j) + 1];
			}
		}
		for (int j = 0; j < COL_CNT; j++) {
			((char*)VIDEO_MEM_ADDRESS)[vidmem_get_offset(ROW_CNT - 1, j)] = '\0';
		}
	}
	vidmem_set_cursor(*row, *col);
}

void vidmem_putchar_exact(int row, int col, char value, char color) {
	if (color == 0) {
		color = 0x0f;
	}
	((char*)VIDEO_MEM_ADDRESS)[vidmem_get_offset(row, col)] = value;
	((char*)VIDEO_MEM_ADDRESS)[vidmem_get_offset(row, col) + 1] = color;
	vidmem_advance_cursor(&row, &col);
}

void vidmem_putchar(char value, char color) {
	vidmem_putchar_exact(vidmem_get_cursor_row(), vidmem_get_cursor_col(), value, color);
}

void vidmem_puts_exact(int row, int col, const char* string, char color) {
	for (int i = 0; string[i] != '\0'; i++) {
		vidmem_putchar_exact(row, col++, string[i], color);
	}
}

void vidmem_puts(const char* string, char color) {
	vidmem_puts_exact(vidmem_get_cursor_row(), vidmem_get_cursor_col(), string, color);
}

void vidmem_clear_screen() {
	for (int i = 0; i < ROW_CNT; i++) {
		for (int j = 0; j < COL_CNT; j++) {
			vidmem_putchar_exact(i, j, '\0', 0);
		}
	}
}
