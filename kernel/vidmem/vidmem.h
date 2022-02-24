// video memory address writing

#pragma once

#include "../util/types.h"

// put this define before including vidmem header to enable simplified function names as well
#ifdef VIDMEM_SIMPLIFIED_API

#define set_cursor         vidmem_set_cursor
#define cursor_row         vidmem_cursor_row
#define cursor_col         vidmem_cursor_col
#define clear_screen       vidmem_clear_screen
#define clear_screen_color vidmem_clear_screen_color
#define putchar            vidmem_putchar
#define putchar_color      vidmem_putchar_color
#define puts               vidmem_puts
#define puts_color         vidmem_puts_color

#endif

// set cursor position
void vidmem_set_cursor(uint_8 row, uint_8 col);

// get cursor position
// row
uint_8 vidmem_cursor_row();
// col
uint_8 vidmem_cursor_col();

// clear the screen
void vidmem_clear_screen();
// clear screen to a specific color
void vidmem_clear_screen_color(uint_8 color);

// put a character on the screen
// then advance cursor by one
void vidmem_putchar(uint_8 data);
// same as vidmem_putchar()
// but allows setting of FG/BG color as well
void vidmem_putchar_color(uint_8 data, uint_8 color);

// put a null-terminated string of characters on the screen
// also advance cursor by string length
void vidmem_puts(uint_8* data);
// same as vidmem_puts()
// but allows setting of FG/BG color as well
void vidmem_puts_color(uint_8* data, uint_8 color);
