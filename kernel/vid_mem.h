// functions for writing to/managing vid_mem display

#pragma once

// put a single char to vid_mem at row/col
void vidmem_putchar(int row, int col, char value, char color);

// put a string to vid_mem at row/col
void vidmem_puts(int row, int col, const char* string, char color);
