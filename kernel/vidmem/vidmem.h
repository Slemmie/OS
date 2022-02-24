// video memory address writing

#pragma once

#include "../util/types.h"

// set cursor position
void vidmem_set_cursor(uint_8 row, uint_8 col);

// clear the screen
void vidmem_clear_screen();
// clear screen to a specific color
void vidmem_clear_screen_color(uint_8 color);
