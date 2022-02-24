// video memory address writing

#pragma once

#include "../util/types.h"

// put this define before including vidmem header to enable simplified aliases as well
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

#define FG_BLACK        VIDMEM_FG_BLACK
#define FG_BLUE         VIDMEM_FG_BLUE
#define FG_GREEN        VIDMEM_FG_GREEN
#define FG_CYAN         VIDMEM_FG_CYAN
#define FG_RED          VIDMEM_FG_RED
#define FG_PURPLE       VIDMEM_FG_PURPLE
#define FG_BROWN        VIDMEM_FG_BROWN
#define FG_GRAY         VIDMEM_FG_GRAY
#define FG_DARK_GRAY    VIDMEM_FG_DARK_GRAY
#define FG_LIGHT_BLUE   VIDMEM_FG_LIGHT_BLUE
#define FG_LIGHT_GREEN  VIDMEM_FG_LIGHT_GREEN
#define FG_LIGHT_CYAN   VIDMEM_FG_LIGHT_CYAN
#define FG_LIGHT_RED    VIDMEM_FG_LIGHT_RED
#define FG_LIGHT_PURPLE VIDMEM_FG_LIGHT_PURPLE
#define FG_YELLOW       VIDMEM_FG_YELLOW
#define FG_WHITE        VIDMEM_FG_WHITE

#define BG_BLACK        VIDMEM_BG_BLACK
#define BG_BLUE         VIDMEM_BG_BLUE
#define BG_GREEN        VIDMEM_BG_GREEN
#define BG_CYAN         VIDMEM_BG_CYAN
#define BG_RED          VIDMEM_BG_RED
#define BG_PURPLE       VIDMEM_BG_PURPLE
#define BG_BROWN        VIDMEM_BG_BROWN
#define BG_GRAY         VIDMEM_BG_GRAY
#define BG_DARK_GRAY    VIDMEM_BG_DARK_GRAY
#define BG_LIGHT_BLUE   VIDMEM_BG_LIGHT_BLUE
#define BG_LIGHT_GREEN  VIDMEM_BG_LIGHT_GREEN
#define BG_LIGHT_CYAN   VIDMEM_BG_LIGHT_CYAN
#define BG_LIGHT_RED    VIDMEM_BG_LIGHT_RED
#define BG_LIGHT_PURPLE VIDMEM_BG_LIGHT_PURPLE
#define BG_YELLOW       VIDMEM_BG_YELLOW
#define BG_WHITE        VIDMEM_BG_WHITE

#endif

// colors
// bitwise OR FG and BG together to get a color with both properties
typedef enum {
	
	VIDMEM_FG_BLACK        = 0x00,
	VIDMEM_FG_BLUE         = 0x01,
	VIDMEM_FG_GREEN        = 0x02,
	VIDMEM_FG_CYAN         = 0x03,
	VIDMEM_FG_RED          = 0x04,
	VIDMEM_FG_PURPLE       = 0x05,
	VIDMEM_FG_BROWN        = 0x06,
	VIDMEM_FG_GRAY         = 0x07,
	VIDMEM_FG_DARK_GRAY    = 0x08,
	VIDMEM_FG_LIGHT_BLUE   = 0x09,
	VIDMEM_FG_LIGHT_GREEN  = 0x0a,
	VIDMEM_FG_LIGHT_CYAN   = 0x0b,
	VIDMEM_FG_LIGHT_RED    = 0x0c,
	VIDMEM_FG_LIGHT_PURPLE = 0x0d,
	VIDMEM_FG_YELLOW       = 0x0e,
	VIDMEM_FG_WHITE        = 0x0f,
	
	VIDMEM_BG_BLACK        = 0x00,
	VIDMEM_BG_BLUE         = 0x10,
	VIDMEM_BG_GREEN        = 0x20,
	VIDMEM_BG_CYAN         = 0x30,
	VIDMEM_BG_RED          = 0x40,
	VIDMEM_BG_PURPLE       = 0x50,
	VIDMEM_BG_BROWN        = 0x60,
	VIDMEM_BG_GRAY         = 0x70,
	VIDMEM_BG_DARK_GRAY    = 0x80,
	VIDMEM_BG_LIGHT_BLUE   = 0x90,
	VIDMEM_BG_LIGHT_GREEN  = 0xa0,
	VIDMEM_BG_LIGHT_CYAN   = 0xb0,
	VIDMEM_BG_LIGHT_RED    = 0xc0,
	VIDMEM_BG_LIGHT_PURPLE = 0xd0,
	VIDMEM_BG_YELLOW       = 0xe0,
	VIDMEM_BG_WHITE        = 0xf0
	
} Vidmem_color;

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
void vidmem_puts(const uint_8* data);
// same as vidmem_puts()
// but allows setting of FG/BG color as well
void vidmem_puts_color(const uint_8* data, uint_8 color);
