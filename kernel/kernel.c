// kernel written in C

#include "vid_mem.h"

void main() {
	// sample program
	// write a character to vid-mem
	
	vidmem_clear_screen();
	vidmem_set_cursor(0, 0);
	for (int i = 0; i < 80 * 25 + 5; i++) {
		vidmem_putchar('0' + (i % 10), 0);
	}
	
}
