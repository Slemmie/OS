// functions for writing to/managing vid_mem display

#pragma once

// use color = 0 to default to white on black
// put a single char to vid_mem at row/col
void vidmem_putchar_exact(int row, int col, char value, char color);
// overload with row and col being appended to
void vidmem_putchar(char value, char color);

// use color = 0 to default to white on black
// put a string to vid_mem at row/col
void vidmem_puts_exact(int row, int col, const char* string, char color);
// overload with row and col being appended to
void vidmem_puts(const char* string, char color);

// set the cursor
void vidmem_set_cursor(int row, int col);

// get the cursor
int vidmem_get_cursor_row();
int vidmem_get_cursor_col();

// clear the entire screan
void vidmem_clear_screen();
